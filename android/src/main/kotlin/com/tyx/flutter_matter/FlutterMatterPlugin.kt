package com.tyx.flutter_matter

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
    engineSessions.register(this, channel)
    if (!hasDeviceControllerLifecycleActivity()) {
      externalChannel = channel
    }
    globalContext = flutterPluginBinding.applicationContext
    ChipClient.getAndroidChipPlatform(flutterPluginBinding.applicationContext)
  }

  internal fun isAttachedToEngine(): Boolean = engineSessions.isRegistered(this)

  internal fun useControllerChannel() {
    externalChannel = channel
  }

  override fun onMethodCall(call: MethodCall, result: Result) {
    val uri = Uri.parse(call.method)
    when (uri.host?.lowercase()) {
      deviceControllerHost -> {
        onDeviceControlCall(uri.path!!, call.arguments.toString(), result, this)
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
    val ownsController = isDeviceControllerOwnedBy(this)
    val fallbackChannel = engineSessions.unregister(this)
    if (externalChannel === channel) {
      externalChannel = if (ownsController) null else fallbackChannel
    }
    scheduleDeviceControllerShutdownOnEngineDetach(this)
  }

  companion object {
    private const val TAG = "FlutterMatterPlugin"
    private val engineSessions = EngineSessionRegistry<FlutterMatterPlugin, MethodChannel>()
    @Volatile
    var externalChannel : MethodChannel? = null
    @SuppressLint("StaticFieldLeak")
    var globalContext: Context? = null
    val executors = Executors.newSingleThreadExecutor()
  }
}
