import 'package:flutter/material.dart';
import 'package:flutter_matter_example/control_page.dart';
import 'package:flutter_matter_example/onboarding.dart';
import 'package:flutter_matter_example/uitls.dart';

import 'data.dart';

class HomePage extends StatefulWidget {
  const HomePage({super.key});

  @override
  State<HomePage> createState() => _HomePageState();
}

class _HomePageState extends State<HomePage> {
  List<Device> devices = [];

  @override
  void initState() {
    super.initState();
    _getDevices();
    deviceChangeNotifier.stream.listen((event) {
      _getDevices();
    });
  }

  void _getDevices() async {
    getDevices().then((value) {
      setState(() {
        devices = value;
      });
    }).catchError((e) {
      showToast("Get devices error $e");
    });
  }

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(title: const Text('Flutter Matter Plugin Demo')),
      floatingActionButton: FloatingActionButton(
          child: Icon(Icons.add),
          onPressed: () {
            Navigator.of(context).push(MaterialPageRoute(
              builder: (context) {
                return OnboardingWidget();
              },
            ));
          }),
      body: ListView.builder(
        itemBuilder: (context, index) {
          return ListTile(
            title: Text("Device ${devices[index].nodeId}"),
            subtitle: Text("NodeId: ${devices[index].nodeId}"),
            onTap: () {
              Navigator.of(context).push(MaterialPageRoute(
              builder: (context) {
                return ControlPage(device: devices[index],);
              },
            ));
            },
          );
        },
        itemCount: devices.length,
      ),
    );
  }
}
