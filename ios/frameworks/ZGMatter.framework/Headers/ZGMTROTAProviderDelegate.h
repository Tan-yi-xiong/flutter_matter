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
#import <ZGMatter/ZGMTRCluster.h>
#import <ZGMatter/ZGMTRCommandPayloadsObjc.h>
#import <ZGMatter/ZGMTRDefines.h>

@class ZGMTRDeviceController;
@class ZGMTRMetrics;

NS_ASSUME_NONNULL_BEGIN

/**
 * The protocol definition for the ZGMTROTAProviderDelegate
 *
 * All delegate methods will be called on the supplied Delegate Queue.
 *
 * While the selectors on this protocol are marked @optional, in practice an
 * implementation must provide an implementation for one of each pair of
 * selectors (e.g. one of the two handleQueryImageForNodeID selectors must be
 * implemented).  The selector ending in "completion:" will be used if present;
 * otherwise the one ending in "completionHandler:" will be used.
 */
@protocol ZGMTROTAProviderDelegate <NSObject>
@optional
/**
 * Notify the delegate when the query image command is received from some node.
 * The controller identifies the fabric the node is on, and the nodeID
 * identifies the node within that fabric.
 *
 * If completion is passed a non-nil error, that will be converted into
 * an error response to the client.  Otherwise it must have a non-nil data,
 * which will be returned to the client.
 *
 * When providing an OTA image, the imageURI in the
 * ZGMTROTASoftwareUpdateProviderClusterQueryImageResponseParams must be set to
 * the file designator of the image.  The completion will create the right BDX
 * URI from that file designator, as needed.  The file designator returned here
 * via imageURI will be the same as the file designator passed to
 * handleBDXTransferSessionBeginForNodeID:controller:fileDesignator:offset:completion:.
 */
- (void)handleQueryImageForNodeID:(NSNumber *)nodeID
                       controller:(ZGMTRDeviceController *)controller
                           params:(ZGMTROTASoftwareUpdateProviderClusterQueryImageParams *)params
                       completion:(void (^)(ZGMTROTASoftwareUpdateProviderClusterQueryImageResponseParams * _Nullable data,
                                      NSError * _Nullable error))completion
    ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));

- (void)handleQueryImageForNodeID:(NSNumber *)nodeID
                       controller:(ZGMTRDeviceController *)controller
                           params:(ZGMTROtaSoftwareUpdateProviderClusterQueryImageParams *)params
                completionHandler:(void (^)(ZGMTROtaSoftwareUpdateProviderClusterQueryImageResponseParams * _Nullable data,
                                      NSError * _Nullable error))completionHandler
    ZGMTR_DEPRECATED_WITH_REPLACEMENT("handleQueryImageForNodeID:controller:params:completion:", ios(16.1, 16.4), macos(13.0, 13.3),
        watchos(9.1, 9.4), tvos(16.1, 16.4));

/**
 * Notify the delegate when the apply update request command is received from
 * some node.  The controller identifies the fabric the node is on, and the
 * nodeID identifies the node within that fabric.
 *
 * If completion is passed a non-nil error, that will be converted into
 * an error response to the client.  Otherwise it must have a non-nil data,
 * which will be returned to the client.
 */
- (void)handleApplyUpdateRequestForNodeID:(NSNumber *)nodeID
                               controller:(ZGMTRDeviceController *)controller
                                   params:(ZGMTROTASoftwareUpdateProviderClusterApplyUpdateRequestParams *)params
                               completion:(void (^)(ZGMTROTASoftwareUpdateProviderClusterApplyUpdateResponseParams * _Nullable data,
                                              NSError * _Nullable error))completion
    ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));

- (void)handleApplyUpdateRequestForNodeID:(NSNumber *)nodeID
                               controller:(ZGMTRDeviceController *)controller
                                   params:(ZGMTROtaSoftwareUpdateProviderClusterApplyUpdateRequestParams *)params
                        completionHandler:(void (^)(ZGMTROtaSoftwareUpdateProviderClusterApplyUpdateResponseParams * _Nullable data,
                                              NSError * _Nullable error))completionHandler
    ZGMTR_DEPRECATED_WITH_REPLACEMENT("handleApplyUpdateRequestForNodeID:controller:params:completion:", ios(16.1, 16.4),
        macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));

/**
 * Notify the delegate when the notify update applied command is received from
 * some node.  The controller identifies the fabric the node is on, and the
 * nodeID identifies the node within that fabric.
 *
 * If completion is passed a non-nil error, that will be converted into
 * an error response to the client.  Otherwise a success response will be sent.
 */
- (void)handleNotifyUpdateAppliedForNodeID:(NSNumber *)nodeID
                                controller:(ZGMTRDeviceController *)controller
                                    params:(ZGMTROTASoftwareUpdateProviderClusterNotifyUpdateAppliedParams *)params
                                completion:(ZGMTRStatusCompletion)completion
    ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));

- (void)handleNotifyUpdateAppliedForNodeID:(NSNumber *)nodeID
                                controller:(ZGMTRDeviceController *)controller
                                    params:(ZGMTROtaSoftwareUpdateProviderClusterNotifyUpdateAppliedParams *)params
                         completionHandler:(StatusCompletion)completionHandler
    ZGMTR_DEPRECATED_WITH_REPLACEMENT("handleNotifyUpdateAppliedForNodeID:controller:params:completion:", ios(16.1, 16.4),
        macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));

/**
 * Notify the delegate when a BDX Session starts for some node.  The controller
 * identifies the fabric the node is on, and the nodeID identifies the node
 * within that fabric.
 */
- (void)handleBDXTransferSessionBeginForNodeID:(NSNumber *)nodeID
                                    controller:(ZGMTRDeviceController *)controller
                                fileDesignator:(NSString *)fileDesignator
                                        offset:(NSNumber *)offset
                                    completion:(ZGMTRStatusCompletion)completion
    ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));

- (void)handleBDXTransferSessionBeginForNodeID:(NSNumber *)nodeID
                                    controller:(ZGMTRDeviceController *)controller
                                fileDesignator:(NSString *)fileDesignator
                                        offset:(NSNumber *)offset
                             completionHandler:(StatusCompletion)completionHandler
    ZGMTR_DEPRECATED_WITH_REPLACEMENT("handleBDXTransferSessionBeginForNodeID:controller:fileDesignator:offset:completion:",
        ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));

/**
 * Notify the delegate when a BDX Session ends for some node.  The controller
 * identifies the fabric the node is on, and the nodeID identifies the node
 * within that fabric.
 */
- (void)handleBDXTransferSessionEndForNodeID:(NSNumber *)nodeID
                                  controller:(ZGMTRDeviceController *)controller
                                     metrics:(ZGMTRMetrics *)metrics
                                       error:(NSError * _Nullable)error
    ZGMTR_AVAILABLE(ios(26.1), macos(26.1), watchos(26.1), tvos(26.1));

- (void)handleBDXTransferSessionEndForNodeID:(NSNumber *)nodeID
                                  controller:(ZGMTRDeviceController *)controller
                                       error:(NSError * _Nullable)error
    ZGMTR_DEPRECATED_WITH_REPLACEMENT("handleBDXTransferSessionEndForNodeID:controller:metrics:error:", ios(16.1, 26.1),
        macos(13.0, 26.1), watchos(9.1, 26.1), tvos(16.1, 26.1));

/**
 * Notify the delegate when a BDX Query message has been received for some node.
 * The controller identifies the fabric the node is on, and the nodeID
 * identifies the node within that fabric.
 *
 * The data passed to the completion must be of size blockSize, unless it's the
 * last block of data.  In that case, it may be smaller than blockSize, and
 * isEOF must be set to YES.
 */
- (void)handleBDXQueryForNodeID:(NSNumber *)nodeID
                     controller:(ZGMTRDeviceController *)controller
                      blockSize:(NSNumber *)blockSize
                     blockIndex:(NSNumber *)blockIndex
                    bytesToSkip:(NSNumber *)bytesToSkip
                     completion:(void (^)(NSData * _Nullable data, BOOL isEOF))completion
    ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));

- (void)handleBDXQueryForNodeID:(NSNumber *)nodeID
                     controller:(ZGMTRDeviceController *)controller
                      blockSize:(NSNumber *)blockSize
                     blockIndex:(NSNumber *)blockIndex
                    bytesToSkip:(NSNumber *)bytesToSkip
              completionHandler:(void (^)(NSData * _Nullable data, BOOL isEOF))completionHandler
    ZGMTR_DEPRECATED_WITH_REPLACEMENT("handleBDXQueryForNodeID:controller:blockSize:blockIndex:bytesToSkip:completion:",
        ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));

@end

NS_ASSUME_NONNULL_END
