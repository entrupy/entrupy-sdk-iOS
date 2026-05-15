//
//  EntrupyError.h
//  EntrupySDK
//
//  Created by Muhammad Waqas on 30/06/2022.
//

#import <Foundation/Foundation.h>
#import "EntrupyServerResponseCode.h"
#import "EntrupyErrorCode.h"

@interface EntrupyError : NSObject

+(NSDictionary *) getErrorDescription:(EntrupyErrorCode)error;
+(NSError *)errorWithCode:(EntrupyErrorCode)errorCode;

@end

