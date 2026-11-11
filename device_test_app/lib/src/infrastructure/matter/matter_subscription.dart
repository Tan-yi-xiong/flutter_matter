import 'dart:async';
import 'dart:typed_data';

import 'package:flutter_matter/flutter_matter.dart';

import 'matter_callback_wrappers.dart';
import 'matter_contracts.dart';

typedef MatterSubscriptionCloseAction =
    Future<bool> Function(int subscriptionId);

class MatterAttributeSubscription
    implements MatterSubscription, SubscriptionCallback {
  MatterAttributeSubscription({
    required this.nodeId,
    required this.endpointId,
    required this.clusterId,
    required this.attributeId,
    required MatterSubscriptionCloseAction closeAction,
  }) : _closeAction = closeAction;

  final int nodeId;
  final int endpointId;
  final int clusterId;
  final int attributeId;
  final MatterSubscriptionCloseAction _closeAction;
  final Completer<int> _established = Completer<int>();
  final StreamController<MatterAttributeValue> _reports =
      StreamController<MatterAttributeValue>();
  final StreamController<MatterException> _errors =
      StreamController<MatterException>();
  int? _subscriptionId;
  bool _closed = false;

  @override
  Stream<MatterAttributeValue> get reports => _reports.stream;

  @override
  Stream<MatterException> get errors => _errors.stream;

  @override
  int get subscriptionId {
    final value = _subscriptionId;
    if (value == null) {
      throw StateError('The subscription has not been established');
    }
    return value;
  }

  @override
  Future<int> waitForEstablished(Duration timeout) {
    return withMatterTimeout<int>(
      future: _established.future,
      timeout: timeout,
      operation: 'Wait for subscription establishment',
    );
  }

  @override
  Future<bool> close({Duration timeout = const Duration(seconds: 10)}) async {
    if (_closed) {
      return true;
    }
    final id = await waitForEstablished(timeout);
    final closed = await withMatterTimeout<bool>(
      future: _closeAction(id),
      timeout: timeout,
      operation: 'Close Matter subscription',
    );
    if (closed) {
      await _finish();
    }
    return closed;
  }

  @override
  void onSubscriptionEstablished(int subscriptionId) {
    _subscriptionId = subscriptionId;
    if (!_established.isCompleted) {
      _established.complete(subscriptionId);
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
      _errors.add(
        MatterException(
          MatterFailureCode.readFailed,
          'Subscription report did not contain the requested attribute',
        ),
      );
      return;
    }
    if (!_reports.isClosed) {
      _reports.add(
        MatterAttributeValue(
          endpointId: endpointId,
          clusterId: clusterId,
          attributeId: attributeId,
          tlv: Uint8List.fromList(tlv),
        ),
      );
    }
  }

  @override
  void onError(
    ChipAttributePath? attributePath,
    ChipEventPath? eventPath,
    Exception e,
  ) {
    final error = MatterException(
      MatterFailureCode.subscribeFailed,
      'Matter subscription reported an error',
      e,
    );
    if (!_established.isCompleted) {
      _established.completeError(error);
    }
    if (!_errors.isClosed) {
      _errors.add(error);
    }
  }

  @override
  void onDone() {
    if (!_established.isCompleted) {
      _established.completeError(
        MatterException(
          MatterFailureCode.subscribeFailed,
          'Subscription completed before it was established',
        ),
      );
    }
    unawaited(_finish());
  }

  Future<void> _finish() async {
    if (_closed) {
      return;
    }
    _closed = true;
    unawaited(_reports.close());
    unawaited(_errors.close());
  }
}
