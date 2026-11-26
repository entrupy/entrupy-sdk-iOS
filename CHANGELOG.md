# Changelog

## 2.3.10

EntrupySDK 2.3.10 is distributed only through Swift Package Manager and fixes how `interceptApplication(_:handleEventsForBackgroundURLSession:completionHandler:)` handles background sessions. Partners who already install the SDK with Swift Package Manager need no integration changes.

### Breaking changes

- EntrupySDK is no longer published to CocoaPods, starting with this version. If you install the SDK with CocoaPods, remove it from your `Podfile` and add it with Swift Package Manager instead.

### Distribution

- EntrupySDK now ships only through Swift Package Manager, and new versions are no longer pushed to CocoaPods.

### Background session fixes

- `interceptApplication(_:handleEventsForBackgroundURLSession:completionHandler:)` now keeps only the completion handler for the SDK's own background download session. A handler for one of your app's sessions can no longer replace it and be called by the SDK.
- Events for other background sessions are now ignored by the SDK, so your app must call the completion handler for its own sessions itself.
