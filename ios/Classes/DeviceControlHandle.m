// 禁用某个警告（在文件顶部添加）
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wunguarded-availability-new"

#include <objc/objc.h>

#import "DeviceControlHandle.h"
#include <MacTypes.h>
#include <Foundation/Foundation.h>
#include <Matter/Matter.h>
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

/////////// Callbacks

@implementation PairingDelegateWarp

- (void)onStatusUpdate:(MTRPairingStatus)status {
    @try {
        NSString *p = createFlutterCallPath(deviceControllerHost, @"CompletionListener/onStatusUpdate");
        NSString *callResult = invokeMethodBlockGet([Global externalChannel], p, toJSONStringFromObject(@{@"status": @(status), jsonKeyHandle: _handle}));
        if (callResult == nil) {
            @throw [NSException
                    exceptionWithName:@"onStatusUpdateException"
                               reason:@"flutter onStatusUpdate result null"
                             userInfo:nil];
        }
    } @catch (NSException *exception) {
        FlutterMatterLog([[NSString alloc] initWithFormat:@"onStatusUpdate exception %@", [exception reason]]);
    } @finally {
        
    }
}

- (void)onPairingComplete:(NSError * _Nullable)error {
    @try {
        NSString *p = createFlutterCallPath(deviceControllerHost, @"CompletionListener/onPairingComplete");
        NSString *callResult = invokeMethodBlockGet([Global externalChannel], p, toJSONStringFromObject(@{@"errorCode": error == nil ? @(0) : @([error code]), jsonKeyHandle: _handle}));
        if (callResult == nil) {
            @throw [NSException
                    exceptionWithName:@"onPairingCompleteException"
                               reason:@"flutter onPairingComplete result null"
                             userInfo:nil];
        }
    } @catch (NSException *exception) {
        FlutterMatterLog([[NSString alloc] initWithFormat:@"onPairingComplete exception %@", [exception reason]]);
    } @finally {
        
    }
    if (!error) {
        NSLog(@"onPairingComplete start commissionDevice");
        NSError *err;
        [_deviceController commissionDevice:[_deviceId unsignedLongValue] commissioningParams:_commissioningParameters error:&err];
        if (err) {
            [self onCommissioningComplete:err];
        }
    }
}

 - (void)onCommissioningComplete:(NSError * _Nullable)error {
     @try {
         NSString *p = createFlutterCallPath(deviceControllerHost, @"CompletionListener/onCommissioningComplete");
         NSString *callResult = invokeMethodBlockGet([Global externalChannel], p, toJSONStringFromObject(@{@"nodeId": _deviceId, @"errorCode": error == nil ? @(0) : @([error code]), jsonKeyHandle: _handle}));
         if (callResult == nil) {
             @throw [NSException
                     exceptionWithName:@"onCommissioningCompleteException"
                                reason:@"flutter onCommissioningComplete result null"
                              userInfo:nil];
         }
     } @catch (NSException *exception) {
         FlutterMatterLog([[NSString alloc] initWithFormat:@"onCommissioningComplete exception %@", [exception reason]]);
     } @finally {
         
     }
 }

- (void)onPairingDeleted:(NSError * _Nullable)error {
    @try {
        NSString *p = createFlutterCallPath(deviceControllerHost, @"CompletionListener/onPairingDeleted");
        NSString *callResult = invokeMethodBlockGet([Global externalChannel], p, toJSONStringFromObject(@{@"errorCode": error == nil ? @(0) : @([error code]), jsonKeyHandle: _handle}));
        if (callResult == nil) {
            @throw [NSException
                    exceptionWithName:@"onPairingDeletedException"
                               reason:@"flutter onPairingDeleted result null"
                             userInfo:nil];
        }
    } @catch (NSException *exception) {
        FlutterMatterLog([[NSString alloc] initWithFormat:@"onPairingDeleted exception %@", [exception reason]]);
    } @finally {
        
    }
}

- (void)onCommissioningStatusUpdate:(NSNumber * _Nullable)nodeId commissioningStage:(NSString *)commissioningStage error:(NSError * _Nullable)error
{
    @try {
        NSString *p = createFlutterCallPath(deviceControllerHost, @"CompletionListener/onCommissioningStatusUpdate");
        NSString *callResult = invokeMethodBlockGet([Global externalChannel], p, toJSONStringFromObject(@{@"errorCode": error == nil ? @(0) : @([error code]), jsonKeyHandle: _handle, @"stage": commissioningStage, @"nodeId": nodeId}));
        if (callResult == nil) {
            @throw [NSException
                    exceptionWithName:@"onPairingDeletedException"
                               reason:@"flutter onPairingDeleted result null"
                             userInfo:nil];
        }
    } @catch (NSException *exception) {
        FlutterMatterLog([[NSString alloc] initWithFormat:@"onPairingDeleted exception %@", [exception reason]]);
    } @finally {
        
    }
}

- (instancetype)initWithHandle:(NSString *)handle commissioningParameters:(MTRCommissioningParameters *)commissioningParameters deviceController:(MTRDeviceController *)deviceController deviceId:(NSNumber *)deviceId {
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
    FlutterMatterLog([[NSString alloc]
        initWithFormat:@"%@ KeypairDelegate.signMessageECDSA_DER call",
                       [[NSThread currentThread] name]]);
    NSString *signMessageECDSA = createFlutterCallPath(
        deviceControllerHost, @"KeypairDelegate/EcdsaSignMessage");
    
    NSString *flutterReuslt = invokeMethodBlockGet(
        [Global externalChannel], signMessageECDSA,
        toJSONStringFromObject(@{@"handle" : _handle, @"message" : nsDataToIntegerArray(message)}));
    
    if (flutterReuslt == nil) {
        @throw [NSException
            exceptionWithName:@"callFlutterExceptionName"
                       reason:@"KeypairDelegate.EcdsaSignMessage result null"
                     userInfo:nil];
    }
    return toByteArrayFromJSONArray(
        [parseJSONString(flutterReuslt) objectForKey:@"ecdsaSign"]);
}

- (SecKeyRef)publicKey {
    FlutterMatterLog(
        [[NSString alloc] initWithFormat:@"%@ KeypairDelegate.publicKey call",
                                         [[NSThread currentThread] name]]);
    NSString *getPublicKeyPath = createFlutterCallPath(
        deviceControllerHost, @"KeypairDelegate/GetPublicKey");
    NSString *flutterReuslt =
        invokeMethodBlockGet([Global externalChannel], getPublicKeyPath,
                             toJSONStringFromObject(@{@"handle" : _handle}));
    if (flutterReuslt == nil) {
        @throw [NSException
            exceptionWithName:@"MainThreadException"
                       reason:@"KeypairDelegate.publicKey result null"
                     userInfo:nil];
    }
    NSData *publicKeyData = toByteArrayFromJSONArray(
        [parseJSONString(flutterReuslt) objectForKey:@"publicKey"]);

    // 使用 SecKeyCreateWithData 创建 SecKeyRef
    return nsDataToSecKey(publicKeyData);
}

- (instancetype)initWithHandle:(NSString *)handle {
    self = [super init];
    if (self) {
        _handle = handle; // 存储 handle
    }
    return self;
}
@end

@implementation MTRNOCChainIssuerWarp

- (void)onNOCChainGenerationNeeded:(CSRInfo *)csrInfo
                   attestationInfo:(AttestationInfo *)attestationInfo
      onNOCChainGenerationComplete:(MTRNOCChainGenerationCompleteHandler)onNOCChainGenerationComplete {
    FlutterMatterLog([[NSString alloc]
        initWithFormat:@"%@ KeypairDelegate.signMessageECDSA_DER call",
                       [[NSThread currentThread] name]]);
    NSString *requestPath = createFlutterCallPath(deviceControllerHost, @"NOCChainIssuer/onNOCChainGenerationNeeded");
    NSDictionary *csrInfoJson = @{
        @"csr": nsDataToIntegerArray([csrInfo csr]),
        @"elementsSignature": nsDataToIntegerArray([csrInfo elementsSignature]),
        @"elements": nsDataToIntegerArray([csrInfo elements]),
        @"nonce": nsDataToIntegerArray([csrInfo nonce])
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
        @"productId": @(0)
    };
    NSString *uuid = [[NSUUID UUID] UUIDString];
    [onNOCChainGenerationCompletes setObject:onNOCChainGenerationComplete forKey:uuid];
    NSString *flutterReuslt = invokeMethodBlockGet([Global externalChannel], requestPath, toJSONStringFromObject(@{
        jsonKeyHandle: _handle,
        @"csrInfo": csrInfoJson,
        @"attestationInfo": attestationInfoJson,
        @"onNOCChainGenerationCompleteHandle": uuid
    }));
    if (flutterReuslt == nil) {
        @throw [NSException
                exceptionWithName:@"onNOCChainGenerationNeededException"
                           reason:@"flutter onNOCChainGenerationNeeded result null"
                         userInfo:nil];
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
    NSArray *rootCertificate = [jsonObject objectForKey:@"rootCertificate"];
    NSData *rootCertificateData = nil;
    if (![rootCertificate isEqual:[NSNull null]]) {
        rootCertificateData = toByteArrayFromJSONArray(rootCertificate);
    }
    NSArray *intermediateCertificate =
        [jsonObject objectForKey:@"intermediateCertificate"];
    NSData *intermediateCertificateData = nil;
    if (![intermediateCertificate isEqual:[NSNull null]]) {
        intermediateCertificateData = toByteArrayFromJSONArray(intermediateCertificate);
    }
    NSArray *operationalCertificate =
        [jsonObject objectForKey:@"operationalCertificate"];
    NSData *operationalCertificateData = nil;
    if (![operationalCertificate isEqual:[NSNull null]]) {
        operationalCertificateData = toByteArrayFromJSONArray(operationalCertificate);
    }
    NSArray *ipk = [jsonObject objectForKey:@"ipk"];
    NSData *ipkData = nil;
    if (![ipk isEqual:[NSNull null]]) {
        ipkData = toByteArrayFromJSONArray(ipk);
    }
    NSNumber *fabricId = [jsonObject objectForKey:@"fabricId"];
    NSNumber *controllerVendorId =
        [jsonObject objectForKey:@"controllerVendorId"];
    NSNumber *udpListenPort = [jsonObject objectForKey:@"udpListenPort"];
    NSNumber *failsafeTimerSeconds =
        [jsonObject objectForKey:@"failsafeTimerSeconds"];
    NSNumber *caseFailsafeTimerSeconds =
        [jsonObject objectForKey:@"caseFailsafeTimerSeconds"];
    NSNumber *nodeId = [jsonObject objectForKey:@"nodeId"];
    NSString *keypairDelegateHandle =
        [jsonObject objectForKey:@"keypairDelegateHandle"];
    NSNumber *setUdpListenPort = [jsonObject objectForKey:@"udpListenPort"];
    NSNumber *attemptNetworkScanWiFi = [jsonObject objectForKey:@"attemptNetworkScanWiFi"];
    NSNumber *attemptNetworkScanThread = [jsonObject objectForKey:@"attemptNetworkScanThread"];
    NSNumber *skipCommissioningComplete = [jsonObject objectForKey:@"skipCommissioningComplete"];
    NSString *countryCode = [jsonObject objectForKey:@"countryCode"];
    NSNumber *adminSubject = [jsonObject objectForKey:@"adminSubject"];
    NSNumber *regulatoryLocationType = [jsonObject objectForKey:@"regulatoryLocationType"];
    NSNumber *enableServerInteractions = [jsonObject objectForKey:@"enableServerInteractions"];
    if ([setUdpListenPort isEqual:[NSNull null]]) {
        setUdpListenPort = @(0);
    }
    if ([attemptNetworkScanWiFi isEqual:[NSNull null]]) {
        attemptNetworkScanWiFi = @(0);
    }
    if ([attemptNetworkScanThread isEqual:[NSNull null]]) {
        attemptNetworkScanThread = @(0);
    }
    if ([skipCommissioningComplete isEqual:[NSNull null]]) {
        skipCommissioningComplete = @(0);
    }
    if ([regulatoryLocationType isEqual:[NSNull null]]) {
        regulatoryLocationType = @(0);
    }
    if ([enableServerInteractions isEqual:[NSNull null]]) {
        enableServerInteractions = @(0);
    }
    if ([failsafeTimerSeconds isEqual:[NSNull null]]) {
        failsafeTimerSeconds = @(30);
    }
    if ([caseFailsafeTimerSeconds isEqual:[NSNull null]]) {
        caseFailsafeTimerSeconds = @(30);
    }
    
    return [[FlutterControllerParams alloc] init:[fabricId intValue] udpListenPort:[udpListenPort intValue] controllerVendorId:[controllerVendorId intValue] failsafeTimerSeconds:[failsafeTimerSeconds intValue] caseFailsafeTimerSeconds:[caseFailsafeTimerSeconds intValue] attemptNetworkScanWiFi:[attemptNetworkScanWiFi intValue] != 0 attemptNetworkScanThread:[attemptNetworkScanThread intValue] != 0 skipCommissioningComplete:[skipCommissioningComplete intValue] != 0 countryCode:countryCode regulatoryLocationType:[regulatoryLocationType intValue] keypairDelegate:keypairDelegateHandle rootCertificate:rootCertificateData intermediateCertificate:intermediateCertificateData operationalCertificate:operationalCertificateData ipk:ipkData adminSubject:[adminSubject intValue] enableServerInteractions:[enableServerInteractions intValue] != 0 setupURL:nil nodeId:[nodeId intValue]];
}

static MTRDeviceControllerStartupParams *
mapControllerParams(FlutterControllerParams *flutterControllerParams) {

    MTRDeviceControllerStartupParams *params;
    if ([flutterControllerParams ipk] != nil &&
        [flutterControllerParams rootCertificate] != nil &&
        [flutterControllerParams intermediateCertificate] != nil &&
        [flutterControllerParams operationalCertificate] != nil &&
        [flutterControllerParams keypairDelegate] != nil) {
        KeypairWarp *kp =
            [[KeypairWarp alloc] initWithHandle:[flutterControllerParams keypairDelegate]];
        params = [[MTRDeviceControllerStartupParams alloc]
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
        params = [[MTRDeviceControllerStartupParams alloc]
            initWithIPK:[flutterControllerParams ipk]
               fabricID:@([flutterControllerParams fabricId])
              nocSigner:kp];
        if ([flutterControllerParams nodeId] != 0) {
            [params setNodeID:@([flutterControllerParams nodeId])];
        }
    } else {
        @throw [NSException
            exceptionWithName:@"CreateControllerParamsException"
                       reason:@"ipk, rootCertificate, operationalCertificate, "
                              @"keypairDelegateHandle or ipk, fabricId, "
                              @"keypairDelegateHandle must not be null"
                     userInfo:nil];
    }
    if ([flutterControllerParams controllerVendorId]) {
        [params setVendorID:@([flutterControllerParams controllerVendorId])];
    }
    return params;
}

static MTRDeviceController* getMTRDeviceController(NSString *handle) {
    FlutterDeviceController *c = [controls objectForKey:handle];
    if (c == nil) {
        return nil;
    }
    return [c controller];
}

/// convert to flutter NodeState class json
static NSDictionary * convertNodeStateJsonFormat(NSArray<NSDictionary<NSString *,id> *> * _Nullable values) {
    NSMutableDictionary * nodeState = [[NSMutableDictionary alloc] init];
    for (id element in values) {
        if (![element isKindOfClass:NSDictionary.class]) {
            continue;
        }
        MTRAttributePath * attrPath = [element objectForKey:MTRAttributePathKey];
        MTREventPath * eventPath = [element objectForKey:MTREventPathKey];

        if (![attrPath isEqual:[NSNull null]] && attrPath != nil) {
            NSDictionary * data = [element objectForKey:MTRDataKey];
            if (![data isKindOfClass:NSDictionary.class]) {
                continue;
            }
            NSMutableDictionary * endpoints = [nodeState objectForKey:@"endpoints"];
            if ([endpoints isEqual:[NSNull null]] || endpoints == nil) {
                endpoints = [[NSMutableDictionary alloc] init];
                [nodeState setObject:endpoints forKey:@"endpoints"];
            }
            NSMutableDictionary * endpointState = [endpoints objectForKey:[[attrPath endpoint] description]];
            if ([endpointState isEqual:[NSNull null]] || endpointState == nil) {
                endpointState = [[NSMutableDictionary alloc] init];
                [endpoints setObject:endpointState forKey:[[attrPath endpoint] description]];
            }
            NSMutableDictionary * clusters = [endpointState objectForKey:@"clusters"];
            if ([clusters isEqual:[NSNull null]] || clusters == nil) {
                clusters = [[NSMutableDictionary alloc] init];
                [endpointState setObject:clusters forKey:@"clusters"];
            }
            NSMutableDictionary * clusterState = [clusters objectForKey:[[attrPath cluster] description]];
            if ([clusterState isEqual:[NSNull null]] || clusterState == nil) {
                clusterState = [[NSMutableDictionary alloc] init];
                [clusters setObject:clusterState forKey:[[attrPath cluster] description]];
            }
            
            NSMutableDictionary * attributes = [clusterState objectForKey:@"attributes"];
            if ([attributes isEqual:[NSNull null]] || attributes == nil) {
                attributes = [[NSMutableDictionary alloc] init];
                [clusterState setObject:attributes forKey:@"attributes"];
            }
            NSData * tlvData = [data objectForKey:MTRTlvValueType];
            [attributes setObject:@{
                @"tlv": tlvData == nil ? [NSNull null] : nsDataToIntegerArray(tlvData)
            } forKey:[[attrPath attribute] description]];
        }

        if (eventPath) {
            NSDictionary * data = [element objectForKey:MTRDataKey];
            if (![data isKindOfClass:NSDictionary.class]) {
                continue;
            }
            NSMutableDictionary * endpoints = [nodeState objectForKey:@"endpoints"];
            if ([endpoints isEqual:[NSNull null]] || endpoints == nil) {
                endpoints = [[NSMutableDictionary alloc] init];
                [nodeState setObject:endpoints forKey:@"endpoints"];
            }
            NSMutableDictionary * endpointState = [endpoints objectForKey:[[attrPath endpoint] description]];
            if ([endpointState isEqual:[NSNull null]] || endpointState == nil) {
                endpointState = [[NSMutableDictionary alloc] init];
                [endpoints setObject:endpointState forKey:[[attrPath endpoint] description]];
            }
            NSMutableDictionary * clusters = [endpointState objectForKey:@"clusters"];
            if ([clusters isEqual:[NSNull null]] || clusters == nil) {
                clusters = [[NSMutableDictionary alloc] init];
                [endpointState setObject:clusters forKey:@"clusters"];
            }
            NSMutableDictionary * clusterState = [clusters objectForKey:[[attrPath cluster] description]];
            if ([clusterState isEqual:[NSNull null]] || clusterState == nil) {
                clusterState = [[NSMutableDictionary alloc] init];
                [clusters setObject:clusterState forKey:[[attrPath cluster] description]];
            }
            NSMutableDictionary * events = [clusterState objectForKey:@"events"];
            if ([events isEqual:[NSNull null]] || events == nil) {
                events = [[NSMutableDictionary alloc] init];
                [clusterState setObject:events forKey:@"events"];
            }
            
            if ([[data allKeys] containsObject: MTRErrorKey]) {
                continue;
            }
            [events setObject:@{
                @"eventNumber": [data objectForKey:MTREventNumberKey],
                @"priorityLevel": [data objectForKey:MTREventPriorityKey],
                @"timestampType": [data objectForKey:MTREventTimeTypeKey],
                @"timestampValue": [[data allKeys] containsObject:MTREventSystemUpTimeKey] ? [data objectForKey:MTREventSystemUpTimeKey] : [data objectForKey:MTREventTimestampDateKey],
                @"tlv": [data objectForKey:MTRTlvValueType]
            } forKey:[[eventPath event] description]];
        }
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
    NSDictionary *jsonObject = parseJSONString(params);
    FlutterControllerParams *fControlParams = mapFlutterControllerParams(jsonObject);
    MTRDeviceControllerStartupParams *controllerParams =
        mapControllerParams(fControlParams);
    MTRDeviceController *controller = [[MTRControllerFactory sharedInstance]
        startControllerOnExistingFabric:controllerParams];
    if (controller == nil) {
        controller = [[MTRControllerFactory sharedInstance]
            startControllerOnNewFabric:controllerParams];
    }
    if (controller == nil) {
        @throw [NSException exceptionWithName:@"newDeviceControllerException"
                                       reason:@"Create Controller failed"
                                     userInfo:nil];
    }
    NSString *uuid = [[controller uniqueIdentifier] UUIDString];
    FlutterDeviceController *fdController = [[FlutterDeviceController alloc] initWithController:controller controllerParams:fControlParams];
    [controls setObject:fdController forKey:uuid];
    return createFlutterRequestResultWithCode(0, @{@"handle" : uuid});
}

static NSString *createRootCertificate(NSString *params) {
    NSDictionary *jsonObject = parseJSONString(params);
    NSString *keypairHandle =
        requestJsonValueNotNull(jsonObject, @"keypairHandle");
    NSNumber *issuerId = [jsonObject objectForKey:@"issuerId"];
    NSNumber *fabricId = [jsonObject objectForKey:@"fabricId"];
    KeypairWarp *kp = [[KeypairWarp alloc] initWithHandle:keypairHandle];
    NSData *rcac = [MTRCertificates createRootCertificate:kp
                                                 issuerID:[issuerId isEqual:[NSNull null]] ? nil : issuerId
                                                 fabricID:[fabricId isEqual:[NSNull null]] ? nil : fabricId
                                                    error:nil];
    if (rcac == nil) {
        return createFlutterRequestResultWithCode(1, @{});
    }
    return createFlutterRequestResultWithCode(0, @{@"data" : nsDataToIntegerArray(rcac)});
}

static NSString *setNocChainIssuer(NSString *params) {
    NSDictionary *jsonObject = parseJSONString(params);
    NSString *handle = requestJsonValueNotNull(jsonObject, jsonKeyHandle);
    MTRDeviceController *deviceController = getMTRDeviceController(handle);
    if ([deviceController isEqual:[NSNull null]] || deviceController == nil) {
        @throw [NSException exceptionWithName:@"setNocChainIssuerException"
                                       reason:@"Not found deviceController"
                                     userInfo:nil];
    }
    MTRNOCChainIssuerWarp *issuer = [[MTRNOCChainIssuerWarp alloc] initWithHandle:handle];
    [deviceController setNocChainIssuer:issuer queue:dispatch_queue_create("nocChainIssuer", DISPATCH_QUEUE_SERIAL)];
    return createFlutterRequestResultWithCode(0, @{});
}

static NSString *onNOCChainGeneration(NSString *params) {
    NSDictionary *jsonObject = parseJSONString(params);
    NSString *handle = requestJsonValueNotNull(jsonObject, jsonKeyHandle);
    MTRDeviceController *deviceController = getMTRDeviceController(handle);
    if ([deviceController isEqual:[NSNull null]] || deviceController == nil) {
        @throw [NSException exceptionWithName:@"setNocChainIssuerException"
                                       reason:@"Not found deviceController"
                                     userInfo:nil];
    }
    NSString *onNOCChainGenerationCompleteHandle = requestJsonValueNotNull(jsonObject, @"onNOCChainGenerationCompleteHandle");
    MTRNOCChainGenerationCompleteHandler completeHandler = [onNOCChainGenerationCompletes objectForKey:onNOCChainGenerationCompleteHandle];
    FlutterControllerParams *controlParams = mapFlutterControllerParams(requestJsonValueNotNull(jsonObject, @"params"));
    NSData *rootCertificate = [controlParams rootCertificate];
    NSData *intermediateCertificate = [controlParams intermediateCertificate];
    NSData *operationalCertificate = [controlParams operationalCertificate];
    NSData *ipk = [controlParams ipk];
    NSNumber *adminSubject = @([controlParams adminSubject]);
    NSError *error = nil;
    completeHandler(operationalCertificate, intermediateCertificate, rootCertificate, ipk, adminSubject, &error);
    return createFlutterRequestResultWithCode(0, @{@"data": error == nil ? @(0) : @([error code])});
}

//static NSString *setCompletionListener(NSString *params) {
//    NSDictionary *jsonObject = parseJSONString(params);
//    NSString *handle = requestJsonValueNotNull(jsonObject, jsonKeyHandle);
//    MTRDeviceController *deviceController = getMTRDeviceController(handle);
//    if ([deviceController isEqual:[NSNull null]] || deviceController == nil) {
//        @throw [NSException exceptionWithName:@"setCompletionListener"
//                                       reason:@"Not found deviceController"
//                                     userInfo:nil];
//    }
//    [deviceController setPairingDelegate:[[PairingDelegateWarp alloc] initWithHandle:handle] queue:dispatch_queue_create("completionListener", DISPATCH_QUEUE_SERIAL)];
//    return createFlutterRequestResultWithCode(0, @{});
//}

static NSString *publicKeyFromCSR(NSString *params) {
    NSDictionary *jsonObject = parseJSONString(params);
    NSData *csr = toByteArrayFromJSONArray(requestJsonValueNotNull(jsonObject, @"csr"));
    NSError *error = nil;
    NSData *publicKey = [MTRCertificates publicKeyFromCSR:csr error:&error];
    if (publicKey == nil) {
        @throw [NSException exceptionWithName:@"publicKeyFromCSRException"
                                       reason:@"CSR 无效"
                                     userInfo:nil];
    }
    return createFlutterRequestResultWithCode(0, @{@"data": nsDataToIntegerArray(publicKey)});
}

static NSString *continueCommissioning(NSString *params) {
    NSDictionary *jsonObject = parseJSONString(params);
    NSString *handle = requestJsonValueNotNull(jsonObject, jsonKeyHandle);
    MTRDeviceController *deviceController = getMTRDeviceController(handle);
    if ([deviceController isEqual:[NSNull null]] || deviceController == nil) {
        @throw [NSException exceptionWithName:@"continueCommissioningException"
                                       reason:@"Not found deviceController"
                                     userInfo:nil];
    }
    NSNumber *devicePtr = requestJsonValueNotNull(jsonObject, @"devicePtr");
    id ignoreAttestationFailureValue = [jsonObject objectForKey:@"ignoreAttestationFailure"];
    NSError *error = nil;
    BOOL success = [deviceController continueCommissioningDevice:(void*)[devicePtr unsignedLongValue] ignoreAttestationFailure:[ignoreAttestationFailureValue isKindOfClass:[NSNumber class]] ? [ignoreAttestationFailureValue boolValue] : NO error:&error];
    return createFlutterRequestResultWithCode(success ? 1 : 0, @{});
}

static NSString *createOperationalCertificate(NSString *params) {
    NSDictionary *jsonObject = parseJSONString(params);
    NSData *signingCertificate = toByteArrayFromJSONArray(requestJsonValueNotNull(jsonObject, @"signingCertificate"));
    NSData *operationalPublicKey = toByteArrayFromJSONArray(requestJsonValueNotNull(jsonObject, @"operationalPublicKey"));
    NSNumber *fabricId = requestJsonValueNotNull(jsonObject, @"fabricId");
    NSNumber *nodeId = requestJsonValueNotNull(jsonObject, @"nodeId");
    NSString *keypairHandle = requestJsonValueNotNull(jsonObject, @"keypairHandle");
    id caseAuthenticatedTags = [jsonObject objectForKey:@"caseAuthenticatedTags"];
    if (![caseAuthenticatedTags isEqual:[NSNull null]] && caseAuthenticatedTags != nil) {
        caseAuthenticatedTags = toByteArrayFromJSONArray(caseAuthenticatedTags);
    } else {
        caseAuthenticatedTags = nil;
    }
    KeypairWarp *kp =
        [[KeypairWarp alloc] initWithHandle:keypairHandle];
    NSError *error = nil;
    
    NSData *operationalCertificate = [MTRCertificates createOperationalCertificate:kp signingCertificate:signingCertificate operationalPublicKey:nsDataToSecKey(operationalPublicKey) fabricID:fabricId nodeID:nodeId caseAuthenticatedTags:caseAuthenticatedTags error:&error];
    return createFlutterRequestResultWithCode(0, @{@"data": nsDataToIntegerArray(operationalCertificate)});
}

static NSString *pairDevice(NSString *params) {
    NSDictionary *jsonObject = parseJSONString(params);
    NSString *handle = requestJsonValueNotNull(jsonObject, jsonKeyHandle);
    FlutterDeviceController *c = [controls objectForKey:handle];
    MTRDeviceController *deviceController = c == nil ? nil : [c controller];
    FlutterControllerParams *fcp = c == nil ? nil : [c controllerParams];
    NSNumber *deviceId = requestJsonValueNotNull(jsonObject, @"deviceId");
    NSString *displayName = requestJsonValueNotNull(jsonObject, @"displayName");
    NSString *ecosystemName = requestJsonValueNotNull(jsonObject, @"ecosystemName");
//    NSNumber *connId = requestJsonValueNotNull(jsonObject, @"connId");
//    NSNumber *setupPINCode = requestJsonValueNotNull(jsonObject, @"setupPincode");
    NSString *onboardingPayload = [jsonObject objectForKey:@"onboardingPayload"];
    NSString *completionListenerHandle = [jsonObject objectForKey:@"completionListener"];
    id csrNonce = [jsonObject objectForKey:@"csrNonce"];
    NSDictionary *networkCredentials = [jsonObject objectForKey:@"networkCredentials"];
    NSString *attestationDelegate = [jsonObject objectForKey:@"attestationDelegate"];
    NSString *ssid = nil;
    NSString *pwd = nil;
    if (![networkCredentials isEqual:[NSNull null]]) {
        NSDictionary *wifiCredentials = [networkCredentials objectForKey:@"wifiCredentials"];
        if (![wifiCredentials isEqual:[NSNull null]]) {
            ssid = [wifiCredentials objectForKey:@"ssid"];
            pwd = [wifiCredentials objectForKey:@"password"];
        }
    }
    
    if (![csrNonce isEqual:[NSNull null]]) {
        csrNonce = toByteArrayFromJSONArray(csrNonce);
    }
    
    if ([NSThread isMainThread]) {
        @throw [NSException exceptionWithName:@"Run on main thread"
                                       reason:@"pairDevice unable run on main thread"
                                     userInfo:nil];
    }
    dispatch_semaphore_t semaphore = dispatch_semaphore_create(0);
    __block NSError *pairError;
    [MatterDevicePair startPairDeviceWithOnboardingPayload:onboardingPayload displayName:displayName ecosystemName:ecosystemName completion:^(NSString * _Nullable code, NSError * _Nullable err) {
        @try {
            if (code != nil) {
                NSLog(@"pair code %@", code);
                NSError *error;
                MTRCommissioningParameters * commissioningParams = [[MTRCommissioningParameters alloc] init];
                commissioningParams.failSafeTimeout = @([fcp failsafeTimerSeconds]);
                commissioningParams.skipCommissioningComplete = [fcp skipCommissioningComplete];
                if (ssid != nil && pwd != nil) {
                    commissioningParams.wifiSSID = [ssid dataUsingEncoding:NSUTF8StringEncoding];
                    commissioningParams.wifiCredentials = [pwd dataUsingEncoding:NSUTF8StringEncoding];
                }
                if (![attestationDelegate isEqual:[NSNull null]]) {
                    [commissioningParams setDeviceAttestationDelegate:[[DeviceAttestationDelegate alloc] initWithHandle:handle]];
                }
                if (![completionListenerHandle isEqual:[NSNull null]]) {
                    PairingDelegateWarp *pairingDelegate = [[PairingDelegateWarp alloc] initWithHandle:handle commissioningParameters:commissioningParams deviceController:deviceController deviceId:deviceId];
                    [deviceController setPairingDelegate:pairingDelegate queue:[Global backgroundSerialQueue]];
                }
                [deviceController pairDevice:[deviceId unsignedLongValue] onboardingPayload:code error:&error];
                if (error) {
                    @throw [NSException exceptionWithName:@"pairDeviceException"
                                                   reason:[error localizedDescription]
                                                 userInfo:nil];
                }
            } else {
                if (err != nil) {
                    @throw [NSException exceptionWithName:@"pairDeviceException"
                                                   reason:[err localizedDescription]
                                                 userInfo:nil];
                }
                @throw [NSException exceptionWithName:@"OnboardingPayloadException"
                                                      reason:@"onboardingPayload is nil"
                                                    userInfo:nil];
            }
        } @catch (NSException *exception) {
            pairError = [NSError errorWithDomain:@""
                                            code:1
                                        userInfo:@{ NSLocalizedDescriptionKey: [exception reason] }];
        } @finally {
          dispatch_semaphore_signal(semaphore);
        }
    }];
    dispatch_semaphore_wait(semaphore, DISPATCH_TIME_FOREVER);
    return createFlutterRequestResultWithCode(pairError != nil ? [pairError code] : 0, @{});
}

//static NSString *setDeviceAttestationDelegate(NSString *params) {
//    NSDictionary *jsonObject = parseJSONString(params);
//    NSString *handle = requestJsonValueNotNull(jsonObject, jsonKeyHandle);
//    MTRDeviceController *deviceController = getMTRDeviceController(handle);
//    if ([deviceController isEqual:[NSNull null]] || deviceController == nil) {
//        @throw [NSException exceptionWithName:@"setDeviceAttestationDelegateException"
//                                       reason:@"Not found deviceController"
//                                     userInfo:nil];
//    }
//    [deviceController setDeviceAttestationDelegate:[[DeviceAttestationDelegate alloc] initWithHandle:handle] timeoutSecs:600];
//    return createFlutterRequestResultWithCode(0, @{});
//}

static NSString *stopDevicePairing(NSString *params) {
    NSDictionary *jsonObject = parseJSONString(params);
    NSString *handle = requestJsonValueNotNull(jsonObject, jsonKeyHandle);
    MTRDeviceController *deviceController = getMTRDeviceController(handle);
    if ([deviceController isEqual:[NSNull null]] || deviceController == nil) {
        @throw [NSException exceptionWithName:@"stopDevicePairingException"
                                       reason:@"Not found deviceController"
                                     userInfo:nil];
    }
    NSNumber *deviceId = requestJsonValueNotNull(jsonObject, @"deviceId");
    NSError *error;
    [deviceController cancelCommissioningForNodeID:deviceId error:&error];
    return createFlutterRequestResultWithCode(0, @{});
}

static NSString *deleteDeviceController(NSString *params) {
    NSDictionary *jsonObject = parseJSONString(params);
    NSString *handle = requestJsonValueNotNull(jsonObject, jsonKeyHandle);
    MTRDeviceController *control = getMTRDeviceController(handle);
    if (control != nil) {
        [control shutdown];
        [controls removeObjectForKey:handle];
    }
    return createFlutterRequestResultWithCode(0, @{});
}

static NSString *connectedDevice(NSString *params) {
    NSDictionary *jsonObject = parseJSONString(params);
    NSString *handle = requestJsonValueNotNull(jsonObject, jsonKeyHandle);
    MTRDeviceController *deviceController = getMTRDeviceController(handle);
    if ([deviceController isEqual:[NSNull null]] || deviceController == nil) {
        @throw [NSException exceptionWithName:@"stopDevicePairingException"
                                       reason:@"Not found deviceController"
                                     userInfo:nil];
    }
    NSNumber *nodeId = requestJsonValueNotNull(jsonObject, @"nodeId");
    NSString *callbackHandle = requestJsonValueNotNull(jsonObject, @"callbackHandle");
    [deviceController getBaseDevice:[nodeId intValue] queue:connectDeviceQueue completionHandler:^(MTRBaseDevice * _Nullable device, NSError * _Nullable error) {
        if (device != nil) {
            FlutterDeviceController *fdc = [controls objectForKey:handle];
            if (fdc != nil) {
                MTRBaseDevice *alreadyConnectDevice = [fdc deviceInfoForNodeID:[nodeId intValue]];
                if (alreadyConnectDevice == nil) {
                    [fdc addConnectedDeviceWithNodeID:[nodeId intValue] deviceInfo:device];
                }
                NSString * path = createFlutterCallPath(deviceControllerHost, @"ConnectedDeviceCallback/onDeviceConnected");
                @try {
                    invokeMethodBlockGet([Global externalChannel], path, toJSONStringFromObject(@{
                        jsonKeyHandle: handle,
                        @"callbackHandle": callbackHandle,
                        @"context": nodeId
                    }));
                } @catch (NSException *exception) {
                    FlutterMatterLog([[NSString alloc] initWithFormat:@"flutter result connect faile %@", [exception reason]]);
                } @finally {
                    
                }
                return;
            }
        }
        FlutterMatterLog([[NSString alloc] initWithFormat:@"matter case connect %@ failed", nodeId]);
        NSString * path = createFlutterCallPath(deviceControllerHost, @"ConnectedDeviceCallback/onConnectionFailure");
        @try {
            invokeMethodBlockGet([Global externalChannel], path, toJSONStringFromObject(@{
                jsonKeyHandle: handle,
                @"callbackHandle": callbackHandle,
                @"context": nodeId,
                @"nodeId": nodeId,
                @"error": error == nil ? @"unknown error" : [error localizedDescription]
            }));
        } @catch (NSException *exception) {
            FlutterMatterLog([[NSString alloc] initWithFormat:@"flutter result connect faile %@", [exception reason]]);
        } @finally {
            
        }
    }];
    
    return createFlutterRequestResultWithCode(0, @{});
}

static NSString *releaseConnectContext(NSString *params) {
    NSDictionary *jsonObject = parseJSONString(params);
    NSString *handle = requestJsonValueNotNull(jsonObject, jsonKeyHandle);
    MTRDeviceController *deviceController = getMTRDeviceController(handle);
    if ([deviceController isEqual:[NSNull null]] || deviceController == nil) {
        @throw [NSException exceptionWithName:@"stopDevicePairingException"
                                       reason:@"Not found deviceController"
                                     userInfo:nil];
    }
    return createFlutterRequestResultWithCode(0, @{});
}

static MTRBaseDevice * getBaseDevice(FlutterDeviceController * fcontrol, NSNumber * nodeId, NSNumber * connectContext) {
    if (connectContext == nil) {
        return [MTRBaseDevice deviceWithNodeID:nodeId controller:[fcontrol controller]];
    }
    return [fcontrol deviceInfoForNodeID:[nodeId intValue]];
}

static NSString *invoke(NSString *params) {
    NSDictionary *jsonObject = parseJSONString(params);
    NSString *handle = requestJsonValueNotNull(jsonObject, jsonKeyHandle);
    MTRDeviceController *deviceController = getMTRDeviceController(handle);
    if ([deviceController isEqual:[NSNull null]] || deviceController == nil) {
        @throw [NSException exceptionWithName:@"invokeException"
                                       reason:@"Not found deviceController"
                                     userInfo:nil];
    }
    NSString *callbackId = requestJsonValueNotNull(jsonObject, @"callback");
    NSNumber *nodeId = requestJsonValueNotNull(jsonObject, @"nodeId");
    
    NSNumber *timedRequestTimeoutMs = [jsonObject objectForKey:@"timedRequestTimeoutMs"];
    if ([timedRequestTimeoutMs isEqual:[NSNull null]]) {
        timedRequestTimeoutMs = @(5000);
    }
    NSNumber *imTimeoutMs = [jsonObject objectForKey:@"imTimeoutMs"];
    if ([imTimeoutMs isEqual:[NSNull null]]) {
        imTimeoutMs = @(0);
    }
    
    NSDictionary * invokeElementJsonObject = requestJsonValueNotNull(jsonObject, @"invokeElement");
    NSNumber * endpointId = [requestJsonValueNotNull(invokeElementJsonObject, @"endpointId") objectForKey:@"id"];
    NSNumber * clusterId = [requestJsonValueNotNull(invokeElementJsonObject, @"clusterId") objectForKey:@"id"];
    NSNumber * commandId = [requestJsonValueNotNull(invokeElementJsonObject, @"commandId") objectForKey:@"id"];
    NSNumber * groupId = [invokeElementJsonObject objectForKey:@"groupId"];
    NSData * tlv = toByteArrayFromJSONArray(requestJsonValueNotNull(invokeElementJsonObject, @"tlv"));
    
    NSNumber * connectContext = [jsonObject objectForKey:@"connectContext"];
    
    FlutterDeviceController *fdc = [controls objectForKey:handle];
    MTRBaseDevice* baseDevice = getBaseDevice(fdc, nodeId, [connectContext isEqual:[NSNull null]] ? nil : connectContext);
    if (baseDevice == nil) {
        return createFlutterRequestResultWithCode(1, @{});
    }
    [baseDevice invokeCommandWithEndpointID:endpointId clusterID:clusterId commandID:commandId commandFields:tlv timedInvokeTimeout:[imTimeoutMs isEqualToNumber:@(0)] ? nil : imTimeoutMs queue:connectDeviceQueue completion:^(NSArray<NSDictionary<NSString *,id> *> * _Nullable values, NSError * _Nullable error) {
        @try {
            if (error) {
                // failed callback
                invokeMethodBlockGet([Global externalChannel], createFlutterCallPath(deviceControllerHost, @"InvokeCallback/onError"), toJSONStringFromObject(@{
                    jsonKeyHandle: handle,
                    @"invokeCallbackPoint": callbackId,
                    @"error": [error localizedDescription]
                }));
            } else {
                // success callback
                NSNumber * resultEndPointId = endpointId;
                NSNumber * resultClusterId = clusterId;
                NSNumber * resultCommandId = commandId;
                if (values != nil && [values count] > 0) {
                    NSDictionary<NSString *,id> * dictionary = [values objectAtIndex:0];
                    id commandPath = [dictionary objectForKey:@"commandPath"];
                    if (![commandPath isEqual:[NSNull null]] && [commandPath isKindOfClass:[MTRCommandPath class]]) {
                        MTRCommandPath * cp = commandPath;
                        resultEndPointId = [cp endpoint];
                        resultClusterId = [cp cluster];
                        resultCommandId = [cp command];
                    }
                }
                invokeMethodBlockGet([Global externalChannel], createFlutterCallPath(deviceControllerHost, @"InvokeCallback/onResponse"), toJSONStringFromObject(@{
                    jsonKeyHandle: handle,
                    @"invokeCallbackPoint": callbackId,
                    @"successCode": @(0),
                    @"invokeElement": values == nil ? nil : @{
                        @"endpointId": @{
                            @"id": resultEndPointId
                        },
                        @"clusterId": @{
                            @"id": resultClusterId
                        },
                        @"commandId": @{
                            @"id": resultCommandId
                        },
                        @"groupId": groupId,
                    }
                }));
            }
            // onDone callback
            invokeMethodBlockGet([Global externalChannel], createFlutterCallPath(deviceControllerHost, @"InvokeCallback/onDone"), toJSONStringFromObject(@{
                jsonKeyHandle: handle,
                @"invokeCallbackPoint": callbackId
            }));
        } @catch (NSException *exception) {
            FlutterMatterLog([[NSString alloc] initWithFormat:@"callback invoke error %@", [exception reason]]);
        } @finally {
            
        }
    }];
    return createFlutterRequestResultWithCode(0, @{});
}

static NSString * subscribe(NSString * params) {
    NSDictionary *jsonObject = parseJSONString(params);
    NSString *handle = requestJsonValueNotNull(jsonObject, jsonKeyHandle);
    MTRDeviceController *deviceController = getMTRDeviceController(handle);
    NSString *callbackId = requestJsonValueNotNull(jsonObject, @"callbackHandle");
    NSNumber *nodeId = requestJsonValueNotNull(jsonObject, @"nodeId");
    NSArray * attributePathsJson = [jsonObject objectForKey:@"attributePaths"];
    NSArray * eventPathsJson = [jsonObject objectForKey:@"eventPathsJson"];
    NSNumber * minInterval = requestJsonValueNotNull(jsonObject, @"minInterval");
    NSNumber * maxInterval = requestJsonValueNotNull(jsonObject, @"maxInterval");
    NSNumber * keepSubscriptions = [jsonObject objectForKey:@"keepSubscriptions"];
    NSNumber * isFabricFiltered = [jsonObject objectForKey:@"isFabricFiltered"];
    NSNumber * imTimeoutMs = [jsonObject objectForKey:@"imTimeoutMs"];
    NSNumber * connectContext = [jsonObject objectForKey:@"connectContext"];
    NSNumber * eventMin = [jsonObject objectForKey:@"eventMin"];
    FlutterDeviceController *fdc = [controls objectForKey:handle];
    MTRBaseDevice* baseDevice = getBaseDevice(fdc, nodeId, [connectContext isEqual:[NSNull null]] ? nil : connectContext);
    if (baseDevice == nil) {
        return createFlutterRequestResultWithCode(1, @{});
    }
    MTRSubscribeParams * subscribeParams = [[MTRSubscribeParams alloc] initWithMinInterval:minInterval maxInterval:maxInterval];
    subscribeParams.replaceExistingSubscriptions = [keepSubscriptions isEqual:[NSNull null]] ? NO : keepSubscriptions.boolValue;
    subscribeParams.filterByFabric = [isFabricFiltered isEqual:[NSNull null]] ? NO : isFabricFiltered.boolValue;
    subscribeParams.resubscribeAutomatically = false;
    
    NSMutableArray * attributePaths = nil;
    if (![attributePathsJson isEqual:[NSNull null]]) {
        attributePaths = [NSMutableArray array];
        for (NSUInteger i = 0; i < attributePathsJson.count; i++) {
            NSDictionary * attributePath = attributePathsJson[i];
            NSNumber * endpointId = [[attributePath objectForKey:@"endpointId"] objectForKey:@"id"];
            NSNumber * clusterId = [[attributePath objectForKey:@"clusterId"] objectForKey:@"id"];
            NSNumber * attributeId = [[attributePath objectForKey:@"attributeId"] objectForKey:@"id"];
            [attributePaths addObject:[MTRAttributeRequestPath requestPathWithEndpointID:endpointId clusterID:clusterId attributeID:attributeId]];
        }
    }
    NSMutableArray * eventPaths = nil;
    if (![eventPathsJson isEqual:[NSNull null]]) {
        eventPaths = [NSMutableArray array];
        for (NSUInteger i = 0; i < eventPathsJson.count; i++) {
            NSDictionary * eventPath = eventPaths[i];
            NSNumber * endpointId = [[eventPath objectForKey:@"endpointId"] objectForKey:@"id"];
            NSNumber * clusterId = [[eventPath objectForKey:@"clusterId"] objectForKey:@"id"];
            NSNumber * eventId = [[eventPath objectForKey:@"eventId"] objectForKey:@"id"];
            [eventPaths addObject:[MTREventRequestPath requestPathWithEndpointID:endpointId clusterID:clusterId eventID:eventId]];
        }
    }
    [baseDevice customSubscribeToAttributePaths:attributePaths eventPaths:eventPaths params:subscribeParams queue:connectDeviceQueue reportHandler:^(NSArray<NSDictionary<NSString *,id> *> * _Nullable values, NSError * _Nullable error) {
        @try {
            if (error) {
                // failed callback
                invokeMethodBlockGet([Global externalChannel], createFlutterCallPath(deviceControllerHost, @"SubscriptionCallback/onError"), toJSONStringFromObject(@{
                    jsonKeyHandle: handle,
                    @"subscriptionCallbackPoint": callbackId,
                    @"error": [error localizedDescription]
                }));
                invokeMethodBlockGet([Global externalChannel], createFlutterCallPath(deviceControllerHost, @"SubscriptionCallback/onDone"), toJSONStringFromObject(@{
                    jsonKeyHandle: handle,
                    @"subscriptionCallbackPoint": callbackId,
                }));
            } else {
                // success callback
                invokeMethodBlockGet([Global externalChannel], createFlutterCallPath(deviceControllerHost, @"SubscriptionCallback/onReport"), toJSONStringFromObject(@{
                    jsonKeyHandle: handle,
                    @"subscriptionCallbackPoint": callbackId,
                    @"nodeState": values == nil ? [NSNull null] : convertNodeStateJsonFormat(values)
                }));
            }
        } @catch (NSException *exception) {
            FlutterMatterLog([[NSString alloc] initWithFormat:@"Call flutter subscribe result error %@", [exception reason]]);
        } @finally {
            
        }
    } subscriptionEstablished:^(NSNumber * _Nonnull subscriptionId) {
        NSLog(@"subscriptionEstablished %@", subscriptionId);
        invokeMethodBlockGet([Global externalChannel], createFlutterCallPath(deviceControllerHost, @"SubscriptionCallback/onSubscriptionEstablished"), toJSONStringFromObject(@{
            jsonKeyHandle: handle,
            @"subscriptionCallbackPoint": callbackId,
            @"subscriptionId": subscriptionId
        }));
    } resubscriptionScheduled:nil];
    return createFlutterRequestResultWithCode(0, @{});
}

static NSString * readRequest(NSString * params) {
    NSDictionary *jsonObject = parseJSONString(params);
    NSString *handle = requestJsonValueNotNull(jsonObject, jsonKeyHandle);
    MTRDeviceController *deviceController = getMTRDeviceController(handle);
    NSString *callbackId = requestJsonValueNotNull(jsonObject, @"callbackHandle");
    NSNumber *nodeId = requestJsonValueNotNull(jsonObject, @"nodeId");
    NSArray * attributePathsJson = [jsonObject objectForKey:@"attributePaths"];
    NSArray * eventPathsJson = [jsonObject objectForKey:@"eventPathsJson"];
    NSNumber * isFabricFiltered = [jsonObject objectForKey:@"isFabricFiltered"];
    NSNumber * imTimeoutMs = [jsonObject objectForKey:@"imTimeoutMs"];
    NSNumber * connectContext = [jsonObject objectForKey:@"connectContext"];
    NSNumber * eventMin = [jsonObject objectForKey:@"eventMin"];
    
    FlutterDeviceController *fdc = [controls objectForKey:handle];
    MTRBaseDevice* baseDevice = getBaseDevice(fdc, nodeId, [connectContext isEqual:[NSNull null]] ? nil : connectContext);
    if (baseDevice == nil) {
        return createFlutterRequestResultWithCode(1, @{});
    }
    
    NSMutableArray * attributePaths = nil;
    if (![attributePathsJson isEqual:[NSNull null]]) {
        attributePaths = [NSMutableArray array];
        for (NSUInteger i = 0; i < attributePathsJson.count; i++) {
            NSDictionary * attributePath = attributePathsJson[i];
            NSNumber * endpointId = [[attributePath objectForKey:@"endpointId"] objectForKey:@"id"];
            NSNumber * clusterId = [[attributePath objectForKey:@"clusterId"] objectForKey:@"id"];
            NSNumber * attributeId = [[attributePath objectForKey:@"attributeId"] objectForKey:@"id"];
            [attributePaths addObject:[MTRAttributeRequestPath requestPathWithEndpointID:endpointId clusterID:clusterId attributeID:attributeId]];
        }
    }
    NSMutableArray * eventPaths = nil;
    if (![eventPathsJson isEqual:[NSNull null]]) {
        eventPaths = [NSMutableArray array];
        for (NSUInteger i = 0; i < eventPathsJson.count; i++) {
            NSDictionary * eventPath = eventPaths[i];
            NSNumber * endpointId = [[eventPath objectForKey:@"endpointId"] objectForKey:@"id"];
            NSNumber * clusterId = [[eventPath objectForKey:@"clusterId"] objectForKey:@"id"];
            NSNumber * eventId = [[eventPath objectForKey:@"eventId"] objectForKey:@"id"];
            [eventPaths addObject:[MTREventRequestPath requestPathWithEndpointID:endpointId clusterID:clusterId eventID:eventId]];
        }
    }
    
    MTRReadParams * readParams = [MTRReadParams alloc];
    readParams.fabricFiltered = isFabricFiltered;
    readParams.minEventNumber = eventMin;
    [baseDevice readAttributePaths:attributePaths eventPaths:eventPaths params:readParams queue:connectDeviceQueue completion:^(NSArray<NSDictionary<NSString *,id> *> * _Nullable values, NSError * _Nullable error) {
        @try {
            if (error) {
                // failed callback
                invokeMethodBlockGet([Global externalChannel], createFlutterCallPath(deviceControllerHost, @"ReportCallback/onError"), toJSONStringFromObject(@{
                    jsonKeyHandle: handle,
                    @"reportCallbackPoint": callbackId,
                    @"error": [error localizedDescription]
                }));
            } else {
                FlutterMatterLog([[NSString alloc] initWithFormat:@"Call flutter readResult values %@", values]);
                // success callback
                invokeMethodBlockGet([Global externalChannel], createFlutterCallPath(deviceControllerHost, @"ReportCallback/onReport"), toJSONStringFromObject(@{
                    jsonKeyHandle: handle,
                    @"reportCallbackPoint": callbackId,
                    @"nodeState": values == nil ? [NSNull null] : convertNodeStateJsonFormat(values)
                }));
            }
            invokeMethodBlockGet([Global externalChannel], createFlutterCallPath(deviceControllerHost, @"ReportCallback/onDone"), toJSONStringFromObject(@{
                jsonKeyHandle: handle,
                @"reportCallbackPoint": callbackId
            }));
        } @catch (NSException *exception) {
            FlutterMatterLog([[NSString alloc] initWithFormat:@"Call flutter readResult exception %@", [exception reason]]);
        } @finally {
            
        }
    }];
    
    return createFlutterRequestResultWithCode(0, @{});
}

static NSString * writeRequest(NSString * params) {
    NSDictionary *jsonObject = parseJSONString(params);
    NSString *handle = requestJsonValueNotNull(jsonObject, jsonKeyHandle);
    MTRDeviceController *deviceController = getMTRDeviceController(handle);
    NSString *callbackId = requestJsonValueNotNull(jsonObject, @"callbackHandle");
    
    NSArray * attributeListJson  = requestJsonValueNotNull(jsonObject, @"attributeList");
    NSNumber *nodeId = requestJsonValueNotNull(jsonObject, @"nodeId");
    NSNumber * imTimeoutMs = [jsonObject objectForKey:@"imTimeoutMs"];
    NSNumber * connectContext = [jsonObject objectForKey:@"connectContext"];
    NSNumber * timedRequestTimeoutMs = [jsonObject objectForKey:@"timedRequestTimeoutMs"];
    
    NSMutableArray * attributePaths = [NSMutableArray array];
    for (NSDictionary * element in attributeListJson) {
        NSNumber * endpointId = [[element objectForKey:@"endpointId"] objectForKey:@"id"];
        NSNumber * clusterId = [[element objectForKey:@"clusterId"] objectForKey:@"id"];
        NSNumber * attributeId = [[element objectForKey:@"attributeId"] objectForKey:@"id"];
        NSData * tlv = toByteArrayFromJSONArray(requestJsonValueNotNull(element, @"tlv"));
        
        [attributePaths addObject: [[MTRAttributeWriteRequest alloc] initWithEndpointID:endpointId clusterID:clusterId attributeID:attributeId tlv:tlv]];
    }
    
    FlutterDeviceController *fdc = [controls objectForKey:handle];
    MTRBaseDevice* baseDevice = getBaseDevice(fdc, nodeId, [connectContext isEqual:[NSNull null]] ? nil : connectContext);
    if (baseDevice == nil) {
        return createFlutterRequestResultWithCode(1, @{});
    }
    
    [baseDevice writeAttributeRequests:attributePaths timedWriteTimeout:timedRequestTimeoutMs imTimeoutMs:imTimeoutMs queue:connectDeviceQueue completion:^(NSArray<NSDictionary<NSString *,id> *> * _Nullable values, NSError * _Nullable error) {
        @try {
            NSNumber * resultEndPointId = @(0);
            NSNumber * resultClusterId = @(0);
            NSNumber * resultCommandId = @(0);
            if (values != nil && [values count] > 0) {
                NSDictionary<NSString *,id> * dictionary = [values objectAtIndex:0];
                id commandPath = [dictionary objectForKey:@"commandPath"];
                if (![commandPath isEqual:[NSNull null]] && [commandPath isKindOfClass:[MTRCommandPath class]]) {
                    MTRCommandPath * cp = commandPath;
                    resultEndPointId = [cp endpoint];
                    resultClusterId = [cp cluster];
                    resultCommandId = [cp command];
                }
            }
            if (error) {
                invokeMethodBlockGet([Global externalChannel], createFlutterCallPath(deviceControllerHost, @"WriteAttributesCallback/onError"), toJSONStringFromObject(@{
                    jsonKeyHandle: handle,
                    @"writeAttributesCallbackPoint": callbackId,
                    @"error": [error localizedDescription],
                    @"attributePath": @{
                        @"endpointId": @{
                            @"id": resultEndPointId
                        },
                        @"clusterId": @{
                            @"id": resultClusterId
                        },
                        @"commandId": @{
                            @"id": resultCommandId
                        },
                    }
                }));
            } else {
                invokeMethodBlockGet([Global externalChannel], createFlutterCallPath(deviceControllerHost, @"WriteAttributesCallback/onResponse"), toJSONStringFromObject(@{
                    jsonKeyHandle: handle,
                    @"writeAttributesCallbackPoint": callbackId,
//                    @"error": [error localizedDescription],
                    @"attributePath": @{
                        @"endpointId": @{
                            @"id": resultEndPointId
                        },
                        @"clusterId": @{
                            @"id": resultClusterId
                        },
                        @"attributeId": @{
                            @"id": resultCommandId
                        },
                    }
                }));
            }
            invokeMethodBlockGet([Global externalChannel], createFlutterCallPath(deviceControllerHost, @"WriteAttributesCallback/onDone"), toJSONStringFromObject(@{
                jsonKeyHandle: handle,
                @"writeAttributesCallbackPoint": callbackId,
            }));
        } @catch (NSException *exception) {
            FlutterMatterLog([[NSString alloc] initWithFormat:@"Call flutter writeAttribute exception %@", [exception reason]]);
        } @finally {
            
        }
    }];
    
    return createFlutterRequestResultWithCode(0, @{});
}

static NSString * openPairingWindowWithPIN(NSString * params) {
    NSDictionary *jsonObject = parseJSONString(params);
    NSString *handle = requestJsonValueNotNull(jsonObject, jsonKeyHandle);
//    MTRDeviceController *deviceController = getMTRDeviceController(handle);
    NSString * callbackId = requestJsonValueNotNull(jsonObject, @"callbackHandle");
    NSNumber * duration = requestJsonValueNotNull(jsonObject, @"duration");
    NSNumber * discriminator = requestJsonValueNotNull(jsonObject, @"discriminator");
    NSNumber * setupPIN = requestJsonValueNotNull(jsonObject, @"setupPIN");
    NSNumber * connectContext = requestJsonValueNotNull(jsonObject, @"connectContext");
    
    FlutterDeviceController *fdc = [controls objectForKey:handle];
    MTRBaseDevice* baseDevice = [fdc deviceInfoForNodeID:[connectContext intValue]];;
    if (baseDevice == nil) {
        return createFlutterRequestResultWithCode(1, @{@"msg": [[NSString alloc] initWithFormat:@"Not found connectDevice by %@", connectContext]});
    }
    [baseDevice openCommissioningWindowWithSetupPasscode:setupPIN discriminator:discriminator duration:duration queue:connectDeviceQueue completion:^(MTRSetupPayload * _Nullable payload, NSError * _Nullable error) {
        @try {
            if (error || payload == nil) {
                invokeMethodBlockGet([Global externalChannel], createFlutterCallPath(deviceControllerHost, @"OpenCommissioningCallback/onError"), toJSONStringFromObject(@{
                    jsonKeyHandle: handle,
                    @"callbackHandle": callbackId,
                    @"status": error == nil ? @(0) : @([error code]),
                    @"connectContext": connectContext
                }));
            } else {
                invokeMethodBlockGet([Global externalChannel], createFlutterCallPath(deviceControllerHost, @"OpenCommissioningCallback/onSuccess"), toJSONStringFromObject(@{
                    jsonKeyHandle: handle,
                    @"callbackHandle": callbackId,
                    @"connectContext": connectContext,
                    @"manualPairingCode": [payload manualEntryCode],
                    @"qrCode": [payload qrCodeString]
                }));
            }
        } @catch (NSException *exception) {
            FlutterMatterLog([[NSString alloc] initWithFormat:@"Call flutter openPairingWindowWithPIN exception %@", [exception reason]]);
        } @finally {
            
        }
    }];
    
    return createFlutterRequestResultWithCode(0, @{});
}

static NSString * getFabricIndex(NSString * params) {
    NSDictionary *jsonObject = parseJSONString(params);
    NSString *handle = requestJsonValueNotNull(jsonObject, jsonKeyHandle);
    MTRDeviceController *deviceController = getMTRDeviceController(handle);
    return createFlutterRequestResultWithCode(0, @{@"data": [NSNumber numberWithLongLong:[deviceController getFabricIndex]]});
}

static NSString * unSubscribe(NSString * params) {
    NSDictionary *jsonObject = parseJSONString(params);
    NSString *handle = requestJsonValueNotNull(jsonObject, jsonKeyHandle);
    MTRDeviceController *deviceController = getMTRDeviceController(handle);
    NSNumber *nodeId = [jsonObject objectForKey:@"nodeId"];
    NSNumber *fabricIndex = [jsonObject objectForKey:@"fabricIndex"];
    NSNumber *subscriptionId = [jsonObject objectForKey:@"subscriptionId"];
    MTRBaseDevice *device = [MTRBaseDevice deviceWithNodeID:nodeId controller:deviceController];
    BOOL success = [device shutdownSubscription:subscriptionId scopedNodeId:nodeId];
    return createFlutterRequestResultWithCode(0, @{@"data": @(success)});
}

void onDeviceControlCall(NSString *path, NSString *params,
                         FlutterResult result) {
    FlutterMatterLog(
        [NSString stringWithFormat:@"onDeviceControlCall path: %@ params: %@",
                                   path, params]);
    if (controls == nil) {
        controls = [[NSMutableDictionary alloc] init];
    }
    if (onNOCChainGenerationCompletes == nil) {
        onNOCChainGenerationCompletes = [[NSMutableDictionary alloc] init];
    }
    if (connectDeviceQueue == nil) {
        connectDeviceQueue = dispatch_queue_create("connectDeviceQueue", DISPATCH_QUEUE_SERIAL);
    }
    dispatch_async(dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_DEFAULT, 0), ^{
        dispatch_async([Global backgroundSerialQueue], ^() {
          NSString *resultData = nil;
          NSException *resultException = nil;
          @try {
              if ([path isEqualToString:@"/new"]) {
                  resultData = newDeviceControllerCall(params);
              } else if ([path isEqualToString:@"/createRootCertificate"]) {
                  resultData = createRootCertificate(params);
              } else if ([path isEqualToString:@"/setNocChainIssuer"]) {
                  resultData = setNocChainIssuer(params);
              } else if ([path isEqualToString:@"/setCompletionListener"]) {
//                  resultData = setCompletionListener(params);
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
              FlutterMatterLog([[NSString alloc] initWithFormat:@"onDeviceControlCall %@ Exception %@", path, [exception reason]]);
              resultException = exception;
          } @finally {
          }

          // callback run on main
          dispatch_sync(dispatch_get_main_queue(), ^() {
            if (resultException) {
                result([FlutterError errorWithCode:@"DeviceControlCallException"
                                           message:[resultException reason]
                                           details:nil]);
            } else if (resultData) {
                result(resultData);
            } else {
                result(FlutterMethodNotImplemented);
            }
          });
        });
    });
}

#pragma clang diagnostic pop
