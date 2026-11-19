/**
 *
 *    Copyright (c) 2020-2023 Project CHIP Authors
 *
 *    Licensed under the Apache License, Version 2.0 (the "License");
 *    you may not use this file except in compliance with the License.
 *    You may obtain a copy of the License at
 *
 *        http://www.apache.org/licenses/LICENSE-2.0
 *
 *    Unless required by applicable law or agreed to in writing, software
 *    distributed under the License is distributed on an "AS IS" BASIS,
 *    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *    See the License for the specific language governing permissions and
 *    limitations under the License.
 */

#import <ZGMatter/ZGMTRDefines.h>

NS_ASSUME_NONNULL_BEGIN

/**
 * This protocol is used by the ZGMatter framework to read and write storage.
 *
 * The ZGMatter framework may call storage methods from arbitrary threads, but
 * will not call storage methods concurrently.
 *
 * Implementations of the storage methods must not call into any ZGMatter
 * framework APIs.
 */
ZGMTR_AVAILABLE(ios(16.4), macos(13.3), watchos(9.4), tvos(16.4))
@protocol ZGMTRStorage <NSObject>
@required

/**
 * Get the data for the given key.  Returns nil if there is no data for the
 * key.
 */
- (NSData * _Nullable)storageDataForKey:(NSString *)key;

/**
 * Set the data for the viven key to the given value.  Returns YES if the key
 * was set successfully, NO otherwise.
 */
- (BOOL)setStorageData:(NSData *)value forKey:(NSString *)key;

/**
 * Delete the key and corresponding data.  Returns YES if the key was present,
 * NO if the key was not present.
 */
- (BOOL)removeStorageDataForKey:(NSString *)key NS_SWIFT_NAME(removeStorageData(forKey:));

@end

ZGMTR_DEPRECATED("Please use ZGMTRStorage", ios(16.1, 16.4), macos(13.0, 13.3), watchos(9.1, 9.4), tvos(16.1, 16.4))
@protocol ZGMTRPersistentStorageDelegate <ZGMTRStorage>
@end

NS_ASSUME_NONNULL_END
