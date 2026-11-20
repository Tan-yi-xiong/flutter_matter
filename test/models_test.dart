import 'dart:convert';
import 'dart:typed_data';

import 'package:flutter_test/flutter_test.dart';
import 'package:flutter_matter/flutter_matter.dart';

void main() {
  group('ChipPathId', () {
    test('encodes and decodes concrete ids', () {
      final id = ChipPathId.forId(6);
      final decoded = ChipPathId.fromJson(id.toJson());

      expect(decoded.id, 6);
      expect(decoded.type, IdType.concrete);
    });

    test('encodes and decodes wildcard ids', () {
      final id = ChipPathId.forWildcard();
      final decoded = ChipPathId.fromJson({
        'id': id.id,
        'type': 'WILDCARD',
      });

      expect(decoded.id, -1);
      expect(decoded.type, IdType.wildcard);
    });
  });

  test('attribute and event paths preserve their fields', () {
    final attributePath = ChipAttributePath(
      endpointId: ChipPathId.forId(1),
      clusterId: ChipPathId.forId(6),
      attributeId: ChipPathId.forWildcard(),
    );
    final decodedAttributePath =
        ChipAttributePath.fromJson(attributePath.toJson());

    expect(decodedAttributePath.endpointId.id, 1);
    expect(decodedAttributePath.clusterId.id, 6);
    expect(decodedAttributePath.attributeId.type, IdType.wildcard);

    final eventPath = ChipEventPath(
      endpointId: ChipPathId.forId(1),
      clusterId: ChipPathId.forId(0x0A),
      eventId: ChipPathId.forId(3),
      isUrgent: true,
    );

    expect(eventPath.toJson(), {
      'endpointId': {'id': 1, 'type': 'concrete'},
      'clusterId': {'id': 10, 'type': 'concrete'},
      'eventId': {'id': 3, 'type': 'concrete'},
      'isUrgent': true,
    });
  });

  test('data version and write request envelopes preserve their fields', () {
    final filter = DataVersionFilter(
      endpointId: ChipPathId.forId(1),
      clusterId: ChipPathId.forId(6),
      dataVersion: 12,
    );
    final request = AttributeWriteRequest(
      endpointId: ChipPathId.forId(1),
      clusterId: ChipPathId.forId(6),
      attributeId: ChipPathId.forId(0),
      dataVersion: 12,
      tlv: Uint8List.fromList([1, 2, 3]),
      json: '{"value":true}',
    );

    expect(filter.toJson()['dataVersion'], 12);
    expect(request.toJson(), {
      'endpointId': {'id': 1, 'type': 'concrete'},
      'clusterId': {'id': 6, 'type': 'concrete'},
      'attributeId': {'id': 0, 'type': 'concrete'},
      'dataVersion': 12,
      'tlv': [1, 2, 3],
      'json': '{"value":true}',
    });
  });

  test('InvokeElement round-trips through JSON', () {
    final invoke = InvokeElement.create(
      1,
      6,
      1,
      Uint8List.fromList([1, 2]),
      '{"command":"on"}',
    );
    final decoded = InvokeElement.fromJson(
      jsonDecode(jsonEncode(invoke.toJson())) as Map<String, dynamic>,
    );

    expect(decoded.endpointId?.id, 1);
    expect(decoded.clusterId.id, 6);
    expect(decoded.commandId.id, 1);
    expect(decoded.tlv, [1, 2]);
    expect(decoded.json, '{"command":"on"}');
  });

  test('NetworkCredentials supports legacy WiFi, named WiFi, and Thread', () {
    final legacy = NetworkCredentials(
      wifiCredentials: WiFiCredentials(ssid: 'legacy', password: 'secret'),
    );
    final openWifi = NetworkCredentials.wifi(
      WiFiCredentials(ssid: 'open', password: ''),
    );
    final thread = NetworkCredentials.thread(
      ThreadCredentials(operationalDataset: Uint8List.fromList([4, 5, 6])),
    );

    expect(legacy.toJson(), {
      'wifiCredentials': {'ssid': 'legacy', 'password': 'secret'},
    });
    expect(openWifi.toJson(), {
      'wifiCredentials': {'ssid': 'open', 'password': ''},
    });
    expect(thread.toJson(), {
      'threadCredentials': {
        'operationalDataset': [4, 5, 6],
      },
    });
  });

  test('ControllerParams keeps current defaults and wire keys', () {
    final encoded =
        jsonDecode(ControllerParams().encode()) as Map<String, dynamic>;

    expect(encoded['fabricId'], 1);
    expect(encoded['udpListenPort'], 0);
    expect(encoded['controllerVendorId'], 0xFFF4);
    expect(encoded['skipAttestationCertificateValidation'], isTrue);
    expect(encoded['nodeId'], 112233);
    expect(encoded.containsKey('setupURL'), isFalse);
  });

  test('NodeState decodes nested endpoint and cluster state', () {
    final state = NodeState.fromJson({
      'endpoints': {
        '1': {
          'clusters': {
            '6': {
              'attributes': {
                '0': {
                  'tlv': <int>[1, 2],
                  'json': '{"value":true}',
                },
              },
              'events': {
                '1': [
                  {
                    'eventNumber': 7,
                    'priorityLevel': 1,
                    'timestampType': 0,
                    'timestampValue': 100,
                    'tlv': null,
                    'json': '{}',
                  },
                ],
              },
              'attributeStatuses': {
                '0': {'status': 0},
              },
              'eventStatuses': {
                '1': [
                  {'status': 1, 'clusterStatus': 2},
                ],
              },
              'dataVersion': 9,
            },
          },
        },
      },
    });

    final cluster = state.endpoints[1]!.clusters[6]!;
    expect(cluster.attributes[0]!.tlv, [1, 2]);
    expect(cluster.attributes[0]!.json, '{"value":true}');
    expect(cluster.events[1]!.single.eventNumber, 7);
    expect(cluster.attributeStatuses[0]!.status, 0);
    expect(cluster.eventStatuses[1]!.single.clusterStatus, 2);
    expect(cluster.dataVersion, 9);
  });

  test('AttributeState normalizes integer byte JSON without width bounds', () {
    final state = AttributeState.fromJson(<String, dynamic>{
      'tlv': <int>[-0x81, -0x80, -1, 0, 0x7f, 0xff, 0x100, 0xffff],
    });

    expect(state.tlv, <int>[0x7f, 0x80, 0xff, 0, 0x7f, 0xff, 0, 0xff]);
  });

  test('ICDDeviceInfo round-trips through JSON', () {
    final info = ICDDeviceInfo(
      symmetricKey: Uint8List.fromList(List<int>.generate(16, (i) => i)),
      userActiveModeTriggerHint: [1, 2],
      userActiveModeTriggerInstruction: 'Press the button',
      icdNodeId: 10,
      icdCounter: 11,
      monitoredSubject: 12,
      fabricId: 13,
      fabricIndex: 2,
    );
    final decoded = ICDDeviceInfo.fromJson(
      jsonDecode(jsonEncode(info.toJson())) as Map<String, dynamic>,
    );

    expect(decoded.symmetricKey, info.symmetricKey);
    expect(decoded.userActiveModeTriggerHint, [1, 2]);
    expect(decoded.userActiveModeTriggerInstruction, 'Press the button');
    expect(decoded.icdNodeId, 10);
    expect(decoded.monitoredSubject, 12);
  });

  group('model JSON validation', () {
    void expectFormatContaining(String field, void Function() callback) {
      expect(
        callback,
        throwsA(
          isA<FormatException>().having(
            (error) => error.message,
            'message',
            contains(field),
          ),
        ),
      );
    }

    final path = <String, dynamic>{'id': 1, 'type': 'concrete'};

    test('path and invoke decoders report field-specific format errors', () {
      expectFormatContaining(
        'ChipPathId.id',
        () => ChipPathId.fromJson(<String, dynamic>{'type': 'concrete'}),
      );
      expectFormatContaining(
        'ChipPathId.type',
        () => ChipPathId.fromJson(<String, dynamic>{
          'id': 1,
          'type': 'future-type',
        }),
      );
      expectFormatContaining(
        'ChipAttributePath.endpointId',
        () => ChipAttributePath.fromJson(<String, dynamic>{
          'endpointId': 'bad',
          'clusterId': path,
          'attributeId': path,
        }),
      );
      expectFormatContaining(
        'InvokeElement.groupId',
        () => InvokeElement.fromJson(<String, dynamic>{
          'clusterId': path,
          'commandId': path,
          'groupId': '1',
        }),
      );
      expectFormatContaining(
        'InvokeElement.tlv',
        () => InvokeElement.fromJson(<String, dynamic>{
          'clusterId': path,
          'commandId': path,
          'tlv': 'not-a-byte-array',
        }),
      );
    });

    test('attribute, event, and status decoders reject invalid field types',
        () {
      expectFormatContaining(
        'AttributeState.tlv',
        () => AttributeState.fromJson(<String, dynamic>{'tlv': 'bad'}),
      );
      expectFormatContaining(
        'AttributeState.json',
        () => AttributeState.fromJson(<String, dynamic>{'json': 4}),
      );
      expectFormatContaining(
        'EventState.eventNumber',
        () => EventState.fromJson(<String, dynamic>{
          'priorityLevel': 1,
          'timestampType': 0,
          'timestampValue': 1,
        }),
      );
      expectFormatContaining(
        'EventState.tlv[0]',
        () => EventState.fromJson(<String, dynamic>{
          'eventNumber': 1,
          'priorityLevel': 1,
          'timestampType': 0,
          'timestampValue': 1,
          'tlv': <dynamic>['bad'],
        }),
      );
      expectFormatContaining(
        'Status.status',
        () => Status.fromJson(<String, dynamic>{'status': '0'}),
      );
      expectFormatContaining(
        'Status.clusterStatus',
        () => Status.fromJson(<String, dynamic>{
          'status': 0,
          'clusterStatus': 'bad',
        }),
      );
    });

    test('node, endpoint, and cluster decoders report nested field context',
        () {
      expectFormatContaining(
        'NodeState.endpoints',
        () => NodeState.fromJson(<String, dynamic>{
          'endpoints': <dynamic>[],
        }),
      );
      expectFormatContaining(
        'NodeState.endpoints key',
        () => NodeState.fromJson(<String, dynamic>{
          'endpoints': <String, dynamic>{'not-an-int': <String, dynamic>{}},
        }),
      );
      expectFormatContaining(
        'NodeState.endpoints[1]',
        () => NodeState.fromJson(<String, dynamic>{
          'endpoints': <String, dynamic>{'1': <dynamic>[]},
        }),
      );
      expectFormatContaining(
        'EndpointState.clusters',
        () => EndpointState.fromJson(<String, dynamic>{
          'clusters': 'bad',
        }),
      );
      expectFormatContaining(
        'ClusterState.attributes',
        () => ClusterState.fromJson(<String, dynamic>{
          'attributes': <dynamic>[],
        }),
      );
      expectFormatContaining(
        'ClusterState.events[1]',
        () => ClusterState.fromJson(<String, dynamic>{
          'events': <String, dynamic>{'1': <String, dynamic>{}},
        }),
      );
      expectFormatContaining(
        'ClusterState.events[1][0]',
        () => ClusterState.fromJson(<String, dynamic>{
          'events': <String, dynamic>{
            '1': <dynamic>[<dynamic>[]],
          },
        }),
      );
      expectFormatContaining(
        'ClusterState.dataVersion',
        () => ClusterState.fromJson(<String, dynamic>{
          'dataVersion': '9',
        }),
      );
    });

    test('ICD device info validates key, hints, and numeric fields', () {
      final validIcd = <String, dynamic>{
        'symmetricKey': List<int>.generate(16, (i) => i),
        'userActiveModeTriggerHint': <int>[1, 2],
        'userActiveModeTriggerInstruction': 'Press',
        'icdNodeId': 1,
        'icdCounter': 2,
        'monitoredSubject': 3,
        'fabricId': 4,
        'fabricIndex': 5,
      };

      expectFormatContaining(
        'ICDDeviceInfo.symmetricKey',
        () => ICDDeviceInfo.fromJson(<String, dynamic>{
          ...validIcd,
          'symmetricKey': <int>[1, 2],
        }),
      );
      expectFormatContaining(
        'ICDDeviceInfo.userActiveModeTriggerHint',
        () => ICDDeviceInfo.fromJson(<String, dynamic>{
          ...validIcd,
          'userActiveModeTriggerHint': '1,2',
        }),
      );
      expectFormatContaining(
        'ICDDeviceInfo.icdNodeId',
        () => ICDDeviceInfo.fromJson(<String, dynamic>{
          ...validIcd,
          'icdNodeId': '1',
        }),
      );
    });
  });
}
