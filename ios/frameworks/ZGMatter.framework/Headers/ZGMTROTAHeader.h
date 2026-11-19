/**
 *
 *    Copyright (c) 2022-2023 Project CHIP Authors
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

#import <ZGMatter/ZGMTRDefines.h>

/**
 * A representation of an OTA image header as defined in the ZGMatter
 * specification's "Over-the-Air (OTA) Software Update File Format" section.
 */

NS_ASSUME_NONNULL_BEGIN

typedef NS_ENUM(NSUInteger, ZGMTROTAImageDigestType) {
    ZGMTROTAImageDigestTypeSha256 = 1,
    ZGMTROTAImageDigestTypeSha256_128,
    ZGMTROTAImageDigestTypeSha256_120,
    ZGMTROTAImageDigestTypeSha256_96,
    ZGMTROTAImageDigestTypeSha256_64,
    ZGMTROTAImageDigestTypeSha256_32,
    ZGMTROTAImageDigestTypeSha384,
    ZGMTROTAImageDigestTypeSha512,
    ZGMTROTAImageDigestTypeSha3_224,
    ZGMTROTAImageDigestTypeSha3_256,
    ZGMTROTAImageDigestTypeSha3_384,
    ZGMTROTAImageDigestTypeSha3_512,
} ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1))
@interface ZGMTROTAHeader : NSObject

/**
 * Initialize the ZGMTROTAHeader with the given ZGMatter OTA software image data (as defined in the
 * "Over-the-Air (OTA) Software Update File Format" section of the ZGMatter specification).  The
 * provided data is expected to point to a large enough initial chunk of an OTA software image that
 * it includes the entire header (e.g. the entire image).
 *
 * If the passed-in data is too small and does not contain the entire OTA image header, initWithData
 * will return nil and the caller should try creating a new ZGMTROTAHeader object and initializing it
 * with a larger chunk of the image.
 */
- (instancetype)initWithData:(NSData *)data ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));

/**
 * The identifier of the vendor whose product this image is meant for.
 *
 * This field can be compared to the vendor id received in the Query Image
 * command to determine whether an image matches.
 *
 * This field may be 0, in which case the image might apply to products from
 * more than one vendor.  If it's nonzero, it must match the vendor id in Query
 * Image for this image to be considered.
 */
@property (nonatomic, copy) NSNumber * vendorID;

/**
 * The identifier of the specific product the image is meant for.  May be 0, if
 * the image might apply to more than one product.  This is allowed, but not
 * required, to be matched against the product id received in Query Image.
 */
@property (nonatomic, copy) NSNumber * productID;

/**
 * The size of the actual image payload, which follows the header in the OTA
 * file.
 */
@property (nonatomic, copy) NSNumber * payloadSize;

/**
 * The version of the software contained in this image.  This is the version the
 * OTA requestor will be updated to if this image is installed.  This can be
 * used to determine whether this image is newer than what the requestor is
 * currently running, by comparing it to the SoftwareVersion in the Query Image
 * command.
 */
@property (nonatomic, copy) NSNumber * softwareVersion;

/**
 * Human-readable version of softwareVersion.  This must not be used for
 * deciding which versions are newer or older; use softwareVersion for that.
 */
@property (nonatomic, copy) NSString * softwareVersionString;

/**
 * If not nil a URL pointing to release notes for the software update
 * represented by the image.
 */
@property (nonatomic, copy, nullable) NSString * releaseNotesURL;

/**
 * A digest of the payload that follows the header.  Can be used to verify that
 * the payload is not truncated or corrupted.
 */
@property (nonatomic, copy) NSData * imageDigest;

/**
 * The specific algorithm that was used to compute imageDigest.
 */
@property (nonatomic, assign) ZGMTROTAImageDigestType imageDigestType;

/**
 * If not nil, specifies the smallest software version that this update can be
 * applied on top of.  In that case, this value must be compared to the
 * SoftwareVersion in the QueryImage command to check whether this image is
 * valid for the OTA requestor.
 */
@property (nonatomic, copy, nullable) NSNumber * minApplicableVersion;

/**
 * If not nil, specifies the largest software version that this update can be
 * applied on top of.  In that case, this value must be compared to the
 * SoftwareVersion in the QueryImage command to check whether this image is
 * valid for the OTA requestor.
 */
@property (nonatomic, copy, nullable) NSNumber * maxApplicableVersion;

@end

ZGMTR_DEPRECATED("Please use ZGMTROTAHeader's initWithData:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
@interface ZGMTROTAHeaderParser : NSObject
+ (nullable ZGMTROTAHeader *)headerFromData:(NSData *)data error:(NSError * __autoreleasing *)error;
@end

NS_ASSUME_NONNULL_END
