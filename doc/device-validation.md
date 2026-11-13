# Device Validation

This document defines the manual device-validation process for `flutter_matter`. It separates device behavior checks from the required Dart CI gate and defines the evidence a reviewer must see before a device-behavior pull request or stable release can be accepted.

The process is manual by design. It does not require or define a self-hosted runner, an Actions hardware workflow, or an automated cross-device UI test.

Every device Run uses a Matter commissionee. The app passes the raw onboarding payload directly to the Matter SDK, which performs commissionee discovery and commissioning. A commissioning failure is preserved and is never retried in the same Run.

## Definitions

- **Controller**: the Android or physical iOS app that discovers, commissions, connects to, and controls a Matter device.
- **Commissionee**: a Matter On/Off device used for validation.
- **Clean cycle**: a complete validation run that starts with a factory-reset commissionee and an open commissioning window.
- **Device-behavior change**: a change that affects commissioning, network discovery, Wi-Fi provisioning, controller lifecycle, attributes, commands, subscriptions, callbacks, MethodChannel contracts, or native Matter behavior.

## Commissionee selection

A suitable Matter commissionee is required for every device Run, including quick iteration. It is suitable when all of the following are true:

- It can be restored to factory state and commissioned again with a valid setup code or setup payload.
- It can be discovered by the Matter SDK through its supported commissioning transports.
- It exposes an On/Off server on endpoint `1`, cluster `0x0006`.
- It supports Basic Information `NodeLabel` on endpoint `0`, cluster `0x0028`, attribute `0x0005`.
- Its state can be changed independently through a physical control, a vendor app, or another local controller.

If no suitable commissionee is available, stop validation and record the blocker. Do not mark results as passed without executing the Run.

## Virtual commissionee (Android VDA)

The Matter Virtual Device App (VDA) is a supported commissionee for iteration and validation on Android. It can run on the controller phone itself or on a separate Android device on the same Wi-Fi network.

### Starting a virtual device

1. Open the VDA and pick `Matter OnOff Switch` from the device list.
2. Review the setup form (device name, discriminator, transport). Keep the discriminator and setup PIN consistent with the onboarding payload passed to `start_run`.
3. Tap `SAVE`, then `Start` on the confirmation page. The app shows the QR payload and manual pairing code.

A started device is ready when `dns-sd -B _matterc._udp` shows an advertisement. The QR page alone does not prove the commissioning window is open.

### Restart quirk

The first `Start` after the app launches can show the QR page without an mDNS advertisement. To recover:

1. Press BACK on the QR page.
2. Confirm the `Factory Reset` dialog.
3. Reopen the VDA, pick the OnOff device again, `SAVE`, and `Start`.

The advertisement appears after this second start. Verify with `dns-sd -B _matterc._udp` before starting the Run.

### Same-phone caveats

- Keep both phones (or the single phone) unlocked during the Run: a locked screen can hide the commissionee's mDNS advertisements from the network.
- Force-stopping the test app also removes the reverse/forward state on the phone; relaunch the app and re-establish the bridge if needed.

### Fabric accumulation

Every commissioned Run adds one fabric to the virtual device, and fabric slots are limited. After a finished Run, reset the device through either of:

- the test app's optional post-Run `Commissionee cleanup` card (purges Run secrets and records a bridge event), or
- the VDA itself: BACK on the QR page and confirm the `Factory Reset` dialog.

The next Run then starts from a clean fabric table.

## Hardware layout

Formal validation requires:

| Role | Requirement |
| --- | --- |
| Controller | An Android phone or physical iPhone running `device_test_app` |
| Commissionee | A Matter On/Off device |
| Network | A non-isolated trusted Wi-Fi network for provisioning and CASE/control |

The controller must be able to reach the target Wi-Fi network. Commissionee discovery is delegated to the Matter SDK. Disable VPNs and private DNS behavior that could block local Matter discovery. Use a temporary test network rather than personal or production credentials whenever possible.

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

1. Make sure the commissionee has an open commissioning window. A factory reset is optional: every Run adds one fabric, so prefer resetting the commissionee after a finished Run instead of before each one.
2. Provide the target Wi-Fi SSID and password. An empty password is valid only for an open network.
3. Let the app automatically purge old run secrets, purge orphaned provisioning keys, and reset controller identities for the current platform before the Run.
4. Start the Run and let the Matter SDK perform discovery and commissioning from the raw onboarding payload.
5. Run every P0 scenario in the order below without replacing a failed result with a later retry.
6. Save the generated JSON and Markdown reports. Add manually captured screenshots only when they are bounded and sanitized.
7. Verify the report schema version and commit before attaching evidence.

The user does not certify controller cleanup or secret purge. If automatic cleanup fails, the Run is blocked before new provisioning state is persisted. Interrupted Runs are discarded at startup; never resume them.

The user does not certify controller cleanup or secret purge. If automatic cleanup fails, the Run is blocked before new provisioning state is persisted.

## P0 scenarios

| Priority | Test ID | Requirement |
| --- | --- | --- |
| P0 | `build_install` | Android APK or signed iOS app installs and launches |
| P0 | `commissioning` | PASE/commissioning completes through SDK-managed discovery with `errorCode == 0` within 120 seconds |
| P0 | `operational_connect` | CASE connection returns a valid connect context within 30 seconds |
| P0 | `onoff_invoke` | Off, On, and Toggle succeed within 10 seconds and change state |
| P0 | `onoff_subscription` | Initial state and an external update arrive within 15 seconds |
| P0 | `node_label_persistence` | NodeLabel write/read succeeds and survives a commissionee restart |

A P0 `failed`, timeout, error, crash, or skipped result must be preserved. A failed P0 test must not be retried inside the same Run to manufacture a passing result.

## P1 and P2 scenarios

P1 results provide stability evidence and do not independently block a stable release:

- `app_restart`: rebuild the controller runtime from persisted credentials and reconnect to the saved node without recommissioning.
- `factory_reset_recommission`: confirm that a subsequent factory reset and commissioning cycle succeeds without relying on old fabric state.

P2 results record defects and must be included in the report:

- `invalid_setup_passcode`: a negative validation run uses a well-formed setup payload with a deliberately incorrect setup passcode and the same discriminator, and must return a clear non-zero failure without a crash.
- `invalid_wifi_password`: provisioning fails clearly without reporting false success.
- `remove_fabric_ui`: existing remove/delete-device UI behavior is recorded accurately.

A P2 failure does not block by default. The maintainer must record the failure and explicitly decide whether it is acceptable for the candidate. Do not claim that the missing public `unPairDevice` method was verified by the existing UI delete flow.

## Report and evidence rules

The dedicated device-test app, or an interim manual reporter, must produce both:

- `device-test-report.json` conforming to schema v4.
- `device-test-report.md` generated from the same test data for direct use in a pull request.

A valid report records:

- Automatically parsed `vendor_id` and `product_id`.
- `network_transport: "wifi"`.
- No commissioning-transport field.
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
- A schema v4 report for each platform.
- Sanitized JSON attachments for both reports; screenshots are optional manual evidence.
- A maintainer confirmation that all required P0 results passed and that P1/P2 results were reviewed.

The stable version tag must not be created when any required P0 result is `Failed` or `Not run`, when the report commit does not match the candidate, when `network_transport` is not `wifi`, or when any required report field is invalid.

## Known limits

- The repository has no supported public `unPairDevice` method; only the existing UI delete path can be evaluated.
- iOS simulator results are not valid evidence.
- Hardware-in-the-loop CI and fully automated iOS external-app control remain outside formal acceptance.
- The device-test workflow has no Thread commissioning path.
