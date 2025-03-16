#include <Foundation/Foundation.h>
#include <Flutter/Flutter.h>

void FlutterMatterLog(NSString * msg);

NSString* createFlutterCallPath(NSString *host, NSString *path);

NSString* createCallFlutterExceptionMessage(NSString *functionName);

NSString* createFlutterRequestResultWithCode(NSInteger code, NSDictionary *jsonData);

id requestJsonValueNotNull(NSDictionary* dictionary, NSString *key);

NSData* toByteArrayFromJSONArray(NSArray *jsonArray);

// 将 JSON 字符串转换为 NSDictionary
NSDictionary* parseJSONString(NSString *jsonString);

// 将 NSDictionary 转换为 JSON 字符串
NSString* toJSONStringFromObject(id object);

NSString* invokeMethodBlockGet(FlutterMethodChannel *channel, NSString* method, NSString* arguments);

NSMutableArray* nsDataToIntegerArray(NSData* data);

SecKeyRef nsDataToSecKey(NSData *publicKeyData);
