package com.tyx.flutter_matter

import io.flutter.plugin.common.MethodChannel
import matter.onboardingpayload.DiscoveryCapability
import matter.onboardingpayload.OnboardingPayload
import matter.onboardingpayload.OnboardingPayloadParser
import org.json.JSONObject

fun onOnboardingCall(path: String, params: String, result: MethodChannel.Result) {
    matterPrint("onOnboardingCall $path")
    val response = try {
        when (path) {
            "/parseManualPairingCode" -> parseManualPairingCode(params)
            "/parseQrCode" -> parseQrCode(params)
            else -> throw IllegalArgumentException("Unsupported onboarding request")
        }
    } catch (e: Exception) {
        reportPlatformException("Onboarding $path failed", e)
        result.postPlatformError(
            "-99",
            onboardingErrorMessage(path),
            safePlatformErrorDetails(e),
            "Onboarding $path"
        )
        return
    }

    try {
        result.success(response)
    } catch (e: Exception) {
        reportPlatformException("Onboarding $path result delivery failed", e)
    }
}

private fun onboardingErrorMessage(path: String): String {
    return when (path) {
        "/parseManualPairingCode" -> "Unable to parse manual pairing code"
        "/parseQrCode" -> "Unable to parse QR code"
        else -> "Unsupported onboarding request"
    }
}

private fun parseOnboardingString(params: String, fieldName: String): String {
    val jsonObject = try {
        JSONObject(params)
    } catch (e: Exception) {
        throw IllegalArgumentException("Onboarding request must be a JSON object", e)
    }
    return jsonObject.requiredStringParam(fieldName)
}

private fun parseManualPayload(pairingCode: String): OnboardingPayload {
    return try {
        OnboardingPayloadParser().parseManualPairingCode(pairingCode)
    } catch (e: Exception) {
        throw IllegalArgumentException("Manual pairing code could not be parsed", e)
    }
}

private fun parseQrPayload(qrCode: String): OnboardingPayload {
    return try {
        OnboardingPayloadParser().parseQrCode(qrCode)
    } catch (e: Exception) {
        throw IllegalArgumentException("QR code could not be parsed", e)
    }
}

internal fun discoveryCapabilitiesToDart(
    capabilities: Iterable<DiscoveryCapability>
): List<Int> {
    return capabilities.mapNotNull { capability ->
        when (capability) {
            DiscoveryCapability.SOFT_AP -> 1
            DiscoveryCapability.BLE -> 2
            DiscoveryCapability.ON_NETWORK -> 3
            else -> null
        }
    }
}

private fun onboardingPayloadToJson(payload: OnboardingPayload): JSONObject {
    return JSONObject(
        mapOf(
            "productId" to payload.productId,
            "vendorId" to payload.vendorId,
            "commissioningFlow" to payload.commissioningFlow,
            "discriminator" to payload.discriminator,
            "version" to payload.version,
            "discoveryCapabilities" to discoveryCapabilitiesToDart(payload.discoveryCapabilities),
            "hasShortDiscriminator" to payload.hasShortDiscriminator,
            "setupPinCode" to payload.setupPinCode
        )
    )
}

fun parseManualPairingCode(params: String): String {
    val pairingCode = parseOnboardingString(params, "pairingCode")
    val payload = parseManualPayload(pairingCode)
    return createFlutterRequestResult(0, onboardingPayloadToJson(payload))
}

fun parseQrCode(params: String): String {
    val qrCode = parseOnboardingString(params, "qrCode")
    val payload = parseQrPayload(qrCode)
    return createFlutterRequestResult(0, onboardingPayloadToJson(payload))
}
