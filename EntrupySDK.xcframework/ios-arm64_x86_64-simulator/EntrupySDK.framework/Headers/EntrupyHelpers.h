//
//  EntrupyHelpers.h
//  EntrupyHelpers
//
//  Created by Dharini Raghavan on 10/29/22.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>


//Macro for converting a HEX color notation to objective-c syntax
#define UIColorFromRGB(rgbValue) \
[UIColor colorWithRed:((float)((rgbValue & 0xFF0000) >> 16))/255.0 \
green:((float)((rgbValue & 0x00FF00) >>  8))/255.0 \
blue:((float)((rgbValue & 0x0000FF) >>  0))/255.0 \
alpha:1.0]

#ifdef DEBUG
#define DEBUG_PRINTF(message,...)\
printf(message,##__VA_ARGS__);
#else
#define DEBUG_PRINTF(message,...)\
;
#endif

@protocol EntrupyHelpers
@end

@interface EntrupyHelpers : NSObject
+(void)setBorder:(UIView *)view :(CGFloat) width : (UIColor *) color;
+(void)setRoundedCorners: (UIView *)view withShadow:(BOOL) shadow;
+ (UIAlertController *) createCustomAlert: (NSString *) title
                                  message: (NSString *) message
                                     type: (NSInteger) alertType
                      settings_completion:(void (^)(void))settingsCompletionBlock
                            ok_completion:(void (^)(void))okCompletionBlock
                         retry_completion:(void (^)(void))retryCompletionBlock
                        cancel_completion:(void (^)(void))cancelCompletionBlock;

+ (UIAlertController *) createCustomAlert: (NSString *) title
                                  message: (NSString *) message
                                     type: (NSInteger) alertType
                               completion:(void (^)(void))completionBlock;

+(UIViewController *)topViewController;
+ (NSString*) getDeviceModel;
+ (NSMutableDictionary *)unpackQueryParametersFromURL:(NSString *)url;
+ (UIImage *)imageWithColor:(UIColor *)color;

+ (nullable NSString *)extractSubstringFromString:(nonnull NSString *)urlString pattern:(nonnull NSString *)pattern;
+(void)addAlphaLabel;
@end
