/**
 *    Copyright (c) 2022-2025 Project CHIP Authors
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
#import <ZGMatter/ZGMTRBaseDevice.h>
#import <ZGMatter/ZGMTRDefines.h>

NS_ASSUME_NONNULL_BEGIN

@protocol ZGMTRDeviceAttestationDelegate;

/**
 * Information that can be provided to commissionWithNodeID to commision devices.
 */
ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1))
@interface ZGMTRCommissioningParameters : NSObject

/**
 * The nonce to use when requesting a CSR for the node's operational
 * certificate.
 *
 * If nil, a random nonce will be generated automatically.
 *
 * If not nil, must be 32 bytes of data.
 */
@property (nonatomic, copy, nullable) NSData * csrNonce ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));

/**
 * The nonce to use when requesting attestation information from the device.
 *
 * If nil, a random nonce will be generated automatically.
 *
 * If not nil, must be 32 bytes of data.
 */
@property (nonatomic, copy, nullable) NSData * attestationNonce;

/**
 * The Wi-Fi SSID, if available.
 */
@property (nonatomic, copy, nullable) NSData * wifiSSID;

/**
 * The Wi-Fi Credentials.  Allowed to be nil or 0-length data for an open
 * network, as long as wifiSSID is not nil.
 */
@property (nonatomic, copy, nullable) NSData * wifiCredentials;

/**
 *  The Thread operational dataset, if available.
 */
@property (nonatomic, copy, nullable) NSData * threadOperationalDataset;

/**
 * An optional delegate that can be notified upon completion of device
 * attestation.  See documentation for ZGMTRDeviceAttestationDelegate for
 * details.
 *
 * The delegate methods will be invoked on an arbitrary thread.
 */
@property (nonatomic, strong, nullable) id<ZGMTRDeviceAttestationDelegate> deviceAttestationDelegate;

/**
 * The timeout, in seconds, to set for the fail-safe when calling into the
 * deviceAttestationDelegate and waiting for it to respond.
 *
 * If nil, the fail-safe will not be extended before calling into the
 * deviceAttestationDelegate.
 */
@property (nonatomic, copy, nullable) NSNumber * failSafeTimeout ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));

/**
 * Only perform the PASE steps of commissioning.
 * If set to YES, commissioning will be completed by another admin on the network.
 *
 * Defaults to NO.
 */
@property (nonatomic, assign) BOOL skipCommissioningComplete ZGMTR_AVAILABLE(ios(17.0), macos(14.0), watchos(10.0), tvos(17.0));

/**
 * The country code to provide to the device during commissioning.
 *
 * If not nil, this must be a 2-character ISO 3166-1 country code, which the
 * device can use to decide on things like radio communications bands.
 */
@property (nonatomic, copy, nullable) NSString * countryCode ZGMTR_AVAILABLE(ios(17.0), macos(14.0), watchos(10.0), tvos(17.0));

/**
 * Read device type information from all endpoints during commissioning.
 * Defaults to NO.
 */
@property (nonatomic, assign) BOOL readEndpointInformation ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));

/**
 * A bitmask of the user’s responses to the presented terms and conditions.
 * Each bit corresponds to a term’s acceptance (1) or non-acceptance (0) at the matching index.
 */
@property (nonatomic, copy, nullable) NSNumber * acceptedTermsAndConditions ZGMTR_PROVISIONALLY_AVAILABLE;

/**
 * The version of the terms and conditions that the user has accepted.
 */
@property (nonatomic, copy, nullable) NSNumber * acceptedTermsAndConditionsVersion ZGMTR_PROVISIONALLY_AVAILABLE;

/**
 * List of attribute paths to read from the commissionee (in addition to
 * whatever attributes are already read to handle readEndpointInformation being
 * YES, or to handle other commissioning tasks).
 *
 * The FeatureMap attribute of all Network Commissioning clusters on the commissionee
 * will always be read and does not need to be included in this list.
 */
@property (nonatomic, copy, nullable) NSArray<ZGMTRAttributeRequestPath *> * extraAttributesToRead ZGMTR_AVAILABLE(ios(26.2), macos(26.2), watchos(26.2), tvos(26.2));

/**
 * Whether to force a network scan before requesting Wi-Fi credentials.
 * The default is NO.
 *
 * Even if this value is NO a scan may still be performed.
 *
 * This value will be ignored if Wi-Fi credentials are provided or not needed.
 *
 * NOTE: Not all APIs that take ZGMTRCommissioningParameters pay attention to this
 * flag.
 */
@property (nonatomic, assign) BOOL forceWiFiScan ZGMTR_AVAILABLE(ios(26.2), macos(26.2), watchos(26.2), tvos(26.2));

/**
 * Whether to force a network scan before requesting Thread credentials.
 * The default is NO.
 *
 * Even if this value is NO a scan may still be performed.
 *
 * This value will be ignored if a Thread operational dataset is provided or not
 * needed.
 *
 * NOTE: Not all APIs that take ZGMTRCommissioningParameters pay attention to this
 * flag.
 */
@property (nonatomic, assign) BOOL forceThreadScan ZGMTR_AVAILABLE(ios(26.2), macos(26.2), watchos(26.2), tvos(26.2));

@end

@interface ZGMTRCommissioningParameters (Deprecated)

@property (nonatomic, copy, nullable) NSData * CSRNonce ZGMTR_DEPRECATED_WITH_REPLACEMENT(
    "csrNonce", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));

@property (nonatomic, copy, nullable) NSNumber * failSafeExpiryTimeoutSecs ZGMTR_DEPRECATED_WITH_REPLACEMENT(
    "failSafeTimeout", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));

@end

NS_ASSUME_NONNULL_END
