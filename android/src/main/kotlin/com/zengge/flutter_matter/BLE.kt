package com.zengge.flutter_matter

import android.os.Looper
import android.util.Log
import androidx.core.os.HandlerCompat
import io.flutter.plugin.common.MethodChannel
import kotlinx.coroutines.runBlocking
import kotlinx.coroutines.withTimeoutOrNull
import org.json.JSONArray
import org.json.JSONObject
import java.util.concurrent.Executors

private val bleExecutors = FlutterMatterPlugin.executors

fun onBLECall(path: String, params: String, result: MethodChannel.Result) {
    matterPrint("onBLECall $path $params")
    fun callResultSuccess(data: Any) {
        HandlerCompat.createAsync(Looper.getMainLooper()).post {
            result.success(data)
        }
    }

    fun callResultError(errorMessage: String) {
        HandlerCompat.createAsync(Looper.getMainLooper()).post {
            result.error("-99", errorMessage, errorMessage)
        }
    }
    bleExecutors.execute {
        try {
            when (path) {
                "/connectDevice" -> {
                    callResultSuccess(connectDevice(params))
                }

                "/disconnect" -> {
                    callResultSuccess(disconnect(params))
                }

                "/setBlePlatformDelegate" -> {
                    callResultSuccess(setBlePlatformDelegate(params))
                }

                "/handleSubscribeComplete" -> {
                    callResultSuccess(handleSubscribeComplete(params))
                }

                "/handleWriteConfirmation" -> {
                    callResultSuccess(handleWriteConfirmation(params))
                }

                "/handleIndicationReceived" -> {
                    callResultSuccess(handleIndicationReceived(params))
                }

                "/handleUnsubscribeComplete" -> {
                    callResultSuccess(handleUnsubscribeComplete(params))
                }

                "/handleConnectionError" -> {
                    callResultSuccess(handleConnectionError(params))
                }

                else -> {
                    throw IllegalArgumentException("Unknown path: $path")
                }
            }
        } catch (e: Exception) {
            e.printStackTrace()
            callResultError(e.stackTraceToString())
        }
    }
}

private val connectingDevices = mutableSetOf<BluetoothManager>()

fun connectDevice(params: String): String {
    val jsonObject = JSONObject(params)
//    val setupPinCode = jsonObject.optNotNull("setupPinCode").toString().toLong()
    val discriminator = jsonObject.optNotNull("discriminator").toString().toInt()
    val isShortDiscriminator = jsonObject.optNotNull("isShortDiscriminator") == true
    val result = runBlocking<Int> {
        val bluetoothManager = BluetoothManager()
        connectingDevices.add(bluetoothManager)
        val device = bluetoothManager.getBluetoothDevice(
            FlutterMatterPlugin.globalContext!!,
            discriminator,
            isShortDiscriminator
        )
        if (device == null) {
            connectingDevices.remove(bluetoothManager)
            return@runBlocking -1
        }

        val gatt = withTimeoutOrNull(7 * 1000) {
            bluetoothManager.connect(FlutterMatterPlugin.globalContext!!, device)
        }
        if (gatt == null) {
            connectingDevices.remove(bluetoothManager)
            return@runBlocking -1
        }

        return@runBlocking bluetoothManager.connectionId
    }
    return createFlutterRequestResult(0, JSONObject(mapOf("data" to result)))
}

fun disconnect(params: String): String {
    val jsonObject = JSONObject(params)
    val connectId = jsonObject.optNotNull("connectId").toString().toInt()
    ChipClient.getAndroidChipPlatform(FlutterMatterPlugin.globalContext).bleManager.onCloseConnection(
        connectId
    )
    return createFlutterRequestResult(0, JSONObject())
}

fun setBlePlatformDelegate(params: String): String {
    val jsonObject = JSONObject(params)
    val handleId = jsonObject.opt(jsonKeyHandle)
    val bleManager: ZGAndroidBleManager =
        ChipClient.getAndroidChipPlatform(FlutterMatterPlugin.globalContext!!).bleManager as ZGAndroidBleManager
    if (handleId == JSONObject.NULL) {
        bleManager.platformDelegate = null
    } else {
        bleManager.platformDelegate = object : ZGAndroidBleManager.BlePlatformDelegate {
            override fun onSubscribeCharacteristic(
                connId: Int,
                svcId: ByteArray?,
                charId: ByteArray?
            ): Boolean {
                val result =
                    FlutterMatterPlugin.externalChannel!!.invokeMethodBlockGet(
                        createFlutterCallPath(
                            bleHost,
                            "BlePlatformDelegate/subscribeCharacteristic"
                        ),
                        JSONObject(
                            mapOf(
                                jsonKeyHandle to handleId,
                                "connObj" to connId,
                                "svcId" to JSONArray(svcId ?: ByteArray(0)),
                                "charId" to JSONArray(charId ?: ByteArray(0))
                            )
                        ).toString()
                    )
                return if (result == null) false else JSONObject(result).optBoolean("data")
            }

            override fun onUnsubscribeCharacteristic(
                connId: Int,
                svcId: ByteArray?,
                charId: ByteArray?
            ): Boolean {
                val result = FlutterMatterPlugin.externalChannel!!.invokeMethodBlockGet(
                    createFlutterCallPath(bleHost, "BlePlatformDelegate/unsubscribeCharacteristic"),
                    JSONObject(
                        mapOf(
                            jsonKeyHandle to handleId,
                            "connObj" to connId,
                            "svcId" to JSONArray(svcId ?: ByteArray(0)),
                            "charId" to JSONArray(charId ?: ByteArray(0))
                        )
                    ).toString()
                )
                return if (result == null) false else JSONObject(result).optBoolean("data")
            }

            override fun onCloseConnection(connId: Int): Boolean {
                val result = FlutterMatterPlugin.externalChannel!!.invokeMethodBlockGet(
                    createFlutterCallPath(bleHost, "BlePlatformDelegate/closeConnection"),
                    JSONObject(
                        mapOf(
                            jsonKeyHandle to handleId,
                            "connObj" to connId,
                        )
                    ).toString()
                )
                return if (result == null) false else JSONObject(result).optBoolean("data")

            }

            override fun onSendWriteRequest(
                connId: Int,
                svcId: ByteArray?,
                charId: ByteArray?,
                characteristicData: ByteArray?
            ): Boolean {
                val result = FlutterMatterPlugin.externalChannel!!.invokeMethodBlockGet(
                    createFlutterCallPath(bleHost, "BlePlatformDelegate/sendWriteRequest"),
                    JSONObject(
                        mapOf(
                            jsonKeyHandle to handleId,
                            "connObj" to connId,
                            "svcId" to JSONArray(svcId ?: ByteArray(0)),
                            "charId" to JSONArray(charId ?: ByteArray(0)),
                            "data" to JSONArray(characteristicData ?: ByteArray(0))
                        )
                    ).toString()
                )
                return if (result == null) false else JSONObject(result).optBoolean("data")

            }

            override fun onGetMTU(connId: Int): Int {
                val result = FlutterMatterPlugin.externalChannel!!.invokeMethodBlockGet(
                    createFlutterCallPath(bleHost, "BlePlatformDelegate/getMTU"),
                    JSONObject(
                        mapOf(
                            jsonKeyHandle to handleId,
                            "connObj" to connId,
                        )
                    ).toString()
                )
                if (result == null) throw RuntimeException("Flutter onGetMTU result is null")
                return JSONObject(result).optNotNull("data").toString().toInt()
            }
        }
    }
    return createFlutterRequestResult(0, JSONObject())
}

fun handleSubscribeComplete(params: String): String {
    val jsonObject = JSONObject(params)
    val connId = jsonObject.optNotNull("connObj").toString().toInt()
    val svcId = jsonObject.getJSONArray("svcId").toByteArray()
    val charId = jsonObject.getJSONArray("charId").toByteArray()
    val success = jsonObject.optBoolean("success")
    ChipClient.getAndroidChipPlatform(FlutterMatterPlugin.globalContext!!)
        .handleSubscribeComplete(connId, svcId, charId, success)
    return createFlutterRequestResult(0, JSONObject())
}

fun handleWriteConfirmation(params: String): String {
    val jsonObject = JSONObject(params)
    val connId = jsonObject.optNotNull("connObj").toString().toInt()
    val svcId = jsonObject.getJSONArray("svcId").toByteArray()
    val charId = jsonObject.getJSONArray("charId").toByteArray()
    val success = jsonObject.optBoolean("success")
    ChipClient.getAndroidChipPlatform(FlutterMatterPlugin.globalContext!!)
        .handleWriteConfirmation(connId, svcId, charId, success)
    return createFlutterRequestResult(0, JSONObject())
}

fun handleIndicationReceived(params: String): String {
    val jsonObject = JSONObject(params)
    val connId = jsonObject.optNotNull("connObj").toString().toInt()
    val svcId = jsonObject.getJSONArray("svcId").toByteArray()
    val charId = jsonObject.getJSONArray("charId").toByteArray()
    val data = jsonObject.getJSONArray("pBuf").toByteArray()
    ChipClient.getAndroidChipPlatform(FlutterMatterPlugin.globalContext!!)
        .handleIndicationReceived(connId, svcId, charId, data)
    return createFlutterRequestResult(0, JSONObject())
}

fun handleUnsubscribeComplete(params: String): String {
    val jsonObject = JSONObject(params)
    val connId = jsonObject.optNotNull("connObj").toString().toInt()
    val svcId = jsonObject.getJSONArray("svcId").toByteArray()
    val charId = jsonObject.getJSONArray("charId").toByteArray()
    val success = jsonObject.optBoolean("success")
    ChipClient.getAndroidChipPlatform(FlutterMatterPlugin.globalContext!!)
        .handleUnsubscribeComplete(connId, svcId, charId, success)
    return createFlutterRequestResult(0, JSONObject())
}

fun handleConnectionError(params: String): String {
    val jsonObject = JSONObject(params)
    val connId = jsonObject.optNotNull("connObj").toString().toInt()
//    val err = jsonObject.optNotNull("err").toString().toInt()
    ChipClient.getAndroidChipPlatform(FlutterMatterPlugin.globalContext!!)
        .handleConnectionError(connId)
    return createFlutterRequestResult(0, JSONObject())
}