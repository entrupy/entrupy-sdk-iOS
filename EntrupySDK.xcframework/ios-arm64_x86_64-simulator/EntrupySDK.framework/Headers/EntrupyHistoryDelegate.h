//
//  EntrupyHistoryDelegate.h
//  EntrupySDK
//
//  Created by Felipe Garcia on 04/05/2022.
//
#import <Foundation/Foundation.h>
#import "EntrupyErrorCode.h"
#import "EntrupyCaptureWorkflowType.h"

@class EntrupyHistoryResultModel;

NS_ASSUME_NONNULL_BEGIN

@protocol EntrupyHistoryDelegate <NSObject>

@required
-(void)historyDidFetchSuccessfully:(NSDictionary *)response forceUpdate: (BOOL) forceUpdate captureWorkflowType:(EntrupyCaptureWorkflowType)captureWorkflowType;
-(void)retakeHistoryDidFetchSuccessfully:(NSDictionary *)response forceUpdate: (BOOL) forceUpdate;
-(void)historyFetchingDidFailWith:(EntrupyErrorCode)errorCode forceUpdate: (BOOL) forceUpdate description: (NSString *) description localizedDescription:(NSString *)localizedDescription captureWorkflowType:(EntrupyCaptureWorkflowType)captureWorkflowType;
-(void)retakeHistoryFetchingDidFailWith:(EntrupyErrorCode)errorCode forceUpdate: (BOOL) forceUpdate description: (NSString *) description localizedDescription:(NSString *)localizedDescription;
@end

NS_ASSUME_NONNULL_END
