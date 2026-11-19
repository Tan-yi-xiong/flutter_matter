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

#import <Foundation/Foundation.h>

#import <ZGMatter/ZGMTRDefines.h>

NS_ASSUME_NONNULL_BEGIN

ZGMTR_EXTERN NSErrorDomain const ZGMTRErrorDomain ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));
ZGMTR_EXTERN NSErrorDomain const ZGMTRInteractionErrorDomain ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

/**
 * ZGMTRErrorDomain contains errors caused by data processing the framework
 * itself is performing.  These can be caused by invalid values provided to a
 * framework API, failure to decode an incoming message, and so forth.
 *
 * This error domain also contains errors that are communicated via success
 * responses from a server but mapped to an error on the client.
 *
 * Errors reported by the server side of a ZGMatter interaction via the normal
 * ZGMatter error-reporting mechanisms use ZGMTRInteractionErrorDomain instead.
 */
typedef NS_ERROR_ENUM(ZGMTRErrorDomain, ZGMTRErrorCode){
    /**
     * ZGMTRErrorCodeGeneralError represents a generic ZGMatter error with no
     * further categorization.
     *
     * The userInfo will have a key named @"errorCode" whose value will be an
     * integer representing the underlying ZGMatter error code.  These integer
     * values should not be assumed to be stable across releases, but may be
     * useful in logging and debugging.
     */
    ZGMTRErrorCodeGeneralError         = 1,
    ZGMTRErrorCodeInvalidStringLength  = 2,
    ZGMTRErrorCodeInvalidIntegerValue  = 3,
    ZGMTRErrorCodeInvalidArgument      = 4,
    ZGMTRErrorCodeInvalidMessageLength = 5,
    ZGMTRErrorCodeInvalidState         = 6,
    ZGMTRErrorCodeWrongAddressType     = 7,
    ZGMTRErrorCodeIntegrityCheckFailed = 8,
    ZGMTRErrorCodeTimeout              = 9,
    ZGMTRErrorCodeBufferTooSmall       = 10,

    /**
     * ZGMTRErrorCodeFabricExists is returned when trying to commission a device
     * into a fabric when it's already part of that fabric.
     */
    ZGMTRErrorCodeFabricExists = 11,

    /**
     * ZGMTRErrorCodeUnknownSchema means the schema for the given cluster/attribute,
     * cluster/event, or cluster/command combination is not known.
     */
    ZGMTRErrorCodeUnknownSchema ZGMTR_AVAILABLE(ios(17.0), macos(14.0), watchos(10.0), tvos(17.0)) = 12,

    /**
     * ZGMTRErrorCodeSchemaMismatch means that provided data did not match the
     * expected schema.
     */
    ZGMTRErrorCodeSchemaMismatch ZGMTR_AVAILABLE(ios(17.0), macos(14.0), watchos(10.0), tvos(17.0)) = 13,

    /**
     * ZGMTRErrorCodeTLVDecodeFailed means that the TLV being decoded was malformed in
     * some way.  This can include things like lengths running past the end of
     * the buffer, strings that are not actually UTF-8, and various other
     * TLV-level failures.
     */
    ZGMTRErrorCodeTLVDecodeFailed ZGMTR_AVAILABLE(ios(17.0), macos(14.0), watchos(10.0), tvos(17.0)) = 14,

    /**
     * ZGMTRErrorCodeDNSSDUnauthorized means that the application is not
     * authorized to perform DNS_SD lookups.  This typically means missing
     * entries for "_matter._tcp" (for operational lookup) and "_matterc._udp"
     * (for commissionable lookup) under the NSBonjourServices key in the
     * application's Info.plist.
     */
    ZGMTRErrorCodeDNSSDUnauthorized ZGMTR_AVAILABLE(ios(17.2), macos(14.2), watchos(10.2), tvos(17.2)) = 15,

    /**
     * The operation was cancelled.
     */
    ZGMTRErrorCodeCancelled ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6)) = 16,

    /**
     * Access to some resource was denied.
     */
    ZGMTRErrorCodeAccessDenied ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = 17,

    /**
     * A request was made to some entity, and that entity cannot handle the
     * request right now, but might be able to at a different point in time.
     */
    ZGMTRErrorCodeBusy ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = 18,

    /**
     * Something was requested that could not be located.
     */
    ZGMTRErrorCodeNotFound ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = 19,
} ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

#define ZGMTRMaxErrorCode ZGMTRErrorCodeNotFound

/**
 * ZGMTRInteractionErrorDomain contains errors that represent a ZGMatter
 * StatusIB error.  These represent errors reported by the other side of a
 * ZGMatter interaction.
 *
 * When the code is ZGMTRInteractionErrorCodeFailure the userInfo may have a
 * key named @"clusterStatus" whose value is the cluster-specific status that
 * was reported.  This key will be absent if there was no cluster-specific
 * status.
 */
typedef NS_ERROR_ENUM(ZGMTRInteractionErrorDomain, ZGMTRInteractionErrorCode){
    // These values come from the general status code table in the ZGMatter
    // Interaction Model specification.
    ZGMTRInteractionErrorCodeFailure                                                                            = 0x01,
    ZGMTRInteractionErrorCodeInvalidSubscription                                                                = 0x7d,
    ZGMTRInteractionErrorCodeUnsupportedAccess                                                                  = 0x7e,
    ZGMTRInteractionErrorCodeUnsupportedEndpoint                                                                = 0x7f,
    ZGMTRInteractionErrorCodeInvalidAction                                                                      = 0x80,
    ZGMTRInteractionErrorCodeUnsupportedCommand                                                                 = 0x81,
    ZGMTRInteractionErrorCodeInvalidCommand                                                                     = 0x85,
    ZGMTRInteractionErrorCodeUnsupportedAttribute                                                               = 0x86,
    ZGMTRInteractionErrorCodeConstraintError                                                                    = 0x87,
    ZGMTRInteractionErrorCodeUnsupportedWrite                                                                   = 0x88,
    ZGMTRInteractionErrorCodeResourceExhausted                                                                  = 0x89,
    ZGMTRInteractionErrorCodeNotFound                                                                           = 0x8b,
    ZGMTRInteractionErrorCodeUnreportableAttribute                                                              = 0x8c,
    ZGMTRInteractionErrorCodeInvalidDataType                                                                    = 0x8d,
    ZGMTRInteractionErrorCodeUnsupportedRead                                                                    = 0x8f,
    ZGMTRInteractionErrorCodeDataVersionMismatch                                                                = 0x92,
    ZGMTRInteractionErrorCodeTimeout                                                                            = 0x94,
    ZGMTRInteractionErrorCodeBusy                                                                               = 0x9c,
    ZGMTRInteractionErrorCodeAccessRestricted ZGMTR_AVAILABLE(ios(26.0), macos(26.0), watchos(26.0), tvos(26.0))  = 0x9d,
    ZGMTRInteractionErrorCodeUnsupportedCluster                                                                 = 0xc3,
    ZGMTRInteractionErrorCodeNoUpstreamSubscription                                                             = 0xc5,
    ZGMTRInteractionErrorCodeNeedsTimedInteraction                                                              = 0xc6,
    ZGMTRInteractionErrorCodeUnsupportedEvent                                                                   = 0xc7,
    ZGMTRInteractionErrorCodePathsExhausted                                                                     = 0xc8,
    ZGMTRInteractionErrorCodeTimedRequestMismatch                                                               = 0xc9,
    ZGMTRInteractionErrorCodeFailsafeRequired                                                                   = 0xca,
    ZGMTRInteractionErrorCodeInvalidInState ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6))    = 0xcb,
    ZGMTRInteractionErrorCodeNoCommandResponse ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6)) = 0xcc,
    ZGMTRInteractionErrorCodeDynamicConstraintError ZGMTR_PROVISIONALLY_AVAILABLE                                 = 0xcf,
    ZGMTRInteractionErrorCodeInvalidTransportType ZGMTR_PROVISIONALLY_AVAILABLE                                   = 0xd1,
} ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

NS_ASSUME_NONNULL_END
