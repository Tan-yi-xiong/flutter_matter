/**
 *    Copyright (c) 2024 Project CHIP Authors
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
#import <ZGMatter/ZGMTRDefines.h>

@class ZGMTRDescriptorClusterDeviceTypeStruct;
@class ZGMTRDeviceType;

NS_ASSUME_NONNULL_BEGIN

/**
 * A representation of a "device type revision" in the sense used in the ZGMatter
 * specification.  This has an identifier and a version number.
 */
NS_SWIFT_SENDABLE
ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6))
@interface ZGMTRDeviceTypeRevision : NSObject <NSCopying> /* <NSSecureCoding> (see below) */

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

/**
 * The provided deviceTypeID must be in the range 0xVVVV0000-0xVVVVBFFF, where
 * VVVV is the vendor identifier (0 for standard device types).
 *
 * The provided deviceTypeRevision must be in the range 1-65535.
 */
- (nullable instancetype)initWithDeviceTypeID:(NSNumber *)deviceTypeID revision:(NSNumber *)revision;

/**
 * Initializes the receiver based on the values in the specified struct.
 */
- (nullable instancetype)initWithDeviceTypeStruct:(ZGMTRDescriptorClusterDeviceTypeStruct *)deviceTypeStruct ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));

@property (nonatomic, copy, readonly) NSNumber * deviceTypeID;
@property (nonatomic, copy, readonly) NSNumber * deviceTypeRevision;

/**
 * Returns the ZGMTRDeviceType corresponding to deviceTypeID,
 * or nil if deviceTypeID does not represent a known device type.
 */
@property (nonatomic, copy, readonly, nullable) ZGMTRDeviceType * typeInformation ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));

@end

ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4))
@interface ZGMTRDeviceTypeRevision () <NSSecureCoding>
@end

NS_ASSUME_NONNULL_END
