#import "Utiles.h"
#import "Flutter/Flutter.h"


void FlutterMatterLog(NSString * msg) {
    NSLog(@"[FlutterMatter] %@", msg);
}

NSString *createFlutterCallPath(NSString *host, NSString *path) {
    // 使用字符串拼接构建路径
    NSString *fullPath = [NSString stringWithFormat:@"//%@/%@", host, path];
    
    // 返回最终的路径字符串
    return fullPath;
}

NSString *createCallFlutterExceptionMessage(NSString *functionName) {
    return [NSString stringWithFormat:@"call flutter %@ failed", functionName];
}

id requestJsonValueNotNull(NSDictionary* dict, NSString *key) {
    id value = [dict objectForKey:key];
    if (value == nil || [value isEqual:[NSNull null]]) {
        @throw [NSException exceptionWithName:@"NotFoundValueException"
                                       reason:[[NSString alloc] initWithFormat:@"Not found json key %@ value", key]
                                     userInfo:nil];
    }
    return value;
}

NSDictionary* parseJSONString(NSString *jsonString) {
    // 将 JSON 字符串转换为 NSData
    NSData *jsonData = [jsonString dataUsingEncoding:NSUTF8StringEncoding];
    
    // 使用 NSJSONSerialization 将 NSData 转换为 NSDictionary 或 NSArray
    NSError *error = nil;
    id jsonObject = [NSJSONSerialization JSONObjectWithData:jsonData options:0 error:&error];
    
    if (error) {
        @throw [NSException exceptionWithName:@"parseJSONStringException"
                                              reason:@"JSONObjectWithData result error"
                                            userInfo:nil];
    }
    
    // 如果解析成功，返回 NSDictionary 或 NSArray
    if ([jsonObject isKindOfClass:[NSDictionary class]]) {
        return jsonObject;
    }
    
    // 如果解析失败，返回 nil
    return nil;
}

NSString* toJSONStringFromObject(id object) {
    // 使用 NSJSONSerialization 将对象转换为 JSON 数据
    NSError *error = nil;
    NSData *jsonData = [NSJSONSerialization dataWithJSONObject:object options:NSJSONWritingPrettyPrinted error:&error];
    
    // 如果序列化失败，返回 nil
    if (!jsonData || error) {
        @throw [NSException exceptionWithName:@"toJSONStringFromObjectException"
                                              reason:@"dataWithJSONObject result error"
                                            userInfo:nil];
    }
    
    // 将 NSData 转换为 NSString
    return [[NSString alloc] initWithData:jsonData encoding:NSUTF8StringEncoding];
}

NSString* createFlutterRequestResultWithCode(NSInteger code, NSDictionary *jsonData) {
    NSMutableDictionary *resultDict = [NSMutableDictionary dictionary];
    resultDict[@"code"] = @(code);
    resultDict[@"jsonData"] = jsonData;
    return toJSONStringFromObject(resultDict);
}

NSData *toByteArrayFromJSONArray(NSArray *jsonArray) {
    NSMutableData *byteArray = [NSMutableData dataWithCapacity:jsonArray.count];

    for (NSNumber *number in jsonArray) {
        // 获取每个元素并转换为字节
        uint8_t byte = [number intValue] & 0xFF;
        [byteArray appendBytes:&byte length:1];
    }

    return byteArray;
}

NSString* invokeMethodBlockGet(FlutterMethodChannel *channel, NSString* method, id arguments) {
    if ([NSThread isMainThread]) {
        @throw [NSException exceptionWithName:@"MainThreadException"
                                           reason:[NSString stringWithFormat:@"Methods must be executed on the not main thread. Current thread: %@", [NSThread currentThread].name]
                                         userInfo:nil];
    }
    
    dispatch_semaphore_t semaphore = dispatch_semaphore_create(0);
    __block NSString *callbackResult = nil;
    __block BOOL invokeFinish = NO;
    dispatch_async(dispatch_get_main_queue(), ^{
        [channel invokeMethod:method arguments:arguments result:^(id result) {
            FlutterMatterLog([[NSString alloc] initWithFormat:@"invoke %@ result %@", method, result]);
            if ([result isKindOfClass:[NSString class]]) {
                @try {
                    NSDictionary *jsonObject = parseJSONString(result);
                    NSNumber *code = [jsonObject objectForKey:@"code"];
                    if ([code isEqualToNumber:@(0)]) {
                        callbackResult = [jsonObject objectForKey:@"resultJson"];
                    } else {
                        FlutterMatterLog([[NSString alloc] initWithFormat:@"invoke %@ error %@", method, code]);
                    }
                } @catch (NSException *exception) {
                    
                } @finally {
                    
                }
            }
            dispatch_semaphore_signal(semaphore);
            invokeFinish = YES;
        }];
    });
    if (!invokeFinish) {
        dispatch_semaphore_wait(semaphore, DISPATCH_TIME_FOREVER);
    }
    return callbackResult;
}

NSMutableArray* nsDataToIntegerArray(NSData* data) {
    // 创建一个可变数组来存储字节的整数值
    NSMutableArray *intArray = [NSMutableArray array];
    
    // 获取 NSData 中的字节数据
    const uint8_t *bytes = [data bytes];
    NSUInteger length = [data length];
    
    // 遍历 NSData 中的每个字节，将其转换为整数值
    for (NSUInteger i = 0; i < length; i++) {
        [intArray addObject:@(bytes[i])];  // 将字节的整数值添加到数组
    }
    
    return intArray;
}

SecKeyRef nsDataToSecKey(NSData *publicKeyData) {
    NSDictionary *attributes = @{
        (__bridge id)kSecAttrKeyType :
            (__bridge id)kSecAttrKeyTypeEC, // 指定密钥类型为 EC（椭圆曲线）
        (__bridge id)
        kSecAttrKeyClass : (__bridge id)kSecAttrKeyClassPublic, // 这是一个公钥
        (__bridge id)kSecAttrKeySizeInBits : @(256), // P-256 是 256 位
    };

    // 使用 SecKeyCreateWithData 创建 SecKeyRef
    return SecKeyCreateWithData(
        (__bridge CFDataRef)publicKeyData,    // 公钥数据
        (__bridge CFDictionaryRef)attributes, // 公钥属性字典
        NULL                                  // 可选的错误返回
    );
}
