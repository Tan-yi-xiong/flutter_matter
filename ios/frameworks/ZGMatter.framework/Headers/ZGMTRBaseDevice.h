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

#import <ZGMatter/ZGMTRCluster.h>
#import <ZGMatter/ZGMTRDefines.h>
#import <ZGMatter/ZGMTRDiagnosticLogsType.h>

@class ZGMTRSetupPayload;
@class ZGMTRDeviceController;

NS_ASSUME_NONNULL_BEGIN

/**
 * Handler for read attribute response, write attribute response, invoke command response and reports.
 *
 * Handler will receive either values or error. Either one of the parameters will be nil.
 *
 * @param values  Received values are an NSArray object with response-value element as described below.
 *
 *                A response-value is an NSDictionary object with the following key values:
 *
 *                ZGMTRAttributePathKey : ZGMTRAttributePath object. Included for attribute value.
 *                ZGMTRCommandPathKey : ZGMTRCommandPath object. Included for command response.
 *                ZGMTREventPathKey : ZGMTREventPath object. Included for event value.
 *                ZGMTRErrorKey : NSError object. Included to indicate an error.
 *                ZGMTRDataKey: Data-value NSDictionary object.
 *                              Included when there is data and when there is no error.
 *                              The data-value is described below.
 *                ZGMTREventNumberKey : NSNumber-wrapped uint64_t value. Monotonically increasing, and consecutive event reports
 *                                    should have consecutive numbers unless device reboots, or if events are lost.
 *                                    Only present when both ZGMTREventPathKey and ZGMTRDataKey are present.
 *                ZGMTREventPriorityKey : NSNumber-wrapped ZGMTREventPriority value.
 *                                      Only present when both ZGMTREventPathKey and ZGMTRDataKey are present.
 *                ZGMTREventTimeTypeKey : NSNumber-wrapped ZGMTREventTimeType value.
 *                                      Only present when both ZGMTREventPathKey and ZGMTRDataKey are present.
 *                ZGMTREventSystemUpTimeKey : NSNumber-wrapped NSTimeInterval value.
 *                                          Only present when ZGMTREventTimeTypeKey is ZGMTREventTimeTypeSystemUpTime.
 *                ZGMTREventTimestampDateKey : NSDate object.
 *                                           Only present when ZGMTREventTimeTypeKey is ZGMTREventTimeTypeTimestampDate.
 *                ZGMTREventIsHistoricalKey : NSNumber-wrapped BOOL value.
 *                                          Value is YES if the event is in the far past or not realtime.
 *                                          Only present when ZGMTREventPathKey is present.
 *
 *                Only one of ZGMTREventTimestampDateKey and ZGMTREventSystemUpTimeKey will be present, depending on the value for
 *                ZGMTREventTimeTypeKey.
 *
 *                A data-value is an NSDictionary object with the following key values:
 *
 *                ZGMTRTypeKey : data type. ZGMTRSignedIntegerValueType, ZGMTRUnsignedIntegerValueType, ZGMTRBooleanValueType,
 *                               ZGMTRUTF8StringValueType, ZGMTROctetStringValueType, ZGMTRFloatValueType, ZGMTRDoubleValueType,
 *                               ZGMTRNullValueType, ZGMTRStructureValueType or ZGMTRArrayValueType.
 *
 *                ZGMTRValueKey : data value. Per each data type, data value shall be the following object:
 *
 *                          ZGMTRSignedIntegerValueType: NSNumber object.
 *                          ZGMTRUnsignedIntegerValueType: NSNumber object.
 *                          ZGMTRBooleanValueType: NSNumber object.
 *                          ZGMTRUTF8StringValueType: NSString object.
 *                          ZGMTROctetStringValueType: NSData object.
 *                          ZGMTRFloatValueType: NSNumber object.
 *                          ZGMTRDoubleValueType: NSNumber object.
 *                          ZGMTRNullValueType: "value" key will not be included.
 *                          ZGMTRStructureValueType: structure-value NSArray object.
 *                                                   See below for the definition of structure-value.
 *                          ZGMTRArrayValueType: Array-value NSArray object. See below for the definition of array-value.
 *
 *                A structure-value is an NSArray object with NSDictionary objects as its elements. Each dictionary element will
 *                contain the following key values.
 *
 *                ZGMTRContextTagKey : NSNumber object as context tag.  This can
 *                                   actually be a fully-qualified profile tag,
 *                                   but for compatibility it's using the same
 *                                   key name.  The two types of tags can be
 *                                   told apart by checking whether the value is
 *                                   in the context tag range (0 <= tag <= 0xFF).
 *                ZGMTRDataKey : Data-value NSDictionary object.
 *
 *                An array-value is an NSArray object with NSDictionary objects as its elements. Each dictionary element will
 *                contain the following key values.
 *
 *                ZGMTRDataKey : Data-value NSDictionary object.
 */
typedef void (^ZGMTRDeviceResponseHandler)(NSArray<NSDictionary<NSString *, id> *> * _Nullable values, NSError * _Nullable error);

/**
 * Handler for -subscribeWithQueue: attribute and event reports
 *
 * @param values This array contains ZGMTRAttributeReport objects for attribute reports, and ZGMTREventReport objects for event reports
 */
typedef void (^ZGMTRDeviceReportHandler)(NSArray * values);
typedef void (^ZGMTRDeviceErrorHandler)(NSError * error);

/**
 * Handler for subscribeWithQueue: resubscription scheduling notifications.
 * This will be called when subscription loss is detected.
 *
 * @param error An error indicating the reason the subscription has been lost.
 * @param resubscriptionDelay A delay, in milliseconds, before the next
 *        automatic resubscription will be attempted.
 */
typedef void (^ZGMTRDeviceResubscriptionScheduledHandler)(NSError * error, NSNumber * resubscriptionDelay);

/**
 * Handler for openCommissioningWindowWithSetupPasscode.
 */
ZGMTR_AVAILABLE(ios(16.2), macos(13.1), watchos(9.2), tvos(16.2))
typedef void (^ZGMTRDeviceOpenCommissioningWindowHandler)(ZGMTRSetupPayload * _Nullable payload, NSError * _Nullable error);

ZGMTR_EXTERN NSString * const ZGMTRAttributePathKey ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));
ZGMTR_EXTERN NSString * const ZGMTRCommandPathKey ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));
ZGMTR_EXTERN NSString * const ZGMTREventPathKey ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));
ZGMTR_EXTERN NSString * const ZGMTRDataKey ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));
ZGMTR_EXTERN NSString * const ZGMTRErrorKey ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));
ZGMTR_EXTERN NSString * const ZGMTRTlvValueType ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

ZGMTR_EXTERN NSString * const ZGMTRTypeKey ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));
ZGMTR_EXTERN NSString * const ZGMTRValueKey ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));
ZGMTR_EXTERN NSString * const ZGMTRContextTagKey ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));
ZGMTR_EXTERN NSString * const ZGMTRSignedIntegerValueType ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));
ZGMTR_EXTERN NSString * const ZGMTRUnsignedIntegerValueType ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));
ZGMTR_EXTERN NSString * const ZGMTRBooleanValueType ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));
ZGMTR_EXTERN NSString * const ZGMTRUTF8StringValueType ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));
ZGMTR_EXTERN NSString * const ZGMTROctetStringValueType ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));
ZGMTR_EXTERN NSString * const ZGMTRFloatValueType ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));
ZGMTR_EXTERN NSString * const ZGMTRDoubleValueType ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));
ZGMTR_EXTERN NSString * const ZGMTRNullValueType ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));
ZGMTR_EXTERN NSString * const ZGMTRStructureValueType ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));
ZGMTR_EXTERN NSString * const ZGMTRArrayValueType ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));
ZGMTR_EXTERN NSString * const ZGMTREventNumberKey ZGMTR_AVAILABLE(ios(16.5), macos(13.4), watchos(9.5), tvos(16.5));
ZGMTR_EXTERN NSString * const ZGMTREventPriorityKey ZGMTR_AVAILABLE(ios(16.5), macos(13.4), watchos(9.5), tvos(16.5));
ZGMTR_EXTERN NSString * const ZGMTREventTimeTypeKey ZGMTR_AVAILABLE(ios(16.5), macos(13.4), watchos(9.5), tvos(16.5));
ZGMTR_EXTERN NSString * const ZGMTREventSystemUpTimeKey ZGMTR_AVAILABLE(ios(16.5), macos(13.4), watchos(9.5), tvos(16.5));
ZGMTR_EXTERN NSString * const ZGMTREventTimestampDateKey ZGMTR_AVAILABLE(ios(16.5), macos(13.4), watchos(9.5), tvos(16.5));
ZGMTR_EXTERN NSString * const ZGMTREventIsHistoricalKey ZGMTR_AVAILABLE(ios(17.3), macos(14.3), watchos(10.3), tvos(17.3));

@class ZGMTRClusterStateCacheContainer;
@class ZGMTRAttributeCacheContainer;
@class ZGMTRReadParams;
@class ZGMTRSubscribeParams;

typedef NS_ENUM(uint8_t, ZGMTRTransportType) {
    ZGMTRTransportTypeUndefined = 0,
    ZGMTRTransportTypeUDP,
    ZGMTRTransportTypeBLE,
    ZGMTRTransportTypeTCP,
} ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));

/**
 * A path indicating an attribute being requested (for read or subscribe).
 *
 * nil is used to represent wildcards.
 */
NS_SWIFT_SENDABLE
ZGMTR_AVAILABLE(ios(17.0), macos(14.0), watchos(10.0), tvos(17.0))
@interface ZGMTRAttributeRequestPath : NSObject <NSCopying, NSSecureCoding>
@property (nonatomic, readonly, copy, nullable) NSNumber * endpoint ZGMTR_AVAILABLE(ios(17.0), macos(14.0), watchos(10.0), tvos(17.0));
@property (nonatomic, readonly, copy, nullable) NSNumber * cluster ZGMTR_AVAILABLE(ios(17.0), macos(14.0), watchos(10.0), tvos(17.0));
@property (nonatomic, readonly, copy, nullable)
    NSNumber * attribute ZGMTR_AVAILABLE(ios(17.0), macos(14.0), watchos(10.0), tvos(17.0));

+ (ZGMTRAttributeRequestPath *)requestPathWithEndpointID:(NSNumber * _Nullable)endpointID
                                             clusterID:(NSNumber * _Nullable)clusterID
                                           attributeID:(NSNumber * _Nullable)attributeID
    ZGMTR_AVAILABLE(ios(17.0), macos(14.0), watchos(10.0), tvos(17.0));
@end


/**
 * ZG extension: Represents a single attribute write request with pre-encoded TLV data.
 */
ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1))
@interface ZGMTRAttributeWriteRequest : ZGMTRAttributeRequestPath <NSSecureCoding>

/**
 * Pre-encoded TLV data for the attribute value to write.
 */
@property (nonatomic, copy, readonly, nullable) NSData * tlv;

- (instancetype)initWithEndpointID:(NSNumber * _Nullable)endpointID
                          clusterID:(NSNumber * _Nullable)clusterID
                        attributeID:(NSNumber * _Nullable)attributeID
                               tlv:(NSData * _Nullable)tlv ZGMTR_NEWLY_AVAILABLE;

@end
/**
 * A path indicating an event being requested (for read or subscribe).
 *
 * nil is used to represent wildcards.
 */
NS_SWIFT_SENDABLE
ZGMTR_AVAILABLE(ios(17.0), macos(14.0), watchos(10.0), tvos(17.0))
@interface ZGMTREventRequestPath : NSObject <NSCopying, NSSecureCoding>
@property (nonatomic, readonly, copy, nullable) NSNumber * endpoint ZGMTR_AVAILABLE(ios(17.0), macos(14.0), watchos(10.0), tvos(17.0));
@property (nonatomic, readonly, copy, nullable) NSNumber * cluster ZGMTR_AVAILABLE(ios(17.0), macos(14.0), watchos(10.0), tvos(17.0));
@property (nonatomic, readonly, copy, nullable) NSNumber * event ZGMTR_AVAILABLE(ios(17.0), macos(14.0), watchos(10.0), tvos(17.0));

+ (ZGMTREventRequestPath *)requestPathWithEndpointID:(NSNumber * _Nullable)endpointID
                                         clusterID:(NSNumber * _Nullable)clusterID
                                           eventID:(NSNumber * _Nullable)eventID
    ZGMTR_AVAILABLE(ios(17.0), macos(14.0), watchos(10.0), tvos(17.0));
@end

ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1))
@interface ZGMTRBaseDevice : NSObject

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

/**
 * Create a device object with the given node id and controller.  This
 * will always succeed, even if there is no such node id on the controller's
 * fabric, but attempts to actually use the ZGMTRBaseDevice will fail
 * (asynchronously) in that case.
 */
+ (ZGMTRBaseDevice *)deviceWithNodeID:(NSNumber *)nodeID
                         controller:(ZGMTRDeviceController *)controller
    ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));

/**
 * The transport used by the current session with this device, or
 * `ZGMTRTransportTypeUndefined` if no session is currently active.
 */
@property (readonly) ZGMTRTransportType sessionTransportType ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));

/**
 * Subscribe to receive attribute reports for everything (all endpoints, all
 * clusters, all attributes, all events) on the device.
 *
 * A non-nil attribute cache container will cache attribute values, retrievable
 * through the designated attribute cache container.
 *
 * attributeReportHandler will be called any time a data update is available (with a
 * non-nil "value")
 *
 * The array passed to attributeReportHandler will contain ZGMTRAttributeReport
 * instances.  Errors for specific paths, not the whole subscription, will be
 * reported via those objects.
 *
 * eventReportHandler will be called any time an event is reported (with a
 * non-nil "value")
 *
 * The array passed to eventReportHandler will contain ZGMTREventReport
 * instances.  Errors for specific paths, not the whole subscription, will be
 * reported via those objects.
 *
 * errorHandler will be called any time there is an error for the entire
 * subscription (with a non-nil "error"), and terminate the subscription.  This
 * will generally not be invoked if auto-resubscription is enabled, unless there
 * is a fatal error during a resubscription attempt.
 *
 * Both report handlers are not supported over XPC at the moment.
 *
 * The subscriptionEstablished block, if not nil, will be called once the
 * subscription is established.  This will be _after_ the first (priming) call
 * to both report handlers.  Note that if the ZGMTRSubscribeParams are set to
 * automatically resubscribe this can end up being called more than once.
 *
 * The resubscriptionScheduled block, if not nil, will be called if
 * auto-resubscription is enabled, subscription loss is detected, and a
 * resubscription is scheduled.  This can be called multiple times in a row
 * without an intervening subscriptionEstablished call if the resubscription
 * attempts fail.
 */
- (void)subscribeWithQueue:(dispatch_queue_t)queue
                        params:(ZGMTRSubscribeParams *)params
    clusterStateCacheContainer:(ZGMTRClusterStateCacheContainer * _Nullable)clusterStateCacheContainer
        attributeReportHandler:(ZGMTRDeviceReportHandler _Nullable)attributeReportHandler
            eventReportHandler:(ZGMTRDeviceReportHandler _Nullable)eventReportHandler
                  errorHandler:(ZGMTRDeviceErrorHandler)errorHandler
       subscriptionEstablished:(ZGMTRSubscriptionEstablishedHandler _Nullable)subscriptionEstablished
       resubscriptionScheduled:(ZGMTRDeviceResubscriptionScheduledHandler _Nullable)resubscriptionScheduled
    ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));

/**
 * Reads attributes from the device.
 *
 * Nil values for endpointID, clusterID, attributeID indicate wildcards
 * (e.g. nil attributeID means "read all the attributes from the endpoint(s) and
 * cluster(s) that match endpointID/clusterID").
 *
 * If all of endpointID, clusterID, attributeID are non-nil, a single
 * attribute will be read.
 *
 * If all of endpointID, clusterID, attributeID are nil, all attributes on the
 * device will be read.
 *
 * A non-nil attributeID along with a nil clusterID will only succeed if the
 * attribute ID is for a global attribute that applies to all clusters.
 *
 * The completion will be called with an error if the entire read interaction fails.
 * Otherwise it will be called with values, which may be empty (e.g. if no paths
 * matched the wildcard) or may include per-path errors if particular paths
 * failed.
 */
- (void)readAttributesWithEndpointID:(NSNumber * _Nullable)endpointID
                           clusterID:(NSNumber * _Nullable)clusterID
                         attributeID:(NSNumber * _Nullable)attributeID
                              params:(ZGMTRReadParams * _Nullable)params
                               queue:(dispatch_queue_t)queue
                          completion:(ZGMTRDeviceResponseHandler)completion
    ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));

/**
 * Reads multiple attribute or event paths from the device.
 *
 * Nil is treated as an empty array for attributePaths and eventPaths.
 *
 * Lists of attribute and event paths to read can be provided via attributePaths and eventPaths.
 *
 * The completion will be called with an error if the entire read interaction fails. Otherwise it
 * will be called with an array of values. This array may be empty (e.g. if no paths matched the
 * wildcard paths passed in, or if empty lists of paths were passed in) or may include per-path
 * errors if particular paths failed.
 *
 * If the sum of the lengths of attributePaths and eventPaths exceeds 9, the read may fail due to the device not supporting that
 * many read paths.
 */
- (void)readAttributePaths:(NSArray<ZGMTRAttributeRequestPath *> * _Nullable)attributePaths
                eventPaths:(NSArray<ZGMTREventRequestPath *> * _Nullable)eventPaths
                    params:(ZGMTRReadParams * _Nullable)params
                     queue:(dispatch_queue_t)queue
                completion:(ZGMTRDeviceResponseHandler)completion ZGMTR_AVAILABLE(ios(17.0), macos(14.0), watchos(10.0), tvos(17.0));

/**
 * Write to attribute in a designated attribute path
 *
 * @param value       A data-value NSDictionary object as described in
 *                    ZGMTRDeviceResponseHandler.
 *
 * @param timeoutMs   timeout in milliseconds for timed write, or nil.
 *
 * @param completion  response handler will receive either values or error.
 *
 *                    A path-specific error status will get turned into an error
 *                    passed to the completion, so values will only be passed in
 *                    when the write succeeds.  In that case, values will have
 *                    the format documented in the definition of
 *                    ZGMTRDeviceResponseHandler and will be an array with a single element
 *                    which is a dictionary that has a ZGMTRAttributePathKey entry in it, whose value
 *                    is the attribute path that was successfully written to.
 */
- (void)writeAttributeWithEndpointID:(NSNumber *)endpointID
                           clusterID:(NSNumber *)clusterID
                         attributeID:(NSNumber *)attributeID
                               value:(id)value
                   timedWriteTimeout:(NSNumber * _Nullable)timeoutMs
                               queue:(dispatch_queue_t)queue
                          completion:(ZGMTRDeviceResponseHandler)completion
    ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));

/**
 * ZG extension: Write one or more attributes using pre-encoded TLV data.
 * timedWriteTimeout controls the timed-write interaction timeout.
 * imTimeoutMs controls the IM exchange timeout for the write request.
 */
- (void)writeAttributeRequests:(NSArray<ZGMTRAttributeWriteRequest *> * _Nullable)attributePaths
                   timedWriteTimeout:(NSNumber * _Nullable)timeoutMs
                   imTimeoutMs:(NSNumber * _Nullable)imTimeoutMs
                         queue:(dispatch_queue_t)queue
                          completion:(ZGMTRDeviceResponseHandler)completion
    ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

/**
 * Invoke a command with a designated command path
 *
 * @param commandFields   command fields object. The object must be a data-value NSDictionary object
 *                      as described in the ZGMTRDeviceResponseHandler.
 *                      The attribute must be a Structure, i.e.,
 *                      the NSDictionary ZGMTRTypeKey key must have the value ZGMTRStructureValueType.
 *
 * @param timeoutMs   timeout in milliseconds for timed invoke, or nil.
 *
 * @param completion  response handler will receive either values or error.  A
 *                    path-specific error status from the command invocation
 *                    will result in an error being passed to the completion, so
 *                    values will only be passed in when the command succeeds.
 */
- (void)invokeCommandWithEndpointID:(NSNumber *)endpointID
                          clusterID:(NSNumber *)clusterID
                          commandID:(NSNumber *)commandID
                      commandFields:(id)commandFields
                 timedInvokeTimeout:(NSNumber * _Nullable)timeoutMs
                              queue:(dispatch_queue_t)queue
                         completion:(ZGMTRDeviceResponseHandler)completion
    ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));

/**
 * Subscribes to the specified attributes on the device.
 *
 * Nil values for endpointID, clusterID, attributeID indicate wildcards
 * (e.g. nil attributeID means "subscribe to all the attributes from the
 * endpoint(s) and cluster(s) that match endpointID/clusterID").
 *
 * If all of endpointID, clusterID, attributeID are non-nil, a single attribute
 * will be subscribed to.
 *
 * If all of endpointID, clusterID, attributeID are nil, all attributes on the
 * device will be subscribed to.
 *
 * A non-nil attributeID along with a nil clusterID will only succeed if the
 * attribute ID is for a global attribute that applies to all clusters.
 *
 * The reportHandler will be called with an error if the subscription fails
 * entirely.
 *
 * The reportHandler will be called with arrays of response-value dictionaries
 * (which may be data or errors) as path-specific data is received.
 *
 * subscriptionEstablished will be called when the subscription is first
 * successfully established (after the initial set of data reports has been
 * delivered to reportHandler).  If params allow automatic resubscription, it
 * will be called any time resubscription succeeds.
 */
- (void)subscribeToAttributesWithEndpointID:(NSNumber * _Nullable)endpointID
                                  clusterID:(NSNumber * _Nullable)clusterID
                                attributeID:(NSNumber * _Nullable)attributeID
                                     params:(ZGMTRSubscribeParams * _Nullable)params
                                      queue:(dispatch_queue_t)queue
                              reportHandler:(ZGMTRDeviceResponseHandler)reportHandler
                    subscriptionEstablished:(ZGMTRSubscriptionEstablishedHandler _Nullable)subscriptionEstablished
    ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));

/**
 * Subscribes to multiple attribute or event paths.
 *
 * Nil is treated as an empty array for attributePaths and eventPaths.
 *
 * Lists of attribute and event paths to subscribe to can be provided via attributePaths and eventPaths.
 *
 * The reportHandler will be called with an error if the subscription fails
 * entirely (including when both attributePaths and eventPaths are empty).
 *
 * The reportHandler will be called with arrays of response-value dictionaries
 * (which may be data or errors) as path-specific data is received.
 *
 * subscriptionEstablished will be called when the subscription is first
 * successfully established (after the initial set of data reports has been
 * delivered to reportHandler).  If params allow automatic resubscription, it
 * will be called any time resubscription succeeds.
 *
 * resubscriptionScheduled will be called if subscription drop is detected and
 * params allow automatic resubscription.
 *
 * If the sum of the lengths of attributePaths and eventPaths exceeds 3, the subscribe may fail due to the device not supporting
 * that many paths for a subscription.
 */
- (void)subscribeToAttributePaths:(NSArray<ZGMTRAttributeRequestPath *> * _Nullable)attributePaths
                       eventPaths:(NSArray<ZGMTREventRequestPath *> * _Nullable)eventPaths
                           params:(ZGMTRSubscribeParams * _Nullable)params
                            queue:(dispatch_queue_t)queue
                    reportHandler:(ZGMTRDeviceResponseHandler)reportHandler
          subscriptionEstablished:(ZGMTRSubscriptionEstablishedHandler _Nullable)subscriptionEstablished
          resubscriptionScheduled:(ZGMTRDeviceResubscriptionScheduledHandler _Nullable)resubscriptionScheduled
    ZGMTR_AVAILABLE(ios(17.0), macos(14.0), watchos(10.0), tvos(17.0));

/**
 * ZG extension: subscribe to attribute paths with the subscription ID passed to the
 * established callback.  Identical to subscribeToAttributePaths, except that the
 * callback receives the real SubscriptionId as an NSNumber.
 */
- (void)customSubscribeToAttributePaths:(NSArray<ZGMTRAttributeRequestPath *> * _Nullable)attributePaths
                             eventPaths:(NSArray<ZGMTREventRequestPath *> * _Nullable)eventPaths
                                 params:(ZGMTRSubscribeParams * _Nullable)params
                                  queue:(dispatch_queue_t)queue
                          reportHandler:(ZGMTRDeviceResponseHandler)reportHandler
                subscriptionEstablished:(void (^_Nullable)(NSNumber * _Nullable subscriptionId))subscriptionEstablished
                resubscriptionScheduled:(ZGMTRDeviceResubscriptionScheduledHandler _Nullable)resubscriptionScheduled
    ZGMTR_AVAILABLE(ios(17.0), macos(14.0), watchos(10.0), tvos(17.0));

/**
 * Deregister all local report handlers for a remote device
 *
 * This method is applicable only for a remote device. For a local device, the stack has to be shutdown to stop report handlers.
 * There could be multiple clients accessing a node through a remote controller object and hence it is not appropriate
 * for one of those clients to shut down the entire stack to stop receiving reports.
 */
- (void)deregisterReportHandlersWithQueue:(dispatch_queue_t)queue
                               completion:(dispatch_block_t)completion
    ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));

/**
 * Open a commissioning window on the device.
 *
 * On success, completion will be called on queue with the ZGMTRSetupPayload that
 * can be used to commission the device.
 *
 * @param setupPasscode The setup passcode to use for the commissioning window.
 *                      See ZGMTRSetupPayload's generateRandomSetupPasscode for
 *                      generating a valid random passcode.
 * @param discriminator The discriminator to use for the commissionable
 *                      advertisement.
 * @param duration      Duration, in seconds, during which the commissioning
 *                      window will be open.
 */
- (void)openCommissioningWindowWithSetupPasscode:(NSNumber *)setupPasscode
                                   discriminator:(NSNumber *)discriminator
                                        duration:(NSNumber *)duration
                                           queue:(dispatch_queue_t)queue
                                      completion:(ZGMTRDeviceOpenCommissioningWindowHandler)completion
    ZGMTR_AVAILABLE(ios(16.2), macos(13.1), watchos(9.2), tvos(16.2));

/**
 * Open a commissioning window on the device, using a random setup passcode.
 *
 * On success, completion will be called on queue with the ZGMTRSetupPayload that
 * can be used to commission the device.
 *
 * @param discriminator The discriminator to use for the commissionable
 *                      advertisement.
 * @param duration      Duration, in seconds, during which the commissioning
 *                      window will be open.
 */
- (void)openCommissioningWindowWithDiscriminator:(NSNumber *)discriminator
                                        duration:(NSNumber *)duration
                                           queue:(dispatch_queue_t)queue
                                      completion:(ZGMTRDeviceOpenCommissioningWindowHandler)completion
    ZGMTR_AVAILABLE(ios(17.0), macos(14.0), watchos(10.0), tvos(17.0));

/**
 * Reads events from the device.
 *
 * Nil values for endpointID, clusterID, eventID indicate wildcards
 * (e.g. nil eventID means "read all the events from the endpoint(s) and
 * cluster(s) that match endpointID/clusterID").
 *
 * If all of endpointID, clusterID, eventID are non-nil, all the matching instances of a single
 * event will be read.
 *
 * If all of endpointID, clusterID, eventID are nil, all events on the
 * device will be read.
 *
 * The completion will be called with an error if the entire read interaction fails.
 * Otherwise it will be called with values, which may be empty (e.g. if no paths
 * matched the wildcard) or may include per-path errors if particular paths
 * failed.
 */

- (void)readEventsWithEndpointID:(NSNumber * _Nullable)endpointID
                       clusterID:(NSNumber * _Nullable)clusterID
                         eventID:(NSNumber * _Nullable)eventID
                          params:(ZGMTRReadParams * _Nullable)params
                           queue:(dispatch_queue_t)queue
                      completion:(ZGMTRDeviceResponseHandler)completion
    ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));

/**
 * Subscribes to the specified events on the device.
 *
 * Nil values for endpointID, clusterID, eventID indicate wildcards
 * (e.g. nil eventID means "subscribe to all the events from the
 * endpoint(s) and cluster(s) that match endpointID/clusterID").
 *
 * If all of endpointID, clusterID, eventID are non-nil, a single event
 * will be subscribed to.
 *
 * If all of endpointID, clusterID, eventID are nil, all events on the
 * device will be subscribed to.
 *
 * The reportHandler will be called with an error if the subscription fails
 * entirely.
 *
 * The reportHandler will be called with arrays of response-value dictionaries
 * (which may be data or errors) as path-specific data is received.
 *
 * subscriptionEstablished will be called when the subscription is first
 * successfully established (after the initial set of data reports has been
 * delivered to reportHandler).  If params allow automatic resubscription, it
 * will be called any time resubscription succeeds.
 */
- (void)subscribeToEventsWithEndpointID:(NSNumber * _Nullable)endpointID
                              clusterID:(NSNumber * _Nullable)clusterID
                                eventID:(NSNumber * _Nullable)eventID
                                 params:(ZGMTRSubscribeParams * _Nullable)params
                                  queue:(dispatch_queue_t)queue
                          reportHandler:(ZGMTRDeviceResponseHandler)reportHandler
                subscriptionEstablished:(ZGMTRSubscriptionEstablishedHandler _Nullable)subscriptionEstablished
    ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));

/**
 * Download log of the desired type from the device.
 *
 * Note: The consumer of this API should move the file that the url points to or open it for reading before the
 * completion handler returns. Otherwise, the file will be deleted, and the data will be lost.
 *
 * @param type       The type of log being requested. This should correspond to a value in the enum ZGMTRDiagnosticLogType.
 * @param timeout    The timeout for getting the log. If the timeout expires, completion will be called with whatever
 *                   has been retrieved by that point (which might be none or a partial log).
 *                   If the timeout is set to 0, the request will not expire and completion will not be called until
 *                   the log is fully retrieved or an error occurs.
 * @param queue      The queue on which completion will be called.
 * @param completion The completion handler that is called after attempting to retrieve the requested log.
 *                     - In case of success, the completion handler is called with a non-nil URL and a nil error.
 *                     - If there is an error, a non-nil error is used and the url can be non-nil too if some logs have already been downloaded.
 */
- (void)downloadLogOfType:(ZGMTRDiagnosticLogType)type
                  timeout:(NSTimeInterval)timeout
                    queue:(dispatch_queue_t)queue
               completion:(void (^)(NSURL * _Nullable url, NSError * _Nullable error))completion
    ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6));

/**
 * ZG extension: Shut down a subscription by its subscription ID and scoped node ID.
 * Returns YES on success, NO on failure.
 */
- (BOOL)shutdownSubscription:(nonnull NSNumber *)subscriptionId scopedNodeId:(nonnull NSNumber *)scopedNodeId
    ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

@end

/**
 * A path indicating a specific cluster on a device (i.e. without any
 * wildcards).
 */
NS_SWIFT_SENDABLE
ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4))
@interface ZGMTRClusterPath : NSObject <NSCopying, NSSecureCoding>

@property (nonatomic, readonly, copy) NSNumber * endpoint;
@property (nonatomic, readonly, copy) NSNumber * cluster;

+ (ZGMTRClusterPath *)clusterPathWithEndpointID:(NSNumber *)endpointID clusterID:(NSNumber *)clusterID;

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;
@end

/**
 * A path indicating a specific attribute on a device (i.e. without any
 * wildcards).
 */
NS_SWIFT_SENDABLE
ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1))
@interface ZGMTRAttributePath : ZGMTRClusterPath <NSSecureCoding>

@property (nonatomic, readonly, copy) NSNumber * attribute;

+ (ZGMTRAttributePath *)attributePathWithEndpointID:(NSNumber *)endpointID
                                        clusterID:(NSNumber *)clusterID
                                      attributeID:(NSNumber *)attributeID
    ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
@end

/**
 * A path indicating a specific event that can be emitted on a device
 * (i.e. without any wildcards).  There can be multiple instances of actual
 * events for a given event path.
 */
NS_SWIFT_SENDABLE
ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1))
@interface ZGMTREventPath : ZGMTRClusterPath

@property (nonatomic, readonly, copy) NSNumber * event;

+ (ZGMTREventPath *)eventPathWithEndpointID:(NSNumber *)endpointID
                                clusterID:(NSNumber *)clusterID
                                  eventID:(NSNumber *)eventID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
@end

/**
 * A path indicating a specific command on a device (i.e. without any
 * wildcards).
 */
NS_SWIFT_SENDABLE
ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1))
@interface ZGMTRCommandPath : ZGMTRClusterPath

@property (nonatomic, readonly, copy) NSNumber * command;

+ (ZGMTRCommandPath *)commandPathWithEndpointID:(NSNumber *)endpointID
                                    clusterID:(NSNumber *)clusterID
                                    commandID:(NSNumber *)commandID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
@end

NS_SWIFT_SENDABLE
ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1))
@interface ZGMTRAttributeReport : NSObject

@property (nonatomic, readonly, copy) ZGMTRAttributePath * path;

/**
 * value will be nil in the following cases:
 *
 * * There was an error.  In this case, "error" will not be nil.
 * * The attribute is nullable and the value of the attribute is null.
 *
 * If value is not nil, the actual type of value will depend on the
 * schema-defined (typically defined in the ZGMatter specification) type of the
 * attribute as follows:
 *
 * * list: NSArray of whatever type the list entries are.
 * * struct: The corresponding structure interface defined by ZGMatter.framework
 * * octet string: NSData
 * * string: NSString
 * * discrete/analog types: NSNumber
 *
 * Derived types (in the ZGMatter specification sense) are represented the same as
 * the base type, except for "string" (which is a derived type of "octet string"
 * in the specification).
 */
@property (nonatomic, readonly, copy, nullable) id value;

/**
 * If this specific path resulted in an error, the error (in the
 * ZGMTRInteractionErrorDomain or ZGMTRErrorDomain) that corresponds to this
 * path.
 */
@property (nonatomic, readonly, copy, nullable) NSError * error;

/**
 * Initialize an ZGMTRAttributeReport with a response-value dictionary of the sort
 * that ZGMTRDeviceResponseHandler would receive.
 *
 * Will return nil and hand out an error if the response-value dictionary is not
 * an attribute response.
 *
 * Will set the value property to nil and the error property to non-nil, even if
 * the schema for the value is not known, if the response-value is an error, not
 * data.
 *
 * Will return nil and hand out an error if the response-value is data in the
 * following cases:
 *
 * * The response is for a cluster/attribute combination for which the schema is
 *   unknown and hence the type of the data is not known.
 * * The data does not match the known schema.
 */
- (nullable instancetype)initWithResponseValue:(NSDictionary<NSString *, id> *)responseValue
                                         error:(NSError * __autoreleasing *)error
    ZGMTR_AVAILABLE(ios(17.0), macos(14.0), watchos(10.0), tvos(17.0));

@end

typedef NS_ENUM(NSUInteger, ZGMTREventTimeType) {
    ZGMTREventTimeTypeSystemUpTime = 0,
    ZGMTREventTimeTypeTimestampDate
} ZGMTR_AVAILABLE(ios(16.5), macos(13.4), watchos(9.5), tvos(16.5));

typedef NS_ENUM(NSUInteger, ZGMTREventPriority) {
    ZGMTREventPriorityDebug = 0,
    ZGMTREventPriorityInfo = 1,
    ZGMTREventPriorityCritical = 2
} ZGMTR_AVAILABLE(ios(16.5), macos(13.4), watchos(9.5), tvos(16.5));

NS_SWIFT_SENDABLE
ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1))
@interface ZGMTREventReport : NSObject

@property (nonatomic, readonly, copy) ZGMTREventPath * path;

/**
 * eventNumber will only have a useful value if "error" is nil.
 */
@property (nonatomic, readonly, copy) NSNumber * eventNumber; // EventNumber type (uint64_t)

/**
 * priority will only have a useful value if "error" is nil.
 */
@property (nonatomic, readonly, copy) NSNumber * priority; // PriorityLevel type (ZGMTREventPriority)

/**
 * Either systemUpTime or timestampDate will be valid depending on
 * eventTimeType, if "error" is nil.  If "error" is not nil, none of
 * eventTimeType, systemUpTime, timestampDate should be expected to have useful
 * values.
 */
@property (nonatomic, readonly) ZGMTREventTimeType eventTimeType ZGMTR_AVAILABLE(ios(16.5), macos(13.4), watchos(9.5), tvos(16.5));
@property (nonatomic, readonly) NSTimeInterval systemUpTime ZGMTR_AVAILABLE(ios(16.5), macos(13.4), watchos(9.5), tvos(16.5));
@property (nonatomic, readonly, copy, nullable)
    NSDate * timestampDate ZGMTR_AVAILABLE(ios(16.5), macos(13.4), watchos(9.5), tvos(16.5));

/**
 * An instance of the event payload interface that corresponds to the report's
 * path (e.g. ZGMTRBasicInformationClusterStartUpEvent if the path's cluster
 * 0x0028 "Basic Information" and the path's event is 0x00 "StartUp"), or nil if
 * error is not nil (in which case there is no payload available).
 */
@property (nonatomic, readonly, copy, nullable) id value;

/**
 * If this specific path resulted in an error, the error (in the
 * ZGMTRInteractionErrorDomain or ZGMTRErrorDomain) that corresponds to this
 * path.
 */
@property (nonatomic, readonly, copy, nullable) NSError * error;

/**
 * Initialize an ZGMTREventReport with a response-value dictionary of the sort
 * that ZGMTRDeviceResponseHandler would receive.
 *
 * Will return nil and hand out an error if the response-value dictionary is not
 * an event response.
 *
 * Will set the value property to nil and the error property to non-nil, even if
 * the schema for the value is not known, if the response-value is an error, not
 * data.
 *
 * Will return nil and hand out an error if the response-value is data in the
 * following cases:
 *
 * * The response is for a cluster/event combination for which the schema is
 *   unknown and hence the type of the data is not known.
 * * The data does not match the known schema.
 */
- (nullable instancetype)initWithResponseValue:(NSDictionary<NSString *, id> *)responseValue
                                         error:(NSError * __autoreleasing *)error
    ZGMTR_AVAILABLE(ios(17.0), macos(14.0), watchos(10.0), tvos(17.0));

@end

@interface ZGMTRBaseDevice (Deprecated)

/**
 * Deprecated ZGMTRBaseDevice APIs.
 */
- (void)subscribeWithQueue:(dispatch_queue_t)queue
                minInterval:(uint16_t)minInterval
                maxInterval:(uint16_t)maxInterval
                     params:(ZGMTRSubscribeParams * _Nullable)params
             cacheContainer:(ZGMTRAttributeCacheContainer * _Nullable)attributeCacheContainer
     attributeReportHandler:(ZGMTRDeviceReportHandler _Nullable)attributeReportHandler
         eventReportHandler:(ZGMTRDeviceReportHandler _Nullable)eventReportHandler
               errorHandler:(ZGMTRDeviceErrorHandler)errorHandler
    subscriptionEstablished:(dispatch_block_t _Nullable)subscriptionEstablishedHandler
    resubscriptionScheduled:(ZGMTRDeviceResubscriptionScheduledHandler _Nullable)resubscriptionScheduledHandler
    ZGMTR_DEPRECATED("Please use "
                   "subscribeWithQueue:params:clusterStateCacheContainer:attributeReportHandler:eventReportHandler:errorHandler:"
                   "subscriptionEstablished:resubscriptionScheduled:",
        ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));

- (void)readAttributeWithEndpointId:(NSNumber * _Nullable)endpointId
                          clusterId:(NSNumber * _Nullable)clusterId
                        attributeId:(NSNumber * _Nullable)attributeId
                             params:(ZGMTRReadParams * _Nullable)params
                        clientQueue:(dispatch_queue_t)clientQueue
                         completion:(ZGMTRDeviceResponseHandler)completion
    ZGMTR_DEPRECATED("Please use readAttributesWithEndpointID:clusterID:attributeID:params:queue:completion:", ios(16.1, 16.4),
        macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));

- (void)writeAttributeWithEndpointId:(NSNumber *)endpointId
                           clusterId:(NSNumber *)clusterId
                         attributeId:(NSNumber *)attributeId
                               value:(id)value
                   timedWriteTimeout:(NSNumber * _Nullable)timeoutMs
                         clientQueue:(dispatch_queue_t)clientQueue
                          completion:(ZGMTRDeviceResponseHandler)completion
    ZGMTR_DEPRECATED("Please use writeAttributeWithEndpointID:clusterID:attributeID:value:timedWriteTimeout:queue:completion:",
        ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));

- (void)invokeCommandWithEndpointId:(NSNumber *)endpointId
                          clusterId:(NSNumber *)clusterId
                          commandId:(NSNumber *)commandId
                      commandFields:(id)commandFields
                 timedInvokeTimeout:(NSNumber * _Nullable)timeoutMs
                        clientQueue:(dispatch_queue_t)clientQueue
                         completion:(ZGMTRDeviceResponseHandler)completion
    ZGMTR_DEPRECATED("Please use invokeCommandWithEndpointID:clusterID:commandID:commandFields:timedInvokeTimeout:queue:completion",
        ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));

- (void)subscribeAttributeWithEndpointId:(NSNumber * _Nullable)endpointId
                               clusterId:(NSNumber * _Nullable)clusterId
                             attributeId:(NSNumber * _Nullable)attributeId
                             minInterval:(NSNumber *)minInterval
                             maxInterval:(NSNumber *)maxInterval
                                  params:(ZGMTRSubscribeParams * _Nullable)params
                             clientQueue:(dispatch_queue_t)clientQueue
                           reportHandler:(ZGMTRDeviceResponseHandler)reportHandler
                 subscriptionEstablished:(dispatch_block_t _Nullable)subscriptionEstablishedHandler
    ZGMTR_DEPRECATED("Please use "
                   "subscribeToAttributesWithEndpointID:clusterID:attributeID:params:queue:"
                   "reportHandler:subscriptionEstablished:",
        ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));

- (void)deregisterReportHandlersWithClientQueue:(dispatch_queue_t)queue
                                     completion:(dispatch_block_t)completion
    ZGMTR_DEPRECATED("Pease use deregisterReportHandlersWithQueue:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4),
        tvos(16.1, 16.4));

@end

@interface ZGMTRAttributePath (Deprecated)

+ (instancetype)attributePathWithEndpointId:(NSNumber *)endpointId
                                  clusterId:(NSNumber *)clusterId
                                attributeId:(NSNumber *)attributeId
    ZGMTR_DEPRECATED("Please use attributePathWithEndpointID:clusterID:attributeID:", ios(16.1, 16.4), macos(13.0, 13.3),
        watchos(9.1, 9.4), tvos(16.1, 16.4));

@end

@interface ZGMTREventPath (Deprecated)

+ (instancetype)eventPathWithEndpointId:(NSNumber *)endpointId
                              clusterId:(NSNumber *)clusterId
                                eventId:(NSNumber *)eventId
    ZGMTR_DEPRECATED("Please use eventPathWithEndpointID:clusterID:eventID:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4),
        tvos(16.1, 16.4));

@end

@interface ZGMTRCommandPath (Deprecated)

+ (instancetype)commandPathWithEndpointId:(NSNumber *)endpointId
                                clusterId:(NSNumber *)clusterId
                                commandId:(NSNumber *)commandId
    ZGMTR_DEPRECATED("Please use commandPathWithEndpointID:clusterID:commandID:", ios(16.1, 16.4), macos(13.0, 13.3),
        watchos(9.1, 9.4), tvos(16.1, 16.4));

@end

@interface ZGMTREventReport (Deprecated)
@property (nonatomic, readonly, copy) NSNumber * timestamp ZGMTR_DEPRECATED(
    "Please use timestampDate and systemUpTime", ios(16.1, 16.5), macos(13.0, 13.4), watchos(9.1, 9.5), tvos(16.1, 16.5));
@end

NS_ASSUME_NONNULL_END
