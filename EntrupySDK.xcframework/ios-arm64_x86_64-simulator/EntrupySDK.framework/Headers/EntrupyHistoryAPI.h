//
//  EntrupyHistoryAPI.h
//  EntrupySDK
//
//  Created by Muhammad Waqas on 21/06/2022.
//

#import <Foundation/Foundation.h>
#import "EntrupyError.h"
#import "EntrupyCaptureWorkflowType.h"

@protocol EntrupyHistoryDelegate;

NS_ASSUME_NONNULL_BEGIN

#define MAX_HISTORY_ITEMS_PER_PAGE 25

@interface EntrupyHistoryAPI : NSObject

@property (nonatomic, weak) id<EntrupyHistoryDelegate> externalDelegate;

- (void) getHistoryItems: (NSArray *) cursor withFilters: (NSArray*) filters withStartDate: (NSTimeInterval) startDate  withEndDate:(NSTimeInterval) endDate fetchLimit: (NSInteger) limit forceUpdate: (BOOL) forceUpdate captureWorkflowType: (EntrupyCaptureWorkflowType) captureWorkflowType;

- (void) getRetakeItems: (NSArray *) cursor withFilters: (NSArray*) filters withStartDate: (NSTimeInterval) startDate  withEndDate:(NSTimeInterval) endDate fetchLimit: (NSInteger) limit forceUpdate: (BOOL) forceUpdate;

@end

NS_ASSUME_NONNULL_END
