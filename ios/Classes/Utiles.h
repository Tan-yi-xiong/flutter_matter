#include <Foundation/Foundation.h>
#include <Flutter/Flutter.h>
#include <Security/Security.h>

NS_ASSUME_NONNULL_BEGIN

/// Stable error codes used by the iOS MethodChannel bridge.  These values are
/// part of the integration contract and must not be changed casually.
extern NSString * const FlutterMatterErrorInvalidArguments;
extern NSString * const FlutterMatterErrorInvalidMethod;
extern NSString * const FlutterMatterErrorUnsupportedHost;
extern NSString * const FlutterMatterErrorMethodNotImplemented;
extern NSString * const FlutterMatterErrorCallbackFailed;
extern NSString * const FlutterMatterErrorInternal;
extern NSString * const FlutterMatterOnBLECallExceptionCode;
extern NSString * const FlutterMatterOnOnboardingCallExceptionCode;
extern NSString * const FlutterMatterDeviceControlCallExceptionCode;

/// Raised for caller-supplied arguments that are missing or have the wrong
/// type.  The exception deliberately carries only the argument name, never the
/// supplied value.
@interface FlutterMatterArgumentException : NSException

@property (nonatomic, copy, readonly) NSString *argumentName;

- (instancetype)initWithArgumentName:(NSString *)argumentName
                              message:(NSString *)message;

@end

void FlutterMatterLog(NSString * msg);

NSString* createFlutterCallPath(NSString *host, NSString *path);

NSString* createCallFlutterExceptionMessage(NSString *functionName);

NSString* createFlutterRequestResultWithCode(NSInteger code, NSDictionary *jsonData);

id requestJsonValueNotNull(NSDictionary* dictionary, NSString *key);

id _Nullable FlutterMatterOptionalJSONValue(NSDictionary *dictionary, NSString *key);
id FlutterMatterRequiredJSONValue(NSDictionary *dictionary, NSString *key);
NSString *FlutterMatterRequiredString(NSDictionary *dictionary, NSString *key);
NSNumber *FlutterMatterRequiredNumber(NSDictionary *dictionary, NSString *key);
NSNumber *FlutterMatterRequiredBoolean(NSDictionary *dictionary, NSString *key);
NSDictionary *FlutterMatterRequiredDictionary(NSDictionary *dictionary, NSString *key);
NSArray *FlutterMatterRequiredArray(NSDictionary *dictionary, NSString *key);
NSString * _Nullable FlutterMatterOptionalString(NSDictionary *dictionary, NSString *key);
NSNumber * _Nullable FlutterMatterOptionalNumber(NSDictionary *dictionary, NSString *key);
NSNumber * _Nullable FlutterMatterOptionalBoolean(NSDictionary *dictionary, NSString *key);
NSDictionary * _Nullable FlutterMatterOptionalDictionary(NSDictionary *dictionary, NSString *key);
NSArray * _Nullable FlutterMatterOptionalArray(NSDictionary *dictionary, NSString *key);
NSData *FlutterMatterRequiredByteArray(NSDictionary *dictionary, NSString *key);
NSData *FlutterMatterByteArrayFromJSONValue(id value, NSString *fieldName);

NSData* toByteArrayFromJSONArray(NSArray *jsonArray);

// 将 JSON 字符串转换为 NSDictionary
NSDictionary* parseJSONString(NSString *jsonString);
NSDictionary* FlutterMatterParseJSONObject(NSString *jsonString);

// 将 NSDictionary 转换为 JSON 字符串
NSString* toJSONStringFromObject(id object);

NSString* invokeMethodBlockGet(FlutterMethodChannel *channel, NSString* method, NSString* arguments);

NSMutableArray* nsDataToIntegerArray(NSData* data);

SecKeyRef _Nullable nsDataToSecKey(NSData *publicKeyData);

FlutterError *FlutterMatterFlutterError(NSString *code,
                                        NSString *message,
                                        NSDictionary<NSString *, id> *details);
FlutterError *FlutterMatterErrorForException(NSException *exception,
                                             NSString *fallbackCode,
                                             NSString *host,
                                             NSString *path);
FlutterError *FlutterMatterUnknownPathError(NSString *host, NSString *path);
FlutterError *FlutterMatterUnsupportedHostError(NSString *host);

NSString *FlutterMatterSafeNSErrorSummary(NSError *error);
NSString *FlutterMatterSafeExceptionSummary(NSException *exception);
void FlutterMatterLogNSError(NSString *context, NSError *error);
void FlutterMatterLogException(NSString *context, NSException *exception);

/// Sends at most one result to Flutter and always delivers it on the main
/// thread.  Use this wherever a native callback owns a FlutterResult.
@interface FlutterMatterResultSender : NSObject

- (instancetype)initWithResult:(FlutterResult)result;

- (void)sendValue:(id _Nullable)value;
- (void)sendError:(FlutterError *)error;
- (void)sendUnsupportedHost:(NSString *)host;
- (void)sendUnknownPathForHost:(NSString *)host path:(NSString *)path;

@end

NS_ASSUME_NONNULL_END
