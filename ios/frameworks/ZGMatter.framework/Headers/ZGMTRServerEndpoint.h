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
#import <ZGMatter/ZGMTRAccessGrant.h>
#import <ZGMatter/ZGMTRDefines.h>
#import <ZGMatter/ZGMTRDeviceTypeRevision.h>
#import <ZGMatter/ZGMTRServerCluster.h>

NS_ASSUME_NONNULL_BEGIN

/**
 * A representation of an endpoint implemented by an ZGMTRDeviceController.
 *
 * ZGMTRServerEndpoint's API can be accessed from any thread.
 */
NS_SWIFT_SENDABLE
ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6))
@interface ZGMTRServerEndpoint : NSObject

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

/**
 * The provided endpointID must be in the range 1-65535.  The list of device
 * types provided must be nonempty (but may include vendor-specific device
 * types).
 */
- (nullable instancetype)initWithEndpointID:(NSNumber *)endpointID deviceTypes:(NSArray<ZGMTRDeviceTypeRevision *> *)deviceTypes;

/**
 * Add an access grant to the endpoint.  If the same access grant is added
 * multiple times, it will be treated as if it were added once (and removing
 * it once will remove it).
 */
- (void)addAccessGrant:(ZGMTRAccessGrant *)accessGrant;

/**
 * Remove an access grant from the endpoint.
 */
- (void)removeAccessGrant:(ZGMTRAccessGrant *)accessGrant;

/**
 * Add a server cluster to the endpoint.  This can only be done before the
 * endpoint has been added to a controller.
 *
 * The cluster must not have the same cluster ID as another cluster on
 * this endpoint.
 *
 * The cluster must not already be added to another endpoint.
 */
- (BOOL)addServerCluster:(ZGMTRServerCluster *)serverCluster;

@property (atomic, copy, readonly) NSNumber * endpointID;

@property (atomic, copy, readonly) NSArray<ZGMTRDeviceTypeRevision *> * deviceTypes;

/**
 * The list of entities that are allowed to access all clusters on this
 * endpoint.  If more fine-grained access control is desired, access grants
 * should be defined on individual clusters.
 *
 * Defaults to empty list, which means no access granted.
 */
@property (atomic, copy, readonly) NSArray<ZGMTRAccessGrant *> * accessGrants;

/**
 * A list of server clusters supported on this endpoint.  The Descriptor cluster
 * does not need to be included unless a TagList attribute is desired on it or
 * it has a non-empty PartsList, or it needs to have cluster-specific access
 * grants.  If not included, the Descriptor cluster will be generated
 * automatically.
 */
@property (atomic, copy, readonly) NSArray<ZGMTRServerCluster *> * serverClusters;

@end

NS_ASSUME_NONNULL_END
