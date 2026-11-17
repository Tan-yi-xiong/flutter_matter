import 'dart:typed_data';

enum ConnectionPhase { disconnected, connecting, connected }

class SavedDevice {
  const SavedDevice({
    required this.nodeId,
    this.vendorId,
    this.productId,
    this.label,
    this.commissionedAt,
  });

  final int nodeId;
  final int? vendorId;
  final int? productId;
  final String? label;
  final DateTime? commissionedAt;

  String get displayName {
    final explicit = label?.trim();
    if (explicit != null && explicit.isNotEmpty) {
      return explicit;
    }
    return 'Matter device ${formatId(nodeId)}';
  }

  Map<String, Object?> toJson() => {
    'nodeId': nodeId,
    if (vendorId != null) 'vendorId': vendorId,
    if (productId != null) 'productId': productId,
    if (label != null) 'label': label,
    if (commissionedAt != null)
      'commissionedAt': commissionedAt!.toUtc().toIso8601String(),
  };

  factory SavedDevice.fromJson(Map<String, dynamic> json) {
    final commissionedAt = json['commissionedAt'];
    return SavedDevice(
      nodeId: (json['nodeId'] as num).toInt(),
      vendorId: (json['vendorId'] as num?)?.toInt(),
      productId: (json['productId'] as num?)?.toInt(),
      label: json['label'] as String?,
      commissionedAt: commissionedAt is String
          ? DateTime.tryParse(commissionedAt)
          : null,
    );
  }
}

class OperationResult {
  const OperationResult({
    required this.success,
    required this.summary,
    this.detail,
  });

  final bool success;
  final String summary;
  final String? detail;

  factory OperationResult.failure(String summary, [Object? error]) {
    return OperationResult(
      success: false,
      summary: summary,
      detail: error?.toString(),
    );
  }
}

class OperationLogEntry {
  const OperationLogEntry({
    required this.timestamp,
    required this.api,
    required this.title,
    required this.result,
  });

  final DateTime timestamp;
  final String api;
  final String title;
  final OperationResult result;
}

class CommissionedNode {
  const CommissionedNode({
    required this.nodeId,
    required this.controller,
    this.vendorId,
    this.productId,
  });

  final int nodeId;
  final dynamic controller;
  final int? vendorId;
  final int? productId;
}

class InvokeReply {
  const InvokeReply({required this.element, required this.successCode});

  final dynamic element;
  final int successCode;
}

class SubscriptionUpdate {
  const SubscriptionUpdate({this.nodeState, this.error});

  final dynamic nodeState;
  final Exception? error;
}

class SubscriptionSession {
  const SubscriptionSession({
    required this.id,
    required this.updates,
    required this.cancel,
  });

  final int id;
  final Stream<SubscriptionUpdate> updates;
  final Future<bool> Function() cancel;
}

class CommissioningWindowResult {
  const CommissioningWindowResult({
    required this.manualPairingCode,
    required this.qrCode,
  });

  final String manualPairingCode;
  final String qrCode;
}

class FabricSnapshot {
  const FabricSnapshot({
    required this.currentFabricIndex,
    required this.rawNodeState,
    required this.rawTlv,
  });

  final int? currentFabricIndex;
  final dynamic rawNodeState;
  final Uint8List? rawTlv;
}

String formatId(int value) {
  final hex = value.toRadixString(16).toUpperCase();
  return '0x${hex.padLeft(hex.length <= 4 ? 4 : hex.length, '0')}';
}

String formatBytes(Uint8List? bytes) {
  if (bytes == null) {
    return 'null';
  }
  if (bytes.isEmpty) {
    return '(empty)';
  }
  return bytes
      .map((value) => value.toRadixString(16).padLeft(2, '0').toUpperCase())
      .join(' ');
}
