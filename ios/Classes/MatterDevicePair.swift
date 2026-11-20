import Foundation
import MatterSupport
import Matter

private final class MatterDevicePairCompletionGate {
    private let lock = NSLock()
    private var completed = false
    private let completion: (String?, Error?) -> Void

    init(completion: @escaping (String?, Error?) -> Void) {
        self.completion = completion
    }

    func finish(_ code: String?, _ error: Error?) {
        lock.lock()
        let shouldComplete = !completed
        if shouldComplete {
            completed = true
        }
        lock.unlock()

        guard shouldComplete else {
            return
        }
        completion(code, error)
    }
}

@objc public class MatterDevicePair : NSObject {
    static public var appUserDefaults: UserDefaults? = nil

    private static func pairingError(code: Int, message: String) -> NSError {
        NSError(domain: "MatterDevicePair", code: code,
                userInfo: [NSLocalizedDescriptionKey: message])
    }

    @available(iOS 16.1, *)
    @objc public static func startPairDevice(onboardingPayload: String?, displayName: String, ecosystemName: String, completion: @escaping (String?, Error?) -> Void) {
        let completionGate = MatterDevicePairCompletionGate(completion: completion)

        guard let onboardingPayload, !onboardingPayload.isEmpty else {
            completionGate.finish(nil, pairingError(code: -10,
                                                    message: "onboardingPayload is required."))
            return
        }

        let homes = [MatterAddDeviceRequest.Home(displayName: displayName)]
        let topology = MatterAddDeviceRequest.Topology(ecosystemName: ecosystemName, homes: homes)
        var request = MatterAddDeviceRequest(topology: topology)

        do {
            if onboardingPayload.hasPrefix("MT:") {
                let qrCodeParser = MTRQRCodeSetupPayloadParser(base38Representation: onboardingPayload)
                request.setupPayload = try qrCodeParser.populatePayload()
            } else {
                let parser = MTRManualSetupPayloadParser(decimalStringRepresentation: onboardingPayload)
                request.setupPayload = try parser.populatePayload()
            }
        } catch {
            completionGate.finish(nil, pairingError(code: -4,
                                                    message: "Invalid onboarding payload."))
            return
        }

        Task {
            do {
                try await request.perform()

                guard let appGroupId = Bundle.main.object(forInfoDictionaryKey: "AppGroupId") as? String,
                      !appGroupId.isEmpty else {
                    completionGate.finish(nil, pairingError(code: -3,
                                                            message: "AppGroupId is not configured."))
                    return
                }

                guard let userDefaults = UserDefaults(suiteName: appGroupId) else {
                    completionGate.finish(nil, pairingError(code: -2,
                                                            message: "App Group storage is unavailable."))
                    return
                }

                let payloadKeyName = "*#commissionOnboardingPayload"
                guard let commissionOnboardingPayload = userDefaults.string(forKey: payloadKeyName),
                      !commissionOnboardingPayload.isEmpty else {
                    completionGate.finish(nil, pairingError(code: -2,
                                                            message: "Pairing payload was not returned."))
                    return
                }

                userDefaults.removeObject(forKey: payloadKeyName)
                completionGate.finish(commissionOnboardingPayload, nil)
            } catch {
                completionGate.finish(nil, pairingError(code: -1,
                                                        message: "Matter pairing failed."))
            }
        }
    }
}
