enum ControllerPlatform {
  android('android'),
  ios('ios');

  const ControllerPlatform(this.wireName);

  final String wireName;

  static ControllerPlatform parse(String value) {
    for (final platform in values) {
      if (platform.wireName == value) {
        return platform;
      }
    }
    throw FormatException('Unknown controller platform: $value');
  }
}

class ControllerMetadata {
  const ControllerMetadata({
    required this.platform,
    required this.deviceModel,
    required this.osVersion,
    required this.appBuild,
  });

  final ControllerPlatform platform;
  final String deviceModel;
  final String osVersion;
  final String appBuild;

  factory ControllerMetadata.fromJson(Map<String, dynamic> json) {
    return ControllerMetadata(
      platform: ControllerPlatform.parse(_requiredString(json, 'platform')),
      deviceModel: _requiredString(json, 'device_model'),
      osVersion: _requiredString(json, 'os_version'),
      appBuild: _requiredString(json, 'app_build'),
    );
  }

  Map<String, Object?> toJson() => <String, Object?>{
    'platform': platform.wireName,
    'device_model': deviceModel,
    'os_version': osVersion,
    'app_build': appBuild,
  };
}

enum CommissioneeType {
  real('real');

  const CommissioneeType(this.wireName);

  final String wireName;

  static CommissioneeType parse(String value) {
    for (final type in values) {
      if (type.wireName == value) {
        return type;
      }
    }
    throw FormatException('Unknown commissionee type: $value');
  }
}

enum CommissioningTransport {
  ble('ble'),
  ip('ip');

  const CommissioningTransport(this.wireName);

  final String wireName;

  static CommissioningTransport parse(String value) {
    for (final transport in values) {
      if (transport.wireName == value) {
        return transport;
      }
    }
    throw FormatException('Unknown commissioning transport: $value');
  }
}

enum NetworkTransport {
  wifi('wifi'),
  thread('thread'),
  unknown('unknown');

  const NetworkTransport(this.wireName);

  final String wireName;

  static NetworkTransport parse(String value) {
    for (final transport in values) {
      if (transport.wireName == value) {
        return transport;
      }
    }
    throw FormatException('Unknown network transport: $value');
  }
}

class CommissioneeMetadata {
  const CommissioneeMetadata({
    required this.vendorId,
    required this.productId,
    required this.networkTransport,
    this.commissioningTransport,
    this.type = CommissioneeType.real,
  });

  final CommissioneeType type;
  final int vendorId;
  final int productId;

  /// The path selected by discovery; null until discovery has completed.
  final CommissioningTransport? commissioningTransport;
  final NetworkTransport networkTransport;

  factory CommissioneeMetadata.fromJson(Map<String, dynamic> json) {
    return CommissioneeMetadata(
      type: CommissioneeType.parse(_requiredString(json, 'type')),
      vendorId: _requiredInt(json, 'vendor_id'),
      productId: _requiredInt(json, 'product_id'),
      commissioningTransport: json['commissioning_transport'] == null
          ? null
          : CommissioningTransport.parse(
              _requiredString(json, 'commissioning_transport'),
            ),
      networkTransport: NetworkTransport.parse(
        _requiredString(json, 'network_transport'),
      ),
    );
  }

  Map<String, Object?> toJson() => <String, Object?>{
    'type': type.wireName,
    'vendor_id': vendorId,
    'product_id': productId,
    if (commissioningTransport != null)
      'commissioning_transport': commissioningTransport!.wireName,
    'network_transport': networkTransport.wireName,
  };
}

class TestAppMetadata {
  const TestAppMetadata({
    required this.name,
    required this.version,
    required this.commit,
  });

  final String name;
  final String version;
  final String commit;

  factory TestAppMetadata.fromJson(Map<String, dynamic> json) {
    return TestAppMetadata(
      name: _requiredString(json, 'name'),
      version: _requiredString(json, 'version'),
      commit: _requiredString(json, 'commit'),
    );
  }

  Map<String, Object?> toJson() => <String, Object?>{
    'name': name,
    'version': version,
    'commit': commit,
  };
}

String _requiredString(Map<String, dynamic> json, String key) {
  final value = json[key];
  if (value is! String) {
    throw FormatException('$key must be a string');
  }
  return value;
}

int _requiredInt(Map<String, dynamic> json, String key) {
  final value = json[key];
  if (value is! int) {
    throw FormatException('$key must be an integer');
  }
  return value;
}
