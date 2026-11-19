/**
 *
 *    Copyright (c) 2022 Project CHIP Authors
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

#pragma mark - Overridable options

/**
 * @define `ZGMTR_NO_AVAILABILITY`
 * Turns off availability annotations, to allow compiling a version of
 * ZGMatter.framework for "local use", not as a system framework.
 */
#ifndef ZGMTR_NO_AVAILABILITY
#define ZGMTR_NO_AVAILABILITY 0
#endif

/**
 * @define `ZGMTR_ENABLE_PROVISIONAL`
 * Makes provisional spec features available for evaluation / testing purposes.
 * The usual API / ABI stability guarantees DO NOT APPLY to provisional features.
 */
#ifndef ZGMTR_ENABLE_PROVISIONAL
#define ZGMTR_ENABLE_PROVISIONAL 0
#endif

/**
 * @define `ZGMTR_ENABLE_UNSTABLE_API`
 * Makes unstbale APIs available for evaluation / testing purposes.
 * The usual API / ABI stability guarantees DO NOT APPLY to unstable APIs.
 */
#ifndef ZGMTR_ENABLE_UNSTABLE_API
#define ZGMTR_ENABLE_UNSTABLE_API 0
#endif

#pragma mark - Attribute macros

#define ZGMTR_EXPORT __attribute__((visibility("default")))

#ifdef __cplusplus
#define ZGMTR_EXTERN extern "C"
#else
#define ZGMTR_EXTERN extern
#endif

#if __has_attribute(__swift_attr__)
#define ZGMTR_SWIFT_DISFAVORED_OVERLOAD __attribute__((__swift_attr__("@_disfavoredOverload")))
#else
#define ZGMTR_SWIFT_DISFAVORED_OVERLOAD
#endif

#pragma mark - Availability / deprecation

// clang-format off
#define _ZGMTR_IMPLICIT_EXPORT                                    \
    _Pragma("clang diagnostic push")                            \
    _Pragma("clang diagnostic ignored \"-Wignored-attributes\"")\
    ZGMTR_EXPORT                                                  \
    _Pragma("clang diagnostic pop")
// clang-format on

#define _ZGMTR_DEPRECATED _ZGMTR_IMPLICIT_EXPORT ZGMTR_SWIFT_DISFAVORED_OVERLOAD
#define _ZGMTR_UNAVAILABLE _ZGMTR_IMPLICIT_EXPORT NS_UNAVAILABLE

// clang-format off
#if ZGMTR_NO_AVAILABILITY
#define ZGMTR_DEPRECATED(...)                     _ZGMTR_DEPRECATED
#define ZGMTR_DEPRECATED_WITH_REPLACEMENT(...)    _ZGMTR_DEPRECATED
#define ZGMTR_AVAILABLE(...)                      _ZGMTR_IMPLICIT_EXPORT
#else
#define ZGMTR_DEPRECATED(...)                     _ZGMTR_DEPRECATED API_DEPRECATED(__VA_ARGS__)
#define ZGMTR_DEPRECATED_WITH_REPLACEMENT(...)    _ZGMTR_DEPRECATED API_DEPRECATED_WITH_REPLACEMENT(__VA_ARGS__)
#define ZGMTR_AVAILABLE(...)                      _ZGMTR_IMPLICIT_EXPORT API_AVAILABLE(__VA_ARGS__)
#endif // ZGMTR_NO_AVAILABILITY
// clang-format on

#define ZGMTR_NEWLY_DEPRECATED(message) _ZGMTR_IMPLICIT_EXPORT
#define ZGMTR_NEWLY_AVAILABLE _ZGMTR_IMPLICIT_EXPORT

#if ZGMTR_ENABLE_PROVISIONAL
#define ZGMTR_PROVISIONALLY_AVAILABLE ZGMTR_NEWLY_AVAILABLE
#else
#define ZGMTR_PROVISIONALLY_AVAILABLE _ZGMTR_UNAVAILABLE
#endif

#if ZGMTR_ENABLE_UNSTABLE_API
#define ZGMTR_UNSTABLE_API ZGMTR_NEWLY_AVAILABLE
#else
#define ZGMTR_UNSTABLE_API _ZGMTR_UNAVAILABLE
#endif

#pragma mark - Types

typedef NSData * ZGMTRTLVBytes;
typedef NSData * ZGMTRCSRDERBytes;
typedef NSData * ZGMTRCertificateDERBytes;
typedef NSData * ZGMTRCertificateTLVBytes;
