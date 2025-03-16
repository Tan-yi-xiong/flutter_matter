import 'package:flutter/cupertino.dart';
import 'package:flutter/foundation.dart';
import 'package:flutter/material.dart';
import 'package:flutter/widgets.dart';
import 'package:flutter_matter/flutter_matter.dart';
import 'package:flutter_matter_example/device_provisioning.dart';
import 'package:flutter_matter_example/wifi_input.dart';
import 'package:fluttertoast/fluttertoast.dart';
import 'package:mobile_scanner/mobile_scanner.dart';

class OnboardingWidget extends StatefulWidget {
  const OnboardingWidget({super.key});

  @override
  State<OnboardingWidget> createState() => _OnboardingWidgetState();
}

class _OnboardingWidgetState extends State<OnboardingWidget> {

  late TextEditingController _editingController;
  bool isParsing = false;

  _OnboardingWidgetState() {
    _editingController = TextEditingController()..text = "MT:-G7B4VSJ01C5MB73120";
  }  

  void onDetect(BarcodeCapture barcodes) {
    _editingController.text = barcodes.barcodes.firstOrNull?.displayValue ?? '';
    parserCode(_editingController.text);
  }

  void parserCode(String code) async {
    if (isParsing) {
      return;
    }
    isParsing = true;
    try {
      final payload = await OnboardingPayloadParser().parse(_editingController.text);
      Navigator.of(context).pushReplacement(MaterialPageRoute(builder: (_) {
        return WifiInputPage(onboardingPayload: payload, code: code,);
      }));
      return;
    } catch (e) {
        Fluttertoast.showToast(msg: '无效Code');
    }
    isParsing = false;
  }

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(
        title: Text('Onboarding'),
      ),
      body:  Stack(
        children: [
          MobileScanner(
            onDetect: onDetect,
          ),
          Align(
            alignment: Alignment.bottomCenter,
            child: Container(
              padding: EdgeInsets.all(6),
              color: Colors.white38,
              child: Row(
                children: [
                  Expanded(
                    child: TextField(
                      controller: _editingController,
                    ),
                  ),
                  ElevatedButton(
                    onPressed: () async {
                      parserCode(_editingController.text);
                    },
                    child: Text('Submit')
                  )
                ],
              ),
            ),
          )
        ],
      ),
    );
  }
}