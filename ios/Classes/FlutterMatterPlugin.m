#import "FlutterMatterPlugin.h"
#include <Foundation/Foundation.h>
#import <Matter/Matter.h>
#import "Constants.h"
#import "DeviceControlHandle.h"
#import "DefaultsUtils.h"
#import "Global.h"
#import "BleHandle.h"
#import "Onboarding.h"

@implementation FlutterMatterPlugin

+ (void)registerWithRegistrar:(NSObject<FlutterPluginRegistrar>*)registrar {
  FlutterMethodChannel* channel = [FlutterMethodChannel
      methodChannelWithName:@"flutter_matter"
            binaryMessenger:[registrar messenger]];
  FlutterMatterPlugin* instance = [[FlutterMatterPlugin alloc] init];
  [registrar addMethodCallDelegate:instance channel:channel];
  [Global setExternalChannel:channel];
    
  
 // 创建matter代码执行的线程队列
 [Global setBackgroundSerialQueue:dispatch_queue_create("Matter Thread queue", DISPATCH_QUEUE_SERIAL)];
    
 // 初始化库,
 InitializeMTR();
}

- (void)handleMethodCall:(FlutterMethodCall*)call result:(FlutterResult)result {
    NSURL *url = [NSURL URLWithString:call.method];
    if (url) {
        NSString *host = [url host];
        NSString *path = [url path];
        if ([[host lowercaseString] isEqualToString:[deviceControllerHost lowercaseString]]) {
            onDeviceControlCall(path, [call arguments], result);
            return;
        } else if ([[host lowercaseString] isEqualToString:[bleHost lowercaseString]]) {
            onBLECall(path, [call arguments], result);
            return;
        } else if ([[host lowercaseString] isEqualToString:[OnboardingHost lowercaseString]]) {
            onOnboardingCall(path, [call arguments], result);
            return;
        }
    }
  result(FlutterMethodNotImplemented);
  
}

@end
