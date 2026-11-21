/**
 *
 *    Copyright (c) 2020-2023 Project CHIP Authors
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
#import <ZGMatter/ZGMTRCertificates.h>

#import <ZGMatter/ZGMTRDefines.h>

NS_ASSUME_NONNULL_BEGIN

@class ZGMTRDeviceController;

ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1))
@interface ZGMTRDeviceAttestationDeviceInfo : NSObject

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

/**
 * The vendor ID from the Device Attestation Certificate. May be nil only if
 * attestation verification failed.
 */
@property (nonatomic, readonly, nullable) NSNumber * vendorID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));

/**
 * The product ID from the Device Attestation Certificate. May be nil only if
 * attestation verification failed.
 */
@property (nonatomic, readonly, nullable) NSNumber * productID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));

/**
 * The vendor ID value from the device's Basic Information cluster that was used
 * for device attestation.  If attestation succeeds, this must match the vendor
 * ID from the certification declaration.
 */
@property (nonatomic, readonly) NSNumber * basicInformationVendorID ZGMTR_AVAILABLE(ios(16.6), macos(13.5), watchos(9.6), tvos(16.6));

/**
 * The product ID value from the device's Basic Information cluster that was
 * used for device attestation.  If attestation succeeds, this must match one of
 * the product IDs from the certification declaration.
 */
@property (nonatomic, readonly) NSNumber * basicInformationProductID ZGMTR_AVAILABLE(ios(16.6), macos(13.5), watchos(9.6), tvos(16.6));

@property (nonatomic, readonly) ZGMTRCertificateDERBytes dacCertificate;
@property (nonatomic, readonly) ZGMTRCertificateDERBytes dacPAICertificate;
@property (nonatomic, readonly, nullable) NSData * certificateDeclaration ZGMTR_DEPRECATED_WITH_REPLACEMENT("certificationDeclaration", ios(16.1, 26.1), macos(13.0, 26.1), watchos(9.1, 26.1), tvos(16.1, 26.1));

/**
 * The attestation challenge from the secure session.
 */
@property (nonatomic, copy, readonly) NSData * attestationChallenge ZGMTR_AVAILABLE(ios(26.1), macos(26.1), watchos(26.1), tvos(26.1));

/**
 * The attestation nonce from the AttestationRequest command.
 */
@property (nonatomic, copy, readonly) NSData * attestationNonce ZGMTR_AVAILABLE(ios(26.1), macos(26.1), watchos(26.1), tvos(26.1));

/**
 * The TLV-encoded attestation_elements_message that was used to find the
 * certificationDeclaration (possibly unsuccessfully).
 */
@property (nonatomic, copy, readonly) ZGMTRTLVBytes elementsTLV ZGMTR_AVAILABLE(ios(26.1), macos(26.1), watchos(26.1), tvos(26.1));

/**
 * The certification declaration of the device, if available.  This is a DER-encoded string
 * representing a CMS-formatted certification declaration.  May be nil only if
 * attestation verification failed.
 */
@property (nonatomic, copy, readonly, nullable) NSData * certificationDeclaration ZGMTR_AVAILABLE(ios(26.1), macos(26.1), watchos(26.1), tvos(26.1));

/**
 * A signature, using the device attestation private key of the device that sent
 * the attestation information, over the concatenation of elementsTLV and
 * attestationChallenge.
 */
@property (nonatomic, copy, readonly) NSData * elementsSignature ZGMTR_AVAILABLE(ios(26.1), macos(26.1), watchos(26.1), tvos(26.1));

@end

/**
 * The protocol definition for the ZGMTRDeviceAttestationDelegate.
 */
@protocol ZGMTRDeviceAttestationDelegate <NSObject>
@optional
/**
 * Only one of the following delegate callbacks should be implemented.
 *
 * If -deviceAttestationFailedForController:opaqueDeviceHandle:error: is implemented, then it will
 * be called when device attestation fails, and the client can decide to continue or stop the
 * commissioning.
 *
 * If -deviceAttestationCompletedForController:opaqueDeviceHandle:attestationDeviceInfo:error: is
 * implemented, then it will always be called when device attestation completes.
 */

/**
 * Notify the delegate when device attestation completed with device info for additional verification. If
 * this callback is implemented, continueCommissioningDevice on ZGMTRDeviceController is expected
 * to be called if commisioning should continue.
 *
 * This allows the delegate to stop commissioning after examining the device info (DAC, PAI, CD).
 *
 * @param controller Controller corresponding to the commissioning process
 * @param opaqueDeviceHandle Handle of device being commissioned
 * @param attestationDeviceInfo Attestation information for the device
 * @param error NSError representing the error code on attestation failure. Nil if success.
 */
- (void)deviceAttestationCompletedForController:(ZGMTRDeviceController *)controller
                             opaqueDeviceHandle:(void *)opaqueDeviceHandle
                          attestationDeviceInfo:(ZGMTRDeviceAttestationDeviceInfo *)attestationDeviceInfo
                                          error:(NSError * _Nullable)error
    ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));

/**
 * Notify the delegate when device attestation fails.  If this callback is implemented,
 * continueCommissioningDevice on ZGMTRDeviceController is expected to be called if commisioning
 * should continue.
 *
 * @param controller Controller corresponding to the commissioning process
 * @param opaqueDeviceHandle Handle of device being commissioned
 * @param error NSError representing the error code for the failure
 */
- (void)deviceAttestationFailedForController:(ZGMTRDeviceController *)controller
                          opaqueDeviceHandle:(void *)opaqueDeviceHandle
                                       error:(NSError * _Nonnull)error
    ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));

- (void)deviceAttestation:(ZGMTRDeviceController *)controller
       completedForDevice:(void *)device
    attestationDeviceInfo:(ZGMTRDeviceAttestationDeviceInfo *)attestationDeviceInfo
                    error:(NSError * _Nullable)error
    ZGMTR_DEPRECATED("Please implement deviceAttestationCompletedForController:opaqueDeviceHandle:attestationDeviceInfo:error:",
        ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));

- (void)deviceAttestation:(ZGMTRDeviceController *)controller
          failedForDevice:(void *)device
                    error:(NSError * _Nonnull)error
    ZGMTR_DEPRECATED("Please implement deviceAttestationFailedForController:opaqueDeviceHandle:error:", ios(16.1, 16.4),
        macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));

@end

NS_ASSUME_NONNULL_END
