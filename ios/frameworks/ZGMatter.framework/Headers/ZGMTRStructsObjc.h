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

#import <ZGMatter/ZGMTRDefines.h>

NS_ASSUME_NONNULL_BEGIN

ZGMTR_PROVISIONALLY_AVAILABLE
@interface ZGMTRDataTypeCurrencyStruct : NSObject <NSCopying>
@property (nonatomic, copy) NSNumber * _Nonnull currency ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSNumber * _Nonnull decimalPoints ZGMTR_PROVISIONALLY_AVAILABLE;
@end

ZGMTR_PROVISIONALLY_AVAILABLE
@interface ZGMTRDataTypePriceStruct : NSObject <NSCopying>
@property (nonatomic, copy) NSNumber * _Nonnull amount ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) ZGMTRDataTypeCurrencyStruct * _Nonnull currency ZGMTR_PROVISIONALLY_AVAILABLE;
@end

ZGMTR_PROVISIONALLY_AVAILABLE
@interface ZGMTRDataTypeMeasurementAccuracyRangeStruct : NSObject <NSCopying>
@property (nonatomic, copy) NSNumber * _Nonnull rangeMin ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSNumber * _Nonnull rangeMax ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSNumber * _Nullable percentMax ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSNumber * _Nullable percentMin ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSNumber * _Nullable percentTypical ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSNumber * _Nullable fixedMax ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSNumber * _Nullable fixedMin ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSNumber * _Nullable fixedTypical ZGMTR_PROVISIONALLY_AVAILABLE;
@end

ZGMTR_PROVISIONALLY_AVAILABLE
@interface ZGMTRDataTypeMeasurementAccuracyStruct : NSObject <NSCopying>
@property (nonatomic, copy) NSNumber * _Nonnull measurementType ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSNumber * _Nonnull measured ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSNumber * _Nonnull minMeasuredValue ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSNumber * _Nonnull maxMeasuredValue ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSArray * _Nonnull accuracyRanges ZGMTR_PROVISIONALLY_AVAILABLE;
@end

ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4))
@interface ZGMTRDataTypeAtomicAttributeStatusStruct : NSObject <NSCopying>
@property (nonatomic, copy) NSNumber * _Nonnull attributeID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));
@property (nonatomic, copy) NSNumber * _Nonnull statusCode ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));
@end

ZGMTR_PROVISIONALLY_AVAILABLE
@interface ZGMTRDataTypeICECandidateStruct : NSObject <NSCopying>
@property (nonatomic, copy) NSString * _Nonnull candidate ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSString * _Nullable sdpMid ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSNumber * _Nullable sdpmLineIndex ZGMTR_PROVISIONALLY_AVAILABLE;
@end

ZGMTR_PROVISIONALLY_AVAILABLE
@interface ZGMTRDataTypeICEServerStruct : NSObject <NSCopying>
@property (nonatomic, copy) NSArray * _Nonnull urls ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSString * _Nullable username ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSString * _Nullable credential ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSNumber * _Nullable caid ZGMTR_PROVISIONALLY_AVAILABLE;
@end

ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4))
@interface ZGMTRDataTypeLocationDescriptorStruct : NSObject <NSCopying>
@property (nonatomic, copy) NSString * _Nonnull locationName ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));
@property (nonatomic, copy) NSNumber * _Nullable floorNumber ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));
@property (nonatomic, copy) NSNumber * _Nullable areaType ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));
@end

ZGMTR_PROVISIONALLY_AVAILABLE
@interface ZGMTRDataTypePowerThresholdStruct : NSObject <NSCopying>
@property (nonatomic, copy) NSNumber * _Nullable powerThreshold ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSNumber * _Nullable apparentPowerThreshold ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSNumber * _Nullable powerThresholdSource ZGMTR_PROVISIONALLY_AVAILABLE;
@end

ZGMTR_PROVISIONALLY_AVAILABLE
@interface ZGMTRDataTypeSemanticTagStruct : NSObject <NSCopying>
@property (nonatomic, copy) NSNumber * _Nullable mfgCode ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSNumber * _Nonnull namespaceID ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSNumber * _Nonnull tag ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSString * _Nullable label ZGMTR_PROVISIONALLY_AVAILABLE;
@end

ZGMTR_PROVISIONALLY_AVAILABLE
@interface ZGMTRDataTypeTestGlobalStruct : NSObject <NSCopying>
@property (nonatomic, copy) NSString * _Nonnull name ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSNumber * _Nullable myBitmap ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSNumber * _Nullable myEnum ZGMTR_PROVISIONALLY_AVAILABLE;
@end

ZGMTR_PROVISIONALLY_AVAILABLE
@interface ZGMTRDataTypeViewportStruct : NSObject <NSCopying>
@property (nonatomic, copy) NSNumber * _Nonnull x1 ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSNumber * _Nonnull y1 ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSNumber * _Nonnull x2 ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSNumber * _Nonnull y2 ZGMTR_PROVISIONALLY_AVAILABLE;
@end

ZGMTR_PROVISIONALLY_AVAILABLE
@interface ZGMTRDataTypeWebRTCSessionStruct : NSObject <NSCopying>
@property (nonatomic, copy) NSNumber * _Nonnull id ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSNumber * _Nonnull peerNodeID ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSNumber * _Nonnull peerEndpointID ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSNumber * _Nonnull streamUsage ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSNumber * _Nullable videoStreamID ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSNumber * _Nullable audioStreamID ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSNumber * _Nonnull metadataEnabled ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSArray * _Nullable videoStreams ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSArray * _Nullable audioStreams ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSNumber * _Nonnull fabricIndex ZGMTR_PROVISIONALLY_AVAILABLE;
@end

ZGMTR_AVAILABLE(ios(16.2), macos(13.1), watchos(9.2), tvos(16.2))
@interface ZGMTRDescriptorClusterDeviceTypeStruct : NSObject <NSCopying>
@property (nonatomic, copy) NSNumber * _Nonnull deviceType ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
@property (nonatomic, copy) NSNumber * _Nonnull type ZGMTR_DEPRECATED("Please use deviceType", ios(16.2, 16.4), macos(13.1, 13.3), watchos(9.2, 9.4), tvos(16.2, 16.4));
@property (nonatomic, copy) NSNumber * _Nonnull revision ZGMTR_AVAILABLE(ios(16.2), macos(13.1), watchos(9.2), tvos(16.2));
@end

ZGMTR_DEPRECATED("Please use ZGMTRDescriptorClusterDeviceTypeStruct", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
@interface ZGMTRDescriptorClusterDeviceType : ZGMTRDescriptorClusterDeviceTypeStruct
@property (nonatomic, copy) NSNumber * _Nonnull revision ZGMTR_DEPRECATED("Please use ZGMTRDescriptorClusterDeviceTypeStruct", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
@end

ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1))
@interface ZGMTRBindingClusterTargetStruct : NSObject <NSCopying>
@property (nonatomic, copy) NSNumber * _Nullable node ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));
@property (nonatomic, copy) NSNumber * _Nullable group ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));
@property (nonatomic, copy) NSNumber * _Nullable endpoint ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));
@property (nonatomic, copy) NSNumber * _Nullable cluster ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));
@property (nonatomic, copy) NSNumber * _Nonnull fabricIndex ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));
@end

ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4))
@interface ZGMTRAccessControlClusterAccessRestrictionStruct : NSObject <NSCopying>
@property (nonatomic, copy) NSNumber * _Nonnull type ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));
@property (nonatomic, copy) NSNumber * _Nullable id ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));
@end

ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4))
@interface ZGMTRAccessControlClusterCommissioningAccessRestrictionEntryStruct : NSObject <NSCopying>
@property (nonatomic, copy) NSNumber * _Nonnull endpoint ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));
@property (nonatomic, copy) NSNumber * _Nonnull cluster ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));
@property (nonatomic, copy) NSArray * _Nonnull restrictions ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));
@end

ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4))
@interface ZGMTRAccessControlClusterAccessRestrictionEntryStruct : NSObject <NSCopying>
@property (nonatomic, copy) NSNumber * _Nonnull endpoint ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));
@property (nonatomic, copy) NSNumber * _Nonnull cluster ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));
@property (nonatomic, copy) NSArray * _Nonnull restrictions ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));
@property (nonatomic, copy) NSNumber * _Nonnull fabricIndex ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));
@end

ZGMTR_AVAILABLE(ios(17.0), macos(14.0), watchos(10.0), tvos(17.0))
@interface ZGMTRAccessControlClusterAccessControlTargetStruct : NSObject <NSCopying>
@property (nonatomic, copy) NSNumber * _Nullable cluster ZGMTR_AVAILABLE(ios(17.0), macos(14.0), watchos(10.0), tvos(17.0));
@property (nonatomic, copy) NSNumber * _Nullable endpoint ZGMTR_AVAILABLE(ios(17.0), macos(14.0), watchos(10.0), tvos(17.0));
@property (nonatomic, copy) NSNumber * _Nullable deviceType ZGMTR_AVAILABLE(ios(17.0), macos(14.0), watchos(10.0), tvos(17.0));
@end

ZGMTR_DEPRECATED("Please use ZGMTRAccessControlClusterAccessControlTargetStruct", ios(16.1, 17.0), macos(13.0, 14.0), watchos(9.1, 10.0), tvos(16.1, 17.0))
@interface ZGMTRAccessControlClusterTarget : ZGMTRAccessControlClusterAccessControlTargetStruct
@property (nonatomic, copy) NSNumber * _Nullable cluster ZGMTR_DEPRECATED("Please use ZGMTRAccessControlClusterAccessControlTargetStruct", ios(16.1, 17.0), macos(13.0, 14.0), watchos(9.1, 10.0), tvos(16.1, 17.0));
@property (nonatomic, copy) NSNumber * _Nullable endpoint ZGMTR_DEPRECATED("Please use ZGMTRAccessControlClusterAccessControlTargetStruct", ios(16.1, 17.0), macos(13.0, 14.0), watchos(9.1, 10.0), tvos(16.1, 17.0));
@property (nonatomic, copy) NSNumber * _Nullable deviceType ZGMTR_DEPRECATED("Please use ZGMTRAccessControlClusterAccessControlTargetStruct", ios(16.1, 17.0), macos(13.0, 14.0), watchos(9.1, 10.0), tvos(16.1, 17.0));
@end

ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4))
@interface ZGMTRAccessControlClusterAccessControlEntryStruct : NSObject <NSCopying>
@property (nonatomic, copy) NSNumber * _Nonnull privilege ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
@property (nonatomic, copy) NSNumber * _Nonnull authMode ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
@property (nonatomic, copy) NSArray * _Nullable subjects ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
@property (nonatomic, copy) NSArray * _Nullable targets ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
@property (nonatomic, copy) NSNumber * _Nullable auxiliaryType ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSNumber * _Nonnull fabricIndex ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
@end

ZGMTR_DEPRECATED("Please use ZGMTRAccessControlClusterAccessControlEntryStruct", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
@interface ZGMTRAccessControlClusterAccessControlEntry : ZGMTRAccessControlClusterAccessControlEntryStruct
@property (nonatomic, copy) NSNumber * _Nonnull privilege ZGMTR_DEPRECATED("Please use ZGMTRAccessControlClusterAccessControlEntryStruct", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
@property (nonatomic, copy) NSNumber * _Nonnull authMode ZGMTR_DEPRECATED("Please use ZGMTRAccessControlClusterAccessControlEntryStruct", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
@property (nonatomic, copy) NSArray * _Nullable subjects ZGMTR_DEPRECATED("Please use ZGMTRAccessControlClusterAccessControlEntryStruct", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
@property (nonatomic, copy) NSArray * _Nullable targets ZGMTR_DEPRECATED("Please use ZGMTRAccessControlClusterAccessControlEntryStruct", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
@property (nonatomic, copy) NSNumber * _Nonnull fabricIndex ZGMTR_DEPRECATED("Please use ZGMTRAccessControlClusterAccessControlEntryStruct", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
@end

ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4))
@interface ZGMTRAccessControlClusterAccessControlExtensionStruct : NSObject <NSCopying>
@property (nonatomic, copy) NSData * _Nonnull data ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
@property (nonatomic, copy) NSNumber * _Nonnull fabricIndex ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
@end

ZGMTR_DEPRECATED("Please use ZGMTRAccessControlClusterAccessControlExtensionStruct", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
@interface ZGMTRAccessControlClusterExtensionEntry : ZGMTRAccessControlClusterAccessControlExtensionStruct
@property (nonatomic, copy) NSData * _Nonnull data ZGMTR_DEPRECATED("Please use ZGMTRAccessControlClusterAccessControlExtensionStruct", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
@property (nonatomic, copy) NSNumber * _Nonnull fabricIndex ZGMTR_DEPRECATED("Please use ZGMTRAccessControlClusterAccessControlExtensionStruct", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
@end

ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1))
@interface ZGMTRAccessControlClusterAccessControlEntryChangedEvent : NSObject <NSCopying>
@property (nonatomic, copy) NSNumber * _Nullable adminNodeID ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));
@property (nonatomic, copy) NSNumber * _Nullable adminPasscodeID ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));
@property (nonatomic, copy) NSNumber * _Nonnull changeType ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));
@property (nonatomic, copy) ZGMTRAccessControlClusterAccessControlEntryStruct * _Nullable latestValue ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));
@property (nonatomic, copy) NSNumber * _Nonnull fabricIndex ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));
@end

ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1))
@interface ZGMTRAccessControlClusterAccessControlExtensionChangedEvent : NSObject <NSCopying>
@property (nonatomic, copy) NSNumber * _Nullable adminNodeID ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));
@property (nonatomic, copy) NSNumber * _Nullable adminPasscodeID ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));
@property (nonatomic, copy) NSNumber * _Nonnull changeType ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));
@property (nonatomic, copy) ZGMTRAccessControlClusterAccessControlExtensionStruct * _Nullable latestValue ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));
@property (nonatomic, copy) NSNumber * _Nonnull fabricIndex ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));
@end

ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4))
@interface ZGMTRAccessControlClusterFabricRestrictionReviewUpdateEvent : NSObject <NSCopying>
@property (nonatomic, copy) NSNumber * _Nonnull token ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));
@property (nonatomic, copy) NSString * _Nullable instruction ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));
@property (nonatomic, copy) NSString * _Nullable arlRequestFlowUrl ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSNumber * _Nonnull fabricIndex ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));
@end

ZGMTR_PROVISIONALLY_AVAILABLE
@interface ZGMTRAccessControlClusterAuxiliaryAccessUpdatedEvent : NSObject <NSCopying>
@property (nonatomic, copy) NSNumber * _Nullable adminNodeID ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSNumber * _Nonnull fabricIndex ZGMTR_PROVISIONALLY_AVAILABLE;
@end

ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1))
@interface ZGMTRActionsClusterActionStruct : NSObject <NSCopying>
@property (nonatomic, copy) NSNumber * _Nonnull actionID ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));
@property (nonatomic, copy) NSString * _Nonnull name ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));
@property (nonatomic, copy) NSNumber * _Nonnull type ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));
@property (nonatomic, copy) NSNumber * _Nonnull endpointListID ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));
@property (nonatomic, copy) NSNumber * _Nonnull supportedCommands ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));
@property (nonatomic, copy) NSNumber * _Nonnull state ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));
@end

ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1))
@interface ZGMTRActionsClusterEndpointListStruct : NSObject <NSCopying>
@property (nonatomic, copy) NSNumber * _Nonnull endpointListID ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));
@property (nonatomic, copy) NSString * _Nonnull name ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));
@property (nonatomic, copy) NSNumber * _Nonnull type ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));
@property (nonatomic, copy) NSArray * _Nonnull endpoints ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));
@end

ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1))
@interface ZGMTRActionsClusterStateChangedEvent : NSObject <NSCopying>
@property (nonatomic, copy) NSNumber * _Nonnull actionID ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));
@property (nonatomic, copy) NSNumber * _Nonnull invokeID ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));
@property (nonatomic, copy, getter=getNewState) NSNumber * _Nonnull newState ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));
@end

ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1))
@interface ZGMTRActionsClusterActionFailedEvent : NSObject <NSCopying>
@property (nonatomic, copy) NSNumber * _Nonnull actionID ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));
@property (nonatomic, copy) NSNumber * _Nonnull invokeID ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));
@property (nonatomic, copy, getter=getNewState) NSNumber * _Nonnull newState ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));
@property (nonatomic, copy) NSNumber * _Nonnull error ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));
@end

ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4))
@interface ZGMTRBasicInformationClusterCapabilityMinimaStruct : NSObject <NSCopying>
@property (nonatomic, copy) NSNumber * _Nonnull caseSessionsPerFabric ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
@property (nonatomic, copy) NSNumber * _Nonnull subscriptionsPerFabric ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
@property (nonatomic, copy) NSNumber * _Nullable simultaneousInvocationsSupported ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSNumber * _Nullable simultaneousWritesSupported ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSNumber * _Nullable readPathsSupported ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSNumber * _Nullable subscribePathsSupported ZGMTR_PROVISIONALLY_AVAILABLE;
@end

ZGMTR_DEPRECATED("Please use ZGMTRBasicInformationClusterCapabilityMinimaStruct", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
@interface ZGMTRBasicClusterCapabilityMinimaStruct : ZGMTRBasicInformationClusterCapabilityMinimaStruct
@property (nonatomic, copy) NSNumber * _Nonnull caseSessionsPerFabric ZGMTR_DEPRECATED("Please use ZGMTRBasicInformationClusterCapabilityMinimaStruct", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
@property (nonatomic, copy) NSNumber * _Nonnull subscriptionsPerFabric ZGMTR_DEPRECATED("Please use ZGMTRBasicInformationClusterCapabilityMinimaStruct", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
@end

ZGMTR_AVAILABLE(ios(17.0), macos(14.0), watchos(10.0), tvos(17.0))
@interface ZGMTRBasicInformationClusterProductAppearanceStruct : NSObject <NSCopying>
@property (nonatomic, copy) NSNumber * _Nonnull finish ZGMTR_AVAILABLE(ios(17.0), macos(14.0), watchos(10.0), tvos(17.0));
@property (nonatomic, copy) NSNumber * _Nullable primaryColor ZGMTR_AVAILABLE(ios(17.0), macos(14.0), watchos(10.0), tvos(17.0));
@end

ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4))
@interface ZGMTRBasicInformationClusterStartUpEvent : NSObject <NSCopying>
@property (nonatomic, copy) NSNumber * _Nonnull softwareVersion ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
@end

ZGMTR_DEPRECATED("Please use ZGMTRBasicInformationClusterStartUpEvent", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
@interface ZGMTRBasicClusterStartUpEvent : ZGMTRBasicInformationClusterStartUpEvent
@property (nonatomic, copy) NSNumber * _Nonnull softwareVersion ZGMTR_DEPRECATED("Please use ZGMTRBasicInformationClusterStartUpEvent", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
@end

ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4))
@interface ZGMTRBasicInformationClusterShutDownEvent : NSObject <NSCopying>
@end

ZGMTR_DEPRECATED("Please use ZGMTRBasicInformationClusterShutDownEvent", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
@interface ZGMTRBasicClusterShutDownEvent : ZGMTRBasicInformationClusterShutDownEvent
@end

ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4))
@interface ZGMTRBasicInformationClusterLeaveEvent : NSObject <NSCopying>
@property (nonatomic, copy) NSNumber * _Nonnull fabricIndex ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
@end

ZGMTR_DEPRECATED("Please use ZGMTRBasicInformationClusterLeaveEvent", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
@interface ZGMTRBasicClusterLeaveEvent : ZGMTRBasicInformationClusterLeaveEvent
@property (nonatomic, copy) NSNumber * _Nonnull fabricIndex ZGMTR_DEPRECATED("Please use ZGMTRBasicInformationClusterLeaveEvent", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
@end

ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4))
@interface ZGMTRBasicInformationClusterReachableChangedEvent : NSObject <NSCopying>
@property (nonatomic, copy) NSNumber * _Nonnull reachableNewValue ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
@end

ZGMTR_DEPRECATED("Please use ZGMTRBasicInformationClusterReachableChangedEvent", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
@interface ZGMTRBasicClusterReachableChangedEvent : ZGMTRBasicInformationClusterReachableChangedEvent
@property (nonatomic, copy) NSNumber * _Nonnull reachableNewValue ZGMTR_DEPRECATED("Please use ZGMTRBasicInformationClusterReachableChangedEvent", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
@end

ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4))
@interface ZGMTROTASoftwareUpdateRequestorClusterProviderLocation : NSObject <NSCopying>
@property (nonatomic, copy) NSNumber * _Nonnull providerNodeID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
@property (nonatomic, copy) NSNumber * _Nonnull endpoint ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
@property (nonatomic, copy) NSNumber * _Nonnull fabricIndex ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
@end

ZGMTR_DEPRECATED("Please use ZGMTROTASoftwareUpdateRequestorClusterProviderLocation", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
@interface ZGMTROtaSoftwareUpdateRequestorClusterProviderLocation : ZGMTROTASoftwareUpdateRequestorClusterProviderLocation
@property (nonatomic, copy) NSNumber * _Nonnull providerNodeID ZGMTR_DEPRECATED("Please use ZGMTROTASoftwareUpdateRequestorClusterProviderLocation", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
@property (nonatomic, copy) NSNumber * _Nonnull endpoint ZGMTR_DEPRECATED("Please use ZGMTROTASoftwareUpdateRequestorClusterProviderLocation", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
@property (nonatomic, copy) NSNumber * _Nonnull fabricIndex ZGMTR_DEPRECATED("Please use ZGMTROTASoftwareUpdateRequestorClusterProviderLocation", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
@end

ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4))
@interface ZGMTROTASoftwareUpdateRequestorClusterStateTransitionEvent : NSObject <NSCopying>
@property (nonatomic, copy) NSNumber * _Nonnull previousState ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
@property (nonatomic, copy, getter=getNewState) NSNumber * _Nonnull newState ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
@property (nonatomic, copy) NSNumber * _Nonnull reason ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
@property (nonatomic, copy) NSNumber * _Nullable targetSoftwareVersion ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
@end

ZGMTR_DEPRECATED("Please use ZGMTROTASoftwareUpdateRequestorClusterStateTransitionEvent", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
@interface ZGMTROtaSoftwareUpdateRequestorClusterStateTransitionEvent : ZGMTROTASoftwareUpdateRequestorClusterStateTransitionEvent
@property (nonatomic, copy) NSNumber * _Nonnull previousState ZGMTR_DEPRECATED("Please use ZGMTROTASoftwareUpdateRequestorClusterStateTransitionEvent", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
@property (nonatomic, copy, getter=getNewState) NSNumber * _Nonnull newState ZGMTR_DEPRECATED("Please use ZGMTROTASoftwareUpdateRequestorClusterStateTransitionEvent", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
@property (nonatomic, copy) NSNumber * _Nonnull reason ZGMTR_DEPRECATED("Please use ZGMTROTASoftwareUpdateRequestorClusterStateTransitionEvent", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
@property (nonatomic, copy) NSNumber * _Nullable targetSoftwareVersion ZGMTR_DEPRECATED("Please use ZGMTROTASoftwareUpdateRequestorClusterStateTransitionEvent", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
@end

ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4))
@interface ZGMTROTASoftwareUpdateRequestorClusterVersionAppliedEvent : NSObject <NSCopying>
@property (nonatomic, copy) NSNumber * _Nonnull softwareVersion ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
@property (nonatomic, copy) NSNumber * _Nonnull productID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
@end

ZGMTR_DEPRECATED("Please use ZGMTROTASoftwareUpdateRequestorClusterVersionAppliedEvent", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
@interface ZGMTROtaSoftwareUpdateRequestorClusterVersionAppliedEvent : ZGMTROTASoftwareUpdateRequestorClusterVersionAppliedEvent
@property (nonatomic, copy) NSNumber * _Nonnull softwareVersion ZGMTR_DEPRECATED("Please use ZGMTROTASoftwareUpdateRequestorClusterVersionAppliedEvent", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
@property (nonatomic, copy) NSNumber * _Nonnull productID ZGMTR_DEPRECATED("Please use ZGMTROTASoftwareUpdateRequestorClusterVersionAppliedEvent", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
@end

ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4))
@interface ZGMTROTASoftwareUpdateRequestorClusterDownloadErrorEvent : NSObject <NSCopying>
@property (nonatomic, copy) NSNumber * _Nonnull softwareVersion ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
@property (nonatomic, copy) NSNumber * _Nonnull bytesDownloaded ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
@property (nonatomic, copy) NSNumber * _Nullable progressPercent ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
@property (nonatomic, copy) NSNumber * _Nullable platformCode ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
@end

ZGMTR_DEPRECATED("Please use ZGMTROTASoftwareUpdateRequestorClusterDownloadErrorEvent", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
@interface ZGMTROtaSoftwareUpdateRequestorClusterDownloadErrorEvent : ZGMTROTASoftwareUpdateRequestorClusterDownloadErrorEvent
@property (nonatomic, copy) NSNumber * _Nonnull softwareVersion ZGMTR_DEPRECATED("Please use ZGMTROTASoftwareUpdateRequestorClusterDownloadErrorEvent", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
@property (nonatomic, copy) NSNumber * _Nonnull bytesDownloaded ZGMTR_DEPRECATED("Please use ZGMTROTASoftwareUpdateRequestorClusterDownloadErrorEvent", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
@property (nonatomic, copy) NSNumber * _Nullable progressPercent ZGMTR_DEPRECATED("Please use ZGMTROTASoftwareUpdateRequestorClusterDownloadErrorEvent", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
@property (nonatomic, copy) NSNumber * _Nullable platformCode ZGMTR_DEPRECATED("Please use ZGMTROTASoftwareUpdateRequestorClusterDownloadErrorEvent", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
@end

ZGMTR_DEPRECATED("This struct is unused and will be removed", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
@interface ZGMTRPowerSourceClusterBatChargeFaultChangeType : NSObject <NSCopying>
@property (nonatomic, copy) NSArray * _Nonnull current ZGMTR_DEPRECATED("Please use ZGMTRPowerSourceClusterBatChargeFaultChangeType", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
@property (nonatomic, copy) NSArray * _Nonnull previous ZGMTR_DEPRECATED("Please use ZGMTRPowerSourceClusterBatChargeFaultChangeType", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
@end

ZGMTR_DEPRECATED("This struct is unused and will be removed", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
@interface ZGMTRPowerSourceClusterBatFaultChangeType : NSObject <NSCopying>
@property (nonatomic, copy) NSArray * _Nonnull current ZGMTR_DEPRECATED("Please use ZGMTRPowerSourceClusterBatFaultChangeType", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
@property (nonatomic, copy) NSArray * _Nonnull previous ZGMTR_DEPRECATED("Please use ZGMTRPowerSourceClusterBatFaultChangeType", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
@end

ZGMTR_DEPRECATED("This struct is unused and will be removed", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
@interface ZGMTRPowerSourceClusterWiredFaultChangeType : NSObject <NSCopying>
@property (nonatomic, copy) NSArray * _Nonnull current ZGMTR_DEPRECATED("Please use ZGMTRPowerSourceClusterWiredFaultChangeType", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
@property (nonatomic, copy) NSArray * _Nonnull previous ZGMTR_DEPRECATED("Please use ZGMTRPowerSourceClusterWiredFaultChangeType", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
@end

ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4))
@interface ZGMTRPowerSourceClusterWiredFaultChangeEvent : NSObject <NSCopying>
@property (nonatomic, copy) NSArray * _Nonnull current ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
@property (nonatomic, copy) NSArray * _Nonnull previous ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
@end

ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4))
@interface ZGMTRPowerSourceClusterBatFaultChangeEvent : NSObject <NSCopying>
@property (nonatomic, copy) NSArray * _Nonnull current ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
@property (nonatomic, copy) NSArray * _Nonnull previous ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
@end

ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4))
@interface ZGMTRPowerSourceClusterBatChargeFaultChangeEvent : NSObject <NSCopying>
@property (nonatomic, copy) NSArray * _Nonnull current ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
@property (nonatomic, copy) NSArray * _Nonnull previous ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
@end

ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1))
@interface ZGMTRGeneralCommissioningClusterBasicCommissioningInfo : NSObject <NSCopying>
@property (nonatomic, copy) NSNumber * _Nonnull failSafeExpiryLengthSeconds ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));
@property (nonatomic, copy) NSNumber * _Nonnull maxCumulativeFailsafeSeconds ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));
@end

ZGMTR_AVAILABLE(ios(17.0), macos(14.0), watchos(10.0), tvos(17.0))
@interface ZGMTRNetworkCommissioningClusterNetworkInfoStruct : NSObject <NSCopying>
@property (nonatomic, copy) NSData * _Nonnull networkID ZGMTR_AVAILABLE(ios(17.0), macos(14.0), watchos(10.0), tvos(17.0));
@property (nonatomic, copy) NSNumber * _Nonnull connected ZGMTR_AVAILABLE(ios(17.0), macos(14.0), watchos(10.0), tvos(17.0));
@property (nonatomic, copy) NSData * _Nullable networkIdentifier ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSData * _Nullable clientIdentifier ZGMTR_PROVISIONALLY_AVAILABLE;
@end

ZGMTR_DEPRECATED("Please use ZGMTRNetworkCommissioningClusterNetworkInfoStruct", ios(16.1, 17.0), macos(13.0, 14.0), watchos(9.1, 10.0), tvos(16.1, 17.0))
@interface ZGMTRNetworkCommissioningClusterNetworkInfo : ZGMTRNetworkCommissioningClusterNetworkInfoStruct
@property (nonatomic, copy) NSData * _Nonnull networkID ZGMTR_DEPRECATED("Please use ZGMTRNetworkCommissioningClusterNetworkInfoStruct", ios(16.1, 17.0), macos(13.0, 14.0), watchos(9.1, 10.0), tvos(16.1, 17.0));
@property (nonatomic, copy) NSNumber * _Nonnull connected ZGMTR_DEPRECATED("Please use ZGMTRNetworkCommissioningClusterNetworkInfoStruct", ios(16.1, 17.0), macos(13.0, 14.0), watchos(9.1, 10.0), tvos(16.1, 17.0));
@end

ZGMTR_AVAILABLE(ios(17.0), macos(14.0), watchos(10.0), tvos(17.0))
@interface ZGMTRNetworkCommissioningClusterThreadInterfaceScanResultStruct : NSObject <NSCopying>
@property (nonatomic, copy) NSNumber * _Nonnull panId ZGMTR_AVAILABLE(ios(17.0), macos(14.0), watchos(10.0), tvos(17.0));
@property (nonatomic, copy) NSNumber * _Nonnull extendedPanId ZGMTR_AVAILABLE(ios(17.0), macos(14.0), watchos(10.0), tvos(17.0));
@property (nonatomic, copy) NSString * _Nonnull networkName ZGMTR_AVAILABLE(ios(17.0), macos(14.0), watchos(10.0), tvos(17.0));
@property (nonatomic, copy) NSNumber * _Nonnull channel ZGMTR_AVAILABLE(ios(17.0), macos(14.0), watchos(10.0), tvos(17.0));
@property (nonatomic, copy) NSNumber * _Nonnull version ZGMTR_AVAILABLE(ios(17.0), macos(14.0), watchos(10.0), tvos(17.0));
@property (nonatomic, copy) NSData * _Nonnull extendedAddress ZGMTR_AVAILABLE(ios(17.0), macos(14.0), watchos(10.0), tvos(17.0));
@property (nonatomic, copy) NSNumber * _Nonnull rssi ZGMTR_AVAILABLE(ios(17.0), macos(14.0), watchos(10.0), tvos(17.0));
@property (nonatomic, copy) NSNumber * _Nonnull lqi ZGMTR_AVAILABLE(ios(17.0), macos(14.0), watchos(10.0), tvos(17.0));
@end

ZGMTR_DEPRECATED("Please use ZGMTRNetworkCommissioningClusterThreadInterfaceScanResultStruct", ios(16.1, 17.0), macos(13.0, 14.0), watchos(9.1, 10.0), tvos(16.1, 17.0))
@interface ZGMTRNetworkCommissioningClusterThreadInterfaceScanResult : ZGMTRNetworkCommissioningClusterThreadInterfaceScanResultStruct
@property (nonatomic, copy) NSNumber * _Nonnull panId ZGMTR_DEPRECATED("Please use ZGMTRNetworkCommissioningClusterThreadInterfaceScanResultStruct", ios(16.1, 17.0), macos(13.0, 14.0), watchos(9.1, 10.0), tvos(16.1, 17.0));
@property (nonatomic, copy) NSNumber * _Nonnull extendedPanId ZGMTR_DEPRECATED("Please use ZGMTRNetworkCommissioningClusterThreadInterfaceScanResultStruct", ios(16.1, 17.0), macos(13.0, 14.0), watchos(9.1, 10.0), tvos(16.1, 17.0));
@property (nonatomic, copy) NSString * _Nonnull networkName ZGMTR_DEPRECATED("Please use ZGMTRNetworkCommissioningClusterThreadInterfaceScanResultStruct", ios(16.1, 17.0), macos(13.0, 14.0), watchos(9.1, 10.0), tvos(16.1, 17.0));
@property (nonatomic, copy) NSNumber * _Nonnull channel ZGMTR_DEPRECATED("Please use ZGMTRNetworkCommissioningClusterThreadInterfaceScanResultStruct", ios(16.1, 17.0), macos(13.0, 14.0), watchos(9.1, 10.0), tvos(16.1, 17.0));
@property (nonatomic, copy) NSNumber * _Nonnull version ZGMTR_DEPRECATED("Please use ZGMTRNetworkCommissioningClusterThreadInterfaceScanResultStruct", ios(16.1, 17.0), macos(13.0, 14.0), watchos(9.1, 10.0), tvos(16.1, 17.0));
@property (nonatomic, copy) NSData * _Nonnull extendedAddress ZGMTR_DEPRECATED("Please use ZGMTRNetworkCommissioningClusterThreadInterfaceScanResultStruct", ios(16.1, 17.0), macos(13.0, 14.0), watchos(9.1, 10.0), tvos(16.1, 17.0));
@property (nonatomic, copy) NSNumber * _Nonnull rssi ZGMTR_DEPRECATED("Please use ZGMTRNetworkCommissioningClusterThreadInterfaceScanResultStruct", ios(16.1, 17.0), macos(13.0, 14.0), watchos(9.1, 10.0), tvos(16.1, 17.0));
@property (nonatomic, copy) NSNumber * _Nonnull lqi ZGMTR_DEPRECATED("Please use ZGMTRNetworkCommissioningClusterThreadInterfaceScanResultStruct", ios(16.1, 17.0), macos(13.0, 14.0), watchos(9.1, 10.0), tvos(16.1, 17.0));
@end

ZGMTR_AVAILABLE(ios(17.0), macos(14.0), watchos(10.0), tvos(17.0))
@interface ZGMTRNetworkCommissioningClusterWiFiInterfaceScanResultStruct : NSObject <NSCopying>
@property (nonatomic, copy) NSNumber * _Nonnull security ZGMTR_AVAILABLE(ios(17.0), macos(14.0), watchos(10.0), tvos(17.0));
@property (nonatomic, copy) NSData * _Nonnull ssid ZGMTR_AVAILABLE(ios(17.0), macos(14.0), watchos(10.0), tvos(17.0));
@property (nonatomic, copy) NSData * _Nonnull bssid ZGMTR_AVAILABLE(ios(17.0), macos(14.0), watchos(10.0), tvos(17.0));
@property (nonatomic, copy) NSNumber * _Nonnull channel ZGMTR_AVAILABLE(ios(17.0), macos(14.0), watchos(10.0), tvos(17.0));
@property (nonatomic, copy) NSNumber * _Nonnull wiFiBand ZGMTR_AVAILABLE(ios(17.0), macos(14.0), watchos(10.0), tvos(17.0));
@property (nonatomic, copy) NSNumber * _Nonnull rssi ZGMTR_AVAILABLE(ios(17.0), macos(14.0), watchos(10.0), tvos(17.0));
@end

ZGMTR_DEPRECATED("Please use ZGMTRNetworkCommissioningClusterWiFiInterfaceScanResultStruct", ios(16.1, 17.0), macos(13.0, 14.0), watchos(9.1, 10.0), tvos(16.1, 17.0))
@interface ZGMTRNetworkCommissioningClusterWiFiInterfaceScanResult : ZGMTRNetworkCommissioningClusterWiFiInterfaceScanResultStruct
@property (nonatomic, copy) NSNumber * _Nonnull security ZGMTR_DEPRECATED("Please use ZGMTRNetworkCommissioningClusterWiFiInterfaceScanResultStruct", ios(16.1, 17.0), macos(13.0, 14.0), watchos(9.1, 10.0), tvos(16.1, 17.0));
@property (nonatomic, copy) NSData * _Nonnull ssid ZGMTR_DEPRECATED("Please use ZGMTRNetworkCommissioningClusterWiFiInterfaceScanResultStruct", ios(16.1, 17.0), macos(13.0, 14.0), watchos(9.1, 10.0), tvos(16.1, 17.0));
@property (nonatomic, copy) NSData * _Nonnull bssid ZGMTR_DEPRECATED("Please use ZGMTRNetworkCommissioningClusterWiFiInterfaceScanResultStruct", ios(16.1, 17.0), macos(13.0, 14.0), watchos(9.1, 10.0), tvos(16.1, 17.0));
@property (nonatomic, copy) NSNumber * _Nonnull channel ZGMTR_DEPRECATED("Please use ZGMTRNetworkCommissioningClusterWiFiInterfaceScanResultStruct", ios(16.1, 17.0), macos(13.0, 14.0), watchos(9.1, 10.0), tvos(16.1, 17.0));
@property (nonatomic, copy) NSNumber * _Nonnull wiFiBand ZGMTR_DEPRECATED("Please use ZGMTRNetworkCommissioningClusterWiFiInterfaceScanResultStruct", ios(16.1, 17.0), macos(13.0, 14.0), watchos(9.1, 10.0), tvos(16.1, 17.0));
@property (nonatomic, copy) NSNumber * _Nonnull rssi ZGMTR_DEPRECATED("Please use ZGMTRNetworkCommissioningClusterWiFiInterfaceScanResultStruct", ios(16.1, 17.0), macos(13.0, 14.0), watchos(9.1, 10.0), tvos(16.1, 17.0));
@end

ZGMTR_PROVISIONALLY_AVAILABLE
@interface ZGMTRGeneralDiagnosticsClusterDeviceLoadStruct : NSObject <NSCopying>
@property (nonatomic, copy) NSNumber * _Nonnull currentSubscriptions ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSNumber * _Nonnull currentSubscriptionsForFabric ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSNumber * _Nonnull totalSubscriptionsEstablished ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSNumber * _Nonnull totalInteractionModelMessagesSent ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSNumber * _Nonnull totalInteractionModelMessagesReceived ZGMTR_PROVISIONALLY_AVAILABLE;
@end

ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4))
@interface ZGMTRGeneralDiagnosticsClusterNetworkInterface : NSObject <NSCopying>
@property (nonatomic, copy) NSString * _Nonnull name ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
@property (nonatomic, copy) NSNumber * _Nonnull isOperational ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
@property (nonatomic, copy) NSNumber * _Nullable offPremiseServicesReachableIPv4 ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
@property (nonatomic, copy) NSNumber * _Nullable offPremiseServicesReachableIPv6 ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
@property (nonatomic, copy) NSData * _Nonnull hardwareAddress ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
@property (nonatomic, copy) NSArray * _Nonnull iPv4Addresses ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
@property (nonatomic, copy) NSArray * _Nonnull iPv6Addresses ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
@property (nonatomic, copy) NSNumber * _Nonnull type ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
@end

ZGMTR_DEPRECATED("Please use ZGMTRGeneralDiagnosticsClusterNetworkInterface", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
@interface ZGMTRGeneralDiagnosticsClusterNetworkInterfaceType : ZGMTRGeneralDiagnosticsClusterNetworkInterface
@property (nonatomic, copy) NSString * _Nonnull name ZGMTR_DEPRECATED("Please use ZGMTRGeneralDiagnosticsClusterNetworkInterface", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
@property (nonatomic, copy) NSNumber * _Nonnull isOperational ZGMTR_DEPRECATED("Please use ZGMTRGeneralDiagnosticsClusterNetworkInterface", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
@property (nonatomic, copy) NSNumber * _Nullable offPremiseServicesReachableIPv4 ZGMTR_DEPRECATED("Please use ZGMTRGeneralDiagnosticsClusterNetworkInterface", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
@property (nonatomic, copy) NSNumber * _Nullable offPremiseServicesReachableIPv6 ZGMTR_DEPRECATED("Please use ZGMTRGeneralDiagnosticsClusterNetworkInterface", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
@property (nonatomic, copy) NSData * _Nonnull hardwareAddress ZGMTR_DEPRECATED("Please use ZGMTRGeneralDiagnosticsClusterNetworkInterface", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
@property (nonatomic, copy) NSArray * _Nonnull iPv4Addresses ZGMTR_DEPRECATED("Please use ZGMTRGeneralDiagnosticsClusterNetworkInterface", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
@property (nonatomic, copy) NSArray * _Nonnull iPv6Addresses ZGMTR_DEPRECATED("Please use ZGMTRGeneralDiagnosticsClusterNetworkInterface", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
@property (nonatomic, copy) NSNumber * _Nonnull type ZGMTR_DEPRECATED("Please use ZGMTRGeneralDiagnosticsClusterNetworkInterface", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
@end

ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1))
@interface ZGMTRGeneralDiagnosticsClusterHardwareFaultChangeEvent : NSObject <NSCopying>
@property (nonatomic, copy) NSArray * _Nonnull current ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));
@property (nonatomic, copy) NSArray * _Nonnull previous ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));
@end

ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1))
@interface ZGMTRGeneralDiagnosticsClusterRadioFaultChangeEvent : NSObject <NSCopying>
@property (nonatomic, copy) NSArray * _Nonnull current ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));
@property (nonatomic, copy) NSArray * _Nonnull previous ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));
@end

ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1))
@interface ZGMTRGeneralDiagnosticsClusterNetworkFaultChangeEvent : NSObject <NSCopying>
@property (nonatomic, copy) NSArray * _Nonnull current ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));
@property (nonatomic, copy) NSArray * _Nonnull previous ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));
@end

ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1))
@interface ZGMTRGeneralDiagnosticsClusterBootReasonEvent : NSObject <NSCopying>
@property (nonatomic, copy) NSNumber * _Nonnull bootReason ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));
@end

ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4))
@interface ZGMTRSoftwareDiagnosticsClusterThreadMetricsStruct : NSObject <NSCopying>
@property (nonatomic, copy) NSNumber * _Nonnull id ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
@property (nonatomic, copy) NSString * _Nullable name ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
@property (nonatomic, copy) NSNumber * _Nullable stackFreeCurrent ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
@property (nonatomic, copy) NSNumber * _Nullable stackFreeMinimum ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
@property (nonatomic, copy) NSNumber * _Nullable stackSize ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
@end

ZGMTR_DEPRECATED("Please use ZGMTRSoftwareDiagnosticsClusterThreadMetricsStruct", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
@interface ZGMTRSoftwareDiagnosticsClusterThreadMetrics : ZGMTRSoftwareDiagnosticsClusterThreadMetricsStruct
@property (nonatomic, copy) NSNumber * _Nonnull id ZGMTR_DEPRECATED("Please use ZGMTRSoftwareDiagnosticsClusterThreadMetricsStruct", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
@property (nonatomic, copy) NSString * _Nullable name ZGMTR_DEPRECATED("Please use ZGMTRSoftwareDiagnosticsClusterThreadMetricsStruct", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
@property (nonatomic, copy) NSNumber * _Nullable stackFreeCurrent ZGMTR_DEPRECATED("Please use ZGMTRSoftwareDiagnosticsClusterThreadMetricsStruct", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
@property (nonatomic, copy) NSNumber * _Nullable stackFreeMinimum ZGMTR_DEPRECATED("Please use ZGMTRSoftwareDiagnosticsClusterThreadMetricsStruct", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
@property (nonatomic, copy) NSNumber * _Nullable stackSize ZGMTR_DEPRECATED("Please use ZGMTRSoftwareDiagnosticsClusterThreadMetricsStruct", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
@end

ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1))
@interface ZGMTRSoftwareDiagnosticsClusterSoftwareFaultEvent : NSObject <NSCopying>
@property (nonatomic, copy) NSNumber * _Nonnull id ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));
@property (nonatomic, copy) NSString * _Nullable name ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));
@property (nonatomic, copy) NSData * _Nullable faultRecording ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));
@end

ZGMTR_AVAILABLE(ios(17.0), macos(14.0), watchos(10.0), tvos(17.0))
@interface ZGMTRThreadNetworkDiagnosticsClusterNeighborTableStruct : NSObject <NSCopying>
@property (nonatomic, copy) NSNumber * _Nonnull extAddress ZGMTR_AVAILABLE(ios(17.0), macos(14.0), watchos(10.0), tvos(17.0));
@property (nonatomic, copy) NSNumber * _Nonnull age ZGMTR_AVAILABLE(ios(17.0), macos(14.0), watchos(10.0), tvos(17.0));
@property (nonatomic, copy) NSNumber * _Nonnull rloc16 ZGMTR_AVAILABLE(ios(17.0), macos(14.0), watchos(10.0), tvos(17.0));
@property (nonatomic, copy) NSNumber * _Nonnull linkFrameCounter ZGMTR_AVAILABLE(ios(17.0), macos(14.0), watchos(10.0), tvos(17.0));
@property (nonatomic, copy) NSNumber * _Nonnull mleFrameCounter ZGMTR_AVAILABLE(ios(17.0), macos(14.0), watchos(10.0), tvos(17.0));
@property (nonatomic, copy) NSNumber * _Nonnull lqi ZGMTR_AVAILABLE(ios(17.0), macos(14.0), watchos(10.0), tvos(17.0));
@property (nonatomic, copy) NSNumber * _Nullable averageRssi ZGMTR_AVAILABLE(ios(17.0), macos(14.0), watchos(10.0), tvos(17.0));
@property (nonatomic, copy) NSNumber * _Nullable lastRssi ZGMTR_AVAILABLE(ios(17.0), macos(14.0), watchos(10.0), tvos(17.0));
@property (nonatomic, copy) NSNumber * _Nonnull frameErrorRate ZGMTR_AVAILABLE(ios(17.0), macos(14.0), watchos(10.0), tvos(17.0));
@property (nonatomic, copy) NSNumber * _Nonnull messageErrorRate ZGMTR_AVAILABLE(ios(17.0), macos(14.0), watchos(10.0), tvos(17.0));
@property (nonatomic, copy) NSNumber * _Nonnull rxOnWhenIdle ZGMTR_AVAILABLE(ios(17.0), macos(14.0), watchos(10.0), tvos(17.0));
@property (nonatomic, copy) NSNumber * _Nonnull fullThreadDevice ZGMTR_AVAILABLE(ios(17.0), macos(14.0), watchos(10.0), tvos(17.0));
@property (nonatomic, copy) NSNumber * _Nonnull fullNetworkData ZGMTR_AVAILABLE(ios(17.0), macos(14.0), watchos(10.0), tvos(17.0));
@property (nonatomic, copy) NSNumber * _Nonnull isChild ZGMTR_AVAILABLE(ios(17.0), macos(14.0), watchos(10.0), tvos(17.0));
@end

ZGMTR_DEPRECATED("Please use ZGMTRThreadNetworkDiagnosticsClusterNeighborTableStruct", ios(16.1, 17.0), macos(13.0, 14.0), watchos(9.1, 10.0), tvos(16.1, 17.0))
@interface ZGMTRThreadNetworkDiagnosticsClusterNeighborTable : ZGMTRThreadNetworkDiagnosticsClusterNeighborTableStruct
@property (nonatomic, copy) NSNumber * _Nonnull extAddress ZGMTR_DEPRECATED("Please use ZGMTRThreadNetworkDiagnosticsClusterNeighborTableStruct", ios(16.1, 17.0), macos(13.0, 14.0), watchos(9.1, 10.0), tvos(16.1, 17.0));
@property (nonatomic, copy) NSNumber * _Nonnull age ZGMTR_DEPRECATED("Please use ZGMTRThreadNetworkDiagnosticsClusterNeighborTableStruct", ios(16.1, 17.0), macos(13.0, 14.0), watchos(9.1, 10.0), tvos(16.1, 17.0));
@property (nonatomic, copy) NSNumber * _Nonnull rloc16 ZGMTR_DEPRECATED("Please use ZGMTRThreadNetworkDiagnosticsClusterNeighborTableStruct", ios(16.1, 17.0), macos(13.0, 14.0), watchos(9.1, 10.0), tvos(16.1, 17.0));
@property (nonatomic, copy) NSNumber * _Nonnull linkFrameCounter ZGMTR_DEPRECATED("Please use ZGMTRThreadNetworkDiagnosticsClusterNeighborTableStruct", ios(16.1, 17.0), macos(13.0, 14.0), watchos(9.1, 10.0), tvos(16.1, 17.0));
@property (nonatomic, copy) NSNumber * _Nonnull mleFrameCounter ZGMTR_DEPRECATED("Please use ZGMTRThreadNetworkDiagnosticsClusterNeighborTableStruct", ios(16.1, 17.0), macos(13.0, 14.0), watchos(9.1, 10.0), tvos(16.1, 17.0));
@property (nonatomic, copy) NSNumber * _Nonnull lqi ZGMTR_DEPRECATED("Please use ZGMTRThreadNetworkDiagnosticsClusterNeighborTableStruct", ios(16.1, 17.0), macos(13.0, 14.0), watchos(9.1, 10.0), tvos(16.1, 17.0));
@property (nonatomic, copy) NSNumber * _Nullable averageRssi ZGMTR_DEPRECATED("Please use ZGMTRThreadNetworkDiagnosticsClusterNeighborTableStruct", ios(16.1, 17.0), macos(13.0, 14.0), watchos(9.1, 10.0), tvos(16.1, 17.0));
@property (nonatomic, copy) NSNumber * _Nullable lastRssi ZGMTR_DEPRECATED("Please use ZGMTRThreadNetworkDiagnosticsClusterNeighborTableStruct", ios(16.1, 17.0), macos(13.0, 14.0), watchos(9.1, 10.0), tvos(16.1, 17.0));
@property (nonatomic, copy) NSNumber * _Nonnull frameErrorRate ZGMTR_DEPRECATED("Please use ZGMTRThreadNetworkDiagnosticsClusterNeighborTableStruct", ios(16.1, 17.0), macos(13.0, 14.0), watchos(9.1, 10.0), tvos(16.1, 17.0));
@property (nonatomic, copy) NSNumber * _Nonnull messageErrorRate ZGMTR_DEPRECATED("Please use ZGMTRThreadNetworkDiagnosticsClusterNeighborTableStruct", ios(16.1, 17.0), macos(13.0, 14.0), watchos(9.1, 10.0), tvos(16.1, 17.0));
@property (nonatomic, copy) NSNumber * _Nonnull rxOnWhenIdle ZGMTR_DEPRECATED("Please use ZGMTRThreadNetworkDiagnosticsClusterNeighborTableStruct", ios(16.1, 17.0), macos(13.0, 14.0), watchos(9.1, 10.0), tvos(16.1, 17.0));
@property (nonatomic, copy) NSNumber * _Nonnull fullThreadDevice ZGMTR_DEPRECATED("Please use ZGMTRThreadNetworkDiagnosticsClusterNeighborTableStruct", ios(16.1, 17.0), macos(13.0, 14.0), watchos(9.1, 10.0), tvos(16.1, 17.0));
@property (nonatomic, copy) NSNumber * _Nonnull fullNetworkData ZGMTR_DEPRECATED("Please use ZGMTRThreadNetworkDiagnosticsClusterNeighborTableStruct", ios(16.1, 17.0), macos(13.0, 14.0), watchos(9.1, 10.0), tvos(16.1, 17.0));
@property (nonatomic, copy) NSNumber * _Nonnull isChild ZGMTR_DEPRECATED("Please use ZGMTRThreadNetworkDiagnosticsClusterNeighborTableStruct", ios(16.1, 17.0), macos(13.0, 14.0), watchos(9.1, 10.0), tvos(16.1, 17.0));
@end

ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1))
@interface ZGMTRThreadNetworkDiagnosticsClusterOperationalDatasetComponents : NSObject <NSCopying>
@property (nonatomic, copy) NSNumber * _Nonnull activeTimestampPresent ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));
@property (nonatomic, copy) NSNumber * _Nonnull pendingTimestampPresent ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));
@property (nonatomic, copy) NSNumber * _Nonnull masterKeyPresent ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));
@property (nonatomic, copy) NSNumber * _Nonnull networkNamePresent ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));
@property (nonatomic, copy) NSNumber * _Nonnull extendedPanIdPresent ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));
@property (nonatomic, copy) NSNumber * _Nonnull meshLocalPrefixPresent ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));
@property (nonatomic, copy) NSNumber * _Nonnull delayPresent ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));
@property (nonatomic, copy) NSNumber * _Nonnull panIdPresent ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));
@property (nonatomic, copy) NSNumber * _Nonnull channelPresent ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));
@property (nonatomic, copy) NSNumber * _Nonnull pskcPresent ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));
@property (nonatomic, copy) NSNumber * _Nonnull securityPolicyPresent ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));
@property (nonatomic, copy) NSNumber * _Nonnull channelMaskPresent ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));
@end

ZGMTR_AVAILABLE(ios(17.0), macos(14.0), watchos(10.0), tvos(17.0))
@interface ZGMTRThreadNetworkDiagnosticsClusterRouteTableStruct : NSObject <NSCopying>
@property (nonatomic, copy) NSNumber * _Nonnull extAddress ZGMTR_AVAILABLE(ios(17.0), macos(14.0), watchos(10.0), tvos(17.0));
@property (nonatomic, copy) NSNumber * _Nonnull rloc16 ZGMTR_AVAILABLE(ios(17.0), macos(14.0), watchos(10.0), tvos(17.0));
@property (nonatomic, copy) NSNumber * _Nonnull routerId ZGMTR_AVAILABLE(ios(17.0), macos(14.0), watchos(10.0), tvos(17.0));
@property (nonatomic, copy) NSNumber * _Nonnull nextHop ZGMTR_AVAILABLE(ios(17.0), macos(14.0), watchos(10.0), tvos(17.0));
@property (nonatomic, copy) NSNumber * _Nonnull pathCost ZGMTR_AVAILABLE(ios(17.0), macos(14.0), watchos(10.0), tvos(17.0));
@property (nonatomic, copy) NSNumber * _Nonnull lqiIn ZGMTR_AVAILABLE(ios(17.0), macos(14.0), watchos(10.0), tvos(17.0));
@property (nonatomic, copy) NSNumber * _Nonnull lqiOut ZGMTR_AVAILABLE(ios(17.0), macos(14.0), watchos(10.0), tvos(17.0));
@property (nonatomic, copy) NSNumber * _Nonnull age ZGMTR_AVAILABLE(ios(17.0), macos(14.0), watchos(10.0), tvos(17.0));
@property (nonatomic, copy) NSNumber * _Nonnull allocated ZGMTR_AVAILABLE(ios(17.0), macos(14.0), watchos(10.0), tvos(17.0));
@property (nonatomic, copy) NSNumber * _Nonnull linkEstablished ZGMTR_AVAILABLE(ios(17.0), macos(14.0), watchos(10.0), tvos(17.0));
@end

ZGMTR_DEPRECATED("Please use ZGMTRThreadNetworkDiagnosticsClusterRouteTableStruct", ios(16.1, 17.0), macos(13.0, 14.0), watchos(9.1, 10.0), tvos(16.1, 17.0))
@interface ZGMTRThreadNetworkDiagnosticsClusterRouteTable : ZGMTRThreadNetworkDiagnosticsClusterRouteTableStruct
@property (nonatomic, copy) NSNumber * _Nonnull extAddress ZGMTR_DEPRECATED("Please use ZGMTRThreadNetworkDiagnosticsClusterRouteTableStruct", ios(16.1, 17.0), macos(13.0, 14.0), watchos(9.1, 10.0), tvos(16.1, 17.0));
@property (nonatomic, copy) NSNumber * _Nonnull rloc16 ZGMTR_DEPRECATED("Please use ZGMTRThreadNetworkDiagnosticsClusterRouteTableStruct", ios(16.1, 17.0), macos(13.0, 14.0), watchos(9.1, 10.0), tvos(16.1, 17.0));
@property (nonatomic, copy) NSNumber * _Nonnull routerId ZGMTR_DEPRECATED("Please use ZGMTRThreadNetworkDiagnosticsClusterRouteTableStruct", ios(16.1, 17.0), macos(13.0, 14.0), watchos(9.1, 10.0), tvos(16.1, 17.0));
@property (nonatomic, copy) NSNumber * _Nonnull nextHop ZGMTR_DEPRECATED("Please use ZGMTRThreadNetworkDiagnosticsClusterRouteTableStruct", ios(16.1, 17.0), macos(13.0, 14.0), watchos(9.1, 10.0), tvos(16.1, 17.0));
@property (nonatomic, copy) NSNumber * _Nonnull pathCost ZGMTR_DEPRECATED("Please use ZGMTRThreadNetworkDiagnosticsClusterRouteTableStruct", ios(16.1, 17.0), macos(13.0, 14.0), watchos(9.1, 10.0), tvos(16.1, 17.0));
@property (nonatomic, copy) NSNumber * _Nonnull lqiIn ZGMTR_DEPRECATED("Please use ZGMTRThreadNetworkDiagnosticsClusterRouteTableStruct", ios(16.1, 17.0), macos(13.0, 14.0), watchos(9.1, 10.0), tvos(16.1, 17.0));
@property (nonatomic, copy) NSNumber * _Nonnull lqiOut ZGMTR_DEPRECATED("Please use ZGMTRThreadNetworkDiagnosticsClusterRouteTableStruct", ios(16.1, 17.0), macos(13.0, 14.0), watchos(9.1, 10.0), tvos(16.1, 17.0));
@property (nonatomic, copy) NSNumber * _Nonnull age ZGMTR_DEPRECATED("Please use ZGMTRThreadNetworkDiagnosticsClusterRouteTableStruct", ios(16.1, 17.0), macos(13.0, 14.0), watchos(9.1, 10.0), tvos(16.1, 17.0));
@property (nonatomic, copy) NSNumber * _Nonnull allocated ZGMTR_DEPRECATED("Please use ZGMTRThreadNetworkDiagnosticsClusterRouteTableStruct", ios(16.1, 17.0), macos(13.0, 14.0), watchos(9.1, 10.0), tvos(16.1, 17.0));
@property (nonatomic, copy) NSNumber * _Nonnull linkEstablished ZGMTR_DEPRECATED("Please use ZGMTRThreadNetworkDiagnosticsClusterRouteTableStruct", ios(16.1, 17.0), macos(13.0, 14.0), watchos(9.1, 10.0), tvos(16.1, 17.0));
@end

ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1))
@interface ZGMTRThreadNetworkDiagnosticsClusterSecurityPolicy : NSObject <NSCopying>
@property (nonatomic, copy) NSNumber * _Nonnull rotationTime ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));
@property (nonatomic, copy) NSNumber * _Nonnull flags ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));
@end

ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1))
@interface ZGMTRThreadNetworkDiagnosticsClusterConnectionStatusEvent : NSObject <NSCopying>
@property (nonatomic, copy) NSNumber * _Nonnull connectionStatus ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));
@end

ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1))
@interface ZGMTRThreadNetworkDiagnosticsClusterNetworkFaultChangeEvent : NSObject <NSCopying>
@property (nonatomic, copy) NSArray * _Nonnull current ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));
@property (nonatomic, copy) NSArray * _Nonnull previous ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));
@end

ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1))
@interface ZGMTRWiFiNetworkDiagnosticsClusterDisconnectionEvent : NSObject <NSCopying>
@property (nonatomic, copy) NSNumber * _Nonnull reasonCode ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));
@end

ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1))
@interface ZGMTRWiFiNetworkDiagnosticsClusterAssociationFailureEvent : NSObject <NSCopying>
@property (nonatomic, copy) NSNumber * _Nonnull associationFailureCause ZGMTR_AVAILABLE(ios(17.4), macos(14.4), watchos(10.4), tvos(17.4));
@property (nonatomic, copy) NSNumber * _Nonnull associationFailure ZGMTR_DEPRECATED("Please use associationFailureCause", ios(16.1, 17.4), macos(13.0, 14.4), watchos(9.1, 10.4), tvos(16.1, 17.4));
@property (nonatomic, copy) NSNumber * _Nonnull status ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));
@end

ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1))
@interface ZGMTRWiFiNetworkDiagnosticsClusterConnectionStatusEvent : NSObject <NSCopying>
@property (nonatomic, copy) NSNumber * _Nonnull connectionStatus ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));
@end

ZGMTR_AVAILABLE(ios(16.5), macos(13.4), watchos(9.5), tvos(16.5))
@interface ZGMTRTimeSynchronizationClusterDSTOffsetStruct : NSObject <NSCopying>
@property (nonatomic, copy) NSNumber * _Nonnull offset ZGMTR_AVAILABLE(ios(16.5), macos(13.4), watchos(9.5), tvos(16.5));
@property (nonatomic, copy) NSNumber * _Nonnull validStarting ZGMTR_AVAILABLE(ios(16.5), macos(13.4), watchos(9.5), tvos(16.5));
@property (nonatomic, copy) NSNumber * _Nullable validUntil ZGMTR_AVAILABLE(ios(16.5), macos(13.4), watchos(9.5), tvos(16.5));
@end

ZGMTR_DEPRECATED("Please use ZGMTRTimeSynchronizationClusterDSTOffsetStruct", ios(16.1, 16.5), macos(13.0, 13.4), watchos(9.1, 9.5), tvos(16.1, 16.5))
@interface ZGMTRTimeSynchronizationClusterDstOffsetType : ZGMTRTimeSynchronizationClusterDSTOffsetStruct
@property (nonatomic, copy) NSNumber * _Nonnull offset ZGMTR_DEPRECATED("Please use ZGMTRTimeSynchronizationClusterDSTOffsetStruct", ios(16.1, 16.5), macos(13.0, 13.4), watchos(9.1, 9.5), tvos(16.1, 16.5));
@property (nonatomic, copy) NSNumber * _Nonnull validStarting ZGMTR_DEPRECATED("Please use ZGMTRTimeSynchronizationClusterDSTOffsetStruct", ios(16.1, 16.5), macos(13.0, 13.4), watchos(9.1, 9.5), tvos(16.1, 16.5));
@property (nonatomic, copy) NSNumber * _Nullable validUntil ZGMTR_DEPRECATED("Please use ZGMTRTimeSynchronizationClusterDSTOffsetStruct", ios(16.1, 16.5), macos(13.0, 13.4), watchos(9.1, 9.5), tvos(16.1, 16.5));
@end

ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4))
@interface ZGMTRTimeSynchronizationClusterFabricScopedTrustedTimeSourceStruct : NSObject <NSCopying>
@property (nonatomic, copy) NSNumber * _Nonnull nodeID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));
@property (nonatomic, copy) NSNumber * _Nonnull endpoint ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));
@end

ZGMTR_AVAILABLE(ios(16.5), macos(13.4), watchos(9.5), tvos(16.5))
@interface ZGMTRTimeSynchronizationClusterTimeZoneStruct : NSObject <NSCopying>
@property (nonatomic, copy) NSNumber * _Nonnull offset ZGMTR_AVAILABLE(ios(16.5), macos(13.4), watchos(9.5), tvos(16.5));
@property (nonatomic, copy) NSNumber * _Nonnull validAt ZGMTR_AVAILABLE(ios(16.5), macos(13.4), watchos(9.5), tvos(16.5));
@property (nonatomic, copy) NSString * _Nullable name ZGMTR_AVAILABLE(ios(16.5), macos(13.4), watchos(9.5), tvos(16.5));
@end

ZGMTR_DEPRECATED("Please use ZGMTRTimeSynchronizationClusterTimeZoneStruct", ios(16.1, 16.5), macos(13.0, 13.4), watchos(9.1, 9.5), tvos(16.1, 16.5))
@interface ZGMTRTimeSynchronizationClusterTimeZoneType : ZGMTRTimeSynchronizationClusterTimeZoneStruct
@property (nonatomic, copy) NSNumber * _Nonnull offset ZGMTR_DEPRECATED("Please use ZGMTRTimeSynchronizationClusterTimeZoneStruct", ios(16.1, 16.5), macos(13.0, 13.4), watchos(9.1, 9.5), tvos(16.1, 16.5));
@property (nonatomic, copy) NSNumber * _Nonnull validAt ZGMTR_DEPRECATED("Please use ZGMTRTimeSynchronizationClusterTimeZoneStruct", ios(16.1, 16.5), macos(13.0, 13.4), watchos(9.1, 9.5), tvos(16.1, 16.5));
@property (nonatomic, copy) NSString * _Nullable name ZGMTR_DEPRECATED("Please use ZGMTRTimeSynchronizationClusterTimeZoneStruct", ios(16.1, 16.5), macos(13.0, 13.4), watchos(9.1, 9.5), tvos(16.1, 16.5));
@end

ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4))
@interface ZGMTRTimeSynchronizationClusterTrustedTimeSourceStruct : NSObject <NSCopying>
@property (nonatomic, copy) NSNumber * _Nonnull fabricIndex ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));
@property (nonatomic, copy) NSNumber * _Nonnull nodeID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));
@property (nonatomic, copy) NSNumber * _Nonnull endpoint ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));
@end

ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4))
@interface ZGMTRTimeSynchronizationClusterDSTTableEmptyEvent : NSObject <NSCopying>
@end

ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4))
@interface ZGMTRTimeSynchronizationClusterDSTStatusEvent : NSObject <NSCopying>
@property (nonatomic, copy) NSNumber * _Nonnull dstOffsetActive ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));
@end

ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4))
@interface ZGMTRTimeSynchronizationClusterTimeZoneStatusEvent : NSObject <NSCopying>
@property (nonatomic, copy) NSNumber * _Nonnull offset ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));
@property (nonatomic, copy) NSString * _Nullable name ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));
@end

ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4))
@interface ZGMTRTimeSynchronizationClusterTimeFailureEvent : NSObject <NSCopying>
@end

ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4))
@interface ZGMTRTimeSynchronizationClusterMissingTrustedTimeSourceEvent : NSObject <NSCopying>
@end

ZGMTR_AVAILABLE(ios(17.0), macos(14.0), watchos(10.0), tvos(17.0))
@interface ZGMTRBridgedDeviceBasicInformationClusterProductAppearanceStruct : NSObject <NSCopying>
@property (nonatomic, copy) NSNumber * _Nonnull finish ZGMTR_AVAILABLE(ios(17.0), macos(14.0), watchos(10.0), tvos(17.0));
@property (nonatomic, copy) NSNumber * _Nullable primaryColor ZGMTR_AVAILABLE(ios(17.0), macos(14.0), watchos(10.0), tvos(17.0));
@end

ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4))
@interface ZGMTRBridgedDeviceBasicInformationClusterStartUpEvent : NSObject <NSCopying>
@property (nonatomic, copy) NSNumber * _Nonnull softwareVersion ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
@end

ZGMTR_DEPRECATED("Please use ZGMTRBridgedDeviceBasicInformationClusterStartUpEvent", ios(16.1, 17.0), macos(13.0, 14.0), watchos(9.1, 10.0), tvos(16.1, 17.0))
@interface ZGMTRBridgedDeviceBasicClusterStartUpEvent : ZGMTRBridgedDeviceBasicInformationClusterStartUpEvent
@property (nonatomic, copy) NSNumber * _Nonnull softwareVersion ZGMTR_DEPRECATED("Please use ZGMTRBridgedDeviceBasicInformationClusterStartUpEvent", ios(16.1, 17.0), macos(13.0, 14.0), watchos(9.1, 10.0), tvos(16.1, 17.0));
@end

ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4))
@interface ZGMTRBridgedDeviceBasicInformationClusterShutDownEvent : NSObject <NSCopying>
@end

ZGMTR_DEPRECATED("Please use ZGMTRBridgedDeviceBasicInformationClusterShutDownEvent", ios(16.1, 17.0), macos(13.0, 14.0), watchos(9.1, 10.0), tvos(16.1, 17.0))
@interface ZGMTRBridgedDeviceBasicClusterShutDownEvent : ZGMTRBridgedDeviceBasicInformationClusterShutDownEvent
@end

ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4))
@interface ZGMTRBridgedDeviceBasicInformationClusterLeaveEvent : NSObject <NSCopying>
@end

ZGMTR_DEPRECATED("Please use ZGMTRBridgedDeviceBasicInformationClusterLeaveEvent", ios(16.1, 17.0), macos(13.0, 14.0), watchos(9.1, 10.0), tvos(16.1, 17.0))
@interface ZGMTRBridgedDeviceBasicClusterLeaveEvent : ZGMTRBridgedDeviceBasicInformationClusterLeaveEvent
@end

ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4))
@interface ZGMTRBridgedDeviceBasicInformationClusterReachableChangedEvent : NSObject <NSCopying>
@property (nonatomic, copy) NSNumber * _Nonnull reachableNewValue ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
@end

ZGMTR_DEPRECATED("Please use ZGMTRBridgedDeviceBasicInformationClusterReachableChangedEvent", ios(16.1, 17.0), macos(13.0, 14.0), watchos(9.1, 10.0), tvos(16.1, 17.0))
@interface ZGMTRBridgedDeviceBasicClusterReachableChangedEvent : ZGMTRBridgedDeviceBasicInformationClusterReachableChangedEvent
@property (nonatomic, copy) NSNumber * _Nonnull reachableNewValue ZGMTR_DEPRECATED("Please use ZGMTRBridgedDeviceBasicInformationClusterReachableChangedEvent", ios(16.1, 17.0), macos(13.0, 14.0), watchos(9.1, 10.0), tvos(16.1, 17.0));
@end

ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4))
@interface ZGMTRBridgedDeviceBasicInformationClusterActiveChangedEvent : NSObject <NSCopying>
@property (nonatomic, copy) NSNumber * _Nonnull promisedActiveDuration ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));
@end

ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1))
@interface ZGMTRSwitchClusterSwitchLatchedEvent : NSObject <NSCopying>
@property (nonatomic, copy, getter=getNewPosition) NSNumber * _Nonnull newPosition ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));
@end

ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1))
@interface ZGMTRSwitchClusterInitialPressEvent : NSObject <NSCopying>
@property (nonatomic, copy, getter=getNewPosition) NSNumber * _Nonnull newPosition ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));
@end

ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1))
@interface ZGMTRSwitchClusterLongPressEvent : NSObject <NSCopying>
@property (nonatomic, copy, getter=getNewPosition) NSNumber * _Nonnull newPosition ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));
@end

ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1))
@interface ZGMTRSwitchClusterShortReleaseEvent : NSObject <NSCopying>
@property (nonatomic, copy) NSNumber * _Nonnull previousPosition ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));
@end

ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1))
@interface ZGMTRSwitchClusterLongReleaseEvent : NSObject <NSCopying>
@property (nonatomic, copy) NSNumber * _Nonnull previousPosition ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));
@end

ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1))
@interface ZGMTRSwitchClusterMultiPressOngoingEvent : NSObject <NSCopying>
@property (nonatomic, copy, getter=getNewPosition) NSNumber * _Nonnull newPosition ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));
@property (nonatomic, copy) NSNumber * _Nonnull currentNumberOfPressesCounted ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));
@end

ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1))
@interface ZGMTRSwitchClusterMultiPressCompleteEvent : NSObject <NSCopying>
@property (nonatomic, copy) NSNumber * _Nonnull previousPosition ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
@property (nonatomic, copy, getter=getNewPosition) NSNumber * _Nonnull newPosition ZGMTR_DEPRECATED("Please use previousPosition", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
@property (nonatomic, copy) NSNumber * _Nonnull totalNumberOfPressesCounted ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));
@end

ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4))
@interface ZGMTROperationalCredentialsClusterFabricDescriptorStruct : NSObject <NSCopying>
@property (nonatomic, copy) NSData * _Nonnull rootPublicKey ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
@property (nonatomic, copy) NSNumber * _Nonnull vendorID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
@property (nonatomic, copy) NSNumber * _Nonnull vendorId ZGMTR_DEPRECATED("Please use vendorID", ios(16.4, 16.4), macos(13.3, 13.3), watchos(9.4, 9.4), tvos(16.4, 16.4));
@property (nonatomic, copy) NSNumber * _Nonnull fabricID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
@property (nonatomic, copy) NSNumber * _Nonnull fabricId ZGMTR_DEPRECATED("Please use fabricID", ios(16.4, 16.4), macos(13.3, 13.3), watchos(9.4, 9.4), tvos(16.4, 16.4));
@property (nonatomic, copy) NSNumber * _Nonnull nodeID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
@property (nonatomic, copy) NSNumber * _Nonnull nodeId ZGMTR_DEPRECATED("Please use nodeID", ios(16.4, 16.4), macos(13.3, 13.3), watchos(9.4, 9.4), tvos(16.4, 16.4));
@property (nonatomic, copy) NSString * _Nonnull label ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
@property (nonatomic, copy) NSData * _Nullable vidVerificationStatement ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSNumber * _Nonnull fabricIndex ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
@end

ZGMTR_DEPRECATED("Please use ZGMTROperationalCredentialsClusterFabricDescriptorStruct", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
@interface ZGMTROperationalCredentialsClusterFabricDescriptor : ZGMTROperationalCredentialsClusterFabricDescriptorStruct
@property (nonatomic, copy) NSData * _Nonnull rootPublicKey ZGMTR_DEPRECATED("Please use ZGMTROperationalCredentialsClusterFabricDescriptorStruct", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
@property (nonatomic, copy) NSString * _Nonnull label ZGMTR_DEPRECATED("Please use ZGMTROperationalCredentialsClusterFabricDescriptorStruct", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
@property (nonatomic, copy) NSNumber * _Nonnull fabricIndex ZGMTR_DEPRECATED("Please use ZGMTROperationalCredentialsClusterFabricDescriptorStruct", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
@end

ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1))
@interface ZGMTROperationalCredentialsClusterNOCStruct : NSObject <NSCopying>
@property (nonatomic, copy) NSData * _Nonnull noc ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));
@property (nonatomic, copy) NSData * _Nullable icac ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));
@property (nonatomic, copy) NSData * _Nullable vvsc ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSNumber * _Nonnull fabricIndex ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));
@end

ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1))
@interface ZGMTRGroupKeyManagementClusterGroupInfoMapStruct : NSObject <NSCopying>
@property (nonatomic, copy) NSNumber * _Nonnull groupId ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));
@property (nonatomic, copy) NSArray * _Nonnull endpoints ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));
@property (nonatomic, copy) NSString * _Nullable groupName ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));
@property (nonatomic, copy) NSNumber * _Nonnull fabricIndex ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));
@end

ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1))
@interface ZGMTRGroupKeyManagementClusterGroupKeyMapStruct : NSObject <NSCopying>
@property (nonatomic, copy) NSNumber * _Nonnull groupId ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));
@property (nonatomic, copy) NSNumber * _Nonnull groupKeySetID ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));
@property (nonatomic, copy) NSNumber * _Nonnull fabricIndex ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));
@end

ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1))
@interface ZGMTRGroupKeyManagementClusterGroupKeySetStruct : NSObject <NSCopying>
@property (nonatomic, copy) NSNumber * _Nonnull groupKeySetID ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));
@property (nonatomic, copy) NSNumber * _Nonnull groupKeySecurityPolicy ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));
@property (nonatomic, copy) NSData * _Nullable epochKey0 ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));
@property (nonatomic, copy) NSNumber * _Nullable epochStartTime0 ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));
@property (nonatomic, copy) NSData * _Nullable epochKey1 ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));
@property (nonatomic, copy) NSNumber * _Nullable epochStartTime1 ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));
@property (nonatomic, copy) NSData * _Nullable epochKey2 ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));
@property (nonatomic, copy) NSNumber * _Nullable epochStartTime2 ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));
@end

ZGMTR_PROVISIONALLY_AVAILABLE
@interface ZGMTRGroupKeyManagementClusterGroupcastAdoptionStruct : NSObject <NSCopying>
@property (nonatomic, copy) NSNumber * _Nonnull groupcastAdopted ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSNumber * _Nonnull fabricIndex ZGMTR_PROVISIONALLY_AVAILABLE;
@end

ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1))
@interface ZGMTRFixedLabelClusterLabelStruct : NSObject <NSCopying>
@property (nonatomic, copy) NSString * _Nonnull label ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));
@property (nonatomic, copy) NSString * _Nonnull value ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));
@end

ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1))
@interface ZGMTRUserLabelClusterLabelStruct : NSObject <NSCopying>
@property (nonatomic, copy) NSString * _Nonnull label ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));
@property (nonatomic, copy) NSString * _Nonnull value ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));
@end

ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1))
@interface ZGMTRBooleanStateClusterStateChangeEvent : NSObject <NSCopying>
@property (nonatomic, copy) NSNumber * _Nonnull stateValue ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));
@end

ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4))
@interface ZGMTRICDManagementClusterMonitoringRegistrationStruct : NSObject <NSCopying>
@property (nonatomic, copy) NSNumber * _Nonnull checkInNodeID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));
@property (nonatomic, copy) NSNumber * _Nonnull monitoredSubject ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));
@property (nonatomic, copy) NSNumber * _Nonnull clientType ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));
@property (nonatomic, copy) NSNumber * _Nonnull fabricIndex ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));
@end

ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4))
@interface ZGMTROvenCavityOperationalStateClusterErrorStateStruct : NSObject <NSCopying>
@property (nonatomic, copy) NSNumber * _Nonnull errorStateID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));
@property (nonatomic, copy) NSString * _Nullable errorStateLabel ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));
@property (nonatomic, copy) NSString * _Nullable errorStateDetails ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));
@end

ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4))
@interface ZGMTROvenCavityOperationalStateClusterOperationalStateStruct : NSObject <NSCopying>
@property (nonatomic, copy) NSNumber * _Nonnull operationalStateID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));
@property (nonatomic, copy) NSString * _Nullable operationalStateLabel ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));
@end

ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4))
@interface ZGMTROvenCavityOperationalStateClusterOperationalErrorEvent : NSObject <NSCopying>
@property (nonatomic, copy) ZGMTROvenCavityOperationalStateClusterErrorStateStruct * _Nonnull errorState ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));
@end

ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4))
@interface ZGMTROvenCavityOperationalStateClusterOperationCompletionEvent : NSObject <NSCopying>
@property (nonatomic, copy) NSNumber * _Nonnull completionErrorCode ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));
@property (nonatomic, copy) NSNumber * _Nullable totalOperationalTime ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));
@property (nonatomic, copy) NSNumber * _Nullable pausedTime ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));
@end

ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4))
@interface ZGMTROvenModeClusterModeTagStruct : NSObject <NSCopying>
@property (nonatomic, copy) NSNumber * _Nullable mfgCode ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));
@property (nonatomic, copy) NSNumber * _Nonnull value ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));
@end

ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4))
@interface ZGMTROvenModeClusterModeOptionStruct : NSObject <NSCopying>
@property (nonatomic, copy) NSString * _Nonnull label ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));
@property (nonatomic, copy) NSNumber * _Nonnull mode ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));
@property (nonatomic, copy) NSArray * _Nonnull modeTags ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));
@end

ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4))
@interface ZGMTRModeSelectClusterSemanticTagStruct : NSObject <NSCopying>
@property (nonatomic, copy) NSNumber * _Nonnull mfgCode ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
@property (nonatomic, copy) NSNumber * _Nonnull value ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
@end

ZGMTR_DEPRECATED("Please use ZGMTRModeSelectClusterSemanticTagStruct", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
@interface ZGMTRModeSelectClusterSemanticTag : ZGMTRModeSelectClusterSemanticTagStruct
@property (nonatomic, copy) NSNumber * _Nonnull mfgCode ZGMTR_DEPRECATED("Please use ZGMTRModeSelectClusterSemanticTagStruct", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
@property (nonatomic, copy) NSNumber * _Nonnull value ZGMTR_DEPRECATED("Please use ZGMTRModeSelectClusterSemanticTagStruct", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
@end

ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1))
@interface ZGMTRModeSelectClusterModeOptionStruct : NSObject <NSCopying>
@property (nonatomic, copy) NSString * _Nonnull label ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));
@property (nonatomic, copy) NSNumber * _Nonnull mode ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));
@property (nonatomic, copy) NSArray * _Nonnull semanticTags ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));
@end

ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4))
@interface ZGMTRLaundryWasherModeClusterModeTagStruct : NSObject <NSCopying>
@property (nonatomic, copy) NSNumber * _Nullable mfgCode ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));
@property (nonatomic, copy) NSNumber * _Nonnull value ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));
@end

ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4))
@interface ZGMTRLaundryWasherModeClusterModeOptionStruct : NSObject <NSCopying>
@property (nonatomic, copy) NSString * _Nonnull label ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));
@property (nonatomic, copy) NSNumber * _Nonnull mode ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));
@property (nonatomic, copy) NSArray * _Nonnull modeTags ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));
@end

ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4))
@interface ZGMTRRefrigeratorAndTemperatureControlledCabinetModeClusterModeTagStruct : NSObject <NSCopying>
@property (nonatomic, copy) NSNumber * _Nullable mfgCode ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));
@property (nonatomic, copy) NSNumber * _Nonnull value ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));
@end

ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4))
@interface ZGMTRRefrigeratorAndTemperatureControlledCabinetModeClusterModeOptionStruct : NSObject <NSCopying>
@property (nonatomic, copy) NSString * _Nonnull label ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));
@property (nonatomic, copy) NSNumber * _Nonnull mode ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));
@property (nonatomic, copy) NSArray * _Nonnull modeTags ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));
@end

ZGMTR_AVAILABLE(ios(17.4), macos(14.4), watchos(10.4), tvos(17.4))
@interface ZGMTRRVCRunModeClusterModeTagStruct : NSObject <NSCopying>
@property (nonatomic, copy) NSNumber * _Nullable mfgCode ZGMTR_AVAILABLE(ios(17.4), macos(14.4), watchos(10.4), tvos(17.4));
@property (nonatomic, copy) NSNumber * _Nonnull value ZGMTR_AVAILABLE(ios(17.4), macos(14.4), watchos(10.4), tvos(17.4));
@end

ZGMTR_AVAILABLE(ios(17.4), macos(14.4), watchos(10.4), tvos(17.4))
@interface ZGMTRRVCRunModeClusterModeOptionStruct : NSObject <NSCopying>
@property (nonatomic, copy) NSString * _Nonnull label ZGMTR_AVAILABLE(ios(17.4), macos(14.4), watchos(10.4), tvos(17.4));
@property (nonatomic, copy) NSNumber * _Nonnull mode ZGMTR_AVAILABLE(ios(17.4), macos(14.4), watchos(10.4), tvos(17.4));
@property (nonatomic, copy) NSArray * _Nonnull modeTags ZGMTR_AVAILABLE(ios(17.4), macos(14.4), watchos(10.4), tvos(17.4));
@end

ZGMTR_AVAILABLE(ios(17.4), macos(14.4), watchos(10.4), tvos(17.4))
@interface ZGMTRRVCCleanModeClusterModeTagStruct : NSObject <NSCopying>
@property (nonatomic, copy) NSNumber * _Nullable mfgCode ZGMTR_AVAILABLE(ios(17.4), macos(14.4), watchos(10.4), tvos(17.4));
@property (nonatomic, copy) NSNumber * _Nonnull value ZGMTR_AVAILABLE(ios(17.4), macos(14.4), watchos(10.4), tvos(17.4));
@end

ZGMTR_AVAILABLE(ios(17.4), macos(14.4), watchos(10.4), tvos(17.4))
@interface ZGMTRRVCCleanModeClusterModeOptionStruct : NSObject <NSCopying>
@property (nonatomic, copy) NSString * _Nonnull label ZGMTR_AVAILABLE(ios(17.4), macos(14.4), watchos(10.4), tvos(17.4));
@property (nonatomic, copy) NSNumber * _Nonnull mode ZGMTR_AVAILABLE(ios(17.4), macos(14.4), watchos(10.4), tvos(17.4));
@property (nonatomic, copy) NSArray * _Nonnull modeTags ZGMTR_AVAILABLE(ios(17.4), macos(14.4), watchos(10.4), tvos(17.4));
@end

ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4))
@interface ZGMTRRefrigeratorAlarmClusterNotifyEvent : NSObject <NSCopying>
@property (nonatomic, copy) NSNumber * _Nonnull active ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));
@property (nonatomic, copy) NSNumber * _Nonnull inactive ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));
@property (nonatomic, copy) NSNumber * _Nonnull state ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));
@property (nonatomic, copy) NSNumber * _Nonnull mask ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));
@end

ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4))
@interface ZGMTRDishwasherModeClusterModeTagStruct : NSObject <NSCopying>
@property (nonatomic, copy) NSNumber * _Nullable mfgCode ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));
@property (nonatomic, copy) NSNumber * _Nonnull value ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));
@end

ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4))
@interface ZGMTRDishwasherModeClusterModeOptionStruct : NSObject <NSCopying>
@property (nonatomic, copy) NSString * _Nonnull label ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));
@property (nonatomic, copy) NSNumber * _Nonnull mode ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));
@property (nonatomic, copy) NSArray * _Nonnull modeTags ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));
@end

ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6))
@interface ZGMTRSmokeCOAlarmClusterSmokeAlarmEvent : NSObject <NSCopying>
@property (nonatomic, copy) NSNumber * _Nonnull alarmSeverityLevel ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6));
@end

ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6))
@interface ZGMTRSmokeCOAlarmClusterCOAlarmEvent : NSObject <NSCopying>
@property (nonatomic, copy) NSNumber * _Nonnull alarmSeverityLevel ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6));
@end

ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6))
@interface ZGMTRSmokeCOAlarmClusterLowBatteryEvent : NSObject <NSCopying>
@property (nonatomic, copy) NSNumber * _Nonnull alarmSeverityLevel ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6));
@end

ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6))
@interface ZGMTRSmokeCOAlarmClusterHardwareFaultEvent : NSObject <NSCopying>
@end

ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6))
@interface ZGMTRSmokeCOAlarmClusterEndOfServiceEvent : NSObject <NSCopying>
@end

ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6))
@interface ZGMTRSmokeCOAlarmClusterSelfTestCompleteEvent : NSObject <NSCopying>
@end

ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6))
@interface ZGMTRSmokeCOAlarmClusterAlarmMutedEvent : NSObject <NSCopying>
@end

ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6))
@interface ZGMTRSmokeCOAlarmClusterMuteEndedEvent : NSObject <NSCopying>
@end

ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6))
@interface ZGMTRSmokeCOAlarmClusterInterconnectSmokeAlarmEvent : NSObject <NSCopying>
@property (nonatomic, copy) NSNumber * _Nonnull alarmSeverityLevel ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6));
@end

ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6))
@interface ZGMTRSmokeCOAlarmClusterInterconnectCOAlarmEvent : NSObject <NSCopying>
@property (nonatomic, copy) NSNumber * _Nonnull alarmSeverityLevel ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6));
@end

ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6))
@interface ZGMTRSmokeCOAlarmClusterAllClearEvent : NSObject <NSCopying>
@end

ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4))
@interface ZGMTRDishwasherAlarmClusterNotifyEvent : NSObject <NSCopying>
@property (nonatomic, copy) NSNumber * _Nonnull active ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));
@property (nonatomic, copy) NSNumber * _Nonnull inactive ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));
@property (nonatomic, copy) NSNumber * _Nonnull state ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));
@property (nonatomic, copy) NSNumber * _Nonnull mask ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));
@end

ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4))
@interface ZGMTRMicrowaveOvenModeClusterModeTagStruct : NSObject <NSCopying>
@property (nonatomic, copy) NSNumber * _Nullable mfgCode ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));
@property (nonatomic, copy) NSNumber * _Nonnull value ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));
@end

ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4))
@interface ZGMTRMicrowaveOvenModeClusterModeOptionStruct : NSObject <NSCopying>
@property (nonatomic, copy) NSString * _Nonnull label ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));
@property (nonatomic, copy) NSNumber * _Nonnull mode ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));
@property (nonatomic, copy) NSArray * _Nonnull modeTags ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));
@end

ZGMTR_AVAILABLE(ios(17.4), macos(14.4), watchos(10.4), tvos(17.4))
@interface ZGMTROperationalStateClusterErrorStateStruct : NSObject <NSCopying>
@property (nonatomic, copy) NSNumber * _Nonnull errorStateID ZGMTR_AVAILABLE(ios(17.4), macos(14.4), watchos(10.4), tvos(17.4));
@property (nonatomic, copy) NSString * _Nullable errorStateLabel ZGMTR_AVAILABLE(ios(17.4), macos(14.4), watchos(10.4), tvos(17.4));
@property (nonatomic, copy) NSString * _Nullable errorStateDetails ZGMTR_AVAILABLE(ios(17.4), macos(14.4), watchos(10.4), tvos(17.4));
@end

ZGMTR_AVAILABLE(ios(17.4), macos(14.4), watchos(10.4), tvos(17.4))
@interface ZGMTROperationalStateClusterOperationalStateStruct : NSObject <NSCopying>
@property (nonatomic, copy) NSNumber * _Nonnull operationalStateID ZGMTR_AVAILABLE(ios(17.4), macos(14.4), watchos(10.4), tvos(17.4));
@property (nonatomic, copy) NSString * _Nullable operationalStateLabel ZGMTR_AVAILABLE(ios(17.4), macos(14.4), watchos(10.4), tvos(17.4));
@end

ZGMTR_AVAILABLE(ios(17.4), macos(14.4), watchos(10.4), tvos(17.4))
@interface ZGMTROperationalStateClusterOperationalErrorEvent : NSObject <NSCopying>
@property (nonatomic, copy) ZGMTROperationalStateClusterErrorStateStruct * _Nonnull errorState ZGMTR_AVAILABLE(ios(17.4), macos(14.4), watchos(10.4), tvos(17.4));
@end

ZGMTR_AVAILABLE(ios(17.4), macos(14.4), watchos(10.4), tvos(17.4))
@interface ZGMTROperationalStateClusterOperationCompletionEvent : NSObject <NSCopying>
@property (nonatomic, copy) NSNumber * _Nonnull completionErrorCode ZGMTR_AVAILABLE(ios(17.4), macos(14.4), watchos(10.4), tvos(17.4));
@property (nonatomic, copy) NSNumber * _Nullable totalOperationalTime ZGMTR_AVAILABLE(ios(17.4), macos(14.4), watchos(10.4), tvos(17.4));
@property (nonatomic, copy) NSNumber * _Nullable pausedTime ZGMTR_AVAILABLE(ios(17.4), macos(14.4), watchos(10.4), tvos(17.4));
@end

ZGMTR_AVAILABLE(ios(17.4), macos(14.4), watchos(10.4), tvos(17.4))
@interface ZGMTRRVCOperationalStateClusterErrorStateStruct : NSObject <NSCopying>
@property (nonatomic, copy) NSNumber * _Nonnull errorStateID ZGMTR_AVAILABLE(ios(17.4), macos(14.4), watchos(10.4), tvos(17.4));
@property (nonatomic, copy) NSString * _Nullable errorStateLabel ZGMTR_AVAILABLE(ios(17.4), macos(14.4), watchos(10.4), tvos(17.4));
@property (nonatomic, copy) NSString * _Nullable errorStateDetails ZGMTR_AVAILABLE(ios(17.4), macos(14.4), watchos(10.4), tvos(17.4));
@end

ZGMTR_AVAILABLE(ios(17.4), macos(14.4), watchos(10.4), tvos(17.4))
@interface ZGMTRRVCOperationalStateClusterOperationalStateStruct : NSObject <NSCopying>
@property (nonatomic, copy) NSNumber * _Nonnull operationalStateID ZGMTR_AVAILABLE(ios(17.4), macos(14.4), watchos(10.4), tvos(17.4));
@property (nonatomic, copy) NSString * _Nullable operationalStateLabel ZGMTR_AVAILABLE(ios(17.4), macos(14.4), watchos(10.4), tvos(17.4));
@end

ZGMTR_AVAILABLE(ios(17.4), macos(14.4), watchos(10.4), tvos(17.4))
@interface ZGMTRRVCOperationalStateClusterOperationalErrorEvent : NSObject <NSCopying>
@property (nonatomic, copy) ZGMTRRVCOperationalStateClusterErrorStateStruct * _Nonnull errorState ZGMTR_AVAILABLE(ios(17.4), macos(14.4), watchos(10.4), tvos(17.4));
@end

ZGMTR_AVAILABLE(ios(17.4), macos(14.4), watchos(10.4), tvos(17.4))
@interface ZGMTRRVCOperationalStateClusterOperationCompletionEvent : NSObject <NSCopying>
@property (nonatomic, copy) NSNumber * _Nonnull completionErrorCode ZGMTR_AVAILABLE(ios(17.4), macos(14.4), watchos(10.4), tvos(17.4));
@property (nonatomic, copy) NSNumber * _Nullable totalOperationalTime ZGMTR_AVAILABLE(ios(17.4), macos(14.4), watchos(10.4), tvos(17.4));
@property (nonatomic, copy) NSNumber * _Nullable pausedTime ZGMTR_AVAILABLE(ios(17.4), macos(14.4), watchos(10.4), tvos(17.4));
@end

ZGMTR_PROVISIONALLY_AVAILABLE
@interface ZGMTRScenesManagementClusterAttributeValuePairStruct : NSObject <NSCopying>
@property (nonatomic, copy) NSNumber * _Nonnull attributeID ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSNumber * _Nullable valueUnsigned8 ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSNumber * _Nullable valueSigned8 ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSNumber * _Nullable valueUnsigned16 ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSNumber * _Nullable valueSigned16 ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSNumber * _Nullable valueUnsigned32 ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSNumber * _Nullable valueSigned32 ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSNumber * _Nullable valueUnsigned64 ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSNumber * _Nullable valueSigned64 ZGMTR_PROVISIONALLY_AVAILABLE;
@end

ZGMTR_PROVISIONALLY_AVAILABLE
@interface ZGMTRScenesManagementClusterExtensionFieldSetStruct : NSObject <NSCopying>
@property (nonatomic, copy) NSNumber * _Nonnull clusterID ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSArray * _Nonnull attributeValueList ZGMTR_PROVISIONALLY_AVAILABLE;
@end

ZGMTR_PROVISIONALLY_AVAILABLE
@interface ZGMTRScenesManagementClusterSceneInfoStruct : NSObject <NSCopying>
@property (nonatomic, copy) NSNumber * _Nonnull sceneCount ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSNumber * _Nonnull currentScene ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSNumber * _Nonnull currentGroup ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSNumber * _Nonnull sceneValid ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSNumber * _Nonnull remainingCapacity ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSNumber * _Nonnull fabricIndex ZGMTR_PROVISIONALLY_AVAILABLE;
@end

ZGMTR_PROVISIONALLY_AVAILABLE
@interface ZGMTRGroupcastClusterMembershipStruct : NSObject <NSCopying>
@property (nonatomic, copy) NSNumber * _Nonnull groupID ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSArray * _Nullable endpoints ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSNumber * _Nonnull keySetID ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSNumber * _Nullable hasAuxiliaryACL ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSNumber * _Nonnull mcastAddrPolicy ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSNumber * _Nonnull fabricIndex ZGMTR_PROVISIONALLY_AVAILABLE;
@end

ZGMTR_PROVISIONALLY_AVAILABLE
@interface ZGMTRGroupcastClusterGroupcastTestingEvent : NSObject <NSCopying>
@property (nonatomic, copy) NSData * _Nullable sourceIpAddress ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSData * _Nullable destinationIpAddress ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSNumber * _Nullable groupID ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSNumber * _Nullable endpointID ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSNumber * _Nullable clusterID ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSNumber * _Nullable elementID ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSNumber * _Nullable accessAllowed ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSNumber * _Nonnull groupcastTestResult ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSNumber * _Nonnull fabricIndex ZGMTR_PROVISIONALLY_AVAILABLE;
@end

ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6))
@interface ZGMTRHEPAFilterMonitoringClusterReplacementProductStruct : NSObject <NSCopying>
@property (nonatomic, copy) NSNumber * _Nonnull productIdentifierType ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6));
@property (nonatomic, copy) NSString * _Nonnull productIdentifierValue ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6));
@end

ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6))
@interface ZGMTRActivatedCarbonFilterMonitoringClusterReplacementProductStruct : NSObject <NSCopying>
@property (nonatomic, copy) NSNumber * _Nonnull productIdentifierType ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6));
@property (nonatomic, copy) NSString * _Nonnull productIdentifierValue ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6));
@end

ZGMTR_PROVISIONALLY_AVAILABLE
@interface ZGMTRWaterTankLevelMonitoringClusterReplacementProductStruct : NSObject <NSCopying>
@property (nonatomic, copy) NSNumber * _Nonnull productIdentifierType ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSString * _Nonnull productIdentifierValue ZGMTR_PROVISIONALLY_AVAILABLE;
@end

ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6))
@interface ZGMTRBooleanStateConfigurationClusterAlarmsStateChangedEvent : NSObject <NSCopying>
@property (nonatomic, copy) NSNumber * _Nonnull alarmsActive ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6));
@property (nonatomic, copy) NSNumber * _Nullable alarmsSuppressed ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6));
@end

ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6))
@interface ZGMTRBooleanStateConfigurationClusterSensorFaultEvent : NSObject <NSCopying>
@property (nonatomic, copy) NSNumber * _Nonnull sensorFault ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6));
@end

ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6))
@interface ZGMTRValveConfigurationAndControlClusterValveStateChangedEvent : NSObject <NSCopying>
@property (nonatomic, copy) NSNumber * _Nonnull valveState ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6));
@property (nonatomic, copy) NSNumber * _Nullable valveLevel ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6));
@end

ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6))
@interface ZGMTRValveConfigurationAndControlClusterValveFaultEvent : NSObject <NSCopying>
@property (nonatomic, copy) NSNumber * _Nonnull valveFault ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6));
@end

ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6))
@interface ZGMTRElectricalPowerMeasurementClusterMeasurementAccuracyRangeStruct : NSObject <NSCopying>
@property (nonatomic, copy) NSNumber * _Nonnull rangeMin ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6));
@property (nonatomic, copy) NSNumber * _Nonnull rangeMax ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6));
@property (nonatomic, copy) NSNumber * _Nullable percentMax ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6));
@property (nonatomic, copy) NSNumber * _Nullable percentMin ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6));
@property (nonatomic, copy) NSNumber * _Nullable percentTypical ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6));
@property (nonatomic, copy) NSNumber * _Nullable fixedMax ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6));
@property (nonatomic, copy) NSNumber * _Nullable fixedMin ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6));
@property (nonatomic, copy) NSNumber * _Nullable fixedTypical ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6));
@end

ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6))
@interface ZGMTRElectricalPowerMeasurementClusterMeasurementAccuracyStruct : NSObject <NSCopying>
@property (nonatomic, copy) NSNumber * _Nonnull measurementType ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6));
@property (nonatomic, copy) NSNumber * _Nonnull measured ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6));
@property (nonatomic, copy) NSNumber * _Nonnull minMeasuredValue ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6));
@property (nonatomic, copy) NSNumber * _Nonnull maxMeasuredValue ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6));
@property (nonatomic, copy) NSArray * _Nonnull accuracyRanges ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6));
@end

ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6))
@interface ZGMTRElectricalPowerMeasurementClusterHarmonicMeasurementStruct : NSObject <NSCopying>
@property (nonatomic, copy) NSNumber * _Nonnull order ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6));
@property (nonatomic, copy) NSNumber * _Nullable measurement ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6));
@end

ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6))
@interface ZGMTRElectricalPowerMeasurementClusterMeasurementRangeStruct : NSObject <NSCopying>
@property (nonatomic, copy) NSNumber * _Nonnull measurementType ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6));
@property (nonatomic, copy) NSNumber * _Nonnull min ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6));
@property (nonatomic, copy) NSNumber * _Nonnull max ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6));
@property (nonatomic, copy) NSNumber * _Nullable startTimestamp ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6));
@property (nonatomic, copy) NSNumber * _Nullable endTimestamp ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6));
@property (nonatomic, copy) NSNumber * _Nullable minTimestamp ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6));
@property (nonatomic, copy) NSNumber * _Nullable maxTimestamp ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6));
@property (nonatomic, copy) NSNumber * _Nullable startSystime ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6));
@property (nonatomic, copy) NSNumber * _Nullable endSystime ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6));
@property (nonatomic, copy) NSNumber * _Nullable minSystime ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6));
@property (nonatomic, copy) NSNumber * _Nullable maxSystime ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6));
@end

ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6))
@interface ZGMTRElectricalPowerMeasurementClusterMeasurementPeriodRangesEvent : NSObject <NSCopying>
@property (nonatomic, copy) NSArray * _Nonnull ranges ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6));
@end

ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4))
@interface ZGMTRElectricalEnergyMeasurementClusterMeasurementAccuracyRangeStruct : NSObject <NSCopying>
@property (nonatomic, copy) NSNumber * _Nonnull rangeMin ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));
@property (nonatomic, copy) NSNumber * _Nonnull rangeMax ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));
@property (nonatomic, copy) NSNumber * _Nullable percentMax ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));
@property (nonatomic, copy) NSNumber * _Nullable percentMin ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));
@property (nonatomic, copy) NSNumber * _Nullable percentTypical ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));
@property (nonatomic, copy) NSNumber * _Nullable fixedMax ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));
@property (nonatomic, copy) NSNumber * _Nullable fixedMin ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));
@property (nonatomic, copy) NSNumber * _Nullable fixedTypical ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));
@end

ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6))
@interface ZGMTRElectricalEnergyMeasurementClusterMeasurementAccuracyStruct : NSObject <NSCopying>
@property (nonatomic, copy) NSNumber * _Nonnull measurementType ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6));
@property (nonatomic, copy) NSNumber * _Nonnull measured ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6));
@property (nonatomic, copy) NSNumber * _Nonnull minMeasuredValue ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6));
@property (nonatomic, copy) NSNumber * _Nonnull maxMeasuredValue ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6));
@property (nonatomic, copy) NSArray * _Nonnull accuracyRanges ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6));
@end

ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6))
@interface ZGMTRElectricalEnergyMeasurementClusterCumulativeEnergyResetStruct : NSObject <NSCopying>
@property (nonatomic, copy) NSNumber * _Nullable importedResetTimestamp ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6));
@property (nonatomic, copy) NSNumber * _Nullable exportedResetTimestamp ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6));
@property (nonatomic, copy) NSNumber * _Nullable importedResetSystime ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6));
@property (nonatomic, copy) NSNumber * _Nullable exportedResetSystime ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6));
@end

ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6))
@interface ZGMTRElectricalEnergyMeasurementClusterEnergyMeasurementStruct : NSObject <NSCopying>
@property (nonatomic, copy) NSNumber * _Nonnull energy ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6));
@property (nonatomic, copy) NSNumber * _Nullable startTimestamp ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6));
@property (nonatomic, copy) NSNumber * _Nullable endTimestamp ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6));
@property (nonatomic, copy) NSNumber * _Nullable startSystime ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6));
@property (nonatomic, copy) NSNumber * _Nullable endSystime ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6));
@property (nonatomic, copy) NSNumber * _Nullable apparentEnergy ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSNumber * _Nullable reactiveEnergy ZGMTR_PROVISIONALLY_AVAILABLE;
@end

ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6))
@interface ZGMTRElectricalEnergyMeasurementClusterCumulativeEnergyMeasuredEvent : NSObject <NSCopying>
@property (nonatomic, copy) ZGMTRElectricalEnergyMeasurementClusterEnergyMeasurementStruct * _Nullable energyImported ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6));
@property (nonatomic, copy) ZGMTRElectricalEnergyMeasurementClusterEnergyMeasurementStruct * _Nullable energyExported ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6));
@end

ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6))
@interface ZGMTRElectricalEnergyMeasurementClusterPeriodicEnergyMeasuredEvent : NSObject <NSCopying>
@property (nonatomic, copy) ZGMTRElectricalEnergyMeasurementClusterEnergyMeasurementStruct * _Nullable energyImported ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6));
@property (nonatomic, copy) ZGMTRElectricalEnergyMeasurementClusterEnergyMeasurementStruct * _Nullable energyExported ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6));
@end

ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4))
@interface ZGMTRWaterHeaterManagementClusterWaterHeaterBoostInfoStruct : NSObject <NSCopying>
@property (nonatomic, copy) NSNumber * _Nonnull duration ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));
@property (nonatomic, copy) NSNumber * _Nullable oneShot ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));
@property (nonatomic, copy) NSNumber * _Nullable emergencyBoost ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));
@property (nonatomic, copy) NSNumber * _Nullable temporarySetpoint ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));
@property (nonatomic, copy) NSNumber * _Nullable targetPercentage ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));
@property (nonatomic, copy) NSNumber * _Nullable targetReheat ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));
@end

ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4))
@interface ZGMTRWaterHeaterManagementClusterBoostStartedEvent : NSObject <NSCopying>
@property (nonatomic, copy) ZGMTRWaterHeaterManagementClusterWaterHeaterBoostInfoStruct * _Nonnull boostInfo ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));
@end

ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4))
@interface ZGMTRWaterHeaterManagementClusterBoostEndedEvent : NSObject <NSCopying>
@end

ZGMTR_PROVISIONALLY_AVAILABLE
@interface ZGMTRCommodityPriceClusterCommodityPriceComponentStruct : NSObject <NSCopying>
@property (nonatomic, copy) NSNumber * _Nonnull price ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSNumber * _Nonnull source ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSString * _Nullable descriptionString ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSNumber * _Nullable tariffComponentID ZGMTR_PROVISIONALLY_AVAILABLE;
@end

ZGMTR_PROVISIONALLY_AVAILABLE
@interface ZGMTRCommodityPriceClusterCommodityPriceStruct : NSObject <NSCopying>
@property (nonatomic, copy) NSNumber * _Nonnull periodStart ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSNumber * _Nullable periodEnd ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSNumber * _Nullable price ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSNumber * _Nullable priceLevel ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSString * _Nullable descriptionString ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSArray * _Nullable components ZGMTR_PROVISIONALLY_AVAILABLE;
@end

ZGMTR_PROVISIONALLY_AVAILABLE
@interface ZGMTRCommodityPriceClusterPriceChangeEvent : NSObject <NSCopying>
@property (nonatomic, copy) ZGMTRCommodityPriceClusterCommodityPriceStruct * _Nullable currentPrice ZGMTR_PROVISIONALLY_AVAILABLE;
@end

ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4))
@interface ZGMTRMessagesClusterMessageResponseOptionStruct : NSObject <NSCopying>
@property (nonatomic, copy) NSNumber * _Nullable messageResponseID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));
@property (nonatomic, copy) NSString * _Nullable label ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));
@end

ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4))
@interface ZGMTRMessagesClusterMessageStruct : NSObject <NSCopying>
@property (nonatomic, copy) NSData * _Nonnull messageID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));
@property (nonatomic, copy) NSNumber * _Nonnull priority ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));
@property (nonatomic, copy) NSNumber * _Nonnull messageControl ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));
@property (nonatomic, copy) NSNumber * _Nullable startTime ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));
@property (nonatomic, copy) NSNumber * _Nullable duration ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));
@property (nonatomic, copy) NSString * _Nonnull messageText ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));
@property (nonatomic, copy) NSArray * _Nullable responses ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));
@end

ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4))
@interface ZGMTRMessagesClusterMessageQueuedEvent : NSObject <NSCopying>
@property (nonatomic, copy) NSData * _Nonnull messageID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));
@end

ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4))
@interface ZGMTRMessagesClusterMessagePresentedEvent : NSObject <NSCopying>
@property (nonatomic, copy) NSData * _Nonnull messageID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));
@end

ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4))
@interface ZGMTRMessagesClusterMessageCompleteEvent : NSObject <NSCopying>
@property (nonatomic, copy) NSData * _Nonnull messageID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));
@property (nonatomic, copy) NSNumber * _Nullable responseID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));
@property (nonatomic, copy) NSString * _Nullable reply ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));
@property (nonatomic, copy) NSNumber * _Nullable futureMessagesPreference ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));
@end

ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4))
@interface ZGMTRDeviceEnergyManagementClusterCostStruct : NSObject <NSCopying>
@property (nonatomic, copy) NSNumber * _Nonnull costType ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));
@property (nonatomic, copy) NSNumber * _Nonnull value ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));
@property (nonatomic, copy) NSNumber * _Nonnull decimalPoints ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));
@property (nonatomic, copy) NSNumber * _Nullable currency ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));
@end

ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4))
@interface ZGMTRDeviceEnergyManagementClusterPowerAdjustStruct : NSObject <NSCopying>
@property (nonatomic, copy) NSNumber * _Nonnull minPower ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));
@property (nonatomic, copy) NSNumber * _Nonnull maxPower ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));
@property (nonatomic, copy) NSNumber * _Nonnull minDuration ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));
@property (nonatomic, copy) NSNumber * _Nonnull maxDuration ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));
@end

ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4))
@interface ZGMTRDeviceEnergyManagementClusterPowerAdjustCapabilityStruct : NSObject <NSCopying>
@property (nonatomic, copy) NSArray * _Nullable powerAdjustCapability ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));
@property (nonatomic, copy) NSNumber * _Nonnull cause ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));
@end

ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4))
@interface ZGMTRDeviceEnergyManagementClusterSlotStruct : NSObject <NSCopying>
@property (nonatomic, copy) NSNumber * _Nonnull minDuration ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));
@property (nonatomic, copy) NSNumber * _Nonnull maxDuration ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));
@property (nonatomic, copy) NSNumber * _Nonnull defaultDuration ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));
@property (nonatomic, copy) NSNumber * _Nonnull elapsedSlotTime ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));
@property (nonatomic, copy) NSNumber * _Nonnull remainingSlotTime ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));
@property (nonatomic, copy) NSNumber * _Nullable slotIsPausable ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));
@property (nonatomic, copy) NSNumber * _Nullable minPauseDuration ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));
@property (nonatomic, copy) NSNumber * _Nullable maxPauseDuration ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));
@property (nonatomic, copy) NSNumber * _Nullable manufacturerESAState ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));
@property (nonatomic, copy) NSNumber * _Nullable nominalPower ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));
@property (nonatomic, copy) NSNumber * _Nullable minPower ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));
@property (nonatomic, copy) NSNumber * _Nullable maxPower ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));
@property (nonatomic, copy) NSNumber * _Nullable nominalEnergy ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));
@property (nonatomic, copy) NSArray * _Nullable costs ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));
@property (nonatomic, copy) NSNumber * _Nullable minPowerAdjustment ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));
@property (nonatomic, copy) NSNumber * _Nullable maxPowerAdjustment ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));
@property (nonatomic, copy) NSNumber * _Nullable minDurationAdjustment ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));
@property (nonatomic, copy) NSNumber * _Nullable maxDurationAdjustment ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));
@end

ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4))
@interface ZGMTRDeviceEnergyManagementClusterForecastStruct : NSObject <NSCopying>
@property (nonatomic, copy) NSNumber * _Nonnull forecastID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));
@property (nonatomic, copy) NSNumber * _Nullable activeSlotNumber ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));
@property (nonatomic, copy) NSNumber * _Nonnull startTime ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));
@property (nonatomic, copy) NSNumber * _Nonnull endTime ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));
@property (nonatomic, copy) NSNumber * _Nullable earliestStartTime ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));
@property (nonatomic, copy) NSNumber * _Nullable latestEndTime ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));
@property (nonatomic, copy) NSNumber * _Nonnull isPausable ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));
@property (nonatomic, copy) NSArray * _Nonnull slots ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));
@property (nonatomic, copy) NSNumber * _Nonnull forecastUpdateReason ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));
@end

ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4))
@interface ZGMTRDeviceEnergyManagementClusterConstraintsStruct : NSObject <NSCopying>
@property (nonatomic, copy) NSNumber * _Nonnull startTime ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));
@property (nonatomic, copy) NSNumber * _Nonnull duration ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));
@property (nonatomic, copy) NSNumber * _Nullable nominalPower ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));
@property (nonatomic, copy) NSNumber * _Nullable maximumEnergy ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));
@property (nonatomic, copy) NSNumber * _Nullable loadControl ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));
@end

ZGMTR_PROVISIONALLY_AVAILABLE
@interface ZGMTRDeviceEnergyManagementClusterPowerRangeAdjustStruct : NSObject <NSCopying>
@property (nonatomic, copy) NSNumber * _Nullable minPower ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSNumber * _Nullable maxPower ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSNumber * _Nonnull cause ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSNumber * _Nonnull endTime ZGMTR_PROVISIONALLY_AVAILABLE;
@end

ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4))
@interface ZGMTRDeviceEnergyManagementClusterSlotAdjustmentStruct : NSObject <NSCopying>
@property (nonatomic, copy) NSNumber * _Nonnull slotIndex ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));
@property (nonatomic, copy) NSNumber * _Nullable nominalPower ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));
@property (nonatomic, copy) NSNumber * _Nonnull duration ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));
@end

ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4))
@interface ZGMTRDeviceEnergyManagementClusterPowerAdjustStartEvent : NSObject <NSCopying>
@end

ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4))
@interface ZGMTRDeviceEnergyManagementClusterPowerAdjustEndEvent : NSObject <NSCopying>
@property (nonatomic, copy) NSNumber * _Nonnull cause ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));
@property (nonatomic, copy) NSNumber * _Nonnull duration ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));
@property (nonatomic, copy) NSNumber * _Nonnull energyUse ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));
@end

ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4))
@interface ZGMTRDeviceEnergyManagementClusterPausedEvent : NSObject <NSCopying>
@end

ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4))
@interface ZGMTRDeviceEnergyManagementClusterResumedEvent : NSObject <NSCopying>
@property (nonatomic, copy) NSNumber * _Nonnull cause ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));
@end

ZGMTR_PROVISIONALLY_AVAILABLE
@interface ZGMTRDeviceEnergyManagementClusterPowerRangeAdjustStartEvent : NSObject <NSCopying>
@property (nonatomic, copy) ZGMTRDeviceEnergyManagementClusterPowerRangeAdjustStruct * _Nonnull adjustment ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSNumber * _Nonnull duration ZGMTR_PROVISIONALLY_AVAILABLE;
@end

ZGMTR_PROVISIONALLY_AVAILABLE
@interface ZGMTRDeviceEnergyManagementClusterPowerRangeAdjustEndEvent : NSObject <NSCopying>
@property (nonatomic, copy) NSNumber * _Nonnull cause ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSNumber * _Nonnull duration ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSNumber * _Nonnull energyUse ZGMTR_PROVISIONALLY_AVAILABLE;
@end

ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4))
@interface ZGMTREnergyEVSEClusterChargingTargetStruct : NSObject <NSCopying>
@property (nonatomic, copy) NSNumber * _Nonnull targetTimeMinutesPastMidnight ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));
@property (nonatomic, copy) NSNumber * _Nullable targetSoC ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));
@property (nonatomic, copy) NSNumber * _Nullable addedEnergy ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));
@end

ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4))
@interface ZGMTREnergyEVSEClusterChargingTargetScheduleStruct : NSObject <NSCopying>
@property (nonatomic, copy) NSNumber * _Nonnull dayOfWeekForSequence ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));
@property (nonatomic, copy) NSArray * _Nonnull chargingTargets ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));
@end

ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4))
@interface ZGMTREnergyEVSEClusterEVConnectedEvent : NSObject <NSCopying>
@property (nonatomic, copy) NSNumber * _Nonnull sessionID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));
@end

ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4))
@interface ZGMTREnergyEVSEClusterEVNotDetectedEvent : NSObject <NSCopying>
@property (nonatomic, copy) NSNumber * _Nonnull sessionID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));
@property (nonatomic, copy) NSNumber * _Nonnull state ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));
@property (nonatomic, copy) NSNumber * _Nonnull sessionDuration ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));
@property (nonatomic, copy) NSNumber * _Nonnull sessionEnergyCharged ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));
@property (nonatomic, copy) NSNumber * _Nullable sessionEnergyDischarged ZGMTR_PROVISIONALLY_AVAILABLE;
@end

ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4))
@interface ZGMTREnergyEVSEClusterEnergyTransferStartedEvent : NSObject <NSCopying>
@property (nonatomic, copy) NSNumber * _Nonnull sessionID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));
@property (nonatomic, copy) NSNumber * _Nonnull state ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));
@property (nonatomic, copy) NSNumber * _Nonnull maximumCurrent ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));
@property (nonatomic, copy) NSNumber * _Nullable maximumDischargeCurrent ZGMTR_PROVISIONALLY_AVAILABLE;
@end

ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4))
@interface ZGMTREnergyEVSEClusterEnergyTransferStoppedEvent : NSObject <NSCopying>
@property (nonatomic, copy) NSNumber * _Nonnull sessionID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));
@property (nonatomic, copy) NSNumber * _Nonnull state ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));
@property (nonatomic, copy) NSNumber * _Nonnull reason ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));
@property (nonatomic, copy) NSNumber * _Nonnull energyTransferred ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));
@property (nonatomic, copy) NSNumber * _Nullable energyDischarged ZGMTR_PROVISIONALLY_AVAILABLE;
@end

ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4))
@interface ZGMTREnergyEVSEClusterFaultEvent : NSObject <NSCopying>
@property (nonatomic, copy) NSNumber * _Nullable sessionID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));
@property (nonatomic, copy) NSNumber * _Nonnull state ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));
@property (nonatomic, copy) NSNumber * _Nonnull faultStatePreviousState ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));
@property (nonatomic, copy) NSNumber * _Nonnull faultStateCurrentState ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));
@end

ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4))
@interface ZGMTREnergyEVSEClusterRFIDEvent : NSObject <NSCopying>
@property (nonatomic, copy) NSData * _Nonnull uid ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));
@end

ZGMTR_PROVISIONALLY_AVAILABLE
@interface ZGMTREnergyPreferenceClusterBalanceStruct : NSObject <NSCopying>
@property (nonatomic, copy) NSNumber * _Nonnull step ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSString * _Nullable label ZGMTR_PROVISIONALLY_AVAILABLE;
@end

ZGMTR_PROVISIONALLY_AVAILABLE
@interface ZGMTRPowerTopologyClusterCircuitNodeStruct : NSObject <NSCopying>
@property (nonatomic, copy) NSNumber * _Nonnull node ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSNumber * _Nullable endpoint ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSString * _Nullable label ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSNumber * _Nonnull fabricIndex ZGMTR_PROVISIONALLY_AVAILABLE;
@end

ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4))
@interface ZGMTREnergyEVSEModeClusterModeTagStruct : NSObject <NSCopying>
@property (nonatomic, copy) NSNumber * _Nullable mfgCode ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));
@property (nonatomic, copy) NSNumber * _Nonnull value ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));
@end

ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4))
@interface ZGMTREnergyEVSEModeClusterModeOptionStruct : NSObject <NSCopying>
@property (nonatomic, copy) NSString * _Nonnull label ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));
@property (nonatomic, copy) NSNumber * _Nonnull mode ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));
@property (nonatomic, copy) NSArray * _Nonnull modeTags ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));
@end

ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4))
@interface ZGMTRWaterHeaterModeClusterModeTagStruct : NSObject <NSCopying>
@property (nonatomic, copy) NSNumber * _Nullable mfgCode ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));
@property (nonatomic, copy) NSNumber * _Nonnull value ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));
@end

ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4))
@interface ZGMTRWaterHeaterModeClusterModeOptionStruct : NSObject <NSCopying>
@property (nonatomic, copy) NSString * _Nonnull label ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));
@property (nonatomic, copy) NSNumber * _Nonnull mode ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));
@property (nonatomic, copy) NSArray * _Nonnull modeTags ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));
@end

ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4))
@interface ZGMTRDeviceEnergyManagementModeClusterModeTagStruct : NSObject <NSCopying>
@property (nonatomic, copy) NSNumber * _Nullable mfgCode ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));
@property (nonatomic, copy) NSNumber * _Nonnull value ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));
@end

ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4))
@interface ZGMTRDeviceEnergyManagementModeClusterModeOptionStruct : NSObject <NSCopying>
@property (nonatomic, copy) NSString * _Nonnull label ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));
@property (nonatomic, copy) NSNumber * _Nonnull mode ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));
@property (nonatomic, copy) NSArray * _Nonnull modeTags ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));
@end

ZGMTR_PROVISIONALLY_AVAILABLE
@interface ZGMTRElectricalGridConditionsClusterElectricalGridConditionsStruct : NSObject <NSCopying>
@property (nonatomic, copy) NSNumber * _Nonnull periodStart ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSNumber * _Nullable periodEnd ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSNumber * _Nonnull gridCarbonIntensity ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSNumber * _Nonnull gridCarbonLevel ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSNumber * _Nonnull localCarbonIntensity ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSNumber * _Nonnull localCarbonLevel ZGMTR_PROVISIONALLY_AVAILABLE;
@end

ZGMTR_PROVISIONALLY_AVAILABLE
@interface ZGMTRElectricalGridConditionsClusterCurrentConditionsChangedEvent : NSObject <NSCopying>
@property (nonatomic, copy) ZGMTRElectricalGridConditionsClusterElectricalGridConditionsStruct * _Nullable currentConditions ZGMTR_PROVISIONALLY_AVAILABLE;
@end

ZGMTR_PROVISIONALLY_AVAILABLE
@interface ZGMTRElectricalAlarmClusterNotifyEvent : NSObject <NSCopying>
@property (nonatomic, copy) NSNumber * _Nonnull active ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSNumber * _Nonnull inactive ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSNumber * _Nonnull state ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSNumber * _Nonnull mask ZGMTR_PROVISIONALLY_AVAILABLE;
@end

ZGMTR_PROVISIONALLY_AVAILABLE
@interface ZGMTRElectricalProtectionAlarmClusterArcFaultRatingsStruct : NSObject <NSCopying>
@property (nonatomic, copy) NSNumber * _Nullable seriesArcCurrentSensitivity ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSNumber * _Nullable parallelArcCurrentSensitivity ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSNumber * _Nullable supportedArcCauses ZGMTR_PROVISIONALLY_AVAILABLE;
@end

ZGMTR_PROVISIONALLY_AVAILABLE
@interface ZGMTRElectricalProtectionAlarmClusterOverLoadRatingsStruct : NSObject <NSCopying>
@property (nonatomic, copy) NSNumber * _Nullable tripCurrent ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSNumber * _Nullable tripCurve ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSNumber * _Nullable tripMechanism ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSNumber * _Nullable ultimateMaxCurrent ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSNumber * _Nullable serviceMaxCurrent ZGMTR_PROVISIONALLY_AVAILABLE;
@end

ZGMTR_PROVISIONALLY_AVAILABLE
@interface ZGMTRElectricalProtectionAlarmClusterOverVoltageRatingsStruct : NSObject <NSCopying>
@property (nonatomic, copy) NSNumber * _Nullable tripMechanism ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSNumber * _Nullable tripVoltage ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSNumber * _Nullable maxContinuousOperatingVoltage ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSNumber * _Nullable responseTime ZGMTR_PROVISIONALLY_AVAILABLE;
@end

ZGMTR_PROVISIONALLY_AVAILABLE
@interface ZGMTRElectricalProtectionAlarmClusterResidualCurrentFaultRatingsStruct : NSObject <NSCopying>
@property (nonatomic, copy) NSNumber * _Nullable currentSensitivity ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSNumber * _Nullable tripMechanism ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSNumber * _Nullable voltageDependent ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSNumber * _Nullable groundFaultClass ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSNumber * _Nullable waveform ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSNumber * _Nullable trippingCharacteristic ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSNumber * _Nullable ultimateMaxCurrent ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSNumber * _Nullable serviceMaxCurrent ZGMTR_PROVISIONALLY_AVAILABLE;
@end

ZGMTR_PROVISIONALLY_AVAILABLE
@interface ZGMTRElectricalProtectionAlarmClusterShortCircuitRatingsStruct : NSObject <NSCopying>
@property (nonatomic, copy) NSNumber * _Nullable tripCurrent ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSNumber * _Nullable tripMechanism ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSNumber * _Nullable tripCurve ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSNumber * _Nullable ultimateMaxCurrent ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSNumber * _Nullable serviceMaxCurrent ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSNumber * _Nullable maxCurrent ZGMTR_PROVISIONALLY_AVAILABLE;
@end

ZGMTR_PROVISIONALLY_AVAILABLE
@interface ZGMTRElectricalProtectionAlarmClusterSurgeProtectionRatingsStruct : NSObject <NSCopying>
@property (nonatomic, copy) NSNumber * _Nullable tripMechanism ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSNumber * _Nullable protectionClass ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSNumber * _Nullable protectionType ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSNumber * _Nullable maxContinuousOperatingVoltage ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSNumber * _Nullable maxVoltageProtection ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSNumber * _Nullable maxTemporaryVoltage ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSNumber * _Nullable nominalDischargeCurrent ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSNumber * _Nullable maximumDishargeCurrent ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSNumber * _Nullable ratedShortCircuitCurrent ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSNumber * _Nullable ratedShortTimeWithstandCurrent ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSNumber * _Nullable energyAbsorptionCapability ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSNumber * _Nullable responseTime ZGMTR_PROVISIONALLY_AVAILABLE;
@end

ZGMTR_PROVISIONALLY_AVAILABLE
@interface ZGMTRElectricalProtectionAlarmClusterNotifyEvent : NSObject <NSCopying>
@property (nonatomic, copy) NSNumber * _Nonnull active ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSNumber * _Nonnull inactive ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSNumber * _Nonnull state ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSNumber * _Nonnull mask ZGMTR_PROVISIONALLY_AVAILABLE;
@end

ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4))
@interface ZGMTRDoorLockClusterCredentialStruct : NSObject <NSCopying>
@property (nonatomic, copy) NSNumber * _Nonnull credentialType ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
@property (nonatomic, copy) NSNumber * _Nonnull credentialIndex ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
@end

ZGMTR_DEPRECATED("Please use ZGMTRDoorLockClusterCredentialStruct", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
@interface ZGMTRDoorLockClusterDlCredential : ZGMTRDoorLockClusterCredentialStruct
@property (nonatomic, copy) NSNumber * _Nonnull credentialType ZGMTR_DEPRECATED("Please use ZGMTRDoorLockClusterCredentialStruct", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
@property (nonatomic, copy) NSNumber * _Nonnull credentialIndex ZGMTR_DEPRECATED("Please use ZGMTRDoorLockClusterCredentialStruct", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
@end

ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1))
@interface ZGMTRDoorLockClusterDoorLockAlarmEvent : NSObject <NSCopying>
@property (nonatomic, copy) NSNumber * _Nonnull alarmCode ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));
@end

ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1))
@interface ZGMTRDoorLockClusterDoorStateChangeEvent : NSObject <NSCopying>
@property (nonatomic, copy) NSNumber * _Nonnull doorState ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));
@end

ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1))
@interface ZGMTRDoorLockClusterLockOperationEvent : NSObject <NSCopying>
@property (nonatomic, copy) NSNumber * _Nonnull lockOperationType ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));
@property (nonatomic, copy) NSNumber * _Nonnull operationSource ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));
@property (nonatomic, copy) NSNumber * _Nullable userIndex ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));
@property (nonatomic, copy) NSNumber * _Nullable fabricIndex ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));
@property (nonatomic, copy) NSNumber * _Nullable sourceNode ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));
@property (nonatomic, copy) NSArray * _Nullable credentials ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));
@end

ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1))
@interface ZGMTRDoorLockClusterLockOperationErrorEvent : NSObject <NSCopying>
@property (nonatomic, copy) NSNumber * _Nonnull lockOperationType ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));
@property (nonatomic, copy) NSNumber * _Nonnull operationSource ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));
@property (nonatomic, copy) NSNumber * _Nonnull operationError ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));
@property (nonatomic, copy) NSNumber * _Nullable userIndex ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));
@property (nonatomic, copy) NSNumber * _Nullable fabricIndex ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));
@property (nonatomic, copy) NSNumber * _Nullable sourceNode ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));
@property (nonatomic, copy) NSArray * _Nullable credentials ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));
@end

ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1))
@interface ZGMTRDoorLockClusterLockUserChangeEvent : NSObject <NSCopying>
@property (nonatomic, copy) NSNumber * _Nonnull lockDataType ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));
@property (nonatomic, copy) NSNumber * _Nonnull dataOperationType ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));
@property (nonatomic, copy) NSNumber * _Nonnull operationSource ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));
@property (nonatomic, copy) NSNumber * _Nullable userIndex ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));
@property (nonatomic, copy) NSNumber * _Nullable fabricIndex ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));
@property (nonatomic, copy) NSNumber * _Nullable sourceNode ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));
@property (nonatomic, copy) NSNumber * _Nullable dataIndex ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1));
@end

ZGMTR_PROVISIONALLY_AVAILABLE
@interface ZGMTRClosureControlClusterOverallCurrentStateStruct : NSObject <NSCopying>
@property (nonatomic, copy) NSNumber * _Nullable position ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSNumber * _Nullable latch ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSNumber * _Nullable speed ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSNumber * _Nullable secureState ZGMTR_PROVISIONALLY_AVAILABLE;
@end

ZGMTR_PROVISIONALLY_AVAILABLE
@interface ZGMTRClosureControlClusterOverallTargetStateStruct : NSObject <NSCopying>
@property (nonatomic, copy) NSNumber * _Nullable position ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSNumber * _Nullable latch ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSNumber * _Nullable speed ZGMTR_PROVISIONALLY_AVAILABLE;
@end

ZGMTR_PROVISIONALLY_AVAILABLE
@interface ZGMTRClosureControlClusterOperationalErrorEvent : NSObject <NSCopying>
@property (nonatomic, copy) NSArray * _Nonnull errorState ZGMTR_PROVISIONALLY_AVAILABLE;
@end

ZGMTR_PROVISIONALLY_AVAILABLE
@interface ZGMTRClosureControlClusterMovementCompletedEvent : NSObject <NSCopying>
@end

ZGMTR_PROVISIONALLY_AVAILABLE
@interface ZGMTRClosureControlClusterEngageStateChangedEvent : NSObject <NSCopying>
@property (nonatomic, copy) NSNumber * _Nonnull engageValue ZGMTR_PROVISIONALLY_AVAILABLE;
@end

ZGMTR_PROVISIONALLY_AVAILABLE
@interface ZGMTRClosureControlClusterSecureStateChangedEvent : NSObject <NSCopying>
@property (nonatomic, copy) NSNumber * _Nonnull secureValue ZGMTR_PROVISIONALLY_AVAILABLE;
@end

ZGMTR_PROVISIONALLY_AVAILABLE
@interface ZGMTRClosureDimensionClusterDimensionStateStruct : NSObject <NSCopying>
@property (nonatomic, copy) NSNumber * _Nullable position ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSNumber * _Nullable latch ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSNumber * _Nullable speed ZGMTR_PROVISIONALLY_AVAILABLE;
@end

ZGMTR_PROVISIONALLY_AVAILABLE
@interface ZGMTRClosureDimensionClusterRangePercent100thsStruct : NSObject <NSCopying>
@property (nonatomic, copy) NSNumber * _Nonnull min ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSNumber * _Nonnull max ZGMTR_PROVISIONALLY_AVAILABLE;
@end

ZGMTR_PROVISIONALLY_AVAILABLE
@interface ZGMTRClosureDimensionClusterUnitRangeStruct : NSObject <NSCopying>
@property (nonatomic, copy) NSNumber * _Nonnull min ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSNumber * _Nonnull max ZGMTR_PROVISIONALLY_AVAILABLE;
@end

ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4))
@interface ZGMTRServiceAreaClusterLandmarkInfoStruct : NSObject <NSCopying>
@property (nonatomic, copy) NSNumber * _Nonnull landmarkTag ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));
@property (nonatomic, copy) NSNumber * _Nullable relativePositionTag ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));
@end

ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4))
@interface ZGMTRServiceAreaClusterAreaInfoStruct : NSObject <NSCopying>
@property (nonatomic, copy) ZGMTRDataTypeLocationDescriptorStruct * _Nullable locationInfo ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));
@property (nonatomic, copy) ZGMTRServiceAreaClusterLandmarkInfoStruct * _Nullable landmarkInfo ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));
@end

ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4))
@interface ZGMTRServiceAreaClusterAreaStruct : NSObject <NSCopying>
@property (nonatomic, copy) NSNumber * _Nonnull areaID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));
@property (nonatomic, copy) NSNumber * _Nullable mapID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));
@property (nonatomic, copy) ZGMTRServiceAreaClusterAreaInfoStruct * _Nonnull areaInfo ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));
@end

ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4))
@interface ZGMTRServiceAreaClusterMapStruct : NSObject <NSCopying>
@property (nonatomic, copy) NSNumber * _Nonnull mapID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));
@property (nonatomic, copy) NSString * _Nonnull name ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));
@end

ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4))
@interface ZGMTRServiceAreaClusterProgressStruct : NSObject <NSCopying>
@property (nonatomic, copy) NSNumber * _Nonnull areaID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));
@property (nonatomic, copy) NSNumber * _Nonnull status ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));
@property (nonatomic, copy) NSNumber * _Nullable totalOperationalTime ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));
@property (nonatomic, copy) NSNumber * _Nullable estimatedTime ZGMTR_PROVISIONALLY_AVAILABLE;
@end

ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1))
@interface ZGMTRPumpConfigurationAndControlClusterSupplyVoltageLowEvent : NSObject <NSCopying>
@end

ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1))
@interface ZGMTRPumpConfigurationAndControlClusterSupplyVoltageHighEvent : NSObject <NSCopying>
@end

ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1))
@interface ZGMTRPumpConfigurationAndControlClusterPowerMissingPhaseEvent : NSObject <NSCopying>
@end

ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1))
@interface ZGMTRPumpConfigurationAndControlClusterSystemPressureLowEvent : NSObject <NSCopying>
@end

ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1))
@interface ZGMTRPumpConfigurationAndControlClusterSystemPressureHighEvent : NSObject <NSCopying>
@end

ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1))
@interface ZGMTRPumpConfigurationAndControlClusterDryRunningEvent : NSObject <NSCopying>
@end

ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1))
@interface ZGMTRPumpConfigurationAndControlClusterMotorTemperatureHighEvent : NSObject <NSCopying>
@end

ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1))
@interface ZGMTRPumpConfigurationAndControlClusterPumpMotorFatalFailureEvent : NSObject <NSCopying>
@end

ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1))
@interface ZGMTRPumpConfigurationAndControlClusterElectronicTemperatureHighEvent : NSObject <NSCopying>
@end

ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1))
@interface ZGMTRPumpConfigurationAndControlClusterPumpBlockedEvent : NSObject <NSCopying>
@end

ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1))
@interface ZGMTRPumpConfigurationAndControlClusterSensorFailureEvent : NSObject <NSCopying>
@end

ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1))
@interface ZGMTRPumpConfigurationAndControlClusterElectronicNonFatalFailureEvent : NSObject <NSCopying>
@end

ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1))
@interface ZGMTRPumpConfigurationAndControlClusterElectronicFatalFailureEvent : NSObject <NSCopying>
@end

ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1))
@interface ZGMTRPumpConfigurationAndControlClusterGeneralFaultEvent : NSObject <NSCopying>
@end

ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1))
@interface ZGMTRPumpConfigurationAndControlClusterLeakageEvent : NSObject <NSCopying>
@end

ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1))
@interface ZGMTRPumpConfigurationAndControlClusterAirDetectionEvent : NSObject <NSCopying>
@end

ZGMTR_AVAILABLE(ios(16.1), macos(13.0), watchos(9.1), tvos(16.1))
@interface ZGMTRPumpConfigurationAndControlClusterTurbineOperationEvent : NSObject <NSCopying>
@end

ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4))
@interface ZGMTRThermostatClusterScheduleTransitionStruct : NSObject <NSCopying>
@property (nonatomic, copy) NSNumber * _Nonnull dayOfWeek ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));
@property (nonatomic, copy) NSNumber * _Nonnull transitionTime ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));
@property (nonatomic, copy) NSData * _Nullable presetHandle ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));
@property (nonatomic, copy) NSNumber * _Nullable systemMode ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));
@property (nonatomic, copy) NSNumber * _Nullable coolingSetpoint ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));
@property (nonatomic, copy) NSNumber * _Nullable heatingSetpoint ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));
@end

ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4))
@interface ZGMTRThermostatClusterScheduleStruct : NSObject <NSCopying>
@property (nonatomic, copy) NSData * _Nullable scheduleHandle ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));
@property (nonatomic, copy) NSNumber * _Nonnull systemMode ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));
@property (nonatomic, copy) NSString * _Nullable name ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));
@property (nonatomic, copy) NSData * _Nullable presetHandle ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));
@property (nonatomic, copy) NSArray * _Nonnull transitions ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));
@property (nonatomic, copy) NSNumber * _Nullable builtIn ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));
@end

ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4))
@interface ZGMTRThermostatClusterPresetStruct : NSObject <NSCopying>
@property (nonatomic, copy) NSData * _Nullable presetHandle ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));
@property (nonatomic, copy) NSNumber * _Nonnull presetScenario ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));
@property (nonatomic, copy) NSString * _Nullable name ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));
@property (nonatomic, copy) NSNumber * _Nullable coolingSetpoint ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));
@property (nonatomic, copy) NSNumber * _Nullable heatingSetpoint ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));
@property (nonatomic, copy) NSNumber * _Nullable builtIn ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));
@end

ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4))
@interface ZGMTRThermostatClusterPresetTypeStruct : NSObject <NSCopying>
@property (nonatomic, copy) NSNumber * _Nonnull presetScenario ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));
@property (nonatomic, copy) NSNumber * _Nonnull numberOfPresets ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));
@property (nonatomic, copy) NSNumber * _Nonnull presetTypeFeatures ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));
@end

ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4))
@interface ZGMTRThermostatClusterScheduleTypeStruct : NSObject <NSCopying>
@property (nonatomic, copy) NSNumber * _Nonnull systemMode ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));
@property (nonatomic, copy) NSNumber * _Nonnull numberOfSchedules ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));
@property (nonatomic, copy) NSNumber * _Nonnull scheduleTypeFeatures ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));
@end

ZGMTR_PROVISIONALLY_AVAILABLE
@interface ZGMTRThermostatClusterThermostatSuggestionStruct : NSObject <NSCopying>
@property (nonatomic, copy) NSNumber * _Nonnull uniqueID ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSData * _Nonnull presetHandle ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSNumber * _Nonnull effectiveTime ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSNumber * _Nonnull expirationTime ZGMTR_PROVISIONALLY_AVAILABLE;
@end

ZGMTR_AVAILABLE(ios(17.4), macos(14.4), watchos(10.4), tvos(17.4))
@interface ZGMTRThermostatClusterWeeklyScheduleTransitionStruct : NSObject <NSCopying>
@property (nonatomic, copy) NSNumber * _Nonnull transitionTime ZGMTR_AVAILABLE(ios(17.4), macos(14.4), watchos(10.4), tvos(17.4));
@property (nonatomic, copy) NSNumber * _Nullable heatSetpoint ZGMTR_AVAILABLE(ios(17.4), macos(14.4), watchos(10.4), tvos(17.4));
@property (nonatomic, copy) NSNumber * _Nullable coolSetpoint ZGMTR_AVAILABLE(ios(17.4), macos(14.4), watchos(10.4), tvos(17.4));
@end

ZGMTR_DEPRECATED("Please use ZGMTRThermostatClusterWeeklyScheduleTransitionStruct", ios(16.1, 17.4), macos(13.0, 14.4), watchos(9.1, 10.4), tvos(16.1, 17.4))
@interface ZGMTRThermostatClusterThermostatScheduleTransition : ZGMTRThermostatClusterWeeklyScheduleTransitionStruct
@property (nonatomic, copy) NSNumber * _Nonnull transitionTime ZGMTR_DEPRECATED("Please use ZGMTRThermostatClusterWeeklyScheduleTransitionStruct", ios(16.1, 17.4), macos(13.0, 14.4), watchos(9.1, 10.4), tvos(16.1, 17.4));
@property (nonatomic, copy) NSNumber * _Nullable heatSetpoint ZGMTR_DEPRECATED("Please use ZGMTRThermostatClusterWeeklyScheduleTransitionStruct", ios(16.1, 17.4), macos(13.0, 14.4), watchos(9.1, 10.4), tvos(16.1, 17.4));
@property (nonatomic, copy) NSNumber * _Nullable coolSetpoint ZGMTR_DEPRECATED("Please use ZGMTRThermostatClusterWeeklyScheduleTransitionStruct", ios(16.1, 17.4), macos(13.0, 14.4), watchos(9.1, 10.4), tvos(16.1, 17.4));
@end

ZGMTR_PROVISIONALLY_AVAILABLE
@interface ZGMTRThermostatClusterSystemModeChangeEvent : NSObject <NSCopying>
@property (nonatomic, copy) NSNumber * _Nullable previousSystemMode ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSNumber * _Nonnull currentSystemMode ZGMTR_PROVISIONALLY_AVAILABLE;
@end

ZGMTR_PROVISIONALLY_AVAILABLE
@interface ZGMTRThermostatClusterLocalTemperatureChangeEvent : NSObject <NSCopying>
@property (nonatomic, copy) NSNumber * _Nullable currentLocalTemperature ZGMTR_PROVISIONALLY_AVAILABLE;
@end

ZGMTR_PROVISIONALLY_AVAILABLE
@interface ZGMTRThermostatClusterOccupancyChangeEvent : NSObject <NSCopying>
@property (nonatomic, copy) NSNumber * _Nullable previousOccupancy ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSNumber * _Nonnull currentOccupancy ZGMTR_PROVISIONALLY_AVAILABLE;
@end

ZGMTR_PROVISIONALLY_AVAILABLE
@interface ZGMTRThermostatClusterSetpointChangeEvent : NSObject <NSCopying>
@property (nonatomic, copy) NSNumber * _Nonnull systemMode ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSNumber * _Nullable occupancy ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSNumber * _Nullable previousSetpoint ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSNumber * _Nonnull currentSetpoint ZGMTR_PROVISIONALLY_AVAILABLE;
@end

ZGMTR_PROVISIONALLY_AVAILABLE
@interface ZGMTRThermostatClusterRunningStateChangeEvent : NSObject <NSCopying>
@property (nonatomic, copy) NSNumber * _Nullable previousRunningState ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSNumber * _Nonnull currentRunningState ZGMTR_PROVISIONALLY_AVAILABLE;
@end

ZGMTR_PROVISIONALLY_AVAILABLE
@interface ZGMTRThermostatClusterRunningModeChangeEvent : NSObject <NSCopying>
@property (nonatomic, copy) NSNumber * _Nullable previousRunningMode ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSNumber * _Nonnull currentRunningMode ZGMTR_PROVISIONALLY_AVAILABLE;
@end

ZGMTR_PROVISIONALLY_AVAILABLE
@interface ZGMTRThermostatClusterActiveScheduleChangeEvent : NSObject <NSCopying>
@property (nonatomic, copy) NSData * _Nullable previousScheduleHandle ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSData * _Nullable currentScheduleHandle ZGMTR_PROVISIONALLY_AVAILABLE;
@end

ZGMTR_PROVISIONALLY_AVAILABLE
@interface ZGMTRThermostatClusterActivePresetChangeEvent : NSObject <NSCopying>
@property (nonatomic, copy) NSData * _Nullable previousPresetHandle ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSData * _Nullable currentPresetHandle ZGMTR_PROVISIONALLY_AVAILABLE;
@end

ZGMTR_PROVISIONALLY_AVAILABLE
@interface ZGMTRDynamicLightingClusterEffectColorStruct : NSObject <NSCopying>
@property (nonatomic, copy) NSNumber * _Nullable level ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSNumber * _Nullable x ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSNumber * _Nullable y ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSNumber * _Nullable hue ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSNumber * _Nullable enhancedHue ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSNumber * _Nullable saturation ZGMTR_PROVISIONALLY_AVAILABLE;
@end

ZGMTR_PROVISIONALLY_AVAILABLE
@interface ZGMTRDynamicLightingClusterEffectStruct : NSObject <NSCopying>
@property (nonatomic, copy) NSNumber * _Nonnull effectID ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSNumber * _Nonnull source ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSString * _Nonnull label ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSNumber * _Nonnull maxSpeed ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSNumber * _Nonnull defaultSpeed ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSNumber * _Nonnull supportsColorPalette ZGMTR_PROVISIONALLY_AVAILABLE;
@end

ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4))
@interface ZGMTROccupancySensingClusterHoldTimeLimitsStruct : NSObject <NSCopying>
@property (nonatomic, copy) NSNumber * _Nonnull holdTimeMin ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));
@property (nonatomic, copy) NSNumber * _Nonnull holdTimeMax ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));
@property (nonatomic, copy) NSNumber * _Nonnull holdTimeDefault ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));
@end

ZGMTR_PROVISIONALLY_AVAILABLE
@interface ZGMTROccupancySensingClusterPredictedOccupancyStruct : NSObject <NSCopying>
@property (nonatomic, copy) NSNumber * _Nonnull startTimestamp ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSNumber * _Nonnull endTimestamp ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSNumber * _Nonnull occupancy ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSNumber * _Nonnull confidence ZGMTR_PROVISIONALLY_AVAILABLE;
@end

ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4))
@interface ZGMTROccupancySensingClusterOccupancyChangedEvent : NSObject <NSCopying>
@property (nonatomic, copy) NSNumber * _Nonnull occupancy ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));
@end

ZGMTR_PROVISIONALLY_AVAILABLE
@interface ZGMTRAmbientContextSensingClusterAmbientContextTypeStruct : NSObject <NSCopying>
@property (nonatomic, copy) NSArray * _Nonnull ambientContextSensed ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSNumber * _Nullable detectionConfidence ZGMTR_PROVISIONALLY_AVAILABLE;
@end

ZGMTR_PROVISIONALLY_AVAILABLE
@interface ZGMTRAmbientContextSensingClusterHoldTimeLimitsStruct : NSObject <NSCopying>
@property (nonatomic, copy) NSNumber * _Nonnull holdTimeMin ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSNumber * _Nonnull holdTimeMax ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSNumber * _Nonnull holdTimeDefault ZGMTR_PROVISIONALLY_AVAILABLE;
@end

ZGMTR_PROVISIONALLY_AVAILABLE
@interface ZGMTRAmbientContextSensingClusterObjectCountConfigStruct : NSObject <NSCopying>
@property (nonatomic, copy) ZGMTRDataTypeSemanticTagStruct * _Nonnull countingObject ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSNumber * _Nonnull objectCountThreshold ZGMTR_PROVISIONALLY_AVAILABLE;
@end

ZGMTR_PROVISIONALLY_AVAILABLE
@interface ZGMTRAmbientContextSensingClusterPredictedActivityStruct : NSObject <NSCopying>
@property (nonatomic, copy) NSNumber * _Nonnull startTimestamp ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSNumber * _Nonnull endTimestamp ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSArray * _Nullable ambientContextType ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSNumber * _Nullable crowdDetected ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSNumber * _Nullable crowdCount ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSNumber * _Nonnull confidence ZGMTR_PROVISIONALLY_AVAILABLE;
@end

ZGMTR_PROVISIONALLY_AVAILABLE
@interface ZGMTRAmbientContextSensingClusterAmbientContextDetectStartedEvent : NSObject <NSCopying>
@property (nonatomic, copy) ZGMTRAmbientContextSensingClusterAmbientContextTypeStruct * _Nullable ambientContextDetected ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSNumber * _Nullable objectCountThresholdReached ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSNumber * _Nullable objectCount ZGMTR_PROVISIONALLY_AVAILABLE;
@end

ZGMTR_PROVISIONALLY_AVAILABLE
@interface ZGMTRAmbientContextSensingClusterAmbientContextDetectEndedEvent : NSObject <NSCopying>
@property (nonatomic, copy) NSNumber * _Nullable eventStartTimePos ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSNumber * _Nullable eventStartTimeSys ZGMTR_PROVISIONALLY_AVAILABLE;
@end

ZGMTR_PROVISIONALLY_AVAILABLE
@interface ZGMTRAmbientSensingUnionClusterUnionContributorStruct : NSObject <NSCopying>
@property (nonatomic, copy) NSNumber * _Nullable contributorNodeID ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSNumber * _Nullable contributorEndpointID ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSString * _Nullable contributorName ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSNumber * _Nonnull contributorHealth ZGMTR_PROVISIONALLY_AVAILABLE;
@end

ZGMTR_PROVISIONALLY_AVAILABLE
@interface ZGMTRAmbientSensingUnionClusterUnionContributorAddedEvent : NSObject <NSCopying>
@property (nonatomic, copy) NSArray * _Nonnull addedContributor ZGMTR_PROVISIONALLY_AVAILABLE;
@end

ZGMTR_PROVISIONALLY_AVAILABLE
@interface ZGMTRAmbientSensingUnionClusterUnionContributorRemovedEvent : NSObject <NSCopying>
@property (nonatomic, copy) NSArray * _Nonnull removedContributor ZGMTR_PROVISIONALLY_AVAILABLE;
@end

ZGMTR_PROVISIONALLY_AVAILABLE
@interface ZGMTRAmbientSensingUnionClusterUnionContributorStatusChangedEvent : NSObject <NSCopying>
@property (nonatomic, copy) NSArray * _Nonnull statusChangedContributor ZGMTR_PROVISIONALLY_AVAILABLE;
@end

ZGMTR_PROVISIONALLY_AVAILABLE
@interface ZGMTRProximityRangingClusterRDRStruct : NSObject <NSCopying>
@property (nonatomic, copy) NSNumber * _Nonnull azimuth ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSNumber * _Nonnull elevation ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSNumber * _Nonnull azimuthAccuracy ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSNumber * _Nonnull elevationAccuracy ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSNumber * _Nonnull reference ZGMTR_PROVISIONALLY_AVAILABLE;
@end

ZGMTR_PROVISIONALLY_AVAILABLE
@interface ZGMTRProximityRangingClusterRangingMeasurementDataStruct : NSObject <NSCopying>
@property (nonatomic, copy) NSData * _Nullable wiFiDevIK ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSNumber * _Nullable bleDeviceID ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSData * _Nullable bltDevIK ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSNumber * _Nullable timeOfMeasurement ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSNumber * _Nullable timeOfMeasurementOffset ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSNumber * _Nullable distance ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSNumber * _Nullable errorMargin ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) ZGMTRProximityRangingClusterRDRStruct * _Nullable rdr ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSNumber * _Nullable detectedAttackLevel ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSNumber * _Nullable rssi ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSNumber * _Nullable txPower ZGMTR_PROVISIONALLY_AVAILABLE;
@end

ZGMTR_PROVISIONALLY_AVAILABLE
@interface ZGMTRProximityRangingClusterBLERangingDeviceRoleConfigStruct : NSObject <NSCopying>
@property (nonatomic, copy) NSNumber * _Nonnull role ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSNumber * _Nonnull peerBLEDeviceID ZGMTR_PROVISIONALLY_AVAILABLE;
@end

ZGMTR_PROVISIONALLY_AVAILABLE
@interface ZGMTRProximityRangingClusterBLTChannelSoundingDeviceRoleConfigStruct : NSObject <NSCopying>
@property (nonatomic, copy) NSNumber * _Nonnull role ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSData * _Nonnull peerBLTDevIK ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSNumber * _Nullable bltcsMode ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSNumber * _Nullable bltcsSecurityLevel ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSData * _Nullable ltk ZGMTR_PROVISIONALLY_AVAILABLE;
@end

ZGMTR_PROVISIONALLY_AVAILABLE
@interface ZGMTRProximityRangingClusterRangingCapabilitiesStruct : NSObject <NSCopying>
@property (nonatomic, copy) NSNumber * _Nonnull technology ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSNumber * _Nonnull frequencyBand ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSNumber * _Nonnull periodicRangingSupport ZGMTR_PROVISIONALLY_AVAILABLE;
@end

ZGMTR_PROVISIONALLY_AVAILABLE
@interface ZGMTRProximityRangingClusterRangingTriggerConditionStruct : NSObject <NSCopying>
@property (nonatomic, copy) NSNumber * _Nonnull startTime ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSNumber * _Nonnull endTime ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSNumber * _Nullable rangingInstanceInterval ZGMTR_PROVISIONALLY_AVAILABLE;
@end

ZGMTR_PROVISIONALLY_AVAILABLE
@interface ZGMTRProximityRangingClusterReportingConditionStruct : NSObject <NSCopying>
@property (nonatomic, copy) NSNumber * _Nullable minDistanceCondition ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSNumber * _Nullable maxDistanceCondition ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSNumber * _Nullable errorMarginCondition ZGMTR_PROVISIONALLY_AVAILABLE;
@end

ZGMTR_PROVISIONALLY_AVAILABLE
@interface ZGMTRProximityRangingClusterWiFiRangingDeviceRoleConfigStruct : NSObject <NSCopying>
@property (nonatomic, copy) NSNumber * _Nonnull role ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSData * _Nonnull peerWiFiDevIK ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSData * _Nullable pmk ZGMTR_PROVISIONALLY_AVAILABLE;
@end

ZGMTR_PROVISIONALLY_AVAILABLE
@interface ZGMTRProximityRangingClusterRangingResultEvent : NSObject <NSCopying>
@property (nonatomic, copy) NSNumber * _Nonnull sessionID ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) ZGMTRProximityRangingClusterRangingMeasurementDataStruct * _Nonnull rangingResultData ZGMTR_PROVISIONALLY_AVAILABLE;
@end

ZGMTR_PROVISIONALLY_AVAILABLE
@interface ZGMTRProximityRangingClusterRangingSessionStatusEvent : NSObject <NSCopying>
@property (nonatomic, copy) NSNumber * _Nonnull sessionID ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSNumber * _Nonnull status ZGMTR_PROVISIONALLY_AVAILABLE;
@end

ZGMTR_PROVISIONALLY_AVAILABLE
@interface ZGMTRNetworkIdentityManagementClusterActiveNetworkIdentityStruct : NSObject <NSCopying>
@property (nonatomic, copy) NSNumber * _Nonnull index ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSNumber * _Nonnull type ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSData * _Nonnull identifier ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSNumber * _Nonnull createdTimestamp ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSNumber * _Nonnull current ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSNumber * _Nullable remainingClients ZGMTR_PROVISIONALLY_AVAILABLE;
@end

ZGMTR_PROVISIONALLY_AVAILABLE
@interface ZGMTRNetworkIdentityManagementClusterClientStruct : NSObject <NSCopying>
@property (nonatomic, copy) NSNumber * _Nonnull clientIndex ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSData * _Nonnull clientIdentifier ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSNumber * _Nonnull clientIdentityType ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSNumber * _Nullable networkIdentityIndex ZGMTR_PROVISIONALLY_AVAILABLE;
@end

ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4))
@interface ZGMTRThreadNetworkDirectoryClusterThreadNetworkStruct : NSObject <NSCopying>
@property (nonatomic, copy) NSData * _Nonnull extendedPanID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));
@property (nonatomic, copy) NSString * _Nonnull networkName ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));
@property (nonatomic, copy) NSNumber * _Nonnull channel ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));
@property (nonatomic, copy) NSNumber * _Nonnull activeTimestamp ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));
@end

ZGMTR_PROVISIONALLY_AVAILABLE
@interface ZGMTRCommissioningProxyClusterScanResultStruct : NSObject <NSCopying>
@property (nonatomic, copy) NSData * _Nullable address ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSNumber * _Nonnull transport ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSNumber * _Nonnull discriminator ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSNumber * _Nonnull vendorID ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSNumber * _Nonnull productID ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSData * _Nullable extendedData ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSNumber * _Nullable wiFiBand ZGMTR_PROVISIONALLY_AVAILABLE;
@end

ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4))
@interface ZGMTRChannelClusterProgramCastStruct : NSObject <NSCopying>
@property (nonatomic, copy) NSString * _Nonnull name ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));
@property (nonatomic, copy) NSString * _Nonnull role ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));
@end

ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4))
@interface ZGMTRChannelClusterProgramCategoryStruct : NSObject <NSCopying>
@property (nonatomic, copy) NSString * _Nonnull category ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));
@property (nonatomic, copy) NSString * _Nullable subCategory ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));
@end

ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4))
@interface ZGMTRChannelClusterSeriesInfoStruct : NSObject <NSCopying>
@property (nonatomic, copy) NSString * _Nonnull season ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));
@property (nonatomic, copy) NSString * _Nonnull episode ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));
@end

ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4))
@interface ZGMTRChannelClusterChannelInfoStruct : NSObject <NSCopying>
@property (nonatomic, copy) NSNumber * _Nonnull majorNumber ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
@property (nonatomic, copy) NSNumber * _Nonnull minorNumber ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
@property (nonatomic, copy) NSString * _Nullable name ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
@property (nonatomic, copy) NSString * _Nullable callSign ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
@property (nonatomic, copy) NSString * _Nullable affiliateCallSign ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
@property (nonatomic, copy) NSString * _Nullable identifier ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));
@property (nonatomic, copy) NSNumber * _Nullable type ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));
@end

ZGMTR_DEPRECATED("Please use ZGMTRChannelClusterChannelInfoStruct", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
@interface ZGMTRChannelClusterChannelInfo : ZGMTRChannelClusterChannelInfoStruct
@property (nonatomic, copy) NSNumber * _Nonnull majorNumber ZGMTR_DEPRECATED("Please use ZGMTRChannelClusterChannelInfoStruct", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
@property (nonatomic, copy) NSNumber * _Nonnull minorNumber ZGMTR_DEPRECATED("Please use ZGMTRChannelClusterChannelInfoStruct", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
@property (nonatomic, copy) NSString * _Nullable name ZGMTR_DEPRECATED("Please use ZGMTRChannelClusterChannelInfoStruct", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
@property (nonatomic, copy) NSString * _Nullable callSign ZGMTR_DEPRECATED("Please use ZGMTRChannelClusterChannelInfoStruct", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
@property (nonatomic, copy) NSString * _Nullable affiliateCallSign ZGMTR_DEPRECATED("Please use ZGMTRChannelClusterChannelInfoStruct", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
@end

ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4))
@interface ZGMTRChannelClusterProgramStruct : NSObject <NSCopying>
@property (nonatomic, copy) NSString * _Nonnull identifier ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));
@property (nonatomic, copy) ZGMTRChannelClusterChannelInfoStruct * _Nonnull channel ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));
@property (nonatomic, copy) NSNumber * _Nonnull startTime ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));
@property (nonatomic, copy) NSNumber * _Nonnull endTime ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));
@property (nonatomic, copy) NSString * _Nonnull title ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));
@property (nonatomic, copy) NSString * _Nullable subtitle ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));
@property (nonatomic, copy) NSString * _Nullable descriptionString ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));
@property (nonatomic, copy) NSArray * _Nullable audioLanguages ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));
@property (nonatomic, copy) NSArray * _Nullable ratings ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));
@property (nonatomic, copy) NSString * _Nullable thumbnailUrl ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSString * _Nullable posterArtUrl ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSString * _Nullable dvbiUrl ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSString * _Nullable releaseDate ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));
@property (nonatomic, copy) NSString * _Nullable parentalGuidanceText ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));
@property (nonatomic, copy) NSNumber * _Nullable recordingFlag ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));
@property (nonatomic, copy) ZGMTRChannelClusterSeriesInfoStruct * _Nullable seriesInfo ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));
@property (nonatomic, copy) NSArray * _Nullable categoryList ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));
@property (nonatomic, copy) NSArray * _Nullable castList ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));
@property (nonatomic, copy) NSArray * _Nullable externalIDList ZGMTR_PROVISIONALLY_AVAILABLE;
@end

ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4))
@interface ZGMTRChannelClusterPageTokenStruct : NSObject <NSCopying>
@property (nonatomic, copy) NSNumber * _Nullable limit ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));
@property (nonatomic, copy) NSString * _Nullable after ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));
@property (nonatomic, copy) NSString * _Nullable before ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));
@end

ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4))
@interface ZGMTRChannelClusterChannelPagingStruct : NSObject <NSCopying>
@property (nonatomic, copy) ZGMTRChannelClusterPageTokenStruct * _Nullable previousToken ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));
@property (nonatomic, copy) ZGMTRChannelClusterPageTokenStruct * _Nullable nextToken ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));
@end

ZGMTR_PROVISIONALLY_AVAILABLE
@interface ZGMTRChannelClusterAdditionalInfoStruct : NSObject <NSCopying>
@property (nonatomic, copy) NSString * _Nonnull name ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSString * _Nonnull value ZGMTR_PROVISIONALLY_AVAILABLE;
@end

ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4))
@interface ZGMTRChannelClusterLineupInfoStruct : NSObject <NSCopying>
@property (nonatomic, copy) NSString * _Nonnull operatorName ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
@property (nonatomic, copy) NSString * _Nullable lineupName ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
@property (nonatomic, copy) NSString * _Nullable postalCode ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
@property (nonatomic, copy) NSNumber * _Nonnull lineupInfoType ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
@end

ZGMTR_DEPRECATED("Please use ZGMTRChannelClusterLineupInfoStruct", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
@interface ZGMTRChannelClusterLineupInfo : ZGMTRChannelClusterLineupInfoStruct
@property (nonatomic, copy) NSString * _Nonnull operatorName ZGMTR_DEPRECATED("Please use ZGMTRChannelClusterLineupInfoStruct", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
@property (nonatomic, copy) NSString * _Nullable lineupName ZGMTR_DEPRECATED("Please use ZGMTRChannelClusterLineupInfoStruct", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
@property (nonatomic, copy) NSString * _Nullable postalCode ZGMTR_DEPRECATED("Please use ZGMTRChannelClusterLineupInfoStruct", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
@property (nonatomic, copy) NSNumber * _Nonnull lineupInfoType ZGMTR_DEPRECATED("Please use ZGMTRChannelClusterLineupInfoStruct", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
@end

ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4))
@interface ZGMTRTargetNavigatorClusterTargetInfoStruct : NSObject <NSCopying>
@property (nonatomic, copy) NSNumber * _Nonnull identifier ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
@property (nonatomic, copy) NSString * _Nonnull name ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
@end

ZGMTR_DEPRECATED("Please use ZGMTRTargetNavigatorClusterTargetInfoStruct", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
@interface ZGMTRTargetNavigatorClusterTargetInfo : ZGMTRTargetNavigatorClusterTargetInfoStruct
@property (nonatomic, copy) NSNumber * _Nonnull identifier ZGMTR_DEPRECATED("Please use ZGMTRTargetNavigatorClusterTargetInfoStruct", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
@property (nonatomic, copy) NSString * _Nonnull name ZGMTR_DEPRECATED("Please use ZGMTRTargetNavigatorClusterTargetInfoStruct", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
@end

ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4))
@interface ZGMTRTargetNavigatorClusterTargetUpdatedEvent : NSObject <NSCopying>
@property (nonatomic, copy) NSArray * _Nonnull targetList ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));
@property (nonatomic, copy) NSNumber * _Nonnull currentTarget ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));
@property (nonatomic, copy) NSData * _Nonnull data ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));
@end

ZGMTR_PROVISIONALLY_AVAILABLE
@interface ZGMTRMediaPlaybackClusterTrackAttributesStruct : NSObject <NSCopying>
@property (nonatomic, copy) NSString * _Nonnull languageCode ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSArray * _Nullable characteristics ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSString * _Nullable displayName ZGMTR_PROVISIONALLY_AVAILABLE;
@end

ZGMTR_PROVISIONALLY_AVAILABLE
@interface ZGMTRMediaPlaybackClusterTrackStruct : NSObject <NSCopying>
@property (nonatomic, copy) NSString * _Nonnull id ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) ZGMTRMediaPlaybackClusterTrackAttributesStruct * _Nullable trackAttributes ZGMTR_PROVISIONALLY_AVAILABLE;
@end

ZGMTR_PROVISIONALLY_AVAILABLE
@interface ZGMTRMediaPlaybackClusterContentInfoStruct : NSObject <NSCopying>
@property (nonatomic, copy) NSNumber * _Nonnull contentType ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSString * _Nullable title ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSString * _Nullable show ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSString * _Nullable season ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSString * _Nullable episode ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSString * _Nullable provider ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSString * _Nullable artist ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSString * _Nullable album ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSString * _Nullable track ZGMTR_PROVISIONALLY_AVAILABLE;
@end

ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4))
@interface ZGMTRMediaPlaybackClusterPlaybackPositionStruct : NSObject <NSCopying>
@property (nonatomic, copy) NSNumber * _Nonnull updatedAt ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
@property (nonatomic, copy) NSNumber * _Nullable position ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
@end

ZGMTR_DEPRECATED("Please use ZGMTRMediaPlaybackClusterPlaybackPositionStruct", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
@interface ZGMTRMediaPlaybackClusterPlaybackPosition : ZGMTRMediaPlaybackClusterPlaybackPositionStruct
@property (nonatomic, copy) NSNumber * _Nonnull updatedAt ZGMTR_DEPRECATED("Please use ZGMTRMediaPlaybackClusterPlaybackPositionStruct", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
@property (nonatomic, copy) NSNumber * _Nullable position ZGMTR_DEPRECATED("Please use ZGMTRMediaPlaybackClusterPlaybackPositionStruct", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
@end

ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4))
@interface ZGMTRMediaPlaybackClusterStateChangedEvent : NSObject <NSCopying>
@property (nonatomic, copy) NSNumber * _Nonnull currentState ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));
@property (nonatomic, copy) NSNumber * _Nonnull startTime ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));
@property (nonatomic, copy) NSNumber * _Nonnull duration ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));
@property (nonatomic, copy) ZGMTRMediaPlaybackClusterPlaybackPositionStruct * _Nonnull sampledPosition ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));
@property (nonatomic, copy) NSNumber * _Nonnull playbackSpeed ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));
@property (nonatomic, copy) NSNumber * _Nonnull seekRangeEnd ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));
@property (nonatomic, copy) NSNumber * _Nonnull seekRangeStart ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));
@property (nonatomic, copy) NSData * _Nullable data ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));
@property (nonatomic, copy) NSNumber * _Nonnull audioAdvanceUnmuted ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));
@end

ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4))
@interface ZGMTRMediaInputClusterInputInfoStruct : NSObject <NSCopying>
@property (nonatomic, copy) NSNumber * _Nonnull index ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
@property (nonatomic, copy) NSNumber * _Nonnull inputType ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
@property (nonatomic, copy) NSString * _Nonnull name ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
@property (nonatomic, copy) NSString * _Nonnull descriptionString ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
@end

ZGMTR_DEPRECATED("Please use ZGMTRMediaInputClusterInputInfoStruct", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
@interface ZGMTRMediaInputClusterInputInfo : ZGMTRMediaInputClusterInputInfoStruct
@property (nonatomic, copy) NSNumber * _Nonnull index ZGMTR_DEPRECATED("Please use ZGMTRMediaInputClusterInputInfoStruct", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
@property (nonatomic, copy) NSNumber * _Nonnull inputType ZGMTR_DEPRECATED("Please use ZGMTRMediaInputClusterInputInfoStruct", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
@property (nonatomic, copy) NSString * _Nonnull name ZGMTR_DEPRECATED("Please use ZGMTRMediaInputClusterInputInfoStruct", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
@property (nonatomic, copy) NSString * _Nonnull descriptionString ZGMTR_DEPRECATED("Please use ZGMTRMediaInputClusterInputInfoStruct", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
@end

ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4))
@interface ZGMTRContentLauncherClusterDimensionStruct : NSObject <NSCopying>
@property (nonatomic, copy) NSNumber * _Nonnull width ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
@property (nonatomic, copy) NSNumber * _Nonnull height ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
@property (nonatomic, copy) NSNumber * _Nonnull metric ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
@end

ZGMTR_DEPRECATED("Please use ZGMTRContentLauncherClusterDimensionStruct", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
@interface ZGMTRContentLauncherClusterDimension : ZGMTRContentLauncherClusterDimensionStruct
@property (nonatomic, copy) NSNumber * _Nonnull width ZGMTR_DEPRECATED("Please use ZGMTRContentLauncherClusterDimensionStruct", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
@property (nonatomic, copy) NSNumber * _Nonnull height ZGMTR_DEPRECATED("Please use ZGMTRContentLauncherClusterDimensionStruct", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
@property (nonatomic, copy) NSNumber * _Nonnull metric ZGMTR_DEPRECATED("Please use ZGMTRContentLauncherClusterDimensionStruct", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
@end

ZGMTR_PROVISIONALLY_AVAILABLE
@interface ZGMTRContentLauncherClusterContentAppInfo : NSObject <NSCopying>
@property (nonatomic, copy) NSNumber * _Nonnull contentAppVendorID ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSNumber * _Nonnull contentAppProductID ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSString * _Nonnull data ZGMTR_PROVISIONALLY_AVAILABLE;
@end

ZGMTR_PROVISIONALLY_AVAILABLE
@interface ZGMTRContentLauncherClusterLaunchUrlInfo : NSObject <NSCopying>
@property (nonatomic, copy) NSString * _Nonnull url ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSString * _Nullable data ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSString * _Nullable contentType ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSArray * _Nullable contentHeaders ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSNumber * _Nullable offsetMillisecs ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSNumber * _Nullable queueType ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSString * _Nullable nextUrl ZGMTR_PROVISIONALLY_AVAILABLE;
@end

ZGMTR_PROVISIONALLY_AVAILABLE
@interface ZGMTRContentLauncherClusterReplicationInfo : NSObject <NSCopying>
@property (nonatomic, copy) ZGMTRContentLauncherClusterLaunchUrlInfo * _Nullable launchUrlInfo ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) ZGMTRContentLauncherClusterContentAppInfo * _Nullable contentAppInfo ZGMTR_PROVISIONALLY_AVAILABLE;
@end

ZGMTR_PROVISIONALLY_AVAILABLE
@interface ZGMTRContentLauncherClusterTrackPreferenceStruct : NSObject <NSCopying>
@property (nonatomic, copy) NSString * _Nonnull languageCode ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSArray * _Nullable characteristics ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSNumber * _Nonnull audioOutputIndex ZGMTR_PROVISIONALLY_AVAILABLE;
@end

ZGMTR_PROVISIONALLY_AVAILABLE
@interface ZGMTRContentLauncherClusterPlaybackPreferencesStruct : NSObject <NSCopying>
@property (nonatomic, copy) NSNumber * _Nonnull playbackPosition ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) ZGMTRContentLauncherClusterTrackPreferenceStruct * _Nonnull textTrack ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSArray * _Nullable audioTracks ZGMTR_PROVISIONALLY_AVAILABLE;
@end

ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4))
@interface ZGMTRContentLauncherClusterAdditionalInfoStruct : NSObject <NSCopying>
@property (nonatomic, copy) NSString * _Nonnull name ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
@property (nonatomic, copy) NSString * _Nonnull value ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
@end

ZGMTR_DEPRECATED("Please use ZGMTRContentLauncherClusterAdditionalInfoStruct", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
@interface ZGMTRContentLauncherClusterAdditionalInfo : ZGMTRContentLauncherClusterAdditionalInfoStruct
@property (nonatomic, copy) NSString * _Nonnull name ZGMTR_DEPRECATED("Please use ZGMTRContentLauncherClusterAdditionalInfoStruct", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
@property (nonatomic, copy) NSString * _Nonnull value ZGMTR_DEPRECATED("Please use ZGMTRContentLauncherClusterAdditionalInfoStruct", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
@end

ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4))
@interface ZGMTRContentLauncherClusterParameterStruct : NSObject <NSCopying>
@property (nonatomic, copy) NSNumber * _Nonnull type ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
@property (nonatomic, copy) NSString * _Nonnull value ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
@property (nonatomic, copy) NSArray * _Nullable externalIDList ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
@end

ZGMTR_DEPRECATED("Please use ZGMTRContentLauncherClusterParameterStruct", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
@interface ZGMTRContentLauncherClusterParameter : ZGMTRContentLauncherClusterParameterStruct
@property (nonatomic, copy) NSNumber * _Nonnull type ZGMTR_DEPRECATED("Please use ZGMTRContentLauncherClusterParameterStruct", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
@property (nonatomic, copy) NSString * _Nonnull value ZGMTR_DEPRECATED("Please use ZGMTRContentLauncherClusterParameterStruct", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
@property (nonatomic, copy) NSArray * _Nullable externalIDList ZGMTR_DEPRECATED("Please use ZGMTRContentLauncherClusterParameterStruct", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
@end

ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4))
@interface ZGMTRContentLauncherClusterContentSearchStruct : NSObject <NSCopying>
@property (nonatomic, copy) NSArray * _Nonnull parameterList ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
@end

ZGMTR_DEPRECATED("Please use ZGMTRContentLauncherClusterContentSearchStruct", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
@interface ZGMTRContentLauncherClusterContentSearch : ZGMTRContentLauncherClusterContentSearchStruct
@property (nonatomic, copy) NSArray * _Nonnull parameterList ZGMTR_DEPRECATED("Please use ZGMTRContentLauncherClusterContentSearchStruct", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
@end

ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4))
@interface ZGMTRContentLauncherClusterStyleInformationStruct : NSObject <NSCopying>
@property (nonatomic, copy) NSString * _Nullable imageURL ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
@property (nonatomic, copy) NSString * _Nullable imageUrl ZGMTR_DEPRECATED("Please use imageURL", ios(16.4, 16.4), macos(13.3, 13.3), watchos(9.4, 9.4), tvos(16.4, 16.4));
@property (nonatomic, copy) NSString * _Nullable color ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
@property (nonatomic, copy) ZGMTRContentLauncherClusterDimensionStruct * _Nullable size ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
@end

ZGMTR_DEPRECATED("Please use ZGMTRContentLauncherClusterStyleInformationStruct", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
@interface ZGMTRContentLauncherClusterStyleInformation : ZGMTRContentLauncherClusterStyleInformationStruct
@property (nonatomic, copy) NSString * _Nullable color ZGMTR_DEPRECATED("Please use ZGMTRContentLauncherClusterStyleInformationStruct", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
@property (nonatomic, copy) ZGMTRContentLauncherClusterDimensionStruct * _Nullable size ZGMTR_DEPRECATED("Please use ZGMTRContentLauncherClusterStyleInformationStruct", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
@end

ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4))
@interface ZGMTRContentLauncherClusterBrandingInformationStruct : NSObject <NSCopying>
@property (nonatomic, copy) NSString * _Nonnull providerName ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
@property (nonatomic, copy) ZGMTRContentLauncherClusterStyleInformationStruct * _Nullable background ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
@property (nonatomic, copy) ZGMTRContentLauncherClusterStyleInformationStruct * _Nullable logo ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
@property (nonatomic, copy) ZGMTRContentLauncherClusterStyleInformationStruct * _Nullable progressBar ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
@property (nonatomic, copy) ZGMTRContentLauncherClusterStyleInformationStruct * _Nullable splash ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
@property (nonatomic, copy) ZGMTRContentLauncherClusterStyleInformationStruct * _Nullable waterMark ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
@end

ZGMTR_DEPRECATED("Please use ZGMTRContentLauncherClusterBrandingInformationStruct", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
@interface ZGMTRContentLauncherClusterBrandingInformation : ZGMTRContentLauncherClusterBrandingInformationStruct
@property (nonatomic, copy) NSString * _Nonnull providerName ZGMTR_DEPRECATED("Please use ZGMTRContentLauncherClusterBrandingInformationStruct", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
@property (nonatomic, copy) ZGMTRContentLauncherClusterStyleInformationStruct * _Nullable background ZGMTR_DEPRECATED("Please use ZGMTRContentLauncherClusterBrandingInformationStruct", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
@property (nonatomic, copy) ZGMTRContentLauncherClusterStyleInformationStruct * _Nullable logo ZGMTR_DEPRECATED("Please use ZGMTRContentLauncherClusterBrandingInformationStruct", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
@property (nonatomic, copy) ZGMTRContentLauncherClusterStyleInformationStruct * _Nullable progressBar ZGMTR_DEPRECATED("Please use ZGMTRContentLauncherClusterBrandingInformationStruct", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
@property (nonatomic, copy) ZGMTRContentLauncherClusterStyleInformationStruct * _Nullable splash ZGMTR_DEPRECATED("Please use ZGMTRContentLauncherClusterBrandingInformationStruct", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
@property (nonatomic, copy) ZGMTRContentLauncherClusterStyleInformationStruct * _Nullable waterMark ZGMTR_DEPRECATED("Please use ZGMTRContentLauncherClusterBrandingInformationStruct", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
@end

ZGMTR_PROVISIONALLY_AVAILABLE
@interface ZGMTRContentLauncherClusterContentPresetStruct : NSObject <NSCopying>
@property (nonatomic, copy) NSNumber * _Nonnull presetID ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSString * _Nonnull presetName ZGMTR_PROVISIONALLY_AVAILABLE;
@end

ZGMTR_PROVISIONALLY_AVAILABLE
@interface ZGMTRContentLauncherClusterContentReplicationEvent : NSObject <NSCopying>
@property (nonatomic, copy) NSNumber * _Nonnull status ZGMTR_PROVISIONALLY_AVAILABLE;
@end

ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4))
@interface ZGMTRAudioOutputClusterOutputInfoStruct : NSObject <NSCopying>
@property (nonatomic, copy) NSNumber * _Nonnull index ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
@property (nonatomic, copy) NSNumber * _Nonnull outputType ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
@property (nonatomic, copy) NSString * _Nonnull name ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
@end

ZGMTR_DEPRECATED("Please use ZGMTRAudioOutputClusterOutputInfoStruct", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
@interface ZGMTRAudioOutputClusterOutputInfo : ZGMTRAudioOutputClusterOutputInfoStruct
@property (nonatomic, copy) NSNumber * _Nonnull index ZGMTR_DEPRECATED("Please use ZGMTRAudioOutputClusterOutputInfoStruct", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
@property (nonatomic, copy) NSNumber * _Nonnull outputType ZGMTR_DEPRECATED("Please use ZGMTRAudioOutputClusterOutputInfoStruct", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
@property (nonatomic, copy) NSString * _Nonnull name ZGMTR_DEPRECATED("Please use ZGMTRAudioOutputClusterOutputInfoStruct", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
@end

ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4))
@interface ZGMTRApplicationLauncherClusterApplicationStruct : NSObject <NSCopying>
@property (nonatomic, copy) NSNumber * _Nonnull catalogVendorID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
@property (nonatomic, copy) NSNumber * _Nonnull catalogVendorId ZGMTR_DEPRECATED("Please use catalogVendorID", ios(16.4, 16.4), macos(13.3, 13.3), watchos(9.4, 9.4), tvos(16.4, 16.4));
@property (nonatomic, copy) NSString * _Nonnull applicationID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
@property (nonatomic, copy) NSString * _Nonnull applicationId ZGMTR_DEPRECATED("Please use applicationID", ios(16.4, 16.4), macos(13.3, 13.3), watchos(9.4, 9.4), tvos(16.4, 16.4));
@end

ZGMTR_DEPRECATED("Please use ZGMTRApplicationLauncherClusterApplicationStruct", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
@interface ZGMTRApplicationLauncherClusterApplication : ZGMTRApplicationLauncherClusterApplicationStruct
@end

ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4))
@interface ZGMTRApplicationLauncherClusterApplicationEPStruct : NSObject <NSCopying>
@property (nonatomic, copy) ZGMTRApplicationLauncherClusterApplicationStruct * _Nonnull application ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
@property (nonatomic, copy) NSNumber * _Nullable endpoint ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
@end

ZGMTR_DEPRECATED("Please use ZGMTRApplicationLauncherClusterApplicationEPStruct", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
@interface ZGMTRApplicationLauncherClusterApplicationEP : ZGMTRApplicationLauncherClusterApplicationEPStruct
@property (nonatomic, copy) ZGMTRApplicationLauncherClusterApplicationStruct * _Nonnull application ZGMTR_DEPRECATED("Please use ZGMTRApplicationLauncherClusterApplicationEPStruct", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
@property (nonatomic, copy) NSNumber * _Nullable endpoint ZGMTR_DEPRECATED("Please use ZGMTRApplicationLauncherClusterApplicationEPStruct", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
@end

ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4))
@interface ZGMTRApplicationBasicClusterApplicationStruct : NSObject <NSCopying>
@property (nonatomic, copy) NSNumber * _Nonnull catalogVendorID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
@property (nonatomic, copy) NSNumber * _Nonnull catalogVendorId ZGMTR_DEPRECATED("Please use catalogVendorID", ios(16.4, 16.4), macos(13.3, 13.3), watchos(9.4, 9.4), tvos(16.4, 16.4));
@property (nonatomic, copy) NSString * _Nonnull applicationID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
@property (nonatomic, copy) NSString * _Nonnull applicationId ZGMTR_DEPRECATED("Please use applicationID", ios(16.4, 16.4), macos(13.3, 13.3), watchos(9.4, 9.4), tvos(16.4, 16.4));
@end

ZGMTR_DEPRECATED("Please use ZGMTRApplicationBasicClusterApplicationStruct", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
@interface ZGMTRApplicationBasicClusterApplicationBasicApplication : ZGMTRApplicationBasicClusterApplicationStruct
@end

ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4))
@interface ZGMTRAccountLoginClusterLoggedOutEvent : NSObject <NSCopying>
@property (nonatomic, copy) NSNumber * _Nullable node ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));
@property (nonatomic, copy) NSNumber * _Nonnull fabricIndex ZGMTR_PROVISIONALLY_AVAILABLE;
@end

ZGMTR_PROVISIONALLY_AVAILABLE
@interface ZGMTRContentControlClusterTimePeriodStruct : NSObject <NSCopying>
@property (nonatomic, copy) NSNumber * _Nonnull startHour ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSNumber * _Nonnull startMinute ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSNumber * _Nonnull endHour ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSNumber * _Nonnull endMinute ZGMTR_PROVISIONALLY_AVAILABLE;
@end

ZGMTR_PROVISIONALLY_AVAILABLE
@interface ZGMTRContentControlClusterTimeWindowStruct : NSObject <NSCopying>
@property (nonatomic, copy) NSNumber * _Nullable timeWindowIndex ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSNumber * _Nonnull dayOfWeek ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSArray * _Nonnull timePeriod ZGMTR_PROVISIONALLY_AVAILABLE;
@end

ZGMTR_PROVISIONALLY_AVAILABLE
@interface ZGMTRContentControlClusterAppInfoStruct : NSObject <NSCopying>
@property (nonatomic, copy) NSNumber * _Nonnull catalogVendorID ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSString * _Nonnull applicationID ZGMTR_PROVISIONALLY_AVAILABLE;
@end

ZGMTR_PROVISIONALLY_AVAILABLE
@interface ZGMTRContentControlClusterBlockChannelStruct : NSObject <NSCopying>
@property (nonatomic, copy) NSNumber * _Nullable blockChannelIndex ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSNumber * _Nonnull majorNumber ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSNumber * _Nonnull minorNumber ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSString * _Nullable identifier ZGMTR_PROVISIONALLY_AVAILABLE;
@end

ZGMTR_PROVISIONALLY_AVAILABLE
@interface ZGMTRContentControlClusterRatingNameStruct : NSObject <NSCopying>
@property (nonatomic, copy) NSString * _Nonnull ratingName ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSString * _Nullable ratingNameDesc ZGMTR_PROVISIONALLY_AVAILABLE;
@end

ZGMTR_PROVISIONALLY_AVAILABLE
@interface ZGMTRContentControlClusterRemainingScreenTimeExpiredEvent : NSObject <NSCopying>
@end

ZGMTR_PROVISIONALLY_AVAILABLE
@interface ZGMTRContentControlClusterEnteringBlockContentTimeWindowEvent : NSObject <NSCopying>
@end

ZGMTR_PROVISIONALLY_AVAILABLE
@interface ZGMTRMediaFileManagementClusterFileDescriptionStruct : NSObject <NSCopying>
@property (nonatomic, copy) NSNumber * _Nonnull fileID ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSString * _Nonnull name ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSNumber * _Nonnull size ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSString * _Nonnull mimeType ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSString * _Nonnull imageUri ZGMTR_PROVISIONALLY_AVAILABLE;
@end

ZGMTR_PROVISIONALLY_AVAILABLE
@interface ZGMTRMediaFileManagementClusterSharedFilesAddedEvent : NSObject <NSCopying>
@property (nonatomic, copy) NSNumber * _Nonnull requestID ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSNumber * _Nonnull responseID ZGMTR_PROVISIONALLY_AVAILABLE;
@end

ZGMTR_PROVISIONALLY_AVAILABLE
@interface ZGMTRZoneManagementClusterTwoDCartesianVertexStruct : NSObject <NSCopying>
@property (nonatomic, copy) NSNumber * _Nonnull x ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSNumber * _Nonnull y ZGMTR_PROVISIONALLY_AVAILABLE;
@end

ZGMTR_PROVISIONALLY_AVAILABLE
@interface ZGMTRZoneManagementClusterTwoDCartesianZoneStruct : NSObject <NSCopying>
@property (nonatomic, copy) NSString * _Nonnull name ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSNumber * _Nonnull use ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSArray * _Nonnull vertices ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSString * _Nullable color ZGMTR_PROVISIONALLY_AVAILABLE;
@end

ZGMTR_PROVISIONALLY_AVAILABLE
@interface ZGMTRZoneManagementClusterZoneInformationStruct : NSObject <NSCopying>
@property (nonatomic, copy) NSNumber * _Nonnull zoneID ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSNumber * _Nonnull zoneType ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSNumber * _Nonnull zoneSource ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) ZGMTRZoneManagementClusterTwoDCartesianZoneStruct * _Nullable twoDCartesianZone ZGMTR_PROVISIONALLY_AVAILABLE;
@end

ZGMTR_PROVISIONALLY_AVAILABLE
@interface ZGMTRZoneManagementClusterZoneTriggerControlStruct : NSObject <NSCopying>
@property (nonatomic, copy) NSNumber * _Nonnull zoneID ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSNumber * _Nonnull initialDuration ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSNumber * _Nonnull augmentationDuration ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSNumber * _Nonnull maxDuration ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSNumber * _Nonnull blindDuration ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSNumber * _Nullable sensitivity ZGMTR_PROVISIONALLY_AVAILABLE;
@end

ZGMTR_PROVISIONALLY_AVAILABLE
@interface ZGMTRZoneManagementClusterZoneTriggeredEvent : NSObject <NSCopying>
@property (nonatomic, copy) NSNumber * _Nonnull zone ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSNumber * _Nonnull reason ZGMTR_PROVISIONALLY_AVAILABLE;
@end

ZGMTR_PROVISIONALLY_AVAILABLE
@interface ZGMTRZoneManagementClusterZoneStoppedEvent : NSObject <NSCopying>
@property (nonatomic, copy) NSNumber * _Nonnull zone ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSNumber * _Nonnull reason ZGMTR_PROVISIONALLY_AVAILABLE;
@end

ZGMTR_PROVISIONALLY_AVAILABLE
@interface ZGMTRCameraAVStreamManagementClusterVideoResolutionStruct : NSObject <NSCopying>
@property (nonatomic, copy) NSNumber * _Nonnull width ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSNumber * _Nonnull height ZGMTR_PROVISIONALLY_AVAILABLE;
@end

ZGMTR_PROVISIONALLY_AVAILABLE
@interface ZGMTRCameraAVStreamManagementClusterVideoStreamStruct : NSObject <NSCopying>
@property (nonatomic, copy) NSNumber * _Nonnull videoStreamID ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSNumber * _Nonnull streamUsage ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSNumber * _Nonnull videoCodec ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSNumber * _Nonnull minFrameRate ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSNumber * _Nonnull maxFrameRate ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) ZGMTRCameraAVStreamManagementClusterVideoResolutionStruct * _Nonnull minResolution ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) ZGMTRCameraAVStreamManagementClusterVideoResolutionStruct * _Nonnull maxResolution ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSNumber * _Nonnull minBitRate ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSNumber * _Nonnull maxBitRate ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSNumber * _Nonnull keyFrameInterval ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSNumber * _Nullable watermarkEnabled ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSNumber * _Nullable osdEnabled ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSNumber * _Nonnull referenceCount ZGMTR_PROVISIONALLY_AVAILABLE;
@end

ZGMTR_PROVISIONALLY_AVAILABLE
@interface ZGMTRCameraAVStreamManagementClusterSnapshotStreamStruct : NSObject <NSCopying>
@property (nonatomic, copy) NSNumber * _Nonnull snapshotStreamID ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSNumber * _Nonnull imageCodec ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSNumber * _Nonnull frameRate ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) ZGMTRCameraAVStreamManagementClusterVideoResolutionStruct * _Nonnull minResolution ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) ZGMTRCameraAVStreamManagementClusterVideoResolutionStruct * _Nonnull maxResolution ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSNumber * _Nonnull quality ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSNumber * _Nonnull referenceCount ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSNumber * _Nonnull encodedPixels ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSNumber * _Nonnull hardwareEncoder ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSNumber * _Nullable watermarkEnabled ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSNumber * _Nullable osdEnabled ZGMTR_PROVISIONALLY_AVAILABLE;
@end

ZGMTR_PROVISIONALLY_AVAILABLE
@interface ZGMTRCameraAVStreamManagementClusterSnapshotCapabilitiesStruct : NSObject <NSCopying>
@property (nonatomic, copy) ZGMTRCameraAVStreamManagementClusterVideoResolutionStruct * _Nonnull resolution ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSNumber * _Nonnull maxFrameRate ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSNumber * _Nonnull imageCodec ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSNumber * _Nonnull requiresEncodedPixels ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSNumber * _Nullable requiresHardwareEncoder ZGMTR_PROVISIONALLY_AVAILABLE;
@end

ZGMTR_PROVISIONALLY_AVAILABLE
@interface ZGMTRCameraAVStreamManagementClusterRateDistortionTradeOffPointsStruct : NSObject <NSCopying>
@property (nonatomic, copy) NSNumber * _Nonnull codec ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) ZGMTRCameraAVStreamManagementClusterVideoResolutionStruct * _Nonnull resolution ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSNumber * _Nonnull minBitRate ZGMTR_PROVISIONALLY_AVAILABLE;
@end

ZGMTR_PROVISIONALLY_AVAILABLE
@interface ZGMTRCameraAVStreamManagementClusterAudioCapabilitiesStruct : NSObject <NSCopying>
@property (nonatomic, copy) NSNumber * _Nonnull maxNumberOfChannels ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSArray * _Nonnull supportedCodecs ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSArray * _Nonnull supportedSampleRates ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSArray * _Nonnull supportedBitDepths ZGMTR_PROVISIONALLY_AVAILABLE;
@end

ZGMTR_PROVISIONALLY_AVAILABLE
@interface ZGMTRCameraAVStreamManagementClusterAudioStreamStruct : NSObject <NSCopying>
@property (nonatomic, copy) NSNumber * _Nonnull audioStreamID ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSNumber * _Nonnull streamUsage ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSNumber * _Nonnull audioCodec ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSNumber * _Nonnull channelCount ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSNumber * _Nonnull sampleRate ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSNumber * _Nonnull bitRate ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSNumber * _Nonnull bitDepth ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSNumber * _Nonnull referenceCount ZGMTR_PROVISIONALLY_AVAILABLE;
@end

ZGMTR_PROVISIONALLY_AVAILABLE
@interface ZGMTRCameraAVStreamManagementClusterVideoSensorParamsStruct : NSObject <NSCopying>
@property (nonatomic, copy) NSNumber * _Nonnull sensorWidth ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSNumber * _Nonnull sensorHeight ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSNumber * _Nonnull maxFPS ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSNumber * _Nullable maxHDRFPS ZGMTR_PROVISIONALLY_AVAILABLE;
@end

ZGMTR_PROVISIONALLY_AVAILABLE
@interface ZGMTRCameraAVSettingsUserLevelManagementClusterMPTZStruct : NSObject <NSCopying>
@property (nonatomic, copy) NSNumber * _Nullable pan ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSNumber * _Nullable tilt ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSNumber * _Nullable zoom ZGMTR_PROVISIONALLY_AVAILABLE;
@end

ZGMTR_PROVISIONALLY_AVAILABLE
@interface ZGMTRCameraAVSettingsUserLevelManagementClusterMPTZPresetStruct : NSObject <NSCopying>
@property (nonatomic, copy) NSNumber * _Nonnull presetID ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSString * _Nonnull name ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) ZGMTRCameraAVSettingsUserLevelManagementClusterMPTZStruct * _Nonnull settings ZGMTR_PROVISIONALLY_AVAILABLE;
@end

ZGMTR_PROVISIONALLY_AVAILABLE
@interface ZGMTRCameraAVSettingsUserLevelManagementClusterDPTZStruct : NSObject <NSCopying>
@property (nonatomic, copy) NSNumber * _Nonnull videoStreamID ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) ZGMTRDataTypeViewportStruct * _Nonnull viewport ZGMTR_PROVISIONALLY_AVAILABLE;
@end

ZGMTR_PROVISIONALLY_AVAILABLE
@interface ZGMTRWebRTCTransportProviderClusterSFrameStruct : NSObject <NSCopying>
@property (nonatomic, copy) NSNumber * _Nonnull cipherSuite ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSData * _Nonnull baseKey ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSData * _Nonnull kid ZGMTR_PROVISIONALLY_AVAILABLE;
@end

ZGMTR_PROVISIONALLY_AVAILABLE
@interface ZGMTRPushAVStreamTransportClusterTransportMotionTriggerTimeControlStruct : NSObject <NSCopying>
@property (nonatomic, copy) NSNumber * _Nonnull initialDuration ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSNumber * _Nonnull augmentationDuration ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSNumber * _Nonnull maxDuration ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSNumber * _Nonnull blindDuration ZGMTR_PROVISIONALLY_AVAILABLE;
@end

ZGMTR_PROVISIONALLY_AVAILABLE
@interface ZGMTRPushAVStreamTransportClusterTransportZoneOptionsStruct : NSObject <NSCopying>
@property (nonatomic, copy) NSNumber * _Nullable zone ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSNumber * _Nullable sensitivity ZGMTR_PROVISIONALLY_AVAILABLE;
@end

ZGMTR_PROVISIONALLY_AVAILABLE
@interface ZGMTRPushAVStreamTransportClusterAudioStreamStruct : NSObject <NSCopying>
@property (nonatomic, copy) NSString * _Nonnull audioStreamName ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSNumber * _Nonnull audioStreamID ZGMTR_PROVISIONALLY_AVAILABLE;
@end

ZGMTR_PROVISIONALLY_AVAILABLE
@interface ZGMTRPushAVStreamTransportClusterVideoStreamStruct : NSObject <NSCopying>
@property (nonatomic, copy) NSString * _Nonnull videoStreamName ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSNumber * _Nonnull videoStreamID ZGMTR_PROVISIONALLY_AVAILABLE;
@end

ZGMTR_PROVISIONALLY_AVAILABLE
@interface ZGMTRPushAVStreamTransportClusterTransportTriggerOptionsStruct : NSObject <NSCopying>
@property (nonatomic, copy) NSNumber * _Nonnull triggerType ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSArray * _Nullable motionZones ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSNumber * _Nullable motionSensitivity ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) ZGMTRPushAVStreamTransportClusterTransportMotionTriggerTimeControlStruct * _Nullable motionTimeControl ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSNumber * _Nullable maxPreRollLen ZGMTR_PROVISIONALLY_AVAILABLE;
@end

ZGMTR_PROVISIONALLY_AVAILABLE
@interface ZGMTRPushAVStreamTransportClusterCMAFContainerOptionsStruct : NSObject <NSCopying>
@property (nonatomic, copy) NSNumber * _Nonnull cmafInterface ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSNumber * _Nonnull segmentDuration ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSNumber * _Nonnull chunkDuration ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSNumber * _Nullable sessionGroup ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSString * _Nullable trackName ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSNumber * _Nullable metadataEnabled ZGMTR_PROVISIONALLY_AVAILABLE;
@end

ZGMTR_PROVISIONALLY_AVAILABLE
@interface ZGMTRPushAVStreamTransportClusterContainerOptionsStruct : NSObject <NSCopying>
@property (nonatomic, copy) NSNumber * _Nonnull containerType ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) ZGMTRPushAVStreamTransportClusterCMAFContainerOptionsStruct * _Nullable cmafContainerOptions ZGMTR_PROVISIONALLY_AVAILABLE;
@end

ZGMTR_PROVISIONALLY_AVAILABLE
@interface ZGMTRPushAVStreamTransportClusterTransportOptionsStruct : NSObject <NSCopying>
@property (nonatomic, copy) NSNumber * _Nonnull streamUsage ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSNumber * _Nullable videoStreamID ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSNumber * _Nullable audioStreamID ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSNumber * _Nonnull tlsEndpointID ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSString * _Nonnull url ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) ZGMTRPushAVStreamTransportClusterTransportTriggerOptionsStruct * _Nonnull triggerOptions ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSNumber * _Nonnull ingestMethod ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) ZGMTRPushAVStreamTransportClusterContainerOptionsStruct * _Nonnull containerOptions ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSNumber * _Nullable expiryTime ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSArray * _Nullable videoStreams ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSArray * _Nullable audioStreams ZGMTR_PROVISIONALLY_AVAILABLE;
@end

ZGMTR_PROVISIONALLY_AVAILABLE
@interface ZGMTRPushAVStreamTransportClusterTransportConfigurationStruct : NSObject <NSCopying>
@property (nonatomic, copy) NSNumber * _Nonnull connectionID ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSNumber * _Nonnull transportStatus ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) ZGMTRPushAVStreamTransportClusterTransportOptionsStruct * _Nullable transportOptions ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSNumber * _Nonnull fabricIndex ZGMTR_PROVISIONALLY_AVAILABLE;
@end

ZGMTR_PROVISIONALLY_AVAILABLE
@interface ZGMTRPushAVStreamTransportClusterSupportedFormatStruct : NSObject <NSCopying>
@property (nonatomic, copy) NSNumber * _Nonnull containerFormat ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSNumber * _Nonnull ingestMethod ZGMTR_PROVISIONALLY_AVAILABLE;
@end

ZGMTR_PROVISIONALLY_AVAILABLE
@interface ZGMTRPushAVStreamTransportClusterPushTransportBeginEvent : NSObject <NSCopying>
@property (nonatomic, copy) NSNumber * _Nonnull connectionID ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSNumber * _Nonnull triggerType ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSNumber * _Nullable activationReason ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSNumber * _Nullable containerType ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSNumber * _Nullable cmafSessionNumber ZGMTR_PROVISIONALLY_AVAILABLE;
@end

ZGMTR_PROVISIONALLY_AVAILABLE
@interface ZGMTRPushAVStreamTransportClusterPushTransportEndEvent : NSObject <NSCopying>
@property (nonatomic, copy) NSNumber * _Nonnull connectionID ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSNumber * _Nullable containerType ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSNumber * _Nullable cmafSessionNumber ZGMTR_PROVISIONALLY_AVAILABLE;
@end

ZGMTR_PROVISIONALLY_AVAILABLE
@interface ZGMTRChimeClusterChimeSoundStruct : NSObject <NSCopying>
@property (nonatomic, copy) NSNumber * _Nonnull chimeID ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSString * _Nonnull name ZGMTR_PROVISIONALLY_AVAILABLE;
@end

ZGMTR_PROVISIONALLY_AVAILABLE
@interface ZGMTRChimeClusterChimeStartedPlayingEvent : NSObject <NSCopying>
@property (nonatomic, copy) NSNumber * _Nonnull chimeID ZGMTR_PROVISIONALLY_AVAILABLE;
@end

ZGMTR_PROVISIONALLY_AVAILABLE
@interface ZGMTRAVAnalysisClusterAnalysisStreamStruct : NSObject <NSCopying>
@property (nonatomic, copy) NSNumber * _Nonnull analysisStreamID ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSNumber * _Nullable webRTCEndpointID ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSNumber * _Nullable pushAVEndpointID ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSNumber * _Nonnull analysisStreamState ZGMTR_PROVISIONALLY_AVAILABLE;
@end

ZGMTR_PROVISIONALLY_AVAILABLE
@interface ZGMTRAVAnalysisClusterContextTriggerStruct : NSObject <NSCopying>
@property (nonatomic, copy) ZGMTRDataTypeSemanticTagStruct * _Nonnull context ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSArray * _Nullable zoneIDs ZGMTR_PROVISIONALLY_AVAILABLE;
@end

ZGMTR_PROVISIONALLY_AVAILABLE
@interface ZGMTRAVAnalysisClusterTrackedContext : NSObject <NSCopying>
@property (nonatomic, copy) NSNumber * _Nonnull identifiedContextID ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) ZGMTRDataTypeSemanticTagStruct * _Nonnull identifiedContext ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSNumber * _Nullable previousZone ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSNumber * _Nullable currentZone ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSNumber * _Nonnull startTime ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSNumber * _Nullable endTime ZGMTR_PROVISIONALLY_AVAILABLE;
@end

ZGMTR_PROVISIONALLY_AVAILABLE
@interface ZGMTRAVAnalysisClusterAnalysisSessionStartEvent : NSObject <NSCopying>
@property (nonatomic, copy) NSNumber * _Nonnull sessionID ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSNumber * _Nullable sourceNodeId ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSArray * _Nullable triggeredZones ZGMTR_PROVISIONALLY_AVAILABLE;
@end

ZGMTR_PROVISIONALLY_AVAILABLE
@interface ZGMTRAVAnalysisClusterAnalysisSessionEndEvent : NSObject <NSCopying>
@property (nonatomic, copy) NSNumber * _Nonnull sessionID ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSNumber * _Nullable sourceNodeId ZGMTR_PROVISIONALLY_AVAILABLE;
@end

ZGMTR_PROVISIONALLY_AVAILABLE
@interface ZGMTRAVAnalysisClusterPerceivedContextEvent : NSObject <NSCopying>
@property (nonatomic, copy) NSNumber * _Nonnull sessionID ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSNumber * _Nullable sourceNodeId ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSNumber * _Nullable sourceStartTimestamp ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy, getter=getNewIdentifiedContexts) NSArray * _Nullable newIdentifiedContexts ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSArray * _Nullable currentIdentifiedContexts ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSArray * _Nullable expiredContexts ZGMTR_PROVISIONALLY_AVAILABLE;
@end

ZGMTR_PROVISIONALLY_AVAILABLE
@interface ZGMTRCommodityTariffClusterPeakPeriodStruct : NSObject <NSCopying>
@property (nonatomic, copy) NSNumber * _Nonnull severity ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSNumber * _Nonnull peakPeriod ZGMTR_PROVISIONALLY_AVAILABLE;
@end

ZGMTR_PROVISIONALLY_AVAILABLE
@interface ZGMTRCommodityTariffClusterAuxiliaryLoadSwitchSettingsStruct : NSObject <NSCopying>
@property (nonatomic, copy) NSNumber * _Nonnull number ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSNumber * _Nonnull requiredState ZGMTR_PROVISIONALLY_AVAILABLE;
@end

ZGMTR_PROVISIONALLY_AVAILABLE
@interface ZGMTRCommodityTariffClusterTariffPriceStruct : NSObject <NSCopying>
@property (nonatomic, copy) NSNumber * _Nonnull priceType ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSNumber * _Nullable price ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSNumber * _Nullable priceLevel ZGMTR_PROVISIONALLY_AVAILABLE;
@end

ZGMTR_PROVISIONALLY_AVAILABLE
@interface ZGMTRCommodityTariffClusterTariffComponentStruct : NSObject <NSCopying>
@property (nonatomic, copy) NSNumber * _Nonnull tariffComponentID ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) ZGMTRCommodityTariffClusterTariffPriceStruct * _Nullable price ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSNumber * _Nullable friendlyCredit ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) ZGMTRCommodityTariffClusterAuxiliaryLoadSwitchSettingsStruct * _Nullable auxiliaryLoad ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) ZGMTRCommodityTariffClusterPeakPeriodStruct * _Nullable peakPeriod ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) ZGMTRDataTypePowerThresholdStruct * _Nullable powerThreshold ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSNumber * _Nullable threshold ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSString * _Nullable label ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSNumber * _Nullable predicted ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSString * _Nullable externalID ZGMTR_PROVISIONALLY_AVAILABLE;
@end

ZGMTR_PROVISIONALLY_AVAILABLE
@interface ZGMTRCommodityTariffClusterCalendarPeriodStruct : NSObject <NSCopying>
@property (nonatomic, copy) NSNumber * _Nullable startDate ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSArray * _Nonnull dayPatternIDs ZGMTR_PROVISIONALLY_AVAILABLE;
@end

ZGMTR_PROVISIONALLY_AVAILABLE
@interface ZGMTRCommodityTariffClusterDayEntryStruct : NSObject <NSCopying>
@property (nonatomic, copy) NSNumber * _Nonnull dayEntryID ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSNumber * _Nonnull startTime ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSNumber * _Nullable duration ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSNumber * _Nullable randomizationOffset ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSNumber * _Nullable randomizationType ZGMTR_PROVISIONALLY_AVAILABLE;
@end

ZGMTR_PROVISIONALLY_AVAILABLE
@interface ZGMTRCommodityTariffClusterDayPatternStruct : NSObject <NSCopying>
@property (nonatomic, copy) NSNumber * _Nonnull dayPatternID ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSNumber * _Nonnull daysOfWeek ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSArray * _Nonnull dayEntryIDs ZGMTR_PROVISIONALLY_AVAILABLE;
@end

ZGMTR_PROVISIONALLY_AVAILABLE
@interface ZGMTRCommodityTariffClusterDayStruct : NSObject <NSCopying>
@property (nonatomic, copy) NSNumber * _Nonnull date ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSNumber * _Nonnull dayType ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSArray * _Nonnull dayEntryIDs ZGMTR_PROVISIONALLY_AVAILABLE;
@end

ZGMTR_PROVISIONALLY_AVAILABLE
@interface ZGMTRCommodityTariffClusterTariffInformationStruct : NSObject <NSCopying>
@property (nonatomic, copy) NSString * _Nullable tariffLabel ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSString * _Nullable providerName ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) ZGMTRDataTypeCurrencyStruct * _Nullable currency ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSNumber * _Nullable blockMode ZGMTR_PROVISIONALLY_AVAILABLE;
@end

ZGMTR_PROVISIONALLY_AVAILABLE
@interface ZGMTRCommodityTariffClusterTariffPeriodStruct : NSObject <NSCopying>
@property (nonatomic, copy) NSString * _Nullable label ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSArray * _Nonnull dayEntryIDs ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSArray * _Nonnull tariffComponentIDs ZGMTR_PROVISIONALLY_AVAILABLE;
@end

ZGMTR_PROVISIONALLY_AVAILABLE
@interface ZGMTREcosystemInformationClusterDeviceTypeStruct : NSObject <NSCopying>
@property (nonatomic, copy) NSNumber * _Nonnull deviceType ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSNumber * _Nonnull revision ZGMTR_PROVISIONALLY_AVAILABLE;
@end

ZGMTR_PROVISIONALLY_AVAILABLE
@interface ZGMTREcosystemInformationClusterEcosystemDeviceStruct : NSObject <NSCopying>
@property (nonatomic, copy) NSString * _Nullable deviceName ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSNumber * _Nullable deviceNameLastEdit ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSNumber * _Nonnull bridgedEndpoint ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSNumber * _Nonnull originalEndpoint ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSArray * _Nonnull deviceTypes ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSArray * _Nonnull uniqueLocationIDs ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSNumber * _Nonnull uniqueLocationIDsLastEdit ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSNumber * _Nonnull fabricIndex ZGMTR_PROVISIONALLY_AVAILABLE;
@end

ZGMTR_PROVISIONALLY_AVAILABLE
@interface ZGMTREcosystemInformationClusterEcosystemLocationStruct : NSObject <NSCopying>
@property (nonatomic, copy) NSString * _Nonnull uniqueLocationID ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) ZGMTRDataTypeLocationDescriptorStruct * _Nonnull locationDescriptor ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSNumber * _Nonnull locationDescriptorLastEdit ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSNumber * _Nonnull fabricIndex ZGMTR_PROVISIONALLY_AVAILABLE;
@end

ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4))
@interface ZGMTRCommissionerControlClusterCommissioningRequestResultEvent : NSObject <NSCopying>
@property (nonatomic, copy) NSNumber * _Nonnull requestID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));
@property (nonatomic, copy) NSNumber * _Nonnull clientNodeID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));
@property (nonatomic, copy) NSNumber * _Nonnull statusCode ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));
@property (nonatomic, copy) NSNumber * _Nonnull fabricIndex ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4));
@end

ZGMTR_PROVISIONALLY_AVAILABLE
@interface ZGMTRJointFabricDatastoreClusterDatastoreStatusEntryStruct : NSObject <NSCopying>
@property (nonatomic, copy) NSNumber * _Nonnull state ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSNumber * _Nonnull updateTimestamp ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSNumber * _Nonnull failureCode ZGMTR_PROVISIONALLY_AVAILABLE;
@end

ZGMTR_PROVISIONALLY_AVAILABLE
@interface ZGMTRJointFabricDatastoreClusterDatastoreNodeKeySetEntryStruct : NSObject <NSCopying>
@property (nonatomic, copy) NSNumber * _Nonnull nodeID ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSNumber * _Nonnull groupKeySetID ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) ZGMTRJointFabricDatastoreClusterDatastoreStatusEntryStruct * _Nonnull statusEntry ZGMTR_PROVISIONALLY_AVAILABLE;
@end

ZGMTR_PROVISIONALLY_AVAILABLE
@interface ZGMTRJointFabricDatastoreClusterDatastoreNodeInformationEntryStruct : NSObject <NSCopying>
@property (nonatomic, copy) NSNumber * _Nonnull nodeID ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSString * _Nonnull friendlyName ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) ZGMTRJointFabricDatastoreClusterDatastoreStatusEntryStruct * _Nonnull commissioningStatusEntry ZGMTR_PROVISIONALLY_AVAILABLE;
@end

ZGMTR_PROVISIONALLY_AVAILABLE
@interface ZGMTRJointFabricDatastoreClusterDatastoreEndpointGroupIDEntryStruct : NSObject <NSCopying>
@property (nonatomic, copy) NSNumber * _Nonnull nodeID ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSNumber * _Nonnull endpointID ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSNumber * _Nonnull groupID ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) ZGMTRJointFabricDatastoreClusterDatastoreStatusEntryStruct * _Nonnull statusEntry ZGMTR_PROVISIONALLY_AVAILABLE;
@end

ZGMTR_PROVISIONALLY_AVAILABLE
@interface ZGMTRJointFabricDatastoreClusterDatastoreBindingTargetStruct : NSObject <NSCopying>
@property (nonatomic, copy) NSNumber * _Nullable node ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSNumber * _Nullable group ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSNumber * _Nullable endpoint ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSNumber * _Nullable cluster ZGMTR_PROVISIONALLY_AVAILABLE;
@end

ZGMTR_PROVISIONALLY_AVAILABLE
@interface ZGMTRJointFabricDatastoreClusterDatastoreEndpointBindingEntryStruct : NSObject <NSCopying>
@property (nonatomic, copy) NSNumber * _Nonnull nodeID ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSNumber * _Nonnull endpointID ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSNumber * _Nonnull listID ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) ZGMTRJointFabricDatastoreClusterDatastoreBindingTargetStruct * _Nonnull binding ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) ZGMTRJointFabricDatastoreClusterDatastoreStatusEntryStruct * _Nonnull statusEntry ZGMTR_PROVISIONALLY_AVAILABLE;
@end

ZGMTR_PROVISIONALLY_AVAILABLE
@interface ZGMTRJointFabricDatastoreClusterDatastoreAccessControlTargetStruct : NSObject <NSCopying>
@property (nonatomic, copy) NSNumber * _Nullable cluster ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSNumber * _Nullable endpoint ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSNumber * _Nullable deviceType ZGMTR_PROVISIONALLY_AVAILABLE;
@end

ZGMTR_PROVISIONALLY_AVAILABLE
@interface ZGMTRJointFabricDatastoreClusterDatastoreAccessControlEntryStruct : NSObject <NSCopying>
@property (nonatomic, copy) NSNumber * _Nonnull privilege ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSNumber * _Nonnull authMode ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSArray * _Nullable subjects ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSArray * _Nullable targets ZGMTR_PROVISIONALLY_AVAILABLE;
@end

ZGMTR_PROVISIONALLY_AVAILABLE
@interface ZGMTRJointFabricDatastoreClusterDatastoreACLEntryStruct : NSObject <NSCopying>
@property (nonatomic, copy) NSNumber * _Nonnull nodeID ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSNumber * _Nonnull listID ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) ZGMTRJointFabricDatastoreClusterDatastoreAccessControlEntryStruct * _Nonnull aclEntry ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) ZGMTRJointFabricDatastoreClusterDatastoreStatusEntryStruct * _Nonnull statusEntry ZGMTR_PROVISIONALLY_AVAILABLE;
@end

ZGMTR_PROVISIONALLY_AVAILABLE
@interface ZGMTRJointFabricDatastoreClusterDatastoreAdministratorInformationEntryStruct : NSObject <NSCopying>
@property (nonatomic, copy) NSNumber * _Nonnull nodeID ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSString * _Nonnull friendlyName ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSNumber * _Nonnull vendorID ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSData * _Nonnull icac ZGMTR_PROVISIONALLY_AVAILABLE;
@end

ZGMTR_PROVISIONALLY_AVAILABLE
@interface ZGMTRJointFabricDatastoreClusterDatastoreEndpointEntryStruct : NSObject <NSCopying>
@property (nonatomic, copy) NSNumber * _Nonnull endpointID ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSNumber * _Nonnull nodeID ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSString * _Nonnull friendlyName ZGMTR_PROVISIONALLY_AVAILABLE;
@end

ZGMTR_PROVISIONALLY_AVAILABLE
@interface ZGMTRJointFabricDatastoreClusterDatastoreGroupInformationEntryStruct : NSObject <NSCopying>
@property (nonatomic, copy) NSNumber * _Nonnull groupID ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSString * _Nonnull friendlyName ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSNumber * _Nullable groupKeySetID ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSNumber * _Nullable groupCAT ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSNumber * _Nullable groupCATVersion ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSNumber * _Nonnull groupPermission ZGMTR_PROVISIONALLY_AVAILABLE;
@end

ZGMTR_PROVISIONALLY_AVAILABLE
@interface ZGMTRJointFabricDatastoreClusterDatastoreGroupKeySetStruct : NSObject <NSCopying>
@property (nonatomic, copy) NSNumber * _Nonnull groupKeySetID ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSNumber * _Nonnull groupKeySecurityPolicy ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSData * _Nullable epochKey0 ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSNumber * _Nullable epochStartTime0 ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSData * _Nullable epochKey1 ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSNumber * _Nullable epochStartTime1 ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSData * _Nullable epochKey2 ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSNumber * _Nullable epochStartTime2 ZGMTR_PROVISIONALLY_AVAILABLE;
@end

ZGMTR_PROVISIONALLY_AVAILABLE
@interface ZGMTRTLSCertificateManagementClusterTLSCertStruct : NSObject <NSCopying>
@property (nonatomic, copy) NSNumber * _Nonnull caid ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSData * _Nullable certificate ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSNumber * _Nonnull fabricIndex ZGMTR_PROVISIONALLY_AVAILABLE;
@end

ZGMTR_PROVISIONALLY_AVAILABLE
@interface ZGMTRTLSCertificateManagementClusterTLSClientCertificateDetailStruct : NSObject <NSCopying>
@property (nonatomic, copy) NSNumber * _Nonnull ccdid ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSData * _Nullable clientCertificate ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSArray * _Nullable intermediateCertificates ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSNumber * _Nonnull fabricIndex ZGMTR_PROVISIONALLY_AVAILABLE;
@end

ZGMTR_PROVISIONALLY_AVAILABLE
@interface ZGMTRTLSClientManagementClusterTLSEndpointStruct : NSObject <NSCopying>
@property (nonatomic, copy) NSNumber * _Nonnull endpointID ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSData * _Nonnull hostname ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSNumber * _Nonnull port ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSNumber * _Nonnull caid ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSNumber * _Nullable ccdid ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSNumber * _Nonnull referenceCount ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSNumber * _Nonnull fabricIndex ZGMTR_PROVISIONALLY_AVAILABLE;
@end

ZGMTR_PROVISIONALLY_AVAILABLE
@interface ZGMTRCommodityMeteringClusterMeteredQuantityStruct : NSObject <NSCopying>
@property (nonatomic, copy) NSArray * _Nonnull tariffComponentIDs ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSNumber * _Nonnull quantity ZGMTR_PROVISIONALLY_AVAILABLE;
@end

ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4))
@interface ZGMTRUnitTestingClusterSimpleStruct : NSObject <NSCopying>
@property (nonatomic, copy) NSNumber * _Nonnull a ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
@property (nonatomic, copy) NSNumber * _Nonnull b ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
@property (nonatomic, copy) NSNumber * _Nonnull c ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
@property (nonatomic, copy) NSData * _Nonnull d ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
@property (nonatomic, copy) NSString * _Nonnull e ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
@property (nonatomic, copy) NSNumber * _Nonnull f ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
@property (nonatomic, copy) NSNumber * _Nonnull g ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
@property (nonatomic, copy) NSNumber * _Nonnull h ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
@property (nonatomic, copy) NSNumber * _Nullable i ZGMTR_PROVISIONALLY_AVAILABLE;
@end

ZGMTR_DEPRECATED("Please use ZGMTRUnitTestingClusterSimpleStruct", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
@interface ZGMTRTestClusterClusterSimpleStruct : ZGMTRUnitTestingClusterSimpleStruct
@property (nonatomic, copy) NSNumber * _Nonnull a ZGMTR_DEPRECATED("Please use ZGMTRUnitTestingClusterSimpleStruct", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
@property (nonatomic, copy) NSNumber * _Nonnull b ZGMTR_DEPRECATED("Please use ZGMTRUnitTestingClusterSimpleStruct", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
@property (nonatomic, copy) NSNumber * _Nonnull c ZGMTR_DEPRECATED("Please use ZGMTRUnitTestingClusterSimpleStruct", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
@property (nonatomic, copy) NSData * _Nonnull d ZGMTR_DEPRECATED("Please use ZGMTRUnitTestingClusterSimpleStruct", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
@property (nonatomic, copy) NSString * _Nonnull e ZGMTR_DEPRECATED("Please use ZGMTRUnitTestingClusterSimpleStruct", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
@property (nonatomic, copy) NSNumber * _Nonnull f ZGMTR_DEPRECATED("Please use ZGMTRUnitTestingClusterSimpleStruct", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
@property (nonatomic, copy) NSNumber * _Nonnull g ZGMTR_DEPRECATED("Please use ZGMTRUnitTestingClusterSimpleStruct", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
@property (nonatomic, copy) NSNumber * _Nonnull h ZGMTR_DEPRECATED("Please use ZGMTRUnitTestingClusterSimpleStruct", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
@end

ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4))
@interface ZGMTRUnitTestingClusterTestFabricScoped : NSObject <NSCopying>
@property (nonatomic, copy) NSNumber * _Nonnull fabricSensitiveInt8u ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
@property (nonatomic, copy) NSNumber * _Nullable optionalFabricSensitiveInt8u ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
@property (nonatomic, copy) NSNumber * _Nullable nullableFabricSensitiveInt8u ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
@property (nonatomic, copy) NSNumber * _Nullable nullableOptionalFabricSensitiveInt8u ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
@property (nonatomic, copy) NSString * _Nonnull fabricSensitiveCharString ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
@property (nonatomic, copy) ZGMTRUnitTestingClusterSimpleStruct * _Nonnull fabricSensitiveStruct ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
@property (nonatomic, copy) NSArray * _Nonnull fabricSensitiveInt8uList ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
@property (nonatomic, copy) NSNumber * _Nonnull fabricIndex ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
@end

ZGMTR_DEPRECATED("Please use ZGMTRUnitTestingClusterTestFabricScoped", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
@interface ZGMTRTestClusterClusterTestFabricScoped : ZGMTRUnitTestingClusterTestFabricScoped
@property (nonatomic, copy) NSNumber * _Nonnull fabricSensitiveInt8u ZGMTR_DEPRECATED("Please use ZGMTRUnitTestingClusterTestFabricScoped", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
@property (nonatomic, copy) NSNumber * _Nullable optionalFabricSensitiveInt8u ZGMTR_DEPRECATED("Please use ZGMTRUnitTestingClusterTestFabricScoped", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
@property (nonatomic, copy) NSNumber * _Nullable nullableFabricSensitiveInt8u ZGMTR_DEPRECATED("Please use ZGMTRUnitTestingClusterTestFabricScoped", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
@property (nonatomic, copy) NSNumber * _Nullable nullableOptionalFabricSensitiveInt8u ZGMTR_DEPRECATED("Please use ZGMTRUnitTestingClusterTestFabricScoped", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
@property (nonatomic, copy) NSString * _Nonnull fabricSensitiveCharString ZGMTR_DEPRECATED("Please use ZGMTRUnitTestingClusterTestFabricScoped", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
@property (nonatomic, copy) ZGMTRTestClusterClusterSimpleStruct * _Nonnull fabricSensitiveStruct ZGMTR_DEPRECATED("Please use ZGMTRUnitTestingClusterTestFabricScoped", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
@property (nonatomic, copy) NSArray * _Nonnull fabricSensitiveInt8uList ZGMTR_DEPRECATED("Please use ZGMTRUnitTestingClusterTestFabricScoped", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
@property (nonatomic, copy) NSNumber * _Nonnull fabricIndex ZGMTR_DEPRECATED("Please use ZGMTRUnitTestingClusterTestFabricScoped", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
@end

ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4))
@interface ZGMTRUnitTestingClusterNullablesAndOptionalsStruct : NSObject <NSCopying>
@property (nonatomic, copy) NSNumber * _Nullable nullableInt ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
@property (nonatomic, copy) NSNumber * _Nullable optionalInt ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
@property (nonatomic, copy) NSNumber * _Nullable nullableOptionalInt ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
@property (nonatomic, copy) NSString * _Nullable nullableString ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
@property (nonatomic, copy) NSString * _Nullable optionalString ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
@property (nonatomic, copy) NSString * _Nullable nullableOptionalString ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
@property (nonatomic, copy) ZGMTRUnitTestingClusterSimpleStruct * _Nullable nullableStruct ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
@property (nonatomic, copy) ZGMTRUnitTestingClusterSimpleStruct * _Nullable optionalStruct ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
@property (nonatomic, copy) ZGMTRUnitTestingClusterSimpleStruct * _Nullable nullableOptionalStruct ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
@property (nonatomic, copy) NSArray * _Nullable nullableList ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
@property (nonatomic, copy) NSArray * _Nullable optionalList ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
@property (nonatomic, copy) NSArray * _Nullable nullableOptionalList ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
@end

ZGMTR_DEPRECATED("Please use ZGMTRUnitTestingClusterNullablesAndOptionalsStruct", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
@interface ZGMTRTestClusterClusterNullablesAndOptionalsStruct : ZGMTRUnitTestingClusterNullablesAndOptionalsStruct
@property (nonatomic, copy) NSNumber * _Nullable nullableInt ZGMTR_DEPRECATED("Please use ZGMTRUnitTestingClusterNullablesAndOptionalsStruct", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
@property (nonatomic, copy) NSNumber * _Nullable optionalInt ZGMTR_DEPRECATED("Please use ZGMTRUnitTestingClusterNullablesAndOptionalsStruct", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
@property (nonatomic, copy) NSNumber * _Nullable nullableOptionalInt ZGMTR_DEPRECATED("Please use ZGMTRUnitTestingClusterNullablesAndOptionalsStruct", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
@property (nonatomic, copy) NSString * _Nullable nullableString ZGMTR_DEPRECATED("Please use ZGMTRUnitTestingClusterNullablesAndOptionalsStruct", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
@property (nonatomic, copy) NSString * _Nullable optionalString ZGMTR_DEPRECATED("Please use ZGMTRUnitTestingClusterNullablesAndOptionalsStruct", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
@property (nonatomic, copy) NSString * _Nullable nullableOptionalString ZGMTR_DEPRECATED("Please use ZGMTRUnitTestingClusterNullablesAndOptionalsStruct", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
@property (nonatomic, copy) ZGMTRTestClusterClusterSimpleStruct * _Nullable nullableStruct ZGMTR_DEPRECATED("Please use ZGMTRUnitTestingClusterNullablesAndOptionalsStruct", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
@property (nonatomic, copy) ZGMTRTestClusterClusterSimpleStruct * _Nullable optionalStruct ZGMTR_DEPRECATED("Please use ZGMTRUnitTestingClusterNullablesAndOptionalsStruct", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
@property (nonatomic, copy) ZGMTRTestClusterClusterSimpleStruct * _Nullable nullableOptionalStruct ZGMTR_DEPRECATED("Please use ZGMTRUnitTestingClusterNullablesAndOptionalsStruct", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
@property (nonatomic, copy) NSArray * _Nullable nullableList ZGMTR_DEPRECATED("Please use ZGMTRUnitTestingClusterNullablesAndOptionalsStruct", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
@property (nonatomic, copy) NSArray * _Nullable optionalList ZGMTR_DEPRECATED("Please use ZGMTRUnitTestingClusterNullablesAndOptionalsStruct", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
@property (nonatomic, copy) NSArray * _Nullable nullableOptionalList ZGMTR_DEPRECATED("Please use ZGMTRUnitTestingClusterNullablesAndOptionalsStruct", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
@end

ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4))
@interface ZGMTRUnitTestingClusterNestedStruct : NSObject <NSCopying>
@property (nonatomic, copy) NSNumber * _Nonnull a ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
@property (nonatomic, copy) NSNumber * _Nonnull b ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
@property (nonatomic, copy) ZGMTRUnitTestingClusterSimpleStruct * _Nonnull c ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
@property (nonatomic, copy) ZGMTRDataTypeTestGlobalStruct * _Nullable d ZGMTR_PROVISIONALLY_AVAILABLE;
@end

ZGMTR_DEPRECATED("Please use ZGMTRUnitTestingClusterNestedStruct", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
@interface ZGMTRTestClusterClusterNestedStruct : ZGMTRUnitTestingClusterNestedStruct
@property (nonatomic, copy) NSNumber * _Nonnull a ZGMTR_DEPRECATED("Please use ZGMTRUnitTestingClusterNestedStruct", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
@property (nonatomic, copy) NSNumber * _Nonnull b ZGMTR_DEPRECATED("Please use ZGMTRUnitTestingClusterNestedStruct", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
@property (nonatomic, copy) ZGMTRTestClusterClusterSimpleStruct * _Nonnull c ZGMTR_DEPRECATED("Please use ZGMTRUnitTestingClusterNestedStruct", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
@end

ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4))
@interface ZGMTRUnitTestingClusterNestedStructList : NSObject <NSCopying>
@property (nonatomic, copy) NSNumber * _Nonnull a ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
@property (nonatomic, copy) NSNumber * _Nonnull b ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
@property (nonatomic, copy) ZGMTRUnitTestingClusterSimpleStruct * _Nonnull c ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
@property (nonatomic, copy) NSArray * _Nonnull d ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
@property (nonatomic, copy) NSArray * _Nonnull e ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
@property (nonatomic, copy) NSArray * _Nonnull f ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
@property (nonatomic, copy) NSArray * _Nonnull g ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
@end

ZGMTR_DEPRECATED("Please use ZGMTRUnitTestingClusterNestedStructList", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
@interface ZGMTRTestClusterClusterNestedStructList : ZGMTRUnitTestingClusterNestedStructList
@property (nonatomic, copy) NSNumber * _Nonnull a ZGMTR_DEPRECATED("Please use ZGMTRUnitTestingClusterNestedStructList", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
@property (nonatomic, copy) NSNumber * _Nonnull b ZGMTR_DEPRECATED("Please use ZGMTRUnitTestingClusterNestedStructList", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
@property (nonatomic, copy) ZGMTRTestClusterClusterSimpleStruct * _Nonnull c ZGMTR_DEPRECATED("Please use ZGMTRUnitTestingClusterNestedStructList", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
@property (nonatomic, copy) NSArray * _Nonnull d ZGMTR_DEPRECATED("Please use ZGMTRUnitTestingClusterNestedStructList", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
@property (nonatomic, copy) NSArray * _Nonnull e ZGMTR_DEPRECATED("Please use ZGMTRUnitTestingClusterNestedStructList", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
@property (nonatomic, copy) NSArray * _Nonnull f ZGMTR_DEPRECATED("Please use ZGMTRUnitTestingClusterNestedStructList", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
@property (nonatomic, copy) NSArray * _Nonnull g ZGMTR_DEPRECATED("Please use ZGMTRUnitTestingClusterNestedStructList", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
@end

ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4))
@interface ZGMTRUnitTestingClusterDoubleNestedStructList : NSObject <NSCopying>
@property (nonatomic, copy) NSArray * _Nonnull a ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
@end

ZGMTR_DEPRECATED("Please use ZGMTRUnitTestingClusterDoubleNestedStructList", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
@interface ZGMTRTestClusterClusterDoubleNestedStructList : ZGMTRUnitTestingClusterDoubleNestedStructList
@property (nonatomic, copy) NSArray * _Nonnull a ZGMTR_DEPRECATED("Please use ZGMTRUnitTestingClusterDoubleNestedStructList", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
@end

ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4))
@interface ZGMTRUnitTestingClusterTestListStructOctet : NSObject <NSCopying>
@property (nonatomic, copy) NSNumber * _Nonnull member1 ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
@property (nonatomic, copy) NSData * _Nonnull member2 ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
@end

ZGMTR_DEPRECATED("Please use ZGMTRUnitTestingClusterTestListStructOctet", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
@interface ZGMTRTestClusterClusterTestListStructOctet : ZGMTRUnitTestingClusterTestListStructOctet
@property (nonatomic, copy) NSNumber * _Nonnull member1 ZGMTR_DEPRECATED("Please use ZGMTRUnitTestingClusterTestListStructOctet", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
@property (nonatomic, copy) NSData * _Nonnull member2 ZGMTR_DEPRECATED("Please use ZGMTRUnitTestingClusterTestListStructOctet", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
@end

ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4))
@interface ZGMTRUnitTestingClusterTestEventEvent : NSObject <NSCopying>
@property (nonatomic, copy) NSNumber * _Nonnull arg1 ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
@property (nonatomic, copy) NSNumber * _Nonnull arg2 ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
@property (nonatomic, copy) NSNumber * _Nonnull arg3 ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
@property (nonatomic, copy) ZGMTRUnitTestingClusterSimpleStruct * _Nonnull arg4 ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
@property (nonatomic, copy) NSArray * _Nonnull arg5 ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
@property (nonatomic, copy) NSArray * _Nonnull arg6 ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
@end

ZGMTR_DEPRECATED("Please use ZGMTRUnitTestingClusterTestEventEvent", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
@interface ZGMTRTestClusterClusterTestEventEvent : ZGMTRUnitTestingClusterTestEventEvent
@property (nonatomic, copy) NSNumber * _Nonnull arg1 ZGMTR_DEPRECATED("Please use ZGMTRUnitTestingClusterTestEventEvent", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
@property (nonatomic, copy) NSNumber * _Nonnull arg2 ZGMTR_DEPRECATED("Please use ZGMTRUnitTestingClusterTestEventEvent", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
@property (nonatomic, copy) NSNumber * _Nonnull arg3 ZGMTR_DEPRECATED("Please use ZGMTRUnitTestingClusterTestEventEvent", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
@property (nonatomic, copy) ZGMTRTestClusterClusterSimpleStruct * _Nonnull arg4 ZGMTR_DEPRECATED("Please use ZGMTRUnitTestingClusterTestEventEvent", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
@property (nonatomic, copy) NSArray * _Nonnull arg5 ZGMTR_DEPRECATED("Please use ZGMTRUnitTestingClusterTestEventEvent", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
@property (nonatomic, copy) NSArray * _Nonnull arg6 ZGMTR_DEPRECATED("Please use ZGMTRUnitTestingClusterTestEventEvent", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
@end

ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4))
@interface ZGMTRUnitTestingClusterTestFabricScopedEventEvent : NSObject <NSCopying>
@property (nonatomic, copy) NSNumber * _Nonnull fabricIndex ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4));
@end

ZGMTR_DEPRECATED("Please use ZGMTRUnitTestingClusterTestFabricScopedEventEvent", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
@interface ZGMTRTestClusterClusterTestFabricScopedEventEvent : ZGMTRUnitTestingClusterTestFabricScopedEventEvent
@property (nonatomic, copy) NSNumber * _Nonnull fabricIndex ZGMTR_DEPRECATED("Please use ZGMTRUnitTestingClusterTestFabricScopedEventEvent", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
@end

ZGMTR_PROVISIONALLY_AVAILABLE
@interface ZGMTRUnitTestingClusterTestDifferentVendorMeiEventEvent : NSObject <NSCopying>
@property (nonatomic, copy) NSNumber * _Nonnull arg1 ZGMTR_PROVISIONALLY_AVAILABLE;
@end

ZGMTR_PROVISIONALLY_AVAILABLE
@interface ZGMTRSampleMEIClusterPingCountEventEvent : NSObject <NSCopying>
@property (nonatomic, copy, getter=getCount) NSNumber * _Nonnull count ZGMTR_PROVISIONALLY_AVAILABLE;
@property (nonatomic, copy) NSNumber * _Nonnull fabricIndex ZGMTR_PROVISIONALLY_AVAILABLE;
@end

NS_ASSUME_NONNULL_END
