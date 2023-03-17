Pod::Spec.new do |spec|
  spec.name               = "EntrupySDK"
  spec.version            = "1.2.3"
  spec.summary            = "Entrupy SDK"
  spec.description        = "The Entrupy SDK for iOS allows you to integrate Entrupy's sneaker authentication functionality into your Swift or Obj-C app"
  spec.homepage           = "https://www.entrupy.com"
  spec.documentation_url  = "https://developer.entrupy.com/v1_2_entrupy_sdk.html"
  spec.license            = { :type => "Commercial", :file => "LICENSE" }
  spec.author             = { "Entrupy Inc." => "sneaker-support@entrupy.com" }
  spec.platform           = :ios, "14.0"
  spec.source             = { :git => "https://github.com/entrupy/entrupy-sdk-iOS.git", :tag => spec.version}
  spec.vendored_frameworks = "EntrupySDK.xcframework"
  spec.preserve_paths      = "EntrupySDK.xcframework"
end

