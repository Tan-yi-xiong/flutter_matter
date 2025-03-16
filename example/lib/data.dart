
import 'dart:async';
import 'dart:convert';
import 'dart:typed_data';

import 'package:flutter/material.dart';
import 'package:flutter_matter/flutter_matter.dart';
import 'package:hex/hex.dart';
import 'package:pem/pem.dart';
import 'package:pointycastle/export.dart';
import 'package:pointycastle/pointycastle.dart';
import 'package:shared_preferences/shared_preferences.dart';

const key_certificate = 'network_certificate';
const key_keypair = 'network_keypair';
const key_max_nodeId = 'last_node_id';
const key_devices = 'devices';

List<int> bigIntToBytes(BigInt bigInt) {
  String hexString = bigInt.toRadixString(16);
  
  if (hexString.length % 2 != 0) {
    hexString = '0$hexString';
  }

  return HEX.decode(hexString);
}


class MyKeypairDelegate implements KeypairDelegate {
  final ECPublicKey publicKey;
  final ECPrivateKey privateKey;
  final Uint8List? pubKey;

  MyKeypairDelegate({required this.publicKey, required this.privateKey, this.pubKey});

  @override
  Uint8List createCertificateSigningRequest() {
    // TODO: implement createCertificateSigningRequest
    throw UnimplementedError();
  }

  @override
  Uint8List ecdsaSignMessage(List<int> message) {
    final secureRandom = FortunaRandom();

    // 使用当前时间生成随机数种子
    final seed = Uint8List(32);
    final random = DateTime.now().millisecondsSinceEpoch;
    for (int i = 0; i < seed.length; i++) {
      seed[i] = random % 256;
    }
    secureRandom.seed(KeyParameter(seed));
    var signer = ECDSASigner(SHA256Digest());
    signer.init(true, ParametersWithRandom(PrivateKeyParameter(privateKey), secureRandom));  // true表示签名

    // 对消息进行签名
    var signature = signer.generateSignature(Uint8List.fromList(message)) as ECSignature;
    final encoded = ASN1Sequence(elements: [
      ASN1Integer(signature.r),
      ASN1Integer(signature.s),
    ]).encode();
    print('ecdsaSignMessage ${message}');
    return encoded;
  }

  @override
  void generatePrivateKey() {
    // TODO: implement generatePrivateKey
  }

  @override
  Uint8List getPublicKey() {
    print('getPublicKey call');

    if (this.pubKey != null) {
      print('reutrn pubkey');
      return pubKey!;
    }

    // 获取 X 和 Y 坐标
    final x = publicKey.Q!.x!.toBigInteger()!;
    final y = publicKey.Q!.y!.toBigInteger()!;

    // 将 X 和 Y 坐标转换为字节数组，并补齐到 32 字节（256 位）
    final xBytes = x.toRadixString(16).padLeft(64, '0');
    final yBytes = y.toRadixString(16).padLeft(64, '0');

    // 将 X 和 Y 坐标转换为 Uint8List
    final xUint8List = Uint8List.fromList(
        List<int>.generate(32, (i) => int.parse(xBytes.substring(i * 2, i * 2 + 2), radix: 16)));
    final yUint8List = Uint8List.fromList(
        List<int>.generate(32, (i) => int.parse(yBytes.substring(i * 2, i * 2 + 2), radix: 16)));

    // 构造无压缩格式的公钥：0x04 + X 坐标 + Y 坐标
    final uncompressedPublicKey = Uint8List(1 + xUint8List.length + yUint8List.length);
    uncompressedPublicKey[0] = 0x04;
    uncompressedPublicKey.setRange(1, 33, xUint8List);
    uncompressedPublicKey.setRange(33, 65, yUint8List);


    return uncompressedPublicKey;
  }
  
}

Future<AsymmetricKeyPair<ECPublicKey, ECPrivateKey>> genAsymmetricKeyPair() async {
  SharedPreferences sp = await SharedPreferences.getInstance();
  final keypairJson = sp.getString(key_keypair);
  if (keypairJson == null) {
    final key = generateP256KeyPair();
    final encodeData = PemCodec(PemLabel.publicKey).encode(Uint8List.fromList((key.publicKey as ECPublicKey).Q!.getEncoded()));
    final encodePriData = PemCodec(PemLabel.privateKey).encode(bigIntToBytes((key.privateKey as ECPrivateKey).d!));
    sp.setString(key_keypair, jsonEncode({
      "publicKey": encodeData,
      "privateKey": encodePriData,
    }));
    return AsymmetricKeyPair(key.publicKey as ECPublicKey, key.privateKey as ECPrivateKey);
  } else {
    final data = jsonDecode(keypairJson);
    
    /// this is ai generate code 😝
    var ecDomainParams = ECCurve_secp256r1(); // 使用 secp256r1 曲线
    var q = ecDomainParams.curve.decodePoint(PemCodec(PemLabel.publicKey).decode(data['publicKey'])); // 从字节数组恢复公钥点

    final publicKey = ECPublicKey(q, ecDomainParams);
    var pem = PemCodec(PemLabel.privateKey).decode(data['privateKey']);
    
    // 提取私钥的字节数据
    var privateKeyBytes = pem;

    // 从字节数据创建 ECPrivateKey 对象
    var privateKey = ECPrivateKey(
      BigInt.parse(HEX.encode(privateKeyBytes), radix: 16),
      ECCurve_secp256r1(),
    );

    return AsymmetricKeyPair(publicKey, privateKey);
  }
}

/// this is ai generate code 😝
AsymmetricKeyPair<PublicKey, PrivateKey> generateP256KeyPair() {
  // 创建一个椭圆曲线密钥生成器
  final keyParams = ECKeyGeneratorParameters(ECCurve_secp256r1());
  final secureRandom = FortunaRandom();

  // 使用当前时间生成随机数种子
  final seed = Uint8List(32);
  final random = DateTime.now().millisecondsSinceEpoch;
  for (int i = 0; i < seed.length; i++) {
    seed[i] = random % 256;
  }
  secureRandom.seed(KeyParameter(seed));

  final keyGen = ECKeyGenerator()
    ..init(ParametersWithRandom(keyParams, secureRandom));

  // 生成密钥对
  return keyGen.generateKeyPair();
}


/// return the app rcac and phone noc
Future<List<Uint8List>> getX509Certificate() async {
  SharedPreferences sp = await SharedPreferences.getInstance();
  final certificates = sp.getString(key_certificate);
  if (certificates != null) {
    final matterInfoData = jsonDecode(certificates);
    final rootCertificate = Uint8List.fromList(matterInfoData['rcac'].cast<int>());
    final operationalCertificate = Uint8List.fromList(matterInfoData['nodeOC'].cast<int>());
    print('rootCertificate: ${base64.encode(rootCertificate)} \n operationalCertificate: ${base64.encode(operationalCertificate)}');
    return [rootCertificate, operationalCertificate];
  }
  final asymmetricKeyPair = await genAsymmetricKeyPair();
  final kp = MyKeypairDelegate(publicKey: asymmetricKeyPair.publicKey, privateKey: asymmetricKeyPair.privateKey);
  final rcac = await ChipDeviceController.createRootCertificate(kp, 0, await getFabricId());
  final nodeOC = await ChipDeviceController.createOperationalCertificate(kp, rcac, kp.getPublicKey(), await getFabricId(), kTestControllerNodeId, null);
  // c.deleteDeviceController();
  sp.setString(key_certificate, jsonEncode({
    'rcac': rcac,
    'nodeOC': nodeOC
  }));
  return [rcac, nodeOC];
}

class Device {
  final int nodeId;

  Device(this.nodeId);

  toJson() {
    return {
      'nodeId': nodeId,
    };
  }

  factory Device.fromJson(Map<String, dynamic> json) {
    return Device(json['nodeId']);
  }
}

Future<int> getNodeId() async {
  final sp = await SharedPreferences.getInstance();
  final nodeId = sp.getInt(key_max_nodeId) ?? 0;
  return nodeId;
}

Future<int> nextNodeId() async {
  final nextNodeId = await getNodeId().then((value) => value + 1);
  return nextNodeId;
}

Future<int> getFabricId() async {
  return 709394;
}


Future<ChipDeviceController> createChipDeviceController() async {
  final keypair = await genAsymmetricKeyPair();
  final kp = keypair;
  final cert = await getX509Certificate();
  final fabricId = await getFabricId();
  final cp = ControllerParams(
    skipCommissioningComplete: false,
    fabricId: fabricId,
    keypairDelegate: MyKeypairDelegate(publicKey: kp.publicKey, privateKey: kp.privateKey),
    ipk: defaultIpk,
    rootCertificate: cert[0],
    intermediateCertificate: cert[0],
    operationalCertificate: cert[1]
  );
  
  return await ChipDeviceController.newControllerIfNotExist(cp);
}

StreamController deviceChangeNotifier = StreamController.broadcast();

Future<void> saveDevice(Device device) async {
  final sp = await SharedPreferences.getInstance();
  final devices = sp.getString(key_devices);
  final devicesList = devices == null ? [] : jsonDecode(devices).cast<Map<String, dynamic>>();
  devicesList.add(device.toJson());
  await sp.setInt(key_max_nodeId, device.nodeId);
  await sp.setString(key_devices, jsonEncode(devicesList)).then((value) {
    deviceChangeNotifier.add(null);
    return value;
  });
}

Future<List<Device>> getDevices() async {
  final sp = await SharedPreferences.getInstance();
  final devices = sp.getString(key_devices);
  final devicesList = devices == null ? [] : jsonDecode(devices).cast<Map<String, dynamic>>();
  return devicesList.map((e) => Device.fromJson(e.cast<String, dynamic>())).toList().cast<Device>();
}

Future<bool> deleteDevice(Device device) async {
  final sp = await SharedPreferences.getInstance();
  final devices = sp.getString(key_devices);
  final devicesList = devices == null ? [] : jsonDecode(devices).cast<Map<String, dynamic>>();
  final newDevicesList = devicesList.where((element) => element['nodeId'] != device.nodeId).toList();
  return await sp.setString(key_devices, jsonEncode(newDevicesList)).then((value) {
    deviceChangeNotifier.add(null);
    return value;
  });
}