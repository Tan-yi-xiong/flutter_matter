package com.tyx.flutter_matter

import android.annotation.SuppressLint
import android.bluetooth.BluetoothAdapter
import android.bluetooth.BluetoothDevice
import android.bluetooth.BluetoothGatt
import android.bluetooth.BluetoothGattCallback
import android.bluetooth.BluetoothGattCharacteristic
import android.bluetooth.BluetoothGattDescriptor
import android.bluetooth.BluetoothProfile
import android.bluetooth.le.ScanCallback
import android.bluetooth.le.ScanFilter
import android.bluetooth.le.ScanResult
import android.bluetooth.le.ScanSettings
import android.content.Context
import android.os.ParcelUuid
import android.util.Log
import chip.platform.AndroidBleManager
import chip.platform.BleCallback
import java.util.UUID
import kotlin.coroutines.resume
import kotlin.coroutines.resumeWithException
import kotlinx.coroutines.CancellableContinuation
import kotlinx.coroutines.channels.ProducerScope
import kotlinx.coroutines.channels.awaitClose
import kotlinx.coroutines.flow.callbackFlow
import kotlinx.coroutines.flow.first
import kotlinx.coroutines.suspendCancellableCoroutine
import kotlinx.coroutines.withTimeoutOrNull

private class BluetoothScanException(message: String, cause: Throwable? = null) :
  Exception(message, cause)

@SuppressLint("MissingPermission")
class BluetoothManager : BleCallback {
  private val bluetoothAdapter: BluetoothAdapter? = BluetoothAdapter.getDefaultAdapter()
  @Volatile
  private var bleGatt: BluetoothGatt? = null
  @Volatile
  var connectionId = 0
    private set

  private fun getServiceData(discriminator: Int): ByteArray {
    val opcode = 0
    val version = 0
    val versionDiscriminator = ((version and 0xf) shl 12) or (discriminator and 0xfff)
    return intArrayOf(opcode, versionDiscriminator, versionDiscriminator shr 8)
      .map { it.toByte() }
      .toByteArray()
  }

  private fun getServiceDataMask(isShortDiscriminator: Boolean): ByteArray {
    val shortDiscriminatorMask =
      when (isShortDiscriminator) {
        true -> 0x00
        false -> 0xff
      }
    return intArrayOf(0xff, shortDiscriminatorMask, 0xff).map { it.toByte() }.toByteArray()
  }

  suspend fun getBluetoothDevice(context: Context, discriminator: Int): BluetoothDevice? {
    return getBluetoothDevice(context, discriminator, false)
  }

  suspend fun getBluetoothDevice(
    context: Context,
    discriminator: Int,
    isShortDiscriminator: Boolean
  ): BluetoothDevice? {
    val adapter = bluetoothAdapter ?: run {
      Log.e(TAG, "Bluetooth adapter is unavailable")
      return null
    }
    if (!adapter.isEnabled && !adapter.enable()) {
      Log.e(TAG, "Unable to enable Bluetooth adapter")
      return null
    }

    val scanner =
      adapter.bluetoothLeScanner
        ?: run {
          Log.e(TAG, "No bluetooth scanner found")
          return null
        }

    return try {
      withTimeoutOrNull(10000) {
        callbackFlow {
          val producerScope: ProducerScope<BluetoothDevice> = this@callbackFlow
          val scanCallback =
            object : ScanCallback() {
              override fun onScanResult(callbackType: Int, result: ScanResult) {
                try {
                  val device = result.device
                  Log.i(TAG, "Bluetooth device scanned")

                  if (producerScope.channel.isClosedForSend) {
                    Log.w(TAG, "Bluetooth device was scanned, but channel is already closed")
                  } else {
                    val sendResult = producerScope.trySend(device)
                    if (sendResult.isFailure) {
                      Log.w(TAG, "Unable to deliver scanned Bluetooth device")
                    }
                  }
                } catch (e: Exception) {
                  reportPlatformException("Bluetooth scan result handling failed", e)
                  producerScope.close(BluetoothScanException("Bluetooth scan result failed", e))
                }
              }

              override fun onScanFailed(errorCode: Int) {
                try {
                  Log.e(TAG, "Bluetooth scan failed with status code $errorCode")
                  producerScope.close(
                    BluetoothScanException("Bluetooth scan failed with status code $errorCode")
                  )
                } catch (e: Exception) {
                  reportPlatformException("Bluetooth scan failure handling failed", e)
                }
              }
            }

          val serviceData = getServiceData(discriminator)
          val serviceDataMask = getServiceDataMask(isShortDiscriminator)

          val scanFilter =
            ScanFilter.Builder()
              .setServiceData(ParcelUuid(UUID.fromString(CHIP_UUID)), serviceData, serviceDataMask)
              .build()

          val scanSettings =
            ScanSettings.Builder().setScanMode(ScanSettings.SCAN_MODE_LOW_LATENCY).build()

          Log.i(TAG, "Starting Bluetooth scan serviceData: ${serviceData.map { it.toString(16) }} serviceDataMask: ${serviceDataMask.map { it.toString(16) }}")
          scanner.startScan(listOf(scanFilter), scanSettings, scanCallback)
          awaitClose {
            try {
              scanner.stopScan(scanCallback)
            } catch (e: Exception) {
              reportPlatformException("Bluetooth scan cleanup failed", e)
            }
          }
        }.first()
      }
    } catch (e: BluetoothScanException) {
      null
    }
  }

  /**
   * Connects to a [BluetoothDevice] and suspends until [BluetoothGattCallback.onServicesDiscovered]
   */
  suspend fun connect(context: Context, device: BluetoothDevice): BluetoothGatt? {
    return suspendCancellableCoroutine { continuation ->
      var gatt: BluetoothGatt? = null
      try {
        val bluetoothManager = ChipClient.getAndroidChipPlatform(context).bleManager
        val bluetoothGattCallback = getBluetoothGattCallback(context, continuation)

        Log.i(TAG, "Connecting")
        gatt = device.connectGatt(context, false, bluetoothGattCallback)
        if (gatt == null) {
          Log.e(TAG, "Bluetooth connect did not create a GATT client")
          continuation.resume(null)
          return@suspendCancellableCoroutine
        }

        bleGatt = gatt
        connectionId = bluetoothManager.addConnection(gatt)
        bluetoothManager.setBleCallback(this)
        continuation.invokeOnCancellation { closeGatt(gatt) }
      } catch (e: Exception) {
        reportPlatformException("Bluetooth connect failed", e)
        closeGatt(gatt)
        connectionId = 0
        if (continuation.isActive) {
          continuation.resumeWithException(e)
        }
      }
    }
  }

  private fun getBluetoothGattCallback(
    context: Context,
    continuation: CancellableContinuation<BluetoothGatt?>
  ): BluetoothGattCallback {
    val wrappedCallback = ChipClient.getAndroidChipPlatform(context).bleManager.callback
    return object : BluetoothGattCallback() {
      private val coroutineContinuation = continuation
      private val completionLock = Any()
      private var completionDelivered = false

      private fun completeConnection(gatt: BluetoothGatt?) {
        val shouldResume = synchronized(completionLock) {
          if (completionDelivered) {
            false
          } else {
            completionDelivered = true
            true
          }
        }
        if (shouldResume && coroutineContinuation.isActive) {
          coroutineContinuation.resume(gatt)
        }
      }

      private fun failConnection(error: Exception) {
        val shouldResume = synchronized(completionLock) {
          if (completionDelivered) {
            false
          } else {
            completionDelivered = true
            true
          }
        }
        if (shouldResume && coroutineContinuation.isActive) {
          coroutineContinuation.resumeWithException(error)
        }
      }

      private fun runCallback(operation: String, callback: () -> Unit): Boolean {
        return try {
          callback()
          true
        } catch (e: Exception) {
          reportPlatformException("Bluetooth $operation callback failed", e)
          failConnection(IllegalStateException("Bluetooth callback failed: $operation", e))
          false
        }
      }

      override fun onConnectionStateChange(gatt: BluetoothGatt?, status: Int, newState: Int) {
        Log.i(
          TAG,
          "onConnectionStateChange status = $status, newState = $newState"
        )
        try {
          super.onConnectionStateChange(gatt, status, newState)
        } catch (e: Exception) {
          reportPlatformException("Bluetooth onConnectionStateChange super callback failed", e)
        }
        if (!runCallback("onConnectionStateChange") {
            wrappedCallback.onConnectionStateChange(gatt, status, newState)
          }) {
          return
        }

        if (newState == BluetoothProfile.STATE_CONNECTED && status == BluetoothGatt.GATT_SUCCESS) {
          Log.i(TAG, "Discovering services")
          val discoveryStarted = try {
            gatt?.discoverServices() == true
          } catch (e: Exception) {
            reportPlatformException("Bluetooth service discovery failed", e)
            false
          }
          if (!discoveryStarted) {
            failConnection(IllegalStateException("Unable to discover Bluetooth services"))
          }
        } else if (newState == BluetoothProfile.STATE_DISCONNECTED || status != BluetoothGatt.GATT_SUCCESS) {
          completeConnection(null)
        }
      }

      override fun onServicesDiscovered(gatt: BluetoothGatt?, status: Int) {
        Log.d(TAG, "onServicesDiscovered status = $status")
        if (!runCallback("onServicesDiscovered") {
            wrappedCallback.onServicesDiscovered(gatt, status)
          }) {
          return
        }
        if (gatt == null || status != BluetoothGatt.GATT_SUCCESS) {
          completeConnection(null)
          return
        }

        Log.i(TAG, "Services discovered")
        val mtuRequested = try {
          gatt.requestMtu(247)
        } catch (e: Exception) {
          reportPlatformException("Bluetooth MTU request failed", e)
          false
        }
        if (!mtuRequested) {
          failConnection(IllegalStateException("Unable to request Bluetooth MTU"))
        }
      }

      override fun onMtuChanged(gatt: BluetoothGatt?, mtu: Int, status: Int) {
        Log.d(TAG, "onMtuChanged mtu = $mtu, status = $status")
        try {
          super.onMtuChanged(gatt, mtu, status)
        } catch (e: Exception) {
          reportPlatformException("Bluetooth onMtuChanged super callback failed", e)
        }
        if (!runCallback("onMtuChanged") {
            wrappedCallback.onMtuChanged(gatt, mtu, status)
          }) {
          return
        }
        if (gatt != null && status == BluetoothGatt.GATT_SUCCESS) {
          completeConnection(gatt)
        } else {
          completeConnection(null)
        }
      }

      override fun onCharacteristicChanged(
        gatt: BluetoothGatt,
        characteristic: BluetoothGattCharacteristic
      ) {
        Log.d(TAG, "onCharacteristicChanged: ${characteristic.uuid}")
        runCallback("onCharacteristicChanged") {
          wrappedCallback.onCharacteristicChanged(gatt, characteristic)
        }
      }

      override fun onCharacteristicRead(
        gatt: BluetoothGatt,
        characteristic: BluetoothGattCharacteristic,
        status: Int
      ) {
        Log.d(TAG, "onCharacteristicRead: ${characteristic.uuid} -> $status")
        runCallback("onCharacteristicRead") {
          wrappedCallback.onCharacteristicRead(gatt, characteristic, status)
        }
      }

      override fun onCharacteristicWrite(
        gatt: BluetoothGatt,
        characteristic: BluetoothGattCharacteristic,
        status: Int
      ) {
        Log.d(TAG, "onCharacteristicWrite: ${characteristic.uuid} -> $status")
        runCallback("onCharacteristicWrite") {
          wrappedCallback.onCharacteristicWrite(gatt, characteristic, status)
        }
      }

      override fun onDescriptorRead(
        gatt: BluetoothGatt,
        descriptor: BluetoothGattDescriptor,
        status: Int
      ) {
        Log.d(TAG, "onDescriptorRead: ${descriptor.uuid} -> $status")
        runCallback("onDescriptorRead") {
          wrappedCallback.onDescriptorRead(gatt, descriptor, status)
        }
      }

      override fun onDescriptorWrite(
        gatt: BluetoothGatt,
        descriptor: BluetoothGattDescriptor,
        status: Int
      ) {
        Log.d(TAG, "onDescriptorWrite: ${descriptor.uuid} -> $status")
        runCallback("onDescriptorWrite") {
          wrappedCallback.onDescriptorWrite(gatt, descriptor, status)
        }
      }

      override fun onReadRemoteRssi(gatt: BluetoothGatt, rssi: Int, status: Int) {
        Log.d(TAG, "onReadRemoteRssi: $rssi -> $status")
        runCallback("onReadRemoteRssi") {
          wrappedCallback.onReadRemoteRssi(gatt, rssi, status)
        }
      }

      override fun onReliableWriteCompleted(gatt: BluetoothGatt, status: Int) {
        Log.d(TAG, "onReliableWriteCompleted: $status")
        runCallback("onReliableWriteCompleted") {
          wrappedCallback.onReliableWriteCompleted(gatt, status)
        }
      }
    }
  }

  internal fun releaseConnection() {
    val gatt = bleGatt
    bleGatt = null
    connectionId = 0
    closeGatt(gatt)
  }

  private fun closeGatt(gatt: BluetoothGatt?) {
    if (gatt == null) {
      return
    }
    try {
      gatt.disconnect()
    } catch (e: Exception) {
      reportPlatformException("Bluetooth GATT disconnect cleanup failed", e)
    }
    try {
      gatt.close()
    } catch (e: Exception) {
      reportPlatformException("Bluetooth GATT close cleanup failed", e)
    }
  }

  companion object {
    private const val TAG = "chip.BluetoothManager"
    private const val CHIP_UUID = "0000FFF6-0000-1000-8000-00805F9B34FB"
  }

  override fun onCloseBleComplete(connId: Int) {
    releaseConnection()
    Log.d(TAG, "onCloseBleComplete")
  }

  override fun onNotifyChipConnectionClosed(connId: Int) {
    releaseConnection()
    Log.d(TAG, "onNotifyChipConnectionClosed")
  }
}

class ZGAndroidBleManager(context: Context) : AndroidBleManager(context) {

  @Volatile
  var platformDelegate: BlePlatformDelegate? = null
    set(value) {
      if (value != null && field != null) {
        throw IllegalStateException("BlePlatformDelegate is already set")
      }
      field = value
    }

  private fun reportCallbackFailure(operation: String, error: Exception) {
    reportPlatformException("Bluetooth GATT manager $operation failed", error)
  }

  override fun onSubscribeCharacteristic(
    connId: Int,
    svcId: ByteArray?,
    charId: ByteArray?
  ): Boolean {
    val delegate = platformDelegate
    if (delegate != null) {
      return try {
        delegate.onSubscribeCharacteristic(connId, svcId, charId)
      } catch (e: Exception) {
        reportCallbackFailure("onSubscribeCharacteristic", e)
        false
      }
    }
    return try {
      super.onSubscribeCharacteristic(connId, svcId, charId)
    } catch (e: Exception) {
      reportCallbackFailure("onSubscribeCharacteristic", e)
      false
    }
  }

  override fun onUnsubscribeCharacteristic(
    connId: Int,
    svcId: ByteArray?,
    charId: ByteArray?
  ): Boolean {
    val delegate = platformDelegate
    if (delegate != null) {
      return try {
        delegate.onUnsubscribeCharacteristic(connId, svcId, charId)
      } catch (e: Exception) {
        reportCallbackFailure("onUnsubscribeCharacteristic", e)
        false
      }
    }
    return try {
      super.onUnsubscribeCharacteristic(connId, svcId, charId)
    } catch (e: Exception) {
      reportCallbackFailure("onUnsubscribeCharacteristic", e)
      false
    }
  }

  override fun onCloseConnection(connId: Int): Boolean {
    val delegate = platformDelegate
    if (delegate != null) {
      return try {
        delegate.onCloseConnection(connId)
      } catch (e: Exception) {
        reportCallbackFailure("onCloseConnection", e)
        false
      }
    }
    return try {
      super.onCloseConnection(connId)
    } catch (e: Exception) {
      reportCallbackFailure("onCloseConnection", e)
      false
    }
  }

  override fun onSendWriteRequest(
    connId: Int,
    svcId: ByteArray?,
    charId: ByteArray?,
    characteristicData: ByteArray?
  ): Boolean {
    val delegate = platformDelegate
    if (delegate != null) {
      return try {
        delegate.onSendWriteRequest(connId, svcId, charId, characteristicData)
      } catch (e: Exception) {
        reportCallbackFailure("onSendWriteRequest", e)
        false
      }
    }
    return try {
      super.onSendWriteRequest(connId, svcId, charId, characteristicData)
    } catch (e: Exception) {
      reportCallbackFailure("onSendWriteRequest", e)
      false
    }
  }

  override fun onGetMTU(connId: Int): Int {
    val delegate = platformDelegate
    if (delegate != null) {
      return try {
        delegate.onGetMTU(connId)
      } catch (e: Exception) {
        reportCallbackFailure("onGetMTU", e)
        DEFAULT_ATT_MTU
      }
    }
    return try {
      super.onGetMTU(connId)
    } catch (e: Exception) {
      reportCallbackFailure("onGetMTU", e)
      DEFAULT_ATT_MTU
    }
  }

  interface BlePlatformDelegate {
    fun onSubscribeCharacteristic(connId: Int, svcId: ByteArray?, charId: ByteArray?): Boolean
    fun onUnsubscribeCharacteristic(connId: Int, svcId: ByteArray?, charId: ByteArray?): Boolean
    fun onCloseConnection(connId: Int): Boolean
    fun onSendWriteRequest(connId: Int, svcId: ByteArray?, charId: ByteArray?, characteristicData: ByteArray?): Boolean
    fun onGetMTU(connId: Int): Int
  }

  companion object {
    private const val DEFAULT_ATT_MTU = 23
  }
}
