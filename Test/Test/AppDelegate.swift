//
//  AppDelegate.swift
//  Test
//
//  Copyright © Future Workshops. All rights reserved.
//

import UIKit
import MobileWorkflowCore

@UIApplicationMain
class AppDelegate: UIResponder, UIApplicationDelegate, AppEventDelegator {

    weak var eventDelegate: AppEventDelegate?

    func application(_ application: UIApplication, didFinishLaunchingWithOptions launchOptions: [UIApplication.LaunchOptionsKey: Any]?) -> Bool {

        return true
    }
    
    func application(_ application: UIApplication, configurationForConnecting connectingSceneSession: UISceneSession, options: UIScene.ConnectionOptions) -> UISceneConfiguration {
        return UISceneConfiguration(name: "Default Configuration", sessionRole: connectingSceneSession.role)
    }
    
    func application(_ app: UIApplication, open url: URL, options: [UIApplication.OpenURLOptionsKey : Any] = [:]) -> Bool {
        self.eventDelegate?.application(app, open: url, options: options) ?? false
    }
    



    func application(_ application: UIApplication, shouldAllowExtensionPointIdentifier extensionPointIdentifier: UIApplication.ExtensionPointIdentifier) -> Bool {
        return false
    }

}