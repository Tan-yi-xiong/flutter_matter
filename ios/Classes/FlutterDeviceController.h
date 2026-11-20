
#import "FlutterControllerParams.h"
#import <Foundation/Foundation.h>
#import <ZGMatter/ZGMatter.h>

NS_ASSUME_NONNULL_BEGIN

@interface FlutterDeviceController : NSObject
@property(nonatomic, strong) ZGMTRDeviceController *controller;
@property(nonatomic, strong) FlutterControllerParams *controllerParams;

- (void)addConnectedDeviceWithNodeID:(uint64_t)nodeID deviceInfo:(ZGMTRBaseDevice *)deviceInfo;
- (void)removeDeviceWithNodeID:(uint64_t)nodeID;
- (nullable ZGMTRBaseDevice *)deviceInfoForNodeID:(uint64_t)nodeID;


- (instancetype)initWithController:(nonnull ZGMTRDeviceController *)controller
                  controllerParams:(nonnull FlutterControllerParams *)controllerParams;

@end

NS_ASSUME_NONNULL_END
