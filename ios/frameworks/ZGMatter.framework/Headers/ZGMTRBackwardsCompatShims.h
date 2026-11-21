/**
 *    Copyright (c) 2023 Project CHIP Authors
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
#import <ZGMatter/ZGMTRCluster.h>
#import <ZGMatter/ZGMTRClusterStateCacheContainer.h>
#import <ZGMatter/ZGMTRClusters.h>
#import <ZGMatter/ZGMTRCommandPayloadsObjc.h>
#import <ZGMatter/ZGMTRDefines.h>
#import <ZGMatter/ZGMTRStructsObjc.h>

/**
 * This file defines manual backwards-compat shims of various sorts to handle
 * API changes that happened.
 */

NS_ASSUME_NONNULL_BEGIN

@interface ZGMTRGroupKeyManagementClusterKeySetReadAllIndicesParams ()
/**
 * This command used to incorrectly have a groupKeySetIDs field.
 */
@property (nonatomic, copy) NSArray * groupKeySetIDs ZGMTR_DEPRECATED(
    "This field has been removed", ios(16.1, 17.0), macos(13.0, 14.0), watchos(9.1, 10.0), tvos(16.1, 17.0));

@end

/**
 * FanControl used to have WindSettingMask and WindSupportMask that had
 * identical values.  Those got replaced with a single WindBitmap.  We codegen
 * WindSupportMask as an alias of WindBitmap, but we need a manual shim for
 * WindSettingMask.
 */
typedef NS_OPTIONS(uint8_t, ZGMTRFanControlWindSettingMask) {
    ZGMTRFanControlWindSettingMaskSleepWind ZGMTR_DEPRECATED(
        "Please use ZGMTRFanControlWindBitmapSleepWind", ios(16.1, 17.0), macos(13.0, 14.0), watchos(9.1, 10.0), tvos(16.1, 17.0))
    = 0x1,
    ZGMTRFanControlWindSettingMaskNaturalWind ZGMTR_DEPRECATED(
        "Please use ZGMTRFanControlWindBitmapNaturalWind", ios(16.1, 17.0), macos(13.0, 14.0), watchos(9.1, 10.0), tvos(16.1, 17.0))
    = 0x2,
} ZGMTR_DEPRECATED("Please use ZGMTRFanControlWindBitmap", ios(16.1, 17.0), macos(13.0, 14.0), watchos(9.1, 10.0), tvos(16.1, 17.0));

/**
 * For the OTA clusters, first we changed the names of the clusters, and then we
 * changed the names of the enums.  That means we now have three names for the
 * enums (newest name, name before enum name change, name before cluster name
 * change).  We can only track one old name for things, so just manually add the
 * intermediate names.
 */
typedef NS_ENUM(uint8_t, ZGMTROTASoftwareUpdateProviderOTAApplyUpdateAction) {
    ZGMTROTASoftwareUpdateProviderOTAApplyUpdateActionProceed ZGMTR_DEPRECATED("Please use ZGMTROTASoftwareUpdateProviderApplyUpdateActionProceed", ios(16.4, 17.2), macos(13.3, 14.2), watchos(9.4, 10.2), tvos(16.4, 17.2))
    = 0x00,
    ZGMTROTASoftwareUpdateProviderOTAApplyUpdateActionAwaitNextAction
        ZGMTR_DEPRECATED("Please use ZGMTROTASoftwareUpdateProviderApplyUpdateActionAwaitNextAction", ios(16.4, 17.2), macos(13.3, 14.2), watchos(9.4, 10.2), tvos(16.4, 17.2))
    = 0x01,
    ZGMTROTASoftwareUpdateProviderOTAApplyUpdateActionDiscontinue
        ZGMTR_DEPRECATED("Please use ZGMTROTASoftwareUpdateProviderApplyUpdateActionDiscontinue", ios(16.4, 17.2), macos(13.3, 14.2), watchos(9.4, 10.2), tvos(16.4, 17.2))
    = 0x02,
} ZGMTR_DEPRECATED("Please use ZGMTROTASoftwareUpdateProviderApplyUpdateAction", ios(16.4, 17.2), macos(13.3, 14.2), watchos(9.4, 10.2), tvos(16.4, 17.2));

typedef NS_ENUM(uint8_t, ZGMTROTASoftwareUpdateProviderOTADownloadProtocol) {
    ZGMTROTASoftwareUpdateProviderOTADownloadProtocolBDXSynchronous
        ZGMTR_DEPRECATED("Please use ZGMTROTASoftwareUpdateProviderDownloadProtocolBDXSynchronous", ios(16.4, 17.2), macos(13.3, 14.2), watchos(9.4, 10.2), tvos(16.4, 17.2))
    = 0x00,
    ZGMTROTASoftwareUpdateProviderOTADownloadProtocolBDXAsynchronous
        ZGMTR_DEPRECATED("Please use ZGMTROTASoftwareUpdateProviderDownloadProtocolBDXAsynchronous", ios(16.4, 17.2), macos(13.3, 14.2), watchos(9.4, 10.2), tvos(16.4, 17.2))
    = 0x01,
    ZGMTROTASoftwareUpdateProviderOTADownloadProtocolHTTPS
        ZGMTR_DEPRECATED("Please use ZGMTROTASoftwareUpdateProviderDownloadProtocolHTTPS", ios(16.4, 17.2), macos(13.3, 14.2), watchos(9.4, 10.2), tvos(16.4, 17.2))
    = 0x02,
    ZGMTROTASoftwareUpdateProviderOTADownloadProtocolVendorSpecific
        ZGMTR_DEPRECATED("Please use ZGMTROTASoftwareUpdateProviderDownloadProtocolVendorSpecific", ios(16.4, 17.2), macos(13.3, 14.2), watchos(9.4, 10.2), tvos(16.4, 17.2))
    = 0x03,
} ZGMTR_DEPRECATED("Please use ZGMTROTASoftwareUpdateProviderDownloadProtocol", ios(16.4, 17.2), macos(13.3, 14.2), watchos(9.4, 10.2), tvos(16.4, 17.2));

typedef NS_ENUM(uint8_t, ZGMTROTASoftwareUpdateProviderOTAQueryStatus) {
    ZGMTROTASoftwareUpdateProviderOTAQueryStatusUpdateAvailable
        ZGMTR_DEPRECATED("Please use ZGMTROTASoftwareUpdateProviderStatusUpdateAvailable", ios(16.4, 17.2), macos(13.3, 14.2), watchos(9.4, 10.2), tvos(16.4, 17.2))
    = 0x00,
    ZGMTROTASoftwareUpdateProviderOTAQueryStatusBusy
        ZGMTR_DEPRECATED("Please use ZGMTROTASoftwareUpdateProviderStatusBusy", ios(16.4, 17.2), macos(13.3, 14.2), watchos(9.4, 10.2), tvos(16.4, 17.2))
    = 0x01,
    ZGMTROTASoftwareUpdateProviderOTAQueryStatusNotAvailable
        ZGMTR_DEPRECATED("Please use ZGMTROTASoftwareUpdateProviderStatusNotAvailable", ios(16.4, 17.2), macos(13.3, 14.2), watchos(9.4, 10.2), tvos(16.4, 17.2))
    = 0x02,
    ZGMTROTASoftwareUpdateProviderOTAQueryStatusDownloadProtocolNotSupported
        ZGMTR_DEPRECATED("Please use ZGMTROTASoftwareUpdateProviderStatusDownloadProtocolNotSupported", ios(16.4, 17.2), macos(13.3, 14.2), watchos(9.4, 10.2), tvos(16.4, 17.2))
    = 0x03,
} ZGMTR_DEPRECATED("Please use ZGMTROTASoftwareUpdateProviderStatus", ios(16.4, 17.2), macos(13.3, 14.2), watchos(9.4, 10.2), tvos(16.4, 17.2));

typedef NS_ENUM(uint8_t, ZGMTROTASoftwareUpdateRequestorOTAAnnouncementReason) {
    ZGMTROTASoftwareUpdateRequestorOTAAnnouncementReasonSimpleAnnouncement
        ZGMTR_DEPRECATED("Please use ZGMTROTASoftwareUpdateRequestorAnnouncementReasonSimpleAnnouncement", ios(16.4, 17.2), macos(13.3, 14.2), watchos(9.4, 10.2), tvos(16.4, 17.2))
    = 0x00,
    ZGMTROTASoftwareUpdateRequestorOTAAnnouncementReasonUpdateAvailable
        ZGMTR_DEPRECATED("Please use ZGMTROTASoftwareUpdateRequestorAnnouncementReasonUpdateAvailable", ios(16.4, 17.2), macos(13.3, 14.2), watchos(9.4, 10.2), tvos(16.4, 17.2))
    = 0x01,
    ZGMTROTASoftwareUpdateRequestorOTAAnnouncementReasonUrgentUpdateAvailable
        ZGMTR_DEPRECATED("Please use ZGMTROTASoftwareUpdateRequestorAnnouncementReasonUrgentUpdateAvailable", ios(16.4, 17.2), macos(13.3, 14.2), watchos(9.4, 10.2), tvos(16.4, 17.2))
    = 0x02,
} ZGMTR_DEPRECATED("Please use ZGMTROTASoftwareUpdateRequestorAnnouncementReason", ios(16.4, 17.2), macos(13.3, 14.2), watchos(9.4, 10.2), tvos(16.4, 17.2));

typedef NS_ENUM(uint8_t, ZGMTROTASoftwareUpdateRequestorOTAChangeReason) {
    ZGMTROTASoftwareUpdateRequestorOTAChangeReasonUnknown
        ZGMTR_DEPRECATED("Please use ZGMTROTASoftwareUpdateRequestorChangeReasonUnknown", ios(16.4, 17.2), macos(13.3, 14.2), watchos(9.4, 10.2), tvos(16.4, 17.2))
    = 0x00,
    ZGMTROTASoftwareUpdateRequestorOTAChangeReasonSuccess
        ZGMTR_DEPRECATED("Please use ZGMTROTASoftwareUpdateRequestorChangeReasonSuccess", ios(16.4, 17.2), macos(13.3, 14.2), watchos(9.4, 10.2), tvos(16.4, 17.2))
    = 0x01,
    ZGMTROTASoftwareUpdateRequestorOTAChangeReasonFailure
        ZGMTR_DEPRECATED("Please use ZGMTROTASoftwareUpdateRequestorChangeReasonFailure", ios(16.4, 17.2), macos(13.3, 14.2), watchos(9.4, 10.2), tvos(16.4, 17.2))
    = 0x02,
    ZGMTROTASoftwareUpdateRequestorOTAChangeReasonTimeOut
        ZGMTR_DEPRECATED("Please use ZGMTROTASoftwareUpdateRequestorChangeReasonTimeOut", ios(16.4, 17.2), macos(13.3, 14.2), watchos(9.4, 10.2), tvos(16.4, 17.2))
    = 0x03,
    ZGMTROTASoftwareUpdateRequestorOTAChangeReasonDelayByProvider
        ZGMTR_DEPRECATED("Please use ZGMTROTASoftwareUpdateRequestorChangeReasonDelayByProvider", ios(16.4, 17.2), macos(13.3, 14.2), watchos(9.4, 10.2), tvos(16.4, 17.2))
    = 0x04,
} ZGMTR_DEPRECATED("Please use ZGMTROTASoftwareUpdateRequestorChangeReason", ios(16.4, 17.2), macos(13.3, 14.2), watchos(9.4, 10.2), tvos(16.4, 17.2));

typedef NS_ENUM(uint8_t, ZGMTROTASoftwareUpdateRequestorOTAUpdateState) {
    ZGMTROTASoftwareUpdateRequestorOTAUpdateStateUnknown
        ZGMTR_DEPRECATED("Please use ZGMTROTASoftwareUpdateRequestorUpdateStateUnknown", ios(16.4, 17.2), macos(13.3, 14.2), watchos(9.4, 10.2), tvos(16.4, 17.2))
    = 0x00,
    ZGMTROTASoftwareUpdateRequestorOTAUpdateStateIdle
        ZGMTR_DEPRECATED("Please use ZGMTROTASoftwareUpdateRequestorUpdateStateIdle", ios(16.4, 17.2), macos(13.3, 14.2), watchos(9.4, 10.2), tvos(16.4, 17.2))
    = 0x01,
    ZGMTROTASoftwareUpdateRequestorOTAUpdateStateQuerying
        ZGMTR_DEPRECATED("Please use ZGMTROTASoftwareUpdateRequestorUpdateStateQuerying", ios(16.4, 17.2), macos(13.3, 14.2), watchos(9.4, 10.2), tvos(16.4, 17.2))
    = 0x02,
    ZGMTROTASoftwareUpdateRequestorOTAUpdateStateDelayedOnQuery
        ZGMTR_DEPRECATED("Please use ZGMTROTASoftwareUpdateRequestorUpdateStateDelayedOnQuery", ios(16.4, 17.2), macos(13.3, 14.2), watchos(9.4, 10.2), tvos(16.4, 17.2))
    = 0x03,
    ZGMTROTASoftwareUpdateRequestorOTAUpdateStateDownloading
        ZGMTR_DEPRECATED("Please use ZGMTROTASoftwareUpdateRequestorUpdateStateDownloading", ios(16.4, 17.2), macos(13.3, 14.2), watchos(9.4, 10.2), tvos(16.4, 17.2))
    = 0x04,
    ZGMTROTASoftwareUpdateRequestorOTAUpdateStateApplying
        ZGMTR_DEPRECATED("Please use ZGMTROTASoftwareUpdateRequestorUpdateStateApplying", ios(16.4, 17.2), macos(13.3, 14.2), watchos(9.4, 10.2), tvos(16.4, 17.2))
    = 0x05,
    ZGMTROTASoftwareUpdateRequestorOTAUpdateStateDelayedOnApply
        ZGMTR_DEPRECATED("Please use ZGMTROTASoftwareUpdateRequestorUpdateStateDelayedOnApply", ios(16.4, 17.2), macos(13.3, 14.2), watchos(9.4, 10.2), tvos(16.4, 17.2))
    = 0x06,
    ZGMTROTASoftwareUpdateRequestorOTAUpdateStateRollingBack
        ZGMTR_DEPRECATED("Please use ZGMTROTASoftwareUpdateRequestorUpdateStateRollingBack", ios(16.4, 17.2), macos(13.3, 14.2), watchos(9.4, 10.2), tvos(16.4, 17.2))
    = 0x07,
    ZGMTROTASoftwareUpdateRequestorOTAUpdateStateDelayedOnUserConsent
        ZGMTR_DEPRECATED("Please use ZGMTROTASoftwareUpdateRequestorUpdateStateDelayedOnUserConsent", ios(16.4, 17.2), macos(13.3, 14.2), watchos(9.4, 10.2), tvos(16.4, 17.2))
    = 0x08,
} ZGMTR_DEPRECATED("Please use ZGMTROTASoftwareUpdateRequestorUpdateState", ios(16.4, 17.2), macos(13.3, 14.2), watchos(9.4, 10.2), tvos(16.4, 17.2));

/**
 * ColorControl used to have HueMoveMode/SaturationMoveMode and HueStepMode/SaturationStepMode that had
 * identical values.  Those got replaced with MoveModeEnum and StepModeEnum respectively.  We codegen
 * HueMoveMode and HueStepMode as aliases of MoveModeEnum and StepModeEnum, but we need manual shims for
 * SaturationMoveMode and SaturationStepMode.
 */
typedef NS_ENUM(uint8_t, ZGMTRColorControlSaturationMoveMode) {
    ZGMTRColorControlSaturationMoveModeStop ZGMTR_DEPRECATED("Please use ZGMTRColorControlMoveModeStop", ios(16.1, 18.2), macos(13.0, 15.2), watchos(9.1, 11.2), tvos(16.1, 18.2))
    = 0x00,
    ZGMTRColorControlSaturationMoveModeUp ZGMTR_DEPRECATED("Please use ZGMTRColorControlMoveModeUp", ios(16.1, 18.2), macos(13.0, 15.2), watchos(9.1, 11.2), tvos(16.1, 18.2))
    = 0x01,
    ZGMTRColorControlSaturationMoveModeDown ZGMTR_DEPRECATED("Please use ZGMTRColorControlMoveModeDown", ios(16.1, 18.2), macos(13.0, 15.2), watchos(9.1, 11.2), tvos(16.1, 18.2))
    = 0x03,
} ZGMTR_DEPRECATED("Please use ZGMTRColorControlMoveMode", ios(16.1, 18.2), macos(13.0, 15.2), watchos(9.1, 11.2), tvos(16.1, 18.2));

typedef NS_ENUM(uint8_t, ZGMTRColorControlSaturationStepMode) {
    ZGMTRColorControlSaturationStepModeUp ZGMTR_DEPRECATED("Please use ZGMTRColorControlStepModeUp", ios(16.1, 18.2), macos(13.0, 15.2), watchos(9.1, 11.2), tvos(16.1, 18.2))
    = 0x01,
    ZGMTRColorControlSaturationStepModeDown ZGMTR_DEPRECATED("Please use ZGMTRColorControlStepModeDown", ios(16.1, 18.2), macos(13.0, 15.2), watchos(9.1, 11.2), tvos(16.1, 18.2))
    = 0x03,
} ZGMTR_DEPRECATED("Please use ZGMTRColorControlStepMode", ios(16.1, 18.2), macos(13.0, 15.2), watchos(9.1, 11.2), tvos(16.1, 18.2));

#pragma mark - Color Control attributes that used to be writable but were switched to readonly.

@interface ZGMTRBaseClusterColorControl (AttributesNowReadonly)

- (void)writeAttributeWhitePointXWithValue:(NSNumber * _Nonnull)value completion:(ZGMTRStatusCompletion)completion ZGMTR_DEPRECATED("This attribute is no longer writable in the ZGMatter standard", ios(16.4, 26.1), macos(13.3, 26.1), watchos(9.4, 26.1), tvos(16.4, 26.1));
- (void)writeAttributeWhitePointXWithValue:(NSNumber * _Nonnull)value params:(ZGMTRWriteParams * _Nullable)params completion:(ZGMTRStatusCompletion)completion ZGMTR_DEPRECATED("This attribute is no longer writable in the ZGMatter standard", ios(16.4, 26.1), macos(13.3, 26.1), watchos(9.4, 26.1), tvos(16.4, 26.1));
- (void)writeAttributeWhitePointYWithValue:(NSNumber * _Nonnull)value completion:(ZGMTRStatusCompletion)completion ZGMTR_DEPRECATED("This attribute is no longer writable in the ZGMatter standard", ios(16.4, 26.1), macos(13.3, 26.1), watchos(9.4, 26.1), tvos(16.4, 26.1));
- (void)writeAttributeWhitePointYWithValue:(NSNumber * _Nonnull)value params:(ZGMTRWriteParams * _Nullable)params completion:(ZGMTRStatusCompletion)completion ZGMTR_DEPRECATED("This attribute is no longer writable in the ZGMatter standard", ios(16.4, 26.1), macos(13.3, 26.1), watchos(9.4, 26.1), tvos(16.4, 26.1));
- (void)writeAttributeColorPointRXWithValue:(NSNumber * _Nonnull)value completion:(ZGMTRStatusCompletion)completion ZGMTR_DEPRECATED("This attribute is no longer writable in the ZGMatter standard", ios(16.4, 26.1), macos(13.3, 26.1), watchos(9.4, 26.1), tvos(16.4, 26.1));
- (void)writeAttributeColorPointRXWithValue:(NSNumber * _Nonnull)value params:(ZGMTRWriteParams * _Nullable)params completion:(ZGMTRStatusCompletion)completion ZGMTR_DEPRECATED("This attribute is no longer writable in the ZGMatter standard", ios(16.4, 26.1), macos(13.3, 26.1), watchos(9.4, 26.1), tvos(16.4, 26.1));
- (void)writeAttributeColorPointRYWithValue:(NSNumber * _Nonnull)value completion:(ZGMTRStatusCompletion)completion ZGMTR_DEPRECATED("This attribute is no longer writable in the ZGMatter standard", ios(16.4, 26.1), macos(13.3, 26.1), watchos(9.4, 26.1), tvos(16.4, 26.1));
- (void)writeAttributeColorPointRYWithValue:(NSNumber * _Nonnull)value params:(ZGMTRWriteParams * _Nullable)params completion:(ZGMTRStatusCompletion)completion ZGMTR_DEPRECATED("This attribute is no longer writable in the ZGMatter standard", ios(16.4, 26.1), macos(13.3, 26.1), watchos(9.4, 26.1), tvos(16.4, 26.1));
- (void)writeAttributeColorPointRIntensityWithValue:(NSNumber * _Nullable)value completion:(ZGMTRStatusCompletion)completion ZGMTR_DEPRECATED("This attribute is no longer writable in the ZGMatter standard", ios(16.4, 26.1), macos(13.3, 26.1), watchos(9.4, 26.1), tvos(16.4, 26.1));
- (void)writeAttributeColorPointRIntensityWithValue:(NSNumber * _Nullable)value params:(ZGMTRWriteParams * _Nullable)params completion:(ZGMTRStatusCompletion)completion ZGMTR_DEPRECATED("This attribute is no longer writable in the ZGMatter standard", ios(16.4, 26.1), macos(13.3, 26.1), watchos(9.4, 26.1), tvos(16.4, 26.1));
- (void)writeAttributeColorPointGXWithValue:(NSNumber * _Nonnull)value completion:(ZGMTRStatusCompletion)completion ZGMTR_DEPRECATED("This attribute is no longer writable in the ZGMatter standard", ios(16.4, 26.1), macos(13.3, 26.1), watchos(9.4, 26.1), tvos(16.4, 26.1));
- (void)writeAttributeColorPointGXWithValue:(NSNumber * _Nonnull)value params:(ZGMTRWriteParams * _Nullable)params completion:(ZGMTRStatusCompletion)completion ZGMTR_DEPRECATED("This attribute is no longer writable in the ZGMatter standard", ios(16.4, 26.1), macos(13.3, 26.1), watchos(9.4, 26.1), tvos(16.4, 26.1));
- (void)writeAttributeColorPointGYWithValue:(NSNumber * _Nonnull)value completion:(ZGMTRStatusCompletion)completion ZGMTR_DEPRECATED("This attribute is no longer writable in the ZGMatter standard", ios(16.4, 26.1), macos(13.3, 26.1), watchos(9.4, 26.1), tvos(16.4, 26.1));
- (void)writeAttributeColorPointGYWithValue:(NSNumber * _Nonnull)value params:(ZGMTRWriteParams * _Nullable)params completion:(ZGMTRStatusCompletion)completion ZGMTR_DEPRECATED("This attribute is no longer writable in the ZGMatter standard", ios(16.4, 26.1), macos(13.3, 26.1), watchos(9.4, 26.1), tvos(16.4, 26.1));
- (void)writeAttributeColorPointGIntensityWithValue:(NSNumber * _Nullable)value completion:(ZGMTRStatusCompletion)completion ZGMTR_DEPRECATED("This attribute is no longer writable in the ZGMatter standard", ios(16.4, 26.1), macos(13.3, 26.1), watchos(9.4, 26.1), tvos(16.4, 26.1));
- (void)writeAttributeColorPointGIntensityWithValue:(NSNumber * _Nullable)value params:(ZGMTRWriteParams * _Nullable)params completion:(ZGMTRStatusCompletion)completion ZGMTR_DEPRECATED("This attribute is no longer writable in the ZGMatter standard", ios(16.4, 26.1), macos(13.3, 26.1), watchos(9.4, 26.1), tvos(16.4, 26.1));
- (void)writeAttributeColorPointBXWithValue:(NSNumber * _Nonnull)value completion:(ZGMTRStatusCompletion)completion ZGMTR_DEPRECATED("This attribute is no longer writable in the ZGMatter standard", ios(16.4, 26.1), macos(13.3, 26.1), watchos(9.4, 26.1), tvos(16.4, 26.1));
- (void)writeAttributeColorPointBXWithValue:(NSNumber * _Nonnull)value params:(ZGMTRWriteParams * _Nullable)params completion:(ZGMTRStatusCompletion)completion ZGMTR_DEPRECATED("This attribute is no longer writable in the ZGMatter standard", ios(16.4, 26.1), macos(13.3, 26.1), watchos(9.4, 26.1), tvos(16.4, 26.1));
- (void)writeAttributeColorPointBYWithValue:(NSNumber * _Nonnull)value completion:(ZGMTRStatusCompletion)completion ZGMTR_DEPRECATED("This attribute is no longer writable in the ZGMatter standard", ios(16.4, 26.1), macos(13.3, 26.1), watchos(9.4, 26.1), tvos(16.4, 26.1));
- (void)writeAttributeColorPointBYWithValue:(NSNumber * _Nonnull)value params:(ZGMTRWriteParams * _Nullable)params completion:(ZGMTRStatusCompletion)completion ZGMTR_DEPRECATED("This attribute is no longer writable in the ZGMatter standard", ios(16.4, 26.1), macos(13.3, 26.1), watchos(9.4, 26.1), tvos(16.4, 26.1));
- (void)writeAttributeColorPointBIntensityWithValue:(NSNumber * _Nullable)value completion:(ZGMTRStatusCompletion)completion ZGMTR_DEPRECATED("This attribute is no longer writable in the ZGMatter standard", ios(16.4, 26.1), macos(13.3, 26.1), watchos(9.4, 26.1), tvos(16.4, 26.1));
- (void)writeAttributeColorPointBIntensityWithValue:(NSNumber * _Nullable)value params:(ZGMTRWriteParams * _Nullable)params completion:(ZGMTRStatusCompletion)completion ZGMTR_DEPRECATED("This attribute is no longer writable in the ZGMatter standard", ios(16.4, 26.1), macos(13.3, 26.1), watchos(9.4, 26.1), tvos(16.4, 26.1));
- (void)writeAttributeWhitePointXWithValue:(NSNumber * _Nonnull)value completionHandler:(ZGMTRStatusCompletion)completionHandler ZGMTR_DEPRECATED("Please use writeAttributeWhitePointXWithValue:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (void)writeAttributeWhitePointXWithValue:(NSNumber * _Nonnull)value params:(ZGMTRWriteParams * _Nullable)params completionHandler:(ZGMTRStatusCompletion)completionHandler ZGMTR_DEPRECATED("Please use writeAttributeWhitePointXWithValue:params:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (void)writeAttributeWhitePointYWithValue:(NSNumber * _Nonnull)value completionHandler:(ZGMTRStatusCompletion)completionHandler ZGMTR_DEPRECATED("Please use writeAttributeWhitePointYWithValue:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (void)writeAttributeWhitePointYWithValue:(NSNumber * _Nonnull)value params:(ZGMTRWriteParams * _Nullable)params completionHandler:(ZGMTRStatusCompletion)completionHandler ZGMTR_DEPRECATED("Please use writeAttributeWhitePointYWithValue:params:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (void)writeAttributeColorPointRXWithValue:(NSNumber * _Nonnull)value completionHandler:(ZGMTRStatusCompletion)completionHandler ZGMTR_DEPRECATED("Please use writeAttributeColorPointRXWithValue:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (void)writeAttributeColorPointRXWithValue:(NSNumber * _Nonnull)value params:(ZGMTRWriteParams * _Nullable)params completionHandler:(ZGMTRStatusCompletion)completionHandler ZGMTR_DEPRECATED("Please use writeAttributeColorPointRXWithValue:params:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (void)writeAttributeColorPointRYWithValue:(NSNumber * _Nonnull)value completionHandler:(ZGMTRStatusCompletion)completionHandler ZGMTR_DEPRECATED("Please use writeAttributeColorPointRYWithValue:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (void)writeAttributeColorPointRYWithValue:(NSNumber * _Nonnull)value params:(ZGMTRWriteParams * _Nullable)params completionHandler:(ZGMTRStatusCompletion)completionHandler ZGMTR_DEPRECATED("Please use writeAttributeColorPointRYWithValue:params:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (void)writeAttributeColorPointRIntensityWithValue:(NSNumber * _Nullable)value completionHandler:(ZGMTRStatusCompletion)completionHandler ZGMTR_DEPRECATED("Please use writeAttributeColorPointRIntensityWithValue:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (void)writeAttributeColorPointRIntensityWithValue:(NSNumber * _Nullable)value params:(ZGMTRWriteParams * _Nullable)params completionHandler:(ZGMTRStatusCompletion)completionHandler ZGMTR_DEPRECATED("Please use writeAttributeColorPointRIntensityWithValue:params:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (void)writeAttributeColorPointGXWithValue:(NSNumber * _Nonnull)value completionHandler:(ZGMTRStatusCompletion)completionHandler ZGMTR_DEPRECATED("Please use writeAttributeColorPointGXWithValue:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (void)writeAttributeColorPointGXWithValue:(NSNumber * _Nonnull)value params:(ZGMTRWriteParams * _Nullable)params completionHandler:(ZGMTRStatusCompletion)completionHandler ZGMTR_DEPRECATED("Please use writeAttributeColorPointGXWithValue:params:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (void)writeAttributeColorPointGYWithValue:(NSNumber * _Nonnull)value completionHandler:(ZGMTRStatusCompletion)completionHandler ZGMTR_DEPRECATED("Please use writeAttributeColorPointGYWithValue:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (void)writeAttributeColorPointGYWithValue:(NSNumber * _Nonnull)value params:(ZGMTRWriteParams * _Nullable)params completionHandler:(ZGMTRStatusCompletion)completionHandler ZGMTR_DEPRECATED("Please use writeAttributeColorPointGYWithValue:params:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (void)writeAttributeColorPointGIntensityWithValue:(NSNumber * _Nullable)value completionHandler:(ZGMTRStatusCompletion)completionHandler ZGMTR_DEPRECATED("Please use writeAttributeColorPointGIntensityWithValue:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (void)writeAttributeColorPointGIntensityWithValue:(NSNumber * _Nullable)value params:(ZGMTRWriteParams * _Nullable)params completionHandler:(ZGMTRStatusCompletion)completionHandler ZGMTR_DEPRECATED("Please use writeAttributeColorPointGIntensityWithValue:params:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (void)writeAttributeColorPointBXWithValue:(NSNumber * _Nonnull)value completionHandler:(ZGMTRStatusCompletion)completionHandler ZGMTR_DEPRECATED("Please use writeAttributeColorPointBXWithValue:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (void)writeAttributeColorPointBXWithValue:(NSNumber * _Nonnull)value params:(ZGMTRWriteParams * _Nullable)params completionHandler:(ZGMTRStatusCompletion)completionHandler ZGMTR_DEPRECATED("Please use writeAttributeColorPointBXWithValue:params:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (void)writeAttributeColorPointBYWithValue:(NSNumber * _Nonnull)value completionHandler:(ZGMTRStatusCompletion)completionHandler ZGMTR_DEPRECATED("Please use writeAttributeColorPointBYWithValue:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (void)writeAttributeColorPointBYWithValue:(NSNumber * _Nonnull)value params:(ZGMTRWriteParams * _Nullable)params completionHandler:(ZGMTRStatusCompletion)completionHandler ZGMTR_DEPRECATED("Please use writeAttributeColorPointBYWithValue:params:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (void)writeAttributeColorPointBIntensityWithValue:(NSNumber * _Nullable)value completionHandler:(ZGMTRStatusCompletion)completionHandler ZGMTR_DEPRECATED("Please use writeAttributeColorPointBIntensityWithValue:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (void)writeAttributeColorPointBIntensityWithValue:(NSNumber * _Nullable)value params:(ZGMTRWriteParams * _Nullable)params completionHandler:(ZGMTRStatusCompletion)completionHandler ZGMTR_DEPRECATED("Please use writeAttributeColorPointBIntensityWithValue:params:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));

@end

@interface ZGMTRClusterColorControl (AttributesNowReadonly)

- (void)writeAttributeWhitePointXWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs ZGMTR_DEPRECATED("This attribute is no longer writable in the ZGMatter standard", ios(16.1, 26.1), macos(13.0, 26.1), watchos(9.1, 26.1), tvos(16.1, 26.1));
- (void)writeAttributeWhitePointXWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs params:(ZGMTRWriteParams * _Nullable)params ZGMTR_DEPRECATED("This attribute is no longer writable in the ZGMatter standard", ios(16.1, 26.1), macos(13.0, 26.1), watchos(9.1, 26.1), tvos(16.1, 26.1));
- (void)writeAttributeWhitePointYWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs ZGMTR_DEPRECATED("This attribute is no longer writable in the ZGMatter standard", ios(16.1, 26.1), macos(13.0, 26.1), watchos(9.1, 26.1), tvos(16.1, 26.1));
- (void)writeAttributeWhitePointYWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs params:(ZGMTRWriteParams * _Nullable)params ZGMTR_DEPRECATED("This attribute is no longer writable in the ZGMatter standard", ios(16.1, 26.1), macos(13.0, 26.1), watchos(9.1, 26.1), tvos(16.1, 26.1));
- (void)writeAttributeColorPointRXWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs ZGMTR_DEPRECATED("This attribute is no longer writable in the ZGMatter standard", ios(16.1, 26.1), macos(13.0, 26.1), watchos(9.1, 26.1), tvos(16.1, 26.1));
- (void)writeAttributeColorPointRXWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs params:(ZGMTRWriteParams * _Nullable)params ZGMTR_DEPRECATED("This attribute is no longer writable in the ZGMatter standard", ios(16.1, 26.1), macos(13.0, 26.1), watchos(9.1, 26.1), tvos(16.1, 26.1));
- (void)writeAttributeColorPointRYWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs ZGMTR_DEPRECATED("This attribute is no longer writable in the ZGMatter standard", ios(16.1, 26.1), macos(13.0, 26.1), watchos(9.1, 26.1), tvos(16.1, 26.1));
- (void)writeAttributeColorPointRYWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs params:(ZGMTRWriteParams * _Nullable)params ZGMTR_DEPRECATED("This attribute is no longer writable in the ZGMatter standard", ios(16.1, 26.1), macos(13.0, 26.1), watchos(9.1, 26.1), tvos(16.1, 26.1));
- (void)writeAttributeColorPointRIntensityWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs ZGMTR_DEPRECATED("This attribute is no longer writable in the ZGMatter standard", ios(16.1, 26.1), macos(13.0, 26.1), watchos(9.1, 26.1), tvos(16.1, 26.1));
- (void)writeAttributeColorPointRIntensityWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs params:(ZGMTRWriteParams * _Nullable)params ZGMTR_DEPRECATED("This attribute is no longer writable in the ZGMatter standard", ios(16.1, 26.1), macos(13.0, 26.1), watchos(9.1, 26.1), tvos(16.1, 26.1));
- (void)writeAttributeColorPointGXWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs ZGMTR_DEPRECATED("This attribute is no longer writable in the ZGMatter standard", ios(16.1, 26.1), macos(13.0, 26.1), watchos(9.1, 26.1), tvos(16.1, 26.1));
- (void)writeAttributeColorPointGXWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs params:(ZGMTRWriteParams * _Nullable)params ZGMTR_DEPRECATED("This attribute is no longer writable in the ZGMatter standard", ios(16.1, 26.1), macos(13.0, 26.1), watchos(9.1, 26.1), tvos(16.1, 26.1));
- (void)writeAttributeColorPointGYWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs ZGMTR_DEPRECATED("This attribute is no longer writable in the ZGMatter standard", ios(16.1, 26.1), macos(13.0, 26.1), watchos(9.1, 26.1), tvos(16.1, 26.1));
- (void)writeAttributeColorPointGYWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs params:(ZGMTRWriteParams * _Nullable)params ZGMTR_DEPRECATED("This attribute is no longer writable in the ZGMatter standard", ios(16.1, 26.1), macos(13.0, 26.1), watchos(9.1, 26.1), tvos(16.1, 26.1));
- (void)writeAttributeColorPointGIntensityWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs ZGMTR_DEPRECATED("This attribute is no longer writable in the ZGMatter standard", ios(16.1, 26.1), macos(13.0, 26.1), watchos(9.1, 26.1), tvos(16.1, 26.1));
- (void)writeAttributeColorPointGIntensityWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs params:(ZGMTRWriteParams * _Nullable)params ZGMTR_DEPRECATED("This attribute is no longer writable in the ZGMatter standard", ios(16.1, 26.1), macos(13.0, 26.1), watchos(9.1, 26.1), tvos(16.1, 26.1));
- (void)writeAttributeColorPointBXWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs ZGMTR_DEPRECATED("This attribute is no longer writable in the ZGMatter standard", ios(16.1, 26.1), macos(13.0, 26.1), watchos(9.1, 26.1), tvos(16.1, 26.1));
- (void)writeAttributeColorPointBXWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs params:(ZGMTRWriteParams * _Nullable)params ZGMTR_DEPRECATED("This attribute is no longer writable in the ZGMatter standard", ios(16.1, 26.1), macos(13.0, 26.1), watchos(9.1, 26.1), tvos(16.1, 26.1));
- (void)writeAttributeColorPointBYWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs ZGMTR_DEPRECATED("This attribute is no longer writable in the ZGMatter standard", ios(16.1, 26.1), macos(13.0, 26.1), watchos(9.1, 26.1), tvos(16.1, 26.1));
- (void)writeAttributeColorPointBYWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs params:(ZGMTRWriteParams * _Nullable)params ZGMTR_DEPRECATED("This attribute is no longer writable in the ZGMatter standard", ios(16.1, 26.1), macos(13.0, 26.1), watchos(9.1, 26.1), tvos(16.1, 26.1));
- (void)writeAttributeColorPointBIntensityWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs ZGMTR_DEPRECATED("This attribute is no longer writable in the ZGMatter standard", ios(16.1, 26.1), macos(13.0, 26.1), watchos(9.1, 26.1), tvos(16.1, 26.1));
- (void)writeAttributeColorPointBIntensityWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs params:(ZGMTRWriteParams * _Nullable)params ZGMTR_DEPRECATED("This attribute is no longer writable in the ZGMatter standard", ios(16.1, 26.1), macos(13.0, 26.1), watchos(9.1, 26.1), tvos(16.1, 26.1));

@end

#pragma mark - Clusters that were removed wholesale: OnOffSwitchConfiguration

/**
 * Cluster On/off Switch Configuration
 *
 * Attributes and commands for configuring On/Off switching devices.
 */
ZGMTR_DEPRECATED("OnOffSwitchConfiguration is deprecated and will be removed", ios(16.1, 18.2), macos(13.0, 15.2), watchos(9.1, 11.2), tvos(16.1, 18.2))
@interface ZGMTRBaseClusterOnOffSwitchConfiguration : ZGMTRGenericBaseCluster

- (void)readAttributeSwitchTypeWithCompletion:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completion ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));
- (void)subscribeAttributeSwitchTypeWithParams:(ZGMTRSubscribeParams *)params
                       subscriptionEstablished:(ZGMTRSubscriptionEstablishedHandler _Nullable)subscriptionEstablished
                                 reportHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))reportHandler ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));
+ (void)readAttributeSwitchTypeWithClusterStateCache:(ZGMTRClusterStateCacheContainer *)clusterStateCacheContainer endpoint:(NSNumber *)endpoint queue:(dispatch_queue_t)queue completion:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completion ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));

- (void)readAttributeSwitchActionsWithCompletion:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completion ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));
- (void)writeAttributeSwitchActionsWithValue:(NSNumber * _Nonnull)value completion:(ZGMTRStatusCompletion)completion ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));
- (void)writeAttributeSwitchActionsWithValue:(NSNumber * _Nonnull)value params:(ZGMTRWriteParams * _Nullable)params completion:(ZGMTRStatusCompletion)completion ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));
- (void)subscribeAttributeSwitchActionsWithParams:(ZGMTRSubscribeParams *)params
                          subscriptionEstablished:(ZGMTRSubscriptionEstablishedHandler _Nullable)subscriptionEstablished
                                    reportHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))reportHandler ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));
+ (void)readAttributeSwitchActionsWithClusterStateCache:(ZGMTRClusterStateCacheContainer *)clusterStateCacheContainer endpoint:(NSNumber *)endpoint queue:(dispatch_queue_t)queue completion:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completion ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));

- (void)readAttributeGeneratedCommandListWithCompletion:(void (^)(NSArray * _Nullable value, NSError * _Nullable error))completion ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));
- (void)subscribeAttributeGeneratedCommandListWithParams:(ZGMTRSubscribeParams *)params
                                 subscriptionEstablished:(ZGMTRSubscriptionEstablishedHandler _Nullable)subscriptionEstablished
                                           reportHandler:(void (^)(NSArray * _Nullable value, NSError * _Nullable error))reportHandler ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));
+ (void)readAttributeGeneratedCommandListWithClusterStateCache:(ZGMTRClusterStateCacheContainer *)clusterStateCacheContainer endpoint:(NSNumber *)endpoint queue:(dispatch_queue_t)queue completion:(void (^)(NSArray * _Nullable value, NSError * _Nullable error))completion ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));

- (void)readAttributeAcceptedCommandListWithCompletion:(void (^)(NSArray * _Nullable value, NSError * _Nullable error))completion ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));
- (void)subscribeAttributeAcceptedCommandListWithParams:(ZGMTRSubscribeParams *)params
                                subscriptionEstablished:(ZGMTRSubscriptionEstablishedHandler _Nullable)subscriptionEstablished
                                          reportHandler:(void (^)(NSArray * _Nullable value, NSError * _Nullable error))reportHandler ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));
+ (void)readAttributeAcceptedCommandListWithClusterStateCache:(ZGMTRClusterStateCacheContainer *)clusterStateCacheContainer endpoint:(NSNumber *)endpoint queue:(dispatch_queue_t)queue completion:(void (^)(NSArray * _Nullable value, NSError * _Nullable error))completion ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));

- (void)readAttributeAttributeListWithCompletion:(void (^)(NSArray * _Nullable value, NSError * _Nullable error))completion ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));
- (void)subscribeAttributeAttributeListWithParams:(ZGMTRSubscribeParams *)params
                          subscriptionEstablished:(ZGMTRSubscriptionEstablishedHandler _Nullable)subscriptionEstablished
                                    reportHandler:(void (^)(NSArray * _Nullable value, NSError * _Nullable error))reportHandler ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));
+ (void)readAttributeAttributeListWithClusterStateCache:(ZGMTRClusterStateCacheContainer *)clusterStateCacheContainer endpoint:(NSNumber *)endpoint queue:(dispatch_queue_t)queue completion:(void (^)(NSArray * _Nullable value, NSError * _Nullable error))completion ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));

- (void)readAttributeFeatureMapWithCompletion:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completion ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));
- (void)subscribeAttributeFeatureMapWithParams:(ZGMTRSubscribeParams *)params
                       subscriptionEstablished:(ZGMTRSubscriptionEstablishedHandler _Nullable)subscriptionEstablished
                                 reportHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))reportHandler ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));
+ (void)readAttributeFeatureMapWithClusterStateCache:(ZGMTRClusterStateCacheContainer *)clusterStateCacheContainer endpoint:(NSNumber *)endpoint queue:(dispatch_queue_t)queue completion:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completion ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));

- (void)readAttributeClusterRevisionWithCompletion:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completion ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));
- (void)subscribeAttributeClusterRevisionWithParams:(ZGMTRSubscribeParams *)params
                            subscriptionEstablished:(ZGMTRSubscriptionEstablishedHandler _Nullable)subscriptionEstablished
                                      reportHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))reportHandler ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));
+ (void)readAttributeClusterRevisionWithClusterStateCache:(ZGMTRClusterStateCacheContainer *)clusterStateCacheContainer endpoint:(NSNumber *)endpoint queue:(dispatch_queue_t)queue completion:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completion ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end

@interface ZGMTRBaseClusterOnOffSwitchConfiguration (Availability)

/**
 * For all instance methods (reads, writes, commands) that take a completion,
 * the completion will be called on the provided queue.
 */
- (instancetype _Nullable)initWithDevice:(ZGMTRBaseDevice *)device
                              endpointID:(NSNumber *)endpointID
                                   queue:(dispatch_queue_t)queue ZGMTR_DEPRECATED("OnOffSwitchConfiguration is deprecated and will be removed", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));

@end

@interface ZGMTRBaseClusterOnOffSwitchConfiguration (Deprecated)

- (nullable instancetype)initWithDevice:(ZGMTRBaseDevice *)device
                               endpoint:(uint16_t)endpoint
                                  queue:(dispatch_queue_t)queue ZGMTR_DEPRECATED("Please use initWithDevice:endpointID:queue:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));

- (void)readAttributeSwitchTypeWithCompletionHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completionHandler ZGMTR_DEPRECATED("Please use readAttributeSwitchTypeWithCompletion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (void)subscribeAttributeSwitchTypeWithMinInterval:(NSNumber * _Nonnull)minInterval maxInterval:(NSNumber * _Nonnull)maxInterval
                                             params:(ZGMTRSubscribeParams * _Nullable)params
                            subscriptionEstablished:(ZGMTRSubscriptionEstablishedHandler _Nullable)subscriptionEstablishedHandler
                                      reportHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))reportHandler ZGMTR_DEPRECATED("Please use subscribeAttributeSwitchTypeWithParams:subscriptionEstablished:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
+ (void)readAttributeSwitchTypeWithAttributeCache:(ZGMTRAttributeCacheContainer *)attributeCacheContainer endpoint:(NSNumber *)endpoint queue:(dispatch_queue_t)queue completionHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completionHandler ZGMTR_DEPRECATED("Please use readAttributeSwitchTypeWithAttributeCache:endpoint:queue:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));

- (void)readAttributeSwitchActionsWithCompletionHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completionHandler ZGMTR_DEPRECATED("Please use readAttributeSwitchActionsWithCompletion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (void)writeAttributeSwitchActionsWithValue:(NSNumber * _Nonnull)value completionHandler:(ZGMTRStatusCompletion)completionHandler ZGMTR_DEPRECATED("Please use writeAttributeSwitchActionsWithValue:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (void)writeAttributeSwitchActionsWithValue:(NSNumber * _Nonnull)value params:(ZGMTRWriteParams * _Nullable)params completionHandler:(ZGMTRStatusCompletion)completionHandler ZGMTR_DEPRECATED("Please use writeAttributeSwitchActionsWithValue:params:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (void)subscribeAttributeSwitchActionsWithMinInterval:(NSNumber * _Nonnull)minInterval maxInterval:(NSNumber * _Nonnull)maxInterval
                                                params:(ZGMTRSubscribeParams * _Nullable)params
                               subscriptionEstablished:(ZGMTRSubscriptionEstablishedHandler _Nullable)subscriptionEstablishedHandler
                                         reportHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))reportHandler ZGMTR_DEPRECATED("Please use subscribeAttributeSwitchActionsWithParams:subscriptionEstablished:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
+ (void)readAttributeSwitchActionsWithAttributeCache:(ZGMTRAttributeCacheContainer *)attributeCacheContainer endpoint:(NSNumber *)endpoint queue:(dispatch_queue_t)queue completionHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completionHandler ZGMTR_DEPRECATED("Please use readAttributeSwitchActionsWithAttributeCache:endpoint:queue:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));

- (void)readAttributeGeneratedCommandListWithCompletionHandler:(void (^)(NSArray * _Nullable value, NSError * _Nullable error))completionHandler ZGMTR_DEPRECATED("Please use readAttributeGeneratedCommandListWithCompletion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (void)subscribeAttributeGeneratedCommandListWithMinInterval:(NSNumber * _Nonnull)minInterval maxInterval:(NSNumber * _Nonnull)maxInterval
                                                       params:(ZGMTRSubscribeParams * _Nullable)params
                                      subscriptionEstablished:(ZGMTRSubscriptionEstablishedHandler _Nullable)subscriptionEstablishedHandler
                                                reportHandler:(void (^)(NSArray * _Nullable value, NSError * _Nullable error))reportHandler ZGMTR_DEPRECATED("Please use subscribeAttributeGeneratedCommandListWithParams:subscriptionEstablished:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
+ (void)readAttributeGeneratedCommandListWithAttributeCache:(ZGMTRAttributeCacheContainer *)attributeCacheContainer endpoint:(NSNumber *)endpoint queue:(dispatch_queue_t)queue completionHandler:(void (^)(NSArray * _Nullable value, NSError * _Nullable error))completionHandler ZGMTR_DEPRECATED("Please use readAttributeGeneratedCommandListWithAttributeCache:endpoint:queue:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));

- (void)readAttributeAcceptedCommandListWithCompletionHandler:(void (^)(NSArray * _Nullable value, NSError * _Nullable error))completionHandler ZGMTR_DEPRECATED("Please use readAttributeAcceptedCommandListWithCompletion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (void)subscribeAttributeAcceptedCommandListWithMinInterval:(NSNumber * _Nonnull)minInterval maxInterval:(NSNumber * _Nonnull)maxInterval
                                                      params:(ZGMTRSubscribeParams * _Nullable)params
                                     subscriptionEstablished:(ZGMTRSubscriptionEstablishedHandler _Nullable)subscriptionEstablishedHandler
                                               reportHandler:(void (^)(NSArray * _Nullable value, NSError * _Nullable error))reportHandler ZGMTR_DEPRECATED("Please use subscribeAttributeAcceptedCommandListWithParams:subscriptionEstablished:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
+ (void)readAttributeAcceptedCommandListWithAttributeCache:(ZGMTRAttributeCacheContainer *)attributeCacheContainer endpoint:(NSNumber *)endpoint queue:(dispatch_queue_t)queue completionHandler:(void (^)(NSArray * _Nullable value, NSError * _Nullable error))completionHandler ZGMTR_DEPRECATED("Please use readAttributeAcceptedCommandListWithAttributeCache:endpoint:queue:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));

- (void)readAttributeAttributeListWithCompletionHandler:(void (^)(NSArray * _Nullable value, NSError * _Nullable error))completionHandler ZGMTR_DEPRECATED("Please use readAttributeAttributeListWithCompletion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (void)subscribeAttributeAttributeListWithMinInterval:(NSNumber * _Nonnull)minInterval maxInterval:(NSNumber * _Nonnull)maxInterval
                                                params:(ZGMTRSubscribeParams * _Nullable)params
                               subscriptionEstablished:(ZGMTRSubscriptionEstablishedHandler _Nullable)subscriptionEstablishedHandler
                                         reportHandler:(void (^)(NSArray * _Nullable value, NSError * _Nullable error))reportHandler ZGMTR_DEPRECATED("Please use subscribeAttributeAttributeListWithParams:subscriptionEstablished:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
+ (void)readAttributeAttributeListWithAttributeCache:(ZGMTRAttributeCacheContainer *)attributeCacheContainer endpoint:(NSNumber *)endpoint queue:(dispatch_queue_t)queue completionHandler:(void (^)(NSArray * _Nullable value, NSError * _Nullable error))completionHandler ZGMTR_DEPRECATED("Please use readAttributeAttributeListWithAttributeCache:endpoint:queue:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));

- (void)readAttributeFeatureMapWithCompletionHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completionHandler ZGMTR_DEPRECATED("Please use readAttributeFeatureMapWithCompletion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (void)subscribeAttributeFeatureMapWithMinInterval:(NSNumber * _Nonnull)minInterval maxInterval:(NSNumber * _Nonnull)maxInterval
                                             params:(ZGMTRSubscribeParams * _Nullable)params
                            subscriptionEstablished:(ZGMTRSubscriptionEstablishedHandler _Nullable)subscriptionEstablishedHandler
                                      reportHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))reportHandler ZGMTR_DEPRECATED("Please use subscribeAttributeFeatureMapWithParams:subscriptionEstablished:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
+ (void)readAttributeFeatureMapWithAttributeCache:(ZGMTRAttributeCacheContainer *)attributeCacheContainer endpoint:(NSNumber *)endpoint queue:(dispatch_queue_t)queue completionHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completionHandler ZGMTR_DEPRECATED("Please use readAttributeFeatureMapWithAttributeCache:endpoint:queue:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));

- (void)readAttributeClusterRevisionWithCompletionHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completionHandler ZGMTR_DEPRECATED("Please use readAttributeClusterRevisionWithCompletion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (void)subscribeAttributeClusterRevisionWithMinInterval:(NSNumber * _Nonnull)minInterval maxInterval:(NSNumber * _Nonnull)maxInterval
                                                  params:(ZGMTRSubscribeParams * _Nullable)params
                                 subscriptionEstablished:(ZGMTRSubscriptionEstablishedHandler _Nullable)subscriptionEstablishedHandler
                                           reportHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))reportHandler ZGMTR_DEPRECATED("Please use subscribeAttributeClusterRevisionWithParams:subscriptionEstablished:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
+ (void)readAttributeClusterRevisionWithAttributeCache:(ZGMTRAttributeCacheContainer *)attributeCacheContainer endpoint:(NSNumber *)endpoint queue:(dispatch_queue_t)queue completionHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completionHandler ZGMTR_DEPRECATED("Please use readAttributeClusterRevisionWithAttributeCache:endpoint:queue:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));

@end

/**
 * Cluster On/off Switch Configuration
 *    Attributes and commands for configuring On/Off switching devices.
 */
ZGMTR_DEPRECATED("OnOffSwitchConfiguration is deprecated and will be removed", ios(16.1, 18.2), macos(13.0, 15.2), watchos(9.1, 11.2), tvos(16.1, 18.2))
@interface ZGMTRClusterOnOffSwitchConfiguration : ZGMTRGenericCluster

- (NSDictionary<NSString *, id> * _Nullable)readAttributeSwitchTypeWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.1, 18.2), macos(13.0, 15.2), watchos(9.1, 11.2), tvos(16.1, 18.2));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeSwitchActionsWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.1, 18.2), macos(13.0, 15.2), watchos(9.1, 11.2), tvos(16.1, 18.2));
- (void)writeAttributeSwitchActionsWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.1, 18.2), macos(13.0, 15.2), watchos(9.1, 11.2), tvos(16.1, 18.2));
- (void)writeAttributeSwitchActionsWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs params:(ZGMTRWriteParams * _Nullable)params ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.1, 18.2), macos(13.0, 15.2), watchos(9.1, 11.2), tvos(16.1, 18.2));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeGeneratedCommandListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.1, 18.2), macos(13.0, 15.2), watchos(9.1, 11.2), tvos(16.1, 18.2));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeAcceptedCommandListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.1, 18.2), macos(13.0, 15.2), watchos(9.1, 11.2), tvos(16.1, 18.2));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeAttributeListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.1, 18.2), macos(13.0, 15.2), watchos(9.1, 11.2), tvos(16.1, 18.2));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeFeatureMapWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.1, 18.2), macos(13.0, 15.2), watchos(9.1, 11.2), tvos(16.1, 18.2));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeClusterRevisionWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.1, 18.2), macos(13.0, 15.2), watchos(9.1, 11.2), tvos(16.1, 18.2));

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end

@interface ZGMTRClusterOnOffSwitchConfiguration (Availability)

/**
 * The queue is currently unused, but may be used in the future for calling completions
 * for command invocations if commands are added to this cluster.
 */
- (instancetype _Nullable)initWithDevice:(ZGMTRDevice *)device
                              endpointID:(NSNumber *)endpointID
                                   queue:(dispatch_queue_t)queue ZGMTR_DEPRECATED("OnOffSwitchConfiguration is deprecated and will be removed", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));

@end

@interface ZGMTRClusterOnOffSwitchConfiguration (Deprecated)

- (nullable instancetype)initWithDevice:(ZGMTRDevice *)device
                               endpoint:(uint16_t)endpoint
                                  queue:(dispatch_queue_t)queue ZGMTR_DEPRECATED("Please use initWithDevice:endpoindID:queue:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));

@end

#pragma mark - Clusters that were removed wholesale: BinaryInputBasic

/**
 * Cluster Binary Input (Basic)
 *
 * An interface for reading the value of a binary measurement and accessing various characteristics of that measurement.
 */
ZGMTR_DEPRECATED("BinaryInputBasic is deprecated and will be removed", ios(16.1, 18.2), macos(13.0, 15.2), watchos(9.1, 11.2), tvos(16.1, 18.2))
@interface ZGMTRBaseClusterBinaryInputBasic : ZGMTRGenericBaseCluster

- (void)readAttributeActiveTextWithCompletion:(void (^)(NSString * _Nullable value, NSError * _Nullable error))completion ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));
- (void)writeAttributeActiveTextWithValue:(NSString * _Nonnull)value completion:(ZGMTRStatusCompletion)completion ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));
- (void)writeAttributeActiveTextWithValue:(NSString * _Nonnull)value params:(ZGMTRWriteParams * _Nullable)params completion:(ZGMTRStatusCompletion)completion ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));
- (void)subscribeAttributeActiveTextWithParams:(ZGMTRSubscribeParams *)params
                       subscriptionEstablished:(ZGMTRSubscriptionEstablishedHandler _Nullable)subscriptionEstablished
                                 reportHandler:(void (^)(NSString * _Nullable value, NSError * _Nullable error))reportHandler ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));
+ (void)readAttributeActiveTextWithClusterStateCache:(ZGMTRClusterStateCacheContainer *)clusterStateCacheContainer endpoint:(NSNumber *)endpoint queue:(dispatch_queue_t)queue completion:(void (^)(NSString * _Nullable value, NSError * _Nullable error))completion ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));

- (void)readAttributeDescriptionWithCompletion:(void (^)(NSString * _Nullable value, NSError * _Nullable error))completion ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));
- (void)writeAttributeDescriptionWithValue:(NSString * _Nonnull)value completion:(ZGMTRStatusCompletion)completion ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));
- (void)writeAttributeDescriptionWithValue:(NSString * _Nonnull)value params:(ZGMTRWriteParams * _Nullable)params completion:(ZGMTRStatusCompletion)completion ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));
- (void)subscribeAttributeDescriptionWithParams:(ZGMTRSubscribeParams *)params
                        subscriptionEstablished:(ZGMTRSubscriptionEstablishedHandler _Nullable)subscriptionEstablished
                                  reportHandler:(void (^)(NSString * _Nullable value, NSError * _Nullable error))reportHandler ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));
+ (void)readAttributeDescriptionWithClusterStateCache:(ZGMTRClusterStateCacheContainer *)clusterStateCacheContainer endpoint:(NSNumber *)endpoint queue:(dispatch_queue_t)queue completion:(void (^)(NSString * _Nullable value, NSError * _Nullable error))completion ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));

- (void)readAttributeInactiveTextWithCompletion:(void (^)(NSString * _Nullable value, NSError * _Nullable error))completion ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));
- (void)writeAttributeInactiveTextWithValue:(NSString * _Nonnull)value completion:(ZGMTRStatusCompletion)completion ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));
- (void)writeAttributeInactiveTextWithValue:(NSString * _Nonnull)value params:(ZGMTRWriteParams * _Nullable)params completion:(ZGMTRStatusCompletion)completion ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));
- (void)subscribeAttributeInactiveTextWithParams:(ZGMTRSubscribeParams *)params
                         subscriptionEstablished:(ZGMTRSubscriptionEstablishedHandler _Nullable)subscriptionEstablished
                                   reportHandler:(void (^)(NSString * _Nullable value, NSError * _Nullable error))reportHandler ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));
+ (void)readAttributeInactiveTextWithClusterStateCache:(ZGMTRClusterStateCacheContainer *)clusterStateCacheContainer endpoint:(NSNumber *)endpoint queue:(dispatch_queue_t)queue completion:(void (^)(NSString * _Nullable value, NSError * _Nullable error))completion ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));

- (void)readAttributeOutOfServiceWithCompletion:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completion ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));
- (void)writeAttributeOutOfServiceWithValue:(NSNumber * _Nonnull)value completion:(ZGMTRStatusCompletion)completion ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));
- (void)writeAttributeOutOfServiceWithValue:(NSNumber * _Nonnull)value params:(ZGMTRWriteParams * _Nullable)params completion:(ZGMTRStatusCompletion)completion ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));
- (void)subscribeAttributeOutOfServiceWithParams:(ZGMTRSubscribeParams *)params
                         subscriptionEstablished:(ZGMTRSubscriptionEstablishedHandler _Nullable)subscriptionEstablished
                                   reportHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))reportHandler ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));
+ (void)readAttributeOutOfServiceWithClusterStateCache:(ZGMTRClusterStateCacheContainer *)clusterStateCacheContainer endpoint:(NSNumber *)endpoint queue:(dispatch_queue_t)queue completion:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completion ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));

- (void)readAttributePolarityWithCompletion:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completion ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));
- (void)subscribeAttributePolarityWithParams:(ZGMTRSubscribeParams *)params
                     subscriptionEstablished:(ZGMTRSubscriptionEstablishedHandler _Nullable)subscriptionEstablished
                               reportHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))reportHandler ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));
+ (void)readAttributePolarityWithClusterStateCache:(ZGMTRClusterStateCacheContainer *)clusterStateCacheContainer endpoint:(NSNumber *)endpoint queue:(dispatch_queue_t)queue completion:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completion ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));

- (void)readAttributePresentValueWithCompletion:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completion ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));
- (void)writeAttributePresentValueWithValue:(NSNumber * _Nonnull)value completion:(ZGMTRStatusCompletion)completion ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));
- (void)writeAttributePresentValueWithValue:(NSNumber * _Nonnull)value params:(ZGMTRWriteParams * _Nullable)params completion:(ZGMTRStatusCompletion)completion ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));
- (void)subscribeAttributePresentValueWithParams:(ZGMTRSubscribeParams *)params
                         subscriptionEstablished:(ZGMTRSubscriptionEstablishedHandler _Nullable)subscriptionEstablished
                                   reportHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))reportHandler ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));
+ (void)readAttributePresentValueWithClusterStateCache:(ZGMTRClusterStateCacheContainer *)clusterStateCacheContainer endpoint:(NSNumber *)endpoint queue:(dispatch_queue_t)queue completion:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completion ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));

- (void)readAttributeReliabilityWithCompletion:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completion ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));
- (void)writeAttributeReliabilityWithValue:(NSNumber * _Nonnull)value completion:(ZGMTRStatusCompletion)completion ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));
- (void)writeAttributeReliabilityWithValue:(NSNumber * _Nonnull)value params:(ZGMTRWriteParams * _Nullable)params completion:(ZGMTRStatusCompletion)completion ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));
- (void)subscribeAttributeReliabilityWithParams:(ZGMTRSubscribeParams *)params
                        subscriptionEstablished:(ZGMTRSubscriptionEstablishedHandler _Nullable)subscriptionEstablished
                                  reportHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))reportHandler ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));
+ (void)readAttributeReliabilityWithClusterStateCache:(ZGMTRClusterStateCacheContainer *)clusterStateCacheContainer endpoint:(NSNumber *)endpoint queue:(dispatch_queue_t)queue completion:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completion ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));

- (void)readAttributeStatusFlagsWithCompletion:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completion ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));
- (void)subscribeAttributeStatusFlagsWithParams:(ZGMTRSubscribeParams *)params
                        subscriptionEstablished:(ZGMTRSubscriptionEstablishedHandler _Nullable)subscriptionEstablished
                                  reportHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))reportHandler ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));
+ (void)readAttributeStatusFlagsWithClusterStateCache:(ZGMTRClusterStateCacheContainer *)clusterStateCacheContainer endpoint:(NSNumber *)endpoint queue:(dispatch_queue_t)queue completion:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completion ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));

- (void)readAttributeApplicationTypeWithCompletion:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completion ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));
- (void)subscribeAttributeApplicationTypeWithParams:(ZGMTRSubscribeParams *)params
                            subscriptionEstablished:(ZGMTRSubscriptionEstablishedHandler _Nullable)subscriptionEstablished
                                      reportHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))reportHandler ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));
+ (void)readAttributeApplicationTypeWithClusterStateCache:(ZGMTRClusterStateCacheContainer *)clusterStateCacheContainer endpoint:(NSNumber *)endpoint queue:(dispatch_queue_t)queue completion:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completion ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));

- (void)readAttributeGeneratedCommandListWithCompletion:(void (^)(NSArray * _Nullable value, NSError * _Nullable error))completion ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));
- (void)subscribeAttributeGeneratedCommandListWithParams:(ZGMTRSubscribeParams *)params
                                 subscriptionEstablished:(ZGMTRSubscriptionEstablishedHandler _Nullable)subscriptionEstablished
                                           reportHandler:(void (^)(NSArray * _Nullable value, NSError * _Nullable error))reportHandler ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));
+ (void)readAttributeGeneratedCommandListWithClusterStateCache:(ZGMTRClusterStateCacheContainer *)clusterStateCacheContainer endpoint:(NSNumber *)endpoint queue:(dispatch_queue_t)queue completion:(void (^)(NSArray * _Nullable value, NSError * _Nullable error))completion ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));

- (void)readAttributeAcceptedCommandListWithCompletion:(void (^)(NSArray * _Nullable value, NSError * _Nullable error))completion ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));
- (void)subscribeAttributeAcceptedCommandListWithParams:(ZGMTRSubscribeParams *)params
                                subscriptionEstablished:(ZGMTRSubscriptionEstablishedHandler _Nullable)subscriptionEstablished
                                          reportHandler:(void (^)(NSArray * _Nullable value, NSError * _Nullable error))reportHandler ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));
+ (void)readAttributeAcceptedCommandListWithClusterStateCache:(ZGMTRClusterStateCacheContainer *)clusterStateCacheContainer endpoint:(NSNumber *)endpoint queue:(dispatch_queue_t)queue completion:(void (^)(NSArray * _Nullable value, NSError * _Nullable error))completion ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));

- (void)readAttributeAttributeListWithCompletion:(void (^)(NSArray * _Nullable value, NSError * _Nullable error))completion ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));
- (void)subscribeAttributeAttributeListWithParams:(ZGMTRSubscribeParams *)params
                          subscriptionEstablished:(ZGMTRSubscriptionEstablishedHandler _Nullable)subscriptionEstablished
                                    reportHandler:(void (^)(NSArray * _Nullable value, NSError * _Nullable error))reportHandler ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));
+ (void)readAttributeAttributeListWithClusterStateCache:(ZGMTRClusterStateCacheContainer *)clusterStateCacheContainer endpoint:(NSNumber *)endpoint queue:(dispatch_queue_t)queue completion:(void (^)(NSArray * _Nullable value, NSError * _Nullable error))completion ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));

- (void)readAttributeFeatureMapWithCompletion:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completion ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));
- (void)subscribeAttributeFeatureMapWithParams:(ZGMTRSubscribeParams *)params
                       subscriptionEstablished:(ZGMTRSubscriptionEstablishedHandler _Nullable)subscriptionEstablished
                                 reportHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))reportHandler ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));
+ (void)readAttributeFeatureMapWithClusterStateCache:(ZGMTRClusterStateCacheContainer *)clusterStateCacheContainer endpoint:(NSNumber *)endpoint queue:(dispatch_queue_t)queue completion:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completion ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));

- (void)readAttributeClusterRevisionWithCompletion:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completion ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));
- (void)subscribeAttributeClusterRevisionWithParams:(ZGMTRSubscribeParams *)params
                            subscriptionEstablished:(ZGMTRSubscriptionEstablishedHandler _Nullable)subscriptionEstablished
                                      reportHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))reportHandler ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));
+ (void)readAttributeClusterRevisionWithClusterStateCache:(ZGMTRClusterStateCacheContainer *)clusterStateCacheContainer endpoint:(NSNumber *)endpoint queue:(dispatch_queue_t)queue completion:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completion ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end

@interface ZGMTRBaseClusterBinaryInputBasic (Availability)

/**
 * For all instance methods (reads, writes, commands) that take a completion,
 * the completion will be called on the provided queue.
 */
- (instancetype _Nullable)initWithDevice:(ZGMTRBaseDevice *)device
                              endpointID:(NSNumber *)endpointID
                                   queue:(dispatch_queue_t)queue ZGMTR_DEPRECATED("BinaryInputBasic is deprecated and will be removed", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));

@end

@interface ZGMTRBaseClusterBinaryInputBasic (Deprecated)

- (nullable instancetype)initWithDevice:(ZGMTRBaseDevice *)device
                               endpoint:(uint16_t)endpoint
                                  queue:(dispatch_queue_t)queue ZGMTR_DEPRECATED("Please use initWithDevice:endpointID:queue:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));

- (void)readAttributeActiveTextWithCompletionHandler:(void (^)(NSString * _Nullable value, NSError * _Nullable error))completionHandler ZGMTR_DEPRECATED("Please use readAttributeActiveTextWithCompletion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (void)writeAttributeActiveTextWithValue:(NSString * _Nonnull)value completionHandler:(ZGMTRStatusCompletion)completionHandler ZGMTR_DEPRECATED("Please use writeAttributeActiveTextWithValue:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (void)writeAttributeActiveTextWithValue:(NSString * _Nonnull)value params:(ZGMTRWriteParams * _Nullable)params completionHandler:(ZGMTRStatusCompletion)completionHandler ZGMTR_DEPRECATED("Please use writeAttributeActiveTextWithValue:params:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (void)subscribeAttributeActiveTextWithMinInterval:(NSNumber * _Nonnull)minInterval maxInterval:(NSNumber * _Nonnull)maxInterval
                                             params:(ZGMTRSubscribeParams * _Nullable)params
                            subscriptionEstablished:(ZGMTRSubscriptionEstablishedHandler _Nullable)subscriptionEstablishedHandler
                                      reportHandler:(void (^)(NSString * _Nullable value, NSError * _Nullable error))reportHandler ZGMTR_DEPRECATED("Please use subscribeAttributeActiveTextWithParams:subscriptionEstablished:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
+ (void)readAttributeActiveTextWithAttributeCache:(ZGMTRAttributeCacheContainer *)attributeCacheContainer endpoint:(NSNumber *)endpoint queue:(dispatch_queue_t)queue completionHandler:(void (^)(NSString * _Nullable value, NSError * _Nullable error))completionHandler ZGMTR_DEPRECATED("Please use readAttributeActiveTextWithAttributeCache:endpoint:queue:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));

- (void)readAttributeDescriptionWithCompletionHandler:(void (^)(NSString * _Nullable value, NSError * _Nullable error))completionHandler ZGMTR_DEPRECATED("Please use readAttributeDescriptionWithCompletion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (void)writeAttributeDescriptionWithValue:(NSString * _Nonnull)value completionHandler:(ZGMTRStatusCompletion)completionHandler ZGMTR_DEPRECATED("Please use writeAttributeDescriptionWithValue:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (void)writeAttributeDescriptionWithValue:(NSString * _Nonnull)value params:(ZGMTRWriteParams * _Nullable)params completionHandler:(ZGMTRStatusCompletion)completionHandler ZGMTR_DEPRECATED("Please use writeAttributeDescriptionWithValue:params:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (void)subscribeAttributeDescriptionWithMinInterval:(NSNumber * _Nonnull)minInterval maxInterval:(NSNumber * _Nonnull)maxInterval
                                              params:(ZGMTRSubscribeParams * _Nullable)params
                             subscriptionEstablished:(ZGMTRSubscriptionEstablishedHandler _Nullable)subscriptionEstablishedHandler
                                       reportHandler:(void (^)(NSString * _Nullable value, NSError * _Nullable error))reportHandler ZGMTR_DEPRECATED("Please use subscribeAttributeDescriptionWithParams:subscriptionEstablished:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
+ (void)readAttributeDescriptionWithAttributeCache:(ZGMTRAttributeCacheContainer *)attributeCacheContainer endpoint:(NSNumber *)endpoint queue:(dispatch_queue_t)queue completionHandler:(void (^)(NSString * _Nullable value, NSError * _Nullable error))completionHandler ZGMTR_DEPRECATED("Please use readAttributeDescriptionWithAttributeCache:endpoint:queue:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));

- (void)readAttributeInactiveTextWithCompletionHandler:(void (^)(NSString * _Nullable value, NSError * _Nullable error))completionHandler ZGMTR_DEPRECATED("Please use readAttributeInactiveTextWithCompletion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (void)writeAttributeInactiveTextWithValue:(NSString * _Nonnull)value completionHandler:(ZGMTRStatusCompletion)completionHandler ZGMTR_DEPRECATED("Please use writeAttributeInactiveTextWithValue:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (void)writeAttributeInactiveTextWithValue:(NSString * _Nonnull)value params:(ZGMTRWriteParams * _Nullable)params completionHandler:(ZGMTRStatusCompletion)completionHandler ZGMTR_DEPRECATED("Please use writeAttributeInactiveTextWithValue:params:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (void)subscribeAttributeInactiveTextWithMinInterval:(NSNumber * _Nonnull)minInterval maxInterval:(NSNumber * _Nonnull)maxInterval
                                               params:(ZGMTRSubscribeParams * _Nullable)params
                              subscriptionEstablished:(ZGMTRSubscriptionEstablishedHandler _Nullable)subscriptionEstablishedHandler
                                        reportHandler:(void (^)(NSString * _Nullable value, NSError * _Nullable error))reportHandler ZGMTR_DEPRECATED("Please use subscribeAttributeInactiveTextWithParams:subscriptionEstablished:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
+ (void)readAttributeInactiveTextWithAttributeCache:(ZGMTRAttributeCacheContainer *)attributeCacheContainer endpoint:(NSNumber *)endpoint queue:(dispatch_queue_t)queue completionHandler:(void (^)(NSString * _Nullable value, NSError * _Nullable error))completionHandler ZGMTR_DEPRECATED("Please use readAttributeInactiveTextWithAttributeCache:endpoint:queue:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));

- (void)readAttributeOutOfServiceWithCompletionHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completionHandler ZGMTR_DEPRECATED("Please use readAttributeOutOfServiceWithCompletion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (void)writeAttributeOutOfServiceWithValue:(NSNumber * _Nonnull)value completionHandler:(ZGMTRStatusCompletion)completionHandler ZGMTR_DEPRECATED("Please use writeAttributeOutOfServiceWithValue:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (void)writeAttributeOutOfServiceWithValue:(NSNumber * _Nonnull)value params:(ZGMTRWriteParams * _Nullable)params completionHandler:(ZGMTRStatusCompletion)completionHandler ZGMTR_DEPRECATED("Please use writeAttributeOutOfServiceWithValue:params:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (void)subscribeAttributeOutOfServiceWithMinInterval:(NSNumber * _Nonnull)minInterval maxInterval:(NSNumber * _Nonnull)maxInterval
                                               params:(ZGMTRSubscribeParams * _Nullable)params
                              subscriptionEstablished:(ZGMTRSubscriptionEstablishedHandler _Nullable)subscriptionEstablishedHandler
                                        reportHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))reportHandler ZGMTR_DEPRECATED("Please use subscribeAttributeOutOfServiceWithParams:subscriptionEstablished:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
+ (void)readAttributeOutOfServiceWithAttributeCache:(ZGMTRAttributeCacheContainer *)attributeCacheContainer endpoint:(NSNumber *)endpoint queue:(dispatch_queue_t)queue completionHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completionHandler ZGMTR_DEPRECATED("Please use readAttributeOutOfServiceWithAttributeCache:endpoint:queue:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));

- (void)readAttributePolarityWithCompletionHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completionHandler ZGMTR_DEPRECATED("Please use readAttributePolarityWithCompletion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (void)subscribeAttributePolarityWithMinInterval:(NSNumber * _Nonnull)minInterval maxInterval:(NSNumber * _Nonnull)maxInterval
                                           params:(ZGMTRSubscribeParams * _Nullable)params
                          subscriptionEstablished:(ZGMTRSubscriptionEstablishedHandler _Nullable)subscriptionEstablishedHandler
                                    reportHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))reportHandler ZGMTR_DEPRECATED("Please use subscribeAttributePolarityWithParams:subscriptionEstablished:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
+ (void)readAttributePolarityWithAttributeCache:(ZGMTRAttributeCacheContainer *)attributeCacheContainer endpoint:(NSNumber *)endpoint queue:(dispatch_queue_t)queue completionHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completionHandler ZGMTR_DEPRECATED("Please use readAttributePolarityWithAttributeCache:endpoint:queue:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));

- (void)readAttributePresentValueWithCompletionHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completionHandler ZGMTR_DEPRECATED("Please use readAttributePresentValueWithCompletion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (void)writeAttributePresentValueWithValue:(NSNumber * _Nonnull)value completionHandler:(ZGMTRStatusCompletion)completionHandler ZGMTR_DEPRECATED("Please use writeAttributePresentValueWithValue:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (void)writeAttributePresentValueWithValue:(NSNumber * _Nonnull)value params:(ZGMTRWriteParams * _Nullable)params completionHandler:(ZGMTRStatusCompletion)completionHandler ZGMTR_DEPRECATED("Please use writeAttributePresentValueWithValue:params:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (void)subscribeAttributePresentValueWithMinInterval:(NSNumber * _Nonnull)minInterval maxInterval:(NSNumber * _Nonnull)maxInterval
                                               params:(ZGMTRSubscribeParams * _Nullable)params
                              subscriptionEstablished:(ZGMTRSubscriptionEstablishedHandler _Nullable)subscriptionEstablishedHandler
                                        reportHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))reportHandler ZGMTR_DEPRECATED("Please use subscribeAttributePresentValueWithParams:subscriptionEstablished:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
+ (void)readAttributePresentValueWithAttributeCache:(ZGMTRAttributeCacheContainer *)attributeCacheContainer endpoint:(NSNumber *)endpoint queue:(dispatch_queue_t)queue completionHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completionHandler ZGMTR_DEPRECATED("Please use readAttributePresentValueWithAttributeCache:endpoint:queue:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));

- (void)readAttributeReliabilityWithCompletionHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completionHandler ZGMTR_DEPRECATED("Please use readAttributeReliabilityWithCompletion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (void)writeAttributeReliabilityWithValue:(NSNumber * _Nonnull)value completionHandler:(ZGMTRStatusCompletion)completionHandler ZGMTR_DEPRECATED("Please use writeAttributeReliabilityWithValue:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (void)writeAttributeReliabilityWithValue:(NSNumber * _Nonnull)value params:(ZGMTRWriteParams * _Nullable)params completionHandler:(ZGMTRStatusCompletion)completionHandler ZGMTR_DEPRECATED("Please use writeAttributeReliabilityWithValue:params:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (void)subscribeAttributeReliabilityWithMinInterval:(NSNumber * _Nonnull)minInterval maxInterval:(NSNumber * _Nonnull)maxInterval
                                              params:(ZGMTRSubscribeParams * _Nullable)params
                             subscriptionEstablished:(ZGMTRSubscriptionEstablishedHandler _Nullable)subscriptionEstablishedHandler
                                       reportHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))reportHandler ZGMTR_DEPRECATED("Please use subscribeAttributeReliabilityWithParams:subscriptionEstablished:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
+ (void)readAttributeReliabilityWithAttributeCache:(ZGMTRAttributeCacheContainer *)attributeCacheContainer endpoint:(NSNumber *)endpoint queue:(dispatch_queue_t)queue completionHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completionHandler ZGMTR_DEPRECATED("Please use readAttributeReliabilityWithAttributeCache:endpoint:queue:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));

- (void)readAttributeStatusFlagsWithCompletionHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completionHandler ZGMTR_DEPRECATED("Please use readAttributeStatusFlagsWithCompletion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (void)subscribeAttributeStatusFlagsWithMinInterval:(NSNumber * _Nonnull)minInterval maxInterval:(NSNumber * _Nonnull)maxInterval
                                              params:(ZGMTRSubscribeParams * _Nullable)params
                             subscriptionEstablished:(ZGMTRSubscriptionEstablishedHandler _Nullable)subscriptionEstablishedHandler
                                       reportHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))reportHandler ZGMTR_DEPRECATED("Please use subscribeAttributeStatusFlagsWithParams:subscriptionEstablished:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
+ (void)readAttributeStatusFlagsWithAttributeCache:(ZGMTRAttributeCacheContainer *)attributeCacheContainer endpoint:(NSNumber *)endpoint queue:(dispatch_queue_t)queue completionHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completionHandler ZGMTR_DEPRECATED("Please use readAttributeStatusFlagsWithAttributeCache:endpoint:queue:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));

- (void)readAttributeApplicationTypeWithCompletionHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completionHandler ZGMTR_DEPRECATED("Please use readAttributeApplicationTypeWithCompletion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (void)subscribeAttributeApplicationTypeWithMinInterval:(NSNumber * _Nonnull)minInterval maxInterval:(NSNumber * _Nonnull)maxInterval
                                                  params:(ZGMTRSubscribeParams * _Nullable)params
                                 subscriptionEstablished:(ZGMTRSubscriptionEstablishedHandler _Nullable)subscriptionEstablishedHandler
                                           reportHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))reportHandler ZGMTR_DEPRECATED("Please use subscribeAttributeApplicationTypeWithParams:subscriptionEstablished:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
+ (void)readAttributeApplicationTypeWithAttributeCache:(ZGMTRAttributeCacheContainer *)attributeCacheContainer endpoint:(NSNumber *)endpoint queue:(dispatch_queue_t)queue completionHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completionHandler ZGMTR_DEPRECATED("Please use readAttributeApplicationTypeWithAttributeCache:endpoint:queue:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));

- (void)readAttributeGeneratedCommandListWithCompletionHandler:(void (^)(NSArray * _Nullable value, NSError * _Nullable error))completionHandler ZGMTR_DEPRECATED("Please use readAttributeGeneratedCommandListWithCompletion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (void)subscribeAttributeGeneratedCommandListWithMinInterval:(NSNumber * _Nonnull)minInterval maxInterval:(NSNumber * _Nonnull)maxInterval
                                                       params:(ZGMTRSubscribeParams * _Nullable)params
                                      subscriptionEstablished:(ZGMTRSubscriptionEstablishedHandler _Nullable)subscriptionEstablishedHandler
                                                reportHandler:(void (^)(NSArray * _Nullable value, NSError * _Nullable error))reportHandler ZGMTR_DEPRECATED("Please use subscribeAttributeGeneratedCommandListWithParams:subscriptionEstablished:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
+ (void)readAttributeGeneratedCommandListWithAttributeCache:(ZGMTRAttributeCacheContainer *)attributeCacheContainer endpoint:(NSNumber *)endpoint queue:(dispatch_queue_t)queue completionHandler:(void (^)(NSArray * _Nullable value, NSError * _Nullable error))completionHandler ZGMTR_DEPRECATED("Please use readAttributeGeneratedCommandListWithAttributeCache:endpoint:queue:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));

- (void)readAttributeAcceptedCommandListWithCompletionHandler:(void (^)(NSArray * _Nullable value, NSError * _Nullable error))completionHandler ZGMTR_DEPRECATED("Please use readAttributeAcceptedCommandListWithCompletion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (void)subscribeAttributeAcceptedCommandListWithMinInterval:(NSNumber * _Nonnull)minInterval maxInterval:(NSNumber * _Nonnull)maxInterval
                                                      params:(ZGMTRSubscribeParams * _Nullable)params
                                     subscriptionEstablished:(ZGMTRSubscriptionEstablishedHandler _Nullable)subscriptionEstablishedHandler
                                               reportHandler:(void (^)(NSArray * _Nullable value, NSError * _Nullable error))reportHandler ZGMTR_DEPRECATED("Please use subscribeAttributeAcceptedCommandListWithParams:subscriptionEstablished:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
+ (void)readAttributeAcceptedCommandListWithAttributeCache:(ZGMTRAttributeCacheContainer *)attributeCacheContainer endpoint:(NSNumber *)endpoint queue:(dispatch_queue_t)queue completionHandler:(void (^)(NSArray * _Nullable value, NSError * _Nullable error))completionHandler ZGMTR_DEPRECATED("Please use readAttributeAcceptedCommandListWithAttributeCache:endpoint:queue:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));

- (void)readAttributeAttributeListWithCompletionHandler:(void (^)(NSArray * _Nullable value, NSError * _Nullable error))completionHandler ZGMTR_DEPRECATED("Please use readAttributeAttributeListWithCompletion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (void)subscribeAttributeAttributeListWithMinInterval:(NSNumber * _Nonnull)minInterval maxInterval:(NSNumber * _Nonnull)maxInterval
                                                params:(ZGMTRSubscribeParams * _Nullable)params
                               subscriptionEstablished:(ZGMTRSubscriptionEstablishedHandler _Nullable)subscriptionEstablishedHandler
                                         reportHandler:(void (^)(NSArray * _Nullable value, NSError * _Nullable error))reportHandler ZGMTR_DEPRECATED("Please use subscribeAttributeAttributeListWithParams:subscriptionEstablished:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
+ (void)readAttributeAttributeListWithAttributeCache:(ZGMTRAttributeCacheContainer *)attributeCacheContainer endpoint:(NSNumber *)endpoint queue:(dispatch_queue_t)queue completionHandler:(void (^)(NSArray * _Nullable value, NSError * _Nullable error))completionHandler ZGMTR_DEPRECATED("Please use readAttributeAttributeListWithAttributeCache:endpoint:queue:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));

- (void)readAttributeFeatureMapWithCompletionHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completionHandler ZGMTR_DEPRECATED("Please use readAttributeFeatureMapWithCompletion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (void)subscribeAttributeFeatureMapWithMinInterval:(NSNumber * _Nonnull)minInterval maxInterval:(NSNumber * _Nonnull)maxInterval
                                             params:(ZGMTRSubscribeParams * _Nullable)params
                            subscriptionEstablished:(ZGMTRSubscriptionEstablishedHandler _Nullable)subscriptionEstablishedHandler
                                      reportHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))reportHandler ZGMTR_DEPRECATED("Please use subscribeAttributeFeatureMapWithParams:subscriptionEstablished:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
+ (void)readAttributeFeatureMapWithAttributeCache:(ZGMTRAttributeCacheContainer *)attributeCacheContainer endpoint:(NSNumber *)endpoint queue:(dispatch_queue_t)queue completionHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completionHandler ZGMTR_DEPRECATED("Please use readAttributeFeatureMapWithAttributeCache:endpoint:queue:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));

- (void)readAttributeClusterRevisionWithCompletionHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completionHandler ZGMTR_DEPRECATED("Please use readAttributeClusterRevisionWithCompletion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (void)subscribeAttributeClusterRevisionWithMinInterval:(NSNumber * _Nonnull)minInterval maxInterval:(NSNumber * _Nonnull)maxInterval
                                                  params:(ZGMTRSubscribeParams * _Nullable)params
                                 subscriptionEstablished:(ZGMTRSubscriptionEstablishedHandler _Nullable)subscriptionEstablishedHandler
                                           reportHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))reportHandler ZGMTR_DEPRECATED("Please use subscribeAttributeClusterRevisionWithParams:subscriptionEstablished:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
+ (void)readAttributeClusterRevisionWithAttributeCache:(ZGMTRAttributeCacheContainer *)attributeCacheContainer endpoint:(NSNumber *)endpoint queue:(dispatch_queue_t)queue completionHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completionHandler ZGMTR_DEPRECATED("Please use readAttributeClusterRevisionWithAttributeCache:endpoint:queue:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));

@end

/**
 * Cluster Binary Input (Basic)
 *    An interface for reading the value of a binary measurement and accessing various characteristics of that measurement.
 */
ZGMTR_DEPRECATED("BinaryInputBasic is deprecated and will be removed", ios(16.1, 18.2), macos(13.0, 15.2), watchos(9.1, 11.2), tvos(16.1, 18.2))
@interface ZGMTRClusterBinaryInputBasic : ZGMTRGenericCluster

- (NSDictionary<NSString *, id> * _Nullable)readAttributeActiveTextWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.1, 18.2), macos(13.0, 15.2), watchos(9.1, 11.2), tvos(16.1, 18.2));
- (void)writeAttributeActiveTextWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.1, 18.2), macos(13.0, 15.2), watchos(9.1, 11.2), tvos(16.1, 18.2));
- (void)writeAttributeActiveTextWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs params:(ZGMTRWriteParams * _Nullable)params ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.1, 18.2), macos(13.0, 15.2), watchos(9.1, 11.2), tvos(16.1, 18.2));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeDescriptionWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.1, 18.2), macos(13.0, 15.2), watchos(9.1, 11.2), tvos(16.1, 18.2));
- (void)writeAttributeDescriptionWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.1, 18.2), macos(13.0, 15.2), watchos(9.1, 11.2), tvos(16.1, 18.2));
- (void)writeAttributeDescriptionWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs params:(ZGMTRWriteParams * _Nullable)params ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.1, 18.2), macos(13.0, 15.2), watchos(9.1, 11.2), tvos(16.1, 18.2));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeInactiveTextWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.1, 18.2), macos(13.0, 15.2), watchos(9.1, 11.2), tvos(16.1, 18.2));
- (void)writeAttributeInactiveTextWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.1, 18.2), macos(13.0, 15.2), watchos(9.1, 11.2), tvos(16.1, 18.2));
- (void)writeAttributeInactiveTextWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs params:(ZGMTRWriteParams * _Nullable)params ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.1, 18.2), macos(13.0, 15.2), watchos(9.1, 11.2), tvos(16.1, 18.2));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeOutOfServiceWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.1, 18.2), macos(13.0, 15.2), watchos(9.1, 11.2), tvos(16.1, 18.2));
- (void)writeAttributeOutOfServiceWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.1, 18.2), macos(13.0, 15.2), watchos(9.1, 11.2), tvos(16.1, 18.2));
- (void)writeAttributeOutOfServiceWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs params:(ZGMTRWriteParams * _Nullable)params ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.1, 18.2), macos(13.0, 15.2), watchos(9.1, 11.2), tvos(16.1, 18.2));

- (NSDictionary<NSString *, id> * _Nullable)readAttributePolarityWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.1, 18.2), macos(13.0, 15.2), watchos(9.1, 11.2), tvos(16.1, 18.2));

- (NSDictionary<NSString *, id> * _Nullable)readAttributePresentValueWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.1, 18.2), macos(13.0, 15.2), watchos(9.1, 11.2), tvos(16.1, 18.2));
- (void)writeAttributePresentValueWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.1, 18.2), macos(13.0, 15.2), watchos(9.1, 11.2), tvos(16.1, 18.2));
- (void)writeAttributePresentValueWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs params:(ZGMTRWriteParams * _Nullable)params ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.1, 18.2), macos(13.0, 15.2), watchos(9.1, 11.2), tvos(16.1, 18.2));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeReliabilityWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.1, 18.2), macos(13.0, 15.2), watchos(9.1, 11.2), tvos(16.1, 18.2));
- (void)writeAttributeReliabilityWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.1, 18.2), macos(13.0, 15.2), watchos(9.1, 11.2), tvos(16.1, 18.2));
- (void)writeAttributeReliabilityWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs params:(ZGMTRWriteParams * _Nullable)params ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.1, 18.2), macos(13.0, 15.2), watchos(9.1, 11.2), tvos(16.1, 18.2));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeStatusFlagsWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.1, 18.2), macos(13.0, 15.2), watchos(9.1, 11.2), tvos(16.1, 18.2));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeApplicationTypeWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.1, 18.2), macos(13.0, 15.2), watchos(9.1, 11.2), tvos(16.1, 18.2));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeGeneratedCommandListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.1, 18.2), macos(13.0, 15.2), watchos(9.1, 11.2), tvos(16.1, 18.2));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeAcceptedCommandListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.1, 18.2), macos(13.0, 15.2), watchos(9.1, 11.2), tvos(16.1, 18.2));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeAttributeListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.1, 18.2), macos(13.0, 15.2), watchos(9.1, 11.2), tvos(16.1, 18.2));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeFeatureMapWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.1, 18.2), macos(13.0, 15.2), watchos(9.1, 11.2), tvos(16.1, 18.2));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeClusterRevisionWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.1, 18.2), macos(13.0, 15.2), watchos(9.1, 11.2), tvos(16.1, 18.2));

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end

@interface ZGMTRClusterBinaryInputBasic (Availability)

/**
 * The queue is currently unused, but may be used in the future for calling completions
 * for command invocations if commands are added to this cluster.
 */
- (instancetype _Nullable)initWithDevice:(ZGMTRDevice *)device
                              endpointID:(NSNumber *)endpointID
                                   queue:(dispatch_queue_t)queue ZGMTR_DEPRECATED("BinaryInputBasic is deprecated and will be removed", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));

@end

@interface ZGMTRClusterBinaryInputBasic (Deprecated)

- (nullable instancetype)initWithDevice:(ZGMTRDevice *)device
                               endpoint:(uint16_t)endpoint
                                  queue:(dispatch_queue_t)queue ZGMTR_DEPRECATED("Please use initWithDevice:endpoindID:queue:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));

@end

#pragma mark - Clusters that were removed wholesale: BarrierControl

ZGMTR_DEPRECATED("This command has been removed", ios(16.1, 18.2), macos(13.0, 15.2), watchos(9.1, 11.2), tvos(16.1, 18.2))
@interface ZGMTRBarrierControlClusterBarrierControlGoToPercentParams : NSObject <NSCopying>

@property (nonatomic, copy) NSNumber * _Nonnull percentOpen ZGMTR_DEPRECATED("The percentOpen field will be removed", ios(16.1, 18.2), macos(13.0, 15.2), watchos(9.1, 11.2), tvos(16.1, 18.2));
/**
 * Controls whether the command is a timed command (using Timed Invoke).
 *
 * If nil (the default value), a regular invoke is done for commands that do
 * not require a timed invoke and a timed invoke with some default timed request
 * timeout is done for commands that require a timed invoke.
 *
 * If not nil, a timed invoke is done, with the provided value used as the timed
 * request timeout.  The value should be chosen small enough to provide the
 * desired security properties but large enough that it will allow a round-trip
 * from the sever to the client (for the status response and actual invoke
 * request) within the timeout window.
 *
 */
@property (nonatomic, copy, nullable) NSNumber * timedInvokeTimeoutMs;

/**
 * Controls how much time, in seconds, we will allow for the server to process the command.
 *
 * The command will then time out if that much time, plus an allowance for retransmits due to network failures, passes.
 *
 * If nil, the framework will try to select an appropriate timeout value itself.
 */
@property (nonatomic, copy, nullable) NSNumber * serverSideProcessingTimeout;
@end

ZGMTR_DEPRECATED("This command has been removed", ios(16.1, 18.2), macos(13.0, 15.2), watchos(9.1, 11.2), tvos(16.1, 18.2))
@interface ZGMTRBarrierControlClusterBarrierControlStopParams : NSObject <NSCopying>
/**
 * Controls whether the command is a timed command (using Timed Invoke).
 *
 * If nil (the default value), a regular invoke is done for commands that do
 * not require a timed invoke and a timed invoke with some default timed request
 * timeout is done for commands that require a timed invoke.
 *
 * If not nil, a timed invoke is done, with the provided value used as the timed
 * request timeout.  The value should be chosen small enough to provide the
 * desired security properties but large enough that it will allow a round-trip
 * from the sever to the client (for the status response and actual invoke
 * request) within the timeout window.
 *
 */
@property (nonatomic, copy, nullable) NSNumber * timedInvokeTimeoutMs;

/**
 * Controls how much time, in seconds, we will allow for the server to process the command.
 *
 * The command will then time out if that much time, plus an allowance for retransmits due to network failures, passes.
 *
 * If nil, the framework will try to select an appropriate timeout value itself.
 */
@property (nonatomic, copy, nullable) NSNumber * serverSideProcessingTimeout;
@end

/**
 * Cluster Barrier Control
 *
 * This cluster provides control of a barrier (garage door).
 */
ZGMTR_DEPRECATED("BarrierControl is deprecated and will be removed", ios(16.1, 18.2), macos(13.0, 15.2), watchos(9.1, 11.2), tvos(16.1, 18.2))
@interface ZGMTRBaseClusterBarrierControl : ZGMTRGenericBaseCluster

/**
 * Command BarrierControlGoToPercent
 *
 * Command to instruct a barrier to go to a percent open state.
 */
- (void)barrierControlGoToPercentWithParams:(ZGMTRBarrierControlClusterBarrierControlGoToPercentParams *)params completion:(ZGMTRStatusCompletion)completion ZGMTR_DEPRECATED("This command is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));
/**
 * Command BarrierControlStop
 *
 * Command that instructs the barrier to stop moving.
 */
- (void)barrierControlStopWithParams:(ZGMTRBarrierControlClusterBarrierControlStopParams * _Nullable)params completion:(ZGMTRStatusCompletion)completion ZGMTR_DEPRECATED("This command is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));
- (void)barrierControlStopWithCompletion:(ZGMTRStatusCompletion)completion
    ZGMTR_DEPRECATED("This command is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));

- (void)readAttributeBarrierMovingStateWithCompletion:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completion ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));
- (void)subscribeAttributeBarrierMovingStateWithParams:(ZGMTRSubscribeParams *)params
                               subscriptionEstablished:(ZGMTRSubscriptionEstablishedHandler _Nullable)subscriptionEstablished
                                         reportHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))reportHandler ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));
+ (void)readAttributeBarrierMovingStateWithClusterStateCache:(ZGMTRClusterStateCacheContainer *)clusterStateCacheContainer endpoint:(NSNumber *)endpoint queue:(dispatch_queue_t)queue completion:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completion ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));

- (void)readAttributeBarrierSafetyStatusWithCompletion:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completion ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));
- (void)subscribeAttributeBarrierSafetyStatusWithParams:(ZGMTRSubscribeParams *)params
                                subscriptionEstablished:(ZGMTRSubscriptionEstablishedHandler _Nullable)subscriptionEstablished
                                          reportHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))reportHandler ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));
+ (void)readAttributeBarrierSafetyStatusWithClusterStateCache:(ZGMTRClusterStateCacheContainer *)clusterStateCacheContainer endpoint:(NSNumber *)endpoint queue:(dispatch_queue_t)queue completion:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completion ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));

- (void)readAttributeBarrierCapabilitiesWithCompletion:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completion ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));
- (void)subscribeAttributeBarrierCapabilitiesWithParams:(ZGMTRSubscribeParams *)params
                                subscriptionEstablished:(ZGMTRSubscriptionEstablishedHandler _Nullable)subscriptionEstablished
                                          reportHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))reportHandler ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));
+ (void)readAttributeBarrierCapabilitiesWithClusterStateCache:(ZGMTRClusterStateCacheContainer *)clusterStateCacheContainer endpoint:(NSNumber *)endpoint queue:(dispatch_queue_t)queue completion:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completion ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));

- (void)readAttributeBarrierOpenEventsWithCompletion:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completion ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));
- (void)writeAttributeBarrierOpenEventsWithValue:(NSNumber * _Nonnull)value completion:(ZGMTRStatusCompletion)completion ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));
- (void)writeAttributeBarrierOpenEventsWithValue:(NSNumber * _Nonnull)value params:(ZGMTRWriteParams * _Nullable)params completion:(ZGMTRStatusCompletion)completion ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));
- (void)subscribeAttributeBarrierOpenEventsWithParams:(ZGMTRSubscribeParams *)params
                              subscriptionEstablished:(ZGMTRSubscriptionEstablishedHandler _Nullable)subscriptionEstablished
                                        reportHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))reportHandler ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));
+ (void)readAttributeBarrierOpenEventsWithClusterStateCache:(ZGMTRClusterStateCacheContainer *)clusterStateCacheContainer endpoint:(NSNumber *)endpoint queue:(dispatch_queue_t)queue completion:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completion ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));

- (void)readAttributeBarrierCloseEventsWithCompletion:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completion ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));
- (void)writeAttributeBarrierCloseEventsWithValue:(NSNumber * _Nonnull)value completion:(ZGMTRStatusCompletion)completion ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));
- (void)writeAttributeBarrierCloseEventsWithValue:(NSNumber * _Nonnull)value params:(ZGMTRWriteParams * _Nullable)params completion:(ZGMTRStatusCompletion)completion ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));
- (void)subscribeAttributeBarrierCloseEventsWithParams:(ZGMTRSubscribeParams *)params
                               subscriptionEstablished:(ZGMTRSubscriptionEstablishedHandler _Nullable)subscriptionEstablished
                                         reportHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))reportHandler ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));
+ (void)readAttributeBarrierCloseEventsWithClusterStateCache:(ZGMTRClusterStateCacheContainer *)clusterStateCacheContainer endpoint:(NSNumber *)endpoint queue:(dispatch_queue_t)queue completion:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completion ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));

- (void)readAttributeBarrierCommandOpenEventsWithCompletion:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completion ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));
- (void)writeAttributeBarrierCommandOpenEventsWithValue:(NSNumber * _Nonnull)value completion:(ZGMTRStatusCompletion)completion ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));
- (void)writeAttributeBarrierCommandOpenEventsWithValue:(NSNumber * _Nonnull)value params:(ZGMTRWriteParams * _Nullable)params completion:(ZGMTRStatusCompletion)completion ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));
- (void)subscribeAttributeBarrierCommandOpenEventsWithParams:(ZGMTRSubscribeParams *)params
                                     subscriptionEstablished:(ZGMTRSubscriptionEstablishedHandler _Nullable)subscriptionEstablished
                                               reportHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))reportHandler ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));
+ (void)readAttributeBarrierCommandOpenEventsWithClusterStateCache:(ZGMTRClusterStateCacheContainer *)clusterStateCacheContainer endpoint:(NSNumber *)endpoint queue:(dispatch_queue_t)queue completion:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completion ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));

- (void)readAttributeBarrierCommandCloseEventsWithCompletion:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completion ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));
- (void)writeAttributeBarrierCommandCloseEventsWithValue:(NSNumber * _Nonnull)value completion:(ZGMTRStatusCompletion)completion ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));
- (void)writeAttributeBarrierCommandCloseEventsWithValue:(NSNumber * _Nonnull)value params:(ZGMTRWriteParams * _Nullable)params completion:(ZGMTRStatusCompletion)completion ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));
- (void)subscribeAttributeBarrierCommandCloseEventsWithParams:(ZGMTRSubscribeParams *)params
                                      subscriptionEstablished:(ZGMTRSubscriptionEstablishedHandler _Nullable)subscriptionEstablished
                                                reportHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))reportHandler ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));
+ (void)readAttributeBarrierCommandCloseEventsWithClusterStateCache:(ZGMTRClusterStateCacheContainer *)clusterStateCacheContainer endpoint:(NSNumber *)endpoint queue:(dispatch_queue_t)queue completion:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completion ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));

- (void)readAttributeBarrierOpenPeriodWithCompletion:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completion ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));
- (void)writeAttributeBarrierOpenPeriodWithValue:(NSNumber * _Nonnull)value completion:(ZGMTRStatusCompletion)completion ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));
- (void)writeAttributeBarrierOpenPeriodWithValue:(NSNumber * _Nonnull)value params:(ZGMTRWriteParams * _Nullable)params completion:(ZGMTRStatusCompletion)completion ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));
- (void)subscribeAttributeBarrierOpenPeriodWithParams:(ZGMTRSubscribeParams *)params
                              subscriptionEstablished:(ZGMTRSubscriptionEstablishedHandler _Nullable)subscriptionEstablished
                                        reportHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))reportHandler ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));
+ (void)readAttributeBarrierOpenPeriodWithClusterStateCache:(ZGMTRClusterStateCacheContainer *)clusterStateCacheContainer endpoint:(NSNumber *)endpoint queue:(dispatch_queue_t)queue completion:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completion ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));

- (void)readAttributeBarrierClosePeriodWithCompletion:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completion ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));
- (void)writeAttributeBarrierClosePeriodWithValue:(NSNumber * _Nonnull)value completion:(ZGMTRStatusCompletion)completion ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));
- (void)writeAttributeBarrierClosePeriodWithValue:(NSNumber * _Nonnull)value params:(ZGMTRWriteParams * _Nullable)params completion:(ZGMTRStatusCompletion)completion ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));
- (void)subscribeAttributeBarrierClosePeriodWithParams:(ZGMTRSubscribeParams *)params
                               subscriptionEstablished:(ZGMTRSubscriptionEstablishedHandler _Nullable)subscriptionEstablished
                                         reportHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))reportHandler ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));
+ (void)readAttributeBarrierClosePeriodWithClusterStateCache:(ZGMTRClusterStateCacheContainer *)clusterStateCacheContainer endpoint:(NSNumber *)endpoint queue:(dispatch_queue_t)queue completion:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completion ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));

- (void)readAttributeBarrierPositionWithCompletion:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completion ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));
- (void)subscribeAttributeBarrierPositionWithParams:(ZGMTRSubscribeParams *)params
                            subscriptionEstablished:(ZGMTRSubscriptionEstablishedHandler _Nullable)subscriptionEstablished
                                      reportHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))reportHandler ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));
+ (void)readAttributeBarrierPositionWithClusterStateCache:(ZGMTRClusterStateCacheContainer *)clusterStateCacheContainer endpoint:(NSNumber *)endpoint queue:(dispatch_queue_t)queue completion:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completion ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));

- (void)readAttributeGeneratedCommandListWithCompletion:(void (^)(NSArray * _Nullable value, NSError * _Nullable error))completion ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));
- (void)subscribeAttributeGeneratedCommandListWithParams:(ZGMTRSubscribeParams *)params
                                 subscriptionEstablished:(ZGMTRSubscriptionEstablishedHandler _Nullable)subscriptionEstablished
                                           reportHandler:(void (^)(NSArray * _Nullable value, NSError * _Nullable error))reportHandler ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));
+ (void)readAttributeGeneratedCommandListWithClusterStateCache:(ZGMTRClusterStateCacheContainer *)clusterStateCacheContainer endpoint:(NSNumber *)endpoint queue:(dispatch_queue_t)queue completion:(void (^)(NSArray * _Nullable value, NSError * _Nullable error))completion ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));

- (void)readAttributeAcceptedCommandListWithCompletion:(void (^)(NSArray * _Nullable value, NSError * _Nullable error))completion ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));
- (void)subscribeAttributeAcceptedCommandListWithParams:(ZGMTRSubscribeParams *)params
                                subscriptionEstablished:(ZGMTRSubscriptionEstablishedHandler _Nullable)subscriptionEstablished
                                          reportHandler:(void (^)(NSArray * _Nullable value, NSError * _Nullable error))reportHandler ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));
+ (void)readAttributeAcceptedCommandListWithClusterStateCache:(ZGMTRClusterStateCacheContainer *)clusterStateCacheContainer endpoint:(NSNumber *)endpoint queue:(dispatch_queue_t)queue completion:(void (^)(NSArray * _Nullable value, NSError * _Nullable error))completion ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));

- (void)readAttributeAttributeListWithCompletion:(void (^)(NSArray * _Nullable value, NSError * _Nullable error))completion ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));
- (void)subscribeAttributeAttributeListWithParams:(ZGMTRSubscribeParams *)params
                          subscriptionEstablished:(ZGMTRSubscriptionEstablishedHandler _Nullable)subscriptionEstablished
                                    reportHandler:(void (^)(NSArray * _Nullable value, NSError * _Nullable error))reportHandler ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));
+ (void)readAttributeAttributeListWithClusterStateCache:(ZGMTRClusterStateCacheContainer *)clusterStateCacheContainer endpoint:(NSNumber *)endpoint queue:(dispatch_queue_t)queue completion:(void (^)(NSArray * _Nullable value, NSError * _Nullable error))completion ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));

- (void)readAttributeFeatureMapWithCompletion:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completion ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));
- (void)subscribeAttributeFeatureMapWithParams:(ZGMTRSubscribeParams *)params
                       subscriptionEstablished:(ZGMTRSubscriptionEstablishedHandler _Nullable)subscriptionEstablished
                                 reportHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))reportHandler ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));
+ (void)readAttributeFeatureMapWithClusterStateCache:(ZGMTRClusterStateCacheContainer *)clusterStateCacheContainer endpoint:(NSNumber *)endpoint queue:(dispatch_queue_t)queue completion:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completion ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));

- (void)readAttributeClusterRevisionWithCompletion:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completion ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));
- (void)subscribeAttributeClusterRevisionWithParams:(ZGMTRSubscribeParams *)params
                            subscriptionEstablished:(ZGMTRSubscriptionEstablishedHandler _Nullable)subscriptionEstablished
                                      reportHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))reportHandler ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));
+ (void)readAttributeClusterRevisionWithClusterStateCache:(ZGMTRClusterStateCacheContainer *)clusterStateCacheContainer endpoint:(NSNumber *)endpoint queue:(dispatch_queue_t)queue completion:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completion ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end

@interface ZGMTRBaseClusterBarrierControl (Availability)

/**
 * For all instance methods (reads, writes, commands) that take a completion,
 * the completion will be called on the provided queue.
 */
- (instancetype _Nullable)initWithDevice:(ZGMTRBaseDevice *)device
                              endpointID:(NSNumber *)endpointID
                                   queue:(dispatch_queue_t)queue ZGMTR_DEPRECATED("BarrierControl is deprecated and will be removed", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));

@end

@interface ZGMTRBaseClusterBarrierControl (Deprecated)

- (nullable instancetype)initWithDevice:(ZGMTRBaseDevice *)device
                               endpoint:(uint16_t)endpoint
                                  queue:(dispatch_queue_t)queue ZGMTR_DEPRECATED("Please use initWithDevice:endpointID:queue:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));

- (void)barrierControlGoToPercentWithParams:(ZGMTRBarrierControlClusterBarrierControlGoToPercentParams *)params completionHandler:(ZGMTRStatusCompletion)completionHandler
    ZGMTR_DEPRECATED("Please use barrierControlGoToPercentWithParams:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (void)barrierControlStopWithParams:(ZGMTRBarrierControlClusterBarrierControlStopParams * _Nullable)params completionHandler:(ZGMTRStatusCompletion)completionHandler
    ZGMTR_DEPRECATED("Please use barrierControlStopWithParams:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (void)barrierControlStopWithCompletionHandler:(ZGMTRStatusCompletion)completionHandler
    ZGMTR_DEPRECATED("Please use barrierControlStopWithCompletion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));

- (void)readAttributeBarrierMovingStateWithCompletionHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completionHandler ZGMTR_DEPRECATED("Please use readAttributeBarrierMovingStateWithCompletion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (void)subscribeAttributeBarrierMovingStateWithMinInterval:(NSNumber * _Nonnull)minInterval maxInterval:(NSNumber * _Nonnull)maxInterval
                                                     params:(ZGMTRSubscribeParams * _Nullable)params
                                    subscriptionEstablished:(ZGMTRSubscriptionEstablishedHandler _Nullable)subscriptionEstablishedHandler
                                              reportHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))reportHandler ZGMTR_DEPRECATED("Please use subscribeAttributeBarrierMovingStateWithParams:subscriptionEstablished:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
+ (void)readAttributeBarrierMovingStateWithAttributeCache:(ZGMTRAttributeCacheContainer *)attributeCacheContainer endpoint:(NSNumber *)endpoint queue:(dispatch_queue_t)queue completionHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completionHandler ZGMTR_DEPRECATED("Please use readAttributeBarrierMovingStateWithAttributeCache:endpoint:queue:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));

- (void)readAttributeBarrierSafetyStatusWithCompletionHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completionHandler ZGMTR_DEPRECATED("Please use readAttributeBarrierSafetyStatusWithCompletion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (void)subscribeAttributeBarrierSafetyStatusWithMinInterval:(NSNumber * _Nonnull)minInterval maxInterval:(NSNumber * _Nonnull)maxInterval
                                                      params:(ZGMTRSubscribeParams * _Nullable)params
                                     subscriptionEstablished:(ZGMTRSubscriptionEstablishedHandler _Nullable)subscriptionEstablishedHandler
                                               reportHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))reportHandler ZGMTR_DEPRECATED("Please use subscribeAttributeBarrierSafetyStatusWithParams:subscriptionEstablished:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
+ (void)readAttributeBarrierSafetyStatusWithAttributeCache:(ZGMTRAttributeCacheContainer *)attributeCacheContainer endpoint:(NSNumber *)endpoint queue:(dispatch_queue_t)queue completionHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completionHandler ZGMTR_DEPRECATED("Please use readAttributeBarrierSafetyStatusWithAttributeCache:endpoint:queue:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));

- (void)readAttributeBarrierCapabilitiesWithCompletionHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completionHandler ZGMTR_DEPRECATED("Please use readAttributeBarrierCapabilitiesWithCompletion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (void)subscribeAttributeBarrierCapabilitiesWithMinInterval:(NSNumber * _Nonnull)minInterval maxInterval:(NSNumber * _Nonnull)maxInterval
                                                      params:(ZGMTRSubscribeParams * _Nullable)params
                                     subscriptionEstablished:(ZGMTRSubscriptionEstablishedHandler _Nullable)subscriptionEstablishedHandler
                                               reportHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))reportHandler ZGMTR_DEPRECATED("Please use subscribeAttributeBarrierCapabilitiesWithParams:subscriptionEstablished:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
+ (void)readAttributeBarrierCapabilitiesWithAttributeCache:(ZGMTRAttributeCacheContainer *)attributeCacheContainer endpoint:(NSNumber *)endpoint queue:(dispatch_queue_t)queue completionHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completionHandler ZGMTR_DEPRECATED("Please use readAttributeBarrierCapabilitiesWithAttributeCache:endpoint:queue:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));

- (void)readAttributeBarrierOpenEventsWithCompletionHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completionHandler ZGMTR_DEPRECATED("Please use readAttributeBarrierOpenEventsWithCompletion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (void)writeAttributeBarrierOpenEventsWithValue:(NSNumber * _Nonnull)value completionHandler:(ZGMTRStatusCompletion)completionHandler ZGMTR_DEPRECATED("Please use writeAttributeBarrierOpenEventsWithValue:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (void)writeAttributeBarrierOpenEventsWithValue:(NSNumber * _Nonnull)value params:(ZGMTRWriteParams * _Nullable)params completionHandler:(ZGMTRStatusCompletion)completionHandler ZGMTR_DEPRECATED("Please use writeAttributeBarrierOpenEventsWithValue:params:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (void)subscribeAttributeBarrierOpenEventsWithMinInterval:(NSNumber * _Nonnull)minInterval maxInterval:(NSNumber * _Nonnull)maxInterval
                                                    params:(ZGMTRSubscribeParams * _Nullable)params
                                   subscriptionEstablished:(ZGMTRSubscriptionEstablishedHandler _Nullable)subscriptionEstablishedHandler
                                             reportHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))reportHandler ZGMTR_DEPRECATED("Please use subscribeAttributeBarrierOpenEventsWithParams:subscriptionEstablished:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
+ (void)readAttributeBarrierOpenEventsWithAttributeCache:(ZGMTRAttributeCacheContainer *)attributeCacheContainer endpoint:(NSNumber *)endpoint queue:(dispatch_queue_t)queue completionHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completionHandler ZGMTR_DEPRECATED("Please use readAttributeBarrierOpenEventsWithAttributeCache:endpoint:queue:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));

- (void)readAttributeBarrierCloseEventsWithCompletionHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completionHandler ZGMTR_DEPRECATED("Please use readAttributeBarrierCloseEventsWithCompletion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (void)writeAttributeBarrierCloseEventsWithValue:(NSNumber * _Nonnull)value completionHandler:(ZGMTRStatusCompletion)completionHandler ZGMTR_DEPRECATED("Please use writeAttributeBarrierCloseEventsWithValue:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (void)writeAttributeBarrierCloseEventsWithValue:(NSNumber * _Nonnull)value params:(ZGMTRWriteParams * _Nullable)params completionHandler:(ZGMTRStatusCompletion)completionHandler ZGMTR_DEPRECATED("Please use writeAttributeBarrierCloseEventsWithValue:params:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (void)subscribeAttributeBarrierCloseEventsWithMinInterval:(NSNumber * _Nonnull)minInterval maxInterval:(NSNumber * _Nonnull)maxInterval
                                                     params:(ZGMTRSubscribeParams * _Nullable)params
                                    subscriptionEstablished:(ZGMTRSubscriptionEstablishedHandler _Nullable)subscriptionEstablishedHandler
                                              reportHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))reportHandler ZGMTR_DEPRECATED("Please use subscribeAttributeBarrierCloseEventsWithParams:subscriptionEstablished:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
+ (void)readAttributeBarrierCloseEventsWithAttributeCache:(ZGMTRAttributeCacheContainer *)attributeCacheContainer endpoint:(NSNumber *)endpoint queue:(dispatch_queue_t)queue completionHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completionHandler ZGMTR_DEPRECATED("Please use readAttributeBarrierCloseEventsWithAttributeCache:endpoint:queue:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));

- (void)readAttributeBarrierCommandOpenEventsWithCompletionHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completionHandler ZGMTR_DEPRECATED("Please use readAttributeBarrierCommandOpenEventsWithCompletion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (void)writeAttributeBarrierCommandOpenEventsWithValue:(NSNumber * _Nonnull)value completionHandler:(ZGMTRStatusCompletion)completionHandler ZGMTR_DEPRECATED("Please use writeAttributeBarrierCommandOpenEventsWithValue:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (void)writeAttributeBarrierCommandOpenEventsWithValue:(NSNumber * _Nonnull)value params:(ZGMTRWriteParams * _Nullable)params completionHandler:(ZGMTRStatusCompletion)completionHandler ZGMTR_DEPRECATED("Please use writeAttributeBarrierCommandOpenEventsWithValue:params:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (void)subscribeAttributeBarrierCommandOpenEventsWithMinInterval:(NSNumber * _Nonnull)minInterval maxInterval:(NSNumber * _Nonnull)maxInterval
                                                           params:(ZGMTRSubscribeParams * _Nullable)params
                                          subscriptionEstablished:(ZGMTRSubscriptionEstablishedHandler _Nullable)subscriptionEstablishedHandler
                                                    reportHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))reportHandler ZGMTR_DEPRECATED("Please use subscribeAttributeBarrierCommandOpenEventsWithParams:subscriptionEstablished:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
+ (void)readAttributeBarrierCommandOpenEventsWithAttributeCache:(ZGMTRAttributeCacheContainer *)attributeCacheContainer endpoint:(NSNumber *)endpoint queue:(dispatch_queue_t)queue completionHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completionHandler ZGMTR_DEPRECATED("Please use readAttributeBarrierCommandOpenEventsWithAttributeCache:endpoint:queue:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));

- (void)readAttributeBarrierCommandCloseEventsWithCompletionHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completionHandler ZGMTR_DEPRECATED("Please use readAttributeBarrierCommandCloseEventsWithCompletion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (void)writeAttributeBarrierCommandCloseEventsWithValue:(NSNumber * _Nonnull)value completionHandler:(ZGMTRStatusCompletion)completionHandler ZGMTR_DEPRECATED("Please use writeAttributeBarrierCommandCloseEventsWithValue:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (void)writeAttributeBarrierCommandCloseEventsWithValue:(NSNumber * _Nonnull)value params:(ZGMTRWriteParams * _Nullable)params completionHandler:(ZGMTRStatusCompletion)completionHandler ZGMTR_DEPRECATED("Please use writeAttributeBarrierCommandCloseEventsWithValue:params:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (void)subscribeAttributeBarrierCommandCloseEventsWithMinInterval:(NSNumber * _Nonnull)minInterval maxInterval:(NSNumber * _Nonnull)maxInterval
                                                            params:(ZGMTRSubscribeParams * _Nullable)params
                                           subscriptionEstablished:(ZGMTRSubscriptionEstablishedHandler _Nullable)subscriptionEstablishedHandler
                                                     reportHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))reportHandler ZGMTR_DEPRECATED("Please use subscribeAttributeBarrierCommandCloseEventsWithParams:subscriptionEstablished:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
+ (void)readAttributeBarrierCommandCloseEventsWithAttributeCache:(ZGMTRAttributeCacheContainer *)attributeCacheContainer endpoint:(NSNumber *)endpoint queue:(dispatch_queue_t)queue completionHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completionHandler ZGMTR_DEPRECATED("Please use readAttributeBarrierCommandCloseEventsWithAttributeCache:endpoint:queue:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));

- (void)readAttributeBarrierOpenPeriodWithCompletionHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completionHandler ZGMTR_DEPRECATED("Please use readAttributeBarrierOpenPeriodWithCompletion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (void)writeAttributeBarrierOpenPeriodWithValue:(NSNumber * _Nonnull)value completionHandler:(ZGMTRStatusCompletion)completionHandler ZGMTR_DEPRECATED("Please use writeAttributeBarrierOpenPeriodWithValue:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (void)writeAttributeBarrierOpenPeriodWithValue:(NSNumber * _Nonnull)value params:(ZGMTRWriteParams * _Nullable)params completionHandler:(ZGMTRStatusCompletion)completionHandler ZGMTR_DEPRECATED("Please use writeAttributeBarrierOpenPeriodWithValue:params:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (void)subscribeAttributeBarrierOpenPeriodWithMinInterval:(NSNumber * _Nonnull)minInterval maxInterval:(NSNumber * _Nonnull)maxInterval
                                                    params:(ZGMTRSubscribeParams * _Nullable)params
                                   subscriptionEstablished:(ZGMTRSubscriptionEstablishedHandler _Nullable)subscriptionEstablishedHandler
                                             reportHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))reportHandler ZGMTR_DEPRECATED("Please use subscribeAttributeBarrierOpenPeriodWithParams:subscriptionEstablished:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
+ (void)readAttributeBarrierOpenPeriodWithAttributeCache:(ZGMTRAttributeCacheContainer *)attributeCacheContainer endpoint:(NSNumber *)endpoint queue:(dispatch_queue_t)queue completionHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completionHandler ZGMTR_DEPRECATED("Please use readAttributeBarrierOpenPeriodWithAttributeCache:endpoint:queue:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));

- (void)readAttributeBarrierClosePeriodWithCompletionHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completionHandler ZGMTR_DEPRECATED("Please use readAttributeBarrierClosePeriodWithCompletion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (void)writeAttributeBarrierClosePeriodWithValue:(NSNumber * _Nonnull)value completionHandler:(ZGMTRStatusCompletion)completionHandler ZGMTR_DEPRECATED("Please use writeAttributeBarrierClosePeriodWithValue:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (void)writeAttributeBarrierClosePeriodWithValue:(NSNumber * _Nonnull)value params:(ZGMTRWriteParams * _Nullable)params completionHandler:(ZGMTRStatusCompletion)completionHandler ZGMTR_DEPRECATED("Please use writeAttributeBarrierClosePeriodWithValue:params:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (void)subscribeAttributeBarrierClosePeriodWithMinInterval:(NSNumber * _Nonnull)minInterval maxInterval:(NSNumber * _Nonnull)maxInterval
                                                     params:(ZGMTRSubscribeParams * _Nullable)params
                                    subscriptionEstablished:(ZGMTRSubscriptionEstablishedHandler _Nullable)subscriptionEstablishedHandler
                                              reportHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))reportHandler ZGMTR_DEPRECATED("Please use subscribeAttributeBarrierClosePeriodWithParams:subscriptionEstablished:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
+ (void)readAttributeBarrierClosePeriodWithAttributeCache:(ZGMTRAttributeCacheContainer *)attributeCacheContainer endpoint:(NSNumber *)endpoint queue:(dispatch_queue_t)queue completionHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completionHandler ZGMTR_DEPRECATED("Please use readAttributeBarrierClosePeriodWithAttributeCache:endpoint:queue:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));

- (void)readAttributeBarrierPositionWithCompletionHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completionHandler ZGMTR_DEPRECATED("Please use readAttributeBarrierPositionWithCompletion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (void)subscribeAttributeBarrierPositionWithMinInterval:(NSNumber * _Nonnull)minInterval maxInterval:(NSNumber * _Nonnull)maxInterval
                                                  params:(ZGMTRSubscribeParams * _Nullable)params
                                 subscriptionEstablished:(ZGMTRSubscriptionEstablishedHandler _Nullable)subscriptionEstablishedHandler
                                           reportHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))reportHandler ZGMTR_DEPRECATED("Please use subscribeAttributeBarrierPositionWithParams:subscriptionEstablished:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
+ (void)readAttributeBarrierPositionWithAttributeCache:(ZGMTRAttributeCacheContainer *)attributeCacheContainer endpoint:(NSNumber *)endpoint queue:(dispatch_queue_t)queue completionHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completionHandler ZGMTR_DEPRECATED("Please use readAttributeBarrierPositionWithAttributeCache:endpoint:queue:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));

- (void)readAttributeGeneratedCommandListWithCompletionHandler:(void (^)(NSArray * _Nullable value, NSError * _Nullable error))completionHandler ZGMTR_DEPRECATED("Please use readAttributeGeneratedCommandListWithCompletion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (void)subscribeAttributeGeneratedCommandListWithMinInterval:(NSNumber * _Nonnull)minInterval maxInterval:(NSNumber * _Nonnull)maxInterval
                                                       params:(ZGMTRSubscribeParams * _Nullable)params
                                      subscriptionEstablished:(ZGMTRSubscriptionEstablishedHandler _Nullable)subscriptionEstablishedHandler
                                                reportHandler:(void (^)(NSArray * _Nullable value, NSError * _Nullable error))reportHandler ZGMTR_DEPRECATED("Please use subscribeAttributeGeneratedCommandListWithParams:subscriptionEstablished:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
+ (void)readAttributeGeneratedCommandListWithAttributeCache:(ZGMTRAttributeCacheContainer *)attributeCacheContainer endpoint:(NSNumber *)endpoint queue:(dispatch_queue_t)queue completionHandler:(void (^)(NSArray * _Nullable value, NSError * _Nullable error))completionHandler ZGMTR_DEPRECATED("Please use readAttributeGeneratedCommandListWithAttributeCache:endpoint:queue:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));

- (void)readAttributeAcceptedCommandListWithCompletionHandler:(void (^)(NSArray * _Nullable value, NSError * _Nullable error))completionHandler ZGMTR_DEPRECATED("Please use readAttributeAcceptedCommandListWithCompletion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (void)subscribeAttributeAcceptedCommandListWithMinInterval:(NSNumber * _Nonnull)minInterval maxInterval:(NSNumber * _Nonnull)maxInterval
                                                      params:(ZGMTRSubscribeParams * _Nullable)params
                                     subscriptionEstablished:(ZGMTRSubscriptionEstablishedHandler _Nullable)subscriptionEstablishedHandler
                                               reportHandler:(void (^)(NSArray * _Nullable value, NSError * _Nullable error))reportHandler ZGMTR_DEPRECATED("Please use subscribeAttributeAcceptedCommandListWithParams:subscriptionEstablished:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
+ (void)readAttributeAcceptedCommandListWithAttributeCache:(ZGMTRAttributeCacheContainer *)attributeCacheContainer endpoint:(NSNumber *)endpoint queue:(dispatch_queue_t)queue completionHandler:(void (^)(NSArray * _Nullable value, NSError * _Nullable error))completionHandler ZGMTR_DEPRECATED("Please use readAttributeAcceptedCommandListWithAttributeCache:endpoint:queue:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));

- (void)readAttributeAttributeListWithCompletionHandler:(void (^)(NSArray * _Nullable value, NSError * _Nullable error))completionHandler ZGMTR_DEPRECATED("Please use readAttributeAttributeListWithCompletion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (void)subscribeAttributeAttributeListWithMinInterval:(NSNumber * _Nonnull)minInterval maxInterval:(NSNumber * _Nonnull)maxInterval
                                                params:(ZGMTRSubscribeParams * _Nullable)params
                               subscriptionEstablished:(ZGMTRSubscriptionEstablishedHandler _Nullable)subscriptionEstablishedHandler
                                         reportHandler:(void (^)(NSArray * _Nullable value, NSError * _Nullable error))reportHandler ZGMTR_DEPRECATED("Please use subscribeAttributeAttributeListWithParams:subscriptionEstablished:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
+ (void)readAttributeAttributeListWithAttributeCache:(ZGMTRAttributeCacheContainer *)attributeCacheContainer endpoint:(NSNumber *)endpoint queue:(dispatch_queue_t)queue completionHandler:(void (^)(NSArray * _Nullable value, NSError * _Nullable error))completionHandler ZGMTR_DEPRECATED("Please use readAttributeAttributeListWithAttributeCache:endpoint:queue:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));

- (void)readAttributeFeatureMapWithCompletionHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completionHandler ZGMTR_DEPRECATED("Please use readAttributeFeatureMapWithCompletion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (void)subscribeAttributeFeatureMapWithMinInterval:(NSNumber * _Nonnull)minInterval maxInterval:(NSNumber * _Nonnull)maxInterval
                                             params:(ZGMTRSubscribeParams * _Nullable)params
                            subscriptionEstablished:(ZGMTRSubscriptionEstablishedHandler _Nullable)subscriptionEstablishedHandler
                                      reportHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))reportHandler ZGMTR_DEPRECATED("Please use subscribeAttributeFeatureMapWithParams:subscriptionEstablished:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
+ (void)readAttributeFeatureMapWithAttributeCache:(ZGMTRAttributeCacheContainer *)attributeCacheContainer endpoint:(NSNumber *)endpoint queue:(dispatch_queue_t)queue completionHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completionHandler ZGMTR_DEPRECATED("Please use readAttributeFeatureMapWithAttributeCache:endpoint:queue:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));

- (void)readAttributeClusterRevisionWithCompletionHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completionHandler ZGMTR_DEPRECATED("Please use readAttributeClusterRevisionWithCompletion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (void)subscribeAttributeClusterRevisionWithMinInterval:(NSNumber * _Nonnull)minInterval maxInterval:(NSNumber * _Nonnull)maxInterval
                                                  params:(ZGMTRSubscribeParams * _Nullable)params
                                 subscriptionEstablished:(ZGMTRSubscriptionEstablishedHandler _Nullable)subscriptionEstablishedHandler
                                           reportHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))reportHandler ZGMTR_DEPRECATED("Please use subscribeAttributeClusterRevisionWithParams:subscriptionEstablished:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
+ (void)readAttributeClusterRevisionWithAttributeCache:(ZGMTRAttributeCacheContainer *)attributeCacheContainer endpoint:(NSNumber *)endpoint queue:(dispatch_queue_t)queue completionHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completionHandler ZGMTR_DEPRECATED("Please use readAttributeClusterRevisionWithAttributeCache:endpoint:queue:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));

@end

/**
 * Cluster Barrier Control
 *    This cluster provides control of a barrier (garage door).
 */
ZGMTR_DEPRECATED("BarrierControl is deprecated and will be removed", ios(16.1, 18.2), macos(13.0, 15.2), watchos(9.1, 11.2), tvos(16.1, 18.2))
@interface ZGMTRClusterBarrierControl : ZGMTRGenericCluster

- (void)barrierControlGoToPercentWithParams:(ZGMTRBarrierControlClusterBarrierControlGoToPercentParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(ZGMTRStatusCompletion)completion ZGMTR_DEPRECATED("This command is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));
- (void)barrierControlStopWithParams:(ZGMTRBarrierControlClusterBarrierControlStopParams * _Nullable)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(ZGMTRStatusCompletion)completion ZGMTR_DEPRECATED("This command is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));
- (void)barrierControlStopWithExpectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedValues expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(ZGMTRStatusCompletion)completion
    ZGMTR_DEPRECATED("This command is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeBarrierMovingStateWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.1, 18.2), macos(13.0, 15.2), watchos(9.1, 11.2), tvos(16.1, 18.2));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeBarrierSafetyStatusWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.1, 18.2), macos(13.0, 15.2), watchos(9.1, 11.2), tvos(16.1, 18.2));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeBarrierCapabilitiesWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.1, 18.2), macos(13.0, 15.2), watchos(9.1, 11.2), tvos(16.1, 18.2));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeBarrierOpenEventsWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.1, 18.2), macos(13.0, 15.2), watchos(9.1, 11.2), tvos(16.1, 18.2));
- (void)writeAttributeBarrierOpenEventsWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.1, 18.2), macos(13.0, 15.2), watchos(9.1, 11.2), tvos(16.1, 18.2));
- (void)writeAttributeBarrierOpenEventsWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs params:(ZGMTRWriteParams * _Nullable)params ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.1, 18.2), macos(13.0, 15.2), watchos(9.1, 11.2), tvos(16.1, 18.2));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeBarrierCloseEventsWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.1, 18.2), macos(13.0, 15.2), watchos(9.1, 11.2), tvos(16.1, 18.2));
- (void)writeAttributeBarrierCloseEventsWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.1, 18.2), macos(13.0, 15.2), watchos(9.1, 11.2), tvos(16.1, 18.2));
- (void)writeAttributeBarrierCloseEventsWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs params:(ZGMTRWriteParams * _Nullable)params ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.1, 18.2), macos(13.0, 15.2), watchos(9.1, 11.2), tvos(16.1, 18.2));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeBarrierCommandOpenEventsWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.1, 18.2), macos(13.0, 15.2), watchos(9.1, 11.2), tvos(16.1, 18.2));
- (void)writeAttributeBarrierCommandOpenEventsWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.1, 18.2), macos(13.0, 15.2), watchos(9.1, 11.2), tvos(16.1, 18.2));
- (void)writeAttributeBarrierCommandOpenEventsWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs params:(ZGMTRWriteParams * _Nullable)params ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.1, 18.2), macos(13.0, 15.2), watchos(9.1, 11.2), tvos(16.1, 18.2));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeBarrierCommandCloseEventsWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.1, 18.2), macos(13.0, 15.2), watchos(9.1, 11.2), tvos(16.1, 18.2));
- (void)writeAttributeBarrierCommandCloseEventsWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.1, 18.2), macos(13.0, 15.2), watchos(9.1, 11.2), tvos(16.1, 18.2));
- (void)writeAttributeBarrierCommandCloseEventsWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs params:(ZGMTRWriteParams * _Nullable)params ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.1, 18.2), macos(13.0, 15.2), watchos(9.1, 11.2), tvos(16.1, 18.2));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeBarrierOpenPeriodWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.1, 18.2), macos(13.0, 15.2), watchos(9.1, 11.2), tvos(16.1, 18.2));
- (void)writeAttributeBarrierOpenPeriodWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.1, 18.2), macos(13.0, 15.2), watchos(9.1, 11.2), tvos(16.1, 18.2));
- (void)writeAttributeBarrierOpenPeriodWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs params:(ZGMTRWriteParams * _Nullable)params ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.1, 18.2), macos(13.0, 15.2), watchos(9.1, 11.2), tvos(16.1, 18.2));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeBarrierClosePeriodWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.1, 18.2), macos(13.0, 15.2), watchos(9.1, 11.2), tvos(16.1, 18.2));
- (void)writeAttributeBarrierClosePeriodWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.1, 18.2), macos(13.0, 15.2), watchos(9.1, 11.2), tvos(16.1, 18.2));
- (void)writeAttributeBarrierClosePeriodWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs params:(ZGMTRWriteParams * _Nullable)params ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.1, 18.2), macos(13.0, 15.2), watchos(9.1, 11.2), tvos(16.1, 18.2));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeBarrierPositionWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.1, 18.2), macos(13.0, 15.2), watchos(9.1, 11.2), tvos(16.1, 18.2));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeGeneratedCommandListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.1, 18.2), macos(13.0, 15.2), watchos(9.1, 11.2), tvos(16.1, 18.2));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeAcceptedCommandListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.1, 18.2), macos(13.0, 15.2), watchos(9.1, 11.2), tvos(16.1, 18.2));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeAttributeListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.1, 18.2), macos(13.0, 15.2), watchos(9.1, 11.2), tvos(16.1, 18.2));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeFeatureMapWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.1, 18.2), macos(13.0, 15.2), watchos(9.1, 11.2), tvos(16.1, 18.2));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeClusterRevisionWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.1, 18.2), macos(13.0, 15.2), watchos(9.1, 11.2), tvos(16.1, 18.2));

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end

@interface ZGMTRClusterBarrierControl (Availability)

/**
 * For all instance methods that take a completion (i.e. command invocations),
 * the completion will be called on the provided queue.
 */
- (instancetype _Nullable)initWithDevice:(ZGMTRDevice *)device
                              endpointID:(NSNumber *)endpointID
                                   queue:(dispatch_queue_t)queue ZGMTR_DEPRECATED("BarrierControl is deprecated and will be removed", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));

@end

@interface ZGMTRClusterBarrierControl (Deprecated)

- (nullable instancetype)initWithDevice:(ZGMTRDevice *)device
                               endpoint:(uint16_t)endpoint
                                  queue:(dispatch_queue_t)queue ZGMTR_DEPRECATED("Please use initWithDevice:endpoindID:queue:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));

- (void)barrierControlGoToPercentWithParams:(ZGMTRBarrierControlClusterBarrierControlGoToPercentParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completionHandler:(ZGMTRStatusCompletion)completionHandler ZGMTR_DEPRECATED("Please use barrierControlGoToPercentWithParams:expectedValues:expectedValueInterval:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (void)barrierControlStopWithParams:(ZGMTRBarrierControlClusterBarrierControlStopParams * _Nullable)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completionHandler:(ZGMTRStatusCompletion)completionHandler ZGMTR_DEPRECATED("Please use barrierControlStopWithParams:expectedValues:expectedValueInterval:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (void)barrierControlStopWithExpectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedValues expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completionHandler:(ZGMTRStatusCompletion)completionHandler ZGMTR_DEPRECATED("Please use barrierControlStopWithExpectedValues:expectedValueInterval:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
@end

#pragma mark - Clusters that were removed wholesale: ElectricalMeasurement

ZGMTR_DEPRECATED("This command has been removed", ios(16.1, 18.2), macos(13.0, 15.2), watchos(9.1, 11.2), tvos(16.1, 18.2))
@interface ZGMTRElectricalMeasurementClusterGetProfileInfoResponseCommandParams : NSObject <NSCopying>

@property (nonatomic, copy) NSNumber * _Nonnull profileCount ZGMTR_DEPRECATED("The profileCount field will be removed", ios(16.1, 18.2), macos(13.0, 15.2), watchos(9.1, 11.2), tvos(16.1, 18.2));

@property (nonatomic, copy) NSNumber * _Nonnull profileIntervalPeriod ZGMTR_DEPRECATED("The profileIntervalPeriod field will be removed", ios(16.1, 18.2), macos(13.0, 15.2), watchos(9.1, 11.2), tvos(16.1, 18.2));

@property (nonatomic, copy) NSNumber * _Nonnull maxNumberOfIntervals ZGMTR_DEPRECATED("The maxNumberOfIntervals field will be removed", ios(16.1, 18.2), macos(13.0, 15.2), watchos(9.1, 11.2), tvos(16.1, 18.2));

@property (nonatomic, copy) NSArray * _Nonnull listOfAttributes ZGMTR_DEPRECATED("The listOfAttributes field will be removed", ios(16.1, 18.2), macos(13.0, 15.2), watchos(9.1, 11.2), tvos(16.1, 18.2));
/**
 * Controls whether the command is a timed command (using Timed Invoke).
 *
 * If nil (the default value), a regular invoke is done for commands that do
 * not require a timed invoke and a timed invoke with some default timed request
 * timeout is done for commands that require a timed invoke.
 *
 * If not nil, a timed invoke is done, with the provided value used as the timed
 * request timeout.  The value should be chosen small enough to provide the
 * desired security properties but large enough that it will allow a round-trip
 * from the sever to the client (for the status response and actual invoke
 * request) within the timeout window.
 *
 */
@property (nonatomic, copy, nullable) NSNumber * timedInvokeTimeoutMs ZGMTR_DEPRECATED("Timed invoke does not make sense for server to client commands", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));

/**
 * Initialize an ZGMTRElectricalMeasurementClusterGetProfileInfoResponseCommandParams with a response-value dictionary
 * of the sort that ZGMTRDeviceResponseHandler would receive.
 *
 * Will return nil and hand out an error if the response-value dictionary is not
 * a command data response or is not the right command response.
 *
 * Will return nil and hand out an error if the data response does not match the known
 * schema for this command.
 */
- (nullable instancetype)initWithResponseValue:(NSDictionary<NSString *, id> *)responseValue
                                         error:(NSError * __autoreleasing *)error ZGMTR_DEPRECATED("This command has been removed", ios(17.0, 18.2), macos(14.0, 15.2), watchos(10.0, 11.2), tvos(17.0, 18.2));
@end

ZGMTR_DEPRECATED("This command has been removed", ios(16.1, 18.2), macos(13.0, 15.2), watchos(9.1, 11.2), tvos(16.1, 18.2))
@interface ZGMTRElectricalMeasurementClusterGetProfileInfoCommandParams : NSObject <NSCopying>
/**
 * Controls whether the command is a timed command (using Timed Invoke).
 *
 * If nil (the default value), a regular invoke is done for commands that do
 * not require a timed invoke and a timed invoke with some default timed request
 * timeout is done for commands that require a timed invoke.
 *
 * If not nil, a timed invoke is done, with the provided value used as the timed
 * request timeout.  The value should be chosen small enough to provide the
 * desired security properties but large enough that it will allow a round-trip
 * from the sever to the client (for the status response and actual invoke
 * request) within the timeout window.
 *
 */
@property (nonatomic, copy, nullable) NSNumber * timedInvokeTimeoutMs;

/**
 * Controls how much time, in seconds, we will allow for the server to process the command.
 *
 * The command will then time out if that much time, plus an allowance for retransmits due to network failures, passes.
 *
 * If nil, the framework will try to select an appropriate timeout value itself.
 */
@property (nonatomic, copy, nullable) NSNumber * serverSideProcessingTimeout;
@end

ZGMTR_DEPRECATED("This command has been removed", ios(16.1, 18.2), macos(13.0, 15.2), watchos(9.1, 11.2), tvos(16.1, 18.2))
@interface ZGMTRElectricalMeasurementClusterGetMeasurementProfileResponseCommandParams : NSObject <NSCopying>

@property (nonatomic, copy) NSNumber * _Nonnull startTime ZGMTR_DEPRECATED("The startTime field will be removed", ios(16.1, 18.2), macos(13.0, 15.2), watchos(9.1, 11.2), tvos(16.1, 18.2));

@property (nonatomic, copy) NSNumber * _Nonnull status ZGMTR_DEPRECATED("The status field will be removed", ios(16.1, 18.2), macos(13.0, 15.2), watchos(9.1, 11.2), tvos(16.1, 18.2));

@property (nonatomic, copy) NSNumber * _Nonnull profileIntervalPeriod ZGMTR_DEPRECATED("The profileIntervalPeriod field will be removed", ios(16.1, 18.2), macos(13.0, 15.2), watchos(9.1, 11.2), tvos(16.1, 18.2));

@property (nonatomic, copy) NSNumber * _Nonnull numberOfIntervalsDelivered ZGMTR_DEPRECATED("The numberOfIntervalsDelivered field will be removed", ios(16.1, 18.2), macos(13.0, 15.2), watchos(9.1, 11.2), tvos(16.1, 18.2));

@property (nonatomic, copy) NSNumber * _Nonnull attributeId ZGMTR_DEPRECATED("The attributeId field will be removed", ios(16.1, 18.2), macos(13.0, 15.2), watchos(9.1, 11.2), tvos(16.1, 18.2));

@property (nonatomic, copy) NSArray * _Nonnull intervals ZGMTR_DEPRECATED("The intervals field will be removed", ios(16.1, 18.2), macos(13.0, 15.2), watchos(9.1, 11.2), tvos(16.1, 18.2));
/**
 * Controls whether the command is a timed command (using Timed Invoke).
 *
 * If nil (the default value), a regular invoke is done for commands that do
 * not require a timed invoke and a timed invoke with some default timed request
 * timeout is done for commands that require a timed invoke.
 *
 * If not nil, a timed invoke is done, with the provided value used as the timed
 * request timeout.  The value should be chosen small enough to provide the
 * desired security properties but large enough that it will allow a round-trip
 * from the sever to the client (for the status response and actual invoke
 * request) within the timeout window.
 *
 */
@property (nonatomic, copy, nullable) NSNumber * timedInvokeTimeoutMs ZGMTR_DEPRECATED("Timed invoke does not make sense for server to client commands", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));

/**
 * Initialize an ZGMTRElectricalMeasurementClusterGetMeasurementProfileResponseCommandParams with a response-value dictionary
 * of the sort that ZGMTRDeviceResponseHandler would receive.
 *
 * Will return nil and hand out an error if the response-value dictionary is not
 * a command data response or is not the right command response.
 *
 * Will return nil and hand out an error if the data response does not match the known
 * schema for this command.
 */
- (nullable instancetype)initWithResponseValue:(NSDictionary<NSString *, id> *)responseValue
                                         error:(NSError * __autoreleasing *)error ZGMTR_DEPRECATED("This command has been removed", ios(17.0, 18.2), macos(14.0, 15.2), watchos(10.0, 11.2), tvos(17.0, 18.2));
@end

ZGMTR_DEPRECATED("This command has been removed", ios(16.1, 18.2), macos(13.0, 15.2), watchos(9.1, 11.2), tvos(16.1, 18.2))
@interface ZGMTRElectricalMeasurementClusterGetMeasurementProfileCommandParams : NSObject <NSCopying>

@property (nonatomic, copy) NSNumber * _Nonnull attributeId ZGMTR_DEPRECATED("The attributeId field will be removed", ios(16.1, 18.2), macos(13.0, 15.2), watchos(9.1, 11.2), tvos(16.1, 18.2));

@property (nonatomic, copy) NSNumber * _Nonnull startTime ZGMTR_DEPRECATED("The startTime field will be removed", ios(16.1, 18.2), macos(13.0, 15.2), watchos(9.1, 11.2), tvos(16.1, 18.2));

@property (nonatomic, copy) NSNumber * _Nonnull numberOfIntervals ZGMTR_DEPRECATED("The numberOfIntervals field will be removed", ios(16.1, 18.2), macos(13.0, 15.2), watchos(9.1, 11.2), tvos(16.1, 18.2));
/**
 * Controls whether the command is a timed command (using Timed Invoke).
 *
 * If nil (the default value), a regular invoke is done for commands that do
 * not require a timed invoke and a timed invoke with some default timed request
 * timeout is done for commands that require a timed invoke.
 *
 * If not nil, a timed invoke is done, with the provided value used as the timed
 * request timeout.  The value should be chosen small enough to provide the
 * desired security properties but large enough that it will allow a round-trip
 * from the sever to the client (for the status response and actual invoke
 * request) within the timeout window.
 *
 */
@property (nonatomic, copy, nullable) NSNumber * timedInvokeTimeoutMs;

/**
 * Controls how much time, in seconds, we will allow for the server to process the command.
 *
 * The command will then time out if that much time, plus an allowance for retransmits due to network failures, passes.
 *
 * If nil, the framework will try to select an appropriate timeout value itself.
 */
@property (nonatomic, copy, nullable) NSNumber * serverSideProcessingTimeout;
@end

/**
 * Cluster Electrical Measurement
 *
 * Attributes related to the electrical properties of a device. This cluster is used by power outlets and other devices that need to provide instantaneous data as opposed to metrology data which should be retrieved from the metering cluster..
 */
ZGMTR_DEPRECATED("ElectricalMeasurement is deprecated and will be removed", ios(16.1, 18.2), macos(13.0, 15.2), watchos(9.1, 11.2), tvos(16.1, 18.2))
@interface ZGMTRBaseClusterElectricalMeasurement : ZGMTRGenericBaseCluster

/**
 * Command GetProfileInfoCommand
 *
 * A function which retrieves the power profiling information from the electrical measurement server.
 */
- (void)getProfileInfoCommandWithParams:(ZGMTRElectricalMeasurementClusterGetProfileInfoCommandParams * _Nullable)params completion:(ZGMTRStatusCompletion)completion ZGMTR_DEPRECATED("This command is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));
- (void)getProfileInfoCommandWithCompletion:(ZGMTRStatusCompletion)completion
    ZGMTR_DEPRECATED("This command is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));
/**
 * Command GetMeasurementProfileCommand
 *
 * A function which retrieves an electricity measurement profile from the electricity measurement server for a specific attribute Id requested.
 */
- (void)getMeasurementProfileCommandWithParams:(ZGMTRElectricalMeasurementClusterGetMeasurementProfileCommandParams *)params completion:(ZGMTRStatusCompletion)completion ZGMTR_DEPRECATED("This command is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));

- (void)readAttributeMeasurementTypeWithCompletion:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completion ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));
- (void)subscribeAttributeMeasurementTypeWithParams:(ZGMTRSubscribeParams *)params
                            subscriptionEstablished:(ZGMTRSubscriptionEstablishedHandler _Nullable)subscriptionEstablished
                                      reportHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))reportHandler ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));
+ (void)readAttributeMeasurementTypeWithClusterStateCache:(ZGMTRClusterStateCacheContainer *)clusterStateCacheContainer endpoint:(NSNumber *)endpoint queue:(dispatch_queue_t)queue completion:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completion ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));

- (void)readAttributeDcVoltageWithCompletion:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completion ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));
- (void)subscribeAttributeDcVoltageWithParams:(ZGMTRSubscribeParams *)params
                      subscriptionEstablished:(ZGMTRSubscriptionEstablishedHandler _Nullable)subscriptionEstablished
                                reportHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))reportHandler ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));
+ (void)readAttributeDcVoltageWithClusterStateCache:(ZGMTRClusterStateCacheContainer *)clusterStateCacheContainer endpoint:(NSNumber *)endpoint queue:(dispatch_queue_t)queue completion:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completion ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));

- (void)readAttributeDcVoltageMinWithCompletion:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completion ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));
- (void)subscribeAttributeDcVoltageMinWithParams:(ZGMTRSubscribeParams *)params
                         subscriptionEstablished:(ZGMTRSubscriptionEstablishedHandler _Nullable)subscriptionEstablished
                                   reportHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))reportHandler ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));
+ (void)readAttributeDcVoltageMinWithClusterStateCache:(ZGMTRClusterStateCacheContainer *)clusterStateCacheContainer endpoint:(NSNumber *)endpoint queue:(dispatch_queue_t)queue completion:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completion ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));

- (void)readAttributeDcVoltageMaxWithCompletion:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completion ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));
- (void)subscribeAttributeDcVoltageMaxWithParams:(ZGMTRSubscribeParams *)params
                         subscriptionEstablished:(ZGMTRSubscriptionEstablishedHandler _Nullable)subscriptionEstablished
                                   reportHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))reportHandler ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));
+ (void)readAttributeDcVoltageMaxWithClusterStateCache:(ZGMTRClusterStateCacheContainer *)clusterStateCacheContainer endpoint:(NSNumber *)endpoint queue:(dispatch_queue_t)queue completion:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completion ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));

- (void)readAttributeDcCurrentWithCompletion:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completion ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));
- (void)subscribeAttributeDcCurrentWithParams:(ZGMTRSubscribeParams *)params
                      subscriptionEstablished:(ZGMTRSubscriptionEstablishedHandler _Nullable)subscriptionEstablished
                                reportHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))reportHandler ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));
+ (void)readAttributeDcCurrentWithClusterStateCache:(ZGMTRClusterStateCacheContainer *)clusterStateCacheContainer endpoint:(NSNumber *)endpoint queue:(dispatch_queue_t)queue completion:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completion ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));

- (void)readAttributeDcCurrentMinWithCompletion:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completion ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));
- (void)subscribeAttributeDcCurrentMinWithParams:(ZGMTRSubscribeParams *)params
                         subscriptionEstablished:(ZGMTRSubscriptionEstablishedHandler _Nullable)subscriptionEstablished
                                   reportHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))reportHandler ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));
+ (void)readAttributeDcCurrentMinWithClusterStateCache:(ZGMTRClusterStateCacheContainer *)clusterStateCacheContainer endpoint:(NSNumber *)endpoint queue:(dispatch_queue_t)queue completion:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completion ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));

- (void)readAttributeDcCurrentMaxWithCompletion:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completion ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));
- (void)subscribeAttributeDcCurrentMaxWithParams:(ZGMTRSubscribeParams *)params
                         subscriptionEstablished:(ZGMTRSubscriptionEstablishedHandler _Nullable)subscriptionEstablished
                                   reportHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))reportHandler ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));
+ (void)readAttributeDcCurrentMaxWithClusterStateCache:(ZGMTRClusterStateCacheContainer *)clusterStateCacheContainer endpoint:(NSNumber *)endpoint queue:(dispatch_queue_t)queue completion:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completion ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));

- (void)readAttributeDcPowerWithCompletion:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completion ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));
- (void)subscribeAttributeDcPowerWithParams:(ZGMTRSubscribeParams *)params
                    subscriptionEstablished:(ZGMTRSubscriptionEstablishedHandler _Nullable)subscriptionEstablished
                              reportHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))reportHandler ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));
+ (void)readAttributeDcPowerWithClusterStateCache:(ZGMTRClusterStateCacheContainer *)clusterStateCacheContainer endpoint:(NSNumber *)endpoint queue:(dispatch_queue_t)queue completion:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completion ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));

- (void)readAttributeDcPowerMinWithCompletion:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completion ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));
- (void)subscribeAttributeDcPowerMinWithParams:(ZGMTRSubscribeParams *)params
                       subscriptionEstablished:(ZGMTRSubscriptionEstablishedHandler _Nullable)subscriptionEstablished
                                 reportHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))reportHandler ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));
+ (void)readAttributeDcPowerMinWithClusterStateCache:(ZGMTRClusterStateCacheContainer *)clusterStateCacheContainer endpoint:(NSNumber *)endpoint queue:(dispatch_queue_t)queue completion:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completion ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));

- (void)readAttributeDcPowerMaxWithCompletion:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completion ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));
- (void)subscribeAttributeDcPowerMaxWithParams:(ZGMTRSubscribeParams *)params
                       subscriptionEstablished:(ZGMTRSubscriptionEstablishedHandler _Nullable)subscriptionEstablished
                                 reportHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))reportHandler ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));
+ (void)readAttributeDcPowerMaxWithClusterStateCache:(ZGMTRClusterStateCacheContainer *)clusterStateCacheContainer endpoint:(NSNumber *)endpoint queue:(dispatch_queue_t)queue completion:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completion ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));

- (void)readAttributeDcVoltageMultiplierWithCompletion:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completion ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));
- (void)subscribeAttributeDcVoltageMultiplierWithParams:(ZGMTRSubscribeParams *)params
                                subscriptionEstablished:(ZGMTRSubscriptionEstablishedHandler _Nullable)subscriptionEstablished
                                          reportHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))reportHandler ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));
+ (void)readAttributeDcVoltageMultiplierWithClusterStateCache:(ZGMTRClusterStateCacheContainer *)clusterStateCacheContainer endpoint:(NSNumber *)endpoint queue:(dispatch_queue_t)queue completion:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completion ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));

- (void)readAttributeDcVoltageDivisorWithCompletion:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completion ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));
- (void)subscribeAttributeDcVoltageDivisorWithParams:(ZGMTRSubscribeParams *)params
                             subscriptionEstablished:(ZGMTRSubscriptionEstablishedHandler _Nullable)subscriptionEstablished
                                       reportHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))reportHandler ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));
+ (void)readAttributeDcVoltageDivisorWithClusterStateCache:(ZGMTRClusterStateCacheContainer *)clusterStateCacheContainer endpoint:(NSNumber *)endpoint queue:(dispatch_queue_t)queue completion:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completion ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));

- (void)readAttributeDcCurrentMultiplierWithCompletion:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completion ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));
- (void)subscribeAttributeDcCurrentMultiplierWithParams:(ZGMTRSubscribeParams *)params
                                subscriptionEstablished:(ZGMTRSubscriptionEstablishedHandler _Nullable)subscriptionEstablished
                                          reportHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))reportHandler ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));
+ (void)readAttributeDcCurrentMultiplierWithClusterStateCache:(ZGMTRClusterStateCacheContainer *)clusterStateCacheContainer endpoint:(NSNumber *)endpoint queue:(dispatch_queue_t)queue completion:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completion ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));

- (void)readAttributeDcCurrentDivisorWithCompletion:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completion ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));
- (void)subscribeAttributeDcCurrentDivisorWithParams:(ZGMTRSubscribeParams *)params
                             subscriptionEstablished:(ZGMTRSubscriptionEstablishedHandler _Nullable)subscriptionEstablished
                                       reportHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))reportHandler ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));
+ (void)readAttributeDcCurrentDivisorWithClusterStateCache:(ZGMTRClusterStateCacheContainer *)clusterStateCacheContainer endpoint:(NSNumber *)endpoint queue:(dispatch_queue_t)queue completion:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completion ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));

- (void)readAttributeDcPowerMultiplierWithCompletion:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completion ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));
- (void)subscribeAttributeDcPowerMultiplierWithParams:(ZGMTRSubscribeParams *)params
                              subscriptionEstablished:(ZGMTRSubscriptionEstablishedHandler _Nullable)subscriptionEstablished
                                        reportHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))reportHandler ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));
+ (void)readAttributeDcPowerMultiplierWithClusterStateCache:(ZGMTRClusterStateCacheContainer *)clusterStateCacheContainer endpoint:(NSNumber *)endpoint queue:(dispatch_queue_t)queue completion:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completion ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));

- (void)readAttributeDcPowerDivisorWithCompletion:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completion ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));
- (void)subscribeAttributeDcPowerDivisorWithParams:(ZGMTRSubscribeParams *)params
                           subscriptionEstablished:(ZGMTRSubscriptionEstablishedHandler _Nullable)subscriptionEstablished
                                     reportHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))reportHandler ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));
+ (void)readAttributeDcPowerDivisorWithClusterStateCache:(ZGMTRClusterStateCacheContainer *)clusterStateCacheContainer endpoint:(NSNumber *)endpoint queue:(dispatch_queue_t)queue completion:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completion ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));

- (void)readAttributeAcFrequencyWithCompletion:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completion ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));
- (void)subscribeAttributeAcFrequencyWithParams:(ZGMTRSubscribeParams *)params
                        subscriptionEstablished:(ZGMTRSubscriptionEstablishedHandler _Nullable)subscriptionEstablished
                                  reportHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))reportHandler ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));
+ (void)readAttributeAcFrequencyWithClusterStateCache:(ZGMTRClusterStateCacheContainer *)clusterStateCacheContainer endpoint:(NSNumber *)endpoint queue:(dispatch_queue_t)queue completion:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completion ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));

- (void)readAttributeAcFrequencyMinWithCompletion:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completion ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));
- (void)subscribeAttributeAcFrequencyMinWithParams:(ZGMTRSubscribeParams *)params
                           subscriptionEstablished:(ZGMTRSubscriptionEstablishedHandler _Nullable)subscriptionEstablished
                                     reportHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))reportHandler ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));
+ (void)readAttributeAcFrequencyMinWithClusterStateCache:(ZGMTRClusterStateCacheContainer *)clusterStateCacheContainer endpoint:(NSNumber *)endpoint queue:(dispatch_queue_t)queue completion:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completion ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));

- (void)readAttributeAcFrequencyMaxWithCompletion:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completion ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));
- (void)subscribeAttributeAcFrequencyMaxWithParams:(ZGMTRSubscribeParams *)params
                           subscriptionEstablished:(ZGMTRSubscriptionEstablishedHandler _Nullable)subscriptionEstablished
                                     reportHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))reportHandler ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));
+ (void)readAttributeAcFrequencyMaxWithClusterStateCache:(ZGMTRClusterStateCacheContainer *)clusterStateCacheContainer endpoint:(NSNumber *)endpoint queue:(dispatch_queue_t)queue completion:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completion ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));

- (void)readAttributeNeutralCurrentWithCompletion:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completion ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));
- (void)subscribeAttributeNeutralCurrentWithParams:(ZGMTRSubscribeParams *)params
                           subscriptionEstablished:(ZGMTRSubscriptionEstablishedHandler _Nullable)subscriptionEstablished
                                     reportHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))reportHandler ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));
+ (void)readAttributeNeutralCurrentWithClusterStateCache:(ZGMTRClusterStateCacheContainer *)clusterStateCacheContainer endpoint:(NSNumber *)endpoint queue:(dispatch_queue_t)queue completion:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completion ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));

- (void)readAttributeTotalActivePowerWithCompletion:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completion ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));
- (void)subscribeAttributeTotalActivePowerWithParams:(ZGMTRSubscribeParams *)params
                             subscriptionEstablished:(ZGMTRSubscriptionEstablishedHandler _Nullable)subscriptionEstablished
                                       reportHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))reportHandler ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));
+ (void)readAttributeTotalActivePowerWithClusterStateCache:(ZGMTRClusterStateCacheContainer *)clusterStateCacheContainer endpoint:(NSNumber *)endpoint queue:(dispatch_queue_t)queue completion:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completion ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));

- (void)readAttributeTotalReactivePowerWithCompletion:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completion ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));
- (void)subscribeAttributeTotalReactivePowerWithParams:(ZGMTRSubscribeParams *)params
                               subscriptionEstablished:(ZGMTRSubscriptionEstablishedHandler _Nullable)subscriptionEstablished
                                         reportHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))reportHandler ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));
+ (void)readAttributeTotalReactivePowerWithClusterStateCache:(ZGMTRClusterStateCacheContainer *)clusterStateCacheContainer endpoint:(NSNumber *)endpoint queue:(dispatch_queue_t)queue completion:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completion ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));

- (void)readAttributeTotalApparentPowerWithCompletion:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completion ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));
- (void)subscribeAttributeTotalApparentPowerWithParams:(ZGMTRSubscribeParams *)params
                               subscriptionEstablished:(ZGMTRSubscriptionEstablishedHandler _Nullable)subscriptionEstablished
                                         reportHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))reportHandler ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));
+ (void)readAttributeTotalApparentPowerWithClusterStateCache:(ZGMTRClusterStateCacheContainer *)clusterStateCacheContainer endpoint:(NSNumber *)endpoint queue:(dispatch_queue_t)queue completion:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completion ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));

- (void)readAttributeMeasured1stHarmonicCurrentWithCompletion:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completion ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));
- (void)subscribeAttributeMeasured1stHarmonicCurrentWithParams:(ZGMTRSubscribeParams *)params
                                       subscriptionEstablished:(ZGMTRSubscriptionEstablishedHandler _Nullable)subscriptionEstablished
                                                 reportHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))reportHandler ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));
+ (void)readAttributeMeasured1stHarmonicCurrentWithClusterStateCache:(ZGMTRClusterStateCacheContainer *)clusterStateCacheContainer endpoint:(NSNumber *)endpoint queue:(dispatch_queue_t)queue completion:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completion ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));

- (void)readAttributeMeasured3rdHarmonicCurrentWithCompletion:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completion ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));
- (void)subscribeAttributeMeasured3rdHarmonicCurrentWithParams:(ZGMTRSubscribeParams *)params
                                       subscriptionEstablished:(ZGMTRSubscriptionEstablishedHandler _Nullable)subscriptionEstablished
                                                 reportHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))reportHandler ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));
+ (void)readAttributeMeasured3rdHarmonicCurrentWithClusterStateCache:(ZGMTRClusterStateCacheContainer *)clusterStateCacheContainer endpoint:(NSNumber *)endpoint queue:(dispatch_queue_t)queue completion:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completion ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));

- (void)readAttributeMeasured5thHarmonicCurrentWithCompletion:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completion ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));
- (void)subscribeAttributeMeasured5thHarmonicCurrentWithParams:(ZGMTRSubscribeParams *)params
                                       subscriptionEstablished:(ZGMTRSubscriptionEstablishedHandler _Nullable)subscriptionEstablished
                                                 reportHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))reportHandler ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));
+ (void)readAttributeMeasured5thHarmonicCurrentWithClusterStateCache:(ZGMTRClusterStateCacheContainer *)clusterStateCacheContainer endpoint:(NSNumber *)endpoint queue:(dispatch_queue_t)queue completion:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completion ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));

- (void)readAttributeMeasured7thHarmonicCurrentWithCompletion:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completion ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));
- (void)subscribeAttributeMeasured7thHarmonicCurrentWithParams:(ZGMTRSubscribeParams *)params
                                       subscriptionEstablished:(ZGMTRSubscriptionEstablishedHandler _Nullable)subscriptionEstablished
                                                 reportHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))reportHandler ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));
+ (void)readAttributeMeasured7thHarmonicCurrentWithClusterStateCache:(ZGMTRClusterStateCacheContainer *)clusterStateCacheContainer endpoint:(NSNumber *)endpoint queue:(dispatch_queue_t)queue completion:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completion ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));

- (void)readAttributeMeasured9thHarmonicCurrentWithCompletion:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completion ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));
- (void)subscribeAttributeMeasured9thHarmonicCurrentWithParams:(ZGMTRSubscribeParams *)params
                                       subscriptionEstablished:(ZGMTRSubscriptionEstablishedHandler _Nullable)subscriptionEstablished
                                                 reportHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))reportHandler ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));
+ (void)readAttributeMeasured9thHarmonicCurrentWithClusterStateCache:(ZGMTRClusterStateCacheContainer *)clusterStateCacheContainer endpoint:(NSNumber *)endpoint queue:(dispatch_queue_t)queue completion:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completion ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));

- (void)readAttributeMeasured11thHarmonicCurrentWithCompletion:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completion ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));
- (void)subscribeAttributeMeasured11thHarmonicCurrentWithParams:(ZGMTRSubscribeParams *)params
                                        subscriptionEstablished:(ZGMTRSubscriptionEstablishedHandler _Nullable)subscriptionEstablished
                                                  reportHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))reportHandler ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));
+ (void)readAttributeMeasured11thHarmonicCurrentWithClusterStateCache:(ZGMTRClusterStateCacheContainer *)clusterStateCacheContainer endpoint:(NSNumber *)endpoint queue:(dispatch_queue_t)queue completion:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completion ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));

- (void)readAttributeMeasuredPhase1stHarmonicCurrentWithCompletion:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completion ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));
- (void)subscribeAttributeMeasuredPhase1stHarmonicCurrentWithParams:(ZGMTRSubscribeParams *)params
                                            subscriptionEstablished:(ZGMTRSubscriptionEstablishedHandler _Nullable)subscriptionEstablished
                                                      reportHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))reportHandler ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));
+ (void)readAttributeMeasuredPhase1stHarmonicCurrentWithClusterStateCache:(ZGMTRClusterStateCacheContainer *)clusterStateCacheContainer endpoint:(NSNumber *)endpoint queue:(dispatch_queue_t)queue completion:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completion ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));

- (void)readAttributeMeasuredPhase3rdHarmonicCurrentWithCompletion:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completion ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));
- (void)subscribeAttributeMeasuredPhase3rdHarmonicCurrentWithParams:(ZGMTRSubscribeParams *)params
                                            subscriptionEstablished:(ZGMTRSubscriptionEstablishedHandler _Nullable)subscriptionEstablished
                                                      reportHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))reportHandler ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));
+ (void)readAttributeMeasuredPhase3rdHarmonicCurrentWithClusterStateCache:(ZGMTRClusterStateCacheContainer *)clusterStateCacheContainer endpoint:(NSNumber *)endpoint queue:(dispatch_queue_t)queue completion:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completion ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));

- (void)readAttributeMeasuredPhase5thHarmonicCurrentWithCompletion:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completion ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));
- (void)subscribeAttributeMeasuredPhase5thHarmonicCurrentWithParams:(ZGMTRSubscribeParams *)params
                                            subscriptionEstablished:(ZGMTRSubscriptionEstablishedHandler _Nullable)subscriptionEstablished
                                                      reportHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))reportHandler ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));
+ (void)readAttributeMeasuredPhase5thHarmonicCurrentWithClusterStateCache:(ZGMTRClusterStateCacheContainer *)clusterStateCacheContainer endpoint:(NSNumber *)endpoint queue:(dispatch_queue_t)queue completion:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completion ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));

- (void)readAttributeMeasuredPhase7thHarmonicCurrentWithCompletion:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completion ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));
- (void)subscribeAttributeMeasuredPhase7thHarmonicCurrentWithParams:(ZGMTRSubscribeParams *)params
                                            subscriptionEstablished:(ZGMTRSubscriptionEstablishedHandler _Nullable)subscriptionEstablished
                                                      reportHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))reportHandler ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));
+ (void)readAttributeMeasuredPhase7thHarmonicCurrentWithClusterStateCache:(ZGMTRClusterStateCacheContainer *)clusterStateCacheContainer endpoint:(NSNumber *)endpoint queue:(dispatch_queue_t)queue completion:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completion ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));

- (void)readAttributeMeasuredPhase9thHarmonicCurrentWithCompletion:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completion ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));
- (void)subscribeAttributeMeasuredPhase9thHarmonicCurrentWithParams:(ZGMTRSubscribeParams *)params
                                            subscriptionEstablished:(ZGMTRSubscriptionEstablishedHandler _Nullable)subscriptionEstablished
                                                      reportHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))reportHandler ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));
+ (void)readAttributeMeasuredPhase9thHarmonicCurrentWithClusterStateCache:(ZGMTRClusterStateCacheContainer *)clusterStateCacheContainer endpoint:(NSNumber *)endpoint queue:(dispatch_queue_t)queue completion:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completion ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));

- (void)readAttributeMeasuredPhase11thHarmonicCurrentWithCompletion:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completion ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));
- (void)subscribeAttributeMeasuredPhase11thHarmonicCurrentWithParams:(ZGMTRSubscribeParams *)params
                                             subscriptionEstablished:(ZGMTRSubscriptionEstablishedHandler _Nullable)subscriptionEstablished
                                                       reportHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))reportHandler ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));
+ (void)readAttributeMeasuredPhase11thHarmonicCurrentWithClusterStateCache:(ZGMTRClusterStateCacheContainer *)clusterStateCacheContainer endpoint:(NSNumber *)endpoint queue:(dispatch_queue_t)queue completion:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completion ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));

- (void)readAttributeAcFrequencyMultiplierWithCompletion:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completion ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));
- (void)subscribeAttributeAcFrequencyMultiplierWithParams:(ZGMTRSubscribeParams *)params
                                  subscriptionEstablished:(ZGMTRSubscriptionEstablishedHandler _Nullable)subscriptionEstablished
                                            reportHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))reportHandler ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));
+ (void)readAttributeAcFrequencyMultiplierWithClusterStateCache:(ZGMTRClusterStateCacheContainer *)clusterStateCacheContainer endpoint:(NSNumber *)endpoint queue:(dispatch_queue_t)queue completion:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completion ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));

- (void)readAttributeAcFrequencyDivisorWithCompletion:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completion ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));
- (void)subscribeAttributeAcFrequencyDivisorWithParams:(ZGMTRSubscribeParams *)params
                               subscriptionEstablished:(ZGMTRSubscriptionEstablishedHandler _Nullable)subscriptionEstablished
                                         reportHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))reportHandler ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));
+ (void)readAttributeAcFrequencyDivisorWithClusterStateCache:(ZGMTRClusterStateCacheContainer *)clusterStateCacheContainer endpoint:(NSNumber *)endpoint queue:(dispatch_queue_t)queue completion:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completion ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));

- (void)readAttributePowerMultiplierWithCompletion:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completion ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));
- (void)subscribeAttributePowerMultiplierWithParams:(ZGMTRSubscribeParams *)params
                            subscriptionEstablished:(ZGMTRSubscriptionEstablishedHandler _Nullable)subscriptionEstablished
                                      reportHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))reportHandler ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));
+ (void)readAttributePowerMultiplierWithClusterStateCache:(ZGMTRClusterStateCacheContainer *)clusterStateCacheContainer endpoint:(NSNumber *)endpoint queue:(dispatch_queue_t)queue completion:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completion ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));

- (void)readAttributePowerDivisorWithCompletion:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completion ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));
- (void)subscribeAttributePowerDivisorWithParams:(ZGMTRSubscribeParams *)params
                         subscriptionEstablished:(ZGMTRSubscriptionEstablishedHandler _Nullable)subscriptionEstablished
                                   reportHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))reportHandler ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));
+ (void)readAttributePowerDivisorWithClusterStateCache:(ZGMTRClusterStateCacheContainer *)clusterStateCacheContainer endpoint:(NSNumber *)endpoint queue:(dispatch_queue_t)queue completion:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completion ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));

- (void)readAttributeHarmonicCurrentMultiplierWithCompletion:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completion ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));
- (void)subscribeAttributeHarmonicCurrentMultiplierWithParams:(ZGMTRSubscribeParams *)params
                                      subscriptionEstablished:(ZGMTRSubscriptionEstablishedHandler _Nullable)subscriptionEstablished
                                                reportHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))reportHandler ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));
+ (void)readAttributeHarmonicCurrentMultiplierWithClusterStateCache:(ZGMTRClusterStateCacheContainer *)clusterStateCacheContainer endpoint:(NSNumber *)endpoint queue:(dispatch_queue_t)queue completion:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completion ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));

- (void)readAttributePhaseHarmonicCurrentMultiplierWithCompletion:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completion ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));
- (void)subscribeAttributePhaseHarmonicCurrentMultiplierWithParams:(ZGMTRSubscribeParams *)params
                                           subscriptionEstablished:(ZGMTRSubscriptionEstablishedHandler _Nullable)subscriptionEstablished
                                                     reportHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))reportHandler ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));
+ (void)readAttributePhaseHarmonicCurrentMultiplierWithClusterStateCache:(ZGMTRClusterStateCacheContainer *)clusterStateCacheContainer endpoint:(NSNumber *)endpoint queue:(dispatch_queue_t)queue completion:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completion ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));

- (void)readAttributeInstantaneousVoltageWithCompletion:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completion ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));
- (void)subscribeAttributeInstantaneousVoltageWithParams:(ZGMTRSubscribeParams *)params
                                 subscriptionEstablished:(ZGMTRSubscriptionEstablishedHandler _Nullable)subscriptionEstablished
                                           reportHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))reportHandler ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));
+ (void)readAttributeInstantaneousVoltageWithClusterStateCache:(ZGMTRClusterStateCacheContainer *)clusterStateCacheContainer endpoint:(NSNumber *)endpoint queue:(dispatch_queue_t)queue completion:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completion ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));

- (void)readAttributeInstantaneousLineCurrentWithCompletion:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completion ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));
- (void)subscribeAttributeInstantaneousLineCurrentWithParams:(ZGMTRSubscribeParams *)params
                                     subscriptionEstablished:(ZGMTRSubscriptionEstablishedHandler _Nullable)subscriptionEstablished
                                               reportHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))reportHandler ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));
+ (void)readAttributeInstantaneousLineCurrentWithClusterStateCache:(ZGMTRClusterStateCacheContainer *)clusterStateCacheContainer endpoint:(NSNumber *)endpoint queue:(dispatch_queue_t)queue completion:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completion ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));

- (void)readAttributeInstantaneousActiveCurrentWithCompletion:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completion ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));
- (void)subscribeAttributeInstantaneousActiveCurrentWithParams:(ZGMTRSubscribeParams *)params
                                       subscriptionEstablished:(ZGMTRSubscriptionEstablishedHandler _Nullable)subscriptionEstablished
                                                 reportHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))reportHandler ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));
+ (void)readAttributeInstantaneousActiveCurrentWithClusterStateCache:(ZGMTRClusterStateCacheContainer *)clusterStateCacheContainer endpoint:(NSNumber *)endpoint queue:(dispatch_queue_t)queue completion:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completion ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));

- (void)readAttributeInstantaneousReactiveCurrentWithCompletion:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completion ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));
- (void)subscribeAttributeInstantaneousReactiveCurrentWithParams:(ZGMTRSubscribeParams *)params
                                         subscriptionEstablished:(ZGMTRSubscriptionEstablishedHandler _Nullable)subscriptionEstablished
                                                   reportHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))reportHandler ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));
+ (void)readAttributeInstantaneousReactiveCurrentWithClusterStateCache:(ZGMTRClusterStateCacheContainer *)clusterStateCacheContainer endpoint:(NSNumber *)endpoint queue:(dispatch_queue_t)queue completion:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completion ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));

- (void)readAttributeInstantaneousPowerWithCompletion:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completion ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));
- (void)subscribeAttributeInstantaneousPowerWithParams:(ZGMTRSubscribeParams *)params
                               subscriptionEstablished:(ZGMTRSubscriptionEstablishedHandler _Nullable)subscriptionEstablished
                                         reportHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))reportHandler ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));
+ (void)readAttributeInstantaneousPowerWithClusterStateCache:(ZGMTRClusterStateCacheContainer *)clusterStateCacheContainer endpoint:(NSNumber *)endpoint queue:(dispatch_queue_t)queue completion:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completion ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));

- (void)readAttributeRmsVoltageWithCompletion:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completion ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));
- (void)subscribeAttributeRmsVoltageWithParams:(ZGMTRSubscribeParams *)params
                       subscriptionEstablished:(ZGMTRSubscriptionEstablishedHandler _Nullable)subscriptionEstablished
                                 reportHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))reportHandler ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));
+ (void)readAttributeRmsVoltageWithClusterStateCache:(ZGMTRClusterStateCacheContainer *)clusterStateCacheContainer endpoint:(NSNumber *)endpoint queue:(dispatch_queue_t)queue completion:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completion ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));

- (void)readAttributeRmsVoltageMinWithCompletion:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completion ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));
- (void)subscribeAttributeRmsVoltageMinWithParams:(ZGMTRSubscribeParams *)params
                          subscriptionEstablished:(ZGMTRSubscriptionEstablishedHandler _Nullable)subscriptionEstablished
                                    reportHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))reportHandler ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));
+ (void)readAttributeRmsVoltageMinWithClusterStateCache:(ZGMTRClusterStateCacheContainer *)clusterStateCacheContainer endpoint:(NSNumber *)endpoint queue:(dispatch_queue_t)queue completion:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completion ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));

- (void)readAttributeRmsVoltageMaxWithCompletion:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completion ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));
- (void)subscribeAttributeRmsVoltageMaxWithParams:(ZGMTRSubscribeParams *)params
                          subscriptionEstablished:(ZGMTRSubscriptionEstablishedHandler _Nullable)subscriptionEstablished
                                    reportHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))reportHandler ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));
+ (void)readAttributeRmsVoltageMaxWithClusterStateCache:(ZGMTRClusterStateCacheContainer *)clusterStateCacheContainer endpoint:(NSNumber *)endpoint queue:(dispatch_queue_t)queue completion:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completion ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));

- (void)readAttributeRmsCurrentWithCompletion:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completion ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));
- (void)subscribeAttributeRmsCurrentWithParams:(ZGMTRSubscribeParams *)params
                       subscriptionEstablished:(ZGMTRSubscriptionEstablishedHandler _Nullable)subscriptionEstablished
                                 reportHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))reportHandler ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));
+ (void)readAttributeRmsCurrentWithClusterStateCache:(ZGMTRClusterStateCacheContainer *)clusterStateCacheContainer endpoint:(NSNumber *)endpoint queue:(dispatch_queue_t)queue completion:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completion ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));

- (void)readAttributeRmsCurrentMinWithCompletion:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completion ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));
- (void)subscribeAttributeRmsCurrentMinWithParams:(ZGMTRSubscribeParams *)params
                          subscriptionEstablished:(ZGMTRSubscriptionEstablishedHandler _Nullable)subscriptionEstablished
                                    reportHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))reportHandler ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));
+ (void)readAttributeRmsCurrentMinWithClusterStateCache:(ZGMTRClusterStateCacheContainer *)clusterStateCacheContainer endpoint:(NSNumber *)endpoint queue:(dispatch_queue_t)queue completion:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completion ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));

- (void)readAttributeRmsCurrentMaxWithCompletion:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completion ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));
- (void)subscribeAttributeRmsCurrentMaxWithParams:(ZGMTRSubscribeParams *)params
                          subscriptionEstablished:(ZGMTRSubscriptionEstablishedHandler _Nullable)subscriptionEstablished
                                    reportHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))reportHandler ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));
+ (void)readAttributeRmsCurrentMaxWithClusterStateCache:(ZGMTRClusterStateCacheContainer *)clusterStateCacheContainer endpoint:(NSNumber *)endpoint queue:(dispatch_queue_t)queue completion:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completion ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));

- (void)readAttributeActivePowerWithCompletion:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completion ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));
- (void)subscribeAttributeActivePowerWithParams:(ZGMTRSubscribeParams *)params
                        subscriptionEstablished:(ZGMTRSubscriptionEstablishedHandler _Nullable)subscriptionEstablished
                                  reportHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))reportHandler ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));
+ (void)readAttributeActivePowerWithClusterStateCache:(ZGMTRClusterStateCacheContainer *)clusterStateCacheContainer endpoint:(NSNumber *)endpoint queue:(dispatch_queue_t)queue completion:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completion ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));

- (void)readAttributeActivePowerMinWithCompletion:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completion ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));
- (void)subscribeAttributeActivePowerMinWithParams:(ZGMTRSubscribeParams *)params
                           subscriptionEstablished:(ZGMTRSubscriptionEstablishedHandler _Nullable)subscriptionEstablished
                                     reportHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))reportHandler ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));
+ (void)readAttributeActivePowerMinWithClusterStateCache:(ZGMTRClusterStateCacheContainer *)clusterStateCacheContainer endpoint:(NSNumber *)endpoint queue:(dispatch_queue_t)queue completion:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completion ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));

- (void)readAttributeActivePowerMaxWithCompletion:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completion ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));
- (void)subscribeAttributeActivePowerMaxWithParams:(ZGMTRSubscribeParams *)params
                           subscriptionEstablished:(ZGMTRSubscriptionEstablishedHandler _Nullable)subscriptionEstablished
                                     reportHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))reportHandler ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));
+ (void)readAttributeActivePowerMaxWithClusterStateCache:(ZGMTRClusterStateCacheContainer *)clusterStateCacheContainer endpoint:(NSNumber *)endpoint queue:(dispatch_queue_t)queue completion:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completion ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));

- (void)readAttributeReactivePowerWithCompletion:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completion ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));
- (void)subscribeAttributeReactivePowerWithParams:(ZGMTRSubscribeParams *)params
                          subscriptionEstablished:(ZGMTRSubscriptionEstablishedHandler _Nullable)subscriptionEstablished
                                    reportHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))reportHandler ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));
+ (void)readAttributeReactivePowerWithClusterStateCache:(ZGMTRClusterStateCacheContainer *)clusterStateCacheContainer endpoint:(NSNumber *)endpoint queue:(dispatch_queue_t)queue completion:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completion ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));

- (void)readAttributeApparentPowerWithCompletion:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completion ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));
- (void)subscribeAttributeApparentPowerWithParams:(ZGMTRSubscribeParams *)params
                          subscriptionEstablished:(ZGMTRSubscriptionEstablishedHandler _Nullable)subscriptionEstablished
                                    reportHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))reportHandler ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));
+ (void)readAttributeApparentPowerWithClusterStateCache:(ZGMTRClusterStateCacheContainer *)clusterStateCacheContainer endpoint:(NSNumber *)endpoint queue:(dispatch_queue_t)queue completion:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completion ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));

- (void)readAttributePowerFactorWithCompletion:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completion ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));
- (void)subscribeAttributePowerFactorWithParams:(ZGMTRSubscribeParams *)params
                        subscriptionEstablished:(ZGMTRSubscriptionEstablishedHandler _Nullable)subscriptionEstablished
                                  reportHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))reportHandler ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));
+ (void)readAttributePowerFactorWithClusterStateCache:(ZGMTRClusterStateCacheContainer *)clusterStateCacheContainer endpoint:(NSNumber *)endpoint queue:(dispatch_queue_t)queue completion:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completion ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));

- (void)readAttributeAverageRmsVoltageMeasurementPeriodWithCompletion:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completion ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));
- (void)writeAttributeAverageRmsVoltageMeasurementPeriodWithValue:(NSNumber * _Nonnull)value completion:(ZGMTRStatusCompletion)completion ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));
- (void)writeAttributeAverageRmsVoltageMeasurementPeriodWithValue:(NSNumber * _Nonnull)value params:(ZGMTRWriteParams * _Nullable)params completion:(ZGMTRStatusCompletion)completion ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));
- (void)subscribeAttributeAverageRmsVoltageMeasurementPeriodWithParams:(ZGMTRSubscribeParams *)params
                                               subscriptionEstablished:(ZGMTRSubscriptionEstablishedHandler _Nullable)subscriptionEstablished
                                                         reportHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))reportHandler ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));
+ (void)readAttributeAverageRmsVoltageMeasurementPeriodWithClusterStateCache:(ZGMTRClusterStateCacheContainer *)clusterStateCacheContainer endpoint:(NSNumber *)endpoint queue:(dispatch_queue_t)queue completion:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completion ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));

- (void)readAttributeAverageRmsUnderVoltageCounterWithCompletion:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completion ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));
- (void)writeAttributeAverageRmsUnderVoltageCounterWithValue:(NSNumber * _Nonnull)value completion:(ZGMTRStatusCompletion)completion ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));
- (void)writeAttributeAverageRmsUnderVoltageCounterWithValue:(NSNumber * _Nonnull)value params:(ZGMTRWriteParams * _Nullable)params completion:(ZGMTRStatusCompletion)completion ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));
- (void)subscribeAttributeAverageRmsUnderVoltageCounterWithParams:(ZGMTRSubscribeParams *)params
                                          subscriptionEstablished:(ZGMTRSubscriptionEstablishedHandler _Nullable)subscriptionEstablished
                                                    reportHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))reportHandler ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));
+ (void)readAttributeAverageRmsUnderVoltageCounterWithClusterStateCache:(ZGMTRClusterStateCacheContainer *)clusterStateCacheContainer endpoint:(NSNumber *)endpoint queue:(dispatch_queue_t)queue completion:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completion ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));

- (void)readAttributeRmsExtremeOverVoltagePeriodWithCompletion:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completion ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));
- (void)writeAttributeRmsExtremeOverVoltagePeriodWithValue:(NSNumber * _Nonnull)value completion:(ZGMTRStatusCompletion)completion ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));
- (void)writeAttributeRmsExtremeOverVoltagePeriodWithValue:(NSNumber * _Nonnull)value params:(ZGMTRWriteParams * _Nullable)params completion:(ZGMTRStatusCompletion)completion ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));
- (void)subscribeAttributeRmsExtremeOverVoltagePeriodWithParams:(ZGMTRSubscribeParams *)params
                                        subscriptionEstablished:(ZGMTRSubscriptionEstablishedHandler _Nullable)subscriptionEstablished
                                                  reportHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))reportHandler ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));
+ (void)readAttributeRmsExtremeOverVoltagePeriodWithClusterStateCache:(ZGMTRClusterStateCacheContainer *)clusterStateCacheContainer endpoint:(NSNumber *)endpoint queue:(dispatch_queue_t)queue completion:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completion ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));

- (void)readAttributeRmsExtremeUnderVoltagePeriodWithCompletion:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completion ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));
- (void)writeAttributeRmsExtremeUnderVoltagePeriodWithValue:(NSNumber * _Nonnull)value completion:(ZGMTRStatusCompletion)completion ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));
- (void)writeAttributeRmsExtremeUnderVoltagePeriodWithValue:(NSNumber * _Nonnull)value params:(ZGMTRWriteParams * _Nullable)params completion:(ZGMTRStatusCompletion)completion ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));
- (void)subscribeAttributeRmsExtremeUnderVoltagePeriodWithParams:(ZGMTRSubscribeParams *)params
                                         subscriptionEstablished:(ZGMTRSubscriptionEstablishedHandler _Nullable)subscriptionEstablished
                                                   reportHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))reportHandler ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));
+ (void)readAttributeRmsExtremeUnderVoltagePeriodWithClusterStateCache:(ZGMTRClusterStateCacheContainer *)clusterStateCacheContainer endpoint:(NSNumber *)endpoint queue:(dispatch_queue_t)queue completion:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completion ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));

- (void)readAttributeRmsVoltageSagPeriodWithCompletion:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completion ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));
- (void)writeAttributeRmsVoltageSagPeriodWithValue:(NSNumber * _Nonnull)value completion:(ZGMTRStatusCompletion)completion ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));
- (void)writeAttributeRmsVoltageSagPeriodWithValue:(NSNumber * _Nonnull)value params:(ZGMTRWriteParams * _Nullable)params completion:(ZGMTRStatusCompletion)completion ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));
- (void)subscribeAttributeRmsVoltageSagPeriodWithParams:(ZGMTRSubscribeParams *)params
                                subscriptionEstablished:(ZGMTRSubscriptionEstablishedHandler _Nullable)subscriptionEstablished
                                          reportHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))reportHandler ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));
+ (void)readAttributeRmsVoltageSagPeriodWithClusterStateCache:(ZGMTRClusterStateCacheContainer *)clusterStateCacheContainer endpoint:(NSNumber *)endpoint queue:(dispatch_queue_t)queue completion:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completion ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));

- (void)readAttributeRmsVoltageSwellPeriodWithCompletion:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completion ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));
- (void)writeAttributeRmsVoltageSwellPeriodWithValue:(NSNumber * _Nonnull)value completion:(ZGMTRStatusCompletion)completion ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));
- (void)writeAttributeRmsVoltageSwellPeriodWithValue:(NSNumber * _Nonnull)value params:(ZGMTRWriteParams * _Nullable)params completion:(ZGMTRStatusCompletion)completion ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));
- (void)subscribeAttributeRmsVoltageSwellPeriodWithParams:(ZGMTRSubscribeParams *)params
                                  subscriptionEstablished:(ZGMTRSubscriptionEstablishedHandler _Nullable)subscriptionEstablished
                                            reportHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))reportHandler ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));
+ (void)readAttributeRmsVoltageSwellPeriodWithClusterStateCache:(ZGMTRClusterStateCacheContainer *)clusterStateCacheContainer endpoint:(NSNumber *)endpoint queue:(dispatch_queue_t)queue completion:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completion ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));

- (void)readAttributeAcVoltageMultiplierWithCompletion:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completion ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));
- (void)subscribeAttributeAcVoltageMultiplierWithParams:(ZGMTRSubscribeParams *)params
                                subscriptionEstablished:(ZGMTRSubscriptionEstablishedHandler _Nullable)subscriptionEstablished
                                          reportHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))reportHandler ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));
+ (void)readAttributeAcVoltageMultiplierWithClusterStateCache:(ZGMTRClusterStateCacheContainer *)clusterStateCacheContainer endpoint:(NSNumber *)endpoint queue:(dispatch_queue_t)queue completion:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completion ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));

- (void)readAttributeAcVoltageDivisorWithCompletion:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completion ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));
- (void)subscribeAttributeAcVoltageDivisorWithParams:(ZGMTRSubscribeParams *)params
                             subscriptionEstablished:(ZGMTRSubscriptionEstablishedHandler _Nullable)subscriptionEstablished
                                       reportHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))reportHandler ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));
+ (void)readAttributeAcVoltageDivisorWithClusterStateCache:(ZGMTRClusterStateCacheContainer *)clusterStateCacheContainer endpoint:(NSNumber *)endpoint queue:(dispatch_queue_t)queue completion:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completion ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));

- (void)readAttributeAcCurrentMultiplierWithCompletion:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completion ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));
- (void)subscribeAttributeAcCurrentMultiplierWithParams:(ZGMTRSubscribeParams *)params
                                subscriptionEstablished:(ZGMTRSubscriptionEstablishedHandler _Nullable)subscriptionEstablished
                                          reportHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))reportHandler ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));
+ (void)readAttributeAcCurrentMultiplierWithClusterStateCache:(ZGMTRClusterStateCacheContainer *)clusterStateCacheContainer endpoint:(NSNumber *)endpoint queue:(dispatch_queue_t)queue completion:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completion ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));

- (void)readAttributeAcCurrentDivisorWithCompletion:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completion ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));
- (void)subscribeAttributeAcCurrentDivisorWithParams:(ZGMTRSubscribeParams *)params
                             subscriptionEstablished:(ZGMTRSubscriptionEstablishedHandler _Nullable)subscriptionEstablished
                                       reportHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))reportHandler ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));
+ (void)readAttributeAcCurrentDivisorWithClusterStateCache:(ZGMTRClusterStateCacheContainer *)clusterStateCacheContainer endpoint:(NSNumber *)endpoint queue:(dispatch_queue_t)queue completion:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completion ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));

- (void)readAttributeAcPowerMultiplierWithCompletion:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completion ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));
- (void)subscribeAttributeAcPowerMultiplierWithParams:(ZGMTRSubscribeParams *)params
                              subscriptionEstablished:(ZGMTRSubscriptionEstablishedHandler _Nullable)subscriptionEstablished
                                        reportHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))reportHandler ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));
+ (void)readAttributeAcPowerMultiplierWithClusterStateCache:(ZGMTRClusterStateCacheContainer *)clusterStateCacheContainer endpoint:(NSNumber *)endpoint queue:(dispatch_queue_t)queue completion:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completion ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));

- (void)readAttributeAcPowerDivisorWithCompletion:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completion ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));
- (void)subscribeAttributeAcPowerDivisorWithParams:(ZGMTRSubscribeParams *)params
                           subscriptionEstablished:(ZGMTRSubscriptionEstablishedHandler _Nullable)subscriptionEstablished
                                     reportHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))reportHandler ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));
+ (void)readAttributeAcPowerDivisorWithClusterStateCache:(ZGMTRClusterStateCacheContainer *)clusterStateCacheContainer endpoint:(NSNumber *)endpoint queue:(dispatch_queue_t)queue completion:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completion ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));

- (void)readAttributeOverloadAlarmsMaskWithCompletion:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completion ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));
- (void)writeAttributeOverloadAlarmsMaskWithValue:(NSNumber * _Nonnull)value completion:(ZGMTRStatusCompletion)completion ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));
- (void)writeAttributeOverloadAlarmsMaskWithValue:(NSNumber * _Nonnull)value params:(ZGMTRWriteParams * _Nullable)params completion:(ZGMTRStatusCompletion)completion ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));
- (void)subscribeAttributeOverloadAlarmsMaskWithParams:(ZGMTRSubscribeParams *)params
                               subscriptionEstablished:(ZGMTRSubscriptionEstablishedHandler _Nullable)subscriptionEstablished
                                         reportHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))reportHandler ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));
+ (void)readAttributeOverloadAlarmsMaskWithClusterStateCache:(ZGMTRClusterStateCacheContainer *)clusterStateCacheContainer endpoint:(NSNumber *)endpoint queue:(dispatch_queue_t)queue completion:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completion ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));

- (void)readAttributeVoltageOverloadWithCompletion:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completion ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));
- (void)subscribeAttributeVoltageOverloadWithParams:(ZGMTRSubscribeParams *)params
                            subscriptionEstablished:(ZGMTRSubscriptionEstablishedHandler _Nullable)subscriptionEstablished
                                      reportHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))reportHandler ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));
+ (void)readAttributeVoltageOverloadWithClusterStateCache:(ZGMTRClusterStateCacheContainer *)clusterStateCacheContainer endpoint:(NSNumber *)endpoint queue:(dispatch_queue_t)queue completion:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completion ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));

- (void)readAttributeCurrentOverloadWithCompletion:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completion ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));
- (void)subscribeAttributeCurrentOverloadWithParams:(ZGMTRSubscribeParams *)params
                            subscriptionEstablished:(ZGMTRSubscriptionEstablishedHandler _Nullable)subscriptionEstablished
                                      reportHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))reportHandler ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));
+ (void)readAttributeCurrentOverloadWithClusterStateCache:(ZGMTRClusterStateCacheContainer *)clusterStateCacheContainer endpoint:(NSNumber *)endpoint queue:(dispatch_queue_t)queue completion:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completion ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));

- (void)readAttributeAcOverloadAlarmsMaskWithCompletion:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completion ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));
- (void)writeAttributeAcOverloadAlarmsMaskWithValue:(NSNumber * _Nonnull)value completion:(ZGMTRStatusCompletion)completion ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));
- (void)writeAttributeAcOverloadAlarmsMaskWithValue:(NSNumber * _Nonnull)value params:(ZGMTRWriteParams * _Nullable)params completion:(ZGMTRStatusCompletion)completion ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));
- (void)subscribeAttributeAcOverloadAlarmsMaskWithParams:(ZGMTRSubscribeParams *)params
                                 subscriptionEstablished:(ZGMTRSubscriptionEstablishedHandler _Nullable)subscriptionEstablished
                                           reportHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))reportHandler ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));
+ (void)readAttributeAcOverloadAlarmsMaskWithClusterStateCache:(ZGMTRClusterStateCacheContainer *)clusterStateCacheContainer endpoint:(NSNumber *)endpoint queue:(dispatch_queue_t)queue completion:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completion ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));

- (void)readAttributeAcVoltageOverloadWithCompletion:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completion ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));
- (void)subscribeAttributeAcVoltageOverloadWithParams:(ZGMTRSubscribeParams *)params
                              subscriptionEstablished:(ZGMTRSubscriptionEstablishedHandler _Nullable)subscriptionEstablished
                                        reportHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))reportHandler ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));
+ (void)readAttributeAcVoltageOverloadWithClusterStateCache:(ZGMTRClusterStateCacheContainer *)clusterStateCacheContainer endpoint:(NSNumber *)endpoint queue:(dispatch_queue_t)queue completion:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completion ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));

- (void)readAttributeAcCurrentOverloadWithCompletion:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completion ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));
- (void)subscribeAttributeAcCurrentOverloadWithParams:(ZGMTRSubscribeParams *)params
                              subscriptionEstablished:(ZGMTRSubscriptionEstablishedHandler _Nullable)subscriptionEstablished
                                        reportHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))reportHandler ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));
+ (void)readAttributeAcCurrentOverloadWithClusterStateCache:(ZGMTRClusterStateCacheContainer *)clusterStateCacheContainer endpoint:(NSNumber *)endpoint queue:(dispatch_queue_t)queue completion:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completion ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));

- (void)readAttributeAcActivePowerOverloadWithCompletion:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completion ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));
- (void)subscribeAttributeAcActivePowerOverloadWithParams:(ZGMTRSubscribeParams *)params
                                  subscriptionEstablished:(ZGMTRSubscriptionEstablishedHandler _Nullable)subscriptionEstablished
                                            reportHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))reportHandler ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));
+ (void)readAttributeAcActivePowerOverloadWithClusterStateCache:(ZGMTRClusterStateCacheContainer *)clusterStateCacheContainer endpoint:(NSNumber *)endpoint queue:(dispatch_queue_t)queue completion:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completion ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));

- (void)readAttributeAcReactivePowerOverloadWithCompletion:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completion ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));
- (void)subscribeAttributeAcReactivePowerOverloadWithParams:(ZGMTRSubscribeParams *)params
                                    subscriptionEstablished:(ZGMTRSubscriptionEstablishedHandler _Nullable)subscriptionEstablished
                                              reportHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))reportHandler ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));
+ (void)readAttributeAcReactivePowerOverloadWithClusterStateCache:(ZGMTRClusterStateCacheContainer *)clusterStateCacheContainer endpoint:(NSNumber *)endpoint queue:(dispatch_queue_t)queue completion:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completion ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));

- (void)readAttributeAverageRmsOverVoltageWithCompletion:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completion ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));
- (void)subscribeAttributeAverageRmsOverVoltageWithParams:(ZGMTRSubscribeParams *)params
                                  subscriptionEstablished:(ZGMTRSubscriptionEstablishedHandler _Nullable)subscriptionEstablished
                                            reportHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))reportHandler ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));
+ (void)readAttributeAverageRmsOverVoltageWithClusterStateCache:(ZGMTRClusterStateCacheContainer *)clusterStateCacheContainer endpoint:(NSNumber *)endpoint queue:(dispatch_queue_t)queue completion:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completion ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));

- (void)readAttributeAverageRmsUnderVoltageWithCompletion:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completion ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));
- (void)subscribeAttributeAverageRmsUnderVoltageWithParams:(ZGMTRSubscribeParams *)params
                                   subscriptionEstablished:(ZGMTRSubscriptionEstablishedHandler _Nullable)subscriptionEstablished
                                             reportHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))reportHandler ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));
+ (void)readAttributeAverageRmsUnderVoltageWithClusterStateCache:(ZGMTRClusterStateCacheContainer *)clusterStateCacheContainer endpoint:(NSNumber *)endpoint queue:(dispatch_queue_t)queue completion:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completion ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));

- (void)readAttributeRmsExtremeOverVoltageWithCompletion:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completion ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));
- (void)subscribeAttributeRmsExtremeOverVoltageWithParams:(ZGMTRSubscribeParams *)params
                                  subscriptionEstablished:(ZGMTRSubscriptionEstablishedHandler _Nullable)subscriptionEstablished
                                            reportHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))reportHandler ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));
+ (void)readAttributeRmsExtremeOverVoltageWithClusterStateCache:(ZGMTRClusterStateCacheContainer *)clusterStateCacheContainer endpoint:(NSNumber *)endpoint queue:(dispatch_queue_t)queue completion:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completion ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));

- (void)readAttributeRmsExtremeUnderVoltageWithCompletion:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completion ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));
- (void)subscribeAttributeRmsExtremeUnderVoltageWithParams:(ZGMTRSubscribeParams *)params
                                   subscriptionEstablished:(ZGMTRSubscriptionEstablishedHandler _Nullable)subscriptionEstablished
                                             reportHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))reportHandler ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));
+ (void)readAttributeRmsExtremeUnderVoltageWithClusterStateCache:(ZGMTRClusterStateCacheContainer *)clusterStateCacheContainer endpoint:(NSNumber *)endpoint queue:(dispatch_queue_t)queue completion:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completion ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));

- (void)readAttributeRmsVoltageSagWithCompletion:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completion ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));
- (void)subscribeAttributeRmsVoltageSagWithParams:(ZGMTRSubscribeParams *)params
                          subscriptionEstablished:(ZGMTRSubscriptionEstablishedHandler _Nullable)subscriptionEstablished
                                    reportHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))reportHandler ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));
+ (void)readAttributeRmsVoltageSagWithClusterStateCache:(ZGMTRClusterStateCacheContainer *)clusterStateCacheContainer endpoint:(NSNumber *)endpoint queue:(dispatch_queue_t)queue completion:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completion ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));

- (void)readAttributeRmsVoltageSwellWithCompletion:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completion ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));
- (void)subscribeAttributeRmsVoltageSwellWithParams:(ZGMTRSubscribeParams *)params
                            subscriptionEstablished:(ZGMTRSubscriptionEstablishedHandler _Nullable)subscriptionEstablished
                                      reportHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))reportHandler ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));
+ (void)readAttributeRmsVoltageSwellWithClusterStateCache:(ZGMTRClusterStateCacheContainer *)clusterStateCacheContainer endpoint:(NSNumber *)endpoint queue:(dispatch_queue_t)queue completion:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completion ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));

- (void)readAttributeLineCurrentPhaseBWithCompletion:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completion ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));
- (void)subscribeAttributeLineCurrentPhaseBWithParams:(ZGMTRSubscribeParams *)params
                              subscriptionEstablished:(ZGMTRSubscriptionEstablishedHandler _Nullable)subscriptionEstablished
                                        reportHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))reportHandler ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));
+ (void)readAttributeLineCurrentPhaseBWithClusterStateCache:(ZGMTRClusterStateCacheContainer *)clusterStateCacheContainer endpoint:(NSNumber *)endpoint queue:(dispatch_queue_t)queue completion:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completion ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));

- (void)readAttributeActiveCurrentPhaseBWithCompletion:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completion ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));
- (void)subscribeAttributeActiveCurrentPhaseBWithParams:(ZGMTRSubscribeParams *)params
                                subscriptionEstablished:(ZGMTRSubscriptionEstablishedHandler _Nullable)subscriptionEstablished
                                          reportHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))reportHandler ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));
+ (void)readAttributeActiveCurrentPhaseBWithClusterStateCache:(ZGMTRClusterStateCacheContainer *)clusterStateCacheContainer endpoint:(NSNumber *)endpoint queue:(dispatch_queue_t)queue completion:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completion ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));

- (void)readAttributeReactiveCurrentPhaseBWithCompletion:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completion ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));
- (void)subscribeAttributeReactiveCurrentPhaseBWithParams:(ZGMTRSubscribeParams *)params
                                  subscriptionEstablished:(ZGMTRSubscriptionEstablishedHandler _Nullable)subscriptionEstablished
                                            reportHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))reportHandler ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));
+ (void)readAttributeReactiveCurrentPhaseBWithClusterStateCache:(ZGMTRClusterStateCacheContainer *)clusterStateCacheContainer endpoint:(NSNumber *)endpoint queue:(dispatch_queue_t)queue completion:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completion ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));

- (void)readAttributeRmsVoltagePhaseBWithCompletion:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completion ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));
- (void)subscribeAttributeRmsVoltagePhaseBWithParams:(ZGMTRSubscribeParams *)params
                             subscriptionEstablished:(ZGMTRSubscriptionEstablishedHandler _Nullable)subscriptionEstablished
                                       reportHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))reportHandler ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));
+ (void)readAttributeRmsVoltagePhaseBWithClusterStateCache:(ZGMTRClusterStateCacheContainer *)clusterStateCacheContainer endpoint:(NSNumber *)endpoint queue:(dispatch_queue_t)queue completion:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completion ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));

- (void)readAttributeRmsVoltageMinPhaseBWithCompletion:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completion ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));
- (void)subscribeAttributeRmsVoltageMinPhaseBWithParams:(ZGMTRSubscribeParams *)params
                                subscriptionEstablished:(ZGMTRSubscriptionEstablishedHandler _Nullable)subscriptionEstablished
                                          reportHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))reportHandler ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));
+ (void)readAttributeRmsVoltageMinPhaseBWithClusterStateCache:(ZGMTRClusterStateCacheContainer *)clusterStateCacheContainer endpoint:(NSNumber *)endpoint queue:(dispatch_queue_t)queue completion:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completion ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));

- (void)readAttributeRmsVoltageMaxPhaseBWithCompletion:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completion ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));
- (void)subscribeAttributeRmsVoltageMaxPhaseBWithParams:(ZGMTRSubscribeParams *)params
                                subscriptionEstablished:(ZGMTRSubscriptionEstablishedHandler _Nullable)subscriptionEstablished
                                          reportHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))reportHandler ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));
+ (void)readAttributeRmsVoltageMaxPhaseBWithClusterStateCache:(ZGMTRClusterStateCacheContainer *)clusterStateCacheContainer endpoint:(NSNumber *)endpoint queue:(dispatch_queue_t)queue completion:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completion ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));

- (void)readAttributeRmsCurrentPhaseBWithCompletion:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completion ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));
- (void)subscribeAttributeRmsCurrentPhaseBWithParams:(ZGMTRSubscribeParams *)params
                             subscriptionEstablished:(ZGMTRSubscriptionEstablishedHandler _Nullable)subscriptionEstablished
                                       reportHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))reportHandler ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));
+ (void)readAttributeRmsCurrentPhaseBWithClusterStateCache:(ZGMTRClusterStateCacheContainer *)clusterStateCacheContainer endpoint:(NSNumber *)endpoint queue:(dispatch_queue_t)queue completion:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completion ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));

- (void)readAttributeRmsCurrentMinPhaseBWithCompletion:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completion ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));
- (void)subscribeAttributeRmsCurrentMinPhaseBWithParams:(ZGMTRSubscribeParams *)params
                                subscriptionEstablished:(ZGMTRSubscriptionEstablishedHandler _Nullable)subscriptionEstablished
                                          reportHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))reportHandler ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));
+ (void)readAttributeRmsCurrentMinPhaseBWithClusterStateCache:(ZGMTRClusterStateCacheContainer *)clusterStateCacheContainer endpoint:(NSNumber *)endpoint queue:(dispatch_queue_t)queue completion:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completion ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));

- (void)readAttributeRmsCurrentMaxPhaseBWithCompletion:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completion ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));
- (void)subscribeAttributeRmsCurrentMaxPhaseBWithParams:(ZGMTRSubscribeParams *)params
                                subscriptionEstablished:(ZGMTRSubscriptionEstablishedHandler _Nullable)subscriptionEstablished
                                          reportHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))reportHandler ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));
+ (void)readAttributeRmsCurrentMaxPhaseBWithClusterStateCache:(ZGMTRClusterStateCacheContainer *)clusterStateCacheContainer endpoint:(NSNumber *)endpoint queue:(dispatch_queue_t)queue completion:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completion ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));

- (void)readAttributeActivePowerPhaseBWithCompletion:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completion ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));
- (void)subscribeAttributeActivePowerPhaseBWithParams:(ZGMTRSubscribeParams *)params
                              subscriptionEstablished:(ZGMTRSubscriptionEstablishedHandler _Nullable)subscriptionEstablished
                                        reportHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))reportHandler ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));
+ (void)readAttributeActivePowerPhaseBWithClusterStateCache:(ZGMTRClusterStateCacheContainer *)clusterStateCacheContainer endpoint:(NSNumber *)endpoint queue:(dispatch_queue_t)queue completion:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completion ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));

- (void)readAttributeActivePowerMinPhaseBWithCompletion:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completion ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));
- (void)subscribeAttributeActivePowerMinPhaseBWithParams:(ZGMTRSubscribeParams *)params
                                 subscriptionEstablished:(ZGMTRSubscriptionEstablishedHandler _Nullable)subscriptionEstablished
                                           reportHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))reportHandler ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));
+ (void)readAttributeActivePowerMinPhaseBWithClusterStateCache:(ZGMTRClusterStateCacheContainer *)clusterStateCacheContainer endpoint:(NSNumber *)endpoint queue:(dispatch_queue_t)queue completion:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completion ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));

- (void)readAttributeActivePowerMaxPhaseBWithCompletion:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completion ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));
- (void)subscribeAttributeActivePowerMaxPhaseBWithParams:(ZGMTRSubscribeParams *)params
                                 subscriptionEstablished:(ZGMTRSubscriptionEstablishedHandler _Nullable)subscriptionEstablished
                                           reportHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))reportHandler ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));
+ (void)readAttributeActivePowerMaxPhaseBWithClusterStateCache:(ZGMTRClusterStateCacheContainer *)clusterStateCacheContainer endpoint:(NSNumber *)endpoint queue:(dispatch_queue_t)queue completion:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completion ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));

- (void)readAttributeReactivePowerPhaseBWithCompletion:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completion ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));
- (void)subscribeAttributeReactivePowerPhaseBWithParams:(ZGMTRSubscribeParams *)params
                                subscriptionEstablished:(ZGMTRSubscriptionEstablishedHandler _Nullable)subscriptionEstablished
                                          reportHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))reportHandler ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));
+ (void)readAttributeReactivePowerPhaseBWithClusterStateCache:(ZGMTRClusterStateCacheContainer *)clusterStateCacheContainer endpoint:(NSNumber *)endpoint queue:(dispatch_queue_t)queue completion:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completion ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));

- (void)readAttributeApparentPowerPhaseBWithCompletion:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completion ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));
- (void)subscribeAttributeApparentPowerPhaseBWithParams:(ZGMTRSubscribeParams *)params
                                subscriptionEstablished:(ZGMTRSubscriptionEstablishedHandler _Nullable)subscriptionEstablished
                                          reportHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))reportHandler ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));
+ (void)readAttributeApparentPowerPhaseBWithClusterStateCache:(ZGMTRClusterStateCacheContainer *)clusterStateCacheContainer endpoint:(NSNumber *)endpoint queue:(dispatch_queue_t)queue completion:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completion ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));

- (void)readAttributePowerFactorPhaseBWithCompletion:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completion ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));
- (void)subscribeAttributePowerFactorPhaseBWithParams:(ZGMTRSubscribeParams *)params
                              subscriptionEstablished:(ZGMTRSubscriptionEstablishedHandler _Nullable)subscriptionEstablished
                                        reportHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))reportHandler ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));
+ (void)readAttributePowerFactorPhaseBWithClusterStateCache:(ZGMTRClusterStateCacheContainer *)clusterStateCacheContainer endpoint:(NSNumber *)endpoint queue:(dispatch_queue_t)queue completion:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completion ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));

- (void)readAttributeAverageRmsVoltageMeasurementPeriodPhaseBWithCompletion:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completion ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));
- (void)subscribeAttributeAverageRmsVoltageMeasurementPeriodPhaseBWithParams:(ZGMTRSubscribeParams *)params
                                                     subscriptionEstablished:(ZGMTRSubscriptionEstablishedHandler _Nullable)subscriptionEstablished
                                                               reportHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))reportHandler ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));
+ (void)readAttributeAverageRmsVoltageMeasurementPeriodPhaseBWithClusterStateCache:(ZGMTRClusterStateCacheContainer *)clusterStateCacheContainer endpoint:(NSNumber *)endpoint queue:(dispatch_queue_t)queue completion:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completion ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));

- (void)readAttributeAverageRmsOverVoltageCounterPhaseBWithCompletion:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completion ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));
- (void)subscribeAttributeAverageRmsOverVoltageCounterPhaseBWithParams:(ZGMTRSubscribeParams *)params
                                               subscriptionEstablished:(ZGMTRSubscriptionEstablishedHandler _Nullable)subscriptionEstablished
                                                         reportHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))reportHandler ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));
+ (void)readAttributeAverageRmsOverVoltageCounterPhaseBWithClusterStateCache:(ZGMTRClusterStateCacheContainer *)clusterStateCacheContainer endpoint:(NSNumber *)endpoint queue:(dispatch_queue_t)queue completion:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completion ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));

- (void)readAttributeAverageRmsUnderVoltageCounterPhaseBWithCompletion:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completion ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));
- (void)subscribeAttributeAverageRmsUnderVoltageCounterPhaseBWithParams:(ZGMTRSubscribeParams *)params
                                                subscriptionEstablished:(ZGMTRSubscriptionEstablishedHandler _Nullable)subscriptionEstablished
                                                          reportHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))reportHandler ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));
+ (void)readAttributeAverageRmsUnderVoltageCounterPhaseBWithClusterStateCache:(ZGMTRClusterStateCacheContainer *)clusterStateCacheContainer endpoint:(NSNumber *)endpoint queue:(dispatch_queue_t)queue completion:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completion ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));

- (void)readAttributeRmsExtremeOverVoltagePeriodPhaseBWithCompletion:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completion ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));
- (void)subscribeAttributeRmsExtremeOverVoltagePeriodPhaseBWithParams:(ZGMTRSubscribeParams *)params
                                              subscriptionEstablished:(ZGMTRSubscriptionEstablishedHandler _Nullable)subscriptionEstablished
                                                        reportHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))reportHandler ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));
+ (void)readAttributeRmsExtremeOverVoltagePeriodPhaseBWithClusterStateCache:(ZGMTRClusterStateCacheContainer *)clusterStateCacheContainer endpoint:(NSNumber *)endpoint queue:(dispatch_queue_t)queue completion:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completion ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));

- (void)readAttributeRmsExtremeUnderVoltagePeriodPhaseBWithCompletion:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completion ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));
- (void)subscribeAttributeRmsExtremeUnderVoltagePeriodPhaseBWithParams:(ZGMTRSubscribeParams *)params
                                               subscriptionEstablished:(ZGMTRSubscriptionEstablishedHandler _Nullable)subscriptionEstablished
                                                         reportHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))reportHandler ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));
+ (void)readAttributeRmsExtremeUnderVoltagePeriodPhaseBWithClusterStateCache:(ZGMTRClusterStateCacheContainer *)clusterStateCacheContainer endpoint:(NSNumber *)endpoint queue:(dispatch_queue_t)queue completion:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completion ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));

- (void)readAttributeRmsVoltageSagPeriodPhaseBWithCompletion:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completion ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));
- (void)subscribeAttributeRmsVoltageSagPeriodPhaseBWithParams:(ZGMTRSubscribeParams *)params
                                      subscriptionEstablished:(ZGMTRSubscriptionEstablishedHandler _Nullable)subscriptionEstablished
                                                reportHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))reportHandler ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));
+ (void)readAttributeRmsVoltageSagPeriodPhaseBWithClusterStateCache:(ZGMTRClusterStateCacheContainer *)clusterStateCacheContainer endpoint:(NSNumber *)endpoint queue:(dispatch_queue_t)queue completion:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completion ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));

- (void)readAttributeRmsVoltageSwellPeriodPhaseBWithCompletion:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completion ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));
- (void)subscribeAttributeRmsVoltageSwellPeriodPhaseBWithParams:(ZGMTRSubscribeParams *)params
                                        subscriptionEstablished:(ZGMTRSubscriptionEstablishedHandler _Nullable)subscriptionEstablished
                                                  reportHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))reportHandler ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));
+ (void)readAttributeRmsVoltageSwellPeriodPhaseBWithClusterStateCache:(ZGMTRClusterStateCacheContainer *)clusterStateCacheContainer endpoint:(NSNumber *)endpoint queue:(dispatch_queue_t)queue completion:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completion ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));

- (void)readAttributeLineCurrentPhaseCWithCompletion:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completion ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));
- (void)subscribeAttributeLineCurrentPhaseCWithParams:(ZGMTRSubscribeParams *)params
                              subscriptionEstablished:(ZGMTRSubscriptionEstablishedHandler _Nullable)subscriptionEstablished
                                        reportHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))reportHandler ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));
+ (void)readAttributeLineCurrentPhaseCWithClusterStateCache:(ZGMTRClusterStateCacheContainer *)clusterStateCacheContainer endpoint:(NSNumber *)endpoint queue:(dispatch_queue_t)queue completion:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completion ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));

- (void)readAttributeActiveCurrentPhaseCWithCompletion:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completion ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));
- (void)subscribeAttributeActiveCurrentPhaseCWithParams:(ZGMTRSubscribeParams *)params
                                subscriptionEstablished:(ZGMTRSubscriptionEstablishedHandler _Nullable)subscriptionEstablished
                                          reportHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))reportHandler ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));
+ (void)readAttributeActiveCurrentPhaseCWithClusterStateCache:(ZGMTRClusterStateCacheContainer *)clusterStateCacheContainer endpoint:(NSNumber *)endpoint queue:(dispatch_queue_t)queue completion:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completion ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));

- (void)readAttributeReactiveCurrentPhaseCWithCompletion:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completion ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));
- (void)subscribeAttributeReactiveCurrentPhaseCWithParams:(ZGMTRSubscribeParams *)params
                                  subscriptionEstablished:(ZGMTRSubscriptionEstablishedHandler _Nullable)subscriptionEstablished
                                            reportHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))reportHandler ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));
+ (void)readAttributeReactiveCurrentPhaseCWithClusterStateCache:(ZGMTRClusterStateCacheContainer *)clusterStateCacheContainer endpoint:(NSNumber *)endpoint queue:(dispatch_queue_t)queue completion:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completion ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));

- (void)readAttributeRmsVoltagePhaseCWithCompletion:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completion ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));
- (void)subscribeAttributeRmsVoltagePhaseCWithParams:(ZGMTRSubscribeParams *)params
                             subscriptionEstablished:(ZGMTRSubscriptionEstablishedHandler _Nullable)subscriptionEstablished
                                       reportHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))reportHandler ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));
+ (void)readAttributeRmsVoltagePhaseCWithClusterStateCache:(ZGMTRClusterStateCacheContainer *)clusterStateCacheContainer endpoint:(NSNumber *)endpoint queue:(dispatch_queue_t)queue completion:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completion ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));

- (void)readAttributeRmsVoltageMinPhaseCWithCompletion:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completion ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));
- (void)subscribeAttributeRmsVoltageMinPhaseCWithParams:(ZGMTRSubscribeParams *)params
                                subscriptionEstablished:(ZGMTRSubscriptionEstablishedHandler _Nullable)subscriptionEstablished
                                          reportHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))reportHandler ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));
+ (void)readAttributeRmsVoltageMinPhaseCWithClusterStateCache:(ZGMTRClusterStateCacheContainer *)clusterStateCacheContainer endpoint:(NSNumber *)endpoint queue:(dispatch_queue_t)queue completion:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completion ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));

- (void)readAttributeRmsVoltageMaxPhaseCWithCompletion:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completion ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));
- (void)subscribeAttributeRmsVoltageMaxPhaseCWithParams:(ZGMTRSubscribeParams *)params
                                subscriptionEstablished:(ZGMTRSubscriptionEstablishedHandler _Nullable)subscriptionEstablished
                                          reportHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))reportHandler ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));
+ (void)readAttributeRmsVoltageMaxPhaseCWithClusterStateCache:(ZGMTRClusterStateCacheContainer *)clusterStateCacheContainer endpoint:(NSNumber *)endpoint queue:(dispatch_queue_t)queue completion:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completion ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));

- (void)readAttributeRmsCurrentPhaseCWithCompletion:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completion ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));
- (void)subscribeAttributeRmsCurrentPhaseCWithParams:(ZGMTRSubscribeParams *)params
                             subscriptionEstablished:(ZGMTRSubscriptionEstablishedHandler _Nullable)subscriptionEstablished
                                       reportHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))reportHandler ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));
+ (void)readAttributeRmsCurrentPhaseCWithClusterStateCache:(ZGMTRClusterStateCacheContainer *)clusterStateCacheContainer endpoint:(NSNumber *)endpoint queue:(dispatch_queue_t)queue completion:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completion ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));

- (void)readAttributeRmsCurrentMinPhaseCWithCompletion:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completion ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));
- (void)subscribeAttributeRmsCurrentMinPhaseCWithParams:(ZGMTRSubscribeParams *)params
                                subscriptionEstablished:(ZGMTRSubscriptionEstablishedHandler _Nullable)subscriptionEstablished
                                          reportHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))reportHandler ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));
+ (void)readAttributeRmsCurrentMinPhaseCWithClusterStateCache:(ZGMTRClusterStateCacheContainer *)clusterStateCacheContainer endpoint:(NSNumber *)endpoint queue:(dispatch_queue_t)queue completion:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completion ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));

- (void)readAttributeRmsCurrentMaxPhaseCWithCompletion:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completion ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));
- (void)subscribeAttributeRmsCurrentMaxPhaseCWithParams:(ZGMTRSubscribeParams *)params
                                subscriptionEstablished:(ZGMTRSubscriptionEstablishedHandler _Nullable)subscriptionEstablished
                                          reportHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))reportHandler ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));
+ (void)readAttributeRmsCurrentMaxPhaseCWithClusterStateCache:(ZGMTRClusterStateCacheContainer *)clusterStateCacheContainer endpoint:(NSNumber *)endpoint queue:(dispatch_queue_t)queue completion:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completion ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));

- (void)readAttributeActivePowerPhaseCWithCompletion:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completion ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));
- (void)subscribeAttributeActivePowerPhaseCWithParams:(ZGMTRSubscribeParams *)params
                              subscriptionEstablished:(ZGMTRSubscriptionEstablishedHandler _Nullable)subscriptionEstablished
                                        reportHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))reportHandler ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));
+ (void)readAttributeActivePowerPhaseCWithClusterStateCache:(ZGMTRClusterStateCacheContainer *)clusterStateCacheContainer endpoint:(NSNumber *)endpoint queue:(dispatch_queue_t)queue completion:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completion ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));

- (void)readAttributeActivePowerMinPhaseCWithCompletion:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completion ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));
- (void)subscribeAttributeActivePowerMinPhaseCWithParams:(ZGMTRSubscribeParams *)params
                                 subscriptionEstablished:(ZGMTRSubscriptionEstablishedHandler _Nullable)subscriptionEstablished
                                           reportHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))reportHandler ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));
+ (void)readAttributeActivePowerMinPhaseCWithClusterStateCache:(ZGMTRClusterStateCacheContainer *)clusterStateCacheContainer endpoint:(NSNumber *)endpoint queue:(dispatch_queue_t)queue completion:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completion ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));

- (void)readAttributeActivePowerMaxPhaseCWithCompletion:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completion ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));
- (void)subscribeAttributeActivePowerMaxPhaseCWithParams:(ZGMTRSubscribeParams *)params
                                 subscriptionEstablished:(ZGMTRSubscriptionEstablishedHandler _Nullable)subscriptionEstablished
                                           reportHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))reportHandler ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));
+ (void)readAttributeActivePowerMaxPhaseCWithClusterStateCache:(ZGMTRClusterStateCacheContainer *)clusterStateCacheContainer endpoint:(NSNumber *)endpoint queue:(dispatch_queue_t)queue completion:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completion ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));

- (void)readAttributeReactivePowerPhaseCWithCompletion:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completion ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));
- (void)subscribeAttributeReactivePowerPhaseCWithParams:(ZGMTRSubscribeParams *)params
                                subscriptionEstablished:(ZGMTRSubscriptionEstablishedHandler _Nullable)subscriptionEstablished
                                          reportHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))reportHandler ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));
+ (void)readAttributeReactivePowerPhaseCWithClusterStateCache:(ZGMTRClusterStateCacheContainer *)clusterStateCacheContainer endpoint:(NSNumber *)endpoint queue:(dispatch_queue_t)queue completion:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completion ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));

- (void)readAttributeApparentPowerPhaseCWithCompletion:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completion ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));
- (void)subscribeAttributeApparentPowerPhaseCWithParams:(ZGMTRSubscribeParams *)params
                                subscriptionEstablished:(ZGMTRSubscriptionEstablishedHandler _Nullable)subscriptionEstablished
                                          reportHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))reportHandler ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));
+ (void)readAttributeApparentPowerPhaseCWithClusterStateCache:(ZGMTRClusterStateCacheContainer *)clusterStateCacheContainer endpoint:(NSNumber *)endpoint queue:(dispatch_queue_t)queue completion:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completion ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));

- (void)readAttributePowerFactorPhaseCWithCompletion:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completion ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));
- (void)subscribeAttributePowerFactorPhaseCWithParams:(ZGMTRSubscribeParams *)params
                              subscriptionEstablished:(ZGMTRSubscriptionEstablishedHandler _Nullable)subscriptionEstablished
                                        reportHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))reportHandler ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));
+ (void)readAttributePowerFactorPhaseCWithClusterStateCache:(ZGMTRClusterStateCacheContainer *)clusterStateCacheContainer endpoint:(NSNumber *)endpoint queue:(dispatch_queue_t)queue completion:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completion ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));

- (void)readAttributeAverageRmsVoltageMeasurementPeriodPhaseCWithCompletion:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completion ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));
- (void)subscribeAttributeAverageRmsVoltageMeasurementPeriodPhaseCWithParams:(ZGMTRSubscribeParams *)params
                                                     subscriptionEstablished:(ZGMTRSubscriptionEstablishedHandler _Nullable)subscriptionEstablished
                                                               reportHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))reportHandler ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));
+ (void)readAttributeAverageRmsVoltageMeasurementPeriodPhaseCWithClusterStateCache:(ZGMTRClusterStateCacheContainer *)clusterStateCacheContainer endpoint:(NSNumber *)endpoint queue:(dispatch_queue_t)queue completion:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completion ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));

- (void)readAttributeAverageRmsOverVoltageCounterPhaseCWithCompletion:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completion ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));
- (void)subscribeAttributeAverageRmsOverVoltageCounterPhaseCWithParams:(ZGMTRSubscribeParams *)params
                                               subscriptionEstablished:(ZGMTRSubscriptionEstablishedHandler _Nullable)subscriptionEstablished
                                                         reportHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))reportHandler ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));
+ (void)readAttributeAverageRmsOverVoltageCounterPhaseCWithClusterStateCache:(ZGMTRClusterStateCacheContainer *)clusterStateCacheContainer endpoint:(NSNumber *)endpoint queue:(dispatch_queue_t)queue completion:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completion ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));

- (void)readAttributeAverageRmsUnderVoltageCounterPhaseCWithCompletion:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completion ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));
- (void)subscribeAttributeAverageRmsUnderVoltageCounterPhaseCWithParams:(ZGMTRSubscribeParams *)params
                                                subscriptionEstablished:(ZGMTRSubscriptionEstablishedHandler _Nullable)subscriptionEstablished
                                                          reportHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))reportHandler ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));
+ (void)readAttributeAverageRmsUnderVoltageCounterPhaseCWithClusterStateCache:(ZGMTRClusterStateCacheContainer *)clusterStateCacheContainer endpoint:(NSNumber *)endpoint queue:(dispatch_queue_t)queue completion:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completion ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));

- (void)readAttributeRmsExtremeOverVoltagePeriodPhaseCWithCompletion:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completion ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));
- (void)subscribeAttributeRmsExtremeOverVoltagePeriodPhaseCWithParams:(ZGMTRSubscribeParams *)params
                                              subscriptionEstablished:(ZGMTRSubscriptionEstablishedHandler _Nullable)subscriptionEstablished
                                                        reportHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))reportHandler ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));
+ (void)readAttributeRmsExtremeOverVoltagePeriodPhaseCWithClusterStateCache:(ZGMTRClusterStateCacheContainer *)clusterStateCacheContainer endpoint:(NSNumber *)endpoint queue:(dispatch_queue_t)queue completion:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completion ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));

- (void)readAttributeRmsExtremeUnderVoltagePeriodPhaseCWithCompletion:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completion ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));
- (void)subscribeAttributeRmsExtremeUnderVoltagePeriodPhaseCWithParams:(ZGMTRSubscribeParams *)params
                                               subscriptionEstablished:(ZGMTRSubscriptionEstablishedHandler _Nullable)subscriptionEstablished
                                                         reportHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))reportHandler ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));
+ (void)readAttributeRmsExtremeUnderVoltagePeriodPhaseCWithClusterStateCache:(ZGMTRClusterStateCacheContainer *)clusterStateCacheContainer endpoint:(NSNumber *)endpoint queue:(dispatch_queue_t)queue completion:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completion ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));

- (void)readAttributeRmsVoltageSagPeriodPhaseCWithCompletion:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completion ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));
- (void)subscribeAttributeRmsVoltageSagPeriodPhaseCWithParams:(ZGMTRSubscribeParams *)params
                                      subscriptionEstablished:(ZGMTRSubscriptionEstablishedHandler _Nullable)subscriptionEstablished
                                                reportHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))reportHandler ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));
+ (void)readAttributeRmsVoltageSagPeriodPhaseCWithClusterStateCache:(ZGMTRClusterStateCacheContainer *)clusterStateCacheContainer endpoint:(NSNumber *)endpoint queue:(dispatch_queue_t)queue completion:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completion ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));

- (void)readAttributeRmsVoltageSwellPeriodPhaseCWithCompletion:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completion ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));
- (void)subscribeAttributeRmsVoltageSwellPeriodPhaseCWithParams:(ZGMTRSubscribeParams *)params
                                        subscriptionEstablished:(ZGMTRSubscriptionEstablishedHandler _Nullable)subscriptionEstablished
                                                  reportHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))reportHandler ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));
+ (void)readAttributeRmsVoltageSwellPeriodPhaseCWithClusterStateCache:(ZGMTRClusterStateCacheContainer *)clusterStateCacheContainer endpoint:(NSNumber *)endpoint queue:(dispatch_queue_t)queue completion:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completion ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));

- (void)readAttributeGeneratedCommandListWithCompletion:(void (^)(NSArray * _Nullable value, NSError * _Nullable error))completion ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));
- (void)subscribeAttributeGeneratedCommandListWithParams:(ZGMTRSubscribeParams *)params
                                 subscriptionEstablished:(ZGMTRSubscriptionEstablishedHandler _Nullable)subscriptionEstablished
                                           reportHandler:(void (^)(NSArray * _Nullable value, NSError * _Nullable error))reportHandler ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));
+ (void)readAttributeGeneratedCommandListWithClusterStateCache:(ZGMTRClusterStateCacheContainer *)clusterStateCacheContainer endpoint:(NSNumber *)endpoint queue:(dispatch_queue_t)queue completion:(void (^)(NSArray * _Nullable value, NSError * _Nullable error))completion ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));

- (void)readAttributeAcceptedCommandListWithCompletion:(void (^)(NSArray * _Nullable value, NSError * _Nullable error))completion ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));
- (void)subscribeAttributeAcceptedCommandListWithParams:(ZGMTRSubscribeParams *)params
                                subscriptionEstablished:(ZGMTRSubscriptionEstablishedHandler _Nullable)subscriptionEstablished
                                          reportHandler:(void (^)(NSArray * _Nullable value, NSError * _Nullable error))reportHandler ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));
+ (void)readAttributeAcceptedCommandListWithClusterStateCache:(ZGMTRClusterStateCacheContainer *)clusterStateCacheContainer endpoint:(NSNumber *)endpoint queue:(dispatch_queue_t)queue completion:(void (^)(NSArray * _Nullable value, NSError * _Nullable error))completion ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));

- (void)readAttributeAttributeListWithCompletion:(void (^)(NSArray * _Nullable value, NSError * _Nullable error))completion ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));
- (void)subscribeAttributeAttributeListWithParams:(ZGMTRSubscribeParams *)params
                          subscriptionEstablished:(ZGMTRSubscriptionEstablishedHandler _Nullable)subscriptionEstablished
                                    reportHandler:(void (^)(NSArray * _Nullable value, NSError * _Nullable error))reportHandler ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));
+ (void)readAttributeAttributeListWithClusterStateCache:(ZGMTRClusterStateCacheContainer *)clusterStateCacheContainer endpoint:(NSNumber *)endpoint queue:(dispatch_queue_t)queue completion:(void (^)(NSArray * _Nullable value, NSError * _Nullable error))completion ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));

- (void)readAttributeFeatureMapWithCompletion:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completion ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));
- (void)subscribeAttributeFeatureMapWithParams:(ZGMTRSubscribeParams *)params
                       subscriptionEstablished:(ZGMTRSubscriptionEstablishedHandler _Nullable)subscriptionEstablished
                                 reportHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))reportHandler ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));
+ (void)readAttributeFeatureMapWithClusterStateCache:(ZGMTRClusterStateCacheContainer *)clusterStateCacheContainer endpoint:(NSNumber *)endpoint queue:(dispatch_queue_t)queue completion:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completion ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));

- (void)readAttributeClusterRevisionWithCompletion:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completion ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));
- (void)subscribeAttributeClusterRevisionWithParams:(ZGMTRSubscribeParams *)params
                            subscriptionEstablished:(ZGMTRSubscriptionEstablishedHandler _Nullable)subscriptionEstablished
                                      reportHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))reportHandler ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));
+ (void)readAttributeClusterRevisionWithClusterStateCache:(ZGMTRClusterStateCacheContainer *)clusterStateCacheContainer endpoint:(NSNumber *)endpoint queue:(dispatch_queue_t)queue completion:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completion ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end

@interface ZGMTRBaseClusterElectricalMeasurement (Availability)

/**
 * For all instance methods (reads, writes, commands) that take a completion,
 * the completion will be called on the provided queue.
 */
- (instancetype _Nullable)initWithDevice:(ZGMTRBaseDevice *)device
                              endpointID:(NSNumber *)endpointID
                                   queue:(dispatch_queue_t)queue ZGMTR_DEPRECATED("ElectricalMeasurement is deprecated and will be removed", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));

@end

@interface ZGMTRBaseClusterElectricalMeasurement (Deprecated)

- (nullable instancetype)initWithDevice:(ZGMTRBaseDevice *)device
                               endpoint:(uint16_t)endpoint
                                  queue:(dispatch_queue_t)queue ZGMTR_DEPRECATED("Please use initWithDevice:endpointID:queue:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));

- (void)getProfileInfoCommandWithParams:(ZGMTRElectricalMeasurementClusterGetProfileInfoCommandParams * _Nullable)params completionHandler:(ZGMTRStatusCompletion)completionHandler
    ZGMTR_DEPRECATED("Please use getProfileInfoCommandWithParams:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (void)getProfileInfoCommandWithCompletionHandler:(ZGMTRStatusCompletion)completionHandler
    ZGMTR_DEPRECATED("Please use getProfileInfoCommandWithCompletion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (void)getMeasurementProfileCommandWithParams:(ZGMTRElectricalMeasurementClusterGetMeasurementProfileCommandParams *)params completionHandler:(ZGMTRStatusCompletion)completionHandler
    ZGMTR_DEPRECATED("Please use getMeasurementProfileCommandWithParams:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));

- (void)readAttributeMeasurementTypeWithCompletionHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completionHandler ZGMTR_DEPRECATED("Please use readAttributeMeasurementTypeWithCompletion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (void)subscribeAttributeMeasurementTypeWithMinInterval:(NSNumber * _Nonnull)minInterval maxInterval:(NSNumber * _Nonnull)maxInterval
                                                  params:(ZGMTRSubscribeParams * _Nullable)params
                                 subscriptionEstablished:(ZGMTRSubscriptionEstablishedHandler _Nullable)subscriptionEstablishedHandler
                                           reportHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))reportHandler ZGMTR_DEPRECATED("Please use subscribeAttributeMeasurementTypeWithParams:subscriptionEstablished:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
+ (void)readAttributeMeasurementTypeWithAttributeCache:(ZGMTRAttributeCacheContainer *)attributeCacheContainer endpoint:(NSNumber *)endpoint queue:(dispatch_queue_t)queue completionHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completionHandler ZGMTR_DEPRECATED("Please use readAttributeMeasurementTypeWithAttributeCache:endpoint:queue:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));

- (void)readAttributeDcVoltageWithCompletionHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completionHandler ZGMTR_DEPRECATED("Please use readAttributeDcVoltageWithCompletion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (void)subscribeAttributeDcVoltageWithMinInterval:(NSNumber * _Nonnull)minInterval maxInterval:(NSNumber * _Nonnull)maxInterval
                                            params:(ZGMTRSubscribeParams * _Nullable)params
                           subscriptionEstablished:(ZGMTRSubscriptionEstablishedHandler _Nullable)subscriptionEstablishedHandler
                                     reportHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))reportHandler ZGMTR_DEPRECATED("Please use subscribeAttributeDcVoltageWithParams:subscriptionEstablished:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
+ (void)readAttributeDcVoltageWithAttributeCache:(ZGMTRAttributeCacheContainer *)attributeCacheContainer endpoint:(NSNumber *)endpoint queue:(dispatch_queue_t)queue completionHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completionHandler ZGMTR_DEPRECATED("Please use readAttributeDcVoltageWithAttributeCache:endpoint:queue:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));

- (void)readAttributeDcVoltageMinWithCompletionHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completionHandler ZGMTR_DEPRECATED("Please use readAttributeDcVoltageMinWithCompletion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (void)subscribeAttributeDcVoltageMinWithMinInterval:(NSNumber * _Nonnull)minInterval maxInterval:(NSNumber * _Nonnull)maxInterval
                                               params:(ZGMTRSubscribeParams * _Nullable)params
                              subscriptionEstablished:(ZGMTRSubscriptionEstablishedHandler _Nullable)subscriptionEstablishedHandler
                                        reportHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))reportHandler ZGMTR_DEPRECATED("Please use subscribeAttributeDcVoltageMinWithParams:subscriptionEstablished:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
+ (void)readAttributeDcVoltageMinWithAttributeCache:(ZGMTRAttributeCacheContainer *)attributeCacheContainer endpoint:(NSNumber *)endpoint queue:(dispatch_queue_t)queue completionHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completionHandler ZGMTR_DEPRECATED("Please use readAttributeDcVoltageMinWithAttributeCache:endpoint:queue:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));

- (void)readAttributeDcVoltageMaxWithCompletionHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completionHandler ZGMTR_DEPRECATED("Please use readAttributeDcVoltageMaxWithCompletion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (void)subscribeAttributeDcVoltageMaxWithMinInterval:(NSNumber * _Nonnull)minInterval maxInterval:(NSNumber * _Nonnull)maxInterval
                                               params:(ZGMTRSubscribeParams * _Nullable)params
                              subscriptionEstablished:(ZGMTRSubscriptionEstablishedHandler _Nullable)subscriptionEstablishedHandler
                                        reportHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))reportHandler ZGMTR_DEPRECATED("Please use subscribeAttributeDcVoltageMaxWithParams:subscriptionEstablished:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
+ (void)readAttributeDcVoltageMaxWithAttributeCache:(ZGMTRAttributeCacheContainer *)attributeCacheContainer endpoint:(NSNumber *)endpoint queue:(dispatch_queue_t)queue completionHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completionHandler ZGMTR_DEPRECATED("Please use readAttributeDcVoltageMaxWithAttributeCache:endpoint:queue:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));

- (void)readAttributeDcCurrentWithCompletionHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completionHandler ZGMTR_DEPRECATED("Please use readAttributeDcCurrentWithCompletion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (void)subscribeAttributeDcCurrentWithMinInterval:(NSNumber * _Nonnull)minInterval maxInterval:(NSNumber * _Nonnull)maxInterval
                                            params:(ZGMTRSubscribeParams * _Nullable)params
                           subscriptionEstablished:(ZGMTRSubscriptionEstablishedHandler _Nullable)subscriptionEstablishedHandler
                                     reportHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))reportHandler ZGMTR_DEPRECATED("Please use subscribeAttributeDcCurrentWithParams:subscriptionEstablished:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
+ (void)readAttributeDcCurrentWithAttributeCache:(ZGMTRAttributeCacheContainer *)attributeCacheContainer endpoint:(NSNumber *)endpoint queue:(dispatch_queue_t)queue completionHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completionHandler ZGMTR_DEPRECATED("Please use readAttributeDcCurrentWithAttributeCache:endpoint:queue:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));

- (void)readAttributeDcCurrentMinWithCompletionHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completionHandler ZGMTR_DEPRECATED("Please use readAttributeDcCurrentMinWithCompletion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (void)subscribeAttributeDcCurrentMinWithMinInterval:(NSNumber * _Nonnull)minInterval maxInterval:(NSNumber * _Nonnull)maxInterval
                                               params:(ZGMTRSubscribeParams * _Nullable)params
                              subscriptionEstablished:(ZGMTRSubscriptionEstablishedHandler _Nullable)subscriptionEstablishedHandler
                                        reportHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))reportHandler ZGMTR_DEPRECATED("Please use subscribeAttributeDcCurrentMinWithParams:subscriptionEstablished:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
+ (void)readAttributeDcCurrentMinWithAttributeCache:(ZGMTRAttributeCacheContainer *)attributeCacheContainer endpoint:(NSNumber *)endpoint queue:(dispatch_queue_t)queue completionHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completionHandler ZGMTR_DEPRECATED("Please use readAttributeDcCurrentMinWithAttributeCache:endpoint:queue:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));

- (void)readAttributeDcCurrentMaxWithCompletionHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completionHandler ZGMTR_DEPRECATED("Please use readAttributeDcCurrentMaxWithCompletion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (void)subscribeAttributeDcCurrentMaxWithMinInterval:(NSNumber * _Nonnull)minInterval maxInterval:(NSNumber * _Nonnull)maxInterval
                                               params:(ZGMTRSubscribeParams * _Nullable)params
                              subscriptionEstablished:(ZGMTRSubscriptionEstablishedHandler _Nullable)subscriptionEstablishedHandler
                                        reportHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))reportHandler ZGMTR_DEPRECATED("Please use subscribeAttributeDcCurrentMaxWithParams:subscriptionEstablished:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
+ (void)readAttributeDcCurrentMaxWithAttributeCache:(ZGMTRAttributeCacheContainer *)attributeCacheContainer endpoint:(NSNumber *)endpoint queue:(dispatch_queue_t)queue completionHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completionHandler ZGMTR_DEPRECATED("Please use readAttributeDcCurrentMaxWithAttributeCache:endpoint:queue:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));

- (void)readAttributeDcPowerWithCompletionHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completionHandler ZGMTR_DEPRECATED("Please use readAttributeDcPowerWithCompletion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (void)subscribeAttributeDcPowerWithMinInterval:(NSNumber * _Nonnull)minInterval maxInterval:(NSNumber * _Nonnull)maxInterval
                                          params:(ZGMTRSubscribeParams * _Nullable)params
                         subscriptionEstablished:(ZGMTRSubscriptionEstablishedHandler _Nullable)subscriptionEstablishedHandler
                                   reportHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))reportHandler ZGMTR_DEPRECATED("Please use subscribeAttributeDcPowerWithParams:subscriptionEstablished:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
+ (void)readAttributeDcPowerWithAttributeCache:(ZGMTRAttributeCacheContainer *)attributeCacheContainer endpoint:(NSNumber *)endpoint queue:(dispatch_queue_t)queue completionHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completionHandler ZGMTR_DEPRECATED("Please use readAttributeDcPowerWithAttributeCache:endpoint:queue:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));

- (void)readAttributeDcPowerMinWithCompletionHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completionHandler ZGMTR_DEPRECATED("Please use readAttributeDcPowerMinWithCompletion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (void)subscribeAttributeDcPowerMinWithMinInterval:(NSNumber * _Nonnull)minInterval maxInterval:(NSNumber * _Nonnull)maxInterval
                                             params:(ZGMTRSubscribeParams * _Nullable)params
                            subscriptionEstablished:(ZGMTRSubscriptionEstablishedHandler _Nullable)subscriptionEstablishedHandler
                                      reportHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))reportHandler ZGMTR_DEPRECATED("Please use subscribeAttributeDcPowerMinWithParams:subscriptionEstablished:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
+ (void)readAttributeDcPowerMinWithAttributeCache:(ZGMTRAttributeCacheContainer *)attributeCacheContainer endpoint:(NSNumber *)endpoint queue:(dispatch_queue_t)queue completionHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completionHandler ZGMTR_DEPRECATED("Please use readAttributeDcPowerMinWithAttributeCache:endpoint:queue:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));

- (void)readAttributeDcPowerMaxWithCompletionHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completionHandler ZGMTR_DEPRECATED("Please use readAttributeDcPowerMaxWithCompletion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (void)subscribeAttributeDcPowerMaxWithMinInterval:(NSNumber * _Nonnull)minInterval maxInterval:(NSNumber * _Nonnull)maxInterval
                                             params:(ZGMTRSubscribeParams * _Nullable)params
                            subscriptionEstablished:(ZGMTRSubscriptionEstablishedHandler _Nullable)subscriptionEstablishedHandler
                                      reportHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))reportHandler ZGMTR_DEPRECATED("Please use subscribeAttributeDcPowerMaxWithParams:subscriptionEstablished:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
+ (void)readAttributeDcPowerMaxWithAttributeCache:(ZGMTRAttributeCacheContainer *)attributeCacheContainer endpoint:(NSNumber *)endpoint queue:(dispatch_queue_t)queue completionHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completionHandler ZGMTR_DEPRECATED("Please use readAttributeDcPowerMaxWithAttributeCache:endpoint:queue:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));

- (void)readAttributeDcVoltageMultiplierWithCompletionHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completionHandler ZGMTR_DEPRECATED("Please use readAttributeDcVoltageMultiplierWithCompletion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (void)subscribeAttributeDcVoltageMultiplierWithMinInterval:(NSNumber * _Nonnull)minInterval maxInterval:(NSNumber * _Nonnull)maxInterval
                                                      params:(ZGMTRSubscribeParams * _Nullable)params
                                     subscriptionEstablished:(ZGMTRSubscriptionEstablishedHandler _Nullable)subscriptionEstablishedHandler
                                               reportHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))reportHandler ZGMTR_DEPRECATED("Please use subscribeAttributeDcVoltageMultiplierWithParams:subscriptionEstablished:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
+ (void)readAttributeDcVoltageMultiplierWithAttributeCache:(ZGMTRAttributeCacheContainer *)attributeCacheContainer endpoint:(NSNumber *)endpoint queue:(dispatch_queue_t)queue completionHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completionHandler ZGMTR_DEPRECATED("Please use readAttributeDcVoltageMultiplierWithAttributeCache:endpoint:queue:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));

- (void)readAttributeDcVoltageDivisorWithCompletionHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completionHandler ZGMTR_DEPRECATED("Please use readAttributeDcVoltageDivisorWithCompletion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (void)subscribeAttributeDcVoltageDivisorWithMinInterval:(NSNumber * _Nonnull)minInterval maxInterval:(NSNumber * _Nonnull)maxInterval
                                                   params:(ZGMTRSubscribeParams * _Nullable)params
                                  subscriptionEstablished:(ZGMTRSubscriptionEstablishedHandler _Nullable)subscriptionEstablishedHandler
                                            reportHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))reportHandler ZGMTR_DEPRECATED("Please use subscribeAttributeDcVoltageDivisorWithParams:subscriptionEstablished:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
+ (void)readAttributeDcVoltageDivisorWithAttributeCache:(ZGMTRAttributeCacheContainer *)attributeCacheContainer endpoint:(NSNumber *)endpoint queue:(dispatch_queue_t)queue completionHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completionHandler ZGMTR_DEPRECATED("Please use readAttributeDcVoltageDivisorWithAttributeCache:endpoint:queue:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));

- (void)readAttributeDcCurrentMultiplierWithCompletionHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completionHandler ZGMTR_DEPRECATED("Please use readAttributeDcCurrentMultiplierWithCompletion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (void)subscribeAttributeDcCurrentMultiplierWithMinInterval:(NSNumber * _Nonnull)minInterval maxInterval:(NSNumber * _Nonnull)maxInterval
                                                      params:(ZGMTRSubscribeParams * _Nullable)params
                                     subscriptionEstablished:(ZGMTRSubscriptionEstablishedHandler _Nullable)subscriptionEstablishedHandler
                                               reportHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))reportHandler ZGMTR_DEPRECATED("Please use subscribeAttributeDcCurrentMultiplierWithParams:subscriptionEstablished:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
+ (void)readAttributeDcCurrentMultiplierWithAttributeCache:(ZGMTRAttributeCacheContainer *)attributeCacheContainer endpoint:(NSNumber *)endpoint queue:(dispatch_queue_t)queue completionHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completionHandler ZGMTR_DEPRECATED("Please use readAttributeDcCurrentMultiplierWithAttributeCache:endpoint:queue:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));

- (void)readAttributeDcCurrentDivisorWithCompletionHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completionHandler ZGMTR_DEPRECATED("Please use readAttributeDcCurrentDivisorWithCompletion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (void)subscribeAttributeDcCurrentDivisorWithMinInterval:(NSNumber * _Nonnull)minInterval maxInterval:(NSNumber * _Nonnull)maxInterval
                                                   params:(ZGMTRSubscribeParams * _Nullable)params
                                  subscriptionEstablished:(ZGMTRSubscriptionEstablishedHandler _Nullable)subscriptionEstablishedHandler
                                            reportHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))reportHandler ZGMTR_DEPRECATED("Please use subscribeAttributeDcCurrentDivisorWithParams:subscriptionEstablished:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
+ (void)readAttributeDcCurrentDivisorWithAttributeCache:(ZGMTRAttributeCacheContainer *)attributeCacheContainer endpoint:(NSNumber *)endpoint queue:(dispatch_queue_t)queue completionHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completionHandler ZGMTR_DEPRECATED("Please use readAttributeDcCurrentDivisorWithAttributeCache:endpoint:queue:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));

- (void)readAttributeDcPowerMultiplierWithCompletionHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completionHandler ZGMTR_DEPRECATED("Please use readAttributeDcPowerMultiplierWithCompletion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (void)subscribeAttributeDcPowerMultiplierWithMinInterval:(NSNumber * _Nonnull)minInterval maxInterval:(NSNumber * _Nonnull)maxInterval
                                                    params:(ZGMTRSubscribeParams * _Nullable)params
                                   subscriptionEstablished:(ZGMTRSubscriptionEstablishedHandler _Nullable)subscriptionEstablishedHandler
                                             reportHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))reportHandler ZGMTR_DEPRECATED("Please use subscribeAttributeDcPowerMultiplierWithParams:subscriptionEstablished:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
+ (void)readAttributeDcPowerMultiplierWithAttributeCache:(ZGMTRAttributeCacheContainer *)attributeCacheContainer endpoint:(NSNumber *)endpoint queue:(dispatch_queue_t)queue completionHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completionHandler ZGMTR_DEPRECATED("Please use readAttributeDcPowerMultiplierWithAttributeCache:endpoint:queue:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));

- (void)readAttributeDcPowerDivisorWithCompletionHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completionHandler ZGMTR_DEPRECATED("Please use readAttributeDcPowerDivisorWithCompletion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (void)subscribeAttributeDcPowerDivisorWithMinInterval:(NSNumber * _Nonnull)minInterval maxInterval:(NSNumber * _Nonnull)maxInterval
                                                 params:(ZGMTRSubscribeParams * _Nullable)params
                                subscriptionEstablished:(ZGMTRSubscriptionEstablishedHandler _Nullable)subscriptionEstablishedHandler
                                          reportHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))reportHandler ZGMTR_DEPRECATED("Please use subscribeAttributeDcPowerDivisorWithParams:subscriptionEstablished:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
+ (void)readAttributeDcPowerDivisorWithAttributeCache:(ZGMTRAttributeCacheContainer *)attributeCacheContainer endpoint:(NSNumber *)endpoint queue:(dispatch_queue_t)queue completionHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completionHandler ZGMTR_DEPRECATED("Please use readAttributeDcPowerDivisorWithAttributeCache:endpoint:queue:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));

- (void)readAttributeAcFrequencyWithCompletionHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completionHandler ZGMTR_DEPRECATED("Please use readAttributeAcFrequencyWithCompletion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (void)subscribeAttributeAcFrequencyWithMinInterval:(NSNumber * _Nonnull)minInterval maxInterval:(NSNumber * _Nonnull)maxInterval
                                              params:(ZGMTRSubscribeParams * _Nullable)params
                             subscriptionEstablished:(ZGMTRSubscriptionEstablishedHandler _Nullable)subscriptionEstablishedHandler
                                       reportHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))reportHandler ZGMTR_DEPRECATED("Please use subscribeAttributeAcFrequencyWithParams:subscriptionEstablished:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
+ (void)readAttributeAcFrequencyWithAttributeCache:(ZGMTRAttributeCacheContainer *)attributeCacheContainer endpoint:(NSNumber *)endpoint queue:(dispatch_queue_t)queue completionHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completionHandler ZGMTR_DEPRECATED("Please use readAttributeAcFrequencyWithAttributeCache:endpoint:queue:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));

- (void)readAttributeAcFrequencyMinWithCompletionHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completionHandler ZGMTR_DEPRECATED("Please use readAttributeAcFrequencyMinWithCompletion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (void)subscribeAttributeAcFrequencyMinWithMinInterval:(NSNumber * _Nonnull)minInterval maxInterval:(NSNumber * _Nonnull)maxInterval
                                                 params:(ZGMTRSubscribeParams * _Nullable)params
                                subscriptionEstablished:(ZGMTRSubscriptionEstablishedHandler _Nullable)subscriptionEstablishedHandler
                                          reportHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))reportHandler ZGMTR_DEPRECATED("Please use subscribeAttributeAcFrequencyMinWithParams:subscriptionEstablished:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
+ (void)readAttributeAcFrequencyMinWithAttributeCache:(ZGMTRAttributeCacheContainer *)attributeCacheContainer endpoint:(NSNumber *)endpoint queue:(dispatch_queue_t)queue completionHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completionHandler ZGMTR_DEPRECATED("Please use readAttributeAcFrequencyMinWithAttributeCache:endpoint:queue:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));

- (void)readAttributeAcFrequencyMaxWithCompletionHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completionHandler ZGMTR_DEPRECATED("Please use readAttributeAcFrequencyMaxWithCompletion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (void)subscribeAttributeAcFrequencyMaxWithMinInterval:(NSNumber * _Nonnull)minInterval maxInterval:(NSNumber * _Nonnull)maxInterval
                                                 params:(ZGMTRSubscribeParams * _Nullable)params
                                subscriptionEstablished:(ZGMTRSubscriptionEstablishedHandler _Nullable)subscriptionEstablishedHandler
                                          reportHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))reportHandler ZGMTR_DEPRECATED("Please use subscribeAttributeAcFrequencyMaxWithParams:subscriptionEstablished:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
+ (void)readAttributeAcFrequencyMaxWithAttributeCache:(ZGMTRAttributeCacheContainer *)attributeCacheContainer endpoint:(NSNumber *)endpoint queue:(dispatch_queue_t)queue completionHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completionHandler ZGMTR_DEPRECATED("Please use readAttributeAcFrequencyMaxWithAttributeCache:endpoint:queue:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));

- (void)readAttributeNeutralCurrentWithCompletionHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completionHandler ZGMTR_DEPRECATED("Please use readAttributeNeutralCurrentWithCompletion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (void)subscribeAttributeNeutralCurrentWithMinInterval:(NSNumber * _Nonnull)minInterval maxInterval:(NSNumber * _Nonnull)maxInterval
                                                 params:(ZGMTRSubscribeParams * _Nullable)params
                                subscriptionEstablished:(ZGMTRSubscriptionEstablishedHandler _Nullable)subscriptionEstablishedHandler
                                          reportHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))reportHandler ZGMTR_DEPRECATED("Please use subscribeAttributeNeutralCurrentWithParams:subscriptionEstablished:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
+ (void)readAttributeNeutralCurrentWithAttributeCache:(ZGMTRAttributeCacheContainer *)attributeCacheContainer endpoint:(NSNumber *)endpoint queue:(dispatch_queue_t)queue completionHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completionHandler ZGMTR_DEPRECATED("Please use readAttributeNeutralCurrentWithAttributeCache:endpoint:queue:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));

- (void)readAttributeTotalActivePowerWithCompletionHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completionHandler ZGMTR_DEPRECATED("Please use readAttributeTotalActivePowerWithCompletion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (void)subscribeAttributeTotalActivePowerWithMinInterval:(NSNumber * _Nonnull)minInterval maxInterval:(NSNumber * _Nonnull)maxInterval
                                                   params:(ZGMTRSubscribeParams * _Nullable)params
                                  subscriptionEstablished:(ZGMTRSubscriptionEstablishedHandler _Nullable)subscriptionEstablishedHandler
                                            reportHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))reportHandler ZGMTR_DEPRECATED("Please use subscribeAttributeTotalActivePowerWithParams:subscriptionEstablished:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
+ (void)readAttributeTotalActivePowerWithAttributeCache:(ZGMTRAttributeCacheContainer *)attributeCacheContainer endpoint:(NSNumber *)endpoint queue:(dispatch_queue_t)queue completionHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completionHandler ZGMTR_DEPRECATED("Please use readAttributeTotalActivePowerWithAttributeCache:endpoint:queue:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));

- (void)readAttributeTotalReactivePowerWithCompletionHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completionHandler ZGMTR_DEPRECATED("Please use readAttributeTotalReactivePowerWithCompletion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (void)subscribeAttributeTotalReactivePowerWithMinInterval:(NSNumber * _Nonnull)minInterval maxInterval:(NSNumber * _Nonnull)maxInterval
                                                     params:(ZGMTRSubscribeParams * _Nullable)params
                                    subscriptionEstablished:(ZGMTRSubscriptionEstablishedHandler _Nullable)subscriptionEstablishedHandler
                                              reportHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))reportHandler ZGMTR_DEPRECATED("Please use subscribeAttributeTotalReactivePowerWithParams:subscriptionEstablished:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
+ (void)readAttributeTotalReactivePowerWithAttributeCache:(ZGMTRAttributeCacheContainer *)attributeCacheContainer endpoint:(NSNumber *)endpoint queue:(dispatch_queue_t)queue completionHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completionHandler ZGMTR_DEPRECATED("Please use readAttributeTotalReactivePowerWithAttributeCache:endpoint:queue:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));

- (void)readAttributeTotalApparentPowerWithCompletionHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completionHandler ZGMTR_DEPRECATED("Please use readAttributeTotalApparentPowerWithCompletion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (void)subscribeAttributeTotalApparentPowerWithMinInterval:(NSNumber * _Nonnull)minInterval maxInterval:(NSNumber * _Nonnull)maxInterval
                                                     params:(ZGMTRSubscribeParams * _Nullable)params
                                    subscriptionEstablished:(ZGMTRSubscriptionEstablishedHandler _Nullable)subscriptionEstablishedHandler
                                              reportHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))reportHandler ZGMTR_DEPRECATED("Please use subscribeAttributeTotalApparentPowerWithParams:subscriptionEstablished:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
+ (void)readAttributeTotalApparentPowerWithAttributeCache:(ZGMTRAttributeCacheContainer *)attributeCacheContainer endpoint:(NSNumber *)endpoint queue:(dispatch_queue_t)queue completionHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completionHandler ZGMTR_DEPRECATED("Please use readAttributeTotalApparentPowerWithAttributeCache:endpoint:queue:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));

- (void)readAttributeMeasured1stHarmonicCurrentWithCompletionHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completionHandler ZGMTR_DEPRECATED("Please use readAttributeMeasured1stHarmonicCurrentWithCompletion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (void)subscribeAttributeMeasured1stHarmonicCurrentWithMinInterval:(NSNumber * _Nonnull)minInterval maxInterval:(NSNumber * _Nonnull)maxInterval
                                                             params:(ZGMTRSubscribeParams * _Nullable)params
                                            subscriptionEstablished:(ZGMTRSubscriptionEstablishedHandler _Nullable)subscriptionEstablishedHandler
                                                      reportHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))reportHandler ZGMTR_DEPRECATED("Please use subscribeAttributeMeasured1stHarmonicCurrentWithParams:subscriptionEstablished:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
+ (void)readAttributeMeasured1stHarmonicCurrentWithAttributeCache:(ZGMTRAttributeCacheContainer *)attributeCacheContainer endpoint:(NSNumber *)endpoint queue:(dispatch_queue_t)queue completionHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completionHandler ZGMTR_DEPRECATED("Please use readAttributeMeasured1stHarmonicCurrentWithAttributeCache:endpoint:queue:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));

- (void)readAttributeMeasured3rdHarmonicCurrentWithCompletionHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completionHandler ZGMTR_DEPRECATED("Please use readAttributeMeasured3rdHarmonicCurrentWithCompletion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (void)subscribeAttributeMeasured3rdHarmonicCurrentWithMinInterval:(NSNumber * _Nonnull)minInterval maxInterval:(NSNumber * _Nonnull)maxInterval
                                                             params:(ZGMTRSubscribeParams * _Nullable)params
                                            subscriptionEstablished:(ZGMTRSubscriptionEstablishedHandler _Nullable)subscriptionEstablishedHandler
                                                      reportHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))reportHandler ZGMTR_DEPRECATED("Please use subscribeAttributeMeasured3rdHarmonicCurrentWithParams:subscriptionEstablished:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
+ (void)readAttributeMeasured3rdHarmonicCurrentWithAttributeCache:(ZGMTRAttributeCacheContainer *)attributeCacheContainer endpoint:(NSNumber *)endpoint queue:(dispatch_queue_t)queue completionHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completionHandler ZGMTR_DEPRECATED("Please use readAttributeMeasured3rdHarmonicCurrentWithAttributeCache:endpoint:queue:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));

- (void)readAttributeMeasured5thHarmonicCurrentWithCompletionHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completionHandler ZGMTR_DEPRECATED("Please use readAttributeMeasured5thHarmonicCurrentWithCompletion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (void)subscribeAttributeMeasured5thHarmonicCurrentWithMinInterval:(NSNumber * _Nonnull)minInterval maxInterval:(NSNumber * _Nonnull)maxInterval
                                                             params:(ZGMTRSubscribeParams * _Nullable)params
                                            subscriptionEstablished:(ZGMTRSubscriptionEstablishedHandler _Nullable)subscriptionEstablishedHandler
                                                      reportHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))reportHandler ZGMTR_DEPRECATED("Please use subscribeAttributeMeasured5thHarmonicCurrentWithParams:subscriptionEstablished:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
+ (void)readAttributeMeasured5thHarmonicCurrentWithAttributeCache:(ZGMTRAttributeCacheContainer *)attributeCacheContainer endpoint:(NSNumber *)endpoint queue:(dispatch_queue_t)queue completionHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completionHandler ZGMTR_DEPRECATED("Please use readAttributeMeasured5thHarmonicCurrentWithAttributeCache:endpoint:queue:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));

- (void)readAttributeMeasured7thHarmonicCurrentWithCompletionHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completionHandler ZGMTR_DEPRECATED("Please use readAttributeMeasured7thHarmonicCurrentWithCompletion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (void)subscribeAttributeMeasured7thHarmonicCurrentWithMinInterval:(NSNumber * _Nonnull)minInterval maxInterval:(NSNumber * _Nonnull)maxInterval
                                                             params:(ZGMTRSubscribeParams * _Nullable)params
                                            subscriptionEstablished:(ZGMTRSubscriptionEstablishedHandler _Nullable)subscriptionEstablishedHandler
                                                      reportHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))reportHandler ZGMTR_DEPRECATED("Please use subscribeAttributeMeasured7thHarmonicCurrentWithParams:subscriptionEstablished:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
+ (void)readAttributeMeasured7thHarmonicCurrentWithAttributeCache:(ZGMTRAttributeCacheContainer *)attributeCacheContainer endpoint:(NSNumber *)endpoint queue:(dispatch_queue_t)queue completionHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completionHandler ZGMTR_DEPRECATED("Please use readAttributeMeasured7thHarmonicCurrentWithAttributeCache:endpoint:queue:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));

- (void)readAttributeMeasured9thHarmonicCurrentWithCompletionHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completionHandler ZGMTR_DEPRECATED("Please use readAttributeMeasured9thHarmonicCurrentWithCompletion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (void)subscribeAttributeMeasured9thHarmonicCurrentWithMinInterval:(NSNumber * _Nonnull)minInterval maxInterval:(NSNumber * _Nonnull)maxInterval
                                                             params:(ZGMTRSubscribeParams * _Nullable)params
                                            subscriptionEstablished:(ZGMTRSubscriptionEstablishedHandler _Nullable)subscriptionEstablishedHandler
                                                      reportHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))reportHandler ZGMTR_DEPRECATED("Please use subscribeAttributeMeasured9thHarmonicCurrentWithParams:subscriptionEstablished:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
+ (void)readAttributeMeasured9thHarmonicCurrentWithAttributeCache:(ZGMTRAttributeCacheContainer *)attributeCacheContainer endpoint:(NSNumber *)endpoint queue:(dispatch_queue_t)queue completionHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completionHandler ZGMTR_DEPRECATED("Please use readAttributeMeasured9thHarmonicCurrentWithAttributeCache:endpoint:queue:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));

- (void)readAttributeMeasured11thHarmonicCurrentWithCompletionHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completionHandler ZGMTR_DEPRECATED("Please use readAttributeMeasured11thHarmonicCurrentWithCompletion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (void)subscribeAttributeMeasured11thHarmonicCurrentWithMinInterval:(NSNumber * _Nonnull)minInterval maxInterval:(NSNumber * _Nonnull)maxInterval
                                                              params:(ZGMTRSubscribeParams * _Nullable)params
                                             subscriptionEstablished:(ZGMTRSubscriptionEstablishedHandler _Nullable)subscriptionEstablishedHandler
                                                       reportHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))reportHandler ZGMTR_DEPRECATED("Please use subscribeAttributeMeasured11thHarmonicCurrentWithParams:subscriptionEstablished:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
+ (void)readAttributeMeasured11thHarmonicCurrentWithAttributeCache:(ZGMTRAttributeCacheContainer *)attributeCacheContainer endpoint:(NSNumber *)endpoint queue:(dispatch_queue_t)queue completionHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completionHandler ZGMTR_DEPRECATED("Please use readAttributeMeasured11thHarmonicCurrentWithAttributeCache:endpoint:queue:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));

- (void)readAttributeMeasuredPhase1stHarmonicCurrentWithCompletionHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completionHandler ZGMTR_DEPRECATED("Please use readAttributeMeasuredPhase1stHarmonicCurrentWithCompletion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (void)subscribeAttributeMeasuredPhase1stHarmonicCurrentWithMinInterval:(NSNumber * _Nonnull)minInterval maxInterval:(NSNumber * _Nonnull)maxInterval
                                                                  params:(ZGMTRSubscribeParams * _Nullable)params
                                                 subscriptionEstablished:(ZGMTRSubscriptionEstablishedHandler _Nullable)subscriptionEstablishedHandler
                                                           reportHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))reportHandler ZGMTR_DEPRECATED("Please use subscribeAttributeMeasuredPhase1stHarmonicCurrentWithParams:subscriptionEstablished:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
+ (void)readAttributeMeasuredPhase1stHarmonicCurrentWithAttributeCache:(ZGMTRAttributeCacheContainer *)attributeCacheContainer endpoint:(NSNumber *)endpoint queue:(dispatch_queue_t)queue completionHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completionHandler ZGMTR_DEPRECATED("Please use readAttributeMeasuredPhase1stHarmonicCurrentWithAttributeCache:endpoint:queue:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));

- (void)readAttributeMeasuredPhase3rdHarmonicCurrentWithCompletionHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completionHandler ZGMTR_DEPRECATED("Please use readAttributeMeasuredPhase3rdHarmonicCurrentWithCompletion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (void)subscribeAttributeMeasuredPhase3rdHarmonicCurrentWithMinInterval:(NSNumber * _Nonnull)minInterval maxInterval:(NSNumber * _Nonnull)maxInterval
                                                                  params:(ZGMTRSubscribeParams * _Nullable)params
                                                 subscriptionEstablished:(ZGMTRSubscriptionEstablishedHandler _Nullable)subscriptionEstablishedHandler
                                                           reportHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))reportHandler ZGMTR_DEPRECATED("Please use subscribeAttributeMeasuredPhase3rdHarmonicCurrentWithParams:subscriptionEstablished:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
+ (void)readAttributeMeasuredPhase3rdHarmonicCurrentWithAttributeCache:(ZGMTRAttributeCacheContainer *)attributeCacheContainer endpoint:(NSNumber *)endpoint queue:(dispatch_queue_t)queue completionHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completionHandler ZGMTR_DEPRECATED("Please use readAttributeMeasuredPhase3rdHarmonicCurrentWithAttributeCache:endpoint:queue:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));

- (void)readAttributeMeasuredPhase5thHarmonicCurrentWithCompletionHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completionHandler ZGMTR_DEPRECATED("Please use readAttributeMeasuredPhase5thHarmonicCurrentWithCompletion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (void)subscribeAttributeMeasuredPhase5thHarmonicCurrentWithMinInterval:(NSNumber * _Nonnull)minInterval maxInterval:(NSNumber * _Nonnull)maxInterval
                                                                  params:(ZGMTRSubscribeParams * _Nullable)params
                                                 subscriptionEstablished:(ZGMTRSubscriptionEstablishedHandler _Nullable)subscriptionEstablishedHandler
                                                           reportHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))reportHandler ZGMTR_DEPRECATED("Please use subscribeAttributeMeasuredPhase5thHarmonicCurrentWithParams:subscriptionEstablished:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
+ (void)readAttributeMeasuredPhase5thHarmonicCurrentWithAttributeCache:(ZGMTRAttributeCacheContainer *)attributeCacheContainer endpoint:(NSNumber *)endpoint queue:(dispatch_queue_t)queue completionHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completionHandler ZGMTR_DEPRECATED("Please use readAttributeMeasuredPhase5thHarmonicCurrentWithAttributeCache:endpoint:queue:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));

- (void)readAttributeMeasuredPhase7thHarmonicCurrentWithCompletionHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completionHandler ZGMTR_DEPRECATED("Please use readAttributeMeasuredPhase7thHarmonicCurrentWithCompletion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (void)subscribeAttributeMeasuredPhase7thHarmonicCurrentWithMinInterval:(NSNumber * _Nonnull)minInterval maxInterval:(NSNumber * _Nonnull)maxInterval
                                                                  params:(ZGMTRSubscribeParams * _Nullable)params
                                                 subscriptionEstablished:(ZGMTRSubscriptionEstablishedHandler _Nullable)subscriptionEstablishedHandler
                                                           reportHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))reportHandler ZGMTR_DEPRECATED("Please use subscribeAttributeMeasuredPhase7thHarmonicCurrentWithParams:subscriptionEstablished:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
+ (void)readAttributeMeasuredPhase7thHarmonicCurrentWithAttributeCache:(ZGMTRAttributeCacheContainer *)attributeCacheContainer endpoint:(NSNumber *)endpoint queue:(dispatch_queue_t)queue completionHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completionHandler ZGMTR_DEPRECATED("Please use readAttributeMeasuredPhase7thHarmonicCurrentWithAttributeCache:endpoint:queue:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));

- (void)readAttributeMeasuredPhase9thHarmonicCurrentWithCompletionHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completionHandler ZGMTR_DEPRECATED("Please use readAttributeMeasuredPhase9thHarmonicCurrentWithCompletion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (void)subscribeAttributeMeasuredPhase9thHarmonicCurrentWithMinInterval:(NSNumber * _Nonnull)minInterval maxInterval:(NSNumber * _Nonnull)maxInterval
                                                                  params:(ZGMTRSubscribeParams * _Nullable)params
                                                 subscriptionEstablished:(ZGMTRSubscriptionEstablishedHandler _Nullable)subscriptionEstablishedHandler
                                                           reportHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))reportHandler ZGMTR_DEPRECATED("Please use subscribeAttributeMeasuredPhase9thHarmonicCurrentWithParams:subscriptionEstablished:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
+ (void)readAttributeMeasuredPhase9thHarmonicCurrentWithAttributeCache:(ZGMTRAttributeCacheContainer *)attributeCacheContainer endpoint:(NSNumber *)endpoint queue:(dispatch_queue_t)queue completionHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completionHandler ZGMTR_DEPRECATED("Please use readAttributeMeasuredPhase9thHarmonicCurrentWithAttributeCache:endpoint:queue:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));

- (void)readAttributeMeasuredPhase11thHarmonicCurrentWithCompletionHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completionHandler ZGMTR_DEPRECATED("Please use readAttributeMeasuredPhase11thHarmonicCurrentWithCompletion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (void)subscribeAttributeMeasuredPhase11thHarmonicCurrentWithMinInterval:(NSNumber * _Nonnull)minInterval maxInterval:(NSNumber * _Nonnull)maxInterval
                                                                   params:(ZGMTRSubscribeParams * _Nullable)params
                                                  subscriptionEstablished:(ZGMTRSubscriptionEstablishedHandler _Nullable)subscriptionEstablishedHandler
                                                            reportHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))reportHandler ZGMTR_DEPRECATED("Please use subscribeAttributeMeasuredPhase11thHarmonicCurrentWithParams:subscriptionEstablished:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
+ (void)readAttributeMeasuredPhase11thHarmonicCurrentWithAttributeCache:(ZGMTRAttributeCacheContainer *)attributeCacheContainer endpoint:(NSNumber *)endpoint queue:(dispatch_queue_t)queue completionHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completionHandler ZGMTR_DEPRECATED("Please use readAttributeMeasuredPhase11thHarmonicCurrentWithAttributeCache:endpoint:queue:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));

- (void)readAttributeAcFrequencyMultiplierWithCompletionHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completionHandler ZGMTR_DEPRECATED("Please use readAttributeAcFrequencyMultiplierWithCompletion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (void)subscribeAttributeAcFrequencyMultiplierWithMinInterval:(NSNumber * _Nonnull)minInterval maxInterval:(NSNumber * _Nonnull)maxInterval
                                                        params:(ZGMTRSubscribeParams * _Nullable)params
                                       subscriptionEstablished:(ZGMTRSubscriptionEstablishedHandler _Nullable)subscriptionEstablishedHandler
                                                 reportHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))reportHandler ZGMTR_DEPRECATED("Please use subscribeAttributeAcFrequencyMultiplierWithParams:subscriptionEstablished:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
+ (void)readAttributeAcFrequencyMultiplierWithAttributeCache:(ZGMTRAttributeCacheContainer *)attributeCacheContainer endpoint:(NSNumber *)endpoint queue:(dispatch_queue_t)queue completionHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completionHandler ZGMTR_DEPRECATED("Please use readAttributeAcFrequencyMultiplierWithAttributeCache:endpoint:queue:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));

- (void)readAttributeAcFrequencyDivisorWithCompletionHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completionHandler ZGMTR_DEPRECATED("Please use readAttributeAcFrequencyDivisorWithCompletion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (void)subscribeAttributeAcFrequencyDivisorWithMinInterval:(NSNumber * _Nonnull)minInterval maxInterval:(NSNumber * _Nonnull)maxInterval
                                                     params:(ZGMTRSubscribeParams * _Nullable)params
                                    subscriptionEstablished:(ZGMTRSubscriptionEstablishedHandler _Nullable)subscriptionEstablishedHandler
                                              reportHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))reportHandler ZGMTR_DEPRECATED("Please use subscribeAttributeAcFrequencyDivisorWithParams:subscriptionEstablished:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
+ (void)readAttributeAcFrequencyDivisorWithAttributeCache:(ZGMTRAttributeCacheContainer *)attributeCacheContainer endpoint:(NSNumber *)endpoint queue:(dispatch_queue_t)queue completionHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completionHandler ZGMTR_DEPRECATED("Please use readAttributeAcFrequencyDivisorWithAttributeCache:endpoint:queue:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));

- (void)readAttributePowerMultiplierWithCompletionHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completionHandler ZGMTR_DEPRECATED("Please use readAttributePowerMultiplierWithCompletion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (void)subscribeAttributePowerMultiplierWithMinInterval:(NSNumber * _Nonnull)minInterval maxInterval:(NSNumber * _Nonnull)maxInterval
                                                  params:(ZGMTRSubscribeParams * _Nullable)params
                                 subscriptionEstablished:(ZGMTRSubscriptionEstablishedHandler _Nullable)subscriptionEstablishedHandler
                                           reportHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))reportHandler ZGMTR_DEPRECATED("Please use subscribeAttributePowerMultiplierWithParams:subscriptionEstablished:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
+ (void)readAttributePowerMultiplierWithAttributeCache:(ZGMTRAttributeCacheContainer *)attributeCacheContainer endpoint:(NSNumber *)endpoint queue:(dispatch_queue_t)queue completionHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completionHandler ZGMTR_DEPRECATED("Please use readAttributePowerMultiplierWithAttributeCache:endpoint:queue:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));

- (void)readAttributePowerDivisorWithCompletionHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completionHandler ZGMTR_DEPRECATED("Please use readAttributePowerDivisorWithCompletion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (void)subscribeAttributePowerDivisorWithMinInterval:(NSNumber * _Nonnull)minInterval maxInterval:(NSNumber * _Nonnull)maxInterval
                                               params:(ZGMTRSubscribeParams * _Nullable)params
                              subscriptionEstablished:(ZGMTRSubscriptionEstablishedHandler _Nullable)subscriptionEstablishedHandler
                                        reportHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))reportHandler ZGMTR_DEPRECATED("Please use subscribeAttributePowerDivisorWithParams:subscriptionEstablished:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
+ (void)readAttributePowerDivisorWithAttributeCache:(ZGMTRAttributeCacheContainer *)attributeCacheContainer endpoint:(NSNumber *)endpoint queue:(dispatch_queue_t)queue completionHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completionHandler ZGMTR_DEPRECATED("Please use readAttributePowerDivisorWithAttributeCache:endpoint:queue:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));

- (void)readAttributeHarmonicCurrentMultiplierWithCompletionHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completionHandler ZGMTR_DEPRECATED("Please use readAttributeHarmonicCurrentMultiplierWithCompletion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (void)subscribeAttributeHarmonicCurrentMultiplierWithMinInterval:(NSNumber * _Nonnull)minInterval maxInterval:(NSNumber * _Nonnull)maxInterval
                                                            params:(ZGMTRSubscribeParams * _Nullable)params
                                           subscriptionEstablished:(ZGMTRSubscriptionEstablishedHandler _Nullable)subscriptionEstablishedHandler
                                                     reportHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))reportHandler ZGMTR_DEPRECATED("Please use subscribeAttributeHarmonicCurrentMultiplierWithParams:subscriptionEstablished:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
+ (void)readAttributeHarmonicCurrentMultiplierWithAttributeCache:(ZGMTRAttributeCacheContainer *)attributeCacheContainer endpoint:(NSNumber *)endpoint queue:(dispatch_queue_t)queue completionHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completionHandler ZGMTR_DEPRECATED("Please use readAttributeHarmonicCurrentMultiplierWithAttributeCache:endpoint:queue:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));

- (void)readAttributePhaseHarmonicCurrentMultiplierWithCompletionHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completionHandler ZGMTR_DEPRECATED("Please use readAttributePhaseHarmonicCurrentMultiplierWithCompletion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (void)subscribeAttributePhaseHarmonicCurrentMultiplierWithMinInterval:(NSNumber * _Nonnull)minInterval maxInterval:(NSNumber * _Nonnull)maxInterval
                                                                 params:(ZGMTRSubscribeParams * _Nullable)params
                                                subscriptionEstablished:(ZGMTRSubscriptionEstablishedHandler _Nullable)subscriptionEstablishedHandler
                                                          reportHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))reportHandler ZGMTR_DEPRECATED("Please use subscribeAttributePhaseHarmonicCurrentMultiplierWithParams:subscriptionEstablished:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
+ (void)readAttributePhaseHarmonicCurrentMultiplierWithAttributeCache:(ZGMTRAttributeCacheContainer *)attributeCacheContainer endpoint:(NSNumber *)endpoint queue:(dispatch_queue_t)queue completionHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completionHandler ZGMTR_DEPRECATED("Please use readAttributePhaseHarmonicCurrentMultiplierWithAttributeCache:endpoint:queue:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));

- (void)readAttributeInstantaneousVoltageWithCompletionHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completionHandler ZGMTR_DEPRECATED("Please use readAttributeInstantaneousVoltageWithCompletion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (void)subscribeAttributeInstantaneousVoltageWithMinInterval:(NSNumber * _Nonnull)minInterval maxInterval:(NSNumber * _Nonnull)maxInterval
                                                       params:(ZGMTRSubscribeParams * _Nullable)params
                                      subscriptionEstablished:(ZGMTRSubscriptionEstablishedHandler _Nullable)subscriptionEstablishedHandler
                                                reportHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))reportHandler ZGMTR_DEPRECATED("Please use subscribeAttributeInstantaneousVoltageWithParams:subscriptionEstablished:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
+ (void)readAttributeInstantaneousVoltageWithAttributeCache:(ZGMTRAttributeCacheContainer *)attributeCacheContainer endpoint:(NSNumber *)endpoint queue:(dispatch_queue_t)queue completionHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completionHandler ZGMTR_DEPRECATED("Please use readAttributeInstantaneousVoltageWithAttributeCache:endpoint:queue:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));

- (void)readAttributeInstantaneousLineCurrentWithCompletionHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completionHandler ZGMTR_DEPRECATED("Please use readAttributeInstantaneousLineCurrentWithCompletion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (void)subscribeAttributeInstantaneousLineCurrentWithMinInterval:(NSNumber * _Nonnull)minInterval maxInterval:(NSNumber * _Nonnull)maxInterval
                                                           params:(ZGMTRSubscribeParams * _Nullable)params
                                          subscriptionEstablished:(ZGMTRSubscriptionEstablishedHandler _Nullable)subscriptionEstablishedHandler
                                                    reportHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))reportHandler ZGMTR_DEPRECATED("Please use subscribeAttributeInstantaneousLineCurrentWithParams:subscriptionEstablished:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
+ (void)readAttributeInstantaneousLineCurrentWithAttributeCache:(ZGMTRAttributeCacheContainer *)attributeCacheContainer endpoint:(NSNumber *)endpoint queue:(dispatch_queue_t)queue completionHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completionHandler ZGMTR_DEPRECATED("Please use readAttributeInstantaneousLineCurrentWithAttributeCache:endpoint:queue:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));

- (void)readAttributeInstantaneousActiveCurrentWithCompletionHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completionHandler ZGMTR_DEPRECATED("Please use readAttributeInstantaneousActiveCurrentWithCompletion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (void)subscribeAttributeInstantaneousActiveCurrentWithMinInterval:(NSNumber * _Nonnull)minInterval maxInterval:(NSNumber * _Nonnull)maxInterval
                                                             params:(ZGMTRSubscribeParams * _Nullable)params
                                            subscriptionEstablished:(ZGMTRSubscriptionEstablishedHandler _Nullable)subscriptionEstablishedHandler
                                                      reportHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))reportHandler ZGMTR_DEPRECATED("Please use subscribeAttributeInstantaneousActiveCurrentWithParams:subscriptionEstablished:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
+ (void)readAttributeInstantaneousActiveCurrentWithAttributeCache:(ZGMTRAttributeCacheContainer *)attributeCacheContainer endpoint:(NSNumber *)endpoint queue:(dispatch_queue_t)queue completionHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completionHandler ZGMTR_DEPRECATED("Please use readAttributeInstantaneousActiveCurrentWithAttributeCache:endpoint:queue:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));

- (void)readAttributeInstantaneousReactiveCurrentWithCompletionHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completionHandler ZGMTR_DEPRECATED("Please use readAttributeInstantaneousReactiveCurrentWithCompletion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (void)subscribeAttributeInstantaneousReactiveCurrentWithMinInterval:(NSNumber * _Nonnull)minInterval maxInterval:(NSNumber * _Nonnull)maxInterval
                                                               params:(ZGMTRSubscribeParams * _Nullable)params
                                              subscriptionEstablished:(ZGMTRSubscriptionEstablishedHandler _Nullable)subscriptionEstablishedHandler
                                                        reportHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))reportHandler ZGMTR_DEPRECATED("Please use subscribeAttributeInstantaneousReactiveCurrentWithParams:subscriptionEstablished:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
+ (void)readAttributeInstantaneousReactiveCurrentWithAttributeCache:(ZGMTRAttributeCacheContainer *)attributeCacheContainer endpoint:(NSNumber *)endpoint queue:(dispatch_queue_t)queue completionHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completionHandler ZGMTR_DEPRECATED("Please use readAttributeInstantaneousReactiveCurrentWithAttributeCache:endpoint:queue:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));

- (void)readAttributeInstantaneousPowerWithCompletionHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completionHandler ZGMTR_DEPRECATED("Please use readAttributeInstantaneousPowerWithCompletion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (void)subscribeAttributeInstantaneousPowerWithMinInterval:(NSNumber * _Nonnull)minInterval maxInterval:(NSNumber * _Nonnull)maxInterval
                                                     params:(ZGMTRSubscribeParams * _Nullable)params
                                    subscriptionEstablished:(ZGMTRSubscriptionEstablishedHandler _Nullable)subscriptionEstablishedHandler
                                              reportHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))reportHandler ZGMTR_DEPRECATED("Please use subscribeAttributeInstantaneousPowerWithParams:subscriptionEstablished:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
+ (void)readAttributeInstantaneousPowerWithAttributeCache:(ZGMTRAttributeCacheContainer *)attributeCacheContainer endpoint:(NSNumber *)endpoint queue:(dispatch_queue_t)queue completionHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completionHandler ZGMTR_DEPRECATED("Please use readAttributeInstantaneousPowerWithAttributeCache:endpoint:queue:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));

- (void)readAttributeRmsVoltageWithCompletionHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completionHandler ZGMTR_DEPRECATED("Please use readAttributeRmsVoltageWithCompletion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (void)subscribeAttributeRmsVoltageWithMinInterval:(NSNumber * _Nonnull)minInterval maxInterval:(NSNumber * _Nonnull)maxInterval
                                             params:(ZGMTRSubscribeParams * _Nullable)params
                            subscriptionEstablished:(ZGMTRSubscriptionEstablishedHandler _Nullable)subscriptionEstablishedHandler
                                      reportHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))reportHandler ZGMTR_DEPRECATED("Please use subscribeAttributeRmsVoltageWithParams:subscriptionEstablished:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
+ (void)readAttributeRmsVoltageWithAttributeCache:(ZGMTRAttributeCacheContainer *)attributeCacheContainer endpoint:(NSNumber *)endpoint queue:(dispatch_queue_t)queue completionHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completionHandler ZGMTR_DEPRECATED("Please use readAttributeRmsVoltageWithAttributeCache:endpoint:queue:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));

- (void)readAttributeRmsVoltageMinWithCompletionHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completionHandler ZGMTR_DEPRECATED("Please use readAttributeRmsVoltageMinWithCompletion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (void)subscribeAttributeRmsVoltageMinWithMinInterval:(NSNumber * _Nonnull)minInterval maxInterval:(NSNumber * _Nonnull)maxInterval
                                                params:(ZGMTRSubscribeParams * _Nullable)params
                               subscriptionEstablished:(ZGMTRSubscriptionEstablishedHandler _Nullable)subscriptionEstablishedHandler
                                         reportHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))reportHandler ZGMTR_DEPRECATED("Please use subscribeAttributeRmsVoltageMinWithParams:subscriptionEstablished:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
+ (void)readAttributeRmsVoltageMinWithAttributeCache:(ZGMTRAttributeCacheContainer *)attributeCacheContainer endpoint:(NSNumber *)endpoint queue:(dispatch_queue_t)queue completionHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completionHandler ZGMTR_DEPRECATED("Please use readAttributeRmsVoltageMinWithAttributeCache:endpoint:queue:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));

- (void)readAttributeRmsVoltageMaxWithCompletionHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completionHandler ZGMTR_DEPRECATED("Please use readAttributeRmsVoltageMaxWithCompletion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (void)subscribeAttributeRmsVoltageMaxWithMinInterval:(NSNumber * _Nonnull)minInterval maxInterval:(NSNumber * _Nonnull)maxInterval
                                                params:(ZGMTRSubscribeParams * _Nullable)params
                               subscriptionEstablished:(ZGMTRSubscriptionEstablishedHandler _Nullable)subscriptionEstablishedHandler
                                         reportHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))reportHandler ZGMTR_DEPRECATED("Please use subscribeAttributeRmsVoltageMaxWithParams:subscriptionEstablished:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
+ (void)readAttributeRmsVoltageMaxWithAttributeCache:(ZGMTRAttributeCacheContainer *)attributeCacheContainer endpoint:(NSNumber *)endpoint queue:(dispatch_queue_t)queue completionHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completionHandler ZGMTR_DEPRECATED("Please use readAttributeRmsVoltageMaxWithAttributeCache:endpoint:queue:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));

- (void)readAttributeRmsCurrentWithCompletionHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completionHandler ZGMTR_DEPRECATED("Please use readAttributeRmsCurrentWithCompletion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (void)subscribeAttributeRmsCurrentWithMinInterval:(NSNumber * _Nonnull)minInterval maxInterval:(NSNumber * _Nonnull)maxInterval
                                             params:(ZGMTRSubscribeParams * _Nullable)params
                            subscriptionEstablished:(ZGMTRSubscriptionEstablishedHandler _Nullable)subscriptionEstablishedHandler
                                      reportHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))reportHandler ZGMTR_DEPRECATED("Please use subscribeAttributeRmsCurrentWithParams:subscriptionEstablished:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
+ (void)readAttributeRmsCurrentWithAttributeCache:(ZGMTRAttributeCacheContainer *)attributeCacheContainer endpoint:(NSNumber *)endpoint queue:(dispatch_queue_t)queue completionHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completionHandler ZGMTR_DEPRECATED("Please use readAttributeRmsCurrentWithAttributeCache:endpoint:queue:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));

- (void)readAttributeRmsCurrentMinWithCompletionHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completionHandler ZGMTR_DEPRECATED("Please use readAttributeRmsCurrentMinWithCompletion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (void)subscribeAttributeRmsCurrentMinWithMinInterval:(NSNumber * _Nonnull)minInterval maxInterval:(NSNumber * _Nonnull)maxInterval
                                                params:(ZGMTRSubscribeParams * _Nullable)params
                               subscriptionEstablished:(ZGMTRSubscriptionEstablishedHandler _Nullable)subscriptionEstablishedHandler
                                         reportHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))reportHandler ZGMTR_DEPRECATED("Please use subscribeAttributeRmsCurrentMinWithParams:subscriptionEstablished:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
+ (void)readAttributeRmsCurrentMinWithAttributeCache:(ZGMTRAttributeCacheContainer *)attributeCacheContainer endpoint:(NSNumber *)endpoint queue:(dispatch_queue_t)queue completionHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completionHandler ZGMTR_DEPRECATED("Please use readAttributeRmsCurrentMinWithAttributeCache:endpoint:queue:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));

- (void)readAttributeRmsCurrentMaxWithCompletionHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completionHandler ZGMTR_DEPRECATED("Please use readAttributeRmsCurrentMaxWithCompletion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (void)subscribeAttributeRmsCurrentMaxWithMinInterval:(NSNumber * _Nonnull)minInterval maxInterval:(NSNumber * _Nonnull)maxInterval
                                                params:(ZGMTRSubscribeParams * _Nullable)params
                               subscriptionEstablished:(ZGMTRSubscriptionEstablishedHandler _Nullable)subscriptionEstablishedHandler
                                         reportHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))reportHandler ZGMTR_DEPRECATED("Please use subscribeAttributeRmsCurrentMaxWithParams:subscriptionEstablished:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
+ (void)readAttributeRmsCurrentMaxWithAttributeCache:(ZGMTRAttributeCacheContainer *)attributeCacheContainer endpoint:(NSNumber *)endpoint queue:(dispatch_queue_t)queue completionHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completionHandler ZGMTR_DEPRECATED("Please use readAttributeRmsCurrentMaxWithAttributeCache:endpoint:queue:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));

- (void)readAttributeActivePowerWithCompletionHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completionHandler ZGMTR_DEPRECATED("Please use readAttributeActivePowerWithCompletion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (void)subscribeAttributeActivePowerWithMinInterval:(NSNumber * _Nonnull)minInterval maxInterval:(NSNumber * _Nonnull)maxInterval
                                              params:(ZGMTRSubscribeParams * _Nullable)params
                             subscriptionEstablished:(ZGMTRSubscriptionEstablishedHandler _Nullable)subscriptionEstablishedHandler
                                       reportHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))reportHandler ZGMTR_DEPRECATED("Please use subscribeAttributeActivePowerWithParams:subscriptionEstablished:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
+ (void)readAttributeActivePowerWithAttributeCache:(ZGMTRAttributeCacheContainer *)attributeCacheContainer endpoint:(NSNumber *)endpoint queue:(dispatch_queue_t)queue completionHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completionHandler ZGMTR_DEPRECATED("Please use readAttributeActivePowerWithAttributeCache:endpoint:queue:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));

- (void)readAttributeActivePowerMinWithCompletionHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completionHandler ZGMTR_DEPRECATED("Please use readAttributeActivePowerMinWithCompletion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (void)subscribeAttributeActivePowerMinWithMinInterval:(NSNumber * _Nonnull)minInterval maxInterval:(NSNumber * _Nonnull)maxInterval
                                                 params:(ZGMTRSubscribeParams * _Nullable)params
                                subscriptionEstablished:(ZGMTRSubscriptionEstablishedHandler _Nullable)subscriptionEstablishedHandler
                                          reportHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))reportHandler ZGMTR_DEPRECATED("Please use subscribeAttributeActivePowerMinWithParams:subscriptionEstablished:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
+ (void)readAttributeActivePowerMinWithAttributeCache:(ZGMTRAttributeCacheContainer *)attributeCacheContainer endpoint:(NSNumber *)endpoint queue:(dispatch_queue_t)queue completionHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completionHandler ZGMTR_DEPRECATED("Please use readAttributeActivePowerMinWithAttributeCache:endpoint:queue:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));

- (void)readAttributeActivePowerMaxWithCompletionHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completionHandler ZGMTR_DEPRECATED("Please use readAttributeActivePowerMaxWithCompletion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (void)subscribeAttributeActivePowerMaxWithMinInterval:(NSNumber * _Nonnull)minInterval maxInterval:(NSNumber * _Nonnull)maxInterval
                                                 params:(ZGMTRSubscribeParams * _Nullable)params
                                subscriptionEstablished:(ZGMTRSubscriptionEstablishedHandler _Nullable)subscriptionEstablishedHandler
                                          reportHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))reportHandler ZGMTR_DEPRECATED("Please use subscribeAttributeActivePowerMaxWithParams:subscriptionEstablished:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
+ (void)readAttributeActivePowerMaxWithAttributeCache:(ZGMTRAttributeCacheContainer *)attributeCacheContainer endpoint:(NSNumber *)endpoint queue:(dispatch_queue_t)queue completionHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completionHandler ZGMTR_DEPRECATED("Please use readAttributeActivePowerMaxWithAttributeCache:endpoint:queue:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));

- (void)readAttributeReactivePowerWithCompletionHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completionHandler ZGMTR_DEPRECATED("Please use readAttributeReactivePowerWithCompletion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (void)subscribeAttributeReactivePowerWithMinInterval:(NSNumber * _Nonnull)minInterval maxInterval:(NSNumber * _Nonnull)maxInterval
                                                params:(ZGMTRSubscribeParams * _Nullable)params
                               subscriptionEstablished:(ZGMTRSubscriptionEstablishedHandler _Nullable)subscriptionEstablishedHandler
                                         reportHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))reportHandler ZGMTR_DEPRECATED("Please use subscribeAttributeReactivePowerWithParams:subscriptionEstablished:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
+ (void)readAttributeReactivePowerWithAttributeCache:(ZGMTRAttributeCacheContainer *)attributeCacheContainer endpoint:(NSNumber *)endpoint queue:(dispatch_queue_t)queue completionHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completionHandler ZGMTR_DEPRECATED("Please use readAttributeReactivePowerWithAttributeCache:endpoint:queue:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));

- (void)readAttributeApparentPowerWithCompletionHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completionHandler ZGMTR_DEPRECATED("Please use readAttributeApparentPowerWithCompletion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (void)subscribeAttributeApparentPowerWithMinInterval:(NSNumber * _Nonnull)minInterval maxInterval:(NSNumber * _Nonnull)maxInterval
                                                params:(ZGMTRSubscribeParams * _Nullable)params
                               subscriptionEstablished:(ZGMTRSubscriptionEstablishedHandler _Nullable)subscriptionEstablishedHandler
                                         reportHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))reportHandler ZGMTR_DEPRECATED("Please use subscribeAttributeApparentPowerWithParams:subscriptionEstablished:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
+ (void)readAttributeApparentPowerWithAttributeCache:(ZGMTRAttributeCacheContainer *)attributeCacheContainer endpoint:(NSNumber *)endpoint queue:(dispatch_queue_t)queue completionHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completionHandler ZGMTR_DEPRECATED("Please use readAttributeApparentPowerWithAttributeCache:endpoint:queue:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));

- (void)readAttributePowerFactorWithCompletionHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completionHandler ZGMTR_DEPRECATED("Please use readAttributePowerFactorWithCompletion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (void)subscribeAttributePowerFactorWithMinInterval:(NSNumber * _Nonnull)minInterval maxInterval:(NSNumber * _Nonnull)maxInterval
                                              params:(ZGMTRSubscribeParams * _Nullable)params
                             subscriptionEstablished:(ZGMTRSubscriptionEstablishedHandler _Nullable)subscriptionEstablishedHandler
                                       reportHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))reportHandler ZGMTR_DEPRECATED("Please use subscribeAttributePowerFactorWithParams:subscriptionEstablished:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
+ (void)readAttributePowerFactorWithAttributeCache:(ZGMTRAttributeCacheContainer *)attributeCacheContainer endpoint:(NSNumber *)endpoint queue:(dispatch_queue_t)queue completionHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completionHandler ZGMTR_DEPRECATED("Please use readAttributePowerFactorWithAttributeCache:endpoint:queue:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));

- (void)readAttributeAverageRmsVoltageMeasurementPeriodWithCompletionHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completionHandler ZGMTR_DEPRECATED("Please use readAttributeAverageRmsVoltageMeasurementPeriodWithCompletion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (void)writeAttributeAverageRmsVoltageMeasurementPeriodWithValue:(NSNumber * _Nonnull)value completionHandler:(ZGMTRStatusCompletion)completionHandler ZGMTR_DEPRECATED("Please use writeAttributeAverageRmsVoltageMeasurementPeriodWithValue:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (void)writeAttributeAverageRmsVoltageMeasurementPeriodWithValue:(NSNumber * _Nonnull)value params:(ZGMTRWriteParams * _Nullable)params completionHandler:(ZGMTRStatusCompletion)completionHandler ZGMTR_DEPRECATED("Please use writeAttributeAverageRmsVoltageMeasurementPeriodWithValue:params:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (void)subscribeAttributeAverageRmsVoltageMeasurementPeriodWithMinInterval:(NSNumber * _Nonnull)minInterval maxInterval:(NSNumber * _Nonnull)maxInterval
                                                                     params:(ZGMTRSubscribeParams * _Nullable)params
                                                    subscriptionEstablished:(ZGMTRSubscriptionEstablishedHandler _Nullable)subscriptionEstablishedHandler
                                                              reportHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))reportHandler ZGMTR_DEPRECATED("Please use subscribeAttributeAverageRmsVoltageMeasurementPeriodWithParams:subscriptionEstablished:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
+ (void)readAttributeAverageRmsVoltageMeasurementPeriodWithAttributeCache:(ZGMTRAttributeCacheContainer *)attributeCacheContainer endpoint:(NSNumber *)endpoint queue:(dispatch_queue_t)queue completionHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completionHandler ZGMTR_DEPRECATED("Please use readAttributeAverageRmsVoltageMeasurementPeriodWithAttributeCache:endpoint:queue:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));

- (void)readAttributeAverageRmsUnderVoltageCounterWithCompletionHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completionHandler ZGMTR_DEPRECATED("Please use readAttributeAverageRmsUnderVoltageCounterWithCompletion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (void)writeAttributeAverageRmsUnderVoltageCounterWithValue:(NSNumber * _Nonnull)value completionHandler:(ZGMTRStatusCompletion)completionHandler ZGMTR_DEPRECATED("Please use writeAttributeAverageRmsUnderVoltageCounterWithValue:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (void)writeAttributeAverageRmsUnderVoltageCounterWithValue:(NSNumber * _Nonnull)value params:(ZGMTRWriteParams * _Nullable)params completionHandler:(ZGMTRStatusCompletion)completionHandler ZGMTR_DEPRECATED("Please use writeAttributeAverageRmsUnderVoltageCounterWithValue:params:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (void)subscribeAttributeAverageRmsUnderVoltageCounterWithMinInterval:(NSNumber * _Nonnull)minInterval maxInterval:(NSNumber * _Nonnull)maxInterval
                                                                params:(ZGMTRSubscribeParams * _Nullable)params
                                               subscriptionEstablished:(ZGMTRSubscriptionEstablishedHandler _Nullable)subscriptionEstablishedHandler
                                                         reportHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))reportHandler ZGMTR_DEPRECATED("Please use subscribeAttributeAverageRmsUnderVoltageCounterWithParams:subscriptionEstablished:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
+ (void)readAttributeAverageRmsUnderVoltageCounterWithAttributeCache:(ZGMTRAttributeCacheContainer *)attributeCacheContainer endpoint:(NSNumber *)endpoint queue:(dispatch_queue_t)queue completionHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completionHandler ZGMTR_DEPRECATED("Please use readAttributeAverageRmsUnderVoltageCounterWithAttributeCache:endpoint:queue:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));

- (void)readAttributeRmsExtremeOverVoltagePeriodWithCompletionHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completionHandler ZGMTR_DEPRECATED("Please use readAttributeRmsExtremeOverVoltagePeriodWithCompletion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (void)writeAttributeRmsExtremeOverVoltagePeriodWithValue:(NSNumber * _Nonnull)value completionHandler:(ZGMTRStatusCompletion)completionHandler ZGMTR_DEPRECATED("Please use writeAttributeRmsExtremeOverVoltagePeriodWithValue:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (void)writeAttributeRmsExtremeOverVoltagePeriodWithValue:(NSNumber * _Nonnull)value params:(ZGMTRWriteParams * _Nullable)params completionHandler:(ZGMTRStatusCompletion)completionHandler ZGMTR_DEPRECATED("Please use writeAttributeRmsExtremeOverVoltagePeriodWithValue:params:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (void)subscribeAttributeRmsExtremeOverVoltagePeriodWithMinInterval:(NSNumber * _Nonnull)minInterval maxInterval:(NSNumber * _Nonnull)maxInterval
                                                              params:(ZGMTRSubscribeParams * _Nullable)params
                                             subscriptionEstablished:(ZGMTRSubscriptionEstablishedHandler _Nullable)subscriptionEstablishedHandler
                                                       reportHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))reportHandler ZGMTR_DEPRECATED("Please use subscribeAttributeRmsExtremeOverVoltagePeriodWithParams:subscriptionEstablished:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
+ (void)readAttributeRmsExtremeOverVoltagePeriodWithAttributeCache:(ZGMTRAttributeCacheContainer *)attributeCacheContainer endpoint:(NSNumber *)endpoint queue:(dispatch_queue_t)queue completionHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completionHandler ZGMTR_DEPRECATED("Please use readAttributeRmsExtremeOverVoltagePeriodWithAttributeCache:endpoint:queue:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));

- (void)readAttributeRmsExtremeUnderVoltagePeriodWithCompletionHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completionHandler ZGMTR_DEPRECATED("Please use readAttributeRmsExtremeUnderVoltagePeriodWithCompletion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (void)writeAttributeRmsExtremeUnderVoltagePeriodWithValue:(NSNumber * _Nonnull)value completionHandler:(ZGMTRStatusCompletion)completionHandler ZGMTR_DEPRECATED("Please use writeAttributeRmsExtremeUnderVoltagePeriodWithValue:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (void)writeAttributeRmsExtremeUnderVoltagePeriodWithValue:(NSNumber * _Nonnull)value params:(ZGMTRWriteParams * _Nullable)params completionHandler:(ZGMTRStatusCompletion)completionHandler ZGMTR_DEPRECATED("Please use writeAttributeRmsExtremeUnderVoltagePeriodWithValue:params:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (void)subscribeAttributeRmsExtremeUnderVoltagePeriodWithMinInterval:(NSNumber * _Nonnull)minInterval maxInterval:(NSNumber * _Nonnull)maxInterval
                                                               params:(ZGMTRSubscribeParams * _Nullable)params
                                              subscriptionEstablished:(ZGMTRSubscriptionEstablishedHandler _Nullable)subscriptionEstablishedHandler
                                                        reportHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))reportHandler ZGMTR_DEPRECATED("Please use subscribeAttributeRmsExtremeUnderVoltagePeriodWithParams:subscriptionEstablished:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
+ (void)readAttributeRmsExtremeUnderVoltagePeriodWithAttributeCache:(ZGMTRAttributeCacheContainer *)attributeCacheContainer endpoint:(NSNumber *)endpoint queue:(dispatch_queue_t)queue completionHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completionHandler ZGMTR_DEPRECATED("Please use readAttributeRmsExtremeUnderVoltagePeriodWithAttributeCache:endpoint:queue:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));

- (void)readAttributeRmsVoltageSagPeriodWithCompletionHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completionHandler ZGMTR_DEPRECATED("Please use readAttributeRmsVoltageSagPeriodWithCompletion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (void)writeAttributeRmsVoltageSagPeriodWithValue:(NSNumber * _Nonnull)value completionHandler:(ZGMTRStatusCompletion)completionHandler ZGMTR_DEPRECATED("Please use writeAttributeRmsVoltageSagPeriodWithValue:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (void)writeAttributeRmsVoltageSagPeriodWithValue:(NSNumber * _Nonnull)value params:(ZGMTRWriteParams * _Nullable)params completionHandler:(ZGMTRStatusCompletion)completionHandler ZGMTR_DEPRECATED("Please use writeAttributeRmsVoltageSagPeriodWithValue:params:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (void)subscribeAttributeRmsVoltageSagPeriodWithMinInterval:(NSNumber * _Nonnull)minInterval maxInterval:(NSNumber * _Nonnull)maxInterval
                                                      params:(ZGMTRSubscribeParams * _Nullable)params
                                     subscriptionEstablished:(ZGMTRSubscriptionEstablishedHandler _Nullable)subscriptionEstablishedHandler
                                               reportHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))reportHandler ZGMTR_DEPRECATED("Please use subscribeAttributeRmsVoltageSagPeriodWithParams:subscriptionEstablished:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
+ (void)readAttributeRmsVoltageSagPeriodWithAttributeCache:(ZGMTRAttributeCacheContainer *)attributeCacheContainer endpoint:(NSNumber *)endpoint queue:(dispatch_queue_t)queue completionHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completionHandler ZGMTR_DEPRECATED("Please use readAttributeRmsVoltageSagPeriodWithAttributeCache:endpoint:queue:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));

- (void)readAttributeRmsVoltageSwellPeriodWithCompletionHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completionHandler ZGMTR_DEPRECATED("Please use readAttributeRmsVoltageSwellPeriodWithCompletion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (void)writeAttributeRmsVoltageSwellPeriodWithValue:(NSNumber * _Nonnull)value completionHandler:(ZGMTRStatusCompletion)completionHandler ZGMTR_DEPRECATED("Please use writeAttributeRmsVoltageSwellPeriodWithValue:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (void)writeAttributeRmsVoltageSwellPeriodWithValue:(NSNumber * _Nonnull)value params:(ZGMTRWriteParams * _Nullable)params completionHandler:(ZGMTRStatusCompletion)completionHandler ZGMTR_DEPRECATED("Please use writeAttributeRmsVoltageSwellPeriodWithValue:params:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (void)subscribeAttributeRmsVoltageSwellPeriodWithMinInterval:(NSNumber * _Nonnull)minInterval maxInterval:(NSNumber * _Nonnull)maxInterval
                                                        params:(ZGMTRSubscribeParams * _Nullable)params
                                       subscriptionEstablished:(ZGMTRSubscriptionEstablishedHandler _Nullable)subscriptionEstablishedHandler
                                                 reportHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))reportHandler ZGMTR_DEPRECATED("Please use subscribeAttributeRmsVoltageSwellPeriodWithParams:subscriptionEstablished:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
+ (void)readAttributeRmsVoltageSwellPeriodWithAttributeCache:(ZGMTRAttributeCacheContainer *)attributeCacheContainer endpoint:(NSNumber *)endpoint queue:(dispatch_queue_t)queue completionHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completionHandler ZGMTR_DEPRECATED("Please use readAttributeRmsVoltageSwellPeriodWithAttributeCache:endpoint:queue:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));

- (void)readAttributeAcVoltageMultiplierWithCompletionHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completionHandler ZGMTR_DEPRECATED("Please use readAttributeAcVoltageMultiplierWithCompletion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (void)subscribeAttributeAcVoltageMultiplierWithMinInterval:(NSNumber * _Nonnull)minInterval maxInterval:(NSNumber * _Nonnull)maxInterval
                                                      params:(ZGMTRSubscribeParams * _Nullable)params
                                     subscriptionEstablished:(ZGMTRSubscriptionEstablishedHandler _Nullable)subscriptionEstablishedHandler
                                               reportHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))reportHandler ZGMTR_DEPRECATED("Please use subscribeAttributeAcVoltageMultiplierWithParams:subscriptionEstablished:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
+ (void)readAttributeAcVoltageMultiplierWithAttributeCache:(ZGMTRAttributeCacheContainer *)attributeCacheContainer endpoint:(NSNumber *)endpoint queue:(dispatch_queue_t)queue completionHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completionHandler ZGMTR_DEPRECATED("Please use readAttributeAcVoltageMultiplierWithAttributeCache:endpoint:queue:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));

- (void)readAttributeAcVoltageDivisorWithCompletionHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completionHandler ZGMTR_DEPRECATED("Please use readAttributeAcVoltageDivisorWithCompletion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (void)subscribeAttributeAcVoltageDivisorWithMinInterval:(NSNumber * _Nonnull)minInterval maxInterval:(NSNumber * _Nonnull)maxInterval
                                                   params:(ZGMTRSubscribeParams * _Nullable)params
                                  subscriptionEstablished:(ZGMTRSubscriptionEstablishedHandler _Nullable)subscriptionEstablishedHandler
                                            reportHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))reportHandler ZGMTR_DEPRECATED("Please use subscribeAttributeAcVoltageDivisorWithParams:subscriptionEstablished:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
+ (void)readAttributeAcVoltageDivisorWithAttributeCache:(ZGMTRAttributeCacheContainer *)attributeCacheContainer endpoint:(NSNumber *)endpoint queue:(dispatch_queue_t)queue completionHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completionHandler ZGMTR_DEPRECATED("Please use readAttributeAcVoltageDivisorWithAttributeCache:endpoint:queue:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));

- (void)readAttributeAcCurrentMultiplierWithCompletionHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completionHandler ZGMTR_DEPRECATED("Please use readAttributeAcCurrentMultiplierWithCompletion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (void)subscribeAttributeAcCurrentMultiplierWithMinInterval:(NSNumber * _Nonnull)minInterval maxInterval:(NSNumber * _Nonnull)maxInterval
                                                      params:(ZGMTRSubscribeParams * _Nullable)params
                                     subscriptionEstablished:(ZGMTRSubscriptionEstablishedHandler _Nullable)subscriptionEstablishedHandler
                                               reportHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))reportHandler ZGMTR_DEPRECATED("Please use subscribeAttributeAcCurrentMultiplierWithParams:subscriptionEstablished:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
+ (void)readAttributeAcCurrentMultiplierWithAttributeCache:(ZGMTRAttributeCacheContainer *)attributeCacheContainer endpoint:(NSNumber *)endpoint queue:(dispatch_queue_t)queue completionHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completionHandler ZGMTR_DEPRECATED("Please use readAttributeAcCurrentMultiplierWithAttributeCache:endpoint:queue:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));

- (void)readAttributeAcCurrentDivisorWithCompletionHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completionHandler ZGMTR_DEPRECATED("Please use readAttributeAcCurrentDivisorWithCompletion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (void)subscribeAttributeAcCurrentDivisorWithMinInterval:(NSNumber * _Nonnull)minInterval maxInterval:(NSNumber * _Nonnull)maxInterval
                                                   params:(ZGMTRSubscribeParams * _Nullable)params
                                  subscriptionEstablished:(ZGMTRSubscriptionEstablishedHandler _Nullable)subscriptionEstablishedHandler
                                            reportHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))reportHandler ZGMTR_DEPRECATED("Please use subscribeAttributeAcCurrentDivisorWithParams:subscriptionEstablished:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
+ (void)readAttributeAcCurrentDivisorWithAttributeCache:(ZGMTRAttributeCacheContainer *)attributeCacheContainer endpoint:(NSNumber *)endpoint queue:(dispatch_queue_t)queue completionHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completionHandler ZGMTR_DEPRECATED("Please use readAttributeAcCurrentDivisorWithAttributeCache:endpoint:queue:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));

- (void)readAttributeAcPowerMultiplierWithCompletionHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completionHandler ZGMTR_DEPRECATED("Please use readAttributeAcPowerMultiplierWithCompletion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (void)subscribeAttributeAcPowerMultiplierWithMinInterval:(NSNumber * _Nonnull)minInterval maxInterval:(NSNumber * _Nonnull)maxInterval
                                                    params:(ZGMTRSubscribeParams * _Nullable)params
                                   subscriptionEstablished:(ZGMTRSubscriptionEstablishedHandler _Nullable)subscriptionEstablishedHandler
                                             reportHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))reportHandler ZGMTR_DEPRECATED("Please use subscribeAttributeAcPowerMultiplierWithParams:subscriptionEstablished:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
+ (void)readAttributeAcPowerMultiplierWithAttributeCache:(ZGMTRAttributeCacheContainer *)attributeCacheContainer endpoint:(NSNumber *)endpoint queue:(dispatch_queue_t)queue completionHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completionHandler ZGMTR_DEPRECATED("Please use readAttributeAcPowerMultiplierWithAttributeCache:endpoint:queue:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));

- (void)readAttributeAcPowerDivisorWithCompletionHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completionHandler ZGMTR_DEPRECATED("Please use readAttributeAcPowerDivisorWithCompletion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (void)subscribeAttributeAcPowerDivisorWithMinInterval:(NSNumber * _Nonnull)minInterval maxInterval:(NSNumber * _Nonnull)maxInterval
                                                 params:(ZGMTRSubscribeParams * _Nullable)params
                                subscriptionEstablished:(ZGMTRSubscriptionEstablishedHandler _Nullable)subscriptionEstablishedHandler
                                          reportHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))reportHandler ZGMTR_DEPRECATED("Please use subscribeAttributeAcPowerDivisorWithParams:subscriptionEstablished:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
+ (void)readAttributeAcPowerDivisorWithAttributeCache:(ZGMTRAttributeCacheContainer *)attributeCacheContainer endpoint:(NSNumber *)endpoint queue:(dispatch_queue_t)queue completionHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completionHandler ZGMTR_DEPRECATED("Please use readAttributeAcPowerDivisorWithAttributeCache:endpoint:queue:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));

- (void)readAttributeOverloadAlarmsMaskWithCompletionHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completionHandler ZGMTR_DEPRECATED("Please use readAttributeOverloadAlarmsMaskWithCompletion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (void)writeAttributeOverloadAlarmsMaskWithValue:(NSNumber * _Nonnull)value completionHandler:(ZGMTRStatusCompletion)completionHandler ZGMTR_DEPRECATED("Please use writeAttributeOverloadAlarmsMaskWithValue:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (void)writeAttributeOverloadAlarmsMaskWithValue:(NSNumber * _Nonnull)value params:(ZGMTRWriteParams * _Nullable)params completionHandler:(ZGMTRStatusCompletion)completionHandler ZGMTR_DEPRECATED("Please use writeAttributeOverloadAlarmsMaskWithValue:params:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (void)subscribeAttributeOverloadAlarmsMaskWithMinInterval:(NSNumber * _Nonnull)minInterval maxInterval:(NSNumber * _Nonnull)maxInterval
                                                     params:(ZGMTRSubscribeParams * _Nullable)params
                                    subscriptionEstablished:(ZGMTRSubscriptionEstablishedHandler _Nullable)subscriptionEstablishedHandler
                                              reportHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))reportHandler ZGMTR_DEPRECATED("Please use subscribeAttributeOverloadAlarmsMaskWithParams:subscriptionEstablished:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
+ (void)readAttributeOverloadAlarmsMaskWithAttributeCache:(ZGMTRAttributeCacheContainer *)attributeCacheContainer endpoint:(NSNumber *)endpoint queue:(dispatch_queue_t)queue completionHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completionHandler ZGMTR_DEPRECATED("Please use readAttributeOverloadAlarmsMaskWithAttributeCache:endpoint:queue:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));

- (void)readAttributeVoltageOverloadWithCompletionHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completionHandler ZGMTR_DEPRECATED("Please use readAttributeVoltageOverloadWithCompletion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (void)subscribeAttributeVoltageOverloadWithMinInterval:(NSNumber * _Nonnull)minInterval maxInterval:(NSNumber * _Nonnull)maxInterval
                                                  params:(ZGMTRSubscribeParams * _Nullable)params
                                 subscriptionEstablished:(ZGMTRSubscriptionEstablishedHandler _Nullable)subscriptionEstablishedHandler
                                           reportHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))reportHandler ZGMTR_DEPRECATED("Please use subscribeAttributeVoltageOverloadWithParams:subscriptionEstablished:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
+ (void)readAttributeVoltageOverloadWithAttributeCache:(ZGMTRAttributeCacheContainer *)attributeCacheContainer endpoint:(NSNumber *)endpoint queue:(dispatch_queue_t)queue completionHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completionHandler ZGMTR_DEPRECATED("Please use readAttributeVoltageOverloadWithAttributeCache:endpoint:queue:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));

- (void)readAttributeCurrentOverloadWithCompletionHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completionHandler ZGMTR_DEPRECATED("Please use readAttributeCurrentOverloadWithCompletion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (void)subscribeAttributeCurrentOverloadWithMinInterval:(NSNumber * _Nonnull)minInterval maxInterval:(NSNumber * _Nonnull)maxInterval
                                                  params:(ZGMTRSubscribeParams * _Nullable)params
                                 subscriptionEstablished:(ZGMTRSubscriptionEstablishedHandler _Nullable)subscriptionEstablishedHandler
                                           reportHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))reportHandler ZGMTR_DEPRECATED("Please use subscribeAttributeCurrentOverloadWithParams:subscriptionEstablished:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
+ (void)readAttributeCurrentOverloadWithAttributeCache:(ZGMTRAttributeCacheContainer *)attributeCacheContainer endpoint:(NSNumber *)endpoint queue:(dispatch_queue_t)queue completionHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completionHandler ZGMTR_DEPRECATED("Please use readAttributeCurrentOverloadWithAttributeCache:endpoint:queue:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));

- (void)readAttributeAcOverloadAlarmsMaskWithCompletionHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completionHandler ZGMTR_DEPRECATED("Please use readAttributeAcOverloadAlarmsMaskWithCompletion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (void)writeAttributeAcOverloadAlarmsMaskWithValue:(NSNumber * _Nonnull)value completionHandler:(ZGMTRStatusCompletion)completionHandler ZGMTR_DEPRECATED("Please use writeAttributeAcOverloadAlarmsMaskWithValue:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (void)writeAttributeAcOverloadAlarmsMaskWithValue:(NSNumber * _Nonnull)value params:(ZGMTRWriteParams * _Nullable)params completionHandler:(ZGMTRStatusCompletion)completionHandler ZGMTR_DEPRECATED("Please use writeAttributeAcOverloadAlarmsMaskWithValue:params:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (void)subscribeAttributeAcOverloadAlarmsMaskWithMinInterval:(NSNumber * _Nonnull)minInterval maxInterval:(NSNumber * _Nonnull)maxInterval
                                                       params:(ZGMTRSubscribeParams * _Nullable)params
                                      subscriptionEstablished:(ZGMTRSubscriptionEstablishedHandler _Nullable)subscriptionEstablishedHandler
                                                reportHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))reportHandler ZGMTR_DEPRECATED("Please use subscribeAttributeAcOverloadAlarmsMaskWithParams:subscriptionEstablished:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
+ (void)readAttributeAcOverloadAlarmsMaskWithAttributeCache:(ZGMTRAttributeCacheContainer *)attributeCacheContainer endpoint:(NSNumber *)endpoint queue:(dispatch_queue_t)queue completionHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completionHandler ZGMTR_DEPRECATED("Please use readAttributeAcOverloadAlarmsMaskWithAttributeCache:endpoint:queue:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));

- (void)readAttributeAcVoltageOverloadWithCompletionHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completionHandler ZGMTR_DEPRECATED("Please use readAttributeAcVoltageOverloadWithCompletion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (void)subscribeAttributeAcVoltageOverloadWithMinInterval:(NSNumber * _Nonnull)minInterval maxInterval:(NSNumber * _Nonnull)maxInterval
                                                    params:(ZGMTRSubscribeParams * _Nullable)params
                                   subscriptionEstablished:(ZGMTRSubscriptionEstablishedHandler _Nullable)subscriptionEstablishedHandler
                                             reportHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))reportHandler ZGMTR_DEPRECATED("Please use subscribeAttributeAcVoltageOverloadWithParams:subscriptionEstablished:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
+ (void)readAttributeAcVoltageOverloadWithAttributeCache:(ZGMTRAttributeCacheContainer *)attributeCacheContainer endpoint:(NSNumber *)endpoint queue:(dispatch_queue_t)queue completionHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completionHandler ZGMTR_DEPRECATED("Please use readAttributeAcVoltageOverloadWithAttributeCache:endpoint:queue:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));

- (void)readAttributeAcCurrentOverloadWithCompletionHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completionHandler ZGMTR_DEPRECATED("Please use readAttributeAcCurrentOverloadWithCompletion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (void)subscribeAttributeAcCurrentOverloadWithMinInterval:(NSNumber * _Nonnull)minInterval maxInterval:(NSNumber * _Nonnull)maxInterval
                                                    params:(ZGMTRSubscribeParams * _Nullable)params
                                   subscriptionEstablished:(ZGMTRSubscriptionEstablishedHandler _Nullable)subscriptionEstablishedHandler
                                             reportHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))reportHandler ZGMTR_DEPRECATED("Please use subscribeAttributeAcCurrentOverloadWithParams:subscriptionEstablished:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
+ (void)readAttributeAcCurrentOverloadWithAttributeCache:(ZGMTRAttributeCacheContainer *)attributeCacheContainer endpoint:(NSNumber *)endpoint queue:(dispatch_queue_t)queue completionHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completionHandler ZGMTR_DEPRECATED("Please use readAttributeAcCurrentOverloadWithAttributeCache:endpoint:queue:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));

- (void)readAttributeAcActivePowerOverloadWithCompletionHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completionHandler ZGMTR_DEPRECATED("Please use readAttributeAcActivePowerOverloadWithCompletion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (void)subscribeAttributeAcActivePowerOverloadWithMinInterval:(NSNumber * _Nonnull)minInterval maxInterval:(NSNumber * _Nonnull)maxInterval
                                                        params:(ZGMTRSubscribeParams * _Nullable)params
                                       subscriptionEstablished:(ZGMTRSubscriptionEstablishedHandler _Nullable)subscriptionEstablishedHandler
                                                 reportHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))reportHandler ZGMTR_DEPRECATED("Please use subscribeAttributeAcActivePowerOverloadWithParams:subscriptionEstablished:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
+ (void)readAttributeAcActivePowerOverloadWithAttributeCache:(ZGMTRAttributeCacheContainer *)attributeCacheContainer endpoint:(NSNumber *)endpoint queue:(dispatch_queue_t)queue completionHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completionHandler ZGMTR_DEPRECATED("Please use readAttributeAcActivePowerOverloadWithAttributeCache:endpoint:queue:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));

- (void)readAttributeAcReactivePowerOverloadWithCompletionHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completionHandler ZGMTR_DEPRECATED("Please use readAttributeAcReactivePowerOverloadWithCompletion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (void)subscribeAttributeAcReactivePowerOverloadWithMinInterval:(NSNumber * _Nonnull)minInterval maxInterval:(NSNumber * _Nonnull)maxInterval
                                                          params:(ZGMTRSubscribeParams * _Nullable)params
                                         subscriptionEstablished:(ZGMTRSubscriptionEstablishedHandler _Nullable)subscriptionEstablishedHandler
                                                   reportHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))reportHandler ZGMTR_DEPRECATED("Please use subscribeAttributeAcReactivePowerOverloadWithParams:subscriptionEstablished:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
+ (void)readAttributeAcReactivePowerOverloadWithAttributeCache:(ZGMTRAttributeCacheContainer *)attributeCacheContainer endpoint:(NSNumber *)endpoint queue:(dispatch_queue_t)queue completionHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completionHandler ZGMTR_DEPRECATED("Please use readAttributeAcReactivePowerOverloadWithAttributeCache:endpoint:queue:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));

- (void)readAttributeAverageRmsOverVoltageWithCompletionHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completionHandler ZGMTR_DEPRECATED("Please use readAttributeAverageRmsOverVoltageWithCompletion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (void)subscribeAttributeAverageRmsOverVoltageWithMinInterval:(NSNumber * _Nonnull)minInterval maxInterval:(NSNumber * _Nonnull)maxInterval
                                                        params:(ZGMTRSubscribeParams * _Nullable)params
                                       subscriptionEstablished:(ZGMTRSubscriptionEstablishedHandler _Nullable)subscriptionEstablishedHandler
                                                 reportHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))reportHandler ZGMTR_DEPRECATED("Please use subscribeAttributeAverageRmsOverVoltageWithParams:subscriptionEstablished:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
+ (void)readAttributeAverageRmsOverVoltageWithAttributeCache:(ZGMTRAttributeCacheContainer *)attributeCacheContainer endpoint:(NSNumber *)endpoint queue:(dispatch_queue_t)queue completionHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completionHandler ZGMTR_DEPRECATED("Please use readAttributeAverageRmsOverVoltageWithAttributeCache:endpoint:queue:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));

- (void)readAttributeAverageRmsUnderVoltageWithCompletionHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completionHandler ZGMTR_DEPRECATED("Please use readAttributeAverageRmsUnderVoltageWithCompletion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (void)subscribeAttributeAverageRmsUnderVoltageWithMinInterval:(NSNumber * _Nonnull)minInterval maxInterval:(NSNumber * _Nonnull)maxInterval
                                                         params:(ZGMTRSubscribeParams * _Nullable)params
                                        subscriptionEstablished:(ZGMTRSubscriptionEstablishedHandler _Nullable)subscriptionEstablishedHandler
                                                  reportHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))reportHandler ZGMTR_DEPRECATED("Please use subscribeAttributeAverageRmsUnderVoltageWithParams:subscriptionEstablished:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
+ (void)readAttributeAverageRmsUnderVoltageWithAttributeCache:(ZGMTRAttributeCacheContainer *)attributeCacheContainer endpoint:(NSNumber *)endpoint queue:(dispatch_queue_t)queue completionHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completionHandler ZGMTR_DEPRECATED("Please use readAttributeAverageRmsUnderVoltageWithAttributeCache:endpoint:queue:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));

- (void)readAttributeRmsExtremeOverVoltageWithCompletionHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completionHandler ZGMTR_DEPRECATED("Please use readAttributeRmsExtremeOverVoltageWithCompletion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (void)subscribeAttributeRmsExtremeOverVoltageWithMinInterval:(NSNumber * _Nonnull)minInterval maxInterval:(NSNumber * _Nonnull)maxInterval
                                                        params:(ZGMTRSubscribeParams * _Nullable)params
                                       subscriptionEstablished:(ZGMTRSubscriptionEstablishedHandler _Nullable)subscriptionEstablishedHandler
                                                 reportHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))reportHandler ZGMTR_DEPRECATED("Please use subscribeAttributeRmsExtremeOverVoltageWithParams:subscriptionEstablished:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
+ (void)readAttributeRmsExtremeOverVoltageWithAttributeCache:(ZGMTRAttributeCacheContainer *)attributeCacheContainer endpoint:(NSNumber *)endpoint queue:(dispatch_queue_t)queue completionHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completionHandler ZGMTR_DEPRECATED("Please use readAttributeRmsExtremeOverVoltageWithAttributeCache:endpoint:queue:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));

- (void)readAttributeRmsExtremeUnderVoltageWithCompletionHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completionHandler ZGMTR_DEPRECATED("Please use readAttributeRmsExtremeUnderVoltageWithCompletion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (void)subscribeAttributeRmsExtremeUnderVoltageWithMinInterval:(NSNumber * _Nonnull)minInterval maxInterval:(NSNumber * _Nonnull)maxInterval
                                                         params:(ZGMTRSubscribeParams * _Nullable)params
                                        subscriptionEstablished:(ZGMTRSubscriptionEstablishedHandler _Nullable)subscriptionEstablishedHandler
                                                  reportHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))reportHandler ZGMTR_DEPRECATED("Please use subscribeAttributeRmsExtremeUnderVoltageWithParams:subscriptionEstablished:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
+ (void)readAttributeRmsExtremeUnderVoltageWithAttributeCache:(ZGMTRAttributeCacheContainer *)attributeCacheContainer endpoint:(NSNumber *)endpoint queue:(dispatch_queue_t)queue completionHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completionHandler ZGMTR_DEPRECATED("Please use readAttributeRmsExtremeUnderVoltageWithAttributeCache:endpoint:queue:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));

- (void)readAttributeRmsVoltageSagWithCompletionHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completionHandler ZGMTR_DEPRECATED("Please use readAttributeRmsVoltageSagWithCompletion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (void)subscribeAttributeRmsVoltageSagWithMinInterval:(NSNumber * _Nonnull)minInterval maxInterval:(NSNumber * _Nonnull)maxInterval
                                                params:(ZGMTRSubscribeParams * _Nullable)params
                               subscriptionEstablished:(ZGMTRSubscriptionEstablishedHandler _Nullable)subscriptionEstablishedHandler
                                         reportHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))reportHandler ZGMTR_DEPRECATED("Please use subscribeAttributeRmsVoltageSagWithParams:subscriptionEstablished:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
+ (void)readAttributeRmsVoltageSagWithAttributeCache:(ZGMTRAttributeCacheContainer *)attributeCacheContainer endpoint:(NSNumber *)endpoint queue:(dispatch_queue_t)queue completionHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completionHandler ZGMTR_DEPRECATED("Please use readAttributeRmsVoltageSagWithAttributeCache:endpoint:queue:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));

- (void)readAttributeRmsVoltageSwellWithCompletionHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completionHandler ZGMTR_DEPRECATED("Please use readAttributeRmsVoltageSwellWithCompletion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (void)subscribeAttributeRmsVoltageSwellWithMinInterval:(NSNumber * _Nonnull)minInterval maxInterval:(NSNumber * _Nonnull)maxInterval
                                                  params:(ZGMTRSubscribeParams * _Nullable)params
                                 subscriptionEstablished:(ZGMTRSubscriptionEstablishedHandler _Nullable)subscriptionEstablishedHandler
                                           reportHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))reportHandler ZGMTR_DEPRECATED("Please use subscribeAttributeRmsVoltageSwellWithParams:subscriptionEstablished:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
+ (void)readAttributeRmsVoltageSwellWithAttributeCache:(ZGMTRAttributeCacheContainer *)attributeCacheContainer endpoint:(NSNumber *)endpoint queue:(dispatch_queue_t)queue completionHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completionHandler ZGMTR_DEPRECATED("Please use readAttributeRmsVoltageSwellWithAttributeCache:endpoint:queue:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));

- (void)readAttributeLineCurrentPhaseBWithCompletionHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completionHandler ZGMTR_DEPRECATED("Please use readAttributeLineCurrentPhaseBWithCompletion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (void)subscribeAttributeLineCurrentPhaseBWithMinInterval:(NSNumber * _Nonnull)minInterval maxInterval:(NSNumber * _Nonnull)maxInterval
                                                    params:(ZGMTRSubscribeParams * _Nullable)params
                                   subscriptionEstablished:(ZGMTRSubscriptionEstablishedHandler _Nullable)subscriptionEstablishedHandler
                                             reportHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))reportHandler ZGMTR_DEPRECATED("Please use subscribeAttributeLineCurrentPhaseBWithParams:subscriptionEstablished:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
+ (void)readAttributeLineCurrentPhaseBWithAttributeCache:(ZGMTRAttributeCacheContainer *)attributeCacheContainer endpoint:(NSNumber *)endpoint queue:(dispatch_queue_t)queue completionHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completionHandler ZGMTR_DEPRECATED("Please use readAttributeLineCurrentPhaseBWithAttributeCache:endpoint:queue:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));

- (void)readAttributeActiveCurrentPhaseBWithCompletionHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completionHandler ZGMTR_DEPRECATED("Please use readAttributeActiveCurrentPhaseBWithCompletion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (void)subscribeAttributeActiveCurrentPhaseBWithMinInterval:(NSNumber * _Nonnull)minInterval maxInterval:(NSNumber * _Nonnull)maxInterval
                                                      params:(ZGMTRSubscribeParams * _Nullable)params
                                     subscriptionEstablished:(ZGMTRSubscriptionEstablishedHandler _Nullable)subscriptionEstablishedHandler
                                               reportHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))reportHandler ZGMTR_DEPRECATED("Please use subscribeAttributeActiveCurrentPhaseBWithParams:subscriptionEstablished:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
+ (void)readAttributeActiveCurrentPhaseBWithAttributeCache:(ZGMTRAttributeCacheContainer *)attributeCacheContainer endpoint:(NSNumber *)endpoint queue:(dispatch_queue_t)queue completionHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completionHandler ZGMTR_DEPRECATED("Please use readAttributeActiveCurrentPhaseBWithAttributeCache:endpoint:queue:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));

- (void)readAttributeReactiveCurrentPhaseBWithCompletionHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completionHandler ZGMTR_DEPRECATED("Please use readAttributeReactiveCurrentPhaseBWithCompletion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (void)subscribeAttributeReactiveCurrentPhaseBWithMinInterval:(NSNumber * _Nonnull)minInterval maxInterval:(NSNumber * _Nonnull)maxInterval
                                                        params:(ZGMTRSubscribeParams * _Nullable)params
                                       subscriptionEstablished:(ZGMTRSubscriptionEstablishedHandler _Nullable)subscriptionEstablishedHandler
                                                 reportHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))reportHandler ZGMTR_DEPRECATED("Please use subscribeAttributeReactiveCurrentPhaseBWithParams:subscriptionEstablished:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
+ (void)readAttributeReactiveCurrentPhaseBWithAttributeCache:(ZGMTRAttributeCacheContainer *)attributeCacheContainer endpoint:(NSNumber *)endpoint queue:(dispatch_queue_t)queue completionHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completionHandler ZGMTR_DEPRECATED("Please use readAttributeReactiveCurrentPhaseBWithAttributeCache:endpoint:queue:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));

- (void)readAttributeRmsVoltagePhaseBWithCompletionHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completionHandler ZGMTR_DEPRECATED("Please use readAttributeRmsVoltagePhaseBWithCompletion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (void)subscribeAttributeRmsVoltagePhaseBWithMinInterval:(NSNumber * _Nonnull)minInterval maxInterval:(NSNumber * _Nonnull)maxInterval
                                                   params:(ZGMTRSubscribeParams * _Nullable)params
                                  subscriptionEstablished:(ZGMTRSubscriptionEstablishedHandler _Nullable)subscriptionEstablishedHandler
                                            reportHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))reportHandler ZGMTR_DEPRECATED("Please use subscribeAttributeRmsVoltagePhaseBWithParams:subscriptionEstablished:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
+ (void)readAttributeRmsVoltagePhaseBWithAttributeCache:(ZGMTRAttributeCacheContainer *)attributeCacheContainer endpoint:(NSNumber *)endpoint queue:(dispatch_queue_t)queue completionHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completionHandler ZGMTR_DEPRECATED("Please use readAttributeRmsVoltagePhaseBWithAttributeCache:endpoint:queue:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));

- (void)readAttributeRmsVoltageMinPhaseBWithCompletionHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completionHandler ZGMTR_DEPRECATED("Please use readAttributeRmsVoltageMinPhaseBWithCompletion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (void)subscribeAttributeRmsVoltageMinPhaseBWithMinInterval:(NSNumber * _Nonnull)minInterval maxInterval:(NSNumber * _Nonnull)maxInterval
                                                      params:(ZGMTRSubscribeParams * _Nullable)params
                                     subscriptionEstablished:(ZGMTRSubscriptionEstablishedHandler _Nullable)subscriptionEstablishedHandler
                                               reportHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))reportHandler ZGMTR_DEPRECATED("Please use subscribeAttributeRmsVoltageMinPhaseBWithParams:subscriptionEstablished:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
+ (void)readAttributeRmsVoltageMinPhaseBWithAttributeCache:(ZGMTRAttributeCacheContainer *)attributeCacheContainer endpoint:(NSNumber *)endpoint queue:(dispatch_queue_t)queue completionHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completionHandler ZGMTR_DEPRECATED("Please use readAttributeRmsVoltageMinPhaseBWithAttributeCache:endpoint:queue:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));

- (void)readAttributeRmsVoltageMaxPhaseBWithCompletionHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completionHandler ZGMTR_DEPRECATED("Please use readAttributeRmsVoltageMaxPhaseBWithCompletion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (void)subscribeAttributeRmsVoltageMaxPhaseBWithMinInterval:(NSNumber * _Nonnull)minInterval maxInterval:(NSNumber * _Nonnull)maxInterval
                                                      params:(ZGMTRSubscribeParams * _Nullable)params
                                     subscriptionEstablished:(ZGMTRSubscriptionEstablishedHandler _Nullable)subscriptionEstablishedHandler
                                               reportHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))reportHandler ZGMTR_DEPRECATED("Please use subscribeAttributeRmsVoltageMaxPhaseBWithParams:subscriptionEstablished:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
+ (void)readAttributeRmsVoltageMaxPhaseBWithAttributeCache:(ZGMTRAttributeCacheContainer *)attributeCacheContainer endpoint:(NSNumber *)endpoint queue:(dispatch_queue_t)queue completionHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completionHandler ZGMTR_DEPRECATED("Please use readAttributeRmsVoltageMaxPhaseBWithAttributeCache:endpoint:queue:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));

- (void)readAttributeRmsCurrentPhaseBWithCompletionHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completionHandler ZGMTR_DEPRECATED("Please use readAttributeRmsCurrentPhaseBWithCompletion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (void)subscribeAttributeRmsCurrentPhaseBWithMinInterval:(NSNumber * _Nonnull)minInterval maxInterval:(NSNumber * _Nonnull)maxInterval
                                                   params:(ZGMTRSubscribeParams * _Nullable)params
                                  subscriptionEstablished:(ZGMTRSubscriptionEstablishedHandler _Nullable)subscriptionEstablishedHandler
                                            reportHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))reportHandler ZGMTR_DEPRECATED("Please use subscribeAttributeRmsCurrentPhaseBWithParams:subscriptionEstablished:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
+ (void)readAttributeRmsCurrentPhaseBWithAttributeCache:(ZGMTRAttributeCacheContainer *)attributeCacheContainer endpoint:(NSNumber *)endpoint queue:(dispatch_queue_t)queue completionHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completionHandler ZGMTR_DEPRECATED("Please use readAttributeRmsCurrentPhaseBWithAttributeCache:endpoint:queue:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));

- (void)readAttributeRmsCurrentMinPhaseBWithCompletionHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completionHandler ZGMTR_DEPRECATED("Please use readAttributeRmsCurrentMinPhaseBWithCompletion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (void)subscribeAttributeRmsCurrentMinPhaseBWithMinInterval:(NSNumber * _Nonnull)minInterval maxInterval:(NSNumber * _Nonnull)maxInterval
                                                      params:(ZGMTRSubscribeParams * _Nullable)params
                                     subscriptionEstablished:(ZGMTRSubscriptionEstablishedHandler _Nullable)subscriptionEstablishedHandler
                                               reportHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))reportHandler ZGMTR_DEPRECATED("Please use subscribeAttributeRmsCurrentMinPhaseBWithParams:subscriptionEstablished:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
+ (void)readAttributeRmsCurrentMinPhaseBWithAttributeCache:(ZGMTRAttributeCacheContainer *)attributeCacheContainer endpoint:(NSNumber *)endpoint queue:(dispatch_queue_t)queue completionHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completionHandler ZGMTR_DEPRECATED("Please use readAttributeRmsCurrentMinPhaseBWithAttributeCache:endpoint:queue:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));

- (void)readAttributeRmsCurrentMaxPhaseBWithCompletionHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completionHandler ZGMTR_DEPRECATED("Please use readAttributeRmsCurrentMaxPhaseBWithCompletion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (void)subscribeAttributeRmsCurrentMaxPhaseBWithMinInterval:(NSNumber * _Nonnull)minInterval maxInterval:(NSNumber * _Nonnull)maxInterval
                                                      params:(ZGMTRSubscribeParams * _Nullable)params
                                     subscriptionEstablished:(ZGMTRSubscriptionEstablishedHandler _Nullable)subscriptionEstablishedHandler
                                               reportHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))reportHandler ZGMTR_DEPRECATED("Please use subscribeAttributeRmsCurrentMaxPhaseBWithParams:subscriptionEstablished:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
+ (void)readAttributeRmsCurrentMaxPhaseBWithAttributeCache:(ZGMTRAttributeCacheContainer *)attributeCacheContainer endpoint:(NSNumber *)endpoint queue:(dispatch_queue_t)queue completionHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completionHandler ZGMTR_DEPRECATED("Please use readAttributeRmsCurrentMaxPhaseBWithAttributeCache:endpoint:queue:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));

- (void)readAttributeActivePowerPhaseBWithCompletionHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completionHandler ZGMTR_DEPRECATED("Please use readAttributeActivePowerPhaseBWithCompletion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (void)subscribeAttributeActivePowerPhaseBWithMinInterval:(NSNumber * _Nonnull)minInterval maxInterval:(NSNumber * _Nonnull)maxInterval
                                                    params:(ZGMTRSubscribeParams * _Nullable)params
                                   subscriptionEstablished:(ZGMTRSubscriptionEstablishedHandler _Nullable)subscriptionEstablishedHandler
                                             reportHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))reportHandler ZGMTR_DEPRECATED("Please use subscribeAttributeActivePowerPhaseBWithParams:subscriptionEstablished:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
+ (void)readAttributeActivePowerPhaseBWithAttributeCache:(ZGMTRAttributeCacheContainer *)attributeCacheContainer endpoint:(NSNumber *)endpoint queue:(dispatch_queue_t)queue completionHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completionHandler ZGMTR_DEPRECATED("Please use readAttributeActivePowerPhaseBWithAttributeCache:endpoint:queue:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));

- (void)readAttributeActivePowerMinPhaseBWithCompletionHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completionHandler ZGMTR_DEPRECATED("Please use readAttributeActivePowerMinPhaseBWithCompletion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (void)subscribeAttributeActivePowerMinPhaseBWithMinInterval:(NSNumber * _Nonnull)minInterval maxInterval:(NSNumber * _Nonnull)maxInterval
                                                       params:(ZGMTRSubscribeParams * _Nullable)params
                                      subscriptionEstablished:(ZGMTRSubscriptionEstablishedHandler _Nullable)subscriptionEstablishedHandler
                                                reportHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))reportHandler ZGMTR_DEPRECATED("Please use subscribeAttributeActivePowerMinPhaseBWithParams:subscriptionEstablished:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
+ (void)readAttributeActivePowerMinPhaseBWithAttributeCache:(ZGMTRAttributeCacheContainer *)attributeCacheContainer endpoint:(NSNumber *)endpoint queue:(dispatch_queue_t)queue completionHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completionHandler ZGMTR_DEPRECATED("Please use readAttributeActivePowerMinPhaseBWithAttributeCache:endpoint:queue:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));

- (void)readAttributeActivePowerMaxPhaseBWithCompletionHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completionHandler ZGMTR_DEPRECATED("Please use readAttributeActivePowerMaxPhaseBWithCompletion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (void)subscribeAttributeActivePowerMaxPhaseBWithMinInterval:(NSNumber * _Nonnull)minInterval maxInterval:(NSNumber * _Nonnull)maxInterval
                                                       params:(ZGMTRSubscribeParams * _Nullable)params
                                      subscriptionEstablished:(ZGMTRSubscriptionEstablishedHandler _Nullable)subscriptionEstablishedHandler
                                                reportHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))reportHandler ZGMTR_DEPRECATED("Please use subscribeAttributeActivePowerMaxPhaseBWithParams:subscriptionEstablished:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
+ (void)readAttributeActivePowerMaxPhaseBWithAttributeCache:(ZGMTRAttributeCacheContainer *)attributeCacheContainer endpoint:(NSNumber *)endpoint queue:(dispatch_queue_t)queue completionHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completionHandler ZGMTR_DEPRECATED("Please use readAttributeActivePowerMaxPhaseBWithAttributeCache:endpoint:queue:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));

- (void)readAttributeReactivePowerPhaseBWithCompletionHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completionHandler ZGMTR_DEPRECATED("Please use readAttributeReactivePowerPhaseBWithCompletion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (void)subscribeAttributeReactivePowerPhaseBWithMinInterval:(NSNumber * _Nonnull)minInterval maxInterval:(NSNumber * _Nonnull)maxInterval
                                                      params:(ZGMTRSubscribeParams * _Nullable)params
                                     subscriptionEstablished:(ZGMTRSubscriptionEstablishedHandler _Nullable)subscriptionEstablishedHandler
                                               reportHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))reportHandler ZGMTR_DEPRECATED("Please use subscribeAttributeReactivePowerPhaseBWithParams:subscriptionEstablished:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
+ (void)readAttributeReactivePowerPhaseBWithAttributeCache:(ZGMTRAttributeCacheContainer *)attributeCacheContainer endpoint:(NSNumber *)endpoint queue:(dispatch_queue_t)queue completionHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completionHandler ZGMTR_DEPRECATED("Please use readAttributeReactivePowerPhaseBWithAttributeCache:endpoint:queue:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));

- (void)readAttributeApparentPowerPhaseBWithCompletionHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completionHandler ZGMTR_DEPRECATED("Please use readAttributeApparentPowerPhaseBWithCompletion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (void)subscribeAttributeApparentPowerPhaseBWithMinInterval:(NSNumber * _Nonnull)minInterval maxInterval:(NSNumber * _Nonnull)maxInterval
                                                      params:(ZGMTRSubscribeParams * _Nullable)params
                                     subscriptionEstablished:(ZGMTRSubscriptionEstablishedHandler _Nullable)subscriptionEstablishedHandler
                                               reportHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))reportHandler ZGMTR_DEPRECATED("Please use subscribeAttributeApparentPowerPhaseBWithParams:subscriptionEstablished:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
+ (void)readAttributeApparentPowerPhaseBWithAttributeCache:(ZGMTRAttributeCacheContainer *)attributeCacheContainer endpoint:(NSNumber *)endpoint queue:(dispatch_queue_t)queue completionHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completionHandler ZGMTR_DEPRECATED("Please use readAttributeApparentPowerPhaseBWithAttributeCache:endpoint:queue:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));

- (void)readAttributePowerFactorPhaseBWithCompletionHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completionHandler ZGMTR_DEPRECATED("Please use readAttributePowerFactorPhaseBWithCompletion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (void)subscribeAttributePowerFactorPhaseBWithMinInterval:(NSNumber * _Nonnull)minInterval maxInterval:(NSNumber * _Nonnull)maxInterval
                                                    params:(ZGMTRSubscribeParams * _Nullable)params
                                   subscriptionEstablished:(ZGMTRSubscriptionEstablishedHandler _Nullable)subscriptionEstablishedHandler
                                             reportHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))reportHandler ZGMTR_DEPRECATED("Please use subscribeAttributePowerFactorPhaseBWithParams:subscriptionEstablished:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
+ (void)readAttributePowerFactorPhaseBWithAttributeCache:(ZGMTRAttributeCacheContainer *)attributeCacheContainer endpoint:(NSNumber *)endpoint queue:(dispatch_queue_t)queue completionHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completionHandler ZGMTR_DEPRECATED("Please use readAttributePowerFactorPhaseBWithAttributeCache:endpoint:queue:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));

- (void)readAttributeAverageRmsVoltageMeasurementPeriodPhaseBWithCompletionHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completionHandler ZGMTR_DEPRECATED("Please use readAttributeAverageRmsVoltageMeasurementPeriodPhaseBWithCompletion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (void)subscribeAttributeAverageRmsVoltageMeasurementPeriodPhaseBWithMinInterval:(NSNumber * _Nonnull)minInterval maxInterval:(NSNumber * _Nonnull)maxInterval
                                                                           params:(ZGMTRSubscribeParams * _Nullable)params
                                                          subscriptionEstablished:(ZGMTRSubscriptionEstablishedHandler _Nullable)subscriptionEstablishedHandler
                                                                    reportHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))reportHandler ZGMTR_DEPRECATED("Please use subscribeAttributeAverageRmsVoltageMeasurementPeriodPhaseBWithParams:subscriptionEstablished:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
+ (void)readAttributeAverageRmsVoltageMeasurementPeriodPhaseBWithAttributeCache:(ZGMTRAttributeCacheContainer *)attributeCacheContainer endpoint:(NSNumber *)endpoint queue:(dispatch_queue_t)queue completionHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completionHandler ZGMTR_DEPRECATED("Please use readAttributeAverageRmsVoltageMeasurementPeriodPhaseBWithAttributeCache:endpoint:queue:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));

- (void)readAttributeAverageRmsOverVoltageCounterPhaseBWithCompletionHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completionHandler ZGMTR_DEPRECATED("Please use readAttributeAverageRmsOverVoltageCounterPhaseBWithCompletion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (void)subscribeAttributeAverageRmsOverVoltageCounterPhaseBWithMinInterval:(NSNumber * _Nonnull)minInterval maxInterval:(NSNumber * _Nonnull)maxInterval
                                                                     params:(ZGMTRSubscribeParams * _Nullable)params
                                                    subscriptionEstablished:(ZGMTRSubscriptionEstablishedHandler _Nullable)subscriptionEstablishedHandler
                                                              reportHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))reportHandler ZGMTR_DEPRECATED("Please use subscribeAttributeAverageRmsOverVoltageCounterPhaseBWithParams:subscriptionEstablished:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
+ (void)readAttributeAverageRmsOverVoltageCounterPhaseBWithAttributeCache:(ZGMTRAttributeCacheContainer *)attributeCacheContainer endpoint:(NSNumber *)endpoint queue:(dispatch_queue_t)queue completionHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completionHandler ZGMTR_DEPRECATED("Please use readAttributeAverageRmsOverVoltageCounterPhaseBWithAttributeCache:endpoint:queue:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));

- (void)readAttributeAverageRmsUnderVoltageCounterPhaseBWithCompletionHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completionHandler ZGMTR_DEPRECATED("Please use readAttributeAverageRmsUnderVoltageCounterPhaseBWithCompletion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (void)subscribeAttributeAverageRmsUnderVoltageCounterPhaseBWithMinInterval:(NSNumber * _Nonnull)minInterval maxInterval:(NSNumber * _Nonnull)maxInterval
                                                                      params:(ZGMTRSubscribeParams * _Nullable)params
                                                     subscriptionEstablished:(ZGMTRSubscriptionEstablishedHandler _Nullable)subscriptionEstablishedHandler
                                                               reportHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))reportHandler ZGMTR_DEPRECATED("Please use subscribeAttributeAverageRmsUnderVoltageCounterPhaseBWithParams:subscriptionEstablished:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
+ (void)readAttributeAverageRmsUnderVoltageCounterPhaseBWithAttributeCache:(ZGMTRAttributeCacheContainer *)attributeCacheContainer endpoint:(NSNumber *)endpoint queue:(dispatch_queue_t)queue completionHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completionHandler ZGMTR_DEPRECATED("Please use readAttributeAverageRmsUnderVoltageCounterPhaseBWithAttributeCache:endpoint:queue:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));

- (void)readAttributeRmsExtremeOverVoltagePeriodPhaseBWithCompletionHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completionHandler ZGMTR_DEPRECATED("Please use readAttributeRmsExtremeOverVoltagePeriodPhaseBWithCompletion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (void)subscribeAttributeRmsExtremeOverVoltagePeriodPhaseBWithMinInterval:(NSNumber * _Nonnull)minInterval maxInterval:(NSNumber * _Nonnull)maxInterval
                                                                    params:(ZGMTRSubscribeParams * _Nullable)params
                                                   subscriptionEstablished:(ZGMTRSubscriptionEstablishedHandler _Nullable)subscriptionEstablishedHandler
                                                             reportHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))reportHandler ZGMTR_DEPRECATED("Please use subscribeAttributeRmsExtremeOverVoltagePeriodPhaseBWithParams:subscriptionEstablished:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
+ (void)readAttributeRmsExtremeOverVoltagePeriodPhaseBWithAttributeCache:(ZGMTRAttributeCacheContainer *)attributeCacheContainer endpoint:(NSNumber *)endpoint queue:(dispatch_queue_t)queue completionHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completionHandler ZGMTR_DEPRECATED("Please use readAttributeRmsExtremeOverVoltagePeriodPhaseBWithAttributeCache:endpoint:queue:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));

- (void)readAttributeRmsExtremeUnderVoltagePeriodPhaseBWithCompletionHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completionHandler ZGMTR_DEPRECATED("Please use readAttributeRmsExtremeUnderVoltagePeriodPhaseBWithCompletion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (void)subscribeAttributeRmsExtremeUnderVoltagePeriodPhaseBWithMinInterval:(NSNumber * _Nonnull)minInterval maxInterval:(NSNumber * _Nonnull)maxInterval
                                                                     params:(ZGMTRSubscribeParams * _Nullable)params
                                                    subscriptionEstablished:(ZGMTRSubscriptionEstablishedHandler _Nullable)subscriptionEstablishedHandler
                                                              reportHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))reportHandler ZGMTR_DEPRECATED("Please use subscribeAttributeRmsExtremeUnderVoltagePeriodPhaseBWithParams:subscriptionEstablished:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
+ (void)readAttributeRmsExtremeUnderVoltagePeriodPhaseBWithAttributeCache:(ZGMTRAttributeCacheContainer *)attributeCacheContainer endpoint:(NSNumber *)endpoint queue:(dispatch_queue_t)queue completionHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completionHandler ZGMTR_DEPRECATED("Please use readAttributeRmsExtremeUnderVoltagePeriodPhaseBWithAttributeCache:endpoint:queue:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));

- (void)readAttributeRmsVoltageSagPeriodPhaseBWithCompletionHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completionHandler ZGMTR_DEPRECATED("Please use readAttributeRmsVoltageSagPeriodPhaseBWithCompletion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (void)subscribeAttributeRmsVoltageSagPeriodPhaseBWithMinInterval:(NSNumber * _Nonnull)minInterval maxInterval:(NSNumber * _Nonnull)maxInterval
                                                            params:(ZGMTRSubscribeParams * _Nullable)params
                                           subscriptionEstablished:(ZGMTRSubscriptionEstablishedHandler _Nullable)subscriptionEstablishedHandler
                                                     reportHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))reportHandler ZGMTR_DEPRECATED("Please use subscribeAttributeRmsVoltageSagPeriodPhaseBWithParams:subscriptionEstablished:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
+ (void)readAttributeRmsVoltageSagPeriodPhaseBWithAttributeCache:(ZGMTRAttributeCacheContainer *)attributeCacheContainer endpoint:(NSNumber *)endpoint queue:(dispatch_queue_t)queue completionHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completionHandler ZGMTR_DEPRECATED("Please use readAttributeRmsVoltageSagPeriodPhaseBWithAttributeCache:endpoint:queue:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));

- (void)readAttributeRmsVoltageSwellPeriodPhaseBWithCompletionHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completionHandler ZGMTR_DEPRECATED("Please use readAttributeRmsVoltageSwellPeriodPhaseBWithCompletion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (void)subscribeAttributeRmsVoltageSwellPeriodPhaseBWithMinInterval:(NSNumber * _Nonnull)minInterval maxInterval:(NSNumber * _Nonnull)maxInterval
                                                              params:(ZGMTRSubscribeParams * _Nullable)params
                                             subscriptionEstablished:(ZGMTRSubscriptionEstablishedHandler _Nullable)subscriptionEstablishedHandler
                                                       reportHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))reportHandler ZGMTR_DEPRECATED("Please use subscribeAttributeRmsVoltageSwellPeriodPhaseBWithParams:subscriptionEstablished:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
+ (void)readAttributeRmsVoltageSwellPeriodPhaseBWithAttributeCache:(ZGMTRAttributeCacheContainer *)attributeCacheContainer endpoint:(NSNumber *)endpoint queue:(dispatch_queue_t)queue completionHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completionHandler ZGMTR_DEPRECATED("Please use readAttributeRmsVoltageSwellPeriodPhaseBWithAttributeCache:endpoint:queue:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));

- (void)readAttributeLineCurrentPhaseCWithCompletionHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completionHandler ZGMTR_DEPRECATED("Please use readAttributeLineCurrentPhaseCWithCompletion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (void)subscribeAttributeLineCurrentPhaseCWithMinInterval:(NSNumber * _Nonnull)minInterval maxInterval:(NSNumber * _Nonnull)maxInterval
                                                    params:(ZGMTRSubscribeParams * _Nullable)params
                                   subscriptionEstablished:(ZGMTRSubscriptionEstablishedHandler _Nullable)subscriptionEstablishedHandler
                                             reportHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))reportHandler ZGMTR_DEPRECATED("Please use subscribeAttributeLineCurrentPhaseCWithParams:subscriptionEstablished:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
+ (void)readAttributeLineCurrentPhaseCWithAttributeCache:(ZGMTRAttributeCacheContainer *)attributeCacheContainer endpoint:(NSNumber *)endpoint queue:(dispatch_queue_t)queue completionHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completionHandler ZGMTR_DEPRECATED("Please use readAttributeLineCurrentPhaseCWithAttributeCache:endpoint:queue:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));

- (void)readAttributeActiveCurrentPhaseCWithCompletionHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completionHandler ZGMTR_DEPRECATED("Please use readAttributeActiveCurrentPhaseCWithCompletion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (void)subscribeAttributeActiveCurrentPhaseCWithMinInterval:(NSNumber * _Nonnull)minInterval maxInterval:(NSNumber * _Nonnull)maxInterval
                                                      params:(ZGMTRSubscribeParams * _Nullable)params
                                     subscriptionEstablished:(ZGMTRSubscriptionEstablishedHandler _Nullable)subscriptionEstablishedHandler
                                               reportHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))reportHandler ZGMTR_DEPRECATED("Please use subscribeAttributeActiveCurrentPhaseCWithParams:subscriptionEstablished:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
+ (void)readAttributeActiveCurrentPhaseCWithAttributeCache:(ZGMTRAttributeCacheContainer *)attributeCacheContainer endpoint:(NSNumber *)endpoint queue:(dispatch_queue_t)queue completionHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completionHandler ZGMTR_DEPRECATED("Please use readAttributeActiveCurrentPhaseCWithAttributeCache:endpoint:queue:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));

- (void)readAttributeReactiveCurrentPhaseCWithCompletionHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completionHandler ZGMTR_DEPRECATED("Please use readAttributeReactiveCurrentPhaseCWithCompletion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (void)subscribeAttributeReactiveCurrentPhaseCWithMinInterval:(NSNumber * _Nonnull)minInterval maxInterval:(NSNumber * _Nonnull)maxInterval
                                                        params:(ZGMTRSubscribeParams * _Nullable)params
                                       subscriptionEstablished:(ZGMTRSubscriptionEstablishedHandler _Nullable)subscriptionEstablishedHandler
                                                 reportHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))reportHandler ZGMTR_DEPRECATED("Please use subscribeAttributeReactiveCurrentPhaseCWithParams:subscriptionEstablished:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
+ (void)readAttributeReactiveCurrentPhaseCWithAttributeCache:(ZGMTRAttributeCacheContainer *)attributeCacheContainer endpoint:(NSNumber *)endpoint queue:(dispatch_queue_t)queue completionHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completionHandler ZGMTR_DEPRECATED("Please use readAttributeReactiveCurrentPhaseCWithAttributeCache:endpoint:queue:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));

- (void)readAttributeRmsVoltagePhaseCWithCompletionHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completionHandler ZGMTR_DEPRECATED("Please use readAttributeRmsVoltagePhaseCWithCompletion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (void)subscribeAttributeRmsVoltagePhaseCWithMinInterval:(NSNumber * _Nonnull)minInterval maxInterval:(NSNumber * _Nonnull)maxInterval
                                                   params:(ZGMTRSubscribeParams * _Nullable)params
                                  subscriptionEstablished:(ZGMTRSubscriptionEstablishedHandler _Nullable)subscriptionEstablishedHandler
                                            reportHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))reportHandler ZGMTR_DEPRECATED("Please use subscribeAttributeRmsVoltagePhaseCWithParams:subscriptionEstablished:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
+ (void)readAttributeRmsVoltagePhaseCWithAttributeCache:(ZGMTRAttributeCacheContainer *)attributeCacheContainer endpoint:(NSNumber *)endpoint queue:(dispatch_queue_t)queue completionHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completionHandler ZGMTR_DEPRECATED("Please use readAttributeRmsVoltagePhaseCWithAttributeCache:endpoint:queue:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));

- (void)readAttributeRmsVoltageMinPhaseCWithCompletionHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completionHandler ZGMTR_DEPRECATED("Please use readAttributeRmsVoltageMinPhaseCWithCompletion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (void)subscribeAttributeRmsVoltageMinPhaseCWithMinInterval:(NSNumber * _Nonnull)minInterval maxInterval:(NSNumber * _Nonnull)maxInterval
                                                      params:(ZGMTRSubscribeParams * _Nullable)params
                                     subscriptionEstablished:(ZGMTRSubscriptionEstablishedHandler _Nullable)subscriptionEstablishedHandler
                                               reportHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))reportHandler ZGMTR_DEPRECATED("Please use subscribeAttributeRmsVoltageMinPhaseCWithParams:subscriptionEstablished:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
+ (void)readAttributeRmsVoltageMinPhaseCWithAttributeCache:(ZGMTRAttributeCacheContainer *)attributeCacheContainer endpoint:(NSNumber *)endpoint queue:(dispatch_queue_t)queue completionHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completionHandler ZGMTR_DEPRECATED("Please use readAttributeRmsVoltageMinPhaseCWithAttributeCache:endpoint:queue:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));

- (void)readAttributeRmsVoltageMaxPhaseCWithCompletionHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completionHandler ZGMTR_DEPRECATED("Please use readAttributeRmsVoltageMaxPhaseCWithCompletion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (void)subscribeAttributeRmsVoltageMaxPhaseCWithMinInterval:(NSNumber * _Nonnull)minInterval maxInterval:(NSNumber * _Nonnull)maxInterval
                                                      params:(ZGMTRSubscribeParams * _Nullable)params
                                     subscriptionEstablished:(ZGMTRSubscriptionEstablishedHandler _Nullable)subscriptionEstablishedHandler
                                               reportHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))reportHandler ZGMTR_DEPRECATED("Please use subscribeAttributeRmsVoltageMaxPhaseCWithParams:subscriptionEstablished:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
+ (void)readAttributeRmsVoltageMaxPhaseCWithAttributeCache:(ZGMTRAttributeCacheContainer *)attributeCacheContainer endpoint:(NSNumber *)endpoint queue:(dispatch_queue_t)queue completionHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completionHandler ZGMTR_DEPRECATED("Please use readAttributeRmsVoltageMaxPhaseCWithAttributeCache:endpoint:queue:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));

- (void)readAttributeRmsCurrentPhaseCWithCompletionHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completionHandler ZGMTR_DEPRECATED("Please use readAttributeRmsCurrentPhaseCWithCompletion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (void)subscribeAttributeRmsCurrentPhaseCWithMinInterval:(NSNumber * _Nonnull)minInterval maxInterval:(NSNumber * _Nonnull)maxInterval
                                                   params:(ZGMTRSubscribeParams * _Nullable)params
                                  subscriptionEstablished:(ZGMTRSubscriptionEstablishedHandler _Nullable)subscriptionEstablishedHandler
                                            reportHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))reportHandler ZGMTR_DEPRECATED("Please use subscribeAttributeRmsCurrentPhaseCWithParams:subscriptionEstablished:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
+ (void)readAttributeRmsCurrentPhaseCWithAttributeCache:(ZGMTRAttributeCacheContainer *)attributeCacheContainer endpoint:(NSNumber *)endpoint queue:(dispatch_queue_t)queue completionHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completionHandler ZGMTR_DEPRECATED("Please use readAttributeRmsCurrentPhaseCWithAttributeCache:endpoint:queue:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));

- (void)readAttributeRmsCurrentMinPhaseCWithCompletionHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completionHandler ZGMTR_DEPRECATED("Please use readAttributeRmsCurrentMinPhaseCWithCompletion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (void)subscribeAttributeRmsCurrentMinPhaseCWithMinInterval:(NSNumber * _Nonnull)minInterval maxInterval:(NSNumber * _Nonnull)maxInterval
                                                      params:(ZGMTRSubscribeParams * _Nullable)params
                                     subscriptionEstablished:(ZGMTRSubscriptionEstablishedHandler _Nullable)subscriptionEstablishedHandler
                                               reportHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))reportHandler ZGMTR_DEPRECATED("Please use subscribeAttributeRmsCurrentMinPhaseCWithParams:subscriptionEstablished:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
+ (void)readAttributeRmsCurrentMinPhaseCWithAttributeCache:(ZGMTRAttributeCacheContainer *)attributeCacheContainer endpoint:(NSNumber *)endpoint queue:(dispatch_queue_t)queue completionHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completionHandler ZGMTR_DEPRECATED("Please use readAttributeRmsCurrentMinPhaseCWithAttributeCache:endpoint:queue:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));

- (void)readAttributeRmsCurrentMaxPhaseCWithCompletionHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completionHandler ZGMTR_DEPRECATED("Please use readAttributeRmsCurrentMaxPhaseCWithCompletion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (void)subscribeAttributeRmsCurrentMaxPhaseCWithMinInterval:(NSNumber * _Nonnull)minInterval maxInterval:(NSNumber * _Nonnull)maxInterval
                                                      params:(ZGMTRSubscribeParams * _Nullable)params
                                     subscriptionEstablished:(ZGMTRSubscriptionEstablishedHandler _Nullable)subscriptionEstablishedHandler
                                               reportHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))reportHandler ZGMTR_DEPRECATED("Please use subscribeAttributeRmsCurrentMaxPhaseCWithParams:subscriptionEstablished:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
+ (void)readAttributeRmsCurrentMaxPhaseCWithAttributeCache:(ZGMTRAttributeCacheContainer *)attributeCacheContainer endpoint:(NSNumber *)endpoint queue:(dispatch_queue_t)queue completionHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completionHandler ZGMTR_DEPRECATED("Please use readAttributeRmsCurrentMaxPhaseCWithAttributeCache:endpoint:queue:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));

- (void)readAttributeActivePowerPhaseCWithCompletionHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completionHandler ZGMTR_DEPRECATED("Please use readAttributeActivePowerPhaseCWithCompletion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (void)subscribeAttributeActivePowerPhaseCWithMinInterval:(NSNumber * _Nonnull)minInterval maxInterval:(NSNumber * _Nonnull)maxInterval
                                                    params:(ZGMTRSubscribeParams * _Nullable)params
                                   subscriptionEstablished:(ZGMTRSubscriptionEstablishedHandler _Nullable)subscriptionEstablishedHandler
                                             reportHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))reportHandler ZGMTR_DEPRECATED("Please use subscribeAttributeActivePowerPhaseCWithParams:subscriptionEstablished:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
+ (void)readAttributeActivePowerPhaseCWithAttributeCache:(ZGMTRAttributeCacheContainer *)attributeCacheContainer endpoint:(NSNumber *)endpoint queue:(dispatch_queue_t)queue completionHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completionHandler ZGMTR_DEPRECATED("Please use readAttributeActivePowerPhaseCWithAttributeCache:endpoint:queue:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));

- (void)readAttributeActivePowerMinPhaseCWithCompletionHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completionHandler ZGMTR_DEPRECATED("Please use readAttributeActivePowerMinPhaseCWithCompletion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (void)subscribeAttributeActivePowerMinPhaseCWithMinInterval:(NSNumber * _Nonnull)minInterval maxInterval:(NSNumber * _Nonnull)maxInterval
                                                       params:(ZGMTRSubscribeParams * _Nullable)params
                                      subscriptionEstablished:(ZGMTRSubscriptionEstablishedHandler _Nullable)subscriptionEstablishedHandler
                                                reportHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))reportHandler ZGMTR_DEPRECATED("Please use subscribeAttributeActivePowerMinPhaseCWithParams:subscriptionEstablished:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
+ (void)readAttributeActivePowerMinPhaseCWithAttributeCache:(ZGMTRAttributeCacheContainer *)attributeCacheContainer endpoint:(NSNumber *)endpoint queue:(dispatch_queue_t)queue completionHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completionHandler ZGMTR_DEPRECATED("Please use readAttributeActivePowerMinPhaseCWithAttributeCache:endpoint:queue:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));

- (void)readAttributeActivePowerMaxPhaseCWithCompletionHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completionHandler ZGMTR_DEPRECATED("Please use readAttributeActivePowerMaxPhaseCWithCompletion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (void)subscribeAttributeActivePowerMaxPhaseCWithMinInterval:(NSNumber * _Nonnull)minInterval maxInterval:(NSNumber * _Nonnull)maxInterval
                                                       params:(ZGMTRSubscribeParams * _Nullable)params
                                      subscriptionEstablished:(ZGMTRSubscriptionEstablishedHandler _Nullable)subscriptionEstablishedHandler
                                                reportHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))reportHandler ZGMTR_DEPRECATED("Please use subscribeAttributeActivePowerMaxPhaseCWithParams:subscriptionEstablished:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
+ (void)readAttributeActivePowerMaxPhaseCWithAttributeCache:(ZGMTRAttributeCacheContainer *)attributeCacheContainer endpoint:(NSNumber *)endpoint queue:(dispatch_queue_t)queue completionHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completionHandler ZGMTR_DEPRECATED("Please use readAttributeActivePowerMaxPhaseCWithAttributeCache:endpoint:queue:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));

- (void)readAttributeReactivePowerPhaseCWithCompletionHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completionHandler ZGMTR_DEPRECATED("Please use readAttributeReactivePowerPhaseCWithCompletion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (void)subscribeAttributeReactivePowerPhaseCWithMinInterval:(NSNumber * _Nonnull)minInterval maxInterval:(NSNumber * _Nonnull)maxInterval
                                                      params:(ZGMTRSubscribeParams * _Nullable)params
                                     subscriptionEstablished:(ZGMTRSubscriptionEstablishedHandler _Nullable)subscriptionEstablishedHandler
                                               reportHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))reportHandler ZGMTR_DEPRECATED("Please use subscribeAttributeReactivePowerPhaseCWithParams:subscriptionEstablished:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
+ (void)readAttributeReactivePowerPhaseCWithAttributeCache:(ZGMTRAttributeCacheContainer *)attributeCacheContainer endpoint:(NSNumber *)endpoint queue:(dispatch_queue_t)queue completionHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completionHandler ZGMTR_DEPRECATED("Please use readAttributeReactivePowerPhaseCWithAttributeCache:endpoint:queue:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));

- (void)readAttributeApparentPowerPhaseCWithCompletionHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completionHandler ZGMTR_DEPRECATED("Please use readAttributeApparentPowerPhaseCWithCompletion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (void)subscribeAttributeApparentPowerPhaseCWithMinInterval:(NSNumber * _Nonnull)minInterval maxInterval:(NSNumber * _Nonnull)maxInterval
                                                      params:(ZGMTRSubscribeParams * _Nullable)params
                                     subscriptionEstablished:(ZGMTRSubscriptionEstablishedHandler _Nullable)subscriptionEstablishedHandler
                                               reportHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))reportHandler ZGMTR_DEPRECATED("Please use subscribeAttributeApparentPowerPhaseCWithParams:subscriptionEstablished:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
+ (void)readAttributeApparentPowerPhaseCWithAttributeCache:(ZGMTRAttributeCacheContainer *)attributeCacheContainer endpoint:(NSNumber *)endpoint queue:(dispatch_queue_t)queue completionHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completionHandler ZGMTR_DEPRECATED("Please use readAttributeApparentPowerPhaseCWithAttributeCache:endpoint:queue:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));

- (void)readAttributePowerFactorPhaseCWithCompletionHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completionHandler ZGMTR_DEPRECATED("Please use readAttributePowerFactorPhaseCWithCompletion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (void)subscribeAttributePowerFactorPhaseCWithMinInterval:(NSNumber * _Nonnull)minInterval maxInterval:(NSNumber * _Nonnull)maxInterval
                                                    params:(ZGMTRSubscribeParams * _Nullable)params
                                   subscriptionEstablished:(ZGMTRSubscriptionEstablishedHandler _Nullable)subscriptionEstablishedHandler
                                             reportHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))reportHandler ZGMTR_DEPRECATED("Please use subscribeAttributePowerFactorPhaseCWithParams:subscriptionEstablished:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
+ (void)readAttributePowerFactorPhaseCWithAttributeCache:(ZGMTRAttributeCacheContainer *)attributeCacheContainer endpoint:(NSNumber *)endpoint queue:(dispatch_queue_t)queue completionHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completionHandler ZGMTR_DEPRECATED("Please use readAttributePowerFactorPhaseCWithAttributeCache:endpoint:queue:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));

- (void)readAttributeAverageRmsVoltageMeasurementPeriodPhaseCWithCompletionHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completionHandler ZGMTR_DEPRECATED("Please use readAttributeAverageRmsVoltageMeasurementPeriodPhaseCWithCompletion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (void)subscribeAttributeAverageRmsVoltageMeasurementPeriodPhaseCWithMinInterval:(NSNumber * _Nonnull)minInterval maxInterval:(NSNumber * _Nonnull)maxInterval
                                                                           params:(ZGMTRSubscribeParams * _Nullable)params
                                                          subscriptionEstablished:(ZGMTRSubscriptionEstablishedHandler _Nullable)subscriptionEstablishedHandler
                                                                    reportHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))reportHandler ZGMTR_DEPRECATED("Please use subscribeAttributeAverageRmsVoltageMeasurementPeriodPhaseCWithParams:subscriptionEstablished:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
+ (void)readAttributeAverageRmsVoltageMeasurementPeriodPhaseCWithAttributeCache:(ZGMTRAttributeCacheContainer *)attributeCacheContainer endpoint:(NSNumber *)endpoint queue:(dispatch_queue_t)queue completionHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completionHandler ZGMTR_DEPRECATED("Please use readAttributeAverageRmsVoltageMeasurementPeriodPhaseCWithAttributeCache:endpoint:queue:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));

- (void)readAttributeAverageRmsOverVoltageCounterPhaseCWithCompletionHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completionHandler ZGMTR_DEPRECATED("Please use readAttributeAverageRmsOverVoltageCounterPhaseCWithCompletion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (void)subscribeAttributeAverageRmsOverVoltageCounterPhaseCWithMinInterval:(NSNumber * _Nonnull)minInterval maxInterval:(NSNumber * _Nonnull)maxInterval
                                                                     params:(ZGMTRSubscribeParams * _Nullable)params
                                                    subscriptionEstablished:(ZGMTRSubscriptionEstablishedHandler _Nullable)subscriptionEstablishedHandler
                                                              reportHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))reportHandler ZGMTR_DEPRECATED("Please use subscribeAttributeAverageRmsOverVoltageCounterPhaseCWithParams:subscriptionEstablished:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
+ (void)readAttributeAverageRmsOverVoltageCounterPhaseCWithAttributeCache:(ZGMTRAttributeCacheContainer *)attributeCacheContainer endpoint:(NSNumber *)endpoint queue:(dispatch_queue_t)queue completionHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completionHandler ZGMTR_DEPRECATED("Please use readAttributeAverageRmsOverVoltageCounterPhaseCWithAttributeCache:endpoint:queue:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));

- (void)readAttributeAverageRmsUnderVoltageCounterPhaseCWithCompletionHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completionHandler ZGMTR_DEPRECATED("Please use readAttributeAverageRmsUnderVoltageCounterPhaseCWithCompletion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (void)subscribeAttributeAverageRmsUnderVoltageCounterPhaseCWithMinInterval:(NSNumber * _Nonnull)minInterval maxInterval:(NSNumber * _Nonnull)maxInterval
                                                                      params:(ZGMTRSubscribeParams * _Nullable)params
                                                     subscriptionEstablished:(ZGMTRSubscriptionEstablishedHandler _Nullable)subscriptionEstablishedHandler
                                                               reportHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))reportHandler ZGMTR_DEPRECATED("Please use subscribeAttributeAverageRmsUnderVoltageCounterPhaseCWithParams:subscriptionEstablished:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
+ (void)readAttributeAverageRmsUnderVoltageCounterPhaseCWithAttributeCache:(ZGMTRAttributeCacheContainer *)attributeCacheContainer endpoint:(NSNumber *)endpoint queue:(dispatch_queue_t)queue completionHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completionHandler ZGMTR_DEPRECATED("Please use readAttributeAverageRmsUnderVoltageCounterPhaseCWithAttributeCache:endpoint:queue:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));

- (void)readAttributeRmsExtremeOverVoltagePeriodPhaseCWithCompletionHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completionHandler ZGMTR_DEPRECATED("Please use readAttributeRmsExtremeOverVoltagePeriodPhaseCWithCompletion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (void)subscribeAttributeRmsExtremeOverVoltagePeriodPhaseCWithMinInterval:(NSNumber * _Nonnull)minInterval maxInterval:(NSNumber * _Nonnull)maxInterval
                                                                    params:(ZGMTRSubscribeParams * _Nullable)params
                                                   subscriptionEstablished:(ZGMTRSubscriptionEstablishedHandler _Nullable)subscriptionEstablishedHandler
                                                             reportHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))reportHandler ZGMTR_DEPRECATED("Please use subscribeAttributeRmsExtremeOverVoltagePeriodPhaseCWithParams:subscriptionEstablished:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
+ (void)readAttributeRmsExtremeOverVoltagePeriodPhaseCWithAttributeCache:(ZGMTRAttributeCacheContainer *)attributeCacheContainer endpoint:(NSNumber *)endpoint queue:(dispatch_queue_t)queue completionHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completionHandler ZGMTR_DEPRECATED("Please use readAttributeRmsExtremeOverVoltagePeriodPhaseCWithAttributeCache:endpoint:queue:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));

- (void)readAttributeRmsExtremeUnderVoltagePeriodPhaseCWithCompletionHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completionHandler ZGMTR_DEPRECATED("Please use readAttributeRmsExtremeUnderVoltagePeriodPhaseCWithCompletion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (void)subscribeAttributeRmsExtremeUnderVoltagePeriodPhaseCWithMinInterval:(NSNumber * _Nonnull)minInterval maxInterval:(NSNumber * _Nonnull)maxInterval
                                                                     params:(ZGMTRSubscribeParams * _Nullable)params
                                                    subscriptionEstablished:(ZGMTRSubscriptionEstablishedHandler _Nullable)subscriptionEstablishedHandler
                                                              reportHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))reportHandler ZGMTR_DEPRECATED("Please use subscribeAttributeRmsExtremeUnderVoltagePeriodPhaseCWithParams:subscriptionEstablished:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
+ (void)readAttributeRmsExtremeUnderVoltagePeriodPhaseCWithAttributeCache:(ZGMTRAttributeCacheContainer *)attributeCacheContainer endpoint:(NSNumber *)endpoint queue:(dispatch_queue_t)queue completionHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completionHandler ZGMTR_DEPRECATED("Please use readAttributeRmsExtremeUnderVoltagePeriodPhaseCWithAttributeCache:endpoint:queue:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));

- (void)readAttributeRmsVoltageSagPeriodPhaseCWithCompletionHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completionHandler ZGMTR_DEPRECATED("Please use readAttributeRmsVoltageSagPeriodPhaseCWithCompletion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (void)subscribeAttributeRmsVoltageSagPeriodPhaseCWithMinInterval:(NSNumber * _Nonnull)minInterval maxInterval:(NSNumber * _Nonnull)maxInterval
                                                            params:(ZGMTRSubscribeParams * _Nullable)params
                                           subscriptionEstablished:(ZGMTRSubscriptionEstablishedHandler _Nullable)subscriptionEstablishedHandler
                                                     reportHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))reportHandler ZGMTR_DEPRECATED("Please use subscribeAttributeRmsVoltageSagPeriodPhaseCWithParams:subscriptionEstablished:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
+ (void)readAttributeRmsVoltageSagPeriodPhaseCWithAttributeCache:(ZGMTRAttributeCacheContainer *)attributeCacheContainer endpoint:(NSNumber *)endpoint queue:(dispatch_queue_t)queue completionHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completionHandler ZGMTR_DEPRECATED("Please use readAttributeRmsVoltageSagPeriodPhaseCWithAttributeCache:endpoint:queue:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));

- (void)readAttributeRmsVoltageSwellPeriodPhaseCWithCompletionHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completionHandler ZGMTR_DEPRECATED("Please use readAttributeRmsVoltageSwellPeriodPhaseCWithCompletion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (void)subscribeAttributeRmsVoltageSwellPeriodPhaseCWithMinInterval:(NSNumber * _Nonnull)minInterval maxInterval:(NSNumber * _Nonnull)maxInterval
                                                              params:(ZGMTRSubscribeParams * _Nullable)params
                                             subscriptionEstablished:(ZGMTRSubscriptionEstablishedHandler _Nullable)subscriptionEstablishedHandler
                                                       reportHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))reportHandler ZGMTR_DEPRECATED("Please use subscribeAttributeRmsVoltageSwellPeriodPhaseCWithParams:subscriptionEstablished:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
+ (void)readAttributeRmsVoltageSwellPeriodPhaseCWithAttributeCache:(ZGMTRAttributeCacheContainer *)attributeCacheContainer endpoint:(NSNumber *)endpoint queue:(dispatch_queue_t)queue completionHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completionHandler ZGMTR_DEPRECATED("Please use readAttributeRmsVoltageSwellPeriodPhaseCWithAttributeCache:endpoint:queue:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));

- (void)readAttributeGeneratedCommandListWithCompletionHandler:(void (^)(NSArray * _Nullable value, NSError * _Nullable error))completionHandler ZGMTR_DEPRECATED("Please use readAttributeGeneratedCommandListWithCompletion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (void)subscribeAttributeGeneratedCommandListWithMinInterval:(NSNumber * _Nonnull)minInterval maxInterval:(NSNumber * _Nonnull)maxInterval
                                                       params:(ZGMTRSubscribeParams * _Nullable)params
                                      subscriptionEstablished:(ZGMTRSubscriptionEstablishedHandler _Nullable)subscriptionEstablishedHandler
                                                reportHandler:(void (^)(NSArray * _Nullable value, NSError * _Nullable error))reportHandler ZGMTR_DEPRECATED("Please use subscribeAttributeGeneratedCommandListWithParams:subscriptionEstablished:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
+ (void)readAttributeGeneratedCommandListWithAttributeCache:(ZGMTRAttributeCacheContainer *)attributeCacheContainer endpoint:(NSNumber *)endpoint queue:(dispatch_queue_t)queue completionHandler:(void (^)(NSArray * _Nullable value, NSError * _Nullable error))completionHandler ZGMTR_DEPRECATED("Please use readAttributeGeneratedCommandListWithAttributeCache:endpoint:queue:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));

- (void)readAttributeAcceptedCommandListWithCompletionHandler:(void (^)(NSArray * _Nullable value, NSError * _Nullable error))completionHandler ZGMTR_DEPRECATED("Please use readAttributeAcceptedCommandListWithCompletion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (void)subscribeAttributeAcceptedCommandListWithMinInterval:(NSNumber * _Nonnull)minInterval maxInterval:(NSNumber * _Nonnull)maxInterval
                                                      params:(ZGMTRSubscribeParams * _Nullable)params
                                     subscriptionEstablished:(ZGMTRSubscriptionEstablishedHandler _Nullable)subscriptionEstablishedHandler
                                               reportHandler:(void (^)(NSArray * _Nullable value, NSError * _Nullable error))reportHandler ZGMTR_DEPRECATED("Please use subscribeAttributeAcceptedCommandListWithParams:subscriptionEstablished:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
+ (void)readAttributeAcceptedCommandListWithAttributeCache:(ZGMTRAttributeCacheContainer *)attributeCacheContainer endpoint:(NSNumber *)endpoint queue:(dispatch_queue_t)queue completionHandler:(void (^)(NSArray * _Nullable value, NSError * _Nullable error))completionHandler ZGMTR_DEPRECATED("Please use readAttributeAcceptedCommandListWithAttributeCache:endpoint:queue:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));

- (void)readAttributeAttributeListWithCompletionHandler:(void (^)(NSArray * _Nullable value, NSError * _Nullable error))completionHandler ZGMTR_DEPRECATED("Please use readAttributeAttributeListWithCompletion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (void)subscribeAttributeAttributeListWithMinInterval:(NSNumber * _Nonnull)minInterval maxInterval:(NSNumber * _Nonnull)maxInterval
                                                params:(ZGMTRSubscribeParams * _Nullable)params
                               subscriptionEstablished:(ZGMTRSubscriptionEstablishedHandler _Nullable)subscriptionEstablishedHandler
                                         reportHandler:(void (^)(NSArray * _Nullable value, NSError * _Nullable error))reportHandler ZGMTR_DEPRECATED("Please use subscribeAttributeAttributeListWithParams:subscriptionEstablished:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
+ (void)readAttributeAttributeListWithAttributeCache:(ZGMTRAttributeCacheContainer *)attributeCacheContainer endpoint:(NSNumber *)endpoint queue:(dispatch_queue_t)queue completionHandler:(void (^)(NSArray * _Nullable value, NSError * _Nullable error))completionHandler ZGMTR_DEPRECATED("Please use readAttributeAttributeListWithAttributeCache:endpoint:queue:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));

- (void)readAttributeFeatureMapWithCompletionHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completionHandler ZGMTR_DEPRECATED("Please use readAttributeFeatureMapWithCompletion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (void)subscribeAttributeFeatureMapWithMinInterval:(NSNumber * _Nonnull)minInterval maxInterval:(NSNumber * _Nonnull)maxInterval
                                             params:(ZGMTRSubscribeParams * _Nullable)params
                            subscriptionEstablished:(ZGMTRSubscriptionEstablishedHandler _Nullable)subscriptionEstablishedHandler
                                      reportHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))reportHandler ZGMTR_DEPRECATED("Please use subscribeAttributeFeatureMapWithParams:subscriptionEstablished:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
+ (void)readAttributeFeatureMapWithAttributeCache:(ZGMTRAttributeCacheContainer *)attributeCacheContainer endpoint:(NSNumber *)endpoint queue:(dispatch_queue_t)queue completionHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completionHandler ZGMTR_DEPRECATED("Please use readAttributeFeatureMapWithAttributeCache:endpoint:queue:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));

- (void)readAttributeClusterRevisionWithCompletionHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completionHandler ZGMTR_DEPRECATED("Please use readAttributeClusterRevisionWithCompletion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (void)subscribeAttributeClusterRevisionWithMinInterval:(NSNumber * _Nonnull)minInterval maxInterval:(NSNumber * _Nonnull)maxInterval
                                                  params:(ZGMTRSubscribeParams * _Nullable)params
                                 subscriptionEstablished:(ZGMTRSubscriptionEstablishedHandler _Nullable)subscriptionEstablishedHandler
                                           reportHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))reportHandler ZGMTR_DEPRECATED("Please use subscribeAttributeClusterRevisionWithParams:subscriptionEstablished:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
+ (void)readAttributeClusterRevisionWithAttributeCache:(ZGMTRAttributeCacheContainer *)attributeCacheContainer endpoint:(NSNumber *)endpoint queue:(dispatch_queue_t)queue completionHandler:(void (^)(NSNumber * _Nullable value, NSError * _Nullable error))completionHandler ZGMTR_DEPRECATED("Please use readAttributeClusterRevisionWithAttributeCache:endpoint:queue:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));

@end

/**
 * Cluster Electrical Measurement
 *    Attributes related to the electrical properties of a device. This cluster is used by power outlets and other devices that need to provide instantaneous data as opposed to metrology data which should be retrieved from the metering cluster..
 */
ZGMTR_DEPRECATED("ElectricalMeasurement is deprecated and will be removed", ios(16.1, 18.2), macos(13.0, 15.2), watchos(9.1, 11.2), tvos(16.1, 18.2))
@interface ZGMTRClusterElectricalMeasurement : ZGMTRGenericCluster

- (void)getProfileInfoCommandWithParams:(ZGMTRElectricalMeasurementClusterGetProfileInfoCommandParams * _Nullable)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(ZGMTRStatusCompletion)completion ZGMTR_DEPRECATED("This command is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));
- (void)getProfileInfoCommandWithExpectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedValues expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(ZGMTRStatusCompletion)completion
    ZGMTR_DEPRECATED("This command is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));
- (void)getMeasurementProfileCommandWithParams:(ZGMTRElectricalMeasurementClusterGetMeasurementProfileCommandParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completion:(ZGMTRStatusCompletion)completion ZGMTR_DEPRECATED("This command is deprecated", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeMeasurementTypeWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.1, 18.2), macos(13.0, 15.2), watchos(9.1, 11.2), tvos(16.1, 18.2));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeDcVoltageWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.1, 18.2), macos(13.0, 15.2), watchos(9.1, 11.2), tvos(16.1, 18.2));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeDcVoltageMinWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.1, 18.2), macos(13.0, 15.2), watchos(9.1, 11.2), tvos(16.1, 18.2));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeDcVoltageMaxWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.1, 18.2), macos(13.0, 15.2), watchos(9.1, 11.2), tvos(16.1, 18.2));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeDcCurrentWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.1, 18.2), macos(13.0, 15.2), watchos(9.1, 11.2), tvos(16.1, 18.2));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeDcCurrentMinWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.1, 18.2), macos(13.0, 15.2), watchos(9.1, 11.2), tvos(16.1, 18.2));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeDcCurrentMaxWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.1, 18.2), macos(13.0, 15.2), watchos(9.1, 11.2), tvos(16.1, 18.2));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeDcPowerWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.1, 18.2), macos(13.0, 15.2), watchos(9.1, 11.2), tvos(16.1, 18.2));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeDcPowerMinWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.1, 18.2), macos(13.0, 15.2), watchos(9.1, 11.2), tvos(16.1, 18.2));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeDcPowerMaxWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.1, 18.2), macos(13.0, 15.2), watchos(9.1, 11.2), tvos(16.1, 18.2));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeDcVoltageMultiplierWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.1, 18.2), macos(13.0, 15.2), watchos(9.1, 11.2), tvos(16.1, 18.2));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeDcVoltageDivisorWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.1, 18.2), macos(13.0, 15.2), watchos(9.1, 11.2), tvos(16.1, 18.2));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeDcCurrentMultiplierWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.1, 18.2), macos(13.0, 15.2), watchos(9.1, 11.2), tvos(16.1, 18.2));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeDcCurrentDivisorWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.1, 18.2), macos(13.0, 15.2), watchos(9.1, 11.2), tvos(16.1, 18.2));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeDcPowerMultiplierWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.1, 18.2), macos(13.0, 15.2), watchos(9.1, 11.2), tvos(16.1, 18.2));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeDcPowerDivisorWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.1, 18.2), macos(13.0, 15.2), watchos(9.1, 11.2), tvos(16.1, 18.2));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeAcFrequencyWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.1, 18.2), macos(13.0, 15.2), watchos(9.1, 11.2), tvos(16.1, 18.2));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeAcFrequencyMinWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.1, 18.2), macos(13.0, 15.2), watchos(9.1, 11.2), tvos(16.1, 18.2));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeAcFrequencyMaxWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.1, 18.2), macos(13.0, 15.2), watchos(9.1, 11.2), tvos(16.1, 18.2));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeNeutralCurrentWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.1, 18.2), macos(13.0, 15.2), watchos(9.1, 11.2), tvos(16.1, 18.2));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeTotalActivePowerWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.1, 18.2), macos(13.0, 15.2), watchos(9.1, 11.2), tvos(16.1, 18.2));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeTotalReactivePowerWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.1, 18.2), macos(13.0, 15.2), watchos(9.1, 11.2), tvos(16.1, 18.2));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeTotalApparentPowerWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.1, 18.2), macos(13.0, 15.2), watchos(9.1, 11.2), tvos(16.1, 18.2));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeMeasured1stHarmonicCurrentWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.1, 18.2), macos(13.0, 15.2), watchos(9.1, 11.2), tvos(16.1, 18.2));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeMeasured3rdHarmonicCurrentWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.1, 18.2), macos(13.0, 15.2), watchos(9.1, 11.2), tvos(16.1, 18.2));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeMeasured5thHarmonicCurrentWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.1, 18.2), macos(13.0, 15.2), watchos(9.1, 11.2), tvos(16.1, 18.2));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeMeasured7thHarmonicCurrentWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.1, 18.2), macos(13.0, 15.2), watchos(9.1, 11.2), tvos(16.1, 18.2));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeMeasured9thHarmonicCurrentWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.1, 18.2), macos(13.0, 15.2), watchos(9.1, 11.2), tvos(16.1, 18.2));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeMeasured11thHarmonicCurrentWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.1, 18.2), macos(13.0, 15.2), watchos(9.1, 11.2), tvos(16.1, 18.2));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeMeasuredPhase1stHarmonicCurrentWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.1, 18.2), macos(13.0, 15.2), watchos(9.1, 11.2), tvos(16.1, 18.2));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeMeasuredPhase3rdHarmonicCurrentWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.1, 18.2), macos(13.0, 15.2), watchos(9.1, 11.2), tvos(16.1, 18.2));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeMeasuredPhase5thHarmonicCurrentWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.1, 18.2), macos(13.0, 15.2), watchos(9.1, 11.2), tvos(16.1, 18.2));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeMeasuredPhase7thHarmonicCurrentWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.1, 18.2), macos(13.0, 15.2), watchos(9.1, 11.2), tvos(16.1, 18.2));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeMeasuredPhase9thHarmonicCurrentWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.1, 18.2), macos(13.0, 15.2), watchos(9.1, 11.2), tvos(16.1, 18.2));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeMeasuredPhase11thHarmonicCurrentWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.1, 18.2), macos(13.0, 15.2), watchos(9.1, 11.2), tvos(16.1, 18.2));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeAcFrequencyMultiplierWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.1, 18.2), macos(13.0, 15.2), watchos(9.1, 11.2), tvos(16.1, 18.2));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeAcFrequencyDivisorWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.1, 18.2), macos(13.0, 15.2), watchos(9.1, 11.2), tvos(16.1, 18.2));

- (NSDictionary<NSString *, id> * _Nullable)readAttributePowerMultiplierWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.1, 18.2), macos(13.0, 15.2), watchos(9.1, 11.2), tvos(16.1, 18.2));

- (NSDictionary<NSString *, id> * _Nullable)readAttributePowerDivisorWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.1, 18.2), macos(13.0, 15.2), watchos(9.1, 11.2), tvos(16.1, 18.2));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeHarmonicCurrentMultiplierWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.1, 18.2), macos(13.0, 15.2), watchos(9.1, 11.2), tvos(16.1, 18.2));

- (NSDictionary<NSString *, id> * _Nullable)readAttributePhaseHarmonicCurrentMultiplierWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.1, 18.2), macos(13.0, 15.2), watchos(9.1, 11.2), tvos(16.1, 18.2));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeInstantaneousVoltageWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.1, 18.2), macos(13.0, 15.2), watchos(9.1, 11.2), tvos(16.1, 18.2));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeInstantaneousLineCurrentWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.1, 18.2), macos(13.0, 15.2), watchos(9.1, 11.2), tvos(16.1, 18.2));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeInstantaneousActiveCurrentWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.1, 18.2), macos(13.0, 15.2), watchos(9.1, 11.2), tvos(16.1, 18.2));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeInstantaneousReactiveCurrentWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.1, 18.2), macos(13.0, 15.2), watchos(9.1, 11.2), tvos(16.1, 18.2));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeInstantaneousPowerWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.1, 18.2), macos(13.0, 15.2), watchos(9.1, 11.2), tvos(16.1, 18.2));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeRmsVoltageWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.1, 18.2), macos(13.0, 15.2), watchos(9.1, 11.2), tvos(16.1, 18.2));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeRmsVoltageMinWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.1, 18.2), macos(13.0, 15.2), watchos(9.1, 11.2), tvos(16.1, 18.2));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeRmsVoltageMaxWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.1, 18.2), macos(13.0, 15.2), watchos(9.1, 11.2), tvos(16.1, 18.2));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeRmsCurrentWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.1, 18.2), macos(13.0, 15.2), watchos(9.1, 11.2), tvos(16.1, 18.2));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeRmsCurrentMinWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.1, 18.2), macos(13.0, 15.2), watchos(9.1, 11.2), tvos(16.1, 18.2));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeRmsCurrentMaxWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.1, 18.2), macos(13.0, 15.2), watchos(9.1, 11.2), tvos(16.1, 18.2));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeActivePowerWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.1, 18.2), macos(13.0, 15.2), watchos(9.1, 11.2), tvos(16.1, 18.2));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeActivePowerMinWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.1, 18.2), macos(13.0, 15.2), watchos(9.1, 11.2), tvos(16.1, 18.2));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeActivePowerMaxWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.1, 18.2), macos(13.0, 15.2), watchos(9.1, 11.2), tvos(16.1, 18.2));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeReactivePowerWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.1, 18.2), macos(13.0, 15.2), watchos(9.1, 11.2), tvos(16.1, 18.2));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeApparentPowerWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.1, 18.2), macos(13.0, 15.2), watchos(9.1, 11.2), tvos(16.1, 18.2));

- (NSDictionary<NSString *, id> * _Nullable)readAttributePowerFactorWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.1, 18.2), macos(13.0, 15.2), watchos(9.1, 11.2), tvos(16.1, 18.2));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeAverageRmsVoltageMeasurementPeriodWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.1, 18.2), macos(13.0, 15.2), watchos(9.1, 11.2), tvos(16.1, 18.2));
- (void)writeAttributeAverageRmsVoltageMeasurementPeriodWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.1, 18.2), macos(13.0, 15.2), watchos(9.1, 11.2), tvos(16.1, 18.2));
- (void)writeAttributeAverageRmsVoltageMeasurementPeriodWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs params:(ZGMTRWriteParams * _Nullable)params ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.1, 18.2), macos(13.0, 15.2), watchos(9.1, 11.2), tvos(16.1, 18.2));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeAverageRmsUnderVoltageCounterWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.1, 18.2), macos(13.0, 15.2), watchos(9.1, 11.2), tvos(16.1, 18.2));
- (void)writeAttributeAverageRmsUnderVoltageCounterWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.1, 18.2), macos(13.0, 15.2), watchos(9.1, 11.2), tvos(16.1, 18.2));
- (void)writeAttributeAverageRmsUnderVoltageCounterWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs params:(ZGMTRWriteParams * _Nullable)params ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.1, 18.2), macos(13.0, 15.2), watchos(9.1, 11.2), tvos(16.1, 18.2));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeRmsExtremeOverVoltagePeriodWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.1, 18.2), macos(13.0, 15.2), watchos(9.1, 11.2), tvos(16.1, 18.2));
- (void)writeAttributeRmsExtremeOverVoltagePeriodWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.1, 18.2), macos(13.0, 15.2), watchos(9.1, 11.2), tvos(16.1, 18.2));
- (void)writeAttributeRmsExtremeOverVoltagePeriodWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs params:(ZGMTRWriteParams * _Nullable)params ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.1, 18.2), macos(13.0, 15.2), watchos(9.1, 11.2), tvos(16.1, 18.2));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeRmsExtremeUnderVoltagePeriodWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.1, 18.2), macos(13.0, 15.2), watchos(9.1, 11.2), tvos(16.1, 18.2));
- (void)writeAttributeRmsExtremeUnderVoltagePeriodWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.1, 18.2), macos(13.0, 15.2), watchos(9.1, 11.2), tvos(16.1, 18.2));
- (void)writeAttributeRmsExtremeUnderVoltagePeriodWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs params:(ZGMTRWriteParams * _Nullable)params ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.1, 18.2), macos(13.0, 15.2), watchos(9.1, 11.2), tvos(16.1, 18.2));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeRmsVoltageSagPeriodWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.1, 18.2), macos(13.0, 15.2), watchos(9.1, 11.2), tvos(16.1, 18.2));
- (void)writeAttributeRmsVoltageSagPeriodWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.1, 18.2), macos(13.0, 15.2), watchos(9.1, 11.2), tvos(16.1, 18.2));
- (void)writeAttributeRmsVoltageSagPeriodWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs params:(ZGMTRWriteParams * _Nullable)params ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.1, 18.2), macos(13.0, 15.2), watchos(9.1, 11.2), tvos(16.1, 18.2));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeRmsVoltageSwellPeriodWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.1, 18.2), macos(13.0, 15.2), watchos(9.1, 11.2), tvos(16.1, 18.2));
- (void)writeAttributeRmsVoltageSwellPeriodWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.1, 18.2), macos(13.0, 15.2), watchos(9.1, 11.2), tvos(16.1, 18.2));
- (void)writeAttributeRmsVoltageSwellPeriodWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs params:(ZGMTRWriteParams * _Nullable)params ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.1, 18.2), macos(13.0, 15.2), watchos(9.1, 11.2), tvos(16.1, 18.2));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeAcVoltageMultiplierWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.1, 18.2), macos(13.0, 15.2), watchos(9.1, 11.2), tvos(16.1, 18.2));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeAcVoltageDivisorWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.1, 18.2), macos(13.0, 15.2), watchos(9.1, 11.2), tvos(16.1, 18.2));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeAcCurrentMultiplierWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.1, 18.2), macos(13.0, 15.2), watchos(9.1, 11.2), tvos(16.1, 18.2));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeAcCurrentDivisorWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.1, 18.2), macos(13.0, 15.2), watchos(9.1, 11.2), tvos(16.1, 18.2));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeAcPowerMultiplierWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.1, 18.2), macos(13.0, 15.2), watchos(9.1, 11.2), tvos(16.1, 18.2));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeAcPowerDivisorWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.1, 18.2), macos(13.0, 15.2), watchos(9.1, 11.2), tvos(16.1, 18.2));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeOverloadAlarmsMaskWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.1, 18.2), macos(13.0, 15.2), watchos(9.1, 11.2), tvos(16.1, 18.2));
- (void)writeAttributeOverloadAlarmsMaskWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.1, 18.2), macos(13.0, 15.2), watchos(9.1, 11.2), tvos(16.1, 18.2));
- (void)writeAttributeOverloadAlarmsMaskWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs params:(ZGMTRWriteParams * _Nullable)params ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.1, 18.2), macos(13.0, 15.2), watchos(9.1, 11.2), tvos(16.1, 18.2));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeVoltageOverloadWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.1, 18.2), macos(13.0, 15.2), watchos(9.1, 11.2), tvos(16.1, 18.2));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeCurrentOverloadWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.1, 18.2), macos(13.0, 15.2), watchos(9.1, 11.2), tvos(16.1, 18.2));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeAcOverloadAlarmsMaskWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.1, 18.2), macos(13.0, 15.2), watchos(9.1, 11.2), tvos(16.1, 18.2));
- (void)writeAttributeAcOverloadAlarmsMaskWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.1, 18.2), macos(13.0, 15.2), watchos(9.1, 11.2), tvos(16.1, 18.2));
- (void)writeAttributeAcOverloadAlarmsMaskWithValue:(NSDictionary<NSString *, id> *)dataValueDictionary expectedValueInterval:(NSNumber *)expectedValueIntervalMs params:(ZGMTRWriteParams * _Nullable)params ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.1, 18.2), macos(13.0, 15.2), watchos(9.1, 11.2), tvos(16.1, 18.2));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeAcVoltageOverloadWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.1, 18.2), macos(13.0, 15.2), watchos(9.1, 11.2), tvos(16.1, 18.2));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeAcCurrentOverloadWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.1, 18.2), macos(13.0, 15.2), watchos(9.1, 11.2), tvos(16.1, 18.2));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeAcActivePowerOverloadWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.1, 18.2), macos(13.0, 15.2), watchos(9.1, 11.2), tvos(16.1, 18.2));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeAcReactivePowerOverloadWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.1, 18.2), macos(13.0, 15.2), watchos(9.1, 11.2), tvos(16.1, 18.2));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeAverageRmsOverVoltageWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.1, 18.2), macos(13.0, 15.2), watchos(9.1, 11.2), tvos(16.1, 18.2));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeAverageRmsUnderVoltageWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.1, 18.2), macos(13.0, 15.2), watchos(9.1, 11.2), tvos(16.1, 18.2));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeRmsExtremeOverVoltageWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.1, 18.2), macos(13.0, 15.2), watchos(9.1, 11.2), tvos(16.1, 18.2));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeRmsExtremeUnderVoltageWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.1, 18.2), macos(13.0, 15.2), watchos(9.1, 11.2), tvos(16.1, 18.2));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeRmsVoltageSagWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.1, 18.2), macos(13.0, 15.2), watchos(9.1, 11.2), tvos(16.1, 18.2));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeRmsVoltageSwellWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.1, 18.2), macos(13.0, 15.2), watchos(9.1, 11.2), tvos(16.1, 18.2));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeLineCurrentPhaseBWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.1, 18.2), macos(13.0, 15.2), watchos(9.1, 11.2), tvos(16.1, 18.2));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeActiveCurrentPhaseBWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.1, 18.2), macos(13.0, 15.2), watchos(9.1, 11.2), tvos(16.1, 18.2));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeReactiveCurrentPhaseBWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.1, 18.2), macos(13.0, 15.2), watchos(9.1, 11.2), tvos(16.1, 18.2));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeRmsVoltagePhaseBWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.1, 18.2), macos(13.0, 15.2), watchos(9.1, 11.2), tvos(16.1, 18.2));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeRmsVoltageMinPhaseBWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.1, 18.2), macos(13.0, 15.2), watchos(9.1, 11.2), tvos(16.1, 18.2));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeRmsVoltageMaxPhaseBWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.1, 18.2), macos(13.0, 15.2), watchos(9.1, 11.2), tvos(16.1, 18.2));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeRmsCurrentPhaseBWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.1, 18.2), macos(13.0, 15.2), watchos(9.1, 11.2), tvos(16.1, 18.2));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeRmsCurrentMinPhaseBWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.1, 18.2), macos(13.0, 15.2), watchos(9.1, 11.2), tvos(16.1, 18.2));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeRmsCurrentMaxPhaseBWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.1, 18.2), macos(13.0, 15.2), watchos(9.1, 11.2), tvos(16.1, 18.2));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeActivePowerPhaseBWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.1, 18.2), macos(13.0, 15.2), watchos(9.1, 11.2), tvos(16.1, 18.2));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeActivePowerMinPhaseBWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.1, 18.2), macos(13.0, 15.2), watchos(9.1, 11.2), tvos(16.1, 18.2));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeActivePowerMaxPhaseBWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.1, 18.2), macos(13.0, 15.2), watchos(9.1, 11.2), tvos(16.1, 18.2));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeReactivePowerPhaseBWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.1, 18.2), macos(13.0, 15.2), watchos(9.1, 11.2), tvos(16.1, 18.2));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeApparentPowerPhaseBWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.1, 18.2), macos(13.0, 15.2), watchos(9.1, 11.2), tvos(16.1, 18.2));

- (NSDictionary<NSString *, id> * _Nullable)readAttributePowerFactorPhaseBWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.1, 18.2), macos(13.0, 15.2), watchos(9.1, 11.2), tvos(16.1, 18.2));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeAverageRmsVoltageMeasurementPeriodPhaseBWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.1, 18.2), macos(13.0, 15.2), watchos(9.1, 11.2), tvos(16.1, 18.2));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeAverageRmsOverVoltageCounterPhaseBWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.1, 18.2), macos(13.0, 15.2), watchos(9.1, 11.2), tvos(16.1, 18.2));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeAverageRmsUnderVoltageCounterPhaseBWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.1, 18.2), macos(13.0, 15.2), watchos(9.1, 11.2), tvos(16.1, 18.2));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeRmsExtremeOverVoltagePeriodPhaseBWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.1, 18.2), macos(13.0, 15.2), watchos(9.1, 11.2), tvos(16.1, 18.2));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeRmsExtremeUnderVoltagePeriodPhaseBWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.1, 18.2), macos(13.0, 15.2), watchos(9.1, 11.2), tvos(16.1, 18.2));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeRmsVoltageSagPeriodPhaseBWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.1, 18.2), macos(13.0, 15.2), watchos(9.1, 11.2), tvos(16.1, 18.2));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeRmsVoltageSwellPeriodPhaseBWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.1, 18.2), macos(13.0, 15.2), watchos(9.1, 11.2), tvos(16.1, 18.2));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeLineCurrentPhaseCWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.1, 18.2), macos(13.0, 15.2), watchos(9.1, 11.2), tvos(16.1, 18.2));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeActiveCurrentPhaseCWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.1, 18.2), macos(13.0, 15.2), watchos(9.1, 11.2), tvos(16.1, 18.2));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeReactiveCurrentPhaseCWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.1, 18.2), macos(13.0, 15.2), watchos(9.1, 11.2), tvos(16.1, 18.2));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeRmsVoltagePhaseCWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.1, 18.2), macos(13.0, 15.2), watchos(9.1, 11.2), tvos(16.1, 18.2));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeRmsVoltageMinPhaseCWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.1, 18.2), macos(13.0, 15.2), watchos(9.1, 11.2), tvos(16.1, 18.2));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeRmsVoltageMaxPhaseCWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.1, 18.2), macos(13.0, 15.2), watchos(9.1, 11.2), tvos(16.1, 18.2));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeRmsCurrentPhaseCWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.1, 18.2), macos(13.0, 15.2), watchos(9.1, 11.2), tvos(16.1, 18.2));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeRmsCurrentMinPhaseCWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.1, 18.2), macos(13.0, 15.2), watchos(9.1, 11.2), tvos(16.1, 18.2));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeRmsCurrentMaxPhaseCWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.1, 18.2), macos(13.0, 15.2), watchos(9.1, 11.2), tvos(16.1, 18.2));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeActivePowerPhaseCWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.1, 18.2), macos(13.0, 15.2), watchos(9.1, 11.2), tvos(16.1, 18.2));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeActivePowerMinPhaseCWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.1, 18.2), macos(13.0, 15.2), watchos(9.1, 11.2), tvos(16.1, 18.2));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeActivePowerMaxPhaseCWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.1, 18.2), macos(13.0, 15.2), watchos(9.1, 11.2), tvos(16.1, 18.2));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeReactivePowerPhaseCWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.1, 18.2), macos(13.0, 15.2), watchos(9.1, 11.2), tvos(16.1, 18.2));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeApparentPowerPhaseCWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.1, 18.2), macos(13.0, 15.2), watchos(9.1, 11.2), tvos(16.1, 18.2));

- (NSDictionary<NSString *, id> * _Nullable)readAttributePowerFactorPhaseCWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.1, 18.2), macos(13.0, 15.2), watchos(9.1, 11.2), tvos(16.1, 18.2));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeAverageRmsVoltageMeasurementPeriodPhaseCWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.1, 18.2), macos(13.0, 15.2), watchos(9.1, 11.2), tvos(16.1, 18.2));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeAverageRmsOverVoltageCounterPhaseCWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.1, 18.2), macos(13.0, 15.2), watchos(9.1, 11.2), tvos(16.1, 18.2));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeAverageRmsUnderVoltageCounterPhaseCWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.1, 18.2), macos(13.0, 15.2), watchos(9.1, 11.2), tvos(16.1, 18.2));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeRmsExtremeOverVoltagePeriodPhaseCWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.1, 18.2), macos(13.0, 15.2), watchos(9.1, 11.2), tvos(16.1, 18.2));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeRmsExtremeUnderVoltagePeriodPhaseCWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.1, 18.2), macos(13.0, 15.2), watchos(9.1, 11.2), tvos(16.1, 18.2));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeRmsVoltageSagPeriodPhaseCWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.1, 18.2), macos(13.0, 15.2), watchos(9.1, 11.2), tvos(16.1, 18.2));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeRmsVoltageSwellPeriodPhaseCWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.1, 18.2), macos(13.0, 15.2), watchos(9.1, 11.2), tvos(16.1, 18.2));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeGeneratedCommandListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.1, 18.2), macos(13.0, 15.2), watchos(9.1, 11.2), tvos(16.1, 18.2));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeAcceptedCommandListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.1, 18.2), macos(13.0, 15.2), watchos(9.1, 11.2), tvos(16.1, 18.2));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeAttributeListWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.1, 18.2), macos(13.0, 15.2), watchos(9.1, 11.2), tvos(16.1, 18.2));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeFeatureMapWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.1, 18.2), macos(13.0, 15.2), watchos(9.1, 11.2), tvos(16.1, 18.2));

- (NSDictionary<NSString *, id> * _Nullable)readAttributeClusterRevisionWithParams:(ZGMTRReadParams * _Nullable)params ZGMTR_DEPRECATED("This attribute is deprecated", ios(16.1, 18.2), macos(13.0, 15.2), watchos(9.1, 11.2), tvos(16.1, 18.2));

- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end

@interface ZGMTRClusterElectricalMeasurement (Availability)

/**
 * For all instance methods that take a completion (i.e. command invocations),
 * the completion will be called on the provided queue.
 */
- (instancetype _Nullable)initWithDevice:(ZGMTRDevice *)device
                              endpointID:(NSNumber *)endpointID
                                   queue:(dispatch_queue_t)queue ZGMTR_DEPRECATED("ElectricalMeasurement is deprecated and will be removed", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2));

@end

@interface ZGMTRClusterElectricalMeasurement (Deprecated)

- (nullable instancetype)initWithDevice:(ZGMTRDevice *)device
                               endpoint:(uint16_t)endpoint
                                  queue:(dispatch_queue_t)queue ZGMTR_DEPRECATED("Please use initWithDevice:endpoindID:queue:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));

- (void)getProfileInfoCommandWithParams:(ZGMTRElectricalMeasurementClusterGetProfileInfoCommandParams * _Nullable)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completionHandler:(ZGMTRStatusCompletion)completionHandler ZGMTR_DEPRECATED("Please use getProfileInfoCommandWithParams:expectedValues:expectedValueInterval:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (void)getProfileInfoCommandWithExpectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedValues expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completionHandler:(ZGMTRStatusCompletion)completionHandler ZGMTR_DEPRECATED("Please use getProfileInfoCommandWithExpectedValues:expectedValueInterval:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
- (void)getMeasurementProfileCommandWithParams:(ZGMTRElectricalMeasurementClusterGetMeasurementProfileCommandParams *)params expectedValues:(NSArray<NSDictionary<NSString *, id> *> * _Nullable)expectedDataValueDictionaries expectedValueInterval:(NSNumber * _Nullable)expectedValueIntervalMs completionHandler:(ZGMTRStatusCompletion)completionHandler ZGMTR_DEPRECATED("Please use getMeasurementProfileCommandWithParams:expectedValues:expectedValueInterval:completion:", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4));
@end

// Note: Add new shims that are not entire cluster removals above the "Clusters that were removed wholesale:" bits

NS_ASSUME_NONNULL_END
