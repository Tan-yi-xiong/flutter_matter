


#import <Foundation/Foundation.h>
#import <Matter/Matter.h>


@interface DeviceAttestationDelegate : NSObject <MTRDeviceAttestationDelegate>

@property (nonatomic, strong) NSString *handle;

- (instancetype)initWithHandle:(NSString *)handle;

@end
