import 'dart:convert';

import 'package:flutter/material.dart';
import 'package:flutter_matter_device_test_app/src/bootstrap/widget_screenshot_capture.dart';
import 'package:flutter_test/flutter_test.dart';

void main() {
  testWidgets('captures a visible boundary as PNG', (tester) async {
    final key = GlobalKey();
    await tester.pumpWidget(
      Directionality(
        textDirection: TextDirection.ltr,
        child: RepaintBoundary(
          key: key,
          child: const SizedBox(
            width: 120,
            height: 80,
            child: ColoredBox(color: Color(0xFF315A45)),
          ),
        ),
      ),
    );
    await tester.pump();
    final capture = WidgetScreenshotCapture(boundaryKey: key);

    final payload = await tester.runAsync(capture.capture);

    expect(payload, isNotNull);
    expect(payload?.mimeType, 'image/png');
    expect(payload?.width, greaterThan(0));
    expect(payload?.height, greaterThan(0));
    expect(base64Decode(payload!.dataBase64).take(4), <int>[
      0x89,
      0x50,
      0x4E,
      0x47,
    ]);
  });

  testWidgets('returns null when the boundary is not mounted', (tester) async {
    final capture = WidgetScreenshotCapture(boundaryKey: GlobalKey());

    final payload = await capture.capture();

    expect(payload, isNull);
  });
}
