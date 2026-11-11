# Security Policy

## Supported Versions

Only the latest published `flutter_matter` release receives security fixes. Earlier releases are unsupported and should be upgraded before requesting a fix. The current latest published release is listed on [pub.dev](https://pub.dev/packages/flutter_matter).

| Version | Supported |
| --- | --- |
| Latest published release | Yes |
| Earlier releases | No |

## Reporting a Vulnerability

Use [GitHub Private Vulnerability Reporting](https://github.com/Tan-yi-xiong/flutter_matter/security/advisories/new) to report a suspected vulnerability. Do not open a public issue for a suspected vulnerability.

Please include:

- The affected `flutter_matter` versions.
- The affected platform: Android, iOS, or both.
- Reproduction steps or a minimal proof of concept.
- The potential security impact.
- Any known mitigation or workaround.

## Scope

This policy covers security issues in:

- Dart code and the public plugin API.
- MethodChannel contracts and Dart-to-native bridges.
- Android and iOS plugin code.
- Bundled Matter binaries, and configuration or packaging of those binaries that affects `flutter_matter` users.

## Response and Disclosure

Maintainers review vulnerability reports on a best-effort basis. No acknowledgment, remediation, or disclosure SLA is guaranteed. Please keep reports and details private until maintainers have confirmed a remediation and coordinated the disclosure plan.

## Sensitive Information

Do not include secrets, private keys, provisioning material, or personal data in a report. Redact sensitive values from logs and use synthetic test data where possible.

## Third-Party Dependencies

Report issues that exist solely in the upstream Matter SDK to the [Project CHIP security process](https://github.com/project-chip/connectedhomeip/security/policy). Report issues to this repository when `flutter_matter` integration, configuration, packaging, or behavior exposes or amplifies the upstream issue. If the issue also affects an upstream dependency, mention the upstream report in your private report.
