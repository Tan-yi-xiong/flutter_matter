package com.zengge.flutter_matter

import io.flutter.plugin.common.MethodChannel
import matter.onboardingpayload.OnboardingPayloadParser
import org.json.JSONObject

fun onOnboardingCall(path: String, params: String, result: MethodChannel.Result) {
    when (path) {
        "/parseManualPairingCode" -> {
            result.success(parseManualPairingCode(params))
        }
        "/parseQrCode" -> {
            result.success(parseQrCode(params))
        }
    }

}

fun parseManualPairingCode(params: String): String {
    val jsonObject = JSONObject(params)
    val pairingCode = jsonObject.optNotNull("pairingCode").toString()
    val payload = OnboardingPayloadParser().parseManualPairingCode(pairingCode)
    return createFlutterRequestResult(0, JSONObject(mapOf("productId" to payload.productId, "vendorId" to payload.vendorId, "commissioningFlow" to payload.commissioningFlow, "discriminator" to payload.discriminator, "version" to payload.version, "discoveryCapabilities" to payload.discoveryCapabilities.map { it.ordinal }, "hasShortDiscriminator" to payload.hasShortDiscriminator, "setupPinCode" to payload.setupPinCode)))
}

fun parseQrCode(params: String): String {
    val jsonObject = JSONObject(params)
    val qrCode = jsonObject.optNotNull("qrCode").toString()
    val payload = OnboardingPayloadParser().parseQrCode(qrCode)
    return createFlutterRequestResult(0, JSONObject(mapOf("productId" to payload.productId, "vendorId" to payload.vendorId, "commissioningFlow" to payload.commissioningFlow, "discriminator" to payload.discriminator, "version" to payload.version, "discoveryCapabilities" to payload.discoveryCapabilities.map { it.ordinal }, "hasShortDiscriminator" to payload.hasShortDiscriminator, "setupPinCode" to payload.setupPinCode)))
}