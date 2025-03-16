package com.zengge.flutter_matter

import android.os.Looper
import android.util.Log
import androidx.annotation.NonNull
import androidx.core.os.HandlerCompat
import chip.devicecontroller.AttestationInfo
import chip.devicecontroller.CSRInfo
import chip.devicecontroller.ChipDeviceController
import chip.devicecontroller.ChipInteractionClient
import chip.devicecontroller.CommissionParameters
import chip.devicecontroller.ControllerParams
import chip.devicecontroller.GetConnectedDeviceCallbackJni
import chip.devicecontroller.ICDCheckInDelegate
import chip.devicecontroller.ICDClientInfo
import chip.devicecontroller.ICDDeviceInfo
import chip.devicecontroller.InvokeCallback
import chip.devicecontroller.KeypairDelegate
import chip.devicecontroller.NetworkCredentials
import chip.devicecontroller.NetworkCredentials.ThreadCredentials
import chip.devicecontroller.NetworkCredentials.WiFiCredentials
import chip.devicecontroller.ReportCallback
import chip.devicecontroller.SubscriptionEstablishedCallback
import chip.devicecontroller.WriteAttributesCallback
import chip.devicecontroller.model.AttributeState
import chip.devicecontroller.model.AttributeWriteRequest
import chip.devicecontroller.model.ChipAttributePath
import chip.devicecontroller.model.ChipEventPath
import chip.devicecontroller.model.ChipPathId
import chip.devicecontroller.model.ClusterState
import chip.devicecontroller.model.EndpointState
import chip.devicecontroller.model.EventState
import chip.devicecontroller.model.InvokeElement
import chip.devicecontroller.model.NodeState
import chip.devicecontroller.model.Status
import matter.onboardingpayload.OnboardingPayloadParser
import io.flutter.plugin.common.MethodChannel
import matter.onboardingpayload.OnboardingPayload
import org.json.JSONArray
import org.json.JSONObject
import java.util.Objects
import java.util.UUID
import java.util.concurrent.Executor
import java.util.concurrent.Executors
import kotlin.concurrent.thread
import kotlin.jvm.optionals.getOrDefault
import kotlin.jvm.optionals.getOrNull

private val controls = mutableMapOf<String, ChipDeviceController>()

private val deviceControllerExecutor = FlutterMatterPlugin.executors

private fun getDeviceController(handle: String): ChipDeviceController? {
    return controls[handle]
}

private fun CSRInfo.toJSONObject(): JSONObject {
    return JSONObject(mapOf(
        "csr" to JSONArray(csr.nullToEmpty()),
        "elementsSignature" to JSONArray(elementsSignature.nullToEmpty()),
        "elements" to JSONArray(elements.nullToEmpty()),
        "nonce" to JSONArray(nonce.nullToEmpty())
    ))
}

private fun AttestationInfo.toJSONObject(): JSONObject {
    return JSONObject(mapOf(
        "challenge" to JSONArray(challenge.nullToEmpty()),
        "nonce" to JSONArray(nonce.nullToEmpty()),
        "elements" to JSONArray(elements.nullToEmpty()),
        "elementsSignature" to JSONArray(elementsSignature.nullToEmpty()),
        "dac" to JSONArray(dac.nullToEmpty()),
        "pai" to JSONArray(pai.nullToEmpty()),
        "firmwareInfo" to JSONArray(firmwareInfo.nullToEmpty()),
        "certificationDeclaration" to JSONArray(certificationDeclaration.nullToEmpty()),
        "vendorId" to vendorId,
        "productId" to productId
    ))
}

private fun ICDDeviceInfo.toJSONObject(): JSONObject {
    return JSONObject(mapOf(
        "symmetricKey" to JSONArray(symmetricKey.nullToEmpty()),
        "userActiveModeTriggerHint" to JSONArray(userActiveModeTriggerHint.map { it.bitIndex }),
        "userActiveModeTriggerInstruction" to JSONArray(userActiveModeTriggerInstruction),
        "icdNodeId" to icdNodeId,
        "icdCounter" to icdCounter,
        "monitoredSubject" to monitoredSubject,
        "fabricId" to fabricId,
        "fabricIndex" to fabricIndex
    ))
}

class KeypairDelegateWarp(
    private val handle: String
): KeypairDelegate {

    override fun generatePrivateKey() {
        matterPrint("[${Thread.currentThread()}] KeypairDelegate.generatePrivateKey call")
        FlutterMatterPlugin.externalChannel?.invokeMethodBlockGet(
            createFlutterCallPath(deviceControllerHost, "KeypairDelegate/GeneratePrivateKey"),
            JSONObject(mapOf("handle" to handle)).toString()
        )
    }

    override fun createCertificateSigningRequest(): ByteArray {
        matterPrint("[${Thread.currentThread()}] KeypairDelegate.createCertificateSigningRequest call")
        val createCertificateSigningRequestPath = createFlutterCallPath(
            deviceControllerHost,
            "KeypairDelegate/CreateCertificateSigningRequest"
        )
        val invokeMethodBlockGetResult =
            FlutterMatterPlugin.externalChannel?.invokeMethodBlockGet(
                createCertificateSigningRequestPath,
                JSONObject(mapOf("handle" to handle)).toString()
            )
        if (invokeMethodBlockGetResult == null) {
            throw RuntimeException("CreateCertificateSigningRequest no result")
        }
        val resultJson = JSONObject(invokeMethodBlockGetResult.toString())
        return resultJson.optJSONArray("certificateSigningRequest").toByteArray()
    }

    override fun getPublicKey(): ByteArray {
        matterPrint("[${Thread.currentThread()}] KeypairDelegate.getPublicKey call")
        val getPublicKeyPath = createFlutterCallPath(
            deviceControllerHost,
            "KeypairDelegate/GetPublicKey"
        )
        val invokeMethodBlockGetResult =
            FlutterMatterPlugin.externalChannel?.invokeMethodBlockGet(
                getPublicKeyPath,
                JSONObject(mapOf("handle" to handle)).toString()
            )
        if (invokeMethodBlockGetResult == null) {
            throw RuntimeException("getPublicKey no result")
        }
        val resultJson = JSONObject(invokeMethodBlockGetResult.toString())
        return resultJson.optJSONArray("publicKey").toByteArray()
    }

    override fun ecdsaSignMessage(message: ByteArray?): ByteArray {
        matterPrint("[${Thread.currentThread()}] KeypairDelegate.ecdsaSignMessage call")
        val ecdsaSignMessageCallPath = createFlutterCallPath(
            deviceControllerHost,
            "KeypairDelegate/EcdsaSignMessage"
        )
        val invokeJsonObject = JSONObject()
        invokeJsonObject.put("handle", handle)
        invokeJsonObject.put("message", JSONArray(message))
        val invokeMethodBlockGetResult =
            FlutterMatterPlugin.externalChannel?.invokeMethodBlockGet(
                ecdsaSignMessageCallPath,
                invokeJsonObject.toString()
            )
        if (invokeMethodBlockGetResult == null) {
            throw RuntimeException("EcdsaSignMessage no result")
        }
        try {
            val resultJson = JSONObject(invokeMethodBlockGetResult.toString())
            return resultJson.optJSONArray("ecdsaSign").toByteArray()
        } catch (e: Exception) {
            e.printStackTrace()
            throw e
        }

    }

}

fun onDeviceControlCall(path: String, params: String, result: MethodChannel.Result) {
    matterPrint("onDeviceControlCall $path $params")
    fun callResultSuccess(data: Any) {
        HandlerCompat.createAsync(Looper.getMainLooper()).post {
            result.success(data)
        }
    }
    fun callResultError(errorMessage: String) {
        HandlerCompat.createAsync(Looper.getMainLooper()).post {
            result.error("-99", errorMessage, "")
        }
    }
    deviceControllerExecutor.execute {
        matterPrint("onDeviceControlCall run")
        try {
            when (path) {
                "/new" -> {
                    callResultSuccess(newDeviceControllerCall(params))
                }
                "/createRootCertificate" -> {
                    callResultSuccess(createRootCertificate(params))
                }
                "/setNocChainIssuer" -> {
                    callResultSuccess(setNocChainIssuer(params))
                }
                "/setCompletionListener" -> {
                    callResultSuccess(setCompletionListener(params))
                }
                "/pairDevice" -> {
                    callResultSuccess(pairDevice(params))
                }
                "/stopDevicePairing" -> {
                    callResultSuccess(stopDevicePairing(params))
                }
                "/createOperationalCertificate" -> {
                    callResultSuccess(createOperationalCertificate(params))
                }
                "/publicKeyFromCSR" -> {
                    callResultSuccess(publicKeyFromCSR(params))
                }
                "/onNOCChainGeneration" -> {
                    callResultSuccess(onNOCChainGeneration(params))
                }
                "/continueCommissioning" -> {
                    callResultSuccess(continueCommissioning(params))
                }
                "/setDeviceAttestationDelegate" -> {
                    callResultSuccess(setDeviceAttestationDelegate(params))
                }
                "/deleteDeviceController" -> {
                    callResultSuccess(deleteDeviceController(params))
                }
                "/invoke" -> {
                    callResultSuccess(invoke(params))
                }
                "/subscribe" -> {
                    callResultSuccess(subscribe(params))
                }
                "/read" -> {
                    callResultSuccess(read(params))
                }
                "/write" -> {
                    callResultSuccess(write(params))
                }
                "/connectedDevice" -> {
                    callResultSuccess(connectedDevice(params))
                }
                "/releaseConnectContext" -> {
                    callResultSuccess(releaseConnectContext(params))
                }
                "/openPairingWindowWithPIN" -> {
                    callResultSuccess(openPairingWindowWithPIN(params))
                }
                "/unPairDevice" -> {
                    callResultSuccess(unPairDevice(params))
                }
                "/getFabricIndex" -> {
                    callResultSuccess(getFabricIndex(params))
                }
                "/unSubscribe" -> {
                    callResultSuccess(unSubscribe(params))
                }
                "/onCloseBleComplete" -> {
                    callResultSuccess(onCloseBleComplete(params))
                }
                else -> {
                    throw Exception("Unable handle path: ${path}")
                }
            }
        } catch (e: Exception) {
            e.printStackTrace()
            callResultError(e.stackTraceToString())
        }
    }
}

private fun mapChipAttributePath(jsonObject: JSONObject): ChipAttributePath {
    val endpointId = jsonObject.optJSONObject("endpointId")
    val clusterId = jsonObject.optJSONObject("clusterId")
    val attributeId = jsonObject.optJSONObject("attributeId")
    return ChipAttributePath.newInstance(
        ChipPathId.forId(endpointId.optLong("id")),
        ChipPathId.forId(clusterId.optLong("id")),
        ChipPathId.forId(attributeId.optLong("id"))
    )
}

private fun mapAttributeWriteRequest(jsonObject: JSONObject): AttributeWriteRequest {
    val endpointId = jsonObject.optJSONObject("endpointId")
    val clusterId = jsonObject.optJSONObject("clusterId")
    val attributeId = jsonObject.optJSONObject("attributeId")
    val tlv = jsonObject.optJSONArray("tlv")
    val json = jsonObject.opt("json")
    if (tlv != null && tlv != JSONObject.NULL) {
        return AttributeWriteRequest.newInstance(
            ChipPathId.forId(endpointId.optLong("id")),
            ChipPathId.forId(clusterId.optLong("id")),
            ChipPathId.forId(attributeId.optLong("id")),
            tlv.toByteArray(),
        )
    } else if (json != JSONObject.NULL) {
        return AttributeWriteRequest.newInstance(
            ChipPathId.forId(endpointId.optLong("id")),
            ChipPathId.forId(clusterId.optLong("id")),
            ChipPathId.forId(attributeId.optLong("id")),
            json.toString(),
        )
    }
    throw Exception("tlv and json one of them cannot be empty")
}

private fun mapChipEventPath(jsonObject: JSONObject): ChipEventPath {
    val endpointId = jsonObject.optJSONObject("endpointId")
    val clusterId = jsonObject.optJSONObject("clusterId")
    val attributeId = jsonObject.optJSONObject("eventId")
    val isUrgent = jsonObject.optBoolean("isUrgent")
    return ChipEventPath.newInstance(
        ChipPathId.forId(endpointId.optLong("id")),
        ChipPathId.forId(clusterId.optLong("id")),
        ChipPathId.forId(attributeId.optLong("id")),
        isUrgent
    )
}

private fun AttributeState.toJson(): JSONObject {
    val jsonObject = JSONObject()
    jsonObject.put("tlv", JSONArray(tlv))
    jsonObject.put("json", jsonObject.toString())
    return jsonObject
}

private fun EventState.toJson(): JSONObject {
    val jsonObject = JSONObject().apply {
        put("tlv", JSONArray(tlv))
        put("json", json.toString())
        put("eventNumber", eventNumber)
        put("priorityLevel", priorityLevel)
        put("timestampType", timestampType)
        put("timestampValue", timestampValue)
        put("eventNumber", eventNumber)
    }
    return jsonObject
}

private fun Status.toJson(): JSONObject {
    return JSONObject().apply {
        put("status", status.id)
        put("clusterStatus", clusterStatus?.orElse(null))
    }
}


private fun ClusterState.toJson(): JSONObject {
    return JSONObject().apply {
        if (attributeStates != null) {
            put("attributes", JSONObject().apply { attributeStates.map { put(it.key.toString(), it.value.toJson()) } })
        }
        if (eventStatuses != null) {
            put("eventStatuses", JSONObject().apply { eventStatuses.map { put(it.key.toString(), JSONArray(it.value.map { v -> v.toJson() })) } })
        }
        if (attributeStatuses != null) {
            put("attributeStatuses",  JSONObject().apply { attributeStatuses.map { put(it.key.toString(), it.value.toJson()) } })
        }
        if (eventStates != null) {
            put("events", JSONObject().apply { eventStates.map { put(it.key.toString(), JSONArray(it.value.map { v -> v.toJson() })) }})
        }
        put("dataVersion", dataVersion?.orElse(null))
    }
}

private fun EndpointState.toJson(): JSONObject {
    return JSONObject().apply {
        put("clusters", JSONObject().apply{ clusterStates.map { put(it.key.toString(), it.value.toJson()) } })
    }
}

private fun NodeState.toJson(): JSONObject {
    return JSONObject().apply {
        put("endpoints", JSONObject().apply{ endpointStates.map { put(it.key.toString(), it.value.toJson()) } })
    }
}

private fun ChipPathId.toJson(): JSONObject {
    return JSONObject().apply {
        put("id", id)
        put("type", type.name)
    }
}

private fun ChipAttributePath.toJson(): JSONObject {
    return JSONObject().apply {
        put("endpointId", endpointId?.toJson())
        put("clusterId", clusterId?.toJson())
        put("attributeId", attributeId?.toJson())
    }
}

private fun mapControllerParams(jsonObject: JSONObject): ControllerParams {
    return ControllerParams.newBuilder().apply {
        setFabricId(jsonObject.optLong("fabricId"))
        setUdpListenPort(jsonObject.optLong("udpListenPort").toInt())
        setControllerVendorId(jsonObject.optLong("controllerVendorId").toInt())
        val failsafeTimerSeconds = jsonObject.optInt("failsafeTimerSeconds")
        if (failsafeTimerSeconds > 0) {
            setFailsafeTimerSeconds(jsonObject.optInt("failsafeTimerSeconds"))
        }
        val caseFailsafeTimerSeconds = jsonObject.optInt("caseFailsafeTimerSeconds")
        if (caseFailsafeTimerSeconds > 0) {
            setCASEFailsafeTimerSeconds(caseFailsafeTimerSeconds)
        }
        setAttemptNetworkScanWiFi(jsonObject.optBoolean("attemptNetworkScanWiFi"))
        setAttemptNetworkScanThread(jsonObject.optBoolean("attemptNetworkScanThread"))
        setSkipCommissioningComplete(jsonObject.optBoolean("skipCommissioningComplete"))
        setSkipAttestationCertificateValidation(jsonObject.optBoolean("skipAttestationCertificateValidation"))
        val countryCode = jsonObject.optString("countryCode")
        if (countryCode.isNotEmpty()) {
            setCountryCode(jsonObject.optString("countryCode"))
        }
        setRegulatoryLocation(jsonObject.optInt("regulatoryLocationType"))
        val keypairDelegateHandle = jsonObject.opt("keypairDelegateHandle")
        if (keypairDelegateHandle != null) {
            setKeypairDelegate(KeypairDelegateWarp(keypairDelegateHandle.toString()))
        }
        setRootCertificate(jsonObject.optJSONArray("rootCertificate")?.toByteArray())
        setIntermediateCertificate(jsonObject.optJSONArray("intermediateCertificate")?.toByteArray())
        setOperationalCertificate(jsonObject.optJSONArray("operationalCertificate")?.toByteArray())
        setIpk(jsonObject.optJSONArray("ipk")?.toByteArray())
        setAdminSubject(jsonObject.optLong("adminSubject"))
        setEnableServerInteractions(jsonObject.optBoolean("enableServerInteractions"))
        val setupURL = jsonObject.optString("setupURL")
        if (setupURL.isNotEmpty()) {
            setSetupURL(setupURL)
        }
    }.build()
}

private fun mapInvokeElement(jsonObject: JSONObject): InvokeElement {
    val endpointIdJson = jsonObject.optJSONObject("endpointId")!!
    val clusterIdJson = jsonObject.optJSONObject("clusterId")!!
    val commandIdJson = jsonObject.optJSONObject("commandId")!!
    val groupId = jsonObject.optInt("groupId")
    val tlv = jsonObject.optJSONArray("tlv")?.toByteArray()
    val json = jsonObject.opt("json")
    return InvokeElement.newInstance(
        ChipPathId.forId(endpointIdJson.optLong("id")),
        ChipPathId.forId(clusterIdJson.optLong("id")),
        ChipPathId.forId(commandIdJson.optLong("id")),
        tlv,
        if (json == JSONObject.NULL) null else json!!.toString()
    )
}

fun newDeviceControllerCall(params: String): String {
    val jsonObject = JSONObject(params)
    val controllerParams = mapControllerParams(jsonObject)
    val chipDeviceController = ChipDeviceController(controllerParams)
    val uuid = UUID.randomUUID().toString()
    controls[uuid] = chipDeviceController
    return createFlutterRequestResult(0, JSONObject(mapOf("handle" to uuid)))
}

fun createRootCertificate(params: String): String {
    val jsonObject = JSONObject(params)
//    val controlHandle = jsonObject.optString("handle")
    val keypairHandle = jsonObject.optString("keypairHandle")
    val issuerId = jsonObject.optLong("issuerId")
    val fabricId = if (jsonObject.isNull("fabricId"))  null else jsonObject.getLong("fabricId")
    //    val chipDeviceController = controls[controlHandle]
    val createRootCertificate: ByteArray? = ChipDeviceController.createRootCertificate(
        KeypairDelegateWarp(keypairHandle),
        issuerId, fabricId
    )

    if (createRootCertificate == null) {
        return createFlutterRequestResult(1, JSONObject())
    }
    return createFlutterRequestResult(0, JSONObject(mapOf("data" to JSONArray(createRootCertificate))))
}


fun setNocChainIssuer(params: String): String {
    val jsonObject = JSONObject(params)
    val handle = jsonObject.optNotNull(jsonKeyHandle)
    val deviceController = Objects.requireNonNull(getDeviceController(handle.toString()), "Not found control handle $handle")
    deviceController!!.setNOCChainIssuer { csrInfo, attestationInfo ->
        val  result = FlutterMatterPlugin.externalChannel?.invokeMethodBlockGet(
            createFlutterCallPath(deviceControllerHost, "NOCChainIssuer/onNOCChainGenerationNeeded"),
            JSONObject(mapOf(
                jsonKeyHandle to handle,
                "csrInfo" to csrInfo.toJSONObject(),
                "attestationInfo" to attestationInfo.toJSONObject()
            )).toString()
        )
        Objects.requireNonNull(result, createCallFlutterExceptionMessage("onNOCChainGenerationNeeded"))
    }
    return createFlutterRequestResult(0, JSONObject())
}

fun setCompletionListener(params: String): String {
    val jsonObject = JSONObject(params)
    val handle = jsonObject.optNotNull(jsonKeyHandle)
    val deviceController = Objects.requireNonNull(getDeviceController(handle.toString()), "Not found control handle $handle")
    deviceController!!.setCompletionListener(object : ChipDeviceController.CompletionListener {

        private fun createParams(params: Map<String, Any?>): JSONObject  {
            return JSONObject(HashMap(params).apply {
                put(jsonKeyHandle, handle)
            })
        }

        override fun onConnectDeviceComplete() {
            try {
                val p = createFlutterCallPath(deviceControllerHost, "CompletionListener/onConnectDeviceComplete")
                val callResult =
                    FlutterMatterPlugin.externalChannel?.invokeMethodBlockGet(p, null)
                Objects.requireNonNull(callResult, createCallFlutterExceptionMessage("onConnectDeviceComplete"))
            } catch (e: Exception) {
                e.printStackTrace()
            }
        }

        override fun onStatusUpdate(status: Int) {
            try {
                val p = createFlutterCallPath(deviceControllerHost, "CompletionListener/onStatusUpdate")
                val callResult =
                    FlutterMatterPlugin.externalChannel?.invokeMethodBlockGet(p, createParams(mapOf("status" to status)).toString())
                Objects.requireNonNull(callResult, createCallFlutterExceptionMessage("onStatusUpdate"))
            } catch (e: Exception) {
                e.printStackTrace()
            }
        }

        override fun onPairingComplete(errorCode: Long) {
            try {
                val p = createFlutterCallPath(deviceControllerHost, "CompletionListener/onPairingComplete")
                val callResult =
                    FlutterMatterPlugin.externalChannel?.invokeMethodBlockGet(p, createParams(mapOf("errorCode" to errorCode)).toString())
                Objects.requireNonNull(callResult, createCallFlutterExceptionMessage("onPairingComplete"))
            } catch (e: Exception) {
                e.printStackTrace()
            }
        }

        override fun onPairingDeleted(errorCode: Long) {
            try {
                val p = createFlutterCallPath(deviceControllerHost, "CompletionListener/onPairingDeleted")
                val callResult =
                    FlutterMatterPlugin.externalChannel?.invokeMethodBlockGet(p, createParams(mapOf("errorCode" to errorCode)).toString())
                Objects.requireNonNull(callResult, createCallFlutterExceptionMessage("onPairingDeleted"))
            } catch (e: Exception) {
                e.printStackTrace()
            }
        }

        override fun onCommissioningComplete(nodeId: Long, errorCode: Long) {
            try {
                val p = createFlutterCallPath(deviceControllerHost, "CompletionListener/onCommissioningComplete")
                val callResult =
                    FlutterMatterPlugin.externalChannel?.invokeMethodBlockGet(p, createParams(mapOf("nodeId" to nodeId, "errorCode" to errorCode)).toString())
                Objects.requireNonNull(callResult, createCallFlutterExceptionMessage("onCommissioningComplete"))
            } catch (e: Exception) {
                e.printStackTrace()
            }
        }

        override fun onReadCommissioningInfo(
            vendorId: Int,
            productId: Int,
            wifiEndpointId: Int,
            threadEndpointId: Int
        ) {
            try {
                val p = createFlutterCallPath(deviceControllerHost, "CompletionListener/onReadCommissioningInfo")
                val callResult =
                    FlutterMatterPlugin.externalChannel?.invokeMethodBlockGet(
                        p,
                        createParams(mapOf("vendorId" to vendorId, "productId" to productId, "wifiEndpointId" to wifiEndpointId, "threadEndpointId" to threadEndpointId)).toString()
                    )
                Objects.requireNonNull(callResult, createCallFlutterExceptionMessage("onReadCommissioningInfo"))
            } catch (e: Exception) {
                e.printStackTrace()
            }
        }

        override fun onCommissioningStatusUpdate(nodeId: Long, stage: String?, errorCode: Long) {
            try {
                val p = createFlutterCallPath(deviceControllerHost, "CompletionListener/onCommissioningStatusUpdate")
                val callResult =
                    FlutterMatterPlugin.externalChannel?.invokeMethodBlockGet(p, createParams(mapOf("stage" to stage, "nodeId" to nodeId, "errorCode" to errorCode)).toString())
                Objects.requireNonNull(callResult, createCallFlutterExceptionMessage("onCommissioningStatusUpdate"))
            }  catch(e: Exception) {
                matterPrint("Call Flutter onCommissioningStatusUpdate error $e")
            }
        }

        override fun onNotifyChipConnectionClosed() {
            try {
                val p = createFlutterCallPath(deviceControllerHost, "CompletionListener/onNotifyChipConnectionClosed")
                val callResult =
                    FlutterMatterPlugin.externalChannel?.invokeMethodBlockGet(p, null)
                Objects.requireNonNull(callResult, createCallFlutterExceptionMessage("onNotifyChipConnectionClosed"))
            } catch (e: Exception) {
                matterPrint("Call Flutter onNotifyChipConnectionClosed error: $e")
            }
        }

        override fun onCloseBleComplete() {
            try {
                val p = createFlutterCallPath(deviceControllerHost, "CompletionListener/onCloseBleComplete")
                val callResult =
                    FlutterMatterPlugin.externalChannel?.invokeMethodBlockGet(p, null)
                Objects.requireNonNull(callResult, createCallFlutterExceptionMessage("onCloseBleComplete"))
            } catch (e: Exception) {
                e.printStackTrace()
            }
        }

        override fun onError(error: Throwable?) {
            try {
                val p = createFlutterCallPath(deviceControllerHost, "CompletionListener/onError")
                val callResult =
                    FlutterMatterPlugin.externalChannel?.invokeMethodBlockGet(p, createParams(mapOf("error" to error.toString())).toString())
                Objects.requireNonNull(callResult, createCallFlutterExceptionMessage("onCommissioningStatusUpdate"))
            } catch (e: Exception) {
                e.printStackTrace()
                matterPrint("Call Flutter CompletionListener/onError error: $e")
            }

        }

        override fun onOpCSRGenerationComplete(csr: ByteArray?) {
            try {
                val p = createFlutterCallPath(deviceControllerHost, "CompletionListener/onOpCSRGenerationComplete")
                val callResult =
                    FlutterMatterPlugin.externalChannel?.invokeMethodBlockGet(p, createParams(mapOf("csr" to JSONArray(csr))).toString())
                Objects.requireNonNull(callResult, createCallFlutterExceptionMessage("onOpCSRGenerationComplete"))
            } catch (e: Exception) {
                matterPrint("Call Flutter onOpCSRGenerationComplete error: $e")
            }
        }

        override fun onICDRegistrationInfoRequired() {
            try {
                val p = createFlutterCallPath(
                    deviceControllerHost,
                    "CompletionListener/onICDRegistrationInfoRequired"
                )
                val callResult =
                    FlutterMatterPlugin.externalChannel?.invokeMethodBlockGet(p, null)
                Objects.requireNonNull(
                    callResult,
                    createCallFlutterExceptionMessage("onICDRegistrationInfoRequired")
                )
            } catch (e: Exception) {
                matterPrint("Call Flutter onICDRegistrationInfoRequired error: $e")
            }
        }

        override fun onICDRegistrationComplete(errorCode: Long, icdDeviceInfo: ICDDeviceInfo?) {
            try {
                val p = createFlutterCallPath(deviceControllerHost, "CompletionListener/onICDRegistrationComplete")
                val callResult =
                    FlutterMatterPlugin.externalChannel?.invokeMethodBlockGet(p, createParams(mapOf("errorCode" to errorCode, "icdDeviceInfo" to icdDeviceInfo?.toJSONObject())).toString())
                Objects.requireNonNull(callResult, createCallFlutterExceptionMessage("onICDRegistrationComplete"))
            } catch (e: Exception) {
                matterPrint("Call Flutter onICDRegistrationComplete failed $e")
            }
        }

    })
    return createFlutterRequestResult(0, JSONObject())
}

fun pairDevice(params: String): String {
    val jsonObject = JSONObject(params)
    val handle = jsonObject.optNotNull(jsonKeyHandle).toString();
    val control = Objects.requireNonNull(getDeviceController(handle), "Not found control")!!
    val deviceId = jsonObject.optNotNull("deviceId").toString().toLong()
    val connId = if (jsonObject.opt("connId") == JSONObject.NULL)  null else jsonObject.optNotNull("connId").toString().toInt()
    val onboardingPayload = jsonObject.opt("onboardingPayload")
    var setupPincode = jsonObject.opt("setupPincode")?.toString()?.toLongOrNull()
    if (setupPincode == null && onboardingPayload != JSONObject.NULL) {
        val payload = onboardingPayload.toString()
        val op: OnboardingPayload
        if (payload.startsWith("MT:")) {
            op = OnboardingPayloadParser().parseQrCode(payload)
        } else {
            op = OnboardingPayloadParser().parseManualPairingCode(payload)
        }
        setupPincode = op.setupPinCode
    };
    if (setupPincode == null) {
        return createFlutterRequestResult(1, JSONObject(mapOf("data" to "Unable get setupPincode")))
    }
    val csrNonce = jsonObject.optJSONArray("csrNonce")?.toByteArray()
    val networkCredentialsJsonObject = jsonObject.optJSONObject("networkCredentials")
    val attestationDelegate = jsonObject.optString("attestationDelegate");
    val wifiCredentialsJSONObject = networkCredentialsJsonObject?.optJSONObject("wifiCredentials")
    val threadCredentialsJSONObject = networkCredentialsJsonObject?.optJSONObject("threadCredentials")
    val completionListenerHandle = jsonObject.optString("completionListener")
    var wifiCredentials: WiFiCredentials? = null
    if (wifiCredentialsJSONObject != null) {
        wifiCredentials = WiFiCredentials(
            wifiCredentialsJSONObject.optNotNull("ssid").toString(),
            wifiCredentialsJSONObject.optNotNull("password").toString(),
        )
    }
    var threadCredentials: ThreadCredentials? = null
    if (threadCredentialsJSONObject != null) {
        threadCredentials = ThreadCredentials(threadCredentialsJSONObject.optJSONArray("operationalDataset").toByteArray())
    }
    var networkCredentials: NetworkCredentials? = null
    if (wifiCredentials != null) {
        networkCredentials = NetworkCredentials.forWiFi(wifiCredentials)
    } else if (threadCredentials != null) {
        networkCredentials = NetworkCredentials.forThread(threadCredentials)
    }
    Objects.requireNonNull(networkCredentials, "networkCredentials not set wifiCredentials or threadCredentials")
    if (attestationDelegate != JSONObject.NULL && !attestationDelegate.isNullOrEmpty()) {
        val failSafeExpiryTimeoutSecs = jsonObject.opt("failSafeExpiryTimeoutSecs").toString().toIntOrNull() ?: 60;
        control.setDeviceAttestationDelegate(failSafeExpiryTimeoutSecs) { devicePtr, attestationInfo, errorCode ->
            thread {
                val p = createFlutterCallPath(deviceControllerHost, "DeviceAttestationDelegate/onDeviceAttestationCompleted")
                val flutterResult = FlutterMatterPlugin.externalChannel?.invokeMethodBlockGet(p, JSONObject(mapOf(
                    jsonKeyHandle to handle, "devicePtr" to devicePtr, "attestationInfo" to attestationInfo?.toJSONObject(), "errorCode" to errorCode)).toString())
                Objects.requireNonNull(flutterResult, "Flutter onDeviceAttestationCompleted result null")
            }
        }
    }
    if (completionListenerHandle != JSONObject.NULL) {
        setCompletionListener(params)
    }
    if (connId != null) {
        control.pairDevice(null, connId, deviceId, setupPincode, csrNonce, networkCredentials)
        // invalici ${ChipDeviceController.connectionId}, unnecessary this value
        // ${ChipDeviceController.connectionId} will hinder the next pairDevice
        control.close()
    } else {
        if (onboardingPayload == JSONObject.NULL) {
            return createFlutterRequestResult(1, JSONObject(mapOf("data" to "onboardingPayload not set, connId not set")))
        }
        matterPrint("pairDeviceWithCode")
        val commissionParams = CommissionParameters.Builder()
            .setCsrNonce(csrNonce)
            .setNetworkCredentials(networkCredentials)
            .build()
        control.pairDeviceWithCode(deviceId, onboardingPayload.toString(), false, false, commissionParams)
    }
    return createFlutterRequestResult(0, JSONObject())
}

fun setDeviceAttestationDelegate(params: String): String {
    val jsonObject = JSONObject(params)
    val handle = jsonObject.optNotNull(jsonKeyHandle).toString()
    val control = Objects.requireNonNull((getDeviceController(handle)), "Not found control")!!
    val failSafeExpiryTimeoutSecs = jsonObject.optNotNull("failSafeExpiryTimeoutSecs").toString().toInt()
    control.setDeviceAttestationDelegate(failSafeExpiryTimeoutSecs) { devicePtr, attestationInfo, errorCode ->
//        deviceControllerExecutor.execute {
            val p = createFlutterCallPath(deviceControllerHost, "DeviceAttestationDelegate/onDeviceAttestationCompleted")
            val flutterResult = FlutterMatterPlugin.externalChannel?.invokeMethodBlockGet(p, JSONObject(mapOf(
                jsonKeyHandle to handle, "devicePtr" to devicePtr, "attestationInfo" to attestationInfo?.toJSONObject(), "errorCode" to errorCode)).toString())
            Objects.requireNonNull(flutterResult, "Flutter onDeviceAttestationCompleted result null")
//        }
    }
    return createFlutterRequestResult(0, JSONObject())
}

fun continueCommissioning(params: String): String {
    val jsonObject = JSONObject(params)
    val control = Objects.requireNonNull((getDeviceController(jsonObject.optNotNull(jsonKeyHandle).toString())), "Not found control")!!
    val devicePtr = jsonObject.optNotNull("devicePtr").toString().toLong()
    val ignoreAttestationFailure = jsonObject.optNotNull("ignoreAttestationFailure") == true
    control.continueCommissioning(devicePtr, ignoreAttestationFailure)
    return createFlutterRequestResult(0, JSONObject())
}

fun stopDevicePairing(params: String): String {
    val jsonObject = JSONObject(params)
    val control = Objects.requireNonNull((getDeviceController(jsonObject.optNotNull(jsonKeyHandle).toString())), "Not found control")!!
    val deviceId = jsonObject.optNotNull("deviceId").toString().toLong()
    control.stopDevicePairing(deviceId)
    return createFlutterRequestResult(0, JSONObject())
}

fun createOperationalCertificate(params: String): String {
    val jsonObject = JSONObject(params)
//    val control = Objects.requireNonNull((getDeviceController(jsonObject.optNotNull(jsonKeyHandle).toString())), "Not found control")!!
    val signingCertificate = Objects.requireNonNull(jsonObject.optJSONArray("signingCertificate"), "signingCertificate is Null").toByteArray()
    val operationalPublicKey = Objects.requireNonNull(jsonObject.optJSONArray("operationalPublicKey"), "operationalPublicKey is Null").toByteArray()
    val fabricId = jsonObject.optNotNull("fabricId").toString().toLong()
    val nodeId = jsonObject.optNotNull("nodeId").toString().toLong()
    val keypairHandle = jsonObject.optNotNull("keypairHandle").toString()
    val caseAuthenticatedTags = jsonObject.optJSONArray("caseAuthenticatedTags")?.toByteArray()
    val operationalCertificate = ChipDeviceController.createOperationalCertificate(
        KeypairDelegateWarp(keypairHandle),
        signingCertificate,
        operationalPublicKey,
        fabricId,
        nodeId,
        caseAuthenticatedTags?.map { it.toInt() }
    )
    return createFlutterRequestResult(0, JSONObject(mapOf("data" to JSONArray(operationalCertificate))))
}

fun publicKeyFromCSR(params: String): String {
    val jsonObject = JSONObject(params)
//    val control = Objects.requireNonNull((getDeviceController(jsonObject.optNotNull(jsonKeyHandle).toString())), "Not found control")!!
    val csr = Objects.requireNonNull(jsonObject.optJSONArray("csr"), "crs is null").toByteArray()
    val publicKeyFromCSR = ChipDeviceController.publicKeyFromCSR(csr)
    return createFlutterRequestResult(0, JSONObject(mapOf("data" to JSONArray(publicKeyFromCSR))))
}

fun onNOCChainGeneration(params: String): String {
    val jsonObject = JSONObject(params)
    val control = Objects.requireNonNull((getDeviceController(jsonObject.optNotNull(jsonKeyHandle).toString())), "Not found control")!!
    val controllerParams = mapControllerParams(
        Objects.requireNonNull(
            jsonObject.optJSONObject("params"),
            "params is null"
        )
    )
    val onNOCChainGenerationResult = control.onNOCChainGeneration(controllerParams)
    return createFlutterRequestResult(0, JSONObject(mapOf("data" to onNOCChainGenerationResult)))
}

fun deleteDeviceController(params: String): String {
    val jsonObject = JSONObject(params)
    val handle = jsonObject.optNotNull(jsonKeyHandle).toString()
    controls.remove(handle)
    return createFlutterRequestResult(0, JSONObject())
}

fun invoke(params: String): String {
    val jsonObject = JSONObject(params)
    val controlId = jsonObject.optNotNull(jsonKeyHandle).toString()
    val control = Objects.requireNonNull((getDeviceController(controlId)), "Not found control")!!
    val callbackId = jsonObject.optNotNull("callback").toString()
    val nodeId = jsonObject.optNotNull("nodeId").toString().toLong()
    val invokeElement = mapInvokeElement(jsonObject.optJSONObject("invokeElement")!!)
    val timedRequestTimeoutMs = jsonObject.optInt("timedRequestTimeoutMs")
    val imTimeoutMs = jsonObject.optInt("imTimeoutMs")
    control.getConnectedDevicePointer(nodeId, object :
        GetConnectedDeviceCallbackJni.GetConnectedDeviceCallback {
            private val cb = object : InvokeCallback {
                override fun onError(ex: Exception?) {
                    try {
                        val p = createFlutterCallPath(deviceControllerHost, "InvokeCallback/onError")
                        val flutterResult = FlutterMatterPlugin.externalChannel?.invokeMethodBlockGet(p, JSONObject(mapOf(
                            jsonKeyHandle to controlId, "invokeCallbackPoint" to callbackId, "error" to (ex?.toString() ?: ""))).toString())
                        Objects.requireNonNull(flutterResult, "Flutter InvokeCallback/onError result null")
                    } catch (e: Exception) {
                        e.printStackTrace()
                    }
                }

                override fun onResponse(invokeElement: InvokeElement, successCode: Long) {
                    try {
                        val p = createFlutterCallPath(deviceControllerHost, "InvokeCallback/onResponse")
                        val cbParams = JSONObject(mapOf(
                            jsonKeyHandle to controlId,
                            "invokeCallbackPoint" to callbackId,
                            "successCode" to successCode,
                            "invokeElement" to JSONObject(mapOf(
                                "endpointId" to JSONObject(mapOf(
                                    "id" to invokeElement.endpointId.id,
                                    "type" to invokeElement.endpointId.type.name
                                )),
                                "clusterId" to JSONObject(mapOf(
                                    "id" to invokeElement.clusterId.id,
                                    "type" to invokeElement.clusterId.type.name
                                )),
                                "commandId" to JSONObject(mapOf(
                                    "id" to invokeElement.commandId.id,
                                    "type" to invokeElement.commandId.type.name
                                )),
                                "groupId" to invokeElement.groupId?.orElse(null),
                                "tlv" to if (invokeElement.tlvByteArray == null) null else JSONArray(invokeElement.tlvByteArray),
                                "json" to if (invokeElement.jsonString == null) null else invokeElement.jsonString
                            )
                            )
                        ))
                        val flutterResult = FlutterMatterPlugin.externalChannel?.invokeMethodBlockGet(p, cbParams.toString()).toString()
                        Objects.requireNonNull(flutterResult, "Flutter InvokeCallback/onResponse result null")
                    } catch (e: Exception) {
                        e.printStackTrace()
                    }

                }

                override fun onDone() {
                    try {
                        val p = createFlutterCallPath(deviceControllerHost, "InvokeCallback/onDone")
                        val flutterResult = FlutterMatterPlugin.externalChannel?.invokeMethodBlockGet(p, JSONObject(mapOf(
                            jsonKeyHandle to controlId, "invokeCallbackPoint" to callbackId)).toString())
                        Objects.requireNonNull(flutterResult, "Flutter InvokeCallback/onDone result null")
                    } catch (e: Exception) {
                        e.printStackTrace()
                    }

                }
            }

            override fun onDeviceConnected(devicePointer: Long) {
                control.invoke(
                    cb,
                    devicePointer,
                    invokeElement,
                    timedRequestTimeoutMs,
                    imTimeoutMs
                )
            }

            override fun onConnectionFailure(nodeId: Long, error: Exception) {
                cb.onError(error)
            }
        })

    return createFlutterRequestResult(0, JSONObject())
}

fun subscribe(params: String): String {
    val jsonObject = JSONObject(params)
    val controlId = jsonObject.optNotNull(jsonKeyHandle).toString()
    val control = Objects.requireNonNull((getDeviceController(controlId)), "Not found control")!!
    val nodeId = jsonObject.optNotNull("nodeId").toString().toLong()
    val callbackHandle = jsonObject.optNotNull("callbackHandle").toString()
    val attributePathsJson = jsonObject.optJSONArray("attributePaths")
    val eventPathsJson = jsonObject.optJSONArray("eventPaths")
//    val dataVersionFilters = jsonObject.opt("dataVersionFilters")
    val minInterval = jsonObject.opt("minInterval")?.toString()?.toIntOrNull()
    val maxInterval = jsonObject.opt("maxInterval")?.toString()?.toIntOrNull()
    val keepSubscriptions = jsonObject.opt("keepSubscriptions") == true
    val isFabricFiltered = jsonObject.opt("isFabricFiltered") == true
    val imTimeoutMs = jsonObject.opt("imTimeoutMs")?.toString()?.toIntOrNull()
    val eventMin = jsonObject.opt("eventMin")?.toString()?.toIntOrNull()
    val connectDevicePointer = jsonObject.opt("connectContext")
    var attributePaths: ArrayList<ChipAttributePath>? = null
    if (attributePathsJson != null && attributePathsJson != JSONObject.NULL) {
        attributePaths = ArrayList()
        for (i in 0 until attributePathsJson.length()) {
            val obj = attributePathsJson.optJSONObject(i)
            attributePaths.add(mapChipAttributePath(obj))
        }
    }
    var eventPaths: ArrayList<ChipEventPath>? = null
    if (eventPathsJson != null && eventPathsJson != JSONObject.NULL) {
        eventPaths = ArrayList()
        for (i in 0 until eventPathsJson.length()) {
            eventPaths.add(mapChipEventPath(eventPathsJson.optJSONObject(i)))
        }
    }

    val reportCallback = object : ReportCallback {
        override fun onError(
            attributePath: ChipAttributePath?,
            eventPath: ChipEventPath?,
            e: java.lang.Exception
        ) {
            matterPrint("subscribe onError attributePath:$attributePath eventPath:$eventPath $e")
            val p = createFlutterCallPath(deviceControllerHost, "SubscriptionCallback/onError")
            try {
                FlutterMatterPlugin.externalChannel?.invokeMethodBlockGet(
                    p,
                    JSONObject(mapOf(
                        jsonKeyHandle to controlId,
                        "subscriptionCallbackPoint" to callbackHandle,
                        "error" to e.toString(),
                    )).toString())
            } catch (e: Exception) {
                e.printStackTrace()
            }
        }

        override fun onReport(nodeState: NodeState?) {
            val p = createFlutterCallPath(deviceControllerHost, "SubscriptionCallback/onReport")
            try {
                FlutterMatterPlugin.externalChannel?.invokeMethodBlockGet(
                    p,
                    JSONObject(mapOf(jsonKeyHandle to controlId, "subscriptionCallbackPoint" to callbackHandle, "nodeState" to nodeState?.toJson())).toString())
            } catch (e: Exception) {
                e.printStackTrace()
            }
        }

        override fun onDone() {
            val p = createFlutterCallPath(deviceControllerHost, "SubscriptionCallback/onDone")
            try {
                FlutterMatterPlugin.externalChannel?.invokeMethodBlockGet(
                    p,
                    JSONObject(mapOf(jsonKeyHandle to controlId, "subscriptionCallbackPoint" to callbackHandle)).toString())
            } catch (e: Exception) {
                e.printStackTrace()
            }
        }
    }

    if (connectDevicePointer == JSONObject.NULL || connectDevicePointer == null) {
        control.getConnectedDevicePointer(nodeId, object : GetConnectedDeviceCallbackJni.GetConnectedDeviceCallback {
            override fun onDeviceConnected(devicePointer: Long) {
                control.subscribeToPath(
                    { subscriptionId ->
                        val p = createFlutterCallPath(deviceControllerHost, "SubscriptionCallback/onSubscriptionEstablished")
                        try {
                            FlutterMatterPlugin.externalChannel?.invokeMethodBlockGet(
                                p,
                                JSONObject(mapOf(jsonKeyHandle to controlId, "subscriptionCallbackPoint" to callbackHandle, "subscriptionId" to subscriptionId)).toString())
                        } catch (e: Exception) {
                            e.printStackTrace()
                        }
                    },
                    null,
                    reportCallback,
                    devicePointer,
                    attributePaths,
                    eventPaths,
                    minInterval ?: 0,
                    maxInterval ?: 0,
                    keepSubscriptions,
                    isFabricFiltered,
                    imTimeoutMs ?: 0,
                )
            }

            override fun onConnectionFailure(nodeId: Long, error: java.lang.Exception?) {
                reportCallback.onError(null, null, error ?: RuntimeException("onConnectionFailure"))
                reportCallback.onDone()
            }
        })
    } else {
        control.subscribeToPath(
            { subscriptionId ->
                val p = createFlutterCallPath(deviceControllerHost, "SubscriptionCallback/onSubscriptionEstablished")
                try {
                    FlutterMatterPlugin.externalChannel?.invokeMethodBlockGet(
                        p,
                        JSONObject(mapOf(jsonKeyHandle to controlId, "subscriptionCallbackPoint" to callbackHandle, "subscriptionId" to subscriptionId)).toString())
                } catch (e: Exception) {
                    e.printStackTrace()
                }
            },
            null,
            reportCallback,
            connectDevicePointer.toString().toLong(),
            attributePaths,
            eventPaths,
            minInterval ?: 0,
            maxInterval ?: 0,
            keepSubscriptions,
            isFabricFiltered,
            imTimeoutMs ?: 0,
        )
    }

    return createFlutterRequestResult(0, JSONObject())
}

fun read(params: String): String {

    val jsonObject = JSONObject(params)
    val controlId = jsonObject.optNotNull(jsonKeyHandle).toString()
    val control = Objects.requireNonNull((getDeviceController(controlId)), "Not found control")!!
    val callbackHandle = jsonObject.optNotNull("callbackHandle").toString()
    val nodeId = jsonObject.optNotNull("nodeId").toString().toLong()
    val attributePathsJson = jsonObject.optJSONArray("attributePaths")
    val eventPathsJson = jsonObject.optJSONArray("eventPaths")
    val connectDevicePointer = jsonObject.opt("connectContext")
//    val dataVersionFilters = jsonObject.opt("dataVersionFilters")
    val isFabricFiltered = jsonObject.opt("isFabricFiltered") == true
    val imTimeoutMs = jsonObject.opt("imTimeoutMs")?.toString()?.toIntOrNull()
    val eventMin = jsonObject.opt("eventMin")?.toString()?.toLongOrNull()
    var attributePaths: ArrayList<ChipAttributePath>? = null
    if (attributePathsJson != null && attributePathsJson != JSONObject.NULL) {
        attributePaths = ArrayList()
        for (i in 0 until attributePathsJson.length()) {
            val obj = attributePathsJson.optJSONObject(i)
            attributePaths.add(mapChipAttributePath(obj))
        }
    }
    var eventPaths: ArrayList<ChipEventPath>? = null
    if (eventPathsJson != null && eventPathsJson != JSONObject.NULL) {
        eventPaths = ArrayList()
        for (i in 0 until eventPathsJson.length()) {
            eventPaths.add(mapChipEventPath(eventPathsJson.optJSONObject(i)))
        }
    }
    val reportCallback = object : ReportCallback {
        override fun onError(
            attributePath: ChipAttributePath?,
            eventPath: ChipEventPath?,
            e: java.lang.Exception
        ) {
            val p = createFlutterCallPath(deviceControllerHost, "ReportCallback/onError")
            try {
                FlutterMatterPlugin.externalChannel?.invokeMethodBlockGet(
                    p,
                    JSONObject(mapOf(jsonKeyHandle to controlId, "reportCallbackPoint" to callbackHandle, "error" to e?.toString())).toString())
            } catch (e: Exception) {
                e.printStackTrace()
            }
        }

        override fun onReport(nodeState: NodeState?) {
            val p = createFlutterCallPath(deviceControllerHost, "ReportCallback/onReport")
            try {
                FlutterMatterPlugin.externalChannel?.invokeMethodBlockGet(
                    p,
                    JSONObject(mapOf(jsonKeyHandle to controlId, "reportCallbackPoint" to callbackHandle, "nodeState" to nodeState?.toJson())).toString())
            } catch (e: Exception) {
                e.printStackTrace()
            }
        }

        override fun onDone() {
            val p = createFlutterCallPath(deviceControllerHost, "ReportCallback/onDone")
            try {
                FlutterMatterPlugin.externalChannel?.invokeMethodBlockGet(
                    p,
                    JSONObject(mapOf(jsonKeyHandle to controlId, "reportCallbackPoint" to callbackHandle)).toString())
            } catch (e: Exception) {
                e.printStackTrace()
            }
        }
    }

    if (connectDevicePointer == JSONObject.NULL || connectDevicePointer == null) {
        control.getConnectedDevicePointer(nodeId, object : GetConnectedDeviceCallbackJni.GetConnectedDeviceCallback {

            override fun onDeviceConnected(devicePointer: Long) {
                control.readPath(reportCallback, devicePointer, attributePaths, eventPaths, isFabricFiltered, imTimeoutMs ?: 0, eventMin)
            }

            override fun onConnectionFailure(nodeId: Long, error: java.lang.Exception?) {
                reportCallback.onError(null, null, error ?: RuntimeException("onConnectionFailure"))
                reportCallback.onDone()
            }

        })
    } else {
        control.readPath(reportCallback, connectDevicePointer.toString().toLong(), attributePaths, eventPaths, isFabricFiltered, imTimeoutMs ?: 0, eventMin)
    }


    return createFlutterRequestResult(0, JSONObject())
}

fun write(params: String): String {

    val jsonObject = JSONObject(params)
    val controlId = jsonObject.optNotNull(jsonKeyHandle).toString()
    val control = Objects.requireNonNull((getDeviceController(controlId)), "Not found control")!!
    val attributeListJson = jsonObject.optJSONArray("attributeList")
    var attributePaths: ArrayList<AttributeWriteRequest>? = null
    val callbackHandle = jsonObject.optNotNull("callbackHandle").toString()
    val nodeId = jsonObject.optNotNull("nodeId").toString().toLong()
    val imTimeoutMs = jsonObject.opt("imTimeoutMs")?.toString()?.toIntOrNull()
    val timedRequestTimeoutMs = jsonObject.opt("timedRequestTimeoutMs")?.toString()?.toIntOrNull()
    val connectDevicePointer = jsonObject.opt("connectContext")
    if (attributeListJson != null && attributeListJson != JSONObject.NULL) {
        attributePaths = ArrayList()
        for (i in 0 until attributeListJson.length()) {
            val obj = attributeListJson.optJSONObject(i)
            attributePaths.add(mapAttributeWriteRequest(obj))
        }
    }

    val wc = object : WriteAttributesCallback {
        override fun onError(attributePath: ChipAttributePath?, e: java.lang.Exception?) {
            val p = createFlutterCallPath(deviceControllerHost, "WriteAttributesCallback/onError")
            try {
                FlutterMatterPlugin.externalChannel?.invokeMethodBlockGet(
                    p,
                    JSONObject(mapOf(
                        jsonKeyHandle to controlId,
                        "writeAttributesCallbackPoint" to callbackHandle,
                        "error" to e?.toString(),
                        "attributePath" to attributePath?.toJson()
                    ),
                    ).toString())
            } catch (e: Exception) {
                e.printStackTrace()
            }
        }

        override fun onResponse(attributePath: ChipAttributePath?, status: Status?) {
            val p = createFlutterCallPath(deviceControllerHost, "WriteAttributesCallback/onResponse")
            try {
                FlutterMatterPlugin.externalChannel?.invokeMethodBlockGet(
                    p,
                    JSONObject(mapOf(
                        jsonKeyHandle to controlId,
                        "writeAttributesCallbackPoint" to callbackHandle,
                        "status" to status?.toJson(),
                        "attributePath" to attributePath?.toJson()
                    ),
                    ).toString())
            } catch (e: Exception) {
                e.printStackTrace()
            }
        }

        override fun onDone() {
            val p = createFlutterCallPath(deviceControllerHost, "WriteAttributesCallback/onDone")
            try {
                FlutterMatterPlugin.externalChannel?.invokeMethodBlockGet(
                    p,
                    JSONObject(mapOf(jsonKeyHandle to controlId, "writeAttributesCallbackPoint" to callbackHandle)).toString())
            } catch (e: Exception) {
                e.printStackTrace()
            }
        }
    }

    if (connectDevicePointer == JSONObject.NULL || connectDevicePointer == null) {
        control.getConnectedDevicePointer(nodeId, object : GetConnectedDeviceCallbackJni.GetConnectedDeviceCallback {
            override fun onDeviceConnected(devicePointer: Long) {
                control.write(wc, devicePointer, attributePaths, imTimeoutMs ?: 0, timedRequestTimeoutMs ?: 0)
            }

            override fun onConnectionFailure(nodeId: Long, error: java.lang.Exception?) {
                wc.onError(null, error ?: RuntimeException("onConnectionFailure"))
                wc.onDone()
            }
        })
    } else {
        control.write(wc, connectDevicePointer.toString().toLong(), attributePaths, imTimeoutMs ?: 0, timedRequestTimeoutMs ?: 0)
    }

    return createFlutterRequestResult(0, JSONObject())
}

fun connectedDevice(params: String): String {
    val jsonObject = JSONObject(params)
    val controlId = jsonObject.optNotNull(jsonKeyHandle).toString()
    val control = Objects.requireNonNull((getDeviceController(controlId)), "Not found control")!!
    val nodeId = jsonObject.optNotNull("nodeId").toString().toLong()
    val callbackHandle = jsonObject.optNotNull("callbackHandle").toString()
    control.getConnectedDevicePointer(nodeId, object : GetConnectedDeviceCallbackJni.GetConnectedDeviceCallback {
        override fun onDeviceConnected(devicePointer: Long) {
            val p = createFlutterCallPath(deviceControllerHost, "ConnectedDeviceCallback/onDeviceConnected")
            try {
                FlutterMatterPlugin.externalChannel?.invokeMethodBlockGet(
                    p,
                    JSONObject(mapOf(jsonKeyHandle to controlId, "callbackHandle" to callbackHandle, "context" to devicePointer)).toString())
            } catch (e: Exception) {
                e.printStackTrace()
            }
        }

        override fun onConnectionFailure(nodeId: Long, error: java.lang.Exception?) {
            val p = createFlutterCallPath(deviceControllerHost, "ConnectedDeviceCallback/onConnectionFailure")
            try {
                FlutterMatterPlugin.externalChannel?.invokeMethodBlockGet(
                    p,
                    JSONObject(mapOf(jsonKeyHandle to controlId, "callbackHandle" to callbackHandle, "nodeId" to nodeId, "error" to error?.toString())).toString())
            } catch (e: Exception) {
                e.printStackTrace()
            }
        }
    })
    return createFlutterRequestResult(0, JSONObject())
}

fun releaseConnectContext(params: String): String {
    val jsonObject = JSONObject(params)
    val controlContext = jsonObject.optNotNull("connectContext").toString().toLong()
    val controlId = jsonObject.optNotNull(jsonKeyHandle).toString()
    val control = Objects.requireNonNull((getDeviceController(controlId)), "Not found control")!!
    control.releaseConnectedDevicePointer(controlContext)
    return createFlutterRequestResult(0, JSONObject())
}

fun openPairingWindowWithPIN(params: String): String {
    val jsonObject = JSONObject(params)
    val controlContext = jsonObject.optNotNull("connectContext").toString().toLong()
    val controlId = jsonObject.optNotNull(jsonKeyHandle).toString()
    val control = Objects.requireNonNull((getDeviceController(controlId)), "Not found control")!!
    val duration = jsonObject.optNotNull("duration").toString().toInt()
    val discriminator = jsonObject.optNotNull("discriminator").toString().toInt()
    val setupPIN = jsonObject.optNotNull("setupPIN").toString().toLong()
    val callbackHandle = jsonObject.optNotNull("callbackHandle").toString()
    val success = control.openPairingWindowWithPINCallback(
        controlContext,
        duration,
        1000,
        discriminator,
        setupPIN,
        object : chip.devicecontroller.OpenCommissioningCallback {
            override fun onError(status: Int, deviceId: Long) {
                val p =
                    createFlutterCallPath(deviceControllerHost, "OpenCommissioningCallback/onError")
                try {
                    FlutterMatterPlugin.externalChannel?.invokeMethodBlockGet(
                        p,
                        JSONObject(
                            mapOf(
                                jsonKeyHandle to controlId,
                                "callbackHandle" to callbackHandle,
                                "status" to status,
                                "connectContext" to deviceId
                            )
                        ).toString()
                    )
                } catch (e: Exception) {
                    e.printStackTrace()
                }
            }

            override fun onSuccess(deviceId: Long, manualPairingCode: String?, qrCode: String?) {
                val p = createFlutterCallPath(
                    deviceControllerHost,
                    "OpenCommissioningCallback/onSuccess"
                )
                try {
                    FlutterMatterPlugin.externalChannel?.invokeMethodBlockGet(
                        p,
                        JSONObject(
                            mapOf(
                                jsonKeyHandle to controlId,
                                "callbackHandle" to callbackHandle,
                                "connectContext" to deviceId,
                                "manualPairingCode" to manualPairingCode,
                                "qrCode" to qrCode
                            )
                        ).toString()
                    )
                } catch (e: Exception) {
                    e.printStackTrace()
                }
            }
        })
    return createFlutterRequestResult(0, JSONObject(mapOf("data" to success)))
}

fun unPairDevice(params: String): String {
    val jsonObject = JSONObject(params)
    val controlId = jsonObject.optNotNull(jsonKeyHandle).toString()
    val control = Objects.requireNonNull((getDeviceController(controlId)), "Not found control")!!
    val nodeId = jsonObject.optNotNull("nodeId").toString().toLong()
    control.unpairDevice(nodeId)
    return createFlutterRequestResult(0, JSONObject(mapOf("data" to true)))
}

fun getFabricIndex(params: String): String {
    val jsonObject = JSONObject(params)
    val controlId = jsonObject.optNotNull(jsonKeyHandle).toString()
    val control = Objects.requireNonNull((getDeviceController(controlId)), "Not found control")!!
    return createFlutterRequestResult(0, JSONObject(mapOf("data" to control.getFabricIndex())))
}

fun unSubscribe(params: String): String {
    val jsonObject = JSONObject(params)
    val controlId = jsonObject.optNotNull(jsonKeyHandle).toString()
    val control = Objects.requireNonNull((getDeviceController(controlId)), "Not found control")!!
    val nodeId = jsonObject.optNotNull("nodeId").toString().toLong()
    val fabricIndex = jsonObject.optNotNull("fabricIndex").toString().toInt()
    val subscriptionId = jsonObject.optNotNull("subscriptionId").toString().toLong()
    control.shutdownSubscriptions(fabricIndex, nodeId, subscriptionId)
    return createFlutterRequestResult(0, JSONObject(mapOf("data" to true))) 
}

fun onCloseBleComplete(params: String): String {
    val jsonObject = JSONObject(params)
    val controlId = jsonObject.optNotNull(jsonKeyHandle).toString()
    val control = Objects.requireNonNull((getDeviceController(controlId)), "Not found control")!!
    control.onCloseBleComplete(0 /** Don't care this param */)
    return createFlutterRequestResult(0, JSONObject(mapOf("data" to true))) 
}