#import "FlutterMatterPlugin.h"
#include <Foundation/Foundation.h>
#import <ZGMatter/ZGMatter.h>
#import "Constants.h"
#import "DeviceControlHandle.h"
#import "DefaultsUtils.h"
#import "Global.h"
#import "BleHandle.h"
#import "Onboarding.h"
#import "Utiles.h"

void FlutterMatterShutdownActiveControllerAsync(void);
void FlutterMatterSetControllerLifecycleEnabled(BOOL enabled);
dispatch_queue_t FlutterMatterEnsureMatterQueue(void);

@implementation FlutterMatterPlugin

+ (void)registerWithRegistrar:(NSObject<FlutterPluginRegistrar>*)registrar {
  @try {
    FlutterMethodChannel* channel = [FlutterMethodChannel
        methodChannelWithName:@"flutter_matter"
              binaryMessenger:[registrar messenger]];
    FlutterMatterPlugin* instance = [[FlutterMatterPlugin alloc] init];
    [registrar addMethodCallDelegate:instance channel:channel];
    [Global setExternalChannel:channel];

    // Keep one process-wide Matter queue across engine re-registration.
    FlutterMatterEnsureMatterQueue();
    FlutterMatterSetControllerLifecycleEnabled(YES);

    // Start the process-wide factory once. Controllers are created only by
    // explicit Dart requests and remain owned by DeviceControlHandle.
    if (!ZGMTRInitializeControllerFactory()) {
      FlutterMatterLog(@"Matter controller factory initialization failed");
    }
  } @catch (NSException *exception) {
    FlutterMatterLogException(@"FlutterMatterPlugin.register", exception);
  }
}

- (void)detachFromEngineForRegistrar:(NSObject<FlutterPluginRegistrar>*)registrar {
  (void)registrar;
  FlutterMatterShutdownActiveControllerAsync();
}

- (void)handleMethodCall:(FlutterMethodCall*)call result:(FlutterResult)result {
  FlutterMatterResultSender *sender = [[FlutterMatterResultSender alloc] initWithResult:result];
  FlutterResult guardedResult = ^(id value) {
    [sender sendValue:value];
  };

  NSString *host = nil;
  NSString *path = nil;
  @try {
    if (![call.method isKindOfClass:[NSString class]] || call.method.length == 0) {
      [sender sendError:FlutterMatterFlutterError(FlutterMatterErrorInvalidMethod,
                                                   @"Method name is missing.",
                                                   @{@"category": @"invalid-method"})];
      return;
    }

    NSURLComponents *components = [NSURLComponents componentsWithString:call.method];
    host = components.host;
    path = components.path;
    if (host.length == 0 || path.length == 0) {
      [sender sendError:FlutterMatterFlutterError(FlutterMatterErrorInvalidMethod,
                                                   @"Method name must contain a host and path.",
                                                   @{@"category": @"invalid-method"})];
      return;
    }

    if (![call.arguments isKindOfClass:[NSString class]]) {
      [sender sendError:FlutterMatterFlutterError(FlutterMatterErrorInvalidArguments,
                                                   @"Request arguments must be a JSON object string.",
                                                   @{@"host": host,
                                                     @"path": path,
                                                     @"category": @"invalid-arguments"})];
      return;
    }

    NSString *normalizedHost = host.lowercaseString;
    if ([normalizedHost isEqualToString:deviceControllerHost.lowercaseString]) {
      onDeviceControlCall(path, (NSString *)call.arguments, guardedResult);
      return;
    }
    if ([normalizedHost isEqualToString:bleHost.lowercaseString]) {
      onBLECall(path, (NSString *)call.arguments, guardedResult);
      return;
    }
    if ([normalizedHost isEqualToString:OnboardingHost.lowercaseString]) {
      onOnboardingCall(path, (NSString *)call.arguments, guardedResult);
      return;
    }

    [sender sendUnsupportedHost:host];
  } @catch (NSException *exception) {
    FlutterMatterLogException(@"FlutterMatterPlugin.dispatch", exception);
    [sender sendError:FlutterMatterErrorForException(exception,
                                                     FlutterMatterErrorInternal,
                                                     host,
                                                     path)];
  }
}

@end
