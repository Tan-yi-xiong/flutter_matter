import 'dart:async';
import 'dart:collection';

import '../application/application.dart';

class _PendingPrompt {
  _PendingPrompt(this.prompt) : completer = Completer<OperatorDecision>();

  final OperatorPrompt prompt;
  final Completer<OperatorDecision> completer;
}

/// Serializes operator prompts so exactly one decision can be pending.
///
/// The RunCoordinator invokes one prompt at a time today. This broker still
/// keeps a FIFO queue so a future or re-entrant caller can never cross prompt
/// IDs, decisions, or waiters.
class OperatorPromptBroker implements OperatorPromptPort {
  final Queue<_PendingPrompt> _queue = Queue<_PendingPrompt>();
  final StreamController<OperatorPrompt?> _activeController =
      StreamController<OperatorPrompt?>.broadcast();

  _PendingPrompt? _active;
  bool _disposed = false;

  OperatorPrompt? get activePrompt => _active?.prompt;

  bool get hasActivePrompt => _active != null;

  int get queuedPromptCount => _queue.length;

  Stream<OperatorPrompt?> get activePromptStream => _activeController.stream;

  @override
  Future<OperatorDecision> request(OperatorPrompt prompt) {
    if (_disposed) {
      throw StateError('The operator prompt broker is closed.');
    }
    final pending = _PendingPrompt(prompt);
    if (_active == null) {
      _active = pending;
      _emitActive();
    } else {
      _queue.add(pending);
    }
    return pending.completer.future;
  }

  void confirmActive() {
    _resolve(OperatorDecision.confirmed());
  }

  void skipActive(String reason) {
    final prompt = _requireActive();
    if (!prompt.canSkip) {
      throw StateError('The active operator prompt cannot be skipped.');
    }
    final trimmed = reason.trim();
    if (prompt.skipRequiresReason && trimmed.isEmpty) {
      throw ArgumentError.value(reason, 'reason', 'Must not be empty');
    }
    _resolve(
      OperatorDecision.skipped(
        trimmed.isEmpty ? 'Skipped by the operator.' : trimmed,
      ),
    );
  }

  void failActive(String reason) {
    _requireActive();
    final trimmed = reason.trim();
    if (trimmed.isEmpty) {
      throw ArgumentError.value(reason, 'reason', 'Must not be empty');
    }
    _resolve(OperatorDecision.failed(trimmed));
  }

  OperatorPrompt _requireActive() {
    if (_disposed) {
      throw StateError('The operator prompt broker is closed.');
    }
    final pending = _active;
    if (pending == null) {
      throw StateError('No operator prompt is active.');
    }
    return pending.prompt;
  }

  void _resolve(OperatorDecision decision) {
    final active = _active;
    if (active == null) {
      throw StateError('No operator prompt is active.');
    }
    _active = _queue.isEmpty ? null : _queue.removeFirst();
    active.completer.complete(decision);
    _emitActive();
  }

  void _emitActive() {
    if (!_activeController.isClosed) {
      _activeController.add(_active?.prompt);
    }
  }

  void dispose() {
    if (_disposed) {
      return;
    }
    _disposed = true;
    final cancelled = <_PendingPrompt>[?_active, ..._queue];
    _active = null;
    _queue.clear();
    for (final pending in cancelled) {
      if (!pending.completer.isCompleted) {
        pending.completer.complete(
          OperatorDecision.failed('The device test app was closed.'),
        );
      }
    }
    _activeController.close();
  }
}
