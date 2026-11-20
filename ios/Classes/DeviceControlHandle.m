// 禁用某个警告（在文件顶部添加）
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wunguarded-availability-new"

#include <objc/objc.h>

#import "DeviceControlHandle.h"
#include <MacTypes.h>
#include <Foundation/Foundation.h>
#include <ZGMatter/ZGMatter.h>
#import "Constants.h"
#import "FlutterMatterPlugin.h"
#import "Global.h"
#import "Utiles.h"
#import "DefaultsUtils.h"
#import "FlutterControllerParams.h"
#import "DeviceAttestationDelegate.h"
#import "FlutterDeviceController.h"
#import "flutter_matter/flutter_matter-Swift.h"


static NSMutableDictionary *controls = nil;
static NSMutableDictionary *onNOCChainGenerationCompletes = nil;
static dispatch_queue_t connectDeviceQueue = nil;
static NSString *activeControlHandle = nil;
static BOOL controllerLifecycleEnabled = NO;
static BOOL controllerLifecyclePoisoned = NO;

static void FlutterMatterEnsureDeviceControlState(void) {
    static dispatch_once_t onceToken;
    dispatch_once(&onceToken, ^{
        controls = [[NSMutableDictionary alloc] init];
        onNOCChainGenerationCompletes = [[NSMutableDictionary alloc] init];
        connectDeviceQueue = dispatch_queue_create("connectDeviceQueue", DISPATCH_QUEUE_SERIAL);
    });
}

dispatch_queue_t FlutterMatterEnsureMatterQueue(void) {
    @synchronized ([Global class]) {
        dispatch_queue_t queue = [Global backgroundSerialQueue];
        if (queue == nil) {
            queue = dispatch_queue_create("Matter Thread queue", DISPATCH_QUEUE_SERIAL);
            [Global setBackgroundSerialQueue:queue];
        }
        return queue;
    }
}

static FlutterDeviceController *FlutterMatterControllerForHandle(NSString *handle) {
    if (handle.length == 0) {
        return nil;
    }
    FlutterMatterEnsureDeviceControlState();
    @synchronized (controls) {
        return controls[handle];
    }
}

static NSString *FlutterMatterActiveControllerHandle(void) {
    FlutterMatterEnsureDeviceControlState();
    @synchronized (controls) {
        return activeControlHandle;
    }
}

static BOOL FlutterMatterIsControllerLifecycleEnabled(void) {
    FlutterMatterEnsureDeviceControlState();
    @synchronized (controls) {
        return controllerLifecycleEnabled;
    }
}

static BOOL FlutterMatterIsControllerLifecyclePoisoned(void) {
    FlutterMatterEnsureDeviceControlState();
    @synchronized (controls) {
        return controllerLifecyclePoisoned;
    }
}

static void FlutterMatterPoisonControllerLifecycle(void) {
    FlutterMatterEnsureDeviceControlState();
    @synchronized (controls) {
        if (!controllerLifecyclePoisoned) {
            controllerLifecyclePoisoned = YES;
            FlutterMatterLog(@"Controller lifecycle is permanently poisoned until process restart");
        }
    }
}

void FlutterMatterSetControllerLifecycleEnabled(BOOL enabled) {
    FlutterMatterEnsureDeviceControlState();
    @synchronized (controls) {
        controllerLifecycleEnabled = enabled;
    }
}

static BOOL FlutterMatterStoreController(NSString *handle, FlutterDeviceController *controller) {
    FlutterMatterEnsureDeviceControlState();
    @synchronized (controls) {
        if (controllerLifecyclePoisoned || !controllerLifecycleEnabled || activeControlHandle.length > 0) {
            return NO;
        }
        controls[handle] = controller;
        activeControlHandle = [handle copy];
        return YES;
    }
}

static void FlutterMatterRemoveController(NSString *handle) {
    FlutterMatterEnsureDeviceControlState();
    @synchronized (controls) {
        [controls removeObjectForKey:handle];
        if ([activeControlHandle isEqualToString:handle]) {
            activeControlHandle = nil;
        }
    }
}

static BOOL FlutterMatterShutdownControllerSafely(ZGMTRDeviceController *controller,
                                                  NSString *context) {
    if (controller == nil) {
        FlutterMatterLog([NSString stringWithFormat:@"%@: controller is unavailable", context]);
        return NO;
    }

    @try {
        [controller shutdown];
        return YES;
    } @catch (NSException *exception) {
        FlutterMatterPoisonControllerLifecycle();
        FlutterMatterLogException(context, exception);
        return NO;
    }
}

void FlutterMatterShutdownActiveControllerAsync(void) {
    FlutterMatterEnsureDeviceControlState();
    FlutterMatterSetControllerLifecycleEnabled(NO);

    NSString *handle = nil;
    FlutterDeviceController *fdController = nil;
    @synchronized (controls) {
        handle = [activeControlHandle copy];
        if (handle.length > 0) {
            fdController = controls[handle];
            [controls removeObjectForKey:handle];
            activeControlHandle = nil;
        }
    }
    if (fdController == nil) {
        return;
    }

    dispatch_queue_t queue = FlutterMatterEnsureMatterQueue();

    dispatch_async(queue, ^{
        BOOL shutdownSucceeded = NO;
        @try {
            ZGMTRDeviceController *controller = [fdController controller];
            FlutterMatterLog(@"Shutting down the active Matter controller");
            shutdownSucceeded = FlutterMatterShutdownControllerSafely(controller,
                                                                      @"controller.detach.shutdown");
        } @catch (NSException *exception) {
            FlutterMatterPoisonControllerLifecycle();
            FlutterMatterLogException(@"controller.detach.prepareShutdown", exception);
        }

        if (shutdownSucceeded) {
            FlutterMatterLog(@"Active Matter controller shutdown completed");
        } else {
            FlutterMatterPoisonControllerLifecycle();
            FlutterMatterLog(@"Active Matter controller state was cleared; native shutdown was not confirmed");
        }
    });
}

static NSError *FlutterMatterOperationError(NSString *message) {
    return [NSError errorWithDomain:@"FlutterMatter"
                               code:1
                           userInfo:@{NSLocalizedDescriptionKey: message ?: @"Matter operation failed."}];
}

static BOOL FlutterMatterInvokeCallback(NSString *path, NSDictionary *payload) {
    if (!FlutterMatterIsControllerLifecycleEnabled()) {
        FlutterMatterLog(@"Dropped Matter callback while controller lifecycle is inactive");
        return NO;
    }

    id callbackHandle = payload[jsonKeyHandle];
    if ([callbackHandle isKindOfClass:[NSString class]] && ((NSString *)callbackHandle).length > 0) {
        NSString *activeHandle = FlutterMatterActiveControllerHandle();
        if (activeHandle.length == 0 || ![activeHandle isEqualToString:callbackHandle]) {
            FlutterMatterLog(@"Dropped Matter callback for an inactive controller");
            return NO;
        }
    }

    @try {
        NSString *arguments = toJSONStringFromObject(payload ?: @{});
        NSString *result = invokeMethodBlockGet([Global externalChannel], path, arguments);
        if (result == nil) {
            FlutterMatterLog([NSString stringWithFormat:@"callback %@ returned no result", path ?: @""]);
            return NO;
        }
        return YES;
    } @catch (NSException *exception) {
        FlutterMatterLogException(path ?: @"callback delivery", exception);
        return NO;
    }
}

/////////// Callbacks

@implementation PairingDelegateWarp

- (void)onStatusUpdate:(ZGMTRPairingStatus)status {
    NSString *path = createFlutterCallPath(deviceControllerHost, @"CompletionListener/onStatusUpdate");
    FlutterMatterInvokeCallback(path, @{@"status": @(status), jsonKeyHandle: _handle ?: @""});
}

- (void)onPairingComplete:(NSError * _Nullable)error {
    NSString *path = createFlutterCallPath(deviceControllerHost, @"CompletionListener/onPairingComplete");
    FlutterMatterInvokeCallback(path, @{
        @"errorCode": error == nil ? @(0) : @([error code]),
        jsonKeyHandle: _handle ?: @"",
    });

    // A CompletionListener-only delegate has no commissioning parameters. Do
    // not attempt to commission with nil state; the pairDevice path supplies
    // all three values.
    if (error == nil && _deviceController != nil && _deviceId != nil && _commissioningParameters != nil) {
        @try {
            NSError *commissionError = nil;
            BOOL started = [_deviceController commissionDevice:[_deviceId unsignedLongLongValue]
                                            commissioningParams:_commissioningParameters
                                                          error:&commissionError];
            if (!started && commissionError == nil) {
                commissionError = FlutterMatterOperationError(@"Commissioning could not be started.");
            }
            if (commissionError != nil) {
                [self onCommissioningComplete:commissionError];
            }
        } @catch (NSException *exception) {
            FlutterMatterLogException(@"PairingDelegateWarp.onPairingComplete.commission", exception);
            [self onCommissioningComplete:FlutterMatterOperationError(@"Commissioning failed.")];
        }
    }
}

 - (void)onCommissioningComplete:(NSError * _Nullable)error {
     NSString *path = createFlutterCallPath(deviceControllerHost, @"CompletionListener/onCommissioningComplete");
     FlutterMatterInvokeCallback(path, @{
         @"nodeId": _deviceId ?: @(0),
         @"errorCode": error == nil ? @(0) : @([error code]),
         jsonKeyHandle: _handle ?: @"",
     });
 }

- (void)onPairingDeleted:(NSError * _Nullable)error {
    NSString *path = createFlutterCallPath(deviceControllerHost, @"CompletionListener/onPairingDeleted");
    FlutterMatterInvokeCallback(path, @{
        @"errorCode": error == nil ? @(0) : @([error code]),
        jsonKeyHandle: _handle ?: @"",
    });
}

- (void)onCommissioningStatusUpdate:(NSNumber * _Nullable)nodeId commissioningStage:(NSString *)commissioningStage error:(NSError * _Nullable)error
{
    NSString *path = createFlutterCallPath(deviceControllerHost, @"CompletionListener/onCommissioningStatusUpdate");
    FlutterMatterInvokeCallback(path, @{
        @"errorCode": error == nil ? @(0) : @([error code]),
        jsonKeyHandle: _handle ?: @"",
        @"stage": commissioningStage ?: @"",
        @"nodeId": nodeId ?: @(0),
    });
}

- (instancetype)initWithHandle:(NSString *)handle commissioningParameters:(ZGMTRCommissioningParameters *)commissioningParameters deviceController:(ZGMTRDeviceController *)deviceController deviceId:(NSNumber *)deviceId {
    self = [super init];
    if (self) {
        _handle = handle;
        _deviceController = deviceController;
        _commissioningParameters = commissioningParameters;
        _deviceId = deviceId;
    }
    return self;
}


@end

@implementation KeypairWarp
- (NSData *)signMessageECDSA_DER:(NSData *)message {
    @try {
        NSString *signMessageECDSA = createFlutterCallPath(
            deviceControllerHost, @"KeypairDelegate/EcdsaSignMessage");
        NSString *flutterResult = invokeMethodBlockGet(
            [Global externalChannel], signMessageECDSA,
            toJSONStringFromObject(@{@"handle" : _handle ?: @"",
                                     @"message" : nsDataToIntegerArray(message)}));
        if (flutterResult == nil) {
            @throw [NSException exceptionWithName:@"FlutterMatterCallbackDeliveryException"
                                           reason:@"Keypair signing callback failed."
                                         userInfo:nil];
        }
        return FlutterMatterRequiredByteArray(FlutterMatterParseJSONObject(flutterResult),
                                              @"ecdsaSign");
    } @catch (NSException *exception) {
        FlutterMatterLogException(@"KeypairWarp.signMessageECDSA_DER", exception);
        return nil;
    }
}

- (SecKeyRef)publicKey {
    @try {
        NSString *getPublicKeyPath = createFlutterCallPath(
            deviceControllerHost, @"KeypairDelegate/GetPublicKey");
        NSString *flutterResult =
            invokeMethodBlockGet([Global externalChannel], getPublicKeyPath,
                                 toJSONStringFromObject(@{@"handle" : _handle ?: @""}));
        if (flutterResult == nil) {
            @throw [NSException exceptionWithName:@"FlutterMatterCallbackDeliveryException"
                                           reason:@"Keypair public-key callback failed."
                                         userInfo:nil];
        }
        NSData *publicKeyData = FlutterMatterRequiredByteArray(
            FlutterMatterParseJSONObject(flutterResult), @"publicKey");
        SecKeyRef key = nsDataToSecKey(publicKeyData);
        if (key == NULL) {
            FlutterMatterLog(@"KeypairWarp.publicKey returned an invalid key");
        }
        return key;
    } @catch (NSException *exception) {
        FlutterMatterLogException(@"KeypairWarp.publicKey", exception);
        return NULL;
    }
}

- (instancetype)initWithHandle:(NSString *)handle {
    self = [super init];
    if (self) {
        _handle = handle; // 存储 handle
    }
    return self;
}
@end

@implementation ZGMTRNOCChainIssuerWarp

- (void)onNOCChainGenerationNeeded:(ZGCSRInfo *)csrInfo
                   attestationInfo:(ZGAttestationInfo *)attestationInfo
      onNOCChainGenerationComplete:(ZGMTRNOCChainGenerationCompleteHandler)onNOCChainGenerationComplete {
    FlutterMatterEnsureDeviceControlState();
    NSString *uuid = [[NSUUID UUID] UUIDString];
    @try {
        NSString *requestPath = createFlutterCallPath(deviceControllerHost,
                                                       @"NOCChainIssuer/onNOCChainGenerationNeeded");
        NSDictionary *csrInfoJson = @{
            @"csr": nsDataToIntegerArray([csrInfo csr]),
            @"elementsSignature": nsDataToIntegerArray([csrInfo elementsSignature]),
            @"elements": nsDataToIntegerArray([csrInfo elements]),
            @"nonce": nsDataToIntegerArray([csrInfo nonce]),
        };
        NSDictionary *attestationInfoJson = @{
            @"challenge": nsDataToIntegerArray([attestationInfo challenge]),
            @"nonce": nsDataToIntegerArray([attestationInfo nonce]),
            @"elements": nsDataToIntegerArray([attestationInfo elements]),
            @"elementsSignature": nsDataToIntegerArray([attestationInfo elementsSignature]),
            @"dac": nsDataToIntegerArray([attestationInfo dac]),
            @"pai": nsDataToIntegerArray([attestationInfo pai]),
            @"firmwareInfo": nsDataToIntegerArray([attestationInfo firmwareInfo]),
            @"certificationDeclaration": nsDataToIntegerArray([attestationInfo certificationDeclaration]),
            @"vendorId": @(0),
            @"productId": @(0),
        };

        @synchronized (onNOCChainGenerationCompletes) {
            onNOCChainGenerationCompletes[uuid] = [onNOCChainGenerationComplete copy];
        }
        NSString *flutterResult = invokeMethodBlockGet(
            [Global externalChannel], requestPath,
            toJSONStringFromObject(@{
                jsonKeyHandle: _handle ?: @"",
                @"csrInfo": csrInfoJson,
                @"attestationInfo": attestationInfoJson,
                @"onNOCChainGenerationCompleteHandle": uuid,
            }));
        if (flutterResult == nil) {
            @throw [NSException exceptionWithName:@"FlutterMatterCallbackDeliveryException"
                                           reason:@"NOC chain generation callback failed."
                                         userInfo:nil];
        }
    } @catch (NSException *exception) {
        FlutterMatterLogException(@"ZGMTRNOCChainIssuerWarp.onNOCChainGenerationNeeded",
                                  exception);
        @synchronized (onNOCChainGenerationCompletes) {
            [onNOCChainGenerationCompletes removeObjectForKey:uuid];
        }
        NSError *error = FlutterMatterOperationError(@"NOC chain generation callback failed.");
        onNOCChainGenerationComplete([NSData data], [NSData data], [NSData data],
                                     [NSData data], nil, &error);
    }
}

- (instancetype)initWithHandle:(NSString *)handle {
    self = [super init];
    if (self) {
        _handle = handle; // 存储 handle
    }
    return self;
}

@end

static FlutterControllerParams * mapFlutterControllerParams(NSDictionary *jsonObject) {
    NSArray *rootCertificate = FlutterMatterOptionalArray(jsonObject, @"rootCertificate");
    NSArray *intermediateCertificate = FlutterMatterOptionalArray(jsonObject, @"intermediateCertificate");
    NSArray *operationalCertificate = FlutterMatterOptionalArray(jsonObject, @"operationalCertificate");
    NSArray *ipk = FlutterMatterOptionalArray(jsonObject, @"ipk");
    NSData *rootCertificateData = rootCertificate == nil ? nil : toByteArrayFromJSONArray(rootCertificate);
    NSData *intermediateCertificateData = intermediateCertificate == nil ? nil : toByteArrayFromJSONArray(intermediateCertificate);
    NSData *operationalCertificateData = operationalCertificate == nil ? nil : toByteArrayFromJSONArray(operationalCertificate);
    NSData *ipkData = ipk == nil ? nil : toByteArrayFromJSONArray(ipk);

    NSNumber *fabricId = FlutterMatterOptionalNumber(jsonObject, @"fabricId") ?: @(0);
    NSNumber *controllerVendorId = FlutterMatterOptionalNumber(jsonObject, @"controllerVendorId") ?: @(0);
    NSNumber *udpListenPort = FlutterMatterOptionalNumber(jsonObject, @"udpListenPort") ?: @(0);
    NSNumber *failsafeTimerSeconds = FlutterMatterOptionalNumber(jsonObject, @"failsafeTimerSeconds") ?: @(30);
    NSNumber *caseFailsafeTimerSeconds = FlutterMatterOptionalNumber(jsonObject, @"caseFailsafeTimerSeconds") ?: @(30);
    NSNumber *nodeId = FlutterMatterOptionalNumber(jsonObject, @"nodeId") ?: @(0);
    NSString *keypairDelegateHandle = FlutterMatterOptionalString(jsonObject, @"keypairDelegateHandle");
    NSNumber *attemptNetworkScanWiFi = FlutterMatterOptionalBoolean(jsonObject, @"attemptNetworkScanWiFi") ?: @(NO);
    NSNumber *attemptNetworkScanThread = FlutterMatterOptionalBoolean(jsonObject, @"attemptNetworkScanThread") ?: @(NO);
    NSNumber *skipCommissioningComplete = FlutterMatterOptionalBoolean(jsonObject, @"skipCommissioningComplete") ?: @(NO);
    NSString *countryCode = FlutterMatterOptionalString(jsonObject, @"countryCode") ?: @"";
    NSNumber *adminSubject = FlutterMatterOptionalNumber(jsonObject, @"adminSubject") ?: @(0);
    NSNumber *regulatoryLocationType = FlutterMatterOptionalNumber(jsonObject, @"regulatoryLocationType") ?: @(0);
    NSNumber *enableServerInteractions = FlutterMatterOptionalBoolean(jsonObject, @"enableServerInteractions") ?: @(NO);

    return [[FlutterControllerParams alloc] init:[fabricId integerValue]
                                        udpListenPort:[udpListenPort integerValue]
                                controllerVendorId:[controllerVendorId integerValue]
                             failsafeTimerSeconds:[failsafeTimerSeconds integerValue]
                         caseFailsafeTimerSeconds:[caseFailsafeTimerSeconds integerValue]
                            attemptNetworkScanWiFi:[attemptNetworkScanWiFi boolValue]
                          attemptNetworkScanThread:[attemptNetworkScanThread boolValue]
                           skipCommissioningComplete:[skipCommissioningComplete boolValue]
                                         countryCode:countryCode
                              regulatoryLocationType:[regulatoryLocationType integerValue]
                                     keypairDelegate:keypairDelegateHandle
                                     rootCertificate:rootCertificateData
                             intermediateCertificate:intermediateCertificateData
                               operationalCertificate:operationalCertificateData
                                               ipk:ipkData
                                      adminSubject:[adminSubject integerValue]
                           enableServerInteractions:[enableServerInteractions boolValue]
                                         setupURL:nil
                                            nodeId:[nodeId integerValue]];
}

static ZGMTRDeviceControllerStartupParams *
mapControllerParams(FlutterControllerParams *flutterControllerParams) {

    ZGMTRDeviceControllerStartupParams *params;
    // intermediateCertificate is optional: the framework accepts nil when the
    // operational certificate is directly signed by the root certificate.
    if ([flutterControllerParams ipk] != nil &&
        [flutterControllerParams rootCertificate] != nil &&
        [flutterControllerParams operationalCertificate] != nil &&
        [flutterControllerParams keypairDelegate] != nil) {
        KeypairWarp *kp =
            [[KeypairWarp alloc] initWithHandle:[flutterControllerParams keypairDelegate]];
        params = [[ZGMTRDeviceControllerStartupParams alloc]
                        initWithIPK:[flutterControllerParams ipk]
                 operationalKeypair:kp
             operationalCertificate:[flutterControllerParams operationalCertificate]
            intermediateCertificate:[flutterControllerParams intermediateCertificate]
                  rootCertificate:[flutterControllerParams rootCertificate]];
    } else if ([flutterControllerParams fabricId] != 0 &&
               [flutterControllerParams ipk] != nil &&
               [flutterControllerParams keypairDelegate] != nil) {
        KeypairWarp *kp =
            [[KeypairWarp alloc] initWithHandle:[flutterControllerParams keypairDelegate]];
        params = [[ZGMTRDeviceControllerStartupParams alloc]
            initWithIPK:[flutterControllerParams ipk]
               fabricID:@([flutterControllerParams fabricId])
              nocSigner:kp];
        if ([flutterControllerParams nodeId] != 0) {
            [params setNodeID:@([flutterControllerParams nodeId])];
        }
    } else {
        @throw [[FlutterMatterArgumentException alloc]
            initWithArgumentName:@"controllerParams"
                           message:@"ipk, rootCertificate, operationalCertificate, and "
                                   @"keypairDelegateHandle (or ipk, fabricId, and "
                                   @"keypairDelegateHandle) are required."];
    }
    if ([flutterControllerParams controllerVendorId]) {
        [params setVendorID:@([flutterControllerParams controllerVendorId])];
    }
    return params;
}

static ZGMTRDeviceController* getZGMTRDeviceController(NSString *handle) {
    FlutterDeviceController *c = FlutterMatterControllerForHandle(handle);
    if (c == nil) {
        return nil;
    }
    return [c controller];
}

static NSString *FlutterMatterPathComponentString(id component) {
    if ([component isKindOfClass:[NSNumber class]] || [component isKindOfClass:[NSString class]]) {
        return [component description];
    }
    return nil;
}

static NSMutableDictionary *FlutterMatterMutableDictionaryAtKey(NSMutableDictionary *parent,
                                                                 NSString *key) {
    if (key.length == 0) {
        return nil;
    }
    id existing = parent[key];
    if ([existing isKindOfClass:[NSMutableDictionary class]]) {
        return existing;
    }
    if (existing != nil && existing != [NSNull null]) {
        return nil;
    }
    NSMutableDictionary *created = [NSMutableDictionary dictionary];
    parent[key] = created;
    return created;
}

static NSNumber *FlutterMatterEventTimestampMilliseconds(NSDictionary *data) {
    id uptime = data[ZGMTREventSystemUpTimeKey];
    if ([uptime isKindOfClass:[NSNumber class]]) {
        return @([uptime doubleValue] * 1000.0);
    }
    id date = data[ZGMTREventTimestampDateKey];
    if ([date isKindOfClass:[NSDate class]]) {
        return @([date timeIntervalSince1970] * 1000.0);
    }
    return nil;
}

static id FlutterMatterTLVJSONValue(id value) {
    if ([value isKindOfClass:[NSData class]]) {
        return nsDataToIntegerArray((NSData *)value);
    }
    if (value == nil || value == [NSNull null]) {
        return [NSNull null];
    }
    return nil;
}

static NSError *FlutterMatterNodeStateConversionError(NSString *message) {
    return [NSError errorWithDomain:@"FlutterMatterNodeStateConversionError"
                               code:1
                           userInfo:@{NSLocalizedDescriptionKey: message ?: @"Report payload was invalid."}];
}

static BOOL FlutterMatterFailNodeStateConversion(NSError **conversionError,
                                                  NSString *message) {
    if (conversionError != NULL) {
        *conversionError = FlutterMatterNodeStateConversionError(message);
    }
    return NO;
}

static NSDictionary *FlutterMatterStatusJSONFromInteractionError(NSError *error,
                                                                  NSError **conversionError) {
    if (![error isKindOfClass:[NSError class]] ||
        ![error.domain isEqualToString:ZGMTRInteractionErrorDomain]) {
        FlutterMatterFailNodeStateConversion(conversionError,
                                              @"Report contained a non-interaction path error.");
        return nil;
    }

    id clusterStatus = error.userInfo[@"clusterStatus"];
    if (clusterStatus == [NSNull null]) {
        clusterStatus = nil;
    }
    if (clusterStatus != nil && ![clusterStatus isKindOfClass:[NSNumber class]]) {
        FlutterMatterFailNodeStateConversion(conversionError,
                                              @"Report path error contained an invalid clusterStatus.");
        return nil;
    }

    NSMutableDictionary *status = [@{@"status": @(error.code)} mutableCopy];
    if (clusterStatus != nil) {
        status[@"clusterStatus"] = clusterStatus;
    }
    return status;
}

static NSDictionary *FlutterMatterAttributePathJSON(NSNumber *endpoint,
                                                     NSNumber *cluster,
                                                     NSNumber *attribute) {
    if (![endpoint isKindOfClass:[NSNumber class]] ||
        ![cluster isKindOfClass:[NSNumber class]] ||
        ![attribute isKindOfClass:[NSNumber class]]) {
        return nil;
    }
    return @{
        @"endpointId": @{@"id": endpoint},
        @"clusterId": @{@"id": cluster},
        @"attributeId": @{@"id": attribute},
    };
}

static NSDictionary *FlutterMatterAttributePathJSONFromResponseValue(id value) {
    if (![value isKindOfClass:[ZGMTRAttributePath class]]) {
        return nil;
    }
    ZGMTRAttributePath *path = (ZGMTRAttributePath *)value;
    return FlutterMatterAttributePathJSON(path.endpoint, path.cluster, path.attribute);
}

/// Convert to Flutter NodeState class JSON.  Framework payloads are validated
/// here because malformed data must become a callback error, not an
/// Objective-C exception or a partial report with wrong endpoint/cluster keys.
/// Return nil and populate conversionError when any report entry is malformed.
static NSDictionary *convertNodeStateJsonFormat(NSArray<NSDictionary<NSString *, id> *> * _Nullable values,
                                                 NSError **conversionError) {
    if (conversionError != NULL) {
        *conversionError = nil;
    }
    if (![values isKindOfClass:[NSArray class]]) {
        FlutterMatterFailNodeStateConversion(conversionError,
                                              @"Report payload was not an array.");
        return nil;
    }

    NSMutableDictionary *nodeState = [NSMutableDictionary dictionary];

    for (id element in values) {
        if (![element isKindOfClass:[NSDictionary class]]) {
            FlutterMatterFailNodeStateConversion(conversionError,
                                                  @"Report contained a non-dictionary entry.");
            return nil;
        }
        NSDictionary *entry = (NSDictionary *)element;
        id attrPathValue = entry[ZGMTRAttributePathKey];
        id eventPathValue = entry[ZGMTREventPathKey];
        id errorValue = entry[ZGMTRErrorKey];
        id dataValue = entry[ZGMTRDataKey];

        if (errorValue != nil) {
            if (dataValue != nil || (attrPathValue == nil) == (eventPathValue == nil)) {
                FlutterMatterFailNodeStateConversion(conversionError,
                                                      @"Report path error was malformed.");
                return nil;
            }
            NSDictionary *status = FlutterMatterStatusJSONFromInteractionError(errorValue,
                                                                                conversionError);
            if (status == nil) {
                return nil;
            }

            if ([attrPathValue isKindOfClass:[ZGMTRAttributePath class]]) {
                ZGMTRAttributePath *attrPath = (ZGMTRAttributePath *)attrPathValue;
                NSString *endpointKey = FlutterMatterPathComponentString([attrPath endpoint]);
                NSString *clusterKey = FlutterMatterPathComponentString([attrPath cluster]);
                NSString *attributeKey = FlutterMatterPathComponentString([attrPath attribute]);
                if (endpointKey == nil || clusterKey == nil || attributeKey == nil) {
                    FlutterMatterFailNodeStateConversion(conversionError,
                                                          @"Attribute status contained an invalid path.");
                    return nil;
                }

                NSMutableDictionary *endpoints = FlutterMatterMutableDictionaryAtKey(nodeState, @"endpoints");
                NSMutableDictionary *endpointState = FlutterMatterMutableDictionaryAtKey(endpoints, endpointKey);
                NSMutableDictionary *clusters = FlutterMatterMutableDictionaryAtKey(endpointState, @"clusters");
                NSMutableDictionary *clusterState = FlutterMatterMutableDictionaryAtKey(clusters, clusterKey);
                NSMutableDictionary *attributes = FlutterMatterMutableDictionaryAtKey(clusterState, @"attributes");
                NSMutableDictionary *attributeStatuses = FlutterMatterMutableDictionaryAtKey(clusterState, @"attributeStatuses");
                if (attributes == nil || attributeStatuses == nil) {
                    FlutterMatterFailNodeStateConversion(conversionError,
                                                          @"Attribute status could not allocate state containers.");
                    return nil;
                }

                // Mirror connectedhomeip States.kt addAttributeStatus: a status
                // replaces any value for the same attribute path.
                [attributes removeObjectForKey:attributeKey];
                attributeStatuses[attributeKey] = status;
                continue;
            }

            if ([eventPathValue isKindOfClass:[ZGMTREventPath class]]) {
                ZGMTREventPath *eventPath = (ZGMTREventPath *)eventPathValue;
                NSString *endpointKey = FlutterMatterPathComponentString([eventPath endpoint]);
                NSString *clusterKey = FlutterMatterPathComponentString([eventPath cluster]);
                NSString *eventKey = FlutterMatterPathComponentString([eventPath event]);
                if (endpointKey == nil || clusterKey == nil || eventKey == nil) {
                    FlutterMatterFailNodeStateConversion(conversionError,
                                                          @"Event status contained an invalid path.");
                    return nil;
                }

                NSMutableDictionary *endpoints = FlutterMatterMutableDictionaryAtKey(nodeState, @"endpoints");
                NSMutableDictionary *endpointState = FlutterMatterMutableDictionaryAtKey(endpoints, endpointKey);
                NSMutableDictionary *clusters = FlutterMatterMutableDictionaryAtKey(endpointState, @"clusters");
                NSMutableDictionary *clusterState = FlutterMatterMutableDictionaryAtKey(clusters, clusterKey);
                NSMutableDictionary *events = FlutterMatterMutableDictionaryAtKey(clusterState, @"events");
                NSMutableDictionary *eventStatuses = FlutterMatterMutableDictionaryAtKey(clusterState, @"eventStatuses");
                if (events == nil || eventStatuses == nil) {
                    FlutterMatterFailNodeStateConversion(conversionError,
                                                          @"Event status could not allocate state containers.");
                    return nil;
                }

                // Mirror connectedhomeip States.kt addEventStatus: a status
                // replaces event values and appends to the status list.
                [events removeObjectForKey:eventKey];
                NSMutableArray *statusList = eventStatuses[eventKey];
                if (statusList == nil) {
                    statusList = [NSMutableArray array];
                    eventStatuses[eventKey] = statusList;
                } else if (![statusList isKindOfClass:[NSMutableArray class]]) {
                    FlutterMatterFailNodeStateConversion(conversionError,
                                                          @"Event status list was malformed.");
                    return nil;
                }
                [statusList addObject:status];
                continue;
            }

            FlutterMatterFailNodeStateConversion(conversionError,
                                                  @"Report path error contained an invalid path.");
            return nil;
        }

        if (![dataValue isKindOfClass:[NSDictionary class]] ||
            (attrPathValue == nil) == (eventPathValue == nil)) {
            FlutterMatterFailNodeStateConversion(conversionError,
                                                  @"Report entry contained invalid data.");
            return nil;
        }
        NSDictionary *data = (NSDictionary *)dataValue;

        if ([attrPathValue isKindOfClass:[ZGMTRAttributePath class]]) {
            ZGMTRAttributePath *attrPath = (ZGMTRAttributePath *)attrPathValue;
            NSString *endpointKey = FlutterMatterPathComponentString([attrPath endpoint]);
            NSString *clusterKey = FlutterMatterPathComponentString([attrPath cluster]);
            NSString *attributeKey = FlutterMatterPathComponentString([attrPath attribute]);
            if (endpointKey == nil || clusterKey == nil || attributeKey == nil) {
                FlutterMatterFailNodeStateConversion(conversionError,
                                                      @"Attribute report contained an invalid path.");
                return nil;
            }

            NSMutableDictionary *endpoints = FlutterMatterMutableDictionaryAtKey(nodeState, @"endpoints");
            NSMutableDictionary *endpointState = FlutterMatterMutableDictionaryAtKey(endpoints, endpointKey);
            NSMutableDictionary *clusters = FlutterMatterMutableDictionaryAtKey(endpointState, @"clusters");
            NSMutableDictionary *clusterState = FlutterMatterMutableDictionaryAtKey(clusters, clusterKey);
            NSMutableDictionary *attributes = FlutterMatterMutableDictionaryAtKey(clusterState, @"attributes");
            if (attributes == nil) {
                FlutterMatterFailNodeStateConversion(conversionError,
                                                      @"Attribute report could not allocate state containers.");
                return nil;
            }
            id tlv = FlutterMatterTLVJSONValue(data[ZGMTRTlvValueType]);
            if (tlv == nil) {
                FlutterMatterFailNodeStateConversion(conversionError,
                                                      @"Attribute report contained a non-byte TLV value.");
                return nil;
            }
            attributes[attributeKey] = @{@"tlv": tlv};
            continue;
        }

        if ([eventPathValue isKindOfClass:[ZGMTREventPath class]]) {
            ZGMTREventPath *eventPath = (ZGMTREventPath *)eventPathValue;
            NSString *endpointKey = FlutterMatterPathComponentString([eventPath endpoint]);
            NSString *clusterKey = FlutterMatterPathComponentString([eventPath cluster]);
            NSString *eventKey = FlutterMatterPathComponentString([eventPath event]);
            NSNumber *eventNumber = data[ZGMTREventNumberKey];
            NSNumber *priorityLevel = data[ZGMTREventPriorityKey];
            NSNumber *timestampType = data[ZGMTREventTimeTypeKey];
            NSNumber *timestampValue = FlutterMatterEventTimestampMilliseconds(data);
            id tlv = FlutterMatterTLVJSONValue(data[ZGMTRTlvValueType]);
            if (endpointKey == nil || clusterKey == nil || eventKey == nil ||
                ![eventNumber isKindOfClass:[NSNumber class]] ||
                ![priorityLevel isKindOfClass:[NSNumber class]] ||
                ![timestampType isKindOfClass:[NSNumber class]] ||
                timestampValue == nil || tlv == nil ||
                [data.allKeys containsObject:ZGMTRErrorKey]) {
                FlutterMatterFailNodeStateConversion(conversionError,
                                                      @"Event report was incomplete or contained an error.");
                return nil;
            }

            NSMutableDictionary *endpoints = FlutterMatterMutableDictionaryAtKey(nodeState, @"endpoints");
            NSMutableDictionary *endpointState = FlutterMatterMutableDictionaryAtKey(endpoints, endpointKey);
            NSMutableDictionary *clusters = FlutterMatterMutableDictionaryAtKey(endpointState, @"clusters");
            NSMutableDictionary *clusterState = FlutterMatterMutableDictionaryAtKey(clusters, clusterKey);
            NSMutableDictionary *events = FlutterMatterMutableDictionaryAtKey(clusterState, @"events");
            if (events == nil) {
                FlutterMatterFailNodeStateConversion(conversionError,
                                                      @"Event report could not allocate state containers.");
                return nil;
            }
            NSMutableArray *eventList = events[eventKey];
            if (![eventList isKindOfClass:[NSMutableArray class]]) {
                eventList = [NSMutableArray array];
                events[eventKey] = eventList;
            }
            [eventList addObject:@{
                @"eventNumber": eventNumber,
                @"priorityLevel": priorityLevel,
                @"timestampType": timestampType,
                @"timestampValue": timestampValue,
                @"tlv": tlv,
            }];
            continue;
        }

        FlutterMatterFailNodeStateConversion(conversionError,
                                              @"Report entry contained an invalid path.");
        return nil;
    }
    return nodeState;
}

////////////////////////////////////////////////////////////
// ██   ██   █████   ███    ██  ██████   ██       ███████
// ██   ██  ██   ██  ████   ██  ██   ██  ██       ██
// ███████  ███████  ██ ██  ██  ██   ██  ██       █████
// ██   ██  ██   ██  ██  ██ ██  ██   ██  ██       ██
// ██   ██  ██   ██  ██   ████  ██████   ███████  ███████
//
// ███    ███  ███████  ████████  ██   ██   ██████   ██████
// ████  ████  ██          ██     ██   ██  ██    ██  ██   ██
// ██ ████ ██  █████       ██     ███████  ██    ██  ██   ██
// ██  ██  ██  ██          ██     ██   ██  ██    ██  ██   ██
// ██      ██  ███████     ██     ██   ██   ██████   ██████
//
//  ██████   █████   ██       ██
// ██       ██   ██  ██       ██
// ██       ███████  ██       ██
// ██       ██   ██  ██       ██
//  ██████  ██   ██  ███████  ███████

static NSString *newDeviceControllerCall(NSString *params) {
    if (FlutterMatterIsControllerLifecyclePoisoned()) {
        return createFlutterRequestResultWithCode(1, @{
            @"error": @"Native controller lifecycle is poisoned; restart the process before creating another controller.",
        });
    }
    if (!FlutterMatterIsControllerLifecycleEnabled()) {
        return createFlutterRequestResultWithCode(1, @{
            @"error": @"Controller lifecycle is inactive.",
        });
    }
    if (FlutterMatterActiveControllerHandle().length > 0) {
        return createFlutterRequestResultWithCode(1, @{
            @"error": @"A Dart-visible controller is already active. Delete it before creating another.",
        });
    }
    if (!ZGMTRInitializeControllerFactory()) {
        return createFlutterRequestResultWithCode(1, @{
            @"error": @"Matter controller factory is unavailable.",
        });
    }

    NSDictionary *jsonObject = FlutterMatterParseJSONObject(params);
    FlutterControllerParams *fControlParams = mapFlutterControllerParams(jsonObject);
    ZGMTRDeviceControllerStartupParams *controllerParams =
        mapControllerParams(fControlParams);

    ZGMTRDeviceController *controller = nil;
    NSString *uuid = nil;
    BOOL stored = NO;
    @try {
        controller = [[ZGMTRControllerFactory sharedInstance]
            startControllerOnExistingFabric:controllerParams];
        if (controller == nil) {
            controller = [[ZGMTRControllerFactory sharedInstance]
                startControllerOnNewFabric:controllerParams];
        }
        if (controller == nil) {
            @throw [NSException exceptionWithName:@"FlutterMatterControllerCreationException"
                                           reason:@"Native controller could not be created."
                                         userInfo:nil];
        }

        uuid = [[controller uniqueIdentifier] UUIDString] ?: [[NSUUID UUID] UUIDString];
        NSString *response = createFlutterRequestResultWithCode(0, @{@"handle" : uuid});
        FlutterDeviceController *fdController =
            [[FlutterDeviceController alloc] initWithController:controller controllerParams:fControlParams];
        if (!FlutterMatterStoreController(uuid, fdController)) {
            FlutterMatterShutdownControllerSafely(controller, @"controller.new.storeRejectedShutdown");
            if (FlutterMatterIsControllerLifecyclePoisoned()) {
                return createFlutterRequestResultWithCode(1, @{
                    @"error": @"Native controller lifecycle is poisoned; restart the process before creating another controller.",
                });
            }
            return createFlutterRequestResultWithCode(1, @{
                @"error": @"Controller lifecycle changed before the controller could be registered.",
            });
        }
        stored = YES;
        return response;
    } @catch (NSException *exception) {
        if (stored && uuid.length > 0) {
            FlutterMatterRemoveController(uuid);
        }
        if (controller != nil) {
            FlutterMatterShutdownControllerSafely(controller, @"controller.new.cleanupAfterFailure");
        }
        @throw;
    }
}

static NSString *createRootCertificate(NSString *params) {
    NSDictionary *jsonObject = FlutterMatterParseJSONObject(params);
    NSString *keypairHandle = FlutterMatterRequiredString(jsonObject, @"keypairHandle");
    NSNumber *issuerId = FlutterMatterOptionalNumber(jsonObject, @"issuerId");
    NSNumber *fabricId = FlutterMatterOptionalNumber(jsonObject, @"fabricId");
    KeypairWarp *kp = [[KeypairWarp alloc] initWithHandle:keypairHandle];
    NSError *error = nil;
    NSData *rcac = [ZGMTRCertificates createRootCertificate:kp
                                                 issuerID:issuerId
                                                 fabricID:fabricId
                                                    error:&error];
    if (rcac == nil) {
        FlutterMatterLogNSError(@"controller.createRootCertificate", error);
        return createFlutterRequestResultWithCode(1, @{
            @"error": @"Unable to create root certificate.",
        });
    }
    return createFlutterRequestResultWithCode(0, @{@"data" : nsDataToIntegerArray(rcac)});
}

static NSString *setNocChainIssuer(NSString *params) {
    NSDictionary *jsonObject = FlutterMatterParseJSONObject(params);
    NSString *handle = FlutterMatterRequiredString(jsonObject, jsonKeyHandle);
    ZGMTRDeviceController *deviceController = getZGMTRDeviceController(handle);
    if (deviceController == nil) {
        @throw [[FlutterMatterArgumentException alloc] initWithArgumentName:jsonKeyHandle
                                                                     message:@"Controller handle was not found."];
    }
    ZGMTRNOCChainIssuerWarp *issuer = [[ZGMTRNOCChainIssuerWarp alloc] initWithHandle:handle];
    [deviceController setNocChainIssuer:issuer queue:dispatch_queue_create("nocChainIssuer", DISPATCH_QUEUE_SERIAL)];
    return createFlutterRequestResultWithCode(0, @{});
}

static NSString *onNOCChainGeneration(NSString *params) {
    NSDictionary *jsonObject = FlutterMatterParseJSONObject(params);
    NSString *handle = FlutterMatterRequiredString(jsonObject, jsonKeyHandle);
    ZGMTRDeviceController *deviceController = getZGMTRDeviceController(handle);
    if (deviceController == nil) {
        @throw [[FlutterMatterArgumentException alloc] initWithArgumentName:jsonKeyHandle
                                                                     message:@"Controller handle was not found."];
    }
    NSString *onNOCChainGenerationCompleteHandle = FlutterMatterRequiredString(jsonObject, @"onNOCChainGenerationCompleteHandle");
    ZGMTRNOCChainGenerationCompleteHandler completeHandler = nil;
    @synchronized (onNOCChainGenerationCompletes) {
        completeHandler = onNOCChainGenerationCompletes[onNOCChainGenerationCompleteHandle];
        [onNOCChainGenerationCompletes removeObjectForKey:onNOCChainGenerationCompleteHandle];
    }
    if (completeHandler == nil) {
        @throw [[FlutterMatterArgumentException alloc] initWithArgumentName:@"onNOCChainGenerationCompleteHandle"
                                                                     message:@"Completion handle was not found."];
    }
    FlutterControllerParams *controlParams = mapFlutterControllerParams(
        FlutterMatterRequiredDictionary(jsonObject, @"params"));
    NSData *rootCertificate = [controlParams rootCertificate];
    NSData *intermediateCertificate = [controlParams intermediateCertificate];
    NSData *operationalCertificate = [controlParams operationalCertificate];
    NSData *ipk = [controlParams ipk];
    NSNumber *adminSubject = @([controlParams adminSubject]);
    NSError *error = nil;
    completeHandler(operationalCertificate, intermediateCertificate, rootCertificate, ipk, adminSubject, &error);
    return createFlutterRequestResultWithCode(0, @{@"data": error == nil ? @(0) : @([error code])});
}

static NSString *setCompletionListener(NSString *params) {
    NSDictionary *jsonObject = FlutterMatterParseJSONObject(params);
    NSString *handle = FlutterMatterRequiredString(jsonObject, jsonKeyHandle);
    ZGMTRDeviceController *deviceController = getZGMTRDeviceController(handle);
    if (deviceController == nil) {
        @throw [[FlutterMatterArgumentException alloc] initWithArgumentName:jsonKeyHandle
                                                                     message:@"Controller handle was not found."];
    }
    [deviceController setPairingDelegate:[[PairingDelegateWarp alloc] initWithHandle:handle commissioningParameters:nil deviceController:deviceController deviceId:nil] queue:dispatch_queue_create("completionListener", DISPATCH_QUEUE_SERIAL)];
    return createFlutterRequestResultWithCode(0, @{});
}

static NSString *publicKeyFromCSR(NSString *params) {
    NSDictionary *jsonObject = FlutterMatterParseJSONObject(params);
    NSData *csr = FlutterMatterRequiredByteArray(jsonObject, @"csr");
    NSError *error = nil;
    NSData *publicKey = [ZGMTRCertificates publicKeyFromCSR:csr error:&error];
    if (publicKey == nil) {
        FlutterMatterLogNSError(@"controller.publicKeyFromCSR", error);
        @throw [[FlutterMatterArgumentException alloc] initWithArgumentName:@"csr"
                                                                     message:@"Invalid CSR."];
    }
    return createFlutterRequestResultWithCode(0, @{@"data": nsDataToIntegerArray(publicKey)});
}

static NSString *continueCommissioning(NSString *params) {
    NSDictionary *jsonObject = FlutterMatterParseJSONObject(params);
    NSString *handle = FlutterMatterRequiredString(jsonObject, jsonKeyHandle);
    ZGMTRDeviceController *deviceController = getZGMTRDeviceController(handle);
    if (deviceController == nil) {
        @throw [[FlutterMatterArgumentException alloc] initWithArgumentName:jsonKeyHandle
                                                                     message:@"Controller handle was not found."];
    }
    NSNumber *devicePtr = FlutterMatterRequiredNumber(jsonObject, @"devicePtr");
    NSNumber *ignoreAttestationFailureValue = FlutterMatterOptionalBoolean(jsonObject, @"ignoreAttestationFailure");
    NSError *error = nil;
    BOOL success = [deviceController continueCommissioningDevice:(void*)[devicePtr unsignedLongValue] ignoreAttestationFailure:ignoreAttestationFailureValue.boolValue error:&error];
    if (!success) {
        FlutterMatterLogNSError(@"controller.continueCommissioning", error);
        return createFlutterRequestResultWithCode(1, @{
            @"error": @"Unable to continue commissioning.",
        });
    }
    return createFlutterRequestResultWithCode(0, @{});
}

static NSString *createOperationalCertificate(NSString *params) {
    NSDictionary *jsonObject = FlutterMatterParseJSONObject(params);
    NSData *signingCertificate = FlutterMatterRequiredByteArray(jsonObject, @"signingCertificate");
    NSData *operationalPublicKey = FlutterMatterRequiredByteArray(jsonObject, @"operationalPublicKey");
    NSNumber *fabricId = FlutterMatterRequiredNumber(jsonObject, @"fabricId");
    NSNumber *nodeId = FlutterMatterRequiredNumber(jsonObject, @"nodeId");
    NSString *keypairHandle = FlutterMatterRequiredString(jsonObject, @"keypairHandle");
    id caseAuthenticatedTags = FlutterMatterOptionalArray(jsonObject, @"caseAuthenticatedTags");
    if (caseAuthenticatedTags != nil) {
        caseAuthenticatedTags = toByteArrayFromJSONArray(caseAuthenticatedTags);
    }
    KeypairWarp *kp =
        [[KeypairWarp alloc] initWithHandle:keypairHandle];
    NSError *error = nil;
    
    NSData *operationalCertificate = [ZGMTRCertificates createOperationalCertificate:kp signingCertificate:signingCertificate operationalPublicKey:nsDataToSecKey(operationalPublicKey) fabricID:fabricId nodeID:nodeId caseAuthenticatedTags:caseAuthenticatedTags error:&error];
    if (operationalCertificate == nil) {
        FlutterMatterLogNSError(@"controller.createOperationalCertificate", error);
        return createFlutterRequestResultWithCode(1, @{
            @"error": @"Unable to create operational certificate.",
        });
    }
    return createFlutterRequestResultWithCode(0, @{@"data": nsDataToIntegerArray(operationalCertificate)});
}

static NSString *pairDevice(NSString *params) {
    NSDictionary *jsonObject = FlutterMatterParseJSONObject(params);
    NSString *handle = FlutterMatterRequiredString(jsonObject, jsonKeyHandle);
    FlutterDeviceController *c = FlutterMatterControllerForHandle(handle);
    ZGMTRDeviceController *deviceController = c == nil ? nil : [c controller];
    FlutterControllerParams *fcp = c == nil ? nil : [c controllerParams];
    if (deviceController == nil || fcp == nil) {
        @throw [[FlutterMatterArgumentException alloc] initWithArgumentName:jsonKeyHandle
                                                                     message:@"Controller handle was not found."];
    }

    NSNumber *deviceId = FlutterMatterRequiredNumber(jsonObject, @"deviceId");
    NSString *displayName = FlutterMatterRequiredString(jsonObject, @"displayName");
    NSString *ecosystemName = FlutterMatterRequiredString(jsonObject, @"ecosystemName");
    NSString *onboardingPayload = FlutterMatterOptionalString(jsonObject, @"onboardingPayload");
    if (onboardingPayload.length == 0) {
        @throw [[FlutterMatterArgumentException alloc] initWithArgumentName:@"onboardingPayload"
                                                                     message:@"onboardingPayload is required on iOS."];
    }
    NSString *completionListenerHandle = FlutterMatterOptionalString(jsonObject, @"completionListener");
    (void)FlutterMatterOptionalArray(jsonObject, @"csrNonce");
    NSDictionary *networkCredentials = FlutterMatterOptionalDictionary(jsonObject, @"networkCredentials");
    NSString *attestationDelegate = FlutterMatterOptionalString(jsonObject, @"attestationDelegate");
    NSString *ssid = nil;
    NSString *pwd = nil;
    NSData *threadOperationalDataset = nil;
    if (networkCredentials != nil) {
        NSDictionary *wifiCredentials = FlutterMatterOptionalDictionary(networkCredentials, @"wifiCredentials");
        NSDictionary *threadCredentials = FlutterMatterOptionalDictionary(networkCredentials, @"threadCredentials");
        if (wifiCredentials != nil && threadCredentials != nil) {
            @throw [[FlutterMatterArgumentException alloc] initWithArgumentName:@"networkCredentials"
                                                                         message:@"wifiCredentials and threadCredentials are mutually exclusive."];
        }
        if (wifiCredentials != nil) {
            ssid = FlutterMatterRequiredString(wifiCredentials, @"ssid");
            pwd = FlutterMatterOptionalString(wifiCredentials, @"password") ?: @"";
            if (ssid.length == 0) {
                @throw [[FlutterMatterArgumentException alloc] initWithArgumentName:@"ssid"
                                                                             message:@"SSID must not be empty."];
            }
        } else if (threadCredentials != nil) {
            threadOperationalDataset = FlutterMatterRequiredByteArray(threadCredentials, @"operationalDataset");
        }
    }

    if ([NSThread isMainThread]) {
        @throw [NSException exceptionWithName:@"FlutterMatterThreadingException"
                                       reason:@"pairDevice cannot run on the main thread."
                                     userInfo:nil];
    }

    dispatch_semaphore_t semaphore = dispatch_semaphore_create(0);
    NSLock *completionLock = [[NSLock alloc] init];
    __block NSError *pairError = nil;
    __block BOOL completionHandled = NO;
    [MatterDevicePair startPairDeviceWithOnboardingPayload:onboardingPayload displayName:displayName ecosystemName:ecosystemName completion:^(NSString * _Nullable code, NSError * _Nullable err) {
        [completionLock lock];
        BOOL isDuplicateCompletion = completionHandled;
        if (!isDuplicateCompletion) {
            completionHandled = YES;
        }
        [completionLock unlock];
        if (isDuplicateCompletion) {
            FlutterMatterLog(@"MatterDevicePair completion invoked more than once");
            return;
        }
        @try {
            if (code != nil && code.length > 0) {
                NSError *error = nil;
                ZGMTRCommissioningParameters *commissioningParams =
                    [[ZGMTRCommissioningParameters alloc] init];
                commissioningParams.failSafeTimeout = @([fcp failsafeTimerSeconds]);
                commissioningParams.skipCommissioningComplete = [fcp skipCommissioningComplete];
                if (ssid != nil) {
                    commissioningParams.wifiSSID = [ssid dataUsingEncoding:NSUTF8StringEncoding];
                    // Matter allows empty Wi-Fi credentials for open networks.
                    commissioningParams.wifiCredentials = [pwd dataUsingEncoding:NSUTF8StringEncoding];
                } else if (threadOperationalDataset != nil) {
                    commissioningParams.threadOperationalDataset = threadOperationalDataset;
                }
                if (attestationDelegate.length > 0) {
                    [commissioningParams setDeviceAttestationDelegate:[[DeviceAttestationDelegate alloc] initWithHandle:handle]];
                }
                if (completionListenerHandle.length > 0) {
                    PairingDelegateWarp *pairingDelegate = [[PairingDelegateWarp alloc] initWithHandle:handle commissioningParameters:commissioningParams deviceController:deviceController deviceId:deviceId];
                    [deviceController setPairingDelegate:pairingDelegate
                                                   queue:[Global backgroundSerialQueue] ?: dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_DEFAULT, 0)];
                }
                BOOL started = [deviceController pairDevice:[deviceId unsignedLongLongValue]
                                           onboardingPayload:code
                                                       error:&error];
                if (!started || error != nil) {
                    pairError = error ?: FlutterMatterOperationError(@"Commissioning could not be started.");
                }
            } else {
                pairError = err ?: FlutterMatterOperationError(@"Pairing payload was not returned.");
            }
        } @catch (NSException *exception) {
            FlutterMatterLogException(@"pairDevice.completion", exception);
            pairError = FlutterMatterOperationError(@"Commissioning could not be started.");
        } @finally {
            dispatch_semaphore_signal(semaphore);
        }
    }];
    dispatch_semaphore_wait(semaphore, DISPATCH_TIME_FOREVER);
    if (pairError != nil) {
        FlutterMatterLogNSError(@"controller.pairDevice", pairError);
        return createFlutterRequestResultWithCode(1, @{
            @"error": FlutterMatterSafeNSErrorSummary(pairError),
        });
    }
    return createFlutterRequestResultWithCode(0, @{});
}

//static NSString *setDeviceAttestationDelegate(NSString *params) {
//    NSDictionary *jsonObject = parseJSONString(params);
//    NSString *handle = requestJsonValueNotNull(jsonObject, jsonKeyHandle);
//    ZGMTRDeviceController *deviceController = getZGMTRDeviceController(handle);
//    if ([deviceController isEqual:[NSNull null]] || deviceController == nil) {
//        @throw [NSException exceptionWithName:@"setDeviceAttestationDelegateException"
//                                       reason:@"Not found deviceController"
//                                     userInfo:nil];
//    }
//    [deviceController setDeviceAttestationDelegate:[[DeviceAttestationDelegate alloc] initWithHandle:handle] timeoutSecs:600];
//    return createFlutterRequestResultWithCode(0, @{});
//}

static NSString *stopDevicePairing(NSString *params) {
    NSDictionary *jsonObject = FlutterMatterParseJSONObject(params);
    NSString *handle = FlutterMatterRequiredString(jsonObject, jsonKeyHandle);
    ZGMTRDeviceController *deviceController = getZGMTRDeviceController(handle);
    if (deviceController == nil) {
        @throw [[FlutterMatterArgumentException alloc] initWithArgumentName:jsonKeyHandle
                                                                     message:@"Controller handle was not found."];
    }
    NSNumber *deviceId = FlutterMatterRequiredNumber(jsonObject, @"deviceId");
    NSError *error = nil;
    BOOL cancelled = [deviceController cancelCommissioningForNodeID:deviceId error:&error];
    if (!cancelled) {
        FlutterMatterLogNSError(@"controller.stopDevicePairing", error);
        return createFlutterRequestResultWithCode(1, @{
            @"error": @"Unable to stop device pairing.",
        });
    }
    return createFlutterRequestResultWithCode(0, @{});
}

static NSString *deleteDeviceController(NSString *params) {
    NSDictionary *jsonObject = FlutterMatterParseJSONObject(params);
    NSString *handle = FlutterMatterRequiredString(jsonObject, jsonKeyHandle);
    FlutterDeviceController *fdController = FlutterMatterControllerForHandle(handle);
    if (fdController == nil) {
        FlutterMatterLog(@"Delete requested for an unknown controller handle");
        return createFlutterRequestResultWithCode(1, @{
            @"error": @"Controller handle was not found.",
        });
    }

    ZGMTRDeviceController *control = [fdController controller];
    if (control == nil) {
        FlutterMatterPoisonControllerLifecycle();
        FlutterMatterRemoveController(handle);
        FlutterMatterLog(@"Controller state was stale and has been cleared");
        return createFlutterRequestResultWithCode(1, @{
            @"error": @"Native controller state was unavailable.",
        });
    }

    FlutterMatterLog(@"Shutting down the requested Matter controller");
    if (!FlutterMatterShutdownControllerSafely(control, @"controller.delete.shutdown")) {
        return createFlutterRequestResultWithCode(1, @{
            @"error": @"Unable to shut down the native controller.",
        });
    }

    FlutterMatterRemoveController(handle);
    FlutterMatterLog(@"Requested Matter controller shutdown completed");
    return createFlutterRequestResultWithCode(0, @{});
}

static NSString *connectedDevice(NSString *params) {
    NSDictionary *jsonObject = FlutterMatterParseJSONObject(params);
    NSString *handle = FlutterMatterRequiredString(jsonObject, jsonKeyHandle);
    ZGMTRDeviceController *deviceController = getZGMTRDeviceController(handle);
    if (deviceController == nil) {
        @throw [[FlutterMatterArgumentException alloc] initWithArgumentName:jsonKeyHandle
                                                                     message:@"Controller handle was not found."];
    }
    NSNumber *nodeId = FlutterMatterRequiredNumber(jsonObject, @"nodeId");
    NSString *callbackHandle = FlutterMatterRequiredString(jsonObject, @"callbackHandle");
    [deviceController getBaseDevice:[nodeId unsignedLongLongValue] queue:connectDeviceQueue completionHandler:^(ZGMTRBaseDevice * _Nullable device, NSError * _Nullable error) {
        if (device != nil) {
            FlutterDeviceController *fdc = FlutterMatterControllerForHandle(handle);
            if (fdc != nil) {
                ZGMTRBaseDevice *alreadyConnectDevice = [fdc deviceInfoForNodeID:[nodeId unsignedLongLongValue]];
                if (alreadyConnectDevice == nil) {
                    [fdc addConnectedDeviceWithNodeID:[nodeId unsignedLongLongValue] deviceInfo:device];
                }
                NSString * path = createFlutterCallPath(deviceControllerHost, @"ConnectedDeviceCallback/onDeviceConnected");
                FlutterMatterInvokeCallback(path, @{
                    jsonKeyHandle: handle,
                    @"callbackHandle": callbackHandle,
                    @"context": nodeId,
                });
                return;
            }
        }
        NSString * path = createFlutterCallPath(deviceControllerHost, @"ConnectedDeviceCallback/onConnectionFailure");
        FlutterMatterInvokeCallback(path, @{
            jsonKeyHandle: handle,
            @"callbackHandle": callbackHandle,
            @"context": nodeId,
            @"nodeId": nodeId,
            @"error": error == nil ? @"Connection failed." : FlutterMatterSafeNSErrorSummary(error),
        });
    }];
    
    return createFlutterRequestResultWithCode(0, @{});
}

static NSString *releaseConnectContext(NSString *params) {
    NSDictionary *jsonObject = FlutterMatterParseJSONObject(params);
    NSString *handle = FlutterMatterRequiredString(jsonObject, jsonKeyHandle);
    ZGMTRDeviceController *deviceController = getZGMTRDeviceController(handle);
    if (deviceController == nil) {
        @throw [[FlutterMatterArgumentException alloc] initWithArgumentName:jsonKeyHandle
                                                                     message:@"Controller handle was not found."];
    }
    NSNumber *connectContext = FlutterMatterOptionalNumber(jsonObject, @"connectContext");
    if (connectContext != nil) {
        FlutterDeviceController *fdc = FlutterMatterControllerForHandle(handle);
        [fdc removeDeviceWithNodeID:[connectContext unsignedLongLongValue]];
    }
    return createFlutterRequestResultWithCode(0, @{});
}

static ZGMTRBaseDevice * getBaseDevice(FlutterDeviceController * fcontrol, NSNumber * nodeId, NSNumber * connectContext) {
    if (fcontrol == nil || nodeId == nil || [fcontrol controller] == nil) {
        return nil;
    }
    if (connectContext == nil) {
        return [ZGMTRBaseDevice deviceWithNodeID:nodeId
                                      controller:[fcontrol controller]];
    }
    return [fcontrol deviceInfoForNodeID:[nodeId unsignedLongLongValue]];
}

static NSNumber *FlutterMatterRequiredPathID(NSDictionary *element, NSString *key) {
    NSDictionary *path = FlutterMatterRequiredDictionary(element, key);
    NSNumber *pathID = FlutterMatterRequiredNumber(path, @"id");
    if (pathID.longLongValue < 0) {
        @throw [[FlutterMatterArgumentException alloc] initWithArgumentName:key
                                                                     message:@"Path id must be non-negative."];
    }
    return pathID;
}

static NSString *invoke(NSString *params) {
    NSDictionary *jsonObject = FlutterMatterParseJSONObject(params);
    NSString *handle = FlutterMatterRequiredString(jsonObject, jsonKeyHandle);
    ZGMTRDeviceController *deviceController = getZGMTRDeviceController(handle);
    if (deviceController == nil) {
        @throw [[FlutterMatterArgumentException alloc] initWithArgumentName:jsonKeyHandle
                                                                     message:@"Controller handle was not found."];
    }
    NSString *callbackId = FlutterMatterRequiredString(jsonObject, @"callback");
    NSNumber *nodeId = FlutterMatterRequiredNumber(jsonObject, @"nodeId");
    
    (void)FlutterMatterOptionalNumber(jsonObject, @"timedRequestTimeoutMs");
    NSNumber *imTimeoutMs = FlutterMatterOptionalNumber(jsonObject, @"imTimeoutMs") ?: @(0);
    
    NSDictionary *invokeElementJsonObject = FlutterMatterRequiredDictionary(jsonObject, @"invokeElement");
    NSNumber *endpointId = FlutterMatterRequiredPathID(invokeElementJsonObject, @"endpointId");
    NSNumber *clusterId = FlutterMatterRequiredPathID(invokeElementJsonObject, @"clusterId");
    NSNumber *commandId = FlutterMatterRequiredPathID(invokeElementJsonObject, @"commandId");
    NSNumber *groupId = FlutterMatterOptionalNumber(invokeElementJsonObject, @"groupId") ?: @(0);
    NSData *tlv = FlutterMatterRequiredByteArray(invokeElementJsonObject, @"tlv");
    
    NSNumber *connectContext = FlutterMatterOptionalNumber(jsonObject, @"connectContext");
    
    FlutterDeviceController *fdc = FlutterMatterControllerForHandle(handle);
    ZGMTRBaseDevice *baseDevice = getBaseDevice(fdc, nodeId, connectContext);
    if (baseDevice == nil) {
        return createFlutterRequestResultWithCode(1, @{
            @"error": @"Connected device was not found.",
        });
    }
    [baseDevice invokeCommandWithEndpointID:endpointId clusterID:clusterId commandID:commandId commandFields:tlv timedInvokeTimeout:[imTimeoutMs isEqualToNumber:@(0)] ? nil : imTimeoutMs queue:connectDeviceQueue completion:^(NSArray<NSDictionary<NSString *,id> *> * _Nullable values, NSError * _Nullable error) {
        @try {
            if (error) {
                FlutterMatterInvokeCallback(createFlutterCallPath(deviceControllerHost, @"InvokeCallback/onError"), @{
                    jsonKeyHandle: handle,
                    @"invokeCallbackPoint": callbackId,
                    @"error": FlutterMatterSafeNSErrorSummary(error),
                });
            } else {
                NSNumber * resultEndPointId = endpointId;
                NSNumber * resultClusterId = clusterId;
                NSNumber * resultCommandId = commandId;
                if (values != nil && [values count] > 0) {
                    NSDictionary<NSString *,id> * dictionary = [values objectAtIndex:0];
                    id commandPath = [dictionary objectForKey:@"commandPath"];
                    if (![commandPath isEqual:[NSNull null]] && [commandPath isKindOfClass:[ZGMTRCommandPath class]]) {
                        ZGMTRCommandPath * cp = commandPath;
                        resultEndPointId = [cp endpoint] ?: resultEndPointId;
                        resultClusterId = [cp cluster] ?: resultClusterId;
                        resultCommandId = [cp command] ?: resultCommandId;
                    }
                }
                FlutterMatterInvokeCallback(createFlutterCallPath(deviceControllerHost, @"InvokeCallback/onResponse"), @{
                    jsonKeyHandle: handle,
                    @"invokeCallbackPoint": callbackId,
                    @"successCode": @(0),
                    @"invokeElement": @{
                        @"endpointId": @{
                            @"id": resultEndPointId
                        },
                        @"clusterId": @{
                            @"id": resultClusterId
                        },
                        @"commandId": @{
                            @"id": resultCommandId
                        },
                        @"groupId": groupId ?: @(0),
                    }
                });
            }
        } @catch (NSException *exception) {
            FlutterMatterLogException(@"InvokeCallback.completion", exception);
            FlutterMatterInvokeCallback(createFlutterCallPath(deviceControllerHost, @"InvokeCallback/onError"), @{
                jsonKeyHandle: handle,
                @"invokeCallbackPoint": callbackId,
                @"error": @"Invoke callback failed.",
            });
        }
        // The Dart callback contract requires onDone even after an error.
        FlutterMatterInvokeCallback(createFlutterCallPath(deviceControllerHost, @"InvokeCallback/onDone"), @{
            jsonKeyHandle: handle,
            @"invokeCallbackPoint": callbackId,
        });
    }];
    return createFlutterRequestResultWithCode(0, @{});
}

static NSNumber * mapFlutterPathId(id jsonValue, NSError **error) {
    if (![jsonValue isKindOfClass:[NSDictionary class]]) {
        if (error != NULL) {
            *error = [NSError errorWithDomain:@"FlutterMatter"
                                         code:1
                                     userInfo:@{NSLocalizedDescriptionKey: @"ChipPathId must be an object."}];
        }
        return nil;
    }

    NSDictionary *pathId = (NSDictionary *)jsonValue;
    id typeValue = pathId[@"type"];
    NSNumber *idValue = pathId[@"id"];

    if (typeValue == [NSNull null] ||
        (typeValue != nil && ![typeValue isKindOfClass:[NSString class]])) {
        if (error != NULL) {
            *error = [NSError errorWithDomain:@"FlutterMatter"
                                         code:1
                                     userInfo:@{NSLocalizedDescriptionKey: @"ChipPathId.type must be a string."}];
        }
        return nil;
    }

    NSString *type = (NSString *)typeValue;
    if ([type caseInsensitiveCompare:@"wildcard"] == NSOrderedSame) {
        // The Matter iOS API represents wildcards with nil, not -1.
        return nil;
    }

    if (type != nil && [type caseInsensitiveCompare:@"concrete"] != NSOrderedSame) {
        if (error != NULL) {
            *error = [NSError errorWithDomain:@"FlutterMatter"
                                         code:1
                                     userInfo:@{NSLocalizedDescriptionKey: @"ChipPathId.type must be 'concrete' or 'wildcard'."}];
        }
        return nil;
    }

    if (idValue == (id)[NSNull null] ||
        ![idValue isKindOfClass:[NSNumber class]] || idValue.longLongValue < 0) {
        if (error != NULL) {
            *error = [NSError errorWithDomain:@"FlutterMatter"
                                         code:1
                                     userInfo:@{NSLocalizedDescriptionKey: @"ChipPathId.id must be a non-negative number."}];
        }
        return nil;
    }

    return idValue;
}

static NSArray<ZGMTRAttributeRequestPath *> * mapFlutterAttributePaths(
    id jsonValue,
    NSError **error) {

    if (jsonValue == nil || jsonValue == [NSNull null]) {
        return nil;
    }

    if (![jsonValue isKindOfClass:[NSArray class]]) {
        if (error != NULL) {
            *error = [NSError errorWithDomain:@"FlutterMatter"
                                         code:1
                                     userInfo:@{NSLocalizedDescriptionKey: @"attributePaths must be an array"}];
        }
        return nil;
    }

    NSMutableArray<ZGMTRAttributeRequestPath *> *paths = [NSMutableArray array];
    for (id item in (NSArray *)jsonValue) {
        if (![item isKindOfClass:[NSDictionary class]]) {
            if (error != NULL) {
                *error = [NSError errorWithDomain:@"FlutterMatter"
                                             code:1
                                         userInfo:@{NSLocalizedDescriptionKey: @"Invalid ChipAttributePath"}];
            }
            return nil;
        }

        NSDictionary *attributePath = (NSDictionary *)item;
        NSError *pathError = nil;
        NSNumber *endpointId = mapFlutterPathId(attributePath[@"endpointId"], &pathError);
        NSNumber *clusterId = mapFlutterPathId(attributePath[@"clusterId"], &pathError);
        NSNumber *attributeId = mapFlutterPathId(attributePath[@"attributeId"], &pathError);
        if (pathError != nil) {
            if (error != NULL) {
                *error = pathError;
            }
            return nil;
        }

        [paths addObject:[ZGMTRAttributeRequestPath requestPathWithEndpointID:endpointId
                                                                       clusterID:clusterId
                                                                     attributeID:attributeId]];
    }

    return [paths copy];
}

static NSArray<ZGMTREventRequestPath *> * mapFlutterEventPaths(id jsonValue, NSError **error) {
    if (jsonValue == nil || jsonValue == [NSNull null]) {
        return nil;
    }
    if (![jsonValue isKindOfClass:[NSArray class]]) {
        if (error != NULL) {
            *error = [NSError errorWithDomain:@"FlutterMatter"
                                         code:1
                                     userInfo:@{NSLocalizedDescriptionKey: @"eventPaths must be an array."}];
        }
        return nil;
    }

    NSMutableArray<ZGMTREventRequestPath *> *paths = [NSMutableArray array];
    for (id item in (NSArray *)jsonValue) {
        if (![item isKindOfClass:[NSDictionary class]]) {
            if (error != NULL) {
                *error = [NSError errorWithDomain:@"FlutterMatter"
                                             code:1
                                         userInfo:@{NSLocalizedDescriptionKey: @"Each event path must be an object."}];
            }
            return nil;
        }

        NSDictionary *eventPath = (NSDictionary *)item;
        NSError *pathError = nil;
        NSNumber *endpointId = mapFlutterPathId(eventPath[@"endpointId"], &pathError);
        NSNumber *clusterId = mapFlutterPathId(eventPath[@"clusterId"], &pathError);
        NSNumber *eventId = mapFlutterPathId(eventPath[@"eventId"], &pathError);
        if (pathError != nil) {
            if (error != NULL) {
                *error = pathError;
            }
            return nil;
        }

        [paths addObject:[ZGMTREventRequestPath requestPathWithEndpointID:endpointId
                                                               clusterID:clusterId
                                                                 eventID:eventId]];
    }
    return [paths copy];
}

static NSString * subscribe(NSString * params) {
   NSDictionary *jsonObject = FlutterMatterParseJSONObject(params);
   NSString *handle = FlutterMatterRequiredString(jsonObject, jsonKeyHandle);
   ZGMTRDeviceController *deviceController = getZGMTRDeviceController(handle);
   if (deviceController == nil) {
       @throw [[FlutterMatterArgumentException alloc] initWithArgumentName:jsonKeyHandle
                                                                    message:@"Controller handle was not found."];
   }
   NSString *callbackId = FlutterMatterRequiredString(jsonObject, @"callbackHandle");
   NSNumber *nodeId = FlutterMatterRequiredNumber(jsonObject, @"nodeId");
   NSArray *attributePathsJson = FlutterMatterOptionalArray(jsonObject, @"attributePaths");
   NSArray *eventPathsJson = FlutterMatterOptionalArray(jsonObject, @"eventPaths");
   NSNumber *minInterval = FlutterMatterRequiredNumber(jsonObject, @"minInterval");
   NSNumber *maxInterval = FlutterMatterRequiredNumber(jsonObject, @"maxInterval");
   (void)FlutterMatterOptionalArray(jsonObject, @"dataVersionFilters");
   NSNumber *keepSubscriptions = FlutterMatterOptionalBoolean(jsonObject, @"keepSubscriptions") ?: @(NO);
   NSNumber *isFabricFiltered = FlutterMatterOptionalBoolean(jsonObject, @"isFabricFiltered") ?: @(NO);
   (void)FlutterMatterOptionalNumber(jsonObject, @"imTimeoutMs");
   NSNumber *connectContext = FlutterMatterOptionalNumber(jsonObject, @"connectContext");
   (void)FlutterMatterOptionalNumber(jsonObject, @"eventMin");
   if (minInterval.doubleValue < 0 || maxInterval.doubleValue < 0 || maxInterval.doubleValue < minInterval.doubleValue) {
       @throw [[FlutterMatterArgumentException alloc] initWithArgumentName:@"minInterval"
                                                                    message:@"Subscription intervals are invalid."];
   }
   FlutterDeviceController *fdc = FlutterMatterControllerForHandle(handle);
   ZGMTRBaseDevice *baseDevice = getBaseDevice(fdc, nodeId, connectContext);
   if (baseDevice == nil) {
       return createFlutterRequestResultWithCode(1, @{
           @"error": @"Connected device was not found.",
       });
   }
   ZGMTRSubscribeParams *subscribeParams = [[ZGMTRSubscribeParams alloc] initWithMinInterval:minInterval maxInterval:maxInterval];
   subscribeParams.replaceExistingSubscriptions = keepSubscriptions.boolValue;
   subscribeParams.filterByFabric = isFabricFiltered.boolValue;
   subscribeParams.resubscribeAutomatically = false;
   
   NSError *attributePathsError = nil;
   NSArray<ZGMTRAttributeRequestPath *> *attributePaths = mapFlutterAttributePaths(attributePathsJson, &attributePathsError);
   if (attributePathsError != nil) {
       @throw [[FlutterMatterArgumentException alloc] initWithArgumentName:@"attributePaths"
                                                                    message:@"attributePaths is invalid."];
   }
   NSError *eventPathsError = nil;
   NSArray<ZGMTREventRequestPath *> *eventPaths = mapFlutterEventPaths(eventPathsJson, &eventPathsError);
   if (eventPathsError != nil) {
       @throw [[FlutterMatterArgumentException alloc] initWithArgumentName:@"eventPaths"
                                                                    message:@"eventPaths is invalid."];
   }
   __block BOOL terminalCallbackSent = NO;
   [baseDevice customSubscribeToAttributePaths:attributePaths eventPaths:eventPaths params:subscribeParams queue:connectDeviceQueue reportHandler:^(NSArray<NSDictionary<NSString *,id> *> * _Nullable values, NSError * _Nullable error) {
       if (terminalCallbackSent) {
           return;
       }

       NSError *callbackError = error;
       NSDictionary *nodeState = nil;
       if (callbackError == nil) {
           NSError *conversionError = nil;
           nodeState = convertNodeStateJsonFormat(values, &conversionError);
           if (nodeState == nil) {
               callbackError = conversionError ?: FlutterMatterNodeStateConversionError(@"Report payload was invalid.");
           }
       }

       if (callbackError != nil) {
           // Subscription errors (including malformed reports) are terminal for
           // this callback registration. Send onError followed by exactly one
           // onDone so Dart releases the callback only after the final event.
           terminalCallbackSent = YES;
           FlutterMatterInvokeCallback(createFlutterCallPath(deviceControllerHost, @"SubscriptionCallback/onError"), @{
               jsonKeyHandle: handle,
               @"subscriptionCallbackPoint": callbackId,
               @"error": FlutterMatterSafeNSErrorSummary(callbackError),
           });
           FlutterMatterInvokeCallback(createFlutterCallPath(deviceControllerHost, @"SubscriptionCallback/onDone"), @{
               jsonKeyHandle: handle,
               @"subscriptionCallbackPoint": callbackId,
           });
           return;
       }

       // Normal reports keep the established subscription callback alive.
       FlutterMatterInvokeCallback(createFlutterCallPath(deviceControllerHost, @"SubscriptionCallback/onReport"), @{
           jsonKeyHandle: handle,
           @"subscriptionCallbackPoint": callbackId,
           @"nodeState": nodeState,
       });
   } subscriptionEstablished:^(NSNumber * _Nonnull subscriptionId) {
       if (terminalCallbackSent) {
           return;
       }
       FlutterMatterInvokeCallback(createFlutterCallPath(deviceControllerHost, @"SubscriptionCallback/onSubscriptionEstablished"), @{
           jsonKeyHandle: handle,
           @"subscriptionCallbackPoint": callbackId,
           @"subscriptionId": subscriptionId ?: @(0),
       });
   } resubscriptionScheduled:nil];
   return createFlutterRequestResultWithCode(0, @{});
    
}

static NSString * readRequest(NSString * params) {
    NSDictionary *jsonObject = FlutterMatterParseJSONObject(params);
    NSString *handle = FlutterMatterRequiredString(jsonObject, jsonKeyHandle);
    ZGMTRDeviceController *deviceController = getZGMTRDeviceController(handle);
    if (deviceController == nil) {
        @throw [[FlutterMatterArgumentException alloc] initWithArgumentName:jsonKeyHandle
                                                                     message:@"Controller handle was not found."];
    }
    NSString *callbackId = FlutterMatterRequiredString(jsonObject, @"callbackHandle");
    NSNumber *nodeId = FlutterMatterRequiredNumber(jsonObject, @"nodeId");
    NSArray *attributePathsJson = FlutterMatterOptionalArray(jsonObject, @"attributePaths");
    NSArray *eventPathsJson = FlutterMatterOptionalArray(jsonObject, @"eventPaths");
    (void)FlutterMatterOptionalArray(jsonObject, @"dataVersionFilters");
    NSNumber *isFabricFiltered = FlutterMatterOptionalBoolean(jsonObject, @"isFabricFiltered") ?: @(NO);
    (void)FlutterMatterOptionalNumber(jsonObject, @"imTimeoutMs");
    NSNumber *connectContext = FlutterMatterOptionalNumber(jsonObject, @"connectContext");
    NSNumber *eventMin = FlutterMatterOptionalNumber(jsonObject, @"eventMin");
    
    FlutterDeviceController *fdc = FlutterMatterControllerForHandle(handle);
    ZGMTRBaseDevice* baseDevice = getBaseDevice(fdc, nodeId, connectContext);
    if (baseDevice == nil) {
        return createFlutterRequestResultWithCode(1, @{
            @"error": @"Connected device was not found.",
        });
    }
    
    NSError *attributePathsError = nil;
    NSArray<ZGMTRAttributeRequestPath *> *attributePaths = mapFlutterAttributePaths(attributePathsJson, &attributePathsError);
    if (attributePathsError != nil) {
        @throw [[FlutterMatterArgumentException alloc] initWithArgumentName:@"attributePaths"
                                                                     message:@"attributePaths is invalid."];
    }
    NSError *eventPathsError = nil;
    NSArray<ZGMTREventRequestPath *> *eventPaths = mapFlutterEventPaths(eventPathsJson, &eventPathsError);
    if (eventPathsError != nil) {
        @throw [[FlutterMatterArgumentException alloc] initWithArgumentName:@"eventPaths"
                                                                     message:@"eventPaths is invalid."];
    }
    
    ZGMTRReadParams *readParams = [ZGMTRReadParams alloc];
    readParams.fabricFiltered = isFabricFiltered;
    readParams.minEventNumber = eventMin;
    [baseDevice readAttributePaths:attributePaths eventPaths:eventPaths params:readParams queue:connectDeviceQueue completion:^(NSArray<NSDictionary<NSString *,id> *> * _Nullable values, NSError * _Nullable error) {
        NSError *callbackError = error;
        NSDictionary *nodeState = nil;
        if (callbackError == nil) {
            NSError *conversionError = nil;
            nodeState = convertNodeStateJsonFormat(values, &conversionError);
            if (nodeState == nil) {
                callbackError = conversionError ?: FlutterMatterNodeStateConversionError(@"Report payload was invalid.");
            }
        }

        if (callbackError != nil) {
            FlutterMatterInvokeCallback(createFlutterCallPath(deviceControllerHost, @"ReportCallback/onError"), @{
                jsonKeyHandle: handle,
                @"reportCallbackPoint": callbackId,
                @"error": FlutterMatterSafeNSErrorSummary(callbackError),
            });
        } else {
            FlutterMatterInvokeCallback(createFlutterCallPath(deviceControllerHost, @"ReportCallback/onReport"), @{
                jsonKeyHandle: handle,
                @"reportCallbackPoint": callbackId,
                @"nodeState": nodeState,
            });
        }
        FlutterMatterInvokeCallback(createFlutterCallPath(deviceControllerHost, @"ReportCallback/onDone"), @{
            jsonKeyHandle: handle,
            @"reportCallbackPoint": callbackId,
        });
    }];
    
    return createFlutterRequestResultWithCode(0, @{});
}

static NSString * writeRequest(NSString * params) {
   NSDictionary *jsonObject = FlutterMatterParseJSONObject(params);
   NSString *handle = FlutterMatterRequiredString(jsonObject, jsonKeyHandle);
   ZGMTRDeviceController *deviceController = getZGMTRDeviceController(handle);
   if (deviceController == nil) {
       @throw [[FlutterMatterArgumentException alloc] initWithArgumentName:jsonKeyHandle
                                                                    message:@"Controller handle was not found."];
   }
   NSString *callbackId = FlutterMatterRequiredString(jsonObject, @"callbackHandle");
   
   NSArray *attributeListJson = FlutterMatterRequiredArray(jsonObject, @"attributeList");
   NSNumber *nodeId = FlutterMatterRequiredNumber(jsonObject, @"nodeId");
   NSNumber *imTimeoutMs = FlutterMatterOptionalNumber(jsonObject, @"imTimeoutMs") ?: @(0);
   NSNumber *connectContext = FlutterMatterOptionalNumber(jsonObject, @"connectContext");
   NSNumber *timedRequestTimeoutMs = FlutterMatterOptionalNumber(jsonObject, @"timedRequestTimeoutMs") ?: @(0);
   
   NSMutableArray *attributePaths = [NSMutableArray arrayWithCapacity:attributeListJson.count];
   for (id item in attributeListJson) {
       if (![item isKindOfClass:[NSDictionary class]]) {
           @throw [[FlutterMatterArgumentException alloc] initWithArgumentName:@"attributeList"
                                                                        message:@"Each attributeList entry must be an object."];
       }
       NSDictionary *element = (NSDictionary *)item;
       NSNumber *endpointId = FlutterMatterRequiredPathID(element, @"endpointId");
       NSNumber *clusterId = FlutterMatterRequiredPathID(element, @"clusterId");
       NSNumber *attributeId = FlutterMatterRequiredPathID(element, @"attributeId");
       NSData *tlv = FlutterMatterRequiredByteArray(element, @"tlv");
       
       [attributePaths addObject: [[ZGMTRAttributeWriteRequest alloc] initWithEndpointID:endpointId clusterID:clusterId attributeID:attributeId tlv:tlv]];
   }
   
   FlutterDeviceController *fdc = FlutterMatterControllerForHandle(handle);
   ZGMTRBaseDevice *baseDevice = getBaseDevice(fdc, nodeId, connectContext);
   if (baseDevice == nil) {
       return createFlutterRequestResultWithCode(1, @{
           @"error": @"Connected device was not found.",
       });
   }
   
   [baseDevice writeAttributeRequests:attributePaths timedWriteTimeout:timedRequestTimeoutMs imTimeoutMs:imTimeoutMs queue:connectDeviceQueue completion:^(NSArray<NSDictionary<NSString *,id> *> * _Nullable values, NSError * _Nullable error) {
       NSArray *responseValues = [values isKindOfClass:[NSArray class]] ? values : nil;
       NSDictionary *errorPath = nil;
       if (error != nil && responseValues.count == 1 &&
           [responseValues[0] isKindOfClass:[NSDictionary class]]) {
           errorPath = FlutterMatterAttributePathJSONFromResponseValue(
               ((NSDictionary *)responseValues[0])[ZGMTRAttributePathKey]);
       }

       if (error != nil) {
           NSMutableDictionary *payload = [@{
               jsonKeyHandle: handle,
               @"writeAttributesCallbackPoint": callbackId,
               @"error": FlutterMatterSafeNSErrorSummary(error),
           } mutableCopy];
           if (errorPath != nil) {
               payload[@"attributePath"] = errorPath;
           }
           FlutterMatterInvokeCallback(createFlutterCallPath(deviceControllerHost, @"WriteAttributesCallback/onError"), payload);
       } else if (responseValues.count == 0) {
           FlutterMatterInvokeCallback(createFlutterCallPath(deviceControllerHost, @"WriteAttributesCallback/onError"), @{
               jsonKeyHandle: handle,
               @"writeAttributesCallbackPoint": callbackId,
               @"error": @"Write completed without an attribute response.",
           });
       } else {
           for (id responseValue in responseValues) {
               if (![responseValue isKindOfClass:[NSDictionary class]]) {
                   FlutterMatterInvokeCallback(createFlutterCallPath(deviceControllerHost, @"WriteAttributesCallback/onError"), @{
                       jsonKeyHandle: handle,
                       @"writeAttributesCallbackPoint": callbackId,
                       @"error": @"Write response contained a malformed entry.",
                   });
                   continue;
               }

               NSDictionary *response = (NSDictionary *)responseValue;
               NSDictionary *attributePath = FlutterMatterAttributePathJSONFromResponseValue(
                   response[ZGMTRAttributePathKey]);
               if (attributePath == nil) {
                   FlutterMatterInvokeCallback(createFlutterCallPath(deviceControllerHost, @"WriteAttributesCallback/onError"), @{
                       jsonKeyHandle: handle,
                       @"writeAttributesCallbackPoint": callbackId,
                       @"error": @"Write response did not contain a valid attribute path.",
                   });
                   continue;
               }

               id responseError = response[ZGMTRErrorKey];
               if (responseError == nil) {
                   FlutterMatterInvokeCallback(createFlutterCallPath(deviceControllerHost, @"WriteAttributesCallback/onResponse"), @{
                       jsonKeyHandle: handle,
                       @"writeAttributesCallbackPoint": callbackId,
                       @"attributePath": attributePath,
                       @"status": @{@"status": @(0)},
                   });
                   continue;
               }

               if ([responseError isKindOfClass:[NSError class]]) {
                   NSError *pathError = (NSError *)responseError;
                   NSError *conversionError = nil;
                   NSDictionary *status = FlutterMatterStatusJSONFromInteractionError(pathError,
                                                                                     &conversionError);
                   if (status != nil) {
                       FlutterMatterInvokeCallback(createFlutterCallPath(deviceControllerHost, @"WriteAttributesCallback/onResponse"), @{
                           jsonKeyHandle: handle,
                           @"writeAttributesCallbackPoint": callbackId,
                           @"attributePath": attributePath,
                           @"status": status,
                       });
                       continue;
                   }
               }

               NSString *summary = [responseError isKindOfClass:[NSError class]]
                   ? FlutterMatterSafeNSErrorSummary(responseError)
                   : @"Write path failed.";
               FlutterMatterInvokeCallback(createFlutterCallPath(deviceControllerHost, @"WriteAttributesCallback/onError"), @{
                   jsonKeyHandle: handle,
                   @"writeAttributesCallbackPoint": callbackId,
                   @"error": summary,
                   @"attributePath": attributePath,
               });
           }
       }
       FlutterMatterInvokeCallback(createFlutterCallPath(deviceControllerHost, @"WriteAttributesCallback/onDone"), @{
           jsonKeyHandle: handle,
           @"writeAttributesCallbackPoint": callbackId,
       });
   }];
   
   return createFlutterRequestResultWithCode(0, @{});
}

static NSString * openPairingWindowWithPIN(NSString * params) {
    NSDictionary *jsonObject = FlutterMatterParseJSONObject(params);
    NSString *handle = FlutterMatterRequiredString(jsonObject, jsonKeyHandle);
    NSString *callbackId = FlutterMatterRequiredString(jsonObject, @"callbackHandle");
    NSNumber *duration = FlutterMatterRequiredNumber(jsonObject, @"duration");
    NSNumber *discriminator = FlutterMatterRequiredNumber(jsonObject, @"discriminator");
    NSNumber *setupPIN = FlutterMatterRequiredNumber(jsonObject, @"setupPIN");
    NSNumber *connectContext = FlutterMatterRequiredNumber(jsonObject, @"connectContext");
    
    FlutterDeviceController *fdc = FlutterMatterControllerForHandle(handle);
    ZGMTRBaseDevice *baseDevice = [fdc deviceInfoForNodeID:[connectContext unsignedLongLongValue]];
    if (baseDevice == nil) {
        return createFlutterRequestResultWithCode(1, @{
            @"msg": @"Connected device was not found.",
        });
    }
    [baseDevice openCommissioningWindowWithSetupPasscode:setupPIN discriminator:discriminator duration:duration queue:connectDeviceQueue completion:^(ZGMTRSetupPayload * _Nullable payload, NSError * _Nullable error) {
        @try {
            if (error || payload == nil) {
                FlutterMatterInvokeCallback(createFlutterCallPath(deviceControllerHost, @"OpenCommissioningCallback/onError"), @{
                    jsonKeyHandle: handle,
                    @"callbackHandle": callbackId,
                    @"status": error == nil ? @(1) : @([error code]),
                    @"connectContext": connectContext,
                });
            } else {
                NSString *manualPairingCode = [payload manualEntryCode] ?: @"";
                NSString *qrCode = [payload qrCodeString] ?: @"";
                if (manualPairingCode.length == 0 || qrCode.length == 0) {
                    FlutterMatterInvokeCallback(createFlutterCallPath(deviceControllerHost, @"OpenCommissioningCallback/onError"), @{
                        jsonKeyHandle: handle,
                        @"callbackHandle": callbackId,
                        @"status": @(1),
                        @"connectContext": connectContext,
                    });
                    return;
                }
                FlutterMatterInvokeCallback(createFlutterCallPath(deviceControllerHost, @"OpenCommissioningCallback/onSuccess"), @{
                    jsonKeyHandle: handle,
                    @"callbackHandle": callbackId,
                    @"connectContext": connectContext,
                    @"manualPairingCode": manualPairingCode,
                    @"qrCode": qrCode,
                });
            }
        } @catch (NSException *exception) {
            FlutterMatterLogException(@"OpenCommissioningCallback.completion", exception);
            FlutterMatterInvokeCallback(createFlutterCallPath(deviceControllerHost, @"OpenCommissioningCallback/onError"), @{
                jsonKeyHandle: handle,
                @"callbackHandle": callbackId,
                @"status": @(1),
                @"connectContext": connectContext,
            });
        }
    }];
    
    return createFlutterRequestResultWithCode(0, @{@"data": @(YES)});
}

static NSString * getFabricIndex(NSString * params) {
  NSDictionary *jsonObject = FlutterMatterParseJSONObject(params);
  NSString *handle = FlutterMatterRequiredString(jsonObject, jsonKeyHandle);
  ZGMTRDeviceController *deviceController = getZGMTRDeviceController(handle);
  if (deviceController == nil) {
      @throw [[FlutterMatterArgumentException alloc] initWithArgumentName:jsonKeyHandle
                                                                   message:@"Controller handle was not found."];
  }
  return createFlutterRequestResultWithCode(0, @{@"data": [NSNumber numberWithLongLong:[deviceController getFabricIndex]]});
}

static NSString * unSubscribe(NSString * params) {
   NSDictionary *jsonObject = FlutterMatterParseJSONObject(params);
   NSString *handle = FlutterMatterRequiredString(jsonObject, jsonKeyHandle);
   ZGMTRDeviceController *deviceController = getZGMTRDeviceController(handle);
   if (deviceController == nil) {
       @throw [[FlutterMatterArgumentException alloc] initWithArgumentName:jsonKeyHandle
                                                                    message:@"Controller handle was not found."];
   }
   NSNumber *nodeId = FlutterMatterRequiredNumber(jsonObject, @"nodeId");
   (void)FlutterMatterOptionalNumber(jsonObject, @"fabricIndex");
   NSNumber *subscriptionId = FlutterMatterRequiredNumber(jsonObject, @"subscriptionId");
   ZGMTRBaseDevice *device = [ZGMTRBaseDevice deviceWithNodeID:nodeId controller:deviceController];
   if (device == nil) {
       return createFlutterRequestResultWithCode(1, @{
           @"data": @(NO),
           @"error": @"Connected device was not found.",
       });
   }
   BOOL success = [device shutdownSubscription:subscriptionId scopedNodeId:nodeId];
   NSMutableDictionary *result = [@{@"data": @(success)} mutableCopy];
   if (!success) {
       result[@"error"] = @"Subscription could not be removed.";
   }
   return createFlutterRequestResultWithCode(success ? 0 : 1, result);
}

void onDeviceControlCall(NSString *path, NSString *params,
                         FlutterResult result) {
    FlutterMatterLog([NSString stringWithFormat:@"onDeviceControlCall path: %@", path ?: @""]);
    FlutterMatterEnsureDeviceControlState();
    FlutterMatterResultSender *sender = [[FlutterMatterResultSender alloc] initWithResult:result];
    dispatch_queue_t queue = FlutterMatterEnsureMatterQueue();
    dispatch_async(queue, ^{
          if (!FlutterMatterIsControllerLifecycleEnabled()) {
              [sender sendValue:createFlutterRequestResultWithCode(1, @{
                  @"error": @"Controller lifecycle is inactive.",
              })];
              return;
          }

          NSString *resultData = nil;
          @try {
              if ([path isEqualToString:@"/new"]) {
                  resultData = newDeviceControllerCall(params);
              } else if ([path isEqualToString:@"/createRootCertificate"]) {
                  resultData = createRootCertificate(params);
              } else if ([path isEqualToString:@"/setNocChainIssuer"]) {
                  resultData = setNocChainIssuer(params);
              } else if ([path isEqualToString:@"/setCompletionListener"]) {
                  resultData = setCompletionListener(params);
              } else if ([path isEqualToString:@"/publicKeyFromCSR"]) {
                  resultData = publicKeyFromCSR(params);
              } else if ([path isEqualToString:@"/onNOCChainGeneration"]) {
                  resultData = onNOCChainGeneration(params);
              } else if ([path isEqualToString:@"/continueCommissioning"]) {
                  resultData = continueCommissioning(params);
              } else if ([path isEqualToString:@"/pairDevice"]) {
                  resultData = pairDevice(params);
              } else if ([path isEqualToString:@"/createOperationalCertificate"]) {
                  resultData = createOperationalCertificate(params);
              } else if ([path isEqualToString:@"/setDeviceAttestationDelegate"]) {
//                  resultData = setDeviceAttestationDelegate(params);
              } else if ([path isEqualToString:@"/stopDevicePairing"]) {
                  resultData = stopDevicePairing(params);
              } else if ([path isEqualToString:@"/deleteDeviceController"]) {
                  resultData = deleteDeviceController(params);
              } else if ([path isEqualToString:@"/invoke"]) {
                  resultData = invoke(params);
              } else if ([path isEqualToString:@"/subscribe"]) {
                  resultData = subscribe(params);
              } else if ([path isEqualToString:@"/read"]) {
                  resultData = readRequest(params);
              } else if ([path isEqualToString:@"/write"]) {
                  resultData = writeRequest(params);
              } else if ([path isEqualToString:@"/connectedDevice"]) {
                  resultData = connectedDevice(params);
              } else if ([path isEqualToString:@"/releaseConnectContext"]) {
                  resultData = releaseConnectContext(params);
              } else if ([path isEqualToString:@"/openPairingWindowWithPIN"]) {
                  resultData = openPairingWindowWithPIN(params);
              }  else if ([path isEqualToString:@"/getFabricIndex"]) {
                  resultData = getFabricIndex(params);
              } else if ([path isEqualToString:@"/unSubscribe"]) {
                  resultData = unSubscribe(params);
              }
          } @catch (NSException *exception) {
              FlutterMatterLogException(@"onDeviceControlCall", exception);
              [sender sendError:FlutterMatterErrorForException(exception,
                                                                FlutterMatterDeviceControlCallExceptionCode,
                                                                deviceControllerHost,
                                                                path ?: @"")];
              return;
          }

          if (resultData != nil) {
              [sender sendValue:resultData];
          } else {
              [sender sendUnknownPathForHost:deviceControllerHost path:path ?: @""];
          }
    });
}

#pragma clang diagnostic pop
