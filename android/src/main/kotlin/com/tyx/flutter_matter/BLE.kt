package com.tyx.flutter_matter

import io.flutter.plugin.common.MethodChannel
import kotlinx.coroutines.runBlocking
import kotlinx.coroutines.withTimeoutOrNull
import org.json.JSONArray
import org.json.JSONObject
import java.util.concurrent.RejectedExecutionException

private val bleExecutors = FlutterMatterPlugin.executors

fun onBLECall(path: String, params: String, result: MethodChannel.Result) {
    matterPrint("onBLECall $path")
    try {
        bleExecutors.execute {
            try {
                val response = when (path) {
                    "/connectDevice" -> connectDevice(params)
                    "/disconnect" -> disconnect(params)
                    "/setBlePlatformDelegate" -> setBlePlatformDelegate(params)
                    "/handleSubscribeComplete" -> handleSubscribeComplete(params)
                    "/handleWriteConfirmation" -> handleWriteConfirmation(params)
                    "/handleIndicationReceived" -> handleIndicationReceived(params)
                    "/handleUnsubscribeComplete" -> handleUnsubscribeComplete(params)
                    "/handleConnectionError" -> handleConnectionError(params)
                    else -> throw IllegalArgumentException("Unknown BLE request path")
                }
                result.postPlatformSuccess(response, "BLE $path")
            } catch (e: Exception) {
                reportPlatformException("BLE $path failed", e)
                result.postPlatformError(
                    "-99",
                    safePlatformErrorMessage("BLE", e),
                    safePlatformErrorDetails(e),
                    "BLE $path"
                )
            }
        }
    } catch (e: RejectedExecutionException) {
        reportPlatformException("BLE $path submission failed", e)
        result.postPlatformError(
            "-99",
            "BLE operation is not available",
            safePlatformErrorDetails(e),
            "BLE $path"
        )
    }
}

private val connectingDevices = mutableSetOf<BluetoothManager>()

fun connectDevice(params: String): String {
    val jsonObject = JSONObject(params)
//    val setupPinCode = jsonObject.optNotNull("setupPinCode").toString().toLong()
    val discriminator = jsonObject.requiredIntParam("discriminator")
    val isShortDiscriminator = jsonObject.requiredBooleanParam("isShortDiscriminator")
    val context = FlutterMatterPlugin.globalContext
        ?: throw IllegalStateException("Plugin context is unavailable")
    val result = runBlocking<Int> {
        val bluetoothManager = BluetoothManager()
        connectingDevices.add(bluetoothManager)
        try {
            val device = bluetoothManager.getBluetoothDevice(
                context,
                discriminator,
                isShortDiscriminator
            )
            if (device == null) {
                connectingDevices.remove(bluetoothManager)
                return@runBlocking -1
            }

            val gatt = withTimeoutOrNull(7 * 1000) {
                bluetoothManager.connect(context, device)
            }
            if (gatt == null) {
                connectingDevices.remove(bluetoothManager)
                bluetoothManager.releaseConnection()
                return@runBlocking -1
            }

            return@runBlocking bluetoothManager.connectionId
        } catch (e: Exception) {
            connectingDevices.remove(bluetoothManager)
            bluetoothManager.releaseConnection()
            throw e
        }
    }
    return createFlutterRequestResult(0, JSONObject(mapOf("data" to result)))
}

fun disconnect(params: String): String {
    val jsonObject = JSONObject(params)
    val connectId = jsonObject.requiredIntParam("connectId")
    val context = FlutterMatterPlugin.globalContext
        ?: throw IllegalStateException("Plugin context is unavailable")
    ChipClient.getAndroidChipPlatform(context).bleManager.onCloseConnection(
        connectId
    )
    return createFlutterRequestResult(0, JSONObject())
}

fun setBlePlatformDelegate(params: String): String {
    val jsonObject = JSONObject(params)
    val handleId = jsonObject.opt(jsonKeyHandle)
    val context = FlutterMatterPlugin.globalContext
        ?: throw IllegalStateException("Plugin context is unavailable")
    val bleManager: ZGAndroidBleManager =
        ChipClient.getAndroidChipPlatform(context).bleManager as ZGAndroidBleManager
    if (handleId == null || handleId == JSONObject.NULL) {
        bleManager.platformDelegate = null
    } else {
        if (handleId !is String || handleId.isBlank()) {
            throw IllegalArgumentException("BlePlatformDelegate handle must be a non-empty string")
        }
        bleManager.platformDelegate = object : ZGAndroidBleManager.BlePlatformDelegate {
            override fun onSubscribeCharacteristic(
                connId: Int,
                svcId: ByteArray?,
                charId: ByteArray?
            ): Boolean {
                return invokeFlutterBleBoolean(
                    "BlePlatformDelegate/subscribeCharacteristic",
                    JSONObject(
                        mapOf(
                            jsonKeyHandle to handleId,
                            "connObj" to connId,
                            "svcId" to JSONArray(svcId ?: ByteArray(0)),
                            "charId" to JSONArray(charId ?: ByteArray(0))
                        )
                    )
                )
            }

            override fun onUnsubscribeCharacteristic(
                connId: Int,
                svcId: ByteArray?,
                charId: ByteArray?
            ): Boolean {
                return invokeFlutterBleBoolean(
                    "BlePlatformDelegate/unsubscribeCharacteristic",
                    JSONObject(
                        mapOf(
                            jsonKeyHandle to handleId,
                            "connObj" to connId,
                            "svcId" to JSONArray(svcId ?: ByteArray(0)),
                            "charId" to JSONArray(charId ?: ByteArray(0))
                        )
                    )
                )
            }

            override fun onCloseConnection(connId: Int): Boolean {
                return invokeFlutterBleBoolean(
                    "BlePlatformDelegate/closeConnection",
                    JSONObject(
                        mapOf(
                            jsonKeyHandle to handleId,
                            "connObj" to connId,
                        )
                    )
                )
            }

            override fun onSendWriteRequest(
                connId: Int,
                svcId: ByteArray?,
                charId: ByteArray?,
                characteristicData: ByteArray?
            ): Boolean {
                return invokeFlutterBleBoolean(
                    "BlePlatformDelegate/sendWriteRequest",
                    JSONObject(
                        mapOf(
                            jsonKeyHandle to handleId,
                            "connObj" to connId,
                            "svcId" to JSONArray(svcId ?: ByteArray(0)),
                            "charId" to JSONArray(charId ?: ByteArray(0)),
                            "data" to JSONArray(characteristicData ?: ByteArray(0))
                        )
                    )
                )
            }

            override fun onGetMTU(connId: Int): Int {
                val result = invokeFlutterBle(
                    "BlePlatformDelegate/getMTU",
                    JSONObject(
                        mapOf(
                            jsonKeyHandle to handleId,
                            "connObj" to connId,
                        )
                    )
                )
                return JSONObject(result).requiredIntParam("data")
            }
        }
    }
    return createFlutterRequestResult(0, JSONObject())
}

fun handleSubscribeComplete(params: String): String {
    val jsonObject = JSONObject(params)
    val connId = jsonObject.requiredIntParam("connObj")
    val svcId = jsonObject.requiredByteArrayParam("svcId")
    val charId = jsonObject.requiredByteArrayParam("charId")
    val success = jsonObject.requiredBooleanParam("success")
    val context = FlutterMatterPlugin.globalContext
        ?: throw IllegalStateException("Plugin context is unavailable")
    ChipClient.getAndroidChipPlatform(context)
        .handleSubscribeComplete(connId, svcId, charId, success)
    return createFlutterRequestResult(0, JSONObject())
}

fun handleWriteConfirmation(params: String): String {
    val jsonObject = JSONObject(params)
    val connId = jsonObject.requiredIntParam("connObj")
    val svcId = jsonObject.requiredByteArrayParam("svcId")
    val charId = jsonObject.requiredByteArrayParam("charId")
    val success = jsonObject.requiredBooleanParam("success")
    val context = FlutterMatterPlugin.globalContext
        ?: throw IllegalStateException("Plugin context is unavailable")
    ChipClient.getAndroidChipPlatform(context)
        .handleWriteConfirmation(connId, svcId, charId, success)
    return createFlutterRequestResult(0, JSONObject())
}

fun handleIndicationReceived(params: String): String {
    val jsonObject = JSONObject(params)
    val connId = jsonObject.requiredIntParam("connObj")
    val svcId = jsonObject.requiredByteArrayParam("svcId")
    val charId = jsonObject.requiredByteArrayParam("charId")
    val data = jsonObject.requiredByteArrayParam("pBuf")
    val context = FlutterMatterPlugin.globalContext
        ?: throw IllegalStateException("Plugin context is unavailable")
    ChipClient.getAndroidChipPlatform(context)
        .handleIndicationReceived(connId, svcId, charId, data)
    return createFlutterRequestResult(0, JSONObject())
}

fun handleUnsubscribeComplete(params: String): String {
    val jsonObject = JSONObject(params)
    val connId = jsonObject.requiredIntParam("connObj")
    val svcId = jsonObject.requiredByteArrayParam("svcId")
    val charId = jsonObject.requiredByteArrayParam("charId")
    val success = jsonObject.requiredBooleanParam("success")
    val context = FlutterMatterPlugin.globalContext
        ?: throw IllegalStateException("Plugin context is unavailable")
    ChipClient.getAndroidChipPlatform(context)
        .handleUnsubscribeComplete(connId, svcId, charId, success)
    return createFlutterRequestResult(0, JSONObject())
}

fun handleConnectionError(params: String): String {
    val jsonObject = JSONObject(params)
    val connId = jsonObject.requiredIntParam("connObj")
//    val err = jsonObject.optNotNull("err").toString().toInt()
    val context = FlutterMatterPlugin.globalContext
        ?: throw IllegalStateException("Plugin context is unavailable")
    ChipClient.getAndroidChipPlatform(context)
        .handleConnectionError(connId)
    return createFlutterRequestResult(0, JSONObject())
}

private fun invokeFlutterBle(path: String, params: JSONObject): String {
    val channel = FlutterMatterPlugin.externalChannel
        ?: throw IllegalStateException("Flutter BLE callback channel is unavailable")
    return channel.invokeMethodBlockGet(
        createFlutterCallPath(bleHost, path),
        params.toString()
    ) ?: throw IllegalStateException("Flutter BLE callback returned no result")
}

private fun invokeFlutterBleBoolean(path: String, params: JSONObject): Boolean {
    val result = invokeFlutterBle(path, params)
    return JSONObject(result).requiredBooleanParam("data")
}
