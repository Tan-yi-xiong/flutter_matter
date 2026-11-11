import 'dart:io';

import 'package:flutter/services.dart';

import '../storage/run_directory.dart';

class ReportArtifacts {
  const ReportArtifacts({required this.jsonFile, required this.markdownFile});

  final File jsonFile;
  final File markdownFile;
}

class ReportFileRepository {
  ReportFileRepository({
    required RunDirectory runDirectory,
    AssetBundle? assetBundle,
  }) : _runDirectory = runDirectory,
       _assetBundle = assetBundle ?? rootBundle;

  static const schemaAssetPath = 'assets/device-test-report.schema.json';

  final RunDirectory _runDirectory;
  final AssetBundle _assetBundle;

  Future<String> loadCanonicalSchema() =>
      _assetBundle.loadString(schemaAssetPath);

  Future<ReportArtifacts> write({
    required String runId,
    required String jsonContents,
    required String markdownContents,
  }) async {
    final jsonFile = await _runDirectory.writeAtomically(
      runId: runId,
      fileName: 'device-test-report.json',
      contents: jsonContents,
    );
    final markdownFile = await _runDirectory.writeAtomically(
      runId: runId,
      fileName: 'device-test-report.md',
      contents: markdownContents,
    );
    return ReportArtifacts(jsonFile: jsonFile, markdownFile: markdownFile);
  }
}
