//
//  EntrupyConfigType.h
//  EntrupySDK
//
//  Created by Entrupy.
//

#ifndef EntrupyConfigType_h
#define EntrupyConfigType_h

typedef NS_ENUM(NSUInteger, EntrupyConfigType) {
    ConfigTypeDebug, //The debug config is used to launch a shorter capture workflow. This is only to be used for dev testing
    ConfigTypeProduction   //The production config loads the regular full length capture workflow
};

#endif /* EntrupyConfigType_h */
