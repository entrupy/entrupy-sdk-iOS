//
//  EntrupyErrorCode.h
//  EntrupySDK
//
//  Created by Muhammad Waqas on 01/07/2022.
//


//MARK: - ErrorCode

typedef NS_ENUM(NSUInteger, EntrupyErrorCode) {
    ErrorCodeOfflineAccess, //Could not connect to the Internet
    ErrorCodeBadRequest, //Incorrect headers, missing/incorrect parameters
    ErrorCodeUnauthorizedAccess, //The authorization token is expired, revoked, request is malformed, or invalid for other reasons
    ErrorCodeForbiddenError, //The bundle ID is invalid, re-using signed authorization requests.
    ErrorCodeInternalServerError,//Entrupy Server error
    ErrorCodeRequestTimeoutError,//The request timedout due to a client-side delay
    ErrorCodeServerTimeoutError, //The Entrupy server timedout
    ErrorCodeTooManyRequests,    //Rate Limit reached
    ErrorCodeImageUploadError,   //Error uploading images
    ErrorCodeUserDeniedPermissions, //The user denied necessary permissions
    ErrorCodeUnknownError //An unknown error occurred
};
