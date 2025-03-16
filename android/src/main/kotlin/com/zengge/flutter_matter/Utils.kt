package com.zengge.flutter_matter

import android.net.Uri
import android.os.Looper
import android.util.Log
import androidx.core.os.HandlerCompat
import io.flutter.plugin.common.MethodChannel
import org.json.JSONArray
import org.json.JSONObject
import java.util.Objects
import java.util.concurrent.ExecutorService

fun createFlutterCallPath(host: String, path: String): String {
    return Uri.parse("//${host}/${path}").toString()
}

fun isOnMainThread(): Boolean {
    return Looper.getMainLooper() == Looper.myLooper()
}

fun createCallFlutterExceptionMessage(functionName: String): String {
    return "call flutter $functionName failed"
}

fun ByteArray?.nullToEmpty(): ByteArray {
    return this ?: ByteArray(0)
}

fun JSONArray.toByteArray(): ByteArray {
    val byteArray = ByteArray(length())
    for (i in 0 until length()) {
        byteArray[i] = (getInt(i) and 0xFF).toByte()
    }
    return byteArray
}

fun JSONObject.optNotNull(name: String): Any {
    if (isNull(name)) {
        Objects.requireNonNull(null, "Params $name must not be null")
    }
    return get(name)
}

fun MethodChannel.invokeMethodBlockGet(method: String, arguments: Any?): String? {
    if (Looper.myLooper() == Looper.getMainLooper()) {
        throw RuntimeException(
            "Methods must be executed on the not main thread. Current thread: "
                    + Thread.currentThread().name
        )
    }
    var returnResult: String? = null
    val lock = Object()
    var invokeFinish = false
    HandlerCompat.createAsync(Looper.getMainLooper()).post {
        invokeMethod(method, arguments, object : MethodChannel.Result {
            override fun success(result: Any?) {
                matterPrint("invokeMethod $method success call")
                try {
                    val jsonObject = JSONObject(result.toString())
                    val code = jsonObject.optInt("code")
                    if (code == 0) {
                        returnResult = jsonObject.optString("resultJson")
                    } else {
                        matterPrint("invokeMethod $method result failed $result")
                    }
                } catch (e: Exception) {
                    e.printStackTrace()
                }
                synchronized(lock) {
                    lock.notifyAll()
                    invokeFinish = true
                }
            }

            override fun error(errorCode: String, errorMessage: String?, errorDetails: Any?) {
                matterPrint("invokeMethod $method result failed /// $errorCode $errorMessage \n $errorDetails")
                synchronized(lock) {
                    lock.notifyAll()
                    invokeFinish = true
                }
            }

            override fun notImplemented() {
                matterPrint("invokeMethod $method result failed notImplemented")
                synchronized(lock) {
                    lock.notifyAll()
                    invokeFinish = true
                }
            }
        })
    }

    synchronized(lock) {
        // maybe flutter already return in here
        if (!invokeFinish) {
            lock.wait()
        } else {
            matterPrint("Not need wait flutter result")
        }
    }

    return returnResult
}

fun createFlutterRequestResult(code: Int, jsonData: JSONObject): String {
    val jsonObject = JSONObject()
    jsonObject.put("code", code)
    jsonObject.put("jsonData", jsonData)
    return jsonObject.toString()
}

fun matterPrint(msg: String) {
    Log.d("FlutterMatter", msg)
}

fun runOnWorkerThread(executors: ExecutorService, runnable: Runnable) {
    if (isOnMainThread()) {
        executors.execute {
            runnable.run()
        }
    } else {
        runnable.run()
    }
}