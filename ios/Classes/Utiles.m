#import "Utiles.h"

#include <CoreFoundation/CoreFoundation.h>
#include <math.h>

NSString * const FlutterMatterErrorInvalidArguments = @"invalidArguments";
NSString * const FlutterMatterErrorInvalidMethod = @"invalidMethod";
NSString * const FlutterMatterErrorUnsupportedHost = @"unsupportedHost";
NSString * const FlutterMatterErrorMethodNotImplemented = @"methodNotImplemented";
NSString * const FlutterMatterErrorCallbackFailed = @"callbackDeliveryFailed";
NSString * const FlutterMatterErrorInternal = @"internalError";
NSString * const FlutterMatterOnBLECallExceptionCode = @"onBLECallException";
NSString * const FlutterMatterOnOnboardingCallExceptionCode = @"onOnboardingCallException";
NSString * const FlutterMatterDeviceControlCallExceptionCode = @"DeviceControlCallException";

@implementation FlutterMatterArgumentException

- (instancetype)initWithArgumentName:(NSString *)argumentName
                              message:(NSString *)message {
    self = [super initWithName:@"FlutterMatterArgumentException"
                       reason:message
                     userInfo:@{@"argumentName": argumentName ?: @"arguments"}];
    if (self) {
        _argumentName = [argumentName copy] ?: @"arguments";
    }
    return self;
}

@end

static void FlutterMatterRaiseInvalidArgument(NSString *name, NSString *message) {
    @throw [[FlutterMatterArgumentException alloc] initWithArgumentName:name
                                                                 message:message];
}

static BOOL FlutterMatterIsBooleanNumber(NSNumber *number) {
    return CFGetTypeID((__bridge CFTypeRef)number) == CFBooleanGetTypeID();
}

static id FlutterMatterJSONValue(NSDictionary *dictionary,
                                 NSString *key,
                                 BOOL required) {
    if (![dictionary isKindOfClass:[NSDictionary class]]) {
        FlutterMatterRaiseInvalidArgument(@"arguments",
                                          @"Request arguments must be a JSON object.");
    }

    id value = dictionary[key];
    if (value == nil || value == [NSNull null]) {
        if (required) {
            FlutterMatterRaiseInvalidArgument(key, @"Missing required argument.");
        }
        return nil;
    }
    return value;
}

id FlutterMatterOptionalJSONValue(NSDictionary *dictionary, NSString *key) {
    return FlutterMatterJSONValue(dictionary, key, NO);
}

id FlutterMatterRequiredJSONValue(NSDictionary *dictionary, NSString *key) {
    return FlutterMatterJSONValue(dictionary, key, YES);
}

NSString *FlutterMatterRequiredString(NSDictionary *dictionary, NSString *key) {
    id value = FlutterMatterRequiredJSONValue(dictionary, key);
    if (![value isKindOfClass:[NSString class]]) {
        FlutterMatterRaiseInvalidArgument(key, @"Expected a string.");
    }
    return (NSString *)value;
}

NSNumber *FlutterMatterRequiredNumber(NSDictionary *dictionary, NSString *key) {
    id value = FlutterMatterRequiredJSONValue(dictionary, key);
    if (![value isKindOfClass:[NSNumber class]] || FlutterMatterIsBooleanNumber(value)) {
        FlutterMatterRaiseInvalidArgument(key, @"Expected a number.");
    }
    return (NSNumber *)value;
}

NSNumber *FlutterMatterRequiredBoolean(NSDictionary *dictionary, NSString *key) {
    id value = FlutterMatterRequiredJSONValue(dictionary, key);
    if (![value isKindOfClass:[NSNumber class]] || !FlutterMatterIsBooleanNumber(value)) {
        FlutterMatterRaiseInvalidArgument(key, @"Expected a boolean.");
    }
    return (NSNumber *)value;
}

NSDictionary *FlutterMatterRequiredDictionary(NSDictionary *dictionary, NSString *key) {
    id value = FlutterMatterRequiredJSONValue(dictionary, key);
    if (![value isKindOfClass:[NSDictionary class]]) {
        FlutterMatterRaiseInvalidArgument(key, @"Expected an object.");
    }
    return (NSDictionary *)value;
}

NSArray *FlutterMatterRequiredArray(NSDictionary *dictionary, NSString *key) {
    id value = FlutterMatterRequiredJSONValue(dictionary, key);
    if (![value isKindOfClass:[NSArray class]]) {
        FlutterMatterRaiseInvalidArgument(key, @"Expected an array.");
    }
    return (NSArray *)value;
}

NSString *FlutterMatterOptionalString(NSDictionary *dictionary, NSString *key) {
    id value = FlutterMatterOptionalJSONValue(dictionary, key);
    if (value == nil) {
        return nil;
    }
    if (![value isKindOfClass:[NSString class]]) {
        FlutterMatterRaiseInvalidArgument(key, @"Expected a string.");
    }
    return (NSString *)value;
}

NSNumber *FlutterMatterOptionalNumber(NSDictionary *dictionary, NSString *key) {
    id value = FlutterMatterOptionalJSONValue(dictionary, key);
    if (value == nil) {
        return nil;
    }
    if (![value isKindOfClass:[NSNumber class]] || FlutterMatterIsBooleanNumber(value)) {
        FlutterMatterRaiseInvalidArgument(key, @"Expected a number.");
    }
    return (NSNumber *)value;
}

NSNumber *FlutterMatterOptionalBoolean(NSDictionary *dictionary, NSString *key) {
    id value = FlutterMatterOptionalJSONValue(dictionary, key);
    if (value == nil) {
        return nil;
    }
    if (![value isKindOfClass:[NSNumber class]] || !FlutterMatterIsBooleanNumber(value)) {
        FlutterMatterRaiseInvalidArgument(key, @"Expected a boolean.");
    }
    return (NSNumber *)value;
}

NSDictionary *FlutterMatterOptionalDictionary(NSDictionary *dictionary, NSString *key) {
    id value = FlutterMatterOptionalJSONValue(dictionary, key);
    if (value == nil) {
        return nil;
    }
    if (![value isKindOfClass:[NSDictionary class]]) {
        FlutterMatterRaiseInvalidArgument(key, @"Expected an object.");
    }
    return (NSDictionary *)value;
}

NSArray *FlutterMatterOptionalArray(NSDictionary *dictionary, NSString *key) {
    id value = FlutterMatterOptionalJSONValue(dictionary, key);
    if (value == nil) {
        return nil;
    }
    if (![value isKindOfClass:[NSArray class]]) {
        FlutterMatterRaiseInvalidArgument(key, @"Expected an array.");
    }
    return (NSArray *)value;
}

NSData *FlutterMatterByteArrayFromJSONValue(id value, NSString *fieldName) {
    if (![value isKindOfClass:[NSArray class]]) {
        FlutterMatterRaiseInvalidArgument(fieldName, @"Expected an array of bytes.");
    }

    NSMutableData *bytes = [NSMutableData dataWithCapacity:((NSArray *)value).count];
    for (id item in (NSArray *)value) {
        if (![item isKindOfClass:[NSNumber class]] || FlutterMatterIsBooleanNumber(item)) {
            FlutterMatterRaiseInvalidArgument(fieldName, @"Each byte must be a number.");
        }
        NSNumber *number = (NSNumber *)item;
        const double byteValue = number.doubleValue;
        if (!isfinite(byteValue) || byteValue < 0 || byteValue > 255 || byteValue != floor(byteValue)) {
            FlutterMatterRaiseInvalidArgument(fieldName, @"Each byte must be an integer from 0 to 255.");
        }
        uint8_t byte = (uint8_t)number.unsignedIntValue;
        [bytes appendBytes:&byte length:1];
    }
    return [bytes copy];
}

NSData *FlutterMatterRequiredByteArray(NSDictionary *dictionary, NSString *key) {
    return FlutterMatterByteArrayFromJSONValue(FlutterMatterRequiredJSONValue(dictionary, key), key);
}

void FlutterMatterLog(NSString *msg) {
    NSLog(@"[FlutterMatter] %@", msg ?: @"");
}

NSString *createFlutterCallPath(NSString *host, NSString *path) {
    return [NSString stringWithFormat:@"//%@/%@", host ?: @"", path ?: @""];
}

NSString *createCallFlutterExceptionMessage(NSString *functionName) {
    return [NSString stringWithFormat:@"call flutter %@ failed", functionName ?: @"callback"];
}

id requestJsonValueNotNull(NSDictionary *dictionary, NSString *key) {
    return FlutterMatterRequiredJSONValue(dictionary, key);
}

NSDictionary *FlutterMatterParseJSONObject(NSString *jsonString) {
    if (![jsonString isKindOfClass:[NSString class]]) {
        FlutterMatterRaiseInvalidArgument(@"arguments",
                                          @"Request arguments must be a JSON object string.");
    }

    NSData *jsonData = [jsonString dataUsingEncoding:NSUTF8StringEncoding];
    if (jsonData == nil) {
        FlutterMatterRaiseInvalidArgument(@"arguments", @"Request arguments are not valid UTF-8.");
    }

    NSError *error = nil;
    id jsonObject = [NSJSONSerialization JSONObjectWithData:jsonData options:0 error:&error];
    if (jsonObject == nil || ![jsonObject isKindOfClass:[NSDictionary class]]) {
        FlutterMatterLog(@"json.parse failed");
        FlutterMatterRaiseInvalidArgument(@"arguments",
                                          @"Request arguments must be a JSON object.");
    }
    return (NSDictionary *)jsonObject;
}

NSDictionary *parseJSONString(NSString *jsonString) {
    return FlutterMatterParseJSONObject(jsonString);
}

NSString *toJSONStringFromObject(id object) {
    if (![NSJSONSerialization isValidJSONObject:object]) {
        @throw [NSException exceptionWithName:@"FlutterMatterEncodingException"
                                       reason:@"Native callback payload is not JSON serializable."
                                     userInfo:nil];
    }

    NSError *error = nil;
    NSData *jsonData = [NSJSONSerialization dataWithJSONObject:object
                                                       options:NSJSONWritingPrettyPrinted
                                                         error:&error];
    if (jsonData == nil || error != nil) {
        FlutterMatterLogNSError(@"json.encode", error);
        @throw [NSException exceptionWithName:@"FlutterMatterEncodingException"
                                       reason:@"Native callback payload could not be encoded."
                                     userInfo:nil];
    }
    return [[NSString alloc] initWithData:jsonData encoding:NSUTF8StringEncoding];
}

NSString *createFlutterRequestResultWithCode(NSInteger code, NSDictionary *jsonData) {
    return toJSONStringFromObject(@{
        @"code": @(code),
        @"jsonData": jsonData ?: @{},
    });
}

NSData *toByteArrayFromJSONArray(NSArray *jsonArray) {
    return FlutterMatterByteArrayFromJSONValue(jsonArray, @"bytes");
}

NSString *invokeMethodBlockGet(FlutterMethodChannel *channel,
                               NSString *method,
                               NSString *arguments) {
    if (channel == nil) {
        @throw [NSException exceptionWithName:@"FlutterMatterCallbackDeliveryException"
                                       reason:@"Flutter callback channel is unavailable."
                                     userInfo:nil];
    }
    if ([NSThread isMainThread]) {
        @throw [NSException exceptionWithName:@"FlutterMatterCallbackDeliveryException"
                                       reason:@"Synchronous Flutter callbacks cannot run on the main thread."
                                     userInfo:nil];
    }

    dispatch_semaphore_t semaphore = dispatch_semaphore_create(0);
    __block NSString *callbackResult = nil;
    __block NSException *callbackException = nil;
    __block BOOL callbackFinished = NO;

    dispatch_async(dispatch_get_main_queue(), ^{
        @try {
            [channel invokeMethod:method arguments:arguments result:^(id result) {
                if (callbackFinished) {
                    FlutterMatterLog([NSString stringWithFormat:@"callback %@ completed more than once",
                                                                method ?: @""]);
                    return;
                }
                callbackFinished = YES;
                @try {
                    if ([result isKindOfClass:[FlutterError class]]) {
                        FlutterMatterRaiseInvalidArgument(@"callback", @"Flutter callback returned an error.");
                    }
                    if (![result isKindOfClass:[NSString class]]) {
                        FlutterMatterRaiseInvalidArgument(@"callback", @"Flutter callback returned an invalid response.");
                    }

                    NSDictionary *jsonObject = FlutterMatterParseJSONObject((NSString *)result);
                    NSNumber *code = FlutterMatterRequiredNumber(jsonObject, @"code");
                    if (code.integerValue != 0) {
                        FlutterMatterLog([NSString stringWithFormat:@"callback %@ failed with code %ld",
                                                                    method ?: @"", (long)code.integerValue]);
                        FlutterMatterRaiseInvalidArgument(@"callback", @"Flutter callback reported failure.");
                    }
                    id resultJson = FlutterMatterRequiredJSONValue(jsonObject, @"resultJson");
                    if (![resultJson isKindOfClass:[NSString class]]) {
                        FlutterMatterRaiseInvalidArgument(@"callback", @"Flutter callback resultJson must be a string.");
                    }
                    callbackResult = (NSString *)resultJson;
                } @catch (NSException *exception) {
                    callbackException = exception;
                } @finally {
                    dispatch_semaphore_signal(semaphore);
                }
            }];
        } @catch (NSException *exception) {
            callbackException = exception;
            dispatch_semaphore_signal(semaphore);
        }
    });

    if (dispatch_semaphore_wait(semaphore, dispatch_time(DISPATCH_TIME_NOW, (int64_t)(30 * NSEC_PER_SEC))) != 0) {
        @throw [NSException exceptionWithName:@"FlutterMatterCallbackTimeoutException"
                                       reason:@"Flutter callback did not complete in time."
                                     userInfo:nil];
    }
    if (callbackException != nil) {
        @throw callbackException;
    }
    return callbackResult;
}

NSMutableArray *nsDataToIntegerArray(NSData *data) {
    if (data == nil) {
        return [NSMutableArray array];
    }
    if (![data isKindOfClass:[NSData class]]) {
        FlutterMatterLog(@"nsDataToIntegerArray received a non-NSData value");
        return [NSMutableArray array];
    }

    NSMutableArray *intArray = [NSMutableArray arrayWithCapacity:data.length];
    const uint8_t *bytes = data.bytes;
    for (NSUInteger i = 0; i < data.length; i++) {
        [intArray addObject:@(bytes[i])];
    }
    return intArray;
}

SecKeyRef nsDataToSecKey(NSData *publicKeyData) {
    if (publicKeyData.length == 0) {
        FlutterMatterLog(@"Cannot create SecKey from empty key data");
        return NULL;
    }

    NSDictionary *attributes = @{
        (__bridge id)kSecAttrKeyType: (__bridge id)kSecAttrKeyTypeEC,
        (__bridge id)kSecAttrKeyClass: (__bridge id)kSecAttrKeyClassPublic,
        (__bridge id)kSecAttrKeySizeInBits: @(256),
    };
    CFErrorRef error = NULL;
    SecKeyRef key = SecKeyCreateWithData((__bridge CFDataRef)publicKeyData,
                                         (__bridge CFDictionaryRef)attributes,
                                         &error);
    if (error != NULL) {
        FlutterMatterLogNSError(@"security.createPublicKey", (__bridge NSError *)error);
        CFRelease(error);
    }
    return key;
}

FlutterError *FlutterMatterFlutterError(NSString *code,
                                        NSString *message,
                                        NSDictionary<NSString *, id> *details) {
    return [FlutterError errorWithCode:code ?: FlutterMatterErrorInternal
                               message:message ?: @"Matter operation failed."
                               details:details ?: @{}];
}

NSString *FlutterMatterSafeNSErrorSummary(NSError *error) {
    if (error == nil) {
        return @"No error";
    }

    // Domain and code are stable and safe. localizedDescription and userInfo
    // can contain setup payloads, credentials, device values, or file paths.
    return [NSString stringWithFormat:@"%@ (code %ld)",
                                      error.domain ?: @"Matter",
                                      (long)error.code];
}

NSString *FlutterMatterSafeExceptionSummary(NSException *exception) {
    if ([exception isKindOfClass:[FlutterMatterArgumentException class]]) {
        FlutterMatterArgumentException *argumentException = (FlutterMatterArgumentException *)exception;
        return [NSString stringWithFormat:@"FlutterMatterArgumentException (%@)",
                                          argumentException.argumentName];
    }
    return exception.name ?: @"Native exception";
}

void FlutterMatterLogNSError(NSString *context, NSError *error) {
    FlutterMatterLog([NSString stringWithFormat:@"%@ failed: %@", context ?: @"native operation",
                                                              FlutterMatterSafeNSErrorSummary(error)]);
}

void FlutterMatterLogException(NSString *context, NSException *exception) {
    FlutterMatterLog([NSString stringWithFormat:@"%@ failed: %@", context ?: @"native callback",
                                                              FlutterMatterSafeExceptionSummary(exception)]);
}

FlutterError *FlutterMatterErrorForException(NSException *exception,
                                             NSString *fallbackCode,
                                             NSString *host,
                                             NSString *path) {
    NSMutableDictionary *details = [@{
        @"host": host ?: @"unknown",
        @"path": path ?: @"unknown",
    } mutableCopy];

    if ([exception isKindOfClass:[FlutterMatterArgumentException class]]) {
        FlutterMatterArgumentException *argumentException = (FlutterMatterArgumentException *)exception;
        details[@"category"] = @"invalid-argument";
        details[@"argument"] = argumentException.argumentName;
        return FlutterMatterFlutterError(FlutterMatterErrorInvalidArguments,
                                         [NSString stringWithFormat:@"Invalid request argument: %@.",
                                                                    argumentException.argumentName],
                                         details);
    }

    details[@"category"] = @"internal-error";
    details[@"exception"] = exception.name ?: @"Native exception";
    return FlutterMatterFlutterError(fallbackCode ?: FlutterMatterErrorInternal,
                                     [NSString stringWithFormat:@"%@ operation failed.", host ?: @"Matter"],
                                     details);
}

FlutterError *FlutterMatterUnknownPathError(NSString *host, NSString *path) {
    return FlutterMatterFlutterError(FlutterMatterErrorMethodNotImplemented,
                                     @"Unsupported MethodChannel method.",
                                     @{
                                         @"host": host ?: @"unknown",
                                         @"path": path ?: @"unknown",
                                         @"category": @"unsupported-method",
                                     });
}

FlutterError *FlutterMatterUnsupportedHostError(NSString *host) {
    return FlutterMatterFlutterError(FlutterMatterErrorUnsupportedHost,
                                     @"Unsupported MethodChannel host.",
                                     @{
                                         @"host": host ?: @"unknown",
                                         @"category": @"unsupported-host",
                                     });
}

@interface FlutterMatterResultSender () {
    FlutterResult _result;
    BOOL _completed;
}
@end

@implementation FlutterMatterResultSender

- (instancetype)initWithResult:(FlutterResult)result {
    self = [super init];
    if (self) {
        _result = [result copy];
        _completed = NO;
    }
    return self;
}

- (void)sendValue:(id)value {
    FlutterResult result = nil;
    @synchronized (self) {
        if (_completed) {
            FlutterMatterLog(@"ignored duplicate MethodChannel result");
            return;
        }
        _completed = YES;
        result = _result;
    }
    if (result == nil) {
        return;
    }

    id safeValue = value ?: [NSNull null];
    void (^deliver)(void) = ^{
        @try {
            result(safeValue);
        } @catch (NSException *exception) {
            FlutterMatterLogException(@"result.delivery", exception);
        }
    };
    if ([NSThread isMainThread]) {
        deliver();
    } else {
        dispatch_async(dispatch_get_main_queue(), deliver);
    }
}

- (void)sendError:(FlutterError *)error {
    [self sendValue:error ?: FlutterMatterFlutterError(FlutterMatterErrorInternal,
                                                        @"Matter operation failed.",
                                                        @{@"category": @"internal-error"})];
}

- (void)sendUnsupportedHost:(NSString *)host {
    [self sendError:FlutterMatterUnsupportedHostError(host)];
}

- (void)sendUnknownPathForHost:(NSString *)host path:(NSString *)path {
    [self sendError:FlutterMatterUnknownPathError(host, path)];
}

@end
