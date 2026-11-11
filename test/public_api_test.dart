import 'dart:io';
import 'dart:typed_data';

import 'package:flutter_test/flutter_test.dart';
import 'package:flutter_matter/flutter_matter.dart';

void main() {
  test('public export list matches the contract golden', () {
    final source = File('lib/flutter_matter.dart').readAsStringSync();
    final exports = RegExp(r"^export '([^']+)'", multiLine: true)
        .allMatches(source)
        .map((match) => match.group(1)!)
        .toList()
      ..sort();

    expect(exports, <String>[
      'src/ble.dart',
      'src/clusters/basic_information_cluster.dart',
      'src/clusters/descriptor_cluster.dart',
      'src/controller.dart',
      'src/model/attribute_state.dart',
      'src/model/attribute_write_request.dart',
      'src/model/chip_attribute_path.dart',
      'src/model/chip_event_path.dart',
      'src/model/chip_path_id.dart',
      'src/model/cluster_state.dart',
      'src/model/data_version_filter.dart',
      'src/model/endpoint_state.dart',
      'src/model/event_state.dart',
      'src/model/icd_device_info.dart',
      'src/model/invoke_element.dart',
      'src/model/node_state.dart',
      'src/model/status.dart',
      'src/nsd.dart',
      'src/onboarding.dart',
      'src/tlv/element.dart',
      'src/tlv/tag.dart',
      'src/tlv/tlv_reader.dart',
      'src/tlv/tlv_types.dart',
      'src/tlv/tlv_writer.dart',
      'src/tlv/values.dart',
    ]);
  });

  test('representative public symbols remain usable', () {
    final controllerParams = ControllerParams();
    final credentials = NetworkCredentials.wifi(
      WiFiCredentials(ssid: 'matter', password: ''),
    );
    final wildcard = ChipPathId.forWildcard();
    final writer = TlvWriter();
    final reader = TlvReader(Uint8List(0));
    final payload = OnboardingPayload(
      version: 0,
      vendorId: 1,
      productId: 2,
      commissioningFlow: 0,
      discoveryCapabilities: {DiscoveryCapability.ble},
      discriminator: 1,
      hasShortDiscriminator: false,
      setupPinCode: 20202021,
    );

    final apiTypes = <Type>[
      AttributeState,
      BLEManager,
      ChipDeviceController,
      CompletionListener,
      DescriptorCluster,
      ICDDeviceInfo,
      NsdManager,
      Status,
    ];

    expect(controllerParams.fabricId, 1);
    expect(credentials.wifiCredentials?.password, '');
    expect(wildcard.type, IdType.wildcard);
    expect(writer.getEncoded(), isEmpty);
    expect(reader.getRemainingLength(), 0);
    expect(payload.vendorId, 1);
    expect(apiTypes, hasLength(8));
  });
}
