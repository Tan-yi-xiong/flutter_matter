# flutter_matter

A low-level Matter controller plugin for Flutter on Android and iOS. It provides commissioning, operational connections, Interaction Model operations, BLE hooks, and TLV helpers backed by the native Matter SDKs.

<p align="center">
  <img src="https://raw.githubusercontent.com/Tan-yi-xiong/flutter_matter/main/images/demo.gif" alt="flutter_matter example app" width="320" />
</p>

<p align="center">
  <a href="https://github.com/Tan-yi-xiong/flutter_matter/actions/workflows/dart-gate.yml"><img src="https://github.com/Tan-yi-xiong/flutter_matter/actions/workflows/dart-gate.yml/badge.svg" alt="Dart Gate"></a>
  <a href="https://pub.dev/packages/flutter_matter"><img src="https://img.shields.io/pub/v/flutter_matter.svg" alt="pub.dev version"></a>
  <a href="https://github.com/Tan-yi-xiong/flutter_matter/blob/main/LICENSE"><img src="https://img.shields.io/badge/license-MIT-blue.svg" alt="MIT License"></a>
</p>

## Quick start

```sh
flutter pub add flutter_matter
```

```dart
import 'package:flutter_matter/flutter_matter.dart';
```

Follow [Getting started](https://github.com/Tan-yi-xiong/flutter_matter/blob/main/doc/getting-started.md) to configure Android or iOS and commission a first device. iOS requires a physical arm64 device; the simulator is not supported.

## What it provides

- BLE and on-network commissioning, including open Wi-Fi and Thread credentials.
- Controller lifecycle, CASE connection ownership, and ICD registration callbacks.
- Attribute and event reads, writes, commands, subscriptions, and wildcard paths.
- Fabric management through OperationalCredentials `read` and `invoke`.
- Optional custom GATT transport on Android, plus DNS-SD helpers on Android.
- TLV primitives and Basic Information/Descriptor cluster helpers.

This is a controller-side plugin. It does not turn an app into a Matter commissionee.

## Documentation

### Start here

- [Getting started](https://github.com/Tan-yi-xiong/flutter_matter/blob/main/doc/getting-started.md)

### Guides

- [Commissioning](https://github.com/Tan-yi-xiong/flutter_matter/blob/main/doc/commissioning.md)
- [Device operations](https://github.com/Tan-yi-xiong/flutter_matter/blob/main/doc/device-operations.md)
- [Example app](https://github.com/Tan-yi-xiong/flutter_matter/blob/main/example/README.md)

### Reference

- [Public API](https://github.com/Tan-yi-xiong/flutter_matter/blob/main/doc/public-api.md)
- [Platform support](https://github.com/Tan-yi-xiong/flutter_matter/blob/main/doc/platform-support.md)

### Maintainers

- [ZGMatter framework build](https://github.com/Tan-yi-xiong/flutter_matter/blob/main/doc/zgmatter-build.md)
- [Architecture](https://github.com/Tan-yi-xiong/flutter_matter/blob/main/ARCHITECTURE.md)
- [Contributing](https://github.com/Tan-yi-xiong/flutter_matter/blob/main/CONTRIBUTING.md)
- [Device validation](https://github.com/Tan-yi-xiong/flutter_matter/blob/main/doc/device-validation.md)
- [Device test report contract](https://github.com/Tan-yi-xiong/flutter_matter/blob/main/doc/device-test-report.md)
- [Release process](https://github.com/Tan-yi-xiong/flutter_matter/blob/main/doc/releasing.md)

## Example app

The [example app](https://github.com/Tan-yi-xiong/flutter_matter/blob/main/example/README.md) is the complete runnable reference for commissioning, device control, the Interaction Model console, NSD, and Android Google Home dual-fabric commissioning. Its README maps each feature to the relevant source file and symbol.

## Security

Report vulnerabilities privately through [GitHub security advisories](https://github.com/Tan-yi-xiong/flutter_matter/security/advisories/new). Do not include setup codes, Wi-Fi credentials, certificates, private keys, or raw device logs in a public issue.

## License

Original `flutter_matter` code is MIT licensed. Matter SDK-derived source and bundled binaries retain their Apache-2.0 terms. See [THIRD_PARTY_NOTICES.md](https://github.com/Tan-yi-xiong/flutter_matter/blob/main/THIRD_PARTY_NOTICES.md).
