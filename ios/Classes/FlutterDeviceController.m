

#import "FlutterDeviceController.h"
#include <Matter/Matter.h>
#include <Foundation/Foundation.h>
#import "FlutterControllerParams.h"

@interface FlutterDeviceController ()
  @property(nonatomic, strong) NSMutableDictionary *connectedDevices;
@end

@implementation FlutterDeviceController


- (instancetype)initWithController:(nonnull MTRDeviceController *)controller
                  controllerParams:(nonnull FlutterControllerParams *)controllerParams {
    self = [super init]; // 调用父类的初始化方法
    if (self) {
        // 使用传递的参数初始化属性
        _controller = controller;
        _controllerParams = controllerParams;
        _connectedDevices = [[NSMutableDictionary alloc] init];
    }
    return self;
}


- (void)addConnectedDeviceWithNodeID:(uint64_t)nodeID deviceInfo:(MTRBaseDevice *)deviceInfo {
  @synchronized (self){
    [_connectedDevices setObject:deviceInfo forKey:@(nodeID)];
  }
  
}

- (void)removeDeviceWithNodeID:(uint64_t)nodeID {
  @synchronized (self){
    [_connectedDevices removeObjectForKey:@(nodeID)];
  }
}

- (nullable MTRBaseDevice *)deviceInfoForNodeID:(uint64_t)nodeID {
  @synchronized (self){
    return [_connectedDevices objectForKey:@(nodeID)];
  }
}

@end
