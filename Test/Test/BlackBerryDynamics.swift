//
//  BlackBerryDynamics.swift
//  MobileWorkflowBlackBerryDynamicsPlugin
//
//  Created by Jonathan Flintham on 12/11/2020.
//

import Foundation
import MobileWorkflowCore
import BlackBerryDynamics.Runtime
import BlackBerryDynamics.SecureStore.File

public enum BlackBerryDynamicsError: LocalizedError {
    case auth(event: GDAppResultCode)
    case serviceAppNotFound(service: String)
    case desiredAppNotFound(app: String)
    
    public var errorDescription: String? {
        switch self {
        case .auth(let event):
            return "BlackBerry Dynamics authorization failed: \(event)"
        case .serviceAppNotFound(let service):
            return "No app found for service: \(service)"
        case .desiredAppNotFound(let app):
            return "Service app not found: \(app)"
        }
    }
    
    var localizedDescription: String {
        return self.errorDescription ?? "Unknown error occurred"
    }
}

public class BlackBerryDynamics: NSObject {
    static var shared = BlackBerryDynamics()
    
    private var good: GDiOS?
    private(set) var started: Bool = false
    private var preAuthCompletion: ((Result<String, Error>) -> Void)?
    
    public let fileManager = GDFileManager.default()
    
    private(set) var serviceClient: BBDServiceClient?
}

extension GDFileManager {
    open override func inputStreamFor(fileAtPath path: String) -> InputStream? {
        return try? GDFileManager.getReadStream(path)
    }
    open override func outputStreamFor(fileAtPath path: String, append: Bool) -> OutputStream? {
        return try? GDFileManager.getWriteStream(path, appendmode: true)
    }
}

extension BlackBerryDynamics {
    
    public func performAuth(completion: @escaping (Result<String, Error>) -> Void) {
        self.preAuthCompletion = completion
        self.authorize()
    }
    
    private func authorize() {
        let good = GDiOS.sharedInstance()
        self.good = good
        self.serviceClient = BBDServiceClient(good: good, fileManager: self.fileManager)

        self.started = false

        // Show the Good Authentication UI.
        self.good?.authorize(self)
    }
}

extension BlackBerryDynamics: GDiOSDelegate {

    public func handle(_ anEvent: GDAppEvent) {
        switch anEvent.type {
        case .authorized:
            self.onAuthorized(anEvent: anEvent)
        case .notAuthorized:
            self.onNotAuthorized(anEvent: anEvent)
        case .remoteSettingsUpdate:
            break // A change to application-related configuration or policy settings.
        case .servicesUpdate:
            break // A change to services-related configuration.
        case .policyUpdate:
            if self.started {
                NotificationCenter.default.post(name: NSNotification.Name(rawValue: "AppPolicyUpdated"), object: nil)
            }
        default:
            print("unhandled event \(anEvent.message)")
        }
    }

    func onNotAuthorized(anEvent: GDAppEvent) {
        /* Handle the Good Libraries not authorized event. */
        switch anEvent.code {
        case .errorIdleLockout:
            break // idle lockout is benign & informational
        case .errorActivationFailed: break
        case .errorProvisioningFailed: break
        case .errorPushConnectionTimeout: break
        case .errorSecurityError: break
        case .errorAppDenied: break
        case .errorAppVersionNotEntitled: break
        case .errorBlocked: break
        case .errorWiped: break
        case .errorRemoteLockout: break
        case .errorPasswordChangeRequired:
            fallthrough
        default:
            self.preAuthCompletion?(.failure(BlackBerryDynamicsError.auth(event: anEvent.code)))
        }
    }

    func onAuthorized(anEvent: GDAppEvent) {
        /* Handle the Good Libraries authorized event. */
        switch anEvent.code {
        case .errorNone:
            if !self.started {
                self.started = true
                self.preAuthCompletion?(.success(anEvent.message))
            }
        default:
            self.preAuthCompletion?(.failure(BlackBerryDynamicsError.auth(event: anEvent.code)))
        }
    }
}
