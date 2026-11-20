# Device validation

Device validation checks behavior that the Dart CI gate cannot exercise. It is manual by design: there is no hosted hardware runner or automated cross-device UI test.

Every Run uses a real Matter commissionee. The device-test app passes the raw onboarding payload to the Matter SDK, which performs discovery and commissioning. A commissioning failure is preserved and is not retried in the same Run.

## Roles and terms

- **Controller:** Android app or physical iPhone running `device_test_app`.
- **Commissionee:** Matter On/Off device used by the Run.
- **Clean cycle:** a complete validation Run that starts with a factory-reset commissionee and an open commissioning window.
- **Device-behavior change:** a change affecting commissioning, BLE, network discovery, Wi-Fi/Thread provisioning, controller lifecycle, attributes, commands, subscriptions, callbacks, MethodChannel behavior, or native Matter code.

## Choose a commissionee

The commissionee must:

- support factory reset and recommissioning with a valid setup payload or manual code;
- be discoverable by the Matter SDK;
- expose On/Off on endpoint `1`, cluster `0x0006`;
- support Basic Information `NodeLabel` on endpoint `0`, cluster `0x0028`, attribute `0x0005`;
- allow an independent state change through a physical control, vendor app, or another local controller.

If no suitable commissionee is available, stop and record the blocker. Do not mark a test passed without executing it.

## Android virtual device

The bundled Matter Virtual Device App can simulate an On/Off commissionee on Android. It can run on the controller phone or another Android device on the same network.

### Install

```sh
adb -s <device-serial> install -r device_test_app/third_party/virtual-device-app.apk

adb -s <device-serial> shell pm grant com.matter.virtual.device.app android.permission.BLUETOOTH_CONNECT
adb -s <device-serial> shell pm grant com.matter.virtual.device.app android.permission.ACCESS_FINE_LOCATION
adb -s <device-serial> shell pm grant com.matter.virtual.device.app android.permission.BLUETOOTH_SCAN
adb -s <device-serial> shell pm grant com.matter.virtual.device.app android.permission.BLUETOOTH_ADVERTISE
```

Reapply the grants after `pm clear`.

### Start

1. Open the VDA and select `Matter OnOff Switch`.
2. Keep the discriminator and setup PIN consistent with the onboarding payload supplied to the app.
3. Select `SAVE`, then `Start`.
4. Confirm the commissioning window is actually open.

The QR page alone is not proof that the device is advertising. When diagnosing startup, `dns-sd -B _matterc._udp` can confirm the advertisement.

### Restart quirk

The first start after launching the VDA can show the QR page without an mDNS advertisement. Recover by pressing BACK, confirming **Factory Reset**, reopening the VDA, selecting the OnOff device, and starting it again. Verify the advertisement before beginning the Run.

### Same-phone use

Keep the controller and VDA unlocked during the Run. A locked screen can hide commissionee advertisements. Force-stopping the test app also removes its ADB reverse/forward state; reconnect the bridge before continuing.

## Hardware layout

| Role | Requirement |
| --- | --- |
| Controller | Android phone or physical iPhone with the test app installed |
| Commissionee | Matter On/Off device with NodeLabel support and an open commissioning window |
| Network | Controller and commissionee can reach the target Wi-Fi network and maintain CASE and multicast traffic |
| Build host | Flutter 3.41.0; Android SDK/JDK 17; for iOS, macOS with Xcode 16.4+ and CocoaPods 1.17 |

iOS signing and provisioning are local maintainer configuration. Never commit credentials or provisioning profiles.

## Clean cycle procedure

For each affected controller platform:

1. Factory-reset the commissionee and open its commissioning window.
2. Provide the target Wi-Fi SSID and password. An empty password is valid only for an open network.
3. Start the app. It purges stale Run state, old provisioning secrets, orphaned keys, and controller identities before persisting new secrets.
4. Run the `full` profile. The Matter SDK performs discovery and commissioning from the raw onboarding payload.
5. Preserve every result. Do not retry a failed commission or P0 case inside the same Run.
6. Save the generated JSON and Markdown reports and verify the plugin commit.
7. Factory-reset the commissionee or remove the test fabric before the next clean cycle.

A failed or interrupted Run can leave a fabric behind. The post-Run **Commissionee cleanup** card only purges Run secrets and records operator confirmation; it does not reset the commissionee or remove the fabric.

## Test matrix

| Test ID | Priority | Purpose |
| --- | --- | --- |
| `build_install` | P0 | Build installs and launches |
| `commissioning` | P0 | PASE commissioning succeeds through SDK-managed discovery |
| `operational_connect` | P0 | CASE connection returns a connect context |
| `onoff_invoke` | P0 | Off, On, and Toggle succeed and change state |
| `onoff_subscription` | P0 | A command-triggered state change reaches an active subscription |
| `node_label_read_write` | P0 | NodeLabel write/read round trip succeeds |
| `invalid_setup_passcode` | P0 | Incorrect same-discriminator passcode fails clearly without a crash |
| `app_restart` | P1 | Reloads persisted credentials, releases the CASE session, and reconnects without recommissioning |

The report contract defines exact timeouts, result rules, and required fields. See [Device Test Report Contract](device-test-report.md).

The `quick` profile contains `build_install`, `commissioning`, `operational_connect`, and `onoff_invoke`. It is iteration feedback only.

## Evidence and gates

For a device-behavior pull request:

- Attach a schema v4 `device-test-report.json` and its generated Markdown summary.
- Ensure the report `plugin_commit` equals the pull-request head.
- Cover Android and physical iOS when behavior is shared, or explain the platform-specific exception.
- Keep screenshots and any other evidence bounded and sanitized.

For a stable release, provide separate Android and physical-iOS clean P0 cycles for the release-candidate commit. Do not tag when any required P0 result is missing, failed, not run, stale, or from another commit.

The Dart CI gate does not prove native compilation or device behavior. A successful build is not a substitute for a Run.

## Known limits

- iOS simulator is unsupported.
- iOS NSD routing is not implemented.
- `pairDeviceWithAddress` and `dataVersionFilters` are Android-only.
- Hosted CI does not run physical-device tests.
- The example app has no automated test role.
