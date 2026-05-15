//
//  ObjcEntrupyImageAnalysisAdapter.h
//  EntrupySDK
//
//  Created on April 14, 2026 by Dharini.
//
//  Pure Objective-C wrapper around EntrupyImageAnalysisUtils.
//  This header does NOT import EntrupyImageAnalysisUtils.h — the C++ implementation
//  is kept entirely in the .m translation unit. As a result this header is safe to
//  import from Swift.
//

#import <UIKit/UIKit.h>
#import <AVFoundation/AVFoundation.h>
#import <CoreMedia/CoreMedia.h>

@class EntrupyCaptureTestArgsJSON;

NS_ASSUME_NONNULL_BEGIN

// MARK: - EntrupyCaptureImageAnalysisDelegate
// Swift-callable delegate that mirrors EntrupyImageAnalysisUtilsDelegate.
// All parameter types are ObjC-compatible (no C++ or OpenCV types).

@protocol EntrupyCaptureImageAnalysisDelegate <NSObject>

// MARK: Tilt / blur live-feedback
- (void)imageAnalysisDidDrawCircleAtX:(int)cx circleY:(int)cy circleR:(int)cr
                             srcWidth:(CGFloat)srcWidth srcHeight:(CGFloat)srcHeight;
- (void)imageAnalysisDidClearTiltBlurPointer;
- (void)imageAnalysisDidRemoveCircleCenterLayer;
- (void)imageAnalysisDidRemoveCircleLayer;
- (void)imageAnalysisDidBlockCamera;
- (void)imageAnalysisDidUnblockCamera;
- (BOOL)imageAnalysisIsDebugHeatMapOn;
- (void)imageAnalysisDidShowFeedbackView;
- (void)imageAnalysisDidHideFeedbackView;
- (void)imageAnalysisDidSetModelImageToNil;
- (void)imageAnalysisDidSetHeatMapImageToNil;
- (void)imageAnalysisDidSetModelImage:(UIImage *)image;
- (void)imageAnalysisDidSetHeatmapImage:(UIImage *)image;
- (void)imageAnalysisDidSetHeatmapBadnessLabel:(NSString *)text;
- (void)imageAnalysisDidSetupBlurProgressMessage:(NSString *)message;
- (void)imageAnalysisDidDetectLEDOrMacroError:(BOOL)displayAlert;
- (void)imageAnalysisDidResolveLEDOrMacroError;

// MARK: Blur detection — per-frame result
- (void)imageAnalysisDidFinishBlurDetectionOnFrameWithSrcWidth:(CGFloat)srcWidth
                                                     srcHeight:(CGFloat)srcHeight
                                                       circleX:(NSInteger)x
                                                       circleY:(NSInteger)y
                                                       circleR:(NSInteger)r
                                            blurMagnitudeLevel:(UIColor *)magnitudeLevel
                                                  blurSumLevel:(UIColor *)sumLevel
                                                 blurMagnitude:(CGFloat)magnitude
                                                     blurAngle:(CGFloat)angle;

// MARK: Blur detection — still
- (void)imageAnalysisDidFinishBlurDetectionOnStill:(NSString *)blurPhotoResult
                                   progressMessage:(NSString *)message
                                          forImage:(UIImage *)image
                                        forPreview:(UIImage *)preview;

// MARK: Region segmentation — per-frame result
- (void)imageAnalysisDidFinishRegionSegmentationOnFrame:(NSArray *)diceCoeffs
                                             diceCenters:(NSArray *)diceCenters
                                             inputFrame:(nullable UIImage *)modelInput
                                             resultMask:(nullable UIImage *)resultMask;

// MARK: Region segmentation — still
- (void)imageAnalysisDidFinishRegionSegmentationOnStill:(NSArray *)diceCoeffs
                                             stillImage:(nullable UIImage *)still
                                           previewImage:(nullable UIImage *)preview
                                              rawPhoto:(nullable AVCapturePhoto *)photo;

// MARK: Rectangle detection
- (void)imageAnalysisDidFinishDetectingRectangleInImage:(UIImage *)image
                                              atCorners:(NSArray *)corners;
- (void)imageAnalysisDidFinishDetectingRectangleInFrameAtCorners:(NSArray *)corners
                                                      frameWidth:(CGFloat)width
                                                     frameHeight:(CGFloat)height;

// MARK: OCR
- (void)imageAnalysisDidFinishReadingTextFromImage:(UIImage *)image
                                      previewImage:(UIImage *)preview
                                              text:(NSArray *)text;
- (void)imageAnalysisDidFinishReadingTextFromFrame:(NSArray *)text
                              rawTextWithConfidence:(nullable id)rawText;

// MARK: Barcode (live frame scan)
- (void)imageAnalysisDidFinishReadingBarcodeFromFrame:(NSString *)value
                                           symbology:(NSString *)symbology
                                       atBarcodeRect:(NSArray *)corners
                                          frameWidth:(CGFloat)width
                                         frameHeight:(CGFloat)height;

@end


// MARK: - ObjcEntrupyImageAnalysisAdapter
// Wraps one EntrupyImageAnalysisUtils instance and forwards all callbacks to
// the Swift-visible EntrupyCaptureImageAnalysisDelegate.

@interface ObjcEntrupyImageAnalysisAdapter : NSObject

@property (nonatomic, weak, nullable) id<EntrupyCaptureImageAnalysisDelegate> delegate;

/// Vision-only helper (`[[EntrupyImageAnalysisUtils alloc] init]`); matches ad-hoc use in `EntrupyCaptureViewController`.
- (instancetype)init;

/// Initialises the underlying utility with a numeric model identifier.
/// Matches `-[EntrupyImageAnalysisUtils initWithModel:]`.
- (instancetype)initWithModel:(NSInteger)model;

/// Initialises the underlying utility with a named CoreML model.
/// Matches `-[EntrupyImageAnalysisUtils initWithModelName:outputClass:regionExifOrientation:isStaticModel:]`.
- (instancetype)initWithModelName:(NSString *)modelName
                      outputClass:(NSInteger)classIndex
            regionExifOrientation:(NSString *)orientation
                    isStaticModel:(BOOL)isStaticModel;

// MARK: Blur detection

/// Run blur detection on a still image.
- (void)runBlurDetectionOnStill:(UIImage *)still
                   previewImage:(UIImage *)preview
                      forConfig:(EntrupyCaptureTestArgsJSON *)configParams;

/// Run blur detection on a video frame (pixel buffer).
- (void)runBlurDetectionOnFrame:(CVPixelBufferRef)pixelBuffer
               runCircleFinding:(BOOL)shouldRunCircleFinding
                  runPrediction:(BOOL)shouldRunPrediction
                        frameNo:(NSInteger)frameNo
                      forConfig:(EntrupyCaptureTestArgsJSON *)configParams;

// MARK: Region segmentation

/// Calculates anchor points for overlay alignment; must be called once per region before frame processing.
- (NSArray *)setupOverlay:(UIImage *)overlay;

/// Run DeepLab segmentation on a video frame.
- (void)runDeepLabSegmentationOnFrame:(CVPixelBufferRef)pixelBuffer
                              frameNo:(NSInteger)frameNo
                      confidenceScore:(CGFloat)confidenceScore;

/// Run DeepLab segmentation on a captured still.
- (void)runDeepLabSegmentationOnStill:(UIImage *)still
                         previewImage:(UIImage *)previewImage
                             rawPhoto:(nullable AVCapturePhoto *)photo
                      confidenceScore:(CGFloat)confidenceScore;

// MARK: Rectangle detection

- (void)detectRectangleInImage:(UIImage *)image NS_SWIFT_NAME(detectRectangle(in:));
- (void)detectRectangleInFrame:(CVPixelBufferRef)pixelBuffer;

// MARK: OCR

- (void)readTextFromImage:(UIImage *)image
             previewImage:(UIImage *)previewImage
              customWords:(NSArray *)customWords;

- (void)readTextFromFrame:(CVPixelBufferRef)pixelBuffer
              customWords:(NSArray *)customWords;

// MARK: Barcode

- (void)readBarcodeFromFrame:(CMSampleBufferRef)sampleBuffer
        supportedSymbologies:(NSArray *)symbologies;

@end

NS_ASSUME_NONNULL_END
