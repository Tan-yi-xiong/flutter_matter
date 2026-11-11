package com.tyx.flutter_matter

import android.app.Service
import android.content.Intent
import android.os.IBinder
import android.util.Log
import com.google.android.gms.home.matter.commissioning.CommissioningCompleteMetadata
import com.google.android.gms.home.matter.commissioning.CommissioningRequestMetadata
import com.google.android.gms.home.matter.commissioning.CommissioningService
import org.json.JSONObject

class MyMatterCommissioningService : Service(), CommissioningService.Callback {

    private lateinit var commissioningServiceDelegate: CommissioningService

    override fun onCreate() {
        super.onCreate()
        commissioningServiceDelegate = CommissioningService.Builder(this)
            .setCallback(this)
            .build()
    }

    override fun onBind(intent: Intent): IBinder? {
        Log.d("MatterService", "onBind")
        return commissioningServiceDelegate.asBinder()
    }

    override fun onCommissioningRequested(metadata: CommissioningRequestMetadata) {
        Log.d("MatterService", "onCommissioningRequested: device is on network")
        
        val ipAddress = metadata.networkLocation?.ipAddress?.hostAddress
        val passcode = metadata.passcode
        
        Log.d("MatterService", "IP: $ipAddress, passcode: $passcode")

        val resultJson = JSONObject()
        resultJson.put("ipAddress", ipAddress)
        resultJson.put("passcode", passcode)
        resultJson.put("vendorId", metadata.deviceDescriptor.vendorId)
        resultJson.put("productId", metadata.deviceDescriptor.productId)

        FlutterMatterPlugin.externalChannel?.invokeMethod("onPlayServicesCommissioningRequested", resultJson.toString())

        // Notify Google Play Services of success.
        commissioningServiceDelegate.sendCommissioningComplete(
            CommissioningCompleteMetadata.builder()
                .setToken("flutter_matter_device")
                .build()
        )
    }
}

