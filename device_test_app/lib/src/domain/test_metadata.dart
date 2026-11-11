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
  real('real'),
  virtual('virtual');

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

enum StateChangeMethod {
  physicalControl('physical_control'),
  vendorApp('vendor_app'),
  commissioneeUi('commissionee_ui'),
  other('other');

  const StateChangeMethod(this.wireName);

  final String wireName;

  static StateChangeMethod parse(String value) {
    for (final method in values) {
      if (method.wireName == value) {
        return method;
      }
    }
    throw FormatException('Unknown state change method: $value');
  }
}

class CommissioneeMetadata {
  const CommissioneeMetadata({
    required this.type,
    required this.model,
    required this.firmware,
    required this.networkTransport,
    required this.stateChangeMethod,
    this.commissioningTransport = CommissioningTransport.ip,
    this.stateChangeNotes,
  });

  final CommissioneeType type;
  final String model;
  final String firmware;
  final CommissioningTransport commissioningTransport;
  final NetworkTransport networkTransport;
  final StateChangeMethod stateChangeMethod;
  final String? stateChangeNotes;

  factory CommissioneeMetadata.fromJson(Map<String, dynamic> json) {
    final transport = _requiredString(json, 'commissioning_transport');

    final rawNotes = json['state_change_notes'];
    if (rawNotes != null && rawNotes is! String) {
      throw const FormatException('state_change_notes must be a string');
    }

    return CommissioneeMetadata(
      type: CommissioneeType.parse(_requiredString(json, 'type')),
      model: _requiredString(json, 'model'),
      firmware: _requiredString(json, 'firmware'),
      commissioningTransport: CommissioningTransport.parse(transport),
      networkTransport: NetworkTransport.parse(
        _requiredString(json, 'network_transport'),
      ),
      stateChangeMethod: StateChangeMethod.parse(
        _requiredString(json, 'state_change_method'),
      ),
      stateChangeNotes: rawNotes as String?,
    );
  }

  Map<String, Object?> toJson() => <String, Object?>{
    'type': type.wireName,
    'model': model,
    'firmware': firmware,
    'commissioning_transport': commissioningTransport.wireName,
    'network_transport': networkTransport.wireName,
    'state_change_method': stateChangeMethod.wireName,
    if (stateChangeNotes != null) 'state_change_notes': stateChangeNotes,
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
