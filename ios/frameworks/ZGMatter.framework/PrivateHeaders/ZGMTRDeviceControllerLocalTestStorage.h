//
/**
 *    Copyright (c) 2023 Project CHIP Authors
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

#import <Foundation/Foundation.h>
#import <ZGMatter/ZGMatter.h>

NS_ASSUME_NONNULL_BEGIN

ZGMTR_EXTERN ZGMTR_EXPORT @interface ZGMTRDeviceControllerLocalTestStorage : NSObject<ZGMTRDeviceControllerStorageDelegate>

// Setting this variable only affects subsequent ZGMTRDeviceController initializations
@property (class, nonatomic, assign) BOOL localTestStorageEnabled;

// This storage persists items to NSUserDefaults for ZGMTRStorageSharingTypeNotShared data. Items with other sharing types will be droppped, or stored/fetched with the "passthrough storage" if one is specified.
- (instancetype)initWithPassThroughStorage:(id<ZGMTRDeviceControllerStorageDelegate> _Nullable)passThroughStorage;

@end

NS_ASSUME_NONNULL_END
