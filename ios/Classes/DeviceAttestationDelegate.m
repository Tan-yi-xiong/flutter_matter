
#import "DeviceAttestationDelegate.h"
#import "Utiles.h"
#import "Global.h"
#import "Constants.h"

@implementation DeviceAttestationDelegate

- (void)deviceAttestationCompletedForController:(MTRDeviceController *)controller
                             opaqueDeviceHandle:(void *)opaqueDeviceHandle
                          attestationDeviceInfo:(MTRDeviceAttestationDeviceInfo *)attestationDeviceInfo
                                          error:(NSError * _Nullable)error
{
    NSString *p = createFlutterCallPath(deviceControllerHost, @"DeviceAttestationDelegate/onDeviceAttestationCompleted");
    NSString *callResult = invokeMethodBlockGet([Global externalChannel], p, toJSONStringFromObject(@{
        jsonKeyHandle: _handle,
        @"devicePtr": @((uintptr_t)opaqueDeviceHandle),
        @"attestationInfo": @{
            @"challenge": @[],
            @"nonce": @[],
            @"elements": @[],
            @"elementsSignature": @[],
            @"firmwareInfo": @[],
            @"dac": [attestationDeviceInfo dacCertificate] == nil ? @[] : nsDataToIntegerArray([attestationDeviceInfo dacCertificate]),
            @"pai": [attestationDeviceInfo dacPAICertificate] == nil ? @[] : nsDataToIntegerArray([attestationDeviceInfo dacPAICertificate]),
            @"vendorId": [attestationDeviceInfo vendorID],
            @"productId": [attestationDeviceInfo productID],
            @"certificationDeclaration": [attestationDeviceInfo certificateDeclaration] == nil ? @[]: nsDataToIntegerArray([attestationDeviceInfo certificateDeclaration]),
        },
        @"errorCode": error == nil ? @(0) : @([error code])
    }));
    if (callResult == nil) {
        @throw [NSException exceptionWithName:@"deviceAttestationCompletedForControllerException"
                                       reason:@"Flutter onDeviceAttestationCompleted result null"
                                     userInfo:nil];
    }
}

- (instancetype)initWithHandle:(NSString *)handle {
    self = [super init];
    if (self) {
        _handle = handle; // 存储 handle
    }
    return self;
}

@end
