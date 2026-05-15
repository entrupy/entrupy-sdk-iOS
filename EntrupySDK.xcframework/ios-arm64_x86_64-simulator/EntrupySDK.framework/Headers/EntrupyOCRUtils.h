//
//  EntrupyOCRUtils.h
//  EntrupySDK
//
//  Created by Felipe Garcia on 22/07/2024.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface EntrupyOCRUtils : NSObject

/// List of valid/accepted OCR Rules
+ (NSArray *)ocrRules;

/**
 Given the item validate if is a valid/accepted OCR item.
 
 - Parameters:
   - item: TRUE if in the valid OCR Items
 
 - Returns: BOOL
*/
+ (BOOL)isSupportedOCR:(NSString *)item;

/**
 Return the first item from special items list match one in the accepted OCR List.
 
 - Parameters:
   - specialItems: List of special items
 
 - Returns: NSString
*/
+ (NSString *)matchOCRItem:(NSArray*)specialItems;

@end

NS_ASSUME_NONNULL_END
