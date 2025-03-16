
#import <Foundation/Foundation.h>

@interface FlutterControllerParams : NSObject

@property (nonatomic, assign) NSInteger fabricId;
@property (nonatomic, assign) NSInteger udpListenPort;
@property (nonatomic, assign) NSInteger controllerVendorId;
@property (nonatomic, assign) NSInteger failsafeTimerSeconds;
@property (nonatomic, assign) NSInteger caseFailsafeTimerSeconds;
@property (nonatomic, assign) BOOL attemptNetworkScanWiFi;
@property (nonatomic, assign) BOOL attemptNetworkScanThread;
@property (nonatomic, assign) BOOL skipCommissioningComplete;
@property (nonatomic, strong) NSString *countryCode;
@property (nonatomic, assign) NSInteger regulatoryLocationType;
@property (nonatomic, strong) id keypairDelegate;  // 可以根据实际需要定义类型
@property (nonatomic, strong) NSData *rootCertificate;  // 根据实际数据类型定义
@property (nonatomic, strong) NSData *intermediateCertificate; // 根据实际数据类型定义
@property (nonatomic, strong) NSData *operationalCertificate;  // 根据实际数据类型定义
@property (nonatomic, strong) NSData *ipk;  // 根据实际数据类型定义
@property (nonatomic, assign) NSInteger adminSubject;
@property (nonatomic, assign) BOOL enableServerInteractions;
@property (nonatomic, strong) NSString *setupURL;
@property (nonatomic, assign) NSInteger nodeId;

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
                         nodeId:(NSInteger)nodeId;

@end
