import 'package:flutter/material.dart';
import 'package:flutter_matter/flutter_matter.dart';
import 'package:flutter_matter_example/data.dart';
import 'package:collection/collection.dart';

import 'uitls.dart';

class _ConnectedDeviceCallbackWarp extends ConnectedDeviceCallback {
  final Function(Object? context) onConnectedFun;
  final Function(Exception)? onConnectionFailureFun;

  _ConnectedDeviceCallbackWarp({required this.onConnectedFun, this.onConnectionFailureFun});

  @override
  void onConnected(Object? context) {
    onConnectedFun(context);
  }

  @override
  void onError(Exception e) {
    onConnectionFailureFun?.call(e);
  }
  
}

class OpenCommissioningCallbackWarp extends OpenCommissioningCallback {
  @override
  void onError(int status, Object? connectContext) {
    print("OpenCommissioningCallbackWarp onError");
  }

  @override
  void onSuccess(Object? connectContext, String manualPairingCode, String qrCode) {
    print('OpenCommissioningCallbackWarp onSuccess $manualPairingCode $qrCode');
  }
}


class ControlPage extends StatefulWidget {
  final Device device;
  const ControlPage({super.key, required this.device});

  @override
  State<ControlPage> createState() => _ControlPageState();
}

class _ControlPageState extends State<ControlPage>
    with SingleTickerProviderStateMixin {
  late TabController tabController;
  Object? connectContext;
  bool connectting = false;
  ChipDeviceController? chipDeviceController;
  final tabs = [
    Tab(text: 'On/Off'),
    Tab(text: 'Read/Write'),
    // Tab(text: 'Subscribe'),
    Tab(text: 'OCW'),
  ];

  @override
  void initState() {
    super.initState();
    tabController = TabController(length: tabs.length, vsync: this);
    createChipDeviceController().then((value) {
      this.chipDeviceController = value;
    });
  }

  void _changeConnectState() {
    if (this.chipDeviceController == null || connectting) {
      return;
    }
    connectting = true;
    if (connectContext == null) {
      chipDeviceController!.connectedDevice(
          widget.device.nodeId,
          _ConnectedDeviceCallbackWarp(onConnectionFailureFun: (_) {
            connectting = false;
          }, onConnectedFun: (context) {
            setState(() {
              connectting = false;
              this.connectContext = context;
            });
          }));
    } else {
      setState(() {
        connectting = false;
        connectContext = null;
      });
    }
  }

  void _unPairDevice() {
    int endpointId = 0; // root endpoint
    int attributeId = 0x00000005;
    int clusterId = 0x0000003E;
    
    chipDeviceController!.read(
      widget.device.nodeId, 
      connectContext: connectContext,
      new ReportCallbackWarp(
        onReportFun: (nodeState) {
          final tlvData = nodeState.endpoints[endpointId]?.clusters[clusterId]?.attributes[attributeId]?.tlv;
          if (tlvData == null) {
            showToast("delete failed");
            return;
          }
          final tlvReader = TlvReader(tlvData);
          final fabricIndex = tlvReader.getUByte(AnonymousTag.instance);

          // send remove command
          final tlvWriter = TlvWriter();
          tlvWriter.startStructure(AnonymousTag.instance);
          tlvWriter.putUnsigned(ContextSpecificTag(0), fabricIndex);
          tlvWriter.endStructure();
          chipDeviceController!.invoke(InvokeCallbackWarp(
            onResponseCB: (p0, p1) {
              showToast("delete success");
              deleteDevice(widget.device);
              Navigator.pop(context);
            },
            onErrorCB: (p1) {
              showToast("delete failed");
            },
          ), widget.device.nodeId, timedRequestTimeoutMs: 5000, connectContext: connectContext, InvokeElement.create(endpointId, clusterId, 0x0A, tlvWriter.getEncoded(), null));
        },
        onErrorFun: (_, __, ___) {
          showToast("delete failed");
        },
      ), 
      [ChipAttributePath(endpointId: ChipPathId.forId(endpointId), attributeId: ChipPathId.forId(attributeId), clusterId: ChipPathId.forId(clusterId),)],
      null, 
      null, 
      false, 
      5000, 
      0
    );
  }

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(
        title: const Text('Control'),
        actions: [
          TextButton(
              onPressed: () {
                _changeConnectState();
              },
              child: Text(connectContext == null ? "Connect" : "disConnect"))
        ],
        bottom: TabBar(
          controller: tabController,
          tabs: tabs,
        ),
      ),
      floatingActionButton: FloatingActionButton(onPressed: () {
        _unPairDevice();
      }, child: Icon(Icons.delete), backgroundColor: Colors.red,),
      body: TabBarView(
        controller: tabController,
        children: tabs.mapIndexed((index, e) {
          return Builder(builder: (_) {
            if (connectContext == null) {
              return Center(child: Text("Device not connected"));
            } else {
              if (tabs[index].text == 'OCW') {
                return OCWTabPage(
                    chipDeviceController: chipDeviceController!,
                    controlDevice: widget.device,
                    controlContext: connectContext);
              }
              if (tabs[index].text == 'Read/Write') {
                return Read_WritePage(
                    chipDeviceController: chipDeviceController!,
                    controlDevice: widget.device,
                    controlContext: connectContext);
              }
              return OnOffPage(
                  chipDeviceController: chipDeviceController!,
                  controlDevice: widget.device);
            }
          });
        }).toList(),
      ),
    );
  }
}

class InvokeCallbackWarp implements InvokeCallback {
  final Function()? onDoneCB;
  final Function(Exception)? onErrorCB;
  final Function(InvokeElement, int)? onResponseCB;

  InvokeCallbackWarp({this.onDoneCB, this.onErrorCB, this.onResponseCB});

  @override
  void onDone() {
    onDoneCB?.call();
  }

  @override
  void onError(Exception e) {
    onErrorCB?.call(e);
  }

  @override
  void onResponse(InvokeElement invokeElement, int successCode) {
    onResponseCB?.call(invokeElement, successCode);
  }
}

/// On/Off Page
class OnOffPage extends StatefulWidget {
  final ChipDeviceController chipDeviceController;
  final Device controlDevice;
  final Object? controlContext;
  const OnOffPage(
      {super.key,
      required this.chipDeviceController,
      required this.controlDevice,
      this.controlContext});

  @override
  State<OnOffPage> createState() => _OnOffPageState();
}

class _OnOffPageState extends State<OnOffPage> {
  Set<int> subscribedIds = {};
  String? onoffState;

  void _onoffControl(int commandId) {
    TlvWriter writer = TlvWriter();
    writer.startStructure(AnonymousTag.instance);
    writer.endStructure();
    final ele =
        InvokeElement.create(0x1, 0x6, commandId, writer.getEncoded(), null);
    widget.chipDeviceController.invoke(
        connectContext: widget.controlContext,
        InvokeCallbackWarp(
          onResponseCB: (p0, p1) {
            showToast("Send successfully");
          },
          onErrorCB: (p1) {
            showToast("Send failed");
          },
        ),
        widget.controlDevice.nodeId,
        ele);
  }

  void _subscribe() {
    int endpointId = 1;
    int attributeId = 0x00000000;
    int clusterId = 0x00000006;
    widget.chipDeviceController.subscribe(
      connectContext: widget.controlContext,
      widget.controlDevice.nodeId,
      SubscriptionCallbackWarp(
        onSubscriptionEstablishedFun: (subscriptionId) {
          subscribedIds.add(subscriptionId);
        },
        onDoneFun: () {
          setState(() {
            onoffState = null;
          });
        },
        onReportFun: (nodeState) {
          final tlvData = nodeState.endpoints[endpointId]?.clusters[clusterId]
              ?.attributes[attributeId]?.tlv;
          setState(() {
            onoffState =
                "on: ${TlvReader(tlvData!).getBool(AnonymousTag.instance)}";
          });
        },
      ),
      [
        ChipAttributePath(
          endpointId: ChipPathId.forId(endpointId),
          attributeId: ChipPathId.forId(attributeId),
          clusterId: ChipPathId.forId(clusterId),
        )
      ],
      null,
      3,
      8,
      true,
      false,
      6000,
      0,
    );
  }

  @override
  void dispose() {
    super.dispose();
    subscribedIds.forEach((element) {
      widget.chipDeviceController.getFabricIndex().then((value) {
        if (value == null) {
          return;
        }
        widget.chipDeviceController
            .unSubscription(value, widget.controlDevice.nodeId, element);
      });
    });
  }

  @override
  Widget build(BuildContext context) {
    return ListView(
      children: [
        ListTile(
          title: const Text('Off'),
          onTap: () {
            _onoffControl(0);
          },
        ),
        ListTile(
          title: const Text('On'),
          onTap: () {
            _onoffControl(1);
          },
        ),
        ListTile(
          title: const Text('Toggle'),
          onTap: () {
            _onoffControl(2);
          },
        ),
        ListTile(
          title: const Text('Subscribe on/off state'),
          subtitle: onoffState == null ? null : Text(onoffState!),
          onTap: () {
            _subscribe();
          },
        ),
      ],
    );
  }
}

/// OCW Page
class OCWTabPage extends StatelessWidget {
  final ChipDeviceController chipDeviceController;
  final Device controlDevice;
  final Object? controlContext;

  const OCWTabPage(
      {super.key,
      required this.chipDeviceController,
      required this.controlDevice,
      this.controlContext});

  @override
  Widget build(BuildContext context) {
    return Center(
      child: Column(
        children: [
          ElevatedButton(
              onPressed: () {
                final tlvWriter = TlvWriter();
                tlvWriter.startStructure(AnonymousTag.instance);
                tlvWriter.endStructure();
                final invokeElement = InvokeElement.create(
                    0, 0x0000003C, 0x00000002, tlvWriter.getEncoded(), null);
                chipDeviceController!.invoke(
                    InvokeCallbackWarp(
                      onDoneCB: () {
                        chipDeviceController
                            .openPairingWindowWithPIN(
                                controlContext!,
                                180,
                                3850,
                                20202021,
                                new OpenCommissioningCallbackWarp())
                            .then((value) {
                          showToast("Success, code: ${value}");
                        }).catchError((e, s) {
                          print(s);
                          showToast("failed");
                        });
                      },
                      onResponseCB: (_, __) {},
                      onErrorCB: (p0) {},
                    ),
                    controlDevice.nodeId,
                    invokeElement,
                    connectContext: controlContext,
                    timedRequestTimeoutMs: 2000,
                    imTimeoutMs: 0);
              },
              child: Text('openPairingWindow'))
        ],
      ),
    );
  }
}


/// Read/Write Page
class Read_WritePage extends StatefulWidget {
  final ChipDeviceController chipDeviceController;
  final Device controlDevice;
  final Object? controlContext;
  const Read_WritePage({super.key, required this.chipDeviceController, required this.controlDevice, this.controlContext});

  @override
  State<Read_WritePage> createState() => _Read_WritePageState();
}

class _Read_WritePageState extends State<Read_WritePage> {

  String _readValue = '';
  TextEditingController editingController = TextEditingController();

  void _writeNodeLabel(String writeValue) {
    int endpointId = 0; // root endpoint
    int clusterId = 0x00000028;
    int attributeId = 0x00000005;
    widget.chipDeviceController.write(
      widget.controlDevice.nodeId, 
      WriteAttributesCallbackWarp(
        onResponseFun: (_, __) {
          showToast("Write Success");
        },
      ), 
      [AttributeWriteRequest(endpointId: ChipPathId.forId(endpointId), clusterId: ChipPathId.forId(clusterId), attributeId: ChipPathId.forId(attributeId), dataVersion: 0, tlv: TlvWriter().putString(AnonymousTag.instance, writeValue).getEncoded())], 
      5000, 
      2000,
      connectContext: widget.controlContext
    );
  }

  void _readNodeLabel() {
    int endpointId = 0; // root endpoint
    int clusterId = 0x00000028;
    int attributeId = 0x00000005;
    widget.chipDeviceController.read(
      widget.controlDevice.nodeId, 
      connectContext: widget.controlContext,
      new ReportCallbackWarp(
        onReportFun: (nodeState) {
          final tlvData = nodeState.endpoints[endpointId]?.clusters[clusterId]?.attributes[attributeId]?.tlv;
          if (tlvData == null) {
            showToast("read failed");
            return;
          }
          TlvReader reader = TlvReader(tlvData);
          setState(() {
            this._readValue = reader.getString(AnonymousTag.instance).toString();
          });
        },
        onErrorFun: (_, __, ___) {
          showToast("read failed");
        },
      ), 
      [ChipAttributePath(endpointId: ChipPathId.forId(endpointId), attributeId: ChipPathId.forId(attributeId), clusterId: ChipPathId.forId(clusterId),)],
      null, 
      null, 
      false, 
      5000, 
      0
    );
  }

  @override
  Widget build(BuildContext context) {
    return Center(
      child: Column(
        children: [
          Row(
            children: [
              Text("NodeLabel: "),
              SizedBox(width: 5,),
              Expanded(
                child: TextField(
                  controller: editingController,
                  decoration: InputDecoration(
                    hintText: "Enter a value"
                  ),
                ),
              ),
            ],
          ),
          SizedBox(height: 16,),
          ElevatedButton(
            onPressed: () {
              final writeValue = editingController.text;
              if (writeValue.isEmpty) {
                showToast("Please enter a value");
                return;
              }
              _writeNodeLabel(writeValue);
            },
            child: Text("Write NodeLabel"),
          ),
          SizedBox(height: 32,),
          ElevatedButton(
            onPressed: () {
              _readNodeLabel();
            },
            child: Text("Read NodeLabel"),
          ),
          SizedBox(height: 12,),
          Text("Device NodeLabel Value: $_readValue")
        ],
      ),
    );
  }
}