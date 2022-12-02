Pod::Spec.new do |spec|
    spec.name               = "EntrupySDK"
    spec.version            = "1.2.0"
    spec.summary            = "Entrupy SDK"
    spec.description        = "The Entrupy SDK for iOS allows you to integrate Entrupy's sneaker authentication functionality into your Swift or Obj-C app"
    spec.homepage           = "https://www.entrupy.com"
    spec.documentation_url  = "https://developer.entrupy.com/v1_2.html/v1_2_entrupy_sdk.html"
    spec.license            = { :type => "Commercial", :file => "LICENSE" }
    spec.author             = { "Entrupy Inc." => "sneaker-support@entrupy.com" }
    spec.swift_version      = "5.3"
    spec.platform           = :ios, "14.0"
    spec.source             = { :git => "https://github.com/entrupy/entrupy-sdk-iOS.git", :tag => spec.version}

    spec.user_target_xcconfig = {
      'USER_HEADER_SEARCH_PATHS' => '"$(PODS_ROOT)/{PROJECT_NAME}/Release" "$(PODS_ROOT)/{PROJECT_NAME}/Release/{PROJECT_NAME}.xcframework/{XCFRAMEWORK_RELEASE_GROUP_DIR}/{PROJECT_NAME}.framework/Headers"',
      'FRAMEWORK_SEARCH_PATHS' => '"$(PODS_ROOT)/{PROJECT_NAME}/Release"'
    }

    spec.xcconfig = {
      'FRAMEWORK_SEARCH_PATHS' => '"${PODS_ROOT}/EntrupySDK" "${PODS_XCFRAMEWORKS_BUILD_DIR}/EntrupySDK"'
    }

    # Published binaries
    spec.vendored_frameworks = "EntrupySDK.xcframework"
  
    spec.pod_target_xcconfig = { 'EXCLUDED_ARCHS[sdk=iphonesimulator*]' => 'arm64' }
    spec.user_target_xcconfig = { 'EXCLUDED_ARCHS[sdk=iphonesimulator*]' => 'arm64' }
  end

