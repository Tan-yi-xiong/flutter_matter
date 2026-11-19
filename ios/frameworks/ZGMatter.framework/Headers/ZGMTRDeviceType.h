/*
 *    Copyright (c) 2024 Project CHIP Authors
 *    All rights reserved.
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

#pragma once

#import <Foundation/Foundation.h>

#import <ZGMatter/ZGMTRDefines.h>

NS_ASSUME_NONNULL_BEGIN

/**
 * Meta-data about a device type defined in the ZGMatter specification.
 */
ZGMTR_AVAILABLE(ios(18.2), macos(15.2), watchos(11.2), tvos(18.2))
@interface ZGMTRDeviceType : NSObject /* <NSCopying> (see below) */

/**
 * Returns an ZGMTRDeviceType for the given ID, if the ID is known.  Returns nil
 * for unknown IDs.
 */
+ (nullable ZGMTRDeviceType *)deviceTypeForID:(NSNumber *)deviceTypeID;

/**
 * The identifier of the device type (32-bit unsigned integer).
 */
@property (nonatomic, readonly, copy) NSNumber * id;

/**
 * Returns the name of the device type.
 */
@property (nonatomic, readonly, retain) NSString * name;

/**
 * Returns whether this is a utility device type.
 */
@property (nonatomic, readonly, assign) BOOL isUtility;

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end

ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4))
@interface ZGMTRDeviceType () <NSCopying>
@end

NS_ASSUME_NONNULL_END
