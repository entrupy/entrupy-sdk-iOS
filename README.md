# EntrupySDK iOS

The Entrupy SDK for iOS allows you to integrate Entrupy's authentication functionality into your Swift or Objective-C app.

## Registering your application
Contact developer@entrupy.com to get your app’s bundle ID registered with entrupy. Include details about how you plan to use Entrupy in your app. If approved, you will be issued a License Key to use the SDK and credentials to run this app. 

## Requirements

- iOS 15.8 or higher
- Swift 5.x

## Installation

### Swift Package Manager (SPM)

To integrate `EntrupySDK` into your Xcode project:

1. Select **File** > **Add Packages...**
2. Enter the repository URL: `https://github.com/entrupy/entrupy-sdk-iOS.git`
3. Select package `entrupy-sdk-ios`.  
4. Set the **Dependency Rule** to **Up to Next Major Version**.  
5. Click **Add Package**.  
6. In the **Choose Package Products** prompt, add the library to your app target.

### CocoaPods

1.  Add the Entrupy SDK to your `Podfile`:

    ```ruby
    platform :ios, '15.8'
    use_frameworks!

    target 'YourAppTarget' do
      pod 'EntrupySDK', '~> X.X.X' # Replace X.X.X with the latest SDK version
    end
    ```
    note : 
    Refer to the SDK's release page for the latest version number - [link](https://github.com/entrupy/entrupy-sdk-iOS/releases)

2.  Run `pod install` in your project directory from the terminal.
3.  Open the generated `.xcworkspace` file in Xcode and build your project.

## Usage

For detailed documentation on how to use the SDK, please visit the [Entrupy Developer Portal](https://developer.entrupy.com/docs/mobile-sdks/ios/overview).

## License

The Entrupy SDK is released under a Commercial license. See `LICENSE` for more details.

