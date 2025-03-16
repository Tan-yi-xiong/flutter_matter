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
#import <Matter/Matter.h>

//@implementation FlutterBlePlatformDelegate
//
//- (instancetype)initWithHandle:(NSString *)handle {
//    self = [super init];
//    if (self) {
//        _handle = handle; // 存储 handle
//    }
//    return self;
//}
//
//- (BOOL)subscribeCharacteristicWithConnection:(id)connObj
//                                    serviceId:(NSData *)svcId
//                             characteristicId:(NSData *)charId {
//    NSString *requestPath = createFlutterCallPath(bleHost, @"BlePlatformDelegate/subscribeCharacteristic");
//    NSString *result = invokeMethodBlockGet([Global externalChannel], requestPath, toJSONStringFromObject(@{
//        jsonKeyHandle: _handle,
//        @"connObj": connObj,
//        @"svcId": nsDataToIntegerArray(svcId),
//        @"charId": nsDataToIntegerArray(charId)
//    }));
//    if (result == nil) {
//        return NO;
//    }
//    return YES;
//}
//
//- (BOOL)unsubscribeCharacteristicWithConnection:(id)connObj
//                                      serviceId:(NSData *)svcId
//                               characteristicId:(NSData *)charId {
//    NSString *requestPath = createFlutterCallPath(bleHost, @"BlePlatformDelegate/unsubscribeCharacteristic");
//    NSString *result = invokeMethodBlockGet([Global externalChannel], requestPath, toJSONStringFromObject(@{
//        jsonKeyHandle: _handle,
//        @"connObj": connObj,
//        @"svcId": nsDataToIntegerArray(svcId),
//        @"charId": nsDataToIntegerArray(charId)
//    }));
//    if (result == nil) {
//        return NO;
//    }
//    return YES;
//}
//
//- (BOOL)closeConnectionWithConnection:(id)connObj {
//    NSString *requestPath = createFlutterCallPath(bleHost, @"BlePlatformDelegate/closeConnection");
//    NSString *result = invokeMethodBlockGet([Global externalChannel], requestPath, toJSONStringFromObject(@{
//        jsonKeyHandle: _handle,
//        @"connObj": connObj,
//    }));
//    if (result == nil) {
//        return NO;
//    }
//    return YES;
//}
//
//- (uint16_t)getMTUForConnection:(id)connObj {
//    NSString *requestPath = createFlutterCallPath(bleHost, @"BlePlatformDelegate/getMTU");
//    NSString *result = invokeMethodBlockGet([Global externalChannel], requestPath, toJSONStringFromObject(@{
//        jsonKeyHandle: _handle,
//        @"connObj": connObj,
//    }));
//    if (result == nil) {
//        return 23;
//    }
//    NSDictionary *jsonObject = parseJSONString(result);
//    NSNumber *mtu = requestJsonValueNotNull(jsonObject, @"data");
//    return [mtu unsignedIntValue];
//}
//
//- (BOOL)sendIndicationWithConnection:(id)connObj
//                           serviceId:(NSData *)svcId
//                    characteristicId:(NSData *)charId
//                             payload:(NSData *)pBuf {
//    // This method does not need
//    return NO;
//}
//
//- (BOOL)sendWriteRequestWithConnection:(id)connObj
//                             serviceId:(NSData *)svcId
//                      characteristicId:(NSData *)charId
//                               payload:(NSData *)pBuf {
//    NSString *requestPath = createFlutterCallPath(bleHost, @"BlePlatformDelegate/sendWriteRequest");
//    NSString *result = invokeMethodBlockGet([Global externalChannel], requestPath, toJSONStringFromObject(@{
//        jsonKeyHandle: _handle,
//        @"connObj": connObj,
//        @"svcId": nsDataToIntegerArray(svcId),
//        @"charId": nsDataToIntegerArray(charId),
//        @"data": nsDataToIntegerArray(pBuf),
//    }));
//    if (result == nil) {
//        return NO;
//    }
//    return YES;
//}
//
//@end

static NSString *flutterSetBlePlatformDelegate(NSString *params) {
    NSDictionary *jsonObject = parseJSONString(params);
    NSString *handleId = [jsonObject objectForKey:jsonKeyHandle];
    BOOL setSuccess = NO;
//    if ([handleId isEqual:[NSNull null]]) {
//        setSuccess = [MTRBleManager setBlePlatformDelegate:nil];
//    } else {
//        FlutterBlePlatformDelegate *platformDelegate = [[FlutterBlePlatformDelegate alloc] initWithHandle:handleId];
//        setSuccess = [MTRBleManager setBlePlatformDelegate:platformDelegate];
//    }
    return createFlutterRequestResultWithCode(setSuccess ? 0 : 1, @{});
}

static NSString *handleSubscribeComplete(NSString *params) {
    NSDictionary *jsonObject = parseJSONString(params);
    id connId = requestJsonValueNotNull(jsonObject, @"connObj");
    NSData *svcId = toByteArrayFromJSONArray([jsonObject objectForKey:@"svcId"]);
    NSData *charId = toByteArrayFromJSONArray([jsonObject objectForKey:@"charId"]);
//    NSNumber *success = [jsonObject objectForKey:@"success"];
    BOOL setSuccess = NO;//[MTRBleManager handleSubscribeCompleteWithConnection:connId serviceId:svcId characteristicId:charId];
    return createFlutterRequestResultWithCode(setSuccess ? 0 : 1, @{});
}

static NSString *handleWriteConfirmation(NSString *params) {
    NSDictionary *jsonObject = parseJSONString(params);
    id connId = requestJsonValueNotNull(jsonObject, @"connObj");
    NSData *svcId = toByteArrayFromJSONArray([jsonObject objectForKey:@"svcId"]);
    NSData *charId = toByteArrayFromJSONArray([jsonObject objectForKey:@"charId"]);
    BOOL setSuccess = NO;//[MTRBleManager handleWriteConfirmationWithConnection:connId serviceId:svcId characteristicId:charId];
    return createFlutterRequestResultWithCode(setSuccess ? 0 : 1, @{});
}

static NSString *handleIndicationReceived(NSString *params) {
    NSDictionary *jsonObject = parseJSONString(params);
    id connId = requestJsonValueNotNull(jsonObject, @"connObj");
    NSData *svcId = toByteArrayFromJSONArray([jsonObject objectForKey:@"svcId"]);
    NSData *charId = toByteArrayFromJSONArray([jsonObject objectForKey:@"charId"]);
    NSData *data = toByteArrayFromJSONArray([jsonObject objectForKey:@"pBuf"]);
    BOOL setSuccess = NO;// [MTRBleManager handleIndicationReceivedWithConnection:connId serviceId:svcId characteristicId:charId payloadData:data];
    return createFlutterRequestResultWithCode(setSuccess ? 0 : 1, @{});
}

static NSString *handleUnsubscribeComplete(NSString *params) {
    NSDictionary *jsonObject = parseJSONString(params);
    id connId = requestJsonValueNotNull(jsonObject, @"connObj");
    NSData *svcId = toByteArrayFromJSONArray([jsonObject objectForKey:@"svcId"]);
    NSData *charId = toByteArrayFromJSONArray([jsonObject objectForKey:@"charId"]);
    BOOL setSuccess = NO; //[MTRBleManager handleUnsubscribeCompleteWithConnection:connId serviceId:svcId characteristicId:charId];
    return createFlutterRequestResultWithCode(setSuccess ? 0 : 1, @{});
}

static NSString *handleConnectionError(NSString *params) {
    NSDictionary *jsonObject = parseJSONString(params);
    id connId = requestJsonValueNotNull(jsonObject, @"connId");
//    [MTRBleManager handleConnectionErrorWithConnection:connId];
    return createFlutterRequestResultWithCode(0, @{});
}

void onBLECall(NSString *path, NSString *params, FlutterResult result) {
    FlutterMatterLog([NSString
        stringWithFormat:@"onBLECall path: %@ params: %@", path, params]);
    dispatch_async(
        dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_DEFAULT, 0), ^{
          dispatch_async([Global backgroundSerialQueue], ^() {
            NSString *resultData = nil;
            NSException *resultException = nil;
            @try {
                if ([path isEqualToString:@"/setBlePlatformDelegate"]) {
                    resultData = flutterSetBlePlatformDelegate(params);
                } else if ([path isEqualToString:@"/handleSubscribeComplete"]) {
                    resultData = handleSubscribeComplete(params);
                } else if ([path isEqualToString:@"/handleWriteConfirmation"]) {
                    resultData = handleWriteConfirmation(params);
                } else if ([path isEqualToString:@"/handleIndicationReceived"]) {
                    resultData = handleIndicationReceived(params);
                } else if ([path isEqualToString:@"/handleUnsubscribeComplete"]) {
                    resultData = handleUnsubscribeComplete(params);
                } else if ([path isEqualToString:@"/handleConnectionError"]) {
                    resultData = handleConnectionError(params);
                }
            } @catch (NSException *exception) {
                FlutterMatterLog([[NSString alloc]
                    initWithFormat:@"onBLECall %@ Exception %@", path,
                                  [exception reason]]);
                resultException = exception;
            } @finally {
            }

            // callback run on main
            dispatch_sync(dispatch_get_main_queue(), ^() {
              if (resultException) {
                  result([FlutterError errorWithCode:@"onBLECallException"
                                             message:[resultException reason]
                                             details:nil]);
              } else if (resultData) {
                  result(resultData);
              } else {
                  result(FlutterMethodNotImplemented);
              }
            });
          });
        });
}
