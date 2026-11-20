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

static CHIPToolPersistentStorageDelegate * sStorage = nil;
static NSObject * sFactoryStartupLock = nil;

BOOL ZGMTRInitializeControllerFactory(void)
{
    static dispatch_once_t onceToken;
    dispatch_once(&onceToken, ^{
        sStorage = [[CHIPToolPersistentStorageDelegate alloc] init];
        sFactoryStartupLock = [[NSObject alloc] init];
    });

    @synchronized (sFactoryStartupLock) {
        @try {
            __auto_type * factory = [ZGMTRControllerFactory sharedInstance];
            if (factory.isRunning) {
                return YES;
            }

            __auto_type * factoryParams = [[ZGMTRControllerFactoryParams alloc] initWithStorage:sStorage];
            if ([factory startup:factoryParams] && factory.isRunning) {
                return YES;
            }
        } @catch (NSException *exception) {
            FlutterMatterLogException(@"defaults.controllerFactory.startup", exception);
        }

        FlutterMatterLog(@"Matter controller factory startup failed");
        return NO;
    }
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
