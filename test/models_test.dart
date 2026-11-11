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
}
