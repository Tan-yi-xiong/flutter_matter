import 'dart:io';

import 'package:device_info_plus/device_info_plus.dart';
import 'package:package_info_plus/package_info_plus.dart';

class PlatformInfo {
  const PlatformInfo({
    required this.platform,
    required this.deviceModel,
    required this.osVersion,
    required this.appVersion,
    required this.appBuild,
  });

  final String platform;
  final String deviceModel;
  final String osVersion;
  final String appVersion;
  final String appBuild;
}

class PlatformInfoService {
  PlatformInfoService({DeviceInfoPlugin? deviceInfo, PackageInfo? packageInfo})
    : _deviceInfo = deviceInfo ?? DeviceInfoPlugin(),
      _packageInfo = packageInfo;

  final DeviceInfoPlugin _deviceInfo;
  PackageInfo? _packageInfo;

  Future<PlatformInfo> load() async {
    final packageInfo = _packageInfo ??= await PackageInfo.fromPlatform();
    if (Platform.isAndroid) {
      final info = await _deviceInfo.androidInfo;
      return PlatformInfo(
        platform: 'android',
        deviceModel: _bounded('${info.manufacturer} ${info.model}'),
        osVersion:
            'Android ${info.version.release} (API ${info.version.sdkInt})',
        appVersion: packageInfo.version,
        appBuild: '${packageInfo.version} (${packageInfo.buildNumber})',
      );
    }
    if (Platform.isIOS) {
      final info = await _deviceInfo.iosInfo;
      return PlatformInfo(
        platform: 'ios',
        deviceModel: _bounded(info.utsname.machine),
        osVersion: 'iOS ${info.systemVersion}',
        appVersion: packageInfo.version,
        appBuild: '${packageInfo.version} (${packageInfo.buildNumber})',
      );
    }
    throw UnsupportedError(
      'flutter_matter device testing supports Android and iOS only.',
    );
  }

  String _bounded(String value) {
    final normalized = value.trim();
    if (normalized.isEmpty) {
      return 'Unknown';
    }
    return normalized.length <= 120 ? normalized : normalized.substring(0, 120);
  }
}
