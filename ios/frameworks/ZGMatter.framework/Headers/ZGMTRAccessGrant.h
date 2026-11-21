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
#import <ZGMatter/ZGMTRBaseClusters.h>
#import <ZGMatter/ZGMTRDefines.h>

NS_ASSUME_NONNULL_BEGIN

/**
 * An access grant, which can be represented as an entry in the ZGMatter Access
 * Control cluster.
 */
NS_SWIFT_SENDABLE
ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6))
@interface ZGMTRAccessGrant : NSObject <NSCopying>

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

/**
 * Grant access at the provided level to a specific node on the fabric.  The
 * provided nodeID must be an operational node identifier.
 */
+ (nullable ZGMTRAccessGrant *)accessGrantForNodeID:(NSNumber *)nodeID privilege:(ZGMTRAccessControlEntryPrivilege)privilege;

/**
 * Grant access to any node on the fabric that has a matching CASE Authenticated
 * Tag in its operational certificate.  The provided caseAuthenticatedTag must
 * be a 32-bit unsigned integer with lower 16 bits not 0, per the ZGMatter
 * specification.
 */
+ (nullable ZGMTRAccessGrant *)accessGrantForCASEAuthenticatedTag:(NSNumber *)caseAuthenticatedTag privilege:(ZGMTRAccessControlEntryPrivilege)privilege;

/**
 * Grant access to any node on the fabric that is communicating with us via
 * group messages sent to the given group.  The provided groupID must be a valid
 * group identifier in the range 1-65535.
 */
+ (nullable ZGMTRAccessGrant *)accessGrantForGroupID:(NSNumber *)groupID privilege:(ZGMTRAccessControlEntryPrivilege)privilege;

/**
 * Grant access to any node on the fabric, as long as it's communicating with us
 * over a unicast authenticated channel.
 */
+ (ZGMTRAccessGrant *)accessGrantForAllNodesWithPrivilege:(ZGMTRAccessControlEntryPrivilege)privilege;

/**
 * The matter access control subject ID that access has been granted for.  Nil
 * when access has been granted for all subjects (e.g. via initForAllNodesWithPrivilege).
 */
@property (nonatomic, copy, readonly, nullable) NSNumber * subjectID;

/**
 * The privilege that has been granted
 */
@property (nonatomic, assign, readonly) ZGMTRAccessControlEntryPrivilege grantedPrivilege;

/**
 * The type of authentication mode the access grant is
 * for. ZGMTRAccessControlEntryAuthModeCASE for unicast messages and
 * ZGMTRAccessControlEntryAuthModeGroup for groupcast ones.
 */
@property (nonatomic, assign, readonly) ZGMTRAccessControlEntryAuthMode authenticationMode;

@end

NS_ASSUME_NONNULL_END
