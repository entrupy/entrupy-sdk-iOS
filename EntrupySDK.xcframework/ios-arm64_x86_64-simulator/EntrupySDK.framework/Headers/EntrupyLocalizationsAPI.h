//
//  EntrupyLocalizationsRequest.h
//  EntrupySDK
//
//  Created by Entrupy.
//  Copyright © 2024 Entrupy Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "EntrupyErrorCode.h"

NS_ASSUME_NONNULL_BEGIN

@interface EntrupyLocalizationsAPI : NSObject
// Class method for Swift compatibility - builds request dictionary directly
+ (void)sendLocalizationsRequestWithLastUpdatedTimestamp:(NSString * _Nullable)lastUpdatedTimestamp
                                                  success:(void (^)(NSMutableDictionary* json))success
                                                  failure:(void (^)(NSMutableDictionary* json, EntrupyErrorCode errorCode, NSString *description, NSString *localizedDescription))failure;

@end

NS_ASSUME_NONNULL_END
