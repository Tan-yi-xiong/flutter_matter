#include "Onboarding.h"
#include "ZGMatter/ZGMatter.h"
#include "Utiles.h"
#include "Global.h"
#include "Constants.h"

static NSArray *FlutterMatterDiscoveryCapabilitiesJSON(ZGMTRSetupPayload *setupPayload) {
    if (@available(iOS 16.4, *)) {
        ZGMTRDiscoveryCapabilities discoveryCapabilities = [setupPayload discoveryCapabilities];
        NSMutableArray *capabilities = [NSMutableArray array];
        if ((discoveryCapabilities & ZGMTRDiscoveryCapabilitiesSoftAP) != 0) {
            [capabilities addObject:@(1)];
        }
        if ((discoveryCapabilities & ZGMTRDiscoveryCapabilitiesBLE) != 0) {
            [capabilities addObject:@(2)];
        }
        if ((discoveryCapabilities & ZGMTRDiscoveryCapabilitiesOnNetwork) != 0) {
            [capabilities addObject:@(3)];
        }
        return capabilities;
    }
    return @[];
}

static NSDictionary *FlutterMatterSetupPayloadJSON(ZGMTRSetupPayload *setupPayload) {
    NSMutableDictionary *result = [@{
        @"productId": [setupPayload productID],
        @"vendorId": [setupPayload vendorID],
        @"commissioningFlow": @([setupPayload commissioningFlow]),
        @"discriminator": [setupPayload discriminator],
        @"version": [setupPayload version],
        @"setupPinCode": [setupPayload setUpPINCode],
        @"hasShortDiscriminator": @([setupPayload hasShortDiscriminator])
    } mutableCopy];
    result[@"discoveryCapabilities"] = FlutterMatterDiscoveryCapabilitiesJSON(setupPayload);
    return result;
}

static NSString *parseManualPairingCode(NSString *params) {
    NSDictionary *jsonObject = FlutterMatterParseJSONObject(params);
    NSString *decimalString = FlutterMatterRequiredString(jsonObject, @"pairingCode");
    ZGMTRManualSetupPayloadParser *parser =
        [[ZGMTRManualSetupPayloadParser alloc] initWithDecimalStringRepresentation:decimalString];
    NSError *error = nil;
    ZGMTRSetupPayload *setupPayload = [parser populatePayload:&error];
    if (setupPayload == nil) {
        FlutterMatterLogNSError(@"onboarding.manual.parse", error);
        return createFlutterRequestResultWithCode(1, @{
            @"error": @"Invalid manual pairing code.",
        });
    }
    return createFlutterRequestResultWithCode(0, FlutterMatterSetupPayloadJSON(setupPayload));
}

static NSString *parseQrCode(NSString *params) {
    NSDictionary *jsonObject = FlutterMatterParseJSONObject(params);
    NSString *qrCode = FlutterMatterRequiredString(jsonObject, @"qrCode");
    ZGMTRQRCodeSetupPayloadParser *parser =
        [[ZGMTRQRCodeSetupPayloadParser alloc] initWithBase38Representation:qrCode];
    NSError *error = nil;
    ZGMTRSetupPayload *setupPayload = [parser populatePayload:&error];
    if (setupPayload == nil) {
        FlutterMatterLogNSError(@"onboarding.qr.parse", error);
        return createFlutterRequestResultWithCode(1, @{
            @"error": @"Invalid QR code.",
        });
    }
    return createFlutterRequestResultWithCode(0, FlutterMatterSetupPayloadJSON(setupPayload));
}

void onOnboardingCall(NSString *path, NSString *params, FlutterResult result) {
    FlutterMatterLog([NSString stringWithFormat:@"onOnboardingCall path: %@", path ?: @""]);
    FlutterMatterResultSender *sender = [[FlutterMatterResultSender alloc] initWithResult:result];
    dispatch_queue_t queue = [Global backgroundSerialQueue];
    if (queue == nil) {
        queue = dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_DEFAULT, 0);
    }

    dispatch_async(queue, ^{
        @try {
            NSString *resultData = nil;
            if ([path isEqualToString:@"/parseManualPairingCode"]) {
                resultData = parseManualPairingCode(params);
            } else if ([path isEqualToString:@"/parseQrCode"]) {
                resultData = parseQrCode(params);
            }

            if (resultData != nil) {
                [sender sendValue:resultData];
            } else {
                [sender sendUnknownPathForHost:OnboardingHost path:path ?: @""];
            }
        } @catch (NSException *exception) {
            FlutterMatterLogException(@"onOnboardingCall", exception);
            [sender sendError:FlutterMatterErrorForException(exception,
                                                             FlutterMatterOnOnboardingCallExceptionCode,
                                                             OnboardingHost,
                                                             path ?: @"")];
        }
    });
}
