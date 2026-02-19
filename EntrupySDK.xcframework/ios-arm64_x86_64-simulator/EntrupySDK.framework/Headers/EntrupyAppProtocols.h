//
//  EntrupyAppProtocols.h
//  EntrupySDK
//
//  Created by Entrupy.
//
#import <UIKit/UIKit.h>
#import "EntrupyErrorCode.h"
#import "EntrupyConfigType.h"

@class EntrupyDetailViewConfiguration;

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
///   - result: The authentication result as a dictionary. This dictionary is decodable with `EntrupyCaptureResult` struct using Swift's `JSONDecoder`.
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
/// - Parameter result: The search response dictionary containing the requested number of items or fewer if there aren't enough items and a cursor to the next page. This dictionary is decodable with `EntrupySearchResult` struct using Swift's `JSONDecoder`.
-(void) didSearchSubmissionsCompleteSuccessfully:(NSDictionary *_Nonnull)result;

/// Invoked if the search fails
/// - Parameters:
///   - errorCode: The error code
///   - description: An error description
///   - localizedDescription: A localized error description
-(void) didSearchSubmissionsFailWithError:(EntrupyErrorCode)errorCode description:(NSString *_Nonnull)description localizedDescription: (NSString *_Nonnull)localizedDescription;

@end

@protocol EntrupyFlagDelegate <NSObject>
/**
 Invoked upon the successful setting or clearing of a flag associated with a result.

 - Parameters:
   - entrupyID: The Entrupy ID associated with the result.
   - flag: A boolean value indicating the requested flag operation.

 */
- (void)didFlagResultSuccessfullyForEntrupyID:(NSString *_Nonnull)entrupyID
                             forRequestedFlag:(BOOL)flag;

/**
 Invoked upon failure to set or clear a flag associated with a result.

 - Parameters:
   - errorCode: The error code.
   - description: An error description.
   - localizedDescription: A localized error description.
   - entrupyID: The Entrupy ID associated with the result.
   - flag: A boolean value indicating the requested flag operation.

 */
- (void)didFlagResultFailWithError:(EntrupyErrorCode)errorCode
                       description:(NSString *_Nonnull)description
              localizedDescription:(NSString *_Nonnull)localizedDescription
                      forEntrupyID:(NSString *_Nonnull)entrupyID
                  forRequestedFlag:(BOOL)flag;



@end

/**
 Delegate protocol for handling Detail View Controller presentation events.

 @note Implement this delegate to handle Detail View lifecycle events.
*/
@protocol EntrupyDetailViewDelegate <NSObject>

/**
 Called when the SDK successfully presents the Detail View Controller.
 
 This indicates the view has been displayed and the user can interact with
 the view controller showing authentication status, timeline, results,
 and available actions for the specified item.
 
 @param entrupyID The unique Entrupy ID of the item being displayed in the Detail View
*/
- (void)didDisplayDetailViewForItemWithEntrupyID:(NSString *_Nonnull)entrupyID;

/**
 Called when the Detail View Controller is dismissed by the user.
 
 This occurs when the user closes the Detail View through available navigation
 controls. The view controller has been removed from the presentation stack.
 
 @param entrupyID The unique Entrupy ID of the item that was being viewed
*/
- (void)didDismissDetailViewForItemWithEntrupyID:(NSString *_Nonnull)entrupyID;

/**
 Called when the SDK fails to present the Detail View Controller.
 
 This can occur due to various reasons such as unauthorized access, network errors,
 invalid Entrupy ID, or internal SDK errors. The Detail View will not be shown.
 
 @param errorCode The specific error code describing the type of failure
 @param description A technical description of the error for debugging
 @param localizedDescription A user-friendly, localized error message suitable for display
 @param entrupyID The Entrupy ID that was requested but failed to display
*/
- (void)didDisplayDetailViewFailWithError:(EntrupyErrorCode)errorCode
                                         description:(NSString *_Nonnull)description
                                localizedDescription:(NSString *_Nonnull)localizedDescription
                                       forEntrupyID:(NSString *_Nonnull)entrupyID;

@end



/// Delegate protocol for the SDK’s built-in flagging UI.
@protocol EntrupyFlagViewDelegate <NSObject>

/**
 Called when the SDK successfully presents the flag view for the given result.

 - Parameter entrupyID: The Entrupy ID of the result whose flag view was presented.
 */
- (void)didDisplayFlagViewForItemWithEntrupyID:(NSString *_Nonnull)entrupyID;

/**
 Called when the user submits a flag from the built-in flag view.

 - Parameter entrupyID: The Entrupy ID of the result that was flagged.
 */
- (void)didUserSubmitFlagForEntrupyID:(NSString *_Nonnull)entrupyID;

/**
 Called when the user cancels or dismisses the flag view without submitting a flag.

 - Parameter entrupyID: The Entrupy ID of the result whose flag view was dismissed.
 */
- (void)didUserCancelFlagViewForItemWithEntrupyID:(NSString *_Nonnull)entrupyID;

/**
 Called when the SDK fails to present the flag view.

 This can occur due to invalid authorization, an invalid Entrupy ID, missing flag configuration,
 network failures, or internal SDK errors.

 - Parameters:
   - errorCode: The specific error code describing the failure.
   - description: A technical description of the error for debugging.
   - localizedDescription: A user-friendly, localized error message suitable for display.
   - entrupyID: The Entrupy ID that was requested but failed to present.
 */
- (void)didDisplayFlagViewFailWithError:(EntrupyErrorCode)errorCode
                             description:(NSString *_Nonnull)description
                    localizedDescription:(NSString *_Nonnull)localizedDescription
                           forEntrupyID:(NSString *_Nonnull)entrupyID;

@end


@protocol EntrupyRetakeCaptureDelegate <NSObject>

/// Invoked when the user successfully completes the retake capture workflow
///
/// - Parameters:
///   - result: The retake capture result as a dictionary. This dictionary is decodable with `EntrupyCaptureResult` struct using Swift's `JSONDecoder`.
///   - entrupyID: The Entrupy ID of the item for which retake capture was completed
-(void) didRetakeCaptureCompleteSuccessfully:(NSDictionary *_Nonnull)result
                        forItemWithEntrupyID:(NSString *_Nonnull)entrupyID;

/// Invoked if the user cancels the retake capture workflow without completing the process
/// - Parameter entrupyID: The Entrupy ID of the item for which retake capture was cancelled
-(void) didUserCancelRetakeCaptureForItemWithEntrupyID: (NSString *_Nonnull)entrupyID;

/// Invoked if the retake capture workflow fails due to an error
/// - Parameters:
///   - errorCode: The error code
///   - description: An error description
///   - localizedDescription: A localized error description
///   - entrupyID: The Entrupy ID of the item for which retake capture failed
-(void) didRetakeCaptureFailWithError:(EntrupyErrorCode)errorCode
                          description:(NSString *_Nonnull)description
                 localizedDescription: (NSString *_Nonnull)localizedDescription
                 forItemWithEntrupyID:(NSString *_Nonnull)entrupyID;


/// Invoked if the retake capture workflow times out.
/// Retake capture sessions are automatically aborted if not completed within the allocated time limit of two hours
/// - Parameters:
///   - entrupyID: The Entrupy ID of the item for which retake capture timed out
 
-(void) didRetakeCaptureTimeoutForItemWithEntrupyID:(NSString *_Nonnull)entrupyID;

@end


@protocol EntrupySearchRetakeDelegate <NSObject>

/// Invoked if the search retakes request is successful
///
/// - Parameter result: The response dictionary containing items that have pending retake requests. This dictionary can be decoded into the `EntrupySearchResult` struct using Swift's `JSONDecoder`
-(void) didSearchRetakesCompleteSuccessfully:(NSDictionary *_Nonnull)result;

/// Invoked if the search retakes request fails
/// - Parameters:
///   - errorCode: The error code
///   - description: An error description
///   - localizedDescription: A localized error description
-(void) didSearchRetakesFailWithError:(EntrupyErrorCode)errorCode description:(NSString *_Nonnull)description localizedDescription: (NSString *_Nonnull)localizedDescription;

@end



@protocol EntrupyMarketEdgeViewDelegate <NSObject>
/**
 Invoked when the SDK successfully presents the market edge view for an item.

 - Parameter entrupyID: The unique Entrupy ID of the item being displayed in the market edge view
*/
- (void)didDisplayMarketEdgeViewForItemWithEntrupyID:(NSString *_Nonnull)entrupyID;

/**
 Called when the Market Edge View Controller is dismissed by the user.
 
 @param entrupyID The unique Entrupy ID of the item that was being viewed
*/
- (void)didDismissMarketEdgeViewForItemWithEntrupyID:(NSString *_Nonnull)entrupyID;

/**
 Called when the SDK fails to present the Market Edge view.
 
 @param errorCode The specific error code describing the type of failure
 @param description A technical description of the error for debugging
 @param localizedDescription A user-friendly, localized error message suitable for display
 @param entrupyID The Entrupy ID that was requested but failed to display
*/
- (void)didDisplayMarketEdgeViewFailWithError:(EntrupyErrorCode)errorCode
                                         description:(NSString *_Nonnull)description
                                localizedDescription:(NSString *_Nonnull)localizedDescription
                                       forEntrupyID:(NSString *_Nonnull)entrupyID;

@end



@protocol EntrupyMarketEdgeDelegate <NSObject>
/**
 Invoked when market edge are successfully fetched for an item.

 - Parameters:
   - response: The market edge data as a dictionary. This dictionary is decodable with `EntrupyMarketEdge` struct using Swift's `JSONDecoder`.
   - entrupyID: The Entrupy ID associated with the item.
 */
- (void)didFetchMarketEdgeCompleteSuccessfully:(NSDictionary *_Nonnull)response
                                       forEntrupyID:(NSString *_Nonnull)entrupyID;

/**
 Invoked when market edge fetch fails.

 - Parameters:
   - errorCode: The error code
   - description: An error description
   - localizedDescription: A localized error description
   - entrupyID: The Entrupy ID associated with the item
 */
- (void)didFetchMarketEdgeFailWithError:(EntrupyErrorCode)errorCode
                                  description:(NSString *_Nonnull)description
                        localizedDescription:(NSString *_Nonnull)localizedDescription
                                forEntrupyID:(NSString *_Nonnull)entrupyID;

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
