Pod::Spec.new do |spec|
  spec.name               = "EntrupySDK"
  spec.version            = "1.2.9"
  spec.summary            = "Entrupy SDK"
  spec.description        = "The Entrupy SDK for iOS allows you to integrate Entrupy's authentication functionality into your Swift or Obj-C app"
  spec.homepage           = "https://www.entrupy.com"
  spec.documentation_url  = "https://developer.entrupy.com/docs/mobile-sdks/ios/overview"
  spec.license            = { :type => "Commercial", :file => "LICENSE" }
  spec.author             = { "Entrupy Company" => "support@entrupy.com" }
  spec.platform           = :ios, "15.8"
  spec.source             = { :git => "https://github.com/entrupy/entrupy-sneakerauthentication-sdk-iOS.git", :tag => "spec.version"}
  spec.vendored_frameworks = "EntrupySDK.xcframework"
  spec.preserve_paths      = "EntrupySDK.xcframework"
end
