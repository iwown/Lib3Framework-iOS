Pod::Spec.new do |s|

s.name         = 'BLE3Framework'

s.version      = "4.7.2"

s.summary      = 'Used for iwown BLE smart band'

s.license      = 'MIT'

s.author       = { "xuezou" => "377949550@qq.com" }

s.homepage     = 'https://github.com/xuezou/Lib3Framework-iOS'

s.source       = { :git => "https://github.com/xuezou/Lib3Framework-iOS.git", :tag => s.version}

s.platform     = :ios

s.ios.deployment_target = "8.0"

s.frameworks = 'Foundation'

s.vendored_frameworks = 'BLE3Framework/BLE3Framework.framework'

s.requires_arc = true

end
