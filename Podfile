source 'https://cdn.cocoapods.org/'
source 'https://github.com/FutureWorkshops/MWPodspecs.git' # Use for Swift 5.5
# source 'https://github.com/FutureWorkshops/AppRailPreviewPodspecs.git' # Use for Swift 5.6


project 'Test/Test.xcodeproj'
platform :ios, '15.0'

inhibit_all_warnings!
use_frameworks!

target 'Test' do
  pod 'MWFormsPlugin', '~> 1.3.0'
  pod 'MobileWorkflow', '~> 2.1.4'
end

# Avoid signing pods
post_install do |installer|
  installer.pods_project.targets.each do |target|
    target.build_configurations.each do |config|
      config.build_settings['EXPANDED_CODE_SIGN_IDENTITY'] = ""
      config.build_settings['CODE_SIGNING_REQUIRED'] = "NO"
      config.build_settings['CODE_SIGNING_ALLOWED'] = "NO"
      config.build_settings['BUILD_LIBRARY_FOR_DISTRIBUTION'] = 'YES'
    end
  end
end
