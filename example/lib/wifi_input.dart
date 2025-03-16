
import 'package:flutter/foundation.dart';
import 'package:flutter/material.dart';
import 'package:flutter_matter/flutter_matter.dart';
import 'package:flutter_matter_example/device_provisioning.dart';
import 'package:fluttertoast/fluttertoast.dart';
import 'package:shared_preferences/shared_preferences.dart';

class WifiInputPage extends StatefulWidget {
  final OnboardingPayload onboardingPayload;
  final String code;
  const WifiInputPage({super.key, required this.onboardingPayload, required this.code});

  @override
  State<WifiInputPage> createState() => _WifiInputPageState();
}

class _WifiInputPageState extends State<WifiInputPage> {

  TextEditingController _ssidController = TextEditingController();
  TextEditingController _passwordController = TextEditingController();

  @override
  void initState() {
    super.initState();
    SharedPreferences.getInstance().then((sp) {
      _ssidController.text = sp.getString('wifi_ssid') ?? '';
      _passwordController.text = sp.getString('wifi_password') ?? '';
    });
  }

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(title: Text('WifiInfo'),),
      body: Padding(
        padding: const EdgeInsets.symmetric(horizontal: 16),
        child: Column(
          children: [
            TextField(
              controller: _ssidController,
              decoration: InputDecoration(
                hintText: 'WifiName'
              ),
            ),
            TextField(
              controller: _passwordController,
              decoration: InputDecoration(
                hintText: 'WifiPassword'
              ),
            ),
            SizedBox(height: 16,),
            ElevatedButton(onPressed: () {
              final ssid = _ssidController.text;
              final password = _passwordController.text;
              if (ssid.trim().isEmpty || password.trim().isEmpty) {
                Fluttertoast.showToast(msg: '请输入wifi信息');
                return;
              }
              SharedPreferences.getInstance().then((sp) {
                sp.setString('wifi_ssid', ssid);
                sp.setString('wifi_password', password);
              });
              Navigator.of(context).pushReplacement(MaterialPageRoute(builder: (_) {
                return DeviceProvisioningPage(
                  payload: widget.onboardingPayload,
                  onboardingPayload: widget.code,
                  wiFiCredentials: WiFiCredentials(ssid: ssid, password: password),
                );
              }));
            }, child: Text('下一步'))
          ]
        ),
      ),
    );
  }
}