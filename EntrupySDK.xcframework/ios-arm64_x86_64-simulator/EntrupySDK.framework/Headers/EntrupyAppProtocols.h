//
//  EntrupyAppProtocols.h
//  EntrupySDK
//
//  Created by Muhammad Waqas on 30/06/2022.
//
#import <UIKit/UIKit.h>
#import "EntrupyErrorCode.h"
#import "EntrupyConfigType.h"
@class EntrupyHistoryResultModel;

@protocol EntrupyLoginDelegate <NSObject>
/**
 Invoked if the login was successful

Save the received authorization token expiry timestamp in the UserDefaults and reauthorize when the token is about to expire.

 [SDK web documentation]:
 https://developer.entrupy.com/v1_2_entrupy_sdk.html

Refer to the [SDK web documentation] for more details.
 - Parameter expirationTime: The authorization token expiration time
*/
-(void) didLoginUserSuccessfully:(NSTimeInterval)expirationTime;


/** Invoked if the login was unsuccessful
 - Parameters:
   - errorCode: The error code
   - description: An error description
   - localizedDescription: A localized error description
 */
-(void) didLoginUserFailWithError:(EntrupyErrorCode)errorCode description:(NSString *_Nonnull)description localizedDescription: (NSString *_Nonnull)localizedDescription;
@end

@protocol EntrupyConfigDelegate <NSObject>
/// Invoked if the config fetch was successful
-(void) didFetchConfigurationSuccessfully;

/// Invoked if the config fetch was unsuccessful
/// - Parameters:
///   - errorCode: The error code
///   - description: An error description
///   - localizedDescription: A localized error description
-(void) didFetchConfigurationFailWithError:(EntrupyErrorCode)errorCode description:(NSString *_Nonnull)description localizedDescription: (NSString *_Nonnull)localizedDescription;
@end

@protocol EntrupyCaptureDelegate <NSObject>
/// Invoked when the user successfully submits the item to Entrupy for verification
///
/// - Parameters:
///   - result: The authentication result as a dictionary
///   - item: The input dictionary supplied to the startCapture method
-(void) didCaptureCompleteSuccessfully:(NSDictionary *_Nonnull)result forItem:(NSDictionary *_Nonnull) item;

/// Invoked if the user quits the capture workflow without submitting the item for verification
/// - Parameter item: The input dictionary supplied to the startCapture method
-(void) didUserCancelCaptureForItem: (NSDictionary *_Nonnull) item;

/// Invoked if the item submission fails
/// - Parameters:
///   - errorCode: The error code
///   - description: An error description
///   - localizedDescription: A localized error description
///   - item: The input dictionary supplied to the startCapture method
-(void) didCaptureFailWithError:(EntrupyErrorCode)errorCode description:(NSString *_Nonnull)description localizedDescription: (NSString *_Nonnull)localizedDescription forItem: (NSDictionary *_Nonnull)item;

/// Invoked if the capture timed out. Captures are automatically aborted if not completed within 2 hours.
/// - Parameter item: The input dictionary supplied to the startCapture method
-(void) didCaptureTimeoutForItem: (NSDictionary *_Nonnull) item;
@end

@protocol EntrupySearchDelegate <NSObject>
/// Invoked if the search is successful
///
/// The "next_cursor" array received in the response can be passed to the searchSubmissions call to receive the next page. If the “next_cursor” array returned is nil or empty it indicates that the last page has been reached.
/// - Parameter result: The search response dictionary containing the requested number of items or fewer if there aren't enough items and a cursor to the next page.
-(void) didSearchSubmissionsCompleteSuccessfully:(NSDictionary *_Nonnull)result;

/// Invoked if the search fails
/// - Parameters:
///   - errorCode: The error code
///   - description: An error description
///   - localizedDescription: A localized error description
-(void) didSearchSubmissionsFailWithError:(EntrupyErrorCode)errorCode description:(NSString *_Nonnull)description localizedDescription: (NSString *_Nonnull)localizedDescription;

@end

@protocol EntrupyAppProtocol <NSObject>
@property (nonatomic, weak) id<EntrupyLoginDelegate> _Nullable loginDelegate;
@property (nonatomic, weak) id<EntrupyConfigDelegate> _Nullable configDelegate;
@property (nonatomic, weak) id<EntrupyCaptureDelegate> _Nullable captureDelegate;
@property (nonatomic, weak) id<EntrupySearchDelegate> _Nullable searchDelegate;

-(void) fetchConfigurationType: (EntrupyConfigType) configType;
-(void) startCaptureForItem:(NSDictionary *_Nonnull)item viewController:(UIViewController *_Nonnull)viewController;
-(void) searchSubmissionsAt:(NSArray *_Nonnull)pageCursor filters:(NSArray *_Nonnull)filters startDate:(NSTimeInterval)startDate endDate:(NSTimeInterval)endDate paginationLimit:(NSInteger)limit;
-(void) cleanup;
- (void)loginUserWithSignedRequest:(NSString *_Nonnull)signedRequest;
- (NSString *_Nonnull)generateSDKAuthorizationRequest;

@end
