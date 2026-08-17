//
//  EntrupyBarcodeCaptureViewController.h
//  EntrupySDK
//
//  Created by Felipe Garcia on 16/05/2023.
//  Copyright © 2023 Entrupy Inc. All rights reserved.
//

#import <UIKit/UIKit.h>

@class ObjcEntrupyCaptureSuccessActionView;
@class ObjcEntrupyCameraInformationView;

NS_ASSUME_NONNULL_BEGIN

@interface EntrupyBarcodeCaptureViewController : UIViewController

@property (nonatomic, copy) void (^entrupyBarcodeCaptureCallback)(NSString *barcode);
@property (nonatomic, copy) void (^entrupyBarcodeCaptureCancelCallback)(void);
@property (nonatomic, copy) void (^entrupyBarcodeCaptureNoCameraPermission)(NSString* errorMessage);

/// Optional secondary action (e.g. "Use Entrupy ID instead"). When nil the button is hidden
/// and no existing callers are affected. Set before presenting the view controller.
@property (nonatomic, copy, nullable) void (^entrupyBarcodeAlternateActionCallback)(NSString *value);

@property (weak, nonatomic) IBOutlet ObjcEntrupyCaptureSuccessActionView *successActionView;
@property (weak, nonatomic) IBOutlet UIView* enterBarCodeNoView;
@property (weak, nonatomic) IBOutlet UILabel* enterBarcodeLabel;
@property (weak, nonatomic) IBOutlet UIView* barcodeCaptureView;
@property (weak, nonatomic) IBOutlet UITextView* barcodeLabelField;
@property (strong, nonatomic) IBOutlet UIView *scanditView;
@property (strong, nonatomic) IBOutlet UIView *cameraFeedView;
@property (weak, nonatomic) IBOutlet UILabel* barcodeTitleLabel;
@property (weak, nonatomic) IBOutlet UILabel *topBarTitle;

@property (weak, nonatomic) IBOutlet ObjcEntrupyCameraInformationView* cameraInformationView;
@property (weak, nonatomic) IBOutlet UILabel* displayNameLabel;

-(void)setNavBarTitle:(NSString*_Nonnull)title;
-(void)setBottomBarTitle:(NSString*_Nonnull)title;
-(void)setInstructionText:(NSString*_Nonnull)text;
-(void)shouldAllowManualInput:(BOOL)allow;
-(void)setBarcodeInputUIConfig:(NSDictionary *_Nullable)config;
/// Sets the title and subtitle shown inside the manual-entry modal (ObjcEntrupyEditBarcodeViewController).
/// When not called the modal falls back to the scan/enter label string as the title.
-(void)setManualEntryTitle:(NSString *_Nullable)title subtitle:(NSString *_Nullable)subtitle;

// In the SDK FP Compare flow, if `customer_item_id` is provided via parameter, this barcode
// region is pre-filled. Update the UI to display the entered barcode state
// instead of the default "Scan Barcode" state.
-(void)setPrefilledBarcode:(NSString *_Nonnull)barcode;
-(void)refreshCapture;

/// Sets the label shown on the optional alternate-action button.
/// Must be called before the view controller is presented.
/// Has no effect when `entrupyBarcodeAlternateActionCallback` is nil.
-(void)setAlternateActionTitle:(NSString *_Nonnull)title;

/// Sets the title shown inside the text-field prompt that appears when the
/// alternate-action button is tapped. Defaults to the value passed to
/// `setAlternateActionTitle:` when not supplied.
-(void)setAlternateActionInputTitle:(NSString *_Nonnull)title;

@end

NS_ASSUME_NONNULL_END
