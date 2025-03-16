
#include "FlutterControllerParams.h"

@implementation FlutterControllerParams : NSObject

- (instancetype)init:(NSInteger)fabricId
                udpListenPort:(NSInteger)udpListenPort
           controllerVendorId:(NSInteger)controllerVendorId
         failsafeTimerSeconds:(NSInteger)failsafeTimerSeconds
     caseFailsafeTimerSeconds:(NSInteger)caseFailsafeTimerSeconds
       attemptNetworkScanWiFi:(BOOL)attemptNetworkScanWiFi
     attemptNetworkScanThread:(BOOL)attemptNetworkScanThread
    skipCommissioningComplete:(BOOL)skipCommissioningComplete
                  countryCode:(NSString *)countryCode
       regulatoryLocationType:(NSInteger)regulatoryLocationType
              keypairDelegate:(id)keypairDelegate
              rootCertificate:(NSData *)rootCertificate
      intermediateCertificate:(NSData *)intermediateCertificate
       operationalCertificate:(NSData *)operationalCertificate
                          ipk:(NSData *)ipk
                 adminSubject:(NSInteger)adminSubject
     enableServerInteractions:(BOOL)enableServerInteractions
                     setupURL:(NSString *)setupURL
                       nodeId:(NSInteger)nodeId {

    self = [super init];
    if (self) {
        // 基本类型直接赋值
        _fabricId = fabricId;
        _udpListenPort = udpListenPort;
        _controllerVendorId = controllerVendorId;
        _failsafeTimerSeconds = failsafeTimerSeconds;
        _caseFailsafeTimerSeconds = caseFailsafeTimerSeconds;
        _attemptNetworkScanWiFi = attemptNetworkScanWiFi;
        _attemptNetworkScanThread = attemptNetworkScanThread;
        _skipCommissioningComplete = skipCommissioningComplete;
        _regulatoryLocationType = regulatoryLocationType;
        _adminSubject = adminSubject;
        _enableServerInteractions = enableServerInteractions;
        _nodeId = nodeId;

        // 对象类型需要做nil检查和默认值处理
        _countryCode = countryCode; // 如果countryCode为nil，则赋值空字符串
        _keypairDelegate = keypairDelegate ?: nil; // 如果keypairDelegate为nil，则赋值nil
        _rootCertificate = rootCertificate ?: nil;
        _intermediateCertificate = intermediateCertificate ?: nil;
        _operationalCertificate = operationalCertificate ?: nil;
        _ipk = ipk ?: nil;
        _setupURL = setupURL; // 如果setupURL为nil，则赋值空字符串
    }
    return self;
}


@end
