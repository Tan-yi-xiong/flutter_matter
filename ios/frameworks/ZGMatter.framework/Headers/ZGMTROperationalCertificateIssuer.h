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

#import <Foundation/Foundation.h>

#import <ZGMatter/ZGMTRCSRInfo.h>
#import <ZGMatter/ZGMTRCertificates.h>
#import <ZGMatter/ZGMTRDefines.h>
#import <ZGMatter/ZGMTRDeviceAttestationInfo.h>

NS_ASSUME_NONNULL_BEGIN

@class ZGMTRDeviceController;

/**
 * A representation of the operational certificate chain for a node.
 */
ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4))
@interface ZGMTROperationalCertificateChain : NSObject

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

- (instancetype)initWithOperationalCertificate:(ZGMTRCertificateDERBytes)operationalCertificate
                       intermediateCertificate:(nullable ZGMTRCertificateDERBytes)intermediateCertificate
                               rootCertificate:(ZGMTRCertificateDERBytes)rootCertificate
                                  adminSubject:(nullable NSNumber *)adminSubject;

@property (nonatomic, copy) ZGMTRCertificateDERBytes operationalCertificate;

/**
 * A nil intermediateCertificate means there is no intermediate.
 */
@property (nonatomic, copy, nullable) ZGMTRCertificateDERBytes intermediateCertificate;

@property (nonatomic, copy) ZGMTRCertificateDERBytes rootCertificate;

/**
 * adminSubject is passed to the device as part of the AddNOC command.  A nil
 * adminSubject means the node id of the relevant ZGMTRDeviceController will be
 * used.
 */
@property (nonatomic, copy, nullable) NSNumber * adminSubject;

@end

ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4))
@protocol ZGMTROperationalCertificateIssuer
@required

/**
 * @brief When an ZGMTROperationalCertificateIssuer is set for an
 * ZGMTRDeviceController, it will be used to issue operational certificates as
 * needed during commissioning.
 *
 * Commissioning will pause when
 * issueOperationalCertificateForRequest:attestationInfo:completion: is called,
 * and resume when the completion is invoked with a non-nil
 * ZGMTROperationalCertificateChain.  When the completion is invoked with an error,
 * commissioning will fail.
 *
 * This will be called on the dispatch queue passed as
 * operationalCertificateIssuerQueue in the ZGMTRDeviceControllerFactoryParams.
 *
 * The csrNonce in the provided ZGMTROperationalCSRInfo will be the nonce that was
 * sent in the CSRRequest command, which will be guaranteed, at this point, to
 * match the nonce in the CSRResponse command.
 */
- (void)issueOperationalCertificateForRequest:(ZGMTROperationalCSRInfo *)csrInfo
                              attestationInfo:(ZGMTRDeviceAttestationInfo *)attestationInfo
                                   controller:(ZGMTRDeviceController *)controller
                                   completion:(void (^)(ZGMTROperationalCertificateChain * _Nullable info,
                                                  NSError * _Nullable error))completion;

/**
 * A way for ZGMTROperationalCertificateIssuer to control whether it wants the
 * ZGMatter framework to perform device attestation checks that require trust
 * anchors.  If this returns NO, then productAttestationAuthorityCertificates
 * should be passed in via ZGMTRDeviceControllerFactoryParams, as well as any
 * desired additional certificationDeclarationCertificates.
 *
 * If this returns YES, then all device attestation checks that require some
 * sort of trust anchors are delegated to this ZGMTROperationalCertificateIssuer,
 * which can use the arguments passed to
 * issueOperationalCertificateForRequest:attestationInfo:controller:completion:
 * to perform the checks.
 *
 * Specifically, the following device attestation checks are not performed and
 * must be done by the ZGMTROperationalCertificateIssuer:
 *
 * (1) Make sure the PAA is valid and approved by CSA.
 * (2) VID-scoped PAA check: if the PAA is VID scoped, then its VID must match the DAC VID.
 * (3) cert chain check: verify PAI is signed by PAA, and DAC is signed by PAI.
 * (4) PAA subject key id extraction: the PAA subject key must match the PAA key referenced in the PAI.
 * (5) CD signature check: make sure a valid CSA CD key is used to sign the CD.
 *
 * This will be read on an arbitrary queue and must not block or call any
 * ZGMatter APIs.
 */
@property (nonatomic, readonly) BOOL shouldSkipAttestationCertificateValidation;

@end

ZGMTR_DEPRECATED("ZGMTRNOCChainIssuer is deprecated", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
typedef void (^ZGMTRNOCChainGenerationCompleteHandler)(NSData * operationalCertificate, NSData * intermediateCertificate,
    NSData * rootCertificate, NSData * _Nullable ipk, NSNumber * _Nullable adminSubject, NSError * __autoreleasing * error);

ZGMTR_DEPRECATED(
    "Please use ZGMTROperationalCertificateIssuer", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
@protocol ZGMTRNOCChainIssuer <NSObject>
@required

- (void)onNOCChainGenerationNeeded:(ZGCSRInfo *)csrInfo
                   attestationInfo:(ZGAttestationInfo *)attestationInfo
      onNOCChainGenerationComplete:(ZGMTRNOCChainGenerationCompleteHandler)onNOCChainGenerationComplete;

@end

NS_ASSUME_NONNULL_END
