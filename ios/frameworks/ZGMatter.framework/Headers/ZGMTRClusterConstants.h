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
#import <stdint.h>

#pragma mark - Clusters IDs

typedef NS_ENUM(uint32_t, ZGMTRClusterIDType) {
    ZGMTRClusterIdentifyID ZGMTR_DEPRECATED("Please use ZGMTRClusterIDTypeIdentifyID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000003,
    ZGMTRClusterGroupsID ZGMTR_DEPRECATED("Please use ZGMTRClusterIDTypeGroupsID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000004,
    ZGMTRClusterOnOffID ZGMTR_DEPRECATED("Please use ZGMTRClusterIDTypeOnOffID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000006,
    ZGMTRClusterLevelControlID ZGMTR_DEPRECATED("Please use ZGMTRClusterIDTypeLevelControlID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000008,
    ZGMTRClusterPulseWidthModulationID ZGMTR_DEPRECATED("Please use ZGMTRClusterIDTypePulseWidthModulationID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x0000001C,
    ZGMTRClusterDescriptorID ZGMTR_DEPRECATED("Please use ZGMTRClusterIDTypeDescriptorID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x0000001D,
    ZGMTRClusterBindingID ZGMTR_DEPRECATED("Please use ZGMTRClusterIDTypeBindingID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x0000001E,
    ZGMTRClusterAccessControlID ZGMTR_DEPRECATED("Please use ZGMTRClusterIDTypeAccessControlID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x0000001F,
    ZGMTRClusterActionsID ZGMTR_DEPRECATED("Please use ZGMTRClusterIDTypeActionsID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000025,
    ZGMTRClusterBasicID ZGMTR_DEPRECATED("Please use ZGMTRClusterIDTypeBasicInformationID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000028,
    ZGMTRClusterOtaSoftwareUpdateProviderID ZGMTR_DEPRECATED("Please use ZGMTRClusterIDTypeOTASoftwareUpdateProviderID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000029,
    ZGMTRClusterOtaSoftwareUpdateRequestorID ZGMTR_DEPRECATED("Please use ZGMTRClusterIDTypeOTASoftwareUpdateRequestorID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x0000002A,
    ZGMTRClusterLocalizationConfigurationID ZGMTR_DEPRECATED("Please use ZGMTRClusterIDTypeLocalizationConfigurationID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x0000002B,
    ZGMTRClusterTimeFormatLocalizationID ZGMTR_DEPRECATED("Please use ZGMTRClusterIDTypeTimeFormatLocalizationID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x0000002C,
    ZGMTRClusterUnitLocalizationID ZGMTR_DEPRECATED("Please use ZGMTRClusterIDTypeUnitLocalizationID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x0000002D,
    ZGMTRClusterPowerSourceConfigurationID ZGMTR_DEPRECATED("Please use ZGMTRClusterIDTypePowerSourceConfigurationID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x0000002E,
    ZGMTRClusterPowerSourceID ZGMTR_DEPRECATED("Please use ZGMTRClusterIDTypePowerSourceID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x0000002F,
    ZGMTRClusterGeneralCommissioningID ZGMTR_DEPRECATED("Please use ZGMTRClusterIDTypeGeneralCommissioningID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000030,
    ZGMTRClusterNetworkCommissioningID ZGMTR_DEPRECATED("Please use ZGMTRClusterIDTypeNetworkCommissioningID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000031,
    ZGMTRClusterDiagnosticLogsID ZGMTR_DEPRECATED("Please use ZGMTRClusterIDTypeDiagnosticLogsID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000032,
    ZGMTRClusterGeneralDiagnosticsID ZGMTR_DEPRECATED("Please use ZGMTRClusterIDTypeGeneralDiagnosticsID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000033,
    ZGMTRClusterSoftwareDiagnosticsID ZGMTR_DEPRECATED("Please use ZGMTRClusterIDTypeSoftwareDiagnosticsID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000034,
    ZGMTRClusterThreadNetworkDiagnosticsID ZGMTR_DEPRECATED("Please use ZGMTRClusterIDTypeThreadNetworkDiagnosticsID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000035,
    ZGMTRClusterWiFiNetworkDiagnosticsID ZGMTR_DEPRECATED("Please use ZGMTRClusterIDTypeWiFiNetworkDiagnosticsID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000036,
    ZGMTRClusterEthernetNetworkDiagnosticsID ZGMTR_DEPRECATED("Please use ZGMTRClusterIDTypeEthernetNetworkDiagnosticsID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000037,
    ZGMTRClusterTimeSynchronizationID ZGMTR_DEPRECATED("Please use ZGMTRClusterIDTypeTimeSynchronizationID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000038,
    ZGMTRClusterBridgedDeviceBasicID ZGMTR_DEPRECATED("Please use ZGMTRClusterIDTypeBridgedDeviceBasicInformationID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000039,
    ZGMTRClusterSwitchID ZGMTR_DEPRECATED("Please use ZGMTRClusterIDTypeSwitchID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x0000003B,
    ZGMTRClusterAdministratorCommissioningID ZGMTR_DEPRECATED("Please use ZGMTRClusterIDTypeAdministratorCommissioningID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x0000003C,
    ZGMTRClusterOperationalCredentialsID ZGMTR_DEPRECATED("Please use ZGMTRClusterIDTypeOperationalCredentialsID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x0000003E,
    ZGMTRClusterGroupKeyManagementID ZGMTR_DEPRECATED("Please use ZGMTRClusterIDTypeGroupKeyManagementID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x0000003F,
    ZGMTRClusterFixedLabelID ZGMTR_DEPRECATED("Please use ZGMTRClusterIDTypeFixedLabelID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000040,
    ZGMTRClusterUserLabelID ZGMTR_DEPRECATED("Please use ZGMTRClusterIDTypeUserLabelID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000041,
    ZGMTRClusterBooleanStateID ZGMTR_DEPRECATED("Please use ZGMTRClusterIDTypeBooleanStateID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000045,
    ZGMTRClusterModeSelectID ZGMTR_DEPRECATED("Please use ZGMTRClusterIDTypeModeSelectID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000050,
    ZGMTRClusterDoorLockID ZGMTR_DEPRECATED("Please use ZGMTRClusterIDTypeDoorLockID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000101,
    ZGMTRClusterWindowCoveringID ZGMTR_DEPRECATED("Please use ZGMTRClusterIDTypeWindowCoveringID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000102,
    ZGMTRClusterPumpConfigurationAndControlID ZGMTR_DEPRECATED("Please use ZGMTRClusterIDTypePumpConfigurationAndControlID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000200,
    ZGMTRClusterThermostatID ZGMTR_DEPRECATED("Please use ZGMTRClusterIDTypeThermostatID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000201,
    ZGMTRClusterFanControlID ZGMTR_DEPRECATED("Please use ZGMTRClusterIDTypeFanControlID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000202,
    ZGMTRClusterThermostatUserInterfaceConfigurationID ZGMTR_DEPRECATED("Please use ZGMTRClusterIDTypeThermostatUserInterfaceConfigurationID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000204,
    ZGMTRClusterColorControlID ZGMTR_DEPRECATED("Please use ZGMTRClusterIDTypeColorControlID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000300,
    ZGMTRClusterBallastConfigurationID ZGMTR_DEPRECATED("Please use ZGMTRClusterIDTypeBallastConfigurationID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000301,
    ZGMTRClusterIlluminanceMeasurementID ZGMTR_DEPRECATED("Please use ZGMTRClusterIDTypeIlluminanceMeasurementID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000400,
    ZGMTRClusterTemperatureMeasurementID ZGMTR_DEPRECATED("Please use ZGMTRClusterIDTypeTemperatureMeasurementID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000402,
    ZGMTRClusterPressureMeasurementID ZGMTR_DEPRECATED("Please use ZGMTRClusterIDTypePressureMeasurementID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000403,
    ZGMTRClusterFlowMeasurementID ZGMTR_DEPRECATED("Please use ZGMTRClusterIDTypeFlowMeasurementID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000404,
    ZGMTRClusterRelativeHumidityMeasurementID ZGMTR_DEPRECATED("Please use ZGMTRClusterIDTypeRelativeHumidityMeasurementID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000405,
    ZGMTRClusterOccupancySensingID ZGMTR_DEPRECATED("Please use ZGMTRClusterIDTypeOccupancySensingID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000406,
    ZGMTRClusterWakeOnLanID ZGMTR_DEPRECATED("Please use ZGMTRClusterIDTypeWakeOnLANID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000503,
    ZGMTRClusterChannelID ZGMTR_DEPRECATED("Please use ZGMTRClusterIDTypeChannelID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000504,
    ZGMTRClusterTargetNavigatorID ZGMTR_DEPRECATED("Please use ZGMTRClusterIDTypeTargetNavigatorID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000505,
    ZGMTRClusterMediaPlaybackID ZGMTR_DEPRECATED("Please use ZGMTRClusterIDTypeMediaPlaybackID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000506,
    ZGMTRClusterMediaInputID ZGMTR_DEPRECATED("Please use ZGMTRClusterIDTypeMediaInputID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000507,
    ZGMTRClusterLowPowerID ZGMTR_DEPRECATED("Please use ZGMTRClusterIDTypeLowPowerID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000508,
    ZGMTRClusterKeypadInputID ZGMTR_DEPRECATED("Please use ZGMTRClusterIDTypeKeypadInputID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000509,
    ZGMTRClusterContentLauncherID ZGMTR_DEPRECATED("Please use ZGMTRClusterIDTypeContentLauncherID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x0000050A,
    ZGMTRClusterAudioOutputID ZGMTR_DEPRECATED("Please use ZGMTRClusterIDTypeAudioOutputID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x0000050B,
    ZGMTRClusterApplicationLauncherID ZGMTR_DEPRECATED("Please use ZGMTRClusterIDTypeApplicationLauncherID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x0000050C,
    ZGMTRClusterApplicationBasicID ZGMTR_DEPRECATED("Please use ZGMTRClusterIDTypeApplicationBasicID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x0000050D,
    ZGMTRClusterAccountLoginID ZGMTR_DEPRECATED("Please use ZGMTRClusterIDTypeAccountLoginID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x0000050E,
    ZGMTRClusterTestClusterID ZGMTR_DEPRECATED("Please use ZGMTRClusterIDTypeUnitTestingID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0xFFF1FC05,
    ZGMTRClusterIDTypeIdentifyID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000003,
    ZGMTRClusterIDTypeGroupsID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000004,
    ZGMTRClusterIDTypeOnOffID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000006,
    ZGMTRClusterIDTypeLevelControlID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000008,
    ZGMTRClusterIDTypePulseWidthModulationID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x0000001C,
    ZGMTRClusterIDTypeDescriptorID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x0000001D,
    ZGMTRClusterIDTypeBindingID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x0000001E,
    ZGMTRClusterIDTypeAccessControlID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x0000001F,
    ZGMTRClusterIDTypeActionsID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000025,
    ZGMTRClusterIDTypeBasicInformationID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000028,
    ZGMTRClusterIDTypeOTASoftwareUpdateProviderID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000029,
    ZGMTRClusterIDTypeOTASoftwareUpdateRequestorID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x0000002A,
    ZGMTRClusterIDTypeLocalizationConfigurationID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x0000002B,
    ZGMTRClusterIDTypeTimeFormatLocalizationID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x0000002C,
    ZGMTRClusterIDTypeUnitLocalizationID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x0000002D,
    ZGMTRClusterIDTypePowerSourceConfigurationID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x0000002E,
    ZGMTRClusterIDTypePowerSourceID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x0000002F,
    ZGMTRClusterIDTypeGeneralCommissioningID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000030,
    ZGMTRClusterIDTypeNetworkCommissioningID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000031,
    ZGMTRClusterIDTypeDiagnosticLogsID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000032,
    ZGMTRClusterIDTypeGeneralDiagnosticsID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000033,
    ZGMTRClusterIDTypeSoftwareDiagnosticsID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000034,
    ZGMTRClusterIDTypeThreadNetworkDiagnosticsID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000035,
    ZGMTRClusterIDTypeWiFiNetworkDiagnosticsID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000036,
    ZGMTRClusterIDTypeEthernetNetworkDiagnosticsID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000037,
    ZGMTRClusterIDTypeTimeSynchronizationID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000038,
    ZGMTRClusterIDTypeBridgedDeviceBasicInformationID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000039,
    ZGMTRClusterIDTypeSwitchID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x0000003B,
    ZGMTRClusterIDTypeAdministratorCommissioningID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x0000003C,
    ZGMTRClusterIDTypeOperationalCredentialsID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x0000003E,
    ZGMTRClusterIDTypeGroupKeyManagementID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x0000003F,
    ZGMTRClusterIDTypeFixedLabelID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000040,
    ZGMTRClusterIDTypeUserLabelID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000041,
    ZGMTRClusterIDTypeBooleanStateID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000045,
    ZGMTRClusterIDTypeICDManagementID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = 0x00000046,
    ZGMTRClusterIDTypeOvenCavityOperationalStateID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = 0x00000048,
    ZGMTRClusterIDTypeOvenModeID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = 0x00000049,
    ZGMTRClusterIDTypeLaundryDryerControlsID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = 0x0000004A,
    ZGMTRClusterIDTypeTemperatureControlledCabinetTopologyID ZGMTR_PROVISIONALLY_AVAILABLE = 0x0000004B,
    ZGMTRClusterIDTypeModeSelectID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000050,
    ZGMTRClusterIDTypeLaundryWasherModeID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = 0x00000051,
    ZGMTRClusterIDTypeRefrigeratorAndTemperatureControlledCabinetModeID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = 0x00000052,
    ZGMTRClusterIDTypeLaundryWasherControlsID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = 0x00000053,
    ZGMTRClusterIDTypeRVCRunModeID ZGMTR_AVAILABLE(ios(17.4), macos(14.4), watchos(10.4), tvos(17.4)) = 0x00000054,
    ZGMTRClusterIDTypeRVCCleanModeID ZGMTR_AVAILABLE(ios(17.4), macos(14.4), watchos(10.4), tvos(17.4)) = 0x00000055,
    ZGMTRClusterIDTypeTemperatureControlID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = 0x00000056,
    ZGMTRClusterIDTypeRefrigeratorAlarmID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = 0x00000057,
    ZGMTRClusterIDTypeDishwasherModeID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = 0x00000059,
    ZGMTRClusterIDTypeAirQualityID ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6)) = 0x0000005B,
    ZGMTRClusterIDTypeSmokeCOAlarmID ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6)) = 0x0000005C,
    ZGMTRClusterIDTypeDishwasherAlarmID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = 0x0000005D,
    ZGMTRClusterIDTypeMicrowaveOvenModeID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = 0x0000005E,
    ZGMTRClusterIDTypeMicrowaveOvenControlID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = 0x0000005F,
    ZGMTRClusterIDTypeOperationalStateID ZGMTR_AVAILABLE(ios(17.4), macos(14.4), watchos(10.4), tvos(17.4)) = 0x00000060,
    ZGMTRClusterIDTypeRVCOperationalStateID ZGMTR_AVAILABLE(ios(17.4), macos(14.4), watchos(10.4), tvos(17.4)) = 0x00000061,
    ZGMTRClusterIDTypeScenesManagementID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000062,
    ZGMTRClusterIDTypeGroupcastID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000065,
    ZGMTRClusterIDTypeHEPAFilterMonitoringID ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6)) = 0x00000071,
    ZGMTRClusterIDTypeActivatedCarbonFilterMonitoringID ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6)) = 0x00000072,
    ZGMTRClusterIDTypeWaterTankLevelMonitoringID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000079,
    ZGMTRClusterIDTypeBooleanStateConfigurationID ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6)) = 0x00000080,
    ZGMTRClusterIDTypeValveConfigurationAndControlID ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6)) = 0x00000081,
    ZGMTRClusterIDTypeElectricalPowerMeasurementID ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6)) = 0x00000090,
    ZGMTRClusterIDTypeElectricalEnergyMeasurementID ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6)) = 0x00000091,
    ZGMTRClusterIDTypeWaterHeaterManagementID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = 0x00000094,
    ZGMTRClusterIDTypeCommodityPriceID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000095,
    ZGMTRClusterIDTypeMessagesID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = 0x00000097,
    ZGMTRClusterIDTypeDeviceEnergyManagementID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = 0x00000098,
    ZGMTRClusterIDTypeEnergyEVSEID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = 0x00000099,
    ZGMTRClusterIDTypeEnergyPreferenceID ZGMTR_PROVISIONALLY_AVAILABLE = 0x0000009B,
    ZGMTRClusterIDTypePowerTopologyID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = 0x0000009C,
    ZGMTRClusterIDTypeEnergyEVSEModeID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = 0x0000009D,
    ZGMTRClusterIDTypeWaterHeaterModeID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = 0x0000009E,
    ZGMTRClusterIDTypeDeviceEnergyManagementModeID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = 0x0000009F,
    ZGMTRClusterIDTypeElectricalGridConditionsID ZGMTR_PROVISIONALLY_AVAILABLE = 0x000000A0,
    ZGMTRClusterIDTypeElectricalAlarmID ZGMTR_PROVISIONALLY_AVAILABLE = 0x000000A1,
    ZGMTRClusterIDTypeElectricalDistributionID ZGMTR_PROVISIONALLY_AVAILABLE = 0x000000A2,
    ZGMTRClusterIDTypeElectricalProtectionAlarmID ZGMTR_PROVISIONALLY_AVAILABLE = 0x000000A3,
    ZGMTRClusterIDTypeDoorLockID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000101,
    ZGMTRClusterIDTypeWindowCoveringID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000102,
    ZGMTRClusterIDTypeClosureControlID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000104,
    ZGMTRClusterIDTypeClosureDimensionID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000105,
    ZGMTRClusterIDTypeServiceAreaID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = 0x00000150,
    ZGMTRClusterIDTypePumpConfigurationAndControlID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000200,
    ZGMTRClusterIDTypeThermostatID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000201,
    ZGMTRClusterIDTypeFanControlID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000202,
    ZGMTRClusterIDTypeThermostatUserInterfaceConfigurationID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000204,
    ZGMTRClusterIDTypeHumidistatID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000205,
    ZGMTRClusterIDTypeColorControlID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000300,
    ZGMTRClusterIDTypeBallastConfigurationID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000301,
    ZGMTRClusterIDTypeDynamicLightingID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000305,
    ZGMTRClusterIDTypeIlluminanceMeasurementID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000400,
    ZGMTRClusterIDTypeTemperatureMeasurementID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000402,
    ZGMTRClusterIDTypePressureMeasurementID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000403,
    ZGMTRClusterIDTypeFlowMeasurementID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000404,
    ZGMTRClusterIDTypeRelativeHumidityMeasurementID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000405,
    ZGMTRClusterIDTypeOccupancySensingID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000406,
    ZGMTRClusterIDTypeCarbonMonoxideConcentrationMeasurementID ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6)) = 0x0000040C,
    ZGMTRClusterIDTypeCarbonDioxideConcentrationMeasurementID ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6)) = 0x0000040D,
    ZGMTRClusterIDTypeNitrogenDioxideConcentrationMeasurementID ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6)) = 0x00000413,
    ZGMTRClusterIDTypeOzoneConcentrationMeasurementID ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6)) = 0x00000415,
    ZGMTRClusterIDTypePM25ConcentrationMeasurementID ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6)) = 0x0000042A,
    ZGMTRClusterIDTypeFormaldehydeConcentrationMeasurementID ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6)) = 0x0000042B,
    ZGMTRClusterIDTypePM1ConcentrationMeasurementID ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6)) = 0x0000042C,
    ZGMTRClusterIDTypePM10ConcentrationMeasurementID ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6)) = 0x0000042D,
    ZGMTRClusterIDTypeTotalVolatileOrganicCompoundsConcentrationMeasurementID ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6)) = 0x0000042E,
    ZGMTRClusterIDTypeRadonConcentrationMeasurementID ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6)) = 0x0000042F,
    ZGMTRClusterIDTypeSoilMeasurementID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000430,
    ZGMTRClusterIDTypeAmbientContextSensingID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000431,
    ZGMTRClusterIDTypeAmbientSensingUnionID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000432,
    ZGMTRClusterIDTypeProximityRangingID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000433,
    ZGMTRClusterIDTypeSmokeConcentrationMeasurementID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000434,
    ZGMTRClusterIDTypeNetworkIdentityManagementID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000450,
    ZGMTRClusterIDTypeWiFiNetworkManagementID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = 0x00000451,
    ZGMTRClusterIDTypeThreadBorderRouterManagementID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = 0x00000452,
    ZGMTRClusterIDTypeThreadNetworkDirectoryID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = 0x00000453,
    ZGMTRClusterIDTypeCommissioningProxyID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000455,
    ZGMTRClusterIDTypeWakeOnLANID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000503,
    ZGMTRClusterIDTypeChannelID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000504,
    ZGMTRClusterIDTypeTargetNavigatorID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000505,
    ZGMTRClusterIDTypeMediaPlaybackID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000506,
    ZGMTRClusterIDTypeMediaInputID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000507,
    ZGMTRClusterIDTypeLowPowerID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000508,
    ZGMTRClusterIDTypeKeypadInputID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000509,
    ZGMTRClusterIDTypeContentLauncherID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x0000050A,
    ZGMTRClusterIDTypeAudioOutputID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x0000050B,
    ZGMTRClusterIDTypeApplicationLauncherID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x0000050C,
    ZGMTRClusterIDTypeApplicationBasicID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x0000050D,
    ZGMTRClusterIDTypeAccountLoginID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x0000050E,
    ZGMTRClusterIDTypeContentControlID ZGMTR_PROVISIONALLY_AVAILABLE = 0x0000050F,
    ZGMTRClusterIDTypeContentAppObserverID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = 0x00000510,
    ZGMTRClusterIDTypeMediaFileManagementID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000511,
    ZGMTRClusterIDTypeAudioControlID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000512,
    ZGMTRClusterIDTypeZoneManagementID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000550,
    ZGMTRClusterIDTypeCameraAVStreamManagementID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000551,
    ZGMTRClusterIDTypeCameraAVSettingsUserLevelManagementID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000552,
    ZGMTRClusterIDTypeWebRTCTransportProviderID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000553,
    ZGMTRClusterIDTypeWebRTCTransportRequestorID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000554,
    ZGMTRClusterIDTypePushAVStreamTransportID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000555,
    ZGMTRClusterIDTypeChimeID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000556,
    ZGMTRClusterIDTypeAVAnalysisID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000557,
    ZGMTRClusterIDTypeCommodityTariffID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000700,
    ZGMTRClusterIDTypeEcosystemInformationID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000750,
    ZGMTRClusterIDTypeCommissionerControlID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = 0x00000751,
    ZGMTRClusterIDTypeJointFabricDatastoreID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000752,
    ZGMTRClusterIDTypeJointFabricAdministratorID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000753,
    ZGMTRClusterIDTypeTLSCertificateManagementID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000801,
    ZGMTRClusterIDTypeTLSClientManagementID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000802,
    ZGMTRClusterIDTypeMeterIdentificationID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000B06,
    ZGMTRClusterIDTypeCommodityMeteringID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000B07,
    ZGMTRClusterIDTypeUnitTestingID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0xFFF1FC05,
    ZGMTRClusterIDTypeSampleMEIID ZGMTR_PROVISIONALLY_AVAILABLE = 0xFFF1FC20,
    ZGMTRClusterIDTypeTestHiddenManufacturerSpecificID ZGMTR_PROVISIONALLY_AVAILABLE = 0xFFF1FC21,

    ZGMTRClusterBarrierControlID ZGMTR_DEPRECATED("Please use ZGMTRClusterIDTypeBarrierControlID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000103,
    ZGMTRClusterIDTypeBarrierControlID ZGMTR_DEPRECATED("The BarrierControl cluster will be removed", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2)) = 0x00000103,
    ZGMTRClusterBinaryInputBasicID ZGMTR_DEPRECATED("Please use ZGMTRClusterIDTypeBinaryInputBasicID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x0000000F,
    ZGMTRClusterIDTypeBinaryInputBasicID ZGMTR_DEPRECATED("The BinaryInputBasic cluster will be removed", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2)) = 0x0000000F,
    ZGMTRClusterElectricalMeasurementID ZGMTR_DEPRECATED("Please use ZGMTRClusterIDTypeElectricalMeasurementID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000B04,
    ZGMTRClusterIDTypeElectricalMeasurementID ZGMTR_DEPRECATED("The ElectricalMeasurement cluster will be removed", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2)) = 0x00000B04,
    ZGMTRClusterOnOffSwitchConfigurationID ZGMTR_DEPRECATED("Please use ZGMTRClusterIDTypeOnOffSwitchConfigurationID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000007,
    ZGMTRClusterIDTypeOnOffSwitchConfigurationID ZGMTR_DEPRECATED("The OnOffSwitchConfiguration cluster will be removed", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2)) = 0x00000007,
};

#pragma mark - Attributes IDs

typedef NS_ENUM(uint32_t, ZGMTRAttributeIDType) {
    // Deprecated global attribute names
    ZGMTRClusterGlobalAttributeGeneratedCommandListID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeGlobalAttributeGeneratedCommandListID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x0000FFF8,
    ZGMTRClusterGlobalAttributeAcceptedCommandListID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeGlobalAttributeAcceptedCommandListID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x0000FFF9,
    ZGMTRClusterGlobalAttributeAttributeListID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeGlobalAttributeAttributeListID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x0000FFFB,
    ZGMTRClusterGlobalAttributeFeatureMapID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeGlobalAttributeFeatureMapID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x0000FFFC,
    ZGMTRClusterGlobalAttributeClusterRevisionID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeGlobalAttributeClusterRevisionID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x0000FFFD,

    // Global attributes
    ZGMTRAttributeIDTypeGlobalAttributeGeneratedCommandListID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x0000FFF8,
    ZGMTRAttributeIDTypeGlobalAttributeAcceptedCommandListID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x0000FFF9,
    ZGMTRAttributeIDTypeGlobalAttributeAttributeListID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x0000FFFB,
    ZGMTRAttributeIDTypeGlobalAttributeFeatureMapID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x0000FFFC,
    ZGMTRAttributeIDTypeGlobalAttributeClusterRevisionID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x0000FFFD,

    // Cluster Identify deprecated attribute names
    ZGMTRClusterIdentifyAttributeIdentifyTimeID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterIdentifyAttributeIdentifyTimeID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000000,
    ZGMTRClusterIdentifyAttributeIdentifyTypeID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterIdentifyAttributeIdentifyTypeID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000001,
    ZGMTRClusterIdentifyAttributeGeneratedCommandListID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterIdentifyAttributeGeneratedCommandListID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = ZGMTRClusterGlobalAttributeGeneratedCommandListID,
    ZGMTRClusterIdentifyAttributeAcceptedCommandListID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterIdentifyAttributeAcceptedCommandListID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = ZGMTRClusterGlobalAttributeAcceptedCommandListID,
    ZGMTRClusterIdentifyAttributeAttributeListID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterIdentifyAttributeAttributeListID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = ZGMTRClusterGlobalAttributeAttributeListID,
    ZGMTRClusterIdentifyAttributeFeatureMapID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterIdentifyAttributeFeatureMapID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = ZGMTRClusterGlobalAttributeFeatureMapID,
    ZGMTRClusterIdentifyAttributeClusterRevisionID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterIdentifyAttributeClusterRevisionID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = ZGMTRClusterGlobalAttributeClusterRevisionID,

    // Cluster Identify attributes
    ZGMTRAttributeIDTypeClusterIdentifyAttributeIdentifyTimeID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000000,
    ZGMTRAttributeIDTypeClusterIdentifyAttributeIdentifyTypeID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000001,
    ZGMTRAttributeIDTypeClusterIdentifyAttributeGeneratedCommandListID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = ZGMTRAttributeIDTypeGlobalAttributeGeneratedCommandListID,
    ZGMTRAttributeIDTypeClusterIdentifyAttributeAcceptedCommandListID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = ZGMTRAttributeIDTypeGlobalAttributeAcceptedCommandListID,
    ZGMTRAttributeIDTypeClusterIdentifyAttributeAttributeListID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = ZGMTRAttributeIDTypeGlobalAttributeAttributeListID,
    ZGMTRAttributeIDTypeClusterIdentifyAttributeFeatureMapID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = ZGMTRAttributeIDTypeGlobalAttributeFeatureMapID,
    ZGMTRAttributeIDTypeClusterIdentifyAttributeClusterRevisionID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = ZGMTRAttributeIDTypeGlobalAttributeClusterRevisionID,

    // Cluster Groups deprecated attribute names
    ZGMTRClusterGroupsAttributeNameSupportID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterGroupsAttributeNameSupportID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000000,
    ZGMTRClusterGroupsAttributeGeneratedCommandListID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterGroupsAttributeGeneratedCommandListID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = ZGMTRClusterGlobalAttributeGeneratedCommandListID,
    ZGMTRClusterGroupsAttributeAcceptedCommandListID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterGroupsAttributeAcceptedCommandListID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = ZGMTRClusterGlobalAttributeAcceptedCommandListID,
    ZGMTRClusterGroupsAttributeAttributeListID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterGroupsAttributeAttributeListID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = ZGMTRClusterGlobalAttributeAttributeListID,
    ZGMTRClusterGroupsAttributeFeatureMapID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterGroupsAttributeFeatureMapID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = ZGMTRClusterGlobalAttributeFeatureMapID,
    ZGMTRClusterGroupsAttributeClusterRevisionID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterGroupsAttributeClusterRevisionID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = ZGMTRClusterGlobalAttributeClusterRevisionID,

    // Cluster Groups attributes
    ZGMTRAttributeIDTypeClusterGroupsAttributeNameSupportID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000000,
    ZGMTRAttributeIDTypeClusterGroupsAttributeGeneratedCommandListID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = ZGMTRAttributeIDTypeGlobalAttributeGeneratedCommandListID,
    ZGMTRAttributeIDTypeClusterGroupsAttributeAcceptedCommandListID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = ZGMTRAttributeIDTypeGlobalAttributeAcceptedCommandListID,
    ZGMTRAttributeIDTypeClusterGroupsAttributeAttributeListID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = ZGMTRAttributeIDTypeGlobalAttributeAttributeListID,
    ZGMTRAttributeIDTypeClusterGroupsAttributeFeatureMapID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = ZGMTRAttributeIDTypeGlobalAttributeFeatureMapID,
    ZGMTRAttributeIDTypeClusterGroupsAttributeClusterRevisionID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = ZGMTRAttributeIDTypeGlobalAttributeClusterRevisionID,

    // Cluster OnOff deprecated attribute names
    ZGMTRClusterOnOffAttributeOnOffID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterOnOffAttributeOnOffID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000000,
    ZGMTRClusterOnOffAttributeGlobalSceneControlID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterOnOffAttributeGlobalSceneControlID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00004000,
    ZGMTRClusterOnOffAttributeOnTimeID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterOnOffAttributeOnTimeID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00004001,
    ZGMTRClusterOnOffAttributeOffWaitTimeID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterOnOffAttributeOffWaitTimeID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00004002,
    ZGMTRClusterOnOffAttributeStartUpOnOffID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterOnOffAttributeStartUpOnOffID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00004003,
    ZGMTRClusterOnOffAttributeGeneratedCommandListID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterOnOffAttributeGeneratedCommandListID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = ZGMTRClusterGlobalAttributeGeneratedCommandListID,
    ZGMTRClusterOnOffAttributeAcceptedCommandListID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterOnOffAttributeAcceptedCommandListID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = ZGMTRClusterGlobalAttributeAcceptedCommandListID,
    ZGMTRClusterOnOffAttributeAttributeListID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterOnOffAttributeAttributeListID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = ZGMTRClusterGlobalAttributeAttributeListID,
    ZGMTRClusterOnOffAttributeFeatureMapID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterOnOffAttributeFeatureMapID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = ZGMTRClusterGlobalAttributeFeatureMapID,
    ZGMTRClusterOnOffAttributeClusterRevisionID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterOnOffAttributeClusterRevisionID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = ZGMTRClusterGlobalAttributeClusterRevisionID,

    // Cluster OnOff attributes
    ZGMTRAttributeIDTypeClusterOnOffAttributeOnOffID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000000,
    ZGMTRAttributeIDTypeClusterOnOffAttributeGlobalSceneControlID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00004000,
    ZGMTRAttributeIDTypeClusterOnOffAttributeOnTimeID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00004001,
    ZGMTRAttributeIDTypeClusterOnOffAttributeOffWaitTimeID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00004002,
    ZGMTRAttributeIDTypeClusterOnOffAttributeStartUpOnOffID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00004003,
    ZGMTRAttributeIDTypeClusterOnOffAttributeGeneratedCommandListID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = ZGMTRAttributeIDTypeGlobalAttributeGeneratedCommandListID,
    ZGMTRAttributeIDTypeClusterOnOffAttributeAcceptedCommandListID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = ZGMTRAttributeIDTypeGlobalAttributeAcceptedCommandListID,
    ZGMTRAttributeIDTypeClusterOnOffAttributeAttributeListID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = ZGMTRAttributeIDTypeGlobalAttributeAttributeListID,
    ZGMTRAttributeIDTypeClusterOnOffAttributeFeatureMapID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = ZGMTRAttributeIDTypeGlobalAttributeFeatureMapID,
    ZGMTRAttributeIDTypeClusterOnOffAttributeClusterRevisionID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = ZGMTRAttributeIDTypeGlobalAttributeClusterRevisionID,

    // Cluster LevelControl deprecated attribute names
    ZGMTRClusterLevelControlAttributeCurrentLevelID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterLevelControlAttributeCurrentLevelID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000000,
    ZGMTRClusterLevelControlAttributeRemainingTimeID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterLevelControlAttributeRemainingTimeID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000001,
    ZGMTRClusterLevelControlAttributeMinLevelID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterLevelControlAttributeMinLevelID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000002,
    ZGMTRClusterLevelControlAttributeMaxLevelID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterLevelControlAttributeMaxLevelID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000003,
    ZGMTRClusterLevelControlAttributeCurrentFrequencyID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterLevelControlAttributeCurrentFrequencyID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000004,
    ZGMTRClusterLevelControlAttributeMinFrequencyID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterLevelControlAttributeMinFrequencyID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000005,
    ZGMTRClusterLevelControlAttributeMaxFrequencyID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterLevelControlAttributeMaxFrequencyID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000006,
    ZGMTRClusterLevelControlAttributeOptionsID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterLevelControlAttributeOptionsID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x0000000F,
    ZGMTRClusterLevelControlAttributeOnOffTransitionTimeID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterLevelControlAttributeOnOffTransitionTimeID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000010,
    ZGMTRClusterLevelControlAttributeOnLevelID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterLevelControlAttributeOnLevelID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000011,
    ZGMTRClusterLevelControlAttributeOnTransitionTimeID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterLevelControlAttributeOnTransitionTimeID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000012,
    ZGMTRClusterLevelControlAttributeOffTransitionTimeID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterLevelControlAttributeOffTransitionTimeID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000013,
    ZGMTRClusterLevelControlAttributeDefaultMoveRateID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterLevelControlAttributeDefaultMoveRateID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000014,
    ZGMTRClusterLevelControlAttributeStartUpCurrentLevelID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterLevelControlAttributeStartUpCurrentLevelID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00004000,
    ZGMTRClusterLevelControlAttributeGeneratedCommandListID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterLevelControlAttributeGeneratedCommandListID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = ZGMTRClusterGlobalAttributeGeneratedCommandListID,
    ZGMTRClusterLevelControlAttributeAcceptedCommandListID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterLevelControlAttributeAcceptedCommandListID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = ZGMTRClusterGlobalAttributeAcceptedCommandListID,
    ZGMTRClusterLevelControlAttributeAttributeListID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterLevelControlAttributeAttributeListID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = ZGMTRClusterGlobalAttributeAttributeListID,
    ZGMTRClusterLevelControlAttributeFeatureMapID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterLevelControlAttributeFeatureMapID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = ZGMTRClusterGlobalAttributeFeatureMapID,
    ZGMTRClusterLevelControlAttributeClusterRevisionID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterLevelControlAttributeClusterRevisionID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = ZGMTRClusterGlobalAttributeClusterRevisionID,

    // Cluster LevelControl attributes
    ZGMTRAttributeIDTypeClusterLevelControlAttributeCurrentLevelID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000000,
    ZGMTRAttributeIDTypeClusterLevelControlAttributeRemainingTimeID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000001,
    ZGMTRAttributeIDTypeClusterLevelControlAttributeMinLevelID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000002,
    ZGMTRAttributeIDTypeClusterLevelControlAttributeMaxLevelID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000003,
    ZGMTRAttributeIDTypeClusterLevelControlAttributeCurrentFrequencyID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000004,
    ZGMTRAttributeIDTypeClusterLevelControlAttributeMinFrequencyID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000005,
    ZGMTRAttributeIDTypeClusterLevelControlAttributeMaxFrequencyID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000006,
    ZGMTRAttributeIDTypeClusterLevelControlAttributeOptionsID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x0000000F,
    ZGMTRAttributeIDTypeClusterLevelControlAttributeOnOffTransitionTimeID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000010,
    ZGMTRAttributeIDTypeClusterLevelControlAttributeOnLevelID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000011,
    ZGMTRAttributeIDTypeClusterLevelControlAttributeOnTransitionTimeID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000012,
    ZGMTRAttributeIDTypeClusterLevelControlAttributeOffTransitionTimeID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000013,
    ZGMTRAttributeIDTypeClusterLevelControlAttributeDefaultMoveRateID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000014,
    ZGMTRAttributeIDTypeClusterLevelControlAttributeStartUpCurrentLevelID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00004000,
    ZGMTRAttributeIDTypeClusterLevelControlAttributeGeneratedCommandListID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = ZGMTRAttributeIDTypeGlobalAttributeGeneratedCommandListID,
    ZGMTRAttributeIDTypeClusterLevelControlAttributeAcceptedCommandListID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = ZGMTRAttributeIDTypeGlobalAttributeAcceptedCommandListID,
    ZGMTRAttributeIDTypeClusterLevelControlAttributeAttributeListID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = ZGMTRAttributeIDTypeGlobalAttributeAttributeListID,
    ZGMTRAttributeIDTypeClusterLevelControlAttributeFeatureMapID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = ZGMTRAttributeIDTypeGlobalAttributeFeatureMapID,
    ZGMTRAttributeIDTypeClusterLevelControlAttributeClusterRevisionID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = ZGMTRAttributeIDTypeGlobalAttributeClusterRevisionID,

    // Cluster PulseWidthModulation deprecated attribute names
    ZGMTRClusterPulseWidthModulationAttributeGeneratedCommandListID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterPulseWidthModulationAttributeGeneratedCommandListID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = ZGMTRClusterGlobalAttributeGeneratedCommandListID,
    ZGMTRClusterPulseWidthModulationAttributeAcceptedCommandListID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterPulseWidthModulationAttributeAcceptedCommandListID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = ZGMTRClusterGlobalAttributeAcceptedCommandListID,
    ZGMTRClusterPulseWidthModulationAttributeAttributeListID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterPulseWidthModulationAttributeAttributeListID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = ZGMTRClusterGlobalAttributeAttributeListID,
    ZGMTRClusterPulseWidthModulationAttributeFeatureMapID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterPulseWidthModulationAttributeFeatureMapID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = ZGMTRClusterGlobalAttributeFeatureMapID,
    ZGMTRClusterPulseWidthModulationAttributeClusterRevisionID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterPulseWidthModulationAttributeClusterRevisionID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = ZGMTRClusterGlobalAttributeClusterRevisionID,

    // Cluster PulseWidthModulation attributes
    ZGMTRAttributeIDTypeClusterPulseWidthModulationAttributeGeneratedCommandListID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = ZGMTRAttributeIDTypeGlobalAttributeGeneratedCommandListID,
    ZGMTRAttributeIDTypeClusterPulseWidthModulationAttributeAcceptedCommandListID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = ZGMTRAttributeIDTypeGlobalAttributeAcceptedCommandListID,
    ZGMTRAttributeIDTypeClusterPulseWidthModulationAttributeAttributeListID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = ZGMTRAttributeIDTypeGlobalAttributeAttributeListID,
    ZGMTRAttributeIDTypeClusterPulseWidthModulationAttributeFeatureMapID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = ZGMTRAttributeIDTypeGlobalAttributeFeatureMapID,
    ZGMTRAttributeIDTypeClusterPulseWidthModulationAttributeClusterRevisionID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = ZGMTRAttributeIDTypeGlobalAttributeClusterRevisionID,

    // Cluster Descriptor deprecated attribute names
    ZGMTRClusterDescriptorAttributeDeviceTypeListID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterDescriptorAttributeDeviceTypeListID", ios(16.2, 16.4), macos(13.1, 13.3), watchos(9.2, 9.4), tvos(16.2, 16.4))
    = 0x00000000,
    ZGMTRClusterDescriptorAttributeDeviceListID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterDescriptorAttributeDeviceTypeListID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000000,
    ZGMTRClusterDescriptorAttributeServerListID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterDescriptorAttributeServerListID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000001,
    ZGMTRClusterDescriptorAttributeClientListID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterDescriptorAttributeClientListID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000002,
    ZGMTRClusterDescriptorAttributePartsListID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterDescriptorAttributePartsListID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000003,
    ZGMTRClusterDescriptorAttributeGeneratedCommandListID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterDescriptorAttributeGeneratedCommandListID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = ZGMTRClusterGlobalAttributeGeneratedCommandListID,
    ZGMTRClusterDescriptorAttributeAcceptedCommandListID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterDescriptorAttributeAcceptedCommandListID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = ZGMTRClusterGlobalAttributeAcceptedCommandListID,
    ZGMTRClusterDescriptorAttributeAttributeListID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterDescriptorAttributeAttributeListID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = ZGMTRClusterGlobalAttributeAttributeListID,
    ZGMTRClusterDescriptorAttributeFeatureMapID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterDescriptorAttributeFeatureMapID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = ZGMTRClusterGlobalAttributeFeatureMapID,
    ZGMTRClusterDescriptorAttributeClusterRevisionID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterDescriptorAttributeClusterRevisionID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = ZGMTRClusterGlobalAttributeClusterRevisionID,

    // Cluster Descriptor attributes
    ZGMTRAttributeIDTypeClusterDescriptorAttributeDeviceTypeListID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000000,
    ZGMTRAttributeIDTypeClusterDescriptorAttributeServerListID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000001,
    ZGMTRAttributeIDTypeClusterDescriptorAttributeClientListID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000002,
    ZGMTRAttributeIDTypeClusterDescriptorAttributePartsListID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000003,
    ZGMTRAttributeIDTypeClusterDescriptorAttributeTagListID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000004,
    ZGMTRAttributeIDTypeClusterDescriptorAttributeEndpointUniqueIDID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000005,
    ZGMTRAttributeIDTypeClusterDescriptorAttributeGeneratedCommandListID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = ZGMTRAttributeIDTypeGlobalAttributeGeneratedCommandListID,
    ZGMTRAttributeIDTypeClusterDescriptorAttributeAcceptedCommandListID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = ZGMTRAttributeIDTypeGlobalAttributeAcceptedCommandListID,
    ZGMTRAttributeIDTypeClusterDescriptorAttributeAttributeListID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = ZGMTRAttributeIDTypeGlobalAttributeAttributeListID,
    ZGMTRAttributeIDTypeClusterDescriptorAttributeFeatureMapID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = ZGMTRAttributeIDTypeGlobalAttributeFeatureMapID,
    ZGMTRAttributeIDTypeClusterDescriptorAttributeClusterRevisionID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = ZGMTRAttributeIDTypeGlobalAttributeClusterRevisionID,

    // Cluster Binding deprecated attribute names
    ZGMTRClusterBindingAttributeBindingID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterBindingAttributeBindingID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000000,
    ZGMTRClusterBindingAttributeGeneratedCommandListID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterBindingAttributeGeneratedCommandListID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = ZGMTRClusterGlobalAttributeGeneratedCommandListID,
    ZGMTRClusterBindingAttributeAcceptedCommandListID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterBindingAttributeAcceptedCommandListID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = ZGMTRClusterGlobalAttributeAcceptedCommandListID,
    ZGMTRClusterBindingAttributeAttributeListID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterBindingAttributeAttributeListID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = ZGMTRClusterGlobalAttributeAttributeListID,
    ZGMTRClusterBindingAttributeFeatureMapID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterBindingAttributeFeatureMapID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = ZGMTRClusterGlobalAttributeFeatureMapID,
    ZGMTRClusterBindingAttributeClusterRevisionID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterBindingAttributeClusterRevisionID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = ZGMTRClusterGlobalAttributeClusterRevisionID,

    // Cluster Binding attributes
    ZGMTRAttributeIDTypeClusterBindingAttributeBindingID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000000,
    ZGMTRAttributeIDTypeClusterBindingAttributeGeneratedCommandListID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = ZGMTRAttributeIDTypeGlobalAttributeGeneratedCommandListID,
    ZGMTRAttributeIDTypeClusterBindingAttributeAcceptedCommandListID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = ZGMTRAttributeIDTypeGlobalAttributeAcceptedCommandListID,
    ZGMTRAttributeIDTypeClusterBindingAttributeAttributeListID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = ZGMTRAttributeIDTypeGlobalAttributeAttributeListID,
    ZGMTRAttributeIDTypeClusterBindingAttributeFeatureMapID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = ZGMTRAttributeIDTypeGlobalAttributeFeatureMapID,
    ZGMTRAttributeIDTypeClusterBindingAttributeClusterRevisionID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = ZGMTRAttributeIDTypeGlobalAttributeClusterRevisionID,

    // Cluster AccessControl deprecated attribute names
    ZGMTRClusterAccessControlAttributeAclID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterAccessControlAttributeACLID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000000,
    ZGMTRClusterAccessControlAttributeExtensionID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterAccessControlAttributeExtensionID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000001,
    ZGMTRClusterAccessControlAttributeSubjectsPerAccessControlEntryID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterAccessControlAttributeSubjectsPerAccessControlEntryID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000002,
    ZGMTRClusterAccessControlAttributeTargetsPerAccessControlEntryID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterAccessControlAttributeTargetsPerAccessControlEntryID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000003,
    ZGMTRClusterAccessControlAttributeAccessControlEntriesPerFabricID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterAccessControlAttributeAccessControlEntriesPerFabricID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000004,
    ZGMTRClusterAccessControlAttributeGeneratedCommandListID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterAccessControlAttributeGeneratedCommandListID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = ZGMTRClusterGlobalAttributeGeneratedCommandListID,
    ZGMTRClusterAccessControlAttributeAcceptedCommandListID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterAccessControlAttributeAcceptedCommandListID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = ZGMTRClusterGlobalAttributeAcceptedCommandListID,
    ZGMTRClusterAccessControlAttributeAttributeListID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterAccessControlAttributeAttributeListID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = ZGMTRClusterGlobalAttributeAttributeListID,
    ZGMTRClusterAccessControlAttributeFeatureMapID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterAccessControlAttributeFeatureMapID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = ZGMTRClusterGlobalAttributeFeatureMapID,
    ZGMTRClusterAccessControlAttributeClusterRevisionID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterAccessControlAttributeClusterRevisionID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = ZGMTRClusterGlobalAttributeClusterRevisionID,

    // Cluster AccessControl attributes
    ZGMTRAttributeIDTypeClusterAccessControlAttributeACLID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000000,
    ZGMTRAttributeIDTypeClusterAccessControlAttributeExtensionID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000001,
    ZGMTRAttributeIDTypeClusterAccessControlAttributeSubjectsPerAccessControlEntryID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000002,
    ZGMTRAttributeIDTypeClusterAccessControlAttributeTargetsPerAccessControlEntryID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000003,
    ZGMTRAttributeIDTypeClusterAccessControlAttributeAccessControlEntriesPerFabricID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000004,
    ZGMTRAttributeIDTypeClusterAccessControlAttributeCommissioningARLID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = 0x00000005,
    ZGMTRAttributeIDTypeClusterAccessControlAttributeARLID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = 0x00000006,
    ZGMTRAttributeIDTypeClusterAccessControlAttributeAuxiliaryACLID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000007,
    ZGMTRAttributeIDTypeClusterAccessControlAttributeGeneratedCommandListID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = ZGMTRAttributeIDTypeGlobalAttributeGeneratedCommandListID,
    ZGMTRAttributeIDTypeClusterAccessControlAttributeAcceptedCommandListID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = ZGMTRAttributeIDTypeGlobalAttributeAcceptedCommandListID,
    ZGMTRAttributeIDTypeClusterAccessControlAttributeAttributeListID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = ZGMTRAttributeIDTypeGlobalAttributeAttributeListID,
    ZGMTRAttributeIDTypeClusterAccessControlAttributeFeatureMapID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = ZGMTRAttributeIDTypeGlobalAttributeFeatureMapID,
    ZGMTRAttributeIDTypeClusterAccessControlAttributeClusterRevisionID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = ZGMTRAttributeIDTypeGlobalAttributeClusterRevisionID,

    // Cluster Actions deprecated attribute names
    ZGMTRClusterActionsAttributeActionListID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterActionsAttributeActionListID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000000,
    ZGMTRClusterActionsAttributeEndpointListsID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterActionsAttributeEndpointListsID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000001,
    ZGMTRClusterActionsAttributeSetupURLID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterActionsAttributeSetupURLID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000002,
    ZGMTRClusterActionsAttributeGeneratedCommandListID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterActionsAttributeGeneratedCommandListID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = ZGMTRClusterGlobalAttributeGeneratedCommandListID,
    ZGMTRClusterActionsAttributeAcceptedCommandListID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterActionsAttributeAcceptedCommandListID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = ZGMTRClusterGlobalAttributeAcceptedCommandListID,
    ZGMTRClusterActionsAttributeAttributeListID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterActionsAttributeAttributeListID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = ZGMTRClusterGlobalAttributeAttributeListID,
    ZGMTRClusterActionsAttributeFeatureMapID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterActionsAttributeFeatureMapID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = ZGMTRClusterGlobalAttributeFeatureMapID,
    ZGMTRClusterActionsAttributeClusterRevisionID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterActionsAttributeClusterRevisionID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = ZGMTRClusterGlobalAttributeClusterRevisionID,

    // Cluster Actions attributes
    ZGMTRAttributeIDTypeClusterActionsAttributeActionListID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000000,
    ZGMTRAttributeIDTypeClusterActionsAttributeEndpointListsID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000001,
    ZGMTRAttributeIDTypeClusterActionsAttributeSetupURLID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000002,
    ZGMTRAttributeIDTypeClusterActionsAttributeGeneratedCommandListID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = ZGMTRAttributeIDTypeGlobalAttributeGeneratedCommandListID,
    ZGMTRAttributeIDTypeClusterActionsAttributeAcceptedCommandListID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = ZGMTRAttributeIDTypeGlobalAttributeAcceptedCommandListID,
    ZGMTRAttributeIDTypeClusterActionsAttributeAttributeListID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = ZGMTRAttributeIDTypeGlobalAttributeAttributeListID,
    ZGMTRAttributeIDTypeClusterActionsAttributeFeatureMapID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = ZGMTRAttributeIDTypeGlobalAttributeFeatureMapID,
    ZGMTRAttributeIDTypeClusterActionsAttributeClusterRevisionID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = ZGMTRAttributeIDTypeGlobalAttributeClusterRevisionID,

    // Cluster Basic deprecated attribute names
    ZGMTRClusterBasicAttributeDataModelRevisionID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterBasicInformationAttributeDataModelRevisionID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000000,
    ZGMTRClusterBasicAttributeVendorNameID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterBasicInformationAttributeVendorNameID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000001,
    ZGMTRClusterBasicAttributeVendorIDID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterBasicInformationAttributeVendorIDID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000002,
    ZGMTRClusterBasicAttributeProductNameID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterBasicInformationAttributeProductNameID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000003,
    ZGMTRClusterBasicAttributeProductIDID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterBasicInformationAttributeProductIDID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000004,
    ZGMTRClusterBasicAttributeNodeLabelID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterBasicInformationAttributeNodeLabelID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000005,
    ZGMTRClusterBasicAttributeLocationID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterBasicInformationAttributeLocationID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000006,
    ZGMTRClusterBasicAttributeHardwareVersionID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterBasicInformationAttributeHardwareVersionID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000007,
    ZGMTRClusterBasicAttributeHardwareVersionStringID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterBasicInformationAttributeHardwareVersionStringID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000008,
    ZGMTRClusterBasicAttributeSoftwareVersionID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterBasicInformationAttributeSoftwareVersionID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000009,
    ZGMTRClusterBasicAttributeSoftwareVersionStringID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterBasicInformationAttributeSoftwareVersionStringID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x0000000A,
    ZGMTRClusterBasicAttributeManufacturingDateID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterBasicInformationAttributeManufacturingDateID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x0000000B,
    ZGMTRClusterBasicAttributePartNumberID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterBasicInformationAttributePartNumberID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x0000000C,
    ZGMTRClusterBasicAttributeProductURLID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterBasicInformationAttributeProductURLID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x0000000D,
    ZGMTRClusterBasicAttributeProductLabelID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterBasicInformationAttributeProductLabelID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x0000000E,
    ZGMTRClusterBasicAttributeSerialNumberID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterBasicInformationAttributeSerialNumberID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x0000000F,
    ZGMTRClusterBasicAttributeLocalConfigDisabledID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterBasicInformationAttributeLocalConfigDisabledID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000010,
    ZGMTRClusterBasicAttributeReachableID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterBasicInformationAttributeReachableID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000011,
    ZGMTRClusterBasicAttributeUniqueIDID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterBasicInformationAttributeUniqueIDID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000012,
    ZGMTRClusterBasicAttributeCapabilityMinimaID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterBasicInformationAttributeCapabilityMinimaID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000013,
    ZGMTRClusterBasicAttributeGeneratedCommandListID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterBasicInformationAttributeGeneratedCommandListID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = ZGMTRClusterGlobalAttributeGeneratedCommandListID,
    ZGMTRClusterBasicAttributeAcceptedCommandListID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterBasicInformationAttributeAcceptedCommandListID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = ZGMTRClusterGlobalAttributeAcceptedCommandListID,
    ZGMTRClusterBasicAttributeAttributeListID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterBasicInformationAttributeAttributeListID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = ZGMTRClusterGlobalAttributeAttributeListID,
    ZGMTRClusterBasicAttributeFeatureMapID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterBasicInformationAttributeFeatureMapID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = ZGMTRClusterGlobalAttributeFeatureMapID,
    ZGMTRClusterBasicAttributeClusterRevisionID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterBasicInformationAttributeClusterRevisionID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = ZGMTRClusterGlobalAttributeClusterRevisionID,

    // Cluster BasicInformation attributes
    ZGMTRAttributeIDTypeClusterBasicInformationAttributeDataModelRevisionID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000000,
    ZGMTRAttributeIDTypeClusterBasicInformationAttributeVendorNameID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000001,
    ZGMTRAttributeIDTypeClusterBasicInformationAttributeVendorIDID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000002,
    ZGMTRAttributeIDTypeClusterBasicInformationAttributeProductNameID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000003,
    ZGMTRAttributeIDTypeClusterBasicInformationAttributeProductIDID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000004,
    ZGMTRAttributeIDTypeClusterBasicInformationAttributeNodeLabelID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000005,
    ZGMTRAttributeIDTypeClusterBasicInformationAttributeLocationID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000006,
    ZGMTRAttributeIDTypeClusterBasicInformationAttributeHardwareVersionID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000007,
    ZGMTRAttributeIDTypeClusterBasicInformationAttributeHardwareVersionStringID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000008,
    ZGMTRAttributeIDTypeClusterBasicInformationAttributeSoftwareVersionID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000009,
    ZGMTRAttributeIDTypeClusterBasicInformationAttributeSoftwareVersionStringID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x0000000A,
    ZGMTRAttributeIDTypeClusterBasicInformationAttributeManufacturingDateID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x0000000B,
    ZGMTRAttributeIDTypeClusterBasicInformationAttributePartNumberID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x0000000C,
    ZGMTRAttributeIDTypeClusterBasicInformationAttributeProductURLID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x0000000D,
    ZGMTRAttributeIDTypeClusterBasicInformationAttributeProductLabelID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x0000000E,
    ZGMTRAttributeIDTypeClusterBasicInformationAttributeSerialNumberID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x0000000F,
    ZGMTRAttributeIDTypeClusterBasicInformationAttributeLocalConfigDisabledID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000010,
    ZGMTRAttributeIDTypeClusterBasicInformationAttributeReachableID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000011,
    ZGMTRAttributeIDTypeClusterBasicInformationAttributeUniqueIDID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000012,
    ZGMTRAttributeIDTypeClusterBasicInformationAttributeCapabilityMinimaID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000013,
    ZGMTRAttributeIDTypeClusterBasicInformationAttributeProductAppearanceID ZGMTR_AVAILABLE(ios(17.0), macos(14.0), watchos(10.0), tvos(17.0)) = 0x00000014,
    ZGMTRAttributeIDTypeClusterBasicInformationAttributeSpecificationVersionID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = 0x00000015,
    ZGMTRAttributeIDTypeClusterBasicInformationAttributeMaxPathsPerInvokeID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = 0x00000016,
    ZGMTRAttributeIDTypeClusterBasicInformationAttributeDeviceLocationID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000017,
    ZGMTRAttributeIDTypeClusterBasicInformationAttributeConfigurationVersionID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000018,
    ZGMTRAttributeIDTypeClusterBasicInformationAttributeGeneratedCommandListID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = ZGMTRAttributeIDTypeGlobalAttributeGeneratedCommandListID,
    ZGMTRAttributeIDTypeClusterBasicInformationAttributeAcceptedCommandListID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = ZGMTRAttributeIDTypeGlobalAttributeAcceptedCommandListID,
    ZGMTRAttributeIDTypeClusterBasicInformationAttributeAttributeListID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = ZGMTRAttributeIDTypeGlobalAttributeAttributeListID,
    ZGMTRAttributeIDTypeClusterBasicInformationAttributeFeatureMapID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = ZGMTRAttributeIDTypeGlobalAttributeFeatureMapID,
    ZGMTRAttributeIDTypeClusterBasicInformationAttributeClusterRevisionID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = ZGMTRAttributeIDTypeGlobalAttributeClusterRevisionID,

    // Cluster OtaSoftwareUpdateProvider deprecated attribute names
    ZGMTRClusterOtaSoftwareUpdateProviderAttributeGeneratedCommandListID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterOTASoftwareUpdateProviderAttributeGeneratedCommandListID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = ZGMTRClusterGlobalAttributeGeneratedCommandListID,
    ZGMTRClusterOtaSoftwareUpdateProviderAttributeAcceptedCommandListID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterOTASoftwareUpdateProviderAttributeAcceptedCommandListID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = ZGMTRClusterGlobalAttributeAcceptedCommandListID,
    ZGMTRClusterOtaSoftwareUpdateProviderAttributeAttributeListID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterOTASoftwareUpdateProviderAttributeAttributeListID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = ZGMTRClusterGlobalAttributeAttributeListID,
    ZGMTRClusterOtaSoftwareUpdateProviderAttributeFeatureMapID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterOTASoftwareUpdateProviderAttributeFeatureMapID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = ZGMTRClusterGlobalAttributeFeatureMapID,
    ZGMTRClusterOtaSoftwareUpdateProviderAttributeClusterRevisionID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterOTASoftwareUpdateProviderAttributeClusterRevisionID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = ZGMTRClusterGlobalAttributeClusterRevisionID,

    // Cluster OTASoftwareUpdateProvider attributes
    ZGMTRAttributeIDTypeClusterOTASoftwareUpdateProviderAttributeGeneratedCommandListID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = ZGMTRAttributeIDTypeGlobalAttributeGeneratedCommandListID,
    ZGMTRAttributeIDTypeClusterOTASoftwareUpdateProviderAttributeAcceptedCommandListID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = ZGMTRAttributeIDTypeGlobalAttributeAcceptedCommandListID,
    ZGMTRAttributeIDTypeClusterOTASoftwareUpdateProviderAttributeAttributeListID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = ZGMTRAttributeIDTypeGlobalAttributeAttributeListID,
    ZGMTRAttributeIDTypeClusterOTASoftwareUpdateProviderAttributeFeatureMapID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = ZGMTRAttributeIDTypeGlobalAttributeFeatureMapID,
    ZGMTRAttributeIDTypeClusterOTASoftwareUpdateProviderAttributeClusterRevisionID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = ZGMTRAttributeIDTypeGlobalAttributeClusterRevisionID,

    // Cluster OtaSoftwareUpdateRequestor deprecated attribute names
    ZGMTRClusterOtaSoftwareUpdateRequestorAttributeDefaultOtaProvidersID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterOTASoftwareUpdateRequestorAttributeDefaultOTAProvidersID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000000,
    ZGMTRClusterOtaSoftwareUpdateRequestorAttributeUpdatePossibleID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterOTASoftwareUpdateRequestorAttributeUpdatePossibleID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000001,
    ZGMTRClusterOtaSoftwareUpdateRequestorAttributeUpdateStateID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterOTASoftwareUpdateRequestorAttributeUpdateStateID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000002,
    ZGMTRClusterOtaSoftwareUpdateRequestorAttributeUpdateStateProgressID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterOTASoftwareUpdateRequestorAttributeUpdateStateProgressID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000003,
    ZGMTRClusterOtaSoftwareUpdateRequestorAttributeGeneratedCommandListID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterOTASoftwareUpdateRequestorAttributeGeneratedCommandListID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = ZGMTRClusterGlobalAttributeGeneratedCommandListID,
    ZGMTRClusterOtaSoftwareUpdateRequestorAttributeAcceptedCommandListID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterOTASoftwareUpdateRequestorAttributeAcceptedCommandListID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = ZGMTRClusterGlobalAttributeAcceptedCommandListID,
    ZGMTRClusterOtaSoftwareUpdateRequestorAttributeAttributeListID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterOTASoftwareUpdateRequestorAttributeAttributeListID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = ZGMTRClusterGlobalAttributeAttributeListID,
    ZGMTRClusterOtaSoftwareUpdateRequestorAttributeFeatureMapID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterOTASoftwareUpdateRequestorAttributeFeatureMapID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = ZGMTRClusterGlobalAttributeFeatureMapID,
    ZGMTRClusterOtaSoftwareUpdateRequestorAttributeClusterRevisionID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterOTASoftwareUpdateRequestorAttributeClusterRevisionID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = ZGMTRClusterGlobalAttributeClusterRevisionID,

    // Cluster OTASoftwareUpdateRequestor attributes
    ZGMTRAttributeIDTypeClusterOTASoftwareUpdateRequestorAttributeDefaultOTAProvidersID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000000,
    ZGMTRAttributeIDTypeClusterOTASoftwareUpdateRequestorAttributeUpdatePossibleID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000001,
    ZGMTRAttributeIDTypeClusterOTASoftwareUpdateRequestorAttributeUpdateStateID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000002,
    ZGMTRAttributeIDTypeClusterOTASoftwareUpdateRequestorAttributeUpdateStateProgressID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000003,
    ZGMTRAttributeIDTypeClusterOTASoftwareUpdateRequestorAttributeGeneratedCommandListID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = ZGMTRAttributeIDTypeGlobalAttributeGeneratedCommandListID,
    ZGMTRAttributeIDTypeClusterOTASoftwareUpdateRequestorAttributeAcceptedCommandListID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = ZGMTRAttributeIDTypeGlobalAttributeAcceptedCommandListID,
    ZGMTRAttributeIDTypeClusterOTASoftwareUpdateRequestorAttributeAttributeListID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = ZGMTRAttributeIDTypeGlobalAttributeAttributeListID,
    ZGMTRAttributeIDTypeClusterOTASoftwareUpdateRequestorAttributeFeatureMapID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = ZGMTRAttributeIDTypeGlobalAttributeFeatureMapID,
    ZGMTRAttributeIDTypeClusterOTASoftwareUpdateRequestorAttributeClusterRevisionID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = ZGMTRAttributeIDTypeGlobalAttributeClusterRevisionID,

    // Cluster LocalizationConfiguration deprecated attribute names
    ZGMTRClusterLocalizationConfigurationAttributeActiveLocaleID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterLocalizationConfigurationAttributeActiveLocaleID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000000,
    ZGMTRClusterLocalizationConfigurationAttributeSupportedLocalesID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterLocalizationConfigurationAttributeSupportedLocalesID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000001,
    ZGMTRClusterLocalizationConfigurationAttributeGeneratedCommandListID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterLocalizationConfigurationAttributeGeneratedCommandListID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = ZGMTRClusterGlobalAttributeGeneratedCommandListID,
    ZGMTRClusterLocalizationConfigurationAttributeAcceptedCommandListID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterLocalizationConfigurationAttributeAcceptedCommandListID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = ZGMTRClusterGlobalAttributeAcceptedCommandListID,
    ZGMTRClusterLocalizationConfigurationAttributeAttributeListID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterLocalizationConfigurationAttributeAttributeListID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = ZGMTRClusterGlobalAttributeAttributeListID,
    ZGMTRClusterLocalizationConfigurationAttributeFeatureMapID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterLocalizationConfigurationAttributeFeatureMapID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = ZGMTRClusterGlobalAttributeFeatureMapID,
    ZGMTRClusterLocalizationConfigurationAttributeClusterRevisionID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterLocalizationConfigurationAttributeClusterRevisionID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = ZGMTRClusterGlobalAttributeClusterRevisionID,

    // Cluster LocalizationConfiguration attributes
    ZGMTRAttributeIDTypeClusterLocalizationConfigurationAttributeActiveLocaleID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000000,
    ZGMTRAttributeIDTypeClusterLocalizationConfigurationAttributeSupportedLocalesID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000001,
    ZGMTRAttributeIDTypeClusterLocalizationConfigurationAttributeGeneratedCommandListID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = ZGMTRAttributeIDTypeGlobalAttributeGeneratedCommandListID,
    ZGMTRAttributeIDTypeClusterLocalizationConfigurationAttributeAcceptedCommandListID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = ZGMTRAttributeIDTypeGlobalAttributeAcceptedCommandListID,
    ZGMTRAttributeIDTypeClusterLocalizationConfigurationAttributeAttributeListID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = ZGMTRAttributeIDTypeGlobalAttributeAttributeListID,
    ZGMTRAttributeIDTypeClusterLocalizationConfigurationAttributeFeatureMapID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = ZGMTRAttributeIDTypeGlobalAttributeFeatureMapID,
    ZGMTRAttributeIDTypeClusterLocalizationConfigurationAttributeClusterRevisionID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = ZGMTRAttributeIDTypeGlobalAttributeClusterRevisionID,

    // Cluster TimeFormatLocalization deprecated attribute names
    ZGMTRClusterTimeFormatLocalizationAttributeHourFormatID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterTimeFormatLocalizationAttributeHourFormatID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000000,
    ZGMTRClusterTimeFormatLocalizationAttributeActiveCalendarTypeID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterTimeFormatLocalizationAttributeActiveCalendarTypeID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000001,
    ZGMTRClusterTimeFormatLocalizationAttributeSupportedCalendarTypesID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterTimeFormatLocalizationAttributeSupportedCalendarTypesID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000002,
    ZGMTRClusterTimeFormatLocalizationAttributeGeneratedCommandListID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterTimeFormatLocalizationAttributeGeneratedCommandListID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = ZGMTRClusterGlobalAttributeGeneratedCommandListID,
    ZGMTRClusterTimeFormatLocalizationAttributeAcceptedCommandListID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterTimeFormatLocalizationAttributeAcceptedCommandListID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = ZGMTRClusterGlobalAttributeAcceptedCommandListID,
    ZGMTRClusterTimeFormatLocalizationAttributeAttributeListID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterTimeFormatLocalizationAttributeAttributeListID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = ZGMTRClusterGlobalAttributeAttributeListID,
    ZGMTRClusterTimeFormatLocalizationAttributeFeatureMapID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterTimeFormatLocalizationAttributeFeatureMapID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = ZGMTRClusterGlobalAttributeFeatureMapID,
    ZGMTRClusterTimeFormatLocalizationAttributeClusterRevisionID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterTimeFormatLocalizationAttributeClusterRevisionID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = ZGMTRClusterGlobalAttributeClusterRevisionID,

    // Cluster TimeFormatLocalization attributes
    ZGMTRAttributeIDTypeClusterTimeFormatLocalizationAttributeHourFormatID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000000,
    ZGMTRAttributeIDTypeClusterTimeFormatLocalizationAttributeActiveCalendarTypeID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000001,
    ZGMTRAttributeIDTypeClusterTimeFormatLocalizationAttributeSupportedCalendarTypesID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000002,
    ZGMTRAttributeIDTypeClusterTimeFormatLocalizationAttributeGeneratedCommandListID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = ZGMTRAttributeIDTypeGlobalAttributeGeneratedCommandListID,
    ZGMTRAttributeIDTypeClusterTimeFormatLocalizationAttributeAcceptedCommandListID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = ZGMTRAttributeIDTypeGlobalAttributeAcceptedCommandListID,
    ZGMTRAttributeIDTypeClusterTimeFormatLocalizationAttributeAttributeListID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = ZGMTRAttributeIDTypeGlobalAttributeAttributeListID,
    ZGMTRAttributeIDTypeClusterTimeFormatLocalizationAttributeFeatureMapID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = ZGMTRAttributeIDTypeGlobalAttributeFeatureMapID,
    ZGMTRAttributeIDTypeClusterTimeFormatLocalizationAttributeClusterRevisionID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = ZGMTRAttributeIDTypeGlobalAttributeClusterRevisionID,

    // Cluster UnitLocalization deprecated attribute names
    ZGMTRClusterUnitLocalizationAttributeTemperatureUnitID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterUnitLocalizationAttributeTemperatureUnitID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000000,
    ZGMTRClusterUnitLocalizationAttributeGeneratedCommandListID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterUnitLocalizationAttributeGeneratedCommandListID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = ZGMTRClusterGlobalAttributeGeneratedCommandListID,
    ZGMTRClusterUnitLocalizationAttributeAcceptedCommandListID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterUnitLocalizationAttributeAcceptedCommandListID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = ZGMTRClusterGlobalAttributeAcceptedCommandListID,
    ZGMTRClusterUnitLocalizationAttributeAttributeListID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterUnitLocalizationAttributeAttributeListID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = ZGMTRClusterGlobalAttributeAttributeListID,
    ZGMTRClusterUnitLocalizationAttributeFeatureMapID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterUnitLocalizationAttributeFeatureMapID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = ZGMTRClusterGlobalAttributeFeatureMapID,
    ZGMTRClusterUnitLocalizationAttributeClusterRevisionID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterUnitLocalizationAttributeClusterRevisionID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = ZGMTRClusterGlobalAttributeClusterRevisionID,

    // Cluster UnitLocalization attributes
    ZGMTRAttributeIDTypeClusterUnitLocalizationAttributeTemperatureUnitID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000000,
    ZGMTRAttributeIDTypeClusterUnitLocalizationAttributeSupportedTemperatureUnitsID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000001,
    ZGMTRAttributeIDTypeClusterUnitLocalizationAttributeGeneratedCommandListID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = ZGMTRAttributeIDTypeGlobalAttributeGeneratedCommandListID,
    ZGMTRAttributeIDTypeClusterUnitLocalizationAttributeAcceptedCommandListID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = ZGMTRAttributeIDTypeGlobalAttributeAcceptedCommandListID,
    ZGMTRAttributeIDTypeClusterUnitLocalizationAttributeAttributeListID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = ZGMTRAttributeIDTypeGlobalAttributeAttributeListID,
    ZGMTRAttributeIDTypeClusterUnitLocalizationAttributeFeatureMapID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = ZGMTRAttributeIDTypeGlobalAttributeFeatureMapID,
    ZGMTRAttributeIDTypeClusterUnitLocalizationAttributeClusterRevisionID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = ZGMTRAttributeIDTypeGlobalAttributeClusterRevisionID,

    // Cluster PowerSourceConfiguration deprecated attribute names
    ZGMTRClusterPowerSourceConfigurationAttributeSourcesID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterPowerSourceConfigurationAttributeSourcesID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000000,
    ZGMTRClusterPowerSourceConfigurationAttributeGeneratedCommandListID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterPowerSourceConfigurationAttributeGeneratedCommandListID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = ZGMTRClusterGlobalAttributeGeneratedCommandListID,
    ZGMTRClusterPowerSourceConfigurationAttributeAcceptedCommandListID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterPowerSourceConfigurationAttributeAcceptedCommandListID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = ZGMTRClusterGlobalAttributeAcceptedCommandListID,
    ZGMTRClusterPowerSourceConfigurationAttributeAttributeListID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterPowerSourceConfigurationAttributeAttributeListID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = ZGMTRClusterGlobalAttributeAttributeListID,
    ZGMTRClusterPowerSourceConfigurationAttributeFeatureMapID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterPowerSourceConfigurationAttributeFeatureMapID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = ZGMTRClusterGlobalAttributeFeatureMapID,
    ZGMTRClusterPowerSourceConfigurationAttributeClusterRevisionID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterPowerSourceConfigurationAttributeClusterRevisionID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = ZGMTRClusterGlobalAttributeClusterRevisionID,

    // Cluster PowerSourceConfiguration attributes
    ZGMTRAttributeIDTypeClusterPowerSourceConfigurationAttributeSourcesID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000000,
    ZGMTRAttributeIDTypeClusterPowerSourceConfigurationAttributeGeneratedCommandListID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = ZGMTRAttributeIDTypeGlobalAttributeGeneratedCommandListID,
    ZGMTRAttributeIDTypeClusterPowerSourceConfigurationAttributeAcceptedCommandListID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = ZGMTRAttributeIDTypeGlobalAttributeAcceptedCommandListID,
    ZGMTRAttributeIDTypeClusterPowerSourceConfigurationAttributeAttributeListID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = ZGMTRAttributeIDTypeGlobalAttributeAttributeListID,
    ZGMTRAttributeIDTypeClusterPowerSourceConfigurationAttributeFeatureMapID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = ZGMTRAttributeIDTypeGlobalAttributeFeatureMapID,
    ZGMTRAttributeIDTypeClusterPowerSourceConfigurationAttributeClusterRevisionID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = ZGMTRAttributeIDTypeGlobalAttributeClusterRevisionID,

    // Cluster PowerSource deprecated attribute names
    ZGMTRClusterPowerSourceAttributeStatusID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterPowerSourceAttributeStatusID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000000,
    ZGMTRClusterPowerSourceAttributeOrderID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterPowerSourceAttributeOrderID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000001,
    ZGMTRClusterPowerSourceAttributeDescriptionID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterPowerSourceAttributeDescriptionID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000002,
    ZGMTRClusterPowerSourceAttributeWiredAssessedInputVoltageID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterPowerSourceAttributeWiredAssessedInputVoltageID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000003,
    ZGMTRClusterPowerSourceAttributeWiredAssessedInputFrequencyID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterPowerSourceAttributeWiredAssessedInputFrequencyID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000004,
    ZGMTRClusterPowerSourceAttributeWiredCurrentTypeID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterPowerSourceAttributeWiredCurrentTypeID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000005,
    ZGMTRClusterPowerSourceAttributeWiredAssessedCurrentID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterPowerSourceAttributeWiredAssessedCurrentID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000006,
    ZGMTRClusterPowerSourceAttributeWiredNominalVoltageID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterPowerSourceAttributeWiredNominalVoltageID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000007,
    ZGMTRClusterPowerSourceAttributeWiredMaximumCurrentID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterPowerSourceAttributeWiredMaximumCurrentID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000008,
    ZGMTRClusterPowerSourceAttributeWiredPresentID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterPowerSourceAttributeWiredPresentID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000009,
    ZGMTRClusterPowerSourceAttributeActiveWiredFaultsID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterPowerSourceAttributeActiveWiredFaultsID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x0000000A,
    ZGMTRClusterPowerSourceAttributeBatVoltageID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterPowerSourceAttributeBatVoltageID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x0000000B,
    ZGMTRClusterPowerSourceAttributeBatPercentRemainingID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterPowerSourceAttributeBatPercentRemainingID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x0000000C,
    ZGMTRClusterPowerSourceAttributeBatTimeRemainingID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterPowerSourceAttributeBatTimeRemainingID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x0000000D,
    ZGMTRClusterPowerSourceAttributeBatChargeLevelID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterPowerSourceAttributeBatChargeLevelID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x0000000E,
    ZGMTRClusterPowerSourceAttributeBatReplacementNeededID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterPowerSourceAttributeBatReplacementNeededID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x0000000F,
    ZGMTRClusterPowerSourceAttributeBatReplaceabilityID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterPowerSourceAttributeBatReplaceabilityID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000010,
    ZGMTRClusterPowerSourceAttributeBatPresentID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterPowerSourceAttributeBatPresentID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000011,
    ZGMTRClusterPowerSourceAttributeActiveBatFaultsID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterPowerSourceAttributeActiveBatFaultsID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000012,
    ZGMTRClusterPowerSourceAttributeBatReplacementDescriptionID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterPowerSourceAttributeBatReplacementDescriptionID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000013,
    ZGMTRClusterPowerSourceAttributeBatCommonDesignationID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterPowerSourceAttributeBatCommonDesignationID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000014,
    ZGMTRClusterPowerSourceAttributeBatANSIDesignationID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterPowerSourceAttributeBatANSIDesignationID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000015,
    ZGMTRClusterPowerSourceAttributeBatIECDesignationID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterPowerSourceAttributeBatIECDesignationID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000016,
    ZGMTRClusterPowerSourceAttributeBatApprovedChemistryID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterPowerSourceAttributeBatApprovedChemistryID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000017,
    ZGMTRClusterPowerSourceAttributeBatCapacityID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterPowerSourceAttributeBatCapacityID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000018,
    ZGMTRClusterPowerSourceAttributeBatQuantityID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterPowerSourceAttributeBatQuantityID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000019,
    ZGMTRClusterPowerSourceAttributeBatChargeStateID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterPowerSourceAttributeBatChargeStateID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x0000001A,
    ZGMTRClusterPowerSourceAttributeBatTimeToFullChargeID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterPowerSourceAttributeBatTimeToFullChargeID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x0000001B,
    ZGMTRClusterPowerSourceAttributeBatFunctionalWhileChargingID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterPowerSourceAttributeBatFunctionalWhileChargingID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x0000001C,
    ZGMTRClusterPowerSourceAttributeBatChargingCurrentID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterPowerSourceAttributeBatChargingCurrentID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x0000001D,
    ZGMTRClusterPowerSourceAttributeActiveBatChargeFaultsID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterPowerSourceAttributeActiveBatChargeFaultsID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x0000001E,
    ZGMTRClusterPowerSourceAttributeGeneratedCommandListID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterPowerSourceAttributeGeneratedCommandListID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = ZGMTRClusterGlobalAttributeGeneratedCommandListID,
    ZGMTRClusterPowerSourceAttributeAcceptedCommandListID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterPowerSourceAttributeAcceptedCommandListID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = ZGMTRClusterGlobalAttributeAcceptedCommandListID,
    ZGMTRClusterPowerSourceAttributeAttributeListID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterPowerSourceAttributeAttributeListID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = ZGMTRClusterGlobalAttributeAttributeListID,
    ZGMTRClusterPowerSourceAttributeFeatureMapID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterPowerSourceAttributeFeatureMapID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = ZGMTRClusterGlobalAttributeFeatureMapID,
    ZGMTRClusterPowerSourceAttributeClusterRevisionID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterPowerSourceAttributeClusterRevisionID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = ZGMTRClusterGlobalAttributeClusterRevisionID,

    // Cluster PowerSource attributes
    ZGMTRAttributeIDTypeClusterPowerSourceAttributeStatusID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000000,
    ZGMTRAttributeIDTypeClusterPowerSourceAttributeOrderID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000001,
    ZGMTRAttributeIDTypeClusterPowerSourceAttributeDescriptionID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000002,
    ZGMTRAttributeIDTypeClusterPowerSourceAttributeWiredAssessedInputVoltageID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000003,
    ZGMTRAttributeIDTypeClusterPowerSourceAttributeWiredAssessedInputFrequencyID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000004,
    ZGMTRAttributeIDTypeClusterPowerSourceAttributeWiredCurrentTypeID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000005,
    ZGMTRAttributeIDTypeClusterPowerSourceAttributeWiredAssessedCurrentID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000006,
    ZGMTRAttributeIDTypeClusterPowerSourceAttributeWiredNominalVoltageID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000007,
    ZGMTRAttributeIDTypeClusterPowerSourceAttributeWiredMaximumCurrentID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000008,
    ZGMTRAttributeIDTypeClusterPowerSourceAttributeWiredPresentID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000009,
    ZGMTRAttributeIDTypeClusterPowerSourceAttributeActiveWiredFaultsID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x0000000A,
    ZGMTRAttributeIDTypeClusterPowerSourceAttributeBatVoltageID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x0000000B,
    ZGMTRAttributeIDTypeClusterPowerSourceAttributeBatPercentRemainingID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x0000000C,
    ZGMTRAttributeIDTypeClusterPowerSourceAttributeBatTimeRemainingID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x0000000D,
    ZGMTRAttributeIDTypeClusterPowerSourceAttributeBatChargeLevelID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x0000000E,
    ZGMTRAttributeIDTypeClusterPowerSourceAttributeBatReplacementNeededID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x0000000F,
    ZGMTRAttributeIDTypeClusterPowerSourceAttributeBatReplaceabilityID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000010,
    ZGMTRAttributeIDTypeClusterPowerSourceAttributeBatPresentID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000011,
    ZGMTRAttributeIDTypeClusterPowerSourceAttributeActiveBatFaultsID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000012,
    ZGMTRAttributeIDTypeClusterPowerSourceAttributeBatReplacementDescriptionID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000013,
    ZGMTRAttributeIDTypeClusterPowerSourceAttributeBatCommonDesignationID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000014,
    ZGMTRAttributeIDTypeClusterPowerSourceAttributeBatANSIDesignationID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000015,
    ZGMTRAttributeIDTypeClusterPowerSourceAttributeBatIECDesignationID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000016,
    ZGMTRAttributeIDTypeClusterPowerSourceAttributeBatApprovedChemistryID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000017,
    ZGMTRAttributeIDTypeClusterPowerSourceAttributeBatCapacityID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000018,
    ZGMTRAttributeIDTypeClusterPowerSourceAttributeBatQuantityID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000019,
    ZGMTRAttributeIDTypeClusterPowerSourceAttributeBatChargeStateID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x0000001A,
    ZGMTRAttributeIDTypeClusterPowerSourceAttributeBatTimeToFullChargeID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x0000001B,
    ZGMTRAttributeIDTypeClusterPowerSourceAttributeBatFunctionalWhileChargingID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x0000001C,
    ZGMTRAttributeIDTypeClusterPowerSourceAttributeBatChargingCurrentID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x0000001D,
    ZGMTRAttributeIDTypeClusterPowerSourceAttributeActiveBatChargeFaultsID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x0000001E,
    ZGMTRAttributeIDTypeClusterPowerSourceAttributeEndpointListID ZGMTR_AVAILABLE(ios(17.4), macos(14.4), watchos(10.4), tvos(17.4)) = 0x0000001F,
    ZGMTRAttributeIDTypeClusterPowerSourceAttributeGeneratedCommandListID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = ZGMTRAttributeIDTypeGlobalAttributeGeneratedCommandListID,
    ZGMTRAttributeIDTypeClusterPowerSourceAttributeAcceptedCommandListID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = ZGMTRAttributeIDTypeGlobalAttributeAcceptedCommandListID,
    ZGMTRAttributeIDTypeClusterPowerSourceAttributeAttributeListID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = ZGMTRAttributeIDTypeGlobalAttributeAttributeListID,
    ZGMTRAttributeIDTypeClusterPowerSourceAttributeFeatureMapID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = ZGMTRAttributeIDTypeGlobalAttributeFeatureMapID,
    ZGMTRAttributeIDTypeClusterPowerSourceAttributeClusterRevisionID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = ZGMTRAttributeIDTypeGlobalAttributeClusterRevisionID,

    // Cluster GeneralCommissioning deprecated attribute names
    ZGMTRClusterGeneralCommissioningAttributeBreadcrumbID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterGeneralCommissioningAttributeBreadcrumbID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000000,
    ZGMTRClusterGeneralCommissioningAttributeBasicCommissioningInfoID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterGeneralCommissioningAttributeBasicCommissioningInfoID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000001,
    ZGMTRClusterGeneralCommissioningAttributeRegulatoryConfigID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterGeneralCommissioningAttributeRegulatoryConfigID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000002,
    ZGMTRClusterGeneralCommissioningAttributeLocationCapabilityID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterGeneralCommissioningAttributeLocationCapabilityID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000003,
    ZGMTRClusterGeneralCommissioningAttributeSupportsConcurrentConnectionID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterGeneralCommissioningAttributeSupportsConcurrentConnectionID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000004,
    ZGMTRClusterGeneralCommissioningAttributeGeneratedCommandListID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterGeneralCommissioningAttributeGeneratedCommandListID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = ZGMTRClusterGlobalAttributeGeneratedCommandListID,
    ZGMTRClusterGeneralCommissioningAttributeAcceptedCommandListID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterGeneralCommissioningAttributeAcceptedCommandListID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = ZGMTRClusterGlobalAttributeAcceptedCommandListID,
    ZGMTRClusterGeneralCommissioningAttributeAttributeListID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterGeneralCommissioningAttributeAttributeListID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = ZGMTRClusterGlobalAttributeAttributeListID,
    ZGMTRClusterGeneralCommissioningAttributeFeatureMapID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterGeneralCommissioningAttributeFeatureMapID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = ZGMTRClusterGlobalAttributeFeatureMapID,
    ZGMTRClusterGeneralCommissioningAttributeClusterRevisionID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterGeneralCommissioningAttributeClusterRevisionID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = ZGMTRClusterGlobalAttributeClusterRevisionID,

    // Cluster GeneralCommissioning attributes
    ZGMTRAttributeIDTypeClusterGeneralCommissioningAttributeBreadcrumbID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000000,
    ZGMTRAttributeIDTypeClusterGeneralCommissioningAttributeBasicCommissioningInfoID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000001,
    ZGMTRAttributeIDTypeClusterGeneralCommissioningAttributeRegulatoryConfigID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000002,
    ZGMTRAttributeIDTypeClusterGeneralCommissioningAttributeLocationCapabilityID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000003,
    ZGMTRAttributeIDTypeClusterGeneralCommissioningAttributeSupportsConcurrentConnectionID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000004,
    ZGMTRAttributeIDTypeClusterGeneralCommissioningAttributeTCAcceptedVersionID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000005,
    ZGMTRAttributeIDTypeClusterGeneralCommissioningAttributeTCMinRequiredVersionID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000006,
    ZGMTRAttributeIDTypeClusterGeneralCommissioningAttributeTCAcknowledgementsID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000007,
    ZGMTRAttributeIDTypeClusterGeneralCommissioningAttributeTCAcknowledgementsRequiredID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000008,
    ZGMTRAttributeIDTypeClusterGeneralCommissioningAttributeTCUpdateDeadlineID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000009,
    ZGMTRAttributeIDTypeClusterGeneralCommissioningAttributeRecoveryIdentifierID ZGMTR_PROVISIONALLY_AVAILABLE = 0x0000000A,
    ZGMTRAttributeIDTypeClusterGeneralCommissioningAttributeNetworkRecoveryReasonID ZGMTR_PROVISIONALLY_AVAILABLE = 0x0000000B,
    ZGMTRAttributeIDTypeClusterGeneralCommissioningAttributeIsCommissioningWithoutPowerID ZGMTR_PROVISIONALLY_AVAILABLE = 0x0000000C,
    ZGMTRAttributeIDTypeClusterGeneralCommissioningAttributeGeneratedCommandListID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = ZGMTRAttributeIDTypeGlobalAttributeGeneratedCommandListID,
    ZGMTRAttributeIDTypeClusterGeneralCommissioningAttributeAcceptedCommandListID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = ZGMTRAttributeIDTypeGlobalAttributeAcceptedCommandListID,
    ZGMTRAttributeIDTypeClusterGeneralCommissioningAttributeAttributeListID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = ZGMTRAttributeIDTypeGlobalAttributeAttributeListID,
    ZGMTRAttributeIDTypeClusterGeneralCommissioningAttributeFeatureMapID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = ZGMTRAttributeIDTypeGlobalAttributeFeatureMapID,
    ZGMTRAttributeIDTypeClusterGeneralCommissioningAttributeClusterRevisionID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = ZGMTRAttributeIDTypeGlobalAttributeClusterRevisionID,

    // Cluster NetworkCommissioning deprecated attribute names
    ZGMTRClusterNetworkCommissioningAttributeMaxNetworksID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterNetworkCommissioningAttributeMaxNetworksID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000000,
    ZGMTRClusterNetworkCommissioningAttributeNetworksID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterNetworkCommissioningAttributeNetworksID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000001,
    ZGMTRClusterNetworkCommissioningAttributeScanMaxTimeSecondsID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterNetworkCommissioningAttributeScanMaxTimeSecondsID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000002,
    ZGMTRClusterNetworkCommissioningAttributeConnectMaxTimeSecondsID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterNetworkCommissioningAttributeConnectMaxTimeSecondsID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000003,
    ZGMTRClusterNetworkCommissioningAttributeInterfaceEnabledID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterNetworkCommissioningAttributeInterfaceEnabledID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000004,
    ZGMTRClusterNetworkCommissioningAttributeLastNetworkingStatusID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterNetworkCommissioningAttributeLastNetworkingStatusID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000005,
    ZGMTRClusterNetworkCommissioningAttributeLastNetworkIDID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterNetworkCommissioningAttributeLastNetworkIDID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000006,
    ZGMTRClusterNetworkCommissioningAttributeLastConnectErrorValueID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterNetworkCommissioningAttributeLastConnectErrorValueID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000007,
    ZGMTRClusterNetworkCommissioningAttributeGeneratedCommandListID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterNetworkCommissioningAttributeGeneratedCommandListID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = ZGMTRClusterGlobalAttributeGeneratedCommandListID,
    ZGMTRClusterNetworkCommissioningAttributeAcceptedCommandListID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterNetworkCommissioningAttributeAcceptedCommandListID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = ZGMTRClusterGlobalAttributeAcceptedCommandListID,
    ZGMTRClusterNetworkCommissioningAttributeAttributeListID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterNetworkCommissioningAttributeAttributeListID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = ZGMTRClusterGlobalAttributeAttributeListID,
    ZGMTRClusterNetworkCommissioningAttributeFeatureMapID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterNetworkCommissioningAttributeFeatureMapID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = ZGMTRClusterGlobalAttributeFeatureMapID,
    ZGMTRClusterNetworkCommissioningAttributeClusterRevisionID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterNetworkCommissioningAttributeClusterRevisionID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = ZGMTRClusterGlobalAttributeClusterRevisionID,

    // Cluster NetworkCommissioning attributes
    ZGMTRAttributeIDTypeClusterNetworkCommissioningAttributeMaxNetworksID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000000,
    ZGMTRAttributeIDTypeClusterNetworkCommissioningAttributeNetworksID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000001,
    ZGMTRAttributeIDTypeClusterNetworkCommissioningAttributeScanMaxTimeSecondsID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000002,
    ZGMTRAttributeIDTypeClusterNetworkCommissioningAttributeConnectMaxTimeSecondsID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000003,
    ZGMTRAttributeIDTypeClusterNetworkCommissioningAttributeInterfaceEnabledID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000004,
    ZGMTRAttributeIDTypeClusterNetworkCommissioningAttributeLastNetworkingStatusID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000005,
    ZGMTRAttributeIDTypeClusterNetworkCommissioningAttributeLastNetworkIDID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000006,
    ZGMTRAttributeIDTypeClusterNetworkCommissioningAttributeLastConnectErrorValueID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000007,
    ZGMTRAttributeIDTypeClusterNetworkCommissioningAttributeSupportedWiFiBandsID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = 0x00000008,
    ZGMTRAttributeIDTypeClusterNetworkCommissioningAttributeSupportedThreadFeaturesID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = 0x00000009,
    ZGMTRAttributeIDTypeClusterNetworkCommissioningAttributeThreadVersionID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = 0x0000000A,
    ZGMTRAttributeIDTypeClusterNetworkCommissioningAttributeGeneratedCommandListID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = ZGMTRAttributeIDTypeGlobalAttributeGeneratedCommandListID,
    ZGMTRAttributeIDTypeClusterNetworkCommissioningAttributeAcceptedCommandListID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = ZGMTRAttributeIDTypeGlobalAttributeAcceptedCommandListID,
    ZGMTRAttributeIDTypeClusterNetworkCommissioningAttributeAttributeListID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = ZGMTRAttributeIDTypeGlobalAttributeAttributeListID,
    ZGMTRAttributeIDTypeClusterNetworkCommissioningAttributeFeatureMapID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = ZGMTRAttributeIDTypeGlobalAttributeFeatureMapID,
    ZGMTRAttributeIDTypeClusterNetworkCommissioningAttributeClusterRevisionID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = ZGMTRAttributeIDTypeGlobalAttributeClusterRevisionID,

    // Cluster DiagnosticLogs deprecated attribute names
    ZGMTRClusterDiagnosticLogsAttributeGeneratedCommandListID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterDiagnosticLogsAttributeGeneratedCommandListID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = ZGMTRClusterGlobalAttributeGeneratedCommandListID,
    ZGMTRClusterDiagnosticLogsAttributeAcceptedCommandListID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterDiagnosticLogsAttributeAcceptedCommandListID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = ZGMTRClusterGlobalAttributeAcceptedCommandListID,
    ZGMTRClusterDiagnosticLogsAttributeAttributeListID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterDiagnosticLogsAttributeAttributeListID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = ZGMTRClusterGlobalAttributeAttributeListID,
    ZGMTRClusterDiagnosticLogsAttributeFeatureMapID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterDiagnosticLogsAttributeFeatureMapID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = ZGMTRClusterGlobalAttributeFeatureMapID,
    ZGMTRClusterDiagnosticLogsAttributeClusterRevisionID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterDiagnosticLogsAttributeClusterRevisionID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = ZGMTRClusterGlobalAttributeClusterRevisionID,

    // Cluster DiagnosticLogs attributes
    ZGMTRAttributeIDTypeClusterDiagnosticLogsAttributeGeneratedCommandListID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = ZGMTRAttributeIDTypeGlobalAttributeGeneratedCommandListID,
    ZGMTRAttributeIDTypeClusterDiagnosticLogsAttributeAcceptedCommandListID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = ZGMTRAttributeIDTypeGlobalAttributeAcceptedCommandListID,
    ZGMTRAttributeIDTypeClusterDiagnosticLogsAttributeAttributeListID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = ZGMTRAttributeIDTypeGlobalAttributeAttributeListID,
    ZGMTRAttributeIDTypeClusterDiagnosticLogsAttributeFeatureMapID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = ZGMTRAttributeIDTypeGlobalAttributeFeatureMapID,
    ZGMTRAttributeIDTypeClusterDiagnosticLogsAttributeClusterRevisionID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = ZGMTRAttributeIDTypeGlobalAttributeClusterRevisionID,

    // Cluster GeneralDiagnostics deprecated attribute names
    ZGMTRClusterGeneralDiagnosticsAttributeNetworkInterfacesID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterGeneralDiagnosticsAttributeNetworkInterfacesID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000000,
    ZGMTRClusterGeneralDiagnosticsAttributeRebootCountID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterGeneralDiagnosticsAttributeRebootCountID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000001,
    ZGMTRClusterGeneralDiagnosticsAttributeUpTimeID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterGeneralDiagnosticsAttributeUpTimeID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000002,
    ZGMTRClusterGeneralDiagnosticsAttributeTotalOperationalHoursID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterGeneralDiagnosticsAttributeTotalOperationalHoursID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000003,
    ZGMTRClusterGeneralDiagnosticsAttributeBootReasonsID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterGeneralDiagnosticsAttributeBootReasonID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000004,
    ZGMTRClusterGeneralDiagnosticsAttributeActiveHardwareFaultsID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterGeneralDiagnosticsAttributeActiveHardwareFaultsID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000005,
    ZGMTRClusterGeneralDiagnosticsAttributeActiveRadioFaultsID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterGeneralDiagnosticsAttributeActiveRadioFaultsID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000006,
    ZGMTRClusterGeneralDiagnosticsAttributeActiveNetworkFaultsID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterGeneralDiagnosticsAttributeActiveNetworkFaultsID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000007,
    ZGMTRClusterGeneralDiagnosticsAttributeTestEventTriggersEnabledID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterGeneralDiagnosticsAttributeTestEventTriggersEnabledID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000008,
    ZGMTRClusterGeneralDiagnosticsAttributeGeneratedCommandListID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterGeneralDiagnosticsAttributeGeneratedCommandListID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = ZGMTRClusterGlobalAttributeGeneratedCommandListID,
    ZGMTRClusterGeneralDiagnosticsAttributeAcceptedCommandListID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterGeneralDiagnosticsAttributeAcceptedCommandListID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = ZGMTRClusterGlobalAttributeAcceptedCommandListID,
    ZGMTRClusterGeneralDiagnosticsAttributeAttributeListID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterGeneralDiagnosticsAttributeAttributeListID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = ZGMTRClusterGlobalAttributeAttributeListID,
    ZGMTRClusterGeneralDiagnosticsAttributeFeatureMapID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterGeneralDiagnosticsAttributeFeatureMapID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = ZGMTRClusterGlobalAttributeFeatureMapID,
    ZGMTRClusterGeneralDiagnosticsAttributeClusterRevisionID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterGeneralDiagnosticsAttributeClusterRevisionID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = ZGMTRClusterGlobalAttributeClusterRevisionID,

    // Cluster GeneralDiagnostics attributes
    ZGMTRAttributeIDTypeClusterGeneralDiagnosticsAttributeNetworkInterfacesID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000000,
    ZGMTRAttributeIDTypeClusterGeneralDiagnosticsAttributeRebootCountID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000001,
    ZGMTRAttributeIDTypeClusterGeneralDiagnosticsAttributeUpTimeID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000002,
    ZGMTRAttributeIDTypeClusterGeneralDiagnosticsAttributeTotalOperationalHoursID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000003,
    ZGMTRAttributeIDTypeClusterGeneralDiagnosticsAttributeBootReasonID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000004,
    ZGMTRAttributeIDTypeClusterGeneralDiagnosticsAttributeActiveHardwareFaultsID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000005,
    ZGMTRAttributeIDTypeClusterGeneralDiagnosticsAttributeActiveRadioFaultsID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000006,
    ZGMTRAttributeIDTypeClusterGeneralDiagnosticsAttributeActiveNetworkFaultsID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000007,
    ZGMTRAttributeIDTypeClusterGeneralDiagnosticsAttributeTestEventTriggersEnabledID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000008,
    ZGMTRAttributeIDTypeClusterGeneralDiagnosticsAttributeDeviceLoadStatusID ZGMTR_PROVISIONALLY_AVAILABLE = 0x0000000A,
    ZGMTRAttributeIDTypeClusterGeneralDiagnosticsAttributeGeneratedCommandListID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = ZGMTRAttributeIDTypeGlobalAttributeGeneratedCommandListID,
    ZGMTRAttributeIDTypeClusterGeneralDiagnosticsAttributeAcceptedCommandListID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = ZGMTRAttributeIDTypeGlobalAttributeAcceptedCommandListID,
    ZGMTRAttributeIDTypeClusterGeneralDiagnosticsAttributeAttributeListID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = ZGMTRAttributeIDTypeGlobalAttributeAttributeListID,
    ZGMTRAttributeIDTypeClusterGeneralDiagnosticsAttributeFeatureMapID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = ZGMTRAttributeIDTypeGlobalAttributeFeatureMapID,
    ZGMTRAttributeIDTypeClusterGeneralDiagnosticsAttributeClusterRevisionID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = ZGMTRAttributeIDTypeGlobalAttributeClusterRevisionID,

    // Cluster SoftwareDiagnostics deprecated attribute names
    ZGMTRClusterSoftwareDiagnosticsAttributeThreadMetricsID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterSoftwareDiagnosticsAttributeThreadMetricsID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000000,
    ZGMTRClusterSoftwareDiagnosticsAttributeCurrentHeapFreeID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterSoftwareDiagnosticsAttributeCurrentHeapFreeID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000001,
    ZGMTRClusterSoftwareDiagnosticsAttributeCurrentHeapUsedID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterSoftwareDiagnosticsAttributeCurrentHeapUsedID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000002,
    ZGMTRClusterSoftwareDiagnosticsAttributeCurrentHeapHighWatermarkID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterSoftwareDiagnosticsAttributeCurrentHeapHighWatermarkID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000003,
    ZGMTRClusterSoftwareDiagnosticsAttributeGeneratedCommandListID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterSoftwareDiagnosticsAttributeGeneratedCommandListID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = ZGMTRClusterGlobalAttributeGeneratedCommandListID,
    ZGMTRClusterSoftwareDiagnosticsAttributeAcceptedCommandListID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterSoftwareDiagnosticsAttributeAcceptedCommandListID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = ZGMTRClusterGlobalAttributeAcceptedCommandListID,
    ZGMTRClusterSoftwareDiagnosticsAttributeAttributeListID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterSoftwareDiagnosticsAttributeAttributeListID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = ZGMTRClusterGlobalAttributeAttributeListID,
    ZGMTRClusterSoftwareDiagnosticsAttributeFeatureMapID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterSoftwareDiagnosticsAttributeFeatureMapID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = ZGMTRClusterGlobalAttributeFeatureMapID,
    ZGMTRClusterSoftwareDiagnosticsAttributeClusterRevisionID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterSoftwareDiagnosticsAttributeClusterRevisionID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = ZGMTRClusterGlobalAttributeClusterRevisionID,

    // Cluster SoftwareDiagnostics attributes
    ZGMTRAttributeIDTypeClusterSoftwareDiagnosticsAttributeThreadMetricsID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000000,
    ZGMTRAttributeIDTypeClusterSoftwareDiagnosticsAttributeCurrentHeapFreeID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000001,
    ZGMTRAttributeIDTypeClusterSoftwareDiagnosticsAttributeCurrentHeapUsedID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000002,
    ZGMTRAttributeIDTypeClusterSoftwareDiagnosticsAttributeCurrentHeapHighWatermarkID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000003,
    ZGMTRAttributeIDTypeClusterSoftwareDiagnosticsAttributeGeneratedCommandListID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = ZGMTRAttributeIDTypeGlobalAttributeGeneratedCommandListID,
    ZGMTRAttributeIDTypeClusterSoftwareDiagnosticsAttributeAcceptedCommandListID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = ZGMTRAttributeIDTypeGlobalAttributeAcceptedCommandListID,
    ZGMTRAttributeIDTypeClusterSoftwareDiagnosticsAttributeAttributeListID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = ZGMTRAttributeIDTypeGlobalAttributeAttributeListID,
    ZGMTRAttributeIDTypeClusterSoftwareDiagnosticsAttributeFeatureMapID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = ZGMTRAttributeIDTypeGlobalAttributeFeatureMapID,
    ZGMTRAttributeIDTypeClusterSoftwareDiagnosticsAttributeClusterRevisionID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = ZGMTRAttributeIDTypeGlobalAttributeClusterRevisionID,

    // Cluster ThreadNetworkDiagnostics deprecated attribute names
    ZGMTRClusterThreadNetworkDiagnosticsAttributeChannelID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterThreadNetworkDiagnosticsAttributeChannelID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000000,
    ZGMTRClusterThreadNetworkDiagnosticsAttributeRoutingRoleID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterThreadNetworkDiagnosticsAttributeRoutingRoleID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000001,
    ZGMTRClusterThreadNetworkDiagnosticsAttributeNetworkNameID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterThreadNetworkDiagnosticsAttributeNetworkNameID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000002,
    ZGMTRClusterThreadNetworkDiagnosticsAttributePanIdID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterThreadNetworkDiagnosticsAttributePanIdID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000003,
    ZGMTRClusterThreadNetworkDiagnosticsAttributeExtendedPanIdID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterThreadNetworkDiagnosticsAttributeExtendedPanIdID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000004,
    ZGMTRClusterThreadNetworkDiagnosticsAttributeMeshLocalPrefixID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterThreadNetworkDiagnosticsAttributeMeshLocalPrefixID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000005,
    ZGMTRClusterThreadNetworkDiagnosticsAttributeOverrunCountID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterThreadNetworkDiagnosticsAttributeOverrunCountID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000006,
    ZGMTRClusterThreadNetworkDiagnosticsAttributeNeighborTableListID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterThreadNetworkDiagnosticsAttributeNeighborTableID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000007,
    ZGMTRClusterThreadNetworkDiagnosticsAttributeRouteTableListID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterThreadNetworkDiagnosticsAttributeRouteTableID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000008,
    ZGMTRClusterThreadNetworkDiagnosticsAttributePartitionIdID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterThreadNetworkDiagnosticsAttributePartitionIdID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000009,
    ZGMTRClusterThreadNetworkDiagnosticsAttributeWeightingID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterThreadNetworkDiagnosticsAttributeWeightingID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x0000000A,
    ZGMTRClusterThreadNetworkDiagnosticsAttributeDataVersionID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterThreadNetworkDiagnosticsAttributeDataVersionID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x0000000B,
    ZGMTRClusterThreadNetworkDiagnosticsAttributeStableDataVersionID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterThreadNetworkDiagnosticsAttributeStableDataVersionID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x0000000C,
    ZGMTRClusterThreadNetworkDiagnosticsAttributeLeaderRouterIdID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterThreadNetworkDiagnosticsAttributeLeaderRouterIdID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x0000000D,
    ZGMTRClusterThreadNetworkDiagnosticsAttributeDetachedRoleCountID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterThreadNetworkDiagnosticsAttributeDetachedRoleCountID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x0000000E,
    ZGMTRClusterThreadNetworkDiagnosticsAttributeChildRoleCountID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterThreadNetworkDiagnosticsAttributeChildRoleCountID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x0000000F,
    ZGMTRClusterThreadNetworkDiagnosticsAttributeRouterRoleCountID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterThreadNetworkDiagnosticsAttributeRouterRoleCountID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000010,
    ZGMTRClusterThreadNetworkDiagnosticsAttributeLeaderRoleCountID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterThreadNetworkDiagnosticsAttributeLeaderRoleCountID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000011,
    ZGMTRClusterThreadNetworkDiagnosticsAttributeAttachAttemptCountID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterThreadNetworkDiagnosticsAttributeAttachAttemptCountID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000012,
    ZGMTRClusterThreadNetworkDiagnosticsAttributePartitionIdChangeCountID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterThreadNetworkDiagnosticsAttributePartitionIdChangeCountID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000013,
    ZGMTRClusterThreadNetworkDiagnosticsAttributeBetterPartitionAttachAttemptCountID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterThreadNetworkDiagnosticsAttributeBetterPartitionAttachAttemptCountID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000014,
    ZGMTRClusterThreadNetworkDiagnosticsAttributeParentChangeCountID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterThreadNetworkDiagnosticsAttributeParentChangeCountID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000015,
    ZGMTRClusterThreadNetworkDiagnosticsAttributeTxTotalCountID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterThreadNetworkDiagnosticsAttributeTxTotalCountID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000016,
    ZGMTRClusterThreadNetworkDiagnosticsAttributeTxUnicastCountID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterThreadNetworkDiagnosticsAttributeTxUnicastCountID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000017,
    ZGMTRClusterThreadNetworkDiagnosticsAttributeTxBroadcastCountID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterThreadNetworkDiagnosticsAttributeTxBroadcastCountID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000018,
    ZGMTRClusterThreadNetworkDiagnosticsAttributeTxAckRequestedCountID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterThreadNetworkDiagnosticsAttributeTxAckRequestedCountID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000019,
    ZGMTRClusterThreadNetworkDiagnosticsAttributeTxAckedCountID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterThreadNetworkDiagnosticsAttributeTxAckedCountID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x0000001A,
    ZGMTRClusterThreadNetworkDiagnosticsAttributeTxNoAckRequestedCountID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterThreadNetworkDiagnosticsAttributeTxNoAckRequestedCountID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x0000001B,
    ZGMTRClusterThreadNetworkDiagnosticsAttributeTxDataCountID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterThreadNetworkDiagnosticsAttributeTxDataCountID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x0000001C,
    ZGMTRClusterThreadNetworkDiagnosticsAttributeTxDataPollCountID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterThreadNetworkDiagnosticsAttributeTxDataPollCountID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x0000001D,
    ZGMTRClusterThreadNetworkDiagnosticsAttributeTxBeaconCountID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterThreadNetworkDiagnosticsAttributeTxBeaconCountID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x0000001E,
    ZGMTRClusterThreadNetworkDiagnosticsAttributeTxBeaconRequestCountID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterThreadNetworkDiagnosticsAttributeTxBeaconRequestCountID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x0000001F,
    ZGMTRClusterThreadNetworkDiagnosticsAttributeTxOtherCountID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterThreadNetworkDiagnosticsAttributeTxOtherCountID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000020,
    ZGMTRClusterThreadNetworkDiagnosticsAttributeTxRetryCountID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterThreadNetworkDiagnosticsAttributeTxRetryCountID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000021,
    ZGMTRClusterThreadNetworkDiagnosticsAttributeTxDirectMaxRetryExpiryCountID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterThreadNetworkDiagnosticsAttributeTxDirectMaxRetryExpiryCountID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000022,
    ZGMTRClusterThreadNetworkDiagnosticsAttributeTxIndirectMaxRetryExpiryCountID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterThreadNetworkDiagnosticsAttributeTxIndirectMaxRetryExpiryCountID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000023,
    ZGMTRClusterThreadNetworkDiagnosticsAttributeTxErrCcaCountID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterThreadNetworkDiagnosticsAttributeTxErrCcaCountID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000024,
    ZGMTRClusterThreadNetworkDiagnosticsAttributeTxErrAbortCountID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterThreadNetworkDiagnosticsAttributeTxErrAbortCountID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000025,
    ZGMTRClusterThreadNetworkDiagnosticsAttributeTxErrBusyChannelCountID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterThreadNetworkDiagnosticsAttributeTxErrBusyChannelCountID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000026,
    ZGMTRClusterThreadNetworkDiagnosticsAttributeRxTotalCountID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterThreadNetworkDiagnosticsAttributeRxTotalCountID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000027,
    ZGMTRClusterThreadNetworkDiagnosticsAttributeRxUnicastCountID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterThreadNetworkDiagnosticsAttributeRxUnicastCountID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000028,
    ZGMTRClusterThreadNetworkDiagnosticsAttributeRxBroadcastCountID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterThreadNetworkDiagnosticsAttributeRxBroadcastCountID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000029,
    ZGMTRClusterThreadNetworkDiagnosticsAttributeRxDataCountID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterThreadNetworkDiagnosticsAttributeRxDataCountID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x0000002A,
    ZGMTRClusterThreadNetworkDiagnosticsAttributeRxDataPollCountID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterThreadNetworkDiagnosticsAttributeRxDataPollCountID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x0000002B,
    ZGMTRClusterThreadNetworkDiagnosticsAttributeRxBeaconCountID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterThreadNetworkDiagnosticsAttributeRxBeaconCountID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x0000002C,
    ZGMTRClusterThreadNetworkDiagnosticsAttributeRxBeaconRequestCountID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterThreadNetworkDiagnosticsAttributeRxBeaconRequestCountID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x0000002D,
    ZGMTRClusterThreadNetworkDiagnosticsAttributeRxOtherCountID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterThreadNetworkDiagnosticsAttributeRxOtherCountID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x0000002E,
    ZGMTRClusterThreadNetworkDiagnosticsAttributeRxAddressFilteredCountID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterThreadNetworkDiagnosticsAttributeRxAddressFilteredCountID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x0000002F,
    ZGMTRClusterThreadNetworkDiagnosticsAttributeRxDestAddrFilteredCountID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterThreadNetworkDiagnosticsAttributeRxDestAddrFilteredCountID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000030,
    ZGMTRClusterThreadNetworkDiagnosticsAttributeRxDuplicatedCountID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterThreadNetworkDiagnosticsAttributeRxDuplicatedCountID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000031,
    ZGMTRClusterThreadNetworkDiagnosticsAttributeRxErrNoFrameCountID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterThreadNetworkDiagnosticsAttributeRxErrNoFrameCountID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000032,
    ZGMTRClusterThreadNetworkDiagnosticsAttributeRxErrUnknownNeighborCountID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterThreadNetworkDiagnosticsAttributeRxErrUnknownNeighborCountID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000033,
    ZGMTRClusterThreadNetworkDiagnosticsAttributeRxErrInvalidSrcAddrCountID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterThreadNetworkDiagnosticsAttributeRxErrInvalidSrcAddrCountID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000034,
    ZGMTRClusterThreadNetworkDiagnosticsAttributeRxErrSecCountID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterThreadNetworkDiagnosticsAttributeRxErrSecCountID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000035,
    ZGMTRClusterThreadNetworkDiagnosticsAttributeRxErrFcsCountID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterThreadNetworkDiagnosticsAttributeRxErrFcsCountID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000036,
    ZGMTRClusterThreadNetworkDiagnosticsAttributeRxErrOtherCountID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterThreadNetworkDiagnosticsAttributeRxErrOtherCountID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000037,
    ZGMTRClusterThreadNetworkDiagnosticsAttributeActiveTimestampID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterThreadNetworkDiagnosticsAttributeActiveTimestampID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000038,
    ZGMTRClusterThreadNetworkDiagnosticsAttributePendingTimestampID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterThreadNetworkDiagnosticsAttributePendingTimestampID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000039,
    ZGMTRClusterThreadNetworkDiagnosticsAttributeDelayID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterThreadNetworkDiagnosticsAttributeDelayID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x0000003A,
    ZGMTRClusterThreadNetworkDiagnosticsAttributeSecurityPolicyID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterThreadNetworkDiagnosticsAttributeSecurityPolicyID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x0000003B,
    ZGMTRClusterThreadNetworkDiagnosticsAttributeChannelPage0MaskID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterThreadNetworkDiagnosticsAttributeChannelPage0MaskID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x0000003C,
    ZGMTRClusterThreadNetworkDiagnosticsAttributeOperationalDatasetComponentsID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterThreadNetworkDiagnosticsAttributeOperationalDatasetComponentsID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x0000003D,
    ZGMTRClusterThreadNetworkDiagnosticsAttributeActiveNetworkFaultsListID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterThreadNetworkDiagnosticsAttributeActiveNetworkFaultsListID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x0000003E,
    ZGMTRClusterThreadNetworkDiagnosticsAttributeGeneratedCommandListID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterThreadNetworkDiagnosticsAttributeGeneratedCommandListID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = ZGMTRClusterGlobalAttributeGeneratedCommandListID,
    ZGMTRClusterThreadNetworkDiagnosticsAttributeAcceptedCommandListID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterThreadNetworkDiagnosticsAttributeAcceptedCommandListID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = ZGMTRClusterGlobalAttributeAcceptedCommandListID,
    ZGMTRClusterThreadNetworkDiagnosticsAttributeAttributeListID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterThreadNetworkDiagnosticsAttributeAttributeListID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = ZGMTRClusterGlobalAttributeAttributeListID,
    ZGMTRClusterThreadNetworkDiagnosticsAttributeFeatureMapID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterThreadNetworkDiagnosticsAttributeFeatureMapID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = ZGMTRClusterGlobalAttributeFeatureMapID,
    ZGMTRClusterThreadNetworkDiagnosticsAttributeClusterRevisionID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterThreadNetworkDiagnosticsAttributeClusterRevisionID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = ZGMTRClusterGlobalAttributeClusterRevisionID,

    // Cluster ThreadNetworkDiagnostics attributes
    ZGMTRAttributeIDTypeClusterThreadNetworkDiagnosticsAttributeChannelID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000000,
    ZGMTRAttributeIDTypeClusterThreadNetworkDiagnosticsAttributeRoutingRoleID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000001,
    ZGMTRAttributeIDTypeClusterThreadNetworkDiagnosticsAttributeNetworkNameID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000002,
    ZGMTRAttributeIDTypeClusterThreadNetworkDiagnosticsAttributePanIdID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000003,
    ZGMTRAttributeIDTypeClusterThreadNetworkDiagnosticsAttributeExtendedPanIdID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000004,
    ZGMTRAttributeIDTypeClusterThreadNetworkDiagnosticsAttributeMeshLocalPrefixID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000005,
    ZGMTRAttributeIDTypeClusterThreadNetworkDiagnosticsAttributeOverrunCountID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000006,
    ZGMTRAttributeIDTypeClusterThreadNetworkDiagnosticsAttributeNeighborTableID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000007,
    ZGMTRAttributeIDTypeClusterThreadNetworkDiagnosticsAttributeRouteTableID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000008,
    ZGMTRAttributeIDTypeClusterThreadNetworkDiagnosticsAttributePartitionIdID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000009,
    ZGMTRAttributeIDTypeClusterThreadNetworkDiagnosticsAttributeWeightingID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x0000000A,
    ZGMTRAttributeIDTypeClusterThreadNetworkDiagnosticsAttributeDataVersionID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x0000000B,
    ZGMTRAttributeIDTypeClusterThreadNetworkDiagnosticsAttributeStableDataVersionID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x0000000C,
    ZGMTRAttributeIDTypeClusterThreadNetworkDiagnosticsAttributeLeaderRouterIdID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x0000000D,
    ZGMTRAttributeIDTypeClusterThreadNetworkDiagnosticsAttributeDetachedRoleCountID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x0000000E,
    ZGMTRAttributeIDTypeClusterThreadNetworkDiagnosticsAttributeChildRoleCountID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x0000000F,
    ZGMTRAttributeIDTypeClusterThreadNetworkDiagnosticsAttributeRouterRoleCountID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000010,
    ZGMTRAttributeIDTypeClusterThreadNetworkDiagnosticsAttributeLeaderRoleCountID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000011,
    ZGMTRAttributeIDTypeClusterThreadNetworkDiagnosticsAttributeAttachAttemptCountID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000012,
    ZGMTRAttributeIDTypeClusterThreadNetworkDiagnosticsAttributePartitionIdChangeCountID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000013,
    ZGMTRAttributeIDTypeClusterThreadNetworkDiagnosticsAttributeBetterPartitionAttachAttemptCountID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000014,
    ZGMTRAttributeIDTypeClusterThreadNetworkDiagnosticsAttributeParentChangeCountID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000015,
    ZGMTRAttributeIDTypeClusterThreadNetworkDiagnosticsAttributeTxTotalCountID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000016,
    ZGMTRAttributeIDTypeClusterThreadNetworkDiagnosticsAttributeTxUnicastCountID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000017,
    ZGMTRAttributeIDTypeClusterThreadNetworkDiagnosticsAttributeTxBroadcastCountID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000018,
    ZGMTRAttributeIDTypeClusterThreadNetworkDiagnosticsAttributeTxAckRequestedCountID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000019,
    ZGMTRAttributeIDTypeClusterThreadNetworkDiagnosticsAttributeTxAckedCountID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x0000001A,
    ZGMTRAttributeIDTypeClusterThreadNetworkDiagnosticsAttributeTxNoAckRequestedCountID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x0000001B,
    ZGMTRAttributeIDTypeClusterThreadNetworkDiagnosticsAttributeTxDataCountID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x0000001C,
    ZGMTRAttributeIDTypeClusterThreadNetworkDiagnosticsAttributeTxDataPollCountID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x0000001D,
    ZGMTRAttributeIDTypeClusterThreadNetworkDiagnosticsAttributeTxBeaconCountID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x0000001E,
    ZGMTRAttributeIDTypeClusterThreadNetworkDiagnosticsAttributeTxBeaconRequestCountID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x0000001F,
    ZGMTRAttributeIDTypeClusterThreadNetworkDiagnosticsAttributeTxOtherCountID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000020,
    ZGMTRAttributeIDTypeClusterThreadNetworkDiagnosticsAttributeTxRetryCountID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000021,
    ZGMTRAttributeIDTypeClusterThreadNetworkDiagnosticsAttributeTxDirectMaxRetryExpiryCountID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000022,
    ZGMTRAttributeIDTypeClusterThreadNetworkDiagnosticsAttributeTxIndirectMaxRetryExpiryCountID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000023,
    ZGMTRAttributeIDTypeClusterThreadNetworkDiagnosticsAttributeTxErrCcaCountID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000024,
    ZGMTRAttributeIDTypeClusterThreadNetworkDiagnosticsAttributeTxErrAbortCountID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000025,
    ZGMTRAttributeIDTypeClusterThreadNetworkDiagnosticsAttributeTxErrBusyChannelCountID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000026,
    ZGMTRAttributeIDTypeClusterThreadNetworkDiagnosticsAttributeRxTotalCountID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000027,
    ZGMTRAttributeIDTypeClusterThreadNetworkDiagnosticsAttributeRxUnicastCountID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000028,
    ZGMTRAttributeIDTypeClusterThreadNetworkDiagnosticsAttributeRxBroadcastCountID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000029,
    ZGMTRAttributeIDTypeClusterThreadNetworkDiagnosticsAttributeRxDataCountID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x0000002A,
    ZGMTRAttributeIDTypeClusterThreadNetworkDiagnosticsAttributeRxDataPollCountID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x0000002B,
    ZGMTRAttributeIDTypeClusterThreadNetworkDiagnosticsAttributeRxBeaconCountID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x0000002C,
    ZGMTRAttributeIDTypeClusterThreadNetworkDiagnosticsAttributeRxBeaconRequestCountID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x0000002D,
    ZGMTRAttributeIDTypeClusterThreadNetworkDiagnosticsAttributeRxOtherCountID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x0000002E,
    ZGMTRAttributeIDTypeClusterThreadNetworkDiagnosticsAttributeRxAddressFilteredCountID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x0000002F,
    ZGMTRAttributeIDTypeClusterThreadNetworkDiagnosticsAttributeRxDestAddrFilteredCountID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000030,
    ZGMTRAttributeIDTypeClusterThreadNetworkDiagnosticsAttributeRxDuplicatedCountID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000031,
    ZGMTRAttributeIDTypeClusterThreadNetworkDiagnosticsAttributeRxErrNoFrameCountID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000032,
    ZGMTRAttributeIDTypeClusterThreadNetworkDiagnosticsAttributeRxErrUnknownNeighborCountID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000033,
    ZGMTRAttributeIDTypeClusterThreadNetworkDiagnosticsAttributeRxErrInvalidSrcAddrCountID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000034,
    ZGMTRAttributeIDTypeClusterThreadNetworkDiagnosticsAttributeRxErrSecCountID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000035,
    ZGMTRAttributeIDTypeClusterThreadNetworkDiagnosticsAttributeRxErrFcsCountID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000036,
    ZGMTRAttributeIDTypeClusterThreadNetworkDiagnosticsAttributeRxErrOtherCountID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000037,
    ZGMTRAttributeIDTypeClusterThreadNetworkDiagnosticsAttributeActiveTimestampID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000038,
    ZGMTRAttributeIDTypeClusterThreadNetworkDiagnosticsAttributePendingTimestampID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000039,
    ZGMTRAttributeIDTypeClusterThreadNetworkDiagnosticsAttributeDelayID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x0000003A,
    ZGMTRAttributeIDTypeClusterThreadNetworkDiagnosticsAttributeSecurityPolicyID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x0000003B,
    ZGMTRAttributeIDTypeClusterThreadNetworkDiagnosticsAttributeChannelPage0MaskID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x0000003C,
    ZGMTRAttributeIDTypeClusterThreadNetworkDiagnosticsAttributeOperationalDatasetComponentsID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x0000003D,
    ZGMTRAttributeIDTypeClusterThreadNetworkDiagnosticsAttributeActiveNetworkFaultsListID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x0000003E,
    ZGMTRAttributeIDTypeClusterThreadNetworkDiagnosticsAttributeExtAddressID ZGMTR_PROVISIONALLY_AVAILABLE = 0x0000003F,
    ZGMTRAttributeIDTypeClusterThreadNetworkDiagnosticsAttributeRloc16ID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000040,
    ZGMTRAttributeIDTypeClusterThreadNetworkDiagnosticsAttributeGeneratedCommandListID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = ZGMTRAttributeIDTypeGlobalAttributeGeneratedCommandListID,
    ZGMTRAttributeIDTypeClusterThreadNetworkDiagnosticsAttributeAcceptedCommandListID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = ZGMTRAttributeIDTypeGlobalAttributeAcceptedCommandListID,
    ZGMTRAttributeIDTypeClusterThreadNetworkDiagnosticsAttributeAttributeListID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = ZGMTRAttributeIDTypeGlobalAttributeAttributeListID,
    ZGMTRAttributeIDTypeClusterThreadNetworkDiagnosticsAttributeFeatureMapID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = ZGMTRAttributeIDTypeGlobalAttributeFeatureMapID,
    ZGMTRAttributeIDTypeClusterThreadNetworkDiagnosticsAttributeClusterRevisionID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = ZGMTRAttributeIDTypeGlobalAttributeClusterRevisionID,

    // Cluster WiFiNetworkDiagnostics deprecated attribute names
    ZGMTRClusterWiFiNetworkDiagnosticsAttributeBssidID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterWiFiNetworkDiagnosticsAttributeBSSIDID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000000,
    ZGMTRClusterWiFiNetworkDiagnosticsAttributeSecurityTypeID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterWiFiNetworkDiagnosticsAttributeSecurityTypeID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000001,
    ZGMTRClusterWiFiNetworkDiagnosticsAttributeWiFiVersionID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterWiFiNetworkDiagnosticsAttributeWiFiVersionID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000002,
    ZGMTRClusterWiFiNetworkDiagnosticsAttributeChannelNumberID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterWiFiNetworkDiagnosticsAttributeChannelNumberID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000003,
    ZGMTRClusterWiFiNetworkDiagnosticsAttributeRssiID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterWiFiNetworkDiagnosticsAttributeRSSIID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000004,
    ZGMTRClusterWiFiNetworkDiagnosticsAttributeBeaconLostCountID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterWiFiNetworkDiagnosticsAttributeBeaconLostCountID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000005,
    ZGMTRClusterWiFiNetworkDiagnosticsAttributeBeaconRxCountID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterWiFiNetworkDiagnosticsAttributeBeaconRxCountID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000006,
    ZGMTRClusterWiFiNetworkDiagnosticsAttributePacketMulticastRxCountID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterWiFiNetworkDiagnosticsAttributePacketMulticastRxCountID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000007,
    ZGMTRClusterWiFiNetworkDiagnosticsAttributePacketMulticastTxCountID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterWiFiNetworkDiagnosticsAttributePacketMulticastTxCountID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000008,
    ZGMTRClusterWiFiNetworkDiagnosticsAttributePacketUnicastRxCountID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterWiFiNetworkDiagnosticsAttributePacketUnicastRxCountID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000009,
    ZGMTRClusterWiFiNetworkDiagnosticsAttributePacketUnicastTxCountID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterWiFiNetworkDiagnosticsAttributePacketUnicastTxCountID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x0000000A,
    ZGMTRClusterWiFiNetworkDiagnosticsAttributeCurrentMaxRateID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterWiFiNetworkDiagnosticsAttributeCurrentMaxRateID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x0000000B,
    ZGMTRClusterWiFiNetworkDiagnosticsAttributeOverrunCountID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterWiFiNetworkDiagnosticsAttributeOverrunCountID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x0000000C,
    ZGMTRClusterWiFiNetworkDiagnosticsAttributeGeneratedCommandListID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterWiFiNetworkDiagnosticsAttributeGeneratedCommandListID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = ZGMTRClusterGlobalAttributeGeneratedCommandListID,
    ZGMTRClusterWiFiNetworkDiagnosticsAttributeAcceptedCommandListID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterWiFiNetworkDiagnosticsAttributeAcceptedCommandListID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = ZGMTRClusterGlobalAttributeAcceptedCommandListID,
    ZGMTRClusterWiFiNetworkDiagnosticsAttributeAttributeListID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterWiFiNetworkDiagnosticsAttributeAttributeListID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = ZGMTRClusterGlobalAttributeAttributeListID,
    ZGMTRClusterWiFiNetworkDiagnosticsAttributeFeatureMapID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterWiFiNetworkDiagnosticsAttributeFeatureMapID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = ZGMTRClusterGlobalAttributeFeatureMapID,
    ZGMTRClusterWiFiNetworkDiagnosticsAttributeClusterRevisionID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterWiFiNetworkDiagnosticsAttributeClusterRevisionID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = ZGMTRClusterGlobalAttributeClusterRevisionID,

    // Cluster WiFiNetworkDiagnostics attributes
    ZGMTRAttributeIDTypeClusterWiFiNetworkDiagnosticsAttributeBSSIDID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000000,
    ZGMTRAttributeIDTypeClusterWiFiNetworkDiagnosticsAttributeSecurityTypeID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000001,
    ZGMTRAttributeIDTypeClusterWiFiNetworkDiagnosticsAttributeWiFiVersionID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000002,
    ZGMTRAttributeIDTypeClusterWiFiNetworkDiagnosticsAttributeChannelNumberID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000003,
    ZGMTRAttributeIDTypeClusterWiFiNetworkDiagnosticsAttributeRSSIID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000004,
    ZGMTRAttributeIDTypeClusterWiFiNetworkDiagnosticsAttributeBeaconLostCountID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000005,
    ZGMTRAttributeIDTypeClusterWiFiNetworkDiagnosticsAttributeBeaconRxCountID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000006,
    ZGMTRAttributeIDTypeClusterWiFiNetworkDiagnosticsAttributePacketMulticastRxCountID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000007,
    ZGMTRAttributeIDTypeClusterWiFiNetworkDiagnosticsAttributePacketMulticastTxCountID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000008,
    ZGMTRAttributeIDTypeClusterWiFiNetworkDiagnosticsAttributePacketUnicastRxCountID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000009,
    ZGMTRAttributeIDTypeClusterWiFiNetworkDiagnosticsAttributePacketUnicastTxCountID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x0000000A,
    ZGMTRAttributeIDTypeClusterWiFiNetworkDiagnosticsAttributeCurrentMaxRateID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x0000000B,
    ZGMTRAttributeIDTypeClusterWiFiNetworkDiagnosticsAttributeOverrunCountID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x0000000C,
    ZGMTRAttributeIDTypeClusterWiFiNetworkDiagnosticsAttributeGeneratedCommandListID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = ZGMTRAttributeIDTypeGlobalAttributeGeneratedCommandListID,
    ZGMTRAttributeIDTypeClusterWiFiNetworkDiagnosticsAttributeAcceptedCommandListID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = ZGMTRAttributeIDTypeGlobalAttributeAcceptedCommandListID,
    ZGMTRAttributeIDTypeClusterWiFiNetworkDiagnosticsAttributeAttributeListID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = ZGMTRAttributeIDTypeGlobalAttributeAttributeListID,
    ZGMTRAttributeIDTypeClusterWiFiNetworkDiagnosticsAttributeFeatureMapID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = ZGMTRAttributeIDTypeGlobalAttributeFeatureMapID,
    ZGMTRAttributeIDTypeClusterWiFiNetworkDiagnosticsAttributeClusterRevisionID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = ZGMTRAttributeIDTypeGlobalAttributeClusterRevisionID,

    // Cluster EthernetNetworkDiagnostics deprecated attribute names
    ZGMTRClusterEthernetNetworkDiagnosticsAttributePHYRateID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterEthernetNetworkDiagnosticsAttributePHYRateID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000000,
    ZGMTRClusterEthernetNetworkDiagnosticsAttributeFullDuplexID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterEthernetNetworkDiagnosticsAttributeFullDuplexID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000001,
    ZGMTRClusterEthernetNetworkDiagnosticsAttributePacketRxCountID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterEthernetNetworkDiagnosticsAttributePacketRxCountID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000002,
    ZGMTRClusterEthernetNetworkDiagnosticsAttributePacketTxCountID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterEthernetNetworkDiagnosticsAttributePacketTxCountID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000003,
    ZGMTRClusterEthernetNetworkDiagnosticsAttributeTxErrCountID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterEthernetNetworkDiagnosticsAttributeTxErrCountID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000004,
    ZGMTRClusterEthernetNetworkDiagnosticsAttributeCollisionCountID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterEthernetNetworkDiagnosticsAttributeCollisionCountID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000005,
    ZGMTRClusterEthernetNetworkDiagnosticsAttributeOverrunCountID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterEthernetNetworkDiagnosticsAttributeOverrunCountID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000006,
    ZGMTRClusterEthernetNetworkDiagnosticsAttributeCarrierDetectID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterEthernetNetworkDiagnosticsAttributeCarrierDetectID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000007,
    ZGMTRClusterEthernetNetworkDiagnosticsAttributeTimeSinceResetID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterEthernetNetworkDiagnosticsAttributeTimeSinceResetID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000008,
    ZGMTRClusterEthernetNetworkDiagnosticsAttributeGeneratedCommandListID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterEthernetNetworkDiagnosticsAttributeGeneratedCommandListID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = ZGMTRClusterGlobalAttributeGeneratedCommandListID,
    ZGMTRClusterEthernetNetworkDiagnosticsAttributeAcceptedCommandListID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterEthernetNetworkDiagnosticsAttributeAcceptedCommandListID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = ZGMTRClusterGlobalAttributeAcceptedCommandListID,
    ZGMTRClusterEthernetNetworkDiagnosticsAttributeAttributeListID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterEthernetNetworkDiagnosticsAttributeAttributeListID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = ZGMTRClusterGlobalAttributeAttributeListID,
    ZGMTRClusterEthernetNetworkDiagnosticsAttributeFeatureMapID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterEthernetNetworkDiagnosticsAttributeFeatureMapID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = ZGMTRClusterGlobalAttributeFeatureMapID,
    ZGMTRClusterEthernetNetworkDiagnosticsAttributeClusterRevisionID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterEthernetNetworkDiagnosticsAttributeClusterRevisionID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = ZGMTRClusterGlobalAttributeClusterRevisionID,

    // Cluster EthernetNetworkDiagnostics attributes
    ZGMTRAttributeIDTypeClusterEthernetNetworkDiagnosticsAttributePHYRateID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000000,
    ZGMTRAttributeIDTypeClusterEthernetNetworkDiagnosticsAttributeFullDuplexID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000001,
    ZGMTRAttributeIDTypeClusterEthernetNetworkDiagnosticsAttributePacketRxCountID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000002,
    ZGMTRAttributeIDTypeClusterEthernetNetworkDiagnosticsAttributePacketTxCountID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000003,
    ZGMTRAttributeIDTypeClusterEthernetNetworkDiagnosticsAttributeTxErrCountID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000004,
    ZGMTRAttributeIDTypeClusterEthernetNetworkDiagnosticsAttributeCollisionCountID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000005,
    ZGMTRAttributeIDTypeClusterEthernetNetworkDiagnosticsAttributeOverrunCountID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000006,
    ZGMTRAttributeIDTypeClusterEthernetNetworkDiagnosticsAttributeCarrierDetectID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000007,
    ZGMTRAttributeIDTypeClusterEthernetNetworkDiagnosticsAttributeTimeSinceResetID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000008,
    ZGMTRAttributeIDTypeClusterEthernetNetworkDiagnosticsAttributeGeneratedCommandListID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = ZGMTRAttributeIDTypeGlobalAttributeGeneratedCommandListID,
    ZGMTRAttributeIDTypeClusterEthernetNetworkDiagnosticsAttributeAcceptedCommandListID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = ZGMTRAttributeIDTypeGlobalAttributeAcceptedCommandListID,
    ZGMTRAttributeIDTypeClusterEthernetNetworkDiagnosticsAttributeAttributeListID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = ZGMTRAttributeIDTypeGlobalAttributeAttributeListID,
    ZGMTRAttributeIDTypeClusterEthernetNetworkDiagnosticsAttributeFeatureMapID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = ZGMTRAttributeIDTypeGlobalAttributeFeatureMapID,
    ZGMTRAttributeIDTypeClusterEthernetNetworkDiagnosticsAttributeClusterRevisionID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = ZGMTRAttributeIDTypeGlobalAttributeClusterRevisionID,

    // Cluster TimeSynchronization deprecated attribute names
    ZGMTRClusterTimeSynchronizationAttributeUTCTimeID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterTimeSynchronizationAttributeUTCTimeID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000000,
    ZGMTRClusterTimeSynchronizationAttributeGranularityID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterTimeSynchronizationAttributeGranularityID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000001,
    ZGMTRClusterTimeSynchronizationAttributeTimeSourceID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterTimeSynchronizationAttributeTimeSourceID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000002,
    ZGMTRClusterTimeSynchronizationAttributeTrustedTimeNodeIdID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterTimeSynchronizationAttributeTrustedTimeSourceID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000003,
    ZGMTRClusterTimeSynchronizationAttributeDefaultNtpID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterTimeSynchronizationAttributeDefaultNTPID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000004,
    ZGMTRClusterTimeSynchronizationAttributeTimeZoneID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterTimeSynchronizationAttributeTimeZoneID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000005,
    ZGMTRClusterTimeSynchronizationAttributeDstOffsetID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterTimeSynchronizationAttributeDSTOffsetID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000006,
    ZGMTRClusterTimeSynchronizationAttributeLocalTimeID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterTimeSynchronizationAttributeLocalTimeID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000007,
    ZGMTRClusterTimeSynchronizationAttributeTimeZoneDatabaseID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterTimeSynchronizationAttributeTimeZoneDatabaseID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000008,
    ZGMTRClusterTimeSynchronizationAttributeNtpServerPortID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterTimeSynchronizationAttributeNTPServerAvailableID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000009,
    ZGMTRClusterTimeSynchronizationAttributeGeneratedCommandListID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterTimeSynchronizationAttributeGeneratedCommandListID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = ZGMTRClusterGlobalAttributeGeneratedCommandListID,
    ZGMTRClusterTimeSynchronizationAttributeAcceptedCommandListID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterTimeSynchronizationAttributeAcceptedCommandListID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = ZGMTRClusterGlobalAttributeAcceptedCommandListID,
    ZGMTRClusterTimeSynchronizationAttributeAttributeListID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterTimeSynchronizationAttributeAttributeListID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = ZGMTRClusterGlobalAttributeAttributeListID,
    ZGMTRClusterTimeSynchronizationAttributeFeatureMapID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterTimeSynchronizationAttributeFeatureMapID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = ZGMTRClusterGlobalAttributeFeatureMapID,
    ZGMTRClusterTimeSynchronizationAttributeClusterRevisionID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterTimeSynchronizationAttributeClusterRevisionID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = ZGMTRClusterGlobalAttributeClusterRevisionID,

    // Cluster TimeSynchronization attributes
    ZGMTRAttributeIDTypeClusterTimeSynchronizationAttributeUTCTimeID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000000,
    ZGMTRAttributeIDTypeClusterTimeSynchronizationAttributeGranularityID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000001,
    ZGMTRAttributeIDTypeClusterTimeSynchronizationAttributeTimeSourceID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000002,
    ZGMTRAttributeIDTypeClusterTimeSynchronizationAttributeTrustedTimeSourceID ZGMTR_AVAILABLE(ios(17.0), macos(14.0), watchos(10.0), tvos(17.0)) = 0x00000003,
    ZGMTRAttributeIDTypeClusterTimeSynchronizationAttributeTrustedTimeNodeIdID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = ZGMTRAttributeIDTypeClusterTimeSynchronizationAttributeTrustedTimeSourceID,
    ZGMTRAttributeIDTypeClusterTimeSynchronizationAttributeDefaultNTPID ZGMTR_AVAILABLE(ios(17.0), macos(14.0), watchos(10.0), tvos(17.0)) = 0x00000004,
    ZGMTRAttributeIDTypeClusterTimeSynchronizationAttributeDefaultNtpID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = ZGMTRAttributeIDTypeClusterTimeSynchronizationAttributeDefaultNTPID,
    ZGMTRAttributeIDTypeClusterTimeSynchronizationAttributeTimeZoneID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000005,
    ZGMTRAttributeIDTypeClusterTimeSynchronizationAttributeDSTOffsetID ZGMTR_AVAILABLE(ios(16.5), macos(13.4), watchos(9.5), tvos(16.5)) = 0x00000006,
    ZGMTRAttributeIDTypeClusterTimeSynchronizationAttributeDstOffsetID ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeTimeSynchronizationAttributeDSTOffsetID", ios(16.4, 16.5), macos(13.3, 13.4), watchos(9.4, 9.5), tvos(16.4, 16.5)) = ZGMTRAttributeIDTypeClusterTimeSynchronizationAttributeDSTOffsetID,
    ZGMTRAttributeIDTypeClusterTimeSynchronizationAttributeLocalTimeID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000007,
    ZGMTRAttributeIDTypeClusterTimeSynchronizationAttributeTimeZoneDatabaseID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000008,
    ZGMTRAttributeIDTypeClusterTimeSynchronizationAttributeNTPServerAvailableID ZGMTR_AVAILABLE(ios(17.0), macos(14.0), watchos(10.0), tvos(17.0)) = 0x00000009,
    ZGMTRAttributeIDTypeClusterTimeSynchronizationAttributeNtpServerPortID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = ZGMTRAttributeIDTypeClusterTimeSynchronizationAttributeNTPServerAvailableID,
    ZGMTRAttributeIDTypeClusterTimeSynchronizationAttributeTimeZoneListMaxSizeID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = 0x0000000A,
    ZGMTRAttributeIDTypeClusterTimeSynchronizationAttributeDSTOffsetListMaxSizeID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = 0x0000000B,
    ZGMTRAttributeIDTypeClusterTimeSynchronizationAttributeSupportsDNSResolveID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = 0x0000000C,
    ZGMTRAttributeIDTypeClusterTimeSynchronizationAttributeGeneratedCommandListID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = ZGMTRAttributeIDTypeGlobalAttributeGeneratedCommandListID,
    ZGMTRAttributeIDTypeClusterTimeSynchronizationAttributeAcceptedCommandListID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = ZGMTRAttributeIDTypeGlobalAttributeAcceptedCommandListID,
    ZGMTRAttributeIDTypeClusterTimeSynchronizationAttributeAttributeListID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = ZGMTRAttributeIDTypeGlobalAttributeAttributeListID,
    ZGMTRAttributeIDTypeClusterTimeSynchronizationAttributeFeatureMapID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = ZGMTRAttributeIDTypeGlobalAttributeFeatureMapID,
    ZGMTRAttributeIDTypeClusterTimeSynchronizationAttributeClusterRevisionID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = ZGMTRAttributeIDTypeGlobalAttributeClusterRevisionID,

    // Cluster BridgedDeviceBasic deprecated attribute names
    ZGMTRClusterBridgedDeviceBasicAttributeVendorNameID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterBridgedDeviceBasicInformationAttributeVendorNameID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000001,
    ZGMTRClusterBridgedDeviceBasicAttributeVendorIDID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterBridgedDeviceBasicInformationAttributeVendorIDID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000002,
    ZGMTRClusterBridgedDeviceBasicAttributeProductNameID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterBridgedDeviceBasicInformationAttributeProductNameID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000003,
    ZGMTRClusterBridgedDeviceBasicAttributeNodeLabelID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterBridgedDeviceBasicInformationAttributeNodeLabelID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000005,
    ZGMTRClusterBridgedDeviceBasicAttributeHardwareVersionID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterBridgedDeviceBasicInformationAttributeHardwareVersionID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000007,
    ZGMTRClusterBridgedDeviceBasicAttributeHardwareVersionStringID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterBridgedDeviceBasicInformationAttributeHardwareVersionStringID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000008,
    ZGMTRClusterBridgedDeviceBasicAttributeSoftwareVersionID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterBridgedDeviceBasicInformationAttributeSoftwareVersionID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000009,
    ZGMTRClusterBridgedDeviceBasicAttributeSoftwareVersionStringID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterBridgedDeviceBasicInformationAttributeSoftwareVersionStringID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x0000000A,
    ZGMTRClusterBridgedDeviceBasicAttributeManufacturingDateID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterBridgedDeviceBasicInformationAttributeManufacturingDateID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x0000000B,
    ZGMTRClusterBridgedDeviceBasicAttributePartNumberID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterBridgedDeviceBasicInformationAttributePartNumberID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x0000000C,
    ZGMTRClusterBridgedDeviceBasicAttributeProductURLID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterBridgedDeviceBasicInformationAttributeProductURLID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x0000000D,
    ZGMTRClusterBridgedDeviceBasicAttributeProductLabelID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterBridgedDeviceBasicInformationAttributeProductLabelID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x0000000E,
    ZGMTRClusterBridgedDeviceBasicAttributeSerialNumberID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterBridgedDeviceBasicInformationAttributeSerialNumberID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x0000000F,
    ZGMTRClusterBridgedDeviceBasicAttributeReachableID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterBridgedDeviceBasicInformationAttributeReachableID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000011,
    ZGMTRClusterBridgedDeviceBasicAttributeUniqueIDID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterBridgedDeviceBasicInformationAttributeUniqueIDID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000012,
    ZGMTRClusterBridgedDeviceBasicAttributeGeneratedCommandListID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterBridgedDeviceBasicInformationAttributeGeneratedCommandListID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = ZGMTRClusterGlobalAttributeGeneratedCommandListID,
    ZGMTRClusterBridgedDeviceBasicAttributeAcceptedCommandListID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterBridgedDeviceBasicInformationAttributeAcceptedCommandListID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = ZGMTRClusterGlobalAttributeAcceptedCommandListID,
    ZGMTRClusterBridgedDeviceBasicAttributeAttributeListID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterBridgedDeviceBasicInformationAttributeAttributeListID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = ZGMTRClusterGlobalAttributeAttributeListID,
    ZGMTRClusterBridgedDeviceBasicAttributeFeatureMapID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterBridgedDeviceBasicInformationAttributeFeatureMapID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = ZGMTRClusterGlobalAttributeFeatureMapID,
    ZGMTRClusterBridgedDeviceBasicAttributeClusterRevisionID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterBridgedDeviceBasicInformationAttributeClusterRevisionID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = ZGMTRClusterGlobalAttributeClusterRevisionID,

    // Cluster BridgedDeviceBasicInformation attributes
    ZGMTRAttributeIDTypeClusterBridgedDeviceBasicInformationAttributeVendorNameID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000001,
    ZGMTRAttributeIDTypeClusterBridgedDeviceBasicInformationAttributeVendorIDID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000002,
    ZGMTRAttributeIDTypeClusterBridgedDeviceBasicInformationAttributeProductNameID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000003,
    ZGMTRAttributeIDTypeClusterBridgedDeviceBasicInformationAttributeProductIDID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = 0x00000004,
    ZGMTRAttributeIDTypeClusterBridgedDeviceBasicInformationAttributeNodeLabelID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000005,
    ZGMTRAttributeIDTypeClusterBridgedDeviceBasicInformationAttributeHardwareVersionID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000007,
    ZGMTRAttributeIDTypeClusterBridgedDeviceBasicInformationAttributeHardwareVersionStringID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000008,
    ZGMTRAttributeIDTypeClusterBridgedDeviceBasicInformationAttributeSoftwareVersionID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000009,
    ZGMTRAttributeIDTypeClusterBridgedDeviceBasicInformationAttributeSoftwareVersionStringID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x0000000A,
    ZGMTRAttributeIDTypeClusterBridgedDeviceBasicInformationAttributeManufacturingDateID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x0000000B,
    ZGMTRAttributeIDTypeClusterBridgedDeviceBasicInformationAttributePartNumberID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x0000000C,
    ZGMTRAttributeIDTypeClusterBridgedDeviceBasicInformationAttributeProductURLID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x0000000D,
    ZGMTRAttributeIDTypeClusterBridgedDeviceBasicInformationAttributeProductLabelID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x0000000E,
    ZGMTRAttributeIDTypeClusterBridgedDeviceBasicInformationAttributeSerialNumberID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x0000000F,
    ZGMTRAttributeIDTypeClusterBridgedDeviceBasicInformationAttributeReachableID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000011,
    ZGMTRAttributeIDTypeClusterBridgedDeviceBasicInformationAttributeUniqueIDID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000012,
    ZGMTRAttributeIDTypeClusterBridgedDeviceBasicInformationAttributeProductAppearanceID ZGMTR_AVAILABLE(ios(17.0), macos(14.0), watchos(10.0), tvos(17.0)) = 0x00000014,
    ZGMTRAttributeIDTypeClusterBridgedDeviceBasicInformationAttributeDeviceLocationID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000017,
    ZGMTRAttributeIDTypeClusterBridgedDeviceBasicInformationAttributeConfigurationVersionID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000018,
    ZGMTRAttributeIDTypeClusterBridgedDeviceBasicInformationAttributeGeneratedCommandListID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = ZGMTRAttributeIDTypeGlobalAttributeGeneratedCommandListID,
    ZGMTRAttributeIDTypeClusterBridgedDeviceBasicInformationAttributeAcceptedCommandListID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = ZGMTRAttributeIDTypeGlobalAttributeAcceptedCommandListID,
    ZGMTRAttributeIDTypeClusterBridgedDeviceBasicInformationAttributeAttributeListID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = ZGMTRAttributeIDTypeGlobalAttributeAttributeListID,
    ZGMTRAttributeIDTypeClusterBridgedDeviceBasicInformationAttributeFeatureMapID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = ZGMTRAttributeIDTypeGlobalAttributeFeatureMapID,
    ZGMTRAttributeIDTypeClusterBridgedDeviceBasicInformationAttributeClusterRevisionID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = ZGMTRAttributeIDTypeGlobalAttributeClusterRevisionID,

    // Cluster Switch deprecated attribute names
    ZGMTRClusterSwitchAttributeNumberOfPositionsID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterSwitchAttributeNumberOfPositionsID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000000,
    ZGMTRClusterSwitchAttributeCurrentPositionID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterSwitchAttributeCurrentPositionID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000001,
    ZGMTRClusterSwitchAttributeMultiPressMaxID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterSwitchAttributeMultiPressMaxID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000002,
    ZGMTRClusterSwitchAttributeGeneratedCommandListID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterSwitchAttributeGeneratedCommandListID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = ZGMTRClusterGlobalAttributeGeneratedCommandListID,
    ZGMTRClusterSwitchAttributeAcceptedCommandListID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterSwitchAttributeAcceptedCommandListID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = ZGMTRClusterGlobalAttributeAcceptedCommandListID,
    ZGMTRClusterSwitchAttributeAttributeListID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterSwitchAttributeAttributeListID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = ZGMTRClusterGlobalAttributeAttributeListID,
    ZGMTRClusterSwitchAttributeFeatureMapID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterSwitchAttributeFeatureMapID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = ZGMTRClusterGlobalAttributeFeatureMapID,
    ZGMTRClusterSwitchAttributeClusterRevisionID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterSwitchAttributeClusterRevisionID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = ZGMTRClusterGlobalAttributeClusterRevisionID,

    // Cluster Switch attributes
    ZGMTRAttributeIDTypeClusterSwitchAttributeNumberOfPositionsID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000000,
    ZGMTRAttributeIDTypeClusterSwitchAttributeCurrentPositionID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000001,
    ZGMTRAttributeIDTypeClusterSwitchAttributeMultiPressMaxID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000002,
    ZGMTRAttributeIDTypeClusterSwitchAttributeGeneratedCommandListID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = ZGMTRAttributeIDTypeGlobalAttributeGeneratedCommandListID,
    ZGMTRAttributeIDTypeClusterSwitchAttributeAcceptedCommandListID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = ZGMTRAttributeIDTypeGlobalAttributeAcceptedCommandListID,
    ZGMTRAttributeIDTypeClusterSwitchAttributeAttributeListID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = ZGMTRAttributeIDTypeGlobalAttributeAttributeListID,
    ZGMTRAttributeIDTypeClusterSwitchAttributeFeatureMapID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = ZGMTRAttributeIDTypeGlobalAttributeFeatureMapID,
    ZGMTRAttributeIDTypeClusterSwitchAttributeClusterRevisionID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = ZGMTRAttributeIDTypeGlobalAttributeClusterRevisionID,

    // Cluster AdministratorCommissioning deprecated attribute names
    ZGMTRClusterAdministratorCommissioningAttributeWindowStatusID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterAdministratorCommissioningAttributeWindowStatusID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000000,
    ZGMTRClusterAdministratorCommissioningAttributeAdminFabricIndexID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterAdministratorCommissioningAttributeAdminFabricIndexID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000001,
    ZGMTRClusterAdministratorCommissioningAttributeAdminVendorIdID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterAdministratorCommissioningAttributeAdminVendorIdID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000002,
    ZGMTRClusterAdministratorCommissioningAttributeGeneratedCommandListID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterAdministratorCommissioningAttributeGeneratedCommandListID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = ZGMTRClusterGlobalAttributeGeneratedCommandListID,
    ZGMTRClusterAdministratorCommissioningAttributeAcceptedCommandListID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterAdministratorCommissioningAttributeAcceptedCommandListID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = ZGMTRClusterGlobalAttributeAcceptedCommandListID,
    ZGMTRClusterAdministratorCommissioningAttributeAttributeListID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterAdministratorCommissioningAttributeAttributeListID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = ZGMTRClusterGlobalAttributeAttributeListID,
    ZGMTRClusterAdministratorCommissioningAttributeFeatureMapID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterAdministratorCommissioningAttributeFeatureMapID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = ZGMTRClusterGlobalAttributeFeatureMapID,
    ZGMTRClusterAdministratorCommissioningAttributeClusterRevisionID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterAdministratorCommissioningAttributeClusterRevisionID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = ZGMTRClusterGlobalAttributeClusterRevisionID,

    // Cluster AdministratorCommissioning attributes
    ZGMTRAttributeIDTypeClusterAdministratorCommissioningAttributeWindowStatusID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000000,
    ZGMTRAttributeIDTypeClusterAdministratorCommissioningAttributeAdminFabricIndexID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000001,
    ZGMTRAttributeIDTypeClusterAdministratorCommissioningAttributeAdminVendorIdID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000002,
    ZGMTRAttributeIDTypeClusterAdministratorCommissioningAttributeGeneratedCommandListID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = ZGMTRAttributeIDTypeGlobalAttributeGeneratedCommandListID,
    ZGMTRAttributeIDTypeClusterAdministratorCommissioningAttributeAcceptedCommandListID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = ZGMTRAttributeIDTypeGlobalAttributeAcceptedCommandListID,
    ZGMTRAttributeIDTypeClusterAdministratorCommissioningAttributeAttributeListID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = ZGMTRAttributeIDTypeGlobalAttributeAttributeListID,
    ZGMTRAttributeIDTypeClusterAdministratorCommissioningAttributeFeatureMapID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = ZGMTRAttributeIDTypeGlobalAttributeFeatureMapID,
    ZGMTRAttributeIDTypeClusterAdministratorCommissioningAttributeClusterRevisionID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = ZGMTRAttributeIDTypeGlobalAttributeClusterRevisionID,

    // Cluster OperationalCredentials deprecated attribute names
    ZGMTRClusterOperationalCredentialsAttributeNOCsID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterOperationalCredentialsAttributeNOCsID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000000,
    ZGMTRClusterOperationalCredentialsAttributeFabricsID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterOperationalCredentialsAttributeFabricsID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000001,
    ZGMTRClusterOperationalCredentialsAttributeSupportedFabricsID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterOperationalCredentialsAttributeSupportedFabricsID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000002,
    ZGMTRClusterOperationalCredentialsAttributeCommissionedFabricsID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterOperationalCredentialsAttributeCommissionedFabricsID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000003,
    ZGMTRClusterOperationalCredentialsAttributeTrustedRootCertificatesID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterOperationalCredentialsAttributeTrustedRootCertificatesID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000004,
    ZGMTRClusterOperationalCredentialsAttributeCurrentFabricIndexID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterOperationalCredentialsAttributeCurrentFabricIndexID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000005,
    ZGMTRClusterOperationalCredentialsAttributeGeneratedCommandListID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterOperationalCredentialsAttributeGeneratedCommandListID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = ZGMTRClusterGlobalAttributeGeneratedCommandListID,
    ZGMTRClusterOperationalCredentialsAttributeAcceptedCommandListID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterOperationalCredentialsAttributeAcceptedCommandListID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = ZGMTRClusterGlobalAttributeAcceptedCommandListID,
    ZGMTRClusterOperationalCredentialsAttributeAttributeListID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterOperationalCredentialsAttributeAttributeListID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = ZGMTRClusterGlobalAttributeAttributeListID,
    ZGMTRClusterOperationalCredentialsAttributeFeatureMapID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterOperationalCredentialsAttributeFeatureMapID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = ZGMTRClusterGlobalAttributeFeatureMapID,
    ZGMTRClusterOperationalCredentialsAttributeClusterRevisionID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterOperationalCredentialsAttributeClusterRevisionID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = ZGMTRClusterGlobalAttributeClusterRevisionID,

    // Cluster OperationalCredentials attributes
    ZGMTRAttributeIDTypeClusterOperationalCredentialsAttributeNOCsID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000000,
    ZGMTRAttributeIDTypeClusterOperationalCredentialsAttributeFabricsID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000001,
    ZGMTRAttributeIDTypeClusterOperationalCredentialsAttributeSupportedFabricsID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000002,
    ZGMTRAttributeIDTypeClusterOperationalCredentialsAttributeCommissionedFabricsID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000003,
    ZGMTRAttributeIDTypeClusterOperationalCredentialsAttributeTrustedRootCertificatesID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000004,
    ZGMTRAttributeIDTypeClusterOperationalCredentialsAttributeCurrentFabricIndexID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000005,
    ZGMTRAttributeIDTypeClusterOperationalCredentialsAttributeGeneratedCommandListID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = ZGMTRAttributeIDTypeGlobalAttributeGeneratedCommandListID,
    ZGMTRAttributeIDTypeClusterOperationalCredentialsAttributeAcceptedCommandListID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = ZGMTRAttributeIDTypeGlobalAttributeAcceptedCommandListID,
    ZGMTRAttributeIDTypeClusterOperationalCredentialsAttributeAttributeListID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = ZGMTRAttributeIDTypeGlobalAttributeAttributeListID,
    ZGMTRAttributeIDTypeClusterOperationalCredentialsAttributeFeatureMapID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = ZGMTRAttributeIDTypeGlobalAttributeFeatureMapID,
    ZGMTRAttributeIDTypeClusterOperationalCredentialsAttributeClusterRevisionID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = ZGMTRAttributeIDTypeGlobalAttributeClusterRevisionID,

    // Cluster GroupKeyManagement deprecated attribute names
    ZGMTRClusterGroupKeyManagementAttributeGroupKeyMapID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterGroupKeyManagementAttributeGroupKeyMapID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000000,
    ZGMTRClusterGroupKeyManagementAttributeGroupTableID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterGroupKeyManagementAttributeGroupTableID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000001,
    ZGMTRClusterGroupKeyManagementAttributeMaxGroupsPerFabricID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterGroupKeyManagementAttributeMaxGroupsPerFabricID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000002,
    ZGMTRClusterGroupKeyManagementAttributeMaxGroupKeysPerFabricID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterGroupKeyManagementAttributeMaxGroupKeysPerFabricID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000003,
    ZGMTRClusterGroupKeyManagementAttributeGeneratedCommandListID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterGroupKeyManagementAttributeGeneratedCommandListID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = ZGMTRClusterGlobalAttributeGeneratedCommandListID,
    ZGMTRClusterGroupKeyManagementAttributeAcceptedCommandListID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterGroupKeyManagementAttributeAcceptedCommandListID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = ZGMTRClusterGlobalAttributeAcceptedCommandListID,
    ZGMTRClusterGroupKeyManagementAttributeAttributeListID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterGroupKeyManagementAttributeAttributeListID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = ZGMTRClusterGlobalAttributeAttributeListID,
    ZGMTRClusterGroupKeyManagementAttributeFeatureMapID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterGroupKeyManagementAttributeFeatureMapID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = ZGMTRClusterGlobalAttributeFeatureMapID,
    ZGMTRClusterGroupKeyManagementAttributeClusterRevisionID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterGroupKeyManagementAttributeClusterRevisionID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = ZGMTRClusterGlobalAttributeClusterRevisionID,

    // Cluster GroupKeyManagement attributes
    ZGMTRAttributeIDTypeClusterGroupKeyManagementAttributeGroupKeyMapID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000000,
    ZGMTRAttributeIDTypeClusterGroupKeyManagementAttributeGroupTableID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000001,
    ZGMTRAttributeIDTypeClusterGroupKeyManagementAttributeMaxGroupsPerFabricID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000002,
    ZGMTRAttributeIDTypeClusterGroupKeyManagementAttributeMaxGroupKeysPerFabricID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000003,
    ZGMTRAttributeIDTypeClusterGroupKeyManagementAttributeGroupcastAdoptionID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000004,
    ZGMTRAttributeIDTypeClusterGroupKeyManagementAttributeGeneratedCommandListID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = ZGMTRAttributeIDTypeGlobalAttributeGeneratedCommandListID,
    ZGMTRAttributeIDTypeClusterGroupKeyManagementAttributeAcceptedCommandListID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = ZGMTRAttributeIDTypeGlobalAttributeAcceptedCommandListID,
    ZGMTRAttributeIDTypeClusterGroupKeyManagementAttributeAttributeListID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = ZGMTRAttributeIDTypeGlobalAttributeAttributeListID,
    ZGMTRAttributeIDTypeClusterGroupKeyManagementAttributeFeatureMapID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = ZGMTRAttributeIDTypeGlobalAttributeFeatureMapID,
    ZGMTRAttributeIDTypeClusterGroupKeyManagementAttributeClusterRevisionID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = ZGMTRAttributeIDTypeGlobalAttributeClusterRevisionID,

    // Cluster FixedLabel deprecated attribute names
    ZGMTRClusterFixedLabelAttributeLabelListID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterFixedLabelAttributeLabelListID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000000,
    ZGMTRClusterFixedLabelAttributeGeneratedCommandListID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterFixedLabelAttributeGeneratedCommandListID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = ZGMTRClusterGlobalAttributeGeneratedCommandListID,
    ZGMTRClusterFixedLabelAttributeAcceptedCommandListID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterFixedLabelAttributeAcceptedCommandListID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = ZGMTRClusterGlobalAttributeAcceptedCommandListID,
    ZGMTRClusterFixedLabelAttributeAttributeListID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterFixedLabelAttributeAttributeListID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = ZGMTRClusterGlobalAttributeAttributeListID,
    ZGMTRClusterFixedLabelAttributeFeatureMapID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterFixedLabelAttributeFeatureMapID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = ZGMTRClusterGlobalAttributeFeatureMapID,
    ZGMTRClusterFixedLabelAttributeClusterRevisionID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterFixedLabelAttributeClusterRevisionID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = ZGMTRClusterGlobalAttributeClusterRevisionID,

    // Cluster FixedLabel attributes
    ZGMTRAttributeIDTypeClusterFixedLabelAttributeLabelListID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000000,
    ZGMTRAttributeIDTypeClusterFixedLabelAttributeGeneratedCommandListID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = ZGMTRAttributeIDTypeGlobalAttributeGeneratedCommandListID,
    ZGMTRAttributeIDTypeClusterFixedLabelAttributeAcceptedCommandListID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = ZGMTRAttributeIDTypeGlobalAttributeAcceptedCommandListID,
    ZGMTRAttributeIDTypeClusterFixedLabelAttributeAttributeListID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = ZGMTRAttributeIDTypeGlobalAttributeAttributeListID,
    ZGMTRAttributeIDTypeClusterFixedLabelAttributeFeatureMapID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = ZGMTRAttributeIDTypeGlobalAttributeFeatureMapID,
    ZGMTRAttributeIDTypeClusterFixedLabelAttributeClusterRevisionID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = ZGMTRAttributeIDTypeGlobalAttributeClusterRevisionID,

    // Cluster UserLabel deprecated attribute names
    ZGMTRClusterUserLabelAttributeLabelListID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterUserLabelAttributeLabelListID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000000,
    ZGMTRClusterUserLabelAttributeGeneratedCommandListID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterUserLabelAttributeGeneratedCommandListID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = ZGMTRClusterGlobalAttributeGeneratedCommandListID,
    ZGMTRClusterUserLabelAttributeAcceptedCommandListID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterUserLabelAttributeAcceptedCommandListID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = ZGMTRClusterGlobalAttributeAcceptedCommandListID,
    ZGMTRClusterUserLabelAttributeAttributeListID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterUserLabelAttributeAttributeListID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = ZGMTRClusterGlobalAttributeAttributeListID,
    ZGMTRClusterUserLabelAttributeFeatureMapID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterUserLabelAttributeFeatureMapID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = ZGMTRClusterGlobalAttributeFeatureMapID,
    ZGMTRClusterUserLabelAttributeClusterRevisionID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterUserLabelAttributeClusterRevisionID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = ZGMTRClusterGlobalAttributeClusterRevisionID,

    // Cluster UserLabel attributes
    ZGMTRAttributeIDTypeClusterUserLabelAttributeLabelListID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000000,
    ZGMTRAttributeIDTypeClusterUserLabelAttributeGeneratedCommandListID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = ZGMTRAttributeIDTypeGlobalAttributeGeneratedCommandListID,
    ZGMTRAttributeIDTypeClusterUserLabelAttributeAcceptedCommandListID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = ZGMTRAttributeIDTypeGlobalAttributeAcceptedCommandListID,
    ZGMTRAttributeIDTypeClusterUserLabelAttributeAttributeListID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = ZGMTRAttributeIDTypeGlobalAttributeAttributeListID,
    ZGMTRAttributeIDTypeClusterUserLabelAttributeFeatureMapID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = ZGMTRAttributeIDTypeGlobalAttributeFeatureMapID,
    ZGMTRAttributeIDTypeClusterUserLabelAttributeClusterRevisionID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = ZGMTRAttributeIDTypeGlobalAttributeClusterRevisionID,

    // Cluster BooleanState deprecated attribute names
    ZGMTRClusterBooleanStateAttributeStateValueID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterBooleanStateAttributeStateValueID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000000,
    ZGMTRClusterBooleanStateAttributeGeneratedCommandListID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterBooleanStateAttributeGeneratedCommandListID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = ZGMTRClusterGlobalAttributeGeneratedCommandListID,
    ZGMTRClusterBooleanStateAttributeAcceptedCommandListID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterBooleanStateAttributeAcceptedCommandListID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = ZGMTRClusterGlobalAttributeAcceptedCommandListID,
    ZGMTRClusterBooleanStateAttributeAttributeListID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterBooleanStateAttributeAttributeListID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = ZGMTRClusterGlobalAttributeAttributeListID,
    ZGMTRClusterBooleanStateAttributeFeatureMapID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterBooleanStateAttributeFeatureMapID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = ZGMTRClusterGlobalAttributeFeatureMapID,
    ZGMTRClusterBooleanStateAttributeClusterRevisionID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterBooleanStateAttributeClusterRevisionID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = ZGMTRClusterGlobalAttributeClusterRevisionID,

    // Cluster BooleanState attributes
    ZGMTRAttributeIDTypeClusterBooleanStateAttributeStateValueID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000000,
    ZGMTRAttributeIDTypeClusterBooleanStateAttributeGeneratedCommandListID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = ZGMTRAttributeIDTypeGlobalAttributeGeneratedCommandListID,
    ZGMTRAttributeIDTypeClusterBooleanStateAttributeAcceptedCommandListID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = ZGMTRAttributeIDTypeGlobalAttributeAcceptedCommandListID,
    ZGMTRAttributeIDTypeClusterBooleanStateAttributeAttributeListID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = ZGMTRAttributeIDTypeGlobalAttributeAttributeListID,
    ZGMTRAttributeIDTypeClusterBooleanStateAttributeFeatureMapID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = ZGMTRAttributeIDTypeGlobalAttributeFeatureMapID,
    ZGMTRAttributeIDTypeClusterBooleanStateAttributeClusterRevisionID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = ZGMTRAttributeIDTypeGlobalAttributeClusterRevisionID,

    // Cluster ICDManagement attributes
    ZGMTRAttributeIDTypeClusterICDManagementAttributeIdleModeDurationID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = 0x00000000,
    ZGMTRAttributeIDTypeClusterICDManagementAttributeActiveModeDurationID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = 0x00000001,
    ZGMTRAttributeIDTypeClusterICDManagementAttributeActiveModeThresholdID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = 0x00000002,
    ZGMTRAttributeIDTypeClusterICDManagementAttributeRegisteredClientsID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = 0x00000003,
    ZGMTRAttributeIDTypeClusterICDManagementAttributeICDCounterID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = 0x00000004,
    ZGMTRAttributeIDTypeClusterICDManagementAttributeClientsSupportedPerFabricID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = 0x00000005,
    ZGMTRAttributeIDTypeClusterICDManagementAttributeUserActiveModeTriggerHintID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = 0x00000006,
    ZGMTRAttributeIDTypeClusterICDManagementAttributeUserActiveModeTriggerInstructionID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = 0x00000007,
    ZGMTRAttributeIDTypeClusterICDManagementAttributeOperatingModeID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = 0x00000008,
    ZGMTRAttributeIDTypeClusterICDManagementAttributeMaximumCheckInBackOffID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = 0x00000009,
    ZGMTRAttributeIDTypeClusterICDManagementAttributeGeneratedCommandListID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = ZGMTRAttributeIDTypeGlobalAttributeGeneratedCommandListID,
    ZGMTRAttributeIDTypeClusterICDManagementAttributeAcceptedCommandListID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = ZGMTRAttributeIDTypeGlobalAttributeAcceptedCommandListID,
    ZGMTRAttributeIDTypeClusterICDManagementAttributeAttributeListID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = ZGMTRAttributeIDTypeGlobalAttributeAttributeListID,
    ZGMTRAttributeIDTypeClusterICDManagementAttributeFeatureMapID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = ZGMTRAttributeIDTypeGlobalAttributeFeatureMapID,
    ZGMTRAttributeIDTypeClusterICDManagementAttributeClusterRevisionID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = ZGMTRAttributeIDTypeGlobalAttributeClusterRevisionID,

    // Cluster OvenCavityOperationalState attributes
    ZGMTRAttributeIDTypeClusterOvenCavityOperationalStateAttributePhaseListID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = 0x00000000,
    ZGMTRAttributeIDTypeClusterOvenCavityOperationalStateAttributeCurrentPhaseID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = 0x00000001,
    ZGMTRAttributeIDTypeClusterOvenCavityOperationalStateAttributeCountdownTimeID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = 0x00000002,
    ZGMTRAttributeIDTypeClusterOvenCavityOperationalStateAttributeOperationalStateListID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = 0x00000003,
    ZGMTRAttributeIDTypeClusterOvenCavityOperationalStateAttributeOperationalStateID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = 0x00000004,
    ZGMTRAttributeIDTypeClusterOvenCavityOperationalStateAttributeOperationalErrorID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = 0x00000005,
    ZGMTRAttributeIDTypeClusterOvenCavityOperationalStateAttributeGeneratedCommandListID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = ZGMTRAttributeIDTypeGlobalAttributeGeneratedCommandListID,
    ZGMTRAttributeIDTypeClusterOvenCavityOperationalStateAttributeAcceptedCommandListID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = ZGMTRAttributeIDTypeGlobalAttributeAcceptedCommandListID,
    ZGMTRAttributeIDTypeClusterOvenCavityOperationalStateAttributeAttributeListID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = ZGMTRAttributeIDTypeGlobalAttributeAttributeListID,
    ZGMTRAttributeIDTypeClusterOvenCavityOperationalStateAttributeFeatureMapID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = ZGMTRAttributeIDTypeGlobalAttributeFeatureMapID,
    ZGMTRAttributeIDTypeClusterOvenCavityOperationalStateAttributeClusterRevisionID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = ZGMTRAttributeIDTypeGlobalAttributeClusterRevisionID,

    // Cluster OvenMode attributes
    ZGMTRAttributeIDTypeClusterOvenModeAttributeSupportedModesID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = 0x00000000,
    ZGMTRAttributeIDTypeClusterOvenModeAttributeCurrentModeID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = 0x00000001,
    ZGMTRAttributeIDTypeClusterOvenModeAttributeGeneratedCommandListID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = ZGMTRAttributeIDTypeGlobalAttributeGeneratedCommandListID,
    ZGMTRAttributeIDTypeClusterOvenModeAttributeAcceptedCommandListID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = ZGMTRAttributeIDTypeGlobalAttributeAcceptedCommandListID,
    ZGMTRAttributeIDTypeClusterOvenModeAttributeAttributeListID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = ZGMTRAttributeIDTypeGlobalAttributeAttributeListID,
    ZGMTRAttributeIDTypeClusterOvenModeAttributeFeatureMapID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = ZGMTRAttributeIDTypeGlobalAttributeFeatureMapID,
    ZGMTRAttributeIDTypeClusterOvenModeAttributeClusterRevisionID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = ZGMTRAttributeIDTypeGlobalAttributeClusterRevisionID,

    // Cluster LaundryDryerControls attributes
    ZGMTRAttributeIDTypeClusterLaundryDryerControlsAttributeSupportedDrynessLevelsID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = 0x00000000,
    ZGMTRAttributeIDTypeClusterLaundryDryerControlsAttributeSelectedDrynessLevelID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = 0x00000001,
    ZGMTRAttributeIDTypeClusterLaundryDryerControlsAttributeGeneratedCommandListID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = ZGMTRAttributeIDTypeGlobalAttributeGeneratedCommandListID,
    ZGMTRAttributeIDTypeClusterLaundryDryerControlsAttributeAcceptedCommandListID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = ZGMTRAttributeIDTypeGlobalAttributeAcceptedCommandListID,
    ZGMTRAttributeIDTypeClusterLaundryDryerControlsAttributeAttributeListID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = ZGMTRAttributeIDTypeGlobalAttributeAttributeListID,
    ZGMTRAttributeIDTypeClusterLaundryDryerControlsAttributeFeatureMapID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = ZGMTRAttributeIDTypeGlobalAttributeFeatureMapID,
    ZGMTRAttributeIDTypeClusterLaundryDryerControlsAttributeClusterRevisionID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = ZGMTRAttributeIDTypeGlobalAttributeClusterRevisionID,

    // Cluster TemperatureControlledCabinetTopology attributes
    ZGMTRAttributeIDTypeClusterTemperatureControlledCabinetTopologyAttributeDisabledCabinetsID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000000,
    ZGMTRAttributeIDTypeClusterTemperatureControlledCabinetTopologyAttributeTopologyID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000001,
    ZGMTRAttributeIDTypeClusterTemperatureControlledCabinetTopologyAttributeGeneratedCommandListID ZGMTR_PROVISIONALLY_AVAILABLE = ZGMTRAttributeIDTypeGlobalAttributeGeneratedCommandListID,
    ZGMTRAttributeIDTypeClusterTemperatureControlledCabinetTopologyAttributeAcceptedCommandListID ZGMTR_PROVISIONALLY_AVAILABLE = ZGMTRAttributeIDTypeGlobalAttributeAcceptedCommandListID,
    ZGMTRAttributeIDTypeClusterTemperatureControlledCabinetTopologyAttributeAttributeListID ZGMTR_PROVISIONALLY_AVAILABLE = ZGMTRAttributeIDTypeGlobalAttributeAttributeListID,
    ZGMTRAttributeIDTypeClusterTemperatureControlledCabinetTopologyAttributeFeatureMapID ZGMTR_PROVISIONALLY_AVAILABLE = ZGMTRAttributeIDTypeGlobalAttributeFeatureMapID,
    ZGMTRAttributeIDTypeClusterTemperatureControlledCabinetTopologyAttributeClusterRevisionID ZGMTR_PROVISIONALLY_AVAILABLE = ZGMTRAttributeIDTypeGlobalAttributeClusterRevisionID,

    // Cluster ModeSelect deprecated attribute names
    ZGMTRClusterModeSelectAttributeDescriptionID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterModeSelectAttributeDescriptionID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000000,
    ZGMTRClusterModeSelectAttributeStandardNamespaceID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterModeSelectAttributeStandardNamespaceID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000001,
    ZGMTRClusterModeSelectAttributeSupportedModesID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterModeSelectAttributeSupportedModesID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000002,
    ZGMTRClusterModeSelectAttributeCurrentModeID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterModeSelectAttributeCurrentModeID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000003,
    ZGMTRClusterModeSelectAttributeStartUpModeID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterModeSelectAttributeStartUpModeID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000004,
    ZGMTRClusterModeSelectAttributeOnModeID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterModeSelectAttributeOnModeID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000005,
    ZGMTRClusterModeSelectAttributeGeneratedCommandListID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterModeSelectAttributeGeneratedCommandListID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = ZGMTRClusterGlobalAttributeGeneratedCommandListID,
    ZGMTRClusterModeSelectAttributeAcceptedCommandListID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterModeSelectAttributeAcceptedCommandListID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = ZGMTRClusterGlobalAttributeAcceptedCommandListID,
    ZGMTRClusterModeSelectAttributeAttributeListID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterModeSelectAttributeAttributeListID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = ZGMTRClusterGlobalAttributeAttributeListID,
    ZGMTRClusterModeSelectAttributeFeatureMapID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterModeSelectAttributeFeatureMapID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = ZGMTRClusterGlobalAttributeFeatureMapID,
    ZGMTRClusterModeSelectAttributeClusterRevisionID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterModeSelectAttributeClusterRevisionID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = ZGMTRClusterGlobalAttributeClusterRevisionID,

    // Cluster ModeSelect attributes
    ZGMTRAttributeIDTypeClusterModeSelectAttributeDescriptionID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000000,
    ZGMTRAttributeIDTypeClusterModeSelectAttributeStandardNamespaceID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000001,
    ZGMTRAttributeIDTypeClusterModeSelectAttributeSupportedModesID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000002,
    ZGMTRAttributeIDTypeClusterModeSelectAttributeCurrentModeID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000003,
    ZGMTRAttributeIDTypeClusterModeSelectAttributeStartUpModeID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000004,
    ZGMTRAttributeIDTypeClusterModeSelectAttributeOnModeID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000005,
    ZGMTRAttributeIDTypeClusterModeSelectAttributeGeneratedCommandListID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = ZGMTRAttributeIDTypeGlobalAttributeGeneratedCommandListID,
    ZGMTRAttributeIDTypeClusterModeSelectAttributeAcceptedCommandListID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = ZGMTRAttributeIDTypeGlobalAttributeAcceptedCommandListID,
    ZGMTRAttributeIDTypeClusterModeSelectAttributeAttributeListID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = ZGMTRAttributeIDTypeGlobalAttributeAttributeListID,
    ZGMTRAttributeIDTypeClusterModeSelectAttributeFeatureMapID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = ZGMTRAttributeIDTypeGlobalAttributeFeatureMapID,
    ZGMTRAttributeIDTypeClusterModeSelectAttributeClusterRevisionID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = ZGMTRAttributeIDTypeGlobalAttributeClusterRevisionID,

    // Cluster LaundryWasherMode attributes
    ZGMTRAttributeIDTypeClusterLaundryWasherModeAttributeSupportedModesID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = 0x00000000,
    ZGMTRAttributeIDTypeClusterLaundryWasherModeAttributeCurrentModeID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = 0x00000001,
    ZGMTRAttributeIDTypeClusterLaundryWasherModeAttributeGeneratedCommandListID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = ZGMTRAttributeIDTypeGlobalAttributeGeneratedCommandListID,
    ZGMTRAttributeIDTypeClusterLaundryWasherModeAttributeAcceptedCommandListID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = ZGMTRAttributeIDTypeGlobalAttributeAcceptedCommandListID,
    ZGMTRAttributeIDTypeClusterLaundryWasherModeAttributeAttributeListID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = ZGMTRAttributeIDTypeGlobalAttributeAttributeListID,
    ZGMTRAttributeIDTypeClusterLaundryWasherModeAttributeFeatureMapID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = ZGMTRAttributeIDTypeGlobalAttributeFeatureMapID,
    ZGMTRAttributeIDTypeClusterLaundryWasherModeAttributeClusterRevisionID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = ZGMTRAttributeIDTypeGlobalAttributeClusterRevisionID,

    // Cluster RefrigeratorAndTemperatureControlledCabinetMode attributes
    ZGMTRAttributeIDTypeClusterRefrigeratorAndTemperatureControlledCabinetModeAttributeSupportedModesID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = 0x00000000,
    ZGMTRAttributeIDTypeClusterRefrigeratorAndTemperatureControlledCabinetModeAttributeCurrentModeID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = 0x00000001,
    ZGMTRAttributeIDTypeClusterRefrigeratorAndTemperatureControlledCabinetModeAttributeGeneratedCommandListID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = ZGMTRAttributeIDTypeGlobalAttributeGeneratedCommandListID,
    ZGMTRAttributeIDTypeClusterRefrigeratorAndTemperatureControlledCabinetModeAttributeAcceptedCommandListID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = ZGMTRAttributeIDTypeGlobalAttributeAcceptedCommandListID,
    ZGMTRAttributeIDTypeClusterRefrigeratorAndTemperatureControlledCabinetModeAttributeAttributeListID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = ZGMTRAttributeIDTypeGlobalAttributeAttributeListID,
    ZGMTRAttributeIDTypeClusterRefrigeratorAndTemperatureControlledCabinetModeAttributeFeatureMapID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = ZGMTRAttributeIDTypeGlobalAttributeFeatureMapID,
    ZGMTRAttributeIDTypeClusterRefrigeratorAndTemperatureControlledCabinetModeAttributeClusterRevisionID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = ZGMTRAttributeIDTypeGlobalAttributeClusterRevisionID,

    // Cluster LaundryWasherControls attributes
    ZGMTRAttributeIDTypeClusterLaundryWasherControlsAttributeSpinSpeedsID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = 0x00000000,
    ZGMTRAttributeIDTypeClusterLaundryWasherControlsAttributeSpinSpeedCurrentID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = 0x00000001,
    ZGMTRAttributeIDTypeClusterLaundryWasherControlsAttributeNumberOfRinsesID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = 0x00000002,
    ZGMTRAttributeIDTypeClusterLaundryWasherControlsAttributeSupportedRinsesID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = 0x00000003,
    ZGMTRAttributeIDTypeClusterLaundryWasherControlsAttributeGeneratedCommandListID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = ZGMTRAttributeIDTypeGlobalAttributeGeneratedCommandListID,
    ZGMTRAttributeIDTypeClusterLaundryWasherControlsAttributeAcceptedCommandListID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = ZGMTRAttributeIDTypeGlobalAttributeAcceptedCommandListID,
    ZGMTRAttributeIDTypeClusterLaundryWasherControlsAttributeAttributeListID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = ZGMTRAttributeIDTypeGlobalAttributeAttributeListID,
    ZGMTRAttributeIDTypeClusterLaundryWasherControlsAttributeFeatureMapID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = ZGMTRAttributeIDTypeGlobalAttributeFeatureMapID,
    ZGMTRAttributeIDTypeClusterLaundryWasherControlsAttributeClusterRevisionID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = ZGMTRAttributeIDTypeGlobalAttributeClusterRevisionID,

    // Cluster RVCRunMode attributes
    ZGMTRAttributeIDTypeClusterRVCRunModeAttributeSupportedModesID ZGMTR_AVAILABLE(ios(17.4), macos(14.4), watchos(10.4), tvos(17.4)) = 0x00000000,
    ZGMTRAttributeIDTypeClusterRVCRunModeAttributeCurrentModeID ZGMTR_AVAILABLE(ios(17.4), macos(14.4), watchos(10.4), tvos(17.4)) = 0x00000001,
    ZGMTRAttributeIDTypeClusterRVCRunModeAttributeGeneratedCommandListID ZGMTR_AVAILABLE(ios(17.4), macos(14.4), watchos(10.4), tvos(17.4)) = ZGMTRAttributeIDTypeGlobalAttributeGeneratedCommandListID,
    ZGMTRAttributeIDTypeClusterRVCRunModeAttributeAcceptedCommandListID ZGMTR_AVAILABLE(ios(17.4), macos(14.4), watchos(10.4), tvos(17.4)) = ZGMTRAttributeIDTypeGlobalAttributeAcceptedCommandListID,
    ZGMTRAttributeIDTypeClusterRVCRunModeAttributeAttributeListID ZGMTR_AVAILABLE(ios(17.4), macos(14.4), watchos(10.4), tvos(17.4)) = ZGMTRAttributeIDTypeGlobalAttributeAttributeListID,
    ZGMTRAttributeIDTypeClusterRVCRunModeAttributeFeatureMapID ZGMTR_AVAILABLE(ios(17.4), macos(14.4), watchos(10.4), tvos(17.4)) = ZGMTRAttributeIDTypeGlobalAttributeFeatureMapID,
    ZGMTRAttributeIDTypeClusterRVCRunModeAttributeClusterRevisionID ZGMTR_AVAILABLE(ios(17.4), macos(14.4), watchos(10.4), tvos(17.4)) = ZGMTRAttributeIDTypeGlobalAttributeClusterRevisionID,

    // Cluster RVCCleanMode attributes
    ZGMTRAttributeIDTypeClusterRVCCleanModeAttributeSupportedModesID ZGMTR_AVAILABLE(ios(17.4), macos(14.4), watchos(10.4), tvos(17.4)) = 0x00000000,
    ZGMTRAttributeIDTypeClusterRVCCleanModeAttributeCurrentModeID ZGMTR_AVAILABLE(ios(17.4), macos(14.4), watchos(10.4), tvos(17.4)) = 0x00000001,
    ZGMTRAttributeIDTypeClusterRVCCleanModeAttributeGeneratedCommandListID ZGMTR_AVAILABLE(ios(17.4), macos(14.4), watchos(10.4), tvos(17.4)) = ZGMTRAttributeIDTypeGlobalAttributeGeneratedCommandListID,
    ZGMTRAttributeIDTypeClusterRVCCleanModeAttributeAcceptedCommandListID ZGMTR_AVAILABLE(ios(17.4), macos(14.4), watchos(10.4), tvos(17.4)) = ZGMTRAttributeIDTypeGlobalAttributeAcceptedCommandListID,
    ZGMTRAttributeIDTypeClusterRVCCleanModeAttributeAttributeListID ZGMTR_AVAILABLE(ios(17.4), macos(14.4), watchos(10.4), tvos(17.4)) = ZGMTRAttributeIDTypeGlobalAttributeAttributeListID,
    ZGMTRAttributeIDTypeClusterRVCCleanModeAttributeFeatureMapID ZGMTR_AVAILABLE(ios(17.4), macos(14.4), watchos(10.4), tvos(17.4)) = ZGMTRAttributeIDTypeGlobalAttributeFeatureMapID,
    ZGMTRAttributeIDTypeClusterRVCCleanModeAttributeClusterRevisionID ZGMTR_AVAILABLE(ios(17.4), macos(14.4), watchos(10.4), tvos(17.4)) = ZGMTRAttributeIDTypeGlobalAttributeClusterRevisionID,

    // Cluster TemperatureControl attributes
    ZGMTRAttributeIDTypeClusterTemperatureControlAttributeTemperatureSetpointID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = 0x00000000,
    ZGMTRAttributeIDTypeClusterTemperatureControlAttributeMinTemperatureID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = 0x00000001,
    ZGMTRAttributeIDTypeClusterTemperatureControlAttributeMaxTemperatureID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = 0x00000002,
    ZGMTRAttributeIDTypeClusterTemperatureControlAttributeStepID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = 0x00000003,
    ZGMTRAttributeIDTypeClusterTemperatureControlAttributeSelectedTemperatureLevelID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = 0x00000004,
    ZGMTRAttributeIDTypeClusterTemperatureControlAttributeSupportedTemperatureLevelsID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = 0x00000005,
    ZGMTRAttributeIDTypeClusterTemperatureControlAttributeGeneratedCommandListID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = ZGMTRAttributeIDTypeGlobalAttributeGeneratedCommandListID,
    ZGMTRAttributeIDTypeClusterTemperatureControlAttributeAcceptedCommandListID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = ZGMTRAttributeIDTypeGlobalAttributeAcceptedCommandListID,
    ZGMTRAttributeIDTypeClusterTemperatureControlAttributeAttributeListID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = ZGMTRAttributeIDTypeGlobalAttributeAttributeListID,
    ZGMTRAttributeIDTypeClusterTemperatureControlAttributeFeatureMapID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = ZGMTRAttributeIDTypeGlobalAttributeFeatureMapID,
    ZGMTRAttributeIDTypeClusterTemperatureControlAttributeClusterRevisionID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = ZGMTRAttributeIDTypeGlobalAttributeClusterRevisionID,

    // Cluster RefrigeratorAlarm attributes
    ZGMTRAttributeIDTypeClusterRefrigeratorAlarmAttributeMaskID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = 0x00000000,
    ZGMTRAttributeIDTypeClusterRefrigeratorAlarmAttributeStateID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = 0x00000002,
    ZGMTRAttributeIDTypeClusterRefrigeratorAlarmAttributeSupportedID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = 0x00000003,
    ZGMTRAttributeIDTypeClusterRefrigeratorAlarmAttributeGeneratedCommandListID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = ZGMTRAttributeIDTypeGlobalAttributeGeneratedCommandListID,
    ZGMTRAttributeIDTypeClusterRefrigeratorAlarmAttributeAcceptedCommandListID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = ZGMTRAttributeIDTypeGlobalAttributeAcceptedCommandListID,
    ZGMTRAttributeIDTypeClusterRefrigeratorAlarmAttributeAttributeListID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = ZGMTRAttributeIDTypeGlobalAttributeAttributeListID,
    ZGMTRAttributeIDTypeClusterRefrigeratorAlarmAttributeFeatureMapID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = ZGMTRAttributeIDTypeGlobalAttributeFeatureMapID,
    ZGMTRAttributeIDTypeClusterRefrigeratorAlarmAttributeClusterRevisionID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = ZGMTRAttributeIDTypeGlobalAttributeClusterRevisionID,

    // Cluster DishwasherMode attributes
    ZGMTRAttributeIDTypeClusterDishwasherModeAttributeSupportedModesID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = 0x00000000,
    ZGMTRAttributeIDTypeClusterDishwasherModeAttributeCurrentModeID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = 0x00000001,
    ZGMTRAttributeIDTypeClusterDishwasherModeAttributeGeneratedCommandListID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = ZGMTRAttributeIDTypeGlobalAttributeGeneratedCommandListID,
    ZGMTRAttributeIDTypeClusterDishwasherModeAttributeAcceptedCommandListID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = ZGMTRAttributeIDTypeGlobalAttributeAcceptedCommandListID,
    ZGMTRAttributeIDTypeClusterDishwasherModeAttributeAttributeListID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = ZGMTRAttributeIDTypeGlobalAttributeAttributeListID,
    ZGMTRAttributeIDTypeClusterDishwasherModeAttributeFeatureMapID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = ZGMTRAttributeIDTypeGlobalAttributeFeatureMapID,
    ZGMTRAttributeIDTypeClusterDishwasherModeAttributeClusterRevisionID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = ZGMTRAttributeIDTypeGlobalAttributeClusterRevisionID,

    // Cluster AirQuality attributes
    ZGMTRAttributeIDTypeClusterAirQualityAttributeAirQualityID ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6)) = 0x00000000,
    ZGMTRAttributeIDTypeClusterAirQualityAttributeGeneratedCommandListID ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6)) = ZGMTRAttributeIDTypeGlobalAttributeGeneratedCommandListID,
    ZGMTRAttributeIDTypeClusterAirQualityAttributeAcceptedCommandListID ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6)) = ZGMTRAttributeIDTypeGlobalAttributeAcceptedCommandListID,
    ZGMTRAttributeIDTypeClusterAirQualityAttributeAttributeListID ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6)) = ZGMTRAttributeIDTypeGlobalAttributeAttributeListID,
    ZGMTRAttributeIDTypeClusterAirQualityAttributeFeatureMapID ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6)) = ZGMTRAttributeIDTypeGlobalAttributeFeatureMapID,
    ZGMTRAttributeIDTypeClusterAirQualityAttributeClusterRevisionID ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6)) = ZGMTRAttributeIDTypeGlobalAttributeClusterRevisionID,

    // Cluster SmokeCOAlarm attributes
    ZGMTRAttributeIDTypeClusterSmokeCOAlarmAttributeExpressedStateID ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6)) = 0x00000000,
    ZGMTRAttributeIDTypeClusterSmokeCOAlarmAttributeSmokeStateID ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6)) = 0x00000001,
    ZGMTRAttributeIDTypeClusterSmokeCOAlarmAttributeCOStateID ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6)) = 0x00000002,
    ZGMTRAttributeIDTypeClusterSmokeCOAlarmAttributeBatteryAlertID ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6)) = 0x00000003,
    ZGMTRAttributeIDTypeClusterSmokeCOAlarmAttributeDeviceMutedID ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6)) = 0x00000004,
    ZGMTRAttributeIDTypeClusterSmokeCOAlarmAttributeTestInProgressID ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6)) = 0x00000005,
    ZGMTRAttributeIDTypeClusterSmokeCOAlarmAttributeHardwareFaultAlertID ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6)) = 0x00000006,
    ZGMTRAttributeIDTypeClusterSmokeCOAlarmAttributeEndOfServiceAlertID ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6)) = 0x00000007,
    ZGMTRAttributeIDTypeClusterSmokeCOAlarmAttributeInterconnectSmokeAlarmID ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6)) = 0x00000008,
    ZGMTRAttributeIDTypeClusterSmokeCOAlarmAttributeInterconnectCOAlarmID ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6)) = 0x00000009,
    ZGMTRAttributeIDTypeClusterSmokeCOAlarmAttributeContaminationStateID ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6)) = 0x0000000A,
    ZGMTRAttributeIDTypeClusterSmokeCOAlarmAttributeSmokeSensitivityLevelID ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6)) = 0x0000000B,
    ZGMTRAttributeIDTypeClusterSmokeCOAlarmAttributeExpiryDateID ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6)) = 0x0000000C,
    ZGMTRAttributeIDTypeClusterSmokeCOAlarmAttributeUnmountedID ZGMTR_PROVISIONALLY_AVAILABLE = 0x0000000D,
    ZGMTRAttributeIDTypeClusterSmokeCOAlarmAttributeGeneratedCommandListID ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6)) = ZGMTRAttributeIDTypeGlobalAttributeGeneratedCommandListID,
    ZGMTRAttributeIDTypeClusterSmokeCOAlarmAttributeAcceptedCommandListID ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6)) = ZGMTRAttributeIDTypeGlobalAttributeAcceptedCommandListID,
    ZGMTRAttributeIDTypeClusterSmokeCOAlarmAttributeAttributeListID ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6)) = ZGMTRAttributeIDTypeGlobalAttributeAttributeListID,
    ZGMTRAttributeIDTypeClusterSmokeCOAlarmAttributeFeatureMapID ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6)) = ZGMTRAttributeIDTypeGlobalAttributeFeatureMapID,
    ZGMTRAttributeIDTypeClusterSmokeCOAlarmAttributeClusterRevisionID ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6)) = ZGMTRAttributeIDTypeGlobalAttributeClusterRevisionID,

    // Cluster DishwasherAlarm attributes
    ZGMTRAttributeIDTypeClusterDishwasherAlarmAttributeMaskID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = 0x00000000,
    ZGMTRAttributeIDTypeClusterDishwasherAlarmAttributeLatchID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = 0x00000001,
    ZGMTRAttributeIDTypeClusterDishwasherAlarmAttributeStateID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = 0x00000002,
    ZGMTRAttributeIDTypeClusterDishwasherAlarmAttributeSupportedID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = 0x00000003,
    ZGMTRAttributeIDTypeClusterDishwasherAlarmAttributeGeneratedCommandListID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = ZGMTRAttributeIDTypeGlobalAttributeGeneratedCommandListID,
    ZGMTRAttributeIDTypeClusterDishwasherAlarmAttributeAcceptedCommandListID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = ZGMTRAttributeIDTypeGlobalAttributeAcceptedCommandListID,
    ZGMTRAttributeIDTypeClusterDishwasherAlarmAttributeAttributeListID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = ZGMTRAttributeIDTypeGlobalAttributeAttributeListID,
    ZGMTRAttributeIDTypeClusterDishwasherAlarmAttributeFeatureMapID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = ZGMTRAttributeIDTypeGlobalAttributeFeatureMapID,
    ZGMTRAttributeIDTypeClusterDishwasherAlarmAttributeClusterRevisionID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = ZGMTRAttributeIDTypeGlobalAttributeClusterRevisionID,

    // Cluster MicrowaveOvenMode attributes
    ZGMTRAttributeIDTypeClusterMicrowaveOvenModeAttributeSupportedModesID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = 0x00000000,
    ZGMTRAttributeIDTypeClusterMicrowaveOvenModeAttributeCurrentModeID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = 0x00000001,
    ZGMTRAttributeIDTypeClusterMicrowaveOvenModeAttributeGeneratedCommandListID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = ZGMTRAttributeIDTypeGlobalAttributeGeneratedCommandListID,
    ZGMTRAttributeIDTypeClusterMicrowaveOvenModeAttributeAcceptedCommandListID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = ZGMTRAttributeIDTypeGlobalAttributeAcceptedCommandListID,
    ZGMTRAttributeIDTypeClusterMicrowaveOvenModeAttributeAttributeListID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = ZGMTRAttributeIDTypeGlobalAttributeAttributeListID,
    ZGMTRAttributeIDTypeClusterMicrowaveOvenModeAttributeFeatureMapID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = ZGMTRAttributeIDTypeGlobalAttributeFeatureMapID,
    ZGMTRAttributeIDTypeClusterMicrowaveOvenModeAttributeClusterRevisionID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = ZGMTRAttributeIDTypeGlobalAttributeClusterRevisionID,

    // Cluster MicrowaveOvenControl attributes
    ZGMTRAttributeIDTypeClusterMicrowaveOvenControlAttributeCookTimeID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = 0x00000000,
    ZGMTRAttributeIDTypeClusterMicrowaveOvenControlAttributeMaxCookTimeID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = 0x00000001,
    ZGMTRAttributeIDTypeClusterMicrowaveOvenControlAttributePowerSettingID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = 0x00000002,
    ZGMTRAttributeIDTypeClusterMicrowaveOvenControlAttributeMinPowerID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = 0x00000003,
    ZGMTRAttributeIDTypeClusterMicrowaveOvenControlAttributeMaxPowerID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = 0x00000004,
    ZGMTRAttributeIDTypeClusterMicrowaveOvenControlAttributePowerStepID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = 0x00000005,
    ZGMTRAttributeIDTypeClusterMicrowaveOvenControlAttributeSupportedWattsID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000006,
    ZGMTRAttributeIDTypeClusterMicrowaveOvenControlAttributeSelectedWattIndexID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000007,
    ZGMTRAttributeIDTypeClusterMicrowaveOvenControlAttributeWattRatingID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = 0x00000008,
    ZGMTRAttributeIDTypeClusterMicrowaveOvenControlAttributeGeneratedCommandListID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = ZGMTRAttributeIDTypeGlobalAttributeGeneratedCommandListID,
    ZGMTRAttributeIDTypeClusterMicrowaveOvenControlAttributeAcceptedCommandListID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = ZGMTRAttributeIDTypeGlobalAttributeAcceptedCommandListID,
    ZGMTRAttributeIDTypeClusterMicrowaveOvenControlAttributeAttributeListID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = ZGMTRAttributeIDTypeGlobalAttributeAttributeListID,
    ZGMTRAttributeIDTypeClusterMicrowaveOvenControlAttributeFeatureMapID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = ZGMTRAttributeIDTypeGlobalAttributeFeatureMapID,
    ZGMTRAttributeIDTypeClusterMicrowaveOvenControlAttributeClusterRevisionID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = ZGMTRAttributeIDTypeGlobalAttributeClusterRevisionID,

    // Cluster OperationalState attributes
    ZGMTRAttributeIDTypeClusterOperationalStateAttributePhaseListID ZGMTR_AVAILABLE(ios(17.4), macos(14.4), watchos(10.4), tvos(17.4)) = 0x00000000,
    ZGMTRAttributeIDTypeClusterOperationalStateAttributeCurrentPhaseID ZGMTR_AVAILABLE(ios(17.4), macos(14.4), watchos(10.4), tvos(17.4)) = 0x00000001,
    ZGMTRAttributeIDTypeClusterOperationalStateAttributeCountdownTimeID ZGMTR_AVAILABLE(ios(17.4), macos(14.4), watchos(10.4), tvos(17.4)) = 0x00000002,
    ZGMTRAttributeIDTypeClusterOperationalStateAttributeOperationalStateListID ZGMTR_AVAILABLE(ios(17.4), macos(14.4), watchos(10.4), tvos(17.4)) = 0x00000003,
    ZGMTRAttributeIDTypeClusterOperationalStateAttributeOperationalStateID ZGMTR_AVAILABLE(ios(17.4), macos(14.4), watchos(10.4), tvos(17.4)) = 0x00000004,
    ZGMTRAttributeIDTypeClusterOperationalStateAttributeOperationalErrorID ZGMTR_AVAILABLE(ios(17.4), macos(14.4), watchos(10.4), tvos(17.4)) = 0x00000005,
    ZGMTRAttributeIDTypeClusterOperationalStateAttributeGeneratedCommandListID ZGMTR_AVAILABLE(ios(17.4), macos(14.4), watchos(10.4), tvos(17.4)) = ZGMTRAttributeIDTypeGlobalAttributeGeneratedCommandListID,
    ZGMTRAttributeIDTypeClusterOperationalStateAttributeAcceptedCommandListID ZGMTR_AVAILABLE(ios(17.4), macos(14.4), watchos(10.4), tvos(17.4)) = ZGMTRAttributeIDTypeGlobalAttributeAcceptedCommandListID,
    ZGMTRAttributeIDTypeClusterOperationalStateAttributeAttributeListID ZGMTR_AVAILABLE(ios(17.4), macos(14.4), watchos(10.4), tvos(17.4)) = ZGMTRAttributeIDTypeGlobalAttributeAttributeListID,
    ZGMTRAttributeIDTypeClusterOperationalStateAttributeFeatureMapID ZGMTR_AVAILABLE(ios(17.4), macos(14.4), watchos(10.4), tvos(17.4)) = ZGMTRAttributeIDTypeGlobalAttributeFeatureMapID,
    ZGMTRAttributeIDTypeClusterOperationalStateAttributeClusterRevisionID ZGMTR_AVAILABLE(ios(17.4), macos(14.4), watchos(10.4), tvos(17.4)) = ZGMTRAttributeIDTypeGlobalAttributeClusterRevisionID,

    // Cluster RVCOperationalState attributes
    ZGMTRAttributeIDTypeClusterRVCOperationalStateAttributePhaseListID ZGMTR_AVAILABLE(ios(17.4), macos(14.4), watchos(10.4), tvos(17.4)) = 0x00000000,
    ZGMTRAttributeIDTypeClusterRVCOperationalStateAttributeCurrentPhaseID ZGMTR_AVAILABLE(ios(17.4), macos(14.4), watchos(10.4), tvos(17.4)) = 0x00000001,
    ZGMTRAttributeIDTypeClusterRVCOperationalStateAttributeCountdownTimeID ZGMTR_AVAILABLE(ios(17.4), macos(14.4), watchos(10.4), tvos(17.4)) = 0x00000002,
    ZGMTRAttributeIDTypeClusterRVCOperationalStateAttributeOperationalStateListID ZGMTR_AVAILABLE(ios(17.4), macos(14.4), watchos(10.4), tvos(17.4)) = 0x00000003,
    ZGMTRAttributeIDTypeClusterRVCOperationalStateAttributeOperationalStateID ZGMTR_AVAILABLE(ios(17.4), macos(14.4), watchos(10.4), tvos(17.4)) = 0x00000004,
    ZGMTRAttributeIDTypeClusterRVCOperationalStateAttributeOperationalErrorID ZGMTR_AVAILABLE(ios(17.4), macos(14.4), watchos(10.4), tvos(17.4)) = 0x00000005,
    ZGMTRAttributeIDTypeClusterRVCOperationalStateAttributeGeneratedCommandListID ZGMTR_AVAILABLE(ios(17.4), macos(14.4), watchos(10.4), tvos(17.4)) = ZGMTRAttributeIDTypeGlobalAttributeGeneratedCommandListID,
    ZGMTRAttributeIDTypeClusterRVCOperationalStateAttributeAcceptedCommandListID ZGMTR_AVAILABLE(ios(17.4), macos(14.4), watchos(10.4), tvos(17.4)) = ZGMTRAttributeIDTypeGlobalAttributeAcceptedCommandListID,
    ZGMTRAttributeIDTypeClusterRVCOperationalStateAttributeAttributeListID ZGMTR_AVAILABLE(ios(17.4), macos(14.4), watchos(10.4), tvos(17.4)) = ZGMTRAttributeIDTypeGlobalAttributeAttributeListID,
    ZGMTRAttributeIDTypeClusterRVCOperationalStateAttributeFeatureMapID ZGMTR_AVAILABLE(ios(17.4), macos(14.4), watchos(10.4), tvos(17.4)) = ZGMTRAttributeIDTypeGlobalAttributeFeatureMapID,
    ZGMTRAttributeIDTypeClusterRVCOperationalStateAttributeClusterRevisionID ZGMTR_AVAILABLE(ios(17.4), macos(14.4), watchos(10.4), tvos(17.4)) = ZGMTRAttributeIDTypeGlobalAttributeClusterRevisionID,

    // Cluster ScenesManagement attributes
    ZGMTRAttributeIDTypeClusterScenesManagementAttributeSceneTableSizeID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000001,
    ZGMTRAttributeIDTypeClusterScenesManagementAttributeFabricSceneInfoID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000002,
    ZGMTRAttributeIDTypeClusterScenesManagementAttributeGeneratedCommandListID ZGMTR_PROVISIONALLY_AVAILABLE = ZGMTRAttributeIDTypeGlobalAttributeGeneratedCommandListID,
    ZGMTRAttributeIDTypeClusterScenesManagementAttributeAcceptedCommandListID ZGMTR_PROVISIONALLY_AVAILABLE = ZGMTRAttributeIDTypeGlobalAttributeAcceptedCommandListID,
    ZGMTRAttributeIDTypeClusterScenesManagementAttributeAttributeListID ZGMTR_PROVISIONALLY_AVAILABLE = ZGMTRAttributeIDTypeGlobalAttributeAttributeListID,
    ZGMTRAttributeIDTypeClusterScenesManagementAttributeFeatureMapID ZGMTR_PROVISIONALLY_AVAILABLE = ZGMTRAttributeIDTypeGlobalAttributeFeatureMapID,
    ZGMTRAttributeIDTypeClusterScenesManagementAttributeClusterRevisionID ZGMTR_PROVISIONALLY_AVAILABLE = ZGMTRAttributeIDTypeGlobalAttributeClusterRevisionID,

    // Cluster Groupcast attributes
    ZGMTRAttributeIDTypeClusterGroupcastAttributeMembershipID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000000,
    ZGMTRAttributeIDTypeClusterGroupcastAttributeMaxMembershipCountID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000001,
    ZGMTRAttributeIDTypeClusterGroupcastAttributeMaxMcastAddrCountID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000002,
    ZGMTRAttributeIDTypeClusterGroupcastAttributeUsedMcastAddrCountID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000003,
    ZGMTRAttributeIDTypeClusterGroupcastAttributeFabricUnderTestID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000004,
    ZGMTRAttributeIDTypeClusterGroupcastAttributeGeneratedCommandListID ZGMTR_PROVISIONALLY_AVAILABLE = ZGMTRAttributeIDTypeGlobalAttributeGeneratedCommandListID,
    ZGMTRAttributeIDTypeClusterGroupcastAttributeAcceptedCommandListID ZGMTR_PROVISIONALLY_AVAILABLE = ZGMTRAttributeIDTypeGlobalAttributeAcceptedCommandListID,
    ZGMTRAttributeIDTypeClusterGroupcastAttributeAttributeListID ZGMTR_PROVISIONALLY_AVAILABLE = ZGMTRAttributeIDTypeGlobalAttributeAttributeListID,
    ZGMTRAttributeIDTypeClusterGroupcastAttributeFeatureMapID ZGMTR_PROVISIONALLY_AVAILABLE = ZGMTRAttributeIDTypeGlobalAttributeFeatureMapID,
    ZGMTRAttributeIDTypeClusterGroupcastAttributeClusterRevisionID ZGMTR_PROVISIONALLY_AVAILABLE = ZGMTRAttributeIDTypeGlobalAttributeClusterRevisionID,

    // Cluster HEPAFilterMonitoring attributes
    ZGMTRAttributeIDTypeClusterHEPAFilterMonitoringAttributeConditionID ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6)) = 0x00000000,
    ZGMTRAttributeIDTypeClusterHEPAFilterMonitoringAttributeDegradationDirectionID ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6)) = 0x00000001,
    ZGMTRAttributeIDTypeClusterHEPAFilterMonitoringAttributeChangeIndicationID ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6)) = 0x00000002,
    ZGMTRAttributeIDTypeClusterHEPAFilterMonitoringAttributeInPlaceIndicatorID ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6)) = 0x00000003,
    ZGMTRAttributeIDTypeClusterHEPAFilterMonitoringAttributeLastChangedTimeID ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6)) = 0x00000004,
    ZGMTRAttributeIDTypeClusterHEPAFilterMonitoringAttributeReplacementProductListID ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6)) = 0x00000005,
    ZGMTRAttributeIDTypeClusterHEPAFilterMonitoringAttributeGeneratedCommandListID ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6)) = ZGMTRAttributeIDTypeGlobalAttributeGeneratedCommandListID,
    ZGMTRAttributeIDTypeClusterHEPAFilterMonitoringAttributeAcceptedCommandListID ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6)) = ZGMTRAttributeIDTypeGlobalAttributeAcceptedCommandListID,
    ZGMTRAttributeIDTypeClusterHEPAFilterMonitoringAttributeAttributeListID ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6)) = ZGMTRAttributeIDTypeGlobalAttributeAttributeListID,
    ZGMTRAttributeIDTypeClusterHEPAFilterMonitoringAttributeFeatureMapID ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6)) = ZGMTRAttributeIDTypeGlobalAttributeFeatureMapID,
    ZGMTRAttributeIDTypeClusterHEPAFilterMonitoringAttributeClusterRevisionID ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6)) = ZGMTRAttributeIDTypeGlobalAttributeClusterRevisionID,

    // Cluster ActivatedCarbonFilterMonitoring attributes
    ZGMTRAttributeIDTypeClusterActivatedCarbonFilterMonitoringAttributeConditionID ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6)) = 0x00000000,
    ZGMTRAttributeIDTypeClusterActivatedCarbonFilterMonitoringAttributeDegradationDirectionID ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6)) = 0x00000001,
    ZGMTRAttributeIDTypeClusterActivatedCarbonFilterMonitoringAttributeChangeIndicationID ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6)) = 0x00000002,
    ZGMTRAttributeIDTypeClusterActivatedCarbonFilterMonitoringAttributeInPlaceIndicatorID ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6)) = 0x00000003,
    ZGMTRAttributeIDTypeClusterActivatedCarbonFilterMonitoringAttributeLastChangedTimeID ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6)) = 0x00000004,
    ZGMTRAttributeIDTypeClusterActivatedCarbonFilterMonitoringAttributeReplacementProductListID ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6)) = 0x00000005,
    ZGMTRAttributeIDTypeClusterActivatedCarbonFilterMonitoringAttributeGeneratedCommandListID ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6)) = ZGMTRAttributeIDTypeGlobalAttributeGeneratedCommandListID,
    ZGMTRAttributeIDTypeClusterActivatedCarbonFilterMonitoringAttributeAcceptedCommandListID ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6)) = ZGMTRAttributeIDTypeGlobalAttributeAcceptedCommandListID,
    ZGMTRAttributeIDTypeClusterActivatedCarbonFilterMonitoringAttributeAttributeListID ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6)) = ZGMTRAttributeIDTypeGlobalAttributeAttributeListID,
    ZGMTRAttributeIDTypeClusterActivatedCarbonFilterMonitoringAttributeFeatureMapID ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6)) = ZGMTRAttributeIDTypeGlobalAttributeFeatureMapID,
    ZGMTRAttributeIDTypeClusterActivatedCarbonFilterMonitoringAttributeClusterRevisionID ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6)) = ZGMTRAttributeIDTypeGlobalAttributeClusterRevisionID,

    // Cluster WaterTankLevelMonitoring attributes
    ZGMTRAttributeIDTypeClusterWaterTankLevelMonitoringAttributeConditionID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000000,
    ZGMTRAttributeIDTypeClusterWaterTankLevelMonitoringAttributeDegradationDirectionID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000001,
    ZGMTRAttributeIDTypeClusterWaterTankLevelMonitoringAttributeChangeIndicationID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000002,
    ZGMTRAttributeIDTypeClusterWaterTankLevelMonitoringAttributeInPlaceIndicatorID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000003,
    ZGMTRAttributeIDTypeClusterWaterTankLevelMonitoringAttributeLastChangedTimeID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000004,
    ZGMTRAttributeIDTypeClusterWaterTankLevelMonitoringAttributeReplacementProductListID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000005,
    ZGMTRAttributeIDTypeClusterWaterTankLevelMonitoringAttributeGeneratedCommandListID ZGMTR_PROVISIONALLY_AVAILABLE = ZGMTRAttributeIDTypeGlobalAttributeGeneratedCommandListID,
    ZGMTRAttributeIDTypeClusterWaterTankLevelMonitoringAttributeAcceptedCommandListID ZGMTR_PROVISIONALLY_AVAILABLE = ZGMTRAttributeIDTypeGlobalAttributeAcceptedCommandListID,
    ZGMTRAttributeIDTypeClusterWaterTankLevelMonitoringAttributeAttributeListID ZGMTR_PROVISIONALLY_AVAILABLE = ZGMTRAttributeIDTypeGlobalAttributeAttributeListID,
    ZGMTRAttributeIDTypeClusterWaterTankLevelMonitoringAttributeFeatureMapID ZGMTR_PROVISIONALLY_AVAILABLE = ZGMTRAttributeIDTypeGlobalAttributeFeatureMapID,
    ZGMTRAttributeIDTypeClusterWaterTankLevelMonitoringAttributeClusterRevisionID ZGMTR_PROVISIONALLY_AVAILABLE = ZGMTRAttributeIDTypeGlobalAttributeClusterRevisionID,

    // Cluster BooleanStateConfiguration attributes
    ZGMTRAttributeIDTypeClusterBooleanStateConfigurationAttributeCurrentSensitivityLevelID ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6)) = 0x00000000,
    ZGMTRAttributeIDTypeClusterBooleanStateConfigurationAttributeSupportedSensitivityLevelsID ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6)) = 0x00000001,
    ZGMTRAttributeIDTypeClusterBooleanStateConfigurationAttributeDefaultSensitivityLevelID ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6)) = 0x00000002,
    ZGMTRAttributeIDTypeClusterBooleanStateConfigurationAttributeAlarmsActiveID ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6)) = 0x00000003,
    ZGMTRAttributeIDTypeClusterBooleanStateConfigurationAttributeAlarmsSuppressedID ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6)) = 0x00000004,
    ZGMTRAttributeIDTypeClusterBooleanStateConfigurationAttributeAlarmsEnabledID ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6)) = 0x00000005,
    ZGMTRAttributeIDTypeClusterBooleanStateConfigurationAttributeAlarmsSupportedID ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6)) = 0x00000006,
    ZGMTRAttributeIDTypeClusterBooleanStateConfigurationAttributeSensorFaultID ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6)) = 0x00000007,
    ZGMTRAttributeIDTypeClusterBooleanStateConfigurationAttributeGeneratedCommandListID ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6)) = ZGMTRAttributeIDTypeGlobalAttributeGeneratedCommandListID,
    ZGMTRAttributeIDTypeClusterBooleanStateConfigurationAttributeAcceptedCommandListID ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6)) = ZGMTRAttributeIDTypeGlobalAttributeAcceptedCommandListID,
    ZGMTRAttributeIDTypeClusterBooleanStateConfigurationAttributeAttributeListID ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6)) = ZGMTRAttributeIDTypeGlobalAttributeAttributeListID,
    ZGMTRAttributeIDTypeClusterBooleanStateConfigurationAttributeFeatureMapID ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6)) = ZGMTRAttributeIDTypeGlobalAttributeFeatureMapID,
    ZGMTRAttributeIDTypeClusterBooleanStateConfigurationAttributeClusterRevisionID ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6)) = ZGMTRAttributeIDTypeGlobalAttributeClusterRevisionID,

    // Cluster ValveConfigurationAndControl attributes
    ZGMTRAttributeIDTypeClusterValveConfigurationAndControlAttributeOpenDurationID ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6)) = 0x00000000,
    ZGMTRAttributeIDTypeClusterValveConfigurationAndControlAttributeDefaultOpenDurationID ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6)) = 0x00000001,
    ZGMTRAttributeIDTypeClusterValveConfigurationAndControlAttributeAutoCloseTimeID ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6)) = 0x00000002,
    ZGMTRAttributeIDTypeClusterValveConfigurationAndControlAttributeRemainingDurationID ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6)) = 0x00000003,
    ZGMTRAttributeIDTypeClusterValveConfigurationAndControlAttributeCurrentStateID ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6)) = 0x00000004,
    ZGMTRAttributeIDTypeClusterValveConfigurationAndControlAttributeTargetStateID ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6)) = 0x00000005,
    ZGMTRAttributeIDTypeClusterValveConfigurationAndControlAttributeCurrentLevelID ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6)) = 0x00000006,
    ZGMTRAttributeIDTypeClusterValveConfigurationAndControlAttributeTargetLevelID ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6)) = 0x00000007,
    ZGMTRAttributeIDTypeClusterValveConfigurationAndControlAttributeDefaultOpenLevelID ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6)) = 0x00000008,
    ZGMTRAttributeIDTypeClusterValveConfigurationAndControlAttributeValveFaultID ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6)) = 0x00000009,
    ZGMTRAttributeIDTypeClusterValveConfigurationAndControlAttributeLevelStepID ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6)) = 0x0000000A,
    ZGMTRAttributeIDTypeClusterValveConfigurationAndControlAttributeGeneratedCommandListID ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6)) = ZGMTRAttributeIDTypeGlobalAttributeGeneratedCommandListID,
    ZGMTRAttributeIDTypeClusterValveConfigurationAndControlAttributeAcceptedCommandListID ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6)) = ZGMTRAttributeIDTypeGlobalAttributeAcceptedCommandListID,
    ZGMTRAttributeIDTypeClusterValveConfigurationAndControlAttributeAttributeListID ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6)) = ZGMTRAttributeIDTypeGlobalAttributeAttributeListID,
    ZGMTRAttributeIDTypeClusterValveConfigurationAndControlAttributeFeatureMapID ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6)) = ZGMTRAttributeIDTypeGlobalAttributeFeatureMapID,
    ZGMTRAttributeIDTypeClusterValveConfigurationAndControlAttributeClusterRevisionID ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6)) = ZGMTRAttributeIDTypeGlobalAttributeClusterRevisionID,

    // Cluster ElectricalPowerMeasurement attributes
    ZGMTRAttributeIDTypeClusterElectricalPowerMeasurementAttributePowerModeID ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6)) = 0x00000000,
    ZGMTRAttributeIDTypeClusterElectricalPowerMeasurementAttributeNumberOfMeasurementTypesID ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6)) = 0x00000001,
    ZGMTRAttributeIDTypeClusterElectricalPowerMeasurementAttributeAccuracyID ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6)) = 0x00000002,
    ZGMTRAttributeIDTypeClusterElectricalPowerMeasurementAttributeRangesID ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6)) = 0x00000003,
    ZGMTRAttributeIDTypeClusterElectricalPowerMeasurementAttributeVoltageID ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6)) = 0x00000004,
    ZGMTRAttributeIDTypeClusterElectricalPowerMeasurementAttributeActiveCurrentID ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6)) = 0x00000005,
    ZGMTRAttributeIDTypeClusterElectricalPowerMeasurementAttributeReactiveCurrentID ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6)) = 0x00000006,
    ZGMTRAttributeIDTypeClusterElectricalPowerMeasurementAttributeApparentCurrentID ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6)) = 0x00000007,
    ZGMTRAttributeIDTypeClusterElectricalPowerMeasurementAttributeActivePowerID ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6)) = 0x00000008,
    ZGMTRAttributeIDTypeClusterElectricalPowerMeasurementAttributeReactivePowerID ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6)) = 0x00000009,
    ZGMTRAttributeIDTypeClusterElectricalPowerMeasurementAttributeApparentPowerID ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6)) = 0x0000000A,
    ZGMTRAttributeIDTypeClusterElectricalPowerMeasurementAttributeRMSVoltageID ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6)) = 0x0000000B,
    ZGMTRAttributeIDTypeClusterElectricalPowerMeasurementAttributeRMSCurrentID ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6)) = 0x0000000C,
    ZGMTRAttributeIDTypeClusterElectricalPowerMeasurementAttributeRMSPowerID ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6)) = 0x0000000D,
    ZGMTRAttributeIDTypeClusterElectricalPowerMeasurementAttributeFrequencyID ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6)) = 0x0000000E,
    ZGMTRAttributeIDTypeClusterElectricalPowerMeasurementAttributeHarmonicCurrentsID ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6)) = 0x0000000F,
    ZGMTRAttributeIDTypeClusterElectricalPowerMeasurementAttributeHarmonicPhasesID ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6)) = 0x00000010,
    ZGMTRAttributeIDTypeClusterElectricalPowerMeasurementAttributePowerFactorID ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6)) = 0x00000011,
    ZGMTRAttributeIDTypeClusterElectricalPowerMeasurementAttributeNeutralCurrentID ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6)) = 0x00000012,
    ZGMTRAttributeIDTypeClusterElectricalPowerMeasurementAttributeGeneratedCommandListID ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6)) = ZGMTRAttributeIDTypeGlobalAttributeGeneratedCommandListID,
    ZGMTRAttributeIDTypeClusterElectricalPowerMeasurementAttributeAcceptedCommandListID ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6)) = ZGMTRAttributeIDTypeGlobalAttributeAcceptedCommandListID,
    ZGMTRAttributeIDTypeClusterElectricalPowerMeasurementAttributeAttributeListID ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6)) = ZGMTRAttributeIDTypeGlobalAttributeAttributeListID,
    ZGMTRAttributeIDTypeClusterElectricalPowerMeasurementAttributeFeatureMapID ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6)) = ZGMTRAttributeIDTypeGlobalAttributeFeatureMapID,
    ZGMTRAttributeIDTypeClusterElectricalPowerMeasurementAttributeClusterRevisionID ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6)) = ZGMTRAttributeIDTypeGlobalAttributeClusterRevisionID,

    // Cluster ElectricalEnergyMeasurement attributes
    ZGMTRAttributeIDTypeClusterElectricalEnergyMeasurementAttributeAccuracyID ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6)) = 0x00000000,
    ZGMTRAttributeIDTypeClusterElectricalEnergyMeasurementAttributeCumulativeEnergyImportedID ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6)) = 0x00000001,
    ZGMTRAttributeIDTypeClusterElectricalEnergyMeasurementAttributeCumulativeEnergyExportedID ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6)) = 0x00000002,
    ZGMTRAttributeIDTypeClusterElectricalEnergyMeasurementAttributePeriodicEnergyImportedID ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6)) = 0x00000003,
    ZGMTRAttributeIDTypeClusterElectricalEnergyMeasurementAttributePeriodicEnergyExportedID ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6)) = 0x00000004,
    ZGMTRAttributeIDTypeClusterElectricalEnergyMeasurementAttributeCumulativeEnergyResetID ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6)) = 0x00000005,
    ZGMTRAttributeIDTypeClusterElectricalEnergyMeasurementAttributeGeneratedCommandListID ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6)) = ZGMTRAttributeIDTypeGlobalAttributeGeneratedCommandListID,
    ZGMTRAttributeIDTypeClusterElectricalEnergyMeasurementAttributeAcceptedCommandListID ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6)) = ZGMTRAttributeIDTypeGlobalAttributeAcceptedCommandListID,
    ZGMTRAttributeIDTypeClusterElectricalEnergyMeasurementAttributeAttributeListID ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6)) = ZGMTRAttributeIDTypeGlobalAttributeAttributeListID,
    ZGMTRAttributeIDTypeClusterElectricalEnergyMeasurementAttributeFeatureMapID ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6)) = ZGMTRAttributeIDTypeGlobalAttributeFeatureMapID,
    ZGMTRAttributeIDTypeClusterElectricalEnergyMeasurementAttributeClusterRevisionID ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6)) = ZGMTRAttributeIDTypeGlobalAttributeClusterRevisionID,

    // Cluster WaterHeaterManagement attributes
    ZGMTRAttributeIDTypeClusterWaterHeaterManagementAttributeHeaterTypesID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = 0x00000000,
    ZGMTRAttributeIDTypeClusterWaterHeaterManagementAttributeHeatDemandID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = 0x00000001,
    ZGMTRAttributeIDTypeClusterWaterHeaterManagementAttributeTankVolumeID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = 0x00000002,
    ZGMTRAttributeIDTypeClusterWaterHeaterManagementAttributeEstimatedHeatRequiredID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = 0x00000003,
    ZGMTRAttributeIDTypeClusterWaterHeaterManagementAttributeTankPercentageID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = 0x00000004,
    ZGMTRAttributeIDTypeClusterWaterHeaterManagementAttributeBoostStateID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = 0x00000005,
    ZGMTRAttributeIDTypeClusterWaterHeaterManagementAttributeGeneratedCommandListID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = ZGMTRAttributeIDTypeGlobalAttributeGeneratedCommandListID,
    ZGMTRAttributeIDTypeClusterWaterHeaterManagementAttributeAcceptedCommandListID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = ZGMTRAttributeIDTypeGlobalAttributeAcceptedCommandListID,
    ZGMTRAttributeIDTypeClusterWaterHeaterManagementAttributeAttributeListID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = ZGMTRAttributeIDTypeGlobalAttributeAttributeListID,
    ZGMTRAttributeIDTypeClusterWaterHeaterManagementAttributeFeatureMapID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = ZGMTRAttributeIDTypeGlobalAttributeFeatureMapID,
    ZGMTRAttributeIDTypeClusterWaterHeaterManagementAttributeClusterRevisionID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = ZGMTRAttributeIDTypeGlobalAttributeClusterRevisionID,

    // Cluster CommodityPrice attributes
    ZGMTRAttributeIDTypeClusterCommodityPriceAttributeTariffUnitID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000000,
    ZGMTRAttributeIDTypeClusterCommodityPriceAttributeCurrencyID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000001,
    ZGMTRAttributeIDTypeClusterCommodityPriceAttributeCurrentPriceID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000002,
    ZGMTRAttributeIDTypeClusterCommodityPriceAttributePriceForecastID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000003,
    ZGMTRAttributeIDTypeClusterCommodityPriceAttributeGeneratedCommandListID ZGMTR_PROVISIONALLY_AVAILABLE = ZGMTRAttributeIDTypeGlobalAttributeGeneratedCommandListID,
    ZGMTRAttributeIDTypeClusterCommodityPriceAttributeAcceptedCommandListID ZGMTR_PROVISIONALLY_AVAILABLE = ZGMTRAttributeIDTypeGlobalAttributeAcceptedCommandListID,
    ZGMTRAttributeIDTypeClusterCommodityPriceAttributeAttributeListID ZGMTR_PROVISIONALLY_AVAILABLE = ZGMTRAttributeIDTypeGlobalAttributeAttributeListID,
    ZGMTRAttributeIDTypeClusterCommodityPriceAttributeFeatureMapID ZGMTR_PROVISIONALLY_AVAILABLE = ZGMTRAttributeIDTypeGlobalAttributeFeatureMapID,
    ZGMTRAttributeIDTypeClusterCommodityPriceAttributeClusterRevisionID ZGMTR_PROVISIONALLY_AVAILABLE = ZGMTRAttributeIDTypeGlobalAttributeClusterRevisionID,

    // Cluster Messages attributes
    ZGMTRAttributeIDTypeClusterMessagesAttributeMessagesID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = 0x00000000,
    ZGMTRAttributeIDTypeClusterMessagesAttributeActiveMessageIDsID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = 0x00000001,
    ZGMTRAttributeIDTypeClusterMessagesAttributeGeneratedCommandListID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = ZGMTRAttributeIDTypeGlobalAttributeGeneratedCommandListID,
    ZGMTRAttributeIDTypeClusterMessagesAttributeAcceptedCommandListID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = ZGMTRAttributeIDTypeGlobalAttributeAcceptedCommandListID,
    ZGMTRAttributeIDTypeClusterMessagesAttributeAttributeListID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = ZGMTRAttributeIDTypeGlobalAttributeAttributeListID,
    ZGMTRAttributeIDTypeClusterMessagesAttributeFeatureMapID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = ZGMTRAttributeIDTypeGlobalAttributeFeatureMapID,
    ZGMTRAttributeIDTypeClusterMessagesAttributeClusterRevisionID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = ZGMTRAttributeIDTypeGlobalAttributeClusterRevisionID,

    // Cluster DeviceEnergyManagement attributes
    ZGMTRAttributeIDTypeClusterDeviceEnergyManagementAttributeESATypeID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = 0x00000000,
    ZGMTRAttributeIDTypeClusterDeviceEnergyManagementAttributeESACanGenerateID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = 0x00000001,
    ZGMTRAttributeIDTypeClusterDeviceEnergyManagementAttributeESAStateID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = 0x00000002,
    ZGMTRAttributeIDTypeClusterDeviceEnergyManagementAttributeAbsMinPowerID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = 0x00000003,
    ZGMTRAttributeIDTypeClusterDeviceEnergyManagementAttributeAbsMaxPowerID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = 0x00000004,
    ZGMTRAttributeIDTypeClusterDeviceEnergyManagementAttributePowerAdjustmentCapabilityID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = 0x00000005,
    ZGMTRAttributeIDTypeClusterDeviceEnergyManagementAttributeForecastID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = 0x00000006,
    ZGMTRAttributeIDTypeClusterDeviceEnergyManagementAttributeOptOutStateID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = 0x00000007,
    ZGMTRAttributeIDTypeClusterDeviceEnergyManagementAttributePowerRangeAdjustmentID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000008,
    ZGMTRAttributeIDTypeClusterDeviceEnergyManagementAttributeGeneratedCommandListID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = ZGMTRAttributeIDTypeGlobalAttributeGeneratedCommandListID,
    ZGMTRAttributeIDTypeClusterDeviceEnergyManagementAttributeAcceptedCommandListID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = ZGMTRAttributeIDTypeGlobalAttributeAcceptedCommandListID,
    ZGMTRAttributeIDTypeClusterDeviceEnergyManagementAttributeAttributeListID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = ZGMTRAttributeIDTypeGlobalAttributeAttributeListID,
    ZGMTRAttributeIDTypeClusterDeviceEnergyManagementAttributeFeatureMapID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = ZGMTRAttributeIDTypeGlobalAttributeFeatureMapID,
    ZGMTRAttributeIDTypeClusterDeviceEnergyManagementAttributeClusterRevisionID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = ZGMTRAttributeIDTypeGlobalAttributeClusterRevisionID,

    // Cluster EnergyEVSE attributes
    ZGMTRAttributeIDTypeClusterEnergyEVSEAttributeStateID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = 0x00000000,
    ZGMTRAttributeIDTypeClusterEnergyEVSEAttributeSupplyStateID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = 0x00000001,
    ZGMTRAttributeIDTypeClusterEnergyEVSEAttributeFaultStateID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = 0x00000002,
    ZGMTRAttributeIDTypeClusterEnergyEVSEAttributeChargingEnabledUntilID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = 0x00000003,
    ZGMTRAttributeIDTypeClusterEnergyEVSEAttributeDischargingEnabledUntilID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000004,
    ZGMTRAttributeIDTypeClusterEnergyEVSEAttributeCircuitCapacityID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = 0x00000005,
    ZGMTRAttributeIDTypeClusterEnergyEVSEAttributeMinimumChargeCurrentID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = 0x00000006,
    ZGMTRAttributeIDTypeClusterEnergyEVSEAttributeMaximumChargeCurrentID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = 0x00000007,
    ZGMTRAttributeIDTypeClusterEnergyEVSEAttributeMaximumDischargeCurrentID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000008,
    ZGMTRAttributeIDTypeClusterEnergyEVSEAttributeUserMaximumChargeCurrentID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = 0x00000009,
    ZGMTRAttributeIDTypeClusterEnergyEVSEAttributeRandomizationDelayWindowID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = 0x0000000A,
    ZGMTRAttributeIDTypeClusterEnergyEVSEAttributeNextChargeStartTimeID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = 0x00000023,
    ZGMTRAttributeIDTypeClusterEnergyEVSEAttributeNextChargeTargetTimeID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = 0x00000024,
    ZGMTRAttributeIDTypeClusterEnergyEVSEAttributeNextChargeRequiredEnergyID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = 0x00000025,
    ZGMTRAttributeIDTypeClusterEnergyEVSEAttributeNextChargeTargetSoCID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = 0x00000026,
    ZGMTRAttributeIDTypeClusterEnergyEVSEAttributeApproximateEVEfficiencyID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = 0x00000027,
    ZGMTRAttributeIDTypeClusterEnergyEVSEAttributeStateOfChargeID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000030,
    ZGMTRAttributeIDTypeClusterEnergyEVSEAttributeBatteryCapacityID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000031,
    ZGMTRAttributeIDTypeClusterEnergyEVSEAttributeVehicleIDID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000032,
    ZGMTRAttributeIDTypeClusterEnergyEVSEAttributeSessionIDID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = 0x00000040,
    ZGMTRAttributeIDTypeClusterEnergyEVSEAttributeSessionDurationID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = 0x00000041,
    ZGMTRAttributeIDTypeClusterEnergyEVSEAttributeSessionEnergyChargedID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = 0x00000042,
    ZGMTRAttributeIDTypeClusterEnergyEVSEAttributeSessionEnergyDischargedID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000043,
    ZGMTRAttributeIDTypeClusterEnergyEVSEAttributeGeneratedCommandListID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = ZGMTRAttributeIDTypeGlobalAttributeGeneratedCommandListID,
    ZGMTRAttributeIDTypeClusterEnergyEVSEAttributeAcceptedCommandListID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = ZGMTRAttributeIDTypeGlobalAttributeAcceptedCommandListID,
    ZGMTRAttributeIDTypeClusterEnergyEVSEAttributeAttributeListID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = ZGMTRAttributeIDTypeGlobalAttributeAttributeListID,
    ZGMTRAttributeIDTypeClusterEnergyEVSEAttributeFeatureMapID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = ZGMTRAttributeIDTypeGlobalAttributeFeatureMapID,
    ZGMTRAttributeIDTypeClusterEnergyEVSEAttributeClusterRevisionID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = ZGMTRAttributeIDTypeGlobalAttributeClusterRevisionID,

    // Cluster EnergyPreference attributes
    ZGMTRAttributeIDTypeClusterEnergyPreferenceAttributeEnergyBalancesID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000000,
    ZGMTRAttributeIDTypeClusterEnergyPreferenceAttributeCurrentEnergyBalanceID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000001,
    ZGMTRAttributeIDTypeClusterEnergyPreferenceAttributeEnergyPrioritiesID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000002,
    ZGMTRAttributeIDTypeClusterEnergyPreferenceAttributeLowPowerModeSensitivitiesID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000003,
    ZGMTRAttributeIDTypeClusterEnergyPreferenceAttributeCurrentLowPowerModeSensitivityID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000004,
    ZGMTRAttributeIDTypeClusterEnergyPreferenceAttributeGeneratedCommandListID ZGMTR_PROVISIONALLY_AVAILABLE = ZGMTRAttributeIDTypeGlobalAttributeGeneratedCommandListID,
    ZGMTRAttributeIDTypeClusterEnergyPreferenceAttributeAcceptedCommandListID ZGMTR_PROVISIONALLY_AVAILABLE = ZGMTRAttributeIDTypeGlobalAttributeAcceptedCommandListID,
    ZGMTRAttributeIDTypeClusterEnergyPreferenceAttributeAttributeListID ZGMTR_PROVISIONALLY_AVAILABLE = ZGMTRAttributeIDTypeGlobalAttributeAttributeListID,
    ZGMTRAttributeIDTypeClusterEnergyPreferenceAttributeFeatureMapID ZGMTR_PROVISIONALLY_AVAILABLE = ZGMTRAttributeIDTypeGlobalAttributeFeatureMapID,
    ZGMTRAttributeIDTypeClusterEnergyPreferenceAttributeClusterRevisionID ZGMTR_PROVISIONALLY_AVAILABLE = ZGMTRAttributeIDTypeGlobalAttributeClusterRevisionID,

    // Cluster PowerTopology attributes
    ZGMTRAttributeIDTypeClusterPowerTopologyAttributeAvailableEndpointsID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = 0x00000000,
    ZGMTRAttributeIDTypeClusterPowerTopologyAttributeActiveEndpointsID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = 0x00000001,
    ZGMTRAttributeIDTypeClusterPowerTopologyAttributeElectricalCircuitNodesID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000002,
    ZGMTRAttributeIDTypeClusterPowerTopologyAttributeGeneratedCommandListID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = ZGMTRAttributeIDTypeGlobalAttributeGeneratedCommandListID,
    ZGMTRAttributeIDTypeClusterPowerTopologyAttributeAcceptedCommandListID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = ZGMTRAttributeIDTypeGlobalAttributeAcceptedCommandListID,
    ZGMTRAttributeIDTypeClusterPowerTopologyAttributeAttributeListID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = ZGMTRAttributeIDTypeGlobalAttributeAttributeListID,
    ZGMTRAttributeIDTypeClusterPowerTopologyAttributeFeatureMapID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = ZGMTRAttributeIDTypeGlobalAttributeFeatureMapID,
    ZGMTRAttributeIDTypeClusterPowerTopologyAttributeClusterRevisionID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = ZGMTRAttributeIDTypeGlobalAttributeClusterRevisionID,

    // Cluster EnergyEVSEMode attributes
    ZGMTRAttributeIDTypeClusterEnergyEVSEModeAttributeSupportedModesID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = 0x00000000,
    ZGMTRAttributeIDTypeClusterEnergyEVSEModeAttributeCurrentModeID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = 0x00000001,
    ZGMTRAttributeIDTypeClusterEnergyEVSEModeAttributeGeneratedCommandListID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = ZGMTRAttributeIDTypeGlobalAttributeGeneratedCommandListID,
    ZGMTRAttributeIDTypeClusterEnergyEVSEModeAttributeAcceptedCommandListID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = ZGMTRAttributeIDTypeGlobalAttributeAcceptedCommandListID,
    ZGMTRAttributeIDTypeClusterEnergyEVSEModeAttributeAttributeListID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = ZGMTRAttributeIDTypeGlobalAttributeAttributeListID,
    ZGMTRAttributeIDTypeClusterEnergyEVSEModeAttributeFeatureMapID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = ZGMTRAttributeIDTypeGlobalAttributeFeatureMapID,
    ZGMTRAttributeIDTypeClusterEnergyEVSEModeAttributeClusterRevisionID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = ZGMTRAttributeIDTypeGlobalAttributeClusterRevisionID,

    // Cluster WaterHeaterMode attributes
    ZGMTRAttributeIDTypeClusterWaterHeaterModeAttributeSupportedModesID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = 0x00000000,
    ZGMTRAttributeIDTypeClusterWaterHeaterModeAttributeCurrentModeID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = 0x00000001,
    ZGMTRAttributeIDTypeClusterWaterHeaterModeAttributeGeneratedCommandListID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = ZGMTRAttributeIDTypeGlobalAttributeGeneratedCommandListID,
    ZGMTRAttributeIDTypeClusterWaterHeaterModeAttributeAcceptedCommandListID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = ZGMTRAttributeIDTypeGlobalAttributeAcceptedCommandListID,
    ZGMTRAttributeIDTypeClusterWaterHeaterModeAttributeAttributeListID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = ZGMTRAttributeIDTypeGlobalAttributeAttributeListID,
    ZGMTRAttributeIDTypeClusterWaterHeaterModeAttributeFeatureMapID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = ZGMTRAttributeIDTypeGlobalAttributeFeatureMapID,
    ZGMTRAttributeIDTypeClusterWaterHeaterModeAttributeClusterRevisionID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = ZGMTRAttributeIDTypeGlobalAttributeClusterRevisionID,

    // Cluster DeviceEnergyManagementMode attributes
    ZGMTRAttributeIDTypeClusterDeviceEnergyManagementModeAttributeSupportedModesID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = 0x00000000,
    ZGMTRAttributeIDTypeClusterDeviceEnergyManagementModeAttributeCurrentModeID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = 0x00000001,
    ZGMTRAttributeIDTypeClusterDeviceEnergyManagementModeAttributeGeneratedCommandListID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = ZGMTRAttributeIDTypeGlobalAttributeGeneratedCommandListID,
    ZGMTRAttributeIDTypeClusterDeviceEnergyManagementModeAttributeAcceptedCommandListID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = ZGMTRAttributeIDTypeGlobalAttributeAcceptedCommandListID,
    ZGMTRAttributeIDTypeClusterDeviceEnergyManagementModeAttributeAttributeListID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = ZGMTRAttributeIDTypeGlobalAttributeAttributeListID,
    ZGMTRAttributeIDTypeClusterDeviceEnergyManagementModeAttributeFeatureMapID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = ZGMTRAttributeIDTypeGlobalAttributeFeatureMapID,
    ZGMTRAttributeIDTypeClusterDeviceEnergyManagementModeAttributeClusterRevisionID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = ZGMTRAttributeIDTypeGlobalAttributeClusterRevisionID,

    // Cluster ElectricalGridConditions attributes
    ZGMTRAttributeIDTypeClusterElectricalGridConditionsAttributeLocalGenerationAvailableID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000000,
    ZGMTRAttributeIDTypeClusterElectricalGridConditionsAttributeCurrentConditionsID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000001,
    ZGMTRAttributeIDTypeClusterElectricalGridConditionsAttributeForecastConditionsID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000002,
    ZGMTRAttributeIDTypeClusterElectricalGridConditionsAttributeGeneratedCommandListID ZGMTR_PROVISIONALLY_AVAILABLE = ZGMTRAttributeIDTypeGlobalAttributeGeneratedCommandListID,
    ZGMTRAttributeIDTypeClusterElectricalGridConditionsAttributeAcceptedCommandListID ZGMTR_PROVISIONALLY_AVAILABLE = ZGMTRAttributeIDTypeGlobalAttributeAcceptedCommandListID,
    ZGMTRAttributeIDTypeClusterElectricalGridConditionsAttributeAttributeListID ZGMTR_PROVISIONALLY_AVAILABLE = ZGMTRAttributeIDTypeGlobalAttributeAttributeListID,
    ZGMTRAttributeIDTypeClusterElectricalGridConditionsAttributeFeatureMapID ZGMTR_PROVISIONALLY_AVAILABLE = ZGMTRAttributeIDTypeGlobalAttributeFeatureMapID,
    ZGMTRAttributeIDTypeClusterElectricalGridConditionsAttributeClusterRevisionID ZGMTR_PROVISIONALLY_AVAILABLE = ZGMTRAttributeIDTypeGlobalAttributeClusterRevisionID,

    // Cluster ElectricalAlarm attributes
    ZGMTRAttributeIDTypeClusterElectricalAlarmAttributeMaskID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000000,
    ZGMTRAttributeIDTypeClusterElectricalAlarmAttributeLatchID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000001,
    ZGMTRAttributeIDTypeClusterElectricalAlarmAttributeStateID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000002,
    ZGMTRAttributeIDTypeClusterElectricalAlarmAttributeSupportedID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000003,
    ZGMTRAttributeIDTypeClusterElectricalAlarmAttributeOverVoltageThresholdID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000080,
    ZGMTRAttributeIDTypeClusterElectricalAlarmAttributeUnderVoltageThresholdID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000081,
    ZGMTRAttributeIDTypeClusterElectricalAlarmAttributeOverFrequencyThresholdID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000082,
    ZGMTRAttributeIDTypeClusterElectricalAlarmAttributeUnderFrequencyThresholdID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000083,
    ZGMTRAttributeIDTypeClusterElectricalAlarmAttributeOverPowerThresholdID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000084,
    ZGMTRAttributeIDTypeClusterElectricalAlarmAttributeUnderPowerThresholdID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000085,
    ZGMTRAttributeIDTypeClusterElectricalAlarmAttributeOverCurrentThresholdID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000086,
    ZGMTRAttributeIDTypeClusterElectricalAlarmAttributeUnderCurrentThresholdID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000087,
    ZGMTRAttributeIDTypeClusterElectricalAlarmAttributePowerImportThresholdID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000088,
    ZGMTRAttributeIDTypeClusterElectricalAlarmAttributePowerExportThresholdID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000089,
    ZGMTRAttributeIDTypeClusterElectricalAlarmAttributeGeneratedCommandListID ZGMTR_PROVISIONALLY_AVAILABLE = ZGMTRAttributeIDTypeGlobalAttributeGeneratedCommandListID,
    ZGMTRAttributeIDTypeClusterElectricalAlarmAttributeAcceptedCommandListID ZGMTR_PROVISIONALLY_AVAILABLE = ZGMTRAttributeIDTypeGlobalAttributeAcceptedCommandListID,
    ZGMTRAttributeIDTypeClusterElectricalAlarmAttributeAttributeListID ZGMTR_PROVISIONALLY_AVAILABLE = ZGMTRAttributeIDTypeGlobalAttributeAttributeListID,
    ZGMTRAttributeIDTypeClusterElectricalAlarmAttributeFeatureMapID ZGMTR_PROVISIONALLY_AVAILABLE = ZGMTRAttributeIDTypeGlobalAttributeFeatureMapID,
    ZGMTRAttributeIDTypeClusterElectricalAlarmAttributeClusterRevisionID ZGMTR_PROVISIONALLY_AVAILABLE = ZGMTRAttributeIDTypeGlobalAttributeClusterRevisionID,

    // Cluster ElectricalDistribution attributes
    ZGMTRAttributeIDTypeClusterElectricalDistributionAttributeMaxContinuousCurrentID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000000,
    ZGMTRAttributeIDTypeClusterElectricalDistributionAttributeMaxVoltageID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000001,
    ZGMTRAttributeIDTypeClusterElectricalDistributionAttributeNumberOfPolesID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000002,
    ZGMTRAttributeIDTypeClusterElectricalDistributionAttributeEndOfLifeID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000003,
    ZGMTRAttributeIDTypeClusterElectricalDistributionAttributeServiceEntranceRatedID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000004,
    ZGMTRAttributeIDTypeClusterElectricalDistributionAttributeGeneratedCommandListID ZGMTR_PROVISIONALLY_AVAILABLE = ZGMTRAttributeIDTypeGlobalAttributeGeneratedCommandListID,
    ZGMTRAttributeIDTypeClusterElectricalDistributionAttributeAcceptedCommandListID ZGMTR_PROVISIONALLY_AVAILABLE = ZGMTRAttributeIDTypeGlobalAttributeAcceptedCommandListID,
    ZGMTRAttributeIDTypeClusterElectricalDistributionAttributeAttributeListID ZGMTR_PROVISIONALLY_AVAILABLE = ZGMTRAttributeIDTypeGlobalAttributeAttributeListID,
    ZGMTRAttributeIDTypeClusterElectricalDistributionAttributeFeatureMapID ZGMTR_PROVISIONALLY_AVAILABLE = ZGMTRAttributeIDTypeGlobalAttributeFeatureMapID,
    ZGMTRAttributeIDTypeClusterElectricalDistributionAttributeClusterRevisionID ZGMTR_PROVISIONALLY_AVAILABLE = ZGMTRAttributeIDTypeGlobalAttributeClusterRevisionID,

    // Cluster ElectricalProtectionAlarm attributes
    ZGMTRAttributeIDTypeClusterElectricalProtectionAlarmAttributeMaskID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000000,
    ZGMTRAttributeIDTypeClusterElectricalProtectionAlarmAttributeStateID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000002,
    ZGMTRAttributeIDTypeClusterElectricalProtectionAlarmAttributeSupportedID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000003,
    ZGMTRAttributeIDTypeClusterElectricalProtectionAlarmAttributeArcCauseID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000080,
    ZGMTRAttributeIDTypeClusterElectricalProtectionAlarmAttributeOverLoadRatingID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000081,
    ZGMTRAttributeIDTypeClusterElectricalProtectionAlarmAttributeOverVoltageRatingID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000082,
    ZGMTRAttributeIDTypeClusterElectricalProtectionAlarmAttributeSurgeProtectionRatingID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000083,
    ZGMTRAttributeIDTypeClusterElectricalProtectionAlarmAttributeShortCircuitRatingID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000084,
    ZGMTRAttributeIDTypeClusterElectricalProtectionAlarmAttributeResidualCurrentRatingID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000085,
    ZGMTRAttributeIDTypeClusterElectricalProtectionAlarmAttributeArcFaultRatingID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000086,
    ZGMTRAttributeIDTypeClusterElectricalProtectionAlarmAttributeGeneratedCommandListID ZGMTR_PROVISIONALLY_AVAILABLE = ZGMTRAttributeIDTypeGlobalAttributeGeneratedCommandListID,
    ZGMTRAttributeIDTypeClusterElectricalProtectionAlarmAttributeAcceptedCommandListID ZGMTR_PROVISIONALLY_AVAILABLE = ZGMTRAttributeIDTypeGlobalAttributeAcceptedCommandListID,
    ZGMTRAttributeIDTypeClusterElectricalProtectionAlarmAttributeAttributeListID ZGMTR_PROVISIONALLY_AVAILABLE = ZGMTRAttributeIDTypeGlobalAttributeAttributeListID,
    ZGMTRAttributeIDTypeClusterElectricalProtectionAlarmAttributeFeatureMapID ZGMTR_PROVISIONALLY_AVAILABLE = ZGMTRAttributeIDTypeGlobalAttributeFeatureMapID,
    ZGMTRAttributeIDTypeClusterElectricalProtectionAlarmAttributeClusterRevisionID ZGMTR_PROVISIONALLY_AVAILABLE = ZGMTRAttributeIDTypeGlobalAttributeClusterRevisionID,

    // Cluster DoorLock deprecated attribute names
    ZGMTRClusterDoorLockAttributeLockStateID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterDoorLockAttributeLockStateID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000000,
    ZGMTRClusterDoorLockAttributeLockTypeID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterDoorLockAttributeLockTypeID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000001,
    ZGMTRClusterDoorLockAttributeActuatorEnabledID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterDoorLockAttributeActuatorEnabledID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000002,
    ZGMTRClusterDoorLockAttributeDoorStateID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterDoorLockAttributeDoorStateID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000003,
    ZGMTRClusterDoorLockAttributeDoorOpenEventsID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterDoorLockAttributeDoorOpenEventsID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000004,
    ZGMTRClusterDoorLockAttributeDoorClosedEventsID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterDoorLockAttributeDoorClosedEventsID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000005,
    ZGMTRClusterDoorLockAttributeOpenPeriodID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterDoorLockAttributeOpenPeriodID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000006,
    ZGMTRClusterDoorLockAttributeNumberOfTotalUsersSupportedID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterDoorLockAttributeNumberOfTotalUsersSupportedID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000011,
    ZGMTRClusterDoorLockAttributeNumberOfPINUsersSupportedID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterDoorLockAttributeNumberOfPINUsersSupportedID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000012,
    ZGMTRClusterDoorLockAttributeNumberOfRFIDUsersSupportedID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterDoorLockAttributeNumberOfRFIDUsersSupportedID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000013,
    ZGMTRClusterDoorLockAttributeNumberOfWeekDaySchedulesSupportedPerUserID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterDoorLockAttributeNumberOfWeekDaySchedulesSupportedPerUserID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000014,
    ZGMTRClusterDoorLockAttributeNumberOfYearDaySchedulesSupportedPerUserID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterDoorLockAttributeNumberOfYearDaySchedulesSupportedPerUserID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000015,
    ZGMTRClusterDoorLockAttributeNumberOfHolidaySchedulesSupportedID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterDoorLockAttributeNumberOfHolidaySchedulesSupportedID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000016,
    ZGMTRClusterDoorLockAttributeMaxPINCodeLengthID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterDoorLockAttributeMaxPINCodeLengthID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000017,
    ZGMTRClusterDoorLockAttributeMinPINCodeLengthID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterDoorLockAttributeMinPINCodeLengthID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000018,
    ZGMTRClusterDoorLockAttributeMaxRFIDCodeLengthID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterDoorLockAttributeMaxRFIDCodeLengthID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000019,
    ZGMTRClusterDoorLockAttributeMinRFIDCodeLengthID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterDoorLockAttributeMinRFIDCodeLengthID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x0000001A,
    ZGMTRClusterDoorLockAttributeCredentialRulesSupportID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterDoorLockAttributeCredentialRulesSupportID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x0000001B,
    ZGMTRClusterDoorLockAttributeNumberOfCredentialsSupportedPerUserID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterDoorLockAttributeNumberOfCredentialsSupportedPerUserID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x0000001C,
    ZGMTRClusterDoorLockAttributeLanguageID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterDoorLockAttributeLanguageID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000021,
    ZGMTRClusterDoorLockAttributeLEDSettingsID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterDoorLockAttributeLEDSettingsID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000022,
    ZGMTRClusterDoorLockAttributeAutoRelockTimeID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterDoorLockAttributeAutoRelockTimeID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000023,
    ZGMTRClusterDoorLockAttributeSoundVolumeID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterDoorLockAttributeSoundVolumeID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000024,
    ZGMTRClusterDoorLockAttributeOperatingModeID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterDoorLockAttributeOperatingModeID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000025,
    ZGMTRClusterDoorLockAttributeSupportedOperatingModesID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterDoorLockAttributeSupportedOperatingModesID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000026,
    ZGMTRClusterDoorLockAttributeDefaultConfigurationRegisterID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterDoorLockAttributeDefaultConfigurationRegisterID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000027,
    ZGMTRClusterDoorLockAttributeEnableLocalProgrammingID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterDoorLockAttributeEnableLocalProgrammingID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000028,
    ZGMTRClusterDoorLockAttributeEnableOneTouchLockingID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterDoorLockAttributeEnableOneTouchLockingID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000029,
    ZGMTRClusterDoorLockAttributeEnableInsideStatusLEDID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterDoorLockAttributeEnableInsideStatusLEDID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x0000002A,
    ZGMTRClusterDoorLockAttributeEnablePrivacyModeButtonID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterDoorLockAttributeEnablePrivacyModeButtonID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x0000002B,
    ZGMTRClusterDoorLockAttributeLocalProgrammingFeaturesID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterDoorLockAttributeLocalProgrammingFeaturesID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x0000002C,
    ZGMTRClusterDoorLockAttributeWrongCodeEntryLimitID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterDoorLockAttributeWrongCodeEntryLimitID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000030,
    ZGMTRClusterDoorLockAttributeUserCodeTemporaryDisableTimeID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterDoorLockAttributeUserCodeTemporaryDisableTimeID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000031,
    ZGMTRClusterDoorLockAttributeSendPINOverTheAirID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterDoorLockAttributeSendPINOverTheAirID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000032,
    ZGMTRClusterDoorLockAttributeRequirePINforRemoteOperationID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterDoorLockAttributeRequirePINforRemoteOperationID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000033,
    ZGMTRClusterDoorLockAttributeExpiringUserTimeoutID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterDoorLockAttributeExpiringUserTimeoutID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000035,
    ZGMTRClusterDoorLockAttributeGeneratedCommandListID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterDoorLockAttributeGeneratedCommandListID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = ZGMTRClusterGlobalAttributeGeneratedCommandListID,
    ZGMTRClusterDoorLockAttributeAcceptedCommandListID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterDoorLockAttributeAcceptedCommandListID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = ZGMTRClusterGlobalAttributeAcceptedCommandListID,
    ZGMTRClusterDoorLockAttributeAttributeListID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterDoorLockAttributeAttributeListID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = ZGMTRClusterGlobalAttributeAttributeListID,
    ZGMTRClusterDoorLockAttributeFeatureMapID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterDoorLockAttributeFeatureMapID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = ZGMTRClusterGlobalAttributeFeatureMapID,
    ZGMTRClusterDoorLockAttributeClusterRevisionID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterDoorLockAttributeClusterRevisionID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = ZGMTRClusterGlobalAttributeClusterRevisionID,

    // Cluster DoorLock attributes
    ZGMTRAttributeIDTypeClusterDoorLockAttributeLockStateID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000000,
    ZGMTRAttributeIDTypeClusterDoorLockAttributeLockTypeID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000001,
    ZGMTRAttributeIDTypeClusterDoorLockAttributeActuatorEnabledID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000002,
    ZGMTRAttributeIDTypeClusterDoorLockAttributeDoorStateID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000003,
    ZGMTRAttributeIDTypeClusterDoorLockAttributeDoorOpenEventsID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000004,
    ZGMTRAttributeIDTypeClusterDoorLockAttributeDoorClosedEventsID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000005,
    ZGMTRAttributeIDTypeClusterDoorLockAttributeOpenPeriodID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000006,
    ZGMTRAttributeIDTypeClusterDoorLockAttributeNumberOfTotalUsersSupportedID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000011,
    ZGMTRAttributeIDTypeClusterDoorLockAttributeNumberOfPINUsersSupportedID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000012,
    ZGMTRAttributeIDTypeClusterDoorLockAttributeNumberOfRFIDUsersSupportedID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000013,
    ZGMTRAttributeIDTypeClusterDoorLockAttributeNumberOfWeekDaySchedulesSupportedPerUserID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000014,
    ZGMTRAttributeIDTypeClusterDoorLockAttributeNumberOfYearDaySchedulesSupportedPerUserID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000015,
    ZGMTRAttributeIDTypeClusterDoorLockAttributeNumberOfHolidaySchedulesSupportedID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000016,
    ZGMTRAttributeIDTypeClusterDoorLockAttributeMaxPINCodeLengthID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000017,
    ZGMTRAttributeIDTypeClusterDoorLockAttributeMinPINCodeLengthID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000018,
    ZGMTRAttributeIDTypeClusterDoorLockAttributeMaxRFIDCodeLengthID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000019,
    ZGMTRAttributeIDTypeClusterDoorLockAttributeMinRFIDCodeLengthID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x0000001A,
    ZGMTRAttributeIDTypeClusterDoorLockAttributeCredentialRulesSupportID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x0000001B,
    ZGMTRAttributeIDTypeClusterDoorLockAttributeNumberOfCredentialsSupportedPerUserID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x0000001C,
    ZGMTRAttributeIDTypeClusterDoorLockAttributeLanguageID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000021,
    ZGMTRAttributeIDTypeClusterDoorLockAttributeLEDSettingsID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000022,
    ZGMTRAttributeIDTypeClusterDoorLockAttributeAutoRelockTimeID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000023,
    ZGMTRAttributeIDTypeClusterDoorLockAttributeSoundVolumeID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000024,
    ZGMTRAttributeIDTypeClusterDoorLockAttributeOperatingModeID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000025,
    ZGMTRAttributeIDTypeClusterDoorLockAttributeSupportedOperatingModesID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000026,
    ZGMTRAttributeIDTypeClusterDoorLockAttributeDefaultConfigurationRegisterID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000027,
    ZGMTRAttributeIDTypeClusterDoorLockAttributeEnableLocalProgrammingID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000028,
    ZGMTRAttributeIDTypeClusterDoorLockAttributeEnableOneTouchLockingID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000029,
    ZGMTRAttributeIDTypeClusterDoorLockAttributeEnableInsideStatusLEDID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x0000002A,
    ZGMTRAttributeIDTypeClusterDoorLockAttributeEnablePrivacyModeButtonID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x0000002B,
    ZGMTRAttributeIDTypeClusterDoorLockAttributeLocalProgrammingFeaturesID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x0000002C,
    ZGMTRAttributeIDTypeClusterDoorLockAttributeWrongCodeEntryLimitID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000030,
    ZGMTRAttributeIDTypeClusterDoorLockAttributeUserCodeTemporaryDisableTimeID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000031,
    ZGMTRAttributeIDTypeClusterDoorLockAttributeSendPINOverTheAirID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000032,
    ZGMTRAttributeIDTypeClusterDoorLockAttributeRequirePINforRemoteOperationID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000033,
    ZGMTRAttributeIDTypeClusterDoorLockAttributeExpiringUserTimeoutID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000035,
    ZGMTRAttributeIDTypeClusterDoorLockAttributeAliroReaderVerificationKeyID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = 0x00000080,
    ZGMTRAttributeIDTypeClusterDoorLockAttributeAliroReaderGroupIdentifierID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = 0x00000081,
    ZGMTRAttributeIDTypeClusterDoorLockAttributeAliroReaderGroupSubIdentifierID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = 0x00000082,
    ZGMTRAttributeIDTypeClusterDoorLockAttributeAliroExpeditedTransactionSupportedProtocolVersionsID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = 0x00000083,
    ZGMTRAttributeIDTypeClusterDoorLockAttributeAliroGroupResolvingKeyID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = 0x00000084,
    ZGMTRAttributeIDTypeClusterDoorLockAttributeAliroSupportedBLEUWBProtocolVersionsID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = 0x00000085,
    ZGMTRAttributeIDTypeClusterDoorLockAttributeAliroBLEAdvertisingVersionID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = 0x00000086,
    ZGMTRAttributeIDTypeClusterDoorLockAttributeNumberOfAliroCredentialIssuerKeysSupportedID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = 0x00000087,
    ZGMTRAttributeIDTypeClusterDoorLockAttributeNumberOfAliroEndpointKeysSupportedID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = 0x00000088,
    ZGMTRAttributeIDTypeClusterDoorLockAttributeGeneratedCommandListID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = ZGMTRAttributeIDTypeGlobalAttributeGeneratedCommandListID,
    ZGMTRAttributeIDTypeClusterDoorLockAttributeAcceptedCommandListID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = ZGMTRAttributeIDTypeGlobalAttributeAcceptedCommandListID,
    ZGMTRAttributeIDTypeClusterDoorLockAttributeAttributeListID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = ZGMTRAttributeIDTypeGlobalAttributeAttributeListID,
    ZGMTRAttributeIDTypeClusterDoorLockAttributeFeatureMapID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = ZGMTRAttributeIDTypeGlobalAttributeFeatureMapID,
    ZGMTRAttributeIDTypeClusterDoorLockAttributeClusterRevisionID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = ZGMTRAttributeIDTypeGlobalAttributeClusterRevisionID,

    // Cluster WindowCovering deprecated attribute names
    ZGMTRClusterWindowCoveringAttributeTypeID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterWindowCoveringAttributeTypeID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000000,
    ZGMTRClusterWindowCoveringAttributePhysicalClosedLimitLiftID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterWindowCoveringAttributePhysicalClosedLimitLiftID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000001,
    ZGMTRClusterWindowCoveringAttributePhysicalClosedLimitTiltID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterWindowCoveringAttributePhysicalClosedLimitTiltID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000002,
    ZGMTRClusterWindowCoveringAttributeCurrentPositionLiftID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterWindowCoveringAttributeCurrentPositionLiftID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000003,
    ZGMTRClusterWindowCoveringAttributeCurrentPositionTiltID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterWindowCoveringAttributeCurrentPositionTiltID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000004,
    ZGMTRClusterWindowCoveringAttributeNumberOfActuationsLiftID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterWindowCoveringAttributeNumberOfActuationsLiftID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000005,
    ZGMTRClusterWindowCoveringAttributeNumberOfActuationsTiltID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterWindowCoveringAttributeNumberOfActuationsTiltID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000006,
    ZGMTRClusterWindowCoveringAttributeConfigStatusID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterWindowCoveringAttributeConfigStatusID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000007,
    ZGMTRClusterWindowCoveringAttributeCurrentPositionLiftPercentageID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterWindowCoveringAttributeCurrentPositionLiftPercentageID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000008,
    ZGMTRClusterWindowCoveringAttributeCurrentPositionTiltPercentageID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterWindowCoveringAttributeCurrentPositionTiltPercentageID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000009,
    ZGMTRClusterWindowCoveringAttributeOperationalStatusID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterWindowCoveringAttributeOperationalStatusID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x0000000A,
    ZGMTRClusterWindowCoveringAttributeTargetPositionLiftPercent100thsID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterWindowCoveringAttributeTargetPositionLiftPercent100thsID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x0000000B,
    ZGMTRClusterWindowCoveringAttributeTargetPositionTiltPercent100thsID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterWindowCoveringAttributeTargetPositionTiltPercent100thsID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x0000000C,
    ZGMTRClusterWindowCoveringAttributeEndProductTypeID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterWindowCoveringAttributeEndProductTypeID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x0000000D,
    ZGMTRClusterWindowCoveringAttributeCurrentPositionLiftPercent100thsID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterWindowCoveringAttributeCurrentPositionLiftPercent100thsID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x0000000E,
    ZGMTRClusterWindowCoveringAttributeCurrentPositionTiltPercent100thsID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterWindowCoveringAttributeCurrentPositionTiltPercent100thsID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x0000000F,
    ZGMTRClusterWindowCoveringAttributeInstalledOpenLimitLiftID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterWindowCoveringAttributeInstalledOpenLimitLiftID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000010,
    ZGMTRClusterWindowCoveringAttributeInstalledClosedLimitLiftID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterWindowCoveringAttributeInstalledClosedLimitLiftID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000011,
    ZGMTRClusterWindowCoveringAttributeInstalledOpenLimitTiltID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterWindowCoveringAttributeInstalledOpenLimitTiltID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000012,
    ZGMTRClusterWindowCoveringAttributeInstalledClosedLimitTiltID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterWindowCoveringAttributeInstalledClosedLimitTiltID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000013,
    ZGMTRClusterWindowCoveringAttributeModeID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterWindowCoveringAttributeModeID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000017,
    ZGMTRClusterWindowCoveringAttributeSafetyStatusID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterWindowCoveringAttributeSafetyStatusID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x0000001A,
    ZGMTRClusterWindowCoveringAttributeGeneratedCommandListID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterWindowCoveringAttributeGeneratedCommandListID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = ZGMTRClusterGlobalAttributeGeneratedCommandListID,
    ZGMTRClusterWindowCoveringAttributeAcceptedCommandListID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterWindowCoveringAttributeAcceptedCommandListID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = ZGMTRClusterGlobalAttributeAcceptedCommandListID,
    ZGMTRClusterWindowCoveringAttributeAttributeListID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterWindowCoveringAttributeAttributeListID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = ZGMTRClusterGlobalAttributeAttributeListID,
    ZGMTRClusterWindowCoveringAttributeFeatureMapID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterWindowCoveringAttributeFeatureMapID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = ZGMTRClusterGlobalAttributeFeatureMapID,
    ZGMTRClusterWindowCoveringAttributeClusterRevisionID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterWindowCoveringAttributeClusterRevisionID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = ZGMTRClusterGlobalAttributeClusterRevisionID,

    // Cluster WindowCovering attributes
    ZGMTRAttributeIDTypeClusterWindowCoveringAttributeTypeID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000000,
    ZGMTRAttributeIDTypeClusterWindowCoveringAttributePhysicalClosedLimitLiftID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000001,
    ZGMTRAttributeIDTypeClusterWindowCoveringAttributePhysicalClosedLimitTiltID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000002,
    ZGMTRAttributeIDTypeClusterWindowCoveringAttributeCurrentPositionLiftID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000003,
    ZGMTRAttributeIDTypeClusterWindowCoveringAttributeCurrentPositionTiltID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000004,
    ZGMTRAttributeIDTypeClusterWindowCoveringAttributeNumberOfActuationsLiftID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000005,
    ZGMTRAttributeIDTypeClusterWindowCoveringAttributeNumberOfActuationsTiltID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000006,
    ZGMTRAttributeIDTypeClusterWindowCoveringAttributeConfigStatusID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000007,
    ZGMTRAttributeIDTypeClusterWindowCoveringAttributeCurrentPositionLiftPercentageID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000008,
    ZGMTRAttributeIDTypeClusterWindowCoveringAttributeCurrentPositionTiltPercentageID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000009,
    ZGMTRAttributeIDTypeClusterWindowCoveringAttributeOperationalStatusID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x0000000A,
    ZGMTRAttributeIDTypeClusterWindowCoveringAttributeTargetPositionLiftPercent100thsID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x0000000B,
    ZGMTRAttributeIDTypeClusterWindowCoveringAttributeTargetPositionTiltPercent100thsID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x0000000C,
    ZGMTRAttributeIDTypeClusterWindowCoveringAttributeEndProductTypeID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x0000000D,
    ZGMTRAttributeIDTypeClusterWindowCoveringAttributeCurrentPositionLiftPercent100thsID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x0000000E,
    ZGMTRAttributeIDTypeClusterWindowCoveringAttributeCurrentPositionTiltPercent100thsID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x0000000F,
    ZGMTRAttributeIDTypeClusterWindowCoveringAttributeInstalledOpenLimitLiftID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000010,
    ZGMTRAttributeIDTypeClusterWindowCoveringAttributeInstalledClosedLimitLiftID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000011,
    ZGMTRAttributeIDTypeClusterWindowCoveringAttributeInstalledOpenLimitTiltID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000012,
    ZGMTRAttributeIDTypeClusterWindowCoveringAttributeInstalledClosedLimitTiltID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000013,
    ZGMTRAttributeIDTypeClusterWindowCoveringAttributeModeID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000017,
    ZGMTRAttributeIDTypeClusterWindowCoveringAttributeSafetyStatusID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x0000001A,
    ZGMTRAttributeIDTypeClusterWindowCoveringAttributeGeneratedCommandListID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = ZGMTRAttributeIDTypeGlobalAttributeGeneratedCommandListID,
    ZGMTRAttributeIDTypeClusterWindowCoveringAttributeAcceptedCommandListID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = ZGMTRAttributeIDTypeGlobalAttributeAcceptedCommandListID,
    ZGMTRAttributeIDTypeClusterWindowCoveringAttributeAttributeListID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = ZGMTRAttributeIDTypeGlobalAttributeAttributeListID,
    ZGMTRAttributeIDTypeClusterWindowCoveringAttributeFeatureMapID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = ZGMTRAttributeIDTypeGlobalAttributeFeatureMapID,
    ZGMTRAttributeIDTypeClusterWindowCoveringAttributeClusterRevisionID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = ZGMTRAttributeIDTypeGlobalAttributeClusterRevisionID,

    // Cluster ClosureControl attributes
    ZGMTRAttributeIDTypeClusterClosureControlAttributeCountdownTimeID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000000,
    ZGMTRAttributeIDTypeClusterClosureControlAttributeMainStateID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000001,
    ZGMTRAttributeIDTypeClusterClosureControlAttributeCurrentErrorListID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000002,
    ZGMTRAttributeIDTypeClusterClosureControlAttributeOverallCurrentStateID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000003,
    ZGMTRAttributeIDTypeClusterClosureControlAttributeOverallTargetStateID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000004,
    ZGMTRAttributeIDTypeClusterClosureControlAttributeLatchControlModesID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000005,
    ZGMTRAttributeIDTypeClusterClosureControlAttributeGeneratedCommandListID ZGMTR_PROVISIONALLY_AVAILABLE = ZGMTRAttributeIDTypeGlobalAttributeGeneratedCommandListID,
    ZGMTRAttributeIDTypeClusterClosureControlAttributeAcceptedCommandListID ZGMTR_PROVISIONALLY_AVAILABLE = ZGMTRAttributeIDTypeGlobalAttributeAcceptedCommandListID,
    ZGMTRAttributeIDTypeClusterClosureControlAttributeAttributeListID ZGMTR_PROVISIONALLY_AVAILABLE = ZGMTRAttributeIDTypeGlobalAttributeAttributeListID,
    ZGMTRAttributeIDTypeClusterClosureControlAttributeFeatureMapID ZGMTR_PROVISIONALLY_AVAILABLE = ZGMTRAttributeIDTypeGlobalAttributeFeatureMapID,
    ZGMTRAttributeIDTypeClusterClosureControlAttributeClusterRevisionID ZGMTR_PROVISIONALLY_AVAILABLE = ZGMTRAttributeIDTypeGlobalAttributeClusterRevisionID,

    // Cluster ClosureDimension attributes
    ZGMTRAttributeIDTypeClusterClosureDimensionAttributeCurrentStateID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000000,
    ZGMTRAttributeIDTypeClusterClosureDimensionAttributeTargetStateID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000001,
    ZGMTRAttributeIDTypeClusterClosureDimensionAttributeResolutionID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000002,
    ZGMTRAttributeIDTypeClusterClosureDimensionAttributeStepValueID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000003,
    ZGMTRAttributeIDTypeClusterClosureDimensionAttributeUnitID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000004,
    ZGMTRAttributeIDTypeClusterClosureDimensionAttributeUnitRangeID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000005,
    ZGMTRAttributeIDTypeClusterClosureDimensionAttributeLimitRangeID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000006,
    ZGMTRAttributeIDTypeClusterClosureDimensionAttributeTranslationDirectionID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000007,
    ZGMTRAttributeIDTypeClusterClosureDimensionAttributeRotationAxisID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000008,
    ZGMTRAttributeIDTypeClusterClosureDimensionAttributeOverflowID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000009,
    ZGMTRAttributeIDTypeClusterClosureDimensionAttributeModulationTypeID ZGMTR_PROVISIONALLY_AVAILABLE = 0x0000000A,
    ZGMTRAttributeIDTypeClusterClosureDimensionAttributeLatchControlModesID ZGMTR_PROVISIONALLY_AVAILABLE = 0x0000000B,
    ZGMTRAttributeIDTypeClusterClosureDimensionAttributeGeneratedCommandListID ZGMTR_PROVISIONALLY_AVAILABLE = ZGMTRAttributeIDTypeGlobalAttributeGeneratedCommandListID,
    ZGMTRAttributeIDTypeClusterClosureDimensionAttributeAcceptedCommandListID ZGMTR_PROVISIONALLY_AVAILABLE = ZGMTRAttributeIDTypeGlobalAttributeAcceptedCommandListID,
    ZGMTRAttributeIDTypeClusterClosureDimensionAttributeAttributeListID ZGMTR_PROVISIONALLY_AVAILABLE = ZGMTRAttributeIDTypeGlobalAttributeAttributeListID,
    ZGMTRAttributeIDTypeClusterClosureDimensionAttributeFeatureMapID ZGMTR_PROVISIONALLY_AVAILABLE = ZGMTRAttributeIDTypeGlobalAttributeFeatureMapID,
    ZGMTRAttributeIDTypeClusterClosureDimensionAttributeClusterRevisionID ZGMTR_PROVISIONALLY_AVAILABLE = ZGMTRAttributeIDTypeGlobalAttributeClusterRevisionID,

    // Cluster ServiceArea attributes
    ZGMTRAttributeIDTypeClusterServiceAreaAttributeSupportedAreasID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = 0x00000000,
    ZGMTRAttributeIDTypeClusterServiceAreaAttributeSupportedMapsID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = 0x00000001,
    ZGMTRAttributeIDTypeClusterServiceAreaAttributeSelectedAreasID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = 0x00000002,
    ZGMTRAttributeIDTypeClusterServiceAreaAttributeCurrentAreaID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = 0x00000003,
    ZGMTRAttributeIDTypeClusterServiceAreaAttributeEstimatedEndTimeID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = 0x00000004,
    ZGMTRAttributeIDTypeClusterServiceAreaAttributeProgressID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = 0x00000005,
    ZGMTRAttributeIDTypeClusterServiceAreaAttributeGeneratedCommandListID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = ZGMTRAttributeIDTypeGlobalAttributeGeneratedCommandListID,
    ZGMTRAttributeIDTypeClusterServiceAreaAttributeAcceptedCommandListID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = ZGMTRAttributeIDTypeGlobalAttributeAcceptedCommandListID,
    ZGMTRAttributeIDTypeClusterServiceAreaAttributeAttributeListID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = ZGMTRAttributeIDTypeGlobalAttributeAttributeListID,
    ZGMTRAttributeIDTypeClusterServiceAreaAttributeFeatureMapID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = ZGMTRAttributeIDTypeGlobalAttributeFeatureMapID,
    ZGMTRAttributeIDTypeClusterServiceAreaAttributeClusterRevisionID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = ZGMTRAttributeIDTypeGlobalAttributeClusterRevisionID,

    // Cluster PumpConfigurationAndControl deprecated attribute names
    ZGMTRClusterPumpConfigurationAndControlAttributeMaxPressureID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterPumpConfigurationAndControlAttributeMaxPressureID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000000,
    ZGMTRClusterPumpConfigurationAndControlAttributeMaxSpeedID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterPumpConfigurationAndControlAttributeMaxSpeedID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000001,
    ZGMTRClusterPumpConfigurationAndControlAttributeMaxFlowID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterPumpConfigurationAndControlAttributeMaxFlowID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000002,
    ZGMTRClusterPumpConfigurationAndControlAttributeMinConstPressureID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterPumpConfigurationAndControlAttributeMinConstPressureID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000003,
    ZGMTRClusterPumpConfigurationAndControlAttributeMaxConstPressureID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterPumpConfigurationAndControlAttributeMaxConstPressureID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000004,
    ZGMTRClusterPumpConfigurationAndControlAttributeMinCompPressureID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterPumpConfigurationAndControlAttributeMinCompPressureID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000005,
    ZGMTRClusterPumpConfigurationAndControlAttributeMaxCompPressureID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterPumpConfigurationAndControlAttributeMaxCompPressureID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000006,
    ZGMTRClusterPumpConfigurationAndControlAttributeMinConstSpeedID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterPumpConfigurationAndControlAttributeMinConstSpeedID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000007,
    ZGMTRClusterPumpConfigurationAndControlAttributeMaxConstSpeedID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterPumpConfigurationAndControlAttributeMaxConstSpeedID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000008,
    ZGMTRClusterPumpConfigurationAndControlAttributeMinConstFlowID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterPumpConfigurationAndControlAttributeMinConstFlowID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000009,
    ZGMTRClusterPumpConfigurationAndControlAttributeMaxConstFlowID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterPumpConfigurationAndControlAttributeMaxConstFlowID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x0000000A,
    ZGMTRClusterPumpConfigurationAndControlAttributeMinConstTempID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterPumpConfigurationAndControlAttributeMinConstTempID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x0000000B,
    ZGMTRClusterPumpConfigurationAndControlAttributeMaxConstTempID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterPumpConfigurationAndControlAttributeMaxConstTempID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x0000000C,
    ZGMTRClusterPumpConfigurationAndControlAttributePumpStatusID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterPumpConfigurationAndControlAttributePumpStatusID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000010,
    ZGMTRClusterPumpConfigurationAndControlAttributeEffectiveOperationModeID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterPumpConfigurationAndControlAttributeEffectiveOperationModeID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000011,
    ZGMTRClusterPumpConfigurationAndControlAttributeEffectiveControlModeID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterPumpConfigurationAndControlAttributeEffectiveControlModeID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000012,
    ZGMTRClusterPumpConfigurationAndControlAttributeCapacityID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterPumpConfigurationAndControlAttributeCapacityID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000013,
    ZGMTRClusterPumpConfigurationAndControlAttributeSpeedID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterPumpConfigurationAndControlAttributeSpeedID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000014,
    ZGMTRClusterPumpConfigurationAndControlAttributeLifetimeRunningHoursID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterPumpConfigurationAndControlAttributeLifetimeRunningHoursID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000015,
    ZGMTRClusterPumpConfigurationAndControlAttributePowerID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterPumpConfigurationAndControlAttributePowerID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000016,
    ZGMTRClusterPumpConfigurationAndControlAttributeLifetimeEnergyConsumedID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterPumpConfigurationAndControlAttributeLifetimeEnergyConsumedID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000017,
    ZGMTRClusterPumpConfigurationAndControlAttributeOperationModeID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterPumpConfigurationAndControlAttributeOperationModeID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000020,
    ZGMTRClusterPumpConfigurationAndControlAttributeControlModeID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterPumpConfigurationAndControlAttributeControlModeID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000021,
    ZGMTRClusterPumpConfigurationAndControlAttributeGeneratedCommandListID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterPumpConfigurationAndControlAttributeGeneratedCommandListID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = ZGMTRClusterGlobalAttributeGeneratedCommandListID,
    ZGMTRClusterPumpConfigurationAndControlAttributeAcceptedCommandListID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterPumpConfigurationAndControlAttributeAcceptedCommandListID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = ZGMTRClusterGlobalAttributeAcceptedCommandListID,
    ZGMTRClusterPumpConfigurationAndControlAttributeAttributeListID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterPumpConfigurationAndControlAttributeAttributeListID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = ZGMTRClusterGlobalAttributeAttributeListID,
    ZGMTRClusterPumpConfigurationAndControlAttributeFeatureMapID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterPumpConfigurationAndControlAttributeFeatureMapID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = ZGMTRClusterGlobalAttributeFeatureMapID,
    ZGMTRClusterPumpConfigurationAndControlAttributeClusterRevisionID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterPumpConfigurationAndControlAttributeClusterRevisionID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = ZGMTRClusterGlobalAttributeClusterRevisionID,

    // Cluster PumpConfigurationAndControl attributes
    ZGMTRAttributeIDTypeClusterPumpConfigurationAndControlAttributeMaxPressureID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000000,
    ZGMTRAttributeIDTypeClusterPumpConfigurationAndControlAttributeMaxSpeedID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000001,
    ZGMTRAttributeIDTypeClusterPumpConfigurationAndControlAttributeMaxFlowID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000002,
    ZGMTRAttributeIDTypeClusterPumpConfigurationAndControlAttributeMinConstPressureID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000003,
    ZGMTRAttributeIDTypeClusterPumpConfigurationAndControlAttributeMaxConstPressureID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000004,
    ZGMTRAttributeIDTypeClusterPumpConfigurationAndControlAttributeMinCompPressureID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000005,
    ZGMTRAttributeIDTypeClusterPumpConfigurationAndControlAttributeMaxCompPressureID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000006,
    ZGMTRAttributeIDTypeClusterPumpConfigurationAndControlAttributeMinConstSpeedID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000007,
    ZGMTRAttributeIDTypeClusterPumpConfigurationAndControlAttributeMaxConstSpeedID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000008,
    ZGMTRAttributeIDTypeClusterPumpConfigurationAndControlAttributeMinConstFlowID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000009,
    ZGMTRAttributeIDTypeClusterPumpConfigurationAndControlAttributeMaxConstFlowID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x0000000A,
    ZGMTRAttributeIDTypeClusterPumpConfigurationAndControlAttributeMinConstTempID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x0000000B,
    ZGMTRAttributeIDTypeClusterPumpConfigurationAndControlAttributeMaxConstTempID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x0000000C,
    ZGMTRAttributeIDTypeClusterPumpConfigurationAndControlAttributePumpStatusID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000010,
    ZGMTRAttributeIDTypeClusterPumpConfigurationAndControlAttributeEffectiveOperationModeID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000011,
    ZGMTRAttributeIDTypeClusterPumpConfigurationAndControlAttributeEffectiveControlModeID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000012,
    ZGMTRAttributeIDTypeClusterPumpConfigurationAndControlAttributeCapacityID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000013,
    ZGMTRAttributeIDTypeClusterPumpConfigurationAndControlAttributeSpeedID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000014,
    ZGMTRAttributeIDTypeClusterPumpConfigurationAndControlAttributeLifetimeRunningHoursID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000015,
    ZGMTRAttributeIDTypeClusterPumpConfigurationAndControlAttributePowerID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000016,
    ZGMTRAttributeIDTypeClusterPumpConfigurationAndControlAttributeLifetimeEnergyConsumedID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000017,
    ZGMTRAttributeIDTypeClusterPumpConfigurationAndControlAttributeOperationModeID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000020,
    ZGMTRAttributeIDTypeClusterPumpConfigurationAndControlAttributeControlModeID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000021,
    ZGMTRAttributeIDTypeClusterPumpConfigurationAndControlAttributeGeneratedCommandListID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = ZGMTRAttributeIDTypeGlobalAttributeGeneratedCommandListID,
    ZGMTRAttributeIDTypeClusterPumpConfigurationAndControlAttributeAcceptedCommandListID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = ZGMTRAttributeIDTypeGlobalAttributeAcceptedCommandListID,
    ZGMTRAttributeIDTypeClusterPumpConfigurationAndControlAttributeAttributeListID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = ZGMTRAttributeIDTypeGlobalAttributeAttributeListID,
    ZGMTRAttributeIDTypeClusterPumpConfigurationAndControlAttributeFeatureMapID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = ZGMTRAttributeIDTypeGlobalAttributeFeatureMapID,
    ZGMTRAttributeIDTypeClusterPumpConfigurationAndControlAttributeClusterRevisionID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = ZGMTRAttributeIDTypeGlobalAttributeClusterRevisionID,

    // Cluster Thermostat deprecated attribute names
    ZGMTRClusterThermostatAttributeLocalTemperatureID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterThermostatAttributeLocalTemperatureID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000000,
    ZGMTRClusterThermostatAttributeOutdoorTemperatureID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterThermostatAttributeOutdoorTemperatureID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000001,
    ZGMTRClusterThermostatAttributeOccupancyID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterThermostatAttributeOccupancyID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000002,
    ZGMTRClusterThermostatAttributeAbsMinHeatSetpointLimitID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterThermostatAttributeAbsMinHeatSetpointLimitID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000003,
    ZGMTRClusterThermostatAttributeAbsMaxHeatSetpointLimitID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterThermostatAttributeAbsMaxHeatSetpointLimitID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000004,
    ZGMTRClusterThermostatAttributeAbsMinCoolSetpointLimitID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterThermostatAttributeAbsMinCoolSetpointLimitID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000005,
    ZGMTRClusterThermostatAttributeAbsMaxCoolSetpointLimitID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterThermostatAttributeAbsMaxCoolSetpointLimitID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000006,
    ZGMTRClusterThermostatAttributePICoolingDemandID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterThermostatAttributePICoolingDemandID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000007,
    ZGMTRClusterThermostatAttributePIHeatingDemandID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterThermostatAttributePIHeatingDemandID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000008,
    ZGMTRClusterThermostatAttributeHVACSystemTypeConfigurationID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterThermostatAttributeHVACSystemTypeConfigurationID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000009,
    ZGMTRClusterThermostatAttributeLocalTemperatureCalibrationID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterThermostatAttributeLocalTemperatureCalibrationID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000010,
    ZGMTRClusterThermostatAttributeOccupiedCoolingSetpointID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterThermostatAttributeOccupiedCoolingSetpointID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000011,
    ZGMTRClusterThermostatAttributeOccupiedHeatingSetpointID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterThermostatAttributeOccupiedHeatingSetpointID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000012,
    ZGMTRClusterThermostatAttributeUnoccupiedCoolingSetpointID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterThermostatAttributeUnoccupiedCoolingSetpointID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000013,
    ZGMTRClusterThermostatAttributeUnoccupiedHeatingSetpointID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterThermostatAttributeUnoccupiedHeatingSetpointID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000014,
    ZGMTRClusterThermostatAttributeMinHeatSetpointLimitID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterThermostatAttributeMinHeatSetpointLimitID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000015,
    ZGMTRClusterThermostatAttributeMaxHeatSetpointLimitID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterThermostatAttributeMaxHeatSetpointLimitID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000016,
    ZGMTRClusterThermostatAttributeMinCoolSetpointLimitID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterThermostatAttributeMinCoolSetpointLimitID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000017,
    ZGMTRClusterThermostatAttributeMaxCoolSetpointLimitID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterThermostatAttributeMaxCoolSetpointLimitID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000018,
    ZGMTRClusterThermostatAttributeMinSetpointDeadBandID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterThermostatAttributeMinSetpointDeadBandID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000019,
    ZGMTRClusterThermostatAttributeRemoteSensingID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterThermostatAttributeRemoteSensingID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x0000001A,
    ZGMTRClusterThermostatAttributeControlSequenceOfOperationID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterThermostatAttributeControlSequenceOfOperationID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x0000001B,
    ZGMTRClusterThermostatAttributeSystemModeID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterThermostatAttributeSystemModeID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x0000001C,
    ZGMTRClusterThermostatAttributeThermostatRunningModeID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterThermostatAttributeThermostatRunningModeID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x0000001E,
    ZGMTRClusterThermostatAttributeStartOfWeekID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterThermostatAttributeStartOfWeekID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000020,
    ZGMTRClusterThermostatAttributeNumberOfWeeklyTransitionsID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterThermostatAttributeNumberOfWeeklyTransitionsID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000021,
    ZGMTRClusterThermostatAttributeNumberOfDailyTransitionsID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterThermostatAttributeNumberOfDailyTransitionsID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000022,
    ZGMTRClusterThermostatAttributeTemperatureSetpointHoldID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterThermostatAttributeTemperatureSetpointHoldID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000023,
    ZGMTRClusterThermostatAttributeTemperatureSetpointHoldDurationID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterThermostatAttributeTemperatureSetpointHoldDurationID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000024,
    ZGMTRClusterThermostatAttributeThermostatProgrammingOperationModeID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterThermostatAttributeThermostatProgrammingOperationModeID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000025,
    ZGMTRClusterThermostatAttributeThermostatRunningStateID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterThermostatAttributeThermostatRunningStateID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000029,
    ZGMTRClusterThermostatAttributeSetpointChangeSourceID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterThermostatAttributeSetpointChangeSourceID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000030,
    ZGMTRClusterThermostatAttributeSetpointChangeAmountID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterThermostatAttributeSetpointChangeAmountID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000031,
    ZGMTRClusterThermostatAttributeSetpointChangeSourceTimestampID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterThermostatAttributeSetpointChangeSourceTimestampID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000032,
    ZGMTRClusterThermostatAttributeOccupiedSetbackID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterThermostatAttributeOccupiedSetbackID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000034,
    ZGMTRClusterThermostatAttributeOccupiedSetbackMinID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterThermostatAttributeOccupiedSetbackMinID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000035,
    ZGMTRClusterThermostatAttributeOccupiedSetbackMaxID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterThermostatAttributeOccupiedSetbackMaxID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000036,
    ZGMTRClusterThermostatAttributeUnoccupiedSetbackID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterThermostatAttributeUnoccupiedSetbackID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000037,
    ZGMTRClusterThermostatAttributeUnoccupiedSetbackMinID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterThermostatAttributeUnoccupiedSetbackMinID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000038,
    ZGMTRClusterThermostatAttributeUnoccupiedSetbackMaxID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterThermostatAttributeUnoccupiedSetbackMaxID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000039,
    ZGMTRClusterThermostatAttributeEmergencyHeatDeltaID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterThermostatAttributeEmergencyHeatDeltaID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x0000003A,
    ZGMTRClusterThermostatAttributeACTypeID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterThermostatAttributeACTypeID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000040,
    ZGMTRClusterThermostatAttributeACCapacityID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterThermostatAttributeACCapacityID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000041,
    ZGMTRClusterThermostatAttributeACRefrigerantTypeID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterThermostatAttributeACRefrigerantTypeID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000042,
    ZGMTRClusterThermostatAttributeACCompressorTypeID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterThermostatAttributeACCompressorTypeID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000043,
    ZGMTRClusterThermostatAttributeACErrorCodeID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterThermostatAttributeACErrorCodeID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000044,
    ZGMTRClusterThermostatAttributeACLouverPositionID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterThermostatAttributeACLouverPositionID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000045,
    ZGMTRClusterThermostatAttributeACCoilTemperatureID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterThermostatAttributeACCoilTemperatureID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000046,
    ZGMTRClusterThermostatAttributeACCapacityformatID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterThermostatAttributeACCapacityformatID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000047,
    ZGMTRClusterThermostatAttributeGeneratedCommandListID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterThermostatAttributeGeneratedCommandListID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = ZGMTRClusterGlobalAttributeGeneratedCommandListID,
    ZGMTRClusterThermostatAttributeAcceptedCommandListID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterThermostatAttributeAcceptedCommandListID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = ZGMTRClusterGlobalAttributeAcceptedCommandListID,
    ZGMTRClusterThermostatAttributeAttributeListID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterThermostatAttributeAttributeListID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = ZGMTRClusterGlobalAttributeAttributeListID,
    ZGMTRClusterThermostatAttributeFeatureMapID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterThermostatAttributeFeatureMapID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = ZGMTRClusterGlobalAttributeFeatureMapID,
    ZGMTRClusterThermostatAttributeClusterRevisionID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterThermostatAttributeClusterRevisionID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = ZGMTRClusterGlobalAttributeClusterRevisionID,

    // Cluster Thermostat attributes
    ZGMTRAttributeIDTypeClusterThermostatAttributeLocalTemperatureID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000000,
    ZGMTRAttributeIDTypeClusterThermostatAttributeOutdoorTemperatureID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000001,
    ZGMTRAttributeIDTypeClusterThermostatAttributeOccupancyID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000002,
    ZGMTRAttributeIDTypeClusterThermostatAttributeAbsMinHeatSetpointLimitID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000003,
    ZGMTRAttributeIDTypeClusterThermostatAttributeAbsMaxHeatSetpointLimitID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000004,
    ZGMTRAttributeIDTypeClusterThermostatAttributeAbsMinCoolSetpointLimitID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000005,
    ZGMTRAttributeIDTypeClusterThermostatAttributeAbsMaxCoolSetpointLimitID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000006,
    ZGMTRAttributeIDTypeClusterThermostatAttributePICoolingDemandID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000007,
    ZGMTRAttributeIDTypeClusterThermostatAttributePIHeatingDemandID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000008,
    ZGMTRAttributeIDTypeClusterThermostatAttributeHVACSystemTypeConfigurationID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000009,
    ZGMTRAttributeIDTypeClusterThermostatAttributeLocalTemperatureCalibrationID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000010,
    ZGMTRAttributeIDTypeClusterThermostatAttributeOccupiedCoolingSetpointID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000011,
    ZGMTRAttributeIDTypeClusterThermostatAttributeOccupiedHeatingSetpointID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000012,
    ZGMTRAttributeIDTypeClusterThermostatAttributeUnoccupiedCoolingSetpointID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000013,
    ZGMTRAttributeIDTypeClusterThermostatAttributeUnoccupiedHeatingSetpointID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000014,
    ZGMTRAttributeIDTypeClusterThermostatAttributeMinHeatSetpointLimitID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000015,
    ZGMTRAttributeIDTypeClusterThermostatAttributeMaxHeatSetpointLimitID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000016,
    ZGMTRAttributeIDTypeClusterThermostatAttributeMinCoolSetpointLimitID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000017,
    ZGMTRAttributeIDTypeClusterThermostatAttributeMaxCoolSetpointLimitID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000018,
    ZGMTRAttributeIDTypeClusterThermostatAttributeMinSetpointDeadBandID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000019,
    ZGMTRAttributeIDTypeClusterThermostatAttributeRemoteSensingID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x0000001A,
    ZGMTRAttributeIDTypeClusterThermostatAttributeControlSequenceOfOperationID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x0000001B,
    ZGMTRAttributeIDTypeClusterThermostatAttributeSystemModeID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x0000001C,
    ZGMTRAttributeIDTypeClusterThermostatAttributeThermostatRunningModeID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x0000001E,
    ZGMTRAttributeIDTypeClusterThermostatAttributeStartOfWeekID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000020,
    ZGMTRAttributeIDTypeClusterThermostatAttributeNumberOfWeeklyTransitionsID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000021,
    ZGMTRAttributeIDTypeClusterThermostatAttributeNumberOfDailyTransitionsID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000022,
    ZGMTRAttributeIDTypeClusterThermostatAttributeTemperatureSetpointHoldID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000023,
    ZGMTRAttributeIDTypeClusterThermostatAttributeTemperatureSetpointHoldDurationID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000024,
    ZGMTRAttributeIDTypeClusterThermostatAttributeThermostatProgrammingOperationModeID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000025,
    ZGMTRAttributeIDTypeClusterThermostatAttributeThermostatRunningStateID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000029,
    ZGMTRAttributeIDTypeClusterThermostatAttributeSetpointChangeSourceID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000030,
    ZGMTRAttributeIDTypeClusterThermostatAttributeSetpointChangeAmountID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000031,
    ZGMTRAttributeIDTypeClusterThermostatAttributeSetpointChangeSourceTimestampID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000032,
    ZGMTRAttributeIDTypeClusterThermostatAttributeOccupiedSetbackID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000034,
    ZGMTRAttributeIDTypeClusterThermostatAttributeOccupiedSetbackMinID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000035,
    ZGMTRAttributeIDTypeClusterThermostatAttributeOccupiedSetbackMaxID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000036,
    ZGMTRAttributeIDTypeClusterThermostatAttributeUnoccupiedSetbackID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000037,
    ZGMTRAttributeIDTypeClusterThermostatAttributeUnoccupiedSetbackMinID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000038,
    ZGMTRAttributeIDTypeClusterThermostatAttributeUnoccupiedSetbackMaxID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000039,
    ZGMTRAttributeIDTypeClusterThermostatAttributeEmergencyHeatDeltaID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x0000003A,
    ZGMTRAttributeIDTypeClusterThermostatAttributeACTypeID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000040,
    ZGMTRAttributeIDTypeClusterThermostatAttributeACCapacityID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000041,
    ZGMTRAttributeIDTypeClusterThermostatAttributeACRefrigerantTypeID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000042,
    ZGMTRAttributeIDTypeClusterThermostatAttributeACCompressorTypeID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000043,
    ZGMTRAttributeIDTypeClusterThermostatAttributeACErrorCodeID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000044,
    ZGMTRAttributeIDTypeClusterThermostatAttributeACLouverPositionID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000045,
    ZGMTRAttributeIDTypeClusterThermostatAttributeACCoilTemperatureID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000046,
    ZGMTRAttributeIDTypeClusterThermostatAttributeACCapacityformatID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000047,
    ZGMTRAttributeIDTypeClusterThermostatAttributePresetTypesID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = 0x00000048,
    ZGMTRAttributeIDTypeClusterThermostatAttributeScheduleTypesID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = 0x00000049,
    ZGMTRAttributeIDTypeClusterThermostatAttributeNumberOfPresetsID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = 0x0000004A,
    ZGMTRAttributeIDTypeClusterThermostatAttributeNumberOfSchedulesID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = 0x0000004B,
    ZGMTRAttributeIDTypeClusterThermostatAttributeNumberOfScheduleTransitionsID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = 0x0000004C,
    ZGMTRAttributeIDTypeClusterThermostatAttributeNumberOfScheduleTransitionPerDayID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = 0x0000004D,
    ZGMTRAttributeIDTypeClusterThermostatAttributeActivePresetHandleID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = 0x0000004E,
    ZGMTRAttributeIDTypeClusterThermostatAttributeActiveScheduleHandleID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = 0x0000004F,
    ZGMTRAttributeIDTypeClusterThermostatAttributePresetsID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = 0x00000050,
    ZGMTRAttributeIDTypeClusterThermostatAttributeSchedulesID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = 0x00000051,
    ZGMTRAttributeIDTypeClusterThermostatAttributeSetpointHoldExpiryTimestampID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = 0x00000052,
    ZGMTRAttributeIDTypeClusterThermostatAttributeMaxThermostatSuggestionsID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000053,
    ZGMTRAttributeIDTypeClusterThermostatAttributeThermostatSuggestionsID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000054,
    ZGMTRAttributeIDTypeClusterThermostatAttributeCurrentThermostatSuggestionID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000055,
    ZGMTRAttributeIDTypeClusterThermostatAttributeThermostatSuggestionNotFollowingReasonID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000056,
    ZGMTRAttributeIDTypeClusterThermostatAttributeGeneratedCommandListID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = ZGMTRAttributeIDTypeGlobalAttributeGeneratedCommandListID,
    ZGMTRAttributeIDTypeClusterThermostatAttributeAcceptedCommandListID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = ZGMTRAttributeIDTypeGlobalAttributeAcceptedCommandListID,
    ZGMTRAttributeIDTypeClusterThermostatAttributeAttributeListID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = ZGMTRAttributeIDTypeGlobalAttributeAttributeListID,
    ZGMTRAttributeIDTypeClusterThermostatAttributeFeatureMapID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = ZGMTRAttributeIDTypeGlobalAttributeFeatureMapID,
    ZGMTRAttributeIDTypeClusterThermostatAttributeClusterRevisionID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = ZGMTRAttributeIDTypeGlobalAttributeClusterRevisionID,

    // Cluster FanControl deprecated attribute names
    ZGMTRClusterFanControlAttributeFanModeID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterFanControlAttributeFanModeID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000000,
    ZGMTRClusterFanControlAttributeFanModeSequenceID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterFanControlAttributeFanModeSequenceID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000001,
    ZGMTRClusterFanControlAttributePercentSettingID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterFanControlAttributePercentSettingID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000002,
    ZGMTRClusterFanControlAttributePercentCurrentID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterFanControlAttributePercentCurrentID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000003,
    ZGMTRClusterFanControlAttributeSpeedMaxID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterFanControlAttributeSpeedMaxID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000004,
    ZGMTRClusterFanControlAttributeSpeedSettingID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterFanControlAttributeSpeedSettingID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000005,
    ZGMTRClusterFanControlAttributeSpeedCurrentID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterFanControlAttributeSpeedCurrentID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000006,
    ZGMTRClusterFanControlAttributeRockSupportID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterFanControlAttributeRockSupportID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000007,
    ZGMTRClusterFanControlAttributeRockSettingID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterFanControlAttributeRockSettingID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000008,
    ZGMTRClusterFanControlAttributeWindSupportID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterFanControlAttributeWindSupportID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000009,
    ZGMTRClusterFanControlAttributeWindSettingID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterFanControlAttributeWindSettingID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x0000000A,
    ZGMTRClusterFanControlAttributeGeneratedCommandListID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterFanControlAttributeGeneratedCommandListID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = ZGMTRClusterGlobalAttributeGeneratedCommandListID,
    ZGMTRClusterFanControlAttributeAcceptedCommandListID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterFanControlAttributeAcceptedCommandListID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = ZGMTRClusterGlobalAttributeAcceptedCommandListID,
    ZGMTRClusterFanControlAttributeAttributeListID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterFanControlAttributeAttributeListID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = ZGMTRClusterGlobalAttributeAttributeListID,
    ZGMTRClusterFanControlAttributeFeatureMapID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterFanControlAttributeFeatureMapID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = ZGMTRClusterGlobalAttributeFeatureMapID,
    ZGMTRClusterFanControlAttributeClusterRevisionID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterFanControlAttributeClusterRevisionID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = ZGMTRClusterGlobalAttributeClusterRevisionID,

    // Cluster FanControl attributes
    ZGMTRAttributeIDTypeClusterFanControlAttributeFanModeID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000000,
    ZGMTRAttributeIDTypeClusterFanControlAttributeFanModeSequenceID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000001,
    ZGMTRAttributeIDTypeClusterFanControlAttributePercentSettingID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000002,
    ZGMTRAttributeIDTypeClusterFanControlAttributePercentCurrentID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000003,
    ZGMTRAttributeIDTypeClusterFanControlAttributeSpeedMaxID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000004,
    ZGMTRAttributeIDTypeClusterFanControlAttributeSpeedSettingID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000005,
    ZGMTRAttributeIDTypeClusterFanControlAttributeSpeedCurrentID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000006,
    ZGMTRAttributeIDTypeClusterFanControlAttributeRockSupportID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000007,
    ZGMTRAttributeIDTypeClusterFanControlAttributeRockSettingID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000008,
    ZGMTRAttributeIDTypeClusterFanControlAttributeWindSupportID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000009,
    ZGMTRAttributeIDTypeClusterFanControlAttributeWindSettingID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x0000000A,
    ZGMTRAttributeIDTypeClusterFanControlAttributeAirflowDirectionID ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6)) = 0x0000000B,
    ZGMTRAttributeIDTypeClusterFanControlAttributeGeneratedCommandListID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = ZGMTRAttributeIDTypeGlobalAttributeGeneratedCommandListID,
    ZGMTRAttributeIDTypeClusterFanControlAttributeAcceptedCommandListID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = ZGMTRAttributeIDTypeGlobalAttributeAcceptedCommandListID,
    ZGMTRAttributeIDTypeClusterFanControlAttributeAttributeListID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = ZGMTRAttributeIDTypeGlobalAttributeAttributeListID,
    ZGMTRAttributeIDTypeClusterFanControlAttributeFeatureMapID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = ZGMTRAttributeIDTypeGlobalAttributeFeatureMapID,
    ZGMTRAttributeIDTypeClusterFanControlAttributeClusterRevisionID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = ZGMTRAttributeIDTypeGlobalAttributeClusterRevisionID,

    // Cluster ThermostatUserInterfaceConfiguration deprecated attribute names
    ZGMTRClusterThermostatUserInterfaceConfigurationAttributeTemperatureDisplayModeID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterThermostatUserInterfaceConfigurationAttributeTemperatureDisplayModeID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000000,
    ZGMTRClusterThermostatUserInterfaceConfigurationAttributeKeypadLockoutID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterThermostatUserInterfaceConfigurationAttributeKeypadLockoutID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000001,
    ZGMTRClusterThermostatUserInterfaceConfigurationAttributeScheduleProgrammingVisibilityID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterThermostatUserInterfaceConfigurationAttributeScheduleProgrammingVisibilityID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000002,
    ZGMTRClusterThermostatUserInterfaceConfigurationAttributeGeneratedCommandListID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterThermostatUserInterfaceConfigurationAttributeGeneratedCommandListID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = ZGMTRClusterGlobalAttributeGeneratedCommandListID,
    ZGMTRClusterThermostatUserInterfaceConfigurationAttributeAcceptedCommandListID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterThermostatUserInterfaceConfigurationAttributeAcceptedCommandListID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = ZGMTRClusterGlobalAttributeAcceptedCommandListID,
    ZGMTRClusterThermostatUserInterfaceConfigurationAttributeAttributeListID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterThermostatUserInterfaceConfigurationAttributeAttributeListID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = ZGMTRClusterGlobalAttributeAttributeListID,
    ZGMTRClusterThermostatUserInterfaceConfigurationAttributeFeatureMapID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterThermostatUserInterfaceConfigurationAttributeFeatureMapID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = ZGMTRClusterGlobalAttributeFeatureMapID,
    ZGMTRClusterThermostatUserInterfaceConfigurationAttributeClusterRevisionID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterThermostatUserInterfaceConfigurationAttributeClusterRevisionID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = ZGMTRClusterGlobalAttributeClusterRevisionID,

    // Cluster ThermostatUserInterfaceConfiguration attributes
    ZGMTRAttributeIDTypeClusterThermostatUserInterfaceConfigurationAttributeTemperatureDisplayModeID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000000,
    ZGMTRAttributeIDTypeClusterThermostatUserInterfaceConfigurationAttributeKeypadLockoutID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000001,
    ZGMTRAttributeIDTypeClusterThermostatUserInterfaceConfigurationAttributeScheduleProgrammingVisibilityID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000002,
    ZGMTRAttributeIDTypeClusterThermostatUserInterfaceConfigurationAttributeGeneratedCommandListID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = ZGMTRAttributeIDTypeGlobalAttributeGeneratedCommandListID,
    ZGMTRAttributeIDTypeClusterThermostatUserInterfaceConfigurationAttributeAcceptedCommandListID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = ZGMTRAttributeIDTypeGlobalAttributeAcceptedCommandListID,
    ZGMTRAttributeIDTypeClusterThermostatUserInterfaceConfigurationAttributeAttributeListID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = ZGMTRAttributeIDTypeGlobalAttributeAttributeListID,
    ZGMTRAttributeIDTypeClusterThermostatUserInterfaceConfigurationAttributeFeatureMapID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = ZGMTRAttributeIDTypeGlobalAttributeFeatureMapID,
    ZGMTRAttributeIDTypeClusterThermostatUserInterfaceConfigurationAttributeClusterRevisionID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = ZGMTRAttributeIDTypeGlobalAttributeClusterRevisionID,

    // Cluster Humidistat attributes
    ZGMTRAttributeIDTypeClusterHumidistatAttributeModeID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000000,
    ZGMTRAttributeIDTypeClusterHumidistatAttributeSystemStateID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000001,
    ZGMTRAttributeIDTypeClusterHumidistatAttributeUserSetpointID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000002,
    ZGMTRAttributeIDTypeClusterHumidistatAttributeMinSetpointID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000003,
    ZGMTRAttributeIDTypeClusterHumidistatAttributeMaxSetpointID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000004,
    ZGMTRAttributeIDTypeClusterHumidistatAttributeStepID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000005,
    ZGMTRAttributeIDTypeClusterHumidistatAttributeTargetSetpointID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000006,
    ZGMTRAttributeIDTypeClusterHumidistatAttributeMistTypeID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000007,
    ZGMTRAttributeIDTypeClusterHumidistatAttributeContinuousID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000008,
    ZGMTRAttributeIDTypeClusterHumidistatAttributeSleepID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000009,
    ZGMTRAttributeIDTypeClusterHumidistatAttributeOptimalID ZGMTR_PROVISIONALLY_AVAILABLE = 0x0000000A,
    ZGMTRAttributeIDTypeClusterHumidistatAttributeGeneratedCommandListID ZGMTR_PROVISIONALLY_AVAILABLE = ZGMTRAttributeIDTypeGlobalAttributeGeneratedCommandListID,
    ZGMTRAttributeIDTypeClusterHumidistatAttributeAcceptedCommandListID ZGMTR_PROVISIONALLY_AVAILABLE = ZGMTRAttributeIDTypeGlobalAttributeAcceptedCommandListID,
    ZGMTRAttributeIDTypeClusterHumidistatAttributeAttributeListID ZGMTR_PROVISIONALLY_AVAILABLE = ZGMTRAttributeIDTypeGlobalAttributeAttributeListID,
    ZGMTRAttributeIDTypeClusterHumidistatAttributeFeatureMapID ZGMTR_PROVISIONALLY_AVAILABLE = ZGMTRAttributeIDTypeGlobalAttributeFeatureMapID,
    ZGMTRAttributeIDTypeClusterHumidistatAttributeClusterRevisionID ZGMTR_PROVISIONALLY_AVAILABLE = ZGMTRAttributeIDTypeGlobalAttributeClusterRevisionID,

    // Cluster ColorControl deprecated attribute names
    ZGMTRClusterColorControlAttributeCurrentHueID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterColorControlAttributeCurrentHueID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000000,
    ZGMTRClusterColorControlAttributeCurrentSaturationID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterColorControlAttributeCurrentSaturationID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000001,
    ZGMTRClusterColorControlAttributeRemainingTimeID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterColorControlAttributeRemainingTimeID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000002,
    ZGMTRClusterColorControlAttributeCurrentXID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterColorControlAttributeCurrentXID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000003,
    ZGMTRClusterColorControlAttributeCurrentYID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterColorControlAttributeCurrentYID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000004,
    ZGMTRClusterColorControlAttributeDriftCompensationID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterColorControlAttributeDriftCompensationID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000005,
    ZGMTRClusterColorControlAttributeCompensationTextID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterColorControlAttributeCompensationTextID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000006,
    ZGMTRClusterColorControlAttributeColorTemperatureMiredsID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterColorControlAttributeColorTemperatureMiredsID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000007,
    ZGMTRClusterColorControlAttributeColorModeID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterColorControlAttributeColorModeID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000008,
    ZGMTRClusterColorControlAttributeOptionsID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterColorControlAttributeOptionsID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x0000000F,
    ZGMTRClusterColorControlAttributeNumberOfPrimariesID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterColorControlAttributeNumberOfPrimariesID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000010,
    ZGMTRClusterColorControlAttributePrimary1XID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterColorControlAttributePrimary1XID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000011,
    ZGMTRClusterColorControlAttributePrimary1YID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterColorControlAttributePrimary1YID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000012,
    ZGMTRClusterColorControlAttributePrimary1IntensityID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterColorControlAttributePrimary1IntensityID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000013,
    ZGMTRClusterColorControlAttributePrimary2XID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterColorControlAttributePrimary2XID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000015,
    ZGMTRClusterColorControlAttributePrimary2YID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterColorControlAttributePrimary2YID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000016,
    ZGMTRClusterColorControlAttributePrimary2IntensityID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterColorControlAttributePrimary2IntensityID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000017,
    ZGMTRClusterColorControlAttributePrimary3XID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterColorControlAttributePrimary3XID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000019,
    ZGMTRClusterColorControlAttributePrimary3YID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterColorControlAttributePrimary3YID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x0000001A,
    ZGMTRClusterColorControlAttributePrimary3IntensityID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterColorControlAttributePrimary3IntensityID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x0000001B,
    ZGMTRClusterColorControlAttributePrimary4XID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterColorControlAttributePrimary4XID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000020,
    ZGMTRClusterColorControlAttributePrimary4YID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterColorControlAttributePrimary4YID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000021,
    ZGMTRClusterColorControlAttributePrimary4IntensityID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterColorControlAttributePrimary4IntensityID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000022,
    ZGMTRClusterColorControlAttributePrimary5XID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterColorControlAttributePrimary5XID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000024,
    ZGMTRClusterColorControlAttributePrimary5YID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterColorControlAttributePrimary5YID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000025,
    ZGMTRClusterColorControlAttributePrimary5IntensityID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterColorControlAttributePrimary5IntensityID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000026,
    ZGMTRClusterColorControlAttributePrimary6XID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterColorControlAttributePrimary6XID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000028,
    ZGMTRClusterColorControlAttributePrimary6YID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterColorControlAttributePrimary6YID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000029,
    ZGMTRClusterColorControlAttributePrimary6IntensityID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterColorControlAttributePrimary6IntensityID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x0000002A,
    ZGMTRClusterColorControlAttributeWhitePointXID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterColorControlAttributeWhitePointXID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000030,
    ZGMTRClusterColorControlAttributeWhitePointYID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterColorControlAttributeWhitePointYID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000031,
    ZGMTRClusterColorControlAttributeColorPointRXID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterColorControlAttributeColorPointRXID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000032,
    ZGMTRClusterColorControlAttributeColorPointRYID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterColorControlAttributeColorPointRYID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000033,
    ZGMTRClusterColorControlAttributeColorPointRIntensityID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterColorControlAttributeColorPointRIntensityID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000034,
    ZGMTRClusterColorControlAttributeColorPointGXID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterColorControlAttributeColorPointGXID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000036,
    ZGMTRClusterColorControlAttributeColorPointGYID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterColorControlAttributeColorPointGYID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000037,
    ZGMTRClusterColorControlAttributeColorPointGIntensityID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterColorControlAttributeColorPointGIntensityID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000038,
    ZGMTRClusterColorControlAttributeColorPointBXID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterColorControlAttributeColorPointBXID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x0000003A,
    ZGMTRClusterColorControlAttributeColorPointBYID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterColorControlAttributeColorPointBYID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x0000003B,
    ZGMTRClusterColorControlAttributeColorPointBIntensityID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterColorControlAttributeColorPointBIntensityID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x0000003C,
    ZGMTRClusterColorControlAttributeEnhancedCurrentHueID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterColorControlAttributeEnhancedCurrentHueID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00004000,
    ZGMTRClusterColorControlAttributeEnhancedColorModeID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterColorControlAttributeEnhancedColorModeID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00004001,
    ZGMTRClusterColorControlAttributeColorLoopActiveID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterColorControlAttributeColorLoopActiveID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00004002,
    ZGMTRClusterColorControlAttributeColorLoopDirectionID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterColorControlAttributeColorLoopDirectionID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00004003,
    ZGMTRClusterColorControlAttributeColorLoopTimeID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterColorControlAttributeColorLoopTimeID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00004004,
    ZGMTRClusterColorControlAttributeColorLoopStartEnhancedHueID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterColorControlAttributeColorLoopStartEnhancedHueID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00004005,
    ZGMTRClusterColorControlAttributeColorLoopStoredEnhancedHueID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterColorControlAttributeColorLoopStoredEnhancedHueID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00004006,
    ZGMTRClusterColorControlAttributeColorCapabilitiesID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterColorControlAttributeColorCapabilitiesID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x0000400A,
    ZGMTRClusterColorControlAttributeColorTempPhysicalMinMiredsID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterColorControlAttributeColorTempPhysicalMinMiredsID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x0000400B,
    ZGMTRClusterColorControlAttributeColorTempPhysicalMaxMiredsID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterColorControlAttributeColorTempPhysicalMaxMiredsID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x0000400C,
    ZGMTRClusterColorControlAttributeCoupleColorTempToLevelMinMiredsID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterColorControlAttributeCoupleColorTempToLevelMinMiredsID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x0000400D,
    ZGMTRClusterColorControlAttributeStartUpColorTemperatureMiredsID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterColorControlAttributeStartUpColorTemperatureMiredsID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00004010,
    ZGMTRClusterColorControlAttributeGeneratedCommandListID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterColorControlAttributeGeneratedCommandListID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = ZGMTRClusterGlobalAttributeGeneratedCommandListID,
    ZGMTRClusterColorControlAttributeAcceptedCommandListID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterColorControlAttributeAcceptedCommandListID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = ZGMTRClusterGlobalAttributeAcceptedCommandListID,
    ZGMTRClusterColorControlAttributeAttributeListID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterColorControlAttributeAttributeListID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = ZGMTRClusterGlobalAttributeAttributeListID,
    ZGMTRClusterColorControlAttributeFeatureMapID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterColorControlAttributeFeatureMapID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = ZGMTRClusterGlobalAttributeFeatureMapID,
    ZGMTRClusterColorControlAttributeClusterRevisionID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterColorControlAttributeClusterRevisionID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = ZGMTRClusterGlobalAttributeClusterRevisionID,

    // Cluster ColorControl attributes
    ZGMTRAttributeIDTypeClusterColorControlAttributeCurrentHueID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000000,
    ZGMTRAttributeIDTypeClusterColorControlAttributeCurrentSaturationID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000001,
    ZGMTRAttributeIDTypeClusterColorControlAttributeRemainingTimeID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000002,
    ZGMTRAttributeIDTypeClusterColorControlAttributeCurrentXID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000003,
    ZGMTRAttributeIDTypeClusterColorControlAttributeCurrentYID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000004,
    ZGMTRAttributeIDTypeClusterColorControlAttributeDriftCompensationID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000005,
    ZGMTRAttributeIDTypeClusterColorControlAttributeCompensationTextID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000006,
    ZGMTRAttributeIDTypeClusterColorControlAttributeColorTemperatureMiredsID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000007,
    ZGMTRAttributeIDTypeClusterColorControlAttributeColorModeID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000008,
    ZGMTRAttributeIDTypeClusterColorControlAttributeOptionsID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x0000000F,
    ZGMTRAttributeIDTypeClusterColorControlAttributeNumberOfPrimariesID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000010,
    ZGMTRAttributeIDTypeClusterColorControlAttributePrimary1XID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000011,
    ZGMTRAttributeIDTypeClusterColorControlAttributePrimary1YID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000012,
    ZGMTRAttributeIDTypeClusterColorControlAttributePrimary1IntensityID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000013,
    ZGMTRAttributeIDTypeClusterColorControlAttributePrimary2XID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000015,
    ZGMTRAttributeIDTypeClusterColorControlAttributePrimary2YID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000016,
    ZGMTRAttributeIDTypeClusterColorControlAttributePrimary2IntensityID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000017,
    ZGMTRAttributeIDTypeClusterColorControlAttributePrimary3XID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000019,
    ZGMTRAttributeIDTypeClusterColorControlAttributePrimary3YID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x0000001A,
    ZGMTRAttributeIDTypeClusterColorControlAttributePrimary3IntensityID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x0000001B,
    ZGMTRAttributeIDTypeClusterColorControlAttributePrimary4XID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000020,
    ZGMTRAttributeIDTypeClusterColorControlAttributePrimary4YID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000021,
    ZGMTRAttributeIDTypeClusterColorControlAttributePrimary4IntensityID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000022,
    ZGMTRAttributeIDTypeClusterColorControlAttributePrimary5XID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000024,
    ZGMTRAttributeIDTypeClusterColorControlAttributePrimary5YID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000025,
    ZGMTRAttributeIDTypeClusterColorControlAttributePrimary5IntensityID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000026,
    ZGMTRAttributeIDTypeClusterColorControlAttributePrimary6XID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000028,
    ZGMTRAttributeIDTypeClusterColorControlAttributePrimary6YID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000029,
    ZGMTRAttributeIDTypeClusterColorControlAttributePrimary6IntensityID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x0000002A,
    ZGMTRAttributeIDTypeClusterColorControlAttributeWhitePointXID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000030,
    ZGMTRAttributeIDTypeClusterColorControlAttributeWhitePointYID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000031,
    ZGMTRAttributeIDTypeClusterColorControlAttributeColorPointRXID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000032,
    ZGMTRAttributeIDTypeClusterColorControlAttributeColorPointRYID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000033,
    ZGMTRAttributeIDTypeClusterColorControlAttributeColorPointRIntensityID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000034,
    ZGMTRAttributeIDTypeClusterColorControlAttributeColorPointGXID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000036,
    ZGMTRAttributeIDTypeClusterColorControlAttributeColorPointGYID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000037,
    ZGMTRAttributeIDTypeClusterColorControlAttributeColorPointGIntensityID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000038,
    ZGMTRAttributeIDTypeClusterColorControlAttributeColorPointBXID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x0000003A,
    ZGMTRAttributeIDTypeClusterColorControlAttributeColorPointBYID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x0000003B,
    ZGMTRAttributeIDTypeClusterColorControlAttributeColorPointBIntensityID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x0000003C,
    ZGMTRAttributeIDTypeClusterColorControlAttributeEnhancedCurrentHueID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00004000,
    ZGMTRAttributeIDTypeClusterColorControlAttributeEnhancedColorModeID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00004001,
    ZGMTRAttributeIDTypeClusterColorControlAttributeColorLoopActiveID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00004002,
    ZGMTRAttributeIDTypeClusterColorControlAttributeColorLoopDirectionID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00004003,
    ZGMTRAttributeIDTypeClusterColorControlAttributeColorLoopTimeID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00004004,
    ZGMTRAttributeIDTypeClusterColorControlAttributeColorLoopStartEnhancedHueID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00004005,
    ZGMTRAttributeIDTypeClusterColorControlAttributeColorLoopStoredEnhancedHueID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00004006,
    ZGMTRAttributeIDTypeClusterColorControlAttributeColorCapabilitiesID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x0000400A,
    ZGMTRAttributeIDTypeClusterColorControlAttributeColorTempPhysicalMinMiredsID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x0000400B,
    ZGMTRAttributeIDTypeClusterColorControlAttributeColorTempPhysicalMaxMiredsID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x0000400C,
    ZGMTRAttributeIDTypeClusterColorControlAttributeCoupleColorTempToLevelMinMiredsID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x0000400D,
    ZGMTRAttributeIDTypeClusterColorControlAttributeStartUpColorTemperatureMiredsID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00004010,
    ZGMTRAttributeIDTypeClusterColorControlAttributeGeneratedCommandListID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = ZGMTRAttributeIDTypeGlobalAttributeGeneratedCommandListID,
    ZGMTRAttributeIDTypeClusterColorControlAttributeAcceptedCommandListID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = ZGMTRAttributeIDTypeGlobalAttributeAcceptedCommandListID,
    ZGMTRAttributeIDTypeClusterColorControlAttributeAttributeListID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = ZGMTRAttributeIDTypeGlobalAttributeAttributeListID,
    ZGMTRAttributeIDTypeClusterColorControlAttributeFeatureMapID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = ZGMTRAttributeIDTypeGlobalAttributeFeatureMapID,
    ZGMTRAttributeIDTypeClusterColorControlAttributeClusterRevisionID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = ZGMTRAttributeIDTypeGlobalAttributeClusterRevisionID,

    // Cluster BallastConfiguration deprecated attribute names
    ZGMTRClusterBallastConfigurationAttributePhysicalMinLevelID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterBallastConfigurationAttributePhysicalMinLevelID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000000,
    ZGMTRClusterBallastConfigurationAttributePhysicalMaxLevelID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterBallastConfigurationAttributePhysicalMaxLevelID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000001,
    ZGMTRClusterBallastConfigurationAttributeBallastStatusID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterBallastConfigurationAttributeBallastStatusID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000002,
    ZGMTRClusterBallastConfigurationAttributeMinLevelID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterBallastConfigurationAttributeMinLevelID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000010,
    ZGMTRClusterBallastConfigurationAttributeMaxLevelID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterBallastConfigurationAttributeMaxLevelID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000011,
    ZGMTRClusterBallastConfigurationAttributeIntrinsicBalanceFactorID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterBallastConfigurationAttributeIntrinsicBallastFactorID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000014,
    ZGMTRClusterBallastConfigurationAttributeBallastFactorAdjustmentID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterBallastConfigurationAttributeBallastFactorAdjustmentID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000015,
    ZGMTRClusterBallastConfigurationAttributeLampQuantityID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterBallastConfigurationAttributeLampQuantityID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000020,
    ZGMTRClusterBallastConfigurationAttributeLampTypeID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterBallastConfigurationAttributeLampTypeID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000030,
    ZGMTRClusterBallastConfigurationAttributeLampManufacturerID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterBallastConfigurationAttributeLampManufacturerID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000031,
    ZGMTRClusterBallastConfigurationAttributeLampRatedHoursID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterBallastConfigurationAttributeLampRatedHoursID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000032,
    ZGMTRClusterBallastConfigurationAttributeLampBurnHoursID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterBallastConfigurationAttributeLampBurnHoursID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000033,
    ZGMTRClusterBallastConfigurationAttributeLampAlarmModeID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterBallastConfigurationAttributeLampAlarmModeID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000034,
    ZGMTRClusterBallastConfigurationAttributeLampBurnHoursTripPointID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterBallastConfigurationAttributeLampBurnHoursTripPointID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000035,
    ZGMTRClusterBallastConfigurationAttributeGeneratedCommandListID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterBallastConfigurationAttributeGeneratedCommandListID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = ZGMTRClusterGlobalAttributeGeneratedCommandListID,
    ZGMTRClusterBallastConfigurationAttributeAcceptedCommandListID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterBallastConfigurationAttributeAcceptedCommandListID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = ZGMTRClusterGlobalAttributeAcceptedCommandListID,
    ZGMTRClusterBallastConfigurationAttributeAttributeListID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterBallastConfigurationAttributeAttributeListID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = ZGMTRClusterGlobalAttributeAttributeListID,
    ZGMTRClusterBallastConfigurationAttributeFeatureMapID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterBallastConfigurationAttributeFeatureMapID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = ZGMTRClusterGlobalAttributeFeatureMapID,
    ZGMTRClusterBallastConfigurationAttributeClusterRevisionID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterBallastConfigurationAttributeClusterRevisionID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = ZGMTRClusterGlobalAttributeClusterRevisionID,

    // Cluster BallastConfiguration attributes
    ZGMTRAttributeIDTypeClusterBallastConfigurationAttributePhysicalMinLevelID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000000,
    ZGMTRAttributeIDTypeClusterBallastConfigurationAttributePhysicalMaxLevelID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000001,
    ZGMTRAttributeIDTypeClusterBallastConfigurationAttributeBallastStatusID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000002,
    ZGMTRAttributeIDTypeClusterBallastConfigurationAttributeMinLevelID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000010,
    ZGMTRAttributeIDTypeClusterBallastConfigurationAttributeMaxLevelID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000011,
    ZGMTRAttributeIDTypeClusterBallastConfigurationAttributeIntrinsicBallastFactorID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000014,
    ZGMTRAttributeIDTypeClusterBallastConfigurationAttributeBallastFactorAdjustmentID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000015,
    ZGMTRAttributeIDTypeClusterBallastConfigurationAttributeLampQuantityID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000020,
    ZGMTRAttributeIDTypeClusterBallastConfigurationAttributeLampTypeID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000030,
    ZGMTRAttributeIDTypeClusterBallastConfigurationAttributeLampManufacturerID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000031,
    ZGMTRAttributeIDTypeClusterBallastConfigurationAttributeLampRatedHoursID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000032,
    ZGMTRAttributeIDTypeClusterBallastConfigurationAttributeLampBurnHoursID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000033,
    ZGMTRAttributeIDTypeClusterBallastConfigurationAttributeLampAlarmModeID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000034,
    ZGMTRAttributeIDTypeClusterBallastConfigurationAttributeLampBurnHoursTripPointID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000035,
    ZGMTRAttributeIDTypeClusterBallastConfigurationAttributeGeneratedCommandListID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = ZGMTRAttributeIDTypeGlobalAttributeGeneratedCommandListID,
    ZGMTRAttributeIDTypeClusterBallastConfigurationAttributeAcceptedCommandListID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = ZGMTRAttributeIDTypeGlobalAttributeAcceptedCommandListID,
    ZGMTRAttributeIDTypeClusterBallastConfigurationAttributeAttributeListID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = ZGMTRAttributeIDTypeGlobalAttributeAttributeListID,
    ZGMTRAttributeIDTypeClusterBallastConfigurationAttributeFeatureMapID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = ZGMTRAttributeIDTypeGlobalAttributeFeatureMapID,
    ZGMTRAttributeIDTypeClusterBallastConfigurationAttributeClusterRevisionID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = ZGMTRAttributeIDTypeGlobalAttributeClusterRevisionID,

    // Cluster DynamicLighting attributes
    ZGMTRAttributeIDTypeClusterDynamicLightingAttributeAvailableEffectsID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000000,
    ZGMTRAttributeIDTypeClusterDynamicLightingAttributeCurrentEffectIDID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000001,
    ZGMTRAttributeIDTypeClusterDynamicLightingAttributeCurrentSpeedID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000002,
    ZGMTRAttributeIDTypeClusterDynamicLightingAttributeGeneratedCommandListID ZGMTR_PROVISIONALLY_AVAILABLE = ZGMTRAttributeIDTypeGlobalAttributeGeneratedCommandListID,
    ZGMTRAttributeIDTypeClusterDynamicLightingAttributeAcceptedCommandListID ZGMTR_PROVISIONALLY_AVAILABLE = ZGMTRAttributeIDTypeGlobalAttributeAcceptedCommandListID,
    ZGMTRAttributeIDTypeClusterDynamicLightingAttributeAttributeListID ZGMTR_PROVISIONALLY_AVAILABLE = ZGMTRAttributeIDTypeGlobalAttributeAttributeListID,
    ZGMTRAttributeIDTypeClusterDynamicLightingAttributeFeatureMapID ZGMTR_PROVISIONALLY_AVAILABLE = ZGMTRAttributeIDTypeGlobalAttributeFeatureMapID,
    ZGMTRAttributeIDTypeClusterDynamicLightingAttributeClusterRevisionID ZGMTR_PROVISIONALLY_AVAILABLE = ZGMTRAttributeIDTypeGlobalAttributeClusterRevisionID,

    // Cluster IlluminanceMeasurement deprecated attribute names
    ZGMTRClusterIlluminanceMeasurementAttributeMeasuredValueID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterIlluminanceMeasurementAttributeMeasuredValueID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000000,
    ZGMTRClusterIlluminanceMeasurementAttributeMinMeasuredValueID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterIlluminanceMeasurementAttributeMinMeasuredValueID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000001,
    ZGMTRClusterIlluminanceMeasurementAttributeMaxMeasuredValueID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterIlluminanceMeasurementAttributeMaxMeasuredValueID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000002,
    ZGMTRClusterIlluminanceMeasurementAttributeToleranceID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterIlluminanceMeasurementAttributeToleranceID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000003,
    ZGMTRClusterIlluminanceMeasurementAttributeLightSensorTypeID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterIlluminanceMeasurementAttributeLightSensorTypeID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000004,
    ZGMTRClusterIlluminanceMeasurementAttributeGeneratedCommandListID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterIlluminanceMeasurementAttributeGeneratedCommandListID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = ZGMTRClusterGlobalAttributeGeneratedCommandListID,
    ZGMTRClusterIlluminanceMeasurementAttributeAcceptedCommandListID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterIlluminanceMeasurementAttributeAcceptedCommandListID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = ZGMTRClusterGlobalAttributeAcceptedCommandListID,
    ZGMTRClusterIlluminanceMeasurementAttributeAttributeListID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterIlluminanceMeasurementAttributeAttributeListID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = ZGMTRClusterGlobalAttributeAttributeListID,
    ZGMTRClusterIlluminanceMeasurementAttributeFeatureMapID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterIlluminanceMeasurementAttributeFeatureMapID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = ZGMTRClusterGlobalAttributeFeatureMapID,
    ZGMTRClusterIlluminanceMeasurementAttributeClusterRevisionID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterIlluminanceMeasurementAttributeClusterRevisionID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = ZGMTRClusterGlobalAttributeClusterRevisionID,

    // Cluster IlluminanceMeasurement attributes
    ZGMTRAttributeIDTypeClusterIlluminanceMeasurementAttributeMeasuredValueID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000000,
    ZGMTRAttributeIDTypeClusterIlluminanceMeasurementAttributeMinMeasuredValueID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000001,
    ZGMTRAttributeIDTypeClusterIlluminanceMeasurementAttributeMaxMeasuredValueID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000002,
    ZGMTRAttributeIDTypeClusterIlluminanceMeasurementAttributeToleranceID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000003,
    ZGMTRAttributeIDTypeClusterIlluminanceMeasurementAttributeLightSensorTypeID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000004,
    ZGMTRAttributeIDTypeClusterIlluminanceMeasurementAttributeGeneratedCommandListID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = ZGMTRAttributeIDTypeGlobalAttributeGeneratedCommandListID,
    ZGMTRAttributeIDTypeClusterIlluminanceMeasurementAttributeAcceptedCommandListID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = ZGMTRAttributeIDTypeGlobalAttributeAcceptedCommandListID,
    ZGMTRAttributeIDTypeClusterIlluminanceMeasurementAttributeAttributeListID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = ZGMTRAttributeIDTypeGlobalAttributeAttributeListID,
    ZGMTRAttributeIDTypeClusterIlluminanceMeasurementAttributeFeatureMapID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = ZGMTRAttributeIDTypeGlobalAttributeFeatureMapID,
    ZGMTRAttributeIDTypeClusterIlluminanceMeasurementAttributeClusterRevisionID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = ZGMTRAttributeIDTypeGlobalAttributeClusterRevisionID,

    // Cluster TemperatureMeasurement deprecated attribute names
    ZGMTRClusterTemperatureMeasurementAttributeMeasuredValueID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterTemperatureMeasurementAttributeMeasuredValueID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000000,
    ZGMTRClusterTemperatureMeasurementAttributeMinMeasuredValueID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterTemperatureMeasurementAttributeMinMeasuredValueID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000001,
    ZGMTRClusterTemperatureMeasurementAttributeMaxMeasuredValueID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterTemperatureMeasurementAttributeMaxMeasuredValueID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000002,
    ZGMTRClusterTemperatureMeasurementAttributeToleranceID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterTemperatureMeasurementAttributeToleranceID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000003,
    ZGMTRClusterTemperatureMeasurementAttributeGeneratedCommandListID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterTemperatureMeasurementAttributeGeneratedCommandListID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = ZGMTRClusterGlobalAttributeGeneratedCommandListID,
    ZGMTRClusterTemperatureMeasurementAttributeAcceptedCommandListID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterTemperatureMeasurementAttributeAcceptedCommandListID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = ZGMTRClusterGlobalAttributeAcceptedCommandListID,
    ZGMTRClusterTemperatureMeasurementAttributeAttributeListID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterTemperatureMeasurementAttributeAttributeListID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = ZGMTRClusterGlobalAttributeAttributeListID,
    ZGMTRClusterTemperatureMeasurementAttributeFeatureMapID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterTemperatureMeasurementAttributeFeatureMapID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = ZGMTRClusterGlobalAttributeFeatureMapID,
    ZGMTRClusterTemperatureMeasurementAttributeClusterRevisionID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterTemperatureMeasurementAttributeClusterRevisionID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = ZGMTRClusterGlobalAttributeClusterRevisionID,

    // Cluster TemperatureMeasurement attributes
    ZGMTRAttributeIDTypeClusterTemperatureMeasurementAttributeMeasuredValueID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000000,
    ZGMTRAttributeIDTypeClusterTemperatureMeasurementAttributeMinMeasuredValueID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000001,
    ZGMTRAttributeIDTypeClusterTemperatureMeasurementAttributeMaxMeasuredValueID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000002,
    ZGMTRAttributeIDTypeClusterTemperatureMeasurementAttributeToleranceID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000003,
    ZGMTRAttributeIDTypeClusterTemperatureMeasurementAttributeGeneratedCommandListID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = ZGMTRAttributeIDTypeGlobalAttributeGeneratedCommandListID,
    ZGMTRAttributeIDTypeClusterTemperatureMeasurementAttributeAcceptedCommandListID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = ZGMTRAttributeIDTypeGlobalAttributeAcceptedCommandListID,
    ZGMTRAttributeIDTypeClusterTemperatureMeasurementAttributeAttributeListID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = ZGMTRAttributeIDTypeGlobalAttributeAttributeListID,
    ZGMTRAttributeIDTypeClusterTemperatureMeasurementAttributeFeatureMapID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = ZGMTRAttributeIDTypeGlobalAttributeFeatureMapID,
    ZGMTRAttributeIDTypeClusterTemperatureMeasurementAttributeClusterRevisionID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = ZGMTRAttributeIDTypeGlobalAttributeClusterRevisionID,

    // Cluster PressureMeasurement deprecated attribute names
    ZGMTRClusterPressureMeasurementAttributeMeasuredValueID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterPressureMeasurementAttributeMeasuredValueID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000000,
    ZGMTRClusterPressureMeasurementAttributeMinMeasuredValueID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterPressureMeasurementAttributeMinMeasuredValueID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000001,
    ZGMTRClusterPressureMeasurementAttributeMaxMeasuredValueID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterPressureMeasurementAttributeMaxMeasuredValueID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000002,
    ZGMTRClusterPressureMeasurementAttributeToleranceID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterPressureMeasurementAttributeToleranceID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000003,
    ZGMTRClusterPressureMeasurementAttributeScaledValueID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterPressureMeasurementAttributeScaledValueID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000010,
    ZGMTRClusterPressureMeasurementAttributeMinScaledValueID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterPressureMeasurementAttributeMinScaledValueID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000011,
    ZGMTRClusterPressureMeasurementAttributeMaxScaledValueID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterPressureMeasurementAttributeMaxScaledValueID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000012,
    ZGMTRClusterPressureMeasurementAttributeScaledToleranceID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterPressureMeasurementAttributeScaledToleranceID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000013,
    ZGMTRClusterPressureMeasurementAttributeScaleID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterPressureMeasurementAttributeScaleID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000014,
    ZGMTRClusterPressureMeasurementAttributeGeneratedCommandListID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterPressureMeasurementAttributeGeneratedCommandListID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = ZGMTRClusterGlobalAttributeGeneratedCommandListID,
    ZGMTRClusterPressureMeasurementAttributeAcceptedCommandListID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterPressureMeasurementAttributeAcceptedCommandListID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = ZGMTRClusterGlobalAttributeAcceptedCommandListID,
    ZGMTRClusterPressureMeasurementAttributeAttributeListID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterPressureMeasurementAttributeAttributeListID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = ZGMTRClusterGlobalAttributeAttributeListID,
    ZGMTRClusterPressureMeasurementAttributeFeatureMapID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterPressureMeasurementAttributeFeatureMapID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = ZGMTRClusterGlobalAttributeFeatureMapID,
    ZGMTRClusterPressureMeasurementAttributeClusterRevisionID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterPressureMeasurementAttributeClusterRevisionID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = ZGMTRClusterGlobalAttributeClusterRevisionID,

    // Cluster PressureMeasurement attributes
    ZGMTRAttributeIDTypeClusterPressureMeasurementAttributeMeasuredValueID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000000,
    ZGMTRAttributeIDTypeClusterPressureMeasurementAttributeMinMeasuredValueID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000001,
    ZGMTRAttributeIDTypeClusterPressureMeasurementAttributeMaxMeasuredValueID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000002,
    ZGMTRAttributeIDTypeClusterPressureMeasurementAttributeToleranceID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000003,
    ZGMTRAttributeIDTypeClusterPressureMeasurementAttributeScaledValueID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000010,
    ZGMTRAttributeIDTypeClusterPressureMeasurementAttributeMinScaledValueID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000011,
    ZGMTRAttributeIDTypeClusterPressureMeasurementAttributeMaxScaledValueID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000012,
    ZGMTRAttributeIDTypeClusterPressureMeasurementAttributeScaledToleranceID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000013,
    ZGMTRAttributeIDTypeClusterPressureMeasurementAttributeScaleID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000014,
    ZGMTRAttributeIDTypeClusterPressureMeasurementAttributeGeneratedCommandListID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = ZGMTRAttributeIDTypeGlobalAttributeGeneratedCommandListID,
    ZGMTRAttributeIDTypeClusterPressureMeasurementAttributeAcceptedCommandListID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = ZGMTRAttributeIDTypeGlobalAttributeAcceptedCommandListID,
    ZGMTRAttributeIDTypeClusterPressureMeasurementAttributeAttributeListID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = ZGMTRAttributeIDTypeGlobalAttributeAttributeListID,
    ZGMTRAttributeIDTypeClusterPressureMeasurementAttributeFeatureMapID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = ZGMTRAttributeIDTypeGlobalAttributeFeatureMapID,
    ZGMTRAttributeIDTypeClusterPressureMeasurementAttributeClusterRevisionID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = ZGMTRAttributeIDTypeGlobalAttributeClusterRevisionID,

    // Cluster FlowMeasurement deprecated attribute names
    ZGMTRClusterFlowMeasurementAttributeMeasuredValueID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterFlowMeasurementAttributeMeasuredValueID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000000,
    ZGMTRClusterFlowMeasurementAttributeMinMeasuredValueID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterFlowMeasurementAttributeMinMeasuredValueID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000001,
    ZGMTRClusterFlowMeasurementAttributeMaxMeasuredValueID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterFlowMeasurementAttributeMaxMeasuredValueID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000002,
    ZGMTRClusterFlowMeasurementAttributeToleranceID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterFlowMeasurementAttributeToleranceID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000003,
    ZGMTRClusterFlowMeasurementAttributeGeneratedCommandListID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterFlowMeasurementAttributeGeneratedCommandListID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = ZGMTRClusterGlobalAttributeGeneratedCommandListID,
    ZGMTRClusterFlowMeasurementAttributeAcceptedCommandListID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterFlowMeasurementAttributeAcceptedCommandListID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = ZGMTRClusterGlobalAttributeAcceptedCommandListID,
    ZGMTRClusterFlowMeasurementAttributeAttributeListID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterFlowMeasurementAttributeAttributeListID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = ZGMTRClusterGlobalAttributeAttributeListID,
    ZGMTRClusterFlowMeasurementAttributeFeatureMapID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterFlowMeasurementAttributeFeatureMapID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = ZGMTRClusterGlobalAttributeFeatureMapID,
    ZGMTRClusterFlowMeasurementAttributeClusterRevisionID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterFlowMeasurementAttributeClusterRevisionID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = ZGMTRClusterGlobalAttributeClusterRevisionID,

    // Cluster FlowMeasurement attributes
    ZGMTRAttributeIDTypeClusterFlowMeasurementAttributeMeasuredValueID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000000,
    ZGMTRAttributeIDTypeClusterFlowMeasurementAttributeMinMeasuredValueID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000001,
    ZGMTRAttributeIDTypeClusterFlowMeasurementAttributeMaxMeasuredValueID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000002,
    ZGMTRAttributeIDTypeClusterFlowMeasurementAttributeToleranceID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000003,
    ZGMTRAttributeIDTypeClusterFlowMeasurementAttributeGeneratedCommandListID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = ZGMTRAttributeIDTypeGlobalAttributeGeneratedCommandListID,
    ZGMTRAttributeIDTypeClusterFlowMeasurementAttributeAcceptedCommandListID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = ZGMTRAttributeIDTypeGlobalAttributeAcceptedCommandListID,
    ZGMTRAttributeIDTypeClusterFlowMeasurementAttributeAttributeListID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = ZGMTRAttributeIDTypeGlobalAttributeAttributeListID,
    ZGMTRAttributeIDTypeClusterFlowMeasurementAttributeFeatureMapID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = ZGMTRAttributeIDTypeGlobalAttributeFeatureMapID,
    ZGMTRAttributeIDTypeClusterFlowMeasurementAttributeClusterRevisionID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = ZGMTRAttributeIDTypeGlobalAttributeClusterRevisionID,

    // Cluster RelativeHumidityMeasurement deprecated attribute names
    ZGMTRClusterRelativeHumidityMeasurementAttributeMeasuredValueID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterRelativeHumidityMeasurementAttributeMeasuredValueID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000000,
    ZGMTRClusterRelativeHumidityMeasurementAttributeMinMeasuredValueID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterRelativeHumidityMeasurementAttributeMinMeasuredValueID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000001,
    ZGMTRClusterRelativeHumidityMeasurementAttributeMaxMeasuredValueID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterRelativeHumidityMeasurementAttributeMaxMeasuredValueID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000002,
    ZGMTRClusterRelativeHumidityMeasurementAttributeToleranceID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterRelativeHumidityMeasurementAttributeToleranceID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000003,
    ZGMTRClusterRelativeHumidityMeasurementAttributeGeneratedCommandListID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterRelativeHumidityMeasurementAttributeGeneratedCommandListID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = ZGMTRClusterGlobalAttributeGeneratedCommandListID,
    ZGMTRClusterRelativeHumidityMeasurementAttributeAcceptedCommandListID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterRelativeHumidityMeasurementAttributeAcceptedCommandListID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = ZGMTRClusterGlobalAttributeAcceptedCommandListID,
    ZGMTRClusterRelativeHumidityMeasurementAttributeAttributeListID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterRelativeHumidityMeasurementAttributeAttributeListID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = ZGMTRClusterGlobalAttributeAttributeListID,
    ZGMTRClusterRelativeHumidityMeasurementAttributeFeatureMapID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterRelativeHumidityMeasurementAttributeFeatureMapID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = ZGMTRClusterGlobalAttributeFeatureMapID,
    ZGMTRClusterRelativeHumidityMeasurementAttributeClusterRevisionID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterRelativeHumidityMeasurementAttributeClusterRevisionID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = ZGMTRClusterGlobalAttributeClusterRevisionID,

    // Cluster RelativeHumidityMeasurement attributes
    ZGMTRAttributeIDTypeClusterRelativeHumidityMeasurementAttributeMeasuredValueID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000000,
    ZGMTRAttributeIDTypeClusterRelativeHumidityMeasurementAttributeMinMeasuredValueID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000001,
    ZGMTRAttributeIDTypeClusterRelativeHumidityMeasurementAttributeMaxMeasuredValueID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000002,
    ZGMTRAttributeIDTypeClusterRelativeHumidityMeasurementAttributeToleranceID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000003,
    ZGMTRAttributeIDTypeClusterRelativeHumidityMeasurementAttributeGeneratedCommandListID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = ZGMTRAttributeIDTypeGlobalAttributeGeneratedCommandListID,
    ZGMTRAttributeIDTypeClusterRelativeHumidityMeasurementAttributeAcceptedCommandListID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = ZGMTRAttributeIDTypeGlobalAttributeAcceptedCommandListID,
    ZGMTRAttributeIDTypeClusterRelativeHumidityMeasurementAttributeAttributeListID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = ZGMTRAttributeIDTypeGlobalAttributeAttributeListID,
    ZGMTRAttributeIDTypeClusterRelativeHumidityMeasurementAttributeFeatureMapID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = ZGMTRAttributeIDTypeGlobalAttributeFeatureMapID,
    ZGMTRAttributeIDTypeClusterRelativeHumidityMeasurementAttributeClusterRevisionID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = ZGMTRAttributeIDTypeGlobalAttributeClusterRevisionID,

    // Cluster OccupancySensing deprecated attribute names
    ZGMTRClusterOccupancySensingAttributeOccupancyID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterOccupancySensingAttributeOccupancyID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000000,
    ZGMTRClusterOccupancySensingAttributeOccupancySensorTypeID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterOccupancySensingAttributeOccupancySensorTypeID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000001,
    ZGMTRClusterOccupancySensingAttributeOccupancySensorTypeBitmapID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterOccupancySensingAttributeOccupancySensorTypeBitmapID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000002,
    ZGMTRClusterOccupancySensingAttributePirOccupiedToUnoccupiedDelayID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterOccupancySensingAttributePIROccupiedToUnoccupiedDelayID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000010,
    ZGMTRClusterOccupancySensingAttributePirUnoccupiedToOccupiedDelayID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterOccupancySensingAttributePIRUnoccupiedToOccupiedDelayID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000011,
    ZGMTRClusterOccupancySensingAttributePirUnoccupiedToOccupiedThresholdID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterOccupancySensingAttributePIRUnoccupiedToOccupiedThresholdID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000012,
    ZGMTRClusterOccupancySensingAttributeUltrasonicOccupiedToUnoccupiedDelayID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterOccupancySensingAttributeUltrasonicOccupiedToUnoccupiedDelayID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000020,
    ZGMTRClusterOccupancySensingAttributeUltrasonicUnoccupiedToOccupiedDelayID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterOccupancySensingAttributeUltrasonicUnoccupiedToOccupiedDelayID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000021,
    ZGMTRClusterOccupancySensingAttributeUltrasonicUnoccupiedToOccupiedThresholdID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterOccupancySensingAttributeUltrasonicUnoccupiedToOccupiedThresholdID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000022,
    ZGMTRClusterOccupancySensingAttributePhysicalContactOccupiedToUnoccupiedDelayID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterOccupancySensingAttributePhysicalContactOccupiedToUnoccupiedDelayID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000030,
    ZGMTRClusterOccupancySensingAttributePhysicalContactUnoccupiedToOccupiedDelayID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterOccupancySensingAttributePhysicalContactUnoccupiedToOccupiedDelayID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000031,
    ZGMTRClusterOccupancySensingAttributePhysicalContactUnoccupiedToOccupiedThresholdID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterOccupancySensingAttributePhysicalContactUnoccupiedToOccupiedThresholdID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000032,
    ZGMTRClusterOccupancySensingAttributeGeneratedCommandListID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterOccupancySensingAttributeGeneratedCommandListID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = ZGMTRClusterGlobalAttributeGeneratedCommandListID,
    ZGMTRClusterOccupancySensingAttributeAcceptedCommandListID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterOccupancySensingAttributeAcceptedCommandListID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = ZGMTRClusterGlobalAttributeAcceptedCommandListID,
    ZGMTRClusterOccupancySensingAttributeAttributeListID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterOccupancySensingAttributeAttributeListID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = ZGMTRClusterGlobalAttributeAttributeListID,
    ZGMTRClusterOccupancySensingAttributeFeatureMapID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterOccupancySensingAttributeFeatureMapID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = ZGMTRClusterGlobalAttributeFeatureMapID,
    ZGMTRClusterOccupancySensingAttributeClusterRevisionID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterOccupancySensingAttributeClusterRevisionID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = ZGMTRClusterGlobalAttributeClusterRevisionID,

    // Cluster OccupancySensing attributes
    ZGMTRAttributeIDTypeClusterOccupancySensingAttributeOccupancyID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000000,
    ZGMTRAttributeIDTypeClusterOccupancySensingAttributeOccupancySensorTypeID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000001,
    ZGMTRAttributeIDTypeClusterOccupancySensingAttributeOccupancySensorTypeBitmapID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000002,
    ZGMTRAttributeIDTypeClusterOccupancySensingAttributeHoldTimeID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = 0x00000003,
    ZGMTRAttributeIDTypeClusterOccupancySensingAttributeHoldTimeLimitsID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = 0x00000004,
    ZGMTRAttributeIDTypeClusterOccupancySensingAttributePredictedOccupancyID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000005,
    ZGMTRAttributeIDTypeClusterOccupancySensingAttributePIROccupiedToUnoccupiedDelayID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000010,
    ZGMTRAttributeIDTypeClusterOccupancySensingAttributePIRUnoccupiedToOccupiedDelayID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000011,
    ZGMTRAttributeIDTypeClusterOccupancySensingAttributePIRUnoccupiedToOccupiedThresholdID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000012,
    ZGMTRAttributeIDTypeClusterOccupancySensingAttributeUltrasonicOccupiedToUnoccupiedDelayID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000020,
    ZGMTRAttributeIDTypeClusterOccupancySensingAttributeUltrasonicUnoccupiedToOccupiedDelayID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000021,
    ZGMTRAttributeIDTypeClusterOccupancySensingAttributeUltrasonicUnoccupiedToOccupiedThresholdID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000022,
    ZGMTRAttributeIDTypeClusterOccupancySensingAttributePhysicalContactOccupiedToUnoccupiedDelayID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000030,
    ZGMTRAttributeIDTypeClusterOccupancySensingAttributePhysicalContactUnoccupiedToOccupiedDelayID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000031,
    ZGMTRAttributeIDTypeClusterOccupancySensingAttributePhysicalContactUnoccupiedToOccupiedThresholdID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000032,
    ZGMTRAttributeIDTypeClusterOccupancySensingAttributeGeneratedCommandListID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = ZGMTRAttributeIDTypeGlobalAttributeGeneratedCommandListID,
    ZGMTRAttributeIDTypeClusterOccupancySensingAttributeAcceptedCommandListID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = ZGMTRAttributeIDTypeGlobalAttributeAcceptedCommandListID,
    ZGMTRAttributeIDTypeClusterOccupancySensingAttributeAttributeListID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = ZGMTRAttributeIDTypeGlobalAttributeAttributeListID,
    ZGMTRAttributeIDTypeClusterOccupancySensingAttributeFeatureMapID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = ZGMTRAttributeIDTypeGlobalAttributeFeatureMapID,
    ZGMTRAttributeIDTypeClusterOccupancySensingAttributeClusterRevisionID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = ZGMTRAttributeIDTypeGlobalAttributeClusterRevisionID,

    // Cluster CarbonMonoxideConcentrationMeasurement attributes
    ZGMTRAttributeIDTypeClusterCarbonMonoxideConcentrationMeasurementAttributeMeasuredValueID ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6)) = 0x00000000,
    ZGMTRAttributeIDTypeClusterCarbonMonoxideConcentrationMeasurementAttributeMinMeasuredValueID ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6)) = 0x00000001,
    ZGMTRAttributeIDTypeClusterCarbonMonoxideConcentrationMeasurementAttributeMaxMeasuredValueID ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6)) = 0x00000002,
    ZGMTRAttributeIDTypeClusterCarbonMonoxideConcentrationMeasurementAttributePeakMeasuredValueID ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6)) = 0x00000003,
    ZGMTRAttributeIDTypeClusterCarbonMonoxideConcentrationMeasurementAttributePeakMeasuredValueWindowID ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6)) = 0x00000004,
    ZGMTRAttributeIDTypeClusterCarbonMonoxideConcentrationMeasurementAttributeAverageMeasuredValueID ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6)) = 0x00000005,
    ZGMTRAttributeIDTypeClusterCarbonMonoxideConcentrationMeasurementAttributeAverageMeasuredValueWindowID ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6)) = 0x00000006,
    ZGMTRAttributeIDTypeClusterCarbonMonoxideConcentrationMeasurementAttributeUncertaintyID ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6)) = 0x00000007,
    ZGMTRAttributeIDTypeClusterCarbonMonoxideConcentrationMeasurementAttributeMeasurementUnitID ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6)) = 0x00000008,
    ZGMTRAttributeIDTypeClusterCarbonMonoxideConcentrationMeasurementAttributeMeasurementMediumID ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6)) = 0x00000009,
    ZGMTRAttributeIDTypeClusterCarbonMonoxideConcentrationMeasurementAttributeLevelValueID ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6)) = 0x0000000A,
    ZGMTRAttributeIDTypeClusterCarbonMonoxideConcentrationMeasurementAttributeGeneratedCommandListID ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6)) = ZGMTRAttributeIDTypeGlobalAttributeGeneratedCommandListID,
    ZGMTRAttributeIDTypeClusterCarbonMonoxideConcentrationMeasurementAttributeAcceptedCommandListID ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6)) = ZGMTRAttributeIDTypeGlobalAttributeAcceptedCommandListID,
    ZGMTRAttributeIDTypeClusterCarbonMonoxideConcentrationMeasurementAttributeAttributeListID ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6)) = ZGMTRAttributeIDTypeGlobalAttributeAttributeListID,
    ZGMTRAttributeIDTypeClusterCarbonMonoxideConcentrationMeasurementAttributeFeatureMapID ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6)) = ZGMTRAttributeIDTypeGlobalAttributeFeatureMapID,
    ZGMTRAttributeIDTypeClusterCarbonMonoxideConcentrationMeasurementAttributeClusterRevisionID ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6)) = ZGMTRAttributeIDTypeGlobalAttributeClusterRevisionID,

    // Cluster CarbonDioxideConcentrationMeasurement attributes
    ZGMTRAttributeIDTypeClusterCarbonDioxideConcentrationMeasurementAttributeMeasuredValueID ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6)) = 0x00000000,
    ZGMTRAttributeIDTypeClusterCarbonDioxideConcentrationMeasurementAttributeMinMeasuredValueID ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6)) = 0x00000001,
    ZGMTRAttributeIDTypeClusterCarbonDioxideConcentrationMeasurementAttributeMaxMeasuredValueID ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6)) = 0x00000002,
    ZGMTRAttributeIDTypeClusterCarbonDioxideConcentrationMeasurementAttributePeakMeasuredValueID ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6)) = 0x00000003,
    ZGMTRAttributeIDTypeClusterCarbonDioxideConcentrationMeasurementAttributePeakMeasuredValueWindowID ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6)) = 0x00000004,
    ZGMTRAttributeIDTypeClusterCarbonDioxideConcentrationMeasurementAttributeAverageMeasuredValueID ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6)) = 0x00000005,
    ZGMTRAttributeIDTypeClusterCarbonDioxideConcentrationMeasurementAttributeAverageMeasuredValueWindowID ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6)) = 0x00000006,
    ZGMTRAttributeIDTypeClusterCarbonDioxideConcentrationMeasurementAttributeUncertaintyID ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6)) = 0x00000007,
    ZGMTRAttributeIDTypeClusterCarbonDioxideConcentrationMeasurementAttributeMeasurementUnitID ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6)) = 0x00000008,
    ZGMTRAttributeIDTypeClusterCarbonDioxideConcentrationMeasurementAttributeMeasurementMediumID ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6)) = 0x00000009,
    ZGMTRAttributeIDTypeClusterCarbonDioxideConcentrationMeasurementAttributeLevelValueID ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6)) = 0x0000000A,
    ZGMTRAttributeIDTypeClusterCarbonDioxideConcentrationMeasurementAttributeGeneratedCommandListID ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6)) = ZGMTRAttributeIDTypeGlobalAttributeGeneratedCommandListID,
    ZGMTRAttributeIDTypeClusterCarbonDioxideConcentrationMeasurementAttributeAcceptedCommandListID ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6)) = ZGMTRAttributeIDTypeGlobalAttributeAcceptedCommandListID,
    ZGMTRAttributeIDTypeClusterCarbonDioxideConcentrationMeasurementAttributeAttributeListID ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6)) = ZGMTRAttributeIDTypeGlobalAttributeAttributeListID,
    ZGMTRAttributeIDTypeClusterCarbonDioxideConcentrationMeasurementAttributeFeatureMapID ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6)) = ZGMTRAttributeIDTypeGlobalAttributeFeatureMapID,
    ZGMTRAttributeIDTypeClusterCarbonDioxideConcentrationMeasurementAttributeClusterRevisionID ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6)) = ZGMTRAttributeIDTypeGlobalAttributeClusterRevisionID,

    // Cluster NitrogenDioxideConcentrationMeasurement attributes
    ZGMTRAttributeIDTypeClusterNitrogenDioxideConcentrationMeasurementAttributeMeasuredValueID ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6)) = 0x00000000,
    ZGMTRAttributeIDTypeClusterNitrogenDioxideConcentrationMeasurementAttributeMinMeasuredValueID ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6)) = 0x00000001,
    ZGMTRAttributeIDTypeClusterNitrogenDioxideConcentrationMeasurementAttributeMaxMeasuredValueID ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6)) = 0x00000002,
    ZGMTRAttributeIDTypeClusterNitrogenDioxideConcentrationMeasurementAttributePeakMeasuredValueID ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6)) = 0x00000003,
    ZGMTRAttributeIDTypeClusterNitrogenDioxideConcentrationMeasurementAttributePeakMeasuredValueWindowID ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6)) = 0x00000004,
    ZGMTRAttributeIDTypeClusterNitrogenDioxideConcentrationMeasurementAttributeAverageMeasuredValueID ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6)) = 0x00000005,
    ZGMTRAttributeIDTypeClusterNitrogenDioxideConcentrationMeasurementAttributeAverageMeasuredValueWindowID ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6)) = 0x00000006,
    ZGMTRAttributeIDTypeClusterNitrogenDioxideConcentrationMeasurementAttributeUncertaintyID ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6)) = 0x00000007,
    ZGMTRAttributeIDTypeClusterNitrogenDioxideConcentrationMeasurementAttributeMeasurementUnitID ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6)) = 0x00000008,
    ZGMTRAttributeIDTypeClusterNitrogenDioxideConcentrationMeasurementAttributeMeasurementMediumID ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6)) = 0x00000009,
    ZGMTRAttributeIDTypeClusterNitrogenDioxideConcentrationMeasurementAttributeLevelValueID ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6)) = 0x0000000A,
    ZGMTRAttributeIDTypeClusterNitrogenDioxideConcentrationMeasurementAttributeGeneratedCommandListID ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6)) = ZGMTRAttributeIDTypeGlobalAttributeGeneratedCommandListID,
    ZGMTRAttributeIDTypeClusterNitrogenDioxideConcentrationMeasurementAttributeAcceptedCommandListID ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6)) = ZGMTRAttributeIDTypeGlobalAttributeAcceptedCommandListID,
    ZGMTRAttributeIDTypeClusterNitrogenDioxideConcentrationMeasurementAttributeAttributeListID ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6)) = ZGMTRAttributeIDTypeGlobalAttributeAttributeListID,
    ZGMTRAttributeIDTypeClusterNitrogenDioxideConcentrationMeasurementAttributeFeatureMapID ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6)) = ZGMTRAttributeIDTypeGlobalAttributeFeatureMapID,
    ZGMTRAttributeIDTypeClusterNitrogenDioxideConcentrationMeasurementAttributeClusterRevisionID ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6)) = ZGMTRAttributeIDTypeGlobalAttributeClusterRevisionID,

    // Cluster OzoneConcentrationMeasurement attributes
    ZGMTRAttributeIDTypeClusterOzoneConcentrationMeasurementAttributeMeasuredValueID ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6)) = 0x00000000,
    ZGMTRAttributeIDTypeClusterOzoneConcentrationMeasurementAttributeMinMeasuredValueID ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6)) = 0x00000001,
    ZGMTRAttributeIDTypeClusterOzoneConcentrationMeasurementAttributeMaxMeasuredValueID ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6)) = 0x00000002,
    ZGMTRAttributeIDTypeClusterOzoneConcentrationMeasurementAttributePeakMeasuredValueID ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6)) = 0x00000003,
    ZGMTRAttributeIDTypeClusterOzoneConcentrationMeasurementAttributePeakMeasuredValueWindowID ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6)) = 0x00000004,
    ZGMTRAttributeIDTypeClusterOzoneConcentrationMeasurementAttributeAverageMeasuredValueID ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6)) = 0x00000005,
    ZGMTRAttributeIDTypeClusterOzoneConcentrationMeasurementAttributeAverageMeasuredValueWindowID ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6)) = 0x00000006,
    ZGMTRAttributeIDTypeClusterOzoneConcentrationMeasurementAttributeUncertaintyID ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6)) = 0x00000007,
    ZGMTRAttributeIDTypeClusterOzoneConcentrationMeasurementAttributeMeasurementUnitID ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6)) = 0x00000008,
    ZGMTRAttributeIDTypeClusterOzoneConcentrationMeasurementAttributeMeasurementMediumID ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6)) = 0x00000009,
    ZGMTRAttributeIDTypeClusterOzoneConcentrationMeasurementAttributeLevelValueID ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6)) = 0x0000000A,
    ZGMTRAttributeIDTypeClusterOzoneConcentrationMeasurementAttributeGeneratedCommandListID ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6)) = ZGMTRAttributeIDTypeGlobalAttributeGeneratedCommandListID,
    ZGMTRAttributeIDTypeClusterOzoneConcentrationMeasurementAttributeAcceptedCommandListID ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6)) = ZGMTRAttributeIDTypeGlobalAttributeAcceptedCommandListID,
    ZGMTRAttributeIDTypeClusterOzoneConcentrationMeasurementAttributeAttributeListID ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6)) = ZGMTRAttributeIDTypeGlobalAttributeAttributeListID,
    ZGMTRAttributeIDTypeClusterOzoneConcentrationMeasurementAttributeFeatureMapID ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6)) = ZGMTRAttributeIDTypeGlobalAttributeFeatureMapID,
    ZGMTRAttributeIDTypeClusterOzoneConcentrationMeasurementAttributeClusterRevisionID ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6)) = ZGMTRAttributeIDTypeGlobalAttributeClusterRevisionID,

    // Cluster PM25ConcentrationMeasurement attributes
    ZGMTRAttributeIDTypeClusterPM25ConcentrationMeasurementAttributeMeasuredValueID ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6)) = 0x00000000,
    ZGMTRAttributeIDTypeClusterPM25ConcentrationMeasurementAttributeMinMeasuredValueID ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6)) = 0x00000001,
    ZGMTRAttributeIDTypeClusterPM25ConcentrationMeasurementAttributeMaxMeasuredValueID ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6)) = 0x00000002,
    ZGMTRAttributeIDTypeClusterPM25ConcentrationMeasurementAttributePeakMeasuredValueID ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6)) = 0x00000003,
    ZGMTRAttributeIDTypeClusterPM25ConcentrationMeasurementAttributePeakMeasuredValueWindowID ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6)) = 0x00000004,
    ZGMTRAttributeIDTypeClusterPM25ConcentrationMeasurementAttributeAverageMeasuredValueID ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6)) = 0x00000005,
    ZGMTRAttributeIDTypeClusterPM25ConcentrationMeasurementAttributeAverageMeasuredValueWindowID ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6)) = 0x00000006,
    ZGMTRAttributeIDTypeClusterPM25ConcentrationMeasurementAttributeUncertaintyID ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6)) = 0x00000007,
    ZGMTRAttributeIDTypeClusterPM25ConcentrationMeasurementAttributeMeasurementUnitID ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6)) = 0x00000008,
    ZGMTRAttributeIDTypeClusterPM25ConcentrationMeasurementAttributeMeasurementMediumID ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6)) = 0x00000009,
    ZGMTRAttributeIDTypeClusterPM25ConcentrationMeasurementAttributeLevelValueID ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6)) = 0x0000000A,
    ZGMTRAttributeIDTypeClusterPM25ConcentrationMeasurementAttributeGeneratedCommandListID ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6)) = ZGMTRAttributeIDTypeGlobalAttributeGeneratedCommandListID,
    ZGMTRAttributeIDTypeClusterPM25ConcentrationMeasurementAttributeAcceptedCommandListID ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6)) = ZGMTRAttributeIDTypeGlobalAttributeAcceptedCommandListID,
    ZGMTRAttributeIDTypeClusterPM25ConcentrationMeasurementAttributeAttributeListID ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6)) = ZGMTRAttributeIDTypeGlobalAttributeAttributeListID,
    ZGMTRAttributeIDTypeClusterPM25ConcentrationMeasurementAttributeFeatureMapID ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6)) = ZGMTRAttributeIDTypeGlobalAttributeFeatureMapID,
    ZGMTRAttributeIDTypeClusterPM25ConcentrationMeasurementAttributeClusterRevisionID ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6)) = ZGMTRAttributeIDTypeGlobalAttributeClusterRevisionID,

    // Cluster FormaldehydeConcentrationMeasurement attributes
    ZGMTRAttributeIDTypeClusterFormaldehydeConcentrationMeasurementAttributeMeasuredValueID ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6)) = 0x00000000,
    ZGMTRAttributeIDTypeClusterFormaldehydeConcentrationMeasurementAttributeMinMeasuredValueID ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6)) = 0x00000001,
    ZGMTRAttributeIDTypeClusterFormaldehydeConcentrationMeasurementAttributeMaxMeasuredValueID ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6)) = 0x00000002,
    ZGMTRAttributeIDTypeClusterFormaldehydeConcentrationMeasurementAttributePeakMeasuredValueID ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6)) = 0x00000003,
    ZGMTRAttributeIDTypeClusterFormaldehydeConcentrationMeasurementAttributePeakMeasuredValueWindowID ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6)) = 0x00000004,
    ZGMTRAttributeIDTypeClusterFormaldehydeConcentrationMeasurementAttributeAverageMeasuredValueID ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6)) = 0x00000005,
    ZGMTRAttributeIDTypeClusterFormaldehydeConcentrationMeasurementAttributeAverageMeasuredValueWindowID ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6)) = 0x00000006,
    ZGMTRAttributeIDTypeClusterFormaldehydeConcentrationMeasurementAttributeUncertaintyID ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6)) = 0x00000007,
    ZGMTRAttributeIDTypeClusterFormaldehydeConcentrationMeasurementAttributeMeasurementUnitID ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6)) = 0x00000008,
    ZGMTRAttributeIDTypeClusterFormaldehydeConcentrationMeasurementAttributeMeasurementMediumID ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6)) = 0x00000009,
    ZGMTRAttributeIDTypeClusterFormaldehydeConcentrationMeasurementAttributeLevelValueID ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6)) = 0x0000000A,
    ZGMTRAttributeIDTypeClusterFormaldehydeConcentrationMeasurementAttributeGeneratedCommandListID ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6)) = ZGMTRAttributeIDTypeGlobalAttributeGeneratedCommandListID,
    ZGMTRAttributeIDTypeClusterFormaldehydeConcentrationMeasurementAttributeAcceptedCommandListID ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6)) = ZGMTRAttributeIDTypeGlobalAttributeAcceptedCommandListID,
    ZGMTRAttributeIDTypeClusterFormaldehydeConcentrationMeasurementAttributeAttributeListID ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6)) = ZGMTRAttributeIDTypeGlobalAttributeAttributeListID,
    ZGMTRAttributeIDTypeClusterFormaldehydeConcentrationMeasurementAttributeFeatureMapID ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6)) = ZGMTRAttributeIDTypeGlobalAttributeFeatureMapID,
    ZGMTRAttributeIDTypeClusterFormaldehydeConcentrationMeasurementAttributeClusterRevisionID ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6)) = ZGMTRAttributeIDTypeGlobalAttributeClusterRevisionID,

    // Cluster PM1ConcentrationMeasurement attributes
    ZGMTRAttributeIDTypeClusterPM1ConcentrationMeasurementAttributeMeasuredValueID ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6)) = 0x00000000,
    ZGMTRAttributeIDTypeClusterPM1ConcentrationMeasurementAttributeMinMeasuredValueID ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6)) = 0x00000001,
    ZGMTRAttributeIDTypeClusterPM1ConcentrationMeasurementAttributeMaxMeasuredValueID ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6)) = 0x00000002,
    ZGMTRAttributeIDTypeClusterPM1ConcentrationMeasurementAttributePeakMeasuredValueID ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6)) = 0x00000003,
    ZGMTRAttributeIDTypeClusterPM1ConcentrationMeasurementAttributePeakMeasuredValueWindowID ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6)) = 0x00000004,
    ZGMTRAttributeIDTypeClusterPM1ConcentrationMeasurementAttributeAverageMeasuredValueID ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6)) = 0x00000005,
    ZGMTRAttributeIDTypeClusterPM1ConcentrationMeasurementAttributeAverageMeasuredValueWindowID ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6)) = 0x00000006,
    ZGMTRAttributeIDTypeClusterPM1ConcentrationMeasurementAttributeUncertaintyID ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6)) = 0x00000007,
    ZGMTRAttributeIDTypeClusterPM1ConcentrationMeasurementAttributeMeasurementUnitID ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6)) = 0x00000008,
    ZGMTRAttributeIDTypeClusterPM1ConcentrationMeasurementAttributeMeasurementMediumID ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6)) = 0x00000009,
    ZGMTRAttributeIDTypeClusterPM1ConcentrationMeasurementAttributeLevelValueID ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6)) = 0x0000000A,
    ZGMTRAttributeIDTypeClusterPM1ConcentrationMeasurementAttributeGeneratedCommandListID ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6)) = ZGMTRAttributeIDTypeGlobalAttributeGeneratedCommandListID,
    ZGMTRAttributeIDTypeClusterPM1ConcentrationMeasurementAttributeAcceptedCommandListID ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6)) = ZGMTRAttributeIDTypeGlobalAttributeAcceptedCommandListID,
    ZGMTRAttributeIDTypeClusterPM1ConcentrationMeasurementAttributeAttributeListID ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6)) = ZGMTRAttributeIDTypeGlobalAttributeAttributeListID,
    ZGMTRAttributeIDTypeClusterPM1ConcentrationMeasurementAttributeFeatureMapID ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6)) = ZGMTRAttributeIDTypeGlobalAttributeFeatureMapID,
    ZGMTRAttributeIDTypeClusterPM1ConcentrationMeasurementAttributeClusterRevisionID ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6)) = ZGMTRAttributeIDTypeGlobalAttributeClusterRevisionID,

    // Cluster PM10ConcentrationMeasurement attributes
    ZGMTRAttributeIDTypeClusterPM10ConcentrationMeasurementAttributeMeasuredValueID ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6)) = 0x00000000,
    ZGMTRAttributeIDTypeClusterPM10ConcentrationMeasurementAttributeMinMeasuredValueID ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6)) = 0x00000001,
    ZGMTRAttributeIDTypeClusterPM10ConcentrationMeasurementAttributeMaxMeasuredValueID ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6)) = 0x00000002,
    ZGMTRAttributeIDTypeClusterPM10ConcentrationMeasurementAttributePeakMeasuredValueID ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6)) = 0x00000003,
    ZGMTRAttributeIDTypeClusterPM10ConcentrationMeasurementAttributePeakMeasuredValueWindowID ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6)) = 0x00000004,
    ZGMTRAttributeIDTypeClusterPM10ConcentrationMeasurementAttributeAverageMeasuredValueID ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6)) = 0x00000005,
    ZGMTRAttributeIDTypeClusterPM10ConcentrationMeasurementAttributeAverageMeasuredValueWindowID ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6)) = 0x00000006,
    ZGMTRAttributeIDTypeClusterPM10ConcentrationMeasurementAttributeUncertaintyID ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6)) = 0x00000007,
    ZGMTRAttributeIDTypeClusterPM10ConcentrationMeasurementAttributeMeasurementUnitID ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6)) = 0x00000008,
    ZGMTRAttributeIDTypeClusterPM10ConcentrationMeasurementAttributeMeasurementMediumID ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6)) = 0x00000009,
    ZGMTRAttributeIDTypeClusterPM10ConcentrationMeasurementAttributeLevelValueID ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6)) = 0x0000000A,
    ZGMTRAttributeIDTypeClusterPM10ConcentrationMeasurementAttributeGeneratedCommandListID ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6)) = ZGMTRAttributeIDTypeGlobalAttributeGeneratedCommandListID,
    ZGMTRAttributeIDTypeClusterPM10ConcentrationMeasurementAttributeAcceptedCommandListID ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6)) = ZGMTRAttributeIDTypeGlobalAttributeAcceptedCommandListID,
    ZGMTRAttributeIDTypeClusterPM10ConcentrationMeasurementAttributeAttributeListID ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6)) = ZGMTRAttributeIDTypeGlobalAttributeAttributeListID,
    ZGMTRAttributeIDTypeClusterPM10ConcentrationMeasurementAttributeFeatureMapID ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6)) = ZGMTRAttributeIDTypeGlobalAttributeFeatureMapID,
    ZGMTRAttributeIDTypeClusterPM10ConcentrationMeasurementAttributeClusterRevisionID ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6)) = ZGMTRAttributeIDTypeGlobalAttributeClusterRevisionID,

    // Cluster TotalVolatileOrganicCompoundsConcentrationMeasurement attributes
    ZGMTRAttributeIDTypeClusterTotalVolatileOrganicCompoundsConcentrationMeasurementAttributeMeasuredValueID ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6)) = 0x00000000,
    ZGMTRAttributeIDTypeClusterTotalVolatileOrganicCompoundsConcentrationMeasurementAttributeMinMeasuredValueID ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6)) = 0x00000001,
    ZGMTRAttributeIDTypeClusterTotalVolatileOrganicCompoundsConcentrationMeasurementAttributeMaxMeasuredValueID ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6)) = 0x00000002,
    ZGMTRAttributeIDTypeClusterTotalVolatileOrganicCompoundsConcentrationMeasurementAttributePeakMeasuredValueID ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6)) = 0x00000003,
    ZGMTRAttributeIDTypeClusterTotalVolatileOrganicCompoundsConcentrationMeasurementAttributePeakMeasuredValueWindowID ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6)) = 0x00000004,
    ZGMTRAttributeIDTypeClusterTotalVolatileOrganicCompoundsConcentrationMeasurementAttributeAverageMeasuredValueID ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6)) = 0x00000005,
    ZGMTRAttributeIDTypeClusterTotalVolatileOrganicCompoundsConcentrationMeasurementAttributeAverageMeasuredValueWindowID ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6)) = 0x00000006,
    ZGMTRAttributeIDTypeClusterTotalVolatileOrganicCompoundsConcentrationMeasurementAttributeUncertaintyID ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6)) = 0x00000007,
    ZGMTRAttributeIDTypeClusterTotalVolatileOrganicCompoundsConcentrationMeasurementAttributeMeasurementUnitID ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6)) = 0x00000008,
    ZGMTRAttributeIDTypeClusterTotalVolatileOrganicCompoundsConcentrationMeasurementAttributeMeasurementMediumID ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6)) = 0x00000009,
    ZGMTRAttributeIDTypeClusterTotalVolatileOrganicCompoundsConcentrationMeasurementAttributeLevelValueID ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6)) = 0x0000000A,
    ZGMTRAttributeIDTypeClusterTotalVolatileOrganicCompoundsConcentrationMeasurementAttributeGeneratedCommandListID ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6)) = ZGMTRAttributeIDTypeGlobalAttributeGeneratedCommandListID,
    ZGMTRAttributeIDTypeClusterTotalVolatileOrganicCompoundsConcentrationMeasurementAttributeAcceptedCommandListID ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6)) = ZGMTRAttributeIDTypeGlobalAttributeAcceptedCommandListID,
    ZGMTRAttributeIDTypeClusterTotalVolatileOrganicCompoundsConcentrationMeasurementAttributeAttributeListID ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6)) = ZGMTRAttributeIDTypeGlobalAttributeAttributeListID,
    ZGMTRAttributeIDTypeClusterTotalVolatileOrganicCompoundsConcentrationMeasurementAttributeFeatureMapID ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6)) = ZGMTRAttributeIDTypeGlobalAttributeFeatureMapID,
    ZGMTRAttributeIDTypeClusterTotalVolatileOrganicCompoundsConcentrationMeasurementAttributeClusterRevisionID ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6)) = ZGMTRAttributeIDTypeGlobalAttributeClusterRevisionID,

    // Cluster RadonConcentrationMeasurement attributes
    ZGMTRAttributeIDTypeClusterRadonConcentrationMeasurementAttributeMeasuredValueID ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6)) = 0x00000000,
    ZGMTRAttributeIDTypeClusterRadonConcentrationMeasurementAttributeMinMeasuredValueID ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6)) = 0x00000001,
    ZGMTRAttributeIDTypeClusterRadonConcentrationMeasurementAttributeMaxMeasuredValueID ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6)) = 0x00000002,
    ZGMTRAttributeIDTypeClusterRadonConcentrationMeasurementAttributePeakMeasuredValueID ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6)) = 0x00000003,
    ZGMTRAttributeIDTypeClusterRadonConcentrationMeasurementAttributePeakMeasuredValueWindowID ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6)) = 0x00000004,
    ZGMTRAttributeIDTypeClusterRadonConcentrationMeasurementAttributeAverageMeasuredValueID ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6)) = 0x00000005,
    ZGMTRAttributeIDTypeClusterRadonConcentrationMeasurementAttributeAverageMeasuredValueWindowID ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6)) = 0x00000006,
    ZGMTRAttributeIDTypeClusterRadonConcentrationMeasurementAttributeUncertaintyID ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6)) = 0x00000007,
    ZGMTRAttributeIDTypeClusterRadonConcentrationMeasurementAttributeMeasurementUnitID ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6)) = 0x00000008,
    ZGMTRAttributeIDTypeClusterRadonConcentrationMeasurementAttributeMeasurementMediumID ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6)) = 0x00000009,
    ZGMTRAttributeIDTypeClusterRadonConcentrationMeasurementAttributeLevelValueID ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6)) = 0x0000000A,
    ZGMTRAttributeIDTypeClusterRadonConcentrationMeasurementAttributeGeneratedCommandListID ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6)) = ZGMTRAttributeIDTypeGlobalAttributeGeneratedCommandListID,
    ZGMTRAttributeIDTypeClusterRadonConcentrationMeasurementAttributeAcceptedCommandListID ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6)) = ZGMTRAttributeIDTypeGlobalAttributeAcceptedCommandListID,
    ZGMTRAttributeIDTypeClusterRadonConcentrationMeasurementAttributeAttributeListID ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6)) = ZGMTRAttributeIDTypeGlobalAttributeAttributeListID,
    ZGMTRAttributeIDTypeClusterRadonConcentrationMeasurementAttributeFeatureMapID ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6)) = ZGMTRAttributeIDTypeGlobalAttributeFeatureMapID,
    ZGMTRAttributeIDTypeClusterRadonConcentrationMeasurementAttributeClusterRevisionID ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6)) = ZGMTRAttributeIDTypeGlobalAttributeClusterRevisionID,

    // Cluster SoilMeasurement attributes
    ZGMTRAttributeIDTypeClusterSoilMeasurementAttributeSoilMoistureMeasurementLimitsID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000000,
    ZGMTRAttributeIDTypeClusterSoilMeasurementAttributeSoilMoistureMeasuredValueID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000001,
    ZGMTRAttributeIDTypeClusterSoilMeasurementAttributeGeneratedCommandListID ZGMTR_PROVISIONALLY_AVAILABLE = ZGMTRAttributeIDTypeGlobalAttributeGeneratedCommandListID,
    ZGMTRAttributeIDTypeClusterSoilMeasurementAttributeAcceptedCommandListID ZGMTR_PROVISIONALLY_AVAILABLE = ZGMTRAttributeIDTypeGlobalAttributeAcceptedCommandListID,
    ZGMTRAttributeIDTypeClusterSoilMeasurementAttributeAttributeListID ZGMTR_PROVISIONALLY_AVAILABLE = ZGMTRAttributeIDTypeGlobalAttributeAttributeListID,
    ZGMTRAttributeIDTypeClusterSoilMeasurementAttributeFeatureMapID ZGMTR_PROVISIONALLY_AVAILABLE = ZGMTRAttributeIDTypeGlobalAttributeFeatureMapID,
    ZGMTRAttributeIDTypeClusterSoilMeasurementAttributeClusterRevisionID ZGMTR_PROVISIONALLY_AVAILABLE = ZGMTRAttributeIDTypeGlobalAttributeClusterRevisionID,

    // Cluster AmbientContextSensing attributes
    ZGMTRAttributeIDTypeClusterAmbientContextSensingAttributeHumanActivityDetectedID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000000,
    ZGMTRAttributeIDTypeClusterAmbientContextSensingAttributeObjectIdentifiedID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000001,
    ZGMTRAttributeIDTypeClusterAmbientContextSensingAttributeAudioContextDetectedID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000002,
    ZGMTRAttributeIDTypeClusterAmbientContextSensingAttributeAmbientContextTypeID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000003,
    ZGMTRAttributeIDTypeClusterAmbientContextSensingAttributeAmbientContextTypeSupportedID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000004,
    ZGMTRAttributeIDTypeClusterAmbientContextSensingAttributeObjectCountThresholdReachedID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000005,
    ZGMTRAttributeIDTypeClusterAmbientContextSensingAttributeObjectCountConfigID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000006,
    ZGMTRAttributeIDTypeClusterAmbientContextSensingAttributeObjectCountID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000007,
    ZGMTRAttributeIDTypeClusterAmbientContextSensingAttributeSimultaneousDetectionLimitID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000008,
    ZGMTRAttributeIDTypeClusterAmbientContextSensingAttributeHoldTimeID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000009,
    ZGMTRAttributeIDTypeClusterAmbientContextSensingAttributeHoldTimeLimitsID ZGMTR_PROVISIONALLY_AVAILABLE = 0x0000000A,
    ZGMTRAttributeIDTypeClusterAmbientContextSensingAttributePredictedActivityID ZGMTR_PROVISIONALLY_AVAILABLE = 0x0000000B,
    ZGMTRAttributeIDTypeClusterAmbientContextSensingAttributeSensorFusionSupportedID ZGMTR_PROVISIONALLY_AVAILABLE = 0x0000000C,
    ZGMTRAttributeIDTypeClusterAmbientContextSensingAttributeGeneratedCommandListID ZGMTR_PROVISIONALLY_AVAILABLE = ZGMTRAttributeIDTypeGlobalAttributeGeneratedCommandListID,
    ZGMTRAttributeIDTypeClusterAmbientContextSensingAttributeAcceptedCommandListID ZGMTR_PROVISIONALLY_AVAILABLE = ZGMTRAttributeIDTypeGlobalAttributeAcceptedCommandListID,
    ZGMTRAttributeIDTypeClusterAmbientContextSensingAttributeAttributeListID ZGMTR_PROVISIONALLY_AVAILABLE = ZGMTRAttributeIDTypeGlobalAttributeAttributeListID,
    ZGMTRAttributeIDTypeClusterAmbientContextSensingAttributeFeatureMapID ZGMTR_PROVISIONALLY_AVAILABLE = ZGMTRAttributeIDTypeGlobalAttributeFeatureMapID,
    ZGMTRAttributeIDTypeClusterAmbientContextSensingAttributeClusterRevisionID ZGMTR_PROVISIONALLY_AVAILABLE = ZGMTRAttributeIDTypeGlobalAttributeClusterRevisionID,

    // Cluster AmbientSensingUnion attributes
    ZGMTRAttributeIDTypeClusterAmbientSensingUnionAttributeUnionNameID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000000,
    ZGMTRAttributeIDTypeClusterAmbientSensingUnionAttributeUnionHealthID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000001,
    ZGMTRAttributeIDTypeClusterAmbientSensingUnionAttributeUnionContributorListID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000002,
    ZGMTRAttributeIDTypeClusterAmbientSensingUnionAttributeGeneratedCommandListID ZGMTR_PROVISIONALLY_AVAILABLE = ZGMTRAttributeIDTypeGlobalAttributeGeneratedCommandListID,
    ZGMTRAttributeIDTypeClusterAmbientSensingUnionAttributeAcceptedCommandListID ZGMTR_PROVISIONALLY_AVAILABLE = ZGMTRAttributeIDTypeGlobalAttributeAcceptedCommandListID,
    ZGMTRAttributeIDTypeClusterAmbientSensingUnionAttributeAttributeListID ZGMTR_PROVISIONALLY_AVAILABLE = ZGMTRAttributeIDTypeGlobalAttributeAttributeListID,
    ZGMTRAttributeIDTypeClusterAmbientSensingUnionAttributeFeatureMapID ZGMTR_PROVISIONALLY_AVAILABLE = ZGMTRAttributeIDTypeGlobalAttributeFeatureMapID,
    ZGMTRAttributeIDTypeClusterAmbientSensingUnionAttributeClusterRevisionID ZGMTR_PROVISIONALLY_AVAILABLE = ZGMTRAttributeIDTypeGlobalAttributeClusterRevisionID,

    // Cluster ProximityRanging attributes
    ZGMTRAttributeIDTypeClusterProximityRangingAttributeRangingCapabilitiesID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000000,
    ZGMTRAttributeIDTypeClusterProximityRangingAttributeWiFiDevIKID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000001,
    ZGMTRAttributeIDTypeClusterProximityRangingAttributeBLEDeviceIDID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000002,
    ZGMTRAttributeIDTypeClusterProximityRangingAttributeBLTDevIKID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000003,
    ZGMTRAttributeIDTypeClusterProximityRangingAttributeBLTCSSecurityLevelID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000004,
    ZGMTRAttributeIDTypeClusterProximityRangingAttributeBLTCSModeCapabilityID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000005,
    ZGMTRAttributeIDTypeClusterProximityRangingAttributeSessionIDListID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000006,
    ZGMTRAttributeIDTypeClusterProximityRangingAttributeGeneratedCommandListID ZGMTR_PROVISIONALLY_AVAILABLE = ZGMTRAttributeIDTypeGlobalAttributeGeneratedCommandListID,
    ZGMTRAttributeIDTypeClusterProximityRangingAttributeAcceptedCommandListID ZGMTR_PROVISIONALLY_AVAILABLE = ZGMTRAttributeIDTypeGlobalAttributeAcceptedCommandListID,
    ZGMTRAttributeIDTypeClusterProximityRangingAttributeAttributeListID ZGMTR_PROVISIONALLY_AVAILABLE = ZGMTRAttributeIDTypeGlobalAttributeAttributeListID,
    ZGMTRAttributeIDTypeClusterProximityRangingAttributeFeatureMapID ZGMTR_PROVISIONALLY_AVAILABLE = ZGMTRAttributeIDTypeGlobalAttributeFeatureMapID,
    ZGMTRAttributeIDTypeClusterProximityRangingAttributeClusterRevisionID ZGMTR_PROVISIONALLY_AVAILABLE = ZGMTRAttributeIDTypeGlobalAttributeClusterRevisionID,

    // Cluster SmokeConcentrationMeasurement attributes
    ZGMTRAttributeIDTypeClusterSmokeConcentrationMeasurementAttributeMeasuredValueID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000000,
    ZGMTRAttributeIDTypeClusterSmokeConcentrationMeasurementAttributeMinMeasuredValueID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000001,
    ZGMTRAttributeIDTypeClusterSmokeConcentrationMeasurementAttributeMaxMeasuredValueID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000002,
    ZGMTRAttributeIDTypeClusterSmokeConcentrationMeasurementAttributePeakMeasuredValueID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000003,
    ZGMTRAttributeIDTypeClusterSmokeConcentrationMeasurementAttributePeakMeasuredValueWindowID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000004,
    ZGMTRAttributeIDTypeClusterSmokeConcentrationMeasurementAttributeAverageMeasuredValueID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000005,
    ZGMTRAttributeIDTypeClusterSmokeConcentrationMeasurementAttributeAverageMeasuredValueWindowID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000006,
    ZGMTRAttributeIDTypeClusterSmokeConcentrationMeasurementAttributeUncertaintyID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000007,
    ZGMTRAttributeIDTypeClusterSmokeConcentrationMeasurementAttributeMeasurementUnitID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000008,
    ZGMTRAttributeIDTypeClusterSmokeConcentrationMeasurementAttributeMeasurementMediumID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000009,
    ZGMTRAttributeIDTypeClusterSmokeConcentrationMeasurementAttributeLevelValueID ZGMTR_PROVISIONALLY_AVAILABLE = 0x0000000A,
    ZGMTRAttributeIDTypeClusterSmokeConcentrationMeasurementAttributeGeneratedCommandListID ZGMTR_PROVISIONALLY_AVAILABLE = ZGMTRAttributeIDTypeGlobalAttributeGeneratedCommandListID,
    ZGMTRAttributeIDTypeClusterSmokeConcentrationMeasurementAttributeAcceptedCommandListID ZGMTR_PROVISIONALLY_AVAILABLE = ZGMTRAttributeIDTypeGlobalAttributeAcceptedCommandListID,
    ZGMTRAttributeIDTypeClusterSmokeConcentrationMeasurementAttributeAttributeListID ZGMTR_PROVISIONALLY_AVAILABLE = ZGMTRAttributeIDTypeGlobalAttributeAttributeListID,
    ZGMTRAttributeIDTypeClusterSmokeConcentrationMeasurementAttributeFeatureMapID ZGMTR_PROVISIONALLY_AVAILABLE = ZGMTRAttributeIDTypeGlobalAttributeFeatureMapID,
    ZGMTRAttributeIDTypeClusterSmokeConcentrationMeasurementAttributeClusterRevisionID ZGMTR_PROVISIONALLY_AVAILABLE = ZGMTRAttributeIDTypeGlobalAttributeClusterRevisionID,

    // Cluster NetworkIdentityManagement attributes
    ZGMTRAttributeIDTypeClusterNetworkIdentityManagementAttributeActiveNetworkIdentitiesID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000000,
    ZGMTRAttributeIDTypeClusterNetworkIdentityManagementAttributeClientsID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000001,
    ZGMTRAttributeIDTypeClusterNetworkIdentityManagementAttributeClientTableSizeID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000002,
    ZGMTRAttributeIDTypeClusterNetworkIdentityManagementAttributeGeneratedCommandListID ZGMTR_PROVISIONALLY_AVAILABLE = ZGMTRAttributeIDTypeGlobalAttributeGeneratedCommandListID,
    ZGMTRAttributeIDTypeClusterNetworkIdentityManagementAttributeAcceptedCommandListID ZGMTR_PROVISIONALLY_AVAILABLE = ZGMTRAttributeIDTypeGlobalAttributeAcceptedCommandListID,
    ZGMTRAttributeIDTypeClusterNetworkIdentityManagementAttributeAttributeListID ZGMTR_PROVISIONALLY_AVAILABLE = ZGMTRAttributeIDTypeGlobalAttributeAttributeListID,
    ZGMTRAttributeIDTypeClusterNetworkIdentityManagementAttributeFeatureMapID ZGMTR_PROVISIONALLY_AVAILABLE = ZGMTRAttributeIDTypeGlobalAttributeFeatureMapID,
    ZGMTRAttributeIDTypeClusterNetworkIdentityManagementAttributeClusterRevisionID ZGMTR_PROVISIONALLY_AVAILABLE = ZGMTRAttributeIDTypeGlobalAttributeClusterRevisionID,

    // Cluster WiFiNetworkManagement attributes
    ZGMTRAttributeIDTypeClusterWiFiNetworkManagementAttributeSSIDID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = 0x00000000,
    ZGMTRAttributeIDTypeClusterWiFiNetworkManagementAttributePassphraseSurrogateID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = 0x00000001,
    ZGMTRAttributeIDTypeClusterWiFiNetworkManagementAttributeGeneratedCommandListID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = ZGMTRAttributeIDTypeGlobalAttributeGeneratedCommandListID,
    ZGMTRAttributeIDTypeClusterWiFiNetworkManagementAttributeAcceptedCommandListID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = ZGMTRAttributeIDTypeGlobalAttributeAcceptedCommandListID,
    ZGMTRAttributeIDTypeClusterWiFiNetworkManagementAttributeAttributeListID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = ZGMTRAttributeIDTypeGlobalAttributeAttributeListID,
    ZGMTRAttributeIDTypeClusterWiFiNetworkManagementAttributeFeatureMapID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = ZGMTRAttributeIDTypeGlobalAttributeFeatureMapID,
    ZGMTRAttributeIDTypeClusterWiFiNetworkManagementAttributeClusterRevisionID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = ZGMTRAttributeIDTypeGlobalAttributeClusterRevisionID,

    // Cluster ThreadBorderRouterManagement attributes
    ZGMTRAttributeIDTypeClusterThreadBorderRouterManagementAttributeBorderRouterNameID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = 0x00000000,
    ZGMTRAttributeIDTypeClusterThreadBorderRouterManagementAttributeBorderAgentIDID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = 0x00000001,
    ZGMTRAttributeIDTypeClusterThreadBorderRouterManagementAttributeThreadVersionID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = 0x00000002,
    ZGMTRAttributeIDTypeClusterThreadBorderRouterManagementAttributeInterfaceEnabledID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = 0x00000003,
    ZGMTRAttributeIDTypeClusterThreadBorderRouterManagementAttributeActiveDatasetTimestampID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = 0x00000004,
    ZGMTRAttributeIDTypeClusterThreadBorderRouterManagementAttributePendingDatasetTimestampID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = 0x00000005,
    ZGMTRAttributeIDTypeClusterThreadBorderRouterManagementAttributeGeneratedCommandListID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = ZGMTRAttributeIDTypeGlobalAttributeGeneratedCommandListID,
    ZGMTRAttributeIDTypeClusterThreadBorderRouterManagementAttributeAcceptedCommandListID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = ZGMTRAttributeIDTypeGlobalAttributeAcceptedCommandListID,
    ZGMTRAttributeIDTypeClusterThreadBorderRouterManagementAttributeAttributeListID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = ZGMTRAttributeIDTypeGlobalAttributeAttributeListID,
    ZGMTRAttributeIDTypeClusterThreadBorderRouterManagementAttributeFeatureMapID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = ZGMTRAttributeIDTypeGlobalAttributeFeatureMapID,
    ZGMTRAttributeIDTypeClusterThreadBorderRouterManagementAttributeClusterRevisionID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = ZGMTRAttributeIDTypeGlobalAttributeClusterRevisionID,

    // Cluster ThreadNetworkDirectory attributes
    ZGMTRAttributeIDTypeClusterThreadNetworkDirectoryAttributePreferredExtendedPanIDID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = 0x00000000,
    ZGMTRAttributeIDTypeClusterThreadNetworkDirectoryAttributeThreadNetworksID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = 0x00000001,
    ZGMTRAttributeIDTypeClusterThreadNetworkDirectoryAttributeThreadNetworkTableSizeID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = 0x00000002,
    ZGMTRAttributeIDTypeClusterThreadNetworkDirectoryAttributeGeneratedCommandListID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = ZGMTRAttributeIDTypeGlobalAttributeGeneratedCommandListID,
    ZGMTRAttributeIDTypeClusterThreadNetworkDirectoryAttributeAcceptedCommandListID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = ZGMTRAttributeIDTypeGlobalAttributeAcceptedCommandListID,
    ZGMTRAttributeIDTypeClusterThreadNetworkDirectoryAttributeAttributeListID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = ZGMTRAttributeIDTypeGlobalAttributeAttributeListID,
    ZGMTRAttributeIDTypeClusterThreadNetworkDirectoryAttributeFeatureMapID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = ZGMTRAttributeIDTypeGlobalAttributeFeatureMapID,
    ZGMTRAttributeIDTypeClusterThreadNetworkDirectoryAttributeClusterRevisionID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = ZGMTRAttributeIDTypeGlobalAttributeClusterRevisionID,

    // Cluster CommissioningProxy attributes
    ZGMTRAttributeIDTypeClusterCommissioningProxyAttributeTransportID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000000,
    ZGMTRAttributeIDTypeClusterCommissioningProxyAttributeScanMaxTimeID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000001,
    ZGMTRAttributeIDTypeClusterCommissioningProxyAttributeMaxSessionsID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000002,
    ZGMTRAttributeIDTypeClusterCommissioningProxyAttributeMaxCachedResultsID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000003,
    ZGMTRAttributeIDTypeClusterCommissioningProxyAttributeNumCachedResultsID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000004,
    ZGMTRAttributeIDTypeClusterCommissioningProxyAttributeCacheTimeoutID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000005,
    ZGMTRAttributeIDTypeClusterCommissioningProxyAttributeCachedResultsID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000006,
    ZGMTRAttributeIDTypeClusterCommissioningProxyAttributeWiFiBandID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000007,
    ZGMTRAttributeIDTypeClusterCommissioningProxyAttributeGeneratedCommandListID ZGMTR_PROVISIONALLY_AVAILABLE = ZGMTRAttributeIDTypeGlobalAttributeGeneratedCommandListID,
    ZGMTRAttributeIDTypeClusterCommissioningProxyAttributeAcceptedCommandListID ZGMTR_PROVISIONALLY_AVAILABLE = ZGMTRAttributeIDTypeGlobalAttributeAcceptedCommandListID,
    ZGMTRAttributeIDTypeClusterCommissioningProxyAttributeAttributeListID ZGMTR_PROVISIONALLY_AVAILABLE = ZGMTRAttributeIDTypeGlobalAttributeAttributeListID,
    ZGMTRAttributeIDTypeClusterCommissioningProxyAttributeFeatureMapID ZGMTR_PROVISIONALLY_AVAILABLE = ZGMTRAttributeIDTypeGlobalAttributeFeatureMapID,
    ZGMTRAttributeIDTypeClusterCommissioningProxyAttributeClusterRevisionID ZGMTR_PROVISIONALLY_AVAILABLE = ZGMTRAttributeIDTypeGlobalAttributeClusterRevisionID,

    // Cluster WakeOnLan deprecated attribute names
    ZGMTRClusterWakeOnLanAttributeMACAddressID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterWakeOnLANAttributeMACAddressID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000000,
    ZGMTRClusterWakeOnLanAttributeGeneratedCommandListID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterWakeOnLANAttributeGeneratedCommandListID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = ZGMTRClusterGlobalAttributeGeneratedCommandListID,
    ZGMTRClusterWakeOnLanAttributeAcceptedCommandListID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterWakeOnLANAttributeAcceptedCommandListID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = ZGMTRClusterGlobalAttributeAcceptedCommandListID,
    ZGMTRClusterWakeOnLanAttributeAttributeListID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterWakeOnLANAttributeAttributeListID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = ZGMTRClusterGlobalAttributeAttributeListID,
    ZGMTRClusterWakeOnLanAttributeFeatureMapID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterWakeOnLANAttributeFeatureMapID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = ZGMTRClusterGlobalAttributeFeatureMapID,
    ZGMTRClusterWakeOnLanAttributeClusterRevisionID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterWakeOnLANAttributeClusterRevisionID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = ZGMTRClusterGlobalAttributeClusterRevisionID,

    // Cluster WakeOnLAN attributes
    ZGMTRAttributeIDTypeClusterWakeOnLANAttributeMACAddressID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000000,
    ZGMTRAttributeIDTypeClusterWakeOnLANAttributeLinkLocalAddressID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = 0x00000001,
    ZGMTRAttributeIDTypeClusterWakeOnLANAttributeGeneratedCommandListID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = ZGMTRAttributeIDTypeGlobalAttributeGeneratedCommandListID,
    ZGMTRAttributeIDTypeClusterWakeOnLANAttributeAcceptedCommandListID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = ZGMTRAttributeIDTypeGlobalAttributeAcceptedCommandListID,
    ZGMTRAttributeIDTypeClusterWakeOnLANAttributeAttributeListID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = ZGMTRAttributeIDTypeGlobalAttributeAttributeListID,
    ZGMTRAttributeIDTypeClusterWakeOnLANAttributeFeatureMapID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = ZGMTRAttributeIDTypeGlobalAttributeFeatureMapID,
    ZGMTRAttributeIDTypeClusterWakeOnLANAttributeClusterRevisionID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = ZGMTRAttributeIDTypeGlobalAttributeClusterRevisionID,

    // Cluster Channel deprecated attribute names
    ZGMTRClusterChannelAttributeChannelListID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterChannelAttributeChannelListID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000000,
    ZGMTRClusterChannelAttributeLineupID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterChannelAttributeLineupID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000001,
    ZGMTRClusterChannelAttributeCurrentChannelID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterChannelAttributeCurrentChannelID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000002,
    ZGMTRClusterChannelAttributeGeneratedCommandListID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterChannelAttributeGeneratedCommandListID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = ZGMTRClusterGlobalAttributeGeneratedCommandListID,
    ZGMTRClusterChannelAttributeAcceptedCommandListID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterChannelAttributeAcceptedCommandListID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = ZGMTRClusterGlobalAttributeAcceptedCommandListID,
    ZGMTRClusterChannelAttributeAttributeListID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterChannelAttributeAttributeListID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = ZGMTRClusterGlobalAttributeAttributeListID,
    ZGMTRClusterChannelAttributeFeatureMapID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterChannelAttributeFeatureMapID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = ZGMTRClusterGlobalAttributeFeatureMapID,
    ZGMTRClusterChannelAttributeClusterRevisionID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterChannelAttributeClusterRevisionID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = ZGMTRClusterGlobalAttributeClusterRevisionID,

    // Cluster Channel attributes
    ZGMTRAttributeIDTypeClusterChannelAttributeChannelListID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000000,
    ZGMTRAttributeIDTypeClusterChannelAttributeLineupID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000001,
    ZGMTRAttributeIDTypeClusterChannelAttributeCurrentChannelID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000002,
    ZGMTRAttributeIDTypeClusterChannelAttributeGeneratedCommandListID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = ZGMTRAttributeIDTypeGlobalAttributeGeneratedCommandListID,
    ZGMTRAttributeIDTypeClusterChannelAttributeAcceptedCommandListID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = ZGMTRAttributeIDTypeGlobalAttributeAcceptedCommandListID,
    ZGMTRAttributeIDTypeClusterChannelAttributeAttributeListID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = ZGMTRAttributeIDTypeGlobalAttributeAttributeListID,
    ZGMTRAttributeIDTypeClusterChannelAttributeFeatureMapID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = ZGMTRAttributeIDTypeGlobalAttributeFeatureMapID,
    ZGMTRAttributeIDTypeClusterChannelAttributeClusterRevisionID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = ZGMTRAttributeIDTypeGlobalAttributeClusterRevisionID,

    // Cluster TargetNavigator deprecated attribute names
    ZGMTRClusterTargetNavigatorAttributeTargetListID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterTargetNavigatorAttributeTargetListID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000000,
    ZGMTRClusterTargetNavigatorAttributeCurrentTargetID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterTargetNavigatorAttributeCurrentTargetID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000001,
    ZGMTRClusterTargetNavigatorAttributeGeneratedCommandListID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterTargetNavigatorAttributeGeneratedCommandListID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = ZGMTRClusterGlobalAttributeGeneratedCommandListID,
    ZGMTRClusterTargetNavigatorAttributeAcceptedCommandListID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterTargetNavigatorAttributeAcceptedCommandListID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = ZGMTRClusterGlobalAttributeAcceptedCommandListID,
    ZGMTRClusterTargetNavigatorAttributeAttributeListID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterTargetNavigatorAttributeAttributeListID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = ZGMTRClusterGlobalAttributeAttributeListID,
    ZGMTRClusterTargetNavigatorAttributeFeatureMapID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterTargetNavigatorAttributeFeatureMapID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = ZGMTRClusterGlobalAttributeFeatureMapID,
    ZGMTRClusterTargetNavigatorAttributeClusterRevisionID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterTargetNavigatorAttributeClusterRevisionID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = ZGMTRClusterGlobalAttributeClusterRevisionID,

    // Cluster TargetNavigator attributes
    ZGMTRAttributeIDTypeClusterTargetNavigatorAttributeTargetListID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000000,
    ZGMTRAttributeIDTypeClusterTargetNavigatorAttributeCurrentTargetID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000001,
    ZGMTRAttributeIDTypeClusterTargetNavigatorAttributeGeneratedCommandListID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = ZGMTRAttributeIDTypeGlobalAttributeGeneratedCommandListID,
    ZGMTRAttributeIDTypeClusterTargetNavigatorAttributeAcceptedCommandListID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = ZGMTRAttributeIDTypeGlobalAttributeAcceptedCommandListID,
    ZGMTRAttributeIDTypeClusterTargetNavigatorAttributeAttributeListID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = ZGMTRAttributeIDTypeGlobalAttributeAttributeListID,
    ZGMTRAttributeIDTypeClusterTargetNavigatorAttributeFeatureMapID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = ZGMTRAttributeIDTypeGlobalAttributeFeatureMapID,
    ZGMTRAttributeIDTypeClusterTargetNavigatorAttributeClusterRevisionID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = ZGMTRAttributeIDTypeGlobalAttributeClusterRevisionID,

    // Cluster MediaPlayback deprecated attribute names
    ZGMTRClusterMediaPlaybackAttributeCurrentStateID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterMediaPlaybackAttributeCurrentStateID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000000,
    ZGMTRClusterMediaPlaybackAttributeStartTimeID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterMediaPlaybackAttributeStartTimeID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000001,
    ZGMTRClusterMediaPlaybackAttributeDurationID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterMediaPlaybackAttributeDurationID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000002,
    ZGMTRClusterMediaPlaybackAttributeSampledPositionID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterMediaPlaybackAttributeSampledPositionID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000003,
    ZGMTRClusterMediaPlaybackAttributePlaybackSpeedID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterMediaPlaybackAttributePlaybackSpeedID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000004,
    ZGMTRClusterMediaPlaybackAttributeSeekRangeEndID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterMediaPlaybackAttributeSeekRangeEndID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000005,
    ZGMTRClusterMediaPlaybackAttributeSeekRangeStartID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterMediaPlaybackAttributeSeekRangeStartID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000006,
    ZGMTRClusterMediaPlaybackAttributeGeneratedCommandListID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterMediaPlaybackAttributeGeneratedCommandListID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = ZGMTRClusterGlobalAttributeGeneratedCommandListID,
    ZGMTRClusterMediaPlaybackAttributeAcceptedCommandListID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterMediaPlaybackAttributeAcceptedCommandListID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = ZGMTRClusterGlobalAttributeAcceptedCommandListID,
    ZGMTRClusterMediaPlaybackAttributeAttributeListID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterMediaPlaybackAttributeAttributeListID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = ZGMTRClusterGlobalAttributeAttributeListID,
    ZGMTRClusterMediaPlaybackAttributeFeatureMapID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterMediaPlaybackAttributeFeatureMapID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = ZGMTRClusterGlobalAttributeFeatureMapID,
    ZGMTRClusterMediaPlaybackAttributeClusterRevisionID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterMediaPlaybackAttributeClusterRevisionID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = ZGMTRClusterGlobalAttributeClusterRevisionID,

    // Cluster MediaPlayback attributes
    ZGMTRAttributeIDTypeClusterMediaPlaybackAttributeCurrentStateID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000000,
    ZGMTRAttributeIDTypeClusterMediaPlaybackAttributeStartTimeID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000001,
    ZGMTRAttributeIDTypeClusterMediaPlaybackAttributeDurationID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000002,
    ZGMTRAttributeIDTypeClusterMediaPlaybackAttributeSampledPositionID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000003,
    ZGMTRAttributeIDTypeClusterMediaPlaybackAttributePlaybackSpeedID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000004,
    ZGMTRAttributeIDTypeClusterMediaPlaybackAttributeSeekRangeEndID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000005,
    ZGMTRAttributeIDTypeClusterMediaPlaybackAttributeSeekRangeStartID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000006,
    ZGMTRAttributeIDTypeClusterMediaPlaybackAttributeActiveAudioTrackID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000007,
    ZGMTRAttributeIDTypeClusterMediaPlaybackAttributeAvailableAudioTracksID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000008,
    ZGMTRAttributeIDTypeClusterMediaPlaybackAttributeActiveTextTrackID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000009,
    ZGMTRAttributeIDTypeClusterMediaPlaybackAttributeAvailableTextTracksID ZGMTR_PROVISIONALLY_AVAILABLE = 0x0000000A,
    ZGMTRAttributeIDTypeClusterMediaPlaybackAttributeAvailableCommandsID ZGMTR_PROVISIONALLY_AVAILABLE = 0x0000000B,
    ZGMTRAttributeIDTypeClusterMediaPlaybackAttributeContentInfoID ZGMTR_PROVISIONALLY_AVAILABLE = 0x0000000C,
    ZGMTRAttributeIDTypeClusterMediaPlaybackAttributeGeneratedCommandListID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = ZGMTRAttributeIDTypeGlobalAttributeGeneratedCommandListID,
    ZGMTRAttributeIDTypeClusterMediaPlaybackAttributeAcceptedCommandListID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = ZGMTRAttributeIDTypeGlobalAttributeAcceptedCommandListID,
    ZGMTRAttributeIDTypeClusterMediaPlaybackAttributeAttributeListID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = ZGMTRAttributeIDTypeGlobalAttributeAttributeListID,
    ZGMTRAttributeIDTypeClusterMediaPlaybackAttributeFeatureMapID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = ZGMTRAttributeIDTypeGlobalAttributeFeatureMapID,
    ZGMTRAttributeIDTypeClusterMediaPlaybackAttributeClusterRevisionID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = ZGMTRAttributeIDTypeGlobalAttributeClusterRevisionID,

    // Cluster MediaInput deprecated attribute names
    ZGMTRClusterMediaInputAttributeInputListID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterMediaInputAttributeInputListID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000000,
    ZGMTRClusterMediaInputAttributeCurrentInputID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterMediaInputAttributeCurrentInputID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000001,
    ZGMTRClusterMediaInputAttributeGeneratedCommandListID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterMediaInputAttributeGeneratedCommandListID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = ZGMTRClusterGlobalAttributeGeneratedCommandListID,
    ZGMTRClusterMediaInputAttributeAcceptedCommandListID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterMediaInputAttributeAcceptedCommandListID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = ZGMTRClusterGlobalAttributeAcceptedCommandListID,
    ZGMTRClusterMediaInputAttributeAttributeListID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterMediaInputAttributeAttributeListID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = ZGMTRClusterGlobalAttributeAttributeListID,
    ZGMTRClusterMediaInputAttributeFeatureMapID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterMediaInputAttributeFeatureMapID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = ZGMTRClusterGlobalAttributeFeatureMapID,
    ZGMTRClusterMediaInputAttributeClusterRevisionID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterMediaInputAttributeClusterRevisionID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = ZGMTRClusterGlobalAttributeClusterRevisionID,

    // Cluster MediaInput attributes
    ZGMTRAttributeIDTypeClusterMediaInputAttributeInputListID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000000,
    ZGMTRAttributeIDTypeClusterMediaInputAttributeCurrentInputID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000001,
    ZGMTRAttributeIDTypeClusterMediaInputAttributeGeneratedCommandListID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = ZGMTRAttributeIDTypeGlobalAttributeGeneratedCommandListID,
    ZGMTRAttributeIDTypeClusterMediaInputAttributeAcceptedCommandListID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = ZGMTRAttributeIDTypeGlobalAttributeAcceptedCommandListID,
    ZGMTRAttributeIDTypeClusterMediaInputAttributeAttributeListID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = ZGMTRAttributeIDTypeGlobalAttributeAttributeListID,
    ZGMTRAttributeIDTypeClusterMediaInputAttributeFeatureMapID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = ZGMTRAttributeIDTypeGlobalAttributeFeatureMapID,
    ZGMTRAttributeIDTypeClusterMediaInputAttributeClusterRevisionID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = ZGMTRAttributeIDTypeGlobalAttributeClusterRevisionID,

    // Cluster LowPower deprecated attribute names
    ZGMTRClusterLowPowerAttributeGeneratedCommandListID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterLowPowerAttributeGeneratedCommandListID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = ZGMTRClusterGlobalAttributeGeneratedCommandListID,
    ZGMTRClusterLowPowerAttributeAcceptedCommandListID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterLowPowerAttributeAcceptedCommandListID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = ZGMTRClusterGlobalAttributeAcceptedCommandListID,
    ZGMTRClusterLowPowerAttributeAttributeListID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterLowPowerAttributeAttributeListID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = ZGMTRClusterGlobalAttributeAttributeListID,
    ZGMTRClusterLowPowerAttributeFeatureMapID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterLowPowerAttributeFeatureMapID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = ZGMTRClusterGlobalAttributeFeatureMapID,
    ZGMTRClusterLowPowerAttributeClusterRevisionID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterLowPowerAttributeClusterRevisionID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = ZGMTRClusterGlobalAttributeClusterRevisionID,

    // Cluster LowPower attributes
    ZGMTRAttributeIDTypeClusterLowPowerAttributeGeneratedCommandListID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = ZGMTRAttributeIDTypeGlobalAttributeGeneratedCommandListID,
    ZGMTRAttributeIDTypeClusterLowPowerAttributeAcceptedCommandListID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = ZGMTRAttributeIDTypeGlobalAttributeAcceptedCommandListID,
    ZGMTRAttributeIDTypeClusterLowPowerAttributeAttributeListID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = ZGMTRAttributeIDTypeGlobalAttributeAttributeListID,
    ZGMTRAttributeIDTypeClusterLowPowerAttributeFeatureMapID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = ZGMTRAttributeIDTypeGlobalAttributeFeatureMapID,
    ZGMTRAttributeIDTypeClusterLowPowerAttributeClusterRevisionID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = ZGMTRAttributeIDTypeGlobalAttributeClusterRevisionID,

    // Cluster KeypadInput deprecated attribute names
    ZGMTRClusterKeypadInputAttributeGeneratedCommandListID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterKeypadInputAttributeGeneratedCommandListID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = ZGMTRClusterGlobalAttributeGeneratedCommandListID,
    ZGMTRClusterKeypadInputAttributeAcceptedCommandListID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterKeypadInputAttributeAcceptedCommandListID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = ZGMTRClusterGlobalAttributeAcceptedCommandListID,
    ZGMTRClusterKeypadInputAttributeAttributeListID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterKeypadInputAttributeAttributeListID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = ZGMTRClusterGlobalAttributeAttributeListID,
    ZGMTRClusterKeypadInputAttributeFeatureMapID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterKeypadInputAttributeFeatureMapID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = ZGMTRClusterGlobalAttributeFeatureMapID,
    ZGMTRClusterKeypadInputAttributeClusterRevisionID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterKeypadInputAttributeClusterRevisionID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = ZGMTRClusterGlobalAttributeClusterRevisionID,

    // Cluster KeypadInput attributes
    ZGMTRAttributeIDTypeClusterKeypadInputAttributeGeneratedCommandListID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = ZGMTRAttributeIDTypeGlobalAttributeGeneratedCommandListID,
    ZGMTRAttributeIDTypeClusterKeypadInputAttributeAcceptedCommandListID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = ZGMTRAttributeIDTypeGlobalAttributeAcceptedCommandListID,
    ZGMTRAttributeIDTypeClusterKeypadInputAttributeAttributeListID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = ZGMTRAttributeIDTypeGlobalAttributeAttributeListID,
    ZGMTRAttributeIDTypeClusterKeypadInputAttributeFeatureMapID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = ZGMTRAttributeIDTypeGlobalAttributeFeatureMapID,
    ZGMTRAttributeIDTypeClusterKeypadInputAttributeClusterRevisionID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = ZGMTRAttributeIDTypeGlobalAttributeClusterRevisionID,

    // Cluster ContentLauncher deprecated attribute names
    ZGMTRClusterContentLauncherAttributeAcceptHeaderID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterContentLauncherAttributeAcceptHeaderID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000000,
    ZGMTRClusterContentLauncherAttributeSupportedStreamingProtocolsID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterContentLauncherAttributeSupportedStreamingProtocolsID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000001,
    ZGMTRClusterContentLauncherAttributeGeneratedCommandListID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterContentLauncherAttributeGeneratedCommandListID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = ZGMTRClusterGlobalAttributeGeneratedCommandListID,
    ZGMTRClusterContentLauncherAttributeAcceptedCommandListID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterContentLauncherAttributeAcceptedCommandListID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = ZGMTRClusterGlobalAttributeAcceptedCommandListID,
    ZGMTRClusterContentLauncherAttributeAttributeListID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterContentLauncherAttributeAttributeListID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = ZGMTRClusterGlobalAttributeAttributeListID,
    ZGMTRClusterContentLauncherAttributeFeatureMapID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterContentLauncherAttributeFeatureMapID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = ZGMTRClusterGlobalAttributeFeatureMapID,
    ZGMTRClusterContentLauncherAttributeClusterRevisionID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterContentLauncherAttributeClusterRevisionID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = ZGMTRClusterGlobalAttributeClusterRevisionID,

    // Cluster ContentLauncher attributes
    ZGMTRAttributeIDTypeClusterContentLauncherAttributeAcceptHeaderID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000000,
    ZGMTRAttributeIDTypeClusterContentLauncherAttributeSupportedStreamingProtocolsID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000001,
    ZGMTRAttributeIDTypeClusterContentLauncherAttributeMovableID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000002,
    ZGMTRAttributeIDTypeClusterContentLauncherAttributePresetsID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000003,
    ZGMTRAttributeIDTypeClusterContentLauncherAttributeGeneratedCommandListID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = ZGMTRAttributeIDTypeGlobalAttributeGeneratedCommandListID,
    ZGMTRAttributeIDTypeClusterContentLauncherAttributeAcceptedCommandListID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = ZGMTRAttributeIDTypeGlobalAttributeAcceptedCommandListID,
    ZGMTRAttributeIDTypeClusterContentLauncherAttributeAttributeListID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = ZGMTRAttributeIDTypeGlobalAttributeAttributeListID,
    ZGMTRAttributeIDTypeClusterContentLauncherAttributeFeatureMapID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = ZGMTRAttributeIDTypeGlobalAttributeFeatureMapID,
    ZGMTRAttributeIDTypeClusterContentLauncherAttributeClusterRevisionID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = ZGMTRAttributeIDTypeGlobalAttributeClusterRevisionID,

    // Cluster AudioOutput deprecated attribute names
    ZGMTRClusterAudioOutputAttributeOutputListID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterAudioOutputAttributeOutputListID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000000,
    ZGMTRClusterAudioOutputAttributeCurrentOutputID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterAudioOutputAttributeCurrentOutputID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000001,
    ZGMTRClusterAudioOutputAttributeGeneratedCommandListID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterAudioOutputAttributeGeneratedCommandListID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = ZGMTRClusterGlobalAttributeGeneratedCommandListID,
    ZGMTRClusterAudioOutputAttributeAcceptedCommandListID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterAudioOutputAttributeAcceptedCommandListID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = ZGMTRClusterGlobalAttributeAcceptedCommandListID,
    ZGMTRClusterAudioOutputAttributeAttributeListID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterAudioOutputAttributeAttributeListID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = ZGMTRClusterGlobalAttributeAttributeListID,
    ZGMTRClusterAudioOutputAttributeFeatureMapID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterAudioOutputAttributeFeatureMapID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = ZGMTRClusterGlobalAttributeFeatureMapID,
    ZGMTRClusterAudioOutputAttributeClusterRevisionID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterAudioOutputAttributeClusterRevisionID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = ZGMTRClusterGlobalAttributeClusterRevisionID,

    // Cluster AudioOutput attributes
    ZGMTRAttributeIDTypeClusterAudioOutputAttributeOutputListID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000000,
    ZGMTRAttributeIDTypeClusterAudioOutputAttributeCurrentOutputID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000001,
    ZGMTRAttributeIDTypeClusterAudioOutputAttributeGeneratedCommandListID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = ZGMTRAttributeIDTypeGlobalAttributeGeneratedCommandListID,
    ZGMTRAttributeIDTypeClusterAudioOutputAttributeAcceptedCommandListID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = ZGMTRAttributeIDTypeGlobalAttributeAcceptedCommandListID,
    ZGMTRAttributeIDTypeClusterAudioOutputAttributeAttributeListID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = ZGMTRAttributeIDTypeGlobalAttributeAttributeListID,
    ZGMTRAttributeIDTypeClusterAudioOutputAttributeFeatureMapID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = ZGMTRAttributeIDTypeGlobalAttributeFeatureMapID,
    ZGMTRAttributeIDTypeClusterAudioOutputAttributeClusterRevisionID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = ZGMTRAttributeIDTypeGlobalAttributeClusterRevisionID,

    // Cluster ApplicationLauncher deprecated attribute names
    ZGMTRClusterApplicationLauncherAttributeCatalogListID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterApplicationLauncherAttributeCatalogListID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000000,
    ZGMTRClusterApplicationLauncherAttributeCurrentAppID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterApplicationLauncherAttributeCurrentAppID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000001,
    ZGMTRClusterApplicationLauncherAttributeGeneratedCommandListID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterApplicationLauncherAttributeGeneratedCommandListID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = ZGMTRClusterGlobalAttributeGeneratedCommandListID,
    ZGMTRClusterApplicationLauncherAttributeAcceptedCommandListID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterApplicationLauncherAttributeAcceptedCommandListID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = ZGMTRClusterGlobalAttributeAcceptedCommandListID,
    ZGMTRClusterApplicationLauncherAttributeAttributeListID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterApplicationLauncherAttributeAttributeListID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = ZGMTRClusterGlobalAttributeAttributeListID,
    ZGMTRClusterApplicationLauncherAttributeFeatureMapID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterApplicationLauncherAttributeFeatureMapID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = ZGMTRClusterGlobalAttributeFeatureMapID,
    ZGMTRClusterApplicationLauncherAttributeClusterRevisionID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterApplicationLauncherAttributeClusterRevisionID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = ZGMTRClusterGlobalAttributeClusterRevisionID,

    // Cluster ApplicationLauncher attributes
    ZGMTRAttributeIDTypeClusterApplicationLauncherAttributeCatalogListID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000000,
    ZGMTRAttributeIDTypeClusterApplicationLauncherAttributeCurrentAppID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000001,
    ZGMTRAttributeIDTypeClusterApplicationLauncherAttributeGeneratedCommandListID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = ZGMTRAttributeIDTypeGlobalAttributeGeneratedCommandListID,
    ZGMTRAttributeIDTypeClusterApplicationLauncherAttributeAcceptedCommandListID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = ZGMTRAttributeIDTypeGlobalAttributeAcceptedCommandListID,
    ZGMTRAttributeIDTypeClusterApplicationLauncherAttributeAttributeListID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = ZGMTRAttributeIDTypeGlobalAttributeAttributeListID,
    ZGMTRAttributeIDTypeClusterApplicationLauncherAttributeFeatureMapID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = ZGMTRAttributeIDTypeGlobalAttributeFeatureMapID,
    ZGMTRAttributeIDTypeClusterApplicationLauncherAttributeClusterRevisionID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = ZGMTRAttributeIDTypeGlobalAttributeClusterRevisionID,

    // Cluster ApplicationBasic deprecated attribute names
    ZGMTRClusterApplicationBasicAttributeVendorNameID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterApplicationBasicAttributeVendorNameID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000000,
    ZGMTRClusterApplicationBasicAttributeVendorIDID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterApplicationBasicAttributeVendorIDID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000001,
    ZGMTRClusterApplicationBasicAttributeApplicationNameID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterApplicationBasicAttributeApplicationNameID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000002,
    ZGMTRClusterApplicationBasicAttributeProductIDID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterApplicationBasicAttributeProductIDID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000003,
    ZGMTRClusterApplicationBasicAttributeApplicationID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterApplicationBasicAttributeApplicationID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000004,
    ZGMTRClusterApplicationBasicAttributeStatusID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterApplicationBasicAttributeStatusID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000005,
    ZGMTRClusterApplicationBasicAttributeApplicationVersionID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterApplicationBasicAttributeApplicationVersionID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000006,
    ZGMTRClusterApplicationBasicAttributeAllowedVendorListID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterApplicationBasicAttributeAllowedVendorListID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000007,
    ZGMTRClusterApplicationBasicAttributeGeneratedCommandListID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterApplicationBasicAttributeGeneratedCommandListID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = ZGMTRClusterGlobalAttributeGeneratedCommandListID,
    ZGMTRClusterApplicationBasicAttributeAcceptedCommandListID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterApplicationBasicAttributeAcceptedCommandListID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = ZGMTRClusterGlobalAttributeAcceptedCommandListID,
    ZGMTRClusterApplicationBasicAttributeAttributeListID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterApplicationBasicAttributeAttributeListID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = ZGMTRClusterGlobalAttributeAttributeListID,
    ZGMTRClusterApplicationBasicAttributeFeatureMapID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterApplicationBasicAttributeFeatureMapID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = ZGMTRClusterGlobalAttributeFeatureMapID,
    ZGMTRClusterApplicationBasicAttributeClusterRevisionID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterApplicationBasicAttributeClusterRevisionID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = ZGMTRClusterGlobalAttributeClusterRevisionID,

    // Cluster ApplicationBasic attributes
    ZGMTRAttributeIDTypeClusterApplicationBasicAttributeVendorNameID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000000,
    ZGMTRAttributeIDTypeClusterApplicationBasicAttributeVendorIDID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000001,
    ZGMTRAttributeIDTypeClusterApplicationBasicAttributeApplicationNameID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000002,
    ZGMTRAttributeIDTypeClusterApplicationBasicAttributeProductIDID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000003,
    ZGMTRAttributeIDTypeClusterApplicationBasicAttributeApplicationID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000004,
    ZGMTRAttributeIDTypeClusterApplicationBasicAttributeStatusID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000005,
    ZGMTRAttributeIDTypeClusterApplicationBasicAttributeApplicationVersionID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000006,
    ZGMTRAttributeIDTypeClusterApplicationBasicAttributeAllowedVendorListID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000007,
    ZGMTRAttributeIDTypeClusterApplicationBasicAttributeGeneratedCommandListID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = ZGMTRAttributeIDTypeGlobalAttributeGeneratedCommandListID,
    ZGMTRAttributeIDTypeClusterApplicationBasicAttributeAcceptedCommandListID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = ZGMTRAttributeIDTypeGlobalAttributeAcceptedCommandListID,
    ZGMTRAttributeIDTypeClusterApplicationBasicAttributeAttributeListID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = ZGMTRAttributeIDTypeGlobalAttributeAttributeListID,
    ZGMTRAttributeIDTypeClusterApplicationBasicAttributeFeatureMapID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = ZGMTRAttributeIDTypeGlobalAttributeFeatureMapID,
    ZGMTRAttributeIDTypeClusterApplicationBasicAttributeClusterRevisionID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = ZGMTRAttributeIDTypeGlobalAttributeClusterRevisionID,

    // Cluster AccountLogin deprecated attribute names
    ZGMTRClusterAccountLoginAttributeGeneratedCommandListID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterAccountLoginAttributeGeneratedCommandListID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = ZGMTRClusterGlobalAttributeGeneratedCommandListID,
    ZGMTRClusterAccountLoginAttributeAcceptedCommandListID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterAccountLoginAttributeAcceptedCommandListID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = ZGMTRClusterGlobalAttributeAcceptedCommandListID,
    ZGMTRClusterAccountLoginAttributeAttributeListID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterAccountLoginAttributeAttributeListID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = ZGMTRClusterGlobalAttributeAttributeListID,
    ZGMTRClusterAccountLoginAttributeFeatureMapID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterAccountLoginAttributeFeatureMapID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = ZGMTRClusterGlobalAttributeFeatureMapID,
    ZGMTRClusterAccountLoginAttributeClusterRevisionID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterAccountLoginAttributeClusterRevisionID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = ZGMTRClusterGlobalAttributeClusterRevisionID,

    // Cluster AccountLogin attributes
    ZGMTRAttributeIDTypeClusterAccountLoginAttributeGeneratedCommandListID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = ZGMTRAttributeIDTypeGlobalAttributeGeneratedCommandListID,
    ZGMTRAttributeIDTypeClusterAccountLoginAttributeAcceptedCommandListID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = ZGMTRAttributeIDTypeGlobalAttributeAcceptedCommandListID,
    ZGMTRAttributeIDTypeClusterAccountLoginAttributeAttributeListID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = ZGMTRAttributeIDTypeGlobalAttributeAttributeListID,
    ZGMTRAttributeIDTypeClusterAccountLoginAttributeFeatureMapID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = ZGMTRAttributeIDTypeGlobalAttributeFeatureMapID,
    ZGMTRAttributeIDTypeClusterAccountLoginAttributeClusterRevisionID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = ZGMTRAttributeIDTypeGlobalAttributeClusterRevisionID,

    // Cluster ContentControl attributes
    ZGMTRAttributeIDTypeClusterContentControlAttributeEnabledID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000000,
    ZGMTRAttributeIDTypeClusterContentControlAttributeOnDemandRatingsID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000001,
    ZGMTRAttributeIDTypeClusterContentControlAttributeOnDemandRatingThresholdID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000002,
    ZGMTRAttributeIDTypeClusterContentControlAttributeScheduledContentRatingsID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000003,
    ZGMTRAttributeIDTypeClusterContentControlAttributeScheduledContentRatingThresholdID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000004,
    ZGMTRAttributeIDTypeClusterContentControlAttributeScreenDailyTimeID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000005,
    ZGMTRAttributeIDTypeClusterContentControlAttributeRemainingScreenTimeID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000006,
    ZGMTRAttributeIDTypeClusterContentControlAttributeBlockUnratedID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000007,
    ZGMTRAttributeIDTypeClusterContentControlAttributeBlockChannelListID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000008,
    ZGMTRAttributeIDTypeClusterContentControlAttributeBlockApplicationListID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000009,
    ZGMTRAttributeIDTypeClusterContentControlAttributeBlockContentTimeWindowID ZGMTR_PROVISIONALLY_AVAILABLE = 0x0000000A,
    ZGMTRAttributeIDTypeClusterContentControlAttributeGeneratedCommandListID ZGMTR_PROVISIONALLY_AVAILABLE = ZGMTRAttributeIDTypeGlobalAttributeGeneratedCommandListID,
    ZGMTRAttributeIDTypeClusterContentControlAttributeAcceptedCommandListID ZGMTR_PROVISIONALLY_AVAILABLE = ZGMTRAttributeIDTypeGlobalAttributeAcceptedCommandListID,
    ZGMTRAttributeIDTypeClusterContentControlAttributeAttributeListID ZGMTR_PROVISIONALLY_AVAILABLE = ZGMTRAttributeIDTypeGlobalAttributeAttributeListID,
    ZGMTRAttributeIDTypeClusterContentControlAttributeFeatureMapID ZGMTR_PROVISIONALLY_AVAILABLE = ZGMTRAttributeIDTypeGlobalAttributeFeatureMapID,
    ZGMTRAttributeIDTypeClusterContentControlAttributeClusterRevisionID ZGMTR_PROVISIONALLY_AVAILABLE = ZGMTRAttributeIDTypeGlobalAttributeClusterRevisionID,

    // Cluster ContentAppObserver attributes
    ZGMTRAttributeIDTypeClusterContentAppObserverAttributeGeneratedCommandListID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = ZGMTRAttributeIDTypeGlobalAttributeGeneratedCommandListID,
    ZGMTRAttributeIDTypeClusterContentAppObserverAttributeAcceptedCommandListID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = ZGMTRAttributeIDTypeGlobalAttributeAcceptedCommandListID,
    ZGMTRAttributeIDTypeClusterContentAppObserverAttributeAttributeListID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = ZGMTRAttributeIDTypeGlobalAttributeAttributeListID,
    ZGMTRAttributeIDTypeClusterContentAppObserverAttributeFeatureMapID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = ZGMTRAttributeIDTypeGlobalAttributeFeatureMapID,
    ZGMTRAttributeIDTypeClusterContentAppObserverAttributeClusterRevisionID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = ZGMTRAttributeIDTypeGlobalAttributeClusterRevisionID,

    // Cluster MediaFileManagement attributes
    ZGMTRAttributeIDTypeClusterMediaFileManagementAttributeTotalStorageID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000000,
    ZGMTRAttributeIDTypeClusterMediaFileManagementAttributeAvailableStorageID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000001,
    ZGMTRAttributeIDTypeClusterMediaFileManagementAttributeAvailableFilesID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000002,
    ZGMTRAttributeIDTypeClusterMediaFileManagementAttributeSupportedMimeTypesID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000003,
    ZGMTRAttributeIDTypeClusterMediaFileManagementAttributeGeneratedCommandListID ZGMTR_PROVISIONALLY_AVAILABLE = ZGMTRAttributeIDTypeGlobalAttributeGeneratedCommandListID,
    ZGMTRAttributeIDTypeClusterMediaFileManagementAttributeAcceptedCommandListID ZGMTR_PROVISIONALLY_AVAILABLE = ZGMTRAttributeIDTypeGlobalAttributeAcceptedCommandListID,
    ZGMTRAttributeIDTypeClusterMediaFileManagementAttributeAttributeListID ZGMTR_PROVISIONALLY_AVAILABLE = ZGMTRAttributeIDTypeGlobalAttributeAttributeListID,
    ZGMTRAttributeIDTypeClusterMediaFileManagementAttributeFeatureMapID ZGMTR_PROVISIONALLY_AVAILABLE = ZGMTRAttributeIDTypeGlobalAttributeFeatureMapID,
    ZGMTRAttributeIDTypeClusterMediaFileManagementAttributeClusterRevisionID ZGMTR_PROVISIONALLY_AVAILABLE = ZGMTRAttributeIDTypeGlobalAttributeClusterRevisionID,

    // Cluster AudioControl attributes
    ZGMTRAttributeIDTypeClusterAudioControlAttributeSoftMutedID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000000,
    ZGMTRAttributeIDTypeClusterAudioControlAttributePhysicallyMutedID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000001,
    ZGMTRAttributeIDTypeClusterAudioControlAttributeVolumeID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000002,
    ZGMTRAttributeIDTypeClusterAudioControlAttributeMinDeviceVolumeID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000003,
    ZGMTRAttributeIDTypeClusterAudioControlAttributeMaxDeviceVolumeID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000004,
    ZGMTRAttributeIDTypeClusterAudioControlAttributeMaxDeviceVolumeDBID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000005,
    ZGMTRAttributeIDTypeClusterAudioControlAttributeMaxUserVolumeID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000006,
    ZGMTRAttributeIDTypeClusterAudioControlAttributeDefaultStepSizeID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000007,
    ZGMTRAttributeIDTypeClusterAudioControlAttributeSetVolumeUnmutePolicyID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000008,
    ZGMTRAttributeIDTypeClusterAudioControlAttributeIncreaseVolumeUnmutePolicyID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000009,
    ZGMTRAttributeIDTypeClusterAudioControlAttributeIncreaseVolumeUnmuteVolumeID ZGMTR_PROVISIONALLY_AVAILABLE = 0x0000000A,
    ZGMTRAttributeIDTypeClusterAudioControlAttributeDecreaseVolumeUnmutePolicyID ZGMTR_PROVISIONALLY_AVAILABLE = 0x0000000B,
    ZGMTRAttributeIDTypeClusterAudioControlAttributeStartUpMutedID ZGMTR_PROVISIONALLY_AVAILABLE = 0x0000000C,
    ZGMTRAttributeIDTypeClusterAudioControlAttributeStartUpVolumeID ZGMTR_PROVISIONALLY_AVAILABLE = 0x0000000D,
    ZGMTRAttributeIDTypeClusterAudioControlAttributeBassID ZGMTR_PROVISIONALLY_AVAILABLE = 0x0000000E,
    ZGMTRAttributeIDTypeClusterAudioControlAttributeMidID ZGMTR_PROVISIONALLY_AVAILABLE = 0x0000000F,
    ZGMTRAttributeIDTypeClusterAudioControlAttributeTrebleID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000010,
    ZGMTRAttributeIDTypeClusterAudioControlAttributeMinCorrectionID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000011,
    ZGMTRAttributeIDTypeClusterAudioControlAttributeMaxCorrectionID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000012,
    ZGMTRAttributeIDTypeClusterAudioControlAttributeGeneratedCommandListID ZGMTR_PROVISIONALLY_AVAILABLE = ZGMTRAttributeIDTypeGlobalAttributeGeneratedCommandListID,
    ZGMTRAttributeIDTypeClusterAudioControlAttributeAcceptedCommandListID ZGMTR_PROVISIONALLY_AVAILABLE = ZGMTRAttributeIDTypeGlobalAttributeAcceptedCommandListID,
    ZGMTRAttributeIDTypeClusterAudioControlAttributeAttributeListID ZGMTR_PROVISIONALLY_AVAILABLE = ZGMTRAttributeIDTypeGlobalAttributeAttributeListID,
    ZGMTRAttributeIDTypeClusterAudioControlAttributeFeatureMapID ZGMTR_PROVISIONALLY_AVAILABLE = ZGMTRAttributeIDTypeGlobalAttributeFeatureMapID,
    ZGMTRAttributeIDTypeClusterAudioControlAttributeClusterRevisionID ZGMTR_PROVISIONALLY_AVAILABLE = ZGMTRAttributeIDTypeGlobalAttributeClusterRevisionID,

    // Cluster ZoneManagement attributes
    ZGMTRAttributeIDTypeClusterZoneManagementAttributeMaxUserDefinedZonesID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000000,
    ZGMTRAttributeIDTypeClusterZoneManagementAttributeMaxZonesID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000001,
    ZGMTRAttributeIDTypeClusterZoneManagementAttributeZonesID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000002,
    ZGMTRAttributeIDTypeClusterZoneManagementAttributeTriggersID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000003,
    ZGMTRAttributeIDTypeClusterZoneManagementAttributeSensitivityMaxID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000004,
    ZGMTRAttributeIDTypeClusterZoneManagementAttributeSensitivityID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000005,
    ZGMTRAttributeIDTypeClusterZoneManagementAttributeTwoDCartesianMaxID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000006,
    ZGMTRAttributeIDTypeClusterZoneManagementAttributeGeneratedCommandListID ZGMTR_PROVISIONALLY_AVAILABLE = ZGMTRAttributeIDTypeGlobalAttributeGeneratedCommandListID,
    ZGMTRAttributeIDTypeClusterZoneManagementAttributeAcceptedCommandListID ZGMTR_PROVISIONALLY_AVAILABLE = ZGMTRAttributeIDTypeGlobalAttributeAcceptedCommandListID,
    ZGMTRAttributeIDTypeClusterZoneManagementAttributeAttributeListID ZGMTR_PROVISIONALLY_AVAILABLE = ZGMTRAttributeIDTypeGlobalAttributeAttributeListID,
    ZGMTRAttributeIDTypeClusterZoneManagementAttributeFeatureMapID ZGMTR_PROVISIONALLY_AVAILABLE = ZGMTRAttributeIDTypeGlobalAttributeFeatureMapID,
    ZGMTRAttributeIDTypeClusterZoneManagementAttributeClusterRevisionID ZGMTR_PROVISIONALLY_AVAILABLE = ZGMTRAttributeIDTypeGlobalAttributeClusterRevisionID,

    // Cluster CameraAVStreamManagement attributes
    ZGMTRAttributeIDTypeClusterCameraAVStreamManagementAttributeMaxConcurrentEncodersID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000000,
    ZGMTRAttributeIDTypeClusterCameraAVStreamManagementAttributeMaxEncodedPixelRateID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000001,
    ZGMTRAttributeIDTypeClusterCameraAVStreamManagementAttributeVideoSensorParamsID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000002,
    ZGMTRAttributeIDTypeClusterCameraAVStreamManagementAttributeNightVisionUsesInfraredID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000003,
    ZGMTRAttributeIDTypeClusterCameraAVStreamManagementAttributeMinViewportResolutionID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000004,
    ZGMTRAttributeIDTypeClusterCameraAVStreamManagementAttributeRateDistortionTradeOffPointsID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000005,
    ZGMTRAttributeIDTypeClusterCameraAVStreamManagementAttributeMaxContentBufferSizeID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000006,
    ZGMTRAttributeIDTypeClusterCameraAVStreamManagementAttributeMicrophoneCapabilitiesID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000007,
    ZGMTRAttributeIDTypeClusterCameraAVStreamManagementAttributeSpeakerCapabilitiesID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000008,
    ZGMTRAttributeIDTypeClusterCameraAVStreamManagementAttributeTwoWayTalkSupportID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000009,
    ZGMTRAttributeIDTypeClusterCameraAVStreamManagementAttributeSnapshotCapabilitiesID ZGMTR_PROVISIONALLY_AVAILABLE = 0x0000000A,
    ZGMTRAttributeIDTypeClusterCameraAVStreamManagementAttributeMaxNetworkBandwidthID ZGMTR_PROVISIONALLY_AVAILABLE = 0x0000000B,
    ZGMTRAttributeIDTypeClusterCameraAVStreamManagementAttributeCurrentFrameRateID ZGMTR_PROVISIONALLY_AVAILABLE = 0x0000000C,
    ZGMTRAttributeIDTypeClusterCameraAVStreamManagementAttributeHDRModeEnabledID ZGMTR_PROVISIONALLY_AVAILABLE = 0x0000000D,
    ZGMTRAttributeIDTypeClusterCameraAVStreamManagementAttributeSupportedStreamUsagesID ZGMTR_PROVISIONALLY_AVAILABLE = 0x0000000E,
    ZGMTRAttributeIDTypeClusterCameraAVStreamManagementAttributeAllocatedVideoStreamsID ZGMTR_PROVISIONALLY_AVAILABLE = 0x0000000F,
    ZGMTRAttributeIDTypeClusterCameraAVStreamManagementAttributeAllocatedAudioStreamsID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000010,
    ZGMTRAttributeIDTypeClusterCameraAVStreamManagementAttributeAllocatedSnapshotStreamsID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000011,
    ZGMTRAttributeIDTypeClusterCameraAVStreamManagementAttributeStreamUsagePrioritiesID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000012,
    ZGMTRAttributeIDTypeClusterCameraAVStreamManagementAttributeSoftRecordingPrivacyModeEnabledID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000013,
    ZGMTRAttributeIDTypeClusterCameraAVStreamManagementAttributeSoftLivestreamPrivacyModeEnabledID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000014,
    ZGMTRAttributeIDTypeClusterCameraAVStreamManagementAttributeHardPrivacyModeOnID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000015,
    ZGMTRAttributeIDTypeClusterCameraAVStreamManagementAttributeNightVisionID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000016,
    ZGMTRAttributeIDTypeClusterCameraAVStreamManagementAttributeNightVisionIllumID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000017,
    ZGMTRAttributeIDTypeClusterCameraAVStreamManagementAttributeViewportID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000018,
    ZGMTRAttributeIDTypeClusterCameraAVStreamManagementAttributeSpeakerMutedID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000019,
    ZGMTRAttributeIDTypeClusterCameraAVStreamManagementAttributeSpeakerVolumeLevelID ZGMTR_PROVISIONALLY_AVAILABLE = 0x0000001A,
    ZGMTRAttributeIDTypeClusterCameraAVStreamManagementAttributeSpeakerMaxLevelID ZGMTR_PROVISIONALLY_AVAILABLE = 0x0000001B,
    ZGMTRAttributeIDTypeClusterCameraAVStreamManagementAttributeSpeakerMinLevelID ZGMTR_PROVISIONALLY_AVAILABLE = 0x0000001C,
    ZGMTRAttributeIDTypeClusterCameraAVStreamManagementAttributeMicrophoneMutedID ZGMTR_PROVISIONALLY_AVAILABLE = 0x0000001D,
    ZGMTRAttributeIDTypeClusterCameraAVStreamManagementAttributeMicrophoneVolumeLevelID ZGMTR_PROVISIONALLY_AVAILABLE = 0x0000001E,
    ZGMTRAttributeIDTypeClusterCameraAVStreamManagementAttributeMicrophoneMaxLevelID ZGMTR_PROVISIONALLY_AVAILABLE = 0x0000001F,
    ZGMTRAttributeIDTypeClusterCameraAVStreamManagementAttributeMicrophoneMinLevelID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000020,
    ZGMTRAttributeIDTypeClusterCameraAVStreamManagementAttributeMicrophoneAGCEnabledID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000021,
    ZGMTRAttributeIDTypeClusterCameraAVStreamManagementAttributeImageRotationID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000022,
    ZGMTRAttributeIDTypeClusterCameraAVStreamManagementAttributeImageFlipHorizontalID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000023,
    ZGMTRAttributeIDTypeClusterCameraAVStreamManagementAttributeImageFlipVerticalID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000024,
    ZGMTRAttributeIDTypeClusterCameraAVStreamManagementAttributeLocalVideoRecordingEnabledID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000025,
    ZGMTRAttributeIDTypeClusterCameraAVStreamManagementAttributeLocalSnapshotRecordingEnabledID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000026,
    ZGMTRAttributeIDTypeClusterCameraAVStreamManagementAttributeStatusLightEnabledID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000027,
    ZGMTRAttributeIDTypeClusterCameraAVStreamManagementAttributeStatusLightBrightnessID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000028,
    ZGMTRAttributeIDTypeClusterCameraAVStreamManagementAttributeImageRotationDiscreteAnglesID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000029,
    ZGMTRAttributeIDTypeClusterCameraAVStreamManagementAttributeGeneratedCommandListID ZGMTR_PROVISIONALLY_AVAILABLE = ZGMTRAttributeIDTypeGlobalAttributeGeneratedCommandListID,
    ZGMTRAttributeIDTypeClusterCameraAVStreamManagementAttributeAcceptedCommandListID ZGMTR_PROVISIONALLY_AVAILABLE = ZGMTRAttributeIDTypeGlobalAttributeAcceptedCommandListID,
    ZGMTRAttributeIDTypeClusterCameraAVStreamManagementAttributeAttributeListID ZGMTR_PROVISIONALLY_AVAILABLE = ZGMTRAttributeIDTypeGlobalAttributeAttributeListID,
    ZGMTRAttributeIDTypeClusterCameraAVStreamManagementAttributeFeatureMapID ZGMTR_PROVISIONALLY_AVAILABLE = ZGMTRAttributeIDTypeGlobalAttributeFeatureMapID,
    ZGMTRAttributeIDTypeClusterCameraAVStreamManagementAttributeClusterRevisionID ZGMTR_PROVISIONALLY_AVAILABLE = ZGMTRAttributeIDTypeGlobalAttributeClusterRevisionID,

    // Cluster CameraAVSettingsUserLevelManagement attributes
    ZGMTRAttributeIDTypeClusterCameraAVSettingsUserLevelManagementAttributeMPTZPositionID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000000,
    ZGMTRAttributeIDTypeClusterCameraAVSettingsUserLevelManagementAttributeMaxPresetsID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000001,
    ZGMTRAttributeIDTypeClusterCameraAVSettingsUserLevelManagementAttributeMPTZPresetsID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000002,
    ZGMTRAttributeIDTypeClusterCameraAVSettingsUserLevelManagementAttributeDPTZStreamsID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000003,
    ZGMTRAttributeIDTypeClusterCameraAVSettingsUserLevelManagementAttributeZoomMaxID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000004,
    ZGMTRAttributeIDTypeClusterCameraAVSettingsUserLevelManagementAttributeTiltMinID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000005,
    ZGMTRAttributeIDTypeClusterCameraAVSettingsUserLevelManagementAttributeTiltMaxID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000006,
    ZGMTRAttributeIDTypeClusterCameraAVSettingsUserLevelManagementAttributePanMinID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000007,
    ZGMTRAttributeIDTypeClusterCameraAVSettingsUserLevelManagementAttributePanMaxID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000008,
    ZGMTRAttributeIDTypeClusterCameraAVSettingsUserLevelManagementAttributeMovementStateID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000009,
    ZGMTRAttributeIDTypeClusterCameraAVSettingsUserLevelManagementAttributeGeneratedCommandListID ZGMTR_PROVISIONALLY_AVAILABLE = ZGMTRAttributeIDTypeGlobalAttributeGeneratedCommandListID,
    ZGMTRAttributeIDTypeClusterCameraAVSettingsUserLevelManagementAttributeAcceptedCommandListID ZGMTR_PROVISIONALLY_AVAILABLE = ZGMTRAttributeIDTypeGlobalAttributeAcceptedCommandListID,
    ZGMTRAttributeIDTypeClusterCameraAVSettingsUserLevelManagementAttributeAttributeListID ZGMTR_PROVISIONALLY_AVAILABLE = ZGMTRAttributeIDTypeGlobalAttributeAttributeListID,
    ZGMTRAttributeIDTypeClusterCameraAVSettingsUserLevelManagementAttributeFeatureMapID ZGMTR_PROVISIONALLY_AVAILABLE = ZGMTRAttributeIDTypeGlobalAttributeFeatureMapID,
    ZGMTRAttributeIDTypeClusterCameraAVSettingsUserLevelManagementAttributeClusterRevisionID ZGMTR_PROVISIONALLY_AVAILABLE = ZGMTRAttributeIDTypeGlobalAttributeClusterRevisionID,

    // Cluster WebRTCTransportProvider attributes
    ZGMTRAttributeIDTypeClusterWebRTCTransportProviderAttributeCurrentSessionsID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000000,
    ZGMTRAttributeIDTypeClusterWebRTCTransportProviderAttributeGeneratedCommandListID ZGMTR_PROVISIONALLY_AVAILABLE = ZGMTRAttributeIDTypeGlobalAttributeGeneratedCommandListID,
    ZGMTRAttributeIDTypeClusterWebRTCTransportProviderAttributeAcceptedCommandListID ZGMTR_PROVISIONALLY_AVAILABLE = ZGMTRAttributeIDTypeGlobalAttributeAcceptedCommandListID,
    ZGMTRAttributeIDTypeClusterWebRTCTransportProviderAttributeAttributeListID ZGMTR_PROVISIONALLY_AVAILABLE = ZGMTRAttributeIDTypeGlobalAttributeAttributeListID,
    ZGMTRAttributeIDTypeClusterWebRTCTransportProviderAttributeFeatureMapID ZGMTR_PROVISIONALLY_AVAILABLE = ZGMTRAttributeIDTypeGlobalAttributeFeatureMapID,
    ZGMTRAttributeIDTypeClusterWebRTCTransportProviderAttributeClusterRevisionID ZGMTR_PROVISIONALLY_AVAILABLE = ZGMTRAttributeIDTypeGlobalAttributeClusterRevisionID,

    // Cluster WebRTCTransportRequestor attributes
    ZGMTRAttributeIDTypeClusterWebRTCTransportRequestorAttributeCurrentSessionsID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000000,
    ZGMTRAttributeIDTypeClusterWebRTCTransportRequestorAttributeGeneratedCommandListID ZGMTR_PROVISIONALLY_AVAILABLE = ZGMTRAttributeIDTypeGlobalAttributeGeneratedCommandListID,
    ZGMTRAttributeIDTypeClusterWebRTCTransportRequestorAttributeAcceptedCommandListID ZGMTR_PROVISIONALLY_AVAILABLE = ZGMTRAttributeIDTypeGlobalAttributeAcceptedCommandListID,
    ZGMTRAttributeIDTypeClusterWebRTCTransportRequestorAttributeAttributeListID ZGMTR_PROVISIONALLY_AVAILABLE = ZGMTRAttributeIDTypeGlobalAttributeAttributeListID,
    ZGMTRAttributeIDTypeClusterWebRTCTransportRequestorAttributeFeatureMapID ZGMTR_PROVISIONALLY_AVAILABLE = ZGMTRAttributeIDTypeGlobalAttributeFeatureMapID,
    ZGMTRAttributeIDTypeClusterWebRTCTransportRequestorAttributeClusterRevisionID ZGMTR_PROVISIONALLY_AVAILABLE = ZGMTRAttributeIDTypeGlobalAttributeClusterRevisionID,

    // Cluster PushAVStreamTransport attributes
    ZGMTRAttributeIDTypeClusterPushAVStreamTransportAttributeSupportedFormatsID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000000,
    ZGMTRAttributeIDTypeClusterPushAVStreamTransportAttributeCurrentConnectionsID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000001,
    ZGMTRAttributeIDTypeClusterPushAVStreamTransportAttributeGeneratedCommandListID ZGMTR_PROVISIONALLY_AVAILABLE = ZGMTRAttributeIDTypeGlobalAttributeGeneratedCommandListID,
    ZGMTRAttributeIDTypeClusterPushAVStreamTransportAttributeAcceptedCommandListID ZGMTR_PROVISIONALLY_AVAILABLE = ZGMTRAttributeIDTypeGlobalAttributeAcceptedCommandListID,
    ZGMTRAttributeIDTypeClusterPushAVStreamTransportAttributeAttributeListID ZGMTR_PROVISIONALLY_AVAILABLE = ZGMTRAttributeIDTypeGlobalAttributeAttributeListID,
    ZGMTRAttributeIDTypeClusterPushAVStreamTransportAttributeFeatureMapID ZGMTR_PROVISIONALLY_AVAILABLE = ZGMTRAttributeIDTypeGlobalAttributeFeatureMapID,
    ZGMTRAttributeIDTypeClusterPushAVStreamTransportAttributeClusterRevisionID ZGMTR_PROVISIONALLY_AVAILABLE = ZGMTRAttributeIDTypeGlobalAttributeClusterRevisionID,

    // Cluster Chime attributes
    ZGMTRAttributeIDTypeClusterChimeAttributeInstalledChimeSoundsID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000000,
    ZGMTRAttributeIDTypeClusterChimeAttributeSelectedChimeID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000001,
    ZGMTRAttributeIDTypeClusterChimeAttributeEnabledID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000002,
    ZGMTRAttributeIDTypeClusterChimeAttributeGeneratedCommandListID ZGMTR_PROVISIONALLY_AVAILABLE = ZGMTRAttributeIDTypeGlobalAttributeGeneratedCommandListID,
    ZGMTRAttributeIDTypeClusterChimeAttributeAcceptedCommandListID ZGMTR_PROVISIONALLY_AVAILABLE = ZGMTRAttributeIDTypeGlobalAttributeAcceptedCommandListID,
    ZGMTRAttributeIDTypeClusterChimeAttributeAttributeListID ZGMTR_PROVISIONALLY_AVAILABLE = ZGMTRAttributeIDTypeGlobalAttributeAttributeListID,
    ZGMTRAttributeIDTypeClusterChimeAttributeFeatureMapID ZGMTR_PROVISIONALLY_AVAILABLE = ZGMTRAttributeIDTypeGlobalAttributeFeatureMapID,
    ZGMTRAttributeIDTypeClusterChimeAttributeClusterRevisionID ZGMTR_PROVISIONALLY_AVAILABLE = ZGMTRAttributeIDTypeGlobalAttributeClusterRevisionID,

    // Cluster AVAnalysis attributes
    ZGMTRAttributeIDTypeClusterAVAnalysisAttributeSupportedAmbientContextsID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000000,
    ZGMTRAttributeIDTypeClusterAVAnalysisAttributeActiveAmbientContextTriggersID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000001,
    ZGMTRAttributeIDTypeClusterAVAnalysisAttributeMaxAnalysisStreamCountID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000002,
    ZGMTRAttributeIDTypeClusterAVAnalysisAttributeCurrentAnalysisStreamCountID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000003,
    ZGMTRAttributeIDTypeClusterAVAnalysisAttributeAnalysisStreamsID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000004,
    ZGMTRAttributeIDTypeClusterAVAnalysisAttributeTrackingEnabledID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000005,
    ZGMTRAttributeIDTypeClusterAVAnalysisAttributeGeneratedCommandListID ZGMTR_PROVISIONALLY_AVAILABLE = ZGMTRAttributeIDTypeGlobalAttributeGeneratedCommandListID,
    ZGMTRAttributeIDTypeClusterAVAnalysisAttributeAcceptedCommandListID ZGMTR_PROVISIONALLY_AVAILABLE = ZGMTRAttributeIDTypeGlobalAttributeAcceptedCommandListID,
    ZGMTRAttributeIDTypeClusterAVAnalysisAttributeAttributeListID ZGMTR_PROVISIONALLY_AVAILABLE = ZGMTRAttributeIDTypeGlobalAttributeAttributeListID,
    ZGMTRAttributeIDTypeClusterAVAnalysisAttributeFeatureMapID ZGMTR_PROVISIONALLY_AVAILABLE = ZGMTRAttributeIDTypeGlobalAttributeFeatureMapID,
    ZGMTRAttributeIDTypeClusterAVAnalysisAttributeClusterRevisionID ZGMTR_PROVISIONALLY_AVAILABLE = ZGMTRAttributeIDTypeGlobalAttributeClusterRevisionID,

    // Cluster CommodityTariff attributes
    ZGMTRAttributeIDTypeClusterCommodityTariffAttributeTariffInfoID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000000,
    ZGMTRAttributeIDTypeClusterCommodityTariffAttributeTariffUnitID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000001,
    ZGMTRAttributeIDTypeClusterCommodityTariffAttributeStartDateID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000002,
    ZGMTRAttributeIDTypeClusterCommodityTariffAttributeDayEntriesID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000003,
    ZGMTRAttributeIDTypeClusterCommodityTariffAttributeDayPatternsID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000004,
    ZGMTRAttributeIDTypeClusterCommodityTariffAttributeCalendarPeriodsID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000005,
    ZGMTRAttributeIDTypeClusterCommodityTariffAttributeIndividualDaysID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000006,
    ZGMTRAttributeIDTypeClusterCommodityTariffAttributeCurrentDayID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000007,
    ZGMTRAttributeIDTypeClusterCommodityTariffAttributeNextDayID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000008,
    ZGMTRAttributeIDTypeClusterCommodityTariffAttributeCurrentDayEntryID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000009,
    ZGMTRAttributeIDTypeClusterCommodityTariffAttributeCurrentDayEntryDateID ZGMTR_PROVISIONALLY_AVAILABLE = 0x0000000A,
    ZGMTRAttributeIDTypeClusterCommodityTariffAttributeNextDayEntryID ZGMTR_PROVISIONALLY_AVAILABLE = 0x0000000B,
    ZGMTRAttributeIDTypeClusterCommodityTariffAttributeNextDayEntryDateID ZGMTR_PROVISIONALLY_AVAILABLE = 0x0000000C,
    ZGMTRAttributeIDTypeClusterCommodityTariffAttributeTariffComponentsID ZGMTR_PROVISIONALLY_AVAILABLE = 0x0000000D,
    ZGMTRAttributeIDTypeClusterCommodityTariffAttributeTariffPeriodsID ZGMTR_PROVISIONALLY_AVAILABLE = 0x0000000E,
    ZGMTRAttributeIDTypeClusterCommodityTariffAttributeCurrentTariffComponentsID ZGMTR_PROVISIONALLY_AVAILABLE = 0x0000000F,
    ZGMTRAttributeIDTypeClusterCommodityTariffAttributeNextTariffComponentsID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000010,
    ZGMTRAttributeIDTypeClusterCommodityTariffAttributeDefaultRandomizationOffsetID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000011,
    ZGMTRAttributeIDTypeClusterCommodityTariffAttributeDefaultRandomizationTypeID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000012,
    ZGMTRAttributeIDTypeClusterCommodityTariffAttributeGeneratedCommandListID ZGMTR_PROVISIONALLY_AVAILABLE = ZGMTRAttributeIDTypeGlobalAttributeGeneratedCommandListID,
    ZGMTRAttributeIDTypeClusterCommodityTariffAttributeAcceptedCommandListID ZGMTR_PROVISIONALLY_AVAILABLE = ZGMTRAttributeIDTypeGlobalAttributeAcceptedCommandListID,
    ZGMTRAttributeIDTypeClusterCommodityTariffAttributeAttributeListID ZGMTR_PROVISIONALLY_AVAILABLE = ZGMTRAttributeIDTypeGlobalAttributeAttributeListID,
    ZGMTRAttributeIDTypeClusterCommodityTariffAttributeFeatureMapID ZGMTR_PROVISIONALLY_AVAILABLE = ZGMTRAttributeIDTypeGlobalAttributeFeatureMapID,
    ZGMTRAttributeIDTypeClusterCommodityTariffAttributeClusterRevisionID ZGMTR_PROVISIONALLY_AVAILABLE = ZGMTRAttributeIDTypeGlobalAttributeClusterRevisionID,

    // Cluster EcosystemInformation attributes
    ZGMTRAttributeIDTypeClusterEcosystemInformationAttributeDeviceDirectoryID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000000,
    ZGMTRAttributeIDTypeClusterEcosystemInformationAttributeLocationDirectoryID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000001,
    ZGMTRAttributeIDTypeClusterEcosystemInformationAttributeGeneratedCommandListID ZGMTR_PROVISIONALLY_AVAILABLE = ZGMTRAttributeIDTypeGlobalAttributeGeneratedCommandListID,
    ZGMTRAttributeIDTypeClusterEcosystemInformationAttributeAcceptedCommandListID ZGMTR_PROVISIONALLY_AVAILABLE = ZGMTRAttributeIDTypeGlobalAttributeAcceptedCommandListID,
    ZGMTRAttributeIDTypeClusterEcosystemInformationAttributeAttributeListID ZGMTR_PROVISIONALLY_AVAILABLE = ZGMTRAttributeIDTypeGlobalAttributeAttributeListID,
    ZGMTRAttributeIDTypeClusterEcosystemInformationAttributeFeatureMapID ZGMTR_PROVISIONALLY_AVAILABLE = ZGMTRAttributeIDTypeGlobalAttributeFeatureMapID,
    ZGMTRAttributeIDTypeClusterEcosystemInformationAttributeClusterRevisionID ZGMTR_PROVISIONALLY_AVAILABLE = ZGMTRAttributeIDTypeGlobalAttributeClusterRevisionID,

    // Cluster CommissionerControl attributes
    ZGMTRAttributeIDTypeClusterCommissionerControlAttributeSupportedDeviceCategoriesID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = 0x00000000,
    ZGMTRAttributeIDTypeClusterCommissionerControlAttributeGeneratedCommandListID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = ZGMTRAttributeIDTypeGlobalAttributeGeneratedCommandListID,
    ZGMTRAttributeIDTypeClusterCommissionerControlAttributeAcceptedCommandListID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = ZGMTRAttributeIDTypeGlobalAttributeAcceptedCommandListID,
    ZGMTRAttributeIDTypeClusterCommissionerControlAttributeAttributeListID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = ZGMTRAttributeIDTypeGlobalAttributeAttributeListID,
    ZGMTRAttributeIDTypeClusterCommissionerControlAttributeFeatureMapID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = ZGMTRAttributeIDTypeGlobalAttributeFeatureMapID,
    ZGMTRAttributeIDTypeClusterCommissionerControlAttributeClusterRevisionID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = ZGMTRAttributeIDTypeGlobalAttributeClusterRevisionID,

    // Cluster JointFabricDatastore attributes
    ZGMTRAttributeIDTypeClusterJointFabricDatastoreAttributeAnchorRootCAID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000000,
    ZGMTRAttributeIDTypeClusterJointFabricDatastoreAttributeAnchorNodeIDID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000001,
    ZGMTRAttributeIDTypeClusterJointFabricDatastoreAttributeAnchorVendorIDID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000002,
    ZGMTRAttributeIDTypeClusterJointFabricDatastoreAttributeFriendlyNameID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000003,
    ZGMTRAttributeIDTypeClusterJointFabricDatastoreAttributeGroupKeySetListID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000004,
    ZGMTRAttributeIDTypeClusterJointFabricDatastoreAttributeGroupListID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000005,
    ZGMTRAttributeIDTypeClusterJointFabricDatastoreAttributeNodeListID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000006,
    ZGMTRAttributeIDTypeClusterJointFabricDatastoreAttributeAdminListID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000007,
    ZGMTRAttributeIDTypeClusterJointFabricDatastoreAttributeStatusID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000008,
    ZGMTRAttributeIDTypeClusterJointFabricDatastoreAttributeEndpointGroupIDListID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000009,
    ZGMTRAttributeIDTypeClusterJointFabricDatastoreAttributeEndpointBindingListID ZGMTR_PROVISIONALLY_AVAILABLE = 0x0000000A,
    ZGMTRAttributeIDTypeClusterJointFabricDatastoreAttributeNodeKeySetListID ZGMTR_PROVISIONALLY_AVAILABLE = 0x0000000B,
    ZGMTRAttributeIDTypeClusterJointFabricDatastoreAttributeNodeACLListID ZGMTR_PROVISIONALLY_AVAILABLE = 0x0000000C,
    ZGMTRAttributeIDTypeClusterJointFabricDatastoreAttributeNodeEndpointListID ZGMTR_PROVISIONALLY_AVAILABLE = 0x0000000D,
    ZGMTRAttributeIDTypeClusterJointFabricDatastoreAttributeGeneratedCommandListID ZGMTR_PROVISIONALLY_AVAILABLE = ZGMTRAttributeIDTypeGlobalAttributeGeneratedCommandListID,
    ZGMTRAttributeIDTypeClusterJointFabricDatastoreAttributeAcceptedCommandListID ZGMTR_PROVISIONALLY_AVAILABLE = ZGMTRAttributeIDTypeGlobalAttributeAcceptedCommandListID,
    ZGMTRAttributeIDTypeClusterJointFabricDatastoreAttributeAttributeListID ZGMTR_PROVISIONALLY_AVAILABLE = ZGMTRAttributeIDTypeGlobalAttributeAttributeListID,
    ZGMTRAttributeIDTypeClusterJointFabricDatastoreAttributeFeatureMapID ZGMTR_PROVISIONALLY_AVAILABLE = ZGMTRAttributeIDTypeGlobalAttributeFeatureMapID,
    ZGMTRAttributeIDTypeClusterJointFabricDatastoreAttributeClusterRevisionID ZGMTR_PROVISIONALLY_AVAILABLE = ZGMTRAttributeIDTypeGlobalAttributeClusterRevisionID,

    // Cluster JointFabricAdministrator attributes
    ZGMTRAttributeIDTypeClusterJointFabricAdministratorAttributeAdministratorFabricIndexID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000000,
    ZGMTRAttributeIDTypeClusterJointFabricAdministratorAttributeGeneratedCommandListID ZGMTR_PROVISIONALLY_AVAILABLE = ZGMTRAttributeIDTypeGlobalAttributeGeneratedCommandListID,
    ZGMTRAttributeIDTypeClusterJointFabricAdministratorAttributeAcceptedCommandListID ZGMTR_PROVISIONALLY_AVAILABLE = ZGMTRAttributeIDTypeGlobalAttributeAcceptedCommandListID,
    ZGMTRAttributeIDTypeClusterJointFabricAdministratorAttributeAttributeListID ZGMTR_PROVISIONALLY_AVAILABLE = ZGMTRAttributeIDTypeGlobalAttributeAttributeListID,
    ZGMTRAttributeIDTypeClusterJointFabricAdministratorAttributeFeatureMapID ZGMTR_PROVISIONALLY_AVAILABLE = ZGMTRAttributeIDTypeGlobalAttributeFeatureMapID,
    ZGMTRAttributeIDTypeClusterJointFabricAdministratorAttributeClusterRevisionID ZGMTR_PROVISIONALLY_AVAILABLE = ZGMTRAttributeIDTypeGlobalAttributeClusterRevisionID,

    // Cluster TLSCertificateManagement attributes
    ZGMTRAttributeIDTypeClusterTLSCertificateManagementAttributeMaxRootCertificatesID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000000,
    ZGMTRAttributeIDTypeClusterTLSCertificateManagementAttributeProvisionedRootCertificatesID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000001,
    ZGMTRAttributeIDTypeClusterTLSCertificateManagementAttributeMaxClientCertificatesID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000002,
    ZGMTRAttributeIDTypeClusterTLSCertificateManagementAttributeProvisionedClientCertificatesID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000003,
    ZGMTRAttributeIDTypeClusterTLSCertificateManagementAttributeGeneratedCommandListID ZGMTR_PROVISIONALLY_AVAILABLE = ZGMTRAttributeIDTypeGlobalAttributeGeneratedCommandListID,
    ZGMTRAttributeIDTypeClusterTLSCertificateManagementAttributeAcceptedCommandListID ZGMTR_PROVISIONALLY_AVAILABLE = ZGMTRAttributeIDTypeGlobalAttributeAcceptedCommandListID,
    ZGMTRAttributeIDTypeClusterTLSCertificateManagementAttributeAttributeListID ZGMTR_PROVISIONALLY_AVAILABLE = ZGMTRAttributeIDTypeGlobalAttributeAttributeListID,
    ZGMTRAttributeIDTypeClusterTLSCertificateManagementAttributeFeatureMapID ZGMTR_PROVISIONALLY_AVAILABLE = ZGMTRAttributeIDTypeGlobalAttributeFeatureMapID,
    ZGMTRAttributeIDTypeClusterTLSCertificateManagementAttributeClusterRevisionID ZGMTR_PROVISIONALLY_AVAILABLE = ZGMTRAttributeIDTypeGlobalAttributeClusterRevisionID,

    // Cluster TLSClientManagement attributes
    ZGMTRAttributeIDTypeClusterTLSClientManagementAttributeMaxProvisionedID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000000,
    ZGMTRAttributeIDTypeClusterTLSClientManagementAttributeProvisionedEndpointsID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000001,
    ZGMTRAttributeIDTypeClusterTLSClientManagementAttributeGeneratedCommandListID ZGMTR_PROVISIONALLY_AVAILABLE = ZGMTRAttributeIDTypeGlobalAttributeGeneratedCommandListID,
    ZGMTRAttributeIDTypeClusterTLSClientManagementAttributeAcceptedCommandListID ZGMTR_PROVISIONALLY_AVAILABLE = ZGMTRAttributeIDTypeGlobalAttributeAcceptedCommandListID,
    ZGMTRAttributeIDTypeClusterTLSClientManagementAttributeAttributeListID ZGMTR_PROVISIONALLY_AVAILABLE = ZGMTRAttributeIDTypeGlobalAttributeAttributeListID,
    ZGMTRAttributeIDTypeClusterTLSClientManagementAttributeFeatureMapID ZGMTR_PROVISIONALLY_AVAILABLE = ZGMTRAttributeIDTypeGlobalAttributeFeatureMapID,
    ZGMTRAttributeIDTypeClusterTLSClientManagementAttributeClusterRevisionID ZGMTR_PROVISIONALLY_AVAILABLE = ZGMTRAttributeIDTypeGlobalAttributeClusterRevisionID,

    // Cluster MeterIdentification attributes
    ZGMTRAttributeIDTypeClusterMeterIdentificationAttributeMeterTypeID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000000,
    ZGMTRAttributeIDTypeClusterMeterIdentificationAttributePointOfDeliveryID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000001,
    ZGMTRAttributeIDTypeClusterMeterIdentificationAttributeMeterSerialNumberID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000002,
    ZGMTRAttributeIDTypeClusterMeterIdentificationAttributeProtocolVersionID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000003,
    ZGMTRAttributeIDTypeClusterMeterIdentificationAttributePowerThresholdID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000004,
    ZGMTRAttributeIDTypeClusterMeterIdentificationAttributeGeneratedCommandListID ZGMTR_PROVISIONALLY_AVAILABLE = ZGMTRAttributeIDTypeGlobalAttributeGeneratedCommandListID,
    ZGMTRAttributeIDTypeClusterMeterIdentificationAttributeAcceptedCommandListID ZGMTR_PROVISIONALLY_AVAILABLE = ZGMTRAttributeIDTypeGlobalAttributeAcceptedCommandListID,
    ZGMTRAttributeIDTypeClusterMeterIdentificationAttributeAttributeListID ZGMTR_PROVISIONALLY_AVAILABLE = ZGMTRAttributeIDTypeGlobalAttributeAttributeListID,
    ZGMTRAttributeIDTypeClusterMeterIdentificationAttributeFeatureMapID ZGMTR_PROVISIONALLY_AVAILABLE = ZGMTRAttributeIDTypeGlobalAttributeFeatureMapID,
    ZGMTRAttributeIDTypeClusterMeterIdentificationAttributeClusterRevisionID ZGMTR_PROVISIONALLY_AVAILABLE = ZGMTRAttributeIDTypeGlobalAttributeClusterRevisionID,

    // Cluster CommodityMetering attributes
    ZGMTRAttributeIDTypeClusterCommodityMeteringAttributeMeteredQuantityID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000000,
    ZGMTRAttributeIDTypeClusterCommodityMeteringAttributeMeteredQuantityTimestampID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000001,
    ZGMTRAttributeIDTypeClusterCommodityMeteringAttributeTariffUnitID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000002,
    ZGMTRAttributeIDTypeClusterCommodityMeteringAttributeMaximumMeteredQuantitiesID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000003,
    ZGMTRAttributeIDTypeClusterCommodityMeteringAttributeGeneratedCommandListID ZGMTR_PROVISIONALLY_AVAILABLE = ZGMTRAttributeIDTypeGlobalAttributeGeneratedCommandListID,
    ZGMTRAttributeIDTypeClusterCommodityMeteringAttributeAcceptedCommandListID ZGMTR_PROVISIONALLY_AVAILABLE = ZGMTRAttributeIDTypeGlobalAttributeAcceptedCommandListID,
    ZGMTRAttributeIDTypeClusterCommodityMeteringAttributeAttributeListID ZGMTR_PROVISIONALLY_AVAILABLE = ZGMTRAttributeIDTypeGlobalAttributeAttributeListID,
    ZGMTRAttributeIDTypeClusterCommodityMeteringAttributeFeatureMapID ZGMTR_PROVISIONALLY_AVAILABLE = ZGMTRAttributeIDTypeGlobalAttributeFeatureMapID,
    ZGMTRAttributeIDTypeClusterCommodityMeteringAttributeClusterRevisionID ZGMTR_PROVISIONALLY_AVAILABLE = ZGMTRAttributeIDTypeGlobalAttributeClusterRevisionID,

    // Cluster TestCluster deprecated attribute names
    ZGMTRClusterTestClusterAttributeBooleanID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterUnitTestingAttributeBooleanID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000000,
    ZGMTRClusterTestClusterAttributeBitmap8ID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterUnitTestingAttributeBitmap8ID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000001,
    ZGMTRClusterTestClusterAttributeBitmap16ID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterUnitTestingAttributeBitmap16ID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000002,
    ZGMTRClusterTestClusterAttributeBitmap32ID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterUnitTestingAttributeBitmap32ID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000003,
    ZGMTRClusterTestClusterAttributeBitmap64ID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterUnitTestingAttributeBitmap64ID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000004,
    ZGMTRClusterTestClusterAttributeInt8uID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterUnitTestingAttributeInt8uID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000005,
    ZGMTRClusterTestClusterAttributeInt16uID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterUnitTestingAttributeInt16uID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000006,
    ZGMTRClusterTestClusterAttributeInt24uID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterUnitTestingAttributeInt24uID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000007,
    ZGMTRClusterTestClusterAttributeInt32uID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterUnitTestingAttributeInt32uID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000008,
    ZGMTRClusterTestClusterAttributeInt40uID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterUnitTestingAttributeInt40uID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000009,
    ZGMTRClusterTestClusterAttributeInt48uID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterUnitTestingAttributeInt48uID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x0000000A,
    ZGMTRClusterTestClusterAttributeInt56uID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterUnitTestingAttributeInt56uID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x0000000B,
    ZGMTRClusterTestClusterAttributeInt64uID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterUnitTestingAttributeInt64uID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x0000000C,
    ZGMTRClusterTestClusterAttributeInt8sID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterUnitTestingAttributeInt8sID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x0000000D,
    ZGMTRClusterTestClusterAttributeInt16sID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterUnitTestingAttributeInt16sID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x0000000E,
    ZGMTRClusterTestClusterAttributeInt24sID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterUnitTestingAttributeInt24sID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x0000000F,
    ZGMTRClusterTestClusterAttributeInt32sID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterUnitTestingAttributeInt32sID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000010,
    ZGMTRClusterTestClusterAttributeInt40sID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterUnitTestingAttributeInt40sID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000011,
    ZGMTRClusterTestClusterAttributeInt48sID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterUnitTestingAttributeInt48sID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000012,
    ZGMTRClusterTestClusterAttributeInt56sID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterUnitTestingAttributeInt56sID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000013,
    ZGMTRClusterTestClusterAttributeInt64sID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterUnitTestingAttributeInt64sID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000014,
    ZGMTRClusterTestClusterAttributeEnum8ID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterUnitTestingAttributeEnum8ID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000015,
    ZGMTRClusterTestClusterAttributeEnum16ID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterUnitTestingAttributeEnum16ID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000016,
    ZGMTRClusterTestClusterAttributeFloatSingleID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterUnitTestingAttributeFloatSingleID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000017,
    ZGMTRClusterTestClusterAttributeFloatDoubleID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterUnitTestingAttributeFloatDoubleID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000018,
    ZGMTRClusterTestClusterAttributeOctetStringID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterUnitTestingAttributeOctetStringID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000019,
    ZGMTRClusterTestClusterAttributeListInt8uID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterUnitTestingAttributeListInt8uID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x0000001A,
    ZGMTRClusterTestClusterAttributeListOctetStringID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterUnitTestingAttributeListOctetStringID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x0000001B,
    ZGMTRClusterTestClusterAttributeListStructOctetStringID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterUnitTestingAttributeListStructOctetStringID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x0000001C,
    ZGMTRClusterTestClusterAttributeLongOctetStringID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterUnitTestingAttributeLongOctetStringID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x0000001D,
    ZGMTRClusterTestClusterAttributeCharStringID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterUnitTestingAttributeCharStringID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x0000001E,
    ZGMTRClusterTestClusterAttributeLongCharStringID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterUnitTestingAttributeLongCharStringID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x0000001F,
    ZGMTRClusterTestClusterAttributeEpochUsID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterUnitTestingAttributeEpochUsID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000020,
    ZGMTRClusterTestClusterAttributeEpochSID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterUnitTestingAttributeEpochSID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000021,
    ZGMTRClusterTestClusterAttributeVendorIdID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterUnitTestingAttributeVendorIdID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000022,
    ZGMTRClusterTestClusterAttributeListNullablesAndOptionalsStructID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterUnitTestingAttributeListNullablesAndOptionalsStructID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000023,
    ZGMTRClusterTestClusterAttributeEnumAttrID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterUnitTestingAttributeEnumAttrID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000024,
    ZGMTRClusterTestClusterAttributeStructAttrID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterUnitTestingAttributeStructAttrID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000025,
    ZGMTRClusterTestClusterAttributeRangeRestrictedInt8uID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterUnitTestingAttributeRangeRestrictedInt8uID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000026,
    ZGMTRClusterTestClusterAttributeRangeRestrictedInt8sID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterUnitTestingAttributeRangeRestrictedInt8sID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000027,
    ZGMTRClusterTestClusterAttributeRangeRestrictedInt16uID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterUnitTestingAttributeRangeRestrictedInt16uID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000028,
    ZGMTRClusterTestClusterAttributeRangeRestrictedInt16sID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterUnitTestingAttributeRangeRestrictedInt16sID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000029,
    ZGMTRClusterTestClusterAttributeListLongOctetStringID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterUnitTestingAttributeListLongOctetStringID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x0000002A,
    ZGMTRClusterTestClusterAttributeListFabricScopedID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterUnitTestingAttributeListFabricScopedID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x0000002B,
    ZGMTRClusterTestClusterAttributeTimedWriteBooleanID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterUnitTestingAttributeTimedWriteBooleanID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000030,
    ZGMTRClusterTestClusterAttributeGeneralErrorBooleanID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterUnitTestingAttributeGeneralErrorBooleanID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000031,
    ZGMTRClusterTestClusterAttributeClusterErrorBooleanID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterUnitTestingAttributeClusterErrorBooleanID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00000032,
    ZGMTRClusterTestClusterAttributeUnsupportedID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterUnitTestingAttributeUnsupportedID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x000000FF,
    ZGMTRClusterTestClusterAttributeNullableBooleanID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterUnitTestingAttributeNullableBooleanID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00004000,
    ZGMTRClusterTestClusterAttributeNullableBitmap8ID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterUnitTestingAttributeNullableBitmap8ID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00004001,
    ZGMTRClusterTestClusterAttributeNullableBitmap16ID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterUnitTestingAttributeNullableBitmap16ID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00004002,
    ZGMTRClusterTestClusterAttributeNullableBitmap32ID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterUnitTestingAttributeNullableBitmap32ID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00004003,
    ZGMTRClusterTestClusterAttributeNullableBitmap64ID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterUnitTestingAttributeNullableBitmap64ID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00004004,
    ZGMTRClusterTestClusterAttributeNullableInt8uID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterUnitTestingAttributeNullableInt8uID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00004005,
    ZGMTRClusterTestClusterAttributeNullableInt16uID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterUnitTestingAttributeNullableInt16uID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00004006,
    ZGMTRClusterTestClusterAttributeNullableInt24uID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterUnitTestingAttributeNullableInt24uID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00004007,
    ZGMTRClusterTestClusterAttributeNullableInt32uID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterUnitTestingAttributeNullableInt32uID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00004008,
    ZGMTRClusterTestClusterAttributeNullableInt40uID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterUnitTestingAttributeNullableInt40uID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00004009,
    ZGMTRClusterTestClusterAttributeNullableInt48uID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterUnitTestingAttributeNullableInt48uID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x0000400A,
    ZGMTRClusterTestClusterAttributeNullableInt56uID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterUnitTestingAttributeNullableInt56uID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x0000400B,
    ZGMTRClusterTestClusterAttributeNullableInt64uID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterUnitTestingAttributeNullableInt64uID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x0000400C,
    ZGMTRClusterTestClusterAttributeNullableInt8sID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterUnitTestingAttributeNullableInt8sID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x0000400D,
    ZGMTRClusterTestClusterAttributeNullableInt16sID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterUnitTestingAttributeNullableInt16sID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x0000400E,
    ZGMTRClusterTestClusterAttributeNullableInt24sID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterUnitTestingAttributeNullableInt24sID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x0000400F,
    ZGMTRClusterTestClusterAttributeNullableInt32sID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterUnitTestingAttributeNullableInt32sID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00004010,
    ZGMTRClusterTestClusterAttributeNullableInt40sID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterUnitTestingAttributeNullableInt40sID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00004011,
    ZGMTRClusterTestClusterAttributeNullableInt48sID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterUnitTestingAttributeNullableInt48sID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00004012,
    ZGMTRClusterTestClusterAttributeNullableInt56sID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterUnitTestingAttributeNullableInt56sID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00004013,
    ZGMTRClusterTestClusterAttributeNullableInt64sID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterUnitTestingAttributeNullableInt64sID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00004014,
    ZGMTRClusterTestClusterAttributeNullableEnum8ID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterUnitTestingAttributeNullableEnum8ID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00004015,
    ZGMTRClusterTestClusterAttributeNullableEnum16ID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterUnitTestingAttributeNullableEnum16ID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00004016,
    ZGMTRClusterTestClusterAttributeNullableFloatSingleID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterUnitTestingAttributeNullableFloatSingleID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00004017,
    ZGMTRClusterTestClusterAttributeNullableFloatDoubleID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterUnitTestingAttributeNullableFloatDoubleID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00004018,
    ZGMTRClusterTestClusterAttributeNullableOctetStringID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterUnitTestingAttributeNullableOctetStringID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00004019,
    ZGMTRClusterTestClusterAttributeNullableCharStringID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterUnitTestingAttributeNullableCharStringID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x0000401E,
    ZGMTRClusterTestClusterAttributeNullableEnumAttrID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterUnitTestingAttributeNullableEnumAttrID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00004024,
    ZGMTRClusterTestClusterAttributeNullableStructID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterUnitTestingAttributeNullableStructID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00004025,
    ZGMTRClusterTestClusterAttributeNullableRangeRestrictedInt8uID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterUnitTestingAttributeNullableRangeRestrictedInt8uID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00004026,
    ZGMTRClusterTestClusterAttributeNullableRangeRestrictedInt8sID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterUnitTestingAttributeNullableRangeRestrictedInt8sID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00004027,
    ZGMTRClusterTestClusterAttributeNullableRangeRestrictedInt16uID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterUnitTestingAttributeNullableRangeRestrictedInt16uID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00004028,
    ZGMTRClusterTestClusterAttributeNullableRangeRestrictedInt16sID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterUnitTestingAttributeNullableRangeRestrictedInt16sID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = 0x00004029,
    ZGMTRClusterTestClusterAttributeWriteOnlyInt8uID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterUnitTestingAttributeWriteOnlyInt8uID", ios(16.2, 16.4), macos(13.1, 13.3), watchos(9.2, 9.4), tvos(16.2, 16.4)) = 0x0000402A,
    ZGMTRClusterTestClusterAttributeGeneratedCommandListID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterUnitTestingAttributeGeneratedCommandListID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = ZGMTRClusterGlobalAttributeGeneratedCommandListID,
    ZGMTRClusterTestClusterAttributeAcceptedCommandListID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterUnitTestingAttributeAcceptedCommandListID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = ZGMTRClusterGlobalAttributeAcceptedCommandListID,
    ZGMTRClusterTestClusterAttributeAttributeListID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterUnitTestingAttributeAttributeListID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = ZGMTRClusterGlobalAttributeAttributeListID,
    ZGMTRClusterTestClusterAttributeFeatureMapID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterUnitTestingAttributeFeatureMapID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = ZGMTRClusterGlobalAttributeFeatureMapID,
    ZGMTRClusterTestClusterAttributeClusterRevisionID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterUnitTestingAttributeClusterRevisionID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4)) = ZGMTRClusterGlobalAttributeClusterRevisionID,

    // Cluster UnitTesting attributes
    ZGMTRAttributeIDTypeClusterUnitTestingAttributeBooleanID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000000,
    ZGMTRAttributeIDTypeClusterUnitTestingAttributeBitmap8ID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000001,
    ZGMTRAttributeIDTypeClusterUnitTestingAttributeBitmap16ID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000002,
    ZGMTRAttributeIDTypeClusterUnitTestingAttributeBitmap32ID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000003,
    ZGMTRAttributeIDTypeClusterUnitTestingAttributeBitmap64ID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000004,
    ZGMTRAttributeIDTypeClusterUnitTestingAttributeInt8uID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000005,
    ZGMTRAttributeIDTypeClusterUnitTestingAttributeInt16uID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000006,
    ZGMTRAttributeIDTypeClusterUnitTestingAttributeInt24uID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000007,
    ZGMTRAttributeIDTypeClusterUnitTestingAttributeInt32uID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000008,
    ZGMTRAttributeIDTypeClusterUnitTestingAttributeInt40uID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000009,
    ZGMTRAttributeIDTypeClusterUnitTestingAttributeInt48uID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x0000000A,
    ZGMTRAttributeIDTypeClusterUnitTestingAttributeInt56uID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x0000000B,
    ZGMTRAttributeIDTypeClusterUnitTestingAttributeInt64uID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x0000000C,
    ZGMTRAttributeIDTypeClusterUnitTestingAttributeInt8sID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x0000000D,
    ZGMTRAttributeIDTypeClusterUnitTestingAttributeInt16sID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x0000000E,
    ZGMTRAttributeIDTypeClusterUnitTestingAttributeInt24sID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x0000000F,
    ZGMTRAttributeIDTypeClusterUnitTestingAttributeInt32sID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000010,
    ZGMTRAttributeIDTypeClusterUnitTestingAttributeInt40sID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000011,
    ZGMTRAttributeIDTypeClusterUnitTestingAttributeInt48sID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000012,
    ZGMTRAttributeIDTypeClusterUnitTestingAttributeInt56sID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000013,
    ZGMTRAttributeIDTypeClusterUnitTestingAttributeInt64sID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000014,
    ZGMTRAttributeIDTypeClusterUnitTestingAttributeEnum8ID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000015,
    ZGMTRAttributeIDTypeClusterUnitTestingAttributeEnum16ID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000016,
    ZGMTRAttributeIDTypeClusterUnitTestingAttributeFloatSingleID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000017,
    ZGMTRAttributeIDTypeClusterUnitTestingAttributeFloatDoubleID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000018,
    ZGMTRAttributeIDTypeClusterUnitTestingAttributeOctetStringID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000019,
    ZGMTRAttributeIDTypeClusterUnitTestingAttributeListInt8uID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x0000001A,
    ZGMTRAttributeIDTypeClusterUnitTestingAttributeListOctetStringID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x0000001B,
    ZGMTRAttributeIDTypeClusterUnitTestingAttributeListStructOctetStringID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x0000001C,
    ZGMTRAttributeIDTypeClusterUnitTestingAttributeLongOctetStringID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x0000001D,
    ZGMTRAttributeIDTypeClusterUnitTestingAttributeCharStringID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x0000001E,
    ZGMTRAttributeIDTypeClusterUnitTestingAttributeLongCharStringID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x0000001F,
    ZGMTRAttributeIDTypeClusterUnitTestingAttributeEpochUsID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000020,
    ZGMTRAttributeIDTypeClusterUnitTestingAttributeEpochSID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000021,
    ZGMTRAttributeIDTypeClusterUnitTestingAttributeVendorIdID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000022,
    ZGMTRAttributeIDTypeClusterUnitTestingAttributeListNullablesAndOptionalsStructID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000023,
    ZGMTRAttributeIDTypeClusterUnitTestingAttributeEnumAttrID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000024,
    ZGMTRAttributeIDTypeClusterUnitTestingAttributeStructAttrID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000025,
    ZGMTRAttributeIDTypeClusterUnitTestingAttributeRangeRestrictedInt8uID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000026,
    ZGMTRAttributeIDTypeClusterUnitTestingAttributeRangeRestrictedInt8sID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000027,
    ZGMTRAttributeIDTypeClusterUnitTestingAttributeRangeRestrictedInt16uID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000028,
    ZGMTRAttributeIDTypeClusterUnitTestingAttributeRangeRestrictedInt16sID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000029,
    ZGMTRAttributeIDTypeClusterUnitTestingAttributeListLongOctetStringID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x0000002A,
    ZGMTRAttributeIDTypeClusterUnitTestingAttributeListFabricScopedID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x0000002B,
    ZGMTRAttributeIDTypeClusterUnitTestingAttributeTimedWriteBooleanID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000030,
    ZGMTRAttributeIDTypeClusterUnitTestingAttributeGeneralErrorBooleanID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000031,
    ZGMTRAttributeIDTypeClusterUnitTestingAttributeClusterErrorBooleanID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000032,
    ZGMTRAttributeIDTypeClusterUnitTestingAttributeGlobalEnumID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000033,
    ZGMTRAttributeIDTypeClusterUnitTestingAttributeGlobalStructID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000034,
    ZGMTRAttributeIDTypeClusterUnitTestingAttributeUnsupportedAttributeRequiringAdminPrivilegeID ZGMTR_PROVISIONALLY_AVAILABLE = 0x000000FE,
    ZGMTRAttributeIDTypeClusterUnitTestingAttributeUnsupportedID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x000000FF,
    ZGMTRAttributeIDTypeClusterUnitTestingAttributeReadFailureCodeID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00003000,
    ZGMTRAttributeIDTypeClusterUnitTestingAttributeFailureInt32UID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00003001,
    ZGMTRAttributeIDTypeClusterUnitTestingAttributeNullableBooleanID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00004000,
    ZGMTRAttributeIDTypeClusterUnitTestingAttributeNullableBitmap8ID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00004001,
    ZGMTRAttributeIDTypeClusterUnitTestingAttributeNullableBitmap16ID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00004002,
    ZGMTRAttributeIDTypeClusterUnitTestingAttributeNullableBitmap32ID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00004003,
    ZGMTRAttributeIDTypeClusterUnitTestingAttributeNullableBitmap64ID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00004004,
    ZGMTRAttributeIDTypeClusterUnitTestingAttributeNullableInt8uID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00004005,
    ZGMTRAttributeIDTypeClusterUnitTestingAttributeNullableInt16uID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00004006,
    ZGMTRAttributeIDTypeClusterUnitTestingAttributeNullableInt24uID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00004007,
    ZGMTRAttributeIDTypeClusterUnitTestingAttributeNullableInt32uID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00004008,
    ZGMTRAttributeIDTypeClusterUnitTestingAttributeNullableInt40uID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00004009,
    ZGMTRAttributeIDTypeClusterUnitTestingAttributeNullableInt48uID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x0000400A,
    ZGMTRAttributeIDTypeClusterUnitTestingAttributeNullableInt56uID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x0000400B,
    ZGMTRAttributeIDTypeClusterUnitTestingAttributeNullableInt64uID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x0000400C,
    ZGMTRAttributeIDTypeClusterUnitTestingAttributeNullableInt8sID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x0000400D,
    ZGMTRAttributeIDTypeClusterUnitTestingAttributeNullableInt16sID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x0000400E,
    ZGMTRAttributeIDTypeClusterUnitTestingAttributeNullableInt24sID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x0000400F,
    ZGMTRAttributeIDTypeClusterUnitTestingAttributeNullableInt32sID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00004010,
    ZGMTRAttributeIDTypeClusterUnitTestingAttributeNullableInt40sID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00004011,
    ZGMTRAttributeIDTypeClusterUnitTestingAttributeNullableInt48sID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00004012,
    ZGMTRAttributeIDTypeClusterUnitTestingAttributeNullableInt56sID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00004013,
    ZGMTRAttributeIDTypeClusterUnitTestingAttributeNullableInt64sID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00004014,
    ZGMTRAttributeIDTypeClusterUnitTestingAttributeNullableEnum8ID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00004015,
    ZGMTRAttributeIDTypeClusterUnitTestingAttributeNullableEnum16ID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00004016,
    ZGMTRAttributeIDTypeClusterUnitTestingAttributeNullableFloatSingleID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00004017,
    ZGMTRAttributeIDTypeClusterUnitTestingAttributeNullableFloatDoubleID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00004018,
    ZGMTRAttributeIDTypeClusterUnitTestingAttributeNullableOctetStringID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00004019,
    ZGMTRAttributeIDTypeClusterUnitTestingAttributeNullableCharStringID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x0000401E,
    ZGMTRAttributeIDTypeClusterUnitTestingAttributeNullableEnumAttrID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00004024,
    ZGMTRAttributeIDTypeClusterUnitTestingAttributeNullableStructID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00004025,
    ZGMTRAttributeIDTypeClusterUnitTestingAttributeNullableRangeRestrictedInt8uID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00004026,
    ZGMTRAttributeIDTypeClusterUnitTestingAttributeNullableRangeRestrictedInt8sID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00004027,
    ZGMTRAttributeIDTypeClusterUnitTestingAttributeNullableRangeRestrictedInt16uID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00004028,
    ZGMTRAttributeIDTypeClusterUnitTestingAttributeNullableRangeRestrictedInt16sID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00004029,
    ZGMTRAttributeIDTypeClusterUnitTestingAttributeWriteOnlyInt8uID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x0000402A,
    ZGMTRAttributeIDTypeClusterUnitTestingAttributeNullableGlobalEnumID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00004033,
    ZGMTRAttributeIDTypeClusterUnitTestingAttributeNullableGlobalStructID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00004034,
    ZGMTRAttributeIDTypeClusterUnitTestingAttributeGeneratedCommandListID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = ZGMTRAttributeIDTypeGlobalAttributeGeneratedCommandListID,
    ZGMTRAttributeIDTypeClusterUnitTestingAttributeAcceptedCommandListID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = ZGMTRAttributeIDTypeGlobalAttributeAcceptedCommandListID,
    ZGMTRAttributeIDTypeClusterUnitTestingAttributeAttributeListID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = ZGMTRAttributeIDTypeGlobalAttributeAttributeListID,
    ZGMTRAttributeIDTypeClusterUnitTestingAttributeFeatureMapID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = ZGMTRAttributeIDTypeGlobalAttributeFeatureMapID,
    ZGMTRAttributeIDTypeClusterUnitTestingAttributeClusterRevisionID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = ZGMTRAttributeIDTypeGlobalAttributeClusterRevisionID,
    ZGMTRAttributeIDTypeClusterUnitTestingAttributeMeiInt8uID ZGMTR_PROVISIONALLY_AVAILABLE = 0xFFF24F01,

    // Cluster SampleMEI attributes
    ZGMTRAttributeIDTypeClusterSampleMEIAttributeFlipFlopID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000000,
    ZGMTRAttributeIDTypeClusterSampleMEIAttributeGeneratedCommandListID ZGMTR_PROVISIONALLY_AVAILABLE = ZGMTRAttributeIDTypeGlobalAttributeGeneratedCommandListID,
    ZGMTRAttributeIDTypeClusterSampleMEIAttributeAcceptedCommandListID ZGMTR_PROVISIONALLY_AVAILABLE = ZGMTRAttributeIDTypeGlobalAttributeAcceptedCommandListID,
    ZGMTRAttributeIDTypeClusterSampleMEIAttributeAttributeListID ZGMTR_PROVISIONALLY_AVAILABLE = ZGMTRAttributeIDTypeGlobalAttributeAttributeListID,
    ZGMTRAttributeIDTypeClusterSampleMEIAttributeFeatureMapID ZGMTR_PROVISIONALLY_AVAILABLE = ZGMTRAttributeIDTypeGlobalAttributeFeatureMapID,
    ZGMTRAttributeIDTypeClusterSampleMEIAttributeClusterRevisionID ZGMTR_PROVISIONALLY_AVAILABLE = ZGMTRAttributeIDTypeGlobalAttributeClusterRevisionID,

    // Cluster TestHiddenManufacturerSpecific attributes
    ZGMTRAttributeIDTypeClusterTestHiddenManufacturerSpecificAttributeTestAttributeID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000000,
    ZGMTRAttributeIDTypeClusterTestHiddenManufacturerSpecificAttributeGeneratedCommandListID ZGMTR_PROVISIONALLY_AVAILABLE = ZGMTRAttributeIDTypeGlobalAttributeGeneratedCommandListID,
    ZGMTRAttributeIDTypeClusterTestHiddenManufacturerSpecificAttributeAcceptedCommandListID ZGMTR_PROVISIONALLY_AVAILABLE = ZGMTRAttributeIDTypeGlobalAttributeAcceptedCommandListID,
    ZGMTRAttributeIDTypeClusterTestHiddenManufacturerSpecificAttributeAttributeListID ZGMTR_PROVISIONALLY_AVAILABLE = ZGMTRAttributeIDTypeGlobalAttributeAttributeListID,
    ZGMTRAttributeIDTypeClusterTestHiddenManufacturerSpecificAttributeFeatureMapID ZGMTR_PROVISIONALLY_AVAILABLE = ZGMTRAttributeIDTypeGlobalAttributeFeatureMapID,
    ZGMTRAttributeIDTypeClusterTestHiddenManufacturerSpecificAttributeClusterRevisionID ZGMTR_PROVISIONALLY_AVAILABLE = ZGMTRAttributeIDTypeGlobalAttributeClusterRevisionID,

    // Cluster BarrierControl deprecated attribute names
    ZGMTRClusterBarrierControlAttributeBarrierMovingStateID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterBarrierControlAttributeBarrierMovingStateID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x00000001,
    ZGMTRClusterBarrierControlAttributeBarrierSafetyStatusID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterBarrierControlAttributeBarrierSafetyStatusID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x00000002,
    ZGMTRClusterBarrierControlAttributeBarrierCapabilitiesID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterBarrierControlAttributeBarrierCapabilitiesID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x00000003,
    ZGMTRClusterBarrierControlAttributeBarrierOpenEventsID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterBarrierControlAttributeBarrierOpenEventsID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x00000004,
    ZGMTRClusterBarrierControlAttributeBarrierCloseEventsID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterBarrierControlAttributeBarrierCloseEventsID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x00000005,
    ZGMTRClusterBarrierControlAttributeBarrierCommandOpenEventsID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterBarrierControlAttributeBarrierCommandOpenEventsID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x00000006,
    ZGMTRClusterBarrierControlAttributeBarrierCommandCloseEventsID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterBarrierControlAttributeBarrierCommandCloseEventsID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x00000007,
    ZGMTRClusterBarrierControlAttributeBarrierOpenPeriodID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterBarrierControlAttributeBarrierOpenPeriodID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x00000008,
    ZGMTRClusterBarrierControlAttributeBarrierClosePeriodID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterBarrierControlAttributeBarrierClosePeriodID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x00000009,
    ZGMTRClusterBarrierControlAttributeBarrierPositionID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterBarrierControlAttributeBarrierPositionID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x0000000A,
    ZGMTRClusterBarrierControlAttributeGeneratedCommandListID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterBarrierControlAttributeGeneratedCommandListID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = ZGMTRClusterGlobalAttributeGeneratedCommandListID,
    ZGMTRClusterBarrierControlAttributeAcceptedCommandListID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterBarrierControlAttributeAcceptedCommandListID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = ZGMTRClusterGlobalAttributeAcceptedCommandListID,
    ZGMTRClusterBarrierControlAttributeAttributeListID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterBarrierControlAttributeAttributeListID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = ZGMTRClusterGlobalAttributeAttributeListID,
    ZGMTRClusterBarrierControlAttributeFeatureMapID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterBarrierControlAttributeFeatureMapID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = ZGMTRClusterGlobalAttributeFeatureMapID,
    ZGMTRClusterBarrierControlAttributeClusterRevisionID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterBarrierControlAttributeClusterRevisionID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = ZGMTRClusterGlobalAttributeClusterRevisionID,

    // Cluster BarrierControl attributes
    ZGMTRAttributeIDTypeClusterBarrierControlAttributeBarrierMovingStateID ZGMTR_DEPRECATED("The BarrierMovingState attribute will be removed", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2)) = 0x00000001,
    ZGMTRAttributeIDTypeClusterBarrierControlAttributeBarrierSafetyStatusID ZGMTR_DEPRECATED("The BarrierSafetyStatus attribute will be removed", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2)) = 0x00000002,
    ZGMTRAttributeIDTypeClusterBarrierControlAttributeBarrierCapabilitiesID ZGMTR_DEPRECATED("The BarrierCapabilities attribute will be removed", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2)) = 0x00000003,
    ZGMTRAttributeIDTypeClusterBarrierControlAttributeBarrierOpenEventsID ZGMTR_DEPRECATED("The BarrierOpenEvents attribute will be removed", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2)) = 0x00000004,
    ZGMTRAttributeIDTypeClusterBarrierControlAttributeBarrierCloseEventsID ZGMTR_DEPRECATED("The BarrierCloseEvents attribute will be removed", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2)) = 0x00000005,
    ZGMTRAttributeIDTypeClusterBarrierControlAttributeBarrierCommandOpenEventsID ZGMTR_DEPRECATED("The BarrierCommandOpenEvents attribute will be removed", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2)) = 0x00000006,
    ZGMTRAttributeIDTypeClusterBarrierControlAttributeBarrierCommandCloseEventsID ZGMTR_DEPRECATED("The BarrierCommandCloseEvents attribute will be removed", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2)) = 0x00000007,
    ZGMTRAttributeIDTypeClusterBarrierControlAttributeBarrierOpenPeriodID ZGMTR_DEPRECATED("The BarrierOpenPeriod attribute will be removed", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2)) = 0x00000008,
    ZGMTRAttributeIDTypeClusterBarrierControlAttributeBarrierClosePeriodID ZGMTR_DEPRECATED("The BarrierClosePeriod attribute will be removed", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2)) = 0x00000009,
    ZGMTRAttributeIDTypeClusterBarrierControlAttributeBarrierPositionID ZGMTR_DEPRECATED("The BarrierPosition attribute will be removed", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2)) = 0x0000000A,
    ZGMTRAttributeIDTypeClusterBarrierControlAttributeGeneratedCommandListID ZGMTR_DEPRECATED("The GeneratedCommandList attribute will be removed", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2)) = ZGMTRAttributeIDTypeGlobalAttributeGeneratedCommandListID,
    ZGMTRAttributeIDTypeClusterBarrierControlAttributeAcceptedCommandListID ZGMTR_DEPRECATED("The AcceptedCommandList attribute will be removed", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2)) = ZGMTRAttributeIDTypeGlobalAttributeAcceptedCommandListID,
    ZGMTRAttributeIDTypeClusterBarrierControlAttributeAttributeListID ZGMTR_DEPRECATED("The AttributeList attribute will be removed", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2)) = ZGMTRAttributeIDTypeGlobalAttributeAttributeListID,
    ZGMTRAttributeIDTypeClusterBarrierControlAttributeFeatureMapID ZGMTR_DEPRECATED("The FeatureMap attribute will be removed", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2)) = ZGMTRAttributeIDTypeGlobalAttributeFeatureMapID,
    ZGMTRAttributeIDTypeClusterBarrierControlAttributeClusterRevisionID ZGMTR_DEPRECATED("The ClusterRevision attribute will be removed", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2)) = ZGMTRAttributeIDTypeGlobalAttributeClusterRevisionID,

    // Cluster BinaryInputBasic deprecated attribute names
    ZGMTRClusterBinaryInputBasicAttributeActiveTextID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterBinaryInputBasicAttributeActiveTextID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x00000004,
    ZGMTRClusterBinaryInputBasicAttributeDescriptionID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterBinaryInputBasicAttributeDescriptionID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x0000001C,
    ZGMTRClusterBinaryInputBasicAttributeInactiveTextID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterBinaryInputBasicAttributeInactiveTextID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x0000002E,
    ZGMTRClusterBinaryInputBasicAttributeOutOfServiceID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterBinaryInputBasicAttributeOutOfServiceID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x00000051,
    ZGMTRClusterBinaryInputBasicAttributePolarityID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterBinaryInputBasicAttributePolarityID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x00000054,
    ZGMTRClusterBinaryInputBasicAttributePresentValueID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterBinaryInputBasicAttributePresentValueID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x00000055,
    ZGMTRClusterBinaryInputBasicAttributeReliabilityID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterBinaryInputBasicAttributeReliabilityID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x00000067,
    ZGMTRClusterBinaryInputBasicAttributeStatusFlagsID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterBinaryInputBasicAttributeStatusFlagsID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x0000006F,
    ZGMTRClusterBinaryInputBasicAttributeApplicationTypeID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterBinaryInputBasicAttributeApplicationTypeID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x00000100,
    ZGMTRClusterBinaryInputBasicAttributeGeneratedCommandListID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterBinaryInputBasicAttributeGeneratedCommandListID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = ZGMTRClusterGlobalAttributeGeneratedCommandListID,
    ZGMTRClusterBinaryInputBasicAttributeAcceptedCommandListID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterBinaryInputBasicAttributeAcceptedCommandListID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = ZGMTRClusterGlobalAttributeAcceptedCommandListID,
    ZGMTRClusterBinaryInputBasicAttributeAttributeListID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterBinaryInputBasicAttributeAttributeListID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = ZGMTRClusterGlobalAttributeAttributeListID,
    ZGMTRClusterBinaryInputBasicAttributeFeatureMapID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterBinaryInputBasicAttributeFeatureMapID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = ZGMTRClusterGlobalAttributeFeatureMapID,
    ZGMTRClusterBinaryInputBasicAttributeClusterRevisionID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterBinaryInputBasicAttributeClusterRevisionID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = ZGMTRClusterGlobalAttributeClusterRevisionID,

    // Cluster BinaryInputBasic attributes
    ZGMTRAttributeIDTypeClusterBinaryInputBasicAttributeActiveTextID ZGMTR_DEPRECATED("The ActiveText attribute will be removed", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2)) = 0x00000004,
    ZGMTRAttributeIDTypeClusterBinaryInputBasicAttributeDescriptionID ZGMTR_DEPRECATED("The Description attribute will be removed", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2)) = 0x0000001C,
    ZGMTRAttributeIDTypeClusterBinaryInputBasicAttributeInactiveTextID ZGMTR_DEPRECATED("The InactiveText attribute will be removed", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2)) = 0x0000002E,
    ZGMTRAttributeIDTypeClusterBinaryInputBasicAttributeOutOfServiceID ZGMTR_DEPRECATED("The OutOfService attribute will be removed", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2)) = 0x00000051,
    ZGMTRAttributeIDTypeClusterBinaryInputBasicAttributePolarityID ZGMTR_DEPRECATED("The Polarity attribute will be removed", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2)) = 0x00000054,
    ZGMTRAttributeIDTypeClusterBinaryInputBasicAttributePresentValueID ZGMTR_DEPRECATED("The PresentValue attribute will be removed", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2)) = 0x00000055,
    ZGMTRAttributeIDTypeClusterBinaryInputBasicAttributeReliabilityID ZGMTR_DEPRECATED("The Reliability attribute will be removed", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2)) = 0x00000067,
    ZGMTRAttributeIDTypeClusterBinaryInputBasicAttributeStatusFlagsID ZGMTR_DEPRECATED("The StatusFlags attribute will be removed", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2)) = 0x0000006F,
    ZGMTRAttributeIDTypeClusterBinaryInputBasicAttributeApplicationTypeID ZGMTR_DEPRECATED("The ApplicationType attribute will be removed", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2)) = 0x00000100,
    ZGMTRAttributeIDTypeClusterBinaryInputBasicAttributeGeneratedCommandListID ZGMTR_DEPRECATED("The GeneratedCommandList attribute will be removed", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2)) = ZGMTRAttributeIDTypeGlobalAttributeGeneratedCommandListID,
    ZGMTRAttributeIDTypeClusterBinaryInputBasicAttributeAcceptedCommandListID ZGMTR_DEPRECATED("The AcceptedCommandList attribute will be removed", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2)) = ZGMTRAttributeIDTypeGlobalAttributeAcceptedCommandListID,
    ZGMTRAttributeIDTypeClusterBinaryInputBasicAttributeAttributeListID ZGMTR_DEPRECATED("The AttributeList attribute will be removed", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2)) = ZGMTRAttributeIDTypeGlobalAttributeAttributeListID,
    ZGMTRAttributeIDTypeClusterBinaryInputBasicAttributeFeatureMapID ZGMTR_DEPRECATED("The FeatureMap attribute will be removed", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2)) = ZGMTRAttributeIDTypeGlobalAttributeFeatureMapID,
    ZGMTRAttributeIDTypeClusterBinaryInputBasicAttributeClusterRevisionID ZGMTR_DEPRECATED("The ClusterRevision attribute will be removed", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2)) = ZGMTRAttributeIDTypeGlobalAttributeClusterRevisionID,

    // Cluster ElectricalMeasurement deprecated attribute names
    ZGMTRClusterElectricalMeasurementAttributeMeasurementTypeID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterElectricalMeasurementAttributeMeasurementTypeID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x00000000,
    ZGMTRClusterElectricalMeasurementAttributeDcVoltageID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterElectricalMeasurementAttributeDcVoltageID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x00000100,
    ZGMTRClusterElectricalMeasurementAttributeDcVoltageMinID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterElectricalMeasurementAttributeDcVoltageMinID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x00000101,
    ZGMTRClusterElectricalMeasurementAttributeDcVoltageMaxID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterElectricalMeasurementAttributeDcVoltageMaxID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x00000102,
    ZGMTRClusterElectricalMeasurementAttributeDcCurrentID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterElectricalMeasurementAttributeDcCurrentID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x00000103,
    ZGMTRClusterElectricalMeasurementAttributeDcCurrentMinID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterElectricalMeasurementAttributeDcCurrentMinID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x00000104,
    ZGMTRClusterElectricalMeasurementAttributeDcCurrentMaxID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterElectricalMeasurementAttributeDcCurrentMaxID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x00000105,
    ZGMTRClusterElectricalMeasurementAttributeDcPowerID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterElectricalMeasurementAttributeDcPowerID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x00000106,
    ZGMTRClusterElectricalMeasurementAttributeDcPowerMinID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterElectricalMeasurementAttributeDcPowerMinID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x00000107,
    ZGMTRClusterElectricalMeasurementAttributeDcPowerMaxID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterElectricalMeasurementAttributeDcPowerMaxID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x00000108,
    ZGMTRClusterElectricalMeasurementAttributeDcVoltageMultiplierID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterElectricalMeasurementAttributeDcVoltageMultiplierID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x00000200,
    ZGMTRClusterElectricalMeasurementAttributeDcVoltageDivisorID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterElectricalMeasurementAttributeDcVoltageDivisorID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x00000201,
    ZGMTRClusterElectricalMeasurementAttributeDcCurrentMultiplierID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterElectricalMeasurementAttributeDcCurrentMultiplierID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x00000202,
    ZGMTRClusterElectricalMeasurementAttributeDcCurrentDivisorID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterElectricalMeasurementAttributeDcCurrentDivisorID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x00000203,
    ZGMTRClusterElectricalMeasurementAttributeDcPowerMultiplierID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterElectricalMeasurementAttributeDcPowerMultiplierID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x00000204,
    ZGMTRClusterElectricalMeasurementAttributeDcPowerDivisorID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterElectricalMeasurementAttributeDcPowerDivisorID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x00000205,
    ZGMTRClusterElectricalMeasurementAttributeAcFrequencyID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterElectricalMeasurementAttributeAcFrequencyID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x00000300,
    ZGMTRClusterElectricalMeasurementAttributeAcFrequencyMinID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterElectricalMeasurementAttributeAcFrequencyMinID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x00000301,
    ZGMTRClusterElectricalMeasurementAttributeAcFrequencyMaxID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterElectricalMeasurementAttributeAcFrequencyMaxID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x00000302,
    ZGMTRClusterElectricalMeasurementAttributeNeutralCurrentID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterElectricalMeasurementAttributeNeutralCurrentID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x00000303,
    ZGMTRClusterElectricalMeasurementAttributeTotalActivePowerID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterElectricalMeasurementAttributeTotalActivePowerID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x00000304,
    ZGMTRClusterElectricalMeasurementAttributeTotalReactivePowerID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterElectricalMeasurementAttributeTotalReactivePowerID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x00000305,
    ZGMTRClusterElectricalMeasurementAttributeTotalApparentPowerID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterElectricalMeasurementAttributeTotalApparentPowerID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x00000306,
    ZGMTRClusterElectricalMeasurementAttributeMeasured1stHarmonicCurrentID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterElectricalMeasurementAttributeMeasured1stHarmonicCurrentID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x00000307,
    ZGMTRClusterElectricalMeasurementAttributeMeasured3rdHarmonicCurrentID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterElectricalMeasurementAttributeMeasured3rdHarmonicCurrentID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x00000308,
    ZGMTRClusterElectricalMeasurementAttributeMeasured5thHarmonicCurrentID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterElectricalMeasurementAttributeMeasured5thHarmonicCurrentID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x00000309,
    ZGMTRClusterElectricalMeasurementAttributeMeasured7thHarmonicCurrentID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterElectricalMeasurementAttributeMeasured7thHarmonicCurrentID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x0000030A,
    ZGMTRClusterElectricalMeasurementAttributeMeasured9thHarmonicCurrentID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterElectricalMeasurementAttributeMeasured9thHarmonicCurrentID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x0000030B,
    ZGMTRClusterElectricalMeasurementAttributeMeasured11thHarmonicCurrentID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterElectricalMeasurementAttributeMeasured11thHarmonicCurrentID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x0000030C,
    ZGMTRClusterElectricalMeasurementAttributeMeasuredPhase1stHarmonicCurrentID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterElectricalMeasurementAttributeMeasuredPhase1stHarmonicCurrentID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x0000030D,
    ZGMTRClusterElectricalMeasurementAttributeMeasuredPhase3rdHarmonicCurrentID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterElectricalMeasurementAttributeMeasuredPhase3rdHarmonicCurrentID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x0000030E,
    ZGMTRClusterElectricalMeasurementAttributeMeasuredPhase5thHarmonicCurrentID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterElectricalMeasurementAttributeMeasuredPhase5thHarmonicCurrentID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x0000030F,
    ZGMTRClusterElectricalMeasurementAttributeMeasuredPhase7thHarmonicCurrentID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterElectricalMeasurementAttributeMeasuredPhase7thHarmonicCurrentID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x00000310,
    ZGMTRClusterElectricalMeasurementAttributeMeasuredPhase9thHarmonicCurrentID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterElectricalMeasurementAttributeMeasuredPhase9thHarmonicCurrentID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x00000311,
    ZGMTRClusterElectricalMeasurementAttributeMeasuredPhase11thHarmonicCurrentID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterElectricalMeasurementAttributeMeasuredPhase11thHarmonicCurrentID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x00000312,
    ZGMTRClusterElectricalMeasurementAttributeAcFrequencyMultiplierID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterElectricalMeasurementAttributeAcFrequencyMultiplierID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x00000400,
    ZGMTRClusterElectricalMeasurementAttributeAcFrequencyDivisorID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterElectricalMeasurementAttributeAcFrequencyDivisorID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x00000401,
    ZGMTRClusterElectricalMeasurementAttributePowerMultiplierID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterElectricalMeasurementAttributePowerMultiplierID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x00000402,
    ZGMTRClusterElectricalMeasurementAttributePowerDivisorID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterElectricalMeasurementAttributePowerDivisorID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x00000403,
    ZGMTRClusterElectricalMeasurementAttributeHarmonicCurrentMultiplierID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterElectricalMeasurementAttributeHarmonicCurrentMultiplierID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x00000404,
    ZGMTRClusterElectricalMeasurementAttributePhaseHarmonicCurrentMultiplierID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterElectricalMeasurementAttributePhaseHarmonicCurrentMultiplierID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x00000405,
    ZGMTRClusterElectricalMeasurementAttributeInstantaneousVoltageID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterElectricalMeasurementAttributeInstantaneousVoltageID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x00000500,
    ZGMTRClusterElectricalMeasurementAttributeInstantaneousLineCurrentID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterElectricalMeasurementAttributeInstantaneousLineCurrentID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x00000501,
    ZGMTRClusterElectricalMeasurementAttributeInstantaneousActiveCurrentID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterElectricalMeasurementAttributeInstantaneousActiveCurrentID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x00000502,
    ZGMTRClusterElectricalMeasurementAttributeInstantaneousReactiveCurrentID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterElectricalMeasurementAttributeInstantaneousReactiveCurrentID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x00000503,
    ZGMTRClusterElectricalMeasurementAttributeInstantaneousPowerID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterElectricalMeasurementAttributeInstantaneousPowerID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x00000504,
    ZGMTRClusterElectricalMeasurementAttributeRmsVoltageID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterElectricalMeasurementAttributeRmsVoltageID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x00000505,
    ZGMTRClusterElectricalMeasurementAttributeRmsVoltageMinID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterElectricalMeasurementAttributeRmsVoltageMinID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x00000506,
    ZGMTRClusterElectricalMeasurementAttributeRmsVoltageMaxID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterElectricalMeasurementAttributeRmsVoltageMaxID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x00000507,
    ZGMTRClusterElectricalMeasurementAttributeRmsCurrentID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterElectricalMeasurementAttributeRmsCurrentID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x00000508,
    ZGMTRClusterElectricalMeasurementAttributeRmsCurrentMinID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterElectricalMeasurementAttributeRmsCurrentMinID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x00000509,
    ZGMTRClusterElectricalMeasurementAttributeRmsCurrentMaxID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterElectricalMeasurementAttributeRmsCurrentMaxID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x0000050A,
    ZGMTRClusterElectricalMeasurementAttributeActivePowerID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterElectricalMeasurementAttributeActivePowerID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x0000050B,
    ZGMTRClusterElectricalMeasurementAttributeActivePowerMinID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterElectricalMeasurementAttributeActivePowerMinID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x0000050C,
    ZGMTRClusterElectricalMeasurementAttributeActivePowerMaxID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterElectricalMeasurementAttributeActivePowerMaxID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x0000050D,
    ZGMTRClusterElectricalMeasurementAttributeReactivePowerID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterElectricalMeasurementAttributeReactivePowerID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x0000050E,
    ZGMTRClusterElectricalMeasurementAttributeApparentPowerID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterElectricalMeasurementAttributeApparentPowerID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x0000050F,
    ZGMTRClusterElectricalMeasurementAttributePowerFactorID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterElectricalMeasurementAttributePowerFactorID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x00000510,
    ZGMTRClusterElectricalMeasurementAttributeAverageRmsVoltageMeasurementPeriodID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterElectricalMeasurementAttributeAverageRmsVoltageMeasurementPeriodID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x00000511,
    ZGMTRClusterElectricalMeasurementAttributeAverageRmsUnderVoltageCounterID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterElectricalMeasurementAttributeAverageRmsUnderVoltageCounterID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x00000513,
    ZGMTRClusterElectricalMeasurementAttributeRmsExtremeOverVoltagePeriodID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterElectricalMeasurementAttributeRmsExtremeOverVoltagePeriodID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x00000514,
    ZGMTRClusterElectricalMeasurementAttributeRmsExtremeUnderVoltagePeriodID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterElectricalMeasurementAttributeRmsExtremeUnderVoltagePeriodID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x00000515,
    ZGMTRClusterElectricalMeasurementAttributeRmsVoltageSagPeriodID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterElectricalMeasurementAttributeRmsVoltageSagPeriodID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x00000516,
    ZGMTRClusterElectricalMeasurementAttributeRmsVoltageSwellPeriodID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterElectricalMeasurementAttributeRmsVoltageSwellPeriodID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x00000517,
    ZGMTRClusterElectricalMeasurementAttributeAcVoltageMultiplierID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterElectricalMeasurementAttributeAcVoltageMultiplierID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x00000600,
    ZGMTRClusterElectricalMeasurementAttributeAcVoltageDivisorID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterElectricalMeasurementAttributeAcVoltageDivisorID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x00000601,
    ZGMTRClusterElectricalMeasurementAttributeAcCurrentMultiplierID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterElectricalMeasurementAttributeAcCurrentMultiplierID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x00000602,
    ZGMTRClusterElectricalMeasurementAttributeAcCurrentDivisorID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterElectricalMeasurementAttributeAcCurrentDivisorID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x00000603,
    ZGMTRClusterElectricalMeasurementAttributeAcPowerMultiplierID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterElectricalMeasurementAttributeAcPowerMultiplierID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x00000604,
    ZGMTRClusterElectricalMeasurementAttributeAcPowerDivisorID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterElectricalMeasurementAttributeAcPowerDivisorID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x00000605,
    ZGMTRClusterElectricalMeasurementAttributeOverloadAlarmsMaskID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterElectricalMeasurementAttributeOverloadAlarmsMaskID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x00000700,
    ZGMTRClusterElectricalMeasurementAttributeVoltageOverloadID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterElectricalMeasurementAttributeVoltageOverloadID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x00000701,
    ZGMTRClusterElectricalMeasurementAttributeCurrentOverloadID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterElectricalMeasurementAttributeCurrentOverloadID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x00000702,
    ZGMTRClusterElectricalMeasurementAttributeAcOverloadAlarmsMaskID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterElectricalMeasurementAttributeAcOverloadAlarmsMaskID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x00000800,
    ZGMTRClusterElectricalMeasurementAttributeAcVoltageOverloadID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterElectricalMeasurementAttributeAcVoltageOverloadID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x00000801,
    ZGMTRClusterElectricalMeasurementAttributeAcCurrentOverloadID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterElectricalMeasurementAttributeAcCurrentOverloadID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x00000802,
    ZGMTRClusterElectricalMeasurementAttributeAcActivePowerOverloadID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterElectricalMeasurementAttributeAcActivePowerOverloadID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x00000803,
    ZGMTRClusterElectricalMeasurementAttributeAcReactivePowerOverloadID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterElectricalMeasurementAttributeAcReactivePowerOverloadID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x00000804,
    ZGMTRClusterElectricalMeasurementAttributeAverageRmsOverVoltageID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterElectricalMeasurementAttributeAverageRmsOverVoltageID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x00000805,
    ZGMTRClusterElectricalMeasurementAttributeAverageRmsUnderVoltageID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterElectricalMeasurementAttributeAverageRmsUnderVoltageID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x00000806,
    ZGMTRClusterElectricalMeasurementAttributeRmsExtremeOverVoltageID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterElectricalMeasurementAttributeRmsExtremeOverVoltageID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x00000807,
    ZGMTRClusterElectricalMeasurementAttributeRmsExtremeUnderVoltageID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterElectricalMeasurementAttributeRmsExtremeUnderVoltageID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x00000808,
    ZGMTRClusterElectricalMeasurementAttributeRmsVoltageSagID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterElectricalMeasurementAttributeRmsVoltageSagID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x00000809,
    ZGMTRClusterElectricalMeasurementAttributeRmsVoltageSwellID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterElectricalMeasurementAttributeRmsVoltageSwellID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x0000080A,
    ZGMTRClusterElectricalMeasurementAttributeLineCurrentPhaseBID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterElectricalMeasurementAttributeLineCurrentPhaseBID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x00000901,
    ZGMTRClusterElectricalMeasurementAttributeActiveCurrentPhaseBID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterElectricalMeasurementAttributeActiveCurrentPhaseBID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x00000902,
    ZGMTRClusterElectricalMeasurementAttributeReactiveCurrentPhaseBID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterElectricalMeasurementAttributeReactiveCurrentPhaseBID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x00000903,
    ZGMTRClusterElectricalMeasurementAttributeRmsVoltagePhaseBID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterElectricalMeasurementAttributeRmsVoltagePhaseBID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x00000905,
    ZGMTRClusterElectricalMeasurementAttributeRmsVoltageMinPhaseBID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterElectricalMeasurementAttributeRmsVoltageMinPhaseBID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x00000906,
    ZGMTRClusterElectricalMeasurementAttributeRmsVoltageMaxPhaseBID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterElectricalMeasurementAttributeRmsVoltageMaxPhaseBID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x00000907,
    ZGMTRClusterElectricalMeasurementAttributeRmsCurrentPhaseBID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterElectricalMeasurementAttributeRmsCurrentPhaseBID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x00000908,
    ZGMTRClusterElectricalMeasurementAttributeRmsCurrentMinPhaseBID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterElectricalMeasurementAttributeRmsCurrentMinPhaseBID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x00000909,
    ZGMTRClusterElectricalMeasurementAttributeRmsCurrentMaxPhaseBID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterElectricalMeasurementAttributeRmsCurrentMaxPhaseBID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x0000090A,
    ZGMTRClusterElectricalMeasurementAttributeActivePowerPhaseBID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterElectricalMeasurementAttributeActivePowerPhaseBID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x0000090B,
    ZGMTRClusterElectricalMeasurementAttributeActivePowerMinPhaseBID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterElectricalMeasurementAttributeActivePowerMinPhaseBID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x0000090C,
    ZGMTRClusterElectricalMeasurementAttributeActivePowerMaxPhaseBID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterElectricalMeasurementAttributeActivePowerMaxPhaseBID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x0000090D,
    ZGMTRClusterElectricalMeasurementAttributeReactivePowerPhaseBID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterElectricalMeasurementAttributeReactivePowerPhaseBID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x0000090E,
    ZGMTRClusterElectricalMeasurementAttributeApparentPowerPhaseBID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterElectricalMeasurementAttributeApparentPowerPhaseBID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x0000090F,
    ZGMTRClusterElectricalMeasurementAttributePowerFactorPhaseBID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterElectricalMeasurementAttributePowerFactorPhaseBID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x00000910,
    ZGMTRClusterElectricalMeasurementAttributeAverageRmsVoltageMeasurementPeriodPhaseBID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterElectricalMeasurementAttributeAverageRmsVoltageMeasurementPeriodPhaseBID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x00000911,
    ZGMTRClusterElectricalMeasurementAttributeAverageRmsOverVoltageCounterPhaseBID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterElectricalMeasurementAttributeAverageRmsOverVoltageCounterPhaseBID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x00000912,
    ZGMTRClusterElectricalMeasurementAttributeAverageRmsUnderVoltageCounterPhaseBID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterElectricalMeasurementAttributeAverageRmsUnderVoltageCounterPhaseBID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x00000913,
    ZGMTRClusterElectricalMeasurementAttributeRmsExtremeOverVoltagePeriodPhaseBID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterElectricalMeasurementAttributeRmsExtremeOverVoltagePeriodPhaseBID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x00000914,
    ZGMTRClusterElectricalMeasurementAttributeRmsExtremeUnderVoltagePeriodPhaseBID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterElectricalMeasurementAttributeRmsExtremeUnderVoltagePeriodPhaseBID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x00000915,
    ZGMTRClusterElectricalMeasurementAttributeRmsVoltageSagPeriodPhaseBID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterElectricalMeasurementAttributeRmsVoltageSagPeriodPhaseBID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x00000916,
    ZGMTRClusterElectricalMeasurementAttributeRmsVoltageSwellPeriodPhaseBID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterElectricalMeasurementAttributeRmsVoltageSwellPeriodPhaseBID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x00000917,
    ZGMTRClusterElectricalMeasurementAttributeLineCurrentPhaseCID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterElectricalMeasurementAttributeLineCurrentPhaseCID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x00000A01,
    ZGMTRClusterElectricalMeasurementAttributeActiveCurrentPhaseCID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterElectricalMeasurementAttributeActiveCurrentPhaseCID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x00000A02,
    ZGMTRClusterElectricalMeasurementAttributeReactiveCurrentPhaseCID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterElectricalMeasurementAttributeReactiveCurrentPhaseCID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x00000A03,
    ZGMTRClusterElectricalMeasurementAttributeRmsVoltagePhaseCID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterElectricalMeasurementAttributeRmsVoltagePhaseCID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x00000A05,
    ZGMTRClusterElectricalMeasurementAttributeRmsVoltageMinPhaseCID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterElectricalMeasurementAttributeRmsVoltageMinPhaseCID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x00000A06,
    ZGMTRClusterElectricalMeasurementAttributeRmsVoltageMaxPhaseCID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterElectricalMeasurementAttributeRmsVoltageMaxPhaseCID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x00000A07,
    ZGMTRClusterElectricalMeasurementAttributeRmsCurrentPhaseCID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterElectricalMeasurementAttributeRmsCurrentPhaseCID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x00000A08,
    ZGMTRClusterElectricalMeasurementAttributeRmsCurrentMinPhaseCID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterElectricalMeasurementAttributeRmsCurrentMinPhaseCID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x00000A09,
    ZGMTRClusterElectricalMeasurementAttributeRmsCurrentMaxPhaseCID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterElectricalMeasurementAttributeRmsCurrentMaxPhaseCID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x00000A0A,
    ZGMTRClusterElectricalMeasurementAttributeActivePowerPhaseCID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterElectricalMeasurementAttributeActivePowerPhaseCID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x00000A0B,
    ZGMTRClusterElectricalMeasurementAttributeActivePowerMinPhaseCID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterElectricalMeasurementAttributeActivePowerMinPhaseCID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x00000A0C,
    ZGMTRClusterElectricalMeasurementAttributeActivePowerMaxPhaseCID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterElectricalMeasurementAttributeActivePowerMaxPhaseCID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x00000A0D,
    ZGMTRClusterElectricalMeasurementAttributeReactivePowerPhaseCID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterElectricalMeasurementAttributeReactivePowerPhaseCID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x00000A0E,
    ZGMTRClusterElectricalMeasurementAttributeApparentPowerPhaseCID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterElectricalMeasurementAttributeApparentPowerPhaseCID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x00000A0F,
    ZGMTRClusterElectricalMeasurementAttributePowerFactorPhaseCID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterElectricalMeasurementAttributePowerFactorPhaseCID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x00000A10,
    ZGMTRClusterElectricalMeasurementAttributeAverageRmsVoltageMeasurementPeriodPhaseCID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterElectricalMeasurementAttributeAverageRmsVoltageMeasurementPeriodPhaseCID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x00000A11,
    ZGMTRClusterElectricalMeasurementAttributeAverageRmsOverVoltageCounterPhaseCID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterElectricalMeasurementAttributeAverageRmsOverVoltageCounterPhaseCID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x00000A12,
    ZGMTRClusterElectricalMeasurementAttributeAverageRmsUnderVoltageCounterPhaseCID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterElectricalMeasurementAttributeAverageRmsUnderVoltageCounterPhaseCID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x00000A13,
    ZGMTRClusterElectricalMeasurementAttributeRmsExtremeOverVoltagePeriodPhaseCID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterElectricalMeasurementAttributeRmsExtremeOverVoltagePeriodPhaseCID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x00000A14,
    ZGMTRClusterElectricalMeasurementAttributeRmsExtremeUnderVoltagePeriodPhaseCID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterElectricalMeasurementAttributeRmsExtremeUnderVoltagePeriodPhaseCID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x00000A15,
    ZGMTRClusterElectricalMeasurementAttributeRmsVoltageSagPeriodPhaseCID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterElectricalMeasurementAttributeRmsVoltageSagPeriodPhaseCID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x00000A16,
    ZGMTRClusterElectricalMeasurementAttributeRmsVoltageSwellPeriodPhaseCID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterElectricalMeasurementAttributeRmsVoltageSwellPeriodPhaseCID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x00000A17,
    ZGMTRClusterElectricalMeasurementAttributeGeneratedCommandListID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterElectricalMeasurementAttributeGeneratedCommandListID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = ZGMTRClusterGlobalAttributeGeneratedCommandListID,
    ZGMTRClusterElectricalMeasurementAttributeAcceptedCommandListID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterElectricalMeasurementAttributeAcceptedCommandListID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = ZGMTRClusterGlobalAttributeAcceptedCommandListID,
    ZGMTRClusterElectricalMeasurementAttributeAttributeListID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterElectricalMeasurementAttributeAttributeListID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = ZGMTRClusterGlobalAttributeAttributeListID,
    ZGMTRClusterElectricalMeasurementAttributeFeatureMapID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterElectricalMeasurementAttributeFeatureMapID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = ZGMTRClusterGlobalAttributeFeatureMapID,
    ZGMTRClusterElectricalMeasurementAttributeClusterRevisionID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterElectricalMeasurementAttributeClusterRevisionID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = ZGMTRClusterGlobalAttributeClusterRevisionID,

    // Cluster ElectricalMeasurement attributes
    ZGMTRAttributeIDTypeClusterElectricalMeasurementAttributeMeasurementTypeID ZGMTR_DEPRECATED("The MeasurementType attribute will be removed", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2)) = 0x00000000,
    ZGMTRAttributeIDTypeClusterElectricalMeasurementAttributeDcVoltageID ZGMTR_DEPRECATED("The DcVoltage attribute will be removed", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2)) = 0x00000100,
    ZGMTRAttributeIDTypeClusterElectricalMeasurementAttributeDcVoltageMinID ZGMTR_DEPRECATED("The DcVoltageMin attribute will be removed", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2)) = 0x00000101,
    ZGMTRAttributeIDTypeClusterElectricalMeasurementAttributeDcVoltageMaxID ZGMTR_DEPRECATED("The DcVoltageMax attribute will be removed", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2)) = 0x00000102,
    ZGMTRAttributeIDTypeClusterElectricalMeasurementAttributeDcCurrentID ZGMTR_DEPRECATED("The DcCurrent attribute will be removed", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2)) = 0x00000103,
    ZGMTRAttributeIDTypeClusterElectricalMeasurementAttributeDcCurrentMinID ZGMTR_DEPRECATED("The DcCurrentMin attribute will be removed", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2)) = 0x00000104,
    ZGMTRAttributeIDTypeClusterElectricalMeasurementAttributeDcCurrentMaxID ZGMTR_DEPRECATED("The DcCurrentMax attribute will be removed", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2)) = 0x00000105,
    ZGMTRAttributeIDTypeClusterElectricalMeasurementAttributeDcPowerID ZGMTR_DEPRECATED("The DcPower attribute will be removed", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2)) = 0x00000106,
    ZGMTRAttributeIDTypeClusterElectricalMeasurementAttributeDcPowerMinID ZGMTR_DEPRECATED("The DcPowerMin attribute will be removed", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2)) = 0x00000107,
    ZGMTRAttributeIDTypeClusterElectricalMeasurementAttributeDcPowerMaxID ZGMTR_DEPRECATED("The DcPowerMax attribute will be removed", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2)) = 0x00000108,
    ZGMTRAttributeIDTypeClusterElectricalMeasurementAttributeDcVoltageMultiplierID ZGMTR_DEPRECATED("The DcVoltageMultiplier attribute will be removed", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2)) = 0x00000200,
    ZGMTRAttributeIDTypeClusterElectricalMeasurementAttributeDcVoltageDivisorID ZGMTR_DEPRECATED("The DcVoltageDivisor attribute will be removed", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2)) = 0x00000201,
    ZGMTRAttributeIDTypeClusterElectricalMeasurementAttributeDcCurrentMultiplierID ZGMTR_DEPRECATED("The DcCurrentMultiplier attribute will be removed", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2)) = 0x00000202,
    ZGMTRAttributeIDTypeClusterElectricalMeasurementAttributeDcCurrentDivisorID ZGMTR_DEPRECATED("The DcCurrentDivisor attribute will be removed", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2)) = 0x00000203,
    ZGMTRAttributeIDTypeClusterElectricalMeasurementAttributeDcPowerMultiplierID ZGMTR_DEPRECATED("The DcPowerMultiplier attribute will be removed", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2)) = 0x00000204,
    ZGMTRAttributeIDTypeClusterElectricalMeasurementAttributeDcPowerDivisorID ZGMTR_DEPRECATED("The DcPowerDivisor attribute will be removed", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2)) = 0x00000205,
    ZGMTRAttributeIDTypeClusterElectricalMeasurementAttributeAcFrequencyID ZGMTR_DEPRECATED("The AcFrequency attribute will be removed", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2)) = 0x00000300,
    ZGMTRAttributeIDTypeClusterElectricalMeasurementAttributeAcFrequencyMinID ZGMTR_DEPRECATED("The AcFrequencyMin attribute will be removed", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2)) = 0x00000301,
    ZGMTRAttributeIDTypeClusterElectricalMeasurementAttributeAcFrequencyMaxID ZGMTR_DEPRECATED("The AcFrequencyMax attribute will be removed", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2)) = 0x00000302,
    ZGMTRAttributeIDTypeClusterElectricalMeasurementAttributeNeutralCurrentID ZGMTR_DEPRECATED("The NeutralCurrent attribute will be removed", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2)) = 0x00000303,
    ZGMTRAttributeIDTypeClusterElectricalMeasurementAttributeTotalActivePowerID ZGMTR_DEPRECATED("The TotalActivePower attribute will be removed", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2)) = 0x00000304,
    ZGMTRAttributeIDTypeClusterElectricalMeasurementAttributeTotalReactivePowerID ZGMTR_DEPRECATED("The TotalReactivePower attribute will be removed", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2)) = 0x00000305,
    ZGMTRAttributeIDTypeClusterElectricalMeasurementAttributeTotalApparentPowerID ZGMTR_DEPRECATED("The TotalApparentPower attribute will be removed", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2)) = 0x00000306,
    ZGMTRAttributeIDTypeClusterElectricalMeasurementAttributeMeasured1stHarmonicCurrentID ZGMTR_DEPRECATED("The Measured1stHarmonicCurrent attribute will be removed", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2)) = 0x00000307,
    ZGMTRAttributeIDTypeClusterElectricalMeasurementAttributeMeasured3rdHarmonicCurrentID ZGMTR_DEPRECATED("The Measured3rdHarmonicCurrent attribute will be removed", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2)) = 0x00000308,
    ZGMTRAttributeIDTypeClusterElectricalMeasurementAttributeMeasured5thHarmonicCurrentID ZGMTR_DEPRECATED("The Measured5thHarmonicCurrent attribute will be removed", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2)) = 0x00000309,
    ZGMTRAttributeIDTypeClusterElectricalMeasurementAttributeMeasured7thHarmonicCurrentID ZGMTR_DEPRECATED("The Measured7thHarmonicCurrent attribute will be removed", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2)) = 0x0000030A,
    ZGMTRAttributeIDTypeClusterElectricalMeasurementAttributeMeasured9thHarmonicCurrentID ZGMTR_DEPRECATED("The Measured9thHarmonicCurrent attribute will be removed", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2)) = 0x0000030B,
    ZGMTRAttributeIDTypeClusterElectricalMeasurementAttributeMeasured11thHarmonicCurrentID ZGMTR_DEPRECATED("The Measured11thHarmonicCurrent attribute will be removed", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2)) = 0x0000030C,
    ZGMTRAttributeIDTypeClusterElectricalMeasurementAttributeMeasuredPhase1stHarmonicCurrentID ZGMTR_DEPRECATED("The MeasuredPhase1stHarmonicCurrent attribute will be removed", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2)) = 0x0000030D,
    ZGMTRAttributeIDTypeClusterElectricalMeasurementAttributeMeasuredPhase3rdHarmonicCurrentID ZGMTR_DEPRECATED("The MeasuredPhase3rdHarmonicCurrent attribute will be removed", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2)) = 0x0000030E,
    ZGMTRAttributeIDTypeClusterElectricalMeasurementAttributeMeasuredPhase5thHarmonicCurrentID ZGMTR_DEPRECATED("The MeasuredPhase5thHarmonicCurrent attribute will be removed", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2)) = 0x0000030F,
    ZGMTRAttributeIDTypeClusterElectricalMeasurementAttributeMeasuredPhase7thHarmonicCurrentID ZGMTR_DEPRECATED("The MeasuredPhase7thHarmonicCurrent attribute will be removed", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2)) = 0x00000310,
    ZGMTRAttributeIDTypeClusterElectricalMeasurementAttributeMeasuredPhase9thHarmonicCurrentID ZGMTR_DEPRECATED("The MeasuredPhase9thHarmonicCurrent attribute will be removed", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2)) = 0x00000311,
    ZGMTRAttributeIDTypeClusterElectricalMeasurementAttributeMeasuredPhase11thHarmonicCurrentID ZGMTR_DEPRECATED("The MeasuredPhase11thHarmonicCurrent attribute will be removed", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2)) = 0x00000312,
    ZGMTRAttributeIDTypeClusterElectricalMeasurementAttributeAcFrequencyMultiplierID ZGMTR_DEPRECATED("The AcFrequencyMultiplier attribute will be removed", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2)) = 0x00000400,
    ZGMTRAttributeIDTypeClusterElectricalMeasurementAttributeAcFrequencyDivisorID ZGMTR_DEPRECATED("The AcFrequencyDivisor attribute will be removed", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2)) = 0x00000401,
    ZGMTRAttributeIDTypeClusterElectricalMeasurementAttributePowerMultiplierID ZGMTR_DEPRECATED("The PowerMultiplier attribute will be removed", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2)) = 0x00000402,
    ZGMTRAttributeIDTypeClusterElectricalMeasurementAttributePowerDivisorID ZGMTR_DEPRECATED("The PowerDivisor attribute will be removed", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2)) = 0x00000403,
    ZGMTRAttributeIDTypeClusterElectricalMeasurementAttributeHarmonicCurrentMultiplierID ZGMTR_DEPRECATED("The HarmonicCurrentMultiplier attribute will be removed", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2)) = 0x00000404,
    ZGMTRAttributeIDTypeClusterElectricalMeasurementAttributePhaseHarmonicCurrentMultiplierID ZGMTR_DEPRECATED("The PhaseHarmonicCurrentMultiplier attribute will be removed", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2)) = 0x00000405,
    ZGMTRAttributeIDTypeClusterElectricalMeasurementAttributeInstantaneousVoltageID ZGMTR_DEPRECATED("The InstantaneousVoltage attribute will be removed", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2)) = 0x00000500,
    ZGMTRAttributeIDTypeClusterElectricalMeasurementAttributeInstantaneousLineCurrentID ZGMTR_DEPRECATED("The InstantaneousLineCurrent attribute will be removed", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2)) = 0x00000501,
    ZGMTRAttributeIDTypeClusterElectricalMeasurementAttributeInstantaneousActiveCurrentID ZGMTR_DEPRECATED("The InstantaneousActiveCurrent attribute will be removed", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2)) = 0x00000502,
    ZGMTRAttributeIDTypeClusterElectricalMeasurementAttributeInstantaneousReactiveCurrentID ZGMTR_DEPRECATED("The InstantaneousReactiveCurrent attribute will be removed", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2)) = 0x00000503,
    ZGMTRAttributeIDTypeClusterElectricalMeasurementAttributeInstantaneousPowerID ZGMTR_DEPRECATED("The InstantaneousPower attribute will be removed", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2)) = 0x00000504,
    ZGMTRAttributeIDTypeClusterElectricalMeasurementAttributeRmsVoltageID ZGMTR_DEPRECATED("The RmsVoltage attribute will be removed", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2)) = 0x00000505,
    ZGMTRAttributeIDTypeClusterElectricalMeasurementAttributeRmsVoltageMinID ZGMTR_DEPRECATED("The RmsVoltageMin attribute will be removed", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2)) = 0x00000506,
    ZGMTRAttributeIDTypeClusterElectricalMeasurementAttributeRmsVoltageMaxID ZGMTR_DEPRECATED("The RmsVoltageMax attribute will be removed", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2)) = 0x00000507,
    ZGMTRAttributeIDTypeClusterElectricalMeasurementAttributeRmsCurrentID ZGMTR_DEPRECATED("The RmsCurrent attribute will be removed", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2)) = 0x00000508,
    ZGMTRAttributeIDTypeClusterElectricalMeasurementAttributeRmsCurrentMinID ZGMTR_DEPRECATED("The RmsCurrentMin attribute will be removed", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2)) = 0x00000509,
    ZGMTRAttributeIDTypeClusterElectricalMeasurementAttributeRmsCurrentMaxID ZGMTR_DEPRECATED("The RmsCurrentMax attribute will be removed", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2)) = 0x0000050A,
    ZGMTRAttributeIDTypeClusterElectricalMeasurementAttributeActivePowerID ZGMTR_DEPRECATED("The ActivePower attribute will be removed", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2)) = 0x0000050B,
    ZGMTRAttributeIDTypeClusterElectricalMeasurementAttributeActivePowerMinID ZGMTR_DEPRECATED("The ActivePowerMin attribute will be removed", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2)) = 0x0000050C,
    ZGMTRAttributeIDTypeClusterElectricalMeasurementAttributeActivePowerMaxID ZGMTR_DEPRECATED("The ActivePowerMax attribute will be removed", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2)) = 0x0000050D,
    ZGMTRAttributeIDTypeClusterElectricalMeasurementAttributeReactivePowerID ZGMTR_DEPRECATED("The ReactivePower attribute will be removed", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2)) = 0x0000050E,
    ZGMTRAttributeIDTypeClusterElectricalMeasurementAttributeApparentPowerID ZGMTR_DEPRECATED("The ApparentPower attribute will be removed", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2)) = 0x0000050F,
    ZGMTRAttributeIDTypeClusterElectricalMeasurementAttributePowerFactorID ZGMTR_DEPRECATED("The PowerFactor attribute will be removed", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2)) = 0x00000510,
    ZGMTRAttributeIDTypeClusterElectricalMeasurementAttributeAverageRmsVoltageMeasurementPeriodID ZGMTR_DEPRECATED("The AverageRmsVoltageMeasurementPeriod attribute will be removed", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2)) = 0x00000511,
    ZGMTRAttributeIDTypeClusterElectricalMeasurementAttributeAverageRmsUnderVoltageCounterID ZGMTR_DEPRECATED("The AverageRmsUnderVoltageCounter attribute will be removed", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2)) = 0x00000513,
    ZGMTRAttributeIDTypeClusterElectricalMeasurementAttributeRmsExtremeOverVoltagePeriodID ZGMTR_DEPRECATED("The RmsExtremeOverVoltagePeriod attribute will be removed", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2)) = 0x00000514,
    ZGMTRAttributeIDTypeClusterElectricalMeasurementAttributeRmsExtremeUnderVoltagePeriodID ZGMTR_DEPRECATED("The RmsExtremeUnderVoltagePeriod attribute will be removed", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2)) = 0x00000515,
    ZGMTRAttributeIDTypeClusterElectricalMeasurementAttributeRmsVoltageSagPeriodID ZGMTR_DEPRECATED("The RmsVoltageSagPeriod attribute will be removed", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2)) = 0x00000516,
    ZGMTRAttributeIDTypeClusterElectricalMeasurementAttributeRmsVoltageSwellPeriodID ZGMTR_DEPRECATED("The RmsVoltageSwellPeriod attribute will be removed", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2)) = 0x00000517,
    ZGMTRAttributeIDTypeClusterElectricalMeasurementAttributeAcVoltageMultiplierID ZGMTR_DEPRECATED("The AcVoltageMultiplier attribute will be removed", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2)) = 0x00000600,
    ZGMTRAttributeIDTypeClusterElectricalMeasurementAttributeAcVoltageDivisorID ZGMTR_DEPRECATED("The AcVoltageDivisor attribute will be removed", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2)) = 0x00000601,
    ZGMTRAttributeIDTypeClusterElectricalMeasurementAttributeAcCurrentMultiplierID ZGMTR_DEPRECATED("The AcCurrentMultiplier attribute will be removed", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2)) = 0x00000602,
    ZGMTRAttributeIDTypeClusterElectricalMeasurementAttributeAcCurrentDivisorID ZGMTR_DEPRECATED("The AcCurrentDivisor attribute will be removed", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2)) = 0x00000603,
    ZGMTRAttributeIDTypeClusterElectricalMeasurementAttributeAcPowerMultiplierID ZGMTR_DEPRECATED("The AcPowerMultiplier attribute will be removed", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2)) = 0x00000604,
    ZGMTRAttributeIDTypeClusterElectricalMeasurementAttributeAcPowerDivisorID ZGMTR_DEPRECATED("The AcPowerDivisor attribute will be removed", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2)) = 0x00000605,
    ZGMTRAttributeIDTypeClusterElectricalMeasurementAttributeOverloadAlarmsMaskID ZGMTR_DEPRECATED("The OverloadAlarmsMask attribute will be removed", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2)) = 0x00000700,
    ZGMTRAttributeIDTypeClusterElectricalMeasurementAttributeVoltageOverloadID ZGMTR_DEPRECATED("The VoltageOverload attribute will be removed", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2)) = 0x00000701,
    ZGMTRAttributeIDTypeClusterElectricalMeasurementAttributeCurrentOverloadID ZGMTR_DEPRECATED("The CurrentOverload attribute will be removed", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2)) = 0x00000702,
    ZGMTRAttributeIDTypeClusterElectricalMeasurementAttributeAcOverloadAlarmsMaskID ZGMTR_DEPRECATED("The AcOverloadAlarmsMask attribute will be removed", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2)) = 0x00000800,
    ZGMTRAttributeIDTypeClusterElectricalMeasurementAttributeAcVoltageOverloadID ZGMTR_DEPRECATED("The AcVoltageOverload attribute will be removed", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2)) = 0x00000801,
    ZGMTRAttributeIDTypeClusterElectricalMeasurementAttributeAcCurrentOverloadID ZGMTR_DEPRECATED("The AcCurrentOverload attribute will be removed", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2)) = 0x00000802,
    ZGMTRAttributeIDTypeClusterElectricalMeasurementAttributeAcActivePowerOverloadID ZGMTR_DEPRECATED("The AcActivePowerOverload attribute will be removed", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2)) = 0x00000803,
    ZGMTRAttributeIDTypeClusterElectricalMeasurementAttributeAcReactivePowerOverloadID ZGMTR_DEPRECATED("The AcReactivePowerOverload attribute will be removed", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2)) = 0x00000804,
    ZGMTRAttributeIDTypeClusterElectricalMeasurementAttributeAverageRmsOverVoltageID ZGMTR_DEPRECATED("The AverageRmsOverVoltage attribute will be removed", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2)) = 0x00000805,
    ZGMTRAttributeIDTypeClusterElectricalMeasurementAttributeAverageRmsUnderVoltageID ZGMTR_DEPRECATED("The AverageRmsUnderVoltage attribute will be removed", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2)) = 0x00000806,
    ZGMTRAttributeIDTypeClusterElectricalMeasurementAttributeRmsExtremeOverVoltageID ZGMTR_DEPRECATED("The RmsExtremeOverVoltage attribute will be removed", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2)) = 0x00000807,
    ZGMTRAttributeIDTypeClusterElectricalMeasurementAttributeRmsExtremeUnderVoltageID ZGMTR_DEPRECATED("The RmsExtremeUnderVoltage attribute will be removed", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2)) = 0x00000808,
    ZGMTRAttributeIDTypeClusterElectricalMeasurementAttributeRmsVoltageSagID ZGMTR_DEPRECATED("The RmsVoltageSag attribute will be removed", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2)) = 0x00000809,
    ZGMTRAttributeIDTypeClusterElectricalMeasurementAttributeRmsVoltageSwellID ZGMTR_DEPRECATED("The RmsVoltageSwell attribute will be removed", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2)) = 0x0000080A,
    ZGMTRAttributeIDTypeClusterElectricalMeasurementAttributeLineCurrentPhaseBID ZGMTR_DEPRECATED("The LineCurrentPhaseB attribute will be removed", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2)) = 0x00000901,
    ZGMTRAttributeIDTypeClusterElectricalMeasurementAttributeActiveCurrentPhaseBID ZGMTR_DEPRECATED("The ActiveCurrentPhaseB attribute will be removed", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2)) = 0x00000902,
    ZGMTRAttributeIDTypeClusterElectricalMeasurementAttributeReactiveCurrentPhaseBID ZGMTR_DEPRECATED("The ReactiveCurrentPhaseB attribute will be removed", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2)) = 0x00000903,
    ZGMTRAttributeIDTypeClusterElectricalMeasurementAttributeRmsVoltagePhaseBID ZGMTR_DEPRECATED("The RmsVoltagePhaseB attribute will be removed", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2)) = 0x00000905,
    ZGMTRAttributeIDTypeClusterElectricalMeasurementAttributeRmsVoltageMinPhaseBID ZGMTR_DEPRECATED("The RmsVoltageMinPhaseB attribute will be removed", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2)) = 0x00000906,
    ZGMTRAttributeIDTypeClusterElectricalMeasurementAttributeRmsVoltageMaxPhaseBID ZGMTR_DEPRECATED("The RmsVoltageMaxPhaseB attribute will be removed", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2)) = 0x00000907,
    ZGMTRAttributeIDTypeClusterElectricalMeasurementAttributeRmsCurrentPhaseBID ZGMTR_DEPRECATED("The RmsCurrentPhaseB attribute will be removed", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2)) = 0x00000908,
    ZGMTRAttributeIDTypeClusterElectricalMeasurementAttributeRmsCurrentMinPhaseBID ZGMTR_DEPRECATED("The RmsCurrentMinPhaseB attribute will be removed", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2)) = 0x00000909,
    ZGMTRAttributeIDTypeClusterElectricalMeasurementAttributeRmsCurrentMaxPhaseBID ZGMTR_DEPRECATED("The RmsCurrentMaxPhaseB attribute will be removed", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2)) = 0x0000090A,
    ZGMTRAttributeIDTypeClusterElectricalMeasurementAttributeActivePowerPhaseBID ZGMTR_DEPRECATED("The ActivePowerPhaseB attribute will be removed", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2)) = 0x0000090B,
    ZGMTRAttributeIDTypeClusterElectricalMeasurementAttributeActivePowerMinPhaseBID ZGMTR_DEPRECATED("The ActivePowerMinPhaseB attribute will be removed", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2)) = 0x0000090C,
    ZGMTRAttributeIDTypeClusterElectricalMeasurementAttributeActivePowerMaxPhaseBID ZGMTR_DEPRECATED("The ActivePowerMaxPhaseB attribute will be removed", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2)) = 0x0000090D,
    ZGMTRAttributeIDTypeClusterElectricalMeasurementAttributeReactivePowerPhaseBID ZGMTR_DEPRECATED("The ReactivePowerPhaseB attribute will be removed", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2)) = 0x0000090E,
    ZGMTRAttributeIDTypeClusterElectricalMeasurementAttributeApparentPowerPhaseBID ZGMTR_DEPRECATED("The ApparentPowerPhaseB attribute will be removed", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2)) = 0x0000090F,
    ZGMTRAttributeIDTypeClusterElectricalMeasurementAttributePowerFactorPhaseBID ZGMTR_DEPRECATED("The PowerFactorPhaseB attribute will be removed", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2)) = 0x00000910,
    ZGMTRAttributeIDTypeClusterElectricalMeasurementAttributeAverageRmsVoltageMeasurementPeriodPhaseBID ZGMTR_DEPRECATED("The AverageRmsVoltageMeasurementPeriodPhaseB attribute will be removed", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2)) = 0x00000911,
    ZGMTRAttributeIDTypeClusterElectricalMeasurementAttributeAverageRmsOverVoltageCounterPhaseBID ZGMTR_DEPRECATED("The AverageRmsOverVoltageCounterPhaseB attribute will be removed", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2)) = 0x00000912,
    ZGMTRAttributeIDTypeClusterElectricalMeasurementAttributeAverageRmsUnderVoltageCounterPhaseBID ZGMTR_DEPRECATED("The AverageRmsUnderVoltageCounterPhaseB attribute will be removed", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2)) = 0x00000913,
    ZGMTRAttributeIDTypeClusterElectricalMeasurementAttributeRmsExtremeOverVoltagePeriodPhaseBID ZGMTR_DEPRECATED("The RmsExtremeOverVoltagePeriodPhaseB attribute will be removed", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2)) = 0x00000914,
    ZGMTRAttributeIDTypeClusterElectricalMeasurementAttributeRmsExtremeUnderVoltagePeriodPhaseBID ZGMTR_DEPRECATED("The RmsExtremeUnderVoltagePeriodPhaseB attribute will be removed", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2)) = 0x00000915,
    ZGMTRAttributeIDTypeClusterElectricalMeasurementAttributeRmsVoltageSagPeriodPhaseBID ZGMTR_DEPRECATED("The RmsVoltageSagPeriodPhaseB attribute will be removed", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2)) = 0x00000916,
    ZGMTRAttributeIDTypeClusterElectricalMeasurementAttributeRmsVoltageSwellPeriodPhaseBID ZGMTR_DEPRECATED("The RmsVoltageSwellPeriodPhaseB attribute will be removed", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2)) = 0x00000917,
    ZGMTRAttributeIDTypeClusterElectricalMeasurementAttributeLineCurrentPhaseCID ZGMTR_DEPRECATED("The LineCurrentPhaseC attribute will be removed", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2)) = 0x00000A01,
    ZGMTRAttributeIDTypeClusterElectricalMeasurementAttributeActiveCurrentPhaseCID ZGMTR_DEPRECATED("The ActiveCurrentPhaseC attribute will be removed", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2)) = 0x00000A02,
    ZGMTRAttributeIDTypeClusterElectricalMeasurementAttributeReactiveCurrentPhaseCID ZGMTR_DEPRECATED("The ReactiveCurrentPhaseC attribute will be removed", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2)) = 0x00000A03,
    ZGMTRAttributeIDTypeClusterElectricalMeasurementAttributeRmsVoltagePhaseCID ZGMTR_DEPRECATED("The RmsVoltagePhaseC attribute will be removed", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2)) = 0x00000A05,
    ZGMTRAttributeIDTypeClusterElectricalMeasurementAttributeRmsVoltageMinPhaseCID ZGMTR_DEPRECATED("The RmsVoltageMinPhaseC attribute will be removed", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2)) = 0x00000A06,
    ZGMTRAttributeIDTypeClusterElectricalMeasurementAttributeRmsVoltageMaxPhaseCID ZGMTR_DEPRECATED("The RmsVoltageMaxPhaseC attribute will be removed", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2)) = 0x00000A07,
    ZGMTRAttributeIDTypeClusterElectricalMeasurementAttributeRmsCurrentPhaseCID ZGMTR_DEPRECATED("The RmsCurrentPhaseC attribute will be removed", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2)) = 0x00000A08,
    ZGMTRAttributeIDTypeClusterElectricalMeasurementAttributeRmsCurrentMinPhaseCID ZGMTR_DEPRECATED("The RmsCurrentMinPhaseC attribute will be removed", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2)) = 0x00000A09,
    ZGMTRAttributeIDTypeClusterElectricalMeasurementAttributeRmsCurrentMaxPhaseCID ZGMTR_DEPRECATED("The RmsCurrentMaxPhaseC attribute will be removed", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2)) = 0x00000A0A,
    ZGMTRAttributeIDTypeClusterElectricalMeasurementAttributeActivePowerPhaseCID ZGMTR_DEPRECATED("The ActivePowerPhaseC attribute will be removed", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2)) = 0x00000A0B,
    ZGMTRAttributeIDTypeClusterElectricalMeasurementAttributeActivePowerMinPhaseCID ZGMTR_DEPRECATED("The ActivePowerMinPhaseC attribute will be removed", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2)) = 0x00000A0C,
    ZGMTRAttributeIDTypeClusterElectricalMeasurementAttributeActivePowerMaxPhaseCID ZGMTR_DEPRECATED("The ActivePowerMaxPhaseC attribute will be removed", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2)) = 0x00000A0D,
    ZGMTRAttributeIDTypeClusterElectricalMeasurementAttributeReactivePowerPhaseCID ZGMTR_DEPRECATED("The ReactivePowerPhaseC attribute will be removed", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2)) = 0x00000A0E,
    ZGMTRAttributeIDTypeClusterElectricalMeasurementAttributeApparentPowerPhaseCID ZGMTR_DEPRECATED("The ApparentPowerPhaseC attribute will be removed", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2)) = 0x00000A0F,
    ZGMTRAttributeIDTypeClusterElectricalMeasurementAttributePowerFactorPhaseCID ZGMTR_DEPRECATED("The PowerFactorPhaseC attribute will be removed", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2)) = 0x00000A10,
    ZGMTRAttributeIDTypeClusterElectricalMeasurementAttributeAverageRmsVoltageMeasurementPeriodPhaseCID ZGMTR_DEPRECATED("The AverageRmsVoltageMeasurementPeriodPhaseC attribute will be removed", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2)) = 0x00000A11,
    ZGMTRAttributeIDTypeClusterElectricalMeasurementAttributeAverageRmsOverVoltageCounterPhaseCID ZGMTR_DEPRECATED("The AverageRmsOverVoltageCounterPhaseC attribute will be removed", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2)) = 0x00000A12,
    ZGMTRAttributeIDTypeClusterElectricalMeasurementAttributeAverageRmsUnderVoltageCounterPhaseCID ZGMTR_DEPRECATED("The AverageRmsUnderVoltageCounterPhaseC attribute will be removed", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2)) = 0x00000A13,
    ZGMTRAttributeIDTypeClusterElectricalMeasurementAttributeRmsExtremeOverVoltagePeriodPhaseCID ZGMTR_DEPRECATED("The RmsExtremeOverVoltagePeriodPhaseC attribute will be removed", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2)) = 0x00000A14,
    ZGMTRAttributeIDTypeClusterElectricalMeasurementAttributeRmsExtremeUnderVoltagePeriodPhaseCID ZGMTR_DEPRECATED("The RmsExtremeUnderVoltagePeriodPhaseC attribute will be removed", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2)) = 0x00000A15,
    ZGMTRAttributeIDTypeClusterElectricalMeasurementAttributeRmsVoltageSagPeriodPhaseCID ZGMTR_DEPRECATED("The RmsVoltageSagPeriodPhaseC attribute will be removed", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2)) = 0x00000A16,
    ZGMTRAttributeIDTypeClusterElectricalMeasurementAttributeRmsVoltageSwellPeriodPhaseCID ZGMTR_DEPRECATED("The RmsVoltageSwellPeriodPhaseC attribute will be removed", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2)) = 0x00000A17,
    ZGMTRAttributeIDTypeClusterElectricalMeasurementAttributeGeneratedCommandListID ZGMTR_DEPRECATED("The GeneratedCommandList attribute will be removed", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2)) = ZGMTRAttributeIDTypeGlobalAttributeGeneratedCommandListID,
    ZGMTRAttributeIDTypeClusterElectricalMeasurementAttributeAcceptedCommandListID ZGMTR_DEPRECATED("The AcceptedCommandList attribute will be removed", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2)) = ZGMTRAttributeIDTypeGlobalAttributeAcceptedCommandListID,
    ZGMTRAttributeIDTypeClusterElectricalMeasurementAttributeAttributeListID ZGMTR_DEPRECATED("The AttributeList attribute will be removed", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2)) = ZGMTRAttributeIDTypeGlobalAttributeAttributeListID,
    ZGMTRAttributeIDTypeClusterElectricalMeasurementAttributeFeatureMapID ZGMTR_DEPRECATED("The FeatureMap attribute will be removed", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2)) = ZGMTRAttributeIDTypeGlobalAttributeFeatureMapID,
    ZGMTRAttributeIDTypeClusterElectricalMeasurementAttributeClusterRevisionID ZGMTR_DEPRECATED("The ClusterRevision attribute will be removed", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2)) = ZGMTRAttributeIDTypeGlobalAttributeClusterRevisionID,

    // Cluster OnOffSwitchConfiguration deprecated attribute names
    ZGMTRClusterOnOffSwitchConfigurationAttributeSwitchTypeID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterOnOffSwitchConfigurationAttributeSwitchTypeID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x00000000,
    ZGMTRClusterOnOffSwitchConfigurationAttributeSwitchActionsID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterOnOffSwitchConfigurationAttributeSwitchActionsID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x00000010,
    ZGMTRClusterOnOffSwitchConfigurationAttributeGeneratedCommandListID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterOnOffSwitchConfigurationAttributeGeneratedCommandListID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = ZGMTRClusterGlobalAttributeGeneratedCommandListID,
    ZGMTRClusterOnOffSwitchConfigurationAttributeAcceptedCommandListID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterOnOffSwitchConfigurationAttributeAcceptedCommandListID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = ZGMTRClusterGlobalAttributeAcceptedCommandListID,
    ZGMTRClusterOnOffSwitchConfigurationAttributeAttributeListID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterOnOffSwitchConfigurationAttributeAttributeListID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = ZGMTRClusterGlobalAttributeAttributeListID,
    ZGMTRClusterOnOffSwitchConfigurationAttributeFeatureMapID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterOnOffSwitchConfigurationAttributeFeatureMapID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = ZGMTRClusterGlobalAttributeFeatureMapID,
    ZGMTRClusterOnOffSwitchConfigurationAttributeClusterRevisionID
        ZGMTR_DEPRECATED("Please use ZGMTRAttributeIDTypeClusterOnOffSwitchConfigurationAttributeClusterRevisionID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = ZGMTRClusterGlobalAttributeClusterRevisionID,

    // Cluster OnOffSwitchConfiguration attributes
    ZGMTRAttributeIDTypeClusterOnOffSwitchConfigurationAttributeSwitchTypeID ZGMTR_DEPRECATED("The SwitchType attribute will be removed", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2)) = 0x00000000,
    ZGMTRAttributeIDTypeClusterOnOffSwitchConfigurationAttributeSwitchActionsID ZGMTR_DEPRECATED("The SwitchActions attribute will be removed", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2)) = 0x00000010,
    ZGMTRAttributeIDTypeClusterOnOffSwitchConfigurationAttributeGeneratedCommandListID ZGMTR_DEPRECATED("The GeneratedCommandList attribute will be removed", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2)) = ZGMTRAttributeIDTypeGlobalAttributeGeneratedCommandListID,
    ZGMTRAttributeIDTypeClusterOnOffSwitchConfigurationAttributeAcceptedCommandListID ZGMTR_DEPRECATED("The AcceptedCommandList attribute will be removed", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2)) = ZGMTRAttributeIDTypeGlobalAttributeAcceptedCommandListID,
    ZGMTRAttributeIDTypeClusterOnOffSwitchConfigurationAttributeAttributeListID ZGMTR_DEPRECATED("The AttributeList attribute will be removed", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2)) = ZGMTRAttributeIDTypeGlobalAttributeAttributeListID,
    ZGMTRAttributeIDTypeClusterOnOffSwitchConfigurationAttributeFeatureMapID ZGMTR_DEPRECATED("The FeatureMap attribute will be removed", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2)) = ZGMTRAttributeIDTypeGlobalAttributeFeatureMapID,
    ZGMTRAttributeIDTypeClusterOnOffSwitchConfigurationAttributeClusterRevisionID ZGMTR_DEPRECATED("The ClusterRevision attribute will be removed", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2)) = ZGMTRAttributeIDTypeGlobalAttributeClusterRevisionID,
};

#pragma mark - Commands IDs

typedef NS_ENUM(uint32_t, ZGMTRCommandIDType) {

    // Cluster Identify deprecated command id names
    ZGMTRClusterIdentifyCommandIdentifyID
        ZGMTR_DEPRECATED("Please use ZGMTRCommandIDTypeClusterIdentifyCommandIdentifyID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x00000000,
    ZGMTRClusterIdentifyCommandTriggerEffectID
        ZGMTR_DEPRECATED("Please use ZGMTRCommandIDTypeClusterIdentifyCommandTriggerEffectID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x00000040,

    // Cluster Identify commands
    ZGMTRCommandIDTypeClusterIdentifyCommandIdentifyID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000000,
    ZGMTRCommandIDTypeClusterIdentifyCommandTriggerEffectID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000040,

    // Cluster Groups deprecated command id names
    ZGMTRClusterGroupsCommandAddGroupID
        ZGMTR_DEPRECATED("Please use ZGMTRCommandIDTypeClusterGroupsCommandAddGroupID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x00000000,
    ZGMTRClusterGroupsCommandAddGroupResponseID
        ZGMTR_DEPRECATED("Please use ZGMTRCommandIDTypeClusterGroupsCommandAddGroupResponseID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x00000000,
    ZGMTRClusterGroupsCommandViewGroupID
        ZGMTR_DEPRECATED("Please use ZGMTRCommandIDTypeClusterGroupsCommandViewGroupID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x00000001,
    ZGMTRClusterGroupsCommandViewGroupResponseID
        ZGMTR_DEPRECATED("Please use ZGMTRCommandIDTypeClusterGroupsCommandViewGroupResponseID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x00000001,
    ZGMTRClusterGroupsCommandGetGroupMembershipID
        ZGMTR_DEPRECATED("Please use ZGMTRCommandIDTypeClusterGroupsCommandGetGroupMembershipID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x00000002,
    ZGMTRClusterGroupsCommandGetGroupMembershipResponseID
        ZGMTR_DEPRECATED("Please use ZGMTRCommandIDTypeClusterGroupsCommandGetGroupMembershipResponseID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x00000002,
    ZGMTRClusterGroupsCommandRemoveGroupID
        ZGMTR_DEPRECATED("Please use ZGMTRCommandIDTypeClusterGroupsCommandRemoveGroupID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x00000003,
    ZGMTRClusterGroupsCommandRemoveGroupResponseID
        ZGMTR_DEPRECATED("Please use ZGMTRCommandIDTypeClusterGroupsCommandRemoveGroupResponseID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x00000003,
    ZGMTRClusterGroupsCommandRemoveAllGroupsID
        ZGMTR_DEPRECATED("Please use ZGMTRCommandIDTypeClusterGroupsCommandRemoveAllGroupsID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x00000004,
    ZGMTRClusterGroupsCommandAddGroupIfIdentifyingID
        ZGMTR_DEPRECATED("Please use ZGMTRCommandIDTypeClusterGroupsCommandAddGroupIfIdentifyingID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x00000005,

    // Cluster Groups commands
    ZGMTRCommandIDTypeClusterGroupsCommandAddGroupID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000000,
    ZGMTRCommandIDTypeClusterGroupsCommandAddGroupResponseID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000000,
    ZGMTRCommandIDTypeClusterGroupsCommandViewGroupID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000001,
    ZGMTRCommandIDTypeClusterGroupsCommandViewGroupResponseID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000001,
    ZGMTRCommandIDTypeClusterGroupsCommandGetGroupMembershipID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000002,
    ZGMTRCommandIDTypeClusterGroupsCommandGetGroupMembershipResponseID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000002,
    ZGMTRCommandIDTypeClusterGroupsCommandRemoveGroupID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000003,
    ZGMTRCommandIDTypeClusterGroupsCommandRemoveGroupResponseID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000003,
    ZGMTRCommandIDTypeClusterGroupsCommandRemoveAllGroupsID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000004,
    ZGMTRCommandIDTypeClusterGroupsCommandAddGroupIfIdentifyingID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000005,

    // Cluster OnOff deprecated command id names
    ZGMTRClusterOnOffCommandOffID
        ZGMTR_DEPRECATED("Please use ZGMTRCommandIDTypeClusterOnOffCommandOffID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x00000000,
    ZGMTRClusterOnOffCommandOnID
        ZGMTR_DEPRECATED("Please use ZGMTRCommandIDTypeClusterOnOffCommandOnID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x00000001,
    ZGMTRClusterOnOffCommandToggleID
        ZGMTR_DEPRECATED("Please use ZGMTRCommandIDTypeClusterOnOffCommandToggleID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x00000002,
    ZGMTRClusterOnOffCommandOffWithEffectID
        ZGMTR_DEPRECATED("Please use ZGMTRCommandIDTypeClusterOnOffCommandOffWithEffectID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x00000040,
    ZGMTRClusterOnOffCommandOnWithRecallGlobalSceneID
        ZGMTR_DEPRECATED("Please use ZGMTRCommandIDTypeClusterOnOffCommandOnWithRecallGlobalSceneID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x00000041,
    ZGMTRClusterOnOffCommandOnWithTimedOffID
        ZGMTR_DEPRECATED("Please use ZGMTRCommandIDTypeClusterOnOffCommandOnWithTimedOffID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x00000042,

    // Cluster OnOff commands
    ZGMTRCommandIDTypeClusterOnOffCommandOffID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000000,
    ZGMTRCommandIDTypeClusterOnOffCommandOnID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000001,
    ZGMTRCommandIDTypeClusterOnOffCommandToggleID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000002,
    ZGMTRCommandIDTypeClusterOnOffCommandOffWithEffectID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000040,
    ZGMTRCommandIDTypeClusterOnOffCommandOnWithRecallGlobalSceneID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000041,
    ZGMTRCommandIDTypeClusterOnOffCommandOnWithTimedOffID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000042,

    // Cluster LevelControl deprecated command id names
    ZGMTRClusterLevelControlCommandMoveToLevelID
        ZGMTR_DEPRECATED("Please use ZGMTRCommandIDTypeClusterLevelControlCommandMoveToLevelID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x00000000,
    ZGMTRClusterLevelControlCommandMoveID
        ZGMTR_DEPRECATED("Please use ZGMTRCommandIDTypeClusterLevelControlCommandMoveID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x00000001,
    ZGMTRClusterLevelControlCommandStepID
        ZGMTR_DEPRECATED("Please use ZGMTRCommandIDTypeClusterLevelControlCommandStepID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x00000002,
    ZGMTRClusterLevelControlCommandStopID
        ZGMTR_DEPRECATED("Please use ZGMTRCommandIDTypeClusterLevelControlCommandStopID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x00000003,
    ZGMTRClusterLevelControlCommandMoveToLevelWithOnOffID
        ZGMTR_DEPRECATED("Please use ZGMTRCommandIDTypeClusterLevelControlCommandMoveToLevelWithOnOffID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x00000004,
    ZGMTRClusterLevelControlCommandMoveWithOnOffID
        ZGMTR_DEPRECATED("Please use ZGMTRCommandIDTypeClusterLevelControlCommandMoveWithOnOffID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x00000005,
    ZGMTRClusterLevelControlCommandStepWithOnOffID
        ZGMTR_DEPRECATED("Please use ZGMTRCommandIDTypeClusterLevelControlCommandStepWithOnOffID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x00000006,
    ZGMTRClusterLevelControlCommandStopWithOnOffID
        ZGMTR_DEPRECATED("Please use ZGMTRCommandIDTypeClusterLevelControlCommandStopWithOnOffID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x00000007,
    ZGMTRClusterLevelControlCommandMoveToClosestFrequencyID
        ZGMTR_DEPRECATED("Please use ZGMTRCommandIDTypeClusterLevelControlCommandMoveToClosestFrequencyID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x00000008,

    // Cluster LevelControl commands
    ZGMTRCommandIDTypeClusterLevelControlCommandMoveToLevelID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000000,
    ZGMTRCommandIDTypeClusterLevelControlCommandMoveID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000001,
    ZGMTRCommandIDTypeClusterLevelControlCommandStepID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000002,
    ZGMTRCommandIDTypeClusterLevelControlCommandStopID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000003,
    ZGMTRCommandIDTypeClusterLevelControlCommandMoveToLevelWithOnOffID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000004,
    ZGMTRCommandIDTypeClusterLevelControlCommandMoveWithOnOffID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000005,
    ZGMTRCommandIDTypeClusterLevelControlCommandStepWithOnOffID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000006,
    ZGMTRCommandIDTypeClusterLevelControlCommandStopWithOnOffID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000007,
    ZGMTRCommandIDTypeClusterLevelControlCommandMoveToClosestFrequencyID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000008,

    // Cluster AccessControl deprecated command id names

    // Cluster AccessControl commands
    ZGMTRCommandIDTypeClusterAccessControlCommandReviewFabricRestrictionsID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = 0x00000000,
    ZGMTRCommandIDTypeClusterAccessControlCommandReviewFabricRestrictionsResponseID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = 0x00000001,

    // Cluster Actions deprecated command id names
    ZGMTRClusterActionsCommandInstantActionID
        ZGMTR_DEPRECATED("Please use ZGMTRCommandIDTypeClusterActionsCommandInstantActionID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x00000000,
    ZGMTRClusterActionsCommandInstantActionWithTransitionID
        ZGMTR_DEPRECATED("Please use ZGMTRCommandIDTypeClusterActionsCommandInstantActionWithTransitionID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x00000001,
    ZGMTRClusterActionsCommandStartActionID
        ZGMTR_DEPRECATED("Please use ZGMTRCommandIDTypeClusterActionsCommandStartActionID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x00000002,
    ZGMTRClusterActionsCommandStartActionWithDurationID
        ZGMTR_DEPRECATED("Please use ZGMTRCommandIDTypeClusterActionsCommandStartActionWithDurationID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x00000003,
    ZGMTRClusterActionsCommandStopActionID
        ZGMTR_DEPRECATED("Please use ZGMTRCommandIDTypeClusterActionsCommandStopActionID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x00000004,
    ZGMTRClusterActionsCommandPauseActionID
        ZGMTR_DEPRECATED("Please use ZGMTRCommandIDTypeClusterActionsCommandPauseActionID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x00000005,
    ZGMTRClusterActionsCommandPauseActionWithDurationID
        ZGMTR_DEPRECATED("Please use ZGMTRCommandIDTypeClusterActionsCommandPauseActionWithDurationID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x00000006,
    ZGMTRClusterActionsCommandResumeActionID
        ZGMTR_DEPRECATED("Please use ZGMTRCommandIDTypeClusterActionsCommandResumeActionID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x00000007,
    ZGMTRClusterActionsCommandEnableActionID
        ZGMTR_DEPRECATED("Please use ZGMTRCommandIDTypeClusterActionsCommandEnableActionID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x00000008,
    ZGMTRClusterActionsCommandEnableActionWithDurationID
        ZGMTR_DEPRECATED("Please use ZGMTRCommandIDTypeClusterActionsCommandEnableActionWithDurationID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x00000009,
    ZGMTRClusterActionsCommandDisableActionID
        ZGMTR_DEPRECATED("Please use ZGMTRCommandIDTypeClusterActionsCommandDisableActionID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x0000000A,
    ZGMTRClusterActionsCommandDisableActionWithDurationID
        ZGMTR_DEPRECATED("Please use ZGMTRCommandIDTypeClusterActionsCommandDisableActionWithDurationID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x0000000B,

    // Cluster Actions commands
    ZGMTRCommandIDTypeClusterActionsCommandInstantActionID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000000,
    ZGMTRCommandIDTypeClusterActionsCommandInstantActionWithTransitionID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000001,
    ZGMTRCommandIDTypeClusterActionsCommandStartActionID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000002,
    ZGMTRCommandIDTypeClusterActionsCommandStartActionWithDurationID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000003,
    ZGMTRCommandIDTypeClusterActionsCommandStopActionID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000004,
    ZGMTRCommandIDTypeClusterActionsCommandPauseActionID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000005,
    ZGMTRCommandIDTypeClusterActionsCommandPauseActionWithDurationID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000006,
    ZGMTRCommandIDTypeClusterActionsCommandResumeActionID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000007,
    ZGMTRCommandIDTypeClusterActionsCommandEnableActionID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000008,
    ZGMTRCommandIDTypeClusterActionsCommandEnableActionWithDurationID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000009,
    ZGMTRCommandIDTypeClusterActionsCommandDisableActionID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x0000000A,
    ZGMTRCommandIDTypeClusterActionsCommandDisableActionWithDurationID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x0000000B,

    // Cluster Basic deprecated command id names
    ZGMTRClusterBasicCommandMfgSpecificPingID
        ZGMTR_DEPRECATED("Please use ZGMTRCommandIDTypeClusterBasicInformationCommandMfgSpecificPingID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x10020000,

    // Cluster BasicInformation commands

    // Cluster OtaSoftwareUpdateProvider deprecated command id names
    ZGMTRClusterOtaSoftwareUpdateProviderCommandQueryImageID
        ZGMTR_DEPRECATED("Please use ZGMTRCommandIDTypeClusterOTASoftwareUpdateProviderCommandQueryImageID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x00000000,
    ZGMTRClusterOtaSoftwareUpdateProviderCommandQueryImageResponseID
        ZGMTR_DEPRECATED("Please use ZGMTRCommandIDTypeClusterOTASoftwareUpdateProviderCommandQueryImageResponseID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x00000001,
    ZGMTRClusterOtaSoftwareUpdateProviderCommandApplyUpdateRequestID
        ZGMTR_DEPRECATED("Please use ZGMTRCommandIDTypeClusterOTASoftwareUpdateProviderCommandApplyUpdateRequestID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x00000002,
    ZGMTRClusterOtaSoftwareUpdateProviderCommandApplyUpdateResponseID
        ZGMTR_DEPRECATED("Please use ZGMTRCommandIDTypeClusterOTASoftwareUpdateProviderCommandApplyUpdateResponseID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x00000003,
    ZGMTRClusterOtaSoftwareUpdateProviderCommandNotifyUpdateAppliedID
        ZGMTR_DEPRECATED("Please use ZGMTRCommandIDTypeClusterOTASoftwareUpdateProviderCommandNotifyUpdateAppliedID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x00000004,

    // Cluster OTASoftwareUpdateProvider commands
    ZGMTRCommandIDTypeClusterOTASoftwareUpdateProviderCommandQueryImageID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000000,
    ZGMTRCommandIDTypeClusterOTASoftwareUpdateProviderCommandQueryImageResponseID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000001,
    ZGMTRCommandIDTypeClusterOTASoftwareUpdateProviderCommandApplyUpdateRequestID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000002,
    ZGMTRCommandIDTypeClusterOTASoftwareUpdateProviderCommandApplyUpdateResponseID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000003,
    ZGMTRCommandIDTypeClusterOTASoftwareUpdateProviderCommandNotifyUpdateAppliedID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000004,

    // Cluster OtaSoftwareUpdateRequestor deprecated command id names
    ZGMTRClusterOtaSoftwareUpdateRequestorCommandAnnounceOtaProviderID
        ZGMTR_DEPRECATED("Please use ZGMTRCommandIDTypeClusterOTASoftwareUpdateRequestorCommandAnnounceOTAProviderID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x00000000,

    // Cluster OTASoftwareUpdateRequestor commands
    ZGMTRCommandIDTypeClusterOTASoftwareUpdateRequestorCommandAnnounceOTAProviderID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000000,

    // Cluster GeneralCommissioning deprecated command id names
    ZGMTRClusterGeneralCommissioningCommandArmFailSafeID
        ZGMTR_DEPRECATED("Please use ZGMTRCommandIDTypeClusterGeneralCommissioningCommandArmFailSafeID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x00000000,
    ZGMTRClusterGeneralCommissioningCommandArmFailSafeResponseID
        ZGMTR_DEPRECATED("Please use ZGMTRCommandIDTypeClusterGeneralCommissioningCommandArmFailSafeResponseID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x00000001,
    ZGMTRClusterGeneralCommissioningCommandSetRegulatoryConfigID
        ZGMTR_DEPRECATED("Please use ZGMTRCommandIDTypeClusterGeneralCommissioningCommandSetRegulatoryConfigID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x00000002,
    ZGMTRClusterGeneralCommissioningCommandSetRegulatoryConfigResponseID
        ZGMTR_DEPRECATED("Please use ZGMTRCommandIDTypeClusterGeneralCommissioningCommandSetRegulatoryConfigResponseID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x00000003,
    ZGMTRClusterGeneralCommissioningCommandCommissioningCompleteID
        ZGMTR_DEPRECATED("Please use ZGMTRCommandIDTypeClusterGeneralCommissioningCommandCommissioningCompleteID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x00000004,
    ZGMTRClusterGeneralCommissioningCommandCommissioningCompleteResponseID
        ZGMTR_DEPRECATED("Please use ZGMTRCommandIDTypeClusterGeneralCommissioningCommandCommissioningCompleteResponseID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x00000005,

    // Cluster GeneralCommissioning commands
    ZGMTRCommandIDTypeClusterGeneralCommissioningCommandArmFailSafeID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000000,
    ZGMTRCommandIDTypeClusterGeneralCommissioningCommandArmFailSafeResponseID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000001,
    ZGMTRCommandIDTypeClusterGeneralCommissioningCommandSetRegulatoryConfigID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000002,
    ZGMTRCommandIDTypeClusterGeneralCommissioningCommandSetRegulatoryConfigResponseID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000003,
    ZGMTRCommandIDTypeClusterGeneralCommissioningCommandCommissioningCompleteID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000004,
    ZGMTRCommandIDTypeClusterGeneralCommissioningCommandCommissioningCompleteResponseID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000005,
    ZGMTRCommandIDTypeClusterGeneralCommissioningCommandSetTCAcknowledgementsID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000006,
    ZGMTRCommandIDTypeClusterGeneralCommissioningCommandSetTCAcknowledgementsResponseID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000007,

    // Cluster NetworkCommissioning deprecated command id names
    ZGMTRClusterNetworkCommissioningCommandScanNetworksID
        ZGMTR_DEPRECATED("Please use ZGMTRCommandIDTypeClusterNetworkCommissioningCommandScanNetworksID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x00000000,
    ZGMTRClusterNetworkCommissioningCommandScanNetworksResponseID
        ZGMTR_DEPRECATED("Please use ZGMTRCommandIDTypeClusterNetworkCommissioningCommandScanNetworksResponseID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x00000001,
    ZGMTRClusterNetworkCommissioningCommandAddOrUpdateWiFiNetworkID
        ZGMTR_DEPRECATED("Please use ZGMTRCommandIDTypeClusterNetworkCommissioningCommandAddOrUpdateWiFiNetworkID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x00000002,
    ZGMTRClusterNetworkCommissioningCommandAddOrUpdateThreadNetworkID
        ZGMTR_DEPRECATED("Please use ZGMTRCommandIDTypeClusterNetworkCommissioningCommandAddOrUpdateThreadNetworkID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x00000003,
    ZGMTRClusterNetworkCommissioningCommandRemoveNetworkID
        ZGMTR_DEPRECATED("Please use ZGMTRCommandIDTypeClusterNetworkCommissioningCommandRemoveNetworkID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x00000004,
    ZGMTRClusterNetworkCommissioningCommandNetworkConfigResponseID
        ZGMTR_DEPRECATED("Please use ZGMTRCommandIDTypeClusterNetworkCommissioningCommandNetworkConfigResponseID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x00000005,
    ZGMTRClusterNetworkCommissioningCommandConnectNetworkID
        ZGMTR_DEPRECATED("Please use ZGMTRCommandIDTypeClusterNetworkCommissioningCommandConnectNetworkID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x00000006,
    ZGMTRClusterNetworkCommissioningCommandConnectNetworkResponseID
        ZGMTR_DEPRECATED("Please use ZGMTRCommandIDTypeClusterNetworkCommissioningCommandConnectNetworkResponseID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x00000007,
    ZGMTRClusterNetworkCommissioningCommandReorderNetworkID
        ZGMTR_DEPRECATED("Please use ZGMTRCommandIDTypeClusterNetworkCommissioningCommandReorderNetworkID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x00000008,

    // Cluster NetworkCommissioning commands
    ZGMTRCommandIDTypeClusterNetworkCommissioningCommandScanNetworksID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000000,
    ZGMTRCommandIDTypeClusterNetworkCommissioningCommandScanNetworksResponseID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000001,
    ZGMTRCommandIDTypeClusterNetworkCommissioningCommandAddOrUpdateWiFiNetworkID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000002,
    ZGMTRCommandIDTypeClusterNetworkCommissioningCommandAddOrUpdateThreadNetworkID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000003,
    ZGMTRCommandIDTypeClusterNetworkCommissioningCommandRemoveNetworkID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000004,
    ZGMTRCommandIDTypeClusterNetworkCommissioningCommandNetworkConfigResponseID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000005,
    ZGMTRCommandIDTypeClusterNetworkCommissioningCommandConnectNetworkID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000006,
    ZGMTRCommandIDTypeClusterNetworkCommissioningCommandConnectNetworkResponseID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000007,
    ZGMTRCommandIDTypeClusterNetworkCommissioningCommandReorderNetworkID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000008,
    ZGMTRCommandIDTypeClusterNetworkCommissioningCommandQueryIdentityID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000009,
    ZGMTRCommandIDTypeClusterNetworkCommissioningCommandQueryIdentityResponseID ZGMTR_PROVISIONALLY_AVAILABLE = 0x0000000A,

    // Cluster DiagnosticLogs deprecated command id names
    ZGMTRClusterDiagnosticLogsCommandRetrieveLogsRequestID
        ZGMTR_DEPRECATED("Please use ZGMTRCommandIDTypeClusterDiagnosticLogsCommandRetrieveLogsRequestID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x00000000,
    ZGMTRClusterDiagnosticLogsCommandRetrieveLogsResponseID
        ZGMTR_DEPRECATED("Please use ZGMTRCommandIDTypeClusterDiagnosticLogsCommandRetrieveLogsResponseID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x00000001,

    // Cluster DiagnosticLogs commands
    ZGMTRCommandIDTypeClusterDiagnosticLogsCommandRetrieveLogsRequestID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000000,
    ZGMTRCommandIDTypeClusterDiagnosticLogsCommandRetrieveLogsResponseID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000001,

    // Cluster GeneralDiagnostics deprecated command id names
    ZGMTRClusterGeneralDiagnosticsCommandTestEventTriggerID
        ZGMTR_DEPRECATED("Please use ZGMTRCommandIDTypeClusterGeneralDiagnosticsCommandTestEventTriggerID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x00000000,

    // Cluster GeneralDiagnostics commands
    ZGMTRCommandIDTypeClusterGeneralDiagnosticsCommandTestEventTriggerID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000000,
    ZGMTRCommandIDTypeClusterGeneralDiagnosticsCommandTimeSnapshotID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = 0x00000001,
    ZGMTRCommandIDTypeClusterGeneralDiagnosticsCommandTimeSnapshotResponseID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = 0x00000002,
    ZGMTRCommandIDTypeClusterGeneralDiagnosticsCommandPayloadTestRequestID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = 0x00000003,
    ZGMTRCommandIDTypeClusterGeneralDiagnosticsCommandPayloadTestResponseID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = 0x00000004,

    // Cluster SoftwareDiagnostics deprecated command id names
    ZGMTRClusterSoftwareDiagnosticsCommandResetWatermarksID
        ZGMTR_DEPRECATED("Please use ZGMTRCommandIDTypeClusterSoftwareDiagnosticsCommandResetWatermarksID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x00000000,

    // Cluster SoftwareDiagnostics commands
    ZGMTRCommandIDTypeClusterSoftwareDiagnosticsCommandResetWatermarksID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000000,

    // Cluster ThreadNetworkDiagnostics deprecated command id names
    ZGMTRClusterThreadNetworkDiagnosticsCommandResetCountsID
        ZGMTR_DEPRECATED("Please use ZGMTRCommandIDTypeClusterThreadNetworkDiagnosticsCommandResetCountsID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x00000000,

    // Cluster ThreadNetworkDiagnostics commands
    ZGMTRCommandIDTypeClusterThreadNetworkDiagnosticsCommandResetCountsID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000000,

    // Cluster WiFiNetworkDiagnostics deprecated command id names
    ZGMTRClusterWiFiNetworkDiagnosticsCommandResetCountsID
        ZGMTR_DEPRECATED("Please use ZGMTRCommandIDTypeClusterWiFiNetworkDiagnosticsCommandResetCountsID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x00000000,

    // Cluster WiFiNetworkDiagnostics commands
    ZGMTRCommandIDTypeClusterWiFiNetworkDiagnosticsCommandResetCountsID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000000,

    // Cluster EthernetNetworkDiagnostics deprecated command id names
    ZGMTRClusterEthernetNetworkDiagnosticsCommandResetCountsID
        ZGMTR_DEPRECATED("Please use ZGMTRCommandIDTypeClusterEthernetNetworkDiagnosticsCommandResetCountsID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x00000000,

    // Cluster EthernetNetworkDiagnostics commands
    ZGMTRCommandIDTypeClusterEthernetNetworkDiagnosticsCommandResetCountsID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000000,

    // Cluster TimeSynchronization deprecated command id names
    ZGMTRClusterTimeSynchronizationCommandSetUtcTimeID
        ZGMTR_DEPRECATED("Please use ZGMTRCommandIDTypeClusterTimeSynchronizationCommandSetUTCTimeID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x00000000,

    // Cluster TimeSynchronization commands
    ZGMTRCommandIDTypeClusterTimeSynchronizationCommandSetUTCTimeID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = 0x00000000,
    ZGMTRCommandIDTypeClusterTimeSynchronizationCommandSetUtcTimeID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000000,
    ZGMTRCommandIDTypeClusterTimeSynchronizationCommandSetTrustedTimeSourceID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = 0x00000001,
    ZGMTRCommandIDTypeClusterTimeSynchronizationCommandSetTimeZoneID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = 0x00000002,
    ZGMTRCommandIDTypeClusterTimeSynchronizationCommandSetTimeZoneResponseID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = 0x00000003,
    ZGMTRCommandIDTypeClusterTimeSynchronizationCommandSetDSTOffsetID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = 0x00000004,
    ZGMTRCommandIDTypeClusterTimeSynchronizationCommandSetDefaultNTPID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = 0x00000005,

    // Cluster BridgedDeviceBasic deprecated command id names

    // Cluster BridgedDeviceBasicInformation commands
    ZGMTRCommandIDTypeClusterBridgedDeviceBasicInformationCommandKeepActiveID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = 0x00000080,

    // Cluster AdministratorCommissioning deprecated command id names
    ZGMTRClusterAdministratorCommissioningCommandOpenCommissioningWindowID
        ZGMTR_DEPRECATED("Please use ZGMTRCommandIDTypeClusterAdministratorCommissioningCommandOpenCommissioningWindowID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x00000000,
    ZGMTRClusterAdministratorCommissioningCommandOpenBasicCommissioningWindowID
        ZGMTR_DEPRECATED("Please use ZGMTRCommandIDTypeClusterAdministratorCommissioningCommandOpenBasicCommissioningWindowID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x00000001,
    ZGMTRClusterAdministratorCommissioningCommandRevokeCommissioningID
        ZGMTR_DEPRECATED("Please use ZGMTRCommandIDTypeClusterAdministratorCommissioningCommandRevokeCommissioningID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x00000002,

    // Cluster AdministratorCommissioning commands
    ZGMTRCommandIDTypeClusterAdministratorCommissioningCommandOpenCommissioningWindowID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000000,
    ZGMTRCommandIDTypeClusterAdministratorCommissioningCommandOpenBasicCommissioningWindowID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000001,
    ZGMTRCommandIDTypeClusterAdministratorCommissioningCommandRevokeCommissioningID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000002,

    // Cluster OperationalCredentials deprecated command id names
    ZGMTRClusterOperationalCredentialsCommandAttestationRequestID
        ZGMTR_DEPRECATED("Please use ZGMTRCommandIDTypeClusterOperationalCredentialsCommandAttestationRequestID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x00000000,
    ZGMTRClusterOperationalCredentialsCommandAttestationResponseID
        ZGMTR_DEPRECATED("Please use ZGMTRCommandIDTypeClusterOperationalCredentialsCommandAttestationResponseID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x00000001,
    ZGMTRClusterOperationalCredentialsCommandCertificateChainRequestID
        ZGMTR_DEPRECATED("Please use ZGMTRCommandIDTypeClusterOperationalCredentialsCommandCertificateChainRequestID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x00000002,
    ZGMTRClusterOperationalCredentialsCommandCertificateChainResponseID
        ZGMTR_DEPRECATED("Please use ZGMTRCommandIDTypeClusterOperationalCredentialsCommandCertificateChainResponseID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x00000003,
    ZGMTRClusterOperationalCredentialsCommandCSRRequestID
        ZGMTR_DEPRECATED("Please use ZGMTRCommandIDTypeClusterOperationalCredentialsCommandCSRRequestID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x00000004,
    ZGMTRClusterOperationalCredentialsCommandCSRResponseID
        ZGMTR_DEPRECATED("Please use ZGMTRCommandIDTypeClusterOperationalCredentialsCommandCSRResponseID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x00000005,
    ZGMTRClusterOperationalCredentialsCommandAddNOCID
        ZGMTR_DEPRECATED("Please use ZGMTRCommandIDTypeClusterOperationalCredentialsCommandAddNOCID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x00000006,
    ZGMTRClusterOperationalCredentialsCommandUpdateNOCID
        ZGMTR_DEPRECATED("Please use ZGMTRCommandIDTypeClusterOperationalCredentialsCommandUpdateNOCID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x00000007,
    ZGMTRClusterOperationalCredentialsCommandNOCResponseID
        ZGMTR_DEPRECATED("Please use ZGMTRCommandIDTypeClusterOperationalCredentialsCommandNOCResponseID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x00000008,
    ZGMTRClusterOperationalCredentialsCommandUpdateFabricLabelID
        ZGMTR_DEPRECATED("Please use ZGMTRCommandIDTypeClusterOperationalCredentialsCommandUpdateFabricLabelID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x00000009,
    ZGMTRClusterOperationalCredentialsCommandRemoveFabricID
        ZGMTR_DEPRECATED("Please use ZGMTRCommandIDTypeClusterOperationalCredentialsCommandRemoveFabricID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x0000000A,
    ZGMTRClusterOperationalCredentialsCommandAddTrustedRootCertificateID
        ZGMTR_DEPRECATED("Please use ZGMTRCommandIDTypeClusterOperationalCredentialsCommandAddTrustedRootCertificateID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x0000000B,

    // Cluster OperationalCredentials commands
    ZGMTRCommandIDTypeClusterOperationalCredentialsCommandAttestationRequestID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000000,
    ZGMTRCommandIDTypeClusterOperationalCredentialsCommandAttestationResponseID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000001,
    ZGMTRCommandIDTypeClusterOperationalCredentialsCommandCertificateChainRequestID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000002,
    ZGMTRCommandIDTypeClusterOperationalCredentialsCommandCertificateChainResponseID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000003,
    ZGMTRCommandIDTypeClusterOperationalCredentialsCommandCSRRequestID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000004,
    ZGMTRCommandIDTypeClusterOperationalCredentialsCommandCSRResponseID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000005,
    ZGMTRCommandIDTypeClusterOperationalCredentialsCommandAddNOCID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000006,
    ZGMTRCommandIDTypeClusterOperationalCredentialsCommandUpdateNOCID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000007,
    ZGMTRCommandIDTypeClusterOperationalCredentialsCommandNOCResponseID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000008,
    ZGMTRCommandIDTypeClusterOperationalCredentialsCommandUpdateFabricLabelID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000009,
    ZGMTRCommandIDTypeClusterOperationalCredentialsCommandRemoveFabricID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x0000000A,
    ZGMTRCommandIDTypeClusterOperationalCredentialsCommandAddTrustedRootCertificateID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x0000000B,
    ZGMTRCommandIDTypeClusterOperationalCredentialsCommandSetVIDVerificationStatementID ZGMTR_PROVISIONALLY_AVAILABLE = 0x0000000C,
    ZGMTRCommandIDTypeClusterOperationalCredentialsCommandSignVIDVerificationRequestID ZGMTR_PROVISIONALLY_AVAILABLE = 0x0000000D,
    ZGMTRCommandIDTypeClusterOperationalCredentialsCommandSignVIDVerificationResponseID ZGMTR_PROVISIONALLY_AVAILABLE = 0x0000000E,

    // Cluster GroupKeyManagement deprecated command id names
    ZGMTRClusterGroupKeyManagementCommandKeySetWriteID
        ZGMTR_DEPRECATED("Please use ZGMTRCommandIDTypeClusterGroupKeyManagementCommandKeySetWriteID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x00000000,
    ZGMTRClusterGroupKeyManagementCommandKeySetReadID
        ZGMTR_DEPRECATED("Please use ZGMTRCommandIDTypeClusterGroupKeyManagementCommandKeySetReadID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x00000001,
    ZGMTRClusterGroupKeyManagementCommandKeySetReadResponseID
        ZGMTR_DEPRECATED("Please use ZGMTRCommandIDTypeClusterGroupKeyManagementCommandKeySetReadResponseID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x00000002,
    ZGMTRClusterGroupKeyManagementCommandKeySetRemoveID
        ZGMTR_DEPRECATED("Please use ZGMTRCommandIDTypeClusterGroupKeyManagementCommandKeySetRemoveID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x00000003,
    ZGMTRClusterGroupKeyManagementCommandKeySetReadAllIndicesID
        ZGMTR_DEPRECATED("Please use ZGMTRCommandIDTypeClusterGroupKeyManagementCommandKeySetReadAllIndicesID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x00000004,
    ZGMTRClusterGroupKeyManagementCommandKeySetReadAllIndicesResponseID
        ZGMTR_DEPRECATED("Please use ZGMTRCommandIDTypeClusterGroupKeyManagementCommandKeySetReadAllIndicesResponseID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x00000005,

    // Cluster GroupKeyManagement commands
    ZGMTRCommandIDTypeClusterGroupKeyManagementCommandKeySetWriteID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000000,
    ZGMTRCommandIDTypeClusterGroupKeyManagementCommandKeySetReadID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000001,
    ZGMTRCommandIDTypeClusterGroupKeyManagementCommandKeySetReadResponseID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000002,
    ZGMTRCommandIDTypeClusterGroupKeyManagementCommandKeySetRemoveID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000003,
    ZGMTRCommandIDTypeClusterGroupKeyManagementCommandKeySetReadAllIndicesID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000004,
    ZGMTRCommandIDTypeClusterGroupKeyManagementCommandKeySetReadAllIndicesResponseID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000005,

    // Cluster ICDManagement commands
    ZGMTRCommandIDTypeClusterICDManagementCommandRegisterClientID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = 0x00000000,
    ZGMTRCommandIDTypeClusterICDManagementCommandRegisterClientResponseID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = 0x00000001,
    ZGMTRCommandIDTypeClusterICDManagementCommandUnregisterClientID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = 0x00000002,
    ZGMTRCommandIDTypeClusterICDManagementCommandStayActiveRequestID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = 0x00000003,
    ZGMTRCommandIDTypeClusterICDManagementCommandStayActiveResponseID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = 0x00000004,

    // Cluster OvenCavityOperationalState commands
    ZGMTRCommandIDTypeClusterOvenCavityOperationalStateCommandStopID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = 0x00000001,
    ZGMTRCommandIDTypeClusterOvenCavityOperationalStateCommandStartID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = 0x00000002,
    ZGMTRCommandIDTypeClusterOvenCavityOperationalStateCommandOperationalCommandResponseID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = 0x00000004,

    // Cluster OvenMode commands
    ZGMTRCommandIDTypeClusterOvenModeCommandChangeToModeID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = 0x00000000,
    ZGMTRCommandIDTypeClusterOvenModeCommandChangeToModeResponseID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = 0x00000001,

    // Cluster ModeSelect deprecated command id names
    ZGMTRClusterModeSelectCommandChangeToModeID
        ZGMTR_DEPRECATED("Please use ZGMTRCommandIDTypeClusterModeSelectCommandChangeToModeID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x00000000,

    // Cluster ModeSelect commands
    ZGMTRCommandIDTypeClusterModeSelectCommandChangeToModeID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000000,

    // Cluster LaundryWasherMode commands
    ZGMTRCommandIDTypeClusterLaundryWasherModeCommandChangeToModeID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = 0x00000000,
    ZGMTRCommandIDTypeClusterLaundryWasherModeCommandChangeToModeResponseID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = 0x00000001,

    // Cluster RefrigeratorAndTemperatureControlledCabinetMode commands
    ZGMTRCommandIDTypeClusterRefrigeratorAndTemperatureControlledCabinetModeCommandChangeToModeID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = 0x00000000,
    ZGMTRCommandIDTypeClusterRefrigeratorAndTemperatureControlledCabinetModeCommandChangeToModeResponseID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = 0x00000001,

    // Cluster RVCRunMode commands
    ZGMTRCommandIDTypeClusterRVCRunModeCommandChangeToModeID ZGMTR_AVAILABLE(ios(17.4), macos(14.4), watchos(10.4), tvos(17.4)) = 0x00000000,
    ZGMTRCommandIDTypeClusterRVCRunModeCommandChangeToModeResponseID ZGMTR_AVAILABLE(ios(17.4), macos(14.4), watchos(10.4), tvos(17.4)) = 0x00000001,

    // Cluster RVCCleanMode commands
    ZGMTRCommandIDTypeClusterRVCCleanModeCommandChangeToModeID ZGMTR_AVAILABLE(ios(17.4), macos(14.4), watchos(10.4), tvos(17.4)) = 0x00000000,
    ZGMTRCommandIDTypeClusterRVCCleanModeCommandChangeToModeResponseID ZGMTR_AVAILABLE(ios(17.4), macos(14.4), watchos(10.4), tvos(17.4)) = 0x00000001,

    // Cluster TemperatureControl commands
    ZGMTRCommandIDTypeClusterTemperatureControlCommandSetTemperatureID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = 0x00000000,

    // Cluster DishwasherMode commands
    ZGMTRCommandIDTypeClusterDishwasherModeCommandChangeToModeID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = 0x00000000,
    ZGMTRCommandIDTypeClusterDishwasherModeCommandChangeToModeResponseID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = 0x00000001,

    // Cluster SmokeCOAlarm commands
    ZGMTRCommandIDTypeClusterSmokeCOAlarmCommandSelfTestRequestID ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6)) = 0x00000000,

    // Cluster DishwasherAlarm commands
    ZGMTRCommandIDTypeClusterDishwasherAlarmCommandResetID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = 0x00000000,
    ZGMTRCommandIDTypeClusterDishwasherAlarmCommandModifyEnabledAlarmsID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = 0x00000001,

    // Cluster MicrowaveOvenControl commands
    ZGMTRCommandIDTypeClusterMicrowaveOvenControlCommandSetCookingParametersID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = 0x00000000,
    ZGMTRCommandIDTypeClusterMicrowaveOvenControlCommandAddMoreTimeID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = 0x00000001,

    // Cluster OperationalState commands
    ZGMTRCommandIDTypeClusterOperationalStateCommandPauseID ZGMTR_AVAILABLE(ios(17.4), macos(14.4), watchos(10.4), tvos(17.4)) = 0x00000000,
    ZGMTRCommandIDTypeClusterOperationalStateCommandStopID ZGMTR_AVAILABLE(ios(17.4), macos(14.4), watchos(10.4), tvos(17.4)) = 0x00000001,
    ZGMTRCommandIDTypeClusterOperationalStateCommandStartID ZGMTR_AVAILABLE(ios(17.4), macos(14.4), watchos(10.4), tvos(17.4)) = 0x00000002,
    ZGMTRCommandIDTypeClusterOperationalStateCommandResumeID ZGMTR_AVAILABLE(ios(17.4), macos(14.4), watchos(10.4), tvos(17.4)) = 0x00000003,
    ZGMTRCommandIDTypeClusterOperationalStateCommandOperationalCommandResponseID ZGMTR_AVAILABLE(ios(17.4), macos(14.4), watchos(10.4), tvos(17.4)) = 0x00000004,

    // Cluster RVCOperationalState commands
    ZGMTRCommandIDTypeClusterRVCOperationalStateCommandPauseID ZGMTR_AVAILABLE(ios(17.4), macos(14.4), watchos(10.4), tvos(17.4)) = 0x00000000,
    ZGMTRCommandIDTypeClusterRVCOperationalStateCommandResumeID ZGMTR_AVAILABLE(ios(17.4), macos(14.4), watchos(10.4), tvos(17.4)) = 0x00000003,
    ZGMTRCommandIDTypeClusterRVCOperationalStateCommandOperationalCommandResponseID ZGMTR_AVAILABLE(ios(17.4), macos(14.4), watchos(10.4), tvos(17.4)) = 0x00000004,
    ZGMTRCommandIDTypeClusterRVCOperationalStateCommandGoHomeID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = 0x00000080,

    // Cluster ScenesManagement commands
    ZGMTRCommandIDTypeClusterScenesManagementCommandAddSceneID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000000,
    ZGMTRCommandIDTypeClusterScenesManagementCommandAddSceneResponseID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000000,
    ZGMTRCommandIDTypeClusterScenesManagementCommandViewSceneID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000001,
    ZGMTRCommandIDTypeClusterScenesManagementCommandViewSceneResponseID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000001,
    ZGMTRCommandIDTypeClusterScenesManagementCommandRemoveSceneID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000002,
    ZGMTRCommandIDTypeClusterScenesManagementCommandRemoveSceneResponseID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000002,
    ZGMTRCommandIDTypeClusterScenesManagementCommandRemoveAllScenesID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000003,
    ZGMTRCommandIDTypeClusterScenesManagementCommandRemoveAllScenesResponseID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000003,
    ZGMTRCommandIDTypeClusterScenesManagementCommandStoreSceneID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000004,
    ZGMTRCommandIDTypeClusterScenesManagementCommandStoreSceneResponseID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000004,
    ZGMTRCommandIDTypeClusterScenesManagementCommandRecallSceneID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000005,
    ZGMTRCommandIDTypeClusterScenesManagementCommandGetSceneMembershipID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000006,
    ZGMTRCommandIDTypeClusterScenesManagementCommandGetSceneMembershipResponseID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000006,
    ZGMTRCommandIDTypeClusterScenesManagementCommandCopySceneID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000040,
    ZGMTRCommandIDTypeClusterScenesManagementCommandCopySceneResponseID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000040,

    // Cluster Groupcast commands
    ZGMTRCommandIDTypeClusterGroupcastCommandJoinGroupID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000000,
    ZGMTRCommandIDTypeClusterGroupcastCommandLeaveGroupID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000001,
    ZGMTRCommandIDTypeClusterGroupcastCommandLeaveGroupResponseID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000002,
    ZGMTRCommandIDTypeClusterGroupcastCommandUpdateGroupKeyID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000003,
    ZGMTRCommandIDTypeClusterGroupcastCommandConfigureAuxiliaryACLID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000004,
    ZGMTRCommandIDTypeClusterGroupcastCommandGroupcastTestingID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000005,

    // Cluster HEPAFilterMonitoring commands
    ZGMTRCommandIDTypeClusterHEPAFilterMonitoringCommandResetConditionID ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6)) = 0x00000000,

    // Cluster ActivatedCarbonFilterMonitoring commands
    ZGMTRCommandIDTypeClusterActivatedCarbonFilterMonitoringCommandResetConditionID ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6)) = 0x00000000,

    // Cluster WaterTankLevelMonitoring commands
    ZGMTRCommandIDTypeClusterWaterTankLevelMonitoringCommandResetConditionID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000000,

    // Cluster BooleanStateConfiguration commands
    ZGMTRCommandIDTypeClusterBooleanStateConfigurationCommandSuppressAlarmID ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6)) = 0x00000000,
    ZGMTRCommandIDTypeClusterBooleanStateConfigurationCommandEnableDisableAlarmID ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6)) = 0x00000001,

    // Cluster ValveConfigurationAndControl commands
    ZGMTRCommandIDTypeClusterValveConfigurationAndControlCommandOpenID ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6)) = 0x00000000,
    ZGMTRCommandIDTypeClusterValveConfigurationAndControlCommandCloseID ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6)) = 0x00000001,

    // Cluster WaterHeaterManagement commands
    ZGMTRCommandIDTypeClusterWaterHeaterManagementCommandBoostID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = 0x00000000,
    ZGMTRCommandIDTypeClusterWaterHeaterManagementCommandCancelBoostID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = 0x00000001,

    // Cluster CommodityPrice commands
    ZGMTRCommandIDTypeClusterCommodityPriceCommandGetDetailedPriceRequestID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000000,
    ZGMTRCommandIDTypeClusterCommodityPriceCommandGetDetailedPriceResponseID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000001,
    ZGMTRCommandIDTypeClusterCommodityPriceCommandGetDetailedForecastRequestID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000002,
    ZGMTRCommandIDTypeClusterCommodityPriceCommandGetDetailedForecastResponseID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000003,

    // Cluster Messages commands
    ZGMTRCommandIDTypeClusterMessagesCommandPresentMessagesRequestID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = 0x00000000,
    ZGMTRCommandIDTypeClusterMessagesCommandCancelMessagesRequestID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = 0x00000001,

    // Cluster DeviceEnergyManagement commands
    ZGMTRCommandIDTypeClusterDeviceEnergyManagementCommandPowerAdjustRequestID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = 0x00000000,
    ZGMTRCommandIDTypeClusterDeviceEnergyManagementCommandCancelPowerAdjustRequestID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = 0x00000001,
    ZGMTRCommandIDTypeClusterDeviceEnergyManagementCommandStartTimeAdjustRequestID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = 0x00000002,
    ZGMTRCommandIDTypeClusterDeviceEnergyManagementCommandPauseRequestID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = 0x00000003,
    ZGMTRCommandIDTypeClusterDeviceEnergyManagementCommandResumeRequestID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = 0x00000004,
    ZGMTRCommandIDTypeClusterDeviceEnergyManagementCommandModifyForecastRequestID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = 0x00000005,
    ZGMTRCommandIDTypeClusterDeviceEnergyManagementCommandRequestConstraintBasedForecastID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = 0x00000006,
    ZGMTRCommandIDTypeClusterDeviceEnergyManagementCommandCancelRequestID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = 0x00000007,
    ZGMTRCommandIDTypeClusterDeviceEnergyManagementCommandPowerRangeAdjustRequestID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000008,
    ZGMTRCommandIDTypeClusterDeviceEnergyManagementCommandCancelPowerRangeAdjustRequestID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000009,

    // Cluster EnergyEVSE commands
    ZGMTRCommandIDTypeClusterEnergyEVSECommandGetTargetsResponseID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = 0x00000000,
    ZGMTRCommandIDTypeClusterEnergyEVSECommandDisableID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = 0x00000001,
    ZGMTRCommandIDTypeClusterEnergyEVSECommandEnableChargingID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = 0x00000002,
    ZGMTRCommandIDTypeClusterEnergyEVSECommandEnableDischargingID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000003,
    ZGMTRCommandIDTypeClusterEnergyEVSECommandStartDiagnosticsID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = 0x00000004,
    ZGMTRCommandIDTypeClusterEnergyEVSECommandSetTargetsID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = 0x00000005,
    ZGMTRCommandIDTypeClusterEnergyEVSECommandGetTargetsID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = 0x00000006,
    ZGMTRCommandIDTypeClusterEnergyEVSECommandClearTargetsID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = 0x00000007,

    // Cluster EnergyEVSEMode commands
    ZGMTRCommandIDTypeClusterEnergyEVSEModeCommandChangeToModeID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = 0x00000000,
    ZGMTRCommandIDTypeClusterEnergyEVSEModeCommandChangeToModeResponseID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = 0x00000001,

    // Cluster WaterHeaterMode commands
    ZGMTRCommandIDTypeClusterWaterHeaterModeCommandChangeToModeID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = 0x00000000,
    ZGMTRCommandIDTypeClusterWaterHeaterModeCommandChangeToModeResponseID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = 0x00000001,

    // Cluster DeviceEnergyManagementMode commands
    ZGMTRCommandIDTypeClusterDeviceEnergyManagementModeCommandChangeToModeID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = 0x00000000,
    ZGMTRCommandIDTypeClusterDeviceEnergyManagementModeCommandChangeToModeResponseID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = 0x00000001,

    // Cluster ElectricalAlarm commands
    ZGMTRCommandIDTypeClusterElectricalAlarmCommandResetID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000000,
    ZGMTRCommandIDTypeClusterElectricalAlarmCommandModifyEnabledAlarmsID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000001,
    ZGMTRCommandIDTypeClusterElectricalAlarmCommandSetElectricalAlarmThresholdsID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000080,

    // Cluster ElectricalProtectionAlarm commands
    ZGMTRCommandIDTypeClusterElectricalProtectionAlarmCommandModifyEnabledAlarmsID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000001,

    // Cluster DoorLock deprecated command id names
    ZGMTRClusterDoorLockCommandLockDoorID
        ZGMTR_DEPRECATED("Please use ZGMTRCommandIDTypeClusterDoorLockCommandLockDoorID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x00000000,
    ZGMTRClusterDoorLockCommandUnlockDoorID
        ZGMTR_DEPRECATED("Please use ZGMTRCommandIDTypeClusterDoorLockCommandUnlockDoorID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x00000001,
    ZGMTRClusterDoorLockCommandUnlockWithTimeoutID
        ZGMTR_DEPRECATED("Please use ZGMTRCommandIDTypeClusterDoorLockCommandUnlockWithTimeoutID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x00000003,
    ZGMTRClusterDoorLockCommandSetWeekDayScheduleID
        ZGMTR_DEPRECATED("Please use ZGMTRCommandIDTypeClusterDoorLockCommandSetWeekDayScheduleID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x0000000B,
    ZGMTRClusterDoorLockCommandGetWeekDayScheduleID
        ZGMTR_DEPRECATED("Please use ZGMTRCommandIDTypeClusterDoorLockCommandGetWeekDayScheduleID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x0000000C,
    ZGMTRClusterDoorLockCommandGetWeekDayScheduleResponseID
        ZGMTR_DEPRECATED("Please use ZGMTRCommandIDTypeClusterDoorLockCommandGetWeekDayScheduleResponseID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x0000000C,
    ZGMTRClusterDoorLockCommandClearWeekDayScheduleID
        ZGMTR_DEPRECATED("Please use ZGMTRCommandIDTypeClusterDoorLockCommandClearWeekDayScheduleID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x0000000D,
    ZGMTRClusterDoorLockCommandSetYearDayScheduleID
        ZGMTR_DEPRECATED("Please use ZGMTRCommandIDTypeClusterDoorLockCommandSetYearDayScheduleID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x0000000E,
    ZGMTRClusterDoorLockCommandGetYearDayScheduleID
        ZGMTR_DEPRECATED("Please use ZGMTRCommandIDTypeClusterDoorLockCommandGetYearDayScheduleID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x0000000F,
    ZGMTRClusterDoorLockCommandGetYearDayScheduleResponseID
        ZGMTR_DEPRECATED("Please use ZGMTRCommandIDTypeClusterDoorLockCommandGetYearDayScheduleResponseID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x0000000F,
    ZGMTRClusterDoorLockCommandClearYearDayScheduleID
        ZGMTR_DEPRECATED("Please use ZGMTRCommandIDTypeClusterDoorLockCommandClearYearDayScheduleID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x00000010,
    ZGMTRClusterDoorLockCommandSetHolidayScheduleID
        ZGMTR_DEPRECATED("Please use ZGMTRCommandIDTypeClusterDoorLockCommandSetHolidayScheduleID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x00000011,
    ZGMTRClusterDoorLockCommandGetHolidayScheduleID
        ZGMTR_DEPRECATED("Please use ZGMTRCommandIDTypeClusterDoorLockCommandGetHolidayScheduleID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x00000012,
    ZGMTRClusterDoorLockCommandGetHolidayScheduleResponseID
        ZGMTR_DEPRECATED("Please use ZGMTRCommandIDTypeClusterDoorLockCommandGetHolidayScheduleResponseID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x00000012,
    ZGMTRClusterDoorLockCommandClearHolidayScheduleID
        ZGMTR_DEPRECATED("Please use ZGMTRCommandIDTypeClusterDoorLockCommandClearHolidayScheduleID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x00000013,
    ZGMTRClusterDoorLockCommandSetUserID
        ZGMTR_DEPRECATED("Please use ZGMTRCommandIDTypeClusterDoorLockCommandSetUserID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x0000001A,
    ZGMTRClusterDoorLockCommandGetUserID
        ZGMTR_DEPRECATED("Please use ZGMTRCommandIDTypeClusterDoorLockCommandGetUserID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x0000001B,
    ZGMTRClusterDoorLockCommandGetUserResponseID
        ZGMTR_DEPRECATED("Please use ZGMTRCommandIDTypeClusterDoorLockCommandGetUserResponseID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x0000001C,
    ZGMTRClusterDoorLockCommandClearUserID
        ZGMTR_DEPRECATED("Please use ZGMTRCommandIDTypeClusterDoorLockCommandClearUserID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x0000001D,
    ZGMTRClusterDoorLockCommandSetCredentialID
        ZGMTR_DEPRECATED("Please use ZGMTRCommandIDTypeClusterDoorLockCommandSetCredentialID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x00000022,
    ZGMTRClusterDoorLockCommandSetCredentialResponseID
        ZGMTR_DEPRECATED("Please use ZGMTRCommandIDTypeClusterDoorLockCommandSetCredentialResponseID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x00000023,
    ZGMTRClusterDoorLockCommandGetCredentialStatusID
        ZGMTR_DEPRECATED("Please use ZGMTRCommandIDTypeClusterDoorLockCommandGetCredentialStatusID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x00000024,
    ZGMTRClusterDoorLockCommandGetCredentialStatusResponseID
        ZGMTR_DEPRECATED("Please use ZGMTRCommandIDTypeClusterDoorLockCommandGetCredentialStatusResponseID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x00000025,
    ZGMTRClusterDoorLockCommandClearCredentialID
        ZGMTR_DEPRECATED("Please use ZGMTRCommandIDTypeClusterDoorLockCommandClearCredentialID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x00000026,

    // Cluster DoorLock commands
    ZGMTRCommandIDTypeClusterDoorLockCommandLockDoorID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000000,
    ZGMTRCommandIDTypeClusterDoorLockCommandUnlockDoorID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000001,
    ZGMTRCommandIDTypeClusterDoorLockCommandUnlockWithTimeoutID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000003,
    ZGMTRCommandIDTypeClusterDoorLockCommandSetWeekDayScheduleID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x0000000B,
    ZGMTRCommandIDTypeClusterDoorLockCommandGetWeekDayScheduleID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x0000000C,
    ZGMTRCommandIDTypeClusterDoorLockCommandGetWeekDayScheduleResponseID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x0000000C,
    ZGMTRCommandIDTypeClusterDoorLockCommandClearWeekDayScheduleID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x0000000D,
    ZGMTRCommandIDTypeClusterDoorLockCommandSetYearDayScheduleID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x0000000E,
    ZGMTRCommandIDTypeClusterDoorLockCommandGetYearDayScheduleID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x0000000F,
    ZGMTRCommandIDTypeClusterDoorLockCommandGetYearDayScheduleResponseID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x0000000F,
    ZGMTRCommandIDTypeClusterDoorLockCommandClearYearDayScheduleID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000010,
    ZGMTRCommandIDTypeClusterDoorLockCommandSetHolidayScheduleID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000011,
    ZGMTRCommandIDTypeClusterDoorLockCommandGetHolidayScheduleID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000012,
    ZGMTRCommandIDTypeClusterDoorLockCommandGetHolidayScheduleResponseID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000012,
    ZGMTRCommandIDTypeClusterDoorLockCommandClearHolidayScheduleID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000013,
    ZGMTRCommandIDTypeClusterDoorLockCommandSetUserID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x0000001A,
    ZGMTRCommandIDTypeClusterDoorLockCommandGetUserID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x0000001B,
    ZGMTRCommandIDTypeClusterDoorLockCommandGetUserResponseID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x0000001C,
    ZGMTRCommandIDTypeClusterDoorLockCommandClearUserID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x0000001D,
    ZGMTRCommandIDTypeClusterDoorLockCommandSetCredentialID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000022,
    ZGMTRCommandIDTypeClusterDoorLockCommandSetCredentialResponseID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000023,
    ZGMTRCommandIDTypeClusterDoorLockCommandGetCredentialStatusID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000024,
    ZGMTRCommandIDTypeClusterDoorLockCommandGetCredentialStatusResponseID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000025,
    ZGMTRCommandIDTypeClusterDoorLockCommandClearCredentialID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000026,
    ZGMTRCommandIDTypeClusterDoorLockCommandUnboltDoorID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = 0x00000027,
    ZGMTRCommandIDTypeClusterDoorLockCommandSetAliroReaderConfigID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = 0x00000028,
    ZGMTRCommandIDTypeClusterDoorLockCommandClearAliroReaderConfigID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = 0x00000029,

    // Cluster WindowCovering deprecated command id names
    ZGMTRClusterWindowCoveringCommandUpOrOpenID
        ZGMTR_DEPRECATED("Please use ZGMTRCommandIDTypeClusterWindowCoveringCommandUpOrOpenID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x00000000,
    ZGMTRClusterWindowCoveringCommandDownOrCloseID
        ZGMTR_DEPRECATED("Please use ZGMTRCommandIDTypeClusterWindowCoveringCommandDownOrCloseID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x00000001,
    ZGMTRClusterWindowCoveringCommandStopMotionID
        ZGMTR_DEPRECATED("Please use ZGMTRCommandIDTypeClusterWindowCoveringCommandStopMotionID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x00000002,
    ZGMTRClusterWindowCoveringCommandGoToLiftValueID
        ZGMTR_DEPRECATED("Please use ZGMTRCommandIDTypeClusterWindowCoveringCommandGoToLiftValueID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x00000004,
    ZGMTRClusterWindowCoveringCommandGoToLiftPercentageID
        ZGMTR_DEPRECATED("Please use ZGMTRCommandIDTypeClusterWindowCoveringCommandGoToLiftPercentageID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x00000005,
    ZGMTRClusterWindowCoveringCommandGoToTiltValueID
        ZGMTR_DEPRECATED("Please use ZGMTRCommandIDTypeClusterWindowCoveringCommandGoToTiltValueID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x00000007,
    ZGMTRClusterWindowCoveringCommandGoToTiltPercentageID
        ZGMTR_DEPRECATED("Please use ZGMTRCommandIDTypeClusterWindowCoveringCommandGoToTiltPercentageID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x00000008,

    // Cluster WindowCovering commands
    ZGMTRCommandIDTypeClusterWindowCoveringCommandUpOrOpenID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000000,
    ZGMTRCommandIDTypeClusterWindowCoveringCommandDownOrCloseID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000001,
    ZGMTRCommandIDTypeClusterWindowCoveringCommandStopMotionID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000002,
    ZGMTRCommandIDTypeClusterWindowCoveringCommandGoToLiftValueID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000004,
    ZGMTRCommandIDTypeClusterWindowCoveringCommandGoToLiftPercentageID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000005,
    ZGMTRCommandIDTypeClusterWindowCoveringCommandGoToTiltValueID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000007,
    ZGMTRCommandIDTypeClusterWindowCoveringCommandGoToTiltPercentageID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000008,

    // Cluster ClosureControl commands
    ZGMTRCommandIDTypeClusterClosureControlCommandStopID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000000,
    ZGMTRCommandIDTypeClusterClosureControlCommandMoveToID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000001,
    ZGMTRCommandIDTypeClusterClosureControlCommandCalibrateID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000002,
    ZGMTRCommandIDTypeClusterClosureControlCommandGroupedMoveToID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000003,

    // Cluster ClosureDimension commands
    ZGMTRCommandIDTypeClusterClosureDimensionCommandSetTargetID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000000,
    ZGMTRCommandIDTypeClusterClosureDimensionCommandStepID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000001,
    ZGMTRCommandIDTypeClusterClosureDimensionCommandGroupedSetTargetID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000002,
    ZGMTRCommandIDTypeClusterClosureDimensionCommandGroupedStepID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000003,

    // Cluster ServiceArea commands
    ZGMTRCommandIDTypeClusterServiceAreaCommandSelectAreasID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = 0x00000000,
    ZGMTRCommandIDTypeClusterServiceAreaCommandSelectAreasResponseID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = 0x00000001,
    ZGMTRCommandIDTypeClusterServiceAreaCommandSkipAreaID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = 0x00000002,
    ZGMTRCommandIDTypeClusterServiceAreaCommandSkipAreaResponseID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = 0x00000003,

    // Cluster Thermostat deprecated command id names
    ZGMTRClusterThermostatCommandSetpointRaiseLowerID
        ZGMTR_DEPRECATED("Please use ZGMTRCommandIDTypeClusterThermostatCommandSetpointRaiseLowerID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x00000000,
    ZGMTRClusterThermostatCommandGetWeeklyScheduleResponseID
        ZGMTR_DEPRECATED("Please use ZGMTRCommandIDTypeClusterThermostatCommandGetWeeklyScheduleResponseID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x00000000,
    ZGMTRClusterThermostatCommandSetWeeklyScheduleID
        ZGMTR_DEPRECATED("Please use ZGMTRCommandIDTypeClusterThermostatCommandSetWeeklyScheduleID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x00000001,
    ZGMTRClusterThermostatCommandGetWeeklyScheduleID
        ZGMTR_DEPRECATED("Please use ZGMTRCommandIDTypeClusterThermostatCommandGetWeeklyScheduleID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x00000002,
    ZGMTRClusterThermostatCommandClearWeeklyScheduleID
        ZGMTR_DEPRECATED("Please use ZGMTRCommandIDTypeClusterThermostatCommandClearWeeklyScheduleID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x00000003,

    // Cluster Thermostat commands
    ZGMTRCommandIDTypeClusterThermostatCommandSetpointRaiseLowerID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000000,
    ZGMTRCommandIDTypeClusterThermostatCommandGetWeeklyScheduleResponseID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000000,
    ZGMTRCommandIDTypeClusterThermostatCommandSetWeeklyScheduleID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000001,
    ZGMTRCommandIDTypeClusterThermostatCommandGetWeeklyScheduleID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000002,
    ZGMTRCommandIDTypeClusterThermostatCommandAddThermostatSuggestionResponseID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000002,
    ZGMTRCommandIDTypeClusterThermostatCommandClearWeeklyScheduleID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000003,
    ZGMTRCommandIDTypeClusterThermostatCommandSetActiveScheduleRequestID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = 0x00000005,
    ZGMTRCommandIDTypeClusterThermostatCommandSetActivePresetRequestID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = 0x00000006,
    ZGMTRCommandIDTypeClusterThermostatCommandAddThermostatSuggestionID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000007,
    ZGMTRCommandIDTypeClusterThermostatCommandRemoveThermostatSuggestionID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000008,
    ZGMTRCommandIDTypeClusterThermostatCommandAtomicResponseID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = 0x000000FD,
    ZGMTRCommandIDTypeClusterThermostatCommandAtomicRequestID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = 0x000000FE,

    // Cluster FanControl deprecated command id names

    // Cluster FanControl commands
    ZGMTRCommandIDTypeClusterFanControlCommandStepID ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6)) = 0x00000000,

    // Cluster Humidistat commands
    ZGMTRCommandIDTypeClusterHumidistatCommandSetSettingsID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000000,

    // Cluster ColorControl deprecated command id names
    ZGMTRClusterColorControlCommandMoveToHueID
        ZGMTR_DEPRECATED("Please use ZGMTRCommandIDTypeClusterColorControlCommandMoveToHueID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x00000000,
    ZGMTRClusterColorControlCommandMoveHueID
        ZGMTR_DEPRECATED("Please use ZGMTRCommandIDTypeClusterColorControlCommandMoveHueID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x00000001,
    ZGMTRClusterColorControlCommandStepHueID
        ZGMTR_DEPRECATED("Please use ZGMTRCommandIDTypeClusterColorControlCommandStepHueID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x00000002,
    ZGMTRClusterColorControlCommandMoveToSaturationID
        ZGMTR_DEPRECATED("Please use ZGMTRCommandIDTypeClusterColorControlCommandMoveToSaturationID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x00000003,
    ZGMTRClusterColorControlCommandMoveSaturationID
        ZGMTR_DEPRECATED("Please use ZGMTRCommandIDTypeClusterColorControlCommandMoveSaturationID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x00000004,
    ZGMTRClusterColorControlCommandStepSaturationID
        ZGMTR_DEPRECATED("Please use ZGMTRCommandIDTypeClusterColorControlCommandStepSaturationID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x00000005,
    ZGMTRClusterColorControlCommandMoveToHueAndSaturationID
        ZGMTR_DEPRECATED("Please use ZGMTRCommandIDTypeClusterColorControlCommandMoveToHueAndSaturationID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x00000006,
    ZGMTRClusterColorControlCommandMoveToColorID
        ZGMTR_DEPRECATED("Please use ZGMTRCommandIDTypeClusterColorControlCommandMoveToColorID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x00000007,
    ZGMTRClusterColorControlCommandMoveColorID
        ZGMTR_DEPRECATED("Please use ZGMTRCommandIDTypeClusterColorControlCommandMoveColorID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x00000008,
    ZGMTRClusterColorControlCommandStepColorID
        ZGMTR_DEPRECATED("Please use ZGMTRCommandIDTypeClusterColorControlCommandStepColorID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x00000009,
    ZGMTRClusterColorControlCommandMoveToColorTemperatureID
        ZGMTR_DEPRECATED("Please use ZGMTRCommandIDTypeClusterColorControlCommandMoveToColorTemperatureID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x0000000A,
    ZGMTRClusterColorControlCommandEnhancedMoveToHueID
        ZGMTR_DEPRECATED("Please use ZGMTRCommandIDTypeClusterColorControlCommandEnhancedMoveToHueID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x00000040,
    ZGMTRClusterColorControlCommandEnhancedMoveHueID
        ZGMTR_DEPRECATED("Please use ZGMTRCommandIDTypeClusterColorControlCommandEnhancedMoveHueID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x00000041,
    ZGMTRClusterColorControlCommandEnhancedStepHueID
        ZGMTR_DEPRECATED("Please use ZGMTRCommandIDTypeClusterColorControlCommandEnhancedStepHueID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x00000042,
    ZGMTRClusterColorControlCommandEnhancedMoveToHueAndSaturationID
        ZGMTR_DEPRECATED("Please use ZGMTRCommandIDTypeClusterColorControlCommandEnhancedMoveToHueAndSaturationID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x00000043,
    ZGMTRClusterColorControlCommandColorLoopSetID
        ZGMTR_DEPRECATED("Please use ZGMTRCommandIDTypeClusterColorControlCommandColorLoopSetID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x00000044,
    ZGMTRClusterColorControlCommandStopMoveStepID
        ZGMTR_DEPRECATED("Please use ZGMTRCommandIDTypeClusterColorControlCommandStopMoveStepID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x00000047,
    ZGMTRClusterColorControlCommandMoveColorTemperatureID
        ZGMTR_DEPRECATED("Please use ZGMTRCommandIDTypeClusterColorControlCommandMoveColorTemperatureID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x0000004B,
    ZGMTRClusterColorControlCommandStepColorTemperatureID
        ZGMTR_DEPRECATED("Please use ZGMTRCommandIDTypeClusterColorControlCommandStepColorTemperatureID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x0000004C,

    // Cluster ColorControl commands
    ZGMTRCommandIDTypeClusterColorControlCommandMoveToHueID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000000,
    ZGMTRCommandIDTypeClusterColorControlCommandMoveHueID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000001,
    ZGMTRCommandIDTypeClusterColorControlCommandStepHueID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000002,
    ZGMTRCommandIDTypeClusterColorControlCommandMoveToSaturationID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000003,
    ZGMTRCommandIDTypeClusterColorControlCommandMoveSaturationID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000004,
    ZGMTRCommandIDTypeClusterColorControlCommandStepSaturationID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000005,
    ZGMTRCommandIDTypeClusterColorControlCommandMoveToHueAndSaturationID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000006,
    ZGMTRCommandIDTypeClusterColorControlCommandMoveToColorID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000007,
    ZGMTRCommandIDTypeClusterColorControlCommandMoveColorID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000008,
    ZGMTRCommandIDTypeClusterColorControlCommandStepColorID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000009,
    ZGMTRCommandIDTypeClusterColorControlCommandMoveToColorTemperatureID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x0000000A,
    ZGMTRCommandIDTypeClusterColorControlCommandEnhancedMoveToHueID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000040,
    ZGMTRCommandIDTypeClusterColorControlCommandEnhancedMoveHueID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000041,
    ZGMTRCommandIDTypeClusterColorControlCommandEnhancedStepHueID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000042,
    ZGMTRCommandIDTypeClusterColorControlCommandEnhancedMoveToHueAndSaturationID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000043,
    ZGMTRCommandIDTypeClusterColorControlCommandColorLoopSetID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000044,
    ZGMTRCommandIDTypeClusterColorControlCommandStopMoveStepID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000047,
    ZGMTRCommandIDTypeClusterColorControlCommandMoveColorTemperatureID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x0000004B,
    ZGMTRCommandIDTypeClusterColorControlCommandStepColorTemperatureID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x0000004C,

    // Cluster DynamicLighting commands
    ZGMTRCommandIDTypeClusterDynamicLightingCommandStartEffectID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000000,
    ZGMTRCommandIDTypeClusterDynamicLightingCommandStopEffectID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000001,

    // Cluster ProximityRanging commands
    ZGMTRCommandIDTypeClusterProximityRangingCommandStartRangingRequestID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000000,
    ZGMTRCommandIDTypeClusterProximityRangingCommandStartRangingResponseID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000001,
    ZGMTRCommandIDTypeClusterProximityRangingCommandStopRangingRequestID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000002,

    // Cluster NetworkIdentityManagement commands
    ZGMTRCommandIDTypeClusterNetworkIdentityManagementCommandAddClientID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000000,
    ZGMTRCommandIDTypeClusterNetworkIdentityManagementCommandAddClientResponseID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000001,
    ZGMTRCommandIDTypeClusterNetworkIdentityManagementCommandRemoveClientID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000002,
    ZGMTRCommandIDTypeClusterNetworkIdentityManagementCommandQueryIdentityID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000003,
    ZGMTRCommandIDTypeClusterNetworkIdentityManagementCommandQueryIdentityResponseID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000004,
    ZGMTRCommandIDTypeClusterNetworkIdentityManagementCommandImportAdminSecretID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000040,
    ZGMTRCommandIDTypeClusterNetworkIdentityManagementCommandExportAdminSecretID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000041,
    ZGMTRCommandIDTypeClusterNetworkIdentityManagementCommandExportAdminSecretResponseID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000042,

    // Cluster WiFiNetworkManagement commands
    ZGMTRCommandIDTypeClusterWiFiNetworkManagementCommandNetworkPassphraseRequestID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = 0x00000000,
    ZGMTRCommandIDTypeClusterWiFiNetworkManagementCommandNetworkPassphraseResponseID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = 0x00000001,

    // Cluster ThreadBorderRouterManagement commands
    ZGMTRCommandIDTypeClusterThreadBorderRouterManagementCommandGetActiveDatasetRequestID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = 0x00000000,
    ZGMTRCommandIDTypeClusterThreadBorderRouterManagementCommandGetPendingDatasetRequestID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = 0x00000001,
    ZGMTRCommandIDTypeClusterThreadBorderRouterManagementCommandDatasetResponseID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = 0x00000002,
    ZGMTRCommandIDTypeClusterThreadBorderRouterManagementCommandSetActiveDatasetRequestID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = 0x00000003,
    ZGMTRCommandIDTypeClusterThreadBorderRouterManagementCommandSetPendingDatasetRequestID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = 0x00000004,

    // Cluster ThreadNetworkDirectory commands
    ZGMTRCommandIDTypeClusterThreadNetworkDirectoryCommandAddNetworkID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = 0x00000000,
    ZGMTRCommandIDTypeClusterThreadNetworkDirectoryCommandRemoveNetworkID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = 0x00000001,
    ZGMTRCommandIDTypeClusterThreadNetworkDirectoryCommandGetOperationalDatasetID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = 0x00000002,
    ZGMTRCommandIDTypeClusterThreadNetworkDirectoryCommandOperationalDatasetResponseID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = 0x00000003,

    // Cluster CommissioningProxy commands
    ZGMTRCommandIDTypeClusterCommissioningProxyCommandProxyConnectRequestID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000000,
    ZGMTRCommandIDTypeClusterCommissioningProxyCommandProxyConnectResponseID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000001,
    ZGMTRCommandIDTypeClusterCommissioningProxyCommandProxyDisconnectRequestID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000002,
    ZGMTRCommandIDTypeClusterCommissioningProxyCommandProxyScanRequestID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000003,
    ZGMTRCommandIDTypeClusterCommissioningProxyCommandProxyScanResponseID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000004,
    ZGMTRCommandIDTypeClusterCommissioningProxyCommandProxyBackGroundScanStartRequestID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000005,
    ZGMTRCommandIDTypeClusterCommissioningProxyCommandProxyBackGroundScanStopRequestID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000006,
    ZGMTRCommandIDTypeClusterCommissioningProxyCommandProxyMessageRequestID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000007,
    ZGMTRCommandIDTypeClusterCommissioningProxyCommandProxyMessageResponseID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000008,

    // Cluster Channel deprecated command id names
    ZGMTRClusterChannelCommandChangeChannelID
        ZGMTR_DEPRECATED("Please use ZGMTRCommandIDTypeClusterChannelCommandChangeChannelID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x00000000,
    ZGMTRClusterChannelCommandChangeChannelResponseID
        ZGMTR_DEPRECATED("Please use ZGMTRCommandIDTypeClusterChannelCommandChangeChannelResponseID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x00000001,
    ZGMTRClusterChannelCommandChangeChannelByNumberID
        ZGMTR_DEPRECATED("Please use ZGMTRCommandIDTypeClusterChannelCommandChangeChannelByNumberID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x00000002,
    ZGMTRClusterChannelCommandSkipChannelID
        ZGMTR_DEPRECATED("Please use ZGMTRCommandIDTypeClusterChannelCommandSkipChannelID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x00000003,

    // Cluster Channel commands
    ZGMTRCommandIDTypeClusterChannelCommandChangeChannelID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000000,
    ZGMTRCommandIDTypeClusterChannelCommandChangeChannelResponseID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000001,
    ZGMTRCommandIDTypeClusterChannelCommandChangeChannelByNumberID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000002,
    ZGMTRCommandIDTypeClusterChannelCommandSkipChannelID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000003,
    ZGMTRCommandIDTypeClusterChannelCommandGetProgramGuideID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = 0x00000004,
    ZGMTRCommandIDTypeClusterChannelCommandProgramGuideResponseID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = 0x00000005,
    ZGMTRCommandIDTypeClusterChannelCommandRecordProgramID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = 0x00000006,
    ZGMTRCommandIDTypeClusterChannelCommandCancelRecordProgramID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = 0x00000007,

    // Cluster TargetNavigator deprecated command id names
    ZGMTRClusterTargetNavigatorCommandNavigateTargetID
        ZGMTR_DEPRECATED("Please use ZGMTRCommandIDTypeClusterTargetNavigatorCommandNavigateTargetID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x00000000,
    ZGMTRClusterTargetNavigatorCommandNavigateTargetResponseID
        ZGMTR_DEPRECATED("Please use ZGMTRCommandIDTypeClusterTargetNavigatorCommandNavigateTargetResponseID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x00000001,

    // Cluster TargetNavigator commands
    ZGMTRCommandIDTypeClusterTargetNavigatorCommandNavigateTargetID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000000,
    ZGMTRCommandIDTypeClusterTargetNavigatorCommandNavigateTargetResponseID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000001,

    // Cluster MediaPlayback deprecated command id names
    ZGMTRClusterMediaPlaybackCommandPlayID
        ZGMTR_DEPRECATED("Please use ZGMTRCommandIDTypeClusterMediaPlaybackCommandPlayID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x00000000,
    ZGMTRClusterMediaPlaybackCommandPauseID
        ZGMTR_DEPRECATED("Please use ZGMTRCommandIDTypeClusterMediaPlaybackCommandPauseID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x00000001,
    ZGMTRClusterMediaPlaybackCommandStopPlaybackID
        ZGMTR_DEPRECATED("Please use ZGMTRCommandIDTypeClusterMediaPlaybackCommandStopID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x00000002,
    ZGMTRClusterMediaPlaybackCommandStartOverID
        ZGMTR_DEPRECATED("Please use ZGMTRCommandIDTypeClusterMediaPlaybackCommandStartOverID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x00000003,
    ZGMTRClusterMediaPlaybackCommandPreviousID
        ZGMTR_DEPRECATED("Please use ZGMTRCommandIDTypeClusterMediaPlaybackCommandPreviousID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x00000004,
    ZGMTRClusterMediaPlaybackCommandNextID
        ZGMTR_DEPRECATED("Please use ZGMTRCommandIDTypeClusterMediaPlaybackCommandNextID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x00000005,
    ZGMTRClusterMediaPlaybackCommandRewindID
        ZGMTR_DEPRECATED("Please use ZGMTRCommandIDTypeClusterMediaPlaybackCommandRewindID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x00000006,
    ZGMTRClusterMediaPlaybackCommandFastForwardID
        ZGMTR_DEPRECATED("Please use ZGMTRCommandIDTypeClusterMediaPlaybackCommandFastForwardID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x00000007,
    ZGMTRClusterMediaPlaybackCommandSkipForwardID
        ZGMTR_DEPRECATED("Please use ZGMTRCommandIDTypeClusterMediaPlaybackCommandSkipForwardID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x00000008,
    ZGMTRClusterMediaPlaybackCommandSkipBackwardID
        ZGMTR_DEPRECATED("Please use ZGMTRCommandIDTypeClusterMediaPlaybackCommandSkipBackwardID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x00000009,
    ZGMTRClusterMediaPlaybackCommandPlaybackResponseID
        ZGMTR_DEPRECATED("Please use ZGMTRCommandIDTypeClusterMediaPlaybackCommandPlaybackResponseID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x0000000A,
    ZGMTRClusterMediaPlaybackCommandSeekID
        ZGMTR_DEPRECATED("Please use ZGMTRCommandIDTypeClusterMediaPlaybackCommandSeekID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x0000000B,

    // Cluster MediaPlayback commands
    ZGMTRCommandIDTypeClusterMediaPlaybackCommandPlayID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000000,
    ZGMTRCommandIDTypeClusterMediaPlaybackCommandPauseID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000001,
    ZGMTRCommandIDTypeClusterMediaPlaybackCommandStopID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000002,
    ZGMTRCommandIDTypeClusterMediaPlaybackCommandStartOverID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000003,
    ZGMTRCommandIDTypeClusterMediaPlaybackCommandPreviousID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000004,
    ZGMTRCommandIDTypeClusterMediaPlaybackCommandNextID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000005,
    ZGMTRCommandIDTypeClusterMediaPlaybackCommandRewindID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000006,
    ZGMTRCommandIDTypeClusterMediaPlaybackCommandFastForwardID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000007,
    ZGMTRCommandIDTypeClusterMediaPlaybackCommandSkipForwardID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000008,
    ZGMTRCommandIDTypeClusterMediaPlaybackCommandSkipBackwardID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000009,
    ZGMTRCommandIDTypeClusterMediaPlaybackCommandPlaybackResponseID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x0000000A,
    ZGMTRCommandIDTypeClusterMediaPlaybackCommandSeekID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x0000000B,
    ZGMTRCommandIDTypeClusterMediaPlaybackCommandActivateAudioTrackID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = 0x0000000C,
    ZGMTRCommandIDTypeClusterMediaPlaybackCommandActivateTextTrackID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = 0x0000000D,
    ZGMTRCommandIDTypeClusterMediaPlaybackCommandDeactivateTextTrackID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = 0x0000000E,

    // Cluster MediaInput deprecated command id names
    ZGMTRClusterMediaInputCommandSelectInputID
        ZGMTR_DEPRECATED("Please use ZGMTRCommandIDTypeClusterMediaInputCommandSelectInputID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x00000000,
    ZGMTRClusterMediaInputCommandShowInputStatusID
        ZGMTR_DEPRECATED("Please use ZGMTRCommandIDTypeClusterMediaInputCommandShowInputStatusID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x00000001,
    ZGMTRClusterMediaInputCommandHideInputStatusID
        ZGMTR_DEPRECATED("Please use ZGMTRCommandIDTypeClusterMediaInputCommandHideInputStatusID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x00000002,
    ZGMTRClusterMediaInputCommandRenameInputID
        ZGMTR_DEPRECATED("Please use ZGMTRCommandIDTypeClusterMediaInputCommandRenameInputID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x00000003,

    // Cluster MediaInput commands
    ZGMTRCommandIDTypeClusterMediaInputCommandSelectInputID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000000,
    ZGMTRCommandIDTypeClusterMediaInputCommandShowInputStatusID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000001,
    ZGMTRCommandIDTypeClusterMediaInputCommandHideInputStatusID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000002,
    ZGMTRCommandIDTypeClusterMediaInputCommandRenameInputID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000003,

    // Cluster LowPower deprecated command id names
    ZGMTRClusterLowPowerCommandSleepID
        ZGMTR_DEPRECATED("Please use ZGMTRCommandIDTypeClusterLowPowerCommandSleepID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x00000000,

    // Cluster LowPower commands
    ZGMTRCommandIDTypeClusterLowPowerCommandSleepID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000000,

    // Cluster KeypadInput deprecated command id names
    ZGMTRClusterKeypadInputCommandSendKeyID
        ZGMTR_DEPRECATED("Please use ZGMTRCommandIDTypeClusterKeypadInputCommandSendKeyID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x00000000,
    ZGMTRClusterKeypadInputCommandSendKeyResponseID
        ZGMTR_DEPRECATED("Please use ZGMTRCommandIDTypeClusterKeypadInputCommandSendKeyResponseID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x00000001,

    // Cluster KeypadInput commands
    ZGMTRCommandIDTypeClusterKeypadInputCommandSendKeyID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000000,
    ZGMTRCommandIDTypeClusterKeypadInputCommandSendKeyResponseID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000001,

    // Cluster ContentLauncher deprecated command id names
    ZGMTRClusterContentLauncherCommandLaunchContentID
        ZGMTR_DEPRECATED("Please use ZGMTRCommandIDTypeClusterContentLauncherCommandLaunchContentID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x00000000,
    ZGMTRClusterContentLauncherCommandLaunchURLID
        ZGMTR_DEPRECATED("Please use ZGMTRCommandIDTypeClusterContentLauncherCommandLaunchURLID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x00000001,
    ZGMTRClusterContentLauncherCommandLaunchResponseID
        ZGMTR_DEPRECATED("Please use ZGMTRCommandIDTypeClusterContentLauncherCommandLauncherResponseID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x00000002,

    // Cluster ContentLauncher commands
    ZGMTRCommandIDTypeClusterContentLauncherCommandLaunchContentID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000000,
    ZGMTRCommandIDTypeClusterContentLauncherCommandLaunchURLID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000001,
    ZGMTRCommandIDTypeClusterContentLauncherCommandLauncherResponseID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000002,
    ZGMTRCommandIDTypeClusterContentLauncherCommandContentReplicationRequestID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000003,
    ZGMTRCommandIDTypeClusterContentLauncherCommandContentReplicationResponseID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000004,
    ZGMTRCommandIDTypeClusterContentLauncherCommandPlayPresetID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000005,

    // Cluster AudioOutput deprecated command id names
    ZGMTRClusterAudioOutputCommandSelectOutputID
        ZGMTR_DEPRECATED("Please use ZGMTRCommandIDTypeClusterAudioOutputCommandSelectOutputID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x00000000,
    ZGMTRClusterAudioOutputCommandRenameOutputID
        ZGMTR_DEPRECATED("Please use ZGMTRCommandIDTypeClusterAudioOutputCommandRenameOutputID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x00000001,

    // Cluster AudioOutput commands
    ZGMTRCommandIDTypeClusterAudioOutputCommandSelectOutputID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000000,
    ZGMTRCommandIDTypeClusterAudioOutputCommandRenameOutputID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000001,

    // Cluster ApplicationLauncher deprecated command id names
    ZGMTRClusterApplicationLauncherCommandLaunchAppID
        ZGMTR_DEPRECATED("Please use ZGMTRCommandIDTypeClusterApplicationLauncherCommandLaunchAppID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x00000000,
    ZGMTRClusterApplicationLauncherCommandStopAppID
        ZGMTR_DEPRECATED("Please use ZGMTRCommandIDTypeClusterApplicationLauncherCommandStopAppID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x00000001,
    ZGMTRClusterApplicationLauncherCommandHideAppID
        ZGMTR_DEPRECATED("Please use ZGMTRCommandIDTypeClusterApplicationLauncherCommandHideAppID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x00000002,
    ZGMTRClusterApplicationLauncherCommandLauncherResponseID
        ZGMTR_DEPRECATED("Please use ZGMTRCommandIDTypeClusterApplicationLauncherCommandLauncherResponseID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x00000003,

    // Cluster ApplicationLauncher commands
    ZGMTRCommandIDTypeClusterApplicationLauncherCommandLaunchAppID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000000,
    ZGMTRCommandIDTypeClusterApplicationLauncherCommandStopAppID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000001,
    ZGMTRCommandIDTypeClusterApplicationLauncherCommandHideAppID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000002,
    ZGMTRCommandIDTypeClusterApplicationLauncherCommandLauncherResponseID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000003,

    // Cluster AccountLogin deprecated command id names
    ZGMTRClusterAccountLoginCommandGetSetupPINID
        ZGMTR_DEPRECATED("Please use ZGMTRCommandIDTypeClusterAccountLoginCommandGetSetupPINID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x00000000,
    ZGMTRClusterAccountLoginCommandGetSetupPINResponseID
        ZGMTR_DEPRECATED("Please use ZGMTRCommandIDTypeClusterAccountLoginCommandGetSetupPINResponseID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x00000001,
    ZGMTRClusterAccountLoginCommandLoginID
        ZGMTR_DEPRECATED("Please use ZGMTRCommandIDTypeClusterAccountLoginCommandLoginID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x00000002,
    ZGMTRClusterAccountLoginCommandLogoutID
        ZGMTR_DEPRECATED("Please use ZGMTRCommandIDTypeClusterAccountLoginCommandLogoutID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x00000003,

    // Cluster AccountLogin commands
    ZGMTRCommandIDTypeClusterAccountLoginCommandGetSetupPINID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000000,
    ZGMTRCommandIDTypeClusterAccountLoginCommandGetSetupPINResponseID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000001,
    ZGMTRCommandIDTypeClusterAccountLoginCommandLoginID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000002,
    ZGMTRCommandIDTypeClusterAccountLoginCommandLogoutID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000003,

    // Cluster ContentControl commands
    ZGMTRCommandIDTypeClusterContentControlCommandUpdatePINID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000000,
    ZGMTRCommandIDTypeClusterContentControlCommandResetPINID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000001,
    ZGMTRCommandIDTypeClusterContentControlCommandResetPINResponseID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000002,
    ZGMTRCommandIDTypeClusterContentControlCommandEnableID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000003,
    ZGMTRCommandIDTypeClusterContentControlCommandDisableID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000004,
    ZGMTRCommandIDTypeClusterContentControlCommandAddBonusTimeID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000005,
    ZGMTRCommandIDTypeClusterContentControlCommandSetScreenDailyTimeID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000006,
    ZGMTRCommandIDTypeClusterContentControlCommandBlockUnratedContentID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000007,
    ZGMTRCommandIDTypeClusterContentControlCommandUnblockUnratedContentID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000008,
    ZGMTRCommandIDTypeClusterContentControlCommandSetOnDemandRatingThresholdID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000009,
    ZGMTRCommandIDTypeClusterContentControlCommandSetScheduledContentRatingThresholdID ZGMTR_PROVISIONALLY_AVAILABLE = 0x0000000A,
    ZGMTRCommandIDTypeClusterContentControlCommandAddBlockChannelsID ZGMTR_PROVISIONALLY_AVAILABLE = 0x0000000B,
    ZGMTRCommandIDTypeClusterContentControlCommandRemoveBlockChannelsID ZGMTR_PROVISIONALLY_AVAILABLE = 0x0000000C,
    ZGMTRCommandIDTypeClusterContentControlCommandAddBlockApplicationsID ZGMTR_PROVISIONALLY_AVAILABLE = 0x0000000D,
    ZGMTRCommandIDTypeClusterContentControlCommandRemoveBlockApplicationsID ZGMTR_PROVISIONALLY_AVAILABLE = 0x0000000E,
    ZGMTRCommandIDTypeClusterContentControlCommandSetBlockContentTimeWindowID ZGMTR_PROVISIONALLY_AVAILABLE = 0x0000000F,
    ZGMTRCommandIDTypeClusterContentControlCommandRemoveBlockContentTimeWindowID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000010,

    // Cluster ContentAppObserver commands
    ZGMTRCommandIDTypeClusterContentAppObserverCommandContentAppMessageID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = 0x00000000,
    ZGMTRCommandIDTypeClusterContentAppObserverCommandContentAppMessageResponseID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = 0x00000001,

    // Cluster MediaFileManagement commands
    ZGMTRCommandIDTypeClusterMediaFileManagementCommandAddFileID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000000,
    ZGMTRCommandIDTypeClusterMediaFileManagementCommandAddFileResponseID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000001,
    ZGMTRCommandIDTypeClusterMediaFileManagementCommandDeleteFileID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000002,
    ZGMTRCommandIDTypeClusterMediaFileManagementCommandRequestSharedFilesID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000003,
    ZGMTRCommandIDTypeClusterMediaFileManagementCommandGetSharedFileID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000004,
    ZGMTRCommandIDTypeClusterMediaFileManagementCommandGetSharedFileResponseID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000005,
    ZGMTRCommandIDTypeClusterMediaFileManagementCommandOfferFileID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000006,

    // Cluster AudioControl commands
    ZGMTRCommandIDTypeClusterAudioControlCommandMuteID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000000,
    ZGMTRCommandIDTypeClusterAudioControlCommandUnmuteID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000001,
    ZGMTRCommandIDTypeClusterAudioControlCommandToggleMutedID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000002,
    ZGMTRCommandIDTypeClusterAudioControlCommandSetVolumeID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000003,
    ZGMTRCommandIDTypeClusterAudioControlCommandIncreaseVolumeID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000004,
    ZGMTRCommandIDTypeClusterAudioControlCommandDecreaseVolumeID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000005,

    // Cluster ZoneManagement commands
    ZGMTRCommandIDTypeClusterZoneManagementCommandCreateTwoDCartesianZoneID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000000,
    ZGMTRCommandIDTypeClusterZoneManagementCommandCreateTwoDCartesianZoneResponseID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000001,
    ZGMTRCommandIDTypeClusterZoneManagementCommandUpdateTwoDCartesianZoneID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000002,
    ZGMTRCommandIDTypeClusterZoneManagementCommandRemoveZoneID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000003,
    ZGMTRCommandIDTypeClusterZoneManagementCommandCreateOrUpdateTriggerID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000004,
    ZGMTRCommandIDTypeClusterZoneManagementCommandRemoveTriggerID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000005,

    // Cluster CameraAVStreamManagement commands
    ZGMTRCommandIDTypeClusterCameraAVStreamManagementCommandAudioStreamAllocateID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000000,
    ZGMTRCommandIDTypeClusterCameraAVStreamManagementCommandAudioStreamAllocateResponseID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000001,
    ZGMTRCommandIDTypeClusterCameraAVStreamManagementCommandAudioStreamDeallocateID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000002,
    ZGMTRCommandIDTypeClusterCameraAVStreamManagementCommandVideoStreamAllocateID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000003,
    ZGMTRCommandIDTypeClusterCameraAVStreamManagementCommandVideoStreamAllocateResponseID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000004,
    ZGMTRCommandIDTypeClusterCameraAVStreamManagementCommandVideoStreamModifyID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000005,
    ZGMTRCommandIDTypeClusterCameraAVStreamManagementCommandVideoStreamDeallocateID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000006,
    ZGMTRCommandIDTypeClusterCameraAVStreamManagementCommandSnapshotStreamAllocateID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000007,
    ZGMTRCommandIDTypeClusterCameraAVStreamManagementCommandSnapshotStreamAllocateResponseID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000008,
    ZGMTRCommandIDTypeClusterCameraAVStreamManagementCommandSnapshotStreamModifyID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000009,
    ZGMTRCommandIDTypeClusterCameraAVStreamManagementCommandSnapshotStreamDeallocateID ZGMTR_PROVISIONALLY_AVAILABLE = 0x0000000A,
    ZGMTRCommandIDTypeClusterCameraAVStreamManagementCommandSetStreamPrioritiesID ZGMTR_PROVISIONALLY_AVAILABLE = 0x0000000B,
    ZGMTRCommandIDTypeClusterCameraAVStreamManagementCommandCaptureSnapshotID ZGMTR_PROVISIONALLY_AVAILABLE = 0x0000000C,
    ZGMTRCommandIDTypeClusterCameraAVStreamManagementCommandCaptureSnapshotResponseID ZGMTR_PROVISIONALLY_AVAILABLE = 0x0000000D,

    // Cluster CameraAVSettingsUserLevelManagement commands
    ZGMTRCommandIDTypeClusterCameraAVSettingsUserLevelManagementCommandMPTZSetPositionID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000000,
    ZGMTRCommandIDTypeClusterCameraAVSettingsUserLevelManagementCommandMPTZRelativeMoveID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000001,
    ZGMTRCommandIDTypeClusterCameraAVSettingsUserLevelManagementCommandMPTZMoveToPresetID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000002,
    ZGMTRCommandIDTypeClusterCameraAVSettingsUserLevelManagementCommandMPTZSavePresetID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000003,
    ZGMTRCommandIDTypeClusterCameraAVSettingsUserLevelManagementCommandMPTZRemovePresetID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000004,
    ZGMTRCommandIDTypeClusterCameraAVSettingsUserLevelManagementCommandDPTZSetViewportID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000005,
    ZGMTRCommandIDTypeClusterCameraAVSettingsUserLevelManagementCommandDPTZRelativeMoveID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000006,

    // Cluster WebRTCTransportProvider commands
    ZGMTRCommandIDTypeClusterWebRTCTransportProviderCommandSolicitOfferID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000000,
    ZGMTRCommandIDTypeClusterWebRTCTransportProviderCommandSolicitOfferResponseID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000001,
    ZGMTRCommandIDTypeClusterWebRTCTransportProviderCommandProvideOfferID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000002,
    ZGMTRCommandIDTypeClusterWebRTCTransportProviderCommandProvideOfferResponseID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000003,
    ZGMTRCommandIDTypeClusterWebRTCTransportProviderCommandProvideAnswerID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000004,
    ZGMTRCommandIDTypeClusterWebRTCTransportProviderCommandProvideICECandidatesID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000005,
    ZGMTRCommandIDTypeClusterWebRTCTransportProviderCommandEndSessionID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000006,

    // Cluster WebRTCTransportRequestor commands
    ZGMTRCommandIDTypeClusterWebRTCTransportRequestorCommandOfferID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000000,
    ZGMTRCommandIDTypeClusterWebRTCTransportRequestorCommandAnswerID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000001,
    ZGMTRCommandIDTypeClusterWebRTCTransportRequestorCommandICECandidatesID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000002,
    ZGMTRCommandIDTypeClusterWebRTCTransportRequestorCommandEndID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000003,

    // Cluster PushAVStreamTransport commands
    ZGMTRCommandIDTypeClusterPushAVStreamTransportCommandAllocatePushTransportID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000000,
    ZGMTRCommandIDTypeClusterPushAVStreamTransportCommandAllocatePushTransportResponseID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000001,
    ZGMTRCommandIDTypeClusterPushAVStreamTransportCommandDeallocatePushTransportID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000002,
    ZGMTRCommandIDTypeClusterPushAVStreamTransportCommandModifyPushTransportID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000003,
    ZGMTRCommandIDTypeClusterPushAVStreamTransportCommandSetTransportStatusID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000004,
    ZGMTRCommandIDTypeClusterPushAVStreamTransportCommandManuallyTriggerTransportID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000005,
    ZGMTRCommandIDTypeClusterPushAVStreamTransportCommandFindTransportID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000006,
    ZGMTRCommandIDTypeClusterPushAVStreamTransportCommandFindTransportResponseID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000007,

    // Cluster Chime commands
    ZGMTRCommandIDTypeClusterChimeCommandPlayChimeSoundID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000000,

    // Cluster AVAnalysis commands
    ZGMTRCommandIDTypeClusterAVAnalysisCommandEnableContextTriggersID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000000,
    ZGMTRCommandIDTypeClusterAVAnalysisCommandDisableContextTriggersID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000001,
    ZGMTRCommandIDTypeClusterAVAnalysisCommandEstablishAnalysisStreamID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000002,
    ZGMTRCommandIDTypeClusterAVAnalysisCommandEstablishAnalysisStreamResponseID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000003,
    ZGMTRCommandIDTypeClusterAVAnalysisCommandActivateAnalysisStreamID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000004,
    ZGMTRCommandIDTypeClusterAVAnalysisCommandDeactivateAnalysisStreamID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000005,
    ZGMTRCommandIDTypeClusterAVAnalysisCommandRemoveAnalysisStreamID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000006,

    // Cluster CommodityTariff commands
    ZGMTRCommandIDTypeClusterCommodityTariffCommandGetTariffComponentID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000000,
    ZGMTRCommandIDTypeClusterCommodityTariffCommandGetTariffComponentResponseID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000000,
    ZGMTRCommandIDTypeClusterCommodityTariffCommandGetDayEntryID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000001,
    ZGMTRCommandIDTypeClusterCommodityTariffCommandGetDayEntryResponseID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000001,

    // Cluster CommissionerControl commands
    ZGMTRCommandIDTypeClusterCommissionerControlCommandRequestCommissioningApprovalID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = 0x00000000,
    ZGMTRCommandIDTypeClusterCommissionerControlCommandCommissionNodeID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = 0x00000001,
    ZGMTRCommandIDTypeClusterCommissionerControlCommandReverseOpenCommissioningWindowID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = 0x00000002,

    // Cluster JointFabricDatastore commands
    ZGMTRCommandIDTypeClusterJointFabricDatastoreCommandAddKeySetID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000000,
    ZGMTRCommandIDTypeClusterJointFabricDatastoreCommandUpdateKeySetID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000001,
    ZGMTRCommandIDTypeClusterJointFabricDatastoreCommandRemoveKeySetID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000002,
    ZGMTRCommandIDTypeClusterJointFabricDatastoreCommandAddGroupID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000003,
    ZGMTRCommandIDTypeClusterJointFabricDatastoreCommandUpdateGroupID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000004,
    ZGMTRCommandIDTypeClusterJointFabricDatastoreCommandRemoveGroupID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000005,
    ZGMTRCommandIDTypeClusterJointFabricDatastoreCommandAddAdminID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000006,
    ZGMTRCommandIDTypeClusterJointFabricDatastoreCommandUpdateAdminID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000007,
    ZGMTRCommandIDTypeClusterJointFabricDatastoreCommandRemoveAdminID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000008,
    ZGMTRCommandIDTypeClusterJointFabricDatastoreCommandAddPendingNodeID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000009,
    ZGMTRCommandIDTypeClusterJointFabricDatastoreCommandRefreshNodeID ZGMTR_PROVISIONALLY_AVAILABLE = 0x0000000A,
    ZGMTRCommandIDTypeClusterJointFabricDatastoreCommandUpdateNodeID ZGMTR_PROVISIONALLY_AVAILABLE = 0x0000000B,
    ZGMTRCommandIDTypeClusterJointFabricDatastoreCommandRemoveNodeID ZGMTR_PROVISIONALLY_AVAILABLE = 0x0000000C,
    ZGMTRCommandIDTypeClusterJointFabricDatastoreCommandUpdateEndpointForNodeID ZGMTR_PROVISIONALLY_AVAILABLE = 0x0000000D,
    ZGMTRCommandIDTypeClusterJointFabricDatastoreCommandAddGroupIDToEndpointForNodeID ZGMTR_PROVISIONALLY_AVAILABLE = 0x0000000E,
    ZGMTRCommandIDTypeClusterJointFabricDatastoreCommandRemoveGroupIDFromEndpointForNodeID ZGMTR_PROVISIONALLY_AVAILABLE = 0x0000000F,
    ZGMTRCommandIDTypeClusterJointFabricDatastoreCommandAddBindingToEndpointForNodeID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000010,
    ZGMTRCommandIDTypeClusterJointFabricDatastoreCommandRemoveBindingFromEndpointForNodeID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000011,
    ZGMTRCommandIDTypeClusterJointFabricDatastoreCommandAddACLToNodeID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000012,
    ZGMTRCommandIDTypeClusterJointFabricDatastoreCommandRemoveACLFromNodeID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000013,

    // Cluster JointFabricAdministrator commands
    ZGMTRCommandIDTypeClusterJointFabricAdministratorCommandICACCSRRequestID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000000,
    ZGMTRCommandIDTypeClusterJointFabricAdministratorCommandICACCSRResponseID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000001,
    ZGMTRCommandIDTypeClusterJointFabricAdministratorCommandAddICACID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000002,
    ZGMTRCommandIDTypeClusterJointFabricAdministratorCommandICACResponseID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000003,
    ZGMTRCommandIDTypeClusterJointFabricAdministratorCommandOpenJointCommissioningWindowID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000004,
    ZGMTRCommandIDTypeClusterJointFabricAdministratorCommandTransferAnchorRequestID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000005,
    ZGMTRCommandIDTypeClusterJointFabricAdministratorCommandTransferAnchorResponseID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000006,
    ZGMTRCommandIDTypeClusterJointFabricAdministratorCommandTransferAnchorCompleteID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000007,
    ZGMTRCommandIDTypeClusterJointFabricAdministratorCommandAnnounceJointFabricAdministratorID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000008,

    // Cluster TLSCertificateManagement commands
    ZGMTRCommandIDTypeClusterTLSCertificateManagementCommandProvisionRootCertificateID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000000,
    ZGMTRCommandIDTypeClusterTLSCertificateManagementCommandProvisionRootCertificateResponseID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000001,
    ZGMTRCommandIDTypeClusterTLSCertificateManagementCommandFindRootCertificateID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000002,
    ZGMTRCommandIDTypeClusterTLSCertificateManagementCommandFindRootCertificateResponseID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000003,
    ZGMTRCommandIDTypeClusterTLSCertificateManagementCommandLookupRootCertificateID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000004,
    ZGMTRCommandIDTypeClusterTLSCertificateManagementCommandLookupRootCertificateResponseID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000005,
    ZGMTRCommandIDTypeClusterTLSCertificateManagementCommandRemoveRootCertificateID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000006,
    ZGMTRCommandIDTypeClusterTLSCertificateManagementCommandClientCSRID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000007,
    ZGMTRCommandIDTypeClusterTLSCertificateManagementCommandClientCSRResponseID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000008,
    ZGMTRCommandIDTypeClusterTLSCertificateManagementCommandProvisionClientCertificateID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000009,
    ZGMTRCommandIDTypeClusterTLSCertificateManagementCommandFindClientCertificateID ZGMTR_PROVISIONALLY_AVAILABLE = 0x0000000A,
    ZGMTRCommandIDTypeClusterTLSCertificateManagementCommandFindClientCertificateResponseID ZGMTR_PROVISIONALLY_AVAILABLE = 0x0000000B,
    ZGMTRCommandIDTypeClusterTLSCertificateManagementCommandLookupClientCertificateID ZGMTR_PROVISIONALLY_AVAILABLE = 0x0000000C,
    ZGMTRCommandIDTypeClusterTLSCertificateManagementCommandLookupClientCertificateResponseID ZGMTR_PROVISIONALLY_AVAILABLE = 0x0000000D,
    ZGMTRCommandIDTypeClusterTLSCertificateManagementCommandRemoveClientCertificateID ZGMTR_PROVISIONALLY_AVAILABLE = 0x0000000E,

    // Cluster TLSClientManagement commands
    ZGMTRCommandIDTypeClusterTLSClientManagementCommandProvisionEndpointID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000000,
    ZGMTRCommandIDTypeClusterTLSClientManagementCommandProvisionEndpointResponseID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000001,
    ZGMTRCommandIDTypeClusterTLSClientManagementCommandFindEndpointID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000002,
    ZGMTRCommandIDTypeClusterTLSClientManagementCommandFindEndpointResponseID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000003,
    ZGMTRCommandIDTypeClusterTLSClientManagementCommandRemoveEndpointID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000004,

    // Cluster TestCluster deprecated command id names
    ZGMTRClusterTestClusterCommandTestID
        ZGMTR_DEPRECATED("Please use ZGMTRCommandIDTypeClusterUnitTestingCommandTestID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x00000000,
    ZGMTRClusterTestClusterCommandTestSpecificResponseID
        ZGMTR_DEPRECATED("Please use ZGMTRCommandIDTypeClusterUnitTestingCommandTestSpecificResponseID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x00000000,
    ZGMTRClusterTestClusterCommandTestNotHandledID
        ZGMTR_DEPRECATED("Please use ZGMTRCommandIDTypeClusterUnitTestingCommandTestNotHandledID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x00000001,
    ZGMTRClusterTestClusterCommandTestAddArgumentsResponseID
        ZGMTR_DEPRECATED("Please use ZGMTRCommandIDTypeClusterUnitTestingCommandTestAddArgumentsResponseID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x00000001,
    ZGMTRClusterTestClusterCommandTestSpecificID
        ZGMTR_DEPRECATED("Please use ZGMTRCommandIDTypeClusterUnitTestingCommandTestSpecificID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x00000002,
    ZGMTRClusterTestClusterCommandTestSimpleArgumentResponseID
        ZGMTR_DEPRECATED("Please use ZGMTRCommandIDTypeClusterUnitTestingCommandTestSimpleArgumentResponseID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x00000002,
    ZGMTRClusterTestClusterCommandTestUnknownCommandID
        ZGMTR_DEPRECATED("Please use ZGMTRCommandIDTypeClusterUnitTestingCommandTestUnknownCommandID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x00000003,
    ZGMTRClusterTestClusterCommandTestStructArrayArgumentResponseID
        ZGMTR_DEPRECATED("Please use ZGMTRCommandIDTypeClusterUnitTestingCommandTestStructArrayArgumentResponseID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x00000003,
    ZGMTRClusterTestClusterCommandTestAddArgumentsID
        ZGMTR_DEPRECATED("Please use ZGMTRCommandIDTypeClusterUnitTestingCommandTestAddArgumentsID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x00000004,
    ZGMTRClusterTestClusterCommandTestListInt8UReverseResponseID
        ZGMTR_DEPRECATED("Please use ZGMTRCommandIDTypeClusterUnitTestingCommandTestListInt8UReverseResponseID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x00000004,
    ZGMTRClusterTestClusterCommandTestSimpleArgumentRequestID
        ZGMTR_DEPRECATED("Please use ZGMTRCommandIDTypeClusterUnitTestingCommandTestSimpleArgumentRequestID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x00000005,
    ZGMTRClusterTestClusterCommandTestEnumsResponseID
        ZGMTR_DEPRECATED("Please use ZGMTRCommandIDTypeClusterUnitTestingCommandTestEnumsResponseID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x00000005,
    ZGMTRClusterTestClusterCommandTestStructArrayArgumentRequestID
        ZGMTR_DEPRECATED("Please use ZGMTRCommandIDTypeClusterUnitTestingCommandTestStructArrayArgumentRequestID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x00000006,
    ZGMTRClusterTestClusterCommandTestNullableOptionalResponseID
        ZGMTR_DEPRECATED("Please use ZGMTRCommandIDTypeClusterUnitTestingCommandTestNullableOptionalResponseID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x00000006,
    ZGMTRClusterTestClusterCommandTestStructArgumentRequestID
        ZGMTR_DEPRECATED("Please use ZGMTRCommandIDTypeClusterUnitTestingCommandTestStructArgumentRequestID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x00000007,
    ZGMTRClusterTestClusterCommandTestComplexNullableOptionalResponseID
        ZGMTR_DEPRECATED("Please use ZGMTRCommandIDTypeClusterUnitTestingCommandTestComplexNullableOptionalResponseID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x00000007,
    ZGMTRClusterTestClusterCommandTestNestedStructArgumentRequestID
        ZGMTR_DEPRECATED("Please use ZGMTRCommandIDTypeClusterUnitTestingCommandTestNestedStructArgumentRequestID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x00000008,
    ZGMTRClusterTestClusterCommandBooleanResponseID
        ZGMTR_DEPRECATED("Please use ZGMTRCommandIDTypeClusterUnitTestingCommandBooleanResponseID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x00000008,
    ZGMTRClusterTestClusterCommandTestListStructArgumentRequestID
        ZGMTR_DEPRECATED("Please use ZGMTRCommandIDTypeClusterUnitTestingCommandTestListStructArgumentRequestID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x00000009,
    ZGMTRClusterTestClusterCommandSimpleStructResponseID
        ZGMTR_DEPRECATED("Please use ZGMTRCommandIDTypeClusterUnitTestingCommandSimpleStructResponseID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x00000009,
    ZGMTRClusterTestClusterCommandTestListInt8UArgumentRequestID
        ZGMTR_DEPRECATED("Please use ZGMTRCommandIDTypeClusterUnitTestingCommandTestListInt8UArgumentRequestID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x0000000A,
    ZGMTRClusterTestClusterCommandTestEmitTestEventResponseID
        ZGMTR_DEPRECATED("Please use ZGMTRCommandIDTypeClusterUnitTestingCommandTestEmitTestEventResponseID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x0000000A,
    ZGMTRClusterTestClusterCommandTestNestedStructListArgumentRequestID
        ZGMTR_DEPRECATED("Please use ZGMTRCommandIDTypeClusterUnitTestingCommandTestNestedStructListArgumentRequestID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x0000000B,
    ZGMTRClusterTestClusterCommandTestEmitTestFabricScopedEventResponseID
        ZGMTR_DEPRECATED("Please use ZGMTRCommandIDTypeClusterUnitTestingCommandTestEmitTestFabricScopedEventResponseID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x0000000B,
    ZGMTRClusterTestClusterCommandTestListNestedStructListArgumentRequestID
        ZGMTR_DEPRECATED("Please use ZGMTRCommandIDTypeClusterUnitTestingCommandTestListNestedStructListArgumentRequestID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x0000000C,
    ZGMTRClusterTestClusterCommandTestListInt8UReverseRequestID
        ZGMTR_DEPRECATED("Please use ZGMTRCommandIDTypeClusterUnitTestingCommandTestListInt8UReverseRequestID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x0000000D,
    ZGMTRClusterTestClusterCommandTestEnumsRequestID
        ZGMTR_DEPRECATED("Please use ZGMTRCommandIDTypeClusterUnitTestingCommandTestEnumsRequestID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x0000000E,
    ZGMTRClusterTestClusterCommandTestNullableOptionalRequestID
        ZGMTR_DEPRECATED("Please use ZGMTRCommandIDTypeClusterUnitTestingCommandTestNullableOptionalRequestID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x0000000F,
    ZGMTRClusterTestClusterCommandTestComplexNullableOptionalRequestID
        ZGMTR_DEPRECATED("Please use ZGMTRCommandIDTypeClusterUnitTestingCommandTestComplexNullableOptionalRequestID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x00000010,
    ZGMTRClusterTestClusterCommandSimpleStructEchoRequestID
        ZGMTR_DEPRECATED("Please use ZGMTRCommandIDTypeClusterUnitTestingCommandSimpleStructEchoRequestID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x00000011,
    ZGMTRClusterTestClusterCommandTimedInvokeRequestID
        ZGMTR_DEPRECATED("Please use ZGMTRCommandIDTypeClusterUnitTestingCommandTimedInvokeRequestID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x00000012,
    ZGMTRClusterTestClusterCommandTestSimpleOptionalArgumentRequestID
        ZGMTR_DEPRECATED("Please use ZGMTRCommandIDTypeClusterUnitTestingCommandTestSimpleOptionalArgumentRequestID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x00000013,
    ZGMTRClusterTestClusterCommandTestEmitTestEventRequestID
        ZGMTR_DEPRECATED("Please use ZGMTRCommandIDTypeClusterUnitTestingCommandTestEmitTestEventRequestID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x00000014,
    ZGMTRClusterTestClusterCommandTestEmitTestFabricScopedEventRequestID
        ZGMTR_DEPRECATED("Please use ZGMTRCommandIDTypeClusterUnitTestingCommandTestEmitTestFabricScopedEventRequestID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x00000015,

    // Cluster UnitTesting commands
    ZGMTRCommandIDTypeClusterUnitTestingCommandTestID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000000,
    ZGMTRCommandIDTypeClusterUnitTestingCommandTestSpecificResponseID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000000,
    ZGMTRCommandIDTypeClusterUnitTestingCommandTestNotHandledID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000001,
    ZGMTRCommandIDTypeClusterUnitTestingCommandTestAddArgumentsResponseID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000001,
    ZGMTRCommandIDTypeClusterUnitTestingCommandTestSpecificID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000002,
    ZGMTRCommandIDTypeClusterUnitTestingCommandTestSimpleArgumentResponseID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000002,
    ZGMTRCommandIDTypeClusterUnitTestingCommandTestUnknownCommandID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000003,
    ZGMTRCommandIDTypeClusterUnitTestingCommandTestStructArrayArgumentResponseID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000003,
    ZGMTRCommandIDTypeClusterUnitTestingCommandTestAddArgumentsID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000004,
    ZGMTRCommandIDTypeClusterUnitTestingCommandTestListInt8UReverseResponseID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000004,
    ZGMTRCommandIDTypeClusterUnitTestingCommandTestSimpleArgumentRequestID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000005,
    ZGMTRCommandIDTypeClusterUnitTestingCommandTestEnumsResponseID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000005,
    ZGMTRCommandIDTypeClusterUnitTestingCommandTestStructArrayArgumentRequestID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000006,
    ZGMTRCommandIDTypeClusterUnitTestingCommandTestNullableOptionalResponseID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000006,
    ZGMTRCommandIDTypeClusterUnitTestingCommandTestStructArgumentRequestID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000007,
    ZGMTRCommandIDTypeClusterUnitTestingCommandTestComplexNullableOptionalResponseID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000007,
    ZGMTRCommandIDTypeClusterUnitTestingCommandTestNestedStructArgumentRequestID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000008,
    ZGMTRCommandIDTypeClusterUnitTestingCommandBooleanResponseID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000008,
    ZGMTRCommandIDTypeClusterUnitTestingCommandTestListStructArgumentRequestID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000009,
    ZGMTRCommandIDTypeClusterUnitTestingCommandSimpleStructResponseID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000009,
    ZGMTRCommandIDTypeClusterUnitTestingCommandTestListInt8UArgumentRequestID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x0000000A,
    ZGMTRCommandIDTypeClusterUnitTestingCommandTestEmitTestEventResponseID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x0000000A,
    ZGMTRCommandIDTypeClusterUnitTestingCommandTestNestedStructListArgumentRequestID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x0000000B,
    ZGMTRCommandIDTypeClusterUnitTestingCommandTestEmitTestFabricScopedEventResponseID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x0000000B,
    ZGMTRCommandIDTypeClusterUnitTestingCommandTestListNestedStructListArgumentRequestID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x0000000C,
    ZGMTRCommandIDTypeClusterUnitTestingCommandTestBatchHelperResponseID ZGMTR_PROVISIONALLY_AVAILABLE = 0x0000000C,
    ZGMTRCommandIDTypeClusterUnitTestingCommandTestListInt8UReverseRequestID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x0000000D,
    ZGMTRCommandIDTypeClusterUnitTestingCommandStringEchoResponseID ZGMTR_PROVISIONALLY_AVAILABLE = 0x0000000D,
    ZGMTRCommandIDTypeClusterUnitTestingCommandTestEnumsRequestID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x0000000E,
    ZGMTRCommandIDTypeClusterUnitTestingCommandGlobalEchoResponseID ZGMTR_PROVISIONALLY_AVAILABLE = 0x0000000E,
    ZGMTRCommandIDTypeClusterUnitTestingCommandTestNullableOptionalRequestID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x0000000F,
    ZGMTRCommandIDTypeClusterUnitTestingCommandTestComplexNullableOptionalRequestID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000010,
    ZGMTRCommandIDTypeClusterUnitTestingCommandSimpleStructEchoRequestID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000011,
    ZGMTRCommandIDTypeClusterUnitTestingCommandTimedInvokeRequestID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000012,
    ZGMTRCommandIDTypeClusterUnitTestingCommandTestSimpleOptionalArgumentRequestID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000013,
    ZGMTRCommandIDTypeClusterUnitTestingCommandTestEmitTestEventRequestID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000014,
    ZGMTRCommandIDTypeClusterUnitTestingCommandTestEmitTestFabricScopedEventRequestID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000015,
    ZGMTRCommandIDTypeClusterUnitTestingCommandTestBatchHelperRequestID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000016,
    ZGMTRCommandIDTypeClusterUnitTestingCommandTestSecondBatchHelperRequestID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000017,
    ZGMTRCommandIDTypeClusterUnitTestingCommandStringEchoRequestID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000018,
    ZGMTRCommandIDTypeClusterUnitTestingCommandGlobalEchoRequestID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000019,
    ZGMTRCommandIDTypeClusterUnitTestingCommandTestCheckCommandFlagsID ZGMTR_PROVISIONALLY_AVAILABLE = 0x0000001A,
    ZGMTRCommandIDTypeClusterUnitTestingCommandTestDifferentVendorMeiRequestID ZGMTR_PROVISIONALLY_AVAILABLE = 0xFFF200AA,
    ZGMTRCommandIDTypeClusterUnitTestingCommandTestDifferentVendorMeiResponseID ZGMTR_PROVISIONALLY_AVAILABLE = 0xFFF200BB,

    // Cluster SampleMEI commands
    ZGMTRCommandIDTypeClusterSampleMEICommandPingID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000000,
    ZGMTRCommandIDTypeClusterSampleMEICommandAddArgumentsResponseID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000001,
    ZGMTRCommandIDTypeClusterSampleMEICommandAddArgumentsID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000002,

    // Cluster BarrierControl deprecated command id names
    ZGMTRClusterBarrierControlCommandBarrierControlGoToPercentID
        ZGMTR_DEPRECATED("Please use ZGMTRCommandIDTypeClusterBarrierControlCommandBarrierControlGoToPercentID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x00000000,
    ZGMTRClusterBarrierControlCommandBarrierControlStopID
        ZGMTR_DEPRECATED("Please use ZGMTRCommandIDTypeClusterBarrierControlCommandBarrierControlStopID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x00000001,

    // Cluster BarrierControl commands
    ZGMTRCommandIDTypeClusterBarrierControlCommandBarrierControlGoToPercentID ZGMTR_DEPRECATED("The BarrierControlGoToPercent command will be removed", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2)) = 0x00000000,
    ZGMTRCommandIDTypeClusterBarrierControlCommandBarrierControlStopID ZGMTR_DEPRECATED("The BarrierControlStop command will be removed", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2)) = 0x00000001,

    // Cluster ElectricalMeasurement deprecated command id names
    ZGMTRClusterElectricalMeasurementCommandGetProfileInfoResponseCommandID
        ZGMTR_DEPRECATED("Please use ZGMTRCommandIDTypeClusterElectricalMeasurementCommandGetProfileInfoResponseCommandID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x00000000,
    ZGMTRClusterElectricalMeasurementCommandGetProfileInfoCommandID
        ZGMTR_DEPRECATED("Please use ZGMTRCommandIDTypeClusterElectricalMeasurementCommandGetProfileInfoCommandID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x00000000,
    ZGMTRClusterElectricalMeasurementCommandGetMeasurementProfileResponseCommandID
        ZGMTR_DEPRECATED("Please use ZGMTRCommandIDTypeClusterElectricalMeasurementCommandGetMeasurementProfileResponseCommandID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x00000001,
    ZGMTRClusterElectricalMeasurementCommandGetMeasurementProfileCommandID
        ZGMTR_DEPRECATED("Please use ZGMTRCommandIDTypeClusterElectricalMeasurementCommandGetMeasurementProfileCommandID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x00000001,

    // Cluster ElectricalMeasurement commands
    ZGMTRCommandIDTypeClusterElectricalMeasurementCommandGetProfileInfoResponseCommandID ZGMTR_DEPRECATED("The GetProfileInfoResponseCommand command will be removed", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2)) = 0x00000000,
    ZGMTRCommandIDTypeClusterElectricalMeasurementCommandGetProfileInfoCommandID ZGMTR_DEPRECATED("The GetProfileInfoCommand command will be removed", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2)) = 0x00000000,
    ZGMTRCommandIDTypeClusterElectricalMeasurementCommandGetMeasurementProfileResponseCommandID ZGMTR_DEPRECATED("The GetMeasurementProfileResponseCommand command will be removed", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2)) = 0x00000001,
    ZGMTRCommandIDTypeClusterElectricalMeasurementCommandGetMeasurementProfileCommandID ZGMTR_DEPRECATED("The GetMeasurementProfileCommand command will be removed", ios(16.4, 18.2), macos(13.3, 15.2), watchos(9.4, 11.2), tvos(16.4, 18.2)) = 0x00000001,
};

#pragma mark - Events IDs

typedef NS_ENUM(uint32_t, ZGMTREventIDType) {

    // Cluster AccessControl deprecated event names
    ZGMTRClusterAccessControlEventAccessControlEntryChangedID
        ZGMTR_DEPRECATED("Please use ZGMTREventIDTypeClusterAccessControlEventAccessControlEntryChangedID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x00000000,
    ZGMTRClusterAccessControlEventAccessControlExtensionChangedID
        ZGMTR_DEPRECATED("Please use ZGMTREventIDTypeClusterAccessControlEventAccessControlExtensionChangedID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x00000001,

    // Cluster AccessControl events
    ZGMTREventIDTypeClusterAccessControlEventAccessControlEntryChangedID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000000,
    ZGMTREventIDTypeClusterAccessControlEventAccessControlExtensionChangedID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000001,
    ZGMTREventIDTypeClusterAccessControlEventFabricRestrictionReviewUpdateID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = 0x00000002,
    ZGMTREventIDTypeClusterAccessControlEventAuxiliaryAccessUpdatedID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000003,

    // Cluster Actions deprecated event names
    ZGMTRClusterActionsEventStateChangedID
        ZGMTR_DEPRECATED("Please use ZGMTREventIDTypeClusterActionsEventStateChangedID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x00000000,
    ZGMTRClusterActionsEventActionFailedID
        ZGMTR_DEPRECATED("Please use ZGMTREventIDTypeClusterActionsEventActionFailedID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x00000001,

    // Cluster Actions events
    ZGMTREventIDTypeClusterActionsEventStateChangedID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000000,
    ZGMTREventIDTypeClusterActionsEventActionFailedID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000001,

    // Cluster Basic deprecated event names
    ZGMTRClusterBasicEventStartUpID
        ZGMTR_DEPRECATED("Please use ZGMTREventIDTypeClusterBasicInformationEventStartUpID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x00000000,
    ZGMTRClusterBasicEventShutDownID
        ZGMTR_DEPRECATED("Please use ZGMTREventIDTypeClusterBasicInformationEventShutDownID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x00000001,
    ZGMTRClusterBasicEventLeaveID
        ZGMTR_DEPRECATED("Please use ZGMTREventIDTypeClusterBasicInformationEventLeaveID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x00000002,
    ZGMTRClusterBasicEventReachableChangedID
        ZGMTR_DEPRECATED("Please use ZGMTREventIDTypeClusterBasicInformationEventReachableChangedID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x00000003,

    // Cluster BasicInformation events
    ZGMTREventIDTypeClusterBasicInformationEventStartUpID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000000,
    ZGMTREventIDTypeClusterBasicInformationEventShutDownID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000001,
    ZGMTREventIDTypeClusterBasicInformationEventLeaveID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000002,
    ZGMTREventIDTypeClusterBasicInformationEventReachableChangedID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000003,

    // Cluster OtaSoftwareUpdateRequestor deprecated event names
    ZGMTRClusterOtaSoftwareUpdateRequestorEventStateTransitionID
        ZGMTR_DEPRECATED("Please use ZGMTREventIDTypeClusterOTASoftwareUpdateRequestorEventStateTransitionID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x00000000,
    ZGMTRClusterOtaSoftwareUpdateRequestorEventVersionAppliedID
        ZGMTR_DEPRECATED("Please use ZGMTREventIDTypeClusterOTASoftwareUpdateRequestorEventVersionAppliedID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x00000001,
    ZGMTRClusterOtaSoftwareUpdateRequestorEventDownloadErrorID
        ZGMTR_DEPRECATED("Please use ZGMTREventIDTypeClusterOTASoftwareUpdateRequestorEventDownloadErrorID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x00000002,

    // Cluster OTASoftwareUpdateRequestor events
    ZGMTREventIDTypeClusterOTASoftwareUpdateRequestorEventStateTransitionID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000000,
    ZGMTREventIDTypeClusterOTASoftwareUpdateRequestorEventVersionAppliedID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000001,
    ZGMTREventIDTypeClusterOTASoftwareUpdateRequestorEventDownloadErrorID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000002,

    // Cluster PowerSource deprecated event names

    // Cluster PowerSource events
    ZGMTREventIDTypeClusterPowerSourceEventWiredFaultChangeID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000000,
    ZGMTREventIDTypeClusterPowerSourceEventBatFaultChangeID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000001,
    ZGMTREventIDTypeClusterPowerSourceEventBatChargeFaultChangeID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000002,

    // Cluster GeneralDiagnostics deprecated event names
    ZGMTRClusterGeneralDiagnosticsEventHardwareFaultChangeID
        ZGMTR_DEPRECATED("Please use ZGMTREventIDTypeClusterGeneralDiagnosticsEventHardwareFaultChangeID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x00000000,
    ZGMTRClusterGeneralDiagnosticsEventRadioFaultChangeID
        ZGMTR_DEPRECATED("Please use ZGMTREventIDTypeClusterGeneralDiagnosticsEventRadioFaultChangeID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x00000001,
    ZGMTRClusterGeneralDiagnosticsEventNetworkFaultChangeID
        ZGMTR_DEPRECATED("Please use ZGMTREventIDTypeClusterGeneralDiagnosticsEventNetworkFaultChangeID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x00000002,
    ZGMTRClusterGeneralDiagnosticsEventBootReasonID
        ZGMTR_DEPRECATED("Please use ZGMTREventIDTypeClusterGeneralDiagnosticsEventBootReasonID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x00000003,

    // Cluster GeneralDiagnostics events
    ZGMTREventIDTypeClusterGeneralDiagnosticsEventHardwareFaultChangeID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000000,
    ZGMTREventIDTypeClusterGeneralDiagnosticsEventRadioFaultChangeID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000001,
    ZGMTREventIDTypeClusterGeneralDiagnosticsEventNetworkFaultChangeID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000002,
    ZGMTREventIDTypeClusterGeneralDiagnosticsEventBootReasonID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000003,

    // Cluster SoftwareDiagnostics deprecated event names
    ZGMTRClusterSoftwareDiagnosticsEventSoftwareFaultID
        ZGMTR_DEPRECATED("Please use ZGMTREventIDTypeClusterSoftwareDiagnosticsEventSoftwareFaultID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x00000000,

    // Cluster SoftwareDiagnostics events
    ZGMTREventIDTypeClusterSoftwareDiagnosticsEventSoftwareFaultID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000000,

    // Cluster ThreadNetworkDiagnostics deprecated event names
    ZGMTRClusterThreadNetworkDiagnosticsEventConnectionStatusID
        ZGMTR_DEPRECATED("Please use ZGMTREventIDTypeClusterThreadNetworkDiagnosticsEventConnectionStatusID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x00000000,
    ZGMTRClusterThreadNetworkDiagnosticsEventNetworkFaultChangeID
        ZGMTR_DEPRECATED("Please use ZGMTREventIDTypeClusterThreadNetworkDiagnosticsEventNetworkFaultChangeID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x00000001,

    // Cluster ThreadNetworkDiagnostics events
    ZGMTREventIDTypeClusterThreadNetworkDiagnosticsEventConnectionStatusID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000000,
    ZGMTREventIDTypeClusterThreadNetworkDiagnosticsEventNetworkFaultChangeID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000001,

    // Cluster WiFiNetworkDiagnostics deprecated event names
    ZGMTRClusterWiFiNetworkDiagnosticsEventDisconnectionID
        ZGMTR_DEPRECATED("Please use ZGMTREventIDTypeClusterWiFiNetworkDiagnosticsEventDisconnectionID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x00000000,
    ZGMTRClusterWiFiNetworkDiagnosticsEventAssociationFailureID
        ZGMTR_DEPRECATED("Please use ZGMTREventIDTypeClusterWiFiNetworkDiagnosticsEventAssociationFailureID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x00000001,
    ZGMTRClusterWiFiNetworkDiagnosticsEventConnectionStatusID
        ZGMTR_DEPRECATED("Please use ZGMTREventIDTypeClusterWiFiNetworkDiagnosticsEventConnectionStatusID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x00000002,

    // Cluster WiFiNetworkDiagnostics events
    ZGMTREventIDTypeClusterWiFiNetworkDiagnosticsEventDisconnectionID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000000,
    ZGMTREventIDTypeClusterWiFiNetworkDiagnosticsEventAssociationFailureID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000001,
    ZGMTREventIDTypeClusterWiFiNetworkDiagnosticsEventConnectionStatusID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000002,

    // Cluster TimeSynchronization deprecated event names

    // Cluster TimeSynchronization events
    ZGMTREventIDTypeClusterTimeSynchronizationEventDSTTableEmptyID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = 0x00000000,
    ZGMTREventIDTypeClusterTimeSynchronizationEventDSTStatusID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = 0x00000001,
    ZGMTREventIDTypeClusterTimeSynchronizationEventTimeZoneStatusID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = 0x00000002,
    ZGMTREventIDTypeClusterTimeSynchronizationEventTimeFailureID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = 0x00000003,
    ZGMTREventIDTypeClusterTimeSynchronizationEventMissingTrustedTimeSourceID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = 0x00000004,

    // Cluster BridgedDeviceBasic deprecated event names
    ZGMTRClusterBridgedDeviceBasicEventStartUpID
        ZGMTR_DEPRECATED("Please use ZGMTREventIDTypeClusterBridgedDeviceBasicInformationEventStartUpID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x00000000,
    ZGMTRClusterBridgedDeviceBasicEventShutDownID
        ZGMTR_DEPRECATED("Please use ZGMTREventIDTypeClusterBridgedDeviceBasicInformationEventShutDownID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x00000001,
    ZGMTRClusterBridgedDeviceBasicEventLeaveID
        ZGMTR_DEPRECATED("Please use ZGMTREventIDTypeClusterBridgedDeviceBasicInformationEventLeaveID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x00000002,
    ZGMTRClusterBridgedDeviceBasicEventReachableChangedID
        ZGMTR_DEPRECATED("Please use ZGMTREventIDTypeClusterBridgedDeviceBasicInformationEventReachableChangedID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x00000003,

    // Cluster BridgedDeviceBasicInformation events
    ZGMTREventIDTypeClusterBridgedDeviceBasicInformationEventStartUpID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000000,
    ZGMTREventIDTypeClusterBridgedDeviceBasicInformationEventShutDownID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000001,
    ZGMTREventIDTypeClusterBridgedDeviceBasicInformationEventLeaveID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000002,
    ZGMTREventIDTypeClusterBridgedDeviceBasicInformationEventReachableChangedID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000003,
    ZGMTREventIDTypeClusterBridgedDeviceBasicInformationEventActiveChangedID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = 0x00000080,

    // Cluster Switch deprecated event names
    ZGMTRClusterSwitchEventSwitchLatchedID
        ZGMTR_DEPRECATED("Please use ZGMTREventIDTypeClusterSwitchEventSwitchLatchedID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x00000000,
    ZGMTRClusterSwitchEventInitialPressID
        ZGMTR_DEPRECATED("Please use ZGMTREventIDTypeClusterSwitchEventInitialPressID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x00000001,
    ZGMTRClusterSwitchEventLongPressID
        ZGMTR_DEPRECATED("Please use ZGMTREventIDTypeClusterSwitchEventLongPressID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x00000002,
    ZGMTRClusterSwitchEventShortReleaseID
        ZGMTR_DEPRECATED("Please use ZGMTREventIDTypeClusterSwitchEventShortReleaseID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x00000003,
    ZGMTRClusterSwitchEventLongReleaseID
        ZGMTR_DEPRECATED("Please use ZGMTREventIDTypeClusterSwitchEventLongReleaseID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x00000004,
    ZGMTRClusterSwitchEventMultiPressOngoingID
        ZGMTR_DEPRECATED("Please use ZGMTREventIDTypeClusterSwitchEventMultiPressOngoingID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x00000005,
    ZGMTRClusterSwitchEventMultiPressCompleteID
        ZGMTR_DEPRECATED("Please use ZGMTREventIDTypeClusterSwitchEventMultiPressCompleteID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x00000006,

    // Cluster Switch events
    ZGMTREventIDTypeClusterSwitchEventSwitchLatchedID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000000,
    ZGMTREventIDTypeClusterSwitchEventInitialPressID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000001,
    ZGMTREventIDTypeClusterSwitchEventLongPressID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000002,
    ZGMTREventIDTypeClusterSwitchEventShortReleaseID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000003,
    ZGMTREventIDTypeClusterSwitchEventLongReleaseID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000004,
    ZGMTREventIDTypeClusterSwitchEventMultiPressOngoingID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000005,
    ZGMTREventIDTypeClusterSwitchEventMultiPressCompleteID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000006,

    // Cluster BooleanState deprecated event names
    ZGMTRClusterBooleanStateEventStateChangeID
        ZGMTR_DEPRECATED("Please use ZGMTREventIDTypeClusterBooleanStateEventStateChangeID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x00000000,

    // Cluster BooleanState events
    ZGMTREventIDTypeClusterBooleanStateEventStateChangeID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000000,

    // Cluster OvenCavityOperationalState events
    ZGMTREventIDTypeClusterOvenCavityOperationalStateEventOperationalErrorID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = 0x00000000,
    ZGMTREventIDTypeClusterOvenCavityOperationalStateEventOperationCompletionID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = 0x00000001,

    // Cluster RefrigeratorAlarm events
    ZGMTREventIDTypeClusterRefrigeratorAlarmEventNotifyID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = 0x00000000,

    // Cluster SmokeCOAlarm events
    ZGMTREventIDTypeClusterSmokeCOAlarmEventSmokeAlarmID ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6)) = 0x00000000,
    ZGMTREventIDTypeClusterSmokeCOAlarmEventCOAlarmID ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6)) = 0x00000001,
    ZGMTREventIDTypeClusterSmokeCOAlarmEventLowBatteryID ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6)) = 0x00000002,
    ZGMTREventIDTypeClusterSmokeCOAlarmEventHardwareFaultID ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6)) = 0x00000003,
    ZGMTREventIDTypeClusterSmokeCOAlarmEventEndOfServiceID ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6)) = 0x00000004,
    ZGMTREventIDTypeClusterSmokeCOAlarmEventSelfTestCompleteID ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6)) = 0x00000005,
    ZGMTREventIDTypeClusterSmokeCOAlarmEventAlarmMutedID ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6)) = 0x00000006,
    ZGMTREventIDTypeClusterSmokeCOAlarmEventMuteEndedID ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6)) = 0x00000007,
    ZGMTREventIDTypeClusterSmokeCOAlarmEventInterconnectSmokeAlarmID ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6)) = 0x00000008,
    ZGMTREventIDTypeClusterSmokeCOAlarmEventInterconnectCOAlarmID ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6)) = 0x00000009,
    ZGMTREventIDTypeClusterSmokeCOAlarmEventAllClearID ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6)) = 0x0000000A,

    // Cluster DishwasherAlarm events
    ZGMTREventIDTypeClusterDishwasherAlarmEventNotifyID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = 0x00000000,

    // Cluster OperationalState events
    ZGMTREventIDTypeClusterOperationalStateEventOperationalErrorID ZGMTR_AVAILABLE(ios(17.4), macos(14.4), watchos(10.4), tvos(17.4)) = 0x00000000,
    ZGMTREventIDTypeClusterOperationalStateEventOperationCompletionID ZGMTR_AVAILABLE(ios(17.4), macos(14.4), watchos(10.4), tvos(17.4)) = 0x00000001,

    // Cluster RVCOperationalState events
    ZGMTREventIDTypeClusterRVCOperationalStateEventOperationalErrorID ZGMTR_AVAILABLE(ios(17.4), macos(14.4), watchos(10.4), tvos(17.4)) = 0x00000000,
    ZGMTREventIDTypeClusterRVCOperationalStateEventOperationCompletionID ZGMTR_AVAILABLE(ios(17.4), macos(14.4), watchos(10.4), tvos(17.4)) = 0x00000001,

    // Cluster Groupcast events
    ZGMTREventIDTypeClusterGroupcastEventGroupcastTestingID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000000,

    // Cluster BooleanStateConfiguration events
    ZGMTREventIDTypeClusterBooleanStateConfigurationEventAlarmsStateChangedID ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6)) = 0x00000000,
    ZGMTREventIDTypeClusterBooleanStateConfigurationEventSensorFaultID ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6)) = 0x00000001,

    // Cluster ValveConfigurationAndControl events
    ZGMTREventIDTypeClusterValveConfigurationAndControlEventValveStateChangedID ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6)) = 0x00000000,
    ZGMTREventIDTypeClusterValveConfigurationAndControlEventValveFaultID ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6)) = 0x00000001,

    // Cluster ElectricalPowerMeasurement events
    ZGMTREventIDTypeClusterElectricalPowerMeasurementEventMeasurementPeriodRangesID ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6)) = 0x00000000,

    // Cluster ElectricalEnergyMeasurement events
    ZGMTREventIDTypeClusterElectricalEnergyMeasurementEventCumulativeEnergyMeasuredID ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6)) = 0x00000000,
    ZGMTREventIDTypeClusterElectricalEnergyMeasurementEventPeriodicEnergyMeasuredID ZGMTR_AVAILABLE(ios(17.6), macos(14.6), watchos(10.6), tvos(17.6)) = 0x00000001,

    // Cluster WaterHeaterManagement events
    ZGMTREventIDTypeClusterWaterHeaterManagementEventBoostStartedID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = 0x00000000,
    ZGMTREventIDTypeClusterWaterHeaterManagementEventBoostEndedID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = 0x00000001,

    // Cluster CommodityPrice events
    ZGMTREventIDTypeClusterCommodityPriceEventPriceChangeID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000000,

    // Cluster Messages events
    ZGMTREventIDTypeClusterMessagesEventMessageQueuedID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = 0x00000000,
    ZGMTREventIDTypeClusterMessagesEventMessagePresentedID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = 0x00000001,
    ZGMTREventIDTypeClusterMessagesEventMessageCompleteID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = 0x00000002,

    // Cluster DeviceEnergyManagement events
    ZGMTREventIDTypeClusterDeviceEnergyManagementEventPowerAdjustStartID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = 0x00000000,
    ZGMTREventIDTypeClusterDeviceEnergyManagementEventPowerAdjustEndID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = 0x00000001,
    ZGMTREventIDTypeClusterDeviceEnergyManagementEventPausedID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = 0x00000002,
    ZGMTREventIDTypeClusterDeviceEnergyManagementEventResumedID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = 0x00000003,
    ZGMTREventIDTypeClusterDeviceEnergyManagementEventPowerRangeAdjustStartID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000004,
    ZGMTREventIDTypeClusterDeviceEnergyManagementEventPowerRangeAdjustEndID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000005,

    // Cluster EnergyEVSE events
    ZGMTREventIDTypeClusterEnergyEVSEEventEVConnectedID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = 0x00000000,
    ZGMTREventIDTypeClusterEnergyEVSEEventEVNotDetectedID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = 0x00000001,
    ZGMTREventIDTypeClusterEnergyEVSEEventEnergyTransferStartedID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = 0x00000002,
    ZGMTREventIDTypeClusterEnergyEVSEEventEnergyTransferStoppedID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = 0x00000003,
    ZGMTREventIDTypeClusterEnergyEVSEEventFaultID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = 0x00000004,
    ZGMTREventIDTypeClusterEnergyEVSEEventRFIDID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = 0x00000005,

    // Cluster ElectricalGridConditions events
    ZGMTREventIDTypeClusterElectricalGridConditionsEventCurrentConditionsChangedID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000000,

    // Cluster ElectricalAlarm events
    ZGMTREventIDTypeClusterElectricalAlarmEventNotifyID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000000,

    // Cluster ElectricalProtectionAlarm events
    ZGMTREventIDTypeClusterElectricalProtectionAlarmEventNotifyID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000000,

    // Cluster DoorLock deprecated event names
    ZGMTRClusterDoorLockEventDoorLockAlarmID
        ZGMTR_DEPRECATED("Please use ZGMTREventIDTypeClusterDoorLockEventDoorLockAlarmID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x00000000,
    ZGMTRClusterDoorLockEventDoorStateChangeID
        ZGMTR_DEPRECATED("Please use ZGMTREventIDTypeClusterDoorLockEventDoorStateChangeID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x00000001,
    ZGMTRClusterDoorLockEventLockOperationID
        ZGMTR_DEPRECATED("Please use ZGMTREventIDTypeClusterDoorLockEventLockOperationID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x00000002,
    ZGMTRClusterDoorLockEventLockOperationErrorID
        ZGMTR_DEPRECATED("Please use ZGMTREventIDTypeClusterDoorLockEventLockOperationErrorID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x00000003,
    ZGMTRClusterDoorLockEventLockUserChangeID
        ZGMTR_DEPRECATED("Please use ZGMTREventIDTypeClusterDoorLockEventLockUserChangeID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x00000004,

    // Cluster DoorLock events
    ZGMTREventIDTypeClusterDoorLockEventDoorLockAlarmID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000000,
    ZGMTREventIDTypeClusterDoorLockEventDoorStateChangeID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000001,
    ZGMTREventIDTypeClusterDoorLockEventLockOperationID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000002,
    ZGMTREventIDTypeClusterDoorLockEventLockOperationErrorID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000003,
    ZGMTREventIDTypeClusterDoorLockEventLockUserChangeID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000004,

    // Cluster ClosureControl events
    ZGMTREventIDTypeClusterClosureControlEventOperationalErrorID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000000,
    ZGMTREventIDTypeClusterClosureControlEventMovementCompletedID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000001,
    ZGMTREventIDTypeClusterClosureControlEventEngageStateChangedID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000002,
    ZGMTREventIDTypeClusterClosureControlEventSecureStateChangedID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000003,

    // Cluster PumpConfigurationAndControl deprecated event names
    ZGMTRClusterPumpConfigurationAndControlEventSupplyVoltageLowID
        ZGMTR_DEPRECATED("Please use ZGMTREventIDTypeClusterPumpConfigurationAndControlEventSupplyVoltageLowID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x00000000,
    ZGMTRClusterPumpConfigurationAndControlEventSupplyVoltageHighID
        ZGMTR_DEPRECATED("Please use ZGMTREventIDTypeClusterPumpConfigurationAndControlEventSupplyVoltageHighID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x00000001,
    ZGMTRClusterPumpConfigurationAndControlEventPowerMissingPhaseID
        ZGMTR_DEPRECATED("Please use ZGMTREventIDTypeClusterPumpConfigurationAndControlEventPowerMissingPhaseID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x00000002,
    ZGMTRClusterPumpConfigurationAndControlEventSystemPressureLowID
        ZGMTR_DEPRECATED("Please use ZGMTREventIDTypeClusterPumpConfigurationAndControlEventSystemPressureLowID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x00000003,
    ZGMTRClusterPumpConfigurationAndControlEventSystemPressureHighID
        ZGMTR_DEPRECATED("Please use ZGMTREventIDTypeClusterPumpConfigurationAndControlEventSystemPressureHighID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x00000004,
    ZGMTRClusterPumpConfigurationAndControlEventDryRunningID
        ZGMTR_DEPRECATED("Please use ZGMTREventIDTypeClusterPumpConfigurationAndControlEventDryRunningID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x00000005,
    ZGMTRClusterPumpConfigurationAndControlEventMotorTemperatureHighID
        ZGMTR_DEPRECATED("Please use ZGMTREventIDTypeClusterPumpConfigurationAndControlEventMotorTemperatureHighID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x00000006,
    ZGMTRClusterPumpConfigurationAndControlEventPumpMotorFatalFailureID
        ZGMTR_DEPRECATED("Please use ZGMTREventIDTypeClusterPumpConfigurationAndControlEventPumpMotorFatalFailureID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x00000007,
    ZGMTRClusterPumpConfigurationAndControlEventElectronicTemperatureHighID
        ZGMTR_DEPRECATED("Please use ZGMTREventIDTypeClusterPumpConfigurationAndControlEventElectronicTemperatureHighID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x00000008,
    ZGMTRClusterPumpConfigurationAndControlEventPumpBlockedID
        ZGMTR_DEPRECATED("Please use ZGMTREventIDTypeClusterPumpConfigurationAndControlEventPumpBlockedID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x00000009,
    ZGMTRClusterPumpConfigurationAndControlEventSensorFailureID
        ZGMTR_DEPRECATED("Please use ZGMTREventIDTypeClusterPumpConfigurationAndControlEventSensorFailureID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x0000000A,
    ZGMTRClusterPumpConfigurationAndControlEventElectronicNonFatalFailureID
        ZGMTR_DEPRECATED("Please use ZGMTREventIDTypeClusterPumpConfigurationAndControlEventElectronicNonFatalFailureID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x0000000B,
    ZGMTRClusterPumpConfigurationAndControlEventElectronicFatalFailureID
        ZGMTR_DEPRECATED("Please use ZGMTREventIDTypeClusterPumpConfigurationAndControlEventElectronicFatalFailureID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x0000000C,
    ZGMTRClusterPumpConfigurationAndControlEventGeneralFaultID
        ZGMTR_DEPRECATED("Please use ZGMTREventIDTypeClusterPumpConfigurationAndControlEventGeneralFaultID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x0000000D,
    ZGMTRClusterPumpConfigurationAndControlEventLeakageID
        ZGMTR_DEPRECATED("Please use ZGMTREventIDTypeClusterPumpConfigurationAndControlEventLeakageID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x0000000E,
    ZGMTRClusterPumpConfigurationAndControlEventAirDetectionID
        ZGMTR_DEPRECATED("Please use ZGMTREventIDTypeClusterPumpConfigurationAndControlEventAirDetectionID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x0000000F,
    ZGMTRClusterPumpConfigurationAndControlEventTurbineOperationID
        ZGMTR_DEPRECATED("Please use ZGMTREventIDTypeClusterPumpConfigurationAndControlEventTurbineOperationID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x00000010,

    // Cluster PumpConfigurationAndControl events
    ZGMTREventIDTypeClusterPumpConfigurationAndControlEventSupplyVoltageLowID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000000,
    ZGMTREventIDTypeClusterPumpConfigurationAndControlEventSupplyVoltageHighID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000001,
    ZGMTREventIDTypeClusterPumpConfigurationAndControlEventPowerMissingPhaseID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000002,
    ZGMTREventIDTypeClusterPumpConfigurationAndControlEventSystemPressureLowID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000003,
    ZGMTREventIDTypeClusterPumpConfigurationAndControlEventSystemPressureHighID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000004,
    ZGMTREventIDTypeClusterPumpConfigurationAndControlEventDryRunningID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000005,
    ZGMTREventIDTypeClusterPumpConfigurationAndControlEventMotorTemperatureHighID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000006,
    ZGMTREventIDTypeClusterPumpConfigurationAndControlEventPumpMotorFatalFailureID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000007,
    ZGMTREventIDTypeClusterPumpConfigurationAndControlEventElectronicTemperatureHighID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000008,
    ZGMTREventIDTypeClusterPumpConfigurationAndControlEventPumpBlockedID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000009,
    ZGMTREventIDTypeClusterPumpConfigurationAndControlEventSensorFailureID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x0000000A,
    ZGMTREventIDTypeClusterPumpConfigurationAndControlEventElectronicNonFatalFailureID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x0000000B,
    ZGMTREventIDTypeClusterPumpConfigurationAndControlEventElectronicFatalFailureID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x0000000C,
    ZGMTREventIDTypeClusterPumpConfigurationAndControlEventGeneralFaultID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x0000000D,
    ZGMTREventIDTypeClusterPumpConfigurationAndControlEventLeakageID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x0000000E,
    ZGMTREventIDTypeClusterPumpConfigurationAndControlEventAirDetectionID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x0000000F,
    ZGMTREventIDTypeClusterPumpConfigurationAndControlEventTurbineOperationID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000010,

    // Cluster Thermostat deprecated event names

    // Cluster Thermostat events
    ZGMTREventIDTypeClusterThermostatEventSystemModeChangeID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000000,
    ZGMTREventIDTypeClusterThermostatEventLocalTemperatureChangeID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000001,
    ZGMTREventIDTypeClusterThermostatEventOccupancyChangeID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000002,
    ZGMTREventIDTypeClusterThermostatEventSetpointChangeID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000003,
    ZGMTREventIDTypeClusterThermostatEventRunningStateChangeID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000004,
    ZGMTREventIDTypeClusterThermostatEventRunningModeChangeID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000005,
    ZGMTREventIDTypeClusterThermostatEventActiveScheduleChangeID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000006,
    ZGMTREventIDTypeClusterThermostatEventActivePresetChangeID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000007,

    // Cluster OccupancySensing deprecated event names

    // Cluster OccupancySensing events
    ZGMTREventIDTypeClusterOccupancySensingEventOccupancyChangedID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = 0x00000000,

    // Cluster AmbientContextSensing events
    ZGMTREventIDTypeClusterAmbientContextSensingEventAmbientContextDetectStartedID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000000,
    ZGMTREventIDTypeClusterAmbientContextSensingEventAmbientContextDetectEndedID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000001,

    // Cluster AmbientSensingUnion events
    ZGMTREventIDTypeClusterAmbientSensingUnionEventUnionContributorAddedID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000000,
    ZGMTREventIDTypeClusterAmbientSensingUnionEventUnionContributorRemovedID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000001,
    ZGMTREventIDTypeClusterAmbientSensingUnionEventUnionContributorStatusChangedID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000002,

    // Cluster ProximityRanging events
    ZGMTREventIDTypeClusterProximityRangingEventRangingResultID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000000,
    ZGMTREventIDTypeClusterProximityRangingEventRangingSessionStatusID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000001,

    // Cluster TargetNavigator deprecated event names

    // Cluster TargetNavigator events
    ZGMTREventIDTypeClusterTargetNavigatorEventTargetUpdatedID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = 0x00000000,

    // Cluster MediaPlayback deprecated event names

    // Cluster MediaPlayback events
    ZGMTREventIDTypeClusterMediaPlaybackEventStateChangedID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = 0x00000000,

    // Cluster ContentLauncher deprecated event names

    // Cluster ContentLauncher events
    ZGMTREventIDTypeClusterContentLauncherEventContentReplicationID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000000,

    // Cluster AccountLogin deprecated event names

    // Cluster AccountLogin events
    ZGMTREventIDTypeClusterAccountLoginEventLoggedOutID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = 0x00000000,

    // Cluster ContentControl events
    ZGMTREventIDTypeClusterContentControlEventRemainingScreenTimeExpiredID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000000,
    ZGMTREventIDTypeClusterContentControlEventEnteringBlockContentTimeWindowID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000001,

    // Cluster MediaFileManagement events
    ZGMTREventIDTypeClusterMediaFileManagementEventSharedFilesAddedID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000000,

    // Cluster ZoneManagement events
    ZGMTREventIDTypeClusterZoneManagementEventZoneTriggeredID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000000,
    ZGMTREventIDTypeClusterZoneManagementEventZoneStoppedID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000001,

    // Cluster PushAVStreamTransport events
    ZGMTREventIDTypeClusterPushAVStreamTransportEventPushTransportBeginID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000000,
    ZGMTREventIDTypeClusterPushAVStreamTransportEventPushTransportEndID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000001,

    // Cluster Chime events
    ZGMTREventIDTypeClusterChimeEventChimeStartedPlayingID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000000,

    // Cluster AVAnalysis events
    ZGMTREventIDTypeClusterAVAnalysisEventAnalysisSessionStartID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000000,
    ZGMTREventIDTypeClusterAVAnalysisEventAnalysisSessionEndID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000001,
    ZGMTREventIDTypeClusterAVAnalysisEventPerceivedContextID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000002,

    // Cluster CommissionerControl events
    ZGMTREventIDTypeClusterCommissionerControlEventCommissioningRequestResultID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = 0x00000000,

    // Cluster TestCluster deprecated event names
    ZGMTRClusterTestClusterEventTestEventID
        ZGMTR_DEPRECATED("Please use ZGMTREventIDTypeClusterUnitTestingEventTestEventID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x00000001,
    ZGMTRClusterTestClusterEventTestFabricScopedEventID
        ZGMTR_DEPRECATED("Please use ZGMTREventIDTypeClusterUnitTestingEventTestFabricScopedEventID", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
    = 0x00000002,

    // Cluster UnitTesting events
    ZGMTREventIDTypeClusterUnitTestingEventTestEventID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000001,
    ZGMTREventIDTypeClusterUnitTestingEventTestFabricScopedEventID ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4)) = 0x00000002,
    ZGMTREventIDTypeClusterUnitTestingEventTestDifferentVendorMeiEventID ZGMTR_PROVISIONALLY_AVAILABLE = 0xFFF200EE,

    // Cluster SampleMEI events
    ZGMTREventIDTypeClusterSampleMEIEventPingCountEventID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000000,

};

#pragma mark - Device Type IDs

typedef NS_ENUM(uint32_t, ZGMTRDeviceTypeIDType) {
    ZGMTRDeviceTypeIDTypeDoorLockID ZGMTR_AVAILABLE(ios(18.2), macos(15.2), watchos(11.2), tvos(18.2)) = 0x0000000A,
    ZGMTRDeviceTypeIDTypeDoorLockControllerID ZGMTR_AVAILABLE(ios(18.2), macos(15.2), watchos(11.2), tvos(18.2)) = 0x0000000B,
    ZGMTRDeviceTypeIDTypeAggregatorID ZGMTR_AVAILABLE(ios(18.2), macos(15.2), watchos(11.2), tvos(18.2)) = 0x0000000E,
    ZGMTRDeviceTypeIDTypeGenericSwitchID ZGMTR_AVAILABLE(ios(18.2), macos(15.2), watchos(11.2), tvos(18.2)) = 0x0000000F,
    ZGMTRDeviceTypeIDTypePowerSourceID ZGMTR_AVAILABLE(ios(18.2), macos(15.2), watchos(11.2), tvos(18.2)) = 0x00000011,
    ZGMTRDeviceTypeIDTypeOTARequestorID ZGMTR_AVAILABLE(ios(18.2), macos(15.2), watchos(11.2), tvos(18.2)) = 0x00000012,
    ZGMTRDeviceTypeIDTypeBridgedNodeID ZGMTR_AVAILABLE(ios(18.2), macos(15.2), watchos(11.2), tvos(18.2)) = 0x00000013,
    ZGMTRDeviceTypeIDTypeOTAProviderID ZGMTR_AVAILABLE(ios(18.2), macos(15.2), watchos(11.2), tvos(18.2)) = 0x00000014,
    ZGMTRDeviceTypeIDTypeContactSensorID ZGMTR_AVAILABLE(ios(18.2), macos(15.2), watchos(11.2), tvos(18.2)) = 0x00000015,
    ZGMTRDeviceTypeIDTypeRootNodeID ZGMTR_AVAILABLE(ios(18.2), macos(15.2), watchos(11.2), tvos(18.2)) = 0x00000016,
    ZGMTRDeviceTypeIDTypeSolarPowerID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = 0x00000017,
    ZGMTRDeviceTypeIDTypeBatteryStorageID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = 0x00000018,
    ZGMTRDeviceTypeIDTypeSecondaryNetworkInterfaceID ZGMTR_AVAILABLE(ios(18.2), macos(15.2), watchos(11.2), tvos(18.2)) = 0x00000019,
    ZGMTRDeviceTypeIDTypeSpeakerID ZGMTR_AVAILABLE(ios(18.2), macos(15.2), watchos(11.2), tvos(18.2)) = 0x00000022,
    ZGMTRDeviceTypeIDTypeCastingVideoPlayerID ZGMTR_AVAILABLE(ios(18.2), macos(15.2), watchos(11.2), tvos(18.2)) = 0x00000023,
    ZGMTRDeviceTypeIDTypeContentAppID ZGMTR_AVAILABLE(ios(18.2), macos(15.2), watchos(11.2), tvos(18.2)) = 0x00000024,
    ZGMTRDeviceTypeIDTypeModeSelectID ZGMTR_AVAILABLE(ios(18.2), macos(15.2), watchos(11.2), tvos(18.2)) = 0x00000027,
    ZGMTRDeviceTypeIDTypeBasicVideoPlayerID ZGMTR_AVAILABLE(ios(18.2), macos(15.2), watchos(11.2), tvos(18.2)) = 0x00000028,
    ZGMTRDeviceTypeIDTypeCastingVideoClientID ZGMTR_AVAILABLE(ios(18.2), macos(15.2), watchos(11.2), tvos(18.2)) = 0x00000029,
    ZGMTRDeviceTypeIDTypeVideoRemoteControlID ZGMTR_AVAILABLE(ios(18.2), macos(15.2), watchos(11.2), tvos(18.2)) = 0x0000002A,
    ZGMTRDeviceTypeIDTypeFanID ZGMTR_AVAILABLE(ios(18.2), macos(15.2), watchos(11.2), tvos(18.2)) = 0x0000002B,
    ZGMTRDeviceTypeIDTypeAirQualitySensorID ZGMTR_AVAILABLE(ios(18.2), macos(15.2), watchos(11.2), tvos(18.2)) = 0x0000002C,
    ZGMTRDeviceTypeIDTypeAirPurifierID ZGMTR_AVAILABLE(ios(18.2), macos(15.2), watchos(11.2), tvos(18.2)) = 0x0000002D,
    ZGMTRDeviceTypeIDTypeWaterFreezeDetectorID ZGMTR_AVAILABLE(ios(18.2), macos(15.2), watchos(11.2), tvos(18.2)) = 0x00000041,
    ZGMTRDeviceTypeIDTypeWaterValveID ZGMTR_AVAILABLE(ios(18.2), macos(15.2), watchos(11.2), tvos(18.2)) = 0x00000042,
    ZGMTRDeviceTypeIDTypeWaterLeakDetectorID ZGMTR_AVAILABLE(ios(18.2), macos(15.2), watchos(11.2), tvos(18.2)) = 0x00000043,
    ZGMTRDeviceTypeIDTypeRainSensorID ZGMTR_AVAILABLE(ios(18.2), macos(15.2), watchos(11.2), tvos(18.2)) = 0x00000044,
    ZGMTRDeviceTypeIDTypeSoilSensorID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000045,
    ZGMTRDeviceTypeIDTypeRefrigeratorID ZGMTR_AVAILABLE(ios(18.2), macos(15.2), watchos(11.2), tvos(18.2)) = 0x00000070,
    ZGMTRDeviceTypeIDTypeTemperatureControlledCabinetID ZGMTR_AVAILABLE(ios(18.2), macos(15.2), watchos(11.2), tvos(18.2)) = 0x00000071,
    ZGMTRDeviceTypeIDTypeRoomAirConditionerID ZGMTR_AVAILABLE(ios(18.2), macos(15.2), watchos(11.2), tvos(18.2)) = 0x00000072,
    ZGMTRDeviceTypeIDTypeLaundryWasherID ZGMTR_AVAILABLE(ios(18.2), macos(15.2), watchos(11.2), tvos(18.2)) = 0x00000073,
    ZGMTRDeviceTypeIDTypeRoboticVacuumCleanerID ZGMTR_AVAILABLE(ios(18.2), macos(15.2), watchos(11.2), tvos(18.2)) = 0x00000074,
    ZGMTRDeviceTypeIDTypeDishwasherID ZGMTR_AVAILABLE(ios(18.2), macos(15.2), watchos(11.2), tvos(18.2)) = 0x00000075,
    ZGMTRDeviceTypeIDTypeSmokeCOAlarmID ZGMTR_AVAILABLE(ios(18.2), macos(15.2), watchos(11.2), tvos(18.2)) = 0x00000076,
    ZGMTRDeviceTypeIDTypeCookSurfaceID ZGMTR_AVAILABLE(ios(18.2), macos(15.2), watchos(11.2), tvos(18.2)) = 0x00000077,
    ZGMTRDeviceTypeIDTypeCooktopID ZGMTR_AVAILABLE(ios(18.2), macos(15.2), watchos(11.2), tvos(18.2)) = 0x00000078,
    ZGMTRDeviceTypeIDTypeMicrowaveOvenID ZGMTR_AVAILABLE(ios(18.2), macos(15.2), watchos(11.2), tvos(18.2)) = 0x00000079,
    ZGMTRDeviceTypeIDTypeExtractorHoodID ZGMTR_AVAILABLE(ios(18.2), macos(15.2), watchos(11.2), tvos(18.2)) = 0x0000007A,
    ZGMTRDeviceTypeIDTypeOvenID ZGMTR_AVAILABLE(ios(18.2), macos(15.2), watchos(11.2), tvos(18.2)) = 0x0000007B,
    ZGMTRDeviceTypeIDTypeLaundryDryerID ZGMTR_AVAILABLE(ios(18.2), macos(15.2), watchos(11.2), tvos(18.2)) = 0x0000007C,
    ZGMTRDeviceTypeIDTypeHumidifierDehumidifierID ZGMTR_PROVISIONALLY_AVAILABLE = 0x0000007D,
    ZGMTRDeviceTypeIDTypeNetworkInfrastructureManagerID ZGMTR_AVAILABLE(ios(18.2), macos(15.2), watchos(11.2), tvos(18.2)) = 0x00000090,
    ZGMTRDeviceTypeIDTypeThreadBorderRouterID ZGMTR_AVAILABLE(ios(18.2), macos(15.2), watchos(11.2), tvos(18.2)) = 0x00000091,
    ZGMTRDeviceTypeIDTypeCommissioningByProxyID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000092,
    ZGMTRDeviceTypeIDTypeOnOffLightID ZGMTR_AVAILABLE(ios(18.2), macos(15.2), watchos(11.2), tvos(18.2)) = 0x00000100,
    ZGMTRDeviceTypeIDTypeDimmableLightID ZGMTR_AVAILABLE(ios(18.2), macos(15.2), watchos(11.2), tvos(18.2)) = 0x00000101,
    ZGMTRDeviceTypeIDTypeOnOffLightSwitchID ZGMTR_AVAILABLE(ios(18.2), macos(15.2), watchos(11.2), tvos(18.2)) = 0x00000103,
    ZGMTRDeviceTypeIDTypeDimmerSwitchID ZGMTR_AVAILABLE(ios(18.2), macos(15.2), watchos(11.2), tvos(18.2)) = 0x00000104,
    ZGMTRDeviceTypeIDTypeColorDimmerSwitchID ZGMTR_AVAILABLE(ios(18.2), macos(15.2), watchos(11.2), tvos(18.2)) = 0x00000105,
    ZGMTRDeviceTypeIDTypeLightSensorID ZGMTR_AVAILABLE(ios(18.2), macos(15.2), watchos(11.2), tvos(18.2)) = 0x00000106,
    ZGMTRDeviceTypeIDTypeOccupancySensorID ZGMTR_AVAILABLE(ios(18.2), macos(15.2), watchos(11.2), tvos(18.2)) = 0x00000107,
    ZGMTRDeviceTypeIDTypeOnOffPlugInUnitID ZGMTR_AVAILABLE(ios(18.2), macos(15.2), watchos(11.2), tvos(18.2)) = 0x0000010A,
    ZGMTRDeviceTypeIDTypeDimmablePlugInUnitID ZGMTR_AVAILABLE(ios(18.2), macos(15.2), watchos(11.2), tvos(18.2)) = 0x0000010B,
    ZGMTRDeviceTypeIDTypeColorTemperatureLightID ZGMTR_AVAILABLE(ios(18.2), macos(15.2), watchos(11.2), tvos(18.2)) = 0x0000010C,
    ZGMTRDeviceTypeIDTypeExtendedColorLightID ZGMTR_AVAILABLE(ios(18.2), macos(15.2), watchos(11.2), tvos(18.2)) = 0x0000010D,
    ZGMTRDeviceTypeIDTypeMountedOnOffControlID ZGMTR_PROVISIONALLY_AVAILABLE = 0x0000010F,
    ZGMTRDeviceTypeIDTypeMountedDimmableLoadControlID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000110,
    ZGMTRDeviceTypeIDTypeJointFabricAdministratorID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000130,
    ZGMTRDeviceTypeIDTypeIntercomID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000140,
    ZGMTRDeviceTypeIDTypeAudioDoorbellID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000141,
    ZGMTRDeviceTypeIDTypeCameraID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000142,
    ZGMTRDeviceTypeIDTypeVideoDoorbellID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000143,
    ZGMTRDeviceTypeIDTypeFloodlightCameraID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000144,
    ZGMTRDeviceTypeIDTypeSnapshotCameraID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000145,
    ZGMTRDeviceTypeIDTypeChimeID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000146,
    ZGMTRDeviceTypeIDTypeCameraControllerID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000147,
    ZGMTRDeviceTypeIDTypeDoorbellID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000148,
    ZGMTRDeviceTypeIDTypeAmbientContextSensorID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000150,
    ZGMTRDeviceTypeIDTypeProximityRangerID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000152,
    ZGMTRDeviceTypeIDTypeWindowCoveringID ZGMTR_AVAILABLE(ios(18.2), macos(15.2), watchos(11.2), tvos(18.2)) = 0x00000202,
    ZGMTRDeviceTypeIDTypeWindowCoveringControllerID ZGMTR_AVAILABLE(ios(18.2), macos(15.2), watchos(11.2), tvos(18.2)) = 0x00000203,
    ZGMTRDeviceTypeIDTypeClosureID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000230,
    ZGMTRDeviceTypeIDTypeClosurePanelID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000231,
    ZGMTRDeviceTypeIDTypeClosureControllerID ZGMTR_PROVISIONALLY_AVAILABLE = 0x0000023E,
    ZGMTRDeviceTypeIDTypeThermostatID ZGMTR_AVAILABLE(ios(18.2), macos(15.2), watchos(11.2), tvos(18.2)) = 0x00000301,
    ZGMTRDeviceTypeIDTypeTemperatureSensorID ZGMTR_AVAILABLE(ios(18.2), macos(15.2), watchos(11.2), tvos(18.2)) = 0x00000302,
    ZGMTRDeviceTypeIDTypePumpID ZGMTR_AVAILABLE(ios(18.2), macos(15.2), watchos(11.2), tvos(18.2)) = 0x00000303,
    ZGMTRDeviceTypeIDTypePumpControllerID ZGMTR_AVAILABLE(ios(18.2), macos(15.2), watchos(11.2), tvos(18.2)) = 0x00000304,
    ZGMTRDeviceTypeIDTypePressureSensorID ZGMTR_AVAILABLE(ios(18.2), macos(15.2), watchos(11.2), tvos(18.2)) = 0x00000305,
    ZGMTRDeviceTypeIDTypeFlowSensorID ZGMTR_AVAILABLE(ios(18.2), macos(15.2), watchos(11.2), tvos(18.2)) = 0x00000306,
    ZGMTRDeviceTypeIDTypeHumiditySensorID ZGMTR_AVAILABLE(ios(18.2), macos(15.2), watchos(11.2), tvos(18.2)) = 0x00000307,
    ZGMTRDeviceTypeIDTypeHeatPumpID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = 0x00000309,
    ZGMTRDeviceTypeIDTypeThermostatControllerID ZGMTR_PROVISIONALLY_AVAILABLE = 0x0000030A,
    ZGMTRDeviceTypeIDTypeEVSEID ZGMTR_AVAILABLE(ios(18.2), macos(15.2), watchos(11.2), tvos(18.2)) = 0x0000050C,
    ZGMTRDeviceTypeIDTypeDeviceEnergyManagementID ZGMTR_AVAILABLE(ios(18.2), macos(15.2), watchos(11.2), tvos(18.2)) = 0x0000050D,
    ZGMTRDeviceTypeIDTypeWaterHeaterID ZGMTR_AVAILABLE(ios(18.4), macos(15.4), watchos(11.4), tvos(18.4)) = 0x0000050F,
    ZGMTRDeviceTypeIDTypeElectricalSensorID ZGMTR_AVAILABLE(ios(18.2), macos(15.2), watchos(11.2), tvos(18.2)) = 0x00000510,
    ZGMTRDeviceTypeIDTypeElectricalUtilityMeterID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000511,
    ZGMTRDeviceTypeIDTypeMeterReferencePointID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000512,
    ZGMTRDeviceTypeIDTypeElectricalEnergyTariffID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000513,
    ZGMTRDeviceTypeIDTypeElectricalMeterID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000514,
    ZGMTRDeviceTypeIDTypeElectricalCircuitBreakerID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000516,
    ZGMTRDeviceTypeIDTypeElectricalDistributionEnclosureID ZGMTR_PROVISIONALLY_AVAILABLE = 0x00000517,
    ZGMTRDeviceTypeIDTypeControlBridgeID ZGMTR_AVAILABLE(ios(18.2), macos(15.2), watchos(11.2), tvos(18.2)) = 0x00000840,
    ZGMTRDeviceTypeIDTypeOnOffSensorID ZGMTR_AVAILABLE(ios(18.2), macos(15.2), watchos(11.2), tvos(18.2)) = 0x00000850,
} ZGMTR_AVAILABLE(ios(18.2), macos(15.2), watchos(11.2), tvos(18.2));
