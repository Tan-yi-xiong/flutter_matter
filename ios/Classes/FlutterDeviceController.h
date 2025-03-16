
#import "FlutterControllerParams.h"
#import <Foundation/Foundation.h>
#import <Matter/Matter.h>

@interface FlutterDeviceController : NSObject
@property(nonatomic, strong) MTRDeviceController *controller;
@property(nonatomic, strong) FlutterControllerParams *controllerParams;

- (void)addConnectedDeviceWithNodeID:(uint64_t)nodeID deviceInfo:(MTRBaseDevice *)deviceInfo;
- (void)removeDeviceWithNodeID:(uint64_t)nodeID;
- (nullable MTRBaseDevice *)deviceInfoForNodeID:(uint64_t)nodeID;


- (instancetype)initWithController:(nonnull MTRDeviceController *)controller
                  controllerParams:(nonnull FlutterControllerParams *)controllerParams;

@end
