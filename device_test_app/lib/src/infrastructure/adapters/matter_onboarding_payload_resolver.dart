import 'package:flutter_matter/flutter_matter.dart';

abstract interface class MatterOnboardingPayloadResolver {
  Future<OnboardingPayload> resolve(String payload);
}

class FlutterMatterOnboardingPayloadResolver
    implements MatterOnboardingPayloadResolver {
  FlutterMatterOnboardingPayloadResolver({OnboardingPayloadParser? parser})
    : _parser = parser ?? OnboardingPayloadParser();

  final OnboardingPayloadParser _parser;

  @override
  Future<OnboardingPayload> resolve(String payload) => _parser.parse(payload);
}
