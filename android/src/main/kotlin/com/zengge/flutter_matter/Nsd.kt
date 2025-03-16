package com.zengge.flutter_matter

import android.content.Context
import android.os.Looper
import androidx.core.os.HandlerCompat
import chip.platform.ChipMdnsCallback
import chip.platform.NsdManagerServiceResolver
import io.flutter.plugin.common.MethodChannel
import org.json.JSONArray
import org.json.JSONObject
import java.util.Arrays
import java.util.UUID

private val nsdExecutors = FlutterMatterPlugin.executors

class CustomNsdManagerServiceResolver(
    context: Context?,
    nsdManagerResolverAvailState: NsdManagerResolverAvailState? = null,
    timeout: Long = 30000L
) : NsdManagerServiceResolver(context, nsdManagerResolverAvailState, timeout) {

    var resolveProxy: ((
        instanceName: String?,
        serviceType: String?,
        callbackHandle: Long,
        contextHandle:
        Long,
        chipMdnsCallback: ChipMdnsCallback) -> Unit)? = null
         set(value) {
            if (field != null && value != null) {
                throw RuntimeException("repeat set resolveProxy")
            }
            field = value
        }

    var publishProxy: ((
        serviceName: String?,
        hostName: String?,
        type: String?,
        port: Int,
        textEntriesKeys: Array<out String>?,
        textEntriesDatas: Array<out ByteArray>?,
        subTypes: Array<out String>?) -> Unit)? = null
        set(value) {
            if (field != null && value != null) {
                throw RuntimeException("repeat set publishProxy")
            }
            field = value
        }

    var removeServicesProxy: (() -> Unit)? = null
        set(value) {
            if (field != null && value != null) {
                throw RuntimeException("repeat set removeServicesProxy")
            }
            field = value
        }

    override fun resolve(
        instanceName: String?,
        serviceType: String?,
        callbackHandle: Long,
        contextHandle: Long,
        chipMdnsCallback: ChipMdnsCallback
    ) {
        if (resolveProxy != null) {
            return resolveProxy!!(instanceName, serviceType, callbackHandle, contextHandle, chipMdnsCallback)
        }
        return super.resolve(instanceName, serviceType, callbackHandle, contextHandle, chipMdnsCallback)
    }

    override fun publish(
        serviceName: String?,
        hostName: String?,
        type: String?,
        port: Int,
        textEntriesKeys: Array<out String>?,
        textEntriesDatas: Array<out ByteArray>?,
        subTypes: Array<out String>?
    ) {
        if (publishProxy != null) {
            return publishProxy!!(serviceName, hostName, type, port, textEntriesKeys, textEntriesDatas, subTypes)
        }
        return super.publish(serviceName, hostName, type, port, textEntriesKeys, textEntriesDatas, subTypes)
    }

    override fun removeServices() {
        if (removeServicesProxy != null) {
            return removeServicesProxy!!()
        }
        return super.removeServices()
    }
}


private val chipMdnsCallbackRef = HashMap<String, FlutterChipMdnsCallback>()

private class FlutterChipMdnsCallback(
    private val id: String,
    private val callbackHandle: Long,
    private val contextHandle: Long,
    private val chipMdnsCallback: ChipMdnsCallback
) {
    fun handleServiceResolve(
        instanceName: String,
        serviceType: String,
        hostName: String,
        address: String,
        port: Int,
        textEntries: Map<String, ByteArray>?
    ) {
        chipMdnsCallbackRef.remove(id)
        chipMdnsCallback.handleServiceResolve(instanceName, serviceType, hostName, address, port, textEntries, callbackHandle, contextHandle)
    }

    fun handleServiceBrowse(
        instanceName: Array<String?>?,
        serviceType: String?,
    ) {
        chipMdnsCallbackRef.remove(id)
        chipMdnsCallback.handleServiceBrowse(instanceName, serviceType, callbackHandle, contextHandle)
    }
}

fun onNsdCall(path: String, params: String, result: MethodChannel.Result) {
    matterPrint("onNsdCall $path $params")

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

    nsdExecutors.execute {
        try {
            when (path) {
                "/setResolve" -> {
                    callResultSuccess(setResolveProxy(params))
                }
                "/setPublish" -> {
                    callResultSuccess(setPublish(params))
                }
                "/setRemoveServices" -> {
                    callResultSuccess(setRemoveServices(params))
                }
                "/handleServiceResolve" -> {
                    callResultSuccess(handleServiceResolve(params))
                }
                "/handleServiceBrowse" -> {
                    callResultSuccess(handleServiceBrowse(params))
                }
            }

        } catch (e: Exception) {
            e.printStackTrace()
            callResultError(e.stackTraceToString())
        }
    }

}

private fun setResolveProxy(params: String): String {
    val jsonObject = JSONObject(params)
    val proxyHandle = jsonObject.opt("proxyHandle")
    val serviceResolver = ChipClient.getServiceResolver(FlutterMatterPlugin.globalContext!!) as CustomNsdManagerServiceResolver
    if (proxyHandle == JSONObject.NULL || proxyHandle == null) {
        serviceResolver.resolveProxy = null
    } else {
        serviceResolver.resolveProxy = fun (instanceName: String?, serviceType: String?, callbackHandle: Long, contextHandle: Long, chipMdnsCallback: ChipMdnsCallback) {
            val callbackHandleId = UUID.randomUUID().toString()
            chipMdnsCallbackRef[callbackHandleId] = FlutterChipMdnsCallback(callbackHandleId, callbackHandle, contextHandle, chipMdnsCallback)
            runOnWorkerThread(nsdExecutors) {
                try {
                    val result = FlutterMatterPlugin.externalChannel!!.invokeMethodBlockGet(
                        createFlutterCallPath(nsdHost, "resolve"),
                        JSONObject(mapOf(
                            jsonKeyHandle to proxyHandle,
                            "instanceName" to instanceName,
                            "serviceType" to serviceType,
                            "chipMdnsCallbackHandle" to callbackHandleId
                        )).toString()
                    )
                    if (result == null) {
                        throw RuntimeException("Flutter start resolve failed")
                    }
                } catch (e: Exception) {
                    chipMdnsCallbackRef.remove(callbackHandleId)
                    matterPrint("resolve exception: $e")
                }
            }
        }
    }
    return createFlutterRequestResult(0, JSONObject())
}

private fun setPublish(params: String): String {
    val jsonObject = JSONObject(params)
    val proxyHandle = jsonObject.opt("proxyHandle")
    val serviceResolver =
        ChipClient.getServiceResolver(FlutterMatterPlugin.globalContext!!) as CustomNsdManagerServiceResolver
    if (proxyHandle == JSONObject.NULL || proxyHandle == null) {
        serviceResolver.publishProxy = null
    } else {
        serviceResolver.publishProxy = fun(
            serviceName: String?,
            hostName: String?,
            type: String?,
            port: Int,
            textEntriesKeys: Array<out String>?,
            textEntriesDatas: Array<out ByteArray>?,
            subTypes: Array<out String>?
        ) {
            runOnWorkerThread(nsdExecutors) {
                try {
                    val result = FlutterMatterPlugin.externalChannel!!.invokeMethodBlockGet(
                        createFlutterCallPath(nsdHost, "publish"),
                        JSONObject(
                            mapOf(
                                jsonKeyHandle to proxyHandle,
                                "serviceName" to serviceName,
                                "hostName" to hostName,
                                "type" to type,
                                "port" to port,
                                "textEntriesKeys" to if (textEntriesKeys == null) null else JSONArray(
                                    textEntriesKeys.toList()
                                ),
                                "textEntriesDatas" to if (textEntriesDatas == null) null else JSONArray(textEntriesDatas.map { JSONArray(it) }),
                                "subTypes" to if (subTypes == null) null else JSONArray(subTypes.toList()),
                            )
                        ).toString()
                    )
                    if (result == null) {
                        throw RuntimeException("")
                    }
                } catch (e: Exception) {
                    e.printStackTrace()
                    matterPrint("Call flutter publish failed $e")
                }
            }
        }
    }
    return createFlutterRequestResult(0, JSONObject())
}

private fun setRemoveServices(params: String): String {
    val jsonObject = JSONObject(params)
    val proxyHandle = jsonObject.opt("proxyHandle")
    val serviceResolver =
        ChipClient.getServiceResolver(FlutterMatterPlugin.globalContext!!) as CustomNsdManagerServiceResolver
    if (proxyHandle == JSONObject.NULL || proxyHandle == null) {
        serviceResolver.removeServicesProxy = null
    } else {
        serviceResolver.removeServicesProxy = fun () {
            runOnWorkerThread(nsdExecutors) {
                try {
                    val result = FlutterMatterPlugin.externalChannel!!.invokeMethodBlockGet(
                        createFlutterCallPath(nsdHost, "removeServices"),
                        JSONObject(
                            mapOf(
                                jsonKeyHandle to proxyHandle,
                            )
                        ).toString()
                    )
                    if (result == null) {
                        throw RuntimeException("")
                    }
                } catch (e: Exception) {
                    e.printStackTrace()
                    matterPrint("Call flutter removeServices failed $e")
                }
            }
        }
    }
    return createFlutterRequestResult(0, JSONObject())
}

fun handleServiceResolve(params: String): String {
    val jsonObject = JSONObject(params)
    val handle = jsonObject.optNotNull(jsonKeyHandle).toString()
    val instanceName = jsonObject.optNotNull("serviceName").toString()
    val serviceType = jsonObject.optNotNull("serviceType").toString()
    val hostName = jsonObject.optNotNull("hostName").toString()
    val address = jsonObject.optNotNull("address").toString()
    val port = jsonObject.optNotNull("port").toString().toInt()
    val textEntriesJson = jsonObject.optJSONObject("attributes")
    var textEntries: HashMap<String, ByteArray>? = null
    if (textEntriesJson != JSONObject.NULL && textEntriesJson != null) {
        textEntries = HashMap()
        textEntriesJson.keys().forEach {
            textEntries[it] = textEntriesJson.optJSONArray(it)!!.toByteArray()
        }
    }
    val mdnsCallback = chipMdnsCallbackRef[handle] ?: throw RuntimeException("Not found handle [${handle}] callback")
    mdnsCallback.handleServiceResolve(instanceName, serviceType, hostName, address, port, textEntries)
    return createFlutterRequestResult(0, JSONObject())
}

fun handleServiceBrowse(params: String): String {
    val jsonObject = JSONObject(params)
    val handle = jsonObject.optNotNull(jsonKeyHandle).toString()
    val instanceNameJsonArray = jsonObject.optJSONArray("serviceNames")
    val serviceType = jsonObject.optNotNull("serviceType").toString()
    val mdnsCallback = chipMdnsCallbackRef[handle] ?: throw RuntimeException("Not found handle [${handle}] callback")
    val instanceName = mutableListOf<String>()
    if (instanceNameJsonArray != JSONObject.NULL && instanceNameJsonArray != null) {
        for (i in 0 until instanceNameJsonArray.length()) {
            instanceName.add(instanceNameJsonArray.getString(i))
        }
    }
    mdnsCallback.handleServiceBrowse(instanceName.toTypedArray(), serviceType)
    return createFlutterRequestResult(0, JSONObject())
}