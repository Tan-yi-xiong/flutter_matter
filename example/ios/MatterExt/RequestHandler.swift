//
//  RequestHandler.swift
//  MatterExtension
//
//  Created by zero on 12/2/2025.
//  Copyright © 2025 Zhengji. All rights reserved.
//

import MatterSupport

// The extension is launched in response to `MatterAddDeviceRequest.perform()` and this class is the entry point
// for the extension operations.
@available(iOSApplicationExtension 16.1, *)
class RequestHandler: MatterAddDeviceExtensionRequestHandler {
    override func validateDeviceCredential(_ deviceCredential: MatterAddDeviceExtensionRequestHandler.DeviceCredential) async throws {
        // Use this function to perform additional attestation checks if that is useful for your ecosystem.
    }

    override func selectWiFiNetwork(from wifiScanResults: [MatterAddDeviceExtensionRequestHandler.WiFiScanResult]) async throws -> MatterAddDeviceExtensionRequestHandler.WiFiNetworkAssociation {
        // Use this function to select a Wi-Fi network for the device if your ecosystem has special requirements.
        // Or, return `.defaultSystemNetwork` to use the iOS device's current network.
        return .defaultSystemNetwork
    }

    override func selectThreadNetwork(from threadScanResults: [MatterAddDeviceExtensionRequestHandler.ThreadScanResult]) async throws -> MatterAddDeviceExtensionRequestHandler.ThreadNetworkAssociation {
        // Use this function to select a Thread network for the device if your ecosystem has special requirements.
        // Or, return `.defaultSystemNetwork` to use the default Thread network.
        return .defaultSystemNetwork
    }

    override func commissionDevice(in home: MatterAddDeviceRequest.Home?, onboardingPayload: String, commissioningID: UUID) async throws {
        // Use this function to commission the device with your Matter stack.
        let appGroupId = Bundle.main.object(forInfoDictionaryKey: "AppGroupId")
        if (appGroupId == nil) {
            throw NSError(domain: "commissionDevice", code: 1, userInfo: [NSLocalizedDescriptionKey: "ZG commissionDevice AppGroupId not set in info.plist"])
        }
        let ud = UserDefaults(suiteName: appGroupId as? String)
        let payloadKeyName = "*#commissionOnboardingPayload"
        ud?.set(onboardingPayload, forKey: payloadKeyName)
    }

    override func rooms(in home: MatterAddDeviceRequest.Home?) async -> [MatterAddDeviceRequest.Room] {
        // Use this function to return the rooms your ecosystem manages.
        // If your ecosystem manages multiple homes, ensure you are returning rooms that belong to the provided home.
        return [.init(displayName: "Living Room")]
    }

    override func configureDevice(named name: String, in room: MatterAddDeviceRequest.Room?) async {
        // Use this function to configure the (now) commissioned device with the given name and room.
    }
}
