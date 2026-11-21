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

#import <ZGMatter/ZGMTRDefines.h>
#import <ZGMatter/ZGMTRDevice.h> // for ZGMTRDeviceState

NS_ASSUME_NONNULL_BEGIN

ZGMTR_AVAILABLE(ios(18.2), macos(15.2), watchos(11.2), tvos(18.2))
@protocol ZGMTRXPCClientProtocol_ZGMTRDevice <NSObject>
- (oneway void)device:(NSNumber *)nodeID stateChanged:(ZGMTRDeviceState)state;
- (oneway void)device:(NSNumber *)nodeID receivedAttributeReport:(NSArray<NSDictionary<NSString *, id> *> *)attributeReport;
- (oneway void)device:(NSNumber *)nodeID receivedEventReport:(NSArray<NSDictionary<NSString *, id> *> *)eventReport;
- (oneway void)deviceBecameActive:(NSNumber *)nodeID;
- (oneway void)deviceCachePrimed:(NSNumber *)nodeID;
- (oneway void)deviceConfigurationChanged:(NSNumber *)nodeID;
- (oneway void)device:(NSNumber *)nodeID internalStateUpdated:(NSDictionary *)dictionary;
@end

ZGMTR_AVAILABLE(ios(18.2), macos(15.2), watchos(11.2), tvos(18.2))
@protocol ZGMTRXPCClientProtocol_ZGMTRDeviceController <NSObject>
// Not Supported via XPC
//- (oneway void)controller:(NSUUID *)controller statusUpdate:(ZGMTRCommissioningStatus)status;
//- (oneway void)controller:(NSUUID *)controller commissioningSessionEstablishmentDone:(NSError * _Nullable)error;
//- (oneway void)controller:(NSUUID *)controller commissioningComplete:(NSError * _Nullable)error nodeID:(NSNumber * _Nullable)nodeID metrics:(ZGMTRMetrics * _Nullable)metrics;
//- (oneway void)controller:(NSUUID *)controller readCommissioningInfo:(ZGMTRProductIdentity *)info;
@optional
- (oneway void)controller:(NSUUID *)controller controllerConfigurationUpdated:(NSDictionary *)configuration ZGMTR_AVAILABLE(ios(18.3), macos(15.3), watchos(11.3), tvos(18.3));
@end

ZGMTR_AVAILABLE(ios(18.2), macos(15.2), watchos(11.2), tvos(18.2))
@protocol ZGMTRXPCClientProtocol <NSObject, ZGMTRXPCClientProtocol_ZGMTRDevice, ZGMTRXPCClientProtocol_ZGMTRDeviceController>
@end

NS_ASSUME_NONNULL_END
