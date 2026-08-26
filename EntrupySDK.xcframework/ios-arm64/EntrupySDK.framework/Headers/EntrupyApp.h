//
//  EntrupyApp.h
//  EntrupySDK
//
//  Created by Entrupy.
//

#import <Foundation/Foundation.h>
#import "EntrupyAppProtocols.h"

@protocol EntrupyTheme;
@protocol CaptureObjectDataSource;
@class EntrupyDetailViewConfiguration;
@class EntrupyMarketEdgeViewConfiguration;
@class EntrupySearchQuery;


NS_ASSUME_NONNULL_BEGIN

// Internal legacy implementation - use EntrupyApp (Swift) for public API
@interface EntrupyApp_Legacy: NSObject<EntrupyAppProtocol>

@property (nonatomic, weak) id<EntrupyLoginDelegate> loginDelegate;
@property (nonatomic, weak) id<EntrupyConfigDelegate> configDelegate;
@property (nonatomic, weak) id<EntrupyCaptureDelegate> captureDelegate;
@property (nonatomic, weak) id<EntrupySearchDelegate> searchDelegate;
@property (nonatomic, strong) id<EntrupyTheme> theme;
@property (nonatomic, copy, nullable) void(^backgroundTransferCompletionHandler)(void);
@property (nonatomic, weak) id<EntrupyFlagDelegate> flagDelegate;
@property (nonatomic, weak) id<EntrupyDetailViewDelegate> detailViewDelegate;
@property (nonatomic, weak) id<EntrupyFlagViewDelegate> flagViewDelegate;
@property (nonatomic, weak) id<EntrupyRetakeCaptureDelegate> retakeCaptureDelegate;
@property (nonatomic, weak) id<EntrupySearchRetakeDelegate> searchRetakeDelegate;
@property (nonatomic, weak) id<EntrupyMarketEdgeDelegate> marketEdgeDelegate;
@property (nonatomic, weak) id<EntrupyMarketEdgeViewDelegate> marketEdgeViewDelegate;

+ (instancetype)sharedInstance;



/**
 Fetches the configuration required for running the capture and search actions.
 
 This function is optional to implement and can be called once from the viewDidAppear function of the View Controllers invoking the SDK’s startCapture/searchSubmissions method. It fetches configuration required for performing these actions. If this is not explicitly called this’ll be implicitly handled by the sdk before launching the capture workflow or beginning the search causing a few seconds overhead.
 
 - Returns: void
 
 ```swift
 // Swift
 if ( EntrupyApp.sharedInstance().isAuthorizationValid()) {
     //Implement EntrupyConfigDelegate
     EntrupyApp.sharedInstance().configDelegate = self
     
     // Set configType to ConfigTypeDebug if you want a shorter capture workflow during development
     EntrupyApp.sharedInstance().fetchConfigurationType(EntrupyConfigType.ConfigTypeProduction)
 }
 
 ```
 
 ```
 Implement the "EntrupyConfigDelegate" protocol to handle responses from this function
 ```
 
 
 - Parameter configType: ConfigTypeDebug: The debug config is used to launch a shorter capture workflow. This is only to be used for dev testing. All submissions with the debug config will be marked Invalid.
 ConfigTypeProduction: The regular full length config.
 
 */
-(void) fetchConfigurationType: (EntrupyConfigType) configType;

/**
 Starts the capture workflow for performing an authentication
 
 Call this function in response to a user event such as tapping an ‘Authenticate’ button. This function launches Entrupy’s capture workflow modally on the existing view controller. Capture not completed within 2 hours will automatically be aborted and the error delegate will be sent.
 
  
 - Parameter item: A dictionary containing details about the item to be authenticated
 - Parameter viewController: A reference to the view controller launching the Entrupy capture workflow.
 
 - Returns: void

 ## Item Metadata

 The SDK accepts `brand` and `item_type` to identify the capture flow.
 When both match a configured capture flow, the SDK navigates directly to it.
 When no match is found and no `product_category` is provided, an error is returned
 via `didCaptureFailWithError`.

 ### Recommended fields
 - `brand` (String): The brand of the item (e.g., "Nike", "Louis Vuitton", "BAPE")
 - `item_type` (String): The type of item (e.g., "Sneakers", "Outerwear", "Bags")
 Both `brand` and `item_type` are required for capture flow resolution.
 Legacy integrations may continue using `product_category` instead.

 ### Optional fields
 - `customer_item_id` (String): Unique identifier from your system
 - `us_size` (String): e.g., "8", "8.5", "8.5Y"
 - `style_code` (String): e.g., "555088-134"
 - `upc` (String): The item's Universal Product Code

 ### Example
 ```swift
 let itemMetadata: [String: Any] = [
     "brand": "Nike",
     "item_type": "Sneakers",
     "customer_item_id": "AJ1-DO7097-100-9_5"
 ]
 ```

 ### Legacy: `product_category` (backwards compatible)
 Existing integrations using `product_category` ("luxury", "sneakers", "apparel")
 continue to work. New integrations should use `brand` + `item_type`.

 ## Usage Example
 ```swift
 if EntrupyApp.sharedInstance().isAuthorizationValid() {
     EntrupyApp.sharedInstance().captureDelegate = self
     EntrupyApp.sharedInstance().startCapture(forItem: itemMetadata, viewController: self)
 }
 ```
 [Entrupy iOS SDK Documentation](https://developer.entrupy.com/docs/mobile-sdks/ios/overview)

 */
-(void) startCaptureForItem:(NSDictionary *)item viewController:(UIViewController *)viewController;

/**
 Fetches past submissions.
 
 Implement searchSubmissions to fetch past authentications. The search response is paginated into pages of ‘paginationLimit’ items each. The maximum number of items that can be requested per page is 25. The function takes a pageCursor parameter which determines the page that has to be fetched. Pass an empty array for pageCursor to fetch the first page.
 Repeat the searchSubmissions call, setting the pageCursor with the "next_cursor" array received in the delegate response of the previous call until all pages have been retrieved. If the “next_cursor” array returned is nil or empty it indicates that the last page has been reached.
 
 [Entrupy iOS SDK Documentation]:
 https://developer.entrupy.com/docs/mobile-sdks/ios/overview
 
 ```
 Implement the "EntrupySearchDelegate" protocol to handle responses
 from this method.
 ```
 
 
 ```swift
 class ViewController {

     // Tells if all pages have been fetched.
     var lastPage = false
     // Used to load next page (current + 1)
     var nextPageCursor: [Any]? = []
     // Limit of records per page.
     let perPage = 20
     
     override init() {
         super.init()
         
         //Implement the EntrupySearchDelegate protocol
         EntrupyApp.sharedInstance().searchDelegate = self
     }
     
     func fetchAuthentications() {
         let filter:[Dictionary<String,Any>] = [["key": "status.result.id", "value":"authentic"]]
         EntrupyApp.sharedInstance().searchSubmissions(at: self.nextPageCursor ?? [], filters: filter, startDate: 0, endDate: 0, paginationLimit: perPage)
     }
 }
 
 ```
 
 - Parameters:
    -  pageCursor: The cursor to the page that needs to be fetched. Pass an empty array to fetch the first page.
    - filters: Search filters. Check the [SDK web documentation] for possible filter options and examples.
    - startDate: The start date to be applied to the search. Pass 0 if you do not want to set a start date.
    - endDate: The end date to be applied to the search. Pass 0 if you do not want to set an end date.
    - paginationLimit: The pagination limit. The maximum number of items that can be requested per page is 25.
 
 - Returns: void
 
 */
-(void) searchSubmissionsAt:(NSArray *)pageCursor filters:(NSArray *)filters startDate:(NSTimeInterval)startDate endDate:(NSTimeInterval)endDate paginationLimit:(NSInteger)paginationLimit;

/**
 Cleans up user data.
 
 Call the cleanup function on logout or before switching user accounts.
  
 - Returns: void
 
 */


-(void) cleanup;

// MARK: - Authorization

/**
 Logs In user to the Entrupy SDK
 
 To run the services provided by the Entrupy SDK your app has to maintain a valid authorization token for the user. Authorization tokens have to be re-created when they expire.
 
 It is recommended that tokens are created or re-created if expired before calling other SDK methods to avoid additional latency.
 
 [Entrupy iOS SDK Documentation]:
 https://developer.entrupy.com/docs/mobile-sdks/ios/overview
 
 * Implement the following steps on your app and  backend as indicated.
 
 1.  Create the SDK authorization request from your app.
 
 ```swift
 // Swift
 
 // Generates a string to be passed to your app’s backend for signing
 let sdkAuthorizationRequest = EntrupyApp.sharedInstance().generateSDKAuthorizationRequest()
 ```
 
 2. Send the SDK authorization request to your backend for signing. Refer to the [SDK web documentation] for details.
 
 3. Log In to the SDK with the returned signed authorization request
 
- Returns: void
 
 ```swift
 //Swift
 
 if let jsonObject = try? JSONSerialization.jsonObject(
                with: data, options: []
            ) as? [String: Any] {
     //Signed authorization request received from your backend
     if let signedRequest = jsonObject["signed_authorization_request"] as? String {
         //Implement the EntrupyLoginDelegate protocol
         EntrupyApp.sharedInstance().loginDelegate = self
         EntrupyApp.sharedInstance().loginUser(withSignedRequest: signedRequest)
     }
 }
 
 ```
 
 ```
 Implement the "EntrupyLoginDelegate" protocol to handle responses
 from this method.
 ```
 
 - Parameter signedRequest: Signed authorization request received from your backend
 */
- (void)loginUserWithSignedRequest:(NSString *)signedRequest;

/// Generates the SDK Authorization request.
///
/// - Returns: A string to be passed to your app's backend for signing.
- (NSString *)generateSDKAuthorizationRequest;

/** Checks the validity of the authorization token.
 
 - Returns: The function returns a Boolean value of ‘true’ if the authorization token is valid.
 
 */
-(BOOL) isAuthorizationValid;

/**
 Handles EntrupySDK related upload or download events that occured while the app was in the suspended state.

 Call "interceptApplication" in the AppDelegate's handleEventsForBackgroundURLSession method.
 
 
 ```swift
 // AppDelegate

 func application(_ application: UIApplication, handleEventsForBackgroundURLSession identifier: String, completionHandler: @escaping () -> Void) {
     EntrupyApp.sharedInstance().interceptApplication(application, handleEventsForBackgroundURLSession: identifier completionHandler:completionHandler)
 }
 
 ```
 
*/
-(void)interceptApplication:(UIApplication *)application handleEventsForBackgroundURLSession:(NSString *)identifier completionHandler:(void(^ _Nullable)(void))completionHandler;


/**
 Retrieves the flag status, eligibility, and supported flag reasons for an Entrupy result.

 Call this method before displaying any flag or clear-flag UI.
 `flag_status` is the server's flag dictionary, passed through verbatim (extra keys,
 null/absent `id`, and missing or non-boolean `is_flaggable` are preserved).
 `supported_flag_reasons` is typed and redacted to `{id, label}`.
 The payload can be decoded into `EntrupyFlagDetails` when the standard required
 flag fields (`id`, `is_flaggable`) are present.

 - Important:
   Always check both the current flag status and `is_flaggable` before enabling flag actions.

 - Parameters:
   - entrupyID: The Entrupy ID for the result.
   - completionHandler: Called with the flag details dictionary or an error.

 ## Response Model Mapping

 The SDK returns a dictionary payload with:

 - `flag_status`: The server's flag dictionary, passed through verbatim.
   Decodes into `EntrupyCaptureResultStatusFlag` when the standard fields exist.
 - `supported_flag_reasons`: An array of `EntrupyCaptureResultStatusFlagInfo`

 ### EntrupyCaptureResultStatusFlag
 - `id`: Current flag status (`none`, `flagged`, `resolved`)
 - `is_flaggable`: Indicates whether the item can currently be flagged
 - `flag_info`: Optional `EntrupyCaptureResultStatusFlagInfo`
   (Only populated when the item is already flagged)

 ### EntrupyCaptureResultStatusFlagInfo
 - `id`: Reason identifier
   Pass this value as `flagReasonId` when calling `setFlag(...)`
 - `label`: User-facing reason text for display
 - `message`:
   - Always `nil` for `supported_flag_reasons`
   - Populated only in `flag_status.flag_info` with the user-provided note

 ## Example Usage

 ```swift
 EntrupyApp.sharedInstance().getFlagDetailsForResult(withEntrupyID: entrupyID) { details, error in

     if let error = error {
         print("Flag details request failed: \(error.localizedDescription)")
         return
     }

     guard let details,
           let data = try? JSONSerialization.data(withJSONObject: details),
           let parsed = try? JSONDecoder().decode(EntrupyFlagDetails.self, from: data)
     else {
         return
     }

     let itemFlagStatus = parsed.flag_status.id
     let isFlaggable = parsed.flag_status.is_flaggable

     // ---- UI Logic ----
     if (itemFlagStatus == .none || itemFlagStatus == .resolved) && isFlaggable {
         // Show "Flag" button
     } else if itemFlagStatus == .flagged {
         // Show "Clear Flag" button
     } else {
         // Hide flag controls
     }

     let selectedReasonLabel = parsed.flag_status.flag_info?.label ?? ""
     let userMessage = parsed.flag_status.flag_info?.message ?? ""
     let supportedReasons = parsed.supported_flag_reasons

     // Use `supportedReasons` to populate the reason picker UI.
     // On submission, pass the selected reason’s `id` as `flagReasonId` to `setFlag(...)`.
 }
 ```
 [Entrupy iOS SDK Documentation]:
 https://developer.entrupy.com/docs/mobile-sdks/ios/overview
 
 For more information, refer to the SDK web documentation.
 */

- (void)getFlagDetailsForResultWithEntrupyID:(NSString *)entrupyID completionHandler:(void (^ _Nonnull)(NSDictionary * _Nullable details, NSError * _Nullable error))completionHandler;

/**
  Sets or clears a flag for a specific authentication result.

  Call this method to submit a flag request to Entrupy through your custom flagging UI.
  Retrieve valid `flagReasonId` values from the `supported_flag_reasons` array returned by `getFlagDetailsForResultWithEntrupyID:completionHandler:`.
  A message may be included to provide additional context to Entrupy reviewers.
  If you want the SDK to handle reason/message validation automatically, use `displayFlagViewForItemWithEntrupyID:` instead.

  Custom UI approach (recommended sequence):
  1. Call `getFlagDetailsForResultWithEntrupyID:completionHandler:` to check the current flag status (and any existing flag details) and get `supported_flag_reasons`.
  2. Present your custom UI (e.g. a list of reasons + optional free-form note field).
  3. Call `setFlag:forResultWithEntrupyID:flagReasonId:message:` when the user submits (use the selected reason's `id` as `flagReasonId`).
  4. Implement `EntrupyFlagDelegate` to receive success/failure callbacks and update your UI accordingly.

  - Parameters:
     - flag: Pass `YES` to set a flag, or `NO` to clear an existing flag.
     - entrupyID: The Entrupy ID of the item being updated.
     - flagReasonId: The identifier of the selected flag reason.
     - message: Additional details provided by the user.

  Example:
  ```swift
  EntrupyApp.sharedInstance().flagDelegate = self
  let userNote = "Additional context for review"

  EntrupyApp.sharedInstance().setFlag(
      true,
      forResultWithEntrupyID: entrupyID,
      flagReasonId: selectedFlagReason.id,
      message: userNote
  )
 ```
 */
- (void)setFlag:(BOOL)flag forResultWithEntrupyID:(NSString *_Nonnull)entrupyID flagReasonId:(NSString* _Nonnull)flagReasonId message:(NSString* _Nullable)message;

/**
  Presents the Detail View Controller for a specific authenticated item.
 
  Displays the item's status, results, history, and related actions within the SDK.
  Supports Entrupy branding and an ETA-based flow—users can leave while authentication runs in the background.
 
  @param entrupyID The unique Entrupy ID for the item.
  @param viewConfiguration Configuration options, including:
         - displayTimeline: Show/hide event timeline
         - displayUploadedImages: Show/hide captured images
         - enableFlagging: Enable/disable flagging
         - enableItemDetailEdit: Enable/disable item detail editing
 
  @note Requires valid authorization. Presented modally over the current top view controller.
 
 ```swift
 guard EntrupyApp.sharedInstance().isAuthorizationValid() else { return }

 //Implement EntrupyDetailViewConfiguration
 let viewConfig = EntrupyDetailViewConfiguration(
     displayTimeline: true,
     displayUploadedImages: true,
     enableFlagging: true,
     enableItemDetailEdit: false
 )

 //Implement EntrupyDetailViewDelegate
 EntrupyApp.sharedInstance().detailViewDelegate = self

 EntrupyApp.sharedInstance().displayDetailViewForItem(
     withEntrupyID: entrupyId,
     withConfiguration: viewConfig
 )
 
 ```
 
 [Entrupy iOS SDK Documentation]:
 https://developer.entrupy.com/docs/mobile-sdks/ios/overview
 
 */
- (void)displayDetailViewForItemWithEntrupyID:(NSString *_Nonnull)entrupyID withConfiguration:(EntrupyDetailViewConfiguration *_Nonnull)viewConfiguration NS_SWIFT_NAME(displayDetailViewForItem(withEntrupyID:withConfiguration:));

/**
 Presents the Market Edge view for a specific authentication result.

 @param entrupyID The Entrupy ID for the item to display.
 @param viewConfiguration Configuration options, including:
        - displayMarketGrade: Show/hide market grade
        - displayMarketValue: Show/hide market value
        - displayMarketMatch: Show/hide market match
        - displayRegionSelection: Show/hide region selection

 @note The view is Presented modally over the current top view controller.

 ```swift
 guard EntrupyApp.sharedInstance().isAuthorizationValid() else {
     print("User not authorized. Cannot display Market Edge view.")
     return
 }

 let configuration = EntrupyMarketEdgeViewConfiguration(
     displayMarketGrade: true,
     displayMarketValue: true,
     displayMarketMatch: true,
     displayRegionSelection: true
 )

  //Implement EntrupyMarketEdgeViewDelegate to receive presentation callbacks.
 EntrupyApp.sharedInstance().marketEdgeViewDelegate = self
 EntrupyApp.sharedInstance().displayMarketEdgeViewForItem(withEntrupyID: entrupyID, withConfiguration: configuration)
 ```
 */
- (void)displayMarketEdgeViewForItemWithEntrupyID:(NSString *_Nonnull)entrupyID
                                withConfiguration:(EntrupyMarketEdgeViewConfiguration *_Nonnull)viewConfiguration NS_SWIFT_NAME(displayMarketEdgeViewForItem(withEntrupyID:withConfiguration:));


/**
  This method presents the built-in flagging UI that handles the entire flagging workflow

  This view allows users to select a flag reason, add an optional note, and submit a flag. When the user submits the flag in this UI, the SDK
  automatically handles all necessary validation and sets the flag.

  Implement `EntrupyFlagViewDelegate` to receive delegate callbacks for the flagging workflow.

  - Parameter entrupyID: The Entrupy ID of the result to be flagged.

  Example:
  ```swift
  guard EntrupyApp.sharedInstance().isAuthorizationValid() else { return }

  EntrupyApp.sharedInstance().flagViewDelegate = self
  // Present the built-in flagging UI
  EntrupyApp.sharedInstance().displayFlagViewForItem(withEntrupyID: entrupyID)
 
 ```
 */
- (void)displayFlagViewForItemWithEntrupyID:(NSString *_Nonnull)entrupyID;


/**
 Starts the retake workflow for an item with a pending retake request.

 Use this method to initiate a retake capture session for an item that Entrupy has specifically requested additional images for.
 This workflow allows users to capture the required images so the authentication process can be completed.

 Calling this method presents the retake workflow modally over the current top view controller.
 
 ```
 Implement the "EntrupyRetakeCaptureDelegate" protocol to handle responses from this method.
 ```

 - Parameters:
   - entrupyID: The unique Entrupy ID of the item requiring a retake.

 ```swift
 // Swift
 guard EntrupyApp.sharedInstance().isAuthorizationValid() else { return }

 // Implement EntrupyRetakeCaptureDelegate
 EntrupyApp.sharedInstance().retakeCaptureDelegate = self

 // Start retake capture for a specific item
 EntrupyApp.sharedInstance().startRetakeCaptureForItem(withEntrupyID: <Entrupy ID>)

 ```
 
 */
- (void) startRetakeCaptureForItemWithEntrupyID:(NSString *_Nonnull)entrupyID;

/**
 Fetches retake submissions that require additional image captures.

 Use this method to retrieve items that have pending retake requests.

 ```
 Implement the "EntrupySearchRetakeDelegate" protocol to handle responses from this method.
 ```

 ```swift
 // Swift

 guard EntrupyApp.sharedInstance().isAuthorizationValid() else { return }

 // Implement EntrupySearchRetakeDelegate
 EntrupyApp.sharedInstance().searchRetakeDelegate = self

 // Fetch pending retakes
 EntrupyApp.sharedInstance().searchRetakes()
 ```
 
 */
-(void) searchRetakes;


/**
  Fetches MarketEdge data for a given Entrupy ID.

  This API retrieves MarketEdge information associated with an authentication result.
  The response can be decoded into the SDK provided `EntrupyMarketEdge` model, which
  represents a consolidated data for an item.

  `EntrupyMarketEdge` includes:
  - `identifier`: Authentication identifiers for the item.
  - `market_grade`: Condition rating based on submitted images, including rating details,
    item report information, and region-level descriptions (`EntrupyMarketGrade`).
  - `market_value`: Estimated market value derived from recent market data, including
    price and currency (`EntrupyMarketValue`).
  - `market_match`: Recent marketplace listings similar to the submitted item, such as
    brand, style, and price (`EntrupyMarketMatch`).
  - `disclaimer`: Disclaimer text associated with MarketGrade and MarketValue.
  - `error`: Error information when MarketEdge data is unavailable.

  - Parameter entrupyID: The Entrupy authentication ID for which MarketEdge data should be fetched.

  - Important: Ensure the user is logged in before invoking this API.

  ### Usage Example
  ```swift
  // Assign the delegate
  entrupyApp.marketEdgeDelegate = self

  // Request MarketEdge data
  entrupyApp.fetchMarketEdgeForItem(withEntrupyID: entrupyID)

  // Handle success
  func didFetchMarketEdgeCompleteSuccessfully(
      _ response: [AnyHashable: Any],
      forEntrupyID entrupyID: String
  ) {
      do {
          let data = try JSONSerialization.data(withJSONObject: response, options: [])
          let marketEdge = try JSONDecoder().decode(EntrupyMarketEdge.self, from: data)
 
            // Check for MarketEdge level error
            if let error = marketEdge.error {
              // Handle MarketEdge error
              return
          }
 
          // Access MarketEdge properties
          let identifier = marketEdge.identifier
          let marketGrade = marketEdge.market_grade
          let marketValue = marketEdge.market_value
          let marketMatch = marketEdge.market_match
          let disclaimer = marketEdge.disclaimer
          

          // Use the parsed data to populate UI or business logic
      } catch {
          // Handle decoding errors
      }
  }

  // Handle failure
  func didFetchMarketEdgeFailWithError(
      _ errorCode: EntrupyErrorCode,
      description: String,
      localizedDescription: String,
      forEntrupyID entrupyID: String
  ) {
      // Access the error code and localized description for failure cases
  }
 
*/
- (void)fetchMarketEdgeForItemWithEntrupyID:(NSString *_Nonnull)entrupyID;

/**
 Searches authentication items using date ranges and customizable filters.
 Depending on the selected result mode, the response returns either paginated full item history or aggregate counts only.
 
 This method provides a flexible way to query authentication results with various filter options.
 The response is paginated and can be configured to return full result objects or just counts.
 
 ## Response Model
 
 The result dictionary can be decoded into `EntrupySearchItemsResult`:
 - `metadata`: Contains `result_mode` (`.results` or `.countOnly`)
 - `total_count`: Total number of items matching the query
 - `item_count`: Number of items in the current page
 - `items`: Array of `EntrupyCaptureResult` objects (nil when using `.countOnly`)
 - `next_cursor`: Cursor for fetching the next page (nil if last page)
 
 ## Filter Examples
 
 ```swift
 filters: [
     .status([.authentic, .underReview]),
     .brands(["louis_vuitton", "gucci"]),
     .category([.luxury, .apparel]),
     .flag([.flagged])
 ]
 ```
 
 ## Usage Example
 
 ```swift
 guard EntrupyApp.sharedInstance().isAuthorizationValid() else { return }

 // pagination state
 var nextPageCursor: String? = nil
 
 let query = EntrupySearchQuery(
     dateRange: .last(days: 7),
     filters: [
         .status([.authentic]),
         .category([.luxury, .apparel])
     ],
     resultMode: .results,  // or .countOnly
     limit: 20,
     cursor: nextPageCursor
 )
 
 EntrupyApp.sharedInstance().searchAuthenticationItems(query: query) { result, error in
     guard let result = result,
           let data = try? JSONSerialization.data(withJSONObject: result),
           let searchResult = try? JSONDecoder().decode(EntrupySearchItemsResult.self, from: data)
     else {
         return
     }
     
     print("Total: \(searchResult.total_count)")
     if let items = searchResult.items {
         // Process items
     }
 
    // Persist cursor for next page if available
    nextPageCursor = searchResult.next_cursor
 }
 ```
 
 - Parameter query: Search query with dateRange, filters, resultMode, limit, and cursor
 - Parameter completion: Handler called with result dictionary or error
 
 - Note: The product category filter is required for results.
 
 For additional details on search and filtering, please refer to the  [Entrupy iOS SDK Documentation](https://developer.entrupy.com/docs/mobile-sdks/ios/sdk-reference/direct-access-api-guides/programmatic-search-items)
 */

- (void)searchAuthenticationItems:(EntrupySearchQuery *_Nonnull)query
                       completion:(void (^_Nonnull)(NSDictionary * _Nullable result, NSError * _Nullable error))completion
                            NS_SWIFT_NAME(searchAuthenticationItems(query:completion:));

/// For internal use. Do not call from client code.
- (void)updateDefaultConfigsWithCategoryIndex:(NSInteger)categoryIndex
                                  rawResponse:(NSDictionary *)rawResponse
                                  completion:(void (^)(NSError * _Nullable))completion;

/// For internal use. Swift pre-capture sets state then starts authentication capture (legacy builds data source).
- (void)startAuthenticationCaptureWithValidatedItem:(NSDictionary *)item viewController:(UIViewController *)viewController;

/// For internal use. Do not use from client code. Starts retake capture with a pre-fetched config response (Swift sets context and presents).
- (void)startRetakeCaptureWithConfigResponse:(NSDictionary *)configResponse item:(NSDictionary *)item viewController:(UIViewController *)viewController;

/// For internal use. Legacy fallback for compare flow: searches for an existing session by barcode and fetches the compare config.
- (void)searchAndFetchConfigForCompareWithBarcode:(NSString *)barcode
                                         metadata:(NSDictionary *)metadata
                                   viewController:(UIViewController *)viewController;

@end

NS_ASSUME_NONNULL_END
