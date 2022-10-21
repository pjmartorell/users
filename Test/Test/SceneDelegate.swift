//
//  SceneDelegate.swift
//  MobileWorkflowTemplate
//
//  Created by Igor Ferreira on 11/05/2020.
//  Copyright © 2020 Future Workshops. All rights reserved.
//

import UIKit
import MobileWorkflowCore
import MWFormsPlugin

class SceneDelegate: UIResponder, UIWindowSceneDelegate {

    var window: UIWindow?
    private var urlSchemeManagers: [URLSchemeManager] = []
    private var rootViewController: UIViewController!
    private var rootCoordinator: RootCoordinator!
    
    private var blackBerryDynamics = BlackBerryDynamics.shared
    
    /// This is the path for the app license
    private var licensePath: String? { Bundle.main.path(forResource: "mobileworkflow", ofType: "license") }
    
    func scene(_ scene: UIScene, willConnectTo session: UISceneSession, options connectionOptions: UIScene.ConnectionOptions) {
        guard let windowScene = scene as? UIWindowScene else { return }
        
        var dependencies = AppConfigurationDependencies.default(withAppId: Bundle.main.bundleIdentifier ?? "", plugins: [MWFormsPluginStruct.self,MobileWorkflowStruct.self,Struct.self], eventDelegator: UIApplication.shared.delegate as? AppEventDelegator, queueControllerProvider: UIApplication.shared.delegate as? QueueControllerProvider)
        dependencies.fileManager = self.blackBerryDynamics.fileManager
        
        let manager = AppConfigurationManager(dependencies: dependencies)
        
        let preferredConfigurations = self.preferredConfigurations(urlContexts: connectionOptions.urlContexts)
		
		self.rootCoordinator = RootCoordinator(
		    licensePath: self.licensePath,
		    manager: manager,
		    preferredConfigurations: preferredConfigurations
		)

		let window = UIWindow(windowScene: windowScene)
		self.window = window

		self.blackBerryDynamics.performAuth { result in
		    switch result {
		    case .success:
		        self.rootCoordinator.start(in: window)
		    case .failure(let error):
		        print(error.localizedDescription)
		    }
		}
    }
    
    func scene(_ scene: UIScene, openURLContexts URLContexts: Set<UIOpenURLContext>) {
        guard let context = self.urlSchemeManagers.firstValidConfiguration(from: URLContexts) else { return }
        self.rootCoordinator.loadAppConfiguration(context, animated: true)
    }
}

extension SceneDelegate {
    
    private func preferredConfigurations(urlContexts: Set<UIOpenURLContext>) -> [AppConfigurationContext] {
        
        var preferredConfigurations = [AppConfigurationContext]()
        
        if let appPath = Bundle.main.path(forResource: "app", ofType: "json") {
            preferredConfigurations.append(.file(path: appPath, serverId: 3))
        }
        
        return preferredConfigurations
    }
}
