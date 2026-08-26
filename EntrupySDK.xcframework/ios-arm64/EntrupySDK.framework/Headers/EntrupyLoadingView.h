//
//  EntrupyLoadingView.h
//  entrupy
//
//  Created by Dharini Raghavan on 5/10/18.
//  Copyright © 2018 Entrupy Inc. All rights reserved.
//

#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN

/// Overlay spinner side length (40). Compact/XIB default is 30; button/inline is 16.
FOUNDATION_EXPORT const CGFloat EntrupyLoadingOverlaySpinnerSize;
FOUNDATION_EXPORT const CGFloat EntrupyLoadingCompactSpinnerSize;
FOUNDATION_EXPORT const CGFloat EntrupyLoadingButtonSpinnerSize;

/// Branded frame-based loading spinner (`refresh1`…`refresh8`).
/// Use as a blocking overlay (blur / solid background) or as a compact inline spinner.
@interface EntrupyLoadingView: UIView

@property (strong, nonatomic) UIImageView *spinner;
@property (strong, nonatomic) UILabel *banner;

/// Default spinner side length when not in compact mode (40). Compact default is 30.
@property (nonatomic, assign) CGFloat spinnerSize;

/// When YES, spinner is sized for inline/cell use and does not block touches by default.
@property (nonatomic, assign, getter=isCompact) BOOL compact;

/// When YES, a visible spinner intercepts touches so they don't reach views underneath.
/// Overlay (`setupOverlayOnSuperview:`) and XIB hosts default to YES; compact defaults to NO.
/// `-showSpinner:` (view-controller mount) forces NO. Blur variants force YES when not compact.
/// Pass-through is via `hitTest:withEvent:` so a shown spinner stays in the accessibility tree.
@property (nonatomic, assign) BOOL blocksTouches;

-(void) showSpinner;
-(void) showSpinnerWithBlur;
/// Positions the spinner at window-space point `(x, y)` (same space as `UIScreen.bounds` / `convertPoint:fromView:nil`).
-(void) showSpinnerAt: (CGFloat) x  y:(CGFloat) y;
-(void) showSpinnerWithBanner: (NSString *) text;
-(void) showSpinnerWithBlurAndBanner:(NSString*)text;
/// Positions the spinner at window-space point `(x, y)` and shows `text` above it.
-(void) showSpinnerAt: (CGFloat) x  y:(CGFloat) y withBanner:(NSString *) text;
-(void) hideSpinner;
-(void) hideSpinnerAnimated:(void(^ __nullable)(void))completed;

/// Pins this view to `superview` edges as a full-bleed overlay (replaces EntrupyActivityIndicatorView).
/// Starts hidden. When shown, intercepts touches unless `blocksTouches` is set to NO.
- (void)setupOverlayOnSuperview:(UIView *)superview backgroundColor:(UIColor * _Nullable)backgroundColor NS_SWIFT_NAME(setupOverlay(onSuperview:backgroundColor:));

/// Configures this view as a compact inline spinner of the given side length.
- (void)configureCompactWithSize:(CGFloat)size NS_SWIFT_NAME(configureCompact(withSize:));

/// Mounts self on `viewController.view`, falling back to the key window when that view is not yet in a window.
- (void) showSpinner:(UIViewController*)viewController;
- (void) hideSpinnerFromView;

@end

NS_ASSUME_NONNULL_END
