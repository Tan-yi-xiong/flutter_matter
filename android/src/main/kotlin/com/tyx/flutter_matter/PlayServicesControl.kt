package com.tyx.flutter_matter

import android.content.ComponentName
import io.flutter.plugin.common.MethodChannel
import com.google.android.gms.home.matter.Matter
import com.google.android.gms.home.matter.commissioning.CommissioningRequest
import org.json.JSONObject

fun onPlayServicesCall(path: String, params: String, result: MethodChannel.Result) {
    try {
        when (path) {
            "/commissionDevice" -> {
                val context = FlutterMatterPlugin.globalContext
                if (context == null) {
                    result.error("-1", "Context is null", null)
                    return
                }
                
                val commissionRequestBuilder = CommissioningRequest.builder()
                    .setCommissioningService(ComponentName(context, MyMatterCommissioningService::class.java))
                    .build()

                Matter.getCommissioningClient(context)
                    .commissionDevice(commissionRequestBuilder)
                    .addOnSuccessListener {
                        result.success(createFlutterRequestResult(0, JSONObject(mapOf("success" to true))))
                    }
                    .addOnFailureListener { error ->
                        result.error("-2", error.message, null)
                    }
            }
            else -> {
                result.error("-99", "Unknown play services path: $path", null)
            }
        }
    } catch (e: Exception) {
        e.printStackTrace()
        result.error("-99", e.stackTraceToString(), null)
    }
}
