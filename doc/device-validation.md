# Device Validation

This document defines the manual device-validation process for `flutter_matter`. It separates device behavior checks from the required Dart CI gate and defines the evidence a reviewer must see before a device-behavior pull request or stable release can be accepted.

The process is manual by design. It does not require or define a self-hosted runner, an Actions hardware workflow, or an automated cross-device UI test.

Every device Run uses a Matter commissionee. The app discovers the commissionee concurrently over BLE and Wi-Fi/IP and uses the first matching transport. It records `ble` or `ip` as the actual commissioning transport. A commissioning failure is preserved and is never retried through the other transport in the same Run.

## Definitions

- **Controller**: the Android or physical iOS app that discovers, commissions, connects to, and controls a Matter device.
- **Commissionee**: a Matter On/Off device used for validation.
- **Clean cycle**: a complete validation run that starts with a factory-reset commissionee and an open commissioning window.
- **Device-behavior change**: a change that affects commissioning, network discovery, Wi-Fi provisioning, controller lifecycle, attributes, commands, subscriptions, callbacks, MethodChannel contracts, or native Matter behavior.

## Commissionee selection

A suitable Matter commissionee is required for every device Run, including quick iteration. It is suitable when all of the following are true:

- It can be restored to factory state and commissioned again with a valid setup code or setup payload.
- It can be discovered through BLE commissionable discovery, Wi-Fi/IP commissionable discovery, or both.
- It exposes an On/Off server on endpoint `1`, cluster `0x0006`.
- It supports Basic Information `NodeLabel` on endpoint `0`, cluster `0x0028`, attribute `0x0005`.
- Its state can be changed independently through a physical control, a vendor app, or another local controller.

If no suitable commissionee is available, stop validation and record the blocker. Do not mark results as passed without executing the Run.

## Hardware layout

Formal validation requires:

| Role | Requirement |
| --- | --- |
| Controller | An Android phone or physical iPhone running `device_test_app` |
| Commissionee | A Matter On/Off device |
| Network | A non-isolated trusted Wi-Fi network for provisioning and CASE/control |

The controller must be able to reach the target Wi-Fi network. The commissionee may be discovered over BLE before Wi-Fi provisioning or over Wi-Fi/IP before commissioning. Disable VPNs and private DNS behavior that could block local Matter discovery. Use a temporary test network rather than personal or production credentials whenever possible.

The iOS controller must run on a physical iPhone. The vendored `ZGMatter.framework` has no simulator slice, so simulator results are not valid evidence.

## Toolchain and app builds

Record the exact toolchain used in the generated report.

- Flutter: `3.41.0` from `.fvmrc`.
- Android build host: JDK 17 and Android SDK 34 or later.
- iOS build host: macOS with Xcode 16.4 or later and CocoaPods 1.17.
- iOS installation: a maintainer signs the app locally with a valid Apple Development identity and provisioning profile. Signing credentials, provisioning profiles, and private keys must never be committed to the repository or included in evidence.

Use `device_test_app/` as the primary validation surface. A manual interim report may still conform to the same report contract, but it must not claim that the dedicated app generated it.

## Clean cycle procedure

For each controller platform that the change requires:

1. Restore the Matter commissionee to factory state.
2. Open the commissioning window.
3. Restart both devices and confirm Bluetooth, camera, local-network, and commissioning prerequisites are ready.
4. Provide the target Wi-Fi SSID and password. An empty password is valid only for an open network.
5. Confirm the commissionee reset and commissioning-window state through the setup prompt.
6. Let the app automatically purge old run secrets and reset controller identities for the current platform before the Run.
7. Let the app perform concurrent BLE and Wi-Fi/IP discovery and select the first matching transport.
8. Run every P0 scenario in the order below without replacing a failed result with a later retry.
9. Save the generated JSON and Markdown reports. Add manually captured screenshots only when they are bounded and sanitized.
10. Verify the report schema version and commit before attaching evidence.

The user does not certify controller cleanup or secret purge. If automatic cleanup fails, the Run is blocked before new provisioning state is persisted.

## P0 scenarios

| Priority | Test ID | Requirement |
| --- | --- | --- |
| P0 | `build_install` | Android APK or signed iOS app installs and launches |
| P0 | `commissioning_discovery` | Concurrent BLE and Wi-Fi/IP discovery identifies the selected commissionee and selects the first matching transport |
| P0 | `commissioning` | PASE/commissioning completes on the selected transport with `errorCode == 0` within 120 seconds |
| P0 | `operational_connect` | CASE connection returns a valid connect context within 30 seconds |
| P0 | `onoff_invoke` | Off, On, and Toggle succeed within 10 seconds and change state |
| P0 | `onoff_subscription` | Initial state and an external update arrive within 15 seconds |
| P0 | `node_label_persistence` | NodeLabel write/read succeeds and survives a commissionee restart |

A P0 `failed`, timeout, error, crash, or skipped result must be preserved. A failed P0 test must not be retried inside the same Run to manufacture a passing result.

## P1 and P2 scenarios

P1 results provide stability evidence and do not independently block a stable release:

- `app_restart`: restart the controller without recommissioning and reconnect to the saved node.
- `factory_reset_recommission`: confirm that a subsequent factory reset and commissioning cycle succeeds without relying on old fabric state.

P2 results record defects and must be included in the report:

- `invalid_setup_passcode`: an invalid passcode returns a clear non-zero failure without a crash.
- `invalid_wifi_password`: provisioning fails clearly without reporting false success.
- `remove_fabric_ui`: existing remove/delete-device UI behavior is recorded accurately.

A P2 failure does not block by default. The maintainer must record the failure and explicitly decide whether it is acceptable for the candidate. Do not claim that the missing public `unPairDevice` method was verified by the existing UI delete flow.

## Report and evidence rules

The dedicated device-test app, or an interim manual reporter, must produce both:

- `device-test-report.json` conforming to schema v3.
- `device-test-report.md` generated from the same test data for direct use in a pull request.

A valid report records:

- Automatically parsed `vendor_id` and `product_id`.
- The actual commissioning transport: `ble` or `ip`.
- `network_transport: "wifi"`.
- No commissionee model, firmware, or external state-change fields.

A report cannot be reused after relevant code changes. Record the test app version and commit separately from the plugin commit.

Submit a device-behavior report as follows:

1. Paste the generated Markdown summary into the Device Validation section of the pull request.
2. Upload the sanitized JSON file. Manually captured screenshots or other bounded evidence are optional.
3. Link the uploaded files from the Markdown summary and the Device Validation section.
4. Confirm that public GitHub attachments contain no sensitive information.

GitHub attachments in this public repository are public. Never attach device serial numbers, iOS UDIDs, Wi-Fi SSIDs, Wi-Fi passwords, onboarding payloads, setup codes, BLE addresses, certificates, private keys, or complete raw `logcat` output. Keep setup codes and Wi-Fi credentials offline.

## Pull request and release gates

Device-behavior pull requests must include reports for every affected platform:

- Shared Dart, MethodChannel, JSON, callback, or native Matter behavior requires both Android and iOS reports.
- An explicitly platform-specific change requires the affected platform report and a clear statement that the other platform is unaffected.
- Documentation, CI, packaging, and non-device Dart changes may mark device validation as `Not applicable` and explain why.

For a stable release, the release-preparation pull request must contain:

- One clean Android P0 report and one clean iOS P0 report for the candidate commit.
- A schema v3 report for each platform.
- Sanitized JSON attachments for both reports; screenshots are optional manual evidence.
- A maintainer confirmation that all required P0 results passed and that P1/P2 results were reviewed.

The stable version tag must not be created when any required P0 result is `Failed` or `Not run`, when the report commit does not match the candidate, when `network_transport` is not `wifi`, when `commissioning_transport` is neither `ble` nor `ip`, or when the required transport fields are invalid.

## Known limits

- The repository has no supported public `unPairDevice` method; only the existing UI delete path can be evaluated.
- iOS simulator results are not valid evidence.
- Hardware-in-the-loop CI and fully automated iOS external-app control remain outside formal acceptance.
- The device-test workflow has no Thread commissioning path.
