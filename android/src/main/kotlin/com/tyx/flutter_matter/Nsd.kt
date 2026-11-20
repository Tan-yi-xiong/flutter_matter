package com.tyx.flutter_matter

import android.content.Context
import chip.platform.ChipMdnsCallback
import chip.platform.NsdManagerServiceResolver
import io.flutter.plugin.common.MethodChannel
import org.json.JSONArray
import org.json.JSONObject
import java.util.UUID
import java.util.concurrent.ConcurrentHashMap
import java.util.concurrent.RejectedExecutionException

private val nsdExecutors = FlutterMatterPlugin.executors
private const val NSD_CONTEXT = "NSD"

class CustomNsdManagerServiceResolver(
    context: Context?,
    nsdManagerResolverAvailState: NsdManagerResolverAvailState? = null,
    timeout: Long = 30000L
) : NsdManagerServiceResolver(context, nsdManagerResolverAvailState, timeout) {

    @Volatile
    var resolveProxy: ((
        instanceName: String?,
        serviceType: String?,
        callbackHandle: Long,
        contextHandle:
        Long,
        chipMdnsCallback: ChipMdnsCallback) -> Unit)? = null
         set(value) {
            if (field != null && value != null) {
                throw IllegalStateException("NSD resolve proxy is already set")
            }
            field = value
        }

    @Volatile
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
                throw IllegalStateException("NSD publish proxy is already set")
            }
            field = value
        }

    @Volatile
    var removeServicesProxy: (() -> Unit)? = null
        set(value) {
            if (field != null && value != null) {
                throw IllegalStateException("NSD remove-services proxy is already set")
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
        try {
            val proxy = resolveProxy
            if (proxy != null) {
                proxy(instanceName, serviceType, callbackHandle, contextHandle, chipMdnsCallback)
            } else {
                super.resolve(instanceName, serviceType, callbackHandle, contextHandle, chipMdnsCallback)
            }
        } catch (e: Exception) {
            reportNsdCallbackFailure("resolve", e)
        }
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
        try {
            val proxy = publishProxy
            if (proxy != null) {
                proxy(serviceName, hostName, type, port, textEntriesKeys, textEntriesDatas, subTypes)
            } else {
                super.publish(serviceName, hostName, type, port, textEntriesKeys, textEntriesDatas, subTypes)
            }
        } catch (e: Exception) {
            reportNsdCallbackFailure("publish", e)
        }
    }

    override fun removeServices() {
        try {
            val proxy = removeServicesProxy
            if (proxy != null) {
                proxy()
            } else {
                super.removeServices()
            }
        } catch (e: Exception) {
            reportNsdCallbackFailure("removeServices", e)
        }
    }
}


private val chipMdnsCallbackRef = ConcurrentHashMap<String, FlutterChipMdnsCallback>()

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
    matterPrint("onNsdCall $path")

    try {
        nsdExecutors.execute {
            try {
                val response = when (path) {
                    "/setResolve" -> setResolveProxy(params)
                    "/setPublish" -> setPublish(params)
                    "/setRemoveServices" -> setRemoveServices(params)
                    "/handleServiceResolve" -> handleServiceResolve(params)
                    "/handleServiceBrowse" -> handleServiceBrowse(params)
                    else -> throw IllegalArgumentException("Unknown NSD request path")
                }
                result.postPlatformSuccess(response, "NSD $path")
            } catch (e: Exception) {
                reportPlatformException("NSD $path failed", e)
                result.postPlatformError(
                    "-99",
                    safePlatformErrorMessage(NSD_CONTEXT, e),
                    safePlatformErrorDetails(e),
                    "NSD $path"
                )
            }
        }
    } catch (e: RejectedExecutionException) {
        reportPlatformException("NSD $path submission failed", e)
        result.postPlatformError(
            "-99",
            "NSD operation is not available",
            safePlatformErrorDetails(e),
            "NSD $path"
        )
    }
}

private fun nsdServiceResolver(): CustomNsdManagerServiceResolver {
    val context = FlutterMatterPlugin.globalContext
        ?: throw IllegalStateException("Plugin context is unavailable")
    return ChipClient.getServiceResolver(context) as? CustomNsdManagerServiceResolver
        ?: throw IllegalStateException("NSD service resolver is unavailable")
}

private fun nsdChannel(): MethodChannel {
    return FlutterMatterPlugin.externalChannel
        ?: throw IllegalStateException("Flutter NSD callback channel is unavailable")
}

private fun optionalProxyHandle(jsonObject: JSONObject): String? {
    val value = jsonObject.opt("proxyHandle")
    if (value == null || value == JSONObject.NULL) {
        return null
    }
    if (value !is String || value.isBlank()) {
        throw IllegalArgumentException("NSD proxy handle must be a non-empty string")
    }
    return value
}

private fun reportNsdCallbackFailure(context: String, error: Exception) {
    reportPlatformException("NSD $context failed", error)
}

private fun setResolveProxy(params: String): String {
    val jsonObject = JSONObject(params)
    val proxyHandle = optionalProxyHandle(jsonObject)
    val serviceResolver = nsdServiceResolver()
    if (proxyHandle == null) {
        serviceResolver.resolveProxy = null
    } else {
        serviceResolver.resolveProxy = fun (instanceName: String?, serviceType: String?, callbackHandle: Long, contextHandle: Long, chipMdnsCallback: ChipMdnsCallback) {
            val callbackHandleId = UUID.randomUUID().toString()
            chipMdnsCallbackRef[callbackHandleId] = FlutterChipMdnsCallback(callbackHandleId, callbackHandle, contextHandle, chipMdnsCallback)
            val task = Runnable {
                try {
                    val result = nsdChannel().invokeMethodBlockGet(
                        createFlutterCallPath(nsdHost, "resolve"),
                        JSONObject(mapOf(
                            jsonKeyHandle to proxyHandle,
                            "instanceName" to instanceName,
                            "serviceType" to serviceType,
                            "chipMdnsCallbackHandle" to callbackHandleId
                        )).toString()
                    )
                    if (result == null) {
                        throw IllegalStateException("Flutter NSD resolve returned no result")
                    }
                } catch (e: Exception) {
                    chipMdnsCallbackRef.remove(callbackHandleId)
                    reportNsdCallbackFailure("resolve callback", e)
                }
            }
            try {
                runOnWorkerThread(nsdExecutors, task)
            } catch (e: RejectedExecutionException) {
                chipMdnsCallbackRef.remove(callbackHandleId)
                reportNsdCallbackFailure("resolve callback submission", e)
            }
        }
    }
    return createFlutterRequestResult(0, JSONObject())
}

private fun setPublish(params: String): String {
    val jsonObject = JSONObject(params)
    val proxyHandle = optionalProxyHandle(jsonObject)
    val serviceResolver = nsdServiceResolver()
    if (proxyHandle == null) {
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
            val task = Runnable {
                try {
                    val result = nsdChannel().invokeMethodBlockGet(
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
                        throw IllegalStateException("Flutter NSD publish returned no result")
                    }
                } catch (e: Exception) {
                    reportNsdCallbackFailure("publish callback", e)
                }
            }
            try {
                runOnWorkerThread(nsdExecutors, task)
            } catch (e: RejectedExecutionException) {
                reportNsdCallbackFailure("publish callback submission", e)
            }
        }
    }
    return createFlutterRequestResult(0, JSONObject())
}

private fun setRemoveServices(params: String): String {
    val jsonObject = JSONObject(params)
    val proxyHandle = optionalProxyHandle(jsonObject)
    val serviceResolver = nsdServiceResolver()
    if (proxyHandle == null) {
        serviceResolver.removeServicesProxy = null
    } else {
        serviceResolver.removeServicesProxy = fun () {
            val task = Runnable {
                try {
                    val result = nsdChannel().invokeMethodBlockGet(
                        createFlutterCallPath(nsdHost, "removeServices"),
                        JSONObject(
                            mapOf(
                                jsonKeyHandle to proxyHandle,
                            )
                        ).toString()
                    )
                    if (result == null) {
                        throw IllegalStateException("Flutter NSD removeServices returned no result")
                    }
                } catch (e: Exception) {
                    reportNsdCallbackFailure("removeServices callback", e)
                }
            }
            try {
                runOnWorkerThread(nsdExecutors, task)
            } catch (e: RejectedExecutionException) {
                reportNsdCallbackFailure("removeServices callback submission", e)
            }
        }
    }
    return createFlutterRequestResult(0, JSONObject())
}

fun handleServiceResolve(params: String): String {
    val jsonObject = JSONObject(params)
    val handle = jsonObject.requiredStringParam(jsonKeyHandle)
    val instanceName = jsonObject.requiredStringParam("serviceName")
    val serviceType = jsonObject.requiredStringParam("serviceType")
    val hostName = jsonObject.requiredStringParam("hostName")
    val address = jsonObject.requiredStringParam("address")
    val port = jsonObject.requiredIntParam("port")
    val attributesValue = jsonObject.opt("attributes")
    var textEntries: HashMap<String, ByteArray>? = null
    if (attributesValue != null && attributesValue != JSONObject.NULL) {
        if (attributesValue !is JSONObject) {
            throw IllegalArgumentException("NSD attributes must be a JSON object")
        }
        textEntries = HashMap()
        attributesValue.keys().forEach { key ->
            val attributeValue = attributesValue.opt(key)
            if (attributeValue !is JSONArray) {
                throw IllegalArgumentException("NSD attribute values must be byte arrays")
            }
            textEntries[key] = attributeValue.toByteArray()
        }
    }
    val mdnsCallback = chipMdnsCallbackRef[handle]
        ?: throw IllegalStateException("NSD resolve callback is no longer available")
    mdnsCallback.handleServiceResolve(instanceName, serviceType, hostName, address, port, textEntries)
    return createFlutterRequestResult(0, JSONObject())
}

fun handleServiceBrowse(params: String): String {
    val jsonObject = JSONObject(params)
    val handle = jsonObject.requiredStringParam(jsonKeyHandle)
    val namesValue = jsonObject.opt("serviceNames")
    val serviceType = jsonObject.requiredStringParam("serviceType")
    val mdnsCallback = chipMdnsCallbackRef[handle]
        ?: throw IllegalStateException("NSD browse callback is no longer available")
    val instanceName = mutableListOf<String>()
    if (namesValue != null && namesValue != JSONObject.NULL) {
        if (namesValue !is JSONArray) {
            throw IllegalArgumentException("NSD serviceNames must be a JSON array")
        }
        for (i in 0 until namesValue.length()) {
            val value = namesValue.opt(i)
            if (value !is String) {
                throw IllegalArgumentException("NSD serviceNames entries must be strings")
            }
            instanceName.add(value)
        }
    }
    mdnsCallback.handleServiceBrowse(instanceName.toTypedArray(), serviceType)
    return createFlutterRequestResult(0, JSONObject())
}
