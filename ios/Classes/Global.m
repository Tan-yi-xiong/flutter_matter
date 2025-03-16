
#import "Global.h"

static dispatch_queue_t _backgroundSerialQueue = nil;

static FlutterMethodChannel* _channel = nil;

@implementation Global : NSObject

// 获取全局串行队列
+ (dispatch_queue_t)backgroundSerialQueue {
    return _backgroundSerialQueue;
}

+ (void)setBackgroundSerialQueue:(dispatch_queue_t)queue {
    if (_backgroundSerialQueue != nil) {
        @throw  [NSException exceptionWithName:@"setBackgroundSerialQueueException"
                                                reason:@"backgroundSerialQueue has been set"
                                              userInfo:nil];
    }
    _backgroundSerialQueue = queue;
}

+ (FlutterMethodChannel *)externalChannel {
    return _channel;
}

+ (void)setExternalChannel:(FlutterMethodChannel *)externalChannel {
    if (_channel != nil) {
        @throw  [NSException exceptionWithName:@"setFlobalExternalChannelException"
                                                reason:@"externalChannel has been set"
                                              userInfo:nil];
    }
    _channel = externalChannel;
}

@end
