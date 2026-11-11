import '../domain/domain.dart';

/// The actor expected to resolve an operator prompt.
///
/// The app UI may handle [app] prompts directly. [agentAndroid] prompts are
/// intended for an Agent with Android device-control capability, while
/// [human] prompts require the person operating the physical setup.
enum RequiredActor { app, agentAndroid, human }

extension RequiredActorWire on RequiredActor {
  String get wireName => switch (this) {
    RequiredActor.app => 'app',
    RequiredActor.agentAndroid => 'agent_android',
    RequiredActor.human => 'human',
  };

  static RequiredActor parse(Object? value) => switch (value) {
    'app' => RequiredActor.app,
    'agent_android' => RequiredActor.agentAndroid,
    'human' => RequiredActor.human,
    _ => throw FormatException('Unknown required actor: $value'),
  };
}

enum OperatorPromptDecisionStatus { confirmed, skipped, failed }

/// A reviewer-safe request for an external action.
///
/// Prompt text and identifiers must never contain provisioning secrets,
/// device identifiers, certificates, private keys, or raw logs.
class OperatorPrompt {
  const OperatorPrompt({
    required this.id,
    required this.title,
    required this.instructions,
    required this.requiredActor,
    this.testId,
    this.confirmLabel = 'Confirm',
    this.canSkip = true,
    this.skipRequiresReason = true,
  }) : assert(id != ''),
       assert(title != ''),
       assert(instructions != ''),
       assert(confirmLabel != '');

  final String id;
  final String title;
  final String instructions;
  final RequiredActor requiredActor;
  final DeviceTestId? testId;
  final String confirmLabel;
  final bool canSkip;
  final bool skipRequiresReason;

  OperatorPrompt copyWith({DeviceTestId? testId}) => OperatorPrompt(
    id: id,
    title: title,
    instructions: instructions,
    requiredActor: requiredActor,
    testId: testId ?? this.testId,
    confirmLabel: confirmLabel,
    canSkip: canSkip,
    skipRequiresReason: skipRequiresReason,
  );

  Map<String, Object?> toJson() => <String, Object?>{
    'id': id,
    'title': title,
    'instructions': instructions,
    'required_actor': requiredActor.wireName,
    if (testId != null) 'test_id': testId!.wireName,
    'confirm_label': confirmLabel,
    'can_skip': canSkip,
    'skip_requires_reason': skipRequiresReason,
  };

  factory OperatorPrompt.fromJson(Map<String, dynamic> json) {
    final rawTestId = json['test_id'];
    if (rawTestId != null && rawTestId is! String) {
      throw const FormatException('test_id must be a string');
    }
    final canSkip = json['can_skip'];
    final skipRequiresReason = json['skip_requires_reason'];
    if (canSkip is! bool || skipRequiresReason is! bool) {
      throw const FormatException('Prompt skip flags must be booleans');
    }
    return OperatorPrompt(
      id: _requiredString(json, 'id'),
      title: _requiredString(json, 'title'),
      instructions: _requiredString(json, 'instructions'),
      requiredActor: RequiredActorWire.parse(json['required_actor']),
      testId: rawTestId == null
          ? null
          : DeviceTestId.parse(rawTestId as String),
      confirmLabel: _requiredString(json, 'confirm_label'),
      canSkip: canSkip,
      skipRequiresReason: skipRequiresReason,
    );
  }
}

/// The result returned by the UI or Agent after handling a prompt.
class OperatorDecision {
  const OperatorDecision._({required this.status, this.reason});

  factory OperatorDecision.confirmed() =>
      const OperatorDecision._(status: OperatorPromptDecisionStatus.confirmed);

  factory OperatorDecision.skipped(String reason) {
    final trimmed = reason.trim();
    if (trimmed.isEmpty) {
      throw ArgumentError.value(reason, 'reason', 'Must not be empty');
    }
    return OperatorDecision._(
      status: OperatorPromptDecisionStatus.skipped,
      reason: trimmed,
    );
  }

  factory OperatorDecision.failed(String reason) {
    final trimmed = reason.trim();
    if (trimmed.isEmpty) {
      throw ArgumentError.value(reason, 'reason', 'Must not be empty');
    }
    return OperatorDecision._(
      status: OperatorPromptDecisionStatus.failed,
      reason: trimmed,
    );
  }

  final OperatorPromptDecisionStatus status;
  final String? reason;

  bool get isConfirmed => status == OperatorPromptDecisionStatus.confirmed;
}

String _requiredString(Map<String, dynamic> json, String key) {
  final value = json[key];
  if (value is! String) {
    throw FormatException('$key must be a string');
  }
  return value;
}
