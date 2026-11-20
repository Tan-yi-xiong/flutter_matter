/**
 *
 *    Copyright (c) 2020 Project CHIP Authors
 *
 *    Licensed under the Apache License, Version 2.0 (the "License");
 *    you may not use this file except in compliance with the License.
 *    You may obtain a copy of the License at
 *
 *        http://www.apache.org/licenses/LICENSE-2.0
 *
 *    Unless required by applicable law or agreed to in writing, software
 *    distributed under the License is distributed on an "AS IS" BASIS,
 *    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *    See the License for the specific language governing permissions and
 *    limitations under the License.
 */

#import "DefaultsUtils.h"
#import "FabricKeys.h"
#import "Utiles.h"

NSString * const ZGMTRToolDefaultsDomain = @"com.matter.CHIPTool";
NSString * const kNetworkSSIDDefaultsKey = @"networkSSID";
NSString * const kNetworkPasswordDefaultsKey = @"networkPassword";
NSString * const ZGMTRNextAvailableDeviceIDKey = @"nextDeviceID";
NSString * const kFabricIdKey = @"fabricId";
NSString * const kDevicePairedKey = @"Paired";

id ZGMTRGetDomainValueForKey(NSString * domain, NSString * key)
{
    id value = (id) CFBridgingRelease(CFPreferencesCopyAppValue((CFStringRef) key, (CFStringRef) domain));
    if (value) {
        return value;
    }
    return nil;
}

BOOL ZGMTRSetDomainValueForKey(NSString * domain, NSString * key, id value)
{
    CFPreferencesSetAppValue((CFStringRef) key, (__bridge CFPropertyListRef _Nullable)(value), (CFStringRef) domain);
    return CFPreferencesAppSynchronize((CFStringRef) domain) == true;
}

void ZGMTRRemoveDomainValueForKey(NSString * domain, NSString * key)
{
    CFPreferencesSetAppValue((CFStringRef) key, NULL, (CFStringRef) domain);
    CFPreferencesAppSynchronize((CFStringRef) domain);
}

uint64_t ZGMTRGetNextAvailableDeviceID(void)
{
    uint64_t nextAvailableDeviceIdentifier = 1;
    NSNumber * value = ZGMTRGetDomainValueForKey(ZGMTRToolDefaultsDomain, ZGMTRNextAvailableDeviceIDKey);
    if (!value) {
        ZGMTRSetDomainValueForKey(ZGMTRToolDefaultsDomain, ZGMTRNextAvailableDeviceIDKey,
            [NSNumber numberWithUnsignedLongLong:nextAvailableDeviceIdentifier]);
    } else {
        nextAvailableDeviceIdentifier = [value unsignedLongLongValue];
    }

    return nextAvailableDeviceIdentifier;
}

void ZGMTRSetNextAvailableDeviceID(uint64_t id)
{
    ZGMTRSetDomainValueForKey(ZGMTRToolDefaultsDomain, ZGMTRNextAvailableDeviceIDKey, [NSNumber numberWithUnsignedLongLong:id]);
}

static CHIPToolPersistentStorageDelegate * storage = nil;

static uint16_t kTestVendorId = 0xFFF4u;

static ZGMTRDeviceController * sController = nil;

ZGMTRDeviceController * InitializeZGMTR(void)
{
    static dispatch_once_t onceToken;
    dispatch_once(&onceToken, ^{
        CHIPToolPersistentStorageDelegate * storage = [[CHIPToolPersistentStorageDelegate alloc] init];
        __auto_type * factory = [ZGMTRControllerFactory sharedInstance];
        __auto_type * factoryParams = [[ZGMTRControllerFactoryParams alloc] initWithStorage:storage];
        if (![factory startup:factoryParams]) {
            FlutterMatterLog(@"Matter controller factory startup failed");
            return;
        }

        __auto_type * keys = [[FabricKeys alloc] init];
        if (keys == nil) {
            FlutterMatterLog(@"Matter fabric keys could not be initialized");
            return;
        }

        __auto_type * params = [[ZGMTRDeviceControllerStartupParams alloc] initWithSigningKeypair:keys fabricId:1 ipk:keys.ipk];
        params.vendorId = @(kTestVendorId);
        // We're not sure whether we have a fabric configured already; try as if
        // we did, and if not fall back to creating a new one.
        sController = [factory startControllerOnExistingFabric:params];
        if (sController == nil) {
            sController = [factory startControllerOnNewFabric:params];
        }
    });

    return sController;
}

ZGMTRDeviceController * ZGMTRRestartController(ZGMTRDeviceController * controller)
{
    __auto_type * keys = [[FabricKeys alloc] init];
    if (keys == nil) {
        FlutterMatterLog(@"No fabric keys; controller was not restarted");
        return controller;
    }

    FlutterMatterLog(@"Shutting down Matter controller");
    [controller shutdown];

    FlutterMatterLog(@"Starting Matter controller");
    __auto_type * params = [[ZGMTRDeviceControllerStartupParams alloc] initWithSigningKeypair:keys fabricId:1 ipk:keys.ipk];

    sController = [[ZGMTRControllerFactory sharedInstance] startControllerOnExistingFabric:params];

    return sController;
}

uint64_t ZGMTRGetLastPairedDeviceId(void)
{
    uint64_t deviceId = ZGMTRGetNextAvailableDeviceID();
    if (deviceId > 1) {
        deviceId--;
    }
    return deviceId;
}

BOOL ZGMTRGetConnectedDevice(ZGMTRDeviceConnectionCallback completionHandler)
{
    if (completionHandler == nil) {
        FlutterMatterLog(@"Connected-device lookup missing completion handler");
        return NO;
    }
    ZGMTRDeviceController * controller = InitializeZGMTR();
    if (controller == nil) {
        FlutterMatterLog(@"No Matter controller is available for device lookup");
        return NO;
    }

    // Let's use the last device that was paired
    uint64_t deviceId = ZGMTRGetLastPairedDeviceId();
    return [controller getBaseDevice:deviceId queue:dispatch_get_main_queue() completionHandler:completionHandler];
}

ZGMTRBaseDevice * ZGMTRGetDeviceBeingCommissioned(void)
{
    NSError * error = nil;
    ZGMTRDeviceController * controller = InitializeZGMTR();
    if (controller == nil) {
        FlutterMatterLog(@"No Matter controller is available for device lookup");
        return nil;
    }
    ZGMTRBaseDevice * device = [controller getDeviceBeingCommissioned:ZGMTRGetLastPairedDeviceId() error:&error];
    if (error) {
        FlutterMatterLogNSError(@"defaults.getDeviceBeingCommissioned", error);
        return nil;
    }
    return device;
}

BOOL ZGMTRGetConnectedDeviceWithID(uint64_t deviceId, ZGMTRDeviceConnectionCallback completionHandler)
{
    if (completionHandler == nil) {
        FlutterMatterLog(@"Commissioned-device lookup missing completion handler");
        return NO;
    }
    ZGMTRDeviceController * controller = InitializeZGMTR();
    if (controller == nil) {
        FlutterMatterLog(@"No Matter controller is available for commissioned-device lookup");
        return NO;
    }

    return [controller getBaseDevice:deviceId queue:dispatch_get_main_queue() completionHandler:completionHandler];
}

BOOL ZGMTRIsDevicePaired(uint64_t deviceId)
{
    NSString * PairedString = ZGMTRGetDomainValueForKey(ZGMTRToolDefaultsDomain, KeyForPairedDevice(deviceId));
    return [PairedString boolValue];
}

void ZGMTRSetDevicePaired(uint64_t deviceId, BOOL paired)
{
    ZGMTRSetDomainValueForKey(ZGMTRToolDefaultsDomain, KeyForPairedDevice(deviceId), paired ? @"YES" : @"NO");
}

NSString * KeyForPairedDevice(uint64_t deviceId) { return [NSString stringWithFormat:@"%@%llu", kDevicePairedKey, deviceId]; }

void ZGMTRUnpairDeviceWithID(uint64_t deviceId)
{
    ZGMTRSetDevicePaired(deviceId, NO);
    ZGMTRGetConnectedDeviceWithID(deviceId, ^(ZGMTRBaseDevice * _Nullable device, NSError * _Nullable error) {
        if (error) {
            FlutterMatterLogNSError(@"defaults.unpair.lookup", error);
            return;
        }
        if (device == nil) {
            FlutterMatterLog(@"Unpair device lookup returned no device");
            return;
        }
        FlutterMatterLog(@"Attempting to unpair commissioned device");
        ZGMTRBaseClusterOperationalCredentials * opCredsCluster =
            [[ZGMTRBaseClusterOperationalCredentials alloc] initWithDevice:device endpoint:0 queue:dispatch_get_main_queue()];
        [opCredsCluster
            readAttributeCurrentFabricIndexWithCompletionHandler:^(NSNumber * _Nullable value, NSError * _Nullable error) {
                if (error) {
                    FlutterMatterLogNSError(@"defaults.unpair.fabricIndex", error);
                    return;
                }
                if (value == nil) {
                    FlutterMatterLog(@"Unpair fabric-index lookup returned no value");
                    return;
                }
                ZGMTROperationalCredentialsClusterRemoveFabricParams * params =
                    [[ZGMTROperationalCredentialsClusterRemoveFabricParams alloc] init];
                params.fabricIndex = value;
                [opCredsCluster removeFabricWithParams:params
                                     completionHandler:^(ZGMTROperationalCredentialsClusterNOCResponseParams * _Nullable data,
                                         NSError * _Nullable error) {
                                         if (error) {
                                             FlutterMatterLogNSError(@"defaults.unpair.removeFabric", error);
                                             return;
                                         }
                                         FlutterMatterLog(@"Successfully unpaired commissioned device");
                                     }];
            }];
    });
}

@implementation CHIPToolPersistentStorageDelegate

// MARK: ZGMTRPersistentStorageDelegate

- (nullable NSData *)storageDataForKey:(NSString *)key
{
    NSData * value = ZGMTRGetDomainValueForKey(ZGMTRToolDefaultsDomain, key);
    if (value != nil && ![value isKindOfClass:[NSData class]]) {
        FlutterMatterLog(@"Persistent storage returned an unexpected value type");
        return nil;
    }
    return value;
}

- (BOOL)setStorageData:(NSData *)value forKey:(NSString *)key
{
    return ZGMTRSetDomainValueForKey(ZGMTRToolDefaultsDomain, key, value);
}

- (BOOL)removeStorageDataForKey:(NSString *)key
{
    if (ZGMTRGetDomainValueForKey(ZGMTRToolDefaultsDomain, key) == nil) {
        return NO;
    }
    ZGMTRRemoveDomainValueForKey(ZGMTRToolDefaultsDomain, key);
    return YES;
}

@end
