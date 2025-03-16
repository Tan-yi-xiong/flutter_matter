#import "Flutter/Flutter.h"

@interface Global : NSObject

+ (dispatch_queue_t)backgroundSerialQueue;

+ (void)setBackgroundSerialQueue:(dispatch_queue_t)queue;

+ (FlutterMethodChannel *)externalChannel;

+ (void)setExternalChannel:(FlutterMethodChannel *)externalChannel;

@end
