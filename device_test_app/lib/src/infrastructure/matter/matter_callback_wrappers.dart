import 'dart:async';
import 'dart:typed_data';

import 'package:flutter_matter/flutter_matter.dart';

import 'matter_contracts.dart';

Future<T> withMatterTimeout<T>({
  required Future<T> future,
  required Duration timeout,
  required String operation,
}) async {
  try {
    return await future.timeout(timeout);
  } on TimeoutException {
    throw MatterTimeoutException(operation);
  }
}

class MatterCommissionOutcome {
  const MatterCommissionOutcome({
    required this.nodeId,
    required this.errorCode,
  });

  final int nodeId;
  final int errorCode;
}

class MatterCommissioningListener implements CompletionListener {
  MatterCommissioningListener({required int fallbackNodeId})
    : _fallbackNodeId = fallbackNodeId;

  final int _fallbackNodeId;
  final Completer<MatterCommissionOutcome> _completion =
      Completer<MatterCommissionOutcome>();
  final StreamController<MatterCommissioningStage> _stages =
      StreamController<MatterCommissioningStage>.broadcast();
  final List<MatterCommissioningStage> _stageHistory = [];

  Stream<MatterCommissioningStage> get stages => _stages.stream;

  List<MatterCommissioningStage> get stageHistory =>
      List.unmodifiable(_stageHistory);

  bool get isCompleted => _completion.isCompleted;

  Future<MatterCommissionOutcome> wait(Duration timeout) {
    return withMatterTimeout<MatterCommissionOutcome>(
      future: _completion.future,
      timeout: timeout,
      operation: 'Wait for commissioning completion',
    );
  }

  void fail(Object error) {
    if (!_completion.isCompleted) {
      _completion.completeError(error);
    }
    if (!_stages.isClosed) {
      unawaited(_stages.close());
    }
  }

  @override
  void onConnectDeviceComplete() {}

  @override
  void onStatusUpdate(int status) {}

  @override
  void onPairingComplete(int errorCode) {
    if (errorCode != 0) {
      fail(
        MatterException(
          MatterFailureCode.pairingFailed,
          'Pairing failed with error code $errorCode',
        ),
      );
    }
  }

  @override
  void onPairingDeleted(int errorCode) {}

  @override
  void onCommissioningComplete(int? nodeId, int errorCode) {
    if (!_completion.isCompleted) {
      _completion.complete(
        MatterCommissionOutcome(
          nodeId: nodeId ?? _fallbackNodeId,
          errorCode: errorCode,
        ),
      );
    }
    if (!_stages.isClosed) {
      unawaited(_stages.close());
    }
  }

  @override
  void onReadCommissioningInfo(
    int vendorId,
    int productId,
    int wifiEndpointId,
    int threadEndpointId,
  ) {}

  @override
  void onCommissioningStatusUpdate(int nodeId, String stage, int errorCode) {
    final update = MatterCommissioningStage(
      nodeId: nodeId,
      stage: stage,
      errorCode: errorCode,
    );
    _stageHistory.add(update);
    if (!_stages.isClosed) {
      _stages.add(update);
    }
  }

  @override
  void onNotifyChipConnectionClosed() {}

  @override
  void onError(Exception error) {
    fail(
      MatterException(
        MatterFailureCode.commissioningFailed,
        'Commissioning reported an error',
        error,
      ),
    );
  }

  @override
  void onOpCSRGenerationComplete(Uint8List csr) {}

  @override
  void onICDRegistrationInfoRequired() {}

  @override
  void onICDRegistrationComplete(int errorCode, ICDDeviceInfo? icdDeviceInfo) {
    if (errorCode != 0 && !_completion.isCompleted) {
      fail(
        MatterException(
          MatterFailureCode.commissioningFailed,
          'ICD registration failed with error code $errorCode',
        ),
      );
    }
  }
}

class MatterConnectedDeviceCollector implements ConnectedDeviceCallback {
  final Completer<Object?> _completion = Completer<Object?>();

  Future<Object?> wait(Duration timeout) {
    return withMatterTimeout<Object?>(
      future: _completion.future,
      timeout: timeout,
      operation: 'Wait for operational connection',
    );
  }

  @override
  void onError(Exception e) {
    if (!_completion.isCompleted) {
      _completion.completeError(
        MatterException(
          MatterFailureCode.connectFailed,
          'Operational connection failed',
          e,
        ),
      );
    }
  }

  @override
  void onConnected(Object? context) {
    if (!_completion.isCompleted) {
      _completion.complete(context);
    }
  }
}

class MatterInvokeCollector implements InvokeCallback {
  final Completer<MatterInvokeResult> _completion =
      Completer<MatterInvokeResult>();

  Future<MatterInvokeResult> wait(Duration timeout) {
    return withMatterTimeout<MatterInvokeResult>(
      future: _completion.future,
      timeout: timeout,
      operation: 'Wait for invoke response',
    );
  }

  @override
  void onError(Exception e) {
    if (!_completion.isCompleted) {
      _completion.completeError(
        MatterException(
          MatterFailureCode.invokeFailed,
          'Matter invoke failed',
          e,
        ),
      );
    }
  }

  @override
  void onResponse(InvokeElement invokeElement, int successCode) {
    if (!_completion.isCompleted) {
      _completion.complete(
        MatterInvokeResult(
          successCode: successCode,
          responseTlv: invokeElement.tlv == null
              ? null
              : Uint8List.fromList(invokeElement.tlv!),
          responseJson: invokeElement.json,
        ),
      );
    }
  }

  @override
  void onDone() {
    if (!_completion.isCompleted) {
      _completion.completeError(
        MatterException(
          MatterFailureCode.invokeFailed,
          'Invoke completed without a response',
        ),
      );
    }
  }
}

class MatterReadCollector implements ReportCallback {
  final Completer<MatterAttributeValue> _completion =
      Completer<MatterAttributeValue>();
  final int endpointId;
  final int clusterId;
  final int attributeId;

  MatterReadCollector({
    required this.endpointId,
    required this.clusterId,
    required this.attributeId,
  });

  Future<MatterAttributeValue> wait(Duration timeout) {
    return withMatterTimeout<MatterAttributeValue>(
      future: _completion.future,
      timeout: timeout,
      operation: 'Wait for attribute read report',
    );
  }

  @override
  void onError(
    ChipAttributePath? attributePath,
    ChipEventPath? eventPath,
    Exception e,
  ) {
    if (!_completion.isCompleted) {
      _completion.completeError(
        MatterException(
          MatterFailureCode.readFailed,
          'Attribute read failed',
          e,
        ),
      );
    }
  }

  @override
  void onReport(NodeState nodeState) {
    final tlv = nodeState
        .endpoints[endpointId]
        ?.clusters[clusterId]
        ?.attributes[attributeId]
        ?.tlv;
    if (tlv == null) {
      if (!_completion.isCompleted) {
        _completion.completeError(
          MatterException(
            MatterFailureCode.readFailed,
            'Attribute read response did not contain the requested value',
          ),
        );
      }
      return;
    }
    if (!_completion.isCompleted) {
      _completion.complete(
        MatterAttributeValue(
          endpointId: endpointId,
          clusterId: clusterId,
          attributeId: attributeId,
          tlv: tlv,
        ),
      );
    }
  }

  @override
  void onDone() {
    if (!_completion.isCompleted) {
      _completion.completeError(
        MatterException(
          MatterFailureCode.readFailed,
          'Attribute read completed without a report',
        ),
      );
    }
  }
}

class MatterWriteCollector implements WriteAttributesCallback {
  final Completer<MatterWriteResult> _completion =
      Completer<MatterWriteResult>();

  Future<MatterWriteResult> wait(Duration timeout) {
    return withMatterTimeout<MatterWriteResult>(
      future: _completion.future,
      timeout: timeout,
      operation: 'Wait for attribute write response',
    );
  }

  @override
  void onDone() {
    if (!_completion.isCompleted) {
      _completion.completeError(
        MatterException(
          MatterFailureCode.writeFailed,
          'Attribute write completed without a response',
        ),
      );
    }
  }

  @override
  void onError(ChipAttributePath? attributePath, Exception e) {
    if (!_completion.isCompleted) {
      _completion.completeError(
        MatterException(
          MatterFailureCode.writeFailed,
          'Attribute write failed',
          e,
        ),
      );
    }
  }

  @override
  void onResponse(ChipAttributePath? attributePath, Status? status) {
    if (!_completion.isCompleted) {
      _completion.complete(
        MatterWriteResult(
          statusCode: status?.status ?? 0,
          clusterStatus: status?.clusterStatus,
        ),
      );
    }
  }
}
