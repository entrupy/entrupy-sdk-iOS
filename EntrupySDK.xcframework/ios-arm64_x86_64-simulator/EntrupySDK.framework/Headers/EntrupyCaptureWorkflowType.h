//
//  EntrupyCaptureWorkflowType.h
//  EntrupySDK
//
//  Created by Felipe Garcia on 02/06/2023.
//  Copyright © 2023 Entrupy Inc. All rights reserved.
//

/**
 The usage of this is intended for situations that you need to have different actions, reponse that are related to `A` specific resource
 */
typedef NS_ENUM(NSInteger, EntrupyCaptureWorkflowType) {
    fingerprintWorkflow, /// Used when we want to handle specific code and situations for start and use fingerprint
    retakeWorkflow, /// use it when we want to retake item, that was alright capture
    defaultWorkflow,
    flagDetailsWorkflow, /// programmatic getFlagDetailAPI
    flagResultWorkflow,  /// programmatic setFlag
    detailViewWorkflow,
    publicRetakeConfigRefreshWorkflow,
    marketEdgeWorkflow,
    flagReasonsWorkflow,
    flaggingViewWorkflow,  /// used in displayFlagViewForItemWithEntrupyID
    marketEdgeViewWorkflow, /// used in displayMarketEdgeViewForItemWithEntrupyID
    compareWorkflow, /// Used for compare flow where user scans barcode to search and compare items
    searchAuthenticationItemsWorkflow /// Used for searchAuthenticationItemsWithQuery
};
