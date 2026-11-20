package com.tyx.flutter_matter

import android.net.Uri
import android.os.Looper
import android.util.Log
import androidx.core.os.HandlerCompat
import io.flutter.plugin.common.MethodChannel
import org.json.JSONArray
import org.json.JSONException
import org.json.JSONObject
import java.util.concurrent.ExecutorService
import java.util.concurrent.RejectedExecutionException

internal const val FLUTTER_MATTER_LOG_TAG = "FlutterMatter"

private const val FLUTTER_CALLBACK_TIMEOUT_MS = 30_000L

fun createFlutterCallPath(host: String, path: String): String {
    return Uri.parse("//${host}/${path}").toString()
}

fun isOnMainThread(): Boolean {
    return Looper.getMainLooper() == Looper.myLooper()
}

fun createCallFlutterExceptionMessage(functionName: String): String {
    return "call flutter $functionName failed"
}

internal fun reportPlatformException(context: String, error: Throwable) {
    // Log frames only. Throwable messages can contain setup payloads,
    // credentials, or full request bodies supplied by the host app.
    val frames = error.stackTrace.joinToString(separator = "\n") { it.toString() }
    Log.e(FLUTTER_MATTER_LOG_TAG, "$context failed (${error.javaClass.name})\n$frames")
}

internal fun platformErrorCategory(error: Throwable): String {
    return when (error) {
        is JSONException -> "invalid-json"
        is NumberFormatException -> "invalid-number"
        is IllegalArgumentException -> "invalid-request"
        is IllegalStateException -> "invalid-state"
        else -> "internal-error"
    }
}

internal fun safePlatformErrorMessage(prefix: String, error: Throwable): String {
    return when (error) {
        is JSONException -> "$prefix request payload is invalid"
        is NumberFormatException -> "$prefix request contains an invalid number"
        is IllegalArgumentException -> "$prefix request parameter is invalid"
        is IllegalStateException -> "$prefix operation is not available"
        else -> "$prefix operation failed"
    }
}

internal fun safePlatformErrorDetails(error: Throwable): String {
    return JSONObject(
        mapOf(
            "category" to platformErrorCategory(error),
            "errorType" to error.javaClass.simpleName.ifBlank { "Throwable" }
        )
    ).toString()
}

private fun MethodChannel.Result.postToMain(context: String, action: () -> Unit) {
    val posted = HandlerCompat.createAsync(Looper.getMainLooper()).post {
        try {
            action()
        } catch (e: Exception) {
            reportPlatformException("$context result delivery", e)
        }
    }
    if (!posted) {
        reportPlatformException(
            "$context result delivery",
            IllegalStateException("Main looper is unavailable")
        )
    }
}

internal fun MethodChannel.Result.postPlatformSuccess(data: Any, context: String) {
    postToMain(context) {
        success(data)
    }
}

internal fun MethodChannel.Result.postPlatformError(
    code: String,
    message: String,
    details: String?,
    context: String
) {
    postToMain(context) {
        error(code, message, details)
    }
}

fun ByteArray?.nullToEmpty(): ByteArray {
    return this ?: ByteArray(0)
}

internal fun jsonNumberToByte(value: Any?): Byte {
    val number = value as? Number
        ?: throw IllegalArgumentException("Byte array element must be an integer between 0 and 255")

    val asLong = when (number) {
        is Byte, is Short, is Int, is Long -> number.toLong()
        else -> {
            val asDouble = number.toDouble()
            if (asDouble.isNaN() || asDouble.isInfinite() ||
                asDouble < 0.0 || asDouble > 255.0 ||
                asDouble != asDouble.toLong().toDouble()
            ) {
                throw IllegalArgumentException("Byte array element must be an integer between 0 and 255")
            }
            asDouble.toLong()
        }
    }

    if (asLong < 0L || asLong > 255L) {
        throw IllegalArgumentException("Byte array element must be an integer between 0 and 255")
    }
    return asLong.toByte()
}

fun JSONArray.toByteArray(): ByteArray {
    val byteArray = ByteArray(length())
    for (i in 0 until length()) {
        byteArray[i] = jsonNumberToByte(opt(i))
    }
    return byteArray
}

fun JSONObject.optNotNull(name: String): Any {
    if (!has(name) || isNull(name)) {
        throw IllegalArgumentException("Missing required parameter: $name")
    }
    return get(name)
}

internal fun JSONObject.requiredStringParam(name: String): String {
    val value = optNotNull(name)
    if (value !is String) {
        throw IllegalArgumentException("Parameter must be a string: $name")
    }
    if (value.isBlank()) {
        throw IllegalArgumentException("Parameter must not be empty: $name")
    }
    return value
}

internal fun JSONObject.requiredIntParam(name: String): Int {
    val value = optNotNull(name)
    val number = value as? Number
        ?: throw IllegalArgumentException("Parameter must be an integer: $name")
    val asDouble = number.toDouble()
    if (asDouble.isNaN() || asDouble.isInfinite() || asDouble != asDouble.toLong().toDouble()) {
        throw IllegalArgumentException("Parameter must be an integer: $name")
    }
    val asLong = number.toLong()
    if (asLong < Int.MIN_VALUE || asLong > Int.MAX_VALUE) {
        throw IllegalArgumentException("Parameter is outside the integer range: $name")
    }
    return asLong.toInt()
}

internal fun JSONObject.requiredBooleanParam(name: String): Boolean {
    val value = optNotNull(name)
    if (value !is Boolean) {
        throw IllegalArgumentException("Parameter must be a boolean: $name")
    }
    return value
}

internal fun JSONObject.requiredByteArrayParam(name: String): ByteArray {
    val value = optNotNull(name)
    if (value !is JSONArray) {
        throw IllegalArgumentException("Parameter must be a byte array: $name")
    }
    return value.toByteArray()
}

fun MethodChannel.invokeMethodBlockGet(method: String, arguments: Any?): String? {
    if (Looper.myLooper() == Looper.getMainLooper()) {
        throw IllegalStateException(
            "Methods must be executed on the not main thread. Current thread: "
                    + Thread.currentThread().name
        )
    }
    var returnResult: String? = null
    val lock = Object()
    var invokeFinish = false

    fun finish(result: String?) {
        synchronized(lock) {
            if (invokeFinish) {
                return
            }
            returnResult = result
            invokeFinish = true
            lock.notifyAll()
        }
    }

    val posted = HandlerCompat.createAsync(Looper.getMainLooper()).post {
        try {
            invokeMethod(method, arguments, object : MethodChannel.Result {
                override fun success(result: Any?) {
                    try {
                        if (result !is String) {
                            throw IllegalStateException("Flutter callback result is not a JSON string")
                        }
                        val jsonObject = JSONObject(result)
                        val rawCode = jsonObject.opt("code")
                        if (rawCode !is Number) {
                            throw IllegalStateException("Flutter callback result has no integer code")
                        }
                        val code = rawCode.toInt()
                        if (code == 0) {
                            matterPrint("invokeMethod $method success call")
                            finish(jsonObject.optString("resultJson"))
                        } else {
                            matterPrint("invokeMethod $method result failed with code $code")
                            finish(null)
                        }
                    } catch (e: Exception) {
                        reportPlatformException("Flutter callback $method result parsing", e)
                        finish(null)
                    }
                }

                override fun error(errorCode: String, errorMessage: String?, errorDetails: Any?) {
                    matterPrint("invokeMethod $method result failed with code $errorCode")
                    finish(null)
                }

                override fun notImplemented() {
                    matterPrint("invokeMethod $method result failed: not implemented")
                    finish(null)
                }
            })
        } catch (e: Exception) {
            reportPlatformException("Flutter callback $method dispatch", e)
            finish(null)
        }
    }
    if (!posted) {
        reportPlatformException(
            "Flutter callback $method dispatch",
            IllegalStateException("Main looper is unavailable")
        )
        finish(null)
    }

    synchronized(lock) {
        val deadline = System.currentTimeMillis() + FLUTTER_CALLBACK_TIMEOUT_MS
        while (!invokeFinish) {
            val remaining = deadline - System.currentTimeMillis()
            if (remaining <= 0) {
                break
            }
            try {
                lock.wait(remaining)
            } catch (e: InterruptedException) {
                Thread.currentThread().interrupt()
                throw IllegalStateException("Flutter callback was interrupted", e)
            }
        }
        if (!invokeFinish) {
            throw IllegalStateException("Flutter callback timed out")
        }
        return returnResult
    }
}

fun createFlutterRequestResult(code: Int, jsonData: JSONObject): String {
    val jsonObject = JSONObject()
    jsonObject.put("code", code)
    jsonObject.put("jsonData", jsonData)
    return jsonObject.toString()
}

fun matterPrint(msg: String) {
    Log.d(FLUTTER_MATTER_LOG_TAG, msg)
}

fun runOnWorkerThread(executors: ExecutorService, runnable: Runnable) {
    if (isOnMainThread()) {
        try {
            executors.execute {
                try {
                    runnable.run()
                } catch (e: Exception) {
                    reportPlatformException("worker task", e)
                }
            }
        } catch (e: RejectedExecutionException) {
            reportPlatformException("worker task submission", e)
            throw e
        }
    } else {
        try {
            runnable.run()
        } catch (e: Exception) {
            reportPlatformException("worker task", e)
        }
    }
}
