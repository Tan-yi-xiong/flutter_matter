import 'dart:convert';
import 'dart:ui' as ui;

import 'package:flutter/rendering.dart';
import 'package:flutter/widgets.dart';

import '../agent/agent.dart';

/// Captures the visible app surface for an Agent screenshot command.
class WidgetScreenshotCapture {
  WidgetScreenshotCapture({
    required GlobalKey boundaryKey,
    this.pixelRatio = 2,
    this.label = 'device-test-app',
  }) : _boundaryKey = boundaryKey {
    if (pixelRatio <= 0) {
      throw ArgumentError.value(pixelRatio, 'pixelRatio', 'Must be positive');
    }
  }

  final GlobalKey _boundaryKey;
  final double pixelRatio;
  final String label;

  Future<AgentScreenshotPayload?> capture() async {
    final renderObject = _boundaryKey.currentContext?.findRenderObject();
    if (renderObject is! RenderRepaintBoundary) {
      return null;
    }

    ui.Image? image;
    try {
      image = await renderObject.toImage(pixelRatio: pixelRatio);
      final data = await image.toByteData(format: ui.ImageByteFormat.png);
      if (data == null) {
        return null;
      }
      return AgentScreenshotPayload(
        mimeType: 'image/png',
        dataBase64: base64Encode(data.buffer.asUint8List()),
        capturedAt: DateTime.now().toUtc(),
        label: label,
        width: image.width,
        height: image.height,
      );
    } on Object {
      return null;
    } finally {
      image?.dispose();
    }
  }
}
