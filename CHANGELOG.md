# Changelog

## 2.3.10

EntrupySDK 2.3.10 is distributed only through Swift Package Manager and fixes how the SDK handles background URL session events that your app forwards to it. Apps that already install the SDK with Swift Package Manager need no code changes.

### Breaking changes

- EntrupySDK is no longer published to CocoaPods, starting with this version. If you install the SDK with CocoaPods, remove it from your `Podfile` and add EntrupySDK as a Swift Package Manager dependency instead.

### Background session fixes

- `interceptApplication(_:handleEventsForBackgroundURLSession:completionHandler:)` now stores the completion handler only for the SDK's own background download session, so a handler from one of your app's own background sessions can no longer replace it.
- The SDK now ignores events for background sessions it does not own and never calls their completion handlers, so your app keeps completing its own background sessions itself.
- The SDK now calls the completion handler for its own background download session exactly once.
