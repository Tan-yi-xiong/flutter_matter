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

The Matter Virtual Device App (VDA) simulates a Matter On/Off commissionee on an Android phone. Use it when no real device is available. It can run on the controller phone itself or on a separate Android device on the same Wi-Fi network.

### Bundled APK

A prebuilt APK ships at `device_test_app/third_party/virtual-device-app.apk`, so no real device is needed. It was built from `connectedhomeip` commit `1a11f9956e` (SHA-256 `d100e00740a7b22785afe01d815d190786521d602091dbeebf117ee19e7f622a`). Install it with the Bluetooth and location permissions granted (re-run the grants after `pm clear`):

```bash
adb -s <device-serial> install -r device_test_app/third_party/virtual-device-app.apk
adb -s <device-serial> shell pm grant com.matter.virtual.device.app android.permission.BLUETOOTH_CONNECT
adb -s <device-serial> shell pm grant com.matter.virtual.device.app android.permission.ACCESS_FINE_LOCATION
adb -s <device-serial> shell pm grant com.matter.virtual.device.app android.permission.BLUETOOTH_SCAN
adb -s <device-serial> shell pm grant com.matter.virtual.device.app android.permission.BLUETOOTH_ADVERTISE
```

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

A completed `full` Run ends with `fabric_remove`, so the commissionee returns to its uncommissioned state and no fabric slot is consumed. Only a Run that ends early (failed or stopped before `fabric_remove`) leaves its fabric on the commissionee. After such a Run, reset the device through either of:

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

1. Make sure the commissionee has an open commissioning window. A factory reset is optional: a completed `full` Run removes its own fabric, so prefer resetting the commissionee only after an incomplete Run left a fabric behind.
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
| P0 | `onoff_subscription` | An OnOff command triggers a state change and the subscription reports it within the timeout |
| P0 | `node_label_read_write` | NodeLabel write/read round trip succeeds through the library |

A P0 `failed`, timeout, error, crash, or skipped result must be preserved. A failed P0 test must not be retried inside the same Run to manufacture a passing result.

## P1 scenarios

P1 results provide stability evidence and do not independently block a stable release:

- `app_restart`: rebuild the controller runtime from persisted credentials and reconnect to the saved node without recommissioning.
- `fabric_remove`: the fabric-removal command is accepted over CASE and the commissionee no longer accepts CASE afterwards. Device reset is expressed as a library command, not as a manual factory-reset step.

## P0 negative scenario

- `invalid_setup_passcode`: after the main commissioning, the controller re-opens a commissioning window with the original discriminator and passcode (revoke-then-open, mirroring the worked example), then attempts commissioning with a well-formed payload carrying a deliberately incorrect passcode. The attempt must return a clear non-zero failure without a crash. A failed PASE handshake adds no fabric to the commissionee.

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
- A maintainer confirmation that all required P0 results passed and that P1 results were reviewed.

The stable version tag must not be created when any required P0 result is `Failed` or `Not run`, when the report commit does not match the candidate, when `network_transport` is not `wifi`, or when any required report field is invalid.

## Known limits

- The repository has no supported public `unPairDevice` method; the `fabric_remove` CASE command is the supported removal path.
- iOS simulator results are not valid evidence.
- Android validation uses the virtual device app on the controller phone. The 9-item `full` matrix performs every test action through library APIs with no operator prompts; only VDA recovery (the documented restart quirk) and post-Run cleanup remain device-side actions.
- Hardware-in-the-loop CI remains outside formal acceptance.
- The device-test workflow has no Thread commissioning path.
