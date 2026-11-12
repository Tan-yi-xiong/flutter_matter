import 'package:flutter_matter_device_test_app/src/domain/domain.dart';
import 'package:flutter_test/flutter_test.dart';

void main() {
  const testApp = TestAppMetadata(
    name: 'flutter_matter_device_test_app',
    version: '1.0.0',
    commit: 'aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa',
  );
  final startedAt = DateTime.utc(2026, 11, 11, 12);

  group('RunSession', () {
    test('starts full-profile runs with every pending result', () {
      final session = RunSession.start(
        id: 'run-001',
        profile: TestProfile.full,
        testApp: testApp,
        pluginCommit: 'bbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbb',
        startedAt: startedAt,
      );

      expect(session.results, hasLength(12));
      expect(
        session.orderedResults.map((result) => result.status),
        everyElement(DeviceTestStatus.pending),
      );
      expect(session.nextActionableTestId, DeviceTestId.buildInstall);
      expect(session.progress, 0);
      expect(session.allResultsTerminal, isFalse);
    });

    test('records progress and resumes from a JSON snapshot', () {
      final started = RunSession.start(
        id: 'run-002',
        profile: TestProfile.full,
        testApp: testApp,
        pluginCommit: 'bbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbb',
        startedAt: startedAt,
      );
      final withMetadata = started.withOperatorMetadata(
        controller: const ControllerMetadata(
          platform: ControllerPlatform.android,
          deviceModel: 'Pixel 8',
          osVersion: 'Android 15',
          appBuild: 'debug 1.0.0 (1)',
        ),
        commissionee: const CommissioneeMetadata(
          vendorId: 4660,
          productId: 22136,
          commissioningTransport: CommissioningTransport.ip,
          networkTransport: NetworkTransport.wifi,
        ),
        at: startedAt.add(const Duration(seconds: 1)),
      );
      final running = withMetadata.startTest(
        DeviceTestId.buildInstall,
        at: startedAt.add(const Duration(seconds: 2)),
      );
      final progressed = running.recordResult(
        DeviceTestResult(
          testId: DeviceTestId.buildInstall,
          status: DeviceTestStatus.passed,
          duration: const Duration(milliseconds: 4200),
          evidenceFiles: const <String>['android-build-install.png'],
        ),
        at: startedAt.add(const Duration(seconds: 3)),
      );
      final resumed = RunSession.fromJson(progressed.toJson());

      expect(resumed.id, progressed.id);
      expect(resumed.profile, TestProfile.full);
      expect(resumed.phase, progressed.phase);
      expect(resumed.controller?.deviceModel, 'Pixel 8');
      expect(
        resumed.results[DeviceTestId.buildInstall]?.status,
        DeviceTestStatus.passed,
      );
      expect(resumed.nextActionableTestId, DeviceTestId.commissioningDiscovery);
      expect(resumed.progress, closeTo(1 / 12, 0.0001));
    });

    test('serializes and restores schema-version 2 snapshots', () {
      final started = RunSession.start(
        id: 'run-002a',
        profile: TestProfile.quick,
        testApp: testApp,
        pluginCommit: 'bbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbb',
        startedAt: startedAt,
      );
      final withMetadata = started.withOperatorMetadata(
        controller: const ControllerMetadata(
          platform: ControllerPlatform.android,
          deviceModel: 'Pixel 8',
          osVersion: 'Android 15',
          appBuild: 'debug 1.0.0 (1)',
        ),
        commissionee: const CommissioneeMetadata(
          vendorId: 4660,
          productId: 22136,
          networkTransport: NetworkTransport.wifi,
        ),
        at: startedAt.add(const Duration(seconds: 1)),
      );
      final json = withMetadata.toJson();

      expect(json['snapshot_version'], 2);
      expect(json['commissionee'], isNot(contains('commissioning_transport')));
      final resumed = RunSession.fromJson(json);

      expect(resumed.commissionee?.commissioningTransport, isNull);
      expect(resumed.commissionee?.vendorId, 4660);
      expect(resumed.commissionee?.productId, 22136);
    });

    test('rejects schema-version 1 snapshots', () {
      final json = RunSession.start(
        id: 'run-002b',
        profile: TestProfile.quick,
        testApp: testApp,
        pluginCommit: 'bbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbb',
        startedAt: startedAt,
      ).toJson();
      json['snapshot_version'] = 1;

      expect(() => RunSession.fromJson(json), throwsFormatException);
    });

    test('quick sessions only accept quick-profile results', () {
      final session = RunSession.start(
        id: 'run-003',
        profile: TestProfile.quick,
        testApp: testApp,
        pluginCommit: 'bbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbb',
        startedAt: startedAt,
      );

      expect(session.results, hasLength(5));
      expect(
        () => session.recordResult(
          DeviceTestResult(
            testId: DeviceTestId.nodeLabelPersistence,
            status: DeviceTestStatus.passed,
          ),
          at: startedAt.add(const Duration(seconds: 1)),
        ),
        throwsArgumentError,
      );
    });

    test('published results cannot be mutated directly', () {
      final session = RunSession.start(
        id: 'run-004',
        profile: TestProfile.quick,
        testApp: testApp,
        pluginCommit: 'bbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbb',
        startedAt: startedAt,
      );

      expect(
        () => session.results[DeviceTestId.buildInstall] = DeviceTestResult(
          testId: DeviceTestId.buildInstall,
          status: DeviceTestStatus.passed,
        ),
        throwsUnsupportedError,
      );
    });

    test('phase changes preserve the current error unless replaced', () {
      final session =
          RunSession.start(
            id: 'run-005',
            profile: TestProfile.quick,
            testApp: testApp,
            pluginCommit: 'bbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbb',
            startedAt: startedAt,
          ).withPhase(
            RunPhase.failed,
            at: startedAt.add(const Duration(seconds: 1)),
            lastError: 'Bluetooth was unavailable',
          );
      final waiting = session.withPhase(
        RunPhase.awaitingOperator,
        at: startedAt.add(const Duration(seconds: 2)),
      );

      expect(waiting.lastError, 'Bluetooth was unavailable');
    });
  });
}
