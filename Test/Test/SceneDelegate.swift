//
//  SceneDelegate.swift
//  Test
//
//  Copyright © Future Workshops. All rights reserved.
//
import UIKit
import MobileWorkflowCore

import MWFormsPlugin

class SceneDelegate: MWSceneDelegate {
    
    override var licensePath: String? {
        //This path should point to the license file for this project
        Bundle.main.path(forResource: "mobileworkflow", ofType: "license")
    }
    
    override func scene(_ scene: UIScene, willConnectTo session: UISceneSession, options connectionOptions: UIScene.ConnectionOptions) {
        
        self.dependencies.plugins = [MWFormsPluginStruct.self,MobileWorkflowStruct.self]
        
        super.scene(scene, willConnectTo: session, options: connectionOptions)
    }
    
    override func preferredConfigurations(urlContexts: Set<UIOpenURLContext>) -> [AppConfigurationContext] {
        var preferredConfigurations = [AppConfigurationContext]()
        if let filePath = Bundle.main.path(forResource: "app", ofType: "json") {
            preferredConfigurations.append(.file(path: filePath, serverId: 3))
        }
        return preferredConfigurations
    }
}

