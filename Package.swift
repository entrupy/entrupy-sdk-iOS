// swift-tools-version: 5.7
// The swift-tools-version declares the minimum version of Swift required to build this package.

import PackageDescription

let frameworkPath = "EntrupySDK.xcframework"

let package = Package(
    name: "entrupy-sdk-ios",
    defaultLocalization: "en",
    platforms: [
        .iOS("15.8")
    ],
    products: [
        .library(
            name: "entrupy-sdk-ios",
            targets: ["entrupy-sdk-ios"]
        ),
    ],
    targets: [
        .target(
            name: "entrupy-sdk-ios",
            dependencies: ["EntrupySDK"]
        ),
        .binaryTarget(
            name: "EntrupySDK",
            path: frameworkPath
        )
    ]
)
