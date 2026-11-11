# Device Validation

This document defines the manual device-validation process for `flutter_matter`. It separates device behavior checks from the required Dart CI gate and defines the evidence a reviewer must see before a device-behavior pull request or stable release can be accepted.

The process is manual by design. It does not require or define a self-hosted runner, an Actions hardware workflow, or an automated cross-device UI test.

Formal acceptance uses **Wi-Fi/IP commissioning**. A Run must not perform BLE discovery, a BLE pre-scan, or a GATT connection. Future validation uses qualified real Matter hardware only; the Android Virtual Matter Device App path is retired, and virtual-device results are not valid evidence.

## Definitions

- **Controller**: the Android or physical iOS app that discovers, commissions, connects to, and controls a Matter device.
- **Commissionee**: a qualified real Matter device used for formal validation.
- **Development commissionee**: there is no separate development commissionee. Quick iteration, when a device run is performed, still uses a qualified real Matter device; quick reports are not formal PR or release evidence.
- **Clean cycle**: a complete validation run that starts with a factory-reset commissionee and a controller with no previous fabric or saved device state.
- **Device-behavior change**: a change that affects commissioning, network discovery, Wi-Fi provisioning, controller lifecycle, attributes, commands, subscriptions, callbacks, MethodChannel contracts, or native Matter behavior.

## Commissionee selection

A qualified real Matter device is required for every device Run, including quick iteration. It is qualified when all of the following are true:

- It can be restored to factory state and commissioned again with a valid setup code or setup payload.
- It advertises the Matter on-network discovery capability in its setup payload.
- Its commissioning transport is `ip`.
- It is connected to the same trusted Wi-Fi/LAN as the controller.
- It exposes an On/Off server on endpoint `1`, cluster `0x0006`.
- It supports Basic Information `NodeLabel` on endpoint `0`, cluster `0x0028`, attribute `0x0005`.
- Its state can be changed independently through a physical control, a vendor app, or another local controller.

If a qualified real device is unavailable, stop validation. Do not substitute a virtual commissionee in any Run, including quick iteration, and do not mark results as passed from virtual-device evidence.

## Hardware layout

Formal validation requires:

| Role | Requirement |
| --- | --- |
| Controller | An Android phone or physical iPhone running `device_test_app` |
| Commissionee | A qualified real Matter On/Off device |
| Network | One non-isolated trusted Wi-Fi/LAN reachable by both devices |

Both the controller and the commissionee must be connected to the same non-isolated trusted Wi-Fi/LAN. Disable VPNs and private DNS behavior that could block local Matter discovery. Use a temporary test network rather than personal or production credentials whenever possible.

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

1. Restore the real Matter commissionee to factory state.
2. Remove the controller app or clear its application data so no fabric, node, or certificate state remains.
3. Restart both devices and confirm the trusted Wi-Fi/LAN, camera permission, local-network permission, and commissioning prerequisites are ready.
4. Put the real commissionee in an open commissioning window. Do not start a BLE pre-scan or GATT connection.
5. Run `ip_discovery` and `ip_commissioning` over Wi-Fi/IP using a new setup code or setup payload. `ip_discovery` is a readiness check: it verifies that the setup payload advertises the on-network discovery capability and that the selected commissioning transport is `ip`; it does not itself perform discovery. The controller performs the actual mDNS/IP discovery during `ip_commissioning`.
6. Run every P0 scenario in the order below without replacing a failed result with a later retry.
7. Save the generated JSON and Markdown reports. Add manually captured screenshots only when they are sanitized and useful.

Android and iOS are separate clean cycles. The real Matter device must be factory-reset and recommissioned between the Android and iOS cycles.

## P0 matrix

Each required controller platform must pass one clean P0 cycle for a stable release candidate. A device-behavior pull request must provide the platform report or reports required by its scope.

| ID | Scenario | Pass criteria |
| --- | --- | --- |
| `build_install` | Build and install the controller app | Android debug APK or signed iOS app launches without a crash; required permissions are reachable |
| `ip_discovery` | Verify the setup payload advertises on-network discovery | The QR setup payload advertises the Matter on-network discovery capability and the selected commissioning transport is `ip` |
| `ip_commissioning` | Commission the real device over Wi-Fi/IP | The controller discovers the commissionee over mDNS/IP, completes PASE/commissioning with `errorCode == 0` within 120 seconds, and never performs a BLE pre-scan or GATT connection |
| `operational_connect` | Connect to the commissioned node | CASE connection succeeds and a `connectContext` is obtained within 30 seconds |
| `onoff_invoke` | Send Off, On, and Toggle to endpoint `1`, cluster `0x0006` | Each response succeeds within 10 seconds and the commissionee state changes |
| `onoff_subscription` | Subscribe to endpoint `1`, cluster `0x0006`, attribute `0x0000` | Initial state is received; an externally triggered state change is reported within 15 seconds |
| `node_label_persistence` | Write and read endpoint `0`, cluster `0x0028`, attribute `0x0005` | Written value is read back, survives a commissionee restart, and is not stale or empty |

A P0 `failed`, timeout, error, crash, or skipped result must be preserved. A failed P0 test must not be retried inside the same Run to manufacture a passing result.

## P1 and P2 scenarios

P1 results provide stability evidence and do not independently block a stable release:

- `app_restart`: restart the controller without recommissioning and reconnect to the saved node.
- `factory_reset_recommission`: confirm that a subsequent factory reset and full Wi-Fi/IP commissioning cycle succeeds without relying on old fabric state.

P2 results record defects and must be included in the report:

- Invalid setup passcode.
- Invalid Wi-Fi password.
- Existing remove/delete-device UI flow.

A P2 failure does not block by default. The maintainer must record the failure and explicitly decide whether it is acceptable for the candidate. Do not claim that the missing public `unPairDevice` method was verified by the existing UI delete flow.

## Report and evidence rules

The dedicated device-test app, or an interim manual reporter, must produce both:

- `device-test-report.json` conforming to the schema-versioned report contract.
- `device-test-report.md` generated from the same test data for direct use in a pull request.

A formal report must record `commissionee.type: "real"`, `commissionee.commissioning_transport: "ip"`, and `commissionee.network_transport: "wifi"`. Virtual-commissionee reports are not supported; every device run, including quick iteration, uses qualified real Matter hardware.

The report's `plugin_commit` must match the pull request head or the release-candidate commit. A report cannot be reused after relevant code changes. Record the test app version and commit separately from the plugin commit.

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
- A qualified real-device report for each platform; virtual-device reports do not satisfy this requirement.
- Sanitized JSON attachments for both reports; screenshots are optional manual evidence.
- A maintainer confirmation that all required P0 results passed and that P1/P2 results were reviewed.

The stable version tag must not be created when any required P0 result is `Failed` or `Not run`, when the report commit does not match the candidate, when the commissioning transport is not `ip`, or when the commissionee is not real hardware.

## Known limits

- The repository has no supported public `unPairDevice` method; only the existing UI delete path can be evaluated.
- iOS simulator results are not valid evidence.
- Thread-specific credentials, ICD-specific behavior, BLE commissioning, and fully automated iOS external-app control remain outside formal acceptance. The virtual-device path is retired entirely.
