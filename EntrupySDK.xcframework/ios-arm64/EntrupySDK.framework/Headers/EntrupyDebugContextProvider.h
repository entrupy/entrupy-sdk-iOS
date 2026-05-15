//
//  EntrupyDebugContextProvider.h
//  EntrupySDK
//

#import <Foundation/Foundation.h>
@class EntrupyCaptureArtifact;

NS_ASSUME_NONNULL_BEGIN

@protocol EntrupyDebugContextProvider <NSObject>
@optional
/// Returns all capture artifacts for the current session
- (NSArray<EntrupyCaptureArtifact *> *)debugAllArtifacts;
/// Returns the currently active capture artifact
- (EntrupyCaptureArtifact * _Nullable)debugCurrentArtifact;
/// Whether the SnapIQ debug overlay is currently shown
- (BOOL)snapIQDebugOverlayEnabled;
/// Toggle the SnapIQ debug overlay on/off
- (void)setSnapIQDebugOverlayEnabled:(BOOL)enabled;
@end

NS_ASSUME_NONNULL_END
