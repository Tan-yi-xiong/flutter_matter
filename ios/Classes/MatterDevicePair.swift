
import Foundation
import MatterSupport
import Matter

@objc public class MatterDevicePair : NSObject {
    static public var appUserDefaults: UserDefaults? = nil
    
    @available(iOS 16.1, *)
    @objc public static func startPairDevice(onboardingPayload: String?, displayName: String, ecosystemName: String, completion: @escaping (String?, Error?) -> Void) {
        let homes = [MatterAddDeviceRequest.Home(displayName: displayName)]
        let topology = MatterAddDeviceRequest.Topology(ecosystemName: ecosystemName, homes: homes)
        var request = MatterAddDeviceRequest(topology: topology)
        if (onboardingPayload != nil) {
            if (!onboardingPayload!.hasPrefix("MT:")) {
                let parser = MTRManualSetupPayloadParser(decimalStringRepresentation: onboardingPayload!)
                request.setupPayload = try? parser.populatePayload()
            } else {
                let qrCodeParser = MTRQRCodeSetupPayloadParser(base38Representation: onboardingPayload!)
                request.setupPayload = try? qrCodeParser.populatePayload()
            }
            
        }
        Task {
            do {
                
                // vendorID == 0 && productID == 0 is share Device
                if (request.setupPayload?.vendorID == 0 && request.setupPayload?.productID == 0) {
                    completion(onboardingPayload, nil)
                    return
                }
                
                try await request.perform()
                let appGroupId = Bundle.main.object(forInfoDictionaryKey: "AppGroupId")
                if (appGroupId == nil) {
                    completion(nil, NSError(domain: "MatterDevicePair", code: -3, userInfo: [NSLocalizedDescriptionKey: "AppGroupId not set in info.plist"]))
                    return
                }
                let ud = UserDefaults(suiteName: appGroupId as? String)
                if (ud == nil) {
                    completion(nil, NSError(domain: "MatterDevicePair", code: -2, userInfo: [NSLocalizedDescriptionKey: "appUserDefaults not set"]))
                    return
                }
                let payloadKeyName = "*#commissionOnboardingPayload"
                let commissionOnboardingPayload = ud?.string(forKey: payloadKeyName)
                if (commissionOnboardingPayload == nil) {
                    completion(nil, NSError(domain: "MatterDevicePair", code: -2, userInfo: [NSLocalizedDescriptionKey: "commissionOnboardingPayload not set"]))
                } else {
                    ud?.removeObject(forKey: payloadKeyName)
                    completion(commissionOnboardingPayload, nil)
                }
            } catch {
                completion(nil, NSError(domain: "MatterDevicePair", code: -1, userInfo: [NSLocalizedDescriptionKey: "PairFailed"]))
            }
        }
    }
}
