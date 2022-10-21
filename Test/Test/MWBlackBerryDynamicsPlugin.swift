//
//  MWVideoGridPlugin.swift
//  MWVideoGridPlugin
//
//  Created by Jonathan Flintham on 24/11/2020.
//

import Foundation
import MobileWorkflowCore

enum BlackBerryCoreServiceType: ServiceType {
    case network
    
    var typeName: String {
        return NetworkAsyncTaskService.typeName
    }
    
    func buildService(with config: ServiceConfiguration) throws -> AsyncTaskService? {
        guard config.type == self.typeName else { return nil }
        return NetworkAsyncTaskService(urlSession: .shared)
    }
}


public struct MWBlackBerryDynamicsPlugin: Plugin {
    
    public static var allStepsTypes: [StepType] {
        return MWBlackBerryDynamicsStepType.allCases
    }
    public static var networkServiceType: ServiceType {
        return BlackBerryCoreServiceType.network
    }
    
    public static var asyncTaskServices: [AsyncTaskService] = [BBPDFService()]
}

enum MWBlackBerryDynamicsStepType: String, StepType, CaseIterable {
    case bbdEmail = "io.mobileworkflow.bbd.email"
    
    var typeName: String {
        return self.rawValue
    }
    
    var stepClass: BuildableStep.Type {
        switch self {
        case .bbdEmail: return MWBlackBerryDynamicsEmailStep.self
        }
    }
}

enum L10n {
    static let install = "Install"
    static let cancel = "Cancel"
    static let appNotFoundTitle = "App Not Found"
    static let appNotFoundMessage = "Install the BlackBerry Work App from the App Store"
}
