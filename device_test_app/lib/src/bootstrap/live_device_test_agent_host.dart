import '../agent/agent.dart';
import '../app/app.dart';
import '../presentation/ui_models.dart';
import 'agent_run_request_parser.dart';
import 'widget_screenshot_capture.dart';

/// Binds Agent bridge commands to the same application controller used by UI.
class LiveDeviceTestAgentHost implements DeviceTestAgentHost {
  LiveDeviceTestAgentHost({
    required DeviceTestAppController controller,
    required DeviceTestRunPort runner,
    required WidgetScreenshotCapture screenshotCapture,
    AgentRunRequestParser requestParser = const AgentRunRequestParser(),
  }) : _controller = controller,
       _runner = runner,
       _screenshotCapture = screenshotCapture,
       _requestParser = requestParser;

  final DeviceTestAppController _controller;
  final DeviceTestRunPort _runner;
  final WidgetScreenshotCapture _screenshotCapture;
  final AgentRunRequestParser _requestParser;

  @override
  Future<void> startRun(
    AgentRunMode mode,
    Map<String, Object?> arguments,
  ) async {
    try {
      if (_controller.state.busy) {
        throw const DeviceTestAgentHostException(
          code: 'command_in_progress',
          message: 'Another application operation is in progress.',
        );
      }
      final activeRun = _controller.state.activeRun;
      if ((activeRun != null && !activeRun.isTerminal) ||
          (activeRun == null && _controller.state.hasStoredSecrets)) {
        throw const DeviceTestAgentHostException(
          code: 'run_already_active',
          message: 'An unfinished Run must be resumed or stopped first.',
        );
      }
      final cleanCycle = arguments['clean_cycle'];
      final requestsSecretPurge =
          cleanCycle is Map && cleanCycle['secrets_purged'] == true;
      if (requestsSecretPurge) {
        await _controller.purgeSecrets();
        _throwIfControllerError(
          code: 'secrets_purge_failed',
          message: 'Stored provisioning secrets could not be purged.',
        );
      }

      final request = _requestParser.parse(
        arguments: arguments,
        state: _controller.state,
      );
      final expectedMode = switch (mode) {
        AgentRunMode.quick => 'quick',
        AgentRunMode.full => 'full',
        AgentRunMode.none => throw const DeviceTestAgentHostException(
          code: 'invalid_arguments',
          message: "start_run requires mode to be 'quick' or 'full'.",
        ),
      };
      if (request.profile.wireName != expectedMode) {
        throw const DeviceTestAgentHostException(
          code: 'invalid_arguments',
          message: 'The Run mode does not match the setup request.',
        );
      }

      await _controller.startRun(request);
      _throwIfControllerError(
        code: 'run_start_failed',
        message: 'The Run could not be started.',
      );
      if (_controller.state.screen != DeviceTestScreen.runner ||
          !_controller.state.hasStoredSecrets) {
        throw const DeviceTestAgentHostException(
          code: 'run_start_failed',
          message: 'The Run was not accepted by the application.',
        );
      }
    } on AgentRunRequestException catch (error) {
      final fields = error.issues.keys.toList()..sort();
      throw DeviceTestAgentHostException(
        code: 'invalid_arguments',
        message: fields.isEmpty
            ? 'The Run setup is invalid.'
            : 'The Run setup is invalid: ${fields.join(', ')}.',
      );
    } on DeviceTestAgentHostException {
      rethrow;
    } on Object {
      throw const DeviceTestAgentHostException(
        code: 'run_start_failed',
        message: 'The Run could not be started.',
      );
    }
  }

  @override
  Future<void> stopRun() async {
    try {
      await _runner.stop(reason: 'Stopped by the Agent.');
    } on Object {
      throw const DeviceTestAgentHostException(
        code: 'run_stop_failed',
        message: 'The Run could not be stopped.',
      );
    }
  }

  @override
  Future<void> resumeRun() async {
    await _controller.resumeActiveRun();
    _throwIfControllerError(
      code: 'run_not_resumable',
      message: 'The unfinished Run could not be resumed.',
    );
    if (_controller.state.screen != DeviceTestScreen.runner) {
      throw const DeviceTestAgentHostException(
        code: 'run_not_resumable',
        message: 'The unfinished Run could not be resumed.',
      );
    }
  }

  @override
  Future<void> purgeSecrets() async {
    await _controller.purgeSecrets();
    _throwIfControllerError(
      code: 'secrets_purge_failed',
      message: 'Stored provisioning secrets could not be purged.',
    );
    if (_controller.state.hasStoredSecrets) {
      throw const DeviceTestAgentHostException(
        code: 'secrets_purge_failed',
        message: 'Stored provisioning secrets remain available.',
      );
    }
  }

  @override
  Future<void> confirmPrompt(String promptId) async {
    _requireActivePrompt(promptId);
    await _controller.confirmPrompt();
    _throwIfControllerError(
      code: 'prompt_resolution_failed',
      message: 'The active prompt could not be confirmed.',
    );
  }

  @override
  Future<void> skipPrompt({
    required String promptId,
    required String reason,
  }) async {
    _requireActivePrompt(promptId);
    await _controller.skipPrompt(reason);
    _throwIfControllerError(
      code: 'prompt_resolution_failed',
      message: 'The active prompt could not be skipped.',
    );
  }

  @override
  Future<void> failPrompt({
    required String promptId,
    required String reason,
  }) async {
    _requireActivePrompt(promptId);
    await _controller.failPrompt(reason);
    _throwIfControllerError(
      code: 'prompt_resolution_failed',
      message: 'The active prompt could not be failed.',
    );
  }

  @override
  Future<AgentScreenshotPayload> captureScreenshot({String? label}) async {
    final AgentScreenshotPayload? screenshot;
    try {
      screenshot = await _screenshotCapture.capture();
    } on Object {
      throw const DeviceTestAgentHostException(
        code: 'screenshot_unavailable',
        message: 'A screenshot is not available.',
      );
    }
    if (screenshot == null) {
      throw const DeviceTestAgentHostException(
        code: 'screenshot_unavailable',
        message: 'A screenshot is not available.',
      );
    }
    if (label == null || label == screenshot.label) {
      return screenshot;
    }
    return AgentScreenshotPayload(
      mimeType: screenshot.mimeType,
      dataBase64: screenshot.dataBase64,
      capturedAt: screenshot.capturedAt,
      label: label,
      width: screenshot.width,
      height: screenshot.height,
    );
  }

  @override
  Future<AgentReportPayload> buildReport({String? runId}) async {
    final currentRunId = _controller.state.activeRun?.runId;
    if (runId != null && runId != currentRunId) {
      throw const DeviceTestAgentHostException(
        code: 'report_run_mismatch',
        message: 'The requested Run does not match the active Run.',
      );
    }
    final reportJson = _controller.formalReportJson;
    final reportMarkdown = _controller.formalReportMarkdown;
    if (currentRunId == null ||
        reportJson == null ||
        reportMarkdown == null ||
        _controller.reportValidation?.isValid != true) {
      throw const DeviceTestAgentHostException(
        code: 'report_not_ready',
        message: 'The test report is not ready.',
      );
    }
    return AgentReportPayload(
      runId: currentRunId,
      reportJson: reportJson,
      reportMarkdown: reportMarkdown,
    );
  }

  void _requireActivePrompt(String promptId) {
    final activePrompt = _controller.state.prompt;
    if (activePrompt == null || activePrompt.id != promptId) {
      throw const DeviceTestAgentHostException(
        code: 'prompt_mismatch',
        message: 'The requested prompt is not active.',
      );
    }
  }

  void _throwIfControllerError({
    required String code,
    required String message,
  }) {
    final error = _controller.state.errorMessage;
    if (error != null && error.trim().isNotEmpty) {
      throw DeviceTestAgentHostException(code: code, message: message);
    }
  }
}
