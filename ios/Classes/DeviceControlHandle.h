#import <Flutter/Flutter.h>
#import <Matter/Matter.h>

@interface KeypairWarp : NSObject <MTRKeypair>

@property (nonatomic, strong) NSString *handle;

- (instancetype)initWithHandle:(NSString *)handle; 

@end

@interface MTRNOCChainIssuerWarp : NSObject <MTRNOCChainIssuer>

@property (nonatomic, strong) NSString *handle;

- (instancetype)initWithHandle:(NSString *)handle;

@end

@interface PairingDelegateWarp : NSObject<MTRDevicePairingDelegate>

@property (nonatomic, strong) NSString *handle;
@property (nonatomic, strong) MTRCommissioningParameters *commissioningParameters;
@property (nonatomic, strong) MTRDeviceController *deviceController;
@property (nonatomic, strong) NSNumber *deviceId;

- (instancetype)initWithHandle:(NSString *)handle commissioningParameters:(MTRCommissioningParameters *)commissioningParameters deviceController:(MTRDeviceController *)deviceController deviceId:(NSNumber *)deviceId;

@end


void onDeviceControlCall(NSString * path, NSString * params, FlutterResult result);
