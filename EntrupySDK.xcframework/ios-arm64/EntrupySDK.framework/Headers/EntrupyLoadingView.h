//
//  LoadingView.h
//  entrupy
//
//  Created by Dharini Raghavan on 5/10/18.
//  Copyright © 2018 Entrupy Inc. All rights reserved.
//

#import <UIKit/UIKit.h>

@interface EntrupyLoadingView: UIView

@property (strong, nonatomic) UIImageView *spinner;
@property (strong, nonatomic) UILabel *banner;


-(void) showSpinner;
-(void) showSpinnerWithBlur;
-(void) showSpinnerAt: (CGFloat) x  y:(CGFloat) y;
-(void) showSpinnerWithBanner: (NSString *) text;
-(void) showSpinnerWithBlurAndBanner:(NSString*)text;
-(void) showSpinnerAt: (CGFloat) x  y:(CGFloat) y withBanner:(NSString *) text;
-(void) hideSpinner;
-(void) hideSpinnerAnimated:(void(^__nullable)(void))completed;

/// Used when we want to add and remove from any view controller
- (void) showSpinner:(UIViewController*)viewController;
- (void) hideSpinnerFromView;

@end
