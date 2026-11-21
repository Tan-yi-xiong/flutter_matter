
#import "DeviceAttestationDelegate.h"
#import "Utiles.h"
#import "Global.h"
#import "Constants.h"
#import <ZGMatter/ZGMatter.h>

@implementation DeviceAttestationDelegate

- (void)deviceAttestationCompletedForController:(ZGMTRDeviceController *)controller
                             opaqueDeviceHandle:(void *)opaqueDeviceHandle
                          attestationDeviceInfo:(ZGMTRDeviceAttestationDeviceInfo *)attestationDeviceInfo
                                          error:(NSError * _Nullable)error
{
    (void)controller;
    @try {
        NSString *path = createFlutterCallPath(deviceControllerHost,
                                               @"DeviceAttestationDelegate/onDeviceAttestationCompleted");
        NSNumber *vendorId = @(0);
        NSNumber *productId = @(0);
        if (attestationDeviceInfo != nil) {
            if (@available(iOS 16.4, *)) {
                vendorId = [attestationDeviceInfo vendorID] ?: @(0);
                productId = [attestationDeviceInfo productID] ?: @(0);
            }
        }
        NSDictionary *attestationInfo = attestationDeviceInfo == nil ? @{
            @"challenge": @[],
            @"nonce": @[],
            @"elements": @[],
            @"elementsSignature": @[],
            @"firmwareInfo": @[],
            @"dac": @[],
            @"pai": @[],
            @"vendorId": vendorId,
            @"productId": productId,
            @"certificationDeclaration": @[],
        } : @{
            @"challenge": @[],
            @"nonce": @[],
            @"elements": @[],
            @"elementsSignature": @[],
            @"firmwareInfo": @[],
            @"dac": nsDataToIntegerArray([attestationDeviceInfo dacCertificate]),
            @"pai": nsDataToIntegerArray([attestationDeviceInfo dacPAICertificate]),
            @"vendorId": vendorId,
            @"productId": productId,
            @"certificationDeclaration": nsDataToIntegerArray([attestationDeviceInfo certificateDeclaration]),
        };

        NSString *callResult = invokeMethodBlockGet(
            [Global externalChannel], path,
            toJSONStringFromObject(@{
                jsonKeyHandle: _handle ?: @"",
                @"devicePtr": @((uintptr_t)opaqueDeviceHandle),
                @"attestationInfo": attestationInfo,
                @"errorCode": error == nil ? @(0) : @([error code]),
            }));
        if (callResult == nil) {
            @throw [NSException exceptionWithName:@"FlutterMatterCallbackDeliveryException"
                                           reason:@"Device attestation callback delivery failed."
                                         userInfo:nil];
        }
    } @catch (NSException *exception) {
        FlutterMatterLogException(@"DeviceAttestationDelegate.onDeviceAttestationCompleted",
                                  exception);
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
