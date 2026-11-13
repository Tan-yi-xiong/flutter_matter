import 'dart:io';
import 'dart:ui';

import 'package:share_plus/share_plus.dart';

class ShareReportService {
  Future<ShareResult> shareReports({
    required File jsonReport,
    required File markdownReport,
    Rect? sharePositionOrigin,
  }) {
    return SharePlus.instance.share(
      ShareParams(
        title: 'flutter_matter device validation',
        subject: 'flutter_matter device validation report',
        files: [XFile(jsonReport.path), XFile(markdownReport.path)],
        sharePositionOrigin: sharePositionOrigin,
      ),
    );
  }
}
