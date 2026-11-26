# Changelog

## 2.3.10

This release fixes how the SDK handles background URL session events forwarded from your app delegate. It also ends CocoaPods distribution, so the SDK now ships only through Swift Package Manager; apps that already use Swift Package Manager need no code changes.

### Breaking changes

- EntrupySDK is no longer published to CocoaPods, starting with this version. If you install the SDK with CocoaPods, switch to Swift Package Manager to get this and later versions.

### Background session fixes

- `interceptApplication(_:handleEventsForBackgroundURLSession:completionHandler:)` now keeps the completion handler only for the SDK's own background session, so the SDK no longer calls your app's handler in place of its own.
- Events for your app's other background sessions are now logged and ignored by the SDK, so your app must call the completion handlers for its own sessions.
