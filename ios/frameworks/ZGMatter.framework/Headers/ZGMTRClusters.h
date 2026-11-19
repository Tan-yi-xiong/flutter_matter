/*
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

#import <ZGMatter/ZGMTRBaseClusters.h>
#import <ZGMatter/ZGMTRCluster.h>
#import <ZGMatter/ZGMTRCommandPayloadsObjc.h>
#import <ZGMatter/ZGMTRDefines.h>
#import <ZGMatter/ZGMTRDevice.h>

NS_ASSUME_NONNULL_BEGIN

/**
 * Cluster Identify
 *    Attributes and commands for putting a device into Identification mode (e.g. flashing a light).
 */
ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1))
@interface ZGMTRClusterIdentify : ZGMTRGenericCluster

- (void)identifyWithParams:(ZGMTRIdentifyClusterIdentifyParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(ZGMTRStatusCompletion)completion ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
- (void)triggerEffectWithParams:(ZGMTRIdentifyClusterTriggerEffectParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(ZGMTRStatusCompletion)completion ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeIdentifyTimeWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));
- (void)writeAttributeIdentifyTimeWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));
- (void)writeAttributeIdentifyTimeWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs params:(ZGMTRWriteParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeIdentifyTypeWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeGeneratedCommandListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeAcceptedCommandListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeAttributeListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeFeatureMapWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeClusterRevisionWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end

@interface ZGMTRClusterIdentify (Availability)

/**
 * For all instance methods that take a completion (i.e. command invocations),
 * the completion will be called on the provided queue.
 */
- (instancetype _Nullable)initWithDevice:(ZGMTRDevice *)device
                              endpointID:(NSNumber *)endpointID
                                   queue:(dispatch_queue_t)queue ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));

@end

/**
 * Cluster Groups
 *    Attributes and commands for group configuration and manipulation.
 */
ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1))
@interface ZGMTRClusterGroups : ZGMTRGenericCluster

- (void)addGroupWithParams:(ZGMTRGroupsClusterAddGroupParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(void (^)(ZGMTRGroupsClusterAddGroupResponseParams * _Nullable data, NSError * _Nullable error))completion ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
- (void)viewGroupWithParams:(ZGMTRGroupsClusterViewGroupParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(void (^)(ZGMTRGroupsClusterViewGroupResponseParams * _Nullable data, NSError * _Nullable error))completion ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
- (void)getGroupMembershipWithParams:(ZGMTRGroupsClusterGetGroupMembershipParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(void (^)(ZGMTRGroupsClusterGetGroupMembershipResponseParams * _Nullable data, NSError * _Nullable error))completion ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
- (void)removeGroupWithParams:(ZGMTRGroupsClusterRemoveGroupParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(void (^)(ZGMTRGroupsClusterRemoveGroupResponseParams * _Nullable data, NSError * _Nullable error))completion ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
- (void)removeAllGroupsWithParams:(ZGMTRGroupsClusterRemoveAllGroupsParams * _Nullable)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(ZGMTRStatusCompletion)completion ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
- (void)removeAllGroupsWithExpectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedValues expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(ZGMTRStatusCompletion)completion
    ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
- (void)addGroupIfIdentifyingWithParams:(ZGMTRGroupsClusterAddGroupIfIdentifyingParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(ZGMTRStatusCompletion)completion ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeNameSupportWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeGeneratedCommandListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeAcceptedCommandListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeAttributeListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeFeatureMapWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeClusterRevisionWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end

@interface ZGMTRClusterGroups (Availability)

/**
 * For all instance methods that take a completion (i.e. command invocations),
 * the completion will be called on the provided queue.
 */
- (instancetype _Nullable)initWithDevice:(ZGMTRDevice *)device
                              endpointID:(NSNumber *)endpointID
                                   queue:(dispatch_queue_t)queue ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));

@end

/**
 * Cluster On/Off
 *    Attributes and commands for switching devices between 'On' and 'Off' states.
 */
ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1))
@interface ZGMTRClusterOnOff : ZGMTRGenericCluster

- (void)offWithParams:(ZGMTROnOffClusterOffParams * _Nullable)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(ZGMTRStatusCompletion)completion ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
- (void)offWithExpectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedValues expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(ZGMTRStatusCompletion)completion
    ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
- (void)onWithParams:(ZGMTROnOffClusterOnParams * _Nullable)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(ZGMTRStatusCompletion)completion ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
- (void)onWithExpectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedValues expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(ZGMTRStatusCompletion)completion
    ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
- (void)toggleWithParams:(ZGMTROnOffClusterToggleParams * _Nullable)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(ZGMTRStatusCompletion)completion ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
- (void)toggleWithExpectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedValues expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(ZGMTRStatusCompletion)completion
    ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
- (void)offWithEffectWithParams:(ZGMTROnOffClusterOffWithEffectParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(ZGMTRStatusCompletion)completion ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
- (void)onWithRecallGlobalSceneWithParams:(ZGMTROnOffClusterOnWithRecallGlobalSceneParams * _Nullable)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(ZGMTRStatusCompletion)completion ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
- (void)onWithRecallGlobalSceneWithExpectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedValues expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(ZGMTRStatusCompletion)completion
    ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
- (void)onWithTimedOffWithParams:(ZGMTROnOffClusterOnWithTimedOffParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(ZGMTRStatusCompletion)completion ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeOnOffWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeGlobalSceneControlWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeOnTimeWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));
- (void)writeAttributeOnTimeWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));
- (void)writeAttributeOnTimeWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs params:(ZGMTRWriteParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeOffWaitTimeWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));
- (void)writeAttributeOffWaitTimeWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));
- (void)writeAttributeOffWaitTimeWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs params:(ZGMTRWriteParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeStartUpOnOffWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));
- (void)writeAttributeStartUpOnOffWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));
- (void)writeAttributeStartUpOnOffWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs params:(ZGMTRWriteParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeGeneratedCommandListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeAcceptedCommandListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeAttributeListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeFeatureMapWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeClusterRevisionWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end

@interface ZGMTRClusterOnOff (Availability)

/**
 * For all instance methods that take a completion (i.e. command invocations),
 * the completion will be called on the provided queue.
 */
- (instancetype _Nullable)initWithDevice:(ZGMTRDevice *)device
                              endpointID:(NSNumber *)endpointID
                                   queue:(dispatch_queue_t)queue ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));

@end

/**
 * Cluster Level Control
 *    Attributes and commands for controlling devices that can be set to a level between fully 'On' and fully 'Off.'
 */
ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1))
@interface ZGMTRClusterLevelControl : ZGMTRGenericCluster

- (void)moveToLevelWithParams:(ZGMTRLevelControlClusterMoveToLevelParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(ZGMTRStatusCompletion)completion ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
- (void)moveWithParams:(ZGMTRLevelControlClusterMoveParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(ZGMTRStatusCompletion)completion ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
- (void)stepWithParams:(ZGMTRLevelControlClusterStepParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(ZGMTRStatusCompletion)completion ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
- (void)stopWithParams:(ZGMTRLevelControlClusterStopParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(ZGMTRStatusCompletion)completion ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
- (void)moveToLevelWithOnOffWithParams:(ZGMTRLevelControlClusterMoveToLevelWithOnOffParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(ZGMTRStatusCompletion)completion ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
- (void)moveWithOnOffWithParams:(ZGMTRLevelControlClusterMoveWithOnOffParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(ZGMTRStatusCompletion)completion ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
- (void)stepWithOnOffWithParams:(ZGMTRLevelControlClusterStepWithOnOffParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(ZGMTRStatusCompletion)completion ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
- (void)stopWithOnOffWithParams:(ZGMTRLevelControlClusterStopWithOnOffParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(ZGMTRStatusCompletion)completion ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
- (void)moveToClosestFrequencyWithParams:(ZGMTRLevelControlClusterMoveToClosestFrequencyParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(ZGMTRStatusCompletion)completion ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeCurrentLevelWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeRemainingTimeWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeMinLevelWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeMaxLevelWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeCurrentFrequencyWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeMinFrequencyWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeMaxFrequencyWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeOptionsWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));
- (void)writeAttributeOptionsWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));
- (void)writeAttributeOptionsWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs params:(ZGMTRWriteParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeOnOffTransitionTimeWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));
- (void)writeAttributeOnOffTransitionTimeWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));
- (void)writeAttributeOnOffTransitionTimeWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs params:(ZGMTRWriteParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeOnLevelWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));
- (void)writeAttributeOnLevelWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));
- (void)writeAttributeOnLevelWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs params:(ZGMTRWriteParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeOnTransitionTimeWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));
- (void)writeAttributeOnTransitionTimeWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));
- (void)writeAttributeOnTransitionTimeWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs params:(ZGMTRWriteParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeOffTransitionTimeWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));
- (void)writeAttributeOffTransitionTimeWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));
- (void)writeAttributeOffTransitionTimeWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs params:(ZGMTRWriteParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeDefaultMoveRateWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));
- (void)writeAttributeDefaultMoveRateWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));
- (void)writeAttributeDefaultMoveRateWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs params:(ZGMTRWriteParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeStartUpCurrentLevelWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));
- (void)writeAttributeStartUpCurrentLevelWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));
- (void)writeAttributeStartUpCurrentLevelWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs params:(ZGMTRWriteParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeGeneratedCommandListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeAcceptedCommandListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeAttributeListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeFeatureMapWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeClusterRevisionWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end

@interface ZGMTRClusterLevelControl (Availability)

/**
 * For all instance methods that take a completion (i.e. command invocations),
 * the completion will be called on the provided queue.
 */
- (instancetype _Nullable)initWithDevice:(ZGMTRDevice *)device
                              endpointID:(NSNumber *)endpointID
                                   queue:(dispatch_queue_t)queue ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));

@end

/**
 * Cluster Pulse Width Modulation
 *    Cluster to control pulse width modulation
 */
ZGMTR_PROVISIONALLY_AVAILABLE
@interface ZGMTRClusterPulseWidthModulation : ZGMTRGenericCluster

- (NSDictionary<NSString *, id> * _Nullable)readAttributeGeneratedCommandListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeAcceptedCommandListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeAttributeListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeFeatureMapWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeClusterRevisionWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end

@interface ZGMTRClusterPulseWidthModulation (Availability)

/**
 * The queue is currently unused, but may be used in the future for calling completions
 * for command invocations if commands are added to this cluster.
 */
- (instancetype _Nullable)initWithDevice:(ZGMTRDevice *)device
                              endpointID:(NSNumber *)endpointID
                                   queue:(dispatch_queue_t)queue ZGMTR_PROVISIONALLY_AVAILABLE;

@end

/**
 * Cluster Descriptor
 *    The Descriptor Cluster is meant to replace the support from the Zigbee Device Object (ZDO) for describing a node, its endpoints and clusters.
 */
ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1))
@interface ZGMTRClusterDescriptor : ZGMTRGenericCluster

- (NSDictionary<NSString *, id> * _Nullable)readAttributeDeviceTypeListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeServerListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeClientListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributePartsListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeTagListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeEndpointUniqueIDWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeGeneratedCommandListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeAcceptedCommandListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeAttributeListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeFeatureMapWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeClusterRevisionWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end

@interface ZGMTRClusterDescriptor (Availability)

/**
 * The queue is currently unused, but may be used in the future for calling completions
 * for command invocations if commands are added to this cluster.
 */
- (instancetype _Nullable)initWithDevice:(ZGMTRDevice *)device
                              endpointID:(NSNumber *)endpointID
                                   queue:(dispatch_queue_t)queue ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));

@end

/**
 * Cluster Binding
 *    The Binding Cluster is meant to replace the support from the Zigbee Device Object (ZDO) for supporting the binding table.
 */
ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1))
@interface ZGMTRClusterBinding : ZGMTRGenericCluster

- (NSDictionary<NSString *, id> * _Nullable)readAttributeBindingWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));
- (void)writeAttributeBindingWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));
- (void)writeAttributeBindingWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs params:(ZGMTRWriteParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeGeneratedCommandListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeAcceptedCommandListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeAttributeListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeFeatureMapWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeClusterRevisionWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end

@interface ZGMTRClusterBinding (Availability)

/**
 * The queue is currently unused, but may be used in the future for calling completions
 * for command invocations if commands are added to this cluster.
 */
- (instancetype _Nullable)initWithDevice:(ZGMTRDevice *)device
                              endpointID:(NSNumber *)endpointID
                                   queue:(dispatch_queue_t)queue ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));

@end

/**
 * Cluster Access Control
 *    The Access Control Cluster exposes a data model view of a
      Node's Access Control List (ACL), which codifies the rules used to manage
      and enforce Access Control for the Node's endpoints and their associated
      cluster instances.
 */
ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1))
@interface ZGMTRClusterAccessControl : ZGMTRGenericCluster

- (void)reviewFabricRestrictionsWithParams:(ZGMTRAccessControlClusterReviewFabricRestrictionsParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(void (^)(ZGMTRAccessControlClusterReviewFabricRestrictionsResponseParams * _Nullable data, NSError * _Nullable error))completion ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeACLWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
- (void)writeAttributeACLWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
- (void)writeAttributeACLWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs params:(ZGMTRWriteParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeExtensionWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));
- (void)writeAttributeExtensionWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));
- (void)writeAttributeExtensionWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs params:(ZGMTRWriteParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeSubjectsPerAccessControlEntryWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeTargetsPerAccessControlEntryWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeAccessControlEntriesPerFabricWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeCommissioningARLWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeARLWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeAuxiliaryACLWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeGeneratedCommandListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeAcceptedCommandListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeAttributeListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeFeatureMapWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeClusterRevisionWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end

@interface ZGMTRClusterAccessControl (Availability)

/**
 * For all instance methods that take a completion (i.e. command invocations),
 * the completion will be called on the provided queue.
 */
- (instancetype _Nullable)initWithDevice:(ZGMTRDevice *)device
                              endpointID:(NSNumber *)endpointID
                                   queue:(dispatch_queue_t)queue ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));

@end

/**
 * Cluster Actions
 *    This cluster provides a standardized way for a Node (typically a Bridge, but could be any Node) to expose action information.
 */
ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1))
@interface ZGMTRClusterActions : ZGMTRGenericCluster

- (void)instantActionWithParams:(ZGMTRActionsClusterInstantActionParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(ZGMTRStatusCompletion)completion ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
- (void)instantActionWithTransitionWithParams:(ZGMTRActionsClusterInstantActionWithTransitionParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(ZGMTRStatusCompletion)completion ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
- (void)startActionWithParams:(ZGMTRActionsClusterStartActionParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(ZGMTRStatusCompletion)completion ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
- (void)startActionWithDurationWithParams:(ZGMTRActionsClusterStartActionWithDurationParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(ZGMTRStatusCompletion)completion ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
- (void)stopActionWithParams:(ZGMTRActionsClusterStopActionParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(ZGMTRStatusCompletion)completion ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
- (void)pauseActionWithParams:(ZGMTRActionsClusterPauseActionParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(ZGMTRStatusCompletion)completion ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
- (void)pauseActionWithDurationWithParams:(ZGMTRActionsClusterPauseActionWithDurationParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(ZGMTRStatusCompletion)completion ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
- (void)resumeActionWithParams:(ZGMTRActionsClusterResumeActionParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(ZGMTRStatusCompletion)completion ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
- (void)enableActionWithParams:(ZGMTRActionsClusterEnableActionParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(ZGMTRStatusCompletion)completion ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
- (void)enableActionWithDurationWithParams:(ZGMTRActionsClusterEnableActionWithDurationParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(ZGMTRStatusCompletion)completion ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
- (void)disableActionWithParams:(ZGMTRActionsClusterDisableActionParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(ZGMTRStatusCompletion)completion ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
- (void)disableActionWithDurationWithParams:(ZGMTRActionsClusterDisableActionWithDurationParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(ZGMTRStatusCompletion)completion ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeActionListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeEndpointListsWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeSetupURLWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeGeneratedCommandListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeAcceptedCommandListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeAttributeListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeFeatureMapWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeClusterRevisionWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end

@interface ZGMTRClusterActions (Availability)

/**
 * For all instance methods that take a completion (i.e. command invocations),
 * the completion will be called on the provided queue.
 */
- (instancetype _Nullable)initWithDevice:(ZGMTRDevice *)device
                              endpointID:(NSNumber *)endpointID
                                   queue:(dispatch_queue_t)queue ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));

@end

/**
 * Cluster Basic Information
 *    This cluster provides attributes and events for determining basic information about Nodes, which supports both
      Commissioning and operational determination of Node characteristics, such as Vendor ID, Product ID and serial number,
      which apply to the whole Node. Also allows setting user device information such as location.
 */
ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4))
@interface ZGMTRClusterBasicInformation : ZGMTRGenericCluster

- (NSDictionary<NSString *, id> * _Nullable)readAttributeDataModelRevisionWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeVendorNameWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeVendorIDWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeProductNameWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeProductIDWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeNodeLabelWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
- (void)writeAttributeNodeLabelWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
- (void)writeAttributeNodeLabelWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs params:(ZGMTRWriteParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeLocationWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
- (void)writeAttributeLocationWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
- (void)writeAttributeLocationWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs params:(ZGMTRWriteParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeHardwareVersionWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeHardwareVersionStringWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeSoftwareVersionWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeSoftwareVersionStringWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeManufacturingDateWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributePartNumberWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeProductURLWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeProductLabelWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeSerialNumberWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeLocalConfigDisabledWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
- (void)writeAttributeLocalConfigDisabledWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
- (void)writeAttributeLocalConfigDisabledWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs params:(ZGMTRWriteParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeReachableWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeUniqueIDWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeCapabilityMinimaWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeProductAppearanceWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(17.0), macos(14.0), watchos(10.0), tvos(17.0));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeSpecificationVersionWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeMaxPathsPerInvokeWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeDeviceLocationWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;
- (void)writeAttributeDeviceLocationWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs ZGMTR_PROVISIONALLY_AVAILABLE;
- (void)writeAttributeDeviceLocationWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs params:(ZGMTRWriteParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeConfigurationVersionWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeGeneratedCommandListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeAcceptedCommandListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeAttributeListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeFeatureMapWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeClusterRevisionWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end

@interface ZGMTRClusterBasicInformation (Availability)

/**
 * For all instance methods that take a completion (i.e. command invocations),
 * the completion will be called on the provided queue.
 */
- (instancetype _Nullable)initWithDevice:(ZGMTRDevice *)device
                              endpointID:(NSNumber *)endpointID
                                   queue:(dispatch_queue_t)queue ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));

@end

/**
 * Cluster OTA Software Update Provider
 *    This cluster implements the Provider role in the OTA process.
 */
ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4))
@interface ZGMTRClusterOTASoftwareUpdateProvider : ZGMTRGenericCluster

- (void)queryImageWithParams:(ZGMTROTASoftwareUpdateProviderClusterQueryImageParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(void (^)(ZGMTROTASoftwareUpdateProviderClusterQueryImageResponseParams * _Nullable data, NSError * _Nullable error))completion ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
- (void)applyUpdateRequestWithParams:(ZGMTROTASoftwareUpdateProviderClusterApplyUpdateRequestParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(void (^)(ZGMTROTASoftwareUpdateProviderClusterApplyUpdateResponseParams * _Nullable data, NSError * _Nullable error))completion ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
- (void)notifyUpdateAppliedWithParams:(ZGMTROTASoftwareUpdateProviderClusterNotifyUpdateAppliedParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(ZGMTRStatusCompletion)completion ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeGeneratedCommandListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeAcceptedCommandListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeAttributeListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeFeatureMapWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeClusterRevisionWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end

@interface ZGMTRClusterOTASoftwareUpdateProvider (Availability)

/**
 * For all instance methods that take a completion (i.e. command invocations),
 * the completion will be called on the provided queue.
 */
- (instancetype _Nullable)initWithDevice:(ZGMTRDevice *)device
                              endpointID:(NSNumber *)endpointID
                                   queue:(dispatch_queue_t)queue ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));

@end

/**
 * Cluster OTA Software Update Requestor
 *    This cluster implements the Requestor role in the OTA process.
 */
ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4))
@interface ZGMTRClusterOTASoftwareUpdateRequestor : ZGMTRGenericCluster

- (void)announceOTAProviderWithParams:(ZGMTROTASoftwareUpdateRequestorClusterAnnounceOTAProviderParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(ZGMTRStatusCompletion)completion ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeDefaultOTAProvidersWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
- (void)writeAttributeDefaultOTAProvidersWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
- (void)writeAttributeDefaultOTAProvidersWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs params:(ZGMTRWriteParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeUpdatePossibleWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeUpdateStateWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeUpdateStateProgressWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeGeneratedCommandListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeAcceptedCommandListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeAttributeListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeFeatureMapWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeClusterRevisionWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end

@interface ZGMTRClusterOTASoftwareUpdateRequestor (Availability)

/**
 * For all instance methods that take a completion (i.e. command invocations),
 * the completion will be called on the provided queue.
 */
- (instancetype _Nullable)initWithDevice:(ZGMTRDevice *)device
                              endpointID:(NSNumber *)endpointID
                                   queue:(dispatch_queue_t)queue ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));

@end

/**
 * Cluster Localization Configuration
 *    Nodes should be expected to be deployed to any and all regions of the world. These global regions
      may have differing common languages, units of measurements, and numerical formatting
      standards. As such, Nodes that visually or audibly convey information need a mechanism by which
      they can be configured to use a user’s preferred language, units, etc
 */
ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1))
@interface ZGMTRClusterLocalizationConfiguration : ZGMTRGenericCluster

- (NSDictionary<NSString *, id> * _Nullable)readAttributeActiveLocaleWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));
- (void)writeAttributeActiveLocaleWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));
- (void)writeAttributeActiveLocaleWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs params:(ZGMTRWriteParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeSupportedLocalesWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeGeneratedCommandListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeAcceptedCommandListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeAttributeListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeFeatureMapWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeClusterRevisionWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end

@interface ZGMTRClusterLocalizationConfiguration (Availability)

/**
 * The queue is currently unused, but may be used in the future for calling completions
 * for command invocations if commands are added to this cluster.
 */
- (instancetype _Nullable)initWithDevice:(ZGMTRDevice *)device
                              endpointID:(NSNumber *)endpointID
                                   queue:(dispatch_queue_t)queue ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));

@end

/**
 * Cluster Time Format Localization
 *    Nodes should be expected to be deployed to any and all regions of the world. These global regions
      may have differing preferences for how dates and times are conveyed. As such, Nodes that visually
      or audibly convey time information need a mechanism by which they can be configured to use a
      user’s preferred format.
 */
ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1))
@interface ZGMTRClusterTimeFormatLocalization : ZGMTRGenericCluster

- (NSDictionary<NSString *, id> * _Nullable)readAttributeHourFormatWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));
- (void)writeAttributeHourFormatWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));
- (void)writeAttributeHourFormatWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs params:(ZGMTRWriteParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeActiveCalendarTypeWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));
- (void)writeAttributeActiveCalendarTypeWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));
- (void)writeAttributeActiveCalendarTypeWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs params:(ZGMTRWriteParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeSupportedCalendarTypesWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeGeneratedCommandListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeAcceptedCommandListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeAttributeListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeFeatureMapWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeClusterRevisionWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end

@interface ZGMTRClusterTimeFormatLocalization (Availability)

/**
 * The queue is currently unused, but may be used in the future for calling completions
 * for command invocations if commands are added to this cluster.
 */
- (instancetype _Nullable)initWithDevice:(ZGMTRDevice *)device
                              endpointID:(NSNumber *)endpointID
                                   queue:(dispatch_queue_t)queue ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));

@end

/**
 * Cluster Unit Localization
 *    Nodes should be expected to be deployed to any and all regions of the world. These global regions
      may have differing preferences for the units in which values are conveyed in communication to a
      user. As such, Nodes that visually or audibly convey measurable values to the user need a
      mechanism by which they can be configured to use a user’s preferred unit.
 */
ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1))
@interface ZGMTRClusterUnitLocalization : ZGMTRGenericCluster

- (NSDictionary<NSString *, id> * _Nullable)readAttributeTemperatureUnitWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));
- (void)writeAttributeTemperatureUnitWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));
- (void)writeAttributeTemperatureUnitWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs params:(ZGMTRWriteParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeSupportedTemperatureUnitsWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeGeneratedCommandListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeAcceptedCommandListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeAttributeListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeFeatureMapWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeClusterRevisionWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end

@interface ZGMTRClusterUnitLocalization (Availability)

/**
 * The queue is currently unused, but may be used in the future for calling completions
 * for command invocations if commands are added to this cluster.
 */
- (instancetype _Nullable)initWithDevice:(ZGMTRDevice *)device
                              endpointID:(NSNumber *)endpointID
                                   queue:(dispatch_queue_t)queue ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));

@end

/**
 * Cluster Power Source Configuration
 *    This cluster is used to describe the configuration and capabilities of a Device's power system.
 */
ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1))
@interface ZGMTRClusterPowerSourceConfiguration : ZGMTRGenericCluster

- (NSDictionary<NSString *, id> * _Nullable)readAttributeSourcesWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeGeneratedCommandListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeAcceptedCommandListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeAttributeListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeFeatureMapWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeClusterRevisionWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end

@interface ZGMTRClusterPowerSourceConfiguration (Availability)

/**
 * The queue is currently unused, but may be used in the future for calling completions
 * for command invocations if commands are added to this cluster.
 */
- (instancetype _Nullable)initWithDevice:(ZGMTRDevice *)device
                              endpointID:(NSNumber *)endpointID
                                   queue:(dispatch_queue_t)queue ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));

@end

/**
 * Cluster Power Source
 *    This cluster is used to describe the configuration and capabilities of a physical power source that provides power to the Node.
 */
ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1))
@interface ZGMTRClusterPowerSource : ZGMTRGenericCluster

- (NSDictionary<NSString *, id> * _Nullable)readAttributeStatusWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeOrderWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeDescriptionWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeWiredAssessedInputVoltageWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeWiredAssessedInputFrequencyWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeWiredCurrentTypeWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeWiredAssessedCurrentWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeWiredNominalVoltageWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeWiredMaximumCurrentWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeWiredPresentWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeActiveWiredFaultsWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeBatVoltageWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeBatPercentRemainingWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeBatTimeRemainingWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeBatChargeLevelWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeBatReplacementNeededWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeBatReplaceabilityWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeBatPresentWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeActiveBatFaultsWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeBatReplacementDescriptionWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeBatCommonDesignationWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeBatANSIDesignationWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeBatIECDesignationWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeBatApprovedChemistryWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeBatCapacityWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeBatQuantityWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeBatChargeStateWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeBatTimeToFullChargeWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeBatFunctionalWhileChargingWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeBatChargingCurrentWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeActiveBatChargeFaultsWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeEndpointListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(17.4), macos(14.4), watchos(10.4), tvos(17.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeGeneratedCommandListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeAcceptedCommandListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeAttributeListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeFeatureMapWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeClusterRevisionWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end

@interface ZGMTRClusterPowerSource (Availability)

/**
 * The queue is currently unused, but may be used in the future for calling completions
 * for command invocations if commands are added to this cluster.
 */
- (instancetype _Nullable)initWithDevice:(ZGMTRDevice *)device
                              endpointID:(NSNumber *)endpointID
                                   queue:(dispatch_queue_t)queue ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));

@end

/**
 * Cluster General Commissioning
 *    This cluster is used to manage global aspects of the Commissioning flow.
 */
ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1))
@interface ZGMTRClusterGeneralCommissioning : ZGMTRGenericCluster

- (void)armFailSafeWithParams:(ZGMTRGeneralCommissioningClusterArmFailSafeParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(void (^)(ZGMTRGeneralCommissioningClusterArmFailSafeResponseParams * _Nullable data, NSError * _Nullable error))completion ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
- (void)setRegulatoryConfigWithParams:(ZGMTRGeneralCommissioningClusterSetRegulatoryConfigParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(void (^)(ZGMTRGeneralCommissioningClusterSetRegulatoryConfigResponseParams * _Nullable data, NSError * _Nullable error))completion ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
- (void)commissioningCompleteWithParams:(ZGMTRGeneralCommissioningClusterCommissioningCompleteParams * _Nullable)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(void (^)(ZGMTRGeneralCommissioningClusterCommissioningCompleteResponseParams * _Nullable data, NSError * _Nullable error))completion ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
- (void)commissioningCompleteWithExpectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedValues expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(void (^)(ZGMTRGeneralCommissioningClusterCommissioningCompleteResponseParams * _Nullable data, NSError * _Nullable error))completion
    ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
- (void)setTCAcknowledgementsWithParams:(ZGMTRGeneralCommissioningClusterSetTCAcknowledgementsParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(void (^)(ZGMTRGeneralCommissioningClusterSetTCAcknowledgementsResponseParams * _Nullable data, NSError * _Nullable error))completion ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeBreadcrumbWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));
- (void)writeAttributeBreadcrumbWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));
- (void)writeAttributeBreadcrumbWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs params:(ZGMTRWriteParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeBasicCommissioningInfoWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeRegulatoryConfigWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeLocationCapabilityWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeSupportsConcurrentConnectionWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeTCAcceptedVersionWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeTCMinRequiredVersionWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeTCAcknowledgementsWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeTCAcknowledgementsRequiredWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeTCUpdateDeadlineWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeRecoveryIdentifierWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeNetworkRecoveryReasonWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeIsCommissioningWithoutPowerWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeGeneratedCommandListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeAcceptedCommandListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeAttributeListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeFeatureMapWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeClusterRevisionWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end

@interface ZGMTRClusterGeneralCommissioning (Availability)

/**
 * For all instance methods that take a completion (i.e. command invocations),
 * the completion will be called on the provided queue.
 */
- (instancetype _Nullable)initWithDevice:(ZGMTRDevice *)device
                              endpointID:(NSNumber *)endpointID
                                   queue:(dispatch_queue_t)queue ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));

@end

/**
 * Cluster Network Commissioning
 *    Functionality to configure, enable, disable network credentials and access on a ZGMatter device.
 */
ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1))
@interface ZGMTRClusterNetworkCommissioning : ZGMTRGenericCluster

- (void)scanNetworksWithParams:(ZGMTRNetworkCommissioningClusterScanNetworksParams * _Nullable)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(void (^)(ZGMTRNetworkCommissioningClusterScanNetworksResponseParams * _Nullable data, NSError * _Nullable error))completion ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
- (void)scanNetworksWithExpectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedValues expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(void (^)(ZGMTRNetworkCommissioningClusterScanNetworksResponseParams * _Nullable data, NSError * _Nullable error))completion
    ZGMTR_AVAILABLE(ios(17.4), macos(14.4), watchos(10.4), tvos(17.4));
- (void)addOrUpdateWiFiNetworkWithParams:(ZGMTRNetworkCommissioningClusterAddOrUpdateWiFiNetworkParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(void (^)(ZGMTRNetworkCommissioningClusterNetworkConfigResponseParams * _Nullable data, NSError * _Nullable error))completion ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
- (void)addOrUpdateThreadNetworkWithParams:(ZGMTRNetworkCommissioningClusterAddOrUpdateThreadNetworkParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(void (^)(ZGMTRNetworkCommissioningClusterNetworkConfigResponseParams * _Nullable data, NSError * _Nullable error))completion ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
- (void)removeNetworkWithParams:(ZGMTRNetworkCommissioningClusterRemoveNetworkParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(void (^)(ZGMTRNetworkCommissioningClusterNetworkConfigResponseParams * _Nullable data, NSError * _Nullable error))completion ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
- (void)connectNetworkWithParams:(ZGMTRNetworkCommissioningClusterConnectNetworkParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(void (^)(ZGMTRNetworkCommissioningClusterConnectNetworkResponseParams * _Nullable data, NSError * _Nullable error))completion ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
- (void)reorderNetworkWithParams:(ZGMTRNetworkCommissioningClusterReorderNetworkParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(void (^)(ZGMTRNetworkCommissioningClusterNetworkConfigResponseParams * _Nullable data, NSError * _Nullable error))completion ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
- (void)queryIdentityWithParams:(ZGMTRNetworkCommissioningClusterQueryIdentityParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(void (^)(ZGMTRNetworkCommissioningClusterQueryIdentityResponseParams * _Nullable data, NSError * _Nullable error))completion ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeMaxNetworksWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeNetworksWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeScanMaxTimeSecondsWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeConnectMaxTimeSecondsWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeInterfaceEnabledWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));
- (void)writeAttributeInterfaceEnabledWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));
- (void)writeAttributeInterfaceEnabledWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs params:(ZGMTRWriteParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeLastNetworkingStatusWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeLastNetworkIDWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeLastConnectErrorValueWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeSupportedWiFiBandsWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeSupportedThreadFeaturesWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeThreadVersionWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeGeneratedCommandListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeAcceptedCommandListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeAttributeListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeFeatureMapWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeClusterRevisionWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end

@interface ZGMTRClusterNetworkCommissioning (Availability)

/**
 * For all instance methods that take a completion (i.e. command invocations),
 * the completion will be called on the provided queue.
 */
- (instancetype _Nullable)initWithDevice:(ZGMTRDevice *)device
                              endpointID:(NSNumber *)endpointID
                                   queue:(dispatch_queue_t)queue ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));

@end

/**
 * Cluster Diagnostic Logs
 *    The cluster provides commands for retrieving unstructured diagnostic logs from a Node that may be used to aid in diagnostics.
 */
ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1))
@interface ZGMTRClusterDiagnosticLogs : ZGMTRGenericCluster

- (void)retrieveLogsRequestWithParams:(ZGMTRDiagnosticLogsClusterRetrieveLogsRequestParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(void (^)(ZGMTRDiagnosticLogsClusterRetrieveLogsResponseParams * _Nullable data, NSError * _Nullable error))completion ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeGeneratedCommandListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeAcceptedCommandListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeAttributeListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeFeatureMapWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeClusterRevisionWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end

@interface ZGMTRClusterDiagnosticLogs (Availability)

/**
 * For all instance methods that take a completion (i.e. command invocations),
 * the completion will be called on the provided queue.
 */
- (instancetype _Nullable)initWithDevice:(ZGMTRDevice *)device
                              endpointID:(NSNumber *)endpointID
                                   queue:(dispatch_queue_t)queue ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));

@end

/**
 * Cluster General Diagnostics
 *    The General Diagnostics Cluster, along with other diagnostics clusters, provide a means to acquire standardized diagnostics metrics that MAY be used by a Node to assist a user or Administrative Node in diagnosing potential problems.
 */
ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1))
@interface ZGMTRClusterGeneralDiagnostics : ZGMTRGenericCluster

- (void)testEventTriggerWithParams:(ZGMTRGeneralDiagnosticsClusterTestEventTriggerParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(ZGMTRStatusCompletion)completion ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
- (void)timeSnapshotWithParams:(ZGMTRGeneralDiagnosticsClusterTimeSnapshotParams * _Nullable)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(void (^)(ZGMTRGeneralDiagnosticsClusterTimeSnapshotResponseParams * _Nullable data, NSError * _Nullable error))completion ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));
- (void)timeSnapshotWithExpectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedValues expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(void (^)(ZGMTRGeneralDiagnosticsClusterTimeSnapshotResponseParams * _Nullable data, NSError * _Nullable error))completion
    ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));
- (void)payloadTestRequestWithParams:(ZGMTRGeneralDiagnosticsClusterPayloadTestRequestParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(void (^)(ZGMTRGeneralDiagnosticsClusterPayloadTestResponseParams * _Nullable data, NSError * _Nullable error))completion ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeNetworkInterfacesWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeRebootCountWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeUpTimeWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeTotalOperationalHoursWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeBootReasonWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeActiveHardwareFaultsWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeActiveRadioFaultsWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeActiveNetworkFaultsWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeTestEventTriggersEnabledWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeDeviceLoadStatusWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeGeneratedCommandListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeAcceptedCommandListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeAttributeListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeFeatureMapWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeClusterRevisionWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end

@interface ZGMTRClusterGeneralDiagnostics (Availability)

/**
 * For all instance methods that take a completion (i.e. command invocations),
 * the completion will be called on the provided queue.
 */
- (instancetype _Nullable)initWithDevice:(ZGMTRDevice *)device
                              endpointID:(NSNumber *)endpointID
                                   queue:(dispatch_queue_t)queue ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));

@end

/**
 * Cluster Software Diagnostics
 *    The Software Diagnostics Cluster provides a means to acquire standardized diagnostics metrics that MAY be used by a Node to assist a user or Administrative Node in diagnosing potential problems.
 */
ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1))
@interface ZGMTRClusterSoftwareDiagnostics : ZGMTRGenericCluster

- (void)resetWatermarksWithParams:(ZGMTRSoftwareDiagnosticsClusterResetWatermarksParams * _Nullable)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(ZGMTRStatusCompletion)completion ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
- (void)resetWatermarksWithExpectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedValues expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(ZGMTRStatusCompletion)completion
    ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeThreadMetricsWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeCurrentHeapFreeWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeCurrentHeapUsedWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeCurrentHeapHighWatermarkWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeGeneratedCommandListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeAcceptedCommandListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeAttributeListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeFeatureMapWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeClusterRevisionWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end

@interface ZGMTRClusterSoftwareDiagnostics (Availability)

/**
 * For all instance methods that take a completion (i.e. command invocations),
 * the completion will be called on the provided queue.
 */
- (instancetype _Nullable)initWithDevice:(ZGMTRDevice *)device
                              endpointID:(NSNumber *)endpointID
                                   queue:(dispatch_queue_t)queue ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));

@end

/**
 * Cluster Thread Network Diagnostics
 *    The Thread Network Diagnostics Cluster provides a means to acquire standardized diagnostics metrics that MAY be used by a Node to assist a user or Administrative Node in diagnosing potential problems
 */
ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1))
@interface ZGMTRClusterThreadNetworkDiagnostics : ZGMTRGenericCluster

- (void)resetCountsWithParams:(ZGMTRThreadNetworkDiagnosticsClusterResetCountsParams * _Nullable)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(ZGMTRStatusCompletion)completion ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
- (void)resetCountsWithExpectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedValues expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(ZGMTRStatusCompletion)completion
    ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeChannelWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeRoutingRoleWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeNetworkNameWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributePanIdWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeExtendedPanIdWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeMeshLocalPrefixWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeOverrunCountWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeNeighborTableWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeRouteTableWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributePartitionIdWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeWeightingWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeDataVersionWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeStableDataVersionWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeLeaderRouterIdWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeDetachedRoleCountWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeChildRoleCountWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeRouterRoleCountWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeLeaderRoleCountWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeAttachAttemptCountWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributePartitionIdChangeCountWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeBetterPartitionAttachAttemptCountWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeParentChangeCountWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeTxTotalCountWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeTxUnicastCountWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeTxBroadcastCountWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeTxAckRequestedCountWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeTxAckedCountWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeTxNoAckRequestedCountWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeTxDataCountWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeTxDataPollCountWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeTxBeaconCountWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeTxBeaconRequestCountWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeTxOtherCountWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeTxRetryCountWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeTxDirectMaxRetryExpiryCountWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeTxIndirectMaxRetryExpiryCountWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeTxErrCcaCountWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeTxErrAbortCountWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeTxErrBusyChannelCountWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeRxTotalCountWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeRxUnicastCountWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeRxBroadcastCountWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeRxDataCountWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeRxDataPollCountWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeRxBeaconCountWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeRxBeaconRequestCountWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeRxOtherCountWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeRxAddressFilteredCountWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeRxDestAddrFilteredCountWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeRxDuplicatedCountWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeRxErrNoFrameCountWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeRxErrUnknownNeighborCountWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeRxErrInvalidSrcAddrCountWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeRxErrSecCountWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeRxErrFcsCountWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeRxErrOtherCountWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeActiveTimestampWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributePendingTimestampWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeDelayWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeSecurityPolicyWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeChannelPage0MaskWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeOperationalDatasetComponentsWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeActiveNetworkFaultsListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeExtAddressWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeRloc16WithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeGeneratedCommandListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeAcceptedCommandListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeAttributeListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeFeatureMapWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeClusterRevisionWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end

@interface ZGMTRClusterThreadNetworkDiagnostics (Availability)

/**
 * For all instance methods that take a completion (i.e. command invocations),
 * the completion will be called on the provided queue.
 */
- (instancetype _Nullable)initWithDevice:(ZGMTRDevice *)device
                              endpointID:(NSNumber *)endpointID
                                   queue:(dispatch_queue_t)queue ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));

@end

/**
 * Cluster Wi-Fi Network Diagnostics
 *    The Wi-Fi Network Diagnostics Cluster provides a means to acquire standardized diagnostics metrics that MAY be used by a Node to assist a user or Administrative Node in diagnosing potential problems.
 */
ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1))
@interface ZGMTRClusterWiFiNetworkDiagnostics : ZGMTRGenericCluster

- (void)resetCountsWithParams:(ZGMTRWiFiNetworkDiagnosticsClusterResetCountsParams * _Nullable)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(ZGMTRStatusCompletion)completion ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
- (void)resetCountsWithExpectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedValues expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(ZGMTRStatusCompletion)completion
    ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeBSSIDWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeSecurityTypeWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeWiFiVersionWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeChannelNumberWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeRSSIWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeBeaconLostCountWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeBeaconRxCountWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributePacketMulticastRxCountWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributePacketMulticastTxCountWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributePacketUnicastRxCountWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributePacketUnicastTxCountWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeCurrentMaxRateWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeOverrunCountWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeGeneratedCommandListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeAcceptedCommandListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeAttributeListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeFeatureMapWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeClusterRevisionWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end

@interface ZGMTRClusterWiFiNetworkDiagnostics (Availability)

/**
 * For all instance methods that take a completion (i.e. command invocations),
 * the completion will be called on the provided queue.
 */
- (instancetype _Nullable)initWithDevice:(ZGMTRDevice *)device
                              endpointID:(NSNumber *)endpointID
                                   queue:(dispatch_queue_t)queue ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));

@end

/**
 * Cluster Ethernet Network Diagnostics
 *    The Ethernet Network Diagnostics Cluster provides a means to acquire standardized diagnostics metrics that MAY be used by a Node to assist a user or Administrative Node in diagnosing potential problems.
 */
ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1))
@interface ZGMTRClusterEthernetNetworkDiagnostics : ZGMTRGenericCluster

- (void)resetCountsWithParams:(ZGMTREthernetNetworkDiagnosticsClusterResetCountsParams * _Nullable)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(ZGMTRStatusCompletion)completion ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
- (void)resetCountsWithExpectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedValues expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(ZGMTRStatusCompletion)completion
    ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributePHYRateWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeFullDuplexWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributePacketRxCountWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributePacketTxCountWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeTxErrCountWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeCollisionCountWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeOverrunCountWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeCarrierDetectWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeTimeSinceResetWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeGeneratedCommandListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeAcceptedCommandListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeAttributeListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeFeatureMapWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeClusterRevisionWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end

@interface ZGMTRClusterEthernetNetworkDiagnostics (Availability)

/**
 * For all instance methods that take a completion (i.e. command invocations),
 * the completion will be called on the provided queue.
 */
- (instancetype _Nullable)initWithDevice:(ZGMTRDevice *)device
                              endpointID:(NSNumber *)endpointID
                                   queue:(dispatch_queue_t)queue ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));

@end

/**
 * Cluster Time Synchronization
 *    Accurate time is required for a number of reasons, including scheduling, display and validating security materials.
 */
ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4))
@interface ZGMTRClusterTimeSynchronization : ZGMTRGenericCluster

- (void)setUTCTimeWithParams:(ZGMTRTimeSynchronizationClusterSetUTCTimeParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(ZGMTRStatusCompletion)completion ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));
- (void)setTrustedTimeSourceWithParams:(ZGMTRTimeSynchronizationClusterSetTrustedTimeSourceParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(ZGMTRStatusCompletion)completion ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));
- (void)setTimeZoneWithParams:(ZGMTRTimeSynchronizationClusterSetTimeZoneParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(void (^)(ZGMTRTimeSynchronizationClusterSetTimeZoneResponseParams * _Nullable data, NSError * _Nullable error))completion ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));
- (void)setDSTOffsetWithParams:(ZGMTRTimeSynchronizationClusterSetDSTOffsetParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(ZGMTRStatusCompletion)completion ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));
- (void)setDefaultNTPWithParams:(ZGMTRTimeSynchronizationClusterSetDefaultNTPParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(ZGMTRStatusCompletion)completion ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeUTCTimeWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeGranularityWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeTimeSourceWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeTrustedTimeSourceWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeDefaultNTPWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeTimeZoneWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeDSTOffsetWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeLocalTimeWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeTimeZoneDatabaseWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeNTPServerAvailableWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeTimeZoneListMaxSizeWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeDSTOffsetListMaxSizeWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeSupportsDNSResolveWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeGeneratedCommandListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeAcceptedCommandListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeAttributeListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeFeatureMapWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeClusterRevisionWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end

@interface ZGMTRClusterTimeSynchronization (Availability)

/**
 * For all instance methods that take a completion (i.e. command invocations),
 * the completion will be called on the provided queue.
 */
- (instancetype _Nullable)initWithDevice:(ZGMTRDevice *)device
                              endpointID:(NSNumber *)endpointID
                                   queue:(dispatch_queue_t)queue ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));

@end

/**
 * Cluster Bridged Device Basic Information
 *    This Cluster serves two purposes towards a Node communicating with a Bridge: indicate that the functionality on
          the Endpoint where it is placed (and its Parts) is bridged from a non-CHIP technology; and provide a centralized
          collection of attributes that the Node MAY collect to aid in conveying information regarding the Bridged Device to a user,
          such as the vendor name, the model name, or user-assigned name.
 */
ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4))
@interface ZGMTRClusterBridgedDeviceBasicInformation : ZGMTRGenericCluster

- (void)keepActiveWithParams:(ZGMTRBridgedDeviceBasicInformationClusterKeepActiveParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(ZGMTRStatusCompletion)completion ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeVendorNameWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeVendorIDWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeProductNameWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeProductIDWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeNodeLabelWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
- (void)writeAttributeNodeLabelWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
- (void)writeAttributeNodeLabelWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs params:(ZGMTRWriteParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeHardwareVersionWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeHardwareVersionStringWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeSoftwareVersionWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeSoftwareVersionStringWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeManufacturingDateWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributePartNumberWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeProductURLWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeProductLabelWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeSerialNumberWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeReachableWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeUniqueIDWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeProductAppearanceWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(17.0), macos(14.0), watchos(10.0), tvos(17.0));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeDeviceLocationWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;
- (void)writeAttributeDeviceLocationWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs ZGMTR_PROVISIONALLY_AVAILABLE;
- (void)writeAttributeDeviceLocationWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs params:(ZGMTRWriteParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeConfigurationVersionWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeGeneratedCommandListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeAcceptedCommandListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeAttributeListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeFeatureMapWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeClusterRevisionWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end

@interface ZGMTRClusterBridgedDeviceBasicInformation (Availability)

/**
 * For all instance methods that take a completion (i.e. command invocations),
 * the completion will be called on the provided queue.
 */
- (instancetype _Nullable)initWithDevice:(ZGMTRDevice *)device
                              endpointID:(NSNumber *)endpointID
                                   queue:(dispatch_queue_t)queue ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));

@end

/**
 * Cluster Switch
 *    This cluster exposes interactions with a switch device, for the purpose of using those interactions by other devices.
Two types of switch devices are supported: latching switch (e.g. rocker switch) and momentary switch (e.g. push button), distinguished with their feature flags.
Interactions with the switch device are exposed as attributes (for the latching switch) and as events (for both types of switches). An interested party MAY subscribe to these attributes/events and thus be informed of the interactions, and can perform actions based on this, for example by sending commands to perform an action such as controlling a light or a window shade.
 */
ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1))
@interface ZGMTRClusterSwitch : ZGMTRGenericCluster

- (NSDictionary<NSString *, id> * _Nullable)readAttributeNumberOfPositionsWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeCurrentPositionWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeMultiPressMaxWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeGeneratedCommandListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeAcceptedCommandListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeAttributeListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeFeatureMapWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeClusterRevisionWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end

@interface ZGMTRClusterSwitch (Availability)

/**
 * The queue is currently unused, but may be used in the future for calling completions
 * for command invocations if commands are added to this cluster.
 */
- (instancetype _Nullable)initWithDevice:(ZGMTRDevice *)device
                              endpointID:(NSNumber *)endpointID
                                   queue:(dispatch_queue_t)queue ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));

@end

/**
 * Cluster Administrator Commissioning
 *    Commands to trigger a Node to allow a new Administrator to commission it.
 */
ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1))
@interface ZGMTRClusterAdministratorCommissioning : ZGMTRGenericCluster

- (void)openCommissioningWindowWithParams:(ZGMTRAdministratorCommissioningClusterOpenCommissioningWindowParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(ZGMTRStatusCompletion)completion ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
- (void)openBasicCommissioningWindowWithParams:(ZGMTRAdministratorCommissioningClusterOpenBasicCommissioningWindowParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(ZGMTRStatusCompletion)completion ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
- (void)revokeCommissioningWithParams:(ZGMTRAdministratorCommissioningClusterRevokeCommissioningParams * _Nullable)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(ZGMTRStatusCompletion)completion ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
- (void)revokeCommissioningWithExpectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedValues expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(ZGMTRStatusCompletion)completion
    ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeWindowStatusWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeAdminFabricIndexWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeAdminVendorIdWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeGeneratedCommandListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeAcceptedCommandListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeAttributeListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeFeatureMapWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeClusterRevisionWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end

@interface ZGMTRClusterAdministratorCommissioning (Availability)

/**
 * For all instance methods that take a completion (i.e. command invocations),
 * the completion will be called on the provided queue.
 */
- (instancetype _Nullable)initWithDevice:(ZGMTRDevice *)device
                              endpointID:(NSNumber *)endpointID
                                   queue:(dispatch_queue_t)queue ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));

@end

/**
 * Cluster Operational Credentials
 *    This cluster is used to add or remove Operational Credentials on a Commissionee or Node, as well as manage the associated Fabrics.
 */
ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1))
@interface ZGMTRClusterOperationalCredentials : ZGMTRGenericCluster

- (void)attestationRequestWithParams:(ZGMTROperationalCredentialsClusterAttestationRequestParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(void (^)(ZGMTROperationalCredentialsClusterAttestationResponseParams * _Nullable data, NSError * _Nullable error))completion ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
- (void)certificateChainRequestWithParams:(ZGMTROperationalCredentialsClusterCertificateChainRequestParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(void (^)(ZGMTROperationalCredentialsClusterCertificateChainResponseParams * _Nullable data, NSError * _Nullable error))completion ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
- (void)CSRRequestWithParams:(ZGMTROperationalCredentialsClusterCSRRequestParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(void (^)(ZGMTROperationalCredentialsClusterCSRResponseParams * _Nullable data, NSError * _Nullable error))completion ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
- (void)addNOCWithParams:(ZGMTROperationalCredentialsClusterAddNOCParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(void (^)(ZGMTROperationalCredentialsClusterNOCResponseParams * _Nullable data, NSError * _Nullable error))completion ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
- (void)updateNOCWithParams:(ZGMTROperationalCredentialsClusterUpdateNOCParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(void (^)(ZGMTROperationalCredentialsClusterNOCResponseParams * _Nullable data, NSError * _Nullable error))completion ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
- (void)updateFabricLabelWithParams:(ZGMTROperationalCredentialsClusterUpdateFabricLabelParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(void (^)(ZGMTROperationalCredentialsClusterNOCResponseParams * _Nullable data, NSError * _Nullable error))completion ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
- (void)removeFabricWithParams:(ZGMTROperationalCredentialsClusterRemoveFabricParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(void (^)(ZGMTROperationalCredentialsClusterNOCResponseParams * _Nullable data, NSError * _Nullable error))completion ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
- (void)addTrustedRootCertificateWithParams:(ZGMTROperationalCredentialsClusterAddTrustedRootCertificateParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(ZGMTRStatusCompletion)completion ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
- (void)setVIDVerificationStatementWithParams:(ZGMTROperationalCredentialsClusterSetVIDVerificationStatementParams * _Nullable)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(ZGMTRStatusCompletion)completion ZGMTR_PROVISIONALLY_AVAILABLE;
- (void)setVIDVerificationStatementWithExpectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedValues expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(ZGMTRStatusCompletion)completion
    ZGMTR_PROVISIONALLY_AVAILABLE;
- (void)signVIDVerificationRequestWithParams:(ZGMTROperationalCredentialsClusterSignVIDVerificationRequestParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(void (^)(ZGMTROperationalCredentialsClusterSignVIDVerificationResponseParams * _Nullable data, NSError * _Nullable error))completion ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeNOCsWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeFabricsWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeSupportedFabricsWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeCommissionedFabricsWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeTrustedRootCertificatesWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeCurrentFabricIndexWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeGeneratedCommandListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeAcceptedCommandListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeAttributeListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeFeatureMapWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeClusterRevisionWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end

@interface ZGMTRClusterOperationalCredentials (Availability)

/**
 * For all instance methods that take a completion (i.e. command invocations),
 * the completion will be called on the provided queue.
 */
- (instancetype _Nullable)initWithDevice:(ZGMTRDevice *)device
                              endpointID:(NSNumber *)endpointID
                                   queue:(dispatch_queue_t)queue ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));

@end

/**
 * Cluster Group Key Management
 *    The Group Key Management Cluster is the mechanism by which group keys are managed.
 */
ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1))
@interface ZGMTRClusterGroupKeyManagement : ZGMTRGenericCluster

- (void)keySetWriteWithParams:(ZGMTRGroupKeyManagementClusterKeySetWriteParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(ZGMTRStatusCompletion)completion ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
- (void)keySetReadWithParams:(ZGMTRGroupKeyManagementClusterKeySetReadParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(void (^)(ZGMTRGroupKeyManagementClusterKeySetReadResponseParams * _Nullable data, NSError * _Nullable error))completion ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
- (void)keySetRemoveWithParams:(ZGMTRGroupKeyManagementClusterKeySetRemoveParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(ZGMTRStatusCompletion)completion ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
- (void)keySetReadAllIndicesWithParams:(ZGMTRGroupKeyManagementClusterKeySetReadAllIndicesParams * _Nullable)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(void (^)(ZGMTRGroupKeyManagementClusterKeySetReadAllIndicesResponseParams * _Nullable data, NSError * _Nullable error))completion ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
- (void)keySetReadAllIndicesWithExpectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedValues expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(void (^)(ZGMTRGroupKeyManagementClusterKeySetReadAllIndicesResponseParams * _Nullable data, NSError * _Nullable error))completion
    ZGMTR_AVAILABLE(ios(17.0), macos(14.0), watchos(10.0), tvos(17.0));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeGroupKeyMapWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));
- (void)writeAttributeGroupKeyMapWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));
- (void)writeAttributeGroupKeyMapWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs params:(ZGMTRWriteParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeGroupTableWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeMaxGroupsPerFabricWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeMaxGroupKeysPerFabricWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeGroupcastAdoptionWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;
- (void)writeAttributeGroupcastAdoptionWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs ZGMTR_PROVISIONALLY_AVAILABLE;
- (void)writeAttributeGroupcastAdoptionWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs params:(ZGMTRWriteParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeGeneratedCommandListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeAcceptedCommandListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeAttributeListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeFeatureMapWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeClusterRevisionWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end

@interface ZGMTRClusterGroupKeyManagement (Availability)

/**
 * For all instance methods that take a completion (i.e. command invocations),
 * the completion will be called on the provided queue.
 */
- (instancetype _Nullable)initWithDevice:(ZGMTRDevice *)device
                              endpointID:(NSNumber *)endpointID
                                   queue:(dispatch_queue_t)queue ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));

@end

/**
 * Cluster Fixed Label
 *    The Fixed Label Cluster provides a feature for the device to tag an endpoint with zero or more read only
labels.
 */
ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1))
@interface ZGMTRClusterFixedLabel : ZGMTRGenericCluster

- (NSDictionary<NSString *, id> * _Nullable)readAttributeLabelListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeGeneratedCommandListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeAcceptedCommandListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeAttributeListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeFeatureMapWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeClusterRevisionWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end

@interface ZGMTRClusterFixedLabel (Availability)

/**
 * The queue is currently unused, but may be used in the future for calling completions
 * for command invocations if commands are added to this cluster.
 */
- (instancetype _Nullable)initWithDevice:(ZGMTRDevice *)device
                              endpointID:(NSNumber *)endpointID
                                   queue:(dispatch_queue_t)queue ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));

@end

/**
 * Cluster User Label
 *    The User Label Cluster provides a feature to tag an endpoint with zero or more labels.
 */
ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1))
@interface ZGMTRClusterUserLabel : ZGMTRGenericCluster

- (NSDictionary<NSString *, id> * _Nullable)readAttributeLabelListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));
- (void)writeAttributeLabelListWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));
- (void)writeAttributeLabelListWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs params:(ZGMTRWriteParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeGeneratedCommandListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeAcceptedCommandListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeAttributeListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeFeatureMapWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeClusterRevisionWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end

@interface ZGMTRClusterUserLabel (Availability)

/**
 * The queue is currently unused, but may be used in the future for calling completions
 * for command invocations if commands are added to this cluster.
 */
- (instancetype _Nullable)initWithDevice:(ZGMTRDevice *)device
                              endpointID:(NSNumber *)endpointID
                                   queue:(dispatch_queue_t)queue ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));

@end

/**
 * Cluster Boolean State
 *    This cluster provides an interface to a boolean state called StateValue.
 */
ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1))
@interface ZGMTRClusterBooleanState : ZGMTRGenericCluster

- (NSDictionary<NSString *, id> * _Nullable)readAttributeStateValueWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeGeneratedCommandListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeAcceptedCommandListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeAttributeListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeFeatureMapWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeClusterRevisionWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end

@interface ZGMTRClusterBooleanState (Availability)

/**
 * The queue is currently unused, but may be used in the future for calling completions
 * for command invocations if commands are added to this cluster.
 */
- (instancetype _Nullable)initWithDevice:(ZGMTRDevice *)device
                              endpointID:(NSNumber *)endpointID
                                   queue:(dispatch_queue_t)queue ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));

@end

/**
 * Cluster ICD Management
 *    Allows servers to ensure that listed clients are notified when a server is available for communication.
 */
ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4))
@interface ZGMTRClusterICDManagement : ZGMTRGenericCluster

- (void)registerClientWithParams:(ZGMTRICDManagementClusterRegisterClientParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(void (^)(ZGMTRICDManagementClusterRegisterClientResponseParams * _Nullable data, NSError * _Nullable error))completion ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));
- (void)unregisterClientWithParams:(ZGMTRICDManagementClusterUnregisterClientParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(ZGMTRStatusCompletion)completion ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));
- (void)stayActiveRequestWithParams:(ZGMTRICDManagementClusterStayActiveRequestParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(void (^)(ZGMTRICDManagementClusterStayActiveResponseParams * _Nullable data, NSError * _Nullable error))completion ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeIdleModeDurationWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeActiveModeDurationWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeActiveModeThresholdWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeRegisteredClientsWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeICDCounterWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeClientsSupportedPerFabricWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeUserActiveModeTriggerHintWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeUserActiveModeTriggerInstructionWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeOperatingModeWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeMaximumCheckInBackOffWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeGeneratedCommandListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeAcceptedCommandListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeAttributeListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeFeatureMapWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeClusterRevisionWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end

@interface ZGMTRClusterICDManagement (Availability)

/**
 * For all instance methods that take a completion (i.e. command invocations),
 * the completion will be called on the provided queue.
 */
- (instancetype _Nullable)initWithDevice:(ZGMTRDevice *)device
                              endpointID:(NSNumber *)endpointID
                                   queue:(dispatch_queue_t)queue ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));

@end

/**
 * Cluster Oven Cavity Operational State
 *    This cluster supports remotely monitoring and, where supported, changing the operational state of an Oven.
 */
ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4))
@interface ZGMTRClusterOvenCavityOperationalState : ZGMTRGenericCluster

- (void)stopWithParams:(ZGMTROvenCavityOperationalStateClusterStopParams * _Nullable)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(void (^)(ZGMTROvenCavityOperationalStateClusterOperationalCommandResponseParams * _Nullable data, NSError * _Nullable error))completion ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));
- (void)stopWithExpectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedValues expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(void (^)(ZGMTROvenCavityOperationalStateClusterOperationalCommandResponseParams * _Nullable data, NSError * _Nullable error))completion
    ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));
- (void)startWithParams:(ZGMTROvenCavityOperationalStateClusterStartParams * _Nullable)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(void (^)(ZGMTROvenCavityOperationalStateClusterOperationalCommandResponseParams * _Nullable data, NSError * _Nullable error))completion ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));
- (void)startWithExpectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedValues expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(void (^)(ZGMTROvenCavityOperationalStateClusterOperationalCommandResponseParams * _Nullable data, NSError * _Nullable error))completion
    ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributePhaseListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeCurrentPhaseWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeCountdownTimeWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeOperationalStateListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeOperationalStateWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeOperationalErrorWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeGeneratedCommandListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeAcceptedCommandListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeAttributeListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeFeatureMapWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeClusterRevisionWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end

@interface ZGMTRClusterOvenCavityOperationalState (Availability)

/**
 * For all instance methods that take a completion (i.e. command invocations),
 * the completion will be called on the provided queue.
 */
- (instancetype _Nullable)initWithDevice:(ZGMTRDevice *)device
                              endpointID:(NSNumber *)endpointID
                                   queue:(dispatch_queue_t)queue ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));

@end

/**
 * Cluster Oven Mode
 *    Attributes and commands for selecting a mode from a list of supported options.
 */
ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4))
@interface ZGMTRClusterOvenMode : ZGMTRGenericCluster

- (void)changeToModeWithParams:(ZGMTROvenModeClusterChangeToModeParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(void (^)(ZGMTROvenModeClusterChangeToModeResponseParams * _Nullable data, NSError * _Nullable error))completion ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeSupportedModesWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeCurrentModeWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeGeneratedCommandListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeAcceptedCommandListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeAttributeListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeFeatureMapWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeClusterRevisionWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end

@interface ZGMTRClusterOvenMode (Availability)

/**
 * For all instance methods that take a completion (i.e. command invocations),
 * the completion will be called on the provided queue.
 */
- (instancetype _Nullable)initWithDevice:(ZGMTRDevice *)device
                              endpointID:(NSNumber *)endpointID
                                   queue:(dispatch_queue_t)queue ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));

@end

/**
 * Cluster Laundry Dryer Controls
 *    This cluster provides a way to access options associated with the operation of
            a laundry dryer device type.
 */
ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4))
@interface ZGMTRClusterLaundryDryerControls : ZGMTRGenericCluster

- (NSDictionary<NSString *, id> * _Nullable)readAttributeSupportedDrynessLevelsWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeSelectedDrynessLevelWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));
- (void)writeAttributeSelectedDrynessLevelWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));
- (void)writeAttributeSelectedDrynessLevelWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs params:(ZGMTRWriteParams * _Nullable)params ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeGeneratedCommandListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeAcceptedCommandListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeAttributeListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeFeatureMapWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeClusterRevisionWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end

@interface ZGMTRClusterLaundryDryerControls (Availability)

/**
 * The queue is currently unused, but may be used in the future for calling completions
 * for command invocations if commands are added to this cluster.
 */
- (instancetype _Nullable)initWithDevice:(ZGMTRDevice *)device
                              endpointID:(NSNumber *)endpointID
                                   queue:(dispatch_queue_t)queue ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));

@end

/**
 * Cluster Temperature Controlled Cabinet Topology
 *    This cluster provides contextual information with respect to the disablement or otherwise of Temperature Controlled Cabinet Endpoints that may be composed as part of a Device.
 */
ZGMTR_PROVISIONALLY_AVAILABLE
@interface ZGMTRClusterTemperatureControlledCabinetTopology : ZGMTRGenericCluster

- (NSDictionary<NSString *, id> * _Nullable)readAttributeDisabledCabinetsWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeTopologyWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeGeneratedCommandListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeAcceptedCommandListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeAttributeListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeFeatureMapWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeClusterRevisionWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end

@interface ZGMTRClusterTemperatureControlledCabinetTopology (Availability)

/**
 * The queue is currently unused, but may be used in the future for calling completions
 * for command invocations if commands are added to this cluster.
 */
- (instancetype _Nullable)initWithDevice:(ZGMTRDevice *)device
                              endpointID:(NSNumber *)endpointID
                                   queue:(dispatch_queue_t)queue ZGMTR_PROVISIONALLY_AVAILABLE;

@end

/**
 * Cluster Mode Select
 *    Attributes and commands for selecting a mode from a list of supported options.
 */
ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1))
@interface ZGMTRClusterModeSelect : ZGMTRGenericCluster

- (void)changeToModeWithParams:(ZGMTRModeSelectClusterChangeToModeParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(ZGMTRStatusCompletion)completion ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeDescriptionWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeStandardNamespaceWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeSupportedModesWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeCurrentModeWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeStartUpModeWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));
- (void)writeAttributeStartUpModeWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));
- (void)writeAttributeStartUpModeWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs params:(ZGMTRWriteParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeOnModeWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));
- (void)writeAttributeOnModeWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));
- (void)writeAttributeOnModeWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs params:(ZGMTRWriteParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeGeneratedCommandListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeAcceptedCommandListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeAttributeListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeFeatureMapWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeClusterRevisionWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end

@interface ZGMTRClusterModeSelect (Availability)

/**
 * For all instance methods that take a completion (i.e. command invocations),
 * the completion will be called on the provided queue.
 */
- (instancetype _Nullable)initWithDevice:(ZGMTRDevice *)device
                              endpointID:(NSNumber *)endpointID
                                   queue:(dispatch_queue_t)queue ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));

@end

/**
 * Cluster Laundry Washer Mode
 *    Attributes and commands for selecting a mode from a list of supported options.
 */
ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4))
@interface ZGMTRClusterLaundryWasherMode : ZGMTRGenericCluster

- (void)changeToModeWithParams:(ZGMTRLaundryWasherModeClusterChangeToModeParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(void (^)(ZGMTRLaundryWasherModeClusterChangeToModeResponseParams * _Nullable data, NSError * _Nullable error))completion ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeSupportedModesWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeCurrentModeWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeGeneratedCommandListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeAcceptedCommandListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeAttributeListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeFeatureMapWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeClusterRevisionWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end

@interface ZGMTRClusterLaundryWasherMode (Availability)

/**
 * For all instance methods that take a completion (i.e. command invocations),
 * the completion will be called on the provided queue.
 */
- (instancetype _Nullable)initWithDevice:(ZGMTRDevice *)device
                              endpointID:(NSNumber *)endpointID
                                   queue:(dispatch_queue_t)queue ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));

@end

/**
 * Cluster Refrigerator And Temperature Controlled Cabinet Mode
 *    Attributes and commands for selecting a mode from a list of supported options.
 */
ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4))
@interface ZGMTRClusterRefrigeratorAndTemperatureControlledCabinetMode : ZGMTRGenericCluster

- (void)changeToModeWithParams:(ZGMTRRefrigeratorAndTemperatureControlledCabinetModeClusterChangeToModeParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(void (^)(ZGMTRRefrigeratorAndTemperatureControlledCabinetModeClusterChangeToModeResponseParams * _Nullable data, NSError * _Nullable error))completion ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeSupportedModesWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeCurrentModeWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeGeneratedCommandListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeAcceptedCommandListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeAttributeListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeFeatureMapWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeClusterRevisionWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end

@interface ZGMTRClusterRefrigeratorAndTemperatureControlledCabinetMode (Availability)

/**
 * For all instance methods that take a completion (i.e. command invocations),
 * the completion will be called on the provided queue.
 */
- (instancetype _Nullable)initWithDevice:(ZGMTRDevice *)device
                              endpointID:(NSNumber *)endpointID
                                   queue:(dispatch_queue_t)queue ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));

@end

/**
 * Cluster Laundry Washer Controls
 *    This cluster supports remotely monitoring and controlling the different types of functionality available to a washing device, such as a washing machine.
 */
ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4))
@interface ZGMTRClusterLaundryWasherControls : ZGMTRGenericCluster

- (NSDictionary<NSString *, id> * _Nullable)readAttributeSpinSpeedsWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeSpinSpeedCurrentWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));
- (void)writeAttributeSpinSpeedCurrentWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));
- (void)writeAttributeSpinSpeedCurrentWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs params:(ZGMTRWriteParams * _Nullable)params ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeNumberOfRinsesWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));
- (void)writeAttributeNumberOfRinsesWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));
- (void)writeAttributeNumberOfRinsesWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs params:(ZGMTRWriteParams * _Nullable)params ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeSupportedRinsesWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeGeneratedCommandListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeAcceptedCommandListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeAttributeListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeFeatureMapWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeClusterRevisionWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end

@interface ZGMTRClusterLaundryWasherControls (Availability)

/**
 * The queue is currently unused, but may be used in the future for calling completions
 * for command invocations if commands are added to this cluster.
 */
- (instancetype _Nullable)initWithDevice:(ZGMTRDevice *)device
                              endpointID:(NSNumber *)endpointID
                                   queue:(dispatch_queue_t)queue ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));

@end

/**
 * Cluster RVC Run Mode
 *    Attributes and commands for selecting a mode from a list of supported options.
 */
ZGMTR_AVAILABLE(ios(17.4), macos(14.4), watchos(10.4), tvos(17.4))
@interface ZGMTRClusterRVCRunMode : ZGMTRGenericCluster

- (void)changeToModeWithParams:(ZGMTRRVCRunModeClusterChangeToModeParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(void (^)(ZGMTRRVCRunModeClusterChangeToModeResponseParams * _Nullable data, NSError * _Nullable error))completion ZGMTR_AVAILABLE(ios(17.4), macos(14.4), watchos(10.4), tvos(17.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeSupportedModesWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(17.4), macos(14.4), watchos(10.4), tvos(17.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeCurrentModeWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(17.4), macos(14.4), watchos(10.4), tvos(17.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeGeneratedCommandListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(17.4), macos(14.4), watchos(10.4), tvos(17.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeAcceptedCommandListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(17.4), macos(14.4), watchos(10.4), tvos(17.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeAttributeListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(17.4), macos(14.4), watchos(10.4), tvos(17.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeFeatureMapWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(17.4), macos(14.4), watchos(10.4), tvos(17.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeClusterRevisionWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(17.4), macos(14.4), watchos(10.4), tvos(17.4));

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end

@interface ZGMTRClusterRVCRunMode (Availability)

/**
 * For all instance methods that take a completion (i.e. command invocations),
 * the completion will be called on the provided queue.
 */
- (instancetype _Nullable)initWithDevice:(ZGMTRDevice *)device
                              endpointID:(NSNumber *)endpointID
                                   queue:(dispatch_queue_t)queue ZGMTR_AVAILABLE(ios(17.4), macos(14.4), watchos(10.4), tvos(17.4));

@end

/**
 * Cluster RVC Clean Mode
 *    Attributes and commands for selecting a mode from a list of supported options.
 */
ZGMTR_AVAILABLE(ios(17.4), macos(14.4), watchos(10.4), tvos(17.4))
@interface ZGMTRClusterRVCCleanMode : ZGMTRGenericCluster

- (void)changeToModeWithParams:(ZGMTRRVCCleanModeClusterChangeToModeParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(void (^)(ZGMTRRVCCleanModeClusterChangeToModeResponseParams * _Nullable data, NSError * _Nullable error))completion ZGMTR_AVAILABLE(ios(17.4), macos(14.4), watchos(10.4), tvos(17.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeSupportedModesWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(17.4), macos(14.4), watchos(10.4), tvos(17.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeCurrentModeWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(17.4), macos(14.4), watchos(10.4), tvos(17.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeGeneratedCommandListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(17.4), macos(14.4), watchos(10.4), tvos(17.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeAcceptedCommandListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(17.4), macos(14.4), watchos(10.4), tvos(17.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeAttributeListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(17.4), macos(14.4), watchos(10.4), tvos(17.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeFeatureMapWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(17.4), macos(14.4), watchos(10.4), tvos(17.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeClusterRevisionWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(17.4), macos(14.4), watchos(10.4), tvos(17.4));

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end

@interface ZGMTRClusterRVCCleanMode (Availability)

/**
 * For all instance methods that take a completion (i.e. command invocations),
 * the completion will be called on the provided queue.
 */
- (instancetype _Nullable)initWithDevice:(ZGMTRDevice *)device
                              endpointID:(NSNumber *)endpointID
                                   queue:(dispatch_queue_t)queue ZGMTR_AVAILABLE(ios(17.4), macos(14.4), watchos(10.4), tvos(17.4));

@end

/**
 * Cluster Temperature Control
 *    Attributes and commands for configuring the temperature control, and reporting temperature.
 */
ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4))
@interface ZGMTRClusterTemperatureControl : ZGMTRGenericCluster

- (void)setTemperatureWithParams:(ZGMTRTemperatureControlClusterSetTemperatureParams * _Nullable)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(ZGMTRStatusCompletion)completion ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));
- (void)setTemperatureWithExpectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedValues expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(ZGMTRStatusCompletion)completion
    ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeTemperatureSetpointWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeMinTemperatureWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeMaxTemperatureWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeStepWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeSelectedTemperatureLevelWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeSupportedTemperatureLevelsWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeGeneratedCommandListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeAcceptedCommandListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeAttributeListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeFeatureMapWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeClusterRevisionWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end

@interface ZGMTRClusterTemperatureControl (Availability)

/**
 * For all instance methods that take a completion (i.e. command invocations),
 * the completion will be called on the provided queue.
 */
- (instancetype _Nullable)initWithDevice:(ZGMTRDevice *)device
                              endpointID:(NSNumber *)endpointID
                                   queue:(dispatch_queue_t)queue ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));

@end

/**
 * Cluster Refrigerator Alarm
 *    Attributes and commands for configuring the Refrigerator alarm.
 */
ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4))
@interface ZGMTRClusterRefrigeratorAlarm : ZGMTRGenericCluster

- (NSDictionary<NSString *, id> * _Nullable)readAttributeMaskWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeStateWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeSupportedWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeGeneratedCommandListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeAcceptedCommandListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeAttributeListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeFeatureMapWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeClusterRevisionWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end

@interface ZGMTRClusterRefrigeratorAlarm (Availability)

/**
 * The queue is currently unused, but may be used in the future for calling completions
 * for command invocations if commands are added to this cluster.
 */
- (instancetype _Nullable)initWithDevice:(ZGMTRDevice *)device
                              endpointID:(NSNumber *)endpointID
                                   queue:(dispatch_queue_t)queue ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));

@end

/**
 * Cluster Dishwasher Mode
 *    Attributes and commands for selecting a mode from a list of supported options.
 */
ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4))
@interface ZGMTRClusterDishwasherMode : ZGMTRGenericCluster

- (void)changeToModeWithParams:(ZGMTRDishwasherModeClusterChangeToModeParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(void (^)(ZGMTRDishwasherModeClusterChangeToModeResponseParams * _Nullable data, NSError * _Nullable error))completion ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeSupportedModesWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeCurrentModeWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeGeneratedCommandListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeAcceptedCommandListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeAttributeListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeFeatureMapWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeClusterRevisionWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end

@interface ZGMTRClusterDishwasherMode (Availability)

/**
 * For all instance methods that take a completion (i.e. command invocations),
 * the completion will be called on the provided queue.
 */
- (instancetype _Nullable)initWithDevice:(ZGMTRDevice *)device
                              endpointID:(NSNumber *)endpointID
                                   queue:(dispatch_queue_t)queue ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));

@end

/**
 * Cluster Air Quality
 *    Attributes for reporting air quality classification
 */
ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6))
@interface ZGMTRClusterAirQuality : ZGMTRGenericCluster

- (NSDictionary<NSString *, id> * _Nullable)readAttributeAirQualityWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeGeneratedCommandListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeAcceptedCommandListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeAttributeListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeFeatureMapWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeClusterRevisionWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6));

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end

@interface ZGMTRClusterAirQuality (Availability)

/**
 * The queue is currently unused, but may be used in the future for calling completions
 * for command invocations if commands are added to this cluster.
 */
- (instancetype _Nullable)initWithDevice:(ZGMTRDevice *)device
                              endpointID:(NSNumber *)endpointID
                                   queue:(dispatch_queue_t)queue ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6));

@end

/**
 * Cluster Smoke CO Alarm
 *    This cluster provides an interface for observing and managing the state of smoke and CO alarms.
 */
ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6))
@interface ZGMTRClusterSmokeCOAlarm : ZGMTRGenericCluster

- (void)selfTestRequestWithParams:(ZGMTRSmokeCOAlarmClusterSelfTestRequestParams * _Nullable)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(ZGMTRStatusCompletion)completion ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6));
- (void)selfTestRequestWithExpectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedValues expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(ZGMTRStatusCompletion)completion
    ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeExpressedStateWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeSmokeStateWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeCOStateWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeBatteryAlertWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeDeviceMutedWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeTestInProgressWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeHardwareFaultAlertWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeEndOfServiceAlertWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeInterconnectSmokeAlarmWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeInterconnectCOAlarmWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeContaminationStateWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeSmokeSensitivityLevelWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6));
- (void)writeAttributeSmokeSensitivityLevelWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6));
- (void)writeAttributeSmokeSensitivityLevelWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs params:(ZGMTRWriteParams * _Nullable)params ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeExpiryDateWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeUnmountedWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeGeneratedCommandListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeAcceptedCommandListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeAttributeListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeFeatureMapWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeClusterRevisionWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6));

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end

@interface ZGMTRClusterSmokeCOAlarm (Availability)

/**
 * For all instance methods that take a completion (i.e. command invocations),
 * the completion will be called on the provided queue.
 */
- (instancetype _Nullable)initWithDevice:(ZGMTRDevice *)device
                              endpointID:(NSNumber *)endpointID
                                   queue:(dispatch_queue_t)queue ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6));

@end

/**
 * Cluster Dishwasher Alarm
 *    Attributes and commands for configuring the Dishwasher alarm.
 */
ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4))
@interface ZGMTRClusterDishwasherAlarm : ZGMTRGenericCluster

- (void)resetWithParams:(ZGMTRDishwasherAlarmClusterResetParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(ZGMTRStatusCompletion)completion ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));
- (void)modifyEnabledAlarmsWithParams:(ZGMTRDishwasherAlarmClusterModifyEnabledAlarmsParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(ZGMTRStatusCompletion)completion ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeMaskWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeLatchWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeStateWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeSupportedWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeGeneratedCommandListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeAcceptedCommandListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeAttributeListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeFeatureMapWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeClusterRevisionWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end

@interface ZGMTRClusterDishwasherAlarm (Availability)

/**
 * For all instance methods that take a completion (i.e. command invocations),
 * the completion will be called on the provided queue.
 */
- (instancetype _Nullable)initWithDevice:(ZGMTRDevice *)device
                              endpointID:(NSNumber *)endpointID
                                   queue:(dispatch_queue_t)queue ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));

@end

/**
 * Cluster Microwave Oven Mode
 *    Attributes and commands for selecting a mode from a list of supported options.
 */
ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4))
@interface ZGMTRClusterMicrowaveOvenMode : ZGMTRGenericCluster

- (NSDictionary<NSString *, id> * _Nullable)readAttributeSupportedModesWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeCurrentModeWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeGeneratedCommandListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeAcceptedCommandListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeAttributeListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeFeatureMapWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeClusterRevisionWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end

@interface ZGMTRClusterMicrowaveOvenMode (Availability)

/**
 * The queue is currently unused, but may be used in the future for calling completions
 * for command invocations if commands are added to this cluster.
 */
- (instancetype _Nullable)initWithDevice:(ZGMTRDevice *)device
                              endpointID:(NSNumber *)endpointID
                                   queue:(dispatch_queue_t)queue ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));

@end

/**
 * Cluster Microwave Oven Control
 *    Attributes and commands for configuring the microwave oven control, and reporting cooking stats.
 */
ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4))
@interface ZGMTRClusterMicrowaveOvenControl : ZGMTRGenericCluster

- (void)setCookingParametersWithParams:(ZGMTRMicrowaveOvenControlClusterSetCookingParametersParams * _Nullable)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(ZGMTRStatusCompletion)completion ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));
- (void)setCookingParametersWithExpectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedValues expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(ZGMTRStatusCompletion)completion
    ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));
- (void)addMoreTimeWithParams:(ZGMTRMicrowaveOvenControlClusterAddMoreTimeParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(ZGMTRStatusCompletion)completion ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeCookTimeWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeMaxCookTimeWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributePowerSettingWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeMinPowerWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeMaxPowerWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributePowerStepWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeSupportedWattsWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeSelectedWattIndexWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeWattRatingWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeGeneratedCommandListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeAcceptedCommandListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeAttributeListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeFeatureMapWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeClusterRevisionWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end

@interface ZGMTRClusterMicrowaveOvenControl (Availability)

/**
 * For all instance methods that take a completion (i.e. command invocations),
 * the completion will be called on the provided queue.
 */
- (instancetype _Nullable)initWithDevice:(ZGMTRDevice *)device
                              endpointID:(NSNumber *)endpointID
                                   queue:(dispatch_queue_t)queue ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));

@end

/**
 * Cluster Operational State
 *    This cluster supports remotely monitoring and, where supported, changing the operational state of any device where a state machine is a part of the operation.
 */
ZGMTR_AVAILABLE(ios(17.4), macos(14.4), watchos(10.4), tvos(17.4))
@interface ZGMTRClusterOperationalState : ZGMTRGenericCluster

- (void)pauseWithParams:(ZGMTROperationalStateClusterPauseParams * _Nullable)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(void (^)(ZGMTROperationalStateClusterOperationalCommandResponseParams * _Nullable data, NSError * _Nullable error))completion ZGMTR_AVAILABLE(ios(17.4), macos(14.4), watchos(10.4), tvos(17.4));
- (void)pauseWithExpectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedValues expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(void (^)(ZGMTROperationalStateClusterOperationalCommandResponseParams * _Nullable data, NSError * _Nullable error))completion
    ZGMTR_AVAILABLE(ios(17.4), macos(14.4), watchos(10.4), tvos(17.4));
- (void)stopWithParams:(ZGMTROperationalStateClusterStopParams * _Nullable)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(void (^)(ZGMTROperationalStateClusterOperationalCommandResponseParams * _Nullable data, NSError * _Nullable error))completion ZGMTR_AVAILABLE(ios(17.4), macos(14.4), watchos(10.4), tvos(17.4));
- (void)stopWithExpectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedValues expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(void (^)(ZGMTROperationalStateClusterOperationalCommandResponseParams * _Nullable data, NSError * _Nullable error))completion
    ZGMTR_AVAILABLE(ios(17.4), macos(14.4), watchos(10.4), tvos(17.4));
- (void)startWithParams:(ZGMTROperationalStateClusterStartParams * _Nullable)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(void (^)(ZGMTROperationalStateClusterOperationalCommandResponseParams * _Nullable data, NSError * _Nullable error))completion ZGMTR_AVAILABLE(ios(17.4), macos(14.4), watchos(10.4), tvos(17.4));
- (void)startWithExpectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedValues expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(void (^)(ZGMTROperationalStateClusterOperationalCommandResponseParams * _Nullable data, NSError * _Nullable error))completion
    ZGMTR_AVAILABLE(ios(17.4), macos(14.4), watchos(10.4), tvos(17.4));
- (void)resumeWithParams:(ZGMTROperationalStateClusterResumeParams * _Nullable)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(void (^)(ZGMTROperationalStateClusterOperationalCommandResponseParams * _Nullable data, NSError * _Nullable error))completion ZGMTR_AVAILABLE(ios(17.4), macos(14.4), watchos(10.4), tvos(17.4));
- (void)resumeWithExpectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedValues expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(void (^)(ZGMTROperationalStateClusterOperationalCommandResponseParams * _Nullable data, NSError * _Nullable error))completion
    ZGMTR_AVAILABLE(ios(17.4), macos(14.4), watchos(10.4), tvos(17.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributePhaseListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(17.4), macos(14.4), watchos(10.4), tvos(17.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeCurrentPhaseWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(17.4), macos(14.4), watchos(10.4), tvos(17.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeCountdownTimeWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(17.4), macos(14.4), watchos(10.4), tvos(17.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeOperationalStateListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(17.4), macos(14.4), watchos(10.4), tvos(17.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeOperationalStateWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(17.4), macos(14.4), watchos(10.4), tvos(17.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeOperationalErrorWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(17.4), macos(14.4), watchos(10.4), tvos(17.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeGeneratedCommandListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(17.4), macos(14.4), watchos(10.4), tvos(17.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeAcceptedCommandListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(17.4), macos(14.4), watchos(10.4), tvos(17.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeAttributeListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(17.4), macos(14.4), watchos(10.4), tvos(17.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeFeatureMapWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(17.4), macos(14.4), watchos(10.4), tvos(17.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeClusterRevisionWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(17.4), macos(14.4), watchos(10.4), tvos(17.4));

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end

@interface ZGMTRClusterOperationalState (Availability)

/**
 * For all instance methods that take a completion (i.e. command invocations),
 * the completion will be called on the provided queue.
 */
- (instancetype _Nullable)initWithDevice:(ZGMTRDevice *)device
                              endpointID:(NSNumber *)endpointID
                                   queue:(dispatch_queue_t)queue ZGMTR_AVAILABLE(ios(17.4), macos(14.4), watchos(10.4), tvos(17.4));

@end

/**
 * Cluster RVC Operational State
 *    This cluster supports remotely monitoring and, where supported, changing the operational state of a Robotic Vacuum.
 */
ZGMTR_AVAILABLE(ios(17.4), macos(14.4), watchos(10.4), tvos(17.4))
@interface ZGMTRClusterRVCOperationalState : ZGMTRGenericCluster

- (void)pauseWithParams:(ZGMTRRVCOperationalStateClusterPauseParams * _Nullable)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(void (^)(ZGMTRRVCOperationalStateClusterOperationalCommandResponseParams * _Nullable data, NSError * _Nullable error))completion ZGMTR_AVAILABLE(ios(17.4), macos(14.4), watchos(10.4), tvos(17.4));
- (void)pauseWithExpectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedValues expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(void (^)(ZGMTRRVCOperationalStateClusterOperationalCommandResponseParams * _Nullable data, NSError * _Nullable error))completion
    ZGMTR_AVAILABLE(ios(17.4), macos(14.4), watchos(10.4), tvos(17.4));
- (void)resumeWithParams:(ZGMTRRVCOperationalStateClusterResumeParams * _Nullable)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(void (^)(ZGMTRRVCOperationalStateClusterOperationalCommandResponseParams * _Nullable data, NSError * _Nullable error))completion ZGMTR_AVAILABLE(ios(17.4), macos(14.4), watchos(10.4), tvos(17.4));
- (void)resumeWithExpectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedValues expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(void (^)(ZGMTRRVCOperationalStateClusterOperationalCommandResponseParams * _Nullable data, NSError * _Nullable error))completion
    ZGMTR_AVAILABLE(ios(17.4), macos(14.4), watchos(10.4), tvos(17.4));
- (void)goHomeWithParams:(ZGMTRRVCOperationalStateClusterGoHomeParams * _Nullable)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(void (^)(ZGMTRRVCOperationalStateClusterOperationalCommandResponseParams * _Nullable data, NSError * _Nullable error))completion ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));
- (void)goHomeWithExpectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedValues expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(void (^)(ZGMTRRVCOperationalStateClusterOperationalCommandResponseParams * _Nullable data, NSError * _Nullable error))completion
    ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributePhaseListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(17.4), macos(14.4), watchos(10.4), tvos(17.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeCurrentPhaseWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(17.4), macos(14.4), watchos(10.4), tvos(17.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeCountdownTimeWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(17.4), macos(14.4), watchos(10.4), tvos(17.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeOperationalStateListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(17.4), macos(14.4), watchos(10.4), tvos(17.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeOperationalStateWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(17.4), macos(14.4), watchos(10.4), tvos(17.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeOperationalErrorWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(17.4), macos(14.4), watchos(10.4), tvos(17.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeGeneratedCommandListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(17.4), macos(14.4), watchos(10.4), tvos(17.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeAcceptedCommandListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(17.4), macos(14.4), watchos(10.4), tvos(17.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeAttributeListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(17.4), macos(14.4), watchos(10.4), tvos(17.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeFeatureMapWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(17.4), macos(14.4), watchos(10.4), tvos(17.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeClusterRevisionWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(17.4), macos(14.4), watchos(10.4), tvos(17.4));

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end

@interface ZGMTRClusterRVCOperationalState (Availability)

/**
 * For all instance methods that take a completion (i.e. command invocations),
 * the completion will be called on the provided queue.
 */
- (instancetype _Nullable)initWithDevice:(ZGMTRDevice *)device
                              endpointID:(NSNumber *)endpointID
                                   queue:(dispatch_queue_t)queue ZGMTR_AVAILABLE(ios(17.4), macos(14.4), watchos(10.4), tvos(17.4));

@end

/**
 * Cluster Scenes Management
 *    Attributes and commands for scene configuration and manipulation.
 */
ZGMTR_PROVISIONALLY_AVAILABLE
@interface ZGMTRClusterScenesManagement : ZGMTRGenericCluster

- (void)addSceneWithParams:(ZGMTRScenesManagementClusterAddSceneParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(void (^)(ZGMTRScenesManagementClusterAddSceneResponseParams * _Nullable data, NSError * _Nullable error))completion ZGMTR_PROVISIONALLY_AVAILABLE;
- (void)viewSceneWithParams:(ZGMTRScenesManagementClusterViewSceneParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(void (^)(ZGMTRScenesManagementClusterViewSceneResponseParams * _Nullable data, NSError * _Nullable error))completion ZGMTR_PROVISIONALLY_AVAILABLE;
- (void)removeSceneWithParams:(ZGMTRScenesManagementClusterRemoveSceneParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(void (^)(ZGMTRScenesManagementClusterRemoveSceneResponseParams * _Nullable data, NSError * _Nullable error))completion ZGMTR_PROVISIONALLY_AVAILABLE;
- (void)removeAllScenesWithParams:(ZGMTRScenesManagementClusterRemoveAllScenesParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(void (^)(ZGMTRScenesManagementClusterRemoveAllScenesResponseParams * _Nullable data, NSError * _Nullable error))completion ZGMTR_PROVISIONALLY_AVAILABLE;
- (void)storeSceneWithParams:(ZGMTRScenesManagementClusterStoreSceneParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(void (^)(ZGMTRScenesManagementClusterStoreSceneResponseParams * _Nullable data, NSError * _Nullable error))completion ZGMTR_PROVISIONALLY_AVAILABLE;
- (void)recallSceneWithParams:(ZGMTRScenesManagementClusterRecallSceneParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(ZGMTRStatusCompletion)completion ZGMTR_PROVISIONALLY_AVAILABLE;
- (void)getSceneMembershipWithParams:(ZGMTRScenesManagementClusterGetSceneMembershipParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(void (^)(ZGMTRScenesManagementClusterGetSceneMembershipResponseParams * _Nullable data, NSError * _Nullable error))completion ZGMTR_PROVISIONALLY_AVAILABLE;
- (void)copySceneWithParams:(ZGMTRScenesManagementClusterCopySceneParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(void (^)(ZGMTRScenesManagementClusterCopySceneResponseParams * _Nullable data, NSError * _Nullable error))completion ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeSceneTableSizeWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeFabricSceneInfoWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeGeneratedCommandListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeAcceptedCommandListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeAttributeListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeFeatureMapWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeClusterRevisionWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end

@interface ZGMTRClusterScenesManagement (Availability)

/**
 * For all instance methods that take a completion (i.e. command invocations),
 * the completion will be called on the provided queue.
 */
- (instancetype _Nullable)initWithDevice:(ZGMTRDevice *)device
                              endpointID:(NSNumber *)endpointID
                                   queue:(dispatch_queue_t)queue ZGMTR_PROVISIONALLY_AVAILABLE;

@end

/**
 * Cluster Groupcast
 *    The Groupcast cluster manages the content of the node-wide multicast Group membership that is part of the underlying interaction layer.
 */
ZGMTR_PROVISIONALLY_AVAILABLE
@interface ZGMTRClusterGroupcast : ZGMTRGenericCluster

- (void)joinGroupWithParams:(ZGMTRGroupcastClusterJoinGroupParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(ZGMTRStatusCompletion)completion ZGMTR_PROVISIONALLY_AVAILABLE;
- (void)leaveGroupWithParams:(ZGMTRGroupcastClusterLeaveGroupParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(void (^)(ZGMTRGroupcastClusterLeaveGroupResponseParams * _Nullable data, NSError * _Nullable error))completion ZGMTR_PROVISIONALLY_AVAILABLE;
- (void)updateGroupKeyWithParams:(ZGMTRGroupcastClusterUpdateGroupKeyParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(ZGMTRStatusCompletion)completion ZGMTR_PROVISIONALLY_AVAILABLE;
- (void)configureAuxiliaryACLWithParams:(ZGMTRGroupcastClusterConfigureAuxiliaryACLParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(ZGMTRStatusCompletion)completion ZGMTR_PROVISIONALLY_AVAILABLE;
- (void)groupcastTestingWithParams:(ZGMTRGroupcastClusterGroupcastTestingParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(ZGMTRStatusCompletion)completion ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeMembershipWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeMaxMembershipCountWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeMaxMcastAddrCountWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeUsedMcastAddrCountWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeFabricUnderTestWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeGeneratedCommandListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeAcceptedCommandListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeAttributeListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeFeatureMapWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeClusterRevisionWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end

@interface ZGMTRClusterGroupcast (Availability)

/**
 * For all instance methods that take a completion (i.e. command invocations),
 * the completion will be called on the provided queue.
 */
- (instancetype _Nullable)initWithDevice:(ZGMTRDevice *)device
                              endpointID:(NSNumber *)endpointID
                                   queue:(dispatch_queue_t)queue ZGMTR_PROVISIONALLY_AVAILABLE;

@end

/**
 * Cluster HEPA Filter Monitoring
 *    Attributes and commands for monitoring HEPA filters in a device
 */
ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6))
@interface ZGMTRClusterHEPAFilterMonitoring : ZGMTRGenericCluster

- (void)resetConditionWithParams:(ZGMTRHEPAFilterMonitoringClusterResetConditionParams * _Nullable)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(ZGMTRStatusCompletion)completion ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6));
- (void)resetConditionWithExpectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedValues expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(ZGMTRStatusCompletion)completion
    ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeConditionWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeDegradationDirectionWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeChangeIndicationWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeInPlaceIndicatorWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeLastChangedTimeWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6));
- (void)writeAttributeLastChangedTimeWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6));
- (void)writeAttributeLastChangedTimeWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs params:(ZGMTRWriteParams * _Nullable)params ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeReplacementProductListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeGeneratedCommandListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeAcceptedCommandListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeAttributeListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeFeatureMapWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeClusterRevisionWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6));

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end

@interface ZGMTRClusterHEPAFilterMonitoring (Availability)

/**
 * For all instance methods that take a completion (i.e. command invocations),
 * the completion will be called on the provided queue.
 */
- (instancetype _Nullable)initWithDevice:(ZGMTRDevice *)device
                              endpointID:(NSNumber *)endpointID
                                   queue:(dispatch_queue_t)queue ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6));

@end

/**
 * Cluster Activated Carbon Filter Monitoring
 *    Attributes and commands for monitoring activated carbon filters in a device
 */
ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6))
@interface ZGMTRClusterActivatedCarbonFilterMonitoring : ZGMTRGenericCluster

- (void)resetConditionWithParams:(ZGMTRActivatedCarbonFilterMonitoringClusterResetConditionParams * _Nullable)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(ZGMTRStatusCompletion)completion ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6));
- (void)resetConditionWithExpectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedValues expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(ZGMTRStatusCompletion)completion
    ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeConditionWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeDegradationDirectionWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeChangeIndicationWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeInPlaceIndicatorWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeLastChangedTimeWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6));
- (void)writeAttributeLastChangedTimeWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6));
- (void)writeAttributeLastChangedTimeWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs params:(ZGMTRWriteParams * _Nullable)params ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeReplacementProductListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeGeneratedCommandListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeAcceptedCommandListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeAttributeListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeFeatureMapWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeClusterRevisionWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6));

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end

@interface ZGMTRClusterActivatedCarbonFilterMonitoring (Availability)

/**
 * For all instance methods that take a completion (i.e. command invocations),
 * the completion will be called on the provided queue.
 */
- (instancetype _Nullable)initWithDevice:(ZGMTRDevice *)device
                              endpointID:(NSNumber *)endpointID
                                   queue:(dispatch_queue_t)queue ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6));

@end

/**
 * Cluster Water Tank Level Monitoring
 *    This generic cluster provides an interface to the current condition of a resource.
 */
ZGMTR_PROVISIONALLY_AVAILABLE
@interface ZGMTRClusterWaterTankLevelMonitoring : ZGMTRGenericCluster

- (void)resetConditionWithParams:(ZGMTRWaterTankLevelMonitoringClusterResetConditionParams * _Nullable)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(ZGMTRStatusCompletion)completion ZGMTR_PROVISIONALLY_AVAILABLE;
- (void)resetConditionWithExpectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedValues expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(ZGMTRStatusCompletion)completion
    ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeConditionWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeDegradationDirectionWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeChangeIndicationWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeInPlaceIndicatorWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeLastChangedTimeWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;
- (void)writeAttributeLastChangedTimeWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs ZGMTR_PROVISIONALLY_AVAILABLE;
- (void)writeAttributeLastChangedTimeWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs params:(ZGMTRWriteParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeReplacementProductListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeGeneratedCommandListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeAcceptedCommandListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeAttributeListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeFeatureMapWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeClusterRevisionWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end

@interface ZGMTRClusterWaterTankLevelMonitoring (Availability)

/**
 * For all instance methods that take a completion (i.e. command invocations),
 * the completion will be called on the provided queue.
 */
- (instancetype _Nullable)initWithDevice:(ZGMTRDevice *)device
                              endpointID:(NSNumber *)endpointID
                                   queue:(dispatch_queue_t)queue ZGMTR_PROVISIONALLY_AVAILABLE;

@end

/**
 * Cluster Boolean State Configuration
 *    This cluster is used to configure a boolean sensor.
 */
ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6))
@interface ZGMTRClusterBooleanStateConfiguration : ZGMTRGenericCluster

- (void)suppressAlarmWithParams:(ZGMTRBooleanStateConfigurationClusterSuppressAlarmParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(ZGMTRStatusCompletion)completion ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6));
- (void)enableDisableAlarmWithParams:(ZGMTRBooleanStateConfigurationClusterEnableDisableAlarmParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(ZGMTRStatusCompletion)completion ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeCurrentSensitivityLevelWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6));
- (void)writeAttributeCurrentSensitivityLevelWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6));
- (void)writeAttributeCurrentSensitivityLevelWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs params:(ZGMTRWriteParams * _Nullable)params ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeSupportedSensitivityLevelsWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeDefaultSensitivityLevelWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeAlarmsActiveWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeAlarmsSuppressedWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeAlarmsEnabledWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeAlarmsSupportedWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeSensorFaultWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeGeneratedCommandListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeAcceptedCommandListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeAttributeListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeFeatureMapWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeClusterRevisionWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6));

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end

@interface ZGMTRClusterBooleanStateConfiguration (Availability)

/**
 * For all instance methods that take a completion (i.e. command invocations),
 * the completion will be called on the provided queue.
 */
- (instancetype _Nullable)initWithDevice:(ZGMTRDevice *)device
                              endpointID:(NSNumber *)endpointID
                                   queue:(dispatch_queue_t)queue ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6));

@end

/**
 * Cluster Valve Configuration and Control
 *    This cluster is used to configure a valve.
 */
ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6))
@interface ZGMTRClusterValveConfigurationAndControl : ZGMTRGenericCluster

- (void)openWithParams:(ZGMTRValveConfigurationAndControlClusterOpenParams * _Nullable)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(ZGMTRStatusCompletion)completion ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6));
- (void)openWithExpectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedValues expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(ZGMTRStatusCompletion)completion
    ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6));
- (void)closeWithParams:(ZGMTRValveConfigurationAndControlClusterCloseParams * _Nullable)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(ZGMTRStatusCompletion)completion ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6));
- (void)closeWithExpectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedValues expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(ZGMTRStatusCompletion)completion
    ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeOpenDurationWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeDefaultOpenDurationWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6));
- (void)writeAttributeDefaultOpenDurationWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6));
- (void)writeAttributeDefaultOpenDurationWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs params:(ZGMTRWriteParams * _Nullable)params ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeAutoCloseTimeWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeRemainingDurationWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeCurrentStateWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeTargetStateWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeCurrentLevelWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeTargetLevelWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeDefaultOpenLevelWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6));
- (void)writeAttributeDefaultOpenLevelWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6));
- (void)writeAttributeDefaultOpenLevelWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs params:(ZGMTRWriteParams * _Nullable)params ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeValveFaultWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeLevelStepWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeGeneratedCommandListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeAcceptedCommandListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeAttributeListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeFeatureMapWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeClusterRevisionWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6));

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end

@interface ZGMTRClusterValveConfigurationAndControl (Availability)

/**
 * For all instance methods that take a completion (i.e. command invocations),
 * the completion will be called on the provided queue.
 */
- (instancetype _Nullable)initWithDevice:(ZGMTRDevice *)device
                              endpointID:(NSNumber *)endpointID
                                   queue:(dispatch_queue_t)queue ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6));

@end

/**
 * Cluster Electrical Power Measurement
 *    This cluster provides a mechanism for querying data about electrical power as measured by the server.
 */
ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6))
@interface ZGMTRClusterElectricalPowerMeasurement : ZGMTRGenericCluster

- (NSDictionary<NSString *, id> * _Nullable)readAttributePowerModeWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeNumberOfMeasurementTypesWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeAccuracyWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeRangesWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeVoltageWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeActiveCurrentWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeReactiveCurrentWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeApparentCurrentWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeActivePowerWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeReactivePowerWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeApparentPowerWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeRMSVoltageWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeRMSCurrentWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeRMSPowerWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeFrequencyWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeHarmonicCurrentsWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeHarmonicPhasesWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6));

- (NSDictionary<NSString *, id> * _Nullable)readAttributePowerFactorWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeNeutralCurrentWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeGeneratedCommandListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeAcceptedCommandListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeAttributeListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeFeatureMapWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeClusterRevisionWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6));

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end

@interface ZGMTRClusterElectricalPowerMeasurement (Availability)

/**
 * The queue is currently unused, but may be used in the future for calling completions
 * for command invocations if commands are added to this cluster.
 */
- (instancetype _Nullable)initWithDevice:(ZGMTRDevice *)device
                              endpointID:(NSNumber *)endpointID
                                   queue:(dispatch_queue_t)queue ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6));

@end

/**
 * Cluster Electrical Energy Measurement
 *    This cluster provides a mechanism for querying data about the electrical energy imported or provided by the server.
 */
ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6))
@interface ZGMTRClusterElectricalEnergyMeasurement : ZGMTRGenericCluster

- (NSDictionary<NSString *, id> * _Nullable)readAttributeAccuracyWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeCumulativeEnergyImportedWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeCumulativeEnergyExportedWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6));

- (NSDictionary<NSString *, id> * _Nullable)readAttributePeriodicEnergyImportedWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6));

- (NSDictionary<NSString *, id> * _Nullable)readAttributePeriodicEnergyExportedWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeCumulativeEnergyResetWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeGeneratedCommandListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeAcceptedCommandListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeAttributeListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeFeatureMapWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeClusterRevisionWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6));

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end

@interface ZGMTRClusterElectricalEnergyMeasurement (Availability)

/**
 * The queue is currently unused, but may be used in the future for calling completions
 * for command invocations if commands are added to this cluster.
 */
- (instancetype _Nullable)initWithDevice:(ZGMTRDevice *)device
                              endpointID:(NSNumber *)endpointID
                                   queue:(dispatch_queue_t)queue ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6));

@end

/**
 * Cluster Water Heater Management
 *    This cluster is used to allow clients to control the operation of a hot water heating appliance so that it can be used with energy management.
 */
ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4))
@interface ZGMTRClusterWaterHeaterManagement : ZGMTRGenericCluster

- (void)boostWithParams:(ZGMTRWaterHeaterManagementClusterBoostParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(ZGMTRStatusCompletion)completion ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));
- (void)cancelBoostWithParams:(ZGMTRWaterHeaterManagementClusterCancelBoostParams * _Nullable)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(ZGMTRStatusCompletion)completion ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));
- (void)cancelBoostWithExpectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedValues expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(ZGMTRStatusCompletion)completion
    ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeHeaterTypesWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeHeatDemandWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeTankVolumeWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeEstimatedHeatRequiredWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeTankPercentageWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeBoostStateWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeGeneratedCommandListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeAcceptedCommandListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeAttributeListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeFeatureMapWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeClusterRevisionWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end

@interface ZGMTRClusterWaterHeaterManagement (Availability)

/**
 * For all instance methods that take a completion (i.e. command invocations),
 * the completion will be called on the provided queue.
 */
- (instancetype _Nullable)initWithDevice:(ZGMTRDevice *)device
                              endpointID:(NSNumber *)endpointID
                                   queue:(dispatch_queue_t)queue ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));

@end

/**
 * Cluster Commodity Price
 *    The Commodity Price Cluster provides the mechanism for communicating Gas, Energy, or Water pricing information within the premises.
 */
ZGMTR_PROVISIONALLY_AVAILABLE
@interface ZGMTRClusterCommodityPrice : ZGMTRGenericCluster

- (void)getDetailedPriceRequestWithParams:(ZGMTRCommodityPriceClusterGetDetailedPriceRequestParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(void (^)(ZGMTRCommodityPriceClusterGetDetailedPriceResponseParams * _Nullable data, NSError * _Nullable error))completion ZGMTR_PROVISIONALLY_AVAILABLE;
- (void)getDetailedForecastRequestWithParams:(ZGMTRCommodityPriceClusterGetDetailedForecastRequestParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(void (^)(ZGMTRCommodityPriceClusterGetDetailedForecastResponseParams * _Nullable data, NSError * _Nullable error))completion ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeTariffUnitWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeCurrencyWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeCurrentPriceWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributePriceForecastWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeGeneratedCommandListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeAcceptedCommandListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeAttributeListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeFeatureMapWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeClusterRevisionWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end

@interface ZGMTRClusterCommodityPrice (Availability)

/**
 * For all instance methods that take a completion (i.e. command invocations),
 * the completion will be called on the provided queue.
 */
- (instancetype _Nullable)initWithDevice:(ZGMTRDevice *)device
                              endpointID:(NSNumber *)endpointID
                                   queue:(dispatch_queue_t)queue ZGMTR_PROVISIONALLY_AVAILABLE;

@end

/**
 * Cluster Messages
 *    This cluster provides an interface for passing messages to be presented by a device.
 */
ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4))
@interface ZGMTRClusterMessages : ZGMTRGenericCluster

- (void)presentMessagesRequestWithParams:(ZGMTRMessagesClusterPresentMessagesRequestParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(ZGMTRStatusCompletion)completion ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));
- (void)cancelMessagesRequestWithParams:(ZGMTRMessagesClusterCancelMessagesRequestParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(ZGMTRStatusCompletion)completion ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeMessagesWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeActiveMessageIDsWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeGeneratedCommandListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeAcceptedCommandListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeAttributeListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeFeatureMapWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeClusterRevisionWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end

@interface ZGMTRClusterMessages (Availability)

/**
 * For all instance methods that take a completion (i.e. command invocations),
 * the completion will be called on the provided queue.
 */
- (instancetype _Nullable)initWithDevice:(ZGMTRDevice *)device
                              endpointID:(NSNumber *)endpointID
                                   queue:(dispatch_queue_t)queue ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));

@end

/**
 * Cluster Device Energy Management
 *    This cluster allows a client to manage the power draw of a device. An example of such a client could be an Energy Management System (EMS) which controls an Energy Smart Appliance (ESA).
 */
ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4))
@interface ZGMTRClusterDeviceEnergyManagement : ZGMTRGenericCluster

- (void)powerAdjustRequestWithParams:(ZGMTRDeviceEnergyManagementClusterPowerAdjustRequestParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(ZGMTRStatusCompletion)completion ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));
- (void)cancelPowerAdjustRequestWithParams:(ZGMTRDeviceEnergyManagementClusterCancelPowerAdjustRequestParams * _Nullable)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(ZGMTRStatusCompletion)completion ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));
- (void)cancelPowerAdjustRequestWithExpectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedValues expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(ZGMTRStatusCompletion)completion
    ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));
- (void)startTimeAdjustRequestWithParams:(ZGMTRDeviceEnergyManagementClusterStartTimeAdjustRequestParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(ZGMTRStatusCompletion)completion ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));
- (void)pauseRequestWithParams:(ZGMTRDeviceEnergyManagementClusterPauseRequestParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(ZGMTRStatusCompletion)completion ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));
- (void)resumeRequestWithParams:(ZGMTRDeviceEnergyManagementClusterResumeRequestParams * _Nullable)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(ZGMTRStatusCompletion)completion ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));
- (void)resumeRequestWithExpectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedValues expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(ZGMTRStatusCompletion)completion
    ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));
- (void)modifyForecastRequestWithParams:(ZGMTRDeviceEnergyManagementClusterModifyForecastRequestParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(ZGMTRStatusCompletion)completion ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));
- (void)requestConstraintBasedForecastWithParams:(ZGMTRDeviceEnergyManagementClusterRequestConstraintBasedForecastParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(ZGMTRStatusCompletion)completion ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));
- (void)cancelRequestWithParams:(ZGMTRDeviceEnergyManagementClusterCancelRequestParams * _Nullable)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(ZGMTRStatusCompletion)completion ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));
- (void)cancelRequestWithExpectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedValues expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(ZGMTRStatusCompletion)completion
    ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));
- (void)powerRangeAdjustRequestWithParams:(ZGMTRDeviceEnergyManagementClusterPowerRangeAdjustRequestParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(ZGMTRStatusCompletion)completion ZGMTR_PROVISIONALLY_AVAILABLE;
- (void)cancelPowerRangeAdjustRequestWithParams:(ZGMTRDeviceEnergyManagementClusterCancelPowerRangeAdjustRequestParams * _Nullable)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(ZGMTRStatusCompletion)completion ZGMTR_PROVISIONALLY_AVAILABLE;
- (void)cancelPowerRangeAdjustRequestWithExpectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedValues expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(ZGMTRStatusCompletion)completion
    ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeESATypeWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeESACanGenerateWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeESAStateWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeAbsMinPowerWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeAbsMaxPowerWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributePowerAdjustmentCapabilityWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeForecastWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeOptOutStateWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributePowerRangeAdjustmentWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeGeneratedCommandListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeAcceptedCommandListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeAttributeListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeFeatureMapWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeClusterRevisionWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end

@interface ZGMTRClusterDeviceEnergyManagement (Availability)

/**
 * For all instance methods that take a completion (i.e. command invocations),
 * the completion will be called on the provided queue.
 */
- (instancetype _Nullable)initWithDevice:(ZGMTRDevice *)device
                              endpointID:(NSNumber *)endpointID
                                   queue:(dispatch_queue_t)queue ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));

@end

/**
 * Cluster Energy EVSE
 *    Electric Vehicle Supply Equipment (EVSE) is equipment used to charge an Electric Vehicle (EV) or Plug-In Hybrid Electric Vehicle. This cluster provides an interface to the functionality of Electric Vehicle Supply Equipment (EVSE) management.
 */
ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4))
@interface ZGMTRClusterEnergyEVSE : ZGMTRGenericCluster

- (void)disableWithParams:(ZGMTREnergyEVSEClusterDisableParams * _Nullable)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(ZGMTRStatusCompletion)completion ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));
- (void)disableWithExpectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedValues expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(ZGMTRStatusCompletion)completion
    ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));
- (void)enableChargingWithParams:(ZGMTREnergyEVSEClusterEnableChargingParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(ZGMTRStatusCompletion)completion ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));
- (void)enableDischargingWithParams:(ZGMTREnergyEVSEClusterEnableDischargingParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(ZGMTRStatusCompletion)completion ZGMTR_PROVISIONALLY_AVAILABLE;
- (void)startDiagnosticsWithParams:(ZGMTREnergyEVSEClusterStartDiagnosticsParams * _Nullable)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(ZGMTRStatusCompletion)completion ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));
- (void)startDiagnosticsWithExpectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedValues expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(ZGMTRStatusCompletion)completion
    ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));
- (void)setTargetsWithParams:(ZGMTREnergyEVSEClusterSetTargetsParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(ZGMTRStatusCompletion)completion ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));
- (void)getTargetsWithParams:(ZGMTREnergyEVSEClusterGetTargetsParams * _Nullable)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(void (^)(ZGMTREnergyEVSEClusterGetTargetsResponseParams * _Nullable data, NSError * _Nullable error))completion ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));
- (void)getTargetsWithExpectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedValues expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(void (^)(ZGMTREnergyEVSEClusterGetTargetsResponseParams * _Nullable data, NSError * _Nullable error))completion
    ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));
- (void)clearTargetsWithParams:(ZGMTREnergyEVSEClusterClearTargetsParams * _Nullable)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(ZGMTRStatusCompletion)completion ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));
- (void)clearTargetsWithExpectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedValues expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(ZGMTRStatusCompletion)completion
    ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeStateWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeSupplyStateWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeFaultStateWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeChargingEnabledUntilWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeDischargingEnabledUntilWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeCircuitCapacityWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeMinimumChargeCurrentWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeMaximumChargeCurrentWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeMaximumDischargeCurrentWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeUserMaximumChargeCurrentWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));
- (void)writeAttributeUserMaximumChargeCurrentWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));
- (void)writeAttributeUserMaximumChargeCurrentWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs params:(ZGMTRWriteParams * _Nullable)params ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeRandomizationDelayWindowWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));
- (void)writeAttributeRandomizationDelayWindowWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));
- (void)writeAttributeRandomizationDelayWindowWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs params:(ZGMTRWriteParams * _Nullable)params ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeNextChargeStartTimeWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeNextChargeTargetTimeWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeNextChargeRequiredEnergyWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeNextChargeTargetSoCWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeApproximateEVEfficiencyWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));
- (void)writeAttributeApproximateEVEfficiencyWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));
- (void)writeAttributeApproximateEVEfficiencyWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs params:(ZGMTRWriteParams * _Nullable)params ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeStateOfChargeWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeBatteryCapacityWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeVehicleIDWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeSessionIDWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeSessionDurationWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeSessionEnergyChargedWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeSessionEnergyDischargedWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeGeneratedCommandListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeAcceptedCommandListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeAttributeListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeFeatureMapWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeClusterRevisionWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end

@interface ZGMTRClusterEnergyEVSE (Availability)

/**
 * For all instance methods that take a completion (i.e. command invocations),
 * the completion will be called on the provided queue.
 */
- (instancetype _Nullable)initWithDevice:(ZGMTRDevice *)device
                              endpointID:(NSNumber *)endpointID
                                   queue:(dispatch_queue_t)queue ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));

@end

/**
 * Cluster Energy Preference
 *    This cluster provides an interface to specify preferences for how devices should consume energy.
 */
ZGMTR_PROVISIONALLY_AVAILABLE
@interface ZGMTRClusterEnergyPreference : ZGMTRGenericCluster

- (NSDictionary<NSString *, id> * _Nullable)readAttributeEnergyBalancesWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeCurrentEnergyBalanceWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;
- (void)writeAttributeCurrentEnergyBalanceWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs ZGMTR_PROVISIONALLY_AVAILABLE;
- (void)writeAttributeCurrentEnergyBalanceWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs params:(ZGMTRWriteParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeEnergyPrioritiesWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeLowPowerModeSensitivitiesWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeCurrentLowPowerModeSensitivityWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;
- (void)writeAttributeCurrentLowPowerModeSensitivityWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs ZGMTR_PROVISIONALLY_AVAILABLE;
- (void)writeAttributeCurrentLowPowerModeSensitivityWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs params:(ZGMTRWriteParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeGeneratedCommandListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeAcceptedCommandListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeAttributeListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeFeatureMapWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeClusterRevisionWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end

@interface ZGMTRClusterEnergyPreference (Availability)

/**
 * The queue is currently unused, but may be used in the future for calling completions
 * for command invocations if commands are added to this cluster.
 */
- (instancetype _Nullable)initWithDevice:(ZGMTRDevice *)device
                              endpointID:(NSNumber *)endpointID
                                   queue:(dispatch_queue_t)queue ZGMTR_PROVISIONALLY_AVAILABLE;

@end

/**
 * Cluster Power Topology
 *    The Power Topology Cluster provides a mechanism for expressing how power is flowing between endpoints.
 */
ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4))
@interface ZGMTRClusterPowerTopology : ZGMTRGenericCluster

- (NSDictionary<NSString *, id> * _Nullable)readAttributeAvailableEndpointsWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeActiveEndpointsWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeElectricalCircuitNodesWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;
- (void)writeAttributeElectricalCircuitNodesWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs ZGMTR_PROVISIONALLY_AVAILABLE;
- (void)writeAttributeElectricalCircuitNodesWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs params:(ZGMTRWriteParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeGeneratedCommandListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeAcceptedCommandListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeAttributeListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeFeatureMapWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeClusterRevisionWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end

@interface ZGMTRClusterPowerTopology (Availability)

/**
 * The queue is currently unused, but may be used in the future for calling completions
 * for command invocations if commands are added to this cluster.
 */
- (instancetype _Nullable)initWithDevice:(ZGMTRDevice *)device
                              endpointID:(NSNumber *)endpointID
                                   queue:(dispatch_queue_t)queue ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));

@end

/**
 * Cluster Energy EVSE Mode
 *    Attributes and commands for selecting a mode from a list of supported options.
 */
ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4))
@interface ZGMTRClusterEnergyEVSEMode : ZGMTRGenericCluster

- (void)changeToModeWithParams:(ZGMTREnergyEVSEModeClusterChangeToModeParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(void (^)(ZGMTREnergyEVSEModeClusterChangeToModeResponseParams * _Nullable data, NSError * _Nullable error))completion ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeSupportedModesWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeCurrentModeWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeGeneratedCommandListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeAcceptedCommandListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeAttributeListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeFeatureMapWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeClusterRevisionWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end

@interface ZGMTRClusterEnergyEVSEMode (Availability)

/**
 * For all instance methods that take a completion (i.e. command invocations),
 * the completion will be called on the provided queue.
 */
- (instancetype _Nullable)initWithDevice:(ZGMTRDevice *)device
                              endpointID:(NSNumber *)endpointID
                                   queue:(dispatch_queue_t)queue ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));

@end

/**
 * Cluster Water Heater Mode
 *    Attributes and commands for selecting a mode from a list of supported options.
 */
ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4))
@interface ZGMTRClusterWaterHeaterMode : ZGMTRGenericCluster

- (void)changeToModeWithParams:(ZGMTRWaterHeaterModeClusterChangeToModeParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(void (^)(ZGMTRWaterHeaterModeClusterChangeToModeResponseParams * _Nullable data, NSError * _Nullable error))completion ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeSupportedModesWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeCurrentModeWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeGeneratedCommandListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeAcceptedCommandListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeAttributeListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeFeatureMapWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeClusterRevisionWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end

@interface ZGMTRClusterWaterHeaterMode (Availability)

/**
 * For all instance methods that take a completion (i.e. command invocations),
 * the completion will be called on the provided queue.
 */
- (instancetype _Nullable)initWithDevice:(ZGMTRDevice *)device
                              endpointID:(NSNumber *)endpointID
                                   queue:(dispatch_queue_t)queue ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));

@end

/**
 * Cluster Device Energy Management Mode
 *    Attributes and commands for selecting a mode from a list of supported options.
 */
ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4))
@interface ZGMTRClusterDeviceEnergyManagementMode : ZGMTRGenericCluster

- (void)changeToModeWithParams:(ZGMTRDeviceEnergyManagementModeClusterChangeToModeParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(void (^)(ZGMTRDeviceEnergyManagementModeClusterChangeToModeResponseParams * _Nullable data, NSError * _Nullable error))completion ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeSupportedModesWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeCurrentModeWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeGeneratedCommandListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeAcceptedCommandListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeAttributeListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeFeatureMapWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeClusterRevisionWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end

@interface ZGMTRClusterDeviceEnergyManagementMode (Availability)

/**
 * For all instance methods that take a completion (i.e. command invocations),
 * the completion will be called on the provided queue.
 */
- (instancetype _Nullable)initWithDevice:(ZGMTRDevice *)device
                              endpointID:(NSNumber *)endpointID
                                   queue:(dispatch_queue_t)queue ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));

@end

/**
 * Cluster Electrical Grid Conditions
 *    The Electrical Grid Conditions Cluster provides the mechanism for communicating electricity grid carbon intensity to devices within the premises in units of Grams of CO2e per kWh.
 */
ZGMTR_PROVISIONALLY_AVAILABLE
@interface ZGMTRClusterElectricalGridConditions : ZGMTRGenericCluster

- (NSDictionary<NSString *, id> * _Nullable)readAttributeLocalGenerationAvailableWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;
- (void)writeAttributeLocalGenerationAvailableWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs ZGMTR_PROVISIONALLY_AVAILABLE;
- (void)writeAttributeLocalGenerationAvailableWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs params:(ZGMTRWriteParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeCurrentConditionsWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeForecastConditionsWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeGeneratedCommandListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeAcceptedCommandListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeAttributeListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeFeatureMapWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeClusterRevisionWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end

@interface ZGMTRClusterElectricalGridConditions (Availability)

/**
 * The queue is currently unused, but may be used in the future for calling completions
 * for command invocations if commands are added to this cluster.
 */
- (instancetype _Nullable)initWithDevice:(ZGMTRDevice *)device
                              endpointID:(NSNumber *)endpointID
                                   queue:(dispatch_queue_t)queue ZGMTR_PROVISIONALLY_AVAILABLE;

@end

/**
 * Cluster Electrical Alarm
 *    This cluster is a derived cluster of the Alarm Base cluster and provides the alarm definition related to Electrical Sensor device type.
 */
ZGMTR_PROVISIONALLY_AVAILABLE
@interface ZGMTRClusterElectricalAlarm : ZGMTRGenericCluster

- (void)resetWithParams:(ZGMTRElectricalAlarmClusterResetParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(ZGMTRStatusCompletion)completion ZGMTR_PROVISIONALLY_AVAILABLE;
- (void)modifyEnabledAlarmsWithParams:(ZGMTRElectricalAlarmClusterModifyEnabledAlarmsParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(ZGMTRStatusCompletion)completion ZGMTR_PROVISIONALLY_AVAILABLE;
- (void)setElectricalAlarmThresholdsWithParams:(ZGMTRElectricalAlarmClusterSetElectricalAlarmThresholdsParams * _Nullable)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(ZGMTRStatusCompletion)completion ZGMTR_PROVISIONALLY_AVAILABLE;
- (void)setElectricalAlarmThresholdsWithExpectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedValues expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(ZGMTRStatusCompletion)completion
    ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeMaskWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeLatchWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeStateWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeSupportedWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeOverVoltageThresholdWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeUnderVoltageThresholdWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeOverFrequencyThresholdWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeUnderFrequencyThresholdWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeOverPowerThresholdWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeUnderPowerThresholdWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeOverCurrentThresholdWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeUnderCurrentThresholdWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributePowerImportThresholdWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributePowerExportThresholdWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeGeneratedCommandListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeAcceptedCommandListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeAttributeListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeFeatureMapWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeClusterRevisionWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end

@interface ZGMTRClusterElectricalAlarm (Availability)

/**
 * For all instance methods that take a completion (i.e. command invocations),
 * the completion will be called on the provided queue.
 */
- (instancetype _Nullable)initWithDevice:(ZGMTRDevice *)device
                              endpointID:(NSNumber *)endpointID
                                   queue:(dispatch_queue_t)queue ZGMTR_PROVISIONALLY_AVAILABLE;

@end

/**
 * Cluster Electrical Distribution
 *    This cluster provides an interface for a device which distributes electrical power to other devices, providing information about the capacity of the device as well as whether it has been damaged or has reached the end of its service life.
 */
ZGMTR_PROVISIONALLY_AVAILABLE
@interface ZGMTRClusterElectricalDistribution : ZGMTRGenericCluster

- (NSDictionary<NSString *, id> * _Nullable)readAttributeMaxContinuousCurrentWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeMaxVoltageWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeNumberOfPolesWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeEndOfLifeWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeServiceEntranceRatedWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeGeneratedCommandListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeAcceptedCommandListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeAttributeListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeFeatureMapWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeClusterRevisionWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end

@interface ZGMTRClusterElectricalDistribution (Availability)

/**
 * The queue is currently unused, but may be used in the future for calling completions
 * for command invocations if commands are added to this cluster.
 */
- (instancetype _Nullable)initWithDevice:(ZGMTRDevice *)device
                              endpointID:(NSNumber *)endpointID
                                   queue:(dispatch_queue_t)queue ZGMTR_PROVISIONALLY_AVAILABLE;

@end

/**
 * Cluster Electrical Protection Alarm
 *    This cluster is a derived cluster of the Alarm Base cluster and provides the alarm definition related to the Electrical Protection device type.
 */
ZGMTR_PROVISIONALLY_AVAILABLE
@interface ZGMTRClusterElectricalProtectionAlarm : ZGMTRGenericCluster

- (void)modifyEnabledAlarmsWithParams:(ZGMTRElectricalProtectionAlarmClusterModifyEnabledAlarmsParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(ZGMTRStatusCompletion)completion ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeMaskWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeStateWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeSupportedWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeArcCauseWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeOverLoadRatingWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeOverVoltageRatingWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeSurgeProtectionRatingWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeShortCircuitRatingWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeResidualCurrentRatingWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeArcFaultRatingWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeGeneratedCommandListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeAcceptedCommandListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeAttributeListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeFeatureMapWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeClusterRevisionWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end

@interface ZGMTRClusterElectricalProtectionAlarm (Availability)

/**
 * For all instance methods that take a completion (i.e. command invocations),
 * the completion will be called on the provided queue.
 */
- (instancetype _Nullable)initWithDevice:(ZGMTRDevice *)device
                              endpointID:(NSNumber *)endpointID
                                   queue:(dispatch_queue_t)queue ZGMTR_PROVISIONALLY_AVAILABLE;

@end

/**
 * Cluster Door Lock
 *    An interface to a generic way to secure a door
 */
ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1))
@interface ZGMTRClusterDoorLock : ZGMTRGenericCluster

- (void)lockDoorWithParams:(ZGMTRDoorLockClusterLockDoorParams * _Nullable)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(ZGMTRStatusCompletion)completion ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
- (void)lockDoorWithExpectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedValues expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(ZGMTRStatusCompletion)completion
    ZGMTR_AVAILABLE(ios(17.4), macos(14.4), watchos(10.4), tvos(17.4));
- (void)unlockDoorWithParams:(ZGMTRDoorLockClusterUnlockDoorParams * _Nullable)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(ZGMTRStatusCompletion)completion ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
- (void)unlockDoorWithExpectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedValues expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(ZGMTRStatusCompletion)completion
    ZGMTR_AVAILABLE(ios(17.4), macos(14.4), watchos(10.4), tvos(17.4));
- (void)unlockWithTimeoutWithParams:(ZGMTRDoorLockClusterUnlockWithTimeoutParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(ZGMTRStatusCompletion)completion ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
- (void)setWeekDayScheduleWithParams:(ZGMTRDoorLockClusterSetWeekDayScheduleParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(ZGMTRStatusCompletion)completion ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
- (void)getWeekDayScheduleWithParams:(ZGMTRDoorLockClusterGetWeekDayScheduleParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(void (^)(ZGMTRDoorLockClusterGetWeekDayScheduleResponseParams * _Nullable data, NSError * _Nullable error))completion ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
- (void)clearWeekDayScheduleWithParams:(ZGMTRDoorLockClusterClearWeekDayScheduleParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(ZGMTRStatusCompletion)completion ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
- (void)setYearDayScheduleWithParams:(ZGMTRDoorLockClusterSetYearDayScheduleParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(ZGMTRStatusCompletion)completion ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
- (void)getYearDayScheduleWithParams:(ZGMTRDoorLockClusterGetYearDayScheduleParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(void (^)(ZGMTRDoorLockClusterGetYearDayScheduleResponseParams * _Nullable data, NSError * _Nullable error))completion ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
- (void)clearYearDayScheduleWithParams:(ZGMTRDoorLockClusterClearYearDayScheduleParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(ZGMTRStatusCompletion)completion ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
- (void)setHolidayScheduleWithParams:(ZGMTRDoorLockClusterSetHolidayScheduleParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(ZGMTRStatusCompletion)completion ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
- (void)getHolidayScheduleWithParams:(ZGMTRDoorLockClusterGetHolidayScheduleParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(void (^)(ZGMTRDoorLockClusterGetHolidayScheduleResponseParams * _Nullable data, NSError * _Nullable error))completion ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
- (void)clearHolidayScheduleWithParams:(ZGMTRDoorLockClusterClearHolidayScheduleParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(ZGMTRStatusCompletion)completion ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
- (void)setUserWithParams:(ZGMTRDoorLockClusterSetUserParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(ZGMTRStatusCompletion)completion ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
- (void)getUserWithParams:(ZGMTRDoorLockClusterGetUserParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(void (^)(ZGMTRDoorLockClusterGetUserResponseParams * _Nullable data, NSError * _Nullable error))completion ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
- (void)clearUserWithParams:(ZGMTRDoorLockClusterClearUserParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(ZGMTRStatusCompletion)completion ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
- (void)setCredentialWithParams:(ZGMTRDoorLockClusterSetCredentialParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(void (^)(ZGMTRDoorLockClusterSetCredentialResponseParams * _Nullable data, NSError * _Nullable error))completion ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
- (void)getCredentialStatusWithParams:(ZGMTRDoorLockClusterGetCredentialStatusParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(void (^)(ZGMTRDoorLockClusterGetCredentialStatusResponseParams * _Nullable data, NSError * _Nullable error))completion ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
- (void)clearCredentialWithParams:(ZGMTRDoorLockClusterClearCredentialParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(ZGMTRStatusCompletion)completion ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
- (void)unboltDoorWithParams:(ZGMTRDoorLockClusterUnboltDoorParams * _Nullable)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(ZGMTRStatusCompletion)completion ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));
- (void)unboltDoorWithExpectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedValues expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(ZGMTRStatusCompletion)completion
    ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));
- (void)setAliroReaderConfigWithParams:(ZGMTRDoorLockClusterSetAliroReaderConfigParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(ZGMTRStatusCompletion)completion ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));
- (void)clearAliroReaderConfigWithParams:(ZGMTRDoorLockClusterClearAliroReaderConfigParams * _Nullable)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(ZGMTRStatusCompletion)completion ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));
- (void)clearAliroReaderConfigWithExpectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedValues expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(ZGMTRStatusCompletion)completion
    ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeLockStateWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeLockTypeWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeActuatorEnabledWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeDoorStateWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeDoorOpenEventsWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));
- (void)writeAttributeDoorOpenEventsWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));
- (void)writeAttributeDoorOpenEventsWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs params:(ZGMTRWriteParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeDoorClosedEventsWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));
- (void)writeAttributeDoorClosedEventsWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));
- (void)writeAttributeDoorClosedEventsWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs params:(ZGMTRWriteParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeOpenPeriodWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));
- (void)writeAttributeOpenPeriodWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));
- (void)writeAttributeOpenPeriodWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs params:(ZGMTRWriteParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeNumberOfTotalUsersSupportedWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeNumberOfPINUsersSupportedWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeNumberOfRFIDUsersSupportedWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeNumberOfWeekDaySchedulesSupportedPerUserWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeNumberOfYearDaySchedulesSupportedPerUserWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeNumberOfHolidaySchedulesSupportedWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeMaxPINCodeLengthWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeMinPINCodeLengthWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeMaxRFIDCodeLengthWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeMinRFIDCodeLengthWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeCredentialRulesSupportWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeNumberOfCredentialsSupportedPerUserWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeLanguageWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));
- (void)writeAttributeLanguageWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));
- (void)writeAttributeLanguageWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs params:(ZGMTRWriteParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeLEDSettingsWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));
- (void)writeAttributeLEDSettingsWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));
- (void)writeAttributeLEDSettingsWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs params:(ZGMTRWriteParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeAutoRelockTimeWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));
- (void)writeAttributeAutoRelockTimeWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));
- (void)writeAttributeAutoRelockTimeWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs params:(ZGMTRWriteParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeSoundVolumeWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));
- (void)writeAttributeSoundVolumeWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));
- (void)writeAttributeSoundVolumeWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs params:(ZGMTRWriteParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeOperatingModeWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));
- (void)writeAttributeOperatingModeWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));
- (void)writeAttributeOperatingModeWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs params:(ZGMTRWriteParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeSupportedOperatingModesWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeDefaultConfigurationRegisterWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeEnableLocalProgrammingWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));
- (void)writeAttributeEnableLocalProgrammingWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));
- (void)writeAttributeEnableLocalProgrammingWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs params:(ZGMTRWriteParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeEnableOneTouchLockingWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));
- (void)writeAttributeEnableOneTouchLockingWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));
- (void)writeAttributeEnableOneTouchLockingWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs params:(ZGMTRWriteParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeEnableInsideStatusLEDWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));
- (void)writeAttributeEnableInsideStatusLEDWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));
- (void)writeAttributeEnableInsideStatusLEDWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs params:(ZGMTRWriteParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeEnablePrivacyModeButtonWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));
- (void)writeAttributeEnablePrivacyModeButtonWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));
- (void)writeAttributeEnablePrivacyModeButtonWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs params:(ZGMTRWriteParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeLocalProgrammingFeaturesWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));
- (void)writeAttributeLocalProgrammingFeaturesWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));
- (void)writeAttributeLocalProgrammingFeaturesWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs params:(ZGMTRWriteParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeWrongCodeEntryLimitWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));
- (void)writeAttributeWrongCodeEntryLimitWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));
- (void)writeAttributeWrongCodeEntryLimitWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs params:(ZGMTRWriteParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeUserCodeTemporaryDisableTimeWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));
- (void)writeAttributeUserCodeTemporaryDisableTimeWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));
- (void)writeAttributeUserCodeTemporaryDisableTimeWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs params:(ZGMTRWriteParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeSendPINOverTheAirWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));
- (void)writeAttributeSendPINOverTheAirWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));
- (void)writeAttributeSendPINOverTheAirWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs params:(ZGMTRWriteParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeRequirePINforRemoteOperationWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));
- (void)writeAttributeRequirePINforRemoteOperationWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));
- (void)writeAttributeRequirePINforRemoteOperationWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs params:(ZGMTRWriteParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeExpiringUserTimeoutWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));
- (void)writeAttributeExpiringUserTimeoutWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));
- (void)writeAttributeExpiringUserTimeoutWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs params:(ZGMTRWriteParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeAliroReaderVerificationKeyWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeAliroReaderGroupIdentifierWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeAliroReaderGroupSubIdentifierWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeAliroExpeditedTransactionSupportedProtocolVersionsWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeAliroGroupResolvingKeyWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeAliroSupportedBLEUWBProtocolVersionsWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeAliroBLEAdvertisingVersionWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeNumberOfAliroCredentialIssuerKeysSupportedWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeNumberOfAliroEndpointKeysSupportedWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeGeneratedCommandListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeAcceptedCommandListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeAttributeListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeFeatureMapWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeClusterRevisionWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end

@interface ZGMTRClusterDoorLock (Availability)

/**
 * For all instance methods that take a completion (i.e. command invocations),
 * the completion will be called on the provided queue.
 */
- (instancetype _Nullable)initWithDevice:(ZGMTRDevice *)device
                              endpointID:(NSNumber *)endpointID
                                   queue:(dispatch_queue_t)queue ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));

@end

/**
 * Cluster Window Covering
 *    Provides an interface for controlling and adjusting automatic window coverings.
 */
ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1))
@interface ZGMTRClusterWindowCovering : ZGMTRGenericCluster

- (void)upOrOpenWithParams:(ZGMTRWindowCoveringClusterUpOrOpenParams * _Nullable)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(ZGMTRStatusCompletion)completion ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
- (void)upOrOpenWithExpectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedValues expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(ZGMTRStatusCompletion)completion
    ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
- (void)downOrCloseWithParams:(ZGMTRWindowCoveringClusterDownOrCloseParams * _Nullable)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(ZGMTRStatusCompletion)completion ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
- (void)downOrCloseWithExpectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedValues expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(ZGMTRStatusCompletion)completion
    ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
- (void)stopMotionWithParams:(ZGMTRWindowCoveringClusterStopMotionParams * _Nullable)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(ZGMTRStatusCompletion)completion ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
- (void)stopMotionWithExpectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedValues expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(ZGMTRStatusCompletion)completion
    ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
- (void)goToLiftValueWithParams:(ZGMTRWindowCoveringClusterGoToLiftValueParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(ZGMTRStatusCompletion)completion ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
- (void)goToLiftPercentageWithParams:(ZGMTRWindowCoveringClusterGoToLiftPercentageParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(ZGMTRStatusCompletion)completion ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
- (void)goToTiltValueWithParams:(ZGMTRWindowCoveringClusterGoToTiltValueParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(ZGMTRStatusCompletion)completion ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
- (void)goToTiltPercentageWithParams:(ZGMTRWindowCoveringClusterGoToTiltPercentageParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(ZGMTRStatusCompletion)completion ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeTypeWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributePhysicalClosedLimitLiftWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributePhysicalClosedLimitTiltWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeCurrentPositionLiftWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeCurrentPositionTiltWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeNumberOfActuationsLiftWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeNumberOfActuationsTiltWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeConfigStatusWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeCurrentPositionLiftPercentageWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeCurrentPositionTiltPercentageWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeOperationalStatusWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeTargetPositionLiftPercent100thsWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeTargetPositionTiltPercent100thsWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeEndProductTypeWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeCurrentPositionLiftPercent100thsWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeCurrentPositionTiltPercent100thsWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeInstalledOpenLimitLiftWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeInstalledClosedLimitLiftWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeInstalledOpenLimitTiltWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeInstalledClosedLimitTiltWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeModeWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));
- (void)writeAttributeModeWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));
- (void)writeAttributeModeWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs params:(ZGMTRWriteParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeSafetyStatusWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeGeneratedCommandListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeAcceptedCommandListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeAttributeListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeFeatureMapWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeClusterRevisionWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end

@interface ZGMTRClusterWindowCovering (Availability)

/**
 * For all instance methods that take a completion (i.e. command invocations),
 * the completion will be called on the provided queue.
 */
- (instancetype _Nullable)initWithDevice:(ZGMTRDevice *)device
                              endpointID:(NSNumber *)endpointID
                                   queue:(dispatch_queue_t)queue ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));

@end

/**
 * Cluster Closure Control
 *    This cluster provides an interface for controlling a Closure.
 */
ZGMTR_PROVISIONALLY_AVAILABLE
@interface ZGMTRClusterClosureControl : ZGMTRGenericCluster

- (void)stopWithParams:(ZGMTRClosureControlClusterStopParams * _Nullable)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(ZGMTRStatusCompletion)completion ZGMTR_PROVISIONALLY_AVAILABLE;
- (void)stopWithExpectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedValues expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(ZGMTRStatusCompletion)completion
    ZGMTR_PROVISIONALLY_AVAILABLE;
- (void)moveToWithParams:(ZGMTRClosureControlClusterMoveToParams * _Nullable)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(ZGMTRStatusCompletion)completion ZGMTR_PROVISIONALLY_AVAILABLE;
- (void)moveToWithExpectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedValues expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(ZGMTRStatusCompletion)completion
    ZGMTR_PROVISIONALLY_AVAILABLE;
- (void)calibrateWithParams:(ZGMTRClosureControlClusterCalibrateParams * _Nullable)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(ZGMTRStatusCompletion)completion ZGMTR_PROVISIONALLY_AVAILABLE;
- (void)calibrateWithExpectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedValues expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(ZGMTRStatusCompletion)completion
    ZGMTR_PROVISIONALLY_AVAILABLE;
- (void)groupedMoveToWithParams:(ZGMTRClosureControlClusterGroupedMoveToParams * _Nullable)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(ZGMTRStatusCompletion)completion ZGMTR_PROVISIONALLY_AVAILABLE;
- (void)groupedMoveToWithExpectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedValues expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(ZGMTRStatusCompletion)completion
    ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeCountdownTimeWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeMainStateWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeCurrentErrorListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeOverallCurrentStateWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeOverallTargetStateWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeLatchControlModesWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeGeneratedCommandListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeAcceptedCommandListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeAttributeListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeFeatureMapWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeClusterRevisionWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end

@interface ZGMTRClusterClosureControl (Availability)

/**
 * For all instance methods that take a completion (i.e. command invocations),
 * the completion will be called on the provided queue.
 */
- (instancetype _Nullable)initWithDevice:(ZGMTRDevice *)device
                              endpointID:(NSNumber *)endpointID
                                   queue:(dispatch_queue_t)queue ZGMTR_PROVISIONALLY_AVAILABLE;

@end

/**
 * Cluster Closure Dimension
 *    This cluster provides an interface to reflect and control a closure's range of movement, usually involving a panel, by using 6-axis framework.
 */
ZGMTR_PROVISIONALLY_AVAILABLE
@interface ZGMTRClusterClosureDimension : ZGMTRGenericCluster

- (void)setTargetWithParams:(ZGMTRClosureDimensionClusterSetTargetParams * _Nullable)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(ZGMTRStatusCompletion)completion ZGMTR_PROVISIONALLY_AVAILABLE;
- (void)setTargetWithExpectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedValues expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(ZGMTRStatusCompletion)completion
    ZGMTR_PROVISIONALLY_AVAILABLE;
- (void)stepWithParams:(ZGMTRClosureDimensionClusterStepParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(ZGMTRStatusCompletion)completion ZGMTR_PROVISIONALLY_AVAILABLE;
- (void)groupedSetTargetWithParams:(ZGMTRClosureDimensionClusterGroupedSetTargetParams * _Nullable)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(ZGMTRStatusCompletion)completion ZGMTR_PROVISIONALLY_AVAILABLE;
- (void)groupedSetTargetWithExpectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedValues expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(ZGMTRStatusCompletion)completion
    ZGMTR_PROVISIONALLY_AVAILABLE;
- (void)groupedStepWithParams:(ZGMTRClosureDimensionClusterGroupedStepParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(ZGMTRStatusCompletion)completion ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeCurrentStateWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeTargetStateWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeResolutionWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeStepValueWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeUnitWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeUnitRangeWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeLimitRangeWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeTranslationDirectionWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeRotationAxisWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeOverflowWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeModulationTypeWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeLatchControlModesWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeGeneratedCommandListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeAcceptedCommandListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeAttributeListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeFeatureMapWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeClusterRevisionWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end

@interface ZGMTRClusterClosureDimension (Availability)

/**
 * For all instance methods that take a completion (i.e. command invocations),
 * the completion will be called on the provided queue.
 */
- (instancetype _Nullable)initWithDevice:(ZGMTRDevice *)device
                              endpointID:(NSNumber *)endpointID
                                   queue:(dispatch_queue_t)queue ZGMTR_PROVISIONALLY_AVAILABLE;

@end

/**
 * Cluster Service Area
 *    The Service Area cluster provides an interface for controlling the areas where a device should operate, and for querying the current area being serviced.
 */
ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4))
@interface ZGMTRClusterServiceArea : ZGMTRGenericCluster

- (void)selectAreasWithParams:(ZGMTRServiceAreaClusterSelectAreasParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(void (^)(ZGMTRServiceAreaClusterSelectAreasResponseParams * _Nullable data, NSError * _Nullable error))completion ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));
- (void)skipAreaWithParams:(ZGMTRServiceAreaClusterSkipAreaParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(void (^)(ZGMTRServiceAreaClusterSkipAreaResponseParams * _Nullable data, NSError * _Nullable error))completion ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeSupportedAreasWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeSupportedMapsWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeSelectedAreasWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeCurrentAreaWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeEstimatedEndTimeWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeProgressWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeGeneratedCommandListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeAcceptedCommandListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeAttributeListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeFeatureMapWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeClusterRevisionWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end

@interface ZGMTRClusterServiceArea (Availability)

/**
 * For all instance methods that take a completion (i.e. command invocations),
 * the completion will be called on the provided queue.
 */
- (instancetype _Nullable)initWithDevice:(ZGMTRDevice *)device
                              endpointID:(NSNumber *)endpointID
                                   queue:(dispatch_queue_t)queue ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));

@end

/**
 * Cluster Pump Configuration and Control
 *    An interface for configuring and controlling pumps.
 */
ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1))
@interface ZGMTRClusterPumpConfigurationAndControl : ZGMTRGenericCluster

- (NSDictionary<NSString *, id> * _Nullable)readAttributeMaxPressureWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeMaxSpeedWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeMaxFlowWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeMinConstPressureWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeMaxConstPressureWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeMinCompPressureWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeMaxCompPressureWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeMinConstSpeedWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeMaxConstSpeedWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeMinConstFlowWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeMaxConstFlowWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeMinConstTempWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeMaxConstTempWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributePumpStatusWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeEffectiveOperationModeWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeEffectiveControlModeWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeCapacityWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeSpeedWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeLifetimeRunningHoursWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));
- (void)writeAttributeLifetimeRunningHoursWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));
- (void)writeAttributeLifetimeRunningHoursWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs params:(ZGMTRWriteParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributePowerWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeLifetimeEnergyConsumedWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));
- (void)writeAttributeLifetimeEnergyConsumedWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));
- (void)writeAttributeLifetimeEnergyConsumedWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs params:(ZGMTRWriteParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeOperationModeWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));
- (void)writeAttributeOperationModeWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));
- (void)writeAttributeOperationModeWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs params:(ZGMTRWriteParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeControlModeWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));
- (void)writeAttributeControlModeWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));
- (void)writeAttributeControlModeWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs params:(ZGMTRWriteParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeGeneratedCommandListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeAcceptedCommandListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeAttributeListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeFeatureMapWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeClusterRevisionWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end

@interface ZGMTRClusterPumpConfigurationAndControl (Availability)

/**
 * The queue is currently unused, but may be used in the future for calling completions
 * for command invocations if commands are added to this cluster.
 */
- (instancetype _Nullable)initWithDevice:(ZGMTRDevice *)device
                              endpointID:(NSNumber *)endpointID
                                   queue:(dispatch_queue_t)queue ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));

@end

/**
 * Cluster Thermostat
 *    An interface for configuring and controlling the functionality of a thermostat.
 */
ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1))
@interface ZGMTRClusterThermostat : ZGMTRGenericCluster

- (void)setpointRaiseLowerWithParams:(ZGMTRThermostatClusterSetpointRaiseLowerParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(ZGMTRStatusCompletion)completion ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
- (void)setWeeklyScheduleWithParams:(ZGMTRThermostatClusterSetWeeklyScheduleParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(ZGMTRStatusCompletion)completion ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
- (void)getWeeklyScheduleWithParams:(ZGMTRThermostatClusterGetWeeklyScheduleParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(void (^)(ZGMTRThermostatClusterGetWeeklyScheduleResponseParams * _Nullable data, NSError * _Nullable error))completion ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
- (void)clearWeeklyScheduleWithParams:(ZGMTRThermostatClusterClearWeeklyScheduleParams * _Nullable)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(ZGMTRStatusCompletion)completion ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
- (void)clearWeeklyScheduleWithExpectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedValues expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(ZGMTRStatusCompletion)completion
    ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
- (void)setActiveScheduleRequestWithParams:(ZGMTRThermostatClusterSetActiveScheduleRequestParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(ZGMTRStatusCompletion)completion ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));
- (void)setActivePresetRequestWithParams:(ZGMTRThermostatClusterSetActivePresetRequestParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(ZGMTRStatusCompletion)completion ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));
- (void)addThermostatSuggestionWithParams:(ZGMTRThermostatClusterAddThermostatSuggestionParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(void (^)(ZGMTRThermostatClusterAddThermostatSuggestionResponseParams * _Nullable data, NSError * _Nullable error))completion ZGMTR_PROVISIONALLY_AVAILABLE;
- (void)removeThermostatSuggestionWithParams:(ZGMTRThermostatClusterRemoveThermostatSuggestionParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(ZGMTRStatusCompletion)completion ZGMTR_PROVISIONALLY_AVAILABLE;
- (void)atomicRequestWithParams:(ZGMTRThermostatClusterAtomicRequestParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(void (^)(ZGMTRThermostatClusterAtomicResponseParams * _Nullable data, NSError * _Nullable error))completion ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeLocalTemperatureWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeOutdoorTemperatureWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeOccupancyWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeAbsMinHeatSetpointLimitWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeAbsMaxHeatSetpointLimitWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeAbsMinCoolSetpointLimitWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeAbsMaxCoolSetpointLimitWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributePICoolingDemandWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributePIHeatingDemandWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeHVACSystemTypeConfigurationWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));
- (void)writeAttributeHVACSystemTypeConfigurationWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));
- (void)writeAttributeHVACSystemTypeConfigurationWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs params:(ZGMTRWriteParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeLocalTemperatureCalibrationWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));
- (void)writeAttributeLocalTemperatureCalibrationWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));
- (void)writeAttributeLocalTemperatureCalibrationWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs params:(ZGMTRWriteParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeOccupiedCoolingSetpointWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));
- (void)writeAttributeOccupiedCoolingSetpointWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));
- (void)writeAttributeOccupiedCoolingSetpointWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs params:(ZGMTRWriteParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeOccupiedHeatingSetpointWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));
- (void)writeAttributeOccupiedHeatingSetpointWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));
- (void)writeAttributeOccupiedHeatingSetpointWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs params:(ZGMTRWriteParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeUnoccupiedCoolingSetpointWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));
- (void)writeAttributeUnoccupiedCoolingSetpointWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));
- (void)writeAttributeUnoccupiedCoolingSetpointWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs params:(ZGMTRWriteParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeUnoccupiedHeatingSetpointWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));
- (void)writeAttributeUnoccupiedHeatingSetpointWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));
- (void)writeAttributeUnoccupiedHeatingSetpointWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs params:(ZGMTRWriteParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeMinHeatSetpointLimitWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));
- (void)writeAttributeMinHeatSetpointLimitWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));
- (void)writeAttributeMinHeatSetpointLimitWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs params:(ZGMTRWriteParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeMaxHeatSetpointLimitWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));
- (void)writeAttributeMaxHeatSetpointLimitWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));
- (void)writeAttributeMaxHeatSetpointLimitWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs params:(ZGMTRWriteParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeMinCoolSetpointLimitWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));
- (void)writeAttributeMinCoolSetpointLimitWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));
- (void)writeAttributeMinCoolSetpointLimitWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs params:(ZGMTRWriteParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeMaxCoolSetpointLimitWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));
- (void)writeAttributeMaxCoolSetpointLimitWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));
- (void)writeAttributeMaxCoolSetpointLimitWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs params:(ZGMTRWriteParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeMinSetpointDeadBandWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));
- (void)writeAttributeMinSetpointDeadBandWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));
- (void)writeAttributeMinSetpointDeadBandWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs params:(ZGMTRWriteParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeRemoteSensingWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));
- (void)writeAttributeRemoteSensingWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));
- (void)writeAttributeRemoteSensingWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs params:(ZGMTRWriteParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeControlSequenceOfOperationWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));
- (void)writeAttributeControlSequenceOfOperationWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));
- (void)writeAttributeControlSequenceOfOperationWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs params:(ZGMTRWriteParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeSystemModeWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));
- (void)writeAttributeSystemModeWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));
- (void)writeAttributeSystemModeWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs params:(ZGMTRWriteParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeThermostatRunningModeWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeStartOfWeekWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeNumberOfWeeklyTransitionsWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeNumberOfDailyTransitionsWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeTemperatureSetpointHoldWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));
- (void)writeAttributeTemperatureSetpointHoldWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));
- (void)writeAttributeTemperatureSetpointHoldWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs params:(ZGMTRWriteParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeTemperatureSetpointHoldDurationWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));
- (void)writeAttributeTemperatureSetpointHoldDurationWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));
- (void)writeAttributeTemperatureSetpointHoldDurationWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs params:(ZGMTRWriteParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeThermostatProgrammingOperationModeWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));
- (void)writeAttributeThermostatProgrammingOperationModeWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));
- (void)writeAttributeThermostatProgrammingOperationModeWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs params:(ZGMTRWriteParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeThermostatRunningStateWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeSetpointChangeSourceWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeSetpointChangeAmountWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeSetpointChangeSourceTimestampWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeOccupiedSetbackWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));
- (void)writeAttributeOccupiedSetbackWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));
- (void)writeAttributeOccupiedSetbackWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs params:(ZGMTRWriteParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeOccupiedSetbackMinWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeOccupiedSetbackMaxWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeUnoccupiedSetbackWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));
- (void)writeAttributeUnoccupiedSetbackWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));
- (void)writeAttributeUnoccupiedSetbackWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs params:(ZGMTRWriteParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeUnoccupiedSetbackMinWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeUnoccupiedSetbackMaxWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeEmergencyHeatDeltaWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));
- (void)writeAttributeEmergencyHeatDeltaWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));
- (void)writeAttributeEmergencyHeatDeltaWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs params:(ZGMTRWriteParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeACTypeWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));
- (void)writeAttributeACTypeWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));
- (void)writeAttributeACTypeWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs params:(ZGMTRWriteParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeACCapacityWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));
- (void)writeAttributeACCapacityWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));
- (void)writeAttributeACCapacityWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs params:(ZGMTRWriteParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeACRefrigerantTypeWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));
- (void)writeAttributeACRefrigerantTypeWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));
- (void)writeAttributeACRefrigerantTypeWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs params:(ZGMTRWriteParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeACCompressorTypeWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));
- (void)writeAttributeACCompressorTypeWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));
- (void)writeAttributeACCompressorTypeWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs params:(ZGMTRWriteParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeACErrorCodeWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));
- (void)writeAttributeACErrorCodeWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));
- (void)writeAttributeACErrorCodeWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs params:(ZGMTRWriteParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeACLouverPositionWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));
- (void)writeAttributeACLouverPositionWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));
- (void)writeAttributeACLouverPositionWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs params:(ZGMTRWriteParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeACCoilTemperatureWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeACCapacityformatWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));
- (void)writeAttributeACCapacityformatWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));
- (void)writeAttributeACCapacityformatWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs params:(ZGMTRWriteParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributePresetTypesWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeScheduleTypesWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeNumberOfPresetsWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeNumberOfSchedulesWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeNumberOfScheduleTransitionsWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeNumberOfScheduleTransitionPerDayWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeActivePresetHandleWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeActiveScheduleHandleWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributePresetsWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));
- (void)writeAttributePresetsWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));
- (void)writeAttributePresetsWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs params:(ZGMTRWriteParams * _Nullable)params ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeSchedulesWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));
- (void)writeAttributeSchedulesWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));
- (void)writeAttributeSchedulesWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs params:(ZGMTRWriteParams * _Nullable)params ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeSetpointHoldExpiryTimestampWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeMaxThermostatSuggestionsWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeThermostatSuggestionsWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeCurrentThermostatSuggestionWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeThermostatSuggestionNotFollowingReasonWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeGeneratedCommandListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeAcceptedCommandListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeAttributeListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeFeatureMapWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeClusterRevisionWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end

@interface ZGMTRClusterThermostat (Availability)

/**
 * For all instance methods that take a completion (i.e. command invocations),
 * the completion will be called on the provided queue.
 */
- (instancetype _Nullable)initWithDevice:(ZGMTRDevice *)device
                              endpointID:(NSNumber *)endpointID
                                   queue:(dispatch_queue_t)queue ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));

@end

/**
 * Cluster Fan Control
 *    An interface for controlling a fan in a heating/cooling system.
 */
ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1))
@interface ZGMTRClusterFanControl : ZGMTRGenericCluster

- (void)stepWithParams:(ZGMTRFanControlClusterStepParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(ZGMTRStatusCompletion)completion ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeFanModeWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));
- (void)writeAttributeFanModeWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));
- (void)writeAttributeFanModeWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs params:(ZGMTRWriteParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeFanModeSequenceWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));
- (void)writeAttributeFanModeSequenceWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));
- (void)writeAttributeFanModeSequenceWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs params:(ZGMTRWriteParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributePercentSettingWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));
- (void)writeAttributePercentSettingWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));
- (void)writeAttributePercentSettingWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs params:(ZGMTRWriteParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributePercentCurrentWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeSpeedMaxWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeSpeedSettingWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));
- (void)writeAttributeSpeedSettingWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));
- (void)writeAttributeSpeedSettingWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs params:(ZGMTRWriteParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeSpeedCurrentWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeRockSupportWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeRockSettingWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));
- (void)writeAttributeRockSettingWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));
- (void)writeAttributeRockSettingWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs params:(ZGMTRWriteParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeWindSupportWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeWindSettingWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));
- (void)writeAttributeWindSettingWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));
- (void)writeAttributeWindSettingWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs params:(ZGMTRWriteParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeAirflowDirectionWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6));
- (void)writeAttributeAirflowDirectionWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6));
- (void)writeAttributeAirflowDirectionWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs params:(ZGMTRWriteParams * _Nullable)params ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeGeneratedCommandListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeAcceptedCommandListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeAttributeListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeFeatureMapWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeClusterRevisionWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end

@interface ZGMTRClusterFanControl (Availability)

/**
 * For all instance methods that take a completion (i.e. command invocations),
 * the completion will be called on the provided queue.
 */
- (instancetype _Nullable)initWithDevice:(ZGMTRDevice *)device
                              endpointID:(NSNumber *)endpointID
                                   queue:(dispatch_queue_t)queue ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));

@end

/**
 * Cluster Thermostat User Interface Configuration
 *    An interface for configuring the user interface of a thermostat (which may be remote from the thermostat).
 */
ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1))
@interface ZGMTRClusterThermostatUserInterfaceConfiguration : ZGMTRGenericCluster

- (NSDictionary<NSString *, id> * _Nullable)readAttributeTemperatureDisplayModeWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));
- (void)writeAttributeTemperatureDisplayModeWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));
- (void)writeAttributeTemperatureDisplayModeWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs params:(ZGMTRWriteParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeKeypadLockoutWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));
- (void)writeAttributeKeypadLockoutWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));
- (void)writeAttributeKeypadLockoutWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs params:(ZGMTRWriteParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeScheduleProgrammingVisibilityWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));
- (void)writeAttributeScheduleProgrammingVisibilityWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));
- (void)writeAttributeScheduleProgrammingVisibilityWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs params:(ZGMTRWriteParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeGeneratedCommandListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeAcceptedCommandListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeAttributeListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeFeatureMapWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeClusterRevisionWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end

@interface ZGMTRClusterThermostatUserInterfaceConfiguration (Availability)

/**
 * The queue is currently unused, but may be used in the future for calling completions
 * for command invocations if commands are added to this cluster.
 */
- (instancetype _Nullable)initWithDevice:(ZGMTRDevice *)device
                              endpointID:(NSNumber *)endpointID
                                   queue:(dispatch_queue_t)queue ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));

@end

/**
 * Cluster Humidistat
 *    This cluster specifies an interface to control the humidity of an environment.
 */
ZGMTR_PROVISIONALLY_AVAILABLE
@interface ZGMTRClusterHumidistat : ZGMTRGenericCluster

- (void)setSettingsWithParams:(ZGMTRHumidistatClusterSetSettingsParams * _Nullable)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(ZGMTRStatusCompletion)completion ZGMTR_PROVISIONALLY_AVAILABLE;
- (void)setSettingsWithExpectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedValues expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(ZGMTRStatusCompletion)completion
    ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeModeWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeSystemStateWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeUserSetpointWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeMinSetpointWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeMaxSetpointWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeStepWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeTargetSetpointWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeMistTypeWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeContinuousWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeSleepWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeOptimalWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeGeneratedCommandListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeAcceptedCommandListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeAttributeListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeFeatureMapWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeClusterRevisionWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end

@interface ZGMTRClusterHumidistat (Availability)

/**
 * For all instance methods that take a completion (i.e. command invocations),
 * the completion will be called on the provided queue.
 */
- (instancetype _Nullable)initWithDevice:(ZGMTRDevice *)device
                              endpointID:(NSNumber *)endpointID
                                   queue:(dispatch_queue_t)queue ZGMTR_PROVISIONALLY_AVAILABLE;

@end

/**
 * Cluster Color Control
 *    Attributes and commands for controlling the color properties of a color-capable light.
 */
ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1))
@interface ZGMTRClusterColorControl : ZGMTRGenericCluster

- (void)moveToHueWithParams:(ZGMTRColorControlClusterMoveToHueParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(ZGMTRStatusCompletion)completion ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
- (void)moveHueWithParams:(ZGMTRColorControlClusterMoveHueParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(ZGMTRStatusCompletion)completion ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
- (void)stepHueWithParams:(ZGMTRColorControlClusterStepHueParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(ZGMTRStatusCompletion)completion ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
- (void)moveToSaturationWithParams:(ZGMTRColorControlClusterMoveToSaturationParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(ZGMTRStatusCompletion)completion ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
- (void)moveSaturationWithParams:(ZGMTRColorControlClusterMoveSaturationParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(ZGMTRStatusCompletion)completion ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
- (void)stepSaturationWithParams:(ZGMTRColorControlClusterStepSaturationParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(ZGMTRStatusCompletion)completion ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
- (void)moveToHueAndSaturationWithParams:(ZGMTRColorControlClusterMoveToHueAndSaturationParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(ZGMTRStatusCompletion)completion ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
- (void)moveToColorWithParams:(ZGMTRColorControlClusterMoveToColorParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(ZGMTRStatusCompletion)completion ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
- (void)moveColorWithParams:(ZGMTRColorControlClusterMoveColorParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(ZGMTRStatusCompletion)completion ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
- (void)stepColorWithParams:(ZGMTRColorControlClusterStepColorParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(ZGMTRStatusCompletion)completion ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
- (void)moveToColorTemperatureWithParams:(ZGMTRColorControlClusterMoveToColorTemperatureParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(ZGMTRStatusCompletion)completion ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
- (void)enhancedMoveToHueWithParams:(ZGMTRColorControlClusterEnhancedMoveToHueParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(ZGMTRStatusCompletion)completion ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
- (void)enhancedMoveHueWithParams:(ZGMTRColorControlClusterEnhancedMoveHueParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(ZGMTRStatusCompletion)completion ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
- (void)enhancedStepHueWithParams:(ZGMTRColorControlClusterEnhancedStepHueParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(ZGMTRStatusCompletion)completion ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
- (void)enhancedMoveToHueAndSaturationWithParams:(ZGMTRColorControlClusterEnhancedMoveToHueAndSaturationParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(ZGMTRStatusCompletion)completion ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
- (void)colorLoopSetWithParams:(ZGMTRColorControlClusterColorLoopSetParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(ZGMTRStatusCompletion)completion ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
- (void)stopMoveStepWithParams:(ZGMTRColorControlClusterStopMoveStepParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(ZGMTRStatusCompletion)completion ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
- (void)moveColorTemperatureWithParams:(ZGMTRColorControlClusterMoveColorTemperatureParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(ZGMTRStatusCompletion)completion ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
- (void)stepColorTemperatureWithParams:(ZGMTRColorControlClusterStepColorTemperatureParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(ZGMTRStatusCompletion)completion ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeCurrentHueWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeCurrentSaturationWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeRemainingTimeWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeCurrentXWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeCurrentYWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeDriftCompensationWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeCompensationTextWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeColorTemperatureMiredsWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeColorModeWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeOptionsWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));
- (void)writeAttributeOptionsWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));
- (void)writeAttributeOptionsWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs params:(ZGMTRWriteParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeNumberOfPrimariesWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributePrimary1XWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributePrimary1YWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributePrimary1IntensityWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributePrimary2XWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributePrimary2YWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributePrimary2IntensityWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributePrimary3XWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributePrimary3YWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributePrimary3IntensityWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributePrimary4XWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributePrimary4YWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributePrimary4IntensityWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributePrimary5XWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributePrimary5YWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributePrimary5IntensityWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributePrimary6XWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributePrimary6YWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributePrimary6IntensityWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeWhitePointXWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeWhitePointYWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeColorPointRXWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeColorPointRYWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeColorPointRIntensityWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeColorPointGXWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeColorPointGYWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeColorPointGIntensityWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeColorPointBXWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeColorPointBYWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeColorPointBIntensityWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeEnhancedCurrentHueWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeEnhancedColorModeWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeColorLoopActiveWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeColorLoopDirectionWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeColorLoopTimeWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeColorLoopStartEnhancedHueWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeColorLoopStoredEnhancedHueWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeColorCapabilitiesWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeColorTempPhysicalMinMiredsWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeColorTempPhysicalMaxMiredsWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeCoupleColorTempToLevelMinMiredsWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeStartUpColorTemperatureMiredsWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));
- (void)writeAttributeStartUpColorTemperatureMiredsWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));
- (void)writeAttributeStartUpColorTemperatureMiredsWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs params:(ZGMTRWriteParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeGeneratedCommandListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeAcceptedCommandListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeAttributeListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeFeatureMapWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeClusterRevisionWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end

@interface ZGMTRClusterColorControl (Availability)

/**
 * For all instance methods that take a completion (i.e. command invocations),
 * the completion will be called on the provided queue.
 */
- (instancetype _Nullable)initWithDevice:(ZGMTRDevice *)device
                              endpointID:(NSNumber *)endpointID
                                   queue:(dispatch_queue_t)queue ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));

@end

/**
 * Cluster Ballast Configuration
 *    Attributes and commands for configuring a lighting ballast.
 */
ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1))
@interface ZGMTRClusterBallastConfiguration : ZGMTRGenericCluster

- (NSDictionary<NSString *, id> * _Nullable)readAttributePhysicalMinLevelWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributePhysicalMaxLevelWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeBallastStatusWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeMinLevelWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));
- (void)writeAttributeMinLevelWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));
- (void)writeAttributeMinLevelWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs params:(ZGMTRWriteParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeMaxLevelWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));
- (void)writeAttributeMaxLevelWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));
- (void)writeAttributeMaxLevelWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs params:(ZGMTRWriteParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeIntrinsicBallastFactorWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
- (void)writeAttributeIntrinsicBallastFactorWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
- (void)writeAttributeIntrinsicBallastFactorWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs params:(ZGMTRWriteParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeBallastFactorAdjustmentWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));
- (void)writeAttributeBallastFactorAdjustmentWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));
- (void)writeAttributeBallastFactorAdjustmentWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs params:(ZGMTRWriteParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeLampQuantityWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeLampTypeWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));
- (void)writeAttributeLampTypeWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));
- (void)writeAttributeLampTypeWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs params:(ZGMTRWriteParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeLampManufacturerWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));
- (void)writeAttributeLampManufacturerWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));
- (void)writeAttributeLampManufacturerWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs params:(ZGMTRWriteParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeLampRatedHoursWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));
- (void)writeAttributeLampRatedHoursWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));
- (void)writeAttributeLampRatedHoursWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs params:(ZGMTRWriteParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeLampBurnHoursWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));
- (void)writeAttributeLampBurnHoursWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));
- (void)writeAttributeLampBurnHoursWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs params:(ZGMTRWriteParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeLampAlarmModeWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));
- (void)writeAttributeLampAlarmModeWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));
- (void)writeAttributeLampAlarmModeWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs params:(ZGMTRWriteParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeLampBurnHoursTripPointWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));
- (void)writeAttributeLampBurnHoursTripPointWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));
- (void)writeAttributeLampBurnHoursTripPointWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs params:(ZGMTRWriteParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeGeneratedCommandListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeAcceptedCommandListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeAttributeListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeFeatureMapWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeClusterRevisionWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end

@interface ZGMTRClusterBallastConfiguration (Availability)

/**
 * The queue is currently unused, but may be used in the future for calling completions
 * for command invocations if commands are added to this cluster.
 */
- (instancetype _Nullable)initWithDevice:(ZGMTRDevice *)device
                              endpointID:(NSNumber *)endpointID
                                   queue:(dispatch_queue_t)queue ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));

@end

/**
 * Cluster Dynamic Lighting
 *    This cluster provides a means to activate and control dynamic lighting effects on a light.
 */
ZGMTR_PROVISIONALLY_AVAILABLE
@interface ZGMTRClusterDynamicLighting : ZGMTRGenericCluster

- (void)startEffectWithParams:(ZGMTRDynamicLightingClusterStartEffectParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(ZGMTRStatusCompletion)completion ZGMTR_PROVISIONALLY_AVAILABLE;
- (void)stopEffectWithParams:(ZGMTRDynamicLightingClusterStopEffectParams * _Nullable)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(ZGMTRStatusCompletion)completion ZGMTR_PROVISIONALLY_AVAILABLE;
- (void)stopEffectWithExpectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedValues expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(ZGMTRStatusCompletion)completion
    ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeAvailableEffectsWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeCurrentEffectIDWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeCurrentSpeedWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;
- (void)writeAttributeCurrentSpeedWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs ZGMTR_PROVISIONALLY_AVAILABLE;
- (void)writeAttributeCurrentSpeedWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs params:(ZGMTRWriteParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeGeneratedCommandListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeAcceptedCommandListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeAttributeListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeFeatureMapWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeClusterRevisionWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end

@interface ZGMTRClusterDynamicLighting (Availability)

/**
 * For all instance methods that take a completion (i.e. command invocations),
 * the completion will be called on the provided queue.
 */
- (instancetype _Nullable)initWithDevice:(ZGMTRDevice *)device
                              endpointID:(NSNumber *)endpointID
                                   queue:(dispatch_queue_t)queue ZGMTR_PROVISIONALLY_AVAILABLE;

@end

/**
 * Cluster Illuminance Measurement
 *    Attributes and commands for configuring the measurement of illuminance, and reporting illuminance measurements.
 */
ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1))
@interface ZGMTRClusterIlluminanceMeasurement : ZGMTRGenericCluster

- (NSDictionary<NSString *, id> * _Nullable)readAttributeMeasuredValueWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeMinMeasuredValueWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeMaxMeasuredValueWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeToleranceWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeLightSensorTypeWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeGeneratedCommandListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeAcceptedCommandListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeAttributeListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeFeatureMapWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeClusterRevisionWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end

@interface ZGMTRClusterIlluminanceMeasurement (Availability)

/**
 * The queue is currently unused, but may be used in the future for calling completions
 * for command invocations if commands are added to this cluster.
 */
- (instancetype _Nullable)initWithDevice:(ZGMTRDevice *)device
                              endpointID:(NSNumber *)endpointID
                                   queue:(dispatch_queue_t)queue ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));

@end

/**
 * Cluster Temperature Measurement
 *    Attributes and commands for configuring the measurement of temperature, and reporting temperature measurements.
 */
ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1))
@interface ZGMTRClusterTemperatureMeasurement : ZGMTRGenericCluster

- (NSDictionary<NSString *, id> * _Nullable)readAttributeMeasuredValueWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeMinMeasuredValueWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeMaxMeasuredValueWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeToleranceWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeGeneratedCommandListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeAcceptedCommandListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeAttributeListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeFeatureMapWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeClusterRevisionWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end

@interface ZGMTRClusterTemperatureMeasurement (Availability)

/**
 * The queue is currently unused, but may be used in the future for calling completions
 * for command invocations if commands are added to this cluster.
 */
- (instancetype _Nullable)initWithDevice:(ZGMTRDevice *)device
                              endpointID:(NSNumber *)endpointID
                                   queue:(dispatch_queue_t)queue ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));

@end

/**
 * Cluster Pressure Measurement
 *    Attributes and commands for configuring the measurement of pressure, and reporting pressure measurements.
 */
ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1))
@interface ZGMTRClusterPressureMeasurement : ZGMTRGenericCluster

- (NSDictionary<NSString *, id> * _Nullable)readAttributeMeasuredValueWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeMinMeasuredValueWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeMaxMeasuredValueWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeToleranceWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeScaledValueWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeMinScaledValueWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeMaxScaledValueWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeScaledToleranceWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeScaleWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeGeneratedCommandListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeAcceptedCommandListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeAttributeListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeFeatureMapWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeClusterRevisionWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end

@interface ZGMTRClusterPressureMeasurement (Availability)

/**
 * The queue is currently unused, but may be used in the future for calling completions
 * for command invocations if commands are added to this cluster.
 */
- (instancetype _Nullable)initWithDevice:(ZGMTRDevice *)device
                              endpointID:(NSNumber *)endpointID
                                   queue:(dispatch_queue_t)queue ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));

@end

/**
 * Cluster Flow Measurement
 *    Attributes and commands for configuring the measurement of flow, and reporting flow measurements.
 */
ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1))
@interface ZGMTRClusterFlowMeasurement : ZGMTRGenericCluster

- (NSDictionary<NSString *, id> * _Nullable)readAttributeMeasuredValueWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeMinMeasuredValueWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeMaxMeasuredValueWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeToleranceWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeGeneratedCommandListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeAcceptedCommandListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeAttributeListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeFeatureMapWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeClusterRevisionWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end

@interface ZGMTRClusterFlowMeasurement (Availability)

/**
 * The queue is currently unused, but may be used in the future for calling completions
 * for command invocations if commands are added to this cluster.
 */
- (instancetype _Nullable)initWithDevice:(ZGMTRDevice *)device
                              endpointID:(NSNumber *)endpointID
                                   queue:(dispatch_queue_t)queue ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));

@end

/**
 * Cluster Relative Humidity Measurement
 *    Attributes and commands for configuring the measurement of relative humidity, and reporting relative humidity measurements.
 */
ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1))
@interface ZGMTRClusterRelativeHumidityMeasurement : ZGMTRGenericCluster

- (NSDictionary<NSString *, id> * _Nullable)readAttributeMeasuredValueWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeMinMeasuredValueWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeMaxMeasuredValueWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeToleranceWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeGeneratedCommandListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeAcceptedCommandListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeAttributeListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeFeatureMapWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeClusterRevisionWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end

@interface ZGMTRClusterRelativeHumidityMeasurement (Availability)

/**
 * The queue is currently unused, but may be used in the future for calling completions
 * for command invocations if commands are added to this cluster.
 */
- (instancetype _Nullable)initWithDevice:(ZGMTRDevice *)device
                              endpointID:(NSNumber *)endpointID
                                   queue:(dispatch_queue_t)queue ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));

@end

/**
 * Cluster Occupancy Sensing
 *    The server cluster provides an interface to occupancy sensing functionality based on one or more sensing modalities, including configuration and provision of notifications of occupancy status.
 */
ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1))
@interface ZGMTRClusterOccupancySensing : ZGMTRGenericCluster

- (NSDictionary<NSString *, id> * _Nullable)readAttributeOccupancyWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeOccupancySensorTypeWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeOccupancySensorTypeBitmapWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeHoldTimeWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));
- (void)writeAttributeHoldTimeWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));
- (void)writeAttributeHoldTimeWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs params:(ZGMTRWriteParams * _Nullable)params ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeHoldTimeLimitsWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributePredictedOccupancyWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributePIROccupiedToUnoccupiedDelayWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
- (void)writeAttributePIROccupiedToUnoccupiedDelayWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
- (void)writeAttributePIROccupiedToUnoccupiedDelayWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs params:(ZGMTRWriteParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributePIRUnoccupiedToOccupiedDelayWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
- (void)writeAttributePIRUnoccupiedToOccupiedDelayWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
- (void)writeAttributePIRUnoccupiedToOccupiedDelayWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs params:(ZGMTRWriteParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributePIRUnoccupiedToOccupiedThresholdWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
- (void)writeAttributePIRUnoccupiedToOccupiedThresholdWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
- (void)writeAttributePIRUnoccupiedToOccupiedThresholdWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs params:(ZGMTRWriteParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeUltrasonicOccupiedToUnoccupiedDelayWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));
- (void)writeAttributeUltrasonicOccupiedToUnoccupiedDelayWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));
- (void)writeAttributeUltrasonicOccupiedToUnoccupiedDelayWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs params:(ZGMTRWriteParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeUltrasonicUnoccupiedToOccupiedDelayWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));
- (void)writeAttributeUltrasonicUnoccupiedToOccupiedDelayWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));
- (void)writeAttributeUltrasonicUnoccupiedToOccupiedDelayWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs params:(ZGMTRWriteParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeUltrasonicUnoccupiedToOccupiedThresholdWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));
- (void)writeAttributeUltrasonicUnoccupiedToOccupiedThresholdWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));
- (void)writeAttributeUltrasonicUnoccupiedToOccupiedThresholdWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs params:(ZGMTRWriteParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributePhysicalContactOccupiedToUnoccupiedDelayWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));
- (void)writeAttributePhysicalContactOccupiedToUnoccupiedDelayWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));
- (void)writeAttributePhysicalContactOccupiedToUnoccupiedDelayWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs params:(ZGMTRWriteParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributePhysicalContactUnoccupiedToOccupiedDelayWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));
- (void)writeAttributePhysicalContactUnoccupiedToOccupiedDelayWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));
- (void)writeAttributePhysicalContactUnoccupiedToOccupiedDelayWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs params:(ZGMTRWriteParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributePhysicalContactUnoccupiedToOccupiedThresholdWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));
- (void)writeAttributePhysicalContactUnoccupiedToOccupiedThresholdWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));
- (void)writeAttributePhysicalContactUnoccupiedToOccupiedThresholdWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs params:(ZGMTRWriteParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeGeneratedCommandListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeAcceptedCommandListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeAttributeListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeFeatureMapWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeClusterRevisionWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end

@interface ZGMTRClusterOccupancySensing (Availability)

/**
 * The queue is currently unused, but may be used in the future for calling completions
 * for command invocations if commands are added to this cluster.
 */
- (instancetype _Nullable)initWithDevice:(ZGMTRDevice *)device
                              endpointID:(NSNumber *)endpointID
                                   queue:(dispatch_queue_t)queue ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));

@end

/**
 * Cluster Carbon Monoxide Concentration Measurement
 *    Attributes for reporting carbon monoxide concentration measurements
 */
ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6))
@interface ZGMTRClusterCarbonMonoxideConcentrationMeasurement : ZGMTRGenericCluster

- (NSDictionary<NSString *, id> * _Nullable)readAttributeMeasuredValueWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeMinMeasuredValueWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeMaxMeasuredValueWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6));

- (NSDictionary<NSString *, id> * _Nullable)readAttributePeakMeasuredValueWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6));

- (NSDictionary<NSString *, id> * _Nullable)readAttributePeakMeasuredValueWindowWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeAverageMeasuredValueWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeAverageMeasuredValueWindowWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeUncertaintyWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeMeasurementUnitWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeMeasurementMediumWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeLevelValueWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeGeneratedCommandListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeAcceptedCommandListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeAttributeListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeFeatureMapWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeClusterRevisionWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6));

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end

@interface ZGMTRClusterCarbonMonoxideConcentrationMeasurement (Availability)

/**
 * The queue is currently unused, but may be used in the future for calling completions
 * for command invocations if commands are added to this cluster.
 */
- (instancetype _Nullable)initWithDevice:(ZGMTRDevice *)device
                              endpointID:(NSNumber *)endpointID
                                   queue:(dispatch_queue_t)queue ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6));

@end

/**
 * Cluster Carbon Dioxide Concentration Measurement
 *    Attributes for reporting carbon dioxide concentration measurements
 */
ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6))
@interface ZGMTRClusterCarbonDioxideConcentrationMeasurement : ZGMTRGenericCluster

- (NSDictionary<NSString *, id> * _Nullable)readAttributeMeasuredValueWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeMinMeasuredValueWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeMaxMeasuredValueWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6));

- (NSDictionary<NSString *, id> * _Nullable)readAttributePeakMeasuredValueWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6));

- (NSDictionary<NSString *, id> * _Nullable)readAttributePeakMeasuredValueWindowWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeAverageMeasuredValueWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeAverageMeasuredValueWindowWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeUncertaintyWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeMeasurementUnitWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeMeasurementMediumWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeLevelValueWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeGeneratedCommandListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeAcceptedCommandListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeAttributeListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeFeatureMapWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeClusterRevisionWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6));

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end

@interface ZGMTRClusterCarbonDioxideConcentrationMeasurement (Availability)

/**
 * The queue is currently unused, but may be used in the future for calling completions
 * for command invocations if commands are added to this cluster.
 */
- (instancetype _Nullable)initWithDevice:(ZGMTRDevice *)device
                              endpointID:(NSNumber *)endpointID
                                   queue:(dispatch_queue_t)queue ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6));

@end

/**
 * Cluster Nitrogen Dioxide Concentration Measurement
 *    Attributes for reporting nitrogen dioxide concentration measurements
 */
ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6))
@interface ZGMTRClusterNitrogenDioxideConcentrationMeasurement : ZGMTRGenericCluster

- (NSDictionary<NSString *, id> * _Nullable)readAttributeMeasuredValueWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeMinMeasuredValueWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeMaxMeasuredValueWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6));

- (NSDictionary<NSString *, id> * _Nullable)readAttributePeakMeasuredValueWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6));

- (NSDictionary<NSString *, id> * _Nullable)readAttributePeakMeasuredValueWindowWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeAverageMeasuredValueWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeAverageMeasuredValueWindowWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeUncertaintyWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeMeasurementUnitWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeMeasurementMediumWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeLevelValueWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeGeneratedCommandListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeAcceptedCommandListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeAttributeListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeFeatureMapWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeClusterRevisionWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6));

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end

@interface ZGMTRClusterNitrogenDioxideConcentrationMeasurement (Availability)

/**
 * The queue is currently unused, but may be used in the future for calling completions
 * for command invocations if commands are added to this cluster.
 */
- (instancetype _Nullable)initWithDevice:(ZGMTRDevice *)device
                              endpointID:(NSNumber *)endpointID
                                   queue:(dispatch_queue_t)queue ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6));

@end

/**
 * Cluster Ozone Concentration Measurement
 *    Attributes for reporting ozone concentration measurements
 */
ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6))
@interface ZGMTRClusterOzoneConcentrationMeasurement : ZGMTRGenericCluster

- (NSDictionary<NSString *, id> * _Nullable)readAttributeMeasuredValueWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeMinMeasuredValueWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeMaxMeasuredValueWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6));

- (NSDictionary<NSString *, id> * _Nullable)readAttributePeakMeasuredValueWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6));

- (NSDictionary<NSString *, id> * _Nullable)readAttributePeakMeasuredValueWindowWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeAverageMeasuredValueWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeAverageMeasuredValueWindowWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeUncertaintyWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeMeasurementUnitWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeMeasurementMediumWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeLevelValueWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeGeneratedCommandListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeAcceptedCommandListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeAttributeListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeFeatureMapWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeClusterRevisionWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6));

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end

@interface ZGMTRClusterOzoneConcentrationMeasurement (Availability)

/**
 * The queue is currently unused, but may be used in the future for calling completions
 * for command invocations if commands are added to this cluster.
 */
- (instancetype _Nullable)initWithDevice:(ZGMTRDevice *)device
                              endpointID:(NSNumber *)endpointID
                                   queue:(dispatch_queue_t)queue ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6));

@end

/**
 * Cluster PM2.5 Concentration Measurement
 *    Attributes for reporting PM2.5 concentration measurements
 */
ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6))
@interface ZGMTRClusterPM25ConcentrationMeasurement : ZGMTRGenericCluster

- (NSDictionary<NSString *, id> * _Nullable)readAttributeMeasuredValueWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeMinMeasuredValueWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeMaxMeasuredValueWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6));

- (NSDictionary<NSString *, id> * _Nullable)readAttributePeakMeasuredValueWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6));

- (NSDictionary<NSString *, id> * _Nullable)readAttributePeakMeasuredValueWindowWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeAverageMeasuredValueWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeAverageMeasuredValueWindowWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeUncertaintyWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeMeasurementUnitWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeMeasurementMediumWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeLevelValueWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeGeneratedCommandListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeAcceptedCommandListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeAttributeListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeFeatureMapWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeClusterRevisionWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6));

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end

@interface ZGMTRClusterPM25ConcentrationMeasurement (Availability)

/**
 * The queue is currently unused, but may be used in the future for calling completions
 * for command invocations if commands are added to this cluster.
 */
- (instancetype _Nullable)initWithDevice:(ZGMTRDevice *)device
                              endpointID:(NSNumber *)endpointID
                                   queue:(dispatch_queue_t)queue ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6));

@end

/**
 * Cluster Formaldehyde Concentration Measurement
 *    Attributes for reporting formaldehyde concentration measurements
 */
ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6))
@interface ZGMTRClusterFormaldehydeConcentrationMeasurement : ZGMTRGenericCluster

- (NSDictionary<NSString *, id> * _Nullable)readAttributeMeasuredValueWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeMinMeasuredValueWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeMaxMeasuredValueWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6));

- (NSDictionary<NSString *, id> * _Nullable)readAttributePeakMeasuredValueWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6));

- (NSDictionary<NSString *, id> * _Nullable)readAttributePeakMeasuredValueWindowWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeAverageMeasuredValueWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeAverageMeasuredValueWindowWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeUncertaintyWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeMeasurementUnitWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeMeasurementMediumWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeLevelValueWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeGeneratedCommandListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeAcceptedCommandListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeAttributeListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeFeatureMapWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeClusterRevisionWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6));

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end

@interface ZGMTRClusterFormaldehydeConcentrationMeasurement (Availability)

/**
 * The queue is currently unused, but may be used in the future for calling completions
 * for command invocations if commands are added to this cluster.
 */
- (instancetype _Nullable)initWithDevice:(ZGMTRDevice *)device
                              endpointID:(NSNumber *)endpointID
                                   queue:(dispatch_queue_t)queue ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6));

@end

/**
 * Cluster PM1 Concentration Measurement
 *    Attributes for reporting PM1 concentration measurements
 */
ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6))
@interface ZGMTRClusterPM1ConcentrationMeasurement : ZGMTRGenericCluster

- (NSDictionary<NSString *, id> * _Nullable)readAttributeMeasuredValueWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeMinMeasuredValueWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeMaxMeasuredValueWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6));

- (NSDictionary<NSString *, id> * _Nullable)readAttributePeakMeasuredValueWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6));

- (NSDictionary<NSString *, id> * _Nullable)readAttributePeakMeasuredValueWindowWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeAverageMeasuredValueWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeAverageMeasuredValueWindowWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeUncertaintyWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeMeasurementUnitWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeMeasurementMediumWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeLevelValueWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeGeneratedCommandListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeAcceptedCommandListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeAttributeListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeFeatureMapWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeClusterRevisionWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6));

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end

@interface ZGMTRClusterPM1ConcentrationMeasurement (Availability)

/**
 * The queue is currently unused, but may be used in the future for calling completions
 * for command invocations if commands are added to this cluster.
 */
- (instancetype _Nullable)initWithDevice:(ZGMTRDevice *)device
                              endpointID:(NSNumber *)endpointID
                                   queue:(dispatch_queue_t)queue ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6));

@end

/**
 * Cluster PM10 Concentration Measurement
 *    Attributes for reporting PM10 concentration measurements
 */
ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6))
@interface ZGMTRClusterPM10ConcentrationMeasurement : ZGMTRGenericCluster

- (NSDictionary<NSString *, id> * _Nullable)readAttributeMeasuredValueWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeMinMeasuredValueWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeMaxMeasuredValueWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6));

- (NSDictionary<NSString *, id> * _Nullable)readAttributePeakMeasuredValueWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6));

- (NSDictionary<NSString *, id> * _Nullable)readAttributePeakMeasuredValueWindowWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeAverageMeasuredValueWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeAverageMeasuredValueWindowWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeUncertaintyWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeMeasurementUnitWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeMeasurementMediumWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeLevelValueWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeGeneratedCommandListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeAcceptedCommandListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeAttributeListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeFeatureMapWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeClusterRevisionWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6));

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end

@interface ZGMTRClusterPM10ConcentrationMeasurement (Availability)

/**
 * The queue is currently unused, but may be used in the future for calling completions
 * for command invocations if commands are added to this cluster.
 */
- (instancetype _Nullable)initWithDevice:(ZGMTRDevice *)device
                              endpointID:(NSNumber *)endpointID
                                   queue:(dispatch_queue_t)queue ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6));

@end

/**
 * Cluster Total Volatile Organic Compounds Concentration Measurement
 *    Attributes for reporting total volatile organic compounds concentration measurements
 */
ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6))
@interface ZGMTRClusterTotalVolatileOrganicCompoundsConcentrationMeasurement : ZGMTRGenericCluster

- (NSDictionary<NSString *, id> * _Nullable)readAttributeMeasuredValueWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeMinMeasuredValueWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeMaxMeasuredValueWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6));

- (NSDictionary<NSString *, id> * _Nullable)readAttributePeakMeasuredValueWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6));

- (NSDictionary<NSString *, id> * _Nullable)readAttributePeakMeasuredValueWindowWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeAverageMeasuredValueWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeAverageMeasuredValueWindowWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeUncertaintyWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeMeasurementUnitWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeMeasurementMediumWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeLevelValueWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeGeneratedCommandListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeAcceptedCommandListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeAttributeListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeFeatureMapWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeClusterRevisionWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6));

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end

@interface ZGMTRClusterTotalVolatileOrganicCompoundsConcentrationMeasurement (Availability)

/**
 * The queue is currently unused, but may be used in the future for calling completions
 * for command invocations if commands are added to this cluster.
 */
- (instancetype _Nullable)initWithDevice:(ZGMTRDevice *)device
                              endpointID:(NSNumber *)endpointID
                                   queue:(dispatch_queue_t)queue ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6));

@end

/**
 * Cluster Radon Concentration Measurement
 *    Attributes for reporting radon concentration measurements
 */
ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6))
@interface ZGMTRClusterRadonConcentrationMeasurement : ZGMTRGenericCluster

- (NSDictionary<NSString *, id> * _Nullable)readAttributeMeasuredValueWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeMinMeasuredValueWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeMaxMeasuredValueWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6));

- (NSDictionary<NSString *, id> * _Nullable)readAttributePeakMeasuredValueWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6));

- (NSDictionary<NSString *, id> * _Nullable)readAttributePeakMeasuredValueWindowWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeAverageMeasuredValueWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeAverageMeasuredValueWindowWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeUncertaintyWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeMeasurementUnitWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeMeasurementMediumWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeLevelValueWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeGeneratedCommandListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeAcceptedCommandListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeAttributeListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeFeatureMapWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeClusterRevisionWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6));

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end

@interface ZGMTRClusterRadonConcentrationMeasurement (Availability)

/**
 * The queue is currently unused, but may be used in the future for calling completions
 * for command invocations if commands are added to this cluster.
 */
- (instancetype _Nullable)initWithDevice:(ZGMTRDevice *)device
                              endpointID:(NSNumber *)endpointID
                                   queue:(dispatch_queue_t)queue ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6));

@end

/**
 * Cluster Soil Measurement
 *    This cluster provides an interface to soil measurement functionality, including configuration and provision of notifications of soil measurements.
 */
ZGMTR_PROVISIONALLY_AVAILABLE
@interface ZGMTRClusterSoilMeasurement : ZGMTRGenericCluster

- (NSDictionary<NSString *, id> * _Nullable)readAttributeSoilMoistureMeasurementLimitsWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeSoilMoistureMeasuredValueWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeGeneratedCommandListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeAcceptedCommandListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeAttributeListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeFeatureMapWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeClusterRevisionWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end

@interface ZGMTRClusterSoilMeasurement (Availability)

/**
 * The queue is currently unused, but may be used in the future for calling completions
 * for command invocations if commands are added to this cluster.
 */
- (instancetype _Nullable)initWithDevice:(ZGMTRDevice *)device
                              endpointID:(NSNumber *)endpointID
                                   queue:(dispatch_queue_t)queue ZGMTR_PROVISIONALLY_AVAILABLE;

@end

/**
 * Cluster Ambient Context Sensing
 *    This server cluster provides an interface to ambient context sensing functionality.
 */
ZGMTR_PROVISIONALLY_AVAILABLE
@interface ZGMTRClusterAmbientContextSensing : ZGMTRGenericCluster

- (NSDictionary<NSString *, id> * _Nullable)readAttributeHumanActivityDetectedWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeObjectIdentifiedWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeAudioContextDetectedWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeAmbientContextTypeWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeAmbientContextTypeSupportedWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeObjectCountThresholdReachedWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeObjectCountConfigWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;
- (void)writeAttributeObjectCountConfigWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs ZGMTR_PROVISIONALLY_AVAILABLE;
- (void)writeAttributeObjectCountConfigWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs params:(ZGMTRWriteParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeObjectCountWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeSimultaneousDetectionLimitWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeHoldTimeWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;
- (void)writeAttributeHoldTimeWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs ZGMTR_PROVISIONALLY_AVAILABLE;
- (void)writeAttributeHoldTimeWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs params:(ZGMTRWriteParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeHoldTimeLimitsWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributePredictedActivityWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeSensorFusionSupportedWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeGeneratedCommandListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeAcceptedCommandListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeAttributeListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeFeatureMapWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeClusterRevisionWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end

@interface ZGMTRClusterAmbientContextSensing (Availability)

/**
 * The queue is currently unused, but may be used in the future for calling completions
 * for command invocations if commands are added to this cluster.
 */
- (instancetype _Nullable)initWithDevice:(ZGMTRDevice *)device
                              endpointID:(NSNumber *)endpointID
                                   queue:(dispatch_queue_t)queue ZGMTR_PROVISIONALLY_AVAILABLE;

@end

/**
 * Cluster Ambient Sensing Union
 *    This cluster provides data modeling and protocol implementation of multi-node ambient sensing system.
 */
ZGMTR_PROVISIONALLY_AVAILABLE
@interface ZGMTRClusterAmbientSensingUnion : ZGMTRGenericCluster

- (NSDictionary<NSString *, id> * _Nullable)readAttributeUnionNameWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;
- (void)writeAttributeUnionNameWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs ZGMTR_PROVISIONALLY_AVAILABLE;
- (void)writeAttributeUnionNameWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs params:(ZGMTRWriteParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeUnionHealthWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeUnionContributorListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeGeneratedCommandListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeAcceptedCommandListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeAttributeListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeFeatureMapWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeClusterRevisionWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end

@interface ZGMTRClusterAmbientSensingUnion (Availability)

/**
 * The queue is currently unused, but may be used in the future for calling completions
 * for command invocations if commands are added to this cluster.
 */
- (instancetype _Nullable)initWithDevice:(ZGMTRDevice *)device
                              endpointID:(NSNumber *)endpointID
                                   queue:(dispatch_queue_t)queue ZGMTR_PROVISIONALLY_AVAILABLE;

@end

/**
 * Cluster Proximity Ranging
 *    This cluster enables the configuration of proximity ranging sessions and reporting of proximity ranging data.
 */
ZGMTR_PROVISIONALLY_AVAILABLE
@interface ZGMTRClusterProximityRanging : ZGMTRGenericCluster

- (void)startRangingRequestWithParams:(ZGMTRProximityRangingClusterStartRangingRequestParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(void (^)(ZGMTRProximityRangingClusterStartRangingResponseParams * _Nullable data, NSError * _Nullable error))completion ZGMTR_PROVISIONALLY_AVAILABLE;
- (void)stopRangingRequestWithParams:(ZGMTRProximityRangingClusterStopRangingRequestParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(ZGMTRStatusCompletion)completion ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeRangingCapabilitiesWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeWiFiDevIKWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeBLEDeviceIDWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeBLTDevIKWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeBLTCSSecurityLevelWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeBLTCSModeCapabilityWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeSessionIDListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeGeneratedCommandListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeAcceptedCommandListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeAttributeListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeFeatureMapWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeClusterRevisionWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end

@interface ZGMTRClusterProximityRanging (Availability)

/**
 * For all instance methods that take a completion (i.e. command invocations),
 * the completion will be called on the provided queue.
 */
- (instancetype _Nullable)initWithDevice:(ZGMTRDevice *)device
                              endpointID:(NSNumber *)endpointID
                                   queue:(dispatch_queue_t)queue ZGMTR_PROVISIONALLY_AVAILABLE;

@end

/**
 * Cluster Smoke Concentration Measurement
 *    The server cluster provides an interface to concentration measurement functionality.
 */
ZGMTR_PROVISIONALLY_AVAILABLE
@interface ZGMTRClusterSmokeConcentrationMeasurement : ZGMTRGenericCluster

- (NSDictionary<NSString *, id> * _Nullable)readAttributeMeasuredValueWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeMinMeasuredValueWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeMaxMeasuredValueWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributePeakMeasuredValueWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributePeakMeasuredValueWindowWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeAverageMeasuredValueWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeAverageMeasuredValueWindowWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeUncertaintyWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeMeasurementUnitWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeMeasurementMediumWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeLevelValueWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeGeneratedCommandListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeAcceptedCommandListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeAttributeListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeFeatureMapWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeClusterRevisionWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end

@interface ZGMTRClusterSmokeConcentrationMeasurement (Availability)

/**
 * The queue is currently unused, but may be used in the future for calling completions
 * for command invocations if commands are added to this cluster.
 */
- (instancetype _Nullable)initWithDevice:(ZGMTRDevice *)device
                              endpointID:(NSNumber *)endpointID
                                   queue:(dispatch_queue_t)queue ZGMTR_PROVISIONALLY_AVAILABLE;

@end

/**
 * Cluster Network Identity Management
 *    This cluster manages the identities and credentials of devices that connect to a managed network.
 */
ZGMTR_PROVISIONALLY_AVAILABLE
@interface ZGMTRClusterNetworkIdentityManagement : ZGMTRGenericCluster

- (void)addClientWithParams:(ZGMTRNetworkIdentityManagementClusterAddClientParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(void (^)(ZGMTRNetworkIdentityManagementClusterAddClientResponseParams * _Nullable data, NSError * _Nullable error))completion ZGMTR_PROVISIONALLY_AVAILABLE;
- (void)removeClientWithParams:(ZGMTRNetworkIdentityManagementClusterRemoveClientParams * _Nullable)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(ZGMTRStatusCompletion)completion ZGMTR_PROVISIONALLY_AVAILABLE;
- (void)removeClientWithExpectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedValues expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(ZGMTRStatusCompletion)completion
    ZGMTR_PROVISIONALLY_AVAILABLE;
- (void)queryIdentityWithParams:(ZGMTRNetworkIdentityManagementClusterQueryIdentityParams * _Nullable)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(void (^)(ZGMTRNetworkIdentityManagementClusterQueryIdentityResponseParams * _Nullable data, NSError * _Nullable error))completion ZGMTR_PROVISIONALLY_AVAILABLE;
- (void)queryIdentityWithExpectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedValues expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(void (^)(ZGMTRNetworkIdentityManagementClusterQueryIdentityResponseParams * _Nullable data, NSError * _Nullable error))completion
    ZGMTR_PROVISIONALLY_AVAILABLE;
- (void)importAdminSecretWithParams:(ZGMTRNetworkIdentityManagementClusterImportAdminSecretParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(ZGMTRStatusCompletion)completion ZGMTR_PROVISIONALLY_AVAILABLE;
- (void)exportAdminSecretWithParams:(ZGMTRNetworkIdentityManagementClusterExportAdminSecretParams * _Nullable)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(void (^)(ZGMTRNetworkIdentityManagementClusterExportAdminSecretResponseParams * _Nullable data, NSError * _Nullable error))completion ZGMTR_PROVISIONALLY_AVAILABLE;
- (void)exportAdminSecretWithExpectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedValues expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(void (^)(ZGMTRNetworkIdentityManagementClusterExportAdminSecretResponseParams * _Nullable data, NSError * _Nullable error))completion
    ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeActiveNetworkIdentitiesWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeClientsWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeClientTableSizeWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeGeneratedCommandListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeAcceptedCommandListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeAttributeListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeFeatureMapWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeClusterRevisionWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end

@interface ZGMTRClusterNetworkIdentityManagement (Availability)

/**
 * For all instance methods that take a completion (i.e. command invocations),
 * the completion will be called on the provided queue.
 */
- (instancetype _Nullable)initWithDevice:(ZGMTRDevice *)device
                              endpointID:(NSNumber *)endpointID
                                   queue:(dispatch_queue_t)queue ZGMTR_PROVISIONALLY_AVAILABLE;

@end

/**
 * Cluster Wi-Fi Network Management
 *    Functionality to retrieve operational information about a managed Wi-Fi network.
 */
ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4))
@interface ZGMTRClusterWiFiNetworkManagement : ZGMTRGenericCluster

- (void)networkPassphraseRequestWithParams:(ZGMTRWiFiNetworkManagementClusterNetworkPassphraseRequestParams * _Nullable)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(void (^)(ZGMTRWiFiNetworkManagementClusterNetworkPassphraseResponseParams * _Nullable data, NSError * _Nullable error))completion ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));
- (void)networkPassphraseRequestWithExpectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedValues expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(void (^)(ZGMTRWiFiNetworkManagementClusterNetworkPassphraseResponseParams * _Nullable data, NSError * _Nullable error))completion
    ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeSSIDWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributePassphraseSurrogateWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeGeneratedCommandListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeAcceptedCommandListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeAttributeListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeFeatureMapWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeClusterRevisionWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end

@interface ZGMTRClusterWiFiNetworkManagement (Availability)

/**
 * For all instance methods that take a completion (i.e. command invocations),
 * the completion will be called on the provided queue.
 */
- (instancetype _Nullable)initWithDevice:(ZGMTRDevice *)device
                              endpointID:(NSNumber *)endpointID
                                   queue:(dispatch_queue_t)queue ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));

@end

/**
 * Cluster Thread Border Router Management
 *    Manage the Thread network of Thread Border Router
 */
ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4))
@interface ZGMTRClusterThreadBorderRouterManagement : ZGMTRGenericCluster

- (void)getActiveDatasetRequestWithParams:(ZGMTRThreadBorderRouterManagementClusterGetActiveDatasetRequestParams * _Nullable)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(void (^)(ZGMTRThreadBorderRouterManagementClusterDatasetResponseParams * _Nullable data, NSError * _Nullable error))completion ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));
- (void)getActiveDatasetRequestWithExpectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedValues expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(void (^)(ZGMTRThreadBorderRouterManagementClusterDatasetResponseParams * _Nullable data, NSError * _Nullable error))completion
    ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));
- (void)getPendingDatasetRequestWithParams:(ZGMTRThreadBorderRouterManagementClusterGetPendingDatasetRequestParams * _Nullable)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(void (^)(ZGMTRThreadBorderRouterManagementClusterDatasetResponseParams * _Nullable data, NSError * _Nullable error))completion ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));
- (void)getPendingDatasetRequestWithExpectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedValues expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(void (^)(ZGMTRThreadBorderRouterManagementClusterDatasetResponseParams * _Nullable data, NSError * _Nullable error))completion
    ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));
- (void)setActiveDatasetRequestWithParams:(ZGMTRThreadBorderRouterManagementClusterSetActiveDatasetRequestParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(ZGMTRStatusCompletion)completion ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));
- (void)setPendingDatasetRequestWithParams:(ZGMTRThreadBorderRouterManagementClusterSetPendingDatasetRequestParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(ZGMTRStatusCompletion)completion ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeBorderRouterNameWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeBorderAgentIDWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeThreadVersionWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeInterfaceEnabledWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeActiveDatasetTimestampWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributePendingDatasetTimestampWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeGeneratedCommandListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeAcceptedCommandListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeAttributeListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeFeatureMapWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeClusterRevisionWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end

@interface ZGMTRClusterThreadBorderRouterManagement (Availability)

/**
 * For all instance methods that take a completion (i.e. command invocations),
 * the completion will be called on the provided queue.
 */
- (instancetype _Nullable)initWithDevice:(ZGMTRDevice *)device
                              endpointID:(NSNumber *)endpointID
                                   queue:(dispatch_queue_t)queue ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));

@end

/**
 * Cluster Thread Network Directory
 *    Manages the names and credentials of Thread networks visible to the user.
 */
ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4))
@interface ZGMTRClusterThreadNetworkDirectory : ZGMTRGenericCluster

- (void)addNetworkWithParams:(ZGMTRThreadNetworkDirectoryClusterAddNetworkParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(ZGMTRStatusCompletion)completion ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));
- (void)removeNetworkWithParams:(ZGMTRThreadNetworkDirectoryClusterRemoveNetworkParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(ZGMTRStatusCompletion)completion ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));
- (void)getOperationalDatasetWithParams:(ZGMTRThreadNetworkDirectoryClusterGetOperationalDatasetParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(void (^)(ZGMTRThreadNetworkDirectoryClusterOperationalDatasetResponseParams * _Nullable data, NSError * _Nullable error))completion ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributePreferredExtendedPanIDWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));
- (void)writeAttributePreferredExtendedPanIDWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));
- (void)writeAttributePreferredExtendedPanIDWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs params:(ZGMTRWriteParams * _Nullable)params ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeThreadNetworksWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeThreadNetworkTableSizeWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeGeneratedCommandListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeAcceptedCommandListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeAttributeListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeFeatureMapWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeClusterRevisionWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end

@interface ZGMTRClusterThreadNetworkDirectory (Availability)

/**
 * For all instance methods that take a completion (i.e. command invocations),
 * the completion will be called on the provided queue.
 */
- (instancetype _Nullable)initWithDevice:(ZGMTRDevice *)device
                              endpointID:(NSNumber *)endpointID
                                   queue:(dispatch_queue_t)queue ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));

@end

/**
 * Cluster Commissioning Proxy
 *    This cluster provides a proxy service allowing a Commissioner to utilize commissioning transports not supported locally, or to extend the commissioning range of the Commissioner.
 */
ZGMTR_PROVISIONALLY_AVAILABLE
@interface ZGMTRClusterCommissioningProxy : ZGMTRGenericCluster

- (void)proxyConnectRequestWithParams:(ZGMTRCommissioningProxyClusterProxyConnectRequestParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(void (^)(ZGMTRCommissioningProxyClusterProxyConnectResponseParams * _Nullable data, NSError * _Nullable error))completion ZGMTR_PROVISIONALLY_AVAILABLE;
- (void)proxyDisconnectRequestWithParams:(ZGMTRCommissioningProxyClusterProxyDisconnectRequestParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(ZGMTRStatusCompletion)completion ZGMTR_PROVISIONALLY_AVAILABLE;
- (void)proxyScanRequestWithParams:(ZGMTRCommissioningProxyClusterProxyScanRequestParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(void (^)(ZGMTRCommissioningProxyClusterProxyScanResponseParams * _Nullable data, NSError * _Nullable error))completion ZGMTR_PROVISIONALLY_AVAILABLE;
- (void)proxyBackGroundScanStartRequestWithParams:(ZGMTRCommissioningProxyClusterProxyBackGroundScanStartRequestParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(ZGMTRStatusCompletion)completion ZGMTR_PROVISIONALLY_AVAILABLE;
- (void)proxyBackGroundScanStopRequestWithParams:(ZGMTRCommissioningProxyClusterProxyBackGroundScanStopRequestParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(ZGMTRStatusCompletion)completion ZGMTR_PROVISIONALLY_AVAILABLE;
- (void)proxyMessageRequestWithParams:(ZGMTRCommissioningProxyClusterProxyMessageRequestParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(void (^)(ZGMTRCommissioningProxyClusterProxyMessageResponseParams * _Nullable data, NSError * _Nullable error))completion ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeTransportWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeScanMaxTimeWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;
- (void)writeAttributeScanMaxTimeWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs ZGMTR_PROVISIONALLY_AVAILABLE;
- (void)writeAttributeScanMaxTimeWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs params:(ZGMTRWriteParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeMaxSessionsWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeMaxCachedResultsWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeNumCachedResultsWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeCacheTimeoutWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;
- (void)writeAttributeCacheTimeoutWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs ZGMTR_PROVISIONALLY_AVAILABLE;
- (void)writeAttributeCacheTimeoutWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs params:(ZGMTRWriteParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeCachedResultsWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeWiFiBandWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeGeneratedCommandListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeAcceptedCommandListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeAttributeListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeFeatureMapWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeClusterRevisionWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end

@interface ZGMTRClusterCommissioningProxy (Availability)

/**
 * For all instance methods that take a completion (i.e. command invocations),
 * the completion will be called on the provided queue.
 */
- (instancetype _Nullable)initWithDevice:(ZGMTRDevice *)device
                              endpointID:(NSNumber *)endpointID
                                   queue:(dispatch_queue_t)queue ZGMTR_PROVISIONALLY_AVAILABLE;

@end

/**
 * Cluster Wake on LAN
 *    This cluster provides an interface for managing low power mode on a device that supports the Wake On LAN protocol.
 */
ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4))
@interface ZGMTRClusterWakeOnLAN : ZGMTRGenericCluster

- (NSDictionary<NSString *, id> * _Nullable)readAttributeMACAddressWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeLinkLocalAddressWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeGeneratedCommandListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeAcceptedCommandListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeAttributeListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeFeatureMapWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeClusterRevisionWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end

@interface ZGMTRClusterWakeOnLAN (Availability)

/**
 * The queue is currently unused, but may be used in the future for calling completions
 * for command invocations if commands are added to this cluster.
 */
- (instancetype _Nullable)initWithDevice:(ZGMTRDevice *)device
                              endpointID:(NSNumber *)endpointID
                                   queue:(dispatch_queue_t)queue ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));

@end

/**
 * Cluster Channel
 *    This cluster provides an interface for controlling the current Channel on a device.
 */
ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1))
@interface ZGMTRClusterChannel : ZGMTRGenericCluster

- (void)changeChannelWithParams:(ZGMTRChannelClusterChangeChannelParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(void (^)(ZGMTRChannelClusterChangeChannelResponseParams * _Nullable data, NSError * _Nullable error))completion ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
- (void)changeChannelByNumberWithParams:(ZGMTRChannelClusterChangeChannelByNumberParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(ZGMTRStatusCompletion)completion ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
- (void)skipChannelWithParams:(ZGMTRChannelClusterSkipChannelParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(ZGMTRStatusCompletion)completion ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
- (void)getProgramGuideWithParams:(ZGMTRChannelClusterGetProgramGuideParams * _Nullable)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(void (^)(ZGMTRChannelClusterProgramGuideResponseParams * _Nullable data, NSError * _Nullable error))completion ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));
- (void)getProgramGuideWithExpectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedValues expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(void (^)(ZGMTRChannelClusterProgramGuideResponseParams * _Nullable data, NSError * _Nullable error))completion
    ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));
- (void)recordProgramWithParams:(ZGMTRChannelClusterRecordProgramParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(ZGMTRStatusCompletion)completion ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));
- (void)cancelRecordProgramWithParams:(ZGMTRChannelClusterCancelRecordProgramParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(ZGMTRStatusCompletion)completion ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeChannelListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeLineupWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeCurrentChannelWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeGeneratedCommandListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeAcceptedCommandListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeAttributeListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeFeatureMapWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeClusterRevisionWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end

@interface ZGMTRClusterChannel (Availability)

/**
 * For all instance methods that take a completion (i.e. command invocations),
 * the completion will be called on the provided queue.
 */
- (instancetype _Nullable)initWithDevice:(ZGMTRDevice *)device
                              endpointID:(NSNumber *)endpointID
                                   queue:(dispatch_queue_t)queue ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));

@end

/**
 * Cluster Target Navigator
 *    This cluster provides an interface for UX navigation within a set of targets on a device or endpoint.
 */
ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1))
@interface ZGMTRClusterTargetNavigator : ZGMTRGenericCluster

- (void)navigateTargetWithParams:(ZGMTRTargetNavigatorClusterNavigateTargetParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(void (^)(ZGMTRTargetNavigatorClusterNavigateTargetResponseParams * _Nullable data, NSError * _Nullable error))completion ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeTargetListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeCurrentTargetWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeGeneratedCommandListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeAcceptedCommandListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeAttributeListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeFeatureMapWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeClusterRevisionWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end

@interface ZGMTRClusterTargetNavigator (Availability)

/**
 * For all instance methods that take a completion (i.e. command invocations),
 * the completion will be called on the provided queue.
 */
- (instancetype _Nullable)initWithDevice:(ZGMTRDevice *)device
                              endpointID:(NSNumber *)endpointID
                                   queue:(dispatch_queue_t)queue ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));

@end

/**
 * Cluster Media Playback
 *    This cluster provides an interface for controlling Media Playback (PLAY, PAUSE, etc) on a media device such as a TV or Speaker.
 */
ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1))
@interface ZGMTRClusterMediaPlayback : ZGMTRGenericCluster

- (void)playWithParams:(ZGMTRMediaPlaybackClusterPlayParams * _Nullable)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(void (^)(ZGMTRMediaPlaybackClusterPlaybackResponseParams * _Nullable data, NSError * _Nullable error))completion ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
- (void)playWithExpectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedValues expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(void (^)(ZGMTRMediaPlaybackClusterPlaybackResponseParams * _Nullable data, NSError * _Nullable error))completion
    ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
- (void)pauseWithParams:(ZGMTRMediaPlaybackClusterPauseParams * _Nullable)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(void (^)(ZGMTRMediaPlaybackClusterPlaybackResponseParams * _Nullable data, NSError * _Nullable error))completion ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
- (void)pauseWithExpectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedValues expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(void (^)(ZGMTRMediaPlaybackClusterPlaybackResponseParams * _Nullable data, NSError * _Nullable error))completion
    ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
- (void)stopWithParams:(ZGMTRMediaPlaybackClusterStopParams * _Nullable)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(void (^)(ZGMTRMediaPlaybackClusterPlaybackResponseParams * _Nullable data, NSError * _Nullable error))completion ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
- (void)stopWithExpectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedValues expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(void (^)(ZGMTRMediaPlaybackClusterPlaybackResponseParams * _Nullable data, NSError * _Nullable error))completion
    ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
- (void)startOverWithParams:(ZGMTRMediaPlaybackClusterStartOverParams * _Nullable)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(void (^)(ZGMTRMediaPlaybackClusterPlaybackResponseParams * _Nullable data, NSError * _Nullable error))completion ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
- (void)startOverWithExpectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedValues expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(void (^)(ZGMTRMediaPlaybackClusterPlaybackResponseParams * _Nullable data, NSError * _Nullable error))completion
    ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
- (void)previousWithParams:(ZGMTRMediaPlaybackClusterPreviousParams * _Nullable)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(void (^)(ZGMTRMediaPlaybackClusterPlaybackResponseParams * _Nullable data, NSError * _Nullable error))completion ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
- (void)previousWithExpectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedValues expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(void (^)(ZGMTRMediaPlaybackClusterPlaybackResponseParams * _Nullable data, NSError * _Nullable error))completion
    ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
- (void)nextWithParams:(ZGMTRMediaPlaybackClusterNextParams * _Nullable)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(void (^)(ZGMTRMediaPlaybackClusterPlaybackResponseParams * _Nullable data, NSError * _Nullable error))completion ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
- (void)nextWithExpectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedValues expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(void (^)(ZGMTRMediaPlaybackClusterPlaybackResponseParams * _Nullable data, NSError * _Nullable error))completion
    ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
- (void)rewindWithParams:(ZGMTRMediaPlaybackClusterRewindParams * _Nullable)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(void (^)(ZGMTRMediaPlaybackClusterPlaybackResponseParams * _Nullable data, NSError * _Nullable error))completion ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
- (void)rewindWithExpectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedValues expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(void (^)(ZGMTRMediaPlaybackClusterPlaybackResponseParams * _Nullable data, NSError * _Nullable error))completion
    ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
- (void)fastForwardWithParams:(ZGMTRMediaPlaybackClusterFastForwardParams * _Nullable)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(void (^)(ZGMTRMediaPlaybackClusterPlaybackResponseParams * _Nullable data, NSError * _Nullable error))completion ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
- (void)fastForwardWithExpectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedValues expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(void (^)(ZGMTRMediaPlaybackClusterPlaybackResponseParams * _Nullable data, NSError * _Nullable error))completion
    ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
- (void)skipForwardWithParams:(ZGMTRMediaPlaybackClusterSkipForwardParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(void (^)(ZGMTRMediaPlaybackClusterPlaybackResponseParams * _Nullable data, NSError * _Nullable error))completion ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
- (void)skipBackwardWithParams:(ZGMTRMediaPlaybackClusterSkipBackwardParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(void (^)(ZGMTRMediaPlaybackClusterPlaybackResponseParams * _Nullable data, NSError * _Nullable error))completion ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
- (void)seekWithParams:(ZGMTRMediaPlaybackClusterSeekParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(void (^)(ZGMTRMediaPlaybackClusterPlaybackResponseParams * _Nullable data, NSError * _Nullable error))completion ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
- (void)activateAudioTrackWithParams:(ZGMTRMediaPlaybackClusterActivateAudioTrackParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(ZGMTRStatusCompletion)completion ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));
- (void)activateTextTrackWithParams:(ZGMTRMediaPlaybackClusterActivateTextTrackParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(ZGMTRStatusCompletion)completion ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));
- (void)deactivateTextTrackWithParams:(ZGMTRMediaPlaybackClusterDeactivateTextTrackParams * _Nullable)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(ZGMTRStatusCompletion)completion ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));
- (void)deactivateTextTrackWithExpectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedValues expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(ZGMTRStatusCompletion)completion
    ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeCurrentStateWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeStartTimeWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeDurationWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeSampledPositionWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributePlaybackSpeedWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeSeekRangeEndWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeSeekRangeStartWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeActiveAudioTrackWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeAvailableAudioTracksWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeActiveTextTrackWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeAvailableTextTracksWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeAvailableCommandsWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeContentInfoWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeGeneratedCommandListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeAcceptedCommandListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeAttributeListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeFeatureMapWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeClusterRevisionWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end

@interface ZGMTRClusterMediaPlayback (Availability)

/**
 * For all instance methods that take a completion (i.e. command invocations),
 * the completion will be called on the provided queue.
 */
- (instancetype _Nullable)initWithDevice:(ZGMTRDevice *)device
                              endpointID:(NSNumber *)endpointID
                                   queue:(dispatch_queue_t)queue ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));

@end

/**
 * Cluster Media Input
 *    This cluster provides an interface for controlling the Input Selector on a media device such as a TV.
 */
ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1))
@interface ZGMTRClusterMediaInput : ZGMTRGenericCluster

- (void)selectInputWithParams:(ZGMTRMediaInputClusterSelectInputParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(ZGMTRStatusCompletion)completion ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
- (void)showInputStatusWithParams:(ZGMTRMediaInputClusterShowInputStatusParams * _Nullable)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(ZGMTRStatusCompletion)completion ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
- (void)showInputStatusWithExpectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedValues expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(ZGMTRStatusCompletion)completion
    ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
- (void)hideInputStatusWithParams:(ZGMTRMediaInputClusterHideInputStatusParams * _Nullable)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(ZGMTRStatusCompletion)completion ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
- (void)hideInputStatusWithExpectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedValues expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(ZGMTRStatusCompletion)completion
    ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
- (void)renameInputWithParams:(ZGMTRMediaInputClusterRenameInputParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(ZGMTRStatusCompletion)completion ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeInputListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeCurrentInputWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeGeneratedCommandListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeAcceptedCommandListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeAttributeListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeFeatureMapWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeClusterRevisionWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end

@interface ZGMTRClusterMediaInput (Availability)

/**
 * For all instance methods that take a completion (i.e. command invocations),
 * the completion will be called on the provided queue.
 */
- (instancetype _Nullable)initWithDevice:(ZGMTRDevice *)device
                              endpointID:(NSNumber *)endpointID
                                   queue:(dispatch_queue_t)queue ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));

@end

/**
 * Cluster Low Power
 *    This cluster provides an interface for managing low power mode on a device.
 */
ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1))
@interface ZGMTRClusterLowPower : ZGMTRGenericCluster

- (void)sleepWithParams:(ZGMTRLowPowerClusterSleepParams * _Nullable)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(ZGMTRStatusCompletion)completion ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
- (void)sleepWithExpectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedValues expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(ZGMTRStatusCompletion)completion
    ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeGeneratedCommandListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeAcceptedCommandListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeAttributeListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeFeatureMapWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeClusterRevisionWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end

@interface ZGMTRClusterLowPower (Availability)

/**
 * For all instance methods that take a completion (i.e. command invocations),
 * the completion will be called on the provided queue.
 */
- (instancetype _Nullable)initWithDevice:(ZGMTRDevice *)device
                              endpointID:(NSNumber *)endpointID
                                   queue:(dispatch_queue_t)queue ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));

@end

/**
 * Cluster Keypad Input
 *    This cluster provides an interface for controlling a device like a TV using action commands such as UP, DOWN, and SELECT.
 */
ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1))
@interface ZGMTRClusterKeypadInput : ZGMTRGenericCluster

- (void)sendKeyWithParams:(ZGMTRKeypadInputClusterSendKeyParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(void (^)(ZGMTRKeypadInputClusterSendKeyResponseParams * _Nullable data, NSError * _Nullable error))completion ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeGeneratedCommandListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeAcceptedCommandListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeAttributeListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeFeatureMapWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeClusterRevisionWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end

@interface ZGMTRClusterKeypadInput (Availability)

/**
 * For all instance methods that take a completion (i.e. command invocations),
 * the completion will be called on the provided queue.
 */
- (instancetype _Nullable)initWithDevice:(ZGMTRDevice *)device
                              endpointID:(NSNumber *)endpointID
                                   queue:(dispatch_queue_t)queue ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));

@end

/**
 * Cluster Content Launcher
 *    This cluster provides an interface for launching content on a media player device such as a TV or Speaker.
 */
ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1))
@interface ZGMTRClusterContentLauncher : ZGMTRGenericCluster

- (void)launchContentWithParams:(ZGMTRContentLauncherClusterLaunchContentParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(void (^)(ZGMTRContentLauncherClusterLauncherResponseParams * _Nullable data, NSError * _Nullable error))completion ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
- (void)launchURLWithParams:(ZGMTRContentLauncherClusterLaunchURLParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(void (^)(ZGMTRContentLauncherClusterLauncherResponseParams * _Nullable data, NSError * _Nullable error))completion ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
- (void)contentReplicationRequestWithParams:(ZGMTRContentLauncherClusterContentReplicationRequestParams * _Nullable)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(void (^)(ZGMTRContentLauncherClusterContentReplicationResponseParams * _Nullable data, NSError * _Nullable error))completion ZGMTR_PROVISIONALLY_AVAILABLE;
- (void)contentReplicationRequestWithExpectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedValues expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(void (^)(ZGMTRContentLauncherClusterContentReplicationResponseParams * _Nullable data, NSError * _Nullable error))completion
    ZGMTR_PROVISIONALLY_AVAILABLE;
- (void)playPresetWithParams:(ZGMTRContentLauncherClusterPlayPresetParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(ZGMTRStatusCompletion)completion ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeAcceptHeaderWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeSupportedStreamingProtocolsWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));
- (void)writeAttributeSupportedStreamingProtocolsWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));
- (void)writeAttributeSupportedStreamingProtocolsWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs params:(ZGMTRWriteParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeMovableWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributePresetsWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeGeneratedCommandListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeAcceptedCommandListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeAttributeListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeFeatureMapWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeClusterRevisionWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end

@interface ZGMTRClusterContentLauncher (Availability)

/**
 * For all instance methods that take a completion (i.e. command invocations),
 * the completion will be called on the provided queue.
 */
- (instancetype _Nullable)initWithDevice:(ZGMTRDevice *)device
                              endpointID:(NSNumber *)endpointID
                                   queue:(dispatch_queue_t)queue ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));

@end

/**
 * Cluster Audio Output
 *    This cluster provides an interface for controlling the Output on a media device such as a TV.
 */
ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1))
@interface ZGMTRClusterAudioOutput : ZGMTRGenericCluster

- (void)selectOutputWithParams:(ZGMTRAudioOutputClusterSelectOutputParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(ZGMTRStatusCompletion)completion ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
- (void)renameOutputWithParams:(ZGMTRAudioOutputClusterRenameOutputParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(ZGMTRStatusCompletion)completion ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeOutputListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeCurrentOutputWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeGeneratedCommandListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeAcceptedCommandListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeAttributeListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeFeatureMapWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeClusterRevisionWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end

@interface ZGMTRClusterAudioOutput (Availability)

/**
 * For all instance methods that take a completion (i.e. command invocations),
 * the completion will be called on the provided queue.
 */
- (instancetype _Nullable)initWithDevice:(ZGMTRDevice *)device
                              endpointID:(NSNumber *)endpointID
                                   queue:(dispatch_queue_t)queue ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));

@end

/**
 * Cluster Application Launcher
 *    This cluster provides an interface for launching content on a media player device such as a TV or Speaker.
 */
ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1))
@interface ZGMTRClusterApplicationLauncher : ZGMTRGenericCluster

- (void)launchAppWithParams:(ZGMTRApplicationLauncherClusterLaunchAppParams * _Nullable)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(void (^)(ZGMTRApplicationLauncherClusterLauncherResponseParams * _Nullable data, NSError * _Nullable error))completion ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
- (void)launchAppWithExpectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedValues expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(void (^)(ZGMTRApplicationLauncherClusterLauncherResponseParams * _Nullable data, NSError * _Nullable error))completion
    ZGMTR_AVAILABLE(ios(17.4), macos(14.4), watchos(10.4), tvos(17.4));
- (void)stopAppWithParams:(ZGMTRApplicationLauncherClusterStopAppParams * _Nullable)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(void (^)(ZGMTRApplicationLauncherClusterLauncherResponseParams * _Nullable data, NSError * _Nullable error))completion ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
- (void)stopAppWithExpectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedValues expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(void (^)(ZGMTRApplicationLauncherClusterLauncherResponseParams * _Nullable data, NSError * _Nullable error))completion
    ZGMTR_AVAILABLE(ios(17.4), macos(14.4), watchos(10.4), tvos(17.4));
- (void)hideAppWithParams:(ZGMTRApplicationLauncherClusterHideAppParams * _Nullable)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(void (^)(ZGMTRApplicationLauncherClusterLauncherResponseParams * _Nullable data, NSError * _Nullable error))completion ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
- (void)hideAppWithExpectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedValues expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(void (^)(ZGMTRApplicationLauncherClusterLauncherResponseParams * _Nullable data, NSError * _Nullable error))completion
    ZGMTR_AVAILABLE(ios(17.4), macos(14.4), watchos(10.4), tvos(17.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeCatalogListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeCurrentAppWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));
- (void)writeAttributeCurrentAppWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));
- (void)writeAttributeCurrentAppWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs params:(ZGMTRWriteParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeGeneratedCommandListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeAcceptedCommandListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeAttributeListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeFeatureMapWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeClusterRevisionWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end

@interface ZGMTRClusterApplicationLauncher (Availability)

/**
 * For all instance methods that take a completion (i.e. command invocations),
 * the completion will be called on the provided queue.
 */
- (instancetype _Nullable)initWithDevice:(ZGMTRDevice *)device
                              endpointID:(NSNumber *)endpointID
                                   queue:(dispatch_queue_t)queue ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));

@end

/**
 * Cluster Application Basic
 *    This cluster provides information about an application running on a TV or media player device which is represented as an endpoint.
 */
ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1))
@interface ZGMTRClusterApplicationBasic : ZGMTRGenericCluster

- (NSDictionary<NSString *, id> * _Nullable)readAttributeVendorNameWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeVendorIDWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeApplicationNameWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeProductIDWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeApplicationWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeStatusWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeApplicationVersionWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeAllowedVendorListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeGeneratedCommandListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeAcceptedCommandListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeAttributeListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeFeatureMapWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeClusterRevisionWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end

@interface ZGMTRClusterApplicationBasic (Availability)

/**
 * The queue is currently unused, but may be used in the future for calling completions
 * for command invocations if commands are added to this cluster.
 */
- (instancetype _Nullable)initWithDevice:(ZGMTRDevice *)device
                              endpointID:(NSNumber *)endpointID
                                   queue:(dispatch_queue_t)queue ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));

@end

/**
 * Cluster Account Login
 *    This cluster provides commands that facilitate user account login on a Content App or a node. For example, a Content App running on a Video Player device, which is represented as an endpoint (see [TV Architecture]), can use this cluster to help make the user account on the Content App match the user account on the Client.
 */
ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1))
@interface ZGMTRClusterAccountLogin : ZGMTRGenericCluster

- (void)getSetupPINWithParams:(ZGMTRAccountLoginClusterGetSetupPINParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(void (^)(ZGMTRAccountLoginClusterGetSetupPINResponseParams * _Nullable data, NSError * _Nullable error))completion ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
- (void)loginWithParams:(ZGMTRAccountLoginClusterLoginParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(ZGMTRStatusCompletion)completion ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
- (void)logoutWithParams:(ZGMTRAccountLoginClusterLogoutParams * _Nullable)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(ZGMTRStatusCompletion)completion ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
- (void)logoutWithExpectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedValues expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(ZGMTRStatusCompletion)completion
    ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeGeneratedCommandListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeAcceptedCommandListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeAttributeListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeFeatureMapWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeClusterRevisionWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end

@interface ZGMTRClusterAccountLogin (Availability)

/**
 * For all instance methods that take a completion (i.e. command invocations),
 * the completion will be called on the provided queue.
 */
- (instancetype _Nullable)initWithDevice:(ZGMTRDevice *)device
                              endpointID:(NSNumber *)endpointID
                                   queue:(dispatch_queue_t)queue ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));

@end

/**
 * Cluster Content Control
 *    This cluster is used for managing the content control (including "parental control") settings on a media device such as a TV, or Set-top Box.
 */
ZGMTR_PROVISIONALLY_AVAILABLE
@interface ZGMTRClusterContentControl : ZGMTRGenericCluster

- (void)updatePINWithParams:(ZGMTRContentControlClusterUpdatePINParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(ZGMTRStatusCompletion)completion ZGMTR_PROVISIONALLY_AVAILABLE;
- (void)resetPINWithParams:(ZGMTRContentControlClusterResetPINParams * _Nullable)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(void (^)(ZGMTRContentControlClusterResetPINResponseParams * _Nullable data, NSError * _Nullable error))completion ZGMTR_PROVISIONALLY_AVAILABLE;
- (void)resetPINWithExpectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedValues expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(void (^)(ZGMTRContentControlClusterResetPINResponseParams * _Nullable data, NSError * _Nullable error))completion
    ZGMTR_PROVISIONALLY_AVAILABLE;
- (void)enableWithParams:(ZGMTRContentControlClusterEnableParams * _Nullable)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(ZGMTRStatusCompletion)completion ZGMTR_PROVISIONALLY_AVAILABLE;
- (void)enableWithExpectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedValues expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(ZGMTRStatusCompletion)completion
    ZGMTR_PROVISIONALLY_AVAILABLE;
- (void)disableWithParams:(ZGMTRContentControlClusterDisableParams * _Nullable)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(ZGMTRStatusCompletion)completion ZGMTR_PROVISIONALLY_AVAILABLE;
- (void)disableWithExpectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedValues expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(ZGMTRStatusCompletion)completion
    ZGMTR_PROVISIONALLY_AVAILABLE;
- (void)addBonusTimeWithParams:(ZGMTRContentControlClusterAddBonusTimeParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(ZGMTRStatusCompletion)completion ZGMTR_PROVISIONALLY_AVAILABLE;
- (void)setScreenDailyTimeWithParams:(ZGMTRContentControlClusterSetScreenDailyTimeParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(ZGMTRStatusCompletion)completion ZGMTR_PROVISIONALLY_AVAILABLE;
- (void)blockUnratedContentWithParams:(ZGMTRContentControlClusterBlockUnratedContentParams * _Nullable)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(ZGMTRStatusCompletion)completion ZGMTR_PROVISIONALLY_AVAILABLE;
- (void)blockUnratedContentWithExpectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedValues expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(ZGMTRStatusCompletion)completion
    ZGMTR_PROVISIONALLY_AVAILABLE;
- (void)unblockUnratedContentWithParams:(ZGMTRContentControlClusterUnblockUnratedContentParams * _Nullable)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(ZGMTRStatusCompletion)completion ZGMTR_PROVISIONALLY_AVAILABLE;
- (void)unblockUnratedContentWithExpectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedValues expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(ZGMTRStatusCompletion)completion
    ZGMTR_PROVISIONALLY_AVAILABLE;
- (void)setOnDemandRatingThresholdWithParams:(ZGMTRContentControlClusterSetOnDemandRatingThresholdParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(ZGMTRStatusCompletion)completion ZGMTR_PROVISIONALLY_AVAILABLE;
- (void)setScheduledContentRatingThresholdWithParams:(ZGMTRContentControlClusterSetScheduledContentRatingThresholdParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(ZGMTRStatusCompletion)completion ZGMTR_PROVISIONALLY_AVAILABLE;
- (void)addBlockChannelsWithParams:(ZGMTRContentControlClusterAddBlockChannelsParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(ZGMTRStatusCompletion)completion ZGMTR_PROVISIONALLY_AVAILABLE;
- (void)removeBlockChannelsWithParams:(ZGMTRContentControlClusterRemoveBlockChannelsParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(ZGMTRStatusCompletion)completion ZGMTR_PROVISIONALLY_AVAILABLE;
- (void)addBlockApplicationsWithParams:(ZGMTRContentControlClusterAddBlockApplicationsParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(ZGMTRStatusCompletion)completion ZGMTR_PROVISIONALLY_AVAILABLE;
- (void)removeBlockApplicationsWithParams:(ZGMTRContentControlClusterRemoveBlockApplicationsParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(ZGMTRStatusCompletion)completion ZGMTR_PROVISIONALLY_AVAILABLE;
- (void)setBlockContentTimeWindowWithParams:(ZGMTRContentControlClusterSetBlockContentTimeWindowParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(ZGMTRStatusCompletion)completion ZGMTR_PROVISIONALLY_AVAILABLE;
- (void)removeBlockContentTimeWindowWithParams:(ZGMTRContentControlClusterRemoveBlockContentTimeWindowParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(ZGMTRStatusCompletion)completion ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeEnabledWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeOnDemandRatingsWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeOnDemandRatingThresholdWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeScheduledContentRatingsWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeScheduledContentRatingThresholdWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeScreenDailyTimeWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeRemainingScreenTimeWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeBlockUnratedWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeBlockChannelListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeBlockApplicationListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeBlockContentTimeWindowWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeGeneratedCommandListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeAcceptedCommandListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeAttributeListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeFeatureMapWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeClusterRevisionWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end

@interface ZGMTRClusterContentControl (Availability)

/**
 * For all instance methods that take a completion (i.e. command invocations),
 * the completion will be called on the provided queue.
 */
- (instancetype _Nullable)initWithDevice:(ZGMTRDevice *)device
                              endpointID:(NSNumber *)endpointID
                                   queue:(dispatch_queue_t)queue ZGMTR_PROVISIONALLY_AVAILABLE;

@end

/**
 * Cluster Content App Observer
 *    This cluster provides an interface for sending targeted commands to an Observer of a Content App on a Video Player device such as a Streaming Media Player, Smart TV or Smart Screen. The cluster server for Content App Observer is implemented by an endpoint that communicates with a Content App, such as a Casting Video Client. The cluster client for Content App Observer is implemented by a Content App endpoint. A Content App is informed of the NodeId of an Observer when a binding is set on the Content App. The Content App can then send the ContentAppMessage to the Observer (server cluster), and the Observer responds with a ContentAppMessageResponse.
 */
ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4))
@interface ZGMTRClusterContentAppObserver : ZGMTRGenericCluster

- (void)contentAppMessageWithParams:(ZGMTRContentAppObserverClusterContentAppMessageParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(void (^)(ZGMTRContentAppObserverClusterContentAppMessageResponseParams * _Nullable data, NSError * _Nullable error))completion ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeGeneratedCommandListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeAcceptedCommandListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeAttributeListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeFeatureMapWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeClusterRevisionWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end

@interface ZGMTRClusterContentAppObserver (Availability)

/**
 * For all instance methods that take a completion (i.e. command invocations),
 * the completion will be called on the provided queue.
 */
- (instancetype _Nullable)initWithDevice:(ZGMTRDevice *)device
                              endpointID:(NSNumber *)endpointID
                                   queue:(dispatch_queue_t)queue ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));

@end

/**
 * Cluster Media File Management
 *    This cluster provides an interface for managing and sharing media files on devices such as Streaming Speakers, Smart TVs, or other media playback devices.
 */
ZGMTR_PROVISIONALLY_AVAILABLE
@interface ZGMTRClusterMediaFileManagement : ZGMTRGenericCluster

- (void)addFileWithParams:(ZGMTRMediaFileManagementClusterAddFileParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(void (^)(ZGMTRMediaFileManagementClusterAddFileResponseParams * _Nullable data, NSError * _Nullable error))completion ZGMTR_PROVISIONALLY_AVAILABLE;
- (void)deleteFileWithParams:(ZGMTRMediaFileManagementClusterDeleteFileParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(ZGMTRStatusCompletion)completion ZGMTR_PROVISIONALLY_AVAILABLE;
- (void)requestSharedFilesWithParams:(ZGMTRMediaFileManagementClusterRequestSharedFilesParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(ZGMTRStatusCompletion)completion ZGMTR_PROVISIONALLY_AVAILABLE;
- (void)getSharedFileWithParams:(ZGMTRMediaFileManagementClusterGetSharedFileParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(void (^)(ZGMTRMediaFileManagementClusterGetSharedFileResponseParams * _Nullable data, NSError * _Nullable error))completion ZGMTR_PROVISIONALLY_AVAILABLE;
- (void)offerFileWithParams:(ZGMTRMediaFileManagementClusterOfferFileParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(ZGMTRStatusCompletion)completion ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeTotalStorageWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeAvailableStorageWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeAvailableFilesWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeSupportedMimeTypesWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeGeneratedCommandListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeAcceptedCommandListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeAttributeListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeFeatureMapWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeClusterRevisionWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end

@interface ZGMTRClusterMediaFileManagement (Availability)

/**
 * For all instance methods that take a completion (i.e. command invocations),
 * the completion will be called on the provided queue.
 */
- (instancetype _Nullable)initWithDevice:(ZGMTRDevice *)device
                              endpointID:(NSNumber *)endpointID
                                   queue:(dispatch_queue_t)queue ZGMTR_PROVISIONALLY_AVAILABLE;

@end

/**
 * Cluster Audio Control
 *    This cluster provides attributes and commands to control the audio output volume and frequency corrections of a device.
 */
ZGMTR_PROVISIONALLY_AVAILABLE
@interface ZGMTRClusterAudioControl : ZGMTRGenericCluster

- (void)muteWithParams:(ZGMTRAudioControlClusterMuteParams * _Nullable)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(ZGMTRStatusCompletion)completion ZGMTR_PROVISIONALLY_AVAILABLE;
- (void)muteWithExpectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedValues expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(ZGMTRStatusCompletion)completion
    ZGMTR_PROVISIONALLY_AVAILABLE;
- (void)unmuteWithParams:(ZGMTRAudioControlClusterUnmuteParams * _Nullable)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(ZGMTRStatusCompletion)completion ZGMTR_PROVISIONALLY_AVAILABLE;
- (void)unmuteWithExpectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedValues expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(ZGMTRStatusCompletion)completion
    ZGMTR_PROVISIONALLY_AVAILABLE;
- (void)toggleMutedWithParams:(ZGMTRAudioControlClusterToggleMutedParams * _Nullable)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(ZGMTRStatusCompletion)completion ZGMTR_PROVISIONALLY_AVAILABLE;
- (void)toggleMutedWithExpectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedValues expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(ZGMTRStatusCompletion)completion
    ZGMTR_PROVISIONALLY_AVAILABLE;
- (void)setVolumeWithParams:(ZGMTRAudioControlClusterSetVolumeParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(ZGMTRStatusCompletion)completion ZGMTR_PROVISIONALLY_AVAILABLE;
- (void)increaseVolumeWithParams:(ZGMTRAudioControlClusterIncreaseVolumeParams * _Nullable)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(ZGMTRStatusCompletion)completion ZGMTR_PROVISIONALLY_AVAILABLE;
- (void)increaseVolumeWithExpectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedValues expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(ZGMTRStatusCompletion)completion
    ZGMTR_PROVISIONALLY_AVAILABLE;
- (void)decreaseVolumeWithParams:(ZGMTRAudioControlClusterDecreaseVolumeParams * _Nullable)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(ZGMTRStatusCompletion)completion ZGMTR_PROVISIONALLY_AVAILABLE;
- (void)decreaseVolumeWithExpectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedValues expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(ZGMTRStatusCompletion)completion
    ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeSoftMutedWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributePhysicallyMutedWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeVolumeWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeMinDeviceVolumeWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeMaxDeviceVolumeWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeMaxDeviceVolumeDBWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeMaxUserVolumeWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;
- (void)writeAttributeMaxUserVolumeWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs ZGMTR_PROVISIONALLY_AVAILABLE;
- (void)writeAttributeMaxUserVolumeWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs params:(ZGMTRWriteParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeDefaultStepSizeWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;
- (void)writeAttributeDefaultStepSizeWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs ZGMTR_PROVISIONALLY_AVAILABLE;
- (void)writeAttributeDefaultStepSizeWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs params:(ZGMTRWriteParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeSetVolumeUnmutePolicyWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;
- (void)writeAttributeSetVolumeUnmutePolicyWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs ZGMTR_PROVISIONALLY_AVAILABLE;
- (void)writeAttributeSetVolumeUnmutePolicyWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs params:(ZGMTRWriteParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeIncreaseVolumeUnmutePolicyWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;
- (void)writeAttributeIncreaseVolumeUnmutePolicyWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs ZGMTR_PROVISIONALLY_AVAILABLE;
- (void)writeAttributeIncreaseVolumeUnmutePolicyWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs params:(ZGMTRWriteParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeIncreaseVolumeUnmuteVolumeWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;
- (void)writeAttributeIncreaseVolumeUnmuteVolumeWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs ZGMTR_PROVISIONALLY_AVAILABLE;
- (void)writeAttributeIncreaseVolumeUnmuteVolumeWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs params:(ZGMTRWriteParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeDecreaseVolumeUnmutePolicyWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;
- (void)writeAttributeDecreaseVolumeUnmutePolicyWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs ZGMTR_PROVISIONALLY_AVAILABLE;
- (void)writeAttributeDecreaseVolumeUnmutePolicyWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs params:(ZGMTRWriteParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeStartUpMutedWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;
- (void)writeAttributeStartUpMutedWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs ZGMTR_PROVISIONALLY_AVAILABLE;
- (void)writeAttributeStartUpMutedWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs params:(ZGMTRWriteParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeStartUpVolumeWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;
- (void)writeAttributeStartUpVolumeWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs ZGMTR_PROVISIONALLY_AVAILABLE;
- (void)writeAttributeStartUpVolumeWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs params:(ZGMTRWriteParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeBassWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;
- (void)writeAttributeBassWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs ZGMTR_PROVISIONALLY_AVAILABLE;
- (void)writeAttributeBassWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs params:(ZGMTRWriteParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeMidWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;
- (void)writeAttributeMidWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs ZGMTR_PROVISIONALLY_AVAILABLE;
- (void)writeAttributeMidWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs params:(ZGMTRWriteParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeTrebleWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;
- (void)writeAttributeTrebleWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs ZGMTR_PROVISIONALLY_AVAILABLE;
- (void)writeAttributeTrebleWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs params:(ZGMTRWriteParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeMinCorrectionWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeMaxCorrectionWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeGeneratedCommandListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeAcceptedCommandListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeAttributeListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeFeatureMapWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeClusterRevisionWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end

@interface ZGMTRClusterAudioControl (Availability)

/**
 * For all instance methods that take a completion (i.e. command invocations),
 * the completion will be called on the provided queue.
 */
- (instancetype _Nullable)initWithDevice:(ZGMTRDevice *)device
                              endpointID:(NSNumber *)endpointID
                                   queue:(dispatch_queue_t)queue ZGMTR_PROVISIONALLY_AVAILABLE;

@end

/**
 * Cluster Zone Management
 *    This cluster provides an interface to manage regions of interest, or Zones, which can be either manufacturer or user defined.
 */
ZGMTR_PROVISIONALLY_AVAILABLE
@interface ZGMTRClusterZoneManagement : ZGMTRGenericCluster

- (void)createTwoDCartesianZoneWithParams:(ZGMTRZoneManagementClusterCreateTwoDCartesianZoneParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(void (^)(ZGMTRZoneManagementClusterCreateTwoDCartesianZoneResponseParams * _Nullable data, NSError * _Nullable error))completion ZGMTR_PROVISIONALLY_AVAILABLE;
- (void)updateTwoDCartesianZoneWithParams:(ZGMTRZoneManagementClusterUpdateTwoDCartesianZoneParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(ZGMTRStatusCompletion)completion ZGMTR_PROVISIONALLY_AVAILABLE;
- (void)removeZoneWithParams:(ZGMTRZoneManagementClusterRemoveZoneParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(ZGMTRStatusCompletion)completion ZGMTR_PROVISIONALLY_AVAILABLE;
- (void)createOrUpdateTriggerWithParams:(ZGMTRZoneManagementClusterCreateOrUpdateTriggerParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(ZGMTRStatusCompletion)completion ZGMTR_PROVISIONALLY_AVAILABLE;
- (void)removeTriggerWithParams:(ZGMTRZoneManagementClusterRemoveTriggerParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(ZGMTRStatusCompletion)completion ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeMaxUserDefinedZonesWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeMaxZonesWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeZonesWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeTriggersWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeSensitivityMaxWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeSensitivityWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;
- (void)writeAttributeSensitivityWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs ZGMTR_PROVISIONALLY_AVAILABLE;
- (void)writeAttributeSensitivityWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs params:(ZGMTRWriteParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeTwoDCartesianMaxWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeGeneratedCommandListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeAcceptedCommandListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeAttributeListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeFeatureMapWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeClusterRevisionWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end

@interface ZGMTRClusterZoneManagement (Availability)

/**
 * For all instance methods that take a completion (i.e. command invocations),
 * the completion will be called on the provided queue.
 */
- (instancetype _Nullable)initWithDevice:(ZGMTRDevice *)device
                              endpointID:(NSNumber *)endpointID
                                   queue:(dispatch_queue_t)queue ZGMTR_PROVISIONALLY_AVAILABLE;

@end

/**
 * Cluster Camera AV Stream Management
 *    The Camera AV Stream Management cluster is used to allow clients to manage, control, and configure various audio, video, and snapshot streams on a camera.
 */
ZGMTR_PROVISIONALLY_AVAILABLE
@interface ZGMTRClusterCameraAVStreamManagement : ZGMTRGenericCluster

- (void)audioStreamAllocateWithParams:(ZGMTRCameraAVStreamManagementClusterAudioStreamAllocateParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(void (^)(ZGMTRCameraAVStreamManagementClusterAudioStreamAllocateResponseParams * _Nullable data, NSError * _Nullable error))completion ZGMTR_PROVISIONALLY_AVAILABLE;
- (void)audioStreamDeallocateWithParams:(ZGMTRCameraAVStreamManagementClusterAudioStreamDeallocateParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(ZGMTRStatusCompletion)completion ZGMTR_PROVISIONALLY_AVAILABLE;
- (void)videoStreamAllocateWithParams:(ZGMTRCameraAVStreamManagementClusterVideoStreamAllocateParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(void (^)(ZGMTRCameraAVStreamManagementClusterVideoStreamAllocateResponseParams * _Nullable data, NSError * _Nullable error))completion ZGMTR_PROVISIONALLY_AVAILABLE;
- (void)videoStreamModifyWithParams:(ZGMTRCameraAVStreamManagementClusterVideoStreamModifyParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(ZGMTRStatusCompletion)completion ZGMTR_PROVISIONALLY_AVAILABLE;
- (void)videoStreamDeallocateWithParams:(ZGMTRCameraAVStreamManagementClusterVideoStreamDeallocateParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(ZGMTRStatusCompletion)completion ZGMTR_PROVISIONALLY_AVAILABLE;
- (void)snapshotStreamAllocateWithParams:(ZGMTRCameraAVStreamManagementClusterSnapshotStreamAllocateParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(void (^)(ZGMTRCameraAVStreamManagementClusterSnapshotStreamAllocateResponseParams * _Nullable data, NSError * _Nullable error))completion ZGMTR_PROVISIONALLY_AVAILABLE;
- (void)snapshotStreamModifyWithParams:(ZGMTRCameraAVStreamManagementClusterSnapshotStreamModifyParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(ZGMTRStatusCompletion)completion ZGMTR_PROVISIONALLY_AVAILABLE;
- (void)snapshotStreamDeallocateWithParams:(ZGMTRCameraAVStreamManagementClusterSnapshotStreamDeallocateParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(ZGMTRStatusCompletion)completion ZGMTR_PROVISIONALLY_AVAILABLE;
- (void)setStreamPrioritiesWithParams:(ZGMTRCameraAVStreamManagementClusterSetStreamPrioritiesParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(ZGMTRStatusCompletion)completion ZGMTR_PROVISIONALLY_AVAILABLE;
- (void)captureSnapshotWithParams:(ZGMTRCameraAVStreamManagementClusterCaptureSnapshotParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(void (^)(ZGMTRCameraAVStreamManagementClusterCaptureSnapshotResponseParams * _Nullable data, NSError * _Nullable error))completion ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeMaxConcurrentEncodersWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeMaxEncodedPixelRateWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeVideoSensorParamsWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeNightVisionUsesInfraredWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeMinViewportResolutionWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeRateDistortionTradeOffPointsWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeMaxContentBufferSizeWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeMicrophoneCapabilitiesWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeSpeakerCapabilitiesWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeTwoWayTalkSupportWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeSnapshotCapabilitiesWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeMaxNetworkBandwidthWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeCurrentFrameRateWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeHDRModeEnabledWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;
- (void)writeAttributeHDRModeEnabledWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs ZGMTR_PROVISIONALLY_AVAILABLE;
- (void)writeAttributeHDRModeEnabledWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs params:(ZGMTRWriteParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeSupportedStreamUsagesWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeAllocatedVideoStreamsWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeAllocatedAudioStreamsWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeAllocatedSnapshotStreamsWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeStreamUsagePrioritiesWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeSoftRecordingPrivacyModeEnabledWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;
- (void)writeAttributeSoftRecordingPrivacyModeEnabledWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs ZGMTR_PROVISIONALLY_AVAILABLE;
- (void)writeAttributeSoftRecordingPrivacyModeEnabledWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs params:(ZGMTRWriteParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeSoftLivestreamPrivacyModeEnabledWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;
- (void)writeAttributeSoftLivestreamPrivacyModeEnabledWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs ZGMTR_PROVISIONALLY_AVAILABLE;
- (void)writeAttributeSoftLivestreamPrivacyModeEnabledWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs params:(ZGMTRWriteParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeHardPrivacyModeOnWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeNightVisionWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;
- (void)writeAttributeNightVisionWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs ZGMTR_PROVISIONALLY_AVAILABLE;
- (void)writeAttributeNightVisionWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs params:(ZGMTRWriteParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeNightVisionIllumWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;
- (void)writeAttributeNightVisionIllumWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs ZGMTR_PROVISIONALLY_AVAILABLE;
- (void)writeAttributeNightVisionIllumWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs params:(ZGMTRWriteParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeViewportWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;
- (void)writeAttributeViewportWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs ZGMTR_PROVISIONALLY_AVAILABLE;
- (void)writeAttributeViewportWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs params:(ZGMTRWriteParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeSpeakerMutedWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;
- (void)writeAttributeSpeakerMutedWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs ZGMTR_PROVISIONALLY_AVAILABLE;
- (void)writeAttributeSpeakerMutedWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs params:(ZGMTRWriteParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeSpeakerVolumeLevelWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;
- (void)writeAttributeSpeakerVolumeLevelWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs ZGMTR_PROVISIONALLY_AVAILABLE;
- (void)writeAttributeSpeakerVolumeLevelWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs params:(ZGMTRWriteParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeSpeakerMaxLevelWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeSpeakerMinLevelWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeMicrophoneMutedWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;
- (void)writeAttributeMicrophoneMutedWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs ZGMTR_PROVISIONALLY_AVAILABLE;
- (void)writeAttributeMicrophoneMutedWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs params:(ZGMTRWriteParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeMicrophoneVolumeLevelWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;
- (void)writeAttributeMicrophoneVolumeLevelWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs ZGMTR_PROVISIONALLY_AVAILABLE;
- (void)writeAttributeMicrophoneVolumeLevelWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs params:(ZGMTRWriteParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeMicrophoneMaxLevelWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeMicrophoneMinLevelWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeMicrophoneAGCEnabledWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;
- (void)writeAttributeMicrophoneAGCEnabledWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs ZGMTR_PROVISIONALLY_AVAILABLE;
- (void)writeAttributeMicrophoneAGCEnabledWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs params:(ZGMTRWriteParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeImageRotationWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;
- (void)writeAttributeImageRotationWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs ZGMTR_PROVISIONALLY_AVAILABLE;
- (void)writeAttributeImageRotationWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs params:(ZGMTRWriteParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeImageFlipHorizontalWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;
- (void)writeAttributeImageFlipHorizontalWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs ZGMTR_PROVISIONALLY_AVAILABLE;
- (void)writeAttributeImageFlipHorizontalWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs params:(ZGMTRWriteParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeImageFlipVerticalWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;
- (void)writeAttributeImageFlipVerticalWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs ZGMTR_PROVISIONALLY_AVAILABLE;
- (void)writeAttributeImageFlipVerticalWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs params:(ZGMTRWriteParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeLocalVideoRecordingEnabledWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;
- (void)writeAttributeLocalVideoRecordingEnabledWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs ZGMTR_PROVISIONALLY_AVAILABLE;
- (void)writeAttributeLocalVideoRecordingEnabledWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs params:(ZGMTRWriteParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeLocalSnapshotRecordingEnabledWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;
- (void)writeAttributeLocalSnapshotRecordingEnabledWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs ZGMTR_PROVISIONALLY_AVAILABLE;
- (void)writeAttributeLocalSnapshotRecordingEnabledWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs params:(ZGMTRWriteParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeStatusLightEnabledWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;
- (void)writeAttributeStatusLightEnabledWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs ZGMTR_PROVISIONALLY_AVAILABLE;
- (void)writeAttributeStatusLightEnabledWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs params:(ZGMTRWriteParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeStatusLightBrightnessWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;
- (void)writeAttributeStatusLightBrightnessWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs ZGMTR_PROVISIONALLY_AVAILABLE;
- (void)writeAttributeStatusLightBrightnessWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs params:(ZGMTRWriteParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeImageRotationDiscreteAnglesWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;
- (void)writeAttributeImageRotationDiscreteAnglesWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs ZGMTR_PROVISIONALLY_AVAILABLE;
- (void)writeAttributeImageRotationDiscreteAnglesWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs params:(ZGMTRWriteParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeGeneratedCommandListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeAcceptedCommandListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeAttributeListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeFeatureMapWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeClusterRevisionWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end

@interface ZGMTRClusterCameraAVStreamManagement (Availability)

/**
 * For all instance methods that take a completion (i.e. command invocations),
 * the completion will be called on the provided queue.
 */
- (instancetype _Nullable)initWithDevice:(ZGMTRDevice *)device
                              endpointID:(NSNumber *)endpointID
                                   queue:(dispatch_queue_t)queue ZGMTR_PROVISIONALLY_AVAILABLE;

@end

/**
 * Cluster Camera AV Settings User Level Management
 *    This cluster provides an interface into controls associated with the operation of a device that provides pan, tilt, and zoom functions, either mechanically, or against a digital image.
 */
ZGMTR_PROVISIONALLY_AVAILABLE
@interface ZGMTRClusterCameraAVSettingsUserLevelManagement : ZGMTRGenericCluster

- (void)MPTZSetPositionWithParams:(ZGMTRCameraAVSettingsUserLevelManagementClusterMPTZSetPositionParams * _Nullable)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(ZGMTRStatusCompletion)completion ZGMTR_PROVISIONALLY_AVAILABLE;
- (void)MPTZSetPositionWithExpectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedValues expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(ZGMTRStatusCompletion)completion
    ZGMTR_PROVISIONALLY_AVAILABLE;
- (void)MPTZRelativeMoveWithParams:(ZGMTRCameraAVSettingsUserLevelManagementClusterMPTZRelativeMoveParams * _Nullable)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(ZGMTRStatusCompletion)completion ZGMTR_PROVISIONALLY_AVAILABLE;
- (void)MPTZRelativeMoveWithExpectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedValues expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(ZGMTRStatusCompletion)completion
    ZGMTR_PROVISIONALLY_AVAILABLE;
- (void)MPTZMoveToPresetWithParams:(ZGMTRCameraAVSettingsUserLevelManagementClusterMPTZMoveToPresetParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(ZGMTRStatusCompletion)completion ZGMTR_PROVISIONALLY_AVAILABLE;
- (void)MPTZSavePresetWithParams:(ZGMTRCameraAVSettingsUserLevelManagementClusterMPTZSavePresetParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(ZGMTRStatusCompletion)completion ZGMTR_PROVISIONALLY_AVAILABLE;
- (void)MPTZRemovePresetWithParams:(ZGMTRCameraAVSettingsUserLevelManagementClusterMPTZRemovePresetParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(ZGMTRStatusCompletion)completion ZGMTR_PROVISIONALLY_AVAILABLE;
- (void)DPTZSetViewportWithParams:(ZGMTRCameraAVSettingsUserLevelManagementClusterDPTZSetViewportParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(ZGMTRStatusCompletion)completion ZGMTR_PROVISIONALLY_AVAILABLE;
- (void)DPTZRelativeMoveWithParams:(ZGMTRCameraAVSettingsUserLevelManagementClusterDPTZRelativeMoveParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(ZGMTRStatusCompletion)completion ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeMPTZPositionWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeMaxPresetsWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeMPTZPresetsWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeDPTZStreamsWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeZoomMaxWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeTiltMinWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeTiltMaxWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributePanMinWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributePanMaxWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeMovementStateWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeGeneratedCommandListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeAcceptedCommandListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeAttributeListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeFeatureMapWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeClusterRevisionWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end

@interface ZGMTRClusterCameraAVSettingsUserLevelManagement (Availability)

/**
 * For all instance methods that take a completion (i.e. command invocations),
 * the completion will be called on the provided queue.
 */
- (instancetype _Nullable)initWithDevice:(ZGMTRDevice *)device
                              endpointID:(NSNumber *)endpointID
                                   queue:(dispatch_queue_t)queue ZGMTR_PROVISIONALLY_AVAILABLE;

@end

/**
 * Cluster WebRTC Transport Provider
 *    The WebRTC transport provider cluster provides a way for stream providers (e.g. Cameras) to stream or receive their data through WebRTC.
 */
ZGMTR_PROVISIONALLY_AVAILABLE
@interface ZGMTRClusterWebRTCTransportProvider : ZGMTRGenericCluster

- (void)solicitOfferWithParams:(ZGMTRWebRTCTransportProviderClusterSolicitOfferParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(void (^)(ZGMTRWebRTCTransportProviderClusterSolicitOfferResponseParams * _Nullable data, NSError * _Nullable error))completion ZGMTR_PROVISIONALLY_AVAILABLE;
- (void)provideOfferWithParams:(ZGMTRWebRTCTransportProviderClusterProvideOfferParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(void (^)(ZGMTRWebRTCTransportProviderClusterProvideOfferResponseParams * _Nullable data, NSError * _Nullable error))completion ZGMTR_PROVISIONALLY_AVAILABLE;
- (void)provideAnswerWithParams:(ZGMTRWebRTCTransportProviderClusterProvideAnswerParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(ZGMTRStatusCompletion)completion ZGMTR_PROVISIONALLY_AVAILABLE;
- (void)provideICECandidatesWithParams:(ZGMTRWebRTCTransportProviderClusterProvideICECandidatesParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(ZGMTRStatusCompletion)completion ZGMTR_PROVISIONALLY_AVAILABLE;
- (void)endSessionWithParams:(ZGMTRWebRTCTransportProviderClusterEndSessionParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(ZGMTRStatusCompletion)completion ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeCurrentSessionsWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeGeneratedCommandListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeAcceptedCommandListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeAttributeListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeFeatureMapWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeClusterRevisionWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end

@interface ZGMTRClusterWebRTCTransportProvider (Availability)

/**
 * For all instance methods that take a completion (i.e. command invocations),
 * the completion will be called on the provided queue.
 */
- (instancetype _Nullable)initWithDevice:(ZGMTRDevice *)device
                              endpointID:(NSNumber *)endpointID
                                   queue:(dispatch_queue_t)queue ZGMTR_PROVISIONALLY_AVAILABLE;

@end

/**
 * Cluster WebRTC Transport Requestor
 *    The WebRTC transport requestor cluster provides a way for stream consumers (e.g. ZGMatter Stream Viewer) to establish a WebRTC connection with a stream provider.
 */
ZGMTR_PROVISIONALLY_AVAILABLE
@interface ZGMTRClusterWebRTCTransportRequestor : ZGMTRGenericCluster

- (void)offerWithParams:(ZGMTRWebRTCTransportRequestorClusterOfferParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(ZGMTRStatusCompletion)completion ZGMTR_PROVISIONALLY_AVAILABLE;
- (void)answerWithParams:(ZGMTRWebRTCTransportRequestorClusterAnswerParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(ZGMTRStatusCompletion)completion ZGMTR_PROVISIONALLY_AVAILABLE;
- (void)ICECandidatesWithParams:(ZGMTRWebRTCTransportRequestorClusterICECandidatesParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(ZGMTRStatusCompletion)completion ZGMTR_PROVISIONALLY_AVAILABLE;
- (void)endWithParams:(ZGMTRWebRTCTransportRequestorClusterEndParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(ZGMTRStatusCompletion)completion ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeCurrentSessionsWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeGeneratedCommandListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeAcceptedCommandListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeAttributeListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeFeatureMapWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeClusterRevisionWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end

@interface ZGMTRClusterWebRTCTransportRequestor (Availability)

/**
 * For all instance methods that take a completion (i.e. command invocations),
 * the completion will be called on the provided queue.
 */
- (instancetype _Nullable)initWithDevice:(ZGMTRDevice *)device
                              endpointID:(NSNumber *)endpointID
                                   queue:(dispatch_queue_t)queue ZGMTR_PROVISIONALLY_AVAILABLE;

@end

/**
 * Cluster Push AV Stream Transport
 *    This cluster implements the upload of Audio and Video streams from the Push AV Stream Transport Cluster using suitable push-based transports.
 */
ZGMTR_PROVISIONALLY_AVAILABLE
@interface ZGMTRClusterPushAVStreamTransport : ZGMTRGenericCluster

- (void)allocatePushTransportWithParams:(ZGMTRPushAVStreamTransportClusterAllocatePushTransportParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(void (^)(ZGMTRPushAVStreamTransportClusterAllocatePushTransportResponseParams * _Nullable data, NSError * _Nullable error))completion ZGMTR_PROVISIONALLY_AVAILABLE;
- (void)deallocatePushTransportWithParams:(ZGMTRPushAVStreamTransportClusterDeallocatePushTransportParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(ZGMTRStatusCompletion)completion ZGMTR_PROVISIONALLY_AVAILABLE;
- (void)modifyPushTransportWithParams:(ZGMTRPushAVStreamTransportClusterModifyPushTransportParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(ZGMTRStatusCompletion)completion ZGMTR_PROVISIONALLY_AVAILABLE;
- (void)setTransportStatusWithParams:(ZGMTRPushAVStreamTransportClusterSetTransportStatusParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(ZGMTRStatusCompletion)completion ZGMTR_PROVISIONALLY_AVAILABLE;
- (void)manuallyTriggerTransportWithParams:(ZGMTRPushAVStreamTransportClusterManuallyTriggerTransportParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(ZGMTRStatusCompletion)completion ZGMTR_PROVISIONALLY_AVAILABLE;
- (void)findTransportWithParams:(ZGMTRPushAVStreamTransportClusterFindTransportParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(void (^)(ZGMTRPushAVStreamTransportClusterFindTransportResponseParams * _Nullable data, NSError * _Nullable error))completion ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeSupportedFormatsWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeCurrentConnectionsWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeGeneratedCommandListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeAcceptedCommandListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeAttributeListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeFeatureMapWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeClusterRevisionWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end

@interface ZGMTRClusterPushAVStreamTransport (Availability)

/**
 * For all instance methods that take a completion (i.e. command invocations),
 * the completion will be called on the provided queue.
 */
- (instancetype _Nullable)initWithDevice:(ZGMTRDevice *)device
                              endpointID:(NSNumber *)endpointID
                                   queue:(dispatch_queue_t)queue ZGMTR_PROVISIONALLY_AVAILABLE;

@end

/**
 * Cluster Chime
 *    This cluster provides facilities to configure and play Chime sounds, such as those used in a doorbell.
 */
ZGMTR_PROVISIONALLY_AVAILABLE
@interface ZGMTRClusterChime : ZGMTRGenericCluster

- (void)playChimeSoundWithParams:(ZGMTRChimeClusterPlayChimeSoundParams * _Nullable)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(ZGMTRStatusCompletion)completion ZGMTR_PROVISIONALLY_AVAILABLE;
- (void)playChimeSoundWithExpectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedValues expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(ZGMTRStatusCompletion)completion
    ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeInstalledChimeSoundsWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeSelectedChimeWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;
- (void)writeAttributeSelectedChimeWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs ZGMTR_PROVISIONALLY_AVAILABLE;
- (void)writeAttributeSelectedChimeWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs params:(ZGMTRWriteParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeEnabledWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;
- (void)writeAttributeEnabledWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs ZGMTR_PROVISIONALLY_AVAILABLE;
- (void)writeAttributeEnabledWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs params:(ZGMTRWriteParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeGeneratedCommandListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeAcceptedCommandListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeAttributeListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeFeatureMapWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeClusterRevisionWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end

@interface ZGMTRClusterChime (Availability)

/**
 * For all instance methods that take a completion (i.e. command invocations),
 * the completion will be called on the provided queue.
 */
- (instancetype _Nullable)initWithDevice:(ZGMTRDevice *)device
                              endpointID:(NSNumber *)endpointID
                                   queue:(dispatch_queue_t)queue ZGMTR_PROVISIONALLY_AVAILABLE;

@end

/**
 * Cluster AV Analysis
 *    This server cluster provides an interface for controlling events pertaining to AV analysis.
 */
ZGMTR_PROVISIONALLY_AVAILABLE
@interface ZGMTRClusterAVAnalysis : ZGMTRGenericCluster

- (void)enableContextTriggersWithParams:(ZGMTRAVAnalysisClusterEnableContextTriggersParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(ZGMTRStatusCompletion)completion ZGMTR_PROVISIONALLY_AVAILABLE;
- (void)disableContextTriggersWithParams:(ZGMTRAVAnalysisClusterDisableContextTriggersParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(ZGMTRStatusCompletion)completion ZGMTR_PROVISIONALLY_AVAILABLE;
- (void)establishAnalysisStreamWithParams:(ZGMTRAVAnalysisClusterEstablishAnalysisStreamParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(void (^)(ZGMTRAVAnalysisClusterEstablishAnalysisStreamResponseParams * _Nullable data, NSError * _Nullable error))completion ZGMTR_PROVISIONALLY_AVAILABLE;
- (void)activateAnalysisStreamWithParams:(ZGMTRAVAnalysisClusterActivateAnalysisStreamParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(ZGMTRStatusCompletion)completion ZGMTR_PROVISIONALLY_AVAILABLE;
- (void)deactivateAnalysisStreamWithParams:(ZGMTRAVAnalysisClusterDeactivateAnalysisStreamParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(ZGMTRStatusCompletion)completion ZGMTR_PROVISIONALLY_AVAILABLE;
- (void)removeAnalysisStreamWithParams:(ZGMTRAVAnalysisClusterRemoveAnalysisStreamParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(ZGMTRStatusCompletion)completion ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeSupportedAmbientContextsWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeActiveAmbientContextTriggersWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeMaxAnalysisStreamCountWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeCurrentAnalysisStreamCountWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeAnalysisStreamsWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeTrackingEnabledWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;
- (void)writeAttributeTrackingEnabledWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs ZGMTR_PROVISIONALLY_AVAILABLE;
- (void)writeAttributeTrackingEnabledWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs params:(ZGMTRWriteParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeGeneratedCommandListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeAcceptedCommandListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeAttributeListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeFeatureMapWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeClusterRevisionWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end

@interface ZGMTRClusterAVAnalysis (Availability)

/**
 * For all instance methods that take a completion (i.e. command invocations),
 * the completion will be called on the provided queue.
 */
- (instancetype _Nullable)initWithDevice:(ZGMTRDevice *)device
                              endpointID:(NSNumber *)endpointID
                                   queue:(dispatch_queue_t)queue ZGMTR_PROVISIONALLY_AVAILABLE;

@end

/**
 * Cluster Commodity Tariff
 *    The CommodityTariffCluster provides the mechanism for communicating Commodity Tariff information within the premises.
 */
ZGMTR_PROVISIONALLY_AVAILABLE
@interface ZGMTRClusterCommodityTariff : ZGMTRGenericCluster

- (void)getTariffComponentWithParams:(ZGMTRCommodityTariffClusterGetTariffComponentParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(void (^)(ZGMTRCommodityTariffClusterGetTariffComponentResponseParams * _Nullable data, NSError * _Nullable error))completion ZGMTR_PROVISIONALLY_AVAILABLE;
- (void)getDayEntryWithParams:(ZGMTRCommodityTariffClusterGetDayEntryParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(void (^)(ZGMTRCommodityTariffClusterGetDayEntryResponseParams * _Nullable data, NSError * _Nullable error))completion ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeTariffInfoWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeTariffUnitWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeStartDateWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeDayEntriesWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeDayPatternsWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeCalendarPeriodsWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeIndividualDaysWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeCurrentDayWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeNextDayWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeCurrentDayEntryWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeCurrentDayEntryDateWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeNextDayEntryWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeNextDayEntryDateWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeTariffComponentsWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeTariffPeriodsWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeCurrentTariffComponentsWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeNextTariffComponentsWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeDefaultRandomizationOffsetWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeDefaultRandomizationTypeWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeGeneratedCommandListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeAcceptedCommandListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeAttributeListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeFeatureMapWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeClusterRevisionWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end

@interface ZGMTRClusterCommodityTariff (Availability)

/**
 * For all instance methods that take a completion (i.e. command invocations),
 * the completion will be called on the provided queue.
 */
- (instancetype _Nullable)initWithDevice:(ZGMTRDevice *)device
                              endpointID:(NSNumber *)endpointID
                                   queue:(dispatch_queue_t)queue ZGMTR_PROVISIONALLY_AVAILABLE;

@end

/**
 * Cluster Ecosystem Information
 *    Provides extended device information for all the logical devices represented by a Bridged Node.
 */
ZGMTR_PROVISIONALLY_AVAILABLE
@interface ZGMTRClusterEcosystemInformation : ZGMTRGenericCluster

- (NSDictionary<NSString *, id> * _Nullable)readAttributeDeviceDirectoryWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeLocationDirectoryWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeGeneratedCommandListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeAcceptedCommandListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeAttributeListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeFeatureMapWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeClusterRevisionWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end

@interface ZGMTRClusterEcosystemInformation (Availability)

/**
 * The queue is currently unused, but may be used in the future for calling completions
 * for command invocations if commands are added to this cluster.
 */
- (instancetype _Nullable)initWithDevice:(ZGMTRDevice *)device
                              endpointID:(NSNumber *)endpointID
                                   queue:(dispatch_queue_t)queue ZGMTR_PROVISIONALLY_AVAILABLE;

@end

/**
 * Cluster Commissioner Control
 *    Supports the ability for clients to request the commissioning of themselves or other nodes onto a fabric which the cluster server can commission onto.
 */
ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4))
@interface ZGMTRClusterCommissionerControl : ZGMTRGenericCluster

- (void)requestCommissioningApprovalWithParams:(ZGMTRCommissionerControlClusterRequestCommissioningApprovalParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(ZGMTRStatusCompletion)completion ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));
- (void)commissionNodeWithParams:(ZGMTRCommissionerControlClusterCommissionNodeParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(void (^)(ZGMTRCommissionerControlClusterReverseOpenCommissioningWindowParams * _Nullable data, NSError * _Nullable error))completion ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeSupportedDeviceCategoriesWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeGeneratedCommandListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeAcceptedCommandListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeAttributeListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeFeatureMapWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeClusterRevisionWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end

@interface ZGMTRClusterCommissionerControl (Availability)

/**
 * For all instance methods that take a completion (i.e. command invocations),
 * the completion will be called on the provided queue.
 */
- (instancetype _Nullable)initWithDevice:(ZGMTRDevice *)device
                              endpointID:(NSNumber *)endpointID
                                   queue:(dispatch_queue_t)queue ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));

@end

/**
 * Cluster Joint Fabric Datastore
 *    The Joint Fabric Datastore Cluster is a cluster that provides a mechanism for the Joint Fabric Administrators to manage the set of Nodes, Groups, and Group membership among Nodes in the Joint Fabric.
 */
ZGMTR_PROVISIONALLY_AVAILABLE
@interface ZGMTRClusterJointFabricDatastore : ZGMTRGenericCluster

- (void)addKeySetWithParams:(ZGMTRJointFabricDatastoreClusterAddKeySetParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(ZGMTRStatusCompletion)completion ZGMTR_PROVISIONALLY_AVAILABLE;
- (void)updateKeySetWithParams:(ZGMTRJointFabricDatastoreClusterUpdateKeySetParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(ZGMTRStatusCompletion)completion ZGMTR_PROVISIONALLY_AVAILABLE;
- (void)removeKeySetWithParams:(ZGMTRJointFabricDatastoreClusterRemoveKeySetParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(ZGMTRStatusCompletion)completion ZGMTR_PROVISIONALLY_AVAILABLE;
- (void)addGroupWithParams:(ZGMTRJointFabricDatastoreClusterAddGroupParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(ZGMTRStatusCompletion)completion ZGMTR_PROVISIONALLY_AVAILABLE;
- (void)updateGroupWithParams:(ZGMTRJointFabricDatastoreClusterUpdateGroupParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(ZGMTRStatusCompletion)completion ZGMTR_PROVISIONALLY_AVAILABLE;
- (void)removeGroupWithParams:(ZGMTRJointFabricDatastoreClusterRemoveGroupParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(ZGMTRStatusCompletion)completion ZGMTR_PROVISIONALLY_AVAILABLE;
- (void)addAdminWithParams:(ZGMTRJointFabricDatastoreClusterAddAdminParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(ZGMTRStatusCompletion)completion ZGMTR_PROVISIONALLY_AVAILABLE;
- (void)updateAdminWithParams:(ZGMTRJointFabricDatastoreClusterUpdateAdminParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(ZGMTRStatusCompletion)completion ZGMTR_PROVISIONALLY_AVAILABLE;
- (void)removeAdminWithParams:(ZGMTRJointFabricDatastoreClusterRemoveAdminParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(ZGMTRStatusCompletion)completion ZGMTR_PROVISIONALLY_AVAILABLE;
- (void)addPendingNodeWithParams:(ZGMTRJointFabricDatastoreClusterAddPendingNodeParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(ZGMTRStatusCompletion)completion ZGMTR_PROVISIONALLY_AVAILABLE;
- (void)refreshNodeWithParams:(ZGMTRJointFabricDatastoreClusterRefreshNodeParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(ZGMTRStatusCompletion)completion ZGMTR_PROVISIONALLY_AVAILABLE;
- (void)updateNodeWithParams:(ZGMTRJointFabricDatastoreClusterUpdateNodeParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(ZGMTRStatusCompletion)completion ZGMTR_PROVISIONALLY_AVAILABLE;
- (void)removeNodeWithParams:(ZGMTRJointFabricDatastoreClusterRemoveNodeParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(ZGMTRStatusCompletion)completion ZGMTR_PROVISIONALLY_AVAILABLE;
- (void)updateEndpointForNodeWithParams:(ZGMTRJointFabricDatastoreClusterUpdateEndpointForNodeParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(ZGMTRStatusCompletion)completion ZGMTR_PROVISIONALLY_AVAILABLE;
- (void)addGroupIDToEndpointForNodeWithParams:(ZGMTRJointFabricDatastoreClusterAddGroupIDToEndpointForNodeParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(ZGMTRStatusCompletion)completion ZGMTR_PROVISIONALLY_AVAILABLE;
- (void)removeGroupIDFromEndpointForNodeWithParams:(ZGMTRJointFabricDatastoreClusterRemoveGroupIDFromEndpointForNodeParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(ZGMTRStatusCompletion)completion ZGMTR_PROVISIONALLY_AVAILABLE;
- (void)addBindingToEndpointForNodeWithParams:(ZGMTRJointFabricDatastoreClusterAddBindingToEndpointForNodeParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(ZGMTRStatusCompletion)completion ZGMTR_PROVISIONALLY_AVAILABLE;
- (void)removeBindingFromEndpointForNodeWithParams:(ZGMTRJointFabricDatastoreClusterRemoveBindingFromEndpointForNodeParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(ZGMTRStatusCompletion)completion ZGMTR_PROVISIONALLY_AVAILABLE;
- (void)addACLToNodeWithParams:(ZGMTRJointFabricDatastoreClusterAddACLToNodeParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(ZGMTRStatusCompletion)completion ZGMTR_PROVISIONALLY_AVAILABLE;
- (void)removeACLFromNodeWithParams:(ZGMTRJointFabricDatastoreClusterRemoveACLFromNodeParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(ZGMTRStatusCompletion)completion ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeAnchorRootCAWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeAnchorNodeIDWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeAnchorVendorIDWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeFriendlyNameWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeGroupKeySetListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeGroupListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeNodeListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeAdminListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeStatusWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeEndpointGroupIDListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeEndpointBindingListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeNodeKeySetListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeNodeACLListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeNodeEndpointListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeGeneratedCommandListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeAcceptedCommandListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeAttributeListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeFeatureMapWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeClusterRevisionWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end

@interface ZGMTRClusterJointFabricDatastore (Availability)

/**
 * For all instance methods that take a completion (i.e. command invocations),
 * the completion will be called on the provided queue.
 */
- (instancetype _Nullable)initWithDevice:(ZGMTRDevice *)device
                              endpointID:(NSNumber *)endpointID
                                   queue:(dispatch_queue_t)queue ZGMTR_PROVISIONALLY_AVAILABLE;

@end

/**
 * Cluster Joint Fabric Administrator
 *    An instance of the Joint Fabric Administrator Cluster only applies to Joint Fabric Administrator nodes fulfilling the role of Anchor CA.
 */
ZGMTR_PROVISIONALLY_AVAILABLE
@interface ZGMTRClusterJointFabricAdministrator : ZGMTRGenericCluster

- (void)ICACCSRRequestWithParams:(ZGMTRJointFabricAdministratorClusterICACCSRRequestParams * _Nullable)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(void (^)(ZGMTRJointFabricAdministratorClusterICACCSRResponseParams * _Nullable data, NSError * _Nullable error))completion ZGMTR_PROVISIONALLY_AVAILABLE;
- (void)ICACCSRRequestWithExpectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedValues expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(void (^)(ZGMTRJointFabricAdministratorClusterICACCSRResponseParams * _Nullable data, NSError * _Nullable error))completion
    ZGMTR_PROVISIONALLY_AVAILABLE;
- (void)addICACWithParams:(ZGMTRJointFabricAdministratorClusterAddICACParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(void (^)(ZGMTRJointFabricAdministratorClusterICACResponseParams * _Nullable data, NSError * _Nullable error))completion ZGMTR_PROVISIONALLY_AVAILABLE;
- (void)openJointCommissioningWindowWithParams:(ZGMTRJointFabricAdministratorClusterOpenJointCommissioningWindowParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(ZGMTRStatusCompletion)completion ZGMTR_PROVISIONALLY_AVAILABLE;
- (void)transferAnchorRequestWithParams:(ZGMTRJointFabricAdministratorClusterTransferAnchorRequestParams * _Nullable)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(void (^)(ZGMTRJointFabricAdministratorClusterTransferAnchorResponseParams * _Nullable data, NSError * _Nullable error))completion ZGMTR_PROVISIONALLY_AVAILABLE;
- (void)transferAnchorRequestWithExpectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedValues expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(void (^)(ZGMTRJointFabricAdministratorClusterTransferAnchorResponseParams * _Nullable data, NSError * _Nullable error))completion
    ZGMTR_PROVISIONALLY_AVAILABLE;
- (void)transferAnchorCompleteWithParams:(ZGMTRJointFabricAdministratorClusterTransferAnchorCompleteParams * _Nullable)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(ZGMTRStatusCompletion)completion ZGMTR_PROVISIONALLY_AVAILABLE;
- (void)transferAnchorCompleteWithExpectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedValues expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(ZGMTRStatusCompletion)completion
    ZGMTR_PROVISIONALLY_AVAILABLE;
- (void)announceJointFabricAdministratorWithParams:(ZGMTRJointFabricAdministratorClusterAnnounceJointFabricAdministratorParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(ZGMTRStatusCompletion)completion ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeAdministratorFabricIndexWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeGeneratedCommandListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeAcceptedCommandListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeAttributeListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeFeatureMapWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeClusterRevisionWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end

@interface ZGMTRClusterJointFabricAdministrator (Availability)

/**
 * For all instance methods that take a completion (i.e. command invocations),
 * the completion will be called on the provided queue.
 */
- (instancetype _Nullable)initWithDevice:(ZGMTRDevice *)device
                              endpointID:(NSNumber *)endpointID
                                   queue:(dispatch_queue_t)queue ZGMTR_PROVISIONALLY_AVAILABLE;

@end

/**
 * Cluster TLS Certificate Management
 *    This Cluster is used to manage TLS Client Certificates and to provision
      TLS endpoints with enough information to facilitate subsequent connection.
 */
ZGMTR_PROVISIONALLY_AVAILABLE
@interface ZGMTRClusterTLSCertificateManagement : ZGMTRGenericCluster

- (void)provisionRootCertificateWithParams:(ZGMTRTLSCertificateManagementClusterProvisionRootCertificateParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(void (^)(ZGMTRTLSCertificateManagementClusterProvisionRootCertificateResponseParams * _Nullable data, NSError * _Nullable error))completion ZGMTR_PROVISIONALLY_AVAILABLE;
- (void)findRootCertificateWithParams:(ZGMTRTLSCertificateManagementClusterFindRootCertificateParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(void (^)(ZGMTRTLSCertificateManagementClusterFindRootCertificateResponseParams * _Nullable data, NSError * _Nullable error))completion ZGMTR_PROVISIONALLY_AVAILABLE;
- (void)lookupRootCertificateWithParams:(ZGMTRTLSCertificateManagementClusterLookupRootCertificateParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(void (^)(ZGMTRTLSCertificateManagementClusterLookupRootCertificateResponseParams * _Nullable data, NSError * _Nullable error))completion ZGMTR_PROVISIONALLY_AVAILABLE;
- (void)removeRootCertificateWithParams:(ZGMTRTLSCertificateManagementClusterRemoveRootCertificateParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(ZGMTRStatusCompletion)completion ZGMTR_PROVISIONALLY_AVAILABLE;
- (void)clientCSRWithParams:(ZGMTRTLSCertificateManagementClusterClientCSRParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(void (^)(ZGMTRTLSCertificateManagementClusterClientCSRResponseParams * _Nullable data, NSError * _Nullable error))completion ZGMTR_PROVISIONALLY_AVAILABLE;
- (void)provisionClientCertificateWithParams:(ZGMTRTLSCertificateManagementClusterProvisionClientCertificateParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(ZGMTRStatusCompletion)completion ZGMTR_PROVISIONALLY_AVAILABLE;
- (void)findClientCertificateWithParams:(ZGMTRTLSCertificateManagementClusterFindClientCertificateParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(void (^)(ZGMTRTLSCertificateManagementClusterFindClientCertificateResponseParams * _Nullable data, NSError * _Nullable error))completion ZGMTR_PROVISIONALLY_AVAILABLE;
- (void)lookupClientCertificateWithParams:(ZGMTRTLSCertificateManagementClusterLookupClientCertificateParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(void (^)(ZGMTRTLSCertificateManagementClusterLookupClientCertificateResponseParams * _Nullable data, NSError * _Nullable error))completion ZGMTR_PROVISIONALLY_AVAILABLE;
- (void)removeClientCertificateWithParams:(ZGMTRTLSCertificateManagementClusterRemoveClientCertificateParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(ZGMTRStatusCompletion)completion ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeMaxRootCertificatesWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeProvisionedRootCertificatesWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeMaxClientCertificatesWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeProvisionedClientCertificatesWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeGeneratedCommandListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeAcceptedCommandListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeAttributeListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeFeatureMapWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeClusterRevisionWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end

@interface ZGMTRClusterTLSCertificateManagement (Availability)

/**
 * For all instance methods that take a completion (i.e. command invocations),
 * the completion will be called on the provided queue.
 */
- (instancetype _Nullable)initWithDevice:(ZGMTRDevice *)device
                              endpointID:(NSNumber *)endpointID
                                   queue:(dispatch_queue_t)queue ZGMTR_PROVISIONALLY_AVAILABLE;

@end

/**
 * Cluster TLS Client Management
 *    This Cluster is used to provision TLS Endpoints with enough information to facilitate subsequent connection.
 */
ZGMTR_PROVISIONALLY_AVAILABLE
@interface ZGMTRClusterTLSClientManagement : ZGMTRGenericCluster

- (void)provisionEndpointWithParams:(ZGMTRTLSClientManagementClusterProvisionEndpointParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(void (^)(ZGMTRTLSClientManagementClusterProvisionEndpointResponseParams * _Nullable data, NSError * _Nullable error))completion ZGMTR_PROVISIONALLY_AVAILABLE;
- (void)findEndpointWithParams:(ZGMTRTLSClientManagementClusterFindEndpointParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(void (^)(ZGMTRTLSClientManagementClusterFindEndpointResponseParams * _Nullable data, NSError * _Nullable error))completion ZGMTR_PROVISIONALLY_AVAILABLE;
- (void)removeEndpointWithParams:(ZGMTRTLSClientManagementClusterRemoveEndpointParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(ZGMTRStatusCompletion)completion ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeMaxProvisionedWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeProvisionedEndpointsWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeGeneratedCommandListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeAcceptedCommandListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeAttributeListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeFeatureMapWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeClusterRevisionWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end

@interface ZGMTRClusterTLSClientManagement (Availability)

/**
 * For all instance methods that take a completion (i.e. command invocations),
 * the completion will be called on the provided queue.
 */
- (instancetype _Nullable)initWithDevice:(ZGMTRDevice *)device
                              endpointID:(NSNumber *)endpointID
                                   queue:(dispatch_queue_t)queue ZGMTR_PROVISIONALLY_AVAILABLE;

@end

/**
 * Cluster Meter Identification
 *    This Meter Identification Cluster provides attributes for determining advanced information about utility metering device.
 */
ZGMTR_PROVISIONALLY_AVAILABLE
@interface ZGMTRClusterMeterIdentification : ZGMTRGenericCluster

- (NSDictionary<NSString *, id> * _Nullable)readAttributeMeterTypeWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributePointOfDeliveryWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeMeterSerialNumberWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeProtocolVersionWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributePowerThresholdWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeGeneratedCommandListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeAcceptedCommandListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeAttributeListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeFeatureMapWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeClusterRevisionWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end

@interface ZGMTRClusterMeterIdentification (Availability)

/**
 * The queue is currently unused, but may be used in the future for calling completions
 * for command invocations if commands are added to this cluster.
 */
- (instancetype _Nullable)initWithDevice:(ZGMTRDevice *)device
                              endpointID:(NSNumber *)endpointID
                                   queue:(dispatch_queue_t)queue ZGMTR_PROVISIONALLY_AVAILABLE;

@end

/**
 * Cluster Commodity Metering
 *    The Commodity Metering Cluster provides the mechanism for communicating commodity consumption information within a premises.
 */
ZGMTR_PROVISIONALLY_AVAILABLE
@interface ZGMTRClusterCommodityMetering : ZGMTRGenericCluster

- (NSDictionary<NSString *, id> * _Nullable)readAttributeMeteredQuantityWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeMeteredQuantityTimestampWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeTariffUnitWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeMaximumMeteredQuantitiesWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeGeneratedCommandListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeAcceptedCommandListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeAttributeListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeFeatureMapWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeClusterRevisionWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end

@interface ZGMTRClusterCommodityMetering (Availability)

/**
 * The queue is currently unused, but may be used in the future for calling completions
 * for command invocations if commands are added to this cluster.
 */
- (instancetype _Nullable)initWithDevice:(ZGMTRDevice *)device
                              endpointID:(NSNumber *)endpointID
                                   queue:(dispatch_queue_t)queue ZGMTR_PROVISIONALLY_AVAILABLE;

@end

/**
 * Cluster Unit Testing
 *    The Test Cluster is meant to validate the generated code
 */
ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4))
@interface ZGMTRClusterUnitTesting : ZGMTRGenericCluster

- (void)testWithParams:(ZGMTRUnitTestingClusterTestParams * _Nullable)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(ZGMTRStatusCompletion)completion ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
- (void)testWithExpectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedValues expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(ZGMTRStatusCompletion)completion
    ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
- (void)testNotHandledWithParams:(ZGMTRUnitTestingClusterTestNotHandledParams * _Nullable)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(ZGMTRStatusCompletion)completion ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
- (void)testNotHandledWithExpectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedValues expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(ZGMTRStatusCompletion)completion
    ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
- (void)testSpecificWithParams:(ZGMTRUnitTestingClusterTestSpecificParams * _Nullable)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(void (^)(ZGMTRUnitTestingClusterTestSpecificResponseParams * _Nullable data, NSError * _Nullable error))completion ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
- (void)testSpecificWithExpectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedValues expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(void (^)(ZGMTRUnitTestingClusterTestSpecificResponseParams * _Nullable data, NSError * _Nullable error))completion
    ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
- (void)testUnknownCommandWithParams:(ZGMTRUnitTestingClusterTestUnknownCommandParams * _Nullable)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(ZGMTRStatusCompletion)completion ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
- (void)testUnknownCommandWithExpectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedValues expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(ZGMTRStatusCompletion)completion
    ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
- (void)testAddArgumentsWithParams:(ZGMTRUnitTestingClusterTestAddArgumentsParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(void (^)(ZGMTRUnitTestingClusterTestAddArgumentsResponseParams * _Nullable data, NSError * _Nullable error))completion ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
- (void)testSimpleArgumentRequestWithParams:(ZGMTRUnitTestingClusterTestSimpleArgumentRequestParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(void (^)(ZGMTRUnitTestingClusterTestSimpleArgumentResponseParams * _Nullable data, NSError * _Nullable error))completion ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
- (void)testStructArrayArgumentRequestWithParams:(ZGMTRUnitTestingClusterTestStructArrayArgumentRequestParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(void (^)(ZGMTRUnitTestingClusterTestStructArrayArgumentResponseParams * _Nullable data, NSError * _Nullable error))completion ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
- (void)testStructArgumentRequestWithParams:(ZGMTRUnitTestingClusterTestStructArgumentRequestParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(void (^)(ZGMTRUnitTestingClusterBooleanResponseParams * _Nullable data, NSError * _Nullable error))completion ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
- (void)testNestedStructArgumentRequestWithParams:(ZGMTRUnitTestingClusterTestNestedStructArgumentRequestParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(void (^)(ZGMTRUnitTestingClusterBooleanResponseParams * _Nullable data, NSError * _Nullable error))completion ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
- (void)testListStructArgumentRequestWithParams:(ZGMTRUnitTestingClusterTestListStructArgumentRequestParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(void (^)(ZGMTRUnitTestingClusterBooleanResponseParams * _Nullable data, NSError * _Nullable error))completion ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
- (void)testListInt8UArgumentRequestWithParams:(ZGMTRUnitTestingClusterTestListInt8UArgumentRequestParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(void (^)(ZGMTRUnitTestingClusterBooleanResponseParams * _Nullable data, NSError * _Nullable error))completion ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
- (void)testNestedStructListArgumentRequestWithParams:(ZGMTRUnitTestingClusterTestNestedStructListArgumentRequestParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(void (^)(ZGMTRUnitTestingClusterBooleanResponseParams * _Nullable data, NSError * _Nullable error))completion ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
- (void)testListNestedStructListArgumentRequestWithParams:(ZGMTRUnitTestingClusterTestListNestedStructListArgumentRequestParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(void (^)(ZGMTRUnitTestingClusterBooleanResponseParams * _Nullable data, NSError * _Nullable error))completion ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
- (void)testListInt8UReverseRequestWithParams:(ZGMTRUnitTestingClusterTestListInt8UReverseRequestParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(void (^)(ZGMTRUnitTestingClusterTestListInt8UReverseResponseParams * _Nullable data, NSError * _Nullable error))completion ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
- (void)testEnumsRequestWithParams:(ZGMTRUnitTestingClusterTestEnumsRequestParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(void (^)(ZGMTRUnitTestingClusterTestEnumsResponseParams * _Nullable data, NSError * _Nullable error))completion ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
- (void)testNullableOptionalRequestWithParams:(ZGMTRUnitTestingClusterTestNullableOptionalRequestParams * _Nullable)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(void (^)(ZGMTRUnitTestingClusterTestNullableOptionalResponseParams * _Nullable data, NSError * _Nullable error))completion ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
- (void)testNullableOptionalRequestWithExpectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedValues expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(void (^)(ZGMTRUnitTestingClusterTestNullableOptionalResponseParams * _Nullable data, NSError * _Nullable error))completion
    ZGMTR_AVAILABLE(ios(17.4), macos(14.4), watchos(10.4), tvos(17.4));
- (void)testComplexNullableOptionalRequestWithParams:(ZGMTRUnitTestingClusterTestComplexNullableOptionalRequestParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(void (^)(ZGMTRUnitTestingClusterTestComplexNullableOptionalResponseParams * _Nullable data, NSError * _Nullable error))completion ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
- (void)simpleStructEchoRequestWithParams:(ZGMTRUnitTestingClusterSimpleStructEchoRequestParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(void (^)(ZGMTRUnitTestingClusterSimpleStructResponseParams * _Nullable data, NSError * _Nullable error))completion ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
- (void)timedInvokeRequestWithParams:(ZGMTRUnitTestingClusterTimedInvokeRequestParams * _Nullable)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(ZGMTRStatusCompletion)completion ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
- (void)timedInvokeRequestWithExpectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedValues expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(ZGMTRStatusCompletion)completion
    ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
- (void)testSimpleOptionalArgumentRequestWithParams:(ZGMTRUnitTestingClusterTestSimpleOptionalArgumentRequestParams * _Nullable)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(ZGMTRStatusCompletion)completion ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
- (void)testSimpleOptionalArgumentRequestWithExpectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedValues expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(ZGMTRStatusCompletion)completion
    ZGMTR_AVAILABLE(ios(17.4), macos(14.4), watchos(10.4), tvos(17.4));
- (void)testEmitTestEventRequestWithParams:(ZGMTRUnitTestingClusterTestEmitTestEventRequestParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(void (^)(ZGMTRUnitTestingClusterTestEmitTestEventResponseParams * _Nullable data, NSError * _Nullable error))completion ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
- (void)testEmitTestFabricScopedEventRequestWithParams:(ZGMTRUnitTestingClusterTestEmitTestFabricScopedEventRequestParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(void (^)(ZGMTRUnitTestingClusterTestEmitTestFabricScopedEventResponseParams * _Nullable data, NSError * _Nullable error))completion ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
- (void)testBatchHelperRequestWithParams:(ZGMTRUnitTestingClusterTestBatchHelperRequestParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(void (^)(ZGMTRUnitTestingClusterTestBatchHelperResponseParams * _Nullable data, NSError * _Nullable error))completion ZGMTR_PROVISIONALLY_AVAILABLE;
- (void)testSecondBatchHelperRequestWithParams:(ZGMTRUnitTestingClusterTestSecondBatchHelperRequestParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(void (^)(ZGMTRUnitTestingClusterTestBatchHelperResponseParams * _Nullable data, NSError * _Nullable error))completion ZGMTR_PROVISIONALLY_AVAILABLE;
- (void)stringEchoRequestWithParams:(ZGMTRUnitTestingClusterStringEchoRequestParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(void (^)(ZGMTRUnitTestingClusterStringEchoResponseParams * _Nullable data, NSError * _Nullable error))completion ZGMTR_PROVISIONALLY_AVAILABLE;
- (void)globalEchoRequestWithParams:(ZGMTRUnitTestingClusterGlobalEchoRequestParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(void (^)(ZGMTRUnitTestingClusterGlobalEchoResponseParams * _Nullable data, NSError * _Nullable error))completion ZGMTR_PROVISIONALLY_AVAILABLE;
- (void)testCheckCommandFlagsWithParams:(ZGMTRUnitTestingClusterTestCheckCommandFlagsParams * _Nullable)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(ZGMTRStatusCompletion)completion ZGMTR_PROVISIONALLY_AVAILABLE;
- (void)testCheckCommandFlagsWithExpectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedValues expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(ZGMTRStatusCompletion)completion
    ZGMTR_PROVISIONALLY_AVAILABLE;
- (void)testDifferentVendorMeiRequestWithParams:(ZGMTRUnitTestingClusterTestDifferentVendorMeiRequestParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(void (^)(ZGMTRUnitTestingClusterTestDifferentVendorMeiResponseParams * _Nullable data, NSError * _Nullable error))completion ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeBooleanWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
- (void)writeAttributeBooleanWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
- (void)writeAttributeBooleanWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs params:(ZGMTRWriteParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeBitmap8WithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
- (void)writeAttributeBitmap8WithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
- (void)writeAttributeBitmap8WithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs params:(ZGMTRWriteParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeBitmap16WithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
- (void)writeAttributeBitmap16WithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
- (void)writeAttributeBitmap16WithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs params:(ZGMTRWriteParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeBitmap32WithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
- (void)writeAttributeBitmap32WithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
- (void)writeAttributeBitmap32WithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs params:(ZGMTRWriteParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeBitmap64WithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
- (void)writeAttributeBitmap64WithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
- (void)writeAttributeBitmap64WithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs params:(ZGMTRWriteParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeInt8uWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
- (void)writeAttributeInt8uWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
- (void)writeAttributeInt8uWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs params:(ZGMTRWriteParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeInt16uWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
- (void)writeAttributeInt16uWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
- (void)writeAttributeInt16uWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs params:(ZGMTRWriteParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeInt24uWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
- (void)writeAttributeInt24uWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
- (void)writeAttributeInt24uWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs params:(ZGMTRWriteParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeInt32uWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
- (void)writeAttributeInt32uWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
- (void)writeAttributeInt32uWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs params:(ZGMTRWriteParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeInt40uWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
- (void)writeAttributeInt40uWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
- (void)writeAttributeInt40uWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs params:(ZGMTRWriteParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeInt48uWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
- (void)writeAttributeInt48uWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
- (void)writeAttributeInt48uWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs params:(ZGMTRWriteParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeInt56uWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
- (void)writeAttributeInt56uWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
- (void)writeAttributeInt56uWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs params:(ZGMTRWriteParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeInt64uWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
- (void)writeAttributeInt64uWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
- (void)writeAttributeInt64uWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs params:(ZGMTRWriteParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeInt8sWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
- (void)writeAttributeInt8sWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
- (void)writeAttributeInt8sWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs params:(ZGMTRWriteParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeInt16sWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
- (void)writeAttributeInt16sWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
- (void)writeAttributeInt16sWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs params:(ZGMTRWriteParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeInt24sWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
- (void)writeAttributeInt24sWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
- (void)writeAttributeInt24sWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs params:(ZGMTRWriteParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeInt32sWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
- (void)writeAttributeInt32sWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
- (void)writeAttributeInt32sWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs params:(ZGMTRWriteParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeInt40sWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
- (void)writeAttributeInt40sWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
- (void)writeAttributeInt40sWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs params:(ZGMTRWriteParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeInt48sWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
- (void)writeAttributeInt48sWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
- (void)writeAttributeInt48sWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs params:(ZGMTRWriteParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeInt56sWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
- (void)writeAttributeInt56sWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
- (void)writeAttributeInt56sWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs params:(ZGMTRWriteParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeInt64sWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
- (void)writeAttributeInt64sWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
- (void)writeAttributeInt64sWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs params:(ZGMTRWriteParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeEnum8WithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
- (void)writeAttributeEnum8WithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
- (void)writeAttributeEnum8WithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs params:(ZGMTRWriteParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeEnum16WithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
- (void)writeAttributeEnum16WithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
- (void)writeAttributeEnum16WithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs params:(ZGMTRWriteParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeFloatSingleWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
- (void)writeAttributeFloatSingleWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
- (void)writeAttributeFloatSingleWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs params:(ZGMTRWriteParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeFloatDoubleWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
- (void)writeAttributeFloatDoubleWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
- (void)writeAttributeFloatDoubleWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs params:(ZGMTRWriteParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeOctetStringWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
- (void)writeAttributeOctetStringWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
- (void)writeAttributeOctetStringWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs params:(ZGMTRWriteParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeListInt8uWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
- (void)writeAttributeListInt8uWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
- (void)writeAttributeListInt8uWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs params:(ZGMTRWriteParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeListOctetStringWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
- (void)writeAttributeListOctetStringWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
- (void)writeAttributeListOctetStringWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs params:(ZGMTRWriteParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeListStructOctetStringWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
- (void)writeAttributeListStructOctetStringWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
- (void)writeAttributeListStructOctetStringWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs params:(ZGMTRWriteParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeLongOctetStringWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
- (void)writeAttributeLongOctetStringWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
- (void)writeAttributeLongOctetStringWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs params:(ZGMTRWriteParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeCharStringWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
- (void)writeAttributeCharStringWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
- (void)writeAttributeCharStringWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs params:(ZGMTRWriteParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeLongCharStringWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
- (void)writeAttributeLongCharStringWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
- (void)writeAttributeLongCharStringWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs params:(ZGMTRWriteParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeEpochUsWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
- (void)writeAttributeEpochUsWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
- (void)writeAttributeEpochUsWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs params:(ZGMTRWriteParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeEpochSWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
- (void)writeAttributeEpochSWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
- (void)writeAttributeEpochSWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs params:(ZGMTRWriteParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeVendorIdWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
- (void)writeAttributeVendorIdWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
- (void)writeAttributeVendorIdWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs params:(ZGMTRWriteParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeListNullablesAndOptionalsStructWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
- (void)writeAttributeListNullablesAndOptionalsStructWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
- (void)writeAttributeListNullablesAndOptionalsStructWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs params:(ZGMTRWriteParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeEnumAttrWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
- (void)writeAttributeEnumAttrWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
- (void)writeAttributeEnumAttrWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs params:(ZGMTRWriteParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeStructAttrWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
- (void)writeAttributeStructAttrWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
- (void)writeAttributeStructAttrWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs params:(ZGMTRWriteParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeRangeRestrictedInt8uWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
- (void)writeAttributeRangeRestrictedInt8uWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
- (void)writeAttributeRangeRestrictedInt8uWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs params:(ZGMTRWriteParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeRangeRestrictedInt8sWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
- (void)writeAttributeRangeRestrictedInt8sWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
- (void)writeAttributeRangeRestrictedInt8sWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs params:(ZGMTRWriteParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeRangeRestrictedInt16uWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
- (void)writeAttributeRangeRestrictedInt16uWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
- (void)writeAttributeRangeRestrictedInt16uWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs params:(ZGMTRWriteParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeRangeRestrictedInt16sWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
- (void)writeAttributeRangeRestrictedInt16sWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
- (void)writeAttributeRangeRestrictedInt16sWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs params:(ZGMTRWriteParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeListLongOctetStringWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
- (void)writeAttributeListLongOctetStringWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
- (void)writeAttributeListLongOctetStringWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs params:(ZGMTRWriteParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeListFabricScopedWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
- (void)writeAttributeListFabricScopedWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
- (void)writeAttributeListFabricScopedWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs params:(ZGMTRWriteParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeTimedWriteBooleanWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
- (void)writeAttributeTimedWriteBooleanWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
- (void)writeAttributeTimedWriteBooleanWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs params:(ZGMTRWriteParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeGeneralErrorBooleanWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
- (void)writeAttributeGeneralErrorBooleanWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
- (void)writeAttributeGeneralErrorBooleanWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs params:(ZGMTRWriteParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeClusterErrorBooleanWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
- (void)writeAttributeClusterErrorBooleanWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
- (void)writeAttributeClusterErrorBooleanWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs params:(ZGMTRWriteParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeGlobalEnumWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;
- (void)writeAttributeGlobalEnumWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs ZGMTR_PROVISIONALLY_AVAILABLE;
- (void)writeAttributeGlobalEnumWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs params:(ZGMTRWriteParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeGlobalStructWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;
- (void)writeAttributeGlobalStructWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs ZGMTR_PROVISIONALLY_AVAILABLE;
- (void)writeAttributeGlobalStructWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs params:(ZGMTRWriteParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeUnsupportedAttributeRequiringAdminPrivilegeWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;
- (void)writeAttributeUnsupportedAttributeRequiringAdminPrivilegeWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs ZGMTR_PROVISIONALLY_AVAILABLE;
- (void)writeAttributeUnsupportedAttributeRequiringAdminPrivilegeWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs params:(ZGMTRWriteParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeUnsupportedWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
- (void)writeAttributeUnsupportedWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
- (void)writeAttributeUnsupportedWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs params:(ZGMTRWriteParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeReadFailureCodeWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;
- (void)writeAttributeReadFailureCodeWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs ZGMTR_PROVISIONALLY_AVAILABLE;
- (void)writeAttributeReadFailureCodeWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs params:(ZGMTRWriteParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeFailureInt32UWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;
- (void)writeAttributeFailureInt32UWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs ZGMTR_PROVISIONALLY_AVAILABLE;
- (void)writeAttributeFailureInt32UWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs params:(ZGMTRWriteParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeNullableBooleanWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
- (void)writeAttributeNullableBooleanWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
- (void)writeAttributeNullableBooleanWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs params:(ZGMTRWriteParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeNullableBitmap8WithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
- (void)writeAttributeNullableBitmap8WithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
- (void)writeAttributeNullableBitmap8WithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs params:(ZGMTRWriteParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeNullableBitmap16WithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
- (void)writeAttributeNullableBitmap16WithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
- (void)writeAttributeNullableBitmap16WithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs params:(ZGMTRWriteParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeNullableBitmap32WithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
- (void)writeAttributeNullableBitmap32WithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
- (void)writeAttributeNullableBitmap32WithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs params:(ZGMTRWriteParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeNullableBitmap64WithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
- (void)writeAttributeNullableBitmap64WithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
- (void)writeAttributeNullableBitmap64WithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs params:(ZGMTRWriteParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeNullableInt8uWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
- (void)writeAttributeNullableInt8uWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
- (void)writeAttributeNullableInt8uWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs params:(ZGMTRWriteParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeNullableInt16uWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
- (void)writeAttributeNullableInt16uWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
- (void)writeAttributeNullableInt16uWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs params:(ZGMTRWriteParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeNullableInt24uWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
- (void)writeAttributeNullableInt24uWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
- (void)writeAttributeNullableInt24uWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs params:(ZGMTRWriteParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeNullableInt32uWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
- (void)writeAttributeNullableInt32uWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
- (void)writeAttributeNullableInt32uWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs params:(ZGMTRWriteParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeNullableInt40uWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
- (void)writeAttributeNullableInt40uWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
- (void)writeAttributeNullableInt40uWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs params:(ZGMTRWriteParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeNullableInt48uWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
- (void)writeAttributeNullableInt48uWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
- (void)writeAttributeNullableInt48uWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs params:(ZGMTRWriteParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeNullableInt56uWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
- (void)writeAttributeNullableInt56uWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
- (void)writeAttributeNullableInt56uWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs params:(ZGMTRWriteParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeNullableInt64uWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
- (void)writeAttributeNullableInt64uWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
- (void)writeAttributeNullableInt64uWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs params:(ZGMTRWriteParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeNullableInt8sWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
- (void)writeAttributeNullableInt8sWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
- (void)writeAttributeNullableInt8sWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs params:(ZGMTRWriteParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeNullableInt16sWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
- (void)writeAttributeNullableInt16sWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
- (void)writeAttributeNullableInt16sWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs params:(ZGMTRWriteParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeNullableInt24sWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
- (void)writeAttributeNullableInt24sWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
- (void)writeAttributeNullableInt24sWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs params:(ZGMTRWriteParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeNullableInt32sWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
- (void)writeAttributeNullableInt32sWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
- (void)writeAttributeNullableInt32sWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs params:(ZGMTRWriteParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeNullableInt40sWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
- (void)writeAttributeNullableInt40sWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
- (void)writeAttributeNullableInt40sWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs params:(ZGMTRWriteParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeNullableInt48sWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
- (void)writeAttributeNullableInt48sWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
- (void)writeAttributeNullableInt48sWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs params:(ZGMTRWriteParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeNullableInt56sWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
- (void)writeAttributeNullableInt56sWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
- (void)writeAttributeNullableInt56sWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs params:(ZGMTRWriteParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeNullableInt64sWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
- (void)writeAttributeNullableInt64sWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
- (void)writeAttributeNullableInt64sWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs params:(ZGMTRWriteParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeNullableEnum8WithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
- (void)writeAttributeNullableEnum8WithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
- (void)writeAttributeNullableEnum8WithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs params:(ZGMTRWriteParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeNullableEnum16WithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
- (void)writeAttributeNullableEnum16WithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
- (void)writeAttributeNullableEnum16WithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs params:(ZGMTRWriteParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeNullableFloatSingleWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
- (void)writeAttributeNullableFloatSingleWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
- (void)writeAttributeNullableFloatSingleWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs params:(ZGMTRWriteParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeNullableFloatDoubleWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
- (void)writeAttributeNullableFloatDoubleWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
- (void)writeAttributeNullableFloatDoubleWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs params:(ZGMTRWriteParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeNullableOctetStringWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
- (void)writeAttributeNullableOctetStringWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
- (void)writeAttributeNullableOctetStringWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs params:(ZGMTRWriteParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeNullableCharStringWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
- (void)writeAttributeNullableCharStringWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
- (void)writeAttributeNullableCharStringWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs params:(ZGMTRWriteParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeNullableEnumAttrWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
- (void)writeAttributeNullableEnumAttrWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
- (void)writeAttributeNullableEnumAttrWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs params:(ZGMTRWriteParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeNullableStructWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
- (void)writeAttributeNullableStructWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
- (void)writeAttributeNullableStructWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs params:(ZGMTRWriteParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeNullableRangeRestrictedInt8uWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
- (void)writeAttributeNullableRangeRestrictedInt8uWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
- (void)writeAttributeNullableRangeRestrictedInt8uWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs params:(ZGMTRWriteParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeNullableRangeRestrictedInt8sWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
- (void)writeAttributeNullableRangeRestrictedInt8sWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
- (void)writeAttributeNullableRangeRestrictedInt8sWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs params:(ZGMTRWriteParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeNullableRangeRestrictedInt16uWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
- (void)writeAttributeNullableRangeRestrictedInt16uWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
- (void)writeAttributeNullableRangeRestrictedInt16uWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs params:(ZGMTRWriteParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeNullableRangeRestrictedInt16sWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
- (void)writeAttributeNullableRangeRestrictedInt16sWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
- (void)writeAttributeNullableRangeRestrictedInt16sWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs params:(ZGMTRWriteParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeWriteOnlyInt8uWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
- (void)writeAttributeWriteOnlyInt8uWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
- (void)writeAttributeWriteOnlyInt8uWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs params:(ZGMTRWriteParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeNullableGlobalEnumWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;
- (void)writeAttributeNullableGlobalEnumWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs ZGMTR_PROVISIONALLY_AVAILABLE;
- (void)writeAttributeNullableGlobalEnumWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs params:(ZGMTRWriteParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeNullableGlobalStructWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;
- (void)writeAttributeNullableGlobalStructWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs ZGMTR_PROVISIONALLY_AVAILABLE;
- (void)writeAttributeNullableGlobalStructWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs params:(ZGMTRWriteParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeGeneratedCommandListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeAcceptedCommandListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeAttributeListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeFeatureMapWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeClusterRevisionWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeMeiInt8uWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;
- (void)writeAttributeMeiInt8uWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs ZGMTR_PROVISIONALLY_AVAILABLE;
- (void)writeAttributeMeiInt8uWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs params:(ZGMTRWriteParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end

@interface ZGMTRClusterUnitTesting (Availability)

/**
 * For all instance methods that take a completion (i.e. command invocations),
 * the completion will be called on the provided queue.
 */
- (instancetype _Nullable)initWithDevice:(ZGMTRDevice *)device
                              endpointID:(NSNumber *)endpointID
                                   queue:(dispatch_queue_t)queue ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));

@end

/**
 * Cluster Sample MEI
 *    The Sample MEI cluster showcases a cluster manufacturer extensions
 */
ZGMTR_PROVISIONALLY_AVAILABLE
@interface ZGMTRClusterSampleMEI : ZGMTRGenericCluster

- (void)pingWithParams:(ZGMTRSampleMEIClusterPingParams * _Nullable)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(ZGMTRStatusCompletion)completion ZGMTR_PROVISIONALLY_AVAILABLE;
- (void)pingWithExpectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedValues expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(ZGMTRStatusCompletion)completion
    ZGMTR_PROVISIONALLY_AVAILABLE;
- (void)addArgumentsWithParams:(ZGMTRSampleMEIClusterAddArgumentsParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(void (^)(ZGMTRSampleMEIClusterAddArgumentsResponseParams * _Nullable data, NSError * _Nullable error))completion ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeFlipFlopWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;
- (void)writeAttributeFlipFlopWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs ZGMTR_PROVISIONALLY_AVAILABLE;
- (void)writeAttributeFlipFlopWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs params:(ZGMTRWriteParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeGeneratedCommandListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeAcceptedCommandListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeAttributeListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeFeatureMapWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeClusterRevisionWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end

@interface ZGMTRClusterSampleMEI (Availability)

/**
 * For all instance methods that take a completion (i.e. command invocations),
 * the completion will be called on the provided queue.
 */
- (instancetype _Nullable)initWithDevice:(ZGMTRDevice *)device
                              endpointID:(NSNumber *)endpointID
                                   queue:(dispatch_queue_t)queue ZGMTR_PROVISIONALLY_AVAILABLE;

@end

/**
 * Cluster Test Hidden Manufacturer Specific
 *    Test cluster for validating manufacturer-specific cluster handling without controller-side implementation
 */
ZGMTR_PROVISIONALLY_AVAILABLE
@interface ZGMTRClusterTestHiddenManufacturerSpecific : ZGMTRGenericCluster

- (NSDictionary<NSString *, id> * _Nullable)readAttributeTestAttributeWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeGeneratedCommandListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeAcceptedCommandListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeAttributeListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeFeatureMapWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (NSDictionary<NSString *, id> * _Nullable)readAttributeClusterRevisionWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_PROVISIONALLY_AVAILABLE;

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end

@interface ZGMTRClusterTestHiddenManufacturerSpecific (Availability)

/**
 * The queue is currently unused, but may be used in the future for calling completions
 * for command invocations if commands are added to this cluster.
 */
- (instancetype _Nullable)initWithDevice:(ZGMTRDevice *)device
                              endpointID:(NSNumber *)endpointID
                                   queue:(dispatch_queue_t)queue ZGMTR_PROVISIONALLY_AVAILABLE;

@end

ZGMTR_DEPRECATED("Please use ZGMTRClusterBasicInformation", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
@interface ZGMTRClusterBasic : ZGMTRClusterBasicInformation
@end

ZGMTR_DEPRECATED("Please use ZGMTRClusterOTASoftwareUpdateProvider", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
@interface ZGMTRClusterOtaSoftwareUpdateProvider : ZGMTRClusterOTASoftwareUpdateProvider
@end

ZGMTR_DEPRECATED("Please use ZGMTRClusterOTASoftwareUpdateRequestor", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
@interface ZGMTRClusterOtaSoftwareUpdateRequestor : ZGMTRClusterOTASoftwareUpdateRequestor
@end

ZGMTR_DEPRECATED("Please use ZGMTRClusterBridgedDeviceBasicInformation", ios(16.1, 17.0), macos(13.0, 14.0), watchos(9.1, 10.0), tvos(16.1, 17.0))
@interface ZGMTRClusterBridgedDeviceBasic : ZGMTRClusterBridgedDeviceBasicInformation
@end

ZGMTR_DEPRECATED("Please use ZGMTRClusterWakeOnLAN", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
@interface ZGMTRClusterWakeOnLan : ZGMTRClusterWakeOnLAN
@end

ZGMTR_DEPRECATED("Please use ZGMTRClusterUnitTesting", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
@interface ZGMTRClusterTestCluster : ZGMTRClusterUnitTesting
@end

@interface ZGMTRClusterIdentify (Deprecated)

- (nullable instancetype)initWithDevice:(ZGMTRDevice *)device
                               endpoint:(uint16_t)endpoint
                                  queue:(dispatch_queue_t)queue ZGMTR_DEPRECATED("Please use initWithDevice:endpoindID:queue:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));

- (void)identifyWithParams:(ZGMTRIdentifyClusterIdentifyParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completionHandler:(ZGMTRStatusCompletion)completionHandler ZGMTR_DEPRECATED("Please use identifyWithParams:expectedValues:expectedValueInterval:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (void)triggerEffectWithParams:(ZGMTRIdentifyClusterTriggerEffectParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completionHandler:(ZGMTRStatusCompletion)completionHandler ZGMTR_DEPRECATED("Please use triggerEffectWithParams:expectedValues:expectedValueInterval:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
@end

@interface ZGMTRClusterGroups (Deprecated)

- (nullable instancetype)initWithDevice:(ZGMTRDevice *)device
                               endpoint:(uint16_t)endpoint
                                  queue:(dispatch_queue_t)queue ZGMTR_DEPRECATED("Please use initWithDevice:endpoindID:queue:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));

- (void)addGroupWithParams:(ZGMTRGroupsClusterAddGroupParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completionHandler:(void (^)(ZGMTRGroupsClusterAddGroupResponseParams * _Nullable data, NSError * _Nullable error))completionHandler ZGMTR_DEPRECATED("Please use addGroupWithParams:expectedValues:expectedValueInterval:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (void)viewGroupWithParams:(ZGMTRGroupsClusterViewGroupParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completionHandler:(void (^)(ZGMTRGroupsClusterViewGroupResponseParams * _Nullable data, NSError * _Nullable error))completionHandler ZGMTR_DEPRECATED("Please use viewGroupWithParams:expectedValues:expectedValueInterval:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (void)getGroupMembershipWithParams:(ZGMTRGroupsClusterGetGroupMembershipParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completionHandler:(void (^)(ZGMTRGroupsClusterGetGroupMembershipResponseParams * _Nullable data, NSError * _Nullable error))completionHandler ZGMTR_DEPRECATED("Please use getGroupMembershipWithParams:expectedValues:expectedValueInterval:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (void)removeGroupWithParams:(ZGMTRGroupsClusterRemoveGroupParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completionHandler:(void (^)(ZGMTRGroupsClusterRemoveGroupResponseParams * _Nullable data, NSError * _Nullable error))completionHandler ZGMTR_DEPRECATED("Please use removeGroupWithParams:expectedValues:expectedValueInterval:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (void)removeAllGroupsWithParams:(ZGMTRGroupsClusterRemoveAllGroupsParams * _Nullable)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completionHandler:(ZGMTRStatusCompletion)completionHandler ZGMTR_DEPRECATED("Please use removeAllGroupsWithParams:expectedValues:expectedValueInterval:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (void)removeAllGroupsWithExpectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedValues expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completionHandler:(ZGMTRStatusCompletion)completionHandler ZGMTR_DEPRECATED("Please use removeAllGroupsWithExpectedValues:expectedValueInterval:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (void)addGroupIfIdentifyingWithParams:(ZGMTRGroupsClusterAddGroupIfIdentifyingParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completionHandler:(ZGMTRStatusCompletion)completionHandler ZGMTR_DEPRECATED("Please use addGroupIfIdentifyingWithParams:expectedValues:expectedValueInterval:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
@end

@interface ZGMTRClusterOnOff (Deprecated)

- (nullable instancetype)initWithDevice:(ZGMTRDevice *)device
                               endpoint:(uint16_t)endpoint
                                  queue:(dispatch_queue_t)queue ZGMTR_DEPRECATED("Please use initWithDevice:endpoindID:queue:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));

- (void)offWithParams:(ZGMTROnOffClusterOffParams * _Nullable)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completionHandler:(ZGMTRStatusCompletion)completionHandler ZGMTR_DEPRECATED("Please use offWithParams:expectedValues:expectedValueInterval:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (void)offWithExpectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedValues expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completionHandler:(ZGMTRStatusCompletion)completionHandler ZGMTR_DEPRECATED("Please use offWithExpectedValues:expectedValueInterval:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (void)onWithParams:(ZGMTROnOffClusterOnParams * _Nullable)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completionHandler:(ZGMTRStatusCompletion)completionHandler ZGMTR_DEPRECATED("Please use onWithParams:expectedValues:expectedValueInterval:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (void)onWithExpectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedValues expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completionHandler:(ZGMTRStatusCompletion)completionHandler ZGMTR_DEPRECATED("Please use onWithExpectedValues:expectedValueInterval:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (void)toggleWithParams:(ZGMTROnOffClusterToggleParams * _Nullable)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completionHandler:(ZGMTRStatusCompletion)completionHandler ZGMTR_DEPRECATED("Please use toggleWithParams:expectedValues:expectedValueInterval:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (void)toggleWithExpectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedValues expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completionHandler:(ZGMTRStatusCompletion)completionHandler ZGMTR_DEPRECATED("Please use toggleWithExpectedValues:expectedValueInterval:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (void)offWithEffectWithParams:(ZGMTROnOffClusterOffWithEffectParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completionHandler:(ZGMTRStatusCompletion)completionHandler ZGMTR_DEPRECATED("Please use offWithEffectWithParams:expectedValues:expectedValueInterval:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (void)onWithRecallGlobalSceneWithParams:(ZGMTROnOffClusterOnWithRecallGlobalSceneParams * _Nullable)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completionHandler:(ZGMTRStatusCompletion)completionHandler ZGMTR_DEPRECATED("Please use onWithRecallGlobalSceneWithParams:expectedValues:expectedValueInterval:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (void)onWithRecallGlobalSceneWithExpectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedValues expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completionHandler:(ZGMTRStatusCompletion)completionHandler ZGMTR_DEPRECATED("Please use onWithRecallGlobalSceneWithExpectedValues:expectedValueInterval:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (void)onWithTimedOffWithParams:(ZGMTROnOffClusterOnWithTimedOffParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completionHandler:(ZGMTRStatusCompletion)completionHandler ZGMTR_DEPRECATED("Please use onWithTimedOffWithParams:expectedValues:expectedValueInterval:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
@end

@interface ZGMTRClusterLevelControl (Deprecated)

- (nullable instancetype)initWithDevice:(ZGMTRDevice *)device
                               endpoint:(uint16_t)endpoint
                                  queue:(dispatch_queue_t)queue ZGMTR_DEPRECATED("Please use initWithDevice:endpoindID:queue:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));

- (void)moveToLevelWithParams:(ZGMTRLevelControlClusterMoveToLevelParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completionHandler:(ZGMTRStatusCompletion)completionHandler ZGMTR_DEPRECATED("Please use moveToLevelWithParams:expectedValues:expectedValueInterval:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (void)moveWithParams:(ZGMTRLevelControlClusterMoveParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completionHandler:(ZGMTRStatusCompletion)completionHandler ZGMTR_DEPRECATED("Please use moveWithParams:expectedValues:expectedValueInterval:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (void)stepWithParams:(ZGMTRLevelControlClusterStepParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completionHandler:(ZGMTRStatusCompletion)completionHandler ZGMTR_DEPRECATED("Please use stepWithParams:expectedValues:expectedValueInterval:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (void)stopWithParams:(ZGMTRLevelControlClusterStopParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completionHandler:(ZGMTRStatusCompletion)completionHandler ZGMTR_DEPRECATED("Please use stopWithParams:expectedValues:expectedValueInterval:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (void)moveToLevelWithOnOffWithParams:(ZGMTRLevelControlClusterMoveToLevelWithOnOffParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completionHandler:(ZGMTRStatusCompletion)completionHandler ZGMTR_DEPRECATED("Please use moveToLevelWithOnOffWithParams:expectedValues:expectedValueInterval:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (void)moveWithOnOffWithParams:(ZGMTRLevelControlClusterMoveWithOnOffParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completionHandler:(ZGMTRStatusCompletion)completionHandler ZGMTR_DEPRECATED("Please use moveWithOnOffWithParams:expectedValues:expectedValueInterval:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (void)stepWithOnOffWithParams:(ZGMTRLevelControlClusterStepWithOnOffParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completionHandler:(ZGMTRStatusCompletion)completionHandler ZGMTR_DEPRECATED("Please use stepWithOnOffWithParams:expectedValues:expectedValueInterval:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (void)stopWithOnOffWithParams:(ZGMTRLevelControlClusterStopWithOnOffParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completionHandler:(ZGMTRStatusCompletion)completionHandler ZGMTR_DEPRECATED("Please use stopWithOnOffWithParams:expectedValues:expectedValueInterval:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (void)moveToClosestFrequencyWithParams:(ZGMTRLevelControlClusterMoveToClosestFrequencyParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completionHandler:(ZGMTRStatusCompletion)completionHandler ZGMTR_DEPRECATED("Please use moveToClosestFrequencyWithParams:expectedValues:expectedValueInterval:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
@end

@interface ZGMTRClusterDescriptor (Deprecated)

- (nullable instancetype)initWithDevice:(ZGMTRDevice *)device
                               endpoint:(uint16_t)endpoint
                                  queue:(dispatch_queue_t)queue ZGMTR_DEPRECATED("Please use initWithDevice:endpoindID:queue:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));

- (NSDictionary<NSString *, id> *)readAttributeDeviceListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_DEPRECATED("Please use readAttributeDeviceTypeListWithParams on ZGMTRClusterDescriptor", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
@end

@interface ZGMTRClusterBinding (Deprecated)

- (nullable instancetype)initWithDevice:(ZGMTRDevice *)device
                               endpoint:(uint16_t)endpoint
                                  queue:(dispatch_queue_t)queue ZGMTR_DEPRECATED("Please use initWithDevice:endpoindID:queue:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));

@end

@interface ZGMTRClusterAccessControl (Deprecated)

- (nullable instancetype)initWithDevice:(ZGMTRDevice *)device
                               endpoint:(uint16_t)endpoint
                                  queue:(dispatch_queue_t)queue ZGMTR_DEPRECATED("Please use initWithDevice:endpoindID:queue:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));

- (NSDictionary<NSString *, id> *)readAttributeAclWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_DEPRECATED("Please use readAttributeACLWithParams on ZGMTRClusterAccessControl", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (void)writeAttributeAclWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs ZGMTR_DEPRECATED("Please use writeAttributeACLWithValue on ZGMTRClusterAccessControl", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (void)writeAttributeAclWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs params:(ZGMTRWriteParams * _Nullable)params ZGMTR_DEPRECATED("Please use writeAttributeACLWithValue on ZGMTRClusterAccessControl", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
@end

@interface ZGMTRClusterActions (Deprecated)

- (nullable instancetype)initWithDevice:(ZGMTRDevice *)device
                               endpoint:(uint16_t)endpoint
                                  queue:(dispatch_queue_t)queue ZGMTR_DEPRECATED("Please use initWithDevice:endpoindID:queue:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));

- (void)instantActionWithParams:(ZGMTRActionsClusterInstantActionParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completionHandler:(ZGMTRStatusCompletion)completionHandler ZGMTR_DEPRECATED("Please use instantActionWithParams:expectedValues:expectedValueInterval:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (void)instantActionWithTransitionWithParams:(ZGMTRActionsClusterInstantActionWithTransitionParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completionHandler:(ZGMTRStatusCompletion)completionHandler ZGMTR_DEPRECATED("Please use instantActionWithTransitionWithParams:expectedValues:expectedValueInterval:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (void)startActionWithParams:(ZGMTRActionsClusterStartActionParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completionHandler:(ZGMTRStatusCompletion)completionHandler ZGMTR_DEPRECATED("Please use startActionWithParams:expectedValues:expectedValueInterval:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (void)startActionWithDurationWithParams:(ZGMTRActionsClusterStartActionWithDurationParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completionHandler:(ZGMTRStatusCompletion)completionHandler ZGMTR_DEPRECATED("Please use startActionWithDurationWithParams:expectedValues:expectedValueInterval:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (void)stopActionWithParams:(ZGMTRActionsClusterStopActionParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completionHandler:(ZGMTRStatusCompletion)completionHandler ZGMTR_DEPRECATED("Please use stopActionWithParams:expectedValues:expectedValueInterval:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (void)pauseActionWithParams:(ZGMTRActionsClusterPauseActionParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completionHandler:(ZGMTRStatusCompletion)completionHandler ZGMTR_DEPRECATED("Please use pauseActionWithParams:expectedValues:expectedValueInterval:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (void)pauseActionWithDurationWithParams:(ZGMTRActionsClusterPauseActionWithDurationParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completionHandler:(ZGMTRStatusCompletion)completionHandler ZGMTR_DEPRECATED("Please use pauseActionWithDurationWithParams:expectedValues:expectedValueInterval:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (void)resumeActionWithParams:(ZGMTRActionsClusterResumeActionParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completionHandler:(ZGMTRStatusCompletion)completionHandler ZGMTR_DEPRECATED("Please use resumeActionWithParams:expectedValues:expectedValueInterval:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (void)enableActionWithParams:(ZGMTRActionsClusterEnableActionParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completionHandler:(ZGMTRStatusCompletion)completionHandler ZGMTR_DEPRECATED("Please use enableActionWithParams:expectedValues:expectedValueInterval:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (void)enableActionWithDurationWithParams:(ZGMTRActionsClusterEnableActionWithDurationParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completionHandler:(ZGMTRStatusCompletion)completionHandler ZGMTR_DEPRECATED("Please use enableActionWithDurationWithParams:expectedValues:expectedValueInterval:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (void)disableActionWithParams:(ZGMTRActionsClusterDisableActionParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completionHandler:(ZGMTRStatusCompletion)completionHandler ZGMTR_DEPRECATED("Please use disableActionWithParams:expectedValues:expectedValueInterval:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (void)disableActionWithDurationWithParams:(ZGMTRActionsClusterDisableActionWithDurationParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completionHandler:(ZGMTRStatusCompletion)completionHandler ZGMTR_DEPRECATED("Please use disableActionWithDurationWithParams:expectedValues:expectedValueInterval:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
@end

@interface ZGMTRClusterBasic (Deprecated)

- (nullable instancetype)initWithDevice:(ZGMTRDevice *)device
                               endpoint:(uint16_t)endpoint
                                  queue:(dispatch_queue_t)queue ZGMTR_DEPRECATED("Please use initWithDevice:endpoindID:queue:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));

- (void)mfgSpecificPingWithParams:(ZGMTRBasicClusterMfgSpecificPingParams * _Nullable)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completionHandler:(ZGMTRStatusCompletion)completionHandler ZGMTR_DEPRECATED("Please use mfgSpecificPingWithParams:expectedValues:expectedValueInterval:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (void)mfgSpecificPingWithExpectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedValues expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completionHandler:(ZGMTRStatusCompletion)completionHandler ZGMTR_DEPRECATED("Please use mfgSpecificPingWithExpectedValues:expectedValueInterval:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
@end

@interface ZGMTRClusterOtaSoftwareUpdateProvider (Deprecated)

- (nullable instancetype)initWithDevice:(ZGMTRDevice *)device
                               endpoint:(uint16_t)endpoint
                                  queue:(dispatch_queue_t)queue ZGMTR_DEPRECATED("Please use initWithDevice:endpoindID:queue:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));

- (void)queryImageWithParams:(ZGMTROtaSoftwareUpdateProviderClusterQueryImageParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completionHandler:(void (^)(ZGMTROtaSoftwareUpdateProviderClusterQueryImageResponseParams * _Nullable data, NSError * _Nullable error))completionHandler ZGMTR_DEPRECATED("Please use queryImageWithParams:expectedValues:expectedValueInterval:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (void)applyUpdateRequestWithParams:(ZGMTROtaSoftwareUpdateProviderClusterApplyUpdateRequestParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completionHandler:(void (^)(ZGMTROtaSoftwareUpdateProviderClusterApplyUpdateResponseParams * _Nullable data, NSError * _Nullable error))completionHandler ZGMTR_DEPRECATED("Please use applyUpdateRequestWithParams:expectedValues:expectedValueInterval:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (void)notifyUpdateAppliedWithParams:(ZGMTROtaSoftwareUpdateProviderClusterNotifyUpdateAppliedParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completionHandler:(ZGMTRStatusCompletion)completionHandler ZGMTR_DEPRECATED("Please use notifyUpdateAppliedWithParams:expectedValues:expectedValueInterval:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
@end

@interface ZGMTRClusterOtaSoftwareUpdateRequestor (Deprecated)

- (nullable instancetype)initWithDevice:(ZGMTRDevice *)device
                               endpoint:(uint16_t)endpoint
                                  queue:(dispatch_queue_t)queue ZGMTR_DEPRECATED("Please use initWithDevice:endpoindID:queue:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));

- (void)announceOtaProviderWithParams:(ZGMTROtaSoftwareUpdateRequestorClusterAnnounceOtaProviderParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completionHandler:(ZGMTRStatusCompletion)completionHandler ZGMTR_DEPRECATED("Please use announceOTAProviderWithParams:expectedValues:expectedValueInterval:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (NSDictionary<NSString *, id> *)readAttributeDefaultOtaProvidersWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_DEPRECATED("Please use readAttributeDefaultOTAProvidersWithParams on ZGMTRClusterOTASoftwareUpdateRequestor", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (void)writeAttributeDefaultOtaProvidersWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs ZGMTR_DEPRECATED("Please use writeAttributeDefaultOTAProvidersWithValue on ZGMTRClusterOTASoftwareUpdateRequestor", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (void)writeAttributeDefaultOtaProvidersWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs params:(ZGMTRWriteParams * _Nullable)params ZGMTR_DEPRECATED("Please use writeAttributeDefaultOTAProvidersWithValue on ZGMTRClusterOTASoftwareUpdateRequestor", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
@end

@interface ZGMTRClusterLocalizationConfiguration (Deprecated)

- (nullable instancetype)initWithDevice:(ZGMTRDevice *)device
                               endpoint:(uint16_t)endpoint
                                  queue:(dispatch_queue_t)queue ZGMTR_DEPRECATED("Please use initWithDevice:endpoindID:queue:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));

@end

@interface ZGMTRClusterTimeFormatLocalization (Deprecated)

- (nullable instancetype)initWithDevice:(ZGMTRDevice *)device
                               endpoint:(uint16_t)endpoint
                                  queue:(dispatch_queue_t)queue ZGMTR_DEPRECATED("Please use initWithDevice:endpoindID:queue:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));

@end

@interface ZGMTRClusterUnitLocalization (Deprecated)

- (nullable instancetype)initWithDevice:(ZGMTRDevice *)device
                               endpoint:(uint16_t)endpoint
                                  queue:(dispatch_queue_t)queue ZGMTR_DEPRECATED("Please use initWithDevice:endpoindID:queue:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));

@end

@interface ZGMTRClusterPowerSourceConfiguration (Deprecated)

- (nullable instancetype)initWithDevice:(ZGMTRDevice *)device
                               endpoint:(uint16_t)endpoint
                                  queue:(dispatch_queue_t)queue ZGMTR_DEPRECATED("Please use initWithDevice:endpoindID:queue:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));

@end

@interface ZGMTRClusterPowerSource (Deprecated)

- (nullable instancetype)initWithDevice:(ZGMTRDevice *)device
                               endpoint:(uint16_t)endpoint
                                  queue:(dispatch_queue_t)queue ZGMTR_DEPRECATED("Please use initWithDevice:endpoindID:queue:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));

@end

@interface ZGMTRClusterGeneralCommissioning (Deprecated)

- (nullable instancetype)initWithDevice:(ZGMTRDevice *)device
                               endpoint:(uint16_t)endpoint
                                  queue:(dispatch_queue_t)queue ZGMTR_DEPRECATED("Please use initWithDevice:endpoindID:queue:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));

- (void)armFailSafeWithParams:(ZGMTRGeneralCommissioningClusterArmFailSafeParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completionHandler:(void (^)(ZGMTRGeneralCommissioningClusterArmFailSafeResponseParams * _Nullable data, NSError * _Nullable error))completionHandler ZGMTR_DEPRECATED("Please use armFailSafeWithParams:expectedValues:expectedValueInterval:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (void)setRegulatoryConfigWithParams:(ZGMTRGeneralCommissioningClusterSetRegulatoryConfigParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completionHandler:(void (^)(ZGMTRGeneralCommissioningClusterSetRegulatoryConfigResponseParams * _Nullable data, NSError * _Nullable error))completionHandler ZGMTR_DEPRECATED("Please use setRegulatoryConfigWithParams:expectedValues:expectedValueInterval:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (void)commissioningCompleteWithParams:(ZGMTRGeneralCommissioningClusterCommissioningCompleteParams * _Nullable)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completionHandler:(void (^)(ZGMTRGeneralCommissioningClusterCommissioningCompleteResponseParams * _Nullable data, NSError * _Nullable error))completionHandler ZGMTR_DEPRECATED("Please use commissioningCompleteWithParams:expectedValues:expectedValueInterval:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (void)commissioningCompleteWithExpectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedValues expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completionHandler:(void (^)(ZGMTRGeneralCommissioningClusterCommissioningCompleteResponseParams * _Nullable data, NSError * _Nullable error))completionHandler ZGMTR_DEPRECATED("Please use commissioningCompleteWithExpectedValues:expectedValueInterval:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
@end

@interface ZGMTRClusterNetworkCommissioning (Deprecated)

- (nullable instancetype)initWithDevice:(ZGMTRDevice *)device
                               endpoint:(uint16_t)endpoint
                                  queue:(dispatch_queue_t)queue ZGMTR_DEPRECATED("Please use initWithDevice:endpoindID:queue:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));

- (void)scanNetworksWithParams:(ZGMTRNetworkCommissioningClusterScanNetworksParams * _Nullable)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completionHandler:(void (^)(ZGMTRNetworkCommissioningClusterScanNetworksResponseParams * _Nullable data, NSError * _Nullable error))completionHandler ZGMTR_DEPRECATED("Please use scanNetworksWithParams:expectedValues:expectedValueInterval:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (void)addOrUpdateWiFiNetworkWithParams:(ZGMTRNetworkCommissioningClusterAddOrUpdateWiFiNetworkParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completionHandler:(void (^)(ZGMTRNetworkCommissioningClusterNetworkConfigResponseParams * _Nullable data, NSError * _Nullable error))completionHandler ZGMTR_DEPRECATED("Please use addOrUpdateWiFiNetworkWithParams:expectedValues:expectedValueInterval:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (void)addOrUpdateThreadNetworkWithParams:(ZGMTRNetworkCommissioningClusterAddOrUpdateThreadNetworkParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completionHandler:(void (^)(ZGMTRNetworkCommissioningClusterNetworkConfigResponseParams * _Nullable data, NSError * _Nullable error))completionHandler ZGMTR_DEPRECATED("Please use addOrUpdateThreadNetworkWithParams:expectedValues:expectedValueInterval:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (void)removeNetworkWithParams:(ZGMTRNetworkCommissioningClusterRemoveNetworkParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completionHandler:(void (^)(ZGMTRNetworkCommissioningClusterNetworkConfigResponseParams * _Nullable data, NSError * _Nullable error))completionHandler ZGMTR_DEPRECATED("Please use removeNetworkWithParams:expectedValues:expectedValueInterval:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (void)connectNetworkWithParams:(ZGMTRNetworkCommissioningClusterConnectNetworkParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completionHandler:(void (^)(ZGMTRNetworkCommissioningClusterConnectNetworkResponseParams * _Nullable data, NSError * _Nullable error))completionHandler ZGMTR_DEPRECATED("Please use connectNetworkWithParams:expectedValues:expectedValueInterval:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (void)reorderNetworkWithParams:(ZGMTRNetworkCommissioningClusterReorderNetworkParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completionHandler:(void (^)(ZGMTRNetworkCommissioningClusterNetworkConfigResponseParams * _Nullable data, NSError * _Nullable error))completionHandler ZGMTR_DEPRECATED("Please use reorderNetworkWithParams:expectedValues:expectedValueInterval:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
@end

@interface ZGMTRClusterDiagnosticLogs (Deprecated)

- (nullable instancetype)initWithDevice:(ZGMTRDevice *)device
                               endpoint:(uint16_t)endpoint
                                  queue:(dispatch_queue_t)queue ZGMTR_DEPRECATED("Please use initWithDevice:endpoindID:queue:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));

- (void)retrieveLogsRequestWithParams:(ZGMTRDiagnosticLogsClusterRetrieveLogsRequestParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completionHandler:(void (^)(ZGMTRDiagnosticLogsClusterRetrieveLogsResponseParams * _Nullable data, NSError * _Nullable error))completionHandler ZGMTR_DEPRECATED("Please use retrieveLogsRequestWithParams:expectedValues:expectedValueInterval:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
@end

@interface ZGMTRClusterGeneralDiagnostics (Deprecated)

- (nullable instancetype)initWithDevice:(ZGMTRDevice *)device
                               endpoint:(uint16_t)endpoint
                                  queue:(dispatch_queue_t)queue ZGMTR_DEPRECATED("Please use initWithDevice:endpoindID:queue:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));

- (void)testEventTriggerWithParams:(ZGMTRGeneralDiagnosticsClusterTestEventTriggerParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completionHandler:(ZGMTRStatusCompletion)completionHandler ZGMTR_DEPRECATED("Please use testEventTriggerWithParams:expectedValues:expectedValueInterval:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (NSDictionary<NSString *, id> *)readAttributeBootReasonsWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_DEPRECATED("Please use readAttributeBootReasonWithParams on ZGMTRClusterGeneralDiagnostics", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
@end

@interface ZGMTRClusterSoftwareDiagnostics (Deprecated)

- (nullable instancetype)initWithDevice:(ZGMTRDevice *)device
                               endpoint:(uint16_t)endpoint
                                  queue:(dispatch_queue_t)queue ZGMTR_DEPRECATED("Please use initWithDevice:endpoindID:queue:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));

- (void)resetWatermarksWithParams:(ZGMTRSoftwareDiagnosticsClusterResetWatermarksParams * _Nullable)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completionHandler:(ZGMTRStatusCompletion)completionHandler ZGMTR_DEPRECATED("Please use resetWatermarksWithParams:expectedValues:expectedValueInterval:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (void)resetWatermarksWithExpectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedValues expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completionHandler:(ZGMTRStatusCompletion)completionHandler ZGMTR_DEPRECATED("Please use resetWatermarksWithExpectedValues:expectedValueInterval:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
@end

@interface ZGMTRClusterThreadNetworkDiagnostics (Deprecated)

- (nullable instancetype)initWithDevice:(ZGMTRDevice *)device
                               endpoint:(uint16_t)endpoint
                                  queue:(dispatch_queue_t)queue ZGMTR_DEPRECATED("Please use initWithDevice:endpoindID:queue:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));

- (void)resetCountsWithParams:(ZGMTRThreadNetworkDiagnosticsClusterResetCountsParams * _Nullable)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completionHandler:(ZGMTRStatusCompletion)completionHandler ZGMTR_DEPRECATED("Please use resetCountsWithParams:expectedValues:expectedValueInterval:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (void)resetCountsWithExpectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedValues expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completionHandler:(ZGMTRStatusCompletion)completionHandler ZGMTR_DEPRECATED("Please use resetCountsWithExpectedValues:expectedValueInterval:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (NSDictionary<NSString *, id> *)readAttributeNeighborTableListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_DEPRECATED("Please use readAttributeNeighborTableWithParams on ZGMTRClusterThreadNetworkDiagnostics", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (NSDictionary<NSString *, id> *)readAttributeRouteTableListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_DEPRECATED("Please use readAttributeRouteTableWithParams on ZGMTRClusterThreadNetworkDiagnostics", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
@end

@interface ZGMTRClusterWiFiNetworkDiagnostics (Deprecated)

- (nullable instancetype)initWithDevice:(ZGMTRDevice *)device
                               endpoint:(uint16_t)endpoint
                                  queue:(dispatch_queue_t)queue ZGMTR_DEPRECATED("Please use initWithDevice:endpoindID:queue:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));

- (void)resetCountsWithParams:(ZGMTRWiFiNetworkDiagnosticsClusterResetCountsParams * _Nullable)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completionHandler:(ZGMTRStatusCompletion)completionHandler ZGMTR_DEPRECATED("Please use resetCountsWithParams:expectedValues:expectedValueInterval:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (void)resetCountsWithExpectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedValues expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completionHandler:(ZGMTRStatusCompletion)completionHandler ZGMTR_DEPRECATED("Please use resetCountsWithExpectedValues:expectedValueInterval:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (NSDictionary<NSString *, id> *)readAttributeBssidWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_DEPRECATED("Please use readAttributeBSSIDWithParams on ZGMTRClusterWiFiNetworkDiagnostics", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (NSDictionary<NSString *, id> *)readAttributeRssiWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_DEPRECATED("Please use readAttributeRSSIWithParams on ZGMTRClusterWiFiNetworkDiagnostics", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
@end

@interface ZGMTRClusterEthernetNetworkDiagnostics (Deprecated)

- (nullable instancetype)initWithDevice:(ZGMTRDevice *)device
                               endpoint:(uint16_t)endpoint
                                  queue:(dispatch_queue_t)queue ZGMTR_DEPRECATED("Please use initWithDevice:endpoindID:queue:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));

- (void)resetCountsWithParams:(ZGMTREthernetNetworkDiagnosticsClusterResetCountsParams * _Nullable)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completionHandler:(ZGMTRStatusCompletion)completionHandler ZGMTR_DEPRECATED("Please use resetCountsWithParams:expectedValues:expectedValueInterval:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (void)resetCountsWithExpectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedValues expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completionHandler:(ZGMTRStatusCompletion)completionHandler ZGMTR_DEPRECATED("Please use resetCountsWithExpectedValues:expectedValueInterval:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
@end

@interface ZGMTRClusterBridgedDeviceBasic (Deprecated)

- (nullable instancetype)initWithDevice:(ZGMTRDevice *)device
                               endpoint:(uint16_t)endpoint
                                  queue:(dispatch_queue_t)queue ZGMTR_DEPRECATED("Please use initWithDevice:endpoindID:queue:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));

@end

@interface ZGMTRClusterSwitch (Deprecated)

- (nullable instancetype)initWithDevice:(ZGMTRDevice *)device
                               endpoint:(uint16_t)endpoint
                                  queue:(dispatch_queue_t)queue ZGMTR_DEPRECATED("Please use initWithDevice:endpoindID:queue:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));

@end

@interface ZGMTRClusterAdministratorCommissioning (Deprecated)

- (nullable instancetype)initWithDevice:(ZGMTRDevice *)device
                               endpoint:(uint16_t)endpoint
                                  queue:(dispatch_queue_t)queue ZGMTR_DEPRECATED("Please use initWithDevice:endpoindID:queue:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));

- (void)openCommissioningWindowWithParams:(ZGMTRAdministratorCommissioningClusterOpenCommissioningWindowParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completionHandler:(ZGMTRStatusCompletion)completionHandler ZGMTR_DEPRECATED("Please use openCommissioningWindowWithParams:expectedValues:expectedValueInterval:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (void)openBasicCommissioningWindowWithParams:(ZGMTRAdministratorCommissioningClusterOpenBasicCommissioningWindowParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completionHandler:(ZGMTRStatusCompletion)completionHandler ZGMTR_DEPRECATED("Please use openBasicCommissioningWindowWithParams:expectedValues:expectedValueInterval:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (void)revokeCommissioningWithParams:(ZGMTRAdministratorCommissioningClusterRevokeCommissioningParams * _Nullable)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completionHandler:(ZGMTRStatusCompletion)completionHandler ZGMTR_DEPRECATED("Please use revokeCommissioningWithParams:expectedValues:expectedValueInterval:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (void)revokeCommissioningWithExpectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedValues expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completionHandler:(ZGMTRStatusCompletion)completionHandler ZGMTR_DEPRECATED("Please use revokeCommissioningWithExpectedValues:expectedValueInterval:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
@end

@interface ZGMTRClusterOperationalCredentials (Deprecated)

- (nullable instancetype)initWithDevice:(ZGMTRDevice *)device
                               endpoint:(uint16_t)endpoint
                                  queue:(dispatch_queue_t)queue ZGMTR_DEPRECATED("Please use initWithDevice:endpoindID:queue:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));

- (void)attestationRequestWithParams:(ZGMTROperationalCredentialsClusterAttestationRequestParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completionHandler:(void (^)(ZGMTROperationalCredentialsClusterAttestationResponseParams * _Nullable data, NSError * _Nullable error))completionHandler ZGMTR_DEPRECATED("Please use attestationRequestWithParams:expectedValues:expectedValueInterval:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (void)certificateChainRequestWithParams:(ZGMTROperationalCredentialsClusterCertificateChainRequestParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completionHandler:(void (^)(ZGMTROperationalCredentialsClusterCertificateChainResponseParams * _Nullable data, NSError * _Nullable error))completionHandler ZGMTR_DEPRECATED("Please use certificateChainRequestWithParams:expectedValues:expectedValueInterval:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (void)CSRRequestWithParams:(ZGMTROperationalCredentialsClusterCSRRequestParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completionHandler:(void (^)(ZGMTROperationalCredentialsClusterCSRResponseParams * _Nullable data, NSError * _Nullable error))completionHandler ZGMTR_DEPRECATED("Please use CSRRequestWithParams:expectedValues:expectedValueInterval:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (void)addNOCWithParams:(ZGMTROperationalCredentialsClusterAddNOCParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completionHandler:(void (^)(ZGMTROperationalCredentialsClusterNOCResponseParams * _Nullable data, NSError * _Nullable error))completionHandler ZGMTR_DEPRECATED("Please use addNOCWithParams:expectedValues:expectedValueInterval:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (void)updateNOCWithParams:(ZGMTROperationalCredentialsClusterUpdateNOCParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completionHandler:(void (^)(ZGMTROperationalCredentialsClusterNOCResponseParams * _Nullable data, NSError * _Nullable error))completionHandler ZGMTR_DEPRECATED("Please use updateNOCWithParams:expectedValues:expectedValueInterval:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (void)updateFabricLabelWithParams:(ZGMTROperationalCredentialsClusterUpdateFabricLabelParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completionHandler:(void (^)(ZGMTROperationalCredentialsClusterNOCResponseParams * _Nullable data, NSError * _Nullable error))completionHandler ZGMTR_DEPRECATED("Please use updateFabricLabelWithParams:expectedValues:expectedValueInterval:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (void)removeFabricWithParams:(ZGMTROperationalCredentialsClusterRemoveFabricParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completionHandler:(void (^)(ZGMTROperationalCredentialsClusterNOCResponseParams * _Nullable data, NSError * _Nullable error))completionHandler ZGMTR_DEPRECATED("Please use removeFabricWithParams:expectedValues:expectedValueInterval:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (void)addTrustedRootCertificateWithParams:(ZGMTROperationalCredentialsClusterAddTrustedRootCertificateParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completionHandler:(ZGMTRStatusCompletion)completionHandler ZGMTR_DEPRECATED("Please use addTrustedRootCertificateWithParams:expectedValues:expectedValueInterval:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
@end

@interface ZGMTRClusterGroupKeyManagement (Deprecated)

- (nullable instancetype)initWithDevice:(ZGMTRDevice *)device
                               endpoint:(uint16_t)endpoint
                                  queue:(dispatch_queue_t)queue ZGMTR_DEPRECATED("Please use initWithDevice:endpoindID:queue:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));

- (void)keySetWriteWithParams:(ZGMTRGroupKeyManagementClusterKeySetWriteParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completionHandler:(ZGMTRStatusCompletion)completionHandler ZGMTR_DEPRECATED("Please use keySetWriteWithParams:expectedValues:expectedValueInterval:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (void)keySetReadWithParams:(ZGMTRGroupKeyManagementClusterKeySetReadParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completionHandler:(void (^)(ZGMTRGroupKeyManagementClusterKeySetReadResponseParams * _Nullable data, NSError * _Nullable error))completionHandler ZGMTR_DEPRECATED("Please use keySetReadWithParams:expectedValues:expectedValueInterval:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (void)keySetRemoveWithParams:(ZGMTRGroupKeyManagementClusterKeySetRemoveParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completionHandler:(ZGMTRStatusCompletion)completionHandler ZGMTR_DEPRECATED("Please use keySetRemoveWithParams:expectedValues:expectedValueInterval:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (void)keySetReadAllIndicesWithParams:(ZGMTRGroupKeyManagementClusterKeySetReadAllIndicesParams * _Nullable)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completionHandler:(void (^)(ZGMTRGroupKeyManagementClusterKeySetReadAllIndicesResponseParams * _Nullable data, NSError * _Nullable error))completionHandler ZGMTR_DEPRECATED("Please use keySetReadAllIndicesWithParams:expectedValues:expectedValueInterval:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
@end

@interface ZGMTRClusterFixedLabel (Deprecated)

- (nullable instancetype)initWithDevice:(ZGMTRDevice *)device
                               endpoint:(uint16_t)endpoint
                                  queue:(dispatch_queue_t)queue ZGMTR_DEPRECATED("Please use initWithDevice:endpoindID:queue:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));

@end

@interface ZGMTRClusterUserLabel (Deprecated)

- (nullable instancetype)initWithDevice:(ZGMTRDevice *)device
                               endpoint:(uint16_t)endpoint
                                  queue:(dispatch_queue_t)queue ZGMTR_DEPRECATED("Please use initWithDevice:endpoindID:queue:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));

@end

@interface ZGMTRClusterBooleanState (Deprecated)

- (nullable instancetype)initWithDevice:(ZGMTRDevice *)device
                               endpoint:(uint16_t)endpoint
                                  queue:(dispatch_queue_t)queue ZGMTR_DEPRECATED("Please use initWithDevice:endpoindID:queue:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));

@end

@interface ZGMTRClusterModeSelect (Deprecated)

- (nullable instancetype)initWithDevice:(ZGMTRDevice *)device
                               endpoint:(uint16_t)endpoint
                                  queue:(dispatch_queue_t)queue ZGMTR_DEPRECATED("Please use initWithDevice:endpoindID:queue:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));

- (void)changeToModeWithParams:(ZGMTRModeSelectClusterChangeToModeParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completionHandler:(ZGMTRStatusCompletion)completionHandler ZGMTR_DEPRECATED("Please use changeToModeWithParams:expectedValues:expectedValueInterval:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
@end

@interface ZGMTRClusterDoorLock (Deprecated)

- (nullable instancetype)initWithDevice:(ZGMTRDevice *)device
                               endpoint:(uint16_t)endpoint
                                  queue:(dispatch_queue_t)queue ZGMTR_DEPRECATED("Please use initWithDevice:endpoindID:queue:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));

- (void)lockDoorWithParams:(ZGMTRDoorLockClusterLockDoorParams * _Nullable)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completionHandler:(ZGMTRStatusCompletion)completionHandler ZGMTR_DEPRECATED("Please use lockDoorWithParams:expectedValues:expectedValueInterval:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (void)unlockDoorWithParams:(ZGMTRDoorLockClusterUnlockDoorParams * _Nullable)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completionHandler:(ZGMTRStatusCompletion)completionHandler ZGMTR_DEPRECATED("Please use unlockDoorWithParams:expectedValues:expectedValueInterval:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (void)unlockWithTimeoutWithParams:(ZGMTRDoorLockClusterUnlockWithTimeoutParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completionHandler:(ZGMTRStatusCompletion)completionHandler ZGMTR_DEPRECATED("Please use unlockWithTimeoutWithParams:expectedValues:expectedValueInterval:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (void)setWeekDayScheduleWithParams:(ZGMTRDoorLockClusterSetWeekDayScheduleParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completionHandler:(ZGMTRStatusCompletion)completionHandler ZGMTR_DEPRECATED("Please use setWeekDayScheduleWithParams:expectedValues:expectedValueInterval:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (void)getWeekDayScheduleWithParams:(ZGMTRDoorLockClusterGetWeekDayScheduleParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completionHandler:(void (^)(ZGMTRDoorLockClusterGetWeekDayScheduleResponseParams * _Nullable data, NSError * _Nullable error))completionHandler ZGMTR_DEPRECATED("Please use getWeekDayScheduleWithParams:expectedValues:expectedValueInterval:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (void)clearWeekDayScheduleWithParams:(ZGMTRDoorLockClusterClearWeekDayScheduleParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completionHandler:(ZGMTRStatusCompletion)completionHandler ZGMTR_DEPRECATED("Please use clearWeekDayScheduleWithParams:expectedValues:expectedValueInterval:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (void)setYearDayScheduleWithParams:(ZGMTRDoorLockClusterSetYearDayScheduleParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completionHandler:(ZGMTRStatusCompletion)completionHandler ZGMTR_DEPRECATED("Please use setYearDayScheduleWithParams:expectedValues:expectedValueInterval:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (void)getYearDayScheduleWithParams:(ZGMTRDoorLockClusterGetYearDayScheduleParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completionHandler:(void (^)(ZGMTRDoorLockClusterGetYearDayScheduleResponseParams * _Nullable data, NSError * _Nullable error))completionHandler ZGMTR_DEPRECATED("Please use getYearDayScheduleWithParams:expectedValues:expectedValueInterval:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (void)clearYearDayScheduleWithParams:(ZGMTRDoorLockClusterClearYearDayScheduleParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completionHandler:(ZGMTRStatusCompletion)completionHandler ZGMTR_DEPRECATED("Please use clearYearDayScheduleWithParams:expectedValues:expectedValueInterval:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (void)setHolidayScheduleWithParams:(ZGMTRDoorLockClusterSetHolidayScheduleParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completionHandler:(ZGMTRStatusCompletion)completionHandler ZGMTR_DEPRECATED("Please use setHolidayScheduleWithParams:expectedValues:expectedValueInterval:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (void)getHolidayScheduleWithParams:(ZGMTRDoorLockClusterGetHolidayScheduleParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completionHandler:(void (^)(ZGMTRDoorLockClusterGetHolidayScheduleResponseParams * _Nullable data, NSError * _Nullable error))completionHandler ZGMTR_DEPRECATED("Please use getHolidayScheduleWithParams:expectedValues:expectedValueInterval:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (void)clearHolidayScheduleWithParams:(ZGMTRDoorLockClusterClearHolidayScheduleParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completionHandler:(ZGMTRStatusCompletion)completionHandler ZGMTR_DEPRECATED("Please use clearHolidayScheduleWithParams:expectedValues:expectedValueInterval:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (void)setUserWithParams:(ZGMTRDoorLockClusterSetUserParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completionHandler:(ZGMTRStatusCompletion)completionHandler ZGMTR_DEPRECATED("Please use setUserWithParams:expectedValues:expectedValueInterval:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (void)getUserWithParams:(ZGMTRDoorLockClusterGetUserParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completionHandler:(void (^)(ZGMTRDoorLockClusterGetUserResponseParams * _Nullable data, NSError * _Nullable error))completionHandler ZGMTR_DEPRECATED("Please use getUserWithParams:expectedValues:expectedValueInterval:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (void)clearUserWithParams:(ZGMTRDoorLockClusterClearUserParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completionHandler:(ZGMTRStatusCompletion)completionHandler ZGMTR_DEPRECATED("Please use clearUserWithParams:expectedValues:expectedValueInterval:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (void)setCredentialWithParams:(ZGMTRDoorLockClusterSetCredentialParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completionHandler:(void (^)(ZGMTRDoorLockClusterSetCredentialResponseParams * _Nullable data, NSError * _Nullable error))completionHandler ZGMTR_DEPRECATED("Please use setCredentialWithParams:expectedValues:expectedValueInterval:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (void)getCredentialStatusWithParams:(ZGMTRDoorLockClusterGetCredentialStatusParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completionHandler:(void (^)(ZGMTRDoorLockClusterGetCredentialStatusResponseParams * _Nullable data, NSError * _Nullable error))completionHandler ZGMTR_DEPRECATED("Please use getCredentialStatusWithParams:expectedValues:expectedValueInterval:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (void)clearCredentialWithParams:(ZGMTRDoorLockClusterClearCredentialParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completionHandler:(ZGMTRStatusCompletion)completionHandler ZGMTR_DEPRECATED("Please use clearCredentialWithParams:expectedValues:expectedValueInterval:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
@end

@interface ZGMTRClusterWindowCovering (Deprecated)

- (nullable instancetype)initWithDevice:(ZGMTRDevice *)device
                               endpoint:(uint16_t)endpoint
                                  queue:(dispatch_queue_t)queue ZGMTR_DEPRECATED("Please use initWithDevice:endpoindID:queue:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));

- (void)upOrOpenWithParams:(ZGMTRWindowCoveringClusterUpOrOpenParams * _Nullable)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completionHandler:(ZGMTRStatusCompletion)completionHandler ZGMTR_DEPRECATED("Please use upOrOpenWithParams:expectedValues:expectedValueInterval:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (void)upOrOpenWithExpectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedValues expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completionHandler:(ZGMTRStatusCompletion)completionHandler ZGMTR_DEPRECATED("Please use upOrOpenWithExpectedValues:expectedValueInterval:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (void)downOrCloseWithParams:(ZGMTRWindowCoveringClusterDownOrCloseParams * _Nullable)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completionHandler:(ZGMTRStatusCompletion)completionHandler ZGMTR_DEPRECATED("Please use downOrCloseWithParams:expectedValues:expectedValueInterval:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (void)downOrCloseWithExpectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedValues expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completionHandler:(ZGMTRStatusCompletion)completionHandler ZGMTR_DEPRECATED("Please use downOrCloseWithExpectedValues:expectedValueInterval:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (void)stopMotionWithParams:(ZGMTRWindowCoveringClusterStopMotionParams * _Nullable)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completionHandler:(ZGMTRStatusCompletion)completionHandler ZGMTR_DEPRECATED("Please use stopMotionWithParams:expectedValues:expectedValueInterval:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (void)stopMotionWithExpectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedValues expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completionHandler:(ZGMTRStatusCompletion)completionHandler ZGMTR_DEPRECATED("Please use stopMotionWithExpectedValues:expectedValueInterval:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (void)goToLiftValueWithParams:(ZGMTRWindowCoveringClusterGoToLiftValueParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completionHandler:(ZGMTRStatusCompletion)completionHandler ZGMTR_DEPRECATED("Please use goToLiftValueWithParams:expectedValues:expectedValueInterval:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (void)goToLiftPercentageWithParams:(ZGMTRWindowCoveringClusterGoToLiftPercentageParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completionHandler:(ZGMTRStatusCompletion)completionHandler ZGMTR_DEPRECATED("Please use goToLiftPercentageWithParams:expectedValues:expectedValueInterval:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (void)goToTiltValueWithParams:(ZGMTRWindowCoveringClusterGoToTiltValueParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completionHandler:(ZGMTRStatusCompletion)completionHandler ZGMTR_DEPRECATED("Please use goToTiltValueWithParams:expectedValues:expectedValueInterval:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (void)goToTiltPercentageWithParams:(ZGMTRWindowCoveringClusterGoToTiltPercentageParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completionHandler:(ZGMTRStatusCompletion)completionHandler ZGMTR_DEPRECATED("Please use goToTiltPercentageWithParams:expectedValues:expectedValueInterval:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
@end

@interface ZGMTRClusterPumpConfigurationAndControl (Deprecated)

- (nullable instancetype)initWithDevice:(ZGMTRDevice *)device
                               endpoint:(uint16_t)endpoint
                                  queue:(dispatch_queue_t)queue ZGMTR_DEPRECATED("Please use initWithDevice:endpoindID:queue:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));

@end

@interface ZGMTRClusterThermostat (Deprecated)

- (nullable instancetype)initWithDevice:(ZGMTRDevice *)device
                               endpoint:(uint16_t)endpoint
                                  queue:(dispatch_queue_t)queue ZGMTR_DEPRECATED("Please use initWithDevice:endpoindID:queue:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));

- (void)setpointRaiseLowerWithParams:(ZGMTRThermostatClusterSetpointRaiseLowerParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completionHandler:(ZGMTRStatusCompletion)completionHandler ZGMTR_DEPRECATED("Please use setpointRaiseLowerWithParams:expectedValues:expectedValueInterval:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (void)setWeeklyScheduleWithParams:(ZGMTRThermostatClusterSetWeeklyScheduleParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completionHandler:(ZGMTRStatusCompletion)completionHandler ZGMTR_DEPRECATED("Please use setWeeklyScheduleWithParams:expectedValues:expectedValueInterval:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (void)getWeeklyScheduleWithParams:(ZGMTRThermostatClusterGetWeeklyScheduleParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completionHandler:(void (^)(ZGMTRThermostatClusterGetWeeklyScheduleResponseParams * _Nullable data, NSError * _Nullable error))completionHandler ZGMTR_DEPRECATED("Please use getWeeklyScheduleWithParams:expectedValues:expectedValueInterval:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (void)clearWeeklyScheduleWithParams:(ZGMTRThermostatClusterClearWeeklyScheduleParams * _Nullable)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completionHandler:(ZGMTRStatusCompletion)completionHandler ZGMTR_DEPRECATED("Please use clearWeeklyScheduleWithParams:expectedValues:expectedValueInterval:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (void)clearWeeklyScheduleWithExpectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedValues expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completionHandler:(ZGMTRStatusCompletion)completionHandler ZGMTR_DEPRECATED("Please use clearWeeklyScheduleWithExpectedValues:expectedValueInterval:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
@end

@interface ZGMTRClusterFanControl (Deprecated)

- (nullable instancetype)initWithDevice:(ZGMTRDevice *)device
                               endpoint:(uint16_t)endpoint
                                  queue:(dispatch_queue_t)queue ZGMTR_DEPRECATED("Please use initWithDevice:endpoindID:queue:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));

@end

@interface ZGMTRClusterThermostatUserInterfaceConfiguration (Deprecated)

- (nullable instancetype)initWithDevice:(ZGMTRDevice *)device
                               endpoint:(uint16_t)endpoint
                                  queue:(dispatch_queue_t)queue ZGMTR_DEPRECATED("Please use initWithDevice:endpoindID:queue:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));

@end

@interface ZGMTRClusterColorControl (Deprecated)

- (nullable instancetype)initWithDevice:(ZGMTRDevice *)device
                               endpoint:(uint16_t)endpoint
                                  queue:(dispatch_queue_t)queue ZGMTR_DEPRECATED("Please use initWithDevice:endpoindID:queue:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));

- (void)moveToHueWithParams:(ZGMTRColorControlClusterMoveToHueParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completionHandler:(ZGMTRStatusCompletion)completionHandler ZGMTR_DEPRECATED("Please use moveToHueWithParams:expectedValues:expectedValueInterval:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (void)moveHueWithParams:(ZGMTRColorControlClusterMoveHueParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completionHandler:(ZGMTRStatusCompletion)completionHandler ZGMTR_DEPRECATED("Please use moveHueWithParams:expectedValues:expectedValueInterval:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (void)stepHueWithParams:(ZGMTRColorControlClusterStepHueParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completionHandler:(ZGMTRStatusCompletion)completionHandler ZGMTR_DEPRECATED("Please use stepHueWithParams:expectedValues:expectedValueInterval:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (void)moveToSaturationWithParams:(ZGMTRColorControlClusterMoveToSaturationParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completionHandler:(ZGMTRStatusCompletion)completionHandler ZGMTR_DEPRECATED("Please use moveToSaturationWithParams:expectedValues:expectedValueInterval:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (void)moveSaturationWithParams:(ZGMTRColorControlClusterMoveSaturationParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completionHandler:(ZGMTRStatusCompletion)completionHandler ZGMTR_DEPRECATED("Please use moveSaturationWithParams:expectedValues:expectedValueInterval:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (void)stepSaturationWithParams:(ZGMTRColorControlClusterStepSaturationParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completionHandler:(ZGMTRStatusCompletion)completionHandler ZGMTR_DEPRECATED("Please use stepSaturationWithParams:expectedValues:expectedValueInterval:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (void)moveToHueAndSaturationWithParams:(ZGMTRColorControlClusterMoveToHueAndSaturationParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completionHandler:(ZGMTRStatusCompletion)completionHandler ZGMTR_DEPRECATED("Please use moveToHueAndSaturationWithParams:expectedValues:expectedValueInterval:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (void)moveToColorWithParams:(ZGMTRColorControlClusterMoveToColorParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completionHandler:(ZGMTRStatusCompletion)completionHandler ZGMTR_DEPRECATED("Please use moveToColorWithParams:expectedValues:expectedValueInterval:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (void)moveColorWithParams:(ZGMTRColorControlClusterMoveColorParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completionHandler:(ZGMTRStatusCompletion)completionHandler ZGMTR_DEPRECATED("Please use moveColorWithParams:expectedValues:expectedValueInterval:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (void)stepColorWithParams:(ZGMTRColorControlClusterStepColorParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completionHandler:(ZGMTRStatusCompletion)completionHandler ZGMTR_DEPRECATED("Please use stepColorWithParams:expectedValues:expectedValueInterval:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (void)moveToColorTemperatureWithParams:(ZGMTRColorControlClusterMoveToColorTemperatureParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completionHandler:(ZGMTRStatusCompletion)completionHandler ZGMTR_DEPRECATED("Please use moveToColorTemperatureWithParams:expectedValues:expectedValueInterval:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (void)enhancedMoveToHueWithParams:(ZGMTRColorControlClusterEnhancedMoveToHueParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completionHandler:(ZGMTRStatusCompletion)completionHandler ZGMTR_DEPRECATED("Please use enhancedMoveToHueWithParams:expectedValues:expectedValueInterval:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (void)enhancedMoveHueWithParams:(ZGMTRColorControlClusterEnhancedMoveHueParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completionHandler:(ZGMTRStatusCompletion)completionHandler ZGMTR_DEPRECATED("Please use enhancedMoveHueWithParams:expectedValues:expectedValueInterval:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (void)enhancedStepHueWithParams:(ZGMTRColorControlClusterEnhancedStepHueParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completionHandler:(ZGMTRStatusCompletion)completionHandler ZGMTR_DEPRECATED("Please use enhancedStepHueWithParams:expectedValues:expectedValueInterval:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (void)enhancedMoveToHueAndSaturationWithParams:(ZGMTRColorControlClusterEnhancedMoveToHueAndSaturationParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completionHandler:(ZGMTRStatusCompletion)completionHandler ZGMTR_DEPRECATED("Please use enhancedMoveToHueAndSaturationWithParams:expectedValues:expectedValueInterval:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (void)colorLoopSetWithParams:(ZGMTRColorControlClusterColorLoopSetParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completionHandler:(ZGMTRStatusCompletion)completionHandler ZGMTR_DEPRECATED("Please use colorLoopSetWithParams:expectedValues:expectedValueInterval:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (void)stopMoveStepWithParams:(ZGMTRColorControlClusterStopMoveStepParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completionHandler:(ZGMTRStatusCompletion)completionHandler ZGMTR_DEPRECATED("Please use stopMoveStepWithParams:expectedValues:expectedValueInterval:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (void)moveColorTemperatureWithParams:(ZGMTRColorControlClusterMoveColorTemperatureParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completionHandler:(ZGMTRStatusCompletion)completionHandler ZGMTR_DEPRECATED("Please use moveColorTemperatureWithParams:expectedValues:expectedValueInterval:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (void)stepColorTemperatureWithParams:(ZGMTRColorControlClusterStepColorTemperatureParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completionHandler:(ZGMTRStatusCompletion)completionHandler ZGMTR_DEPRECATED("Please use stepColorTemperatureWithParams:expectedValues:expectedValueInterval:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
@end

@interface ZGMTRClusterBallastConfiguration (Deprecated)

- (nullable instancetype)initWithDevice:(ZGMTRDevice *)device
                               endpoint:(uint16_t)endpoint
                                  queue:(dispatch_queue_t)queue ZGMTR_DEPRECATED("Please use initWithDevice:endpoindID:queue:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));

- (NSDictionary<NSString *, id> *)readAttributeIntrinsicBalanceFactorWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_DEPRECATED("Please use readAttributeIntrinsicBallastFactorWithParams on ZGMTRClusterBallastConfiguration", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (void)writeAttributeIntrinsicBalanceFactorWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs ZGMTR_DEPRECATED("Please use writeAttributeIntrinsicBallastFactorWithValue on ZGMTRClusterBallastConfiguration", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (void)writeAttributeIntrinsicBalanceFactorWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs params:(ZGMTRWriteParams * _Nullable)params ZGMTR_DEPRECATED("Please use writeAttributeIntrinsicBallastFactorWithValue on ZGMTRClusterBallastConfiguration", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
@end

@interface ZGMTRClusterIlluminanceMeasurement (Deprecated)

- (nullable instancetype)initWithDevice:(ZGMTRDevice *)device
                               endpoint:(uint16_t)endpoint
                                  queue:(dispatch_queue_t)queue ZGMTR_DEPRECATED("Please use initWithDevice:endpoindID:queue:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));

@end

@interface ZGMTRClusterTemperatureMeasurement (Deprecated)

- (nullable instancetype)initWithDevice:(ZGMTRDevice *)device
                               endpoint:(uint16_t)endpoint
                                  queue:(dispatch_queue_t)queue ZGMTR_DEPRECATED("Please use initWithDevice:endpoindID:queue:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));

@end

@interface ZGMTRClusterPressureMeasurement (Deprecated)

- (nullable instancetype)initWithDevice:(ZGMTRDevice *)device
                               endpoint:(uint16_t)endpoint
                                  queue:(dispatch_queue_t)queue ZGMTR_DEPRECATED("Please use initWithDevice:endpoindID:queue:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));

@end

@interface ZGMTRClusterFlowMeasurement (Deprecated)

- (nullable instancetype)initWithDevice:(ZGMTRDevice *)device
                               endpoint:(uint16_t)endpoint
                                  queue:(dispatch_queue_t)queue ZGMTR_DEPRECATED("Please use initWithDevice:endpoindID:queue:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));

@end

@interface ZGMTRClusterRelativeHumidityMeasurement (Deprecated)

- (nullable instancetype)initWithDevice:(ZGMTRDevice *)device
                               endpoint:(uint16_t)endpoint
                                  queue:(dispatch_queue_t)queue ZGMTR_DEPRECATED("Please use initWithDevice:endpoindID:queue:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));

@end

@interface ZGMTRClusterOccupancySensing (Deprecated)

- (nullable instancetype)initWithDevice:(ZGMTRDevice *)device
                               endpoint:(uint16_t)endpoint
                                  queue:(dispatch_queue_t)queue ZGMTR_DEPRECATED("Please use initWithDevice:endpoindID:queue:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));

- (NSDictionary<NSString *, id> *)readAttributePirOccupiedToUnoccupiedDelayWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_DEPRECATED("Please use readAttributePIROccupiedToUnoccupiedDelayWithParams on ZGMTRClusterOccupancySensing", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (void)writeAttributePirOccupiedToUnoccupiedDelayWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs ZGMTR_DEPRECATED("Please use writeAttributePIROccupiedToUnoccupiedDelayWithValue on ZGMTRClusterOccupancySensing", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (void)writeAttributePirOccupiedToUnoccupiedDelayWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs params:(ZGMTRWriteParams * _Nullable)params ZGMTR_DEPRECATED("Please use writeAttributePIROccupiedToUnoccupiedDelayWithValue on ZGMTRClusterOccupancySensing", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (NSDictionary<NSString *, id> *)readAttributePirUnoccupiedToOccupiedDelayWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_DEPRECATED("Please use readAttributePIRUnoccupiedToOccupiedDelayWithParams on ZGMTRClusterOccupancySensing", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (void)writeAttributePirUnoccupiedToOccupiedDelayWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs ZGMTR_DEPRECATED("Please use writeAttributePIRUnoccupiedToOccupiedDelayWithValue on ZGMTRClusterOccupancySensing", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (void)writeAttributePirUnoccupiedToOccupiedDelayWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs params:(ZGMTRWriteParams * _Nullable)params ZGMTR_DEPRECATED("Please use writeAttributePIRUnoccupiedToOccupiedDelayWithValue on ZGMTRClusterOccupancySensing", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (NSDictionary<NSString *, id> *)readAttributePirUnoccupiedToOccupiedThresholdWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_DEPRECATED("Please use readAttributePIRUnoccupiedToOccupiedThresholdWithParams on ZGMTRClusterOccupancySensing", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (void)writeAttributePirUnoccupiedToOccupiedThresholdWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs ZGMTR_DEPRECATED("Please use writeAttributePIRUnoccupiedToOccupiedThresholdWithValue on ZGMTRClusterOccupancySensing", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (void)writeAttributePirUnoccupiedToOccupiedThresholdWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs params:(ZGMTRWriteParams * _Nullable)params ZGMTR_DEPRECATED("Please use writeAttributePIRUnoccupiedToOccupiedThresholdWithValue on ZGMTRClusterOccupancySensing", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
@end

@interface ZGMTRClusterWakeOnLan (Deprecated)

- (nullable instancetype)initWithDevice:(ZGMTRDevice *)device
                               endpoint:(uint16_t)endpoint
                                  queue:(dispatch_queue_t)queue ZGMTR_DEPRECATED("Please use initWithDevice:endpoindID:queue:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));

@end

@interface ZGMTRClusterChannel (Deprecated)

- (nullable instancetype)initWithDevice:(ZGMTRDevice *)device
                               endpoint:(uint16_t)endpoint
                                  queue:(dispatch_queue_t)queue ZGMTR_DEPRECATED("Please use initWithDevice:endpoindID:queue:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));

- (void)changeChannelWithParams:(ZGMTRChannelClusterChangeChannelParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completionHandler:(void (^)(ZGMTRChannelClusterChangeChannelResponseParams * _Nullable data, NSError * _Nullable error))completionHandler ZGMTR_DEPRECATED("Please use changeChannelWithParams:expectedValues:expectedValueInterval:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (void)changeChannelByNumberWithParams:(ZGMTRChannelClusterChangeChannelByNumberParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completionHandler:(ZGMTRStatusCompletion)completionHandler ZGMTR_DEPRECATED("Please use changeChannelByNumberWithParams:expectedValues:expectedValueInterval:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (void)skipChannelWithParams:(ZGMTRChannelClusterSkipChannelParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completionHandler:(ZGMTRStatusCompletion)completionHandler ZGMTR_DEPRECATED("Please use skipChannelWithParams:expectedValues:expectedValueInterval:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
@end

@interface ZGMTRClusterTargetNavigator (Deprecated)

- (nullable instancetype)initWithDevice:(ZGMTRDevice *)device
                               endpoint:(uint16_t)endpoint
                                  queue:(dispatch_queue_t)queue ZGMTR_DEPRECATED("Please use initWithDevice:endpoindID:queue:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));

- (void)navigateTargetWithParams:(ZGMTRTargetNavigatorClusterNavigateTargetParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completionHandler:(void (^)(ZGMTRTargetNavigatorClusterNavigateTargetResponseParams * _Nullable data, NSError * _Nullable error))completionHandler ZGMTR_DEPRECATED("Please use navigateTargetWithParams:expectedValues:expectedValueInterval:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
@end

@interface ZGMTRClusterMediaPlayback (Deprecated)

- (nullable instancetype)initWithDevice:(ZGMTRDevice *)device
                               endpoint:(uint16_t)endpoint
                                  queue:(dispatch_queue_t)queue ZGMTR_DEPRECATED("Please use initWithDevice:endpoindID:queue:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));

- (void)playWithParams:(ZGMTRMediaPlaybackClusterPlayParams * _Nullable)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completionHandler:(void (^)(ZGMTRMediaPlaybackClusterPlaybackResponseParams * _Nullable data, NSError * _Nullable error))completionHandler ZGMTR_DEPRECATED("Please use playWithParams:expectedValues:expectedValueInterval:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (void)playWithExpectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedValues expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completionHandler:(void (^)(ZGMTRMediaPlaybackClusterPlaybackResponseParams * _Nullable data, NSError * _Nullable error))completionHandler ZGMTR_DEPRECATED("Please use playWithExpectedValues:expectedValueInterval:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (void)pauseWithParams:(ZGMTRMediaPlaybackClusterPauseParams * _Nullable)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completionHandler:(void (^)(ZGMTRMediaPlaybackClusterPlaybackResponseParams * _Nullable data, NSError * _Nullable error))completionHandler ZGMTR_DEPRECATED("Please use pauseWithParams:expectedValues:expectedValueInterval:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (void)pauseWithExpectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedValues expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completionHandler:(void (^)(ZGMTRMediaPlaybackClusterPlaybackResponseParams * _Nullable data, NSError * _Nullable error))completionHandler ZGMTR_DEPRECATED("Please use pauseWithExpectedValues:expectedValueInterval:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (void)stopPlaybackWithParams:(ZGMTRMediaPlaybackClusterStopPlaybackParams * _Nullable)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completionHandler:(void (^)(ZGMTRMediaPlaybackClusterPlaybackResponseParams * _Nullable data, NSError * _Nullable error))completionHandler ZGMTR_DEPRECATED("Please use stopWithParams:expectedValues:expectedValueInterval:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (void)stopPlaybackWithExpectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedValues expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completionHandler:(void (^)(ZGMTRMediaPlaybackClusterPlaybackResponseParams * _Nullable data, NSError * _Nullable error))completionHandler ZGMTR_DEPRECATED("Please use stopWithExpectedValues:expectedValueInterval:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (void)startOverWithParams:(ZGMTRMediaPlaybackClusterStartOverParams * _Nullable)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completionHandler:(void (^)(ZGMTRMediaPlaybackClusterPlaybackResponseParams * _Nullable data, NSError * _Nullable error))completionHandler ZGMTR_DEPRECATED("Please use startOverWithParams:expectedValues:expectedValueInterval:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (void)startOverWithExpectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedValues expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completionHandler:(void (^)(ZGMTRMediaPlaybackClusterPlaybackResponseParams * _Nullable data, NSError * _Nullable error))completionHandler ZGMTR_DEPRECATED("Please use startOverWithExpectedValues:expectedValueInterval:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (void)previousWithParams:(ZGMTRMediaPlaybackClusterPreviousParams * _Nullable)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completionHandler:(void (^)(ZGMTRMediaPlaybackClusterPlaybackResponseParams * _Nullable data, NSError * _Nullable error))completionHandler ZGMTR_DEPRECATED("Please use previousWithParams:expectedValues:expectedValueInterval:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (void)previousWithExpectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedValues expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completionHandler:(void (^)(ZGMTRMediaPlaybackClusterPlaybackResponseParams * _Nullable data, NSError * _Nullable error))completionHandler ZGMTR_DEPRECATED("Please use previousWithExpectedValues:expectedValueInterval:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (void)nextWithParams:(ZGMTRMediaPlaybackClusterNextParams * _Nullable)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completionHandler:(void (^)(ZGMTRMediaPlaybackClusterPlaybackResponseParams * _Nullable data, NSError * _Nullable error))completionHandler ZGMTR_DEPRECATED("Please use nextWithParams:expectedValues:expectedValueInterval:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (void)nextWithExpectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedValues expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completionHandler:(void (^)(ZGMTRMediaPlaybackClusterPlaybackResponseParams * _Nullable data, NSError * _Nullable error))completionHandler ZGMTR_DEPRECATED("Please use nextWithExpectedValues:expectedValueInterval:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (void)rewindWithParams:(ZGMTRMediaPlaybackClusterRewindParams * _Nullable)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completionHandler:(void (^)(ZGMTRMediaPlaybackClusterPlaybackResponseParams * _Nullable data, NSError * _Nullable error))completionHandler ZGMTR_DEPRECATED("Please use rewindWithParams:expectedValues:expectedValueInterval:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (void)rewindWithExpectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedValues expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completionHandler:(void (^)(ZGMTRMediaPlaybackClusterPlaybackResponseParams * _Nullable data, NSError * _Nullable error))completionHandler ZGMTR_DEPRECATED("Please use rewindWithExpectedValues:expectedValueInterval:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (void)fastForwardWithParams:(ZGMTRMediaPlaybackClusterFastForwardParams * _Nullable)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completionHandler:(void (^)(ZGMTRMediaPlaybackClusterPlaybackResponseParams * _Nullable data, NSError * _Nullable error))completionHandler ZGMTR_DEPRECATED("Please use fastForwardWithParams:expectedValues:expectedValueInterval:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (void)fastForwardWithExpectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedValues expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completionHandler:(void (^)(ZGMTRMediaPlaybackClusterPlaybackResponseParams * _Nullable data, NSError * _Nullable error))completionHandler ZGMTR_DEPRECATED("Please use fastForwardWithExpectedValues:expectedValueInterval:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (void)skipForwardWithParams:(ZGMTRMediaPlaybackClusterSkipForwardParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completionHandler:(void (^)(ZGMTRMediaPlaybackClusterPlaybackResponseParams * _Nullable data, NSError * _Nullable error))completionHandler ZGMTR_DEPRECATED("Please use skipForwardWithParams:expectedValues:expectedValueInterval:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (void)skipBackwardWithParams:(ZGMTRMediaPlaybackClusterSkipBackwardParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completionHandler:(void (^)(ZGMTRMediaPlaybackClusterPlaybackResponseParams * _Nullable data, NSError * _Nullable error))completionHandler ZGMTR_DEPRECATED("Please use skipBackwardWithParams:expectedValues:expectedValueInterval:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (void)seekWithParams:(ZGMTRMediaPlaybackClusterSeekParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completionHandler:(void (^)(ZGMTRMediaPlaybackClusterPlaybackResponseParams * _Nullable data, NSError * _Nullable error))completionHandler ZGMTR_DEPRECATED("Please use seekWithParams:expectedValues:expectedValueInterval:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
@end

@interface ZGMTRClusterMediaInput (Deprecated)

- (nullable instancetype)initWithDevice:(ZGMTRDevice *)device
                               endpoint:(uint16_t)endpoint
                                  queue:(dispatch_queue_t)queue ZGMTR_DEPRECATED("Please use initWithDevice:endpoindID:queue:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));

- (void)selectInputWithParams:(ZGMTRMediaInputClusterSelectInputParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completionHandler:(ZGMTRStatusCompletion)completionHandler ZGMTR_DEPRECATED("Please use selectInputWithParams:expectedValues:expectedValueInterval:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (void)showInputStatusWithParams:(ZGMTRMediaInputClusterShowInputStatusParams * _Nullable)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completionHandler:(ZGMTRStatusCompletion)completionHandler ZGMTR_DEPRECATED("Please use showInputStatusWithParams:expectedValues:expectedValueInterval:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (void)showInputStatusWithExpectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedValues expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completionHandler:(ZGMTRStatusCompletion)completionHandler ZGMTR_DEPRECATED("Please use showInputStatusWithExpectedValues:expectedValueInterval:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (void)hideInputStatusWithParams:(ZGMTRMediaInputClusterHideInputStatusParams * _Nullable)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completionHandler:(ZGMTRStatusCompletion)completionHandler ZGMTR_DEPRECATED("Please use hideInputStatusWithParams:expectedValues:expectedValueInterval:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (void)hideInputStatusWithExpectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedValues expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completionHandler:(ZGMTRStatusCompletion)completionHandler ZGMTR_DEPRECATED("Please use hideInputStatusWithExpectedValues:expectedValueInterval:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (void)renameInputWithParams:(ZGMTRMediaInputClusterRenameInputParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completionHandler:(ZGMTRStatusCompletion)completionHandler ZGMTR_DEPRECATED("Please use renameInputWithParams:expectedValues:expectedValueInterval:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
@end

@interface ZGMTRClusterLowPower (Deprecated)

- (nullable instancetype)initWithDevice:(ZGMTRDevice *)device
                               endpoint:(uint16_t)endpoint
                                  queue:(dispatch_queue_t)queue ZGMTR_DEPRECATED("Please use initWithDevice:endpoindID:queue:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));

- (void)sleepWithParams:(ZGMTRLowPowerClusterSleepParams * _Nullable)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completionHandler:(ZGMTRStatusCompletion)completionHandler ZGMTR_DEPRECATED("Please use sleepWithParams:expectedValues:expectedValueInterval:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (void)sleepWithExpectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedValues expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completionHandler:(ZGMTRStatusCompletion)completionHandler ZGMTR_DEPRECATED("Please use sleepWithExpectedValues:expectedValueInterval:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
@end

@interface ZGMTRClusterKeypadInput (Deprecated)

- (nullable instancetype)initWithDevice:(ZGMTRDevice *)device
                               endpoint:(uint16_t)endpoint
                                  queue:(dispatch_queue_t)queue ZGMTR_DEPRECATED("Please use initWithDevice:endpoindID:queue:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));

- (void)sendKeyWithParams:(ZGMTRKeypadInputClusterSendKeyParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completionHandler:(void (^)(ZGMTRKeypadInputClusterSendKeyResponseParams * _Nullable data, NSError * _Nullable error))completionHandler ZGMTR_DEPRECATED("Please use sendKeyWithParams:expectedValues:expectedValueInterval:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
@end

@interface ZGMTRClusterContentLauncher (Deprecated)

- (nullable instancetype)initWithDevice:(ZGMTRDevice *)device
                               endpoint:(uint16_t)endpoint
                                  queue:(dispatch_queue_t)queue ZGMTR_DEPRECATED("Please use initWithDevice:endpoindID:queue:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));

- (void)launchContentWithParams:(ZGMTRContentLauncherClusterLaunchContentParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completionHandler:(void (^)(ZGMTRContentLauncherClusterLaunchResponseParams * _Nullable data, NSError * _Nullable error))completionHandler ZGMTR_DEPRECATED("Please use launchContentWithParams:expectedValues:expectedValueInterval:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (void)launchURLWithParams:(ZGMTRContentLauncherClusterLaunchURLParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completionHandler:(void (^)(ZGMTRContentLauncherClusterLaunchResponseParams * _Nullable data, NSError * _Nullable error))completionHandler ZGMTR_DEPRECATED("Please use launchURLWithParams:expectedValues:expectedValueInterval:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
@end

@interface ZGMTRClusterAudioOutput (Deprecated)

- (nullable instancetype)initWithDevice:(ZGMTRDevice *)device
                               endpoint:(uint16_t)endpoint
                                  queue:(dispatch_queue_t)queue ZGMTR_DEPRECATED("Please use initWithDevice:endpoindID:queue:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));

- (void)selectOutputWithParams:(ZGMTRAudioOutputClusterSelectOutputParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completionHandler:(ZGMTRStatusCompletion)completionHandler ZGMTR_DEPRECATED("Please use selectOutputWithParams:expectedValues:expectedValueInterval:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (void)renameOutputWithParams:(ZGMTRAudioOutputClusterRenameOutputParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completionHandler:(ZGMTRStatusCompletion)completionHandler ZGMTR_DEPRECATED("Please use renameOutputWithParams:expectedValues:expectedValueInterval:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
@end

@interface ZGMTRClusterApplicationLauncher (Deprecated)

- (nullable instancetype)initWithDevice:(ZGMTRDevice *)device
                               endpoint:(uint16_t)endpoint
                                  queue:(dispatch_queue_t)queue ZGMTR_DEPRECATED("Please use initWithDevice:endpoindID:queue:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));

- (void)launchAppWithParams:(ZGMTRApplicationLauncherClusterLaunchAppParams * _Nullable)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completionHandler:(void (^)(ZGMTRApplicationLauncherClusterLauncherResponseParams * _Nullable data, NSError * _Nullable error))completionHandler ZGMTR_DEPRECATED("Please use launchAppWithParams:expectedValues:expectedValueInterval:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (void)stopAppWithParams:(ZGMTRApplicationLauncherClusterStopAppParams * _Nullable)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completionHandler:(void (^)(ZGMTRApplicationLauncherClusterLauncherResponseParams * _Nullable data, NSError * _Nullable error))completionHandler ZGMTR_DEPRECATED("Please use stopAppWithParams:expectedValues:expectedValueInterval:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (void)hideAppWithParams:(ZGMTRApplicationLauncherClusterHideAppParams * _Nullable)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completionHandler:(void (^)(ZGMTRApplicationLauncherClusterLauncherResponseParams * _Nullable data, NSError * _Nullable error))completionHandler ZGMTR_DEPRECATED("Please use hideAppWithParams:expectedValues:expectedValueInterval:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
@end

@interface ZGMTRClusterApplicationBasic (Deprecated)

- (nullable instancetype)initWithDevice:(ZGMTRDevice *)device
                               endpoint:(uint16_t)endpoint
                                  queue:(dispatch_queue_t)queue ZGMTR_DEPRECATED("Please use initWithDevice:endpoindID:queue:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));

@end

@interface ZGMTRClusterAccountLogin (Deprecated)

- (nullable instancetype)initWithDevice:(ZGMTRDevice *)device
                               endpoint:(uint16_t)endpoint
                                  queue:(dispatch_queue_t)queue ZGMTR_DEPRECATED("Please use initWithDevice:endpoindID:queue:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));

- (void)getSetupPINWithParams:(ZGMTRAccountLoginClusterGetSetupPINParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completionHandler:(void (^)(ZGMTRAccountLoginClusterGetSetupPINResponseParams * _Nullable data, NSError * _Nullable error))completionHandler ZGMTR_DEPRECATED("Please use getSetupPINWithParams:expectedValues:expectedValueInterval:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (void)loginWithParams:(ZGMTRAccountLoginClusterLoginParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completionHandler:(ZGMTRStatusCompletion)completionHandler ZGMTR_DEPRECATED("Please use loginWithParams:expectedValues:expectedValueInterval:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (void)logoutWithParams:(ZGMTRAccountLoginClusterLogoutParams * _Nullable)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completionHandler:(ZGMTRStatusCompletion)completionHandler ZGMTR_DEPRECATED("Please use logoutWithParams:expectedValues:expectedValueInterval:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (void)logoutWithExpectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedValues expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completionHandler:(ZGMTRStatusCompletion)completionHandler ZGMTR_DEPRECATED("Please use logoutWithExpectedValues:expectedValueInterval:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
@end

@interface ZGMTRClusterTestCluster (Deprecated)

- (nullable instancetype)initWithDevice:(ZGMTRDevice *)device
                               endpoint:(uint16_t)endpoint
                                  queue:(dispatch_queue_t)queue ZGMTR_DEPRECATED("Please use initWithDevice:endpoindID:queue:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));

- (void)testWithParams:(ZGMTRTestClusterClusterTestParams * _Nullable)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completionHandler:(ZGMTRStatusCompletion)completionHandler ZGMTR_DEPRECATED("Please use testWithParams:expectedValues:expectedValueInterval:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (void)testWithExpectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedValues expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completionHandler:(ZGMTRStatusCompletion)completionHandler ZGMTR_DEPRECATED("Please use testWithExpectedValues:expectedValueInterval:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (void)testNotHandledWithParams:(ZGMTRTestClusterClusterTestNotHandledParams * _Nullable)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completionHandler:(ZGMTRStatusCompletion)completionHandler ZGMTR_DEPRECATED("Please use testNotHandledWithParams:expectedValues:expectedValueInterval:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (void)testNotHandledWithExpectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedValues expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completionHandler:(ZGMTRStatusCompletion)completionHandler ZGMTR_DEPRECATED("Please use testNotHandledWithExpectedValues:expectedValueInterval:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (void)testSpecificWithParams:(ZGMTRTestClusterClusterTestSpecificParams * _Nullable)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completionHandler:(void (^)(ZGMTRTestClusterClusterTestSpecificResponseParams * _Nullable data, NSError * _Nullable error))completionHandler ZGMTR_DEPRECATED("Please use testSpecificWithParams:expectedValues:expectedValueInterval:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (void)testSpecificWithExpectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedValues expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completionHandler:(void (^)(ZGMTRTestClusterClusterTestSpecificResponseParams * _Nullable data, NSError * _Nullable error))completionHandler ZGMTR_DEPRECATED("Please use testSpecificWithExpectedValues:expectedValueInterval:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (void)testUnknownCommandWithParams:(ZGMTRTestClusterClusterTestUnknownCommandParams * _Nullable)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completionHandler:(ZGMTRStatusCompletion)completionHandler ZGMTR_DEPRECATED("Please use testUnknownCommandWithParams:expectedValues:expectedValueInterval:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (void)testUnknownCommandWithExpectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedValues expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completionHandler:(ZGMTRStatusCompletion)completionHandler ZGMTR_DEPRECATED("Please use testUnknownCommandWithExpectedValues:expectedValueInterval:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (void)testAddArgumentsWithParams:(ZGMTRTestClusterClusterTestAddArgumentsParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completionHandler:(void (^)(ZGMTRTestClusterClusterTestAddArgumentsResponseParams * _Nullable data, NSError * _Nullable error))completionHandler ZGMTR_DEPRECATED("Please use testAddArgumentsWithParams:expectedValues:expectedValueInterval:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (void)testSimpleArgumentRequestWithParams:(ZGMTRTestClusterClusterTestSimpleArgumentRequestParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completionHandler:(void (^)(ZGMTRTestClusterClusterTestSimpleArgumentResponseParams * _Nullable data, NSError * _Nullable error))completionHandler ZGMTR_DEPRECATED("Please use testSimpleArgumentRequestWithParams:expectedValues:expectedValueInterval:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (void)testStructArrayArgumentRequestWithParams:(ZGMTRTestClusterClusterTestStructArrayArgumentRequestParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completionHandler:(void (^)(ZGMTRTestClusterClusterTestStructArrayArgumentResponseParams * _Nullable data, NSError * _Nullable error))completionHandler ZGMTR_DEPRECATED("Please use testStructArrayArgumentRequestWithParams:expectedValues:expectedValueInterval:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (void)testStructArgumentRequestWithParams:(ZGMTRTestClusterClusterTestStructArgumentRequestParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completionHandler:(void (^)(ZGMTRTestClusterClusterBooleanResponseParams * _Nullable data, NSError * _Nullable error))completionHandler ZGMTR_DEPRECATED("Please use testStructArgumentRequestWithParams:expectedValues:expectedValueInterval:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (void)testNestedStructArgumentRequestWithParams:(ZGMTRTestClusterClusterTestNestedStructArgumentRequestParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completionHandler:(void (^)(ZGMTRTestClusterClusterBooleanResponseParams * _Nullable data, NSError * _Nullable error))completionHandler ZGMTR_DEPRECATED("Please use testNestedStructArgumentRequestWithParams:expectedValues:expectedValueInterval:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (void)testListStructArgumentRequestWithParams:(ZGMTRTestClusterClusterTestListStructArgumentRequestParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completionHandler:(void (^)(ZGMTRTestClusterClusterBooleanResponseParams * _Nullable data, NSError * _Nullable error))completionHandler ZGMTR_DEPRECATED("Please use testListStructArgumentRequestWithParams:expectedValues:expectedValueInterval:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (void)testListInt8UArgumentRequestWithParams:(ZGMTRTestClusterClusterTestListInt8UArgumentRequestParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completionHandler:(void (^)(ZGMTRTestClusterClusterBooleanResponseParams * _Nullable data, NSError * _Nullable error))completionHandler ZGMTR_DEPRECATED("Please use testListInt8UArgumentRequestWithParams:expectedValues:expectedValueInterval:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (void)testNestedStructListArgumentRequestWithParams:(ZGMTRTestClusterClusterTestNestedStructListArgumentRequestParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completionHandler:(void (^)(ZGMTRTestClusterClusterBooleanResponseParams * _Nullable data, NSError * _Nullable error))completionHandler ZGMTR_DEPRECATED("Please use testNestedStructListArgumentRequestWithParams:expectedValues:expectedValueInterval:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (void)testListNestedStructListArgumentRequestWithParams:(ZGMTRTestClusterClusterTestListNestedStructListArgumentRequestParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completionHandler:(void (^)(ZGMTRTestClusterClusterBooleanResponseParams * _Nullable data, NSError * _Nullable error))completionHandler ZGMTR_DEPRECATED("Please use testListNestedStructListArgumentRequestWithParams:expectedValues:expectedValueInterval:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (void)testListInt8UReverseRequestWithParams:(ZGMTRTestClusterClusterTestListInt8UReverseRequestParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completionHandler:(void (^)(ZGMTRTestClusterClusterTestListInt8UReverseResponseParams * _Nullable data, NSError * _Nullable error))completionHandler ZGMTR_DEPRECATED("Please use testListInt8UReverseRequestWithParams:expectedValues:expectedValueInterval:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (void)testEnumsRequestWithParams:(ZGMTRTestClusterClusterTestEnumsRequestParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completionHandler:(void (^)(ZGMTRTestClusterClusterTestEnumsResponseParams * _Nullable data, NSError * _Nullable error))completionHandler ZGMTR_DEPRECATED("Please use testEnumsRequestWithParams:expectedValues:expectedValueInterval:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (void)testNullableOptionalRequestWithParams:(ZGMTRTestClusterClusterTestNullableOptionalRequestParams * _Nullable)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completionHandler:(void (^)(ZGMTRTestClusterClusterTestNullableOptionalResponseParams * _Nullable data, NSError * _Nullable error))completionHandler ZGMTR_DEPRECATED("Please use testNullableOptionalRequestWithParams:expectedValues:expectedValueInterval:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (void)testNullableOptionalRequestWithExpectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedValues expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completionHandler:(void (^)(ZGMTRTestClusterClusterTestNullableOptionalResponseParams * _Nullable data, NSError * _Nullable error))completionHandler ZGMTR_DEPRECATED("Please use testNullableOptionalRequestWithExpectedValues:expectedValueInterval:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (void)testComplexNullableOptionalRequestWithParams:(ZGMTRTestClusterClusterTestComplexNullableOptionalRequestParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completionHandler:(void (^)(ZGMTRTestClusterClusterTestComplexNullableOptionalResponseParams * _Nullable data, NSError * _Nullable error))completionHandler ZGMTR_DEPRECATED("Please use testComplexNullableOptionalRequestWithParams:expectedValues:expectedValueInterval:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (void)simpleStructEchoRequestWithParams:(ZGMTRTestClusterClusterSimpleStructEchoRequestParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completionHandler:(void (^)(ZGMTRTestClusterClusterSimpleStructResponseParams * _Nullable data, NSError * _Nullable error))completionHandler ZGMTR_DEPRECATED("Please use simpleStructEchoRequestWithParams:expectedValues:expectedValueInterval:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (void)timedInvokeRequestWithParams:(ZGMTRTestClusterClusterTimedInvokeRequestParams * _Nullable)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completionHandler:(ZGMTRStatusCompletion)completionHandler ZGMTR_DEPRECATED("Please use timedInvokeRequestWithParams:expectedValues:expectedValueInterval:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (void)timedInvokeRequestWithExpectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedValues expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completionHandler:(ZGMTRStatusCompletion)completionHandler ZGMTR_DEPRECATED("Please use timedInvokeRequestWithExpectedValues:expectedValueInterval:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (void)testSimpleOptionalArgumentRequestWithParams:(ZGMTRTestClusterClusterTestSimpleOptionalArgumentRequestParams * _Nullable)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completionHandler:(ZGMTRStatusCompletion)completionHandler ZGMTR_DEPRECATED("Please use testSimpleOptionalArgumentRequestWithParams:expectedValues:expectedValueInterval:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (void)testSimpleOptionalArgumentRequestWithExpectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedValues expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completionHandler:(ZGMTRStatusCompletion)completionHandler ZGMTR_DEPRECATED("Please use testSimpleOptionalArgumentRequestWithExpectedValues:expectedValueInterval:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (void)testEmitTestEventRequestWithParams:(ZGMTRTestClusterClusterTestEmitTestEventRequestParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completionHandler:(void (^)(ZGMTRTestClusterClusterTestEmitTestEventResponseParams * _Nullable data, NSError * _Nullable error))completionHandler ZGMTR_DEPRECATED("Please use testEmitTestEventRequestWithParams:expectedValues:expectedValueInterval:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (void)testEmitTestFabricScopedEventRequestWithParams:(ZGMTRTestClusterClusterTestEmitTestFabricScopedEventRequestParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completionHandler:(void (^)(ZGMTRTestClusterClusterTestEmitTestFabricScopedEventResponseParams * _Nullable data, NSError * _Nullable error))completionHandler ZGMTR_DEPRECATED("Please use testEmitTestFabricScopedEventRequestWithParams:expectedValues:expectedValueInterval:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
@end

NS_ASSUME_NONNULL_END
