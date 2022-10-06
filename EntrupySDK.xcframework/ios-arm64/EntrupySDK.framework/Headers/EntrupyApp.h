//
//  EntrupyApp.h
//  EntrupySDK
//
//  Created by Muhammad Waqas on 30/06/2022.
//

#import <Foundation/Foundation.h>
#import "EntrupyAppProtocols.h"

NS_ASSUME_NONNULL_BEGIN

@interface EntrupyApp: NSObject<EntrupyAppProtocol>

@property (nonatomic, weak) id<EntrupyLoginDelegate> loginDelegate;
@property (nonatomic, weak) id<EntrupyConfigDelegate> configDelegate;
@property (nonatomic, weak) id<EntrupyCaptureDelegate> captureDelegate;
@property (nonatomic, weak) id<EntrupySearchDelegate> searchDelegate;

+ (instancetype)sharedInstance;

/**
 Fetches the configuration required for running the capture and search actions
 
 This function is optional to implement and can be called once from the viewDidAppear function of the View Controllers invoking the SDK’s startCapture/searchSubmissions method. It fetches configuration required for performing these actions. If this is not explicitly called this’ll be implicitly handled by the sdk before launching the capture workflow or beginning the search causing a few seconds overhead.
 
 - Returns: void
 
 ```swift
 // Swift
 if ( EntrupyApp.sharedInstance().isAuthorizationValid()) {
     //Implement EntrupyConfigDelegate
     EntrupyApp.sharedInstance().configDelegate = self
     
     // Set configType to ConfigTypeShort if you want a shorter capture workflow during development
     EntrupyApp.sharedInstance().fetchConfigurationType(EntrupyConfigType.ConfigTypeFull)
 }
 
 ```
 
 ```
 Implement the "EntrupyConfigDelegate" protocol to handle responses from this function
 ```
 
 
 - Parameter configType: ConfigTypeShort: Short config is used to launch a shorter capture workflow. This is only to be used for dev testing. All submissions with the short config will be marked Invalid.
 ConfigTypeFull: The regular full length config.
 
 */
-(void) fetchConfigurationType: (EntrupyConfigType) configType;


/**
 Starts the capture workflow for performing an authentication
 
 Call this function in response to a user event such as tapping an ‘Authenticate’ button. This function launches Entrupy’s capture workflow modally on the existing view controller. Capture not completed within 2 hours will automatically be aborted and the error delegate will be sent.
 
  
 - Parameter item: A dictionary containing details about the item to be authenticated
 - Parameter viewController: A reference to the view controller launching the Entrupy capture workflow.
 
 - Returns: void
 
 
 ```
 Implement the "EntrupyCaptureDelegate" to handle responses
 from this method
 ```
 
 * Example usage:
 
 
 ```swift
 
 // Swift
 
 // Create a sneaker metadata dictionary with the following fields
 //
 // brand: the item’s brand.
 // style_name: the item’s full name. Example: “Jordan 1 Retro High White University Blue Black”
 // us_size(optional): the item’s US Size. Example: 8, 8.5, 8.5Y.
 // upc(optional): the item’s UPC.
 // style_code(optional):the item’s style code (AKA “style id”). Example: 555088-134
 // customer_item_id(optional): the unique identifier you use for the item being authenticated (max length = 256).
 // brand and style_name are mandatory
 
 let input: Dictionary = ["brand": "Nike", "style_name": "Air Jordan 1 Retro  High OG SP'", "us_size": "9.5", "upc": "00195244532483", "style_code": "d07097-100", "customer_item_id": "sku-xyz"]
 
 // Check if authorization token is valid
 if ( EntrupyApp.sharedInstance().isAuthorizationValid()) {
 
     // Implement EntrupyCaptureDelegate
     EntrupyApp.sharedInstance().captureDelegate = self
     
     // Pass the sneaker metadata and a reference to the presenting view controller
     EntrupyApp.sharedInstance().startCapture(forItem: input, viewController: self)
 }
 ```
 
 */
-(void) startCaptureForItem:(NSDictionary *)item viewController:(UIViewController *)viewController;


/**
 Fetches past submissions.
 
 Implement searchSubmissions to fetch past authentications. The search response is paginated into pages of ‘paginationLimit’ items each. The maximum number of items that can be requested per page is 25. The function takes a pageCursor parameter which determines the page that has to be fetched. Pass an empty array for pageCursor to fetch the first page.
 Repeat the searchSubmissions call, setting the pageCursor with the "next_cursor" array received in the delegate response of the previous call until all pages have been retrieved. If the “next_cursor” array returned is nil or empty it indicates that the last page has been reached.
 
 [SDK web documentation]:
 https://developer.entrupy.com/v1_2.html/v1_2_entrupy_sdk.html
 
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
 
 [SDK web documentation]:
 https://developer.entrupy.com/v1_2.html/v1_2_entrupy_sdk.html
 
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

@end

NS_ASSUME_NONNULL_END
