//
//  EntrupySessionNotifications.h
//  EntrupySDK
//
//  Public notification name, ecodes, and userInfo keys for the
//  session-ended (revoked token) flow. Kept separate from EntrupyNetwork.h
//  so the networking API is not exposed as public SDK surface.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

/// Posted when the backend reports the session token as revoked
/// (HTTP 403 with `authorized: false` and ecode `invalid_session_token`).
FOUNDATION_EXPORT NSString *const KEntrupySessionEndedNotification;
/// Backend ecode identifying a revoked session token.
FOUNDATION_EXPORT NSString *const KEntrupyInvalidSessionTokenEcode;
/// `userInfo` key carrying the login generation captured when the request was issued (NSNumber).
FOUNDATION_EXPORT NSString *const KEntrupySessionGenerationUserInfoKey;
/// NSUserDefaults key for the login generation counter, incremented on every login.
FOUNDATION_EXPORT NSString *const KEntrupySessionGenerationDefaultsKey;
/// `userInfo` key carrying the HTTP status code that ended the session (NSNumber).
FOUNDATION_EXPORT NSString *const KEntrupySessionEndedStatusCodeUserInfoKey;
/// `userInfo` key carrying the backend ecode string that ended the session.
FOUNDATION_EXPORT NSString *const KEntrupySessionEndedEcodeUserInfoKey;

NS_ASSUME_NONNULL_END
