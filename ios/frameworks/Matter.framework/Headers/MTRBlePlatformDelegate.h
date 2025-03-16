/**
 *
 *    Copyright (c) 2024 Project CHIP Authors
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

#import <Foundation/Foundation.h>

@protocol MTRBlePlatformDelegate <NSObject>

- (BOOL)subscribeCharacteristicWithConnection:(id)connObj
                                              serviceId:(NSData *)svcId
                                             characteristicId:(NSData *)charId;

- (BOOL)unsubscribeCharacteristicWithConnection:(id)connObj
                                                serviceId:(NSData *)svcId
                                               characteristicId:(NSData *)charId;

- (BOOL)closeConnectionWithConnection:(id)connObj;

- (uint16_t)getMTUForConnection:(id)connObj;

- (BOOL)sendIndicationWithConnection:(id)connObj
                                    serviceId:(NSData *)svcId
                               characteristicId:(NSData *)charId
                                       payload:(NSData *)pBuf;

- (BOOL)sendWriteRequestWithConnection:(id)connObj
                                     serviceId:(NSData *)svcId
                                characteristicId:(NSData *)charId
                                        payload:(NSData *)pBuf;

@end

