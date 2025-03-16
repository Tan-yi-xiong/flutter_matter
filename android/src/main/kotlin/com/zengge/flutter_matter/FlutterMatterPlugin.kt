package com.zengge.flutter_matter

import android.annotation.SuppressLint
import android.content.Context
import android.net.Uri

import io.flutter.embedding.engine.plugins.FlutterPlugin
import io.flutter.plugin.common.MethodCall
import io.flutter.plugin.common.MethodChannel
import io.flutter.plugin.common.MethodChannel.MethodCallHandler
import io.flutter.plugin.common.MethodChannel.Result
import java.util.concurrent.Executors

/** FlutterMatterPlugin */
class FlutterMatterPlugin: FlutterPlugin, MethodCallHandler {
  /// The MethodChannel that will the communication between Flutter and native Android
  ///
  /// This local reference serves to register the plugin with the Flutter Engine and unregister it
  /// when the Flutter Engine is detached from the Activity
  private lateinit var channel : MethodChannel

  override fun onAttachedToEngine(flutterPluginBinding: FlutterPlugin.FlutterPluginBinding) {
    channel = MethodChannel(flutterPluginBinding.binaryMessenger, "flutter_matter")
    channel.setMethodCallHandler(this)
    externalChannel = channel
    globalContext = flutterPluginBinding.applicationContext
    ChipClient.getAndroidChipPlatform(flutterPluginBinding.applicationContext)
  }

  override fun onMethodCall(call: MethodCall, result: Result) {
    val uri = Uri.parse(call.method)
    when (uri.host?.lowercase()) {
      deviceControllerHost -> {
        onDeviceControlCall(uri.path!!, call.arguments.toString(), result)
      }
      bleHost -> {
        onBLECall(uri.path!!, call.arguments.toString(), result)
      }
      OnboardingHost -> {
        onOnboardingCall(uri.path!!, call.arguments.toString(), result)
      }
      nsdHost -> {
        onNsdCall(uri.path!!, call.arguments.toString(), result)
      }
      else -> {
        result.error("1", "Unable handle $uri", "")
      }
    }
  }

  override fun onDetachedFromEngine(binding: FlutterPlugin.FlutterPluginBinding) {
    channel.setMethodCallHandler(null)
  }

  companion object {
    private const val TAG = "FlutterMatterPlugin"
    var externalChannel : MethodChannel? = null
    @SuppressLint("StaticFieldLeak")
    var globalContext: Context? = null
    val executors = Executors.newSingleThreadExecutor()
  }
}
