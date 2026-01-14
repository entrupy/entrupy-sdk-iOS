# EntrupySDK iOS

The Entrupy SDK for iOS allows you to integrate Entrupy's authentication functionality into your Swift or Objective-C app.

## Requirements

- iOS 15.8 or higher
- Swift 5.x

## Installation

### Swift Package Manager (SPM)

> [!IMPORTANT]
> Swift Package Manager support is available starting from version **2.0.3** and later.

To integrate `EntrupySDK` into your Xcode project:

1. Select **File** > **Add Packages...**
2. Enter the repository URL: `https://github.com/entrupy/entrupy-sdk-iOS.git`
3. Set the **Dependency Rule** to **Up to Next Major Version** and use `2.0.3`.
4. Select the `entrupy-sdk-ios` library and add it to your app target.

### CocoaPods

1. Open your iOS project and increase the min SDK target to **iOS 15.8+**.
2. Update your `Podfile` to include the platform and the `EntrupySDK` pod:

```ruby
platform :ios, '15.8'

target 'YOUR_TARGET_NAME' do
    # ...
    pod 'EntrupySDK'
    # ...
end
```

3. Open terminal in the root directory and run:

```bash
pod install
```

## Usage

For detailed documentation on how to use the SDK, please visit the [Entrupy Developer Portal](https://developer.entrupy.com/docs/mobile-sdks/ios/overview).

## License

The Entrupy SDK is released under a Commercial license. See `LICENSE` for more details.

