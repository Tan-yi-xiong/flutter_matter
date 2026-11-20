//
//  BleHandle.m
//  Pods
//
//  Created by zero on 28/12/2024.
//

#import "BleHandle.h"
#import "Constants.h"
#import "Global.h"
#import "Utiles.h"
#import <ZGMatter/ZGMatter.h>

static void FlutterMatterValidateOptionalBoolean(NSDictionary *jsonObject,
                                                 NSString *key) {
    (void)FlutterMatterOptionalBoolean(jsonObject, key);
}

static NSString *flutterSetBlePlatformDelegate(NSString *params) {
    NSDictionary *jsonObject = FlutterMatterParseJSONObject(params);
    id handle = FlutterMatterOptionalJSONValue(jsonObject, jsonKeyHandle);
    if (handle != nil && ![handle isKindOfClass:[NSString class]]) {
        @throw [[FlutterMatterArgumentException alloc] initWithArgumentName:jsonKeyHandle
                                                                     message:@"Expected a string or null."];
    }

    // The native BLE delegate is not wired on iOS.  Fail closed with a
    // structured result instead of pretending the callback was installed.
    return createFlutterRequestResultWithCode(1, @{
        @"error": @"BLE platform delegate is not available on iOS.",
    });
}

static void FlutterMatterValidateGattPayload(NSDictionary *jsonObject,
                                              BOOL needsPayload) {
    (void)FlutterMatterRequiredJSONValue(jsonObject, @"connObj");
    (void)FlutterMatterRequiredByteArray(jsonObject, @"svcId");
    (void)FlutterMatterRequiredByteArray(jsonObject, @"charId");
    if (needsPayload) {
        (void)FlutterMatterRequiredByteArray(jsonObject, @"pBuf");
    }
    FlutterMatterValidateOptionalBoolean(jsonObject, @"success");
}

static NSString *handleSubscribeReceived(NSString *params) {
    NSDictionary *jsonObject = FlutterMatterParseJSONObject(params);
    FlutterMatterValidateGattPayload(jsonObject, NO);
    return createFlutterRequestResultWithCode(1, @{
        @"error": @"BLE subscribe callbacks are not available on iOS.",
    });
}

static NSString *handleSubscribeComplete(NSString *params) {
    NSDictionary *jsonObject = FlutterMatterParseJSONObject(params);
    FlutterMatterValidateGattPayload(jsonObject, NO);
    return createFlutterRequestResultWithCode(1, @{
        @"error": @"BLE subscribe completion is not available on iOS.",
    });
}

static NSString *handleWriteReceived(NSString *params) {
    NSDictionary *jsonObject = FlutterMatterParseJSONObject(params);
    FlutterMatterValidateGattPayload(jsonObject, YES);
    return createFlutterRequestResultWithCode(1, @{
        @"error": @"BLE write callbacks are not available on iOS.",
    });
}

static NSString *handleWriteConfirmation(NSString *params) {
    NSDictionary *jsonObject = FlutterMatterParseJSONObject(params);
    FlutterMatterValidateGattPayload(jsonObject, NO);
    return createFlutterRequestResultWithCode(1, @{
        @"error": @"BLE write confirmation is not available on iOS.",
    });
}

static NSString *handleIndicationReceived(NSString *params) {
    NSDictionary *jsonObject = FlutterMatterParseJSONObject(params);
    FlutterMatterValidateGattPayload(jsonObject, YES);
    return createFlutterRequestResultWithCode(1, @{
        @"error": @"BLE indication callbacks are not available on iOS.",
    });
}

static NSString *handleIndicationConfirmation(NSString *params) {
    NSDictionary *jsonObject = FlutterMatterParseJSONObject(params);
    FlutterMatterValidateGattPayload(jsonObject, NO);
    return createFlutterRequestResultWithCode(1, @{
        @"error": @"BLE indication confirmation is not available on iOS.",
    });
}

static NSString *handleUnsubscribeReceived(NSString *params) {
    NSDictionary *jsonObject = FlutterMatterParseJSONObject(params);
    FlutterMatterValidateGattPayload(jsonObject, NO);
    return createFlutterRequestResultWithCode(1, @{
        @"error": @"BLE unsubscribe callbacks are not available on iOS.",
    });
}

static NSString *handleUnsubscribeComplete(NSString *params) {
    NSDictionary *jsonObject = FlutterMatterParseJSONObject(params);
    FlutterMatterValidateGattPayload(jsonObject, NO);
    return createFlutterRequestResultWithCode(1, @{
        @"error": @"BLE unsubscribe completion is not available on iOS.",
    });
}

static NSString *handleConnectionError(NSString *params) {
    NSDictionary *jsonObject = FlutterMatterParseJSONObject(params);
    id connection = FlutterMatterOptionalJSONValue(jsonObject, @"connObj");
    if (connection == nil) {
        connection = FlutterMatterOptionalJSONValue(jsonObject, @"connId");
    }
    if (connection == nil) {
        @throw [[FlutterMatterArgumentException alloc] initWithArgumentName:@"connObj"
                                                                     message:@"Missing required argument."];
    }
    (void)FlutterMatterOptionalNumber(jsonObject, @"err");
    return createFlutterRequestResultWithCode(0, @{});
}

void onBLECall(NSString *path, NSString *params, FlutterResult result) {
    FlutterMatterLog([NSString stringWithFormat:@"onBLECall path: %@", path ?: @""]);
    FlutterMatterResultSender *sender = [[FlutterMatterResultSender alloc] initWithResult:result];
    dispatch_queue_t queue = [Global backgroundSerialQueue];
    if (queue == nil) {
        queue = dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_DEFAULT, 0);
    }

    dispatch_async(queue, ^{
        @try {
            NSString *resultData = nil;
            if ([path isEqualToString:@"/setBlePlatformDelegate"]) {
                resultData = flutterSetBlePlatformDelegate(params);
            } else if ([path isEqualToString:@"/handleSubscribeReceived"]) {
                resultData = handleSubscribeReceived(params);
            } else if ([path isEqualToString:@"/handleSubscribeComplete"]) {
                resultData = handleSubscribeComplete(params);
            } else if ([path isEqualToString:@"/handleUnsubscribeReceived"]) {
                resultData = handleUnsubscribeReceived(params);
            } else if ([path isEqualToString:@"/handleUnsubscribeComplete"]) {
                resultData = handleUnsubscribeComplete(params);
            } else if ([path isEqualToString:@"/handleWriteReceived"]) {
                resultData = handleWriteReceived(params);
            } else if ([path isEqualToString:@"/handleWriteConfirmation"]) {
                resultData = handleWriteConfirmation(params);
            } else if ([path isEqualToString:@"/handleIndicationReceived"]) {
                resultData = handleIndicationReceived(params);
            } else if ([path isEqualToString:@"/handleIndicationConfirmation"]) {
                resultData = handleIndicationConfirmation(params);
            } else if ([path isEqualToString:@"/handleConnectionError"]) {
                resultData = handleConnectionError(params);
            }

            if (resultData != nil) {
                [sender sendValue:resultData];
            } else {
                [sender sendUnknownPathForHost:bleHost path:path ?: @""];
            }
        } @catch (NSException *exception) {
            FlutterMatterLogException(@"onBLECall", exception);
            [sender sendError:FlutterMatterErrorForException(exception,
                                                             FlutterMatterOnBLECallExceptionCode,
                                                             bleHost,
                                                             path ?: @"")];
        }
    });
}
