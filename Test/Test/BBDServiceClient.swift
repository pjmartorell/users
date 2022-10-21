//
//  BBDServiceClient.swift
//  MobileWorkflowTemplate
//
//  Created by Jonathan Flintham on 03/12/2020.
//  Copyright © 2020 Future Workshops. All rights reserved.
//

import Foundation
import BlackBerryDynamics.Runtime
import BlackBerryDynamics.AppKinetics

struct ServiceInformation {
    let identifier: String
    let address: String?
    let name: String
    let version: String
    let icon: UIImage?
}

class BBDServiceClient: NSObject {
    
    private let good: GDiOS
    private let fileManager: GDFileManager
    private let serviceClient: GDServiceClient
    
    init(good: GDiOS, fileManager: GDFileManager) {
        self.good = good
        self.fileManager = fileManager
        self.serviceClient = GDServiceClient()
        super.init()
        self.serviceClient.delegate = self
    }
    
    func performService(_ service: String,
                        version: String,
                        method: String,
                        address: String,
                        parameters: Any? = nil,
                        attachments: [String] = []) throws {
        try GDServiceClient.send(
            to: address,
            withService: service,
            withVersion: version,
            withMethod: method,
            withParams: parameters,
            withAttachments: attachments,
            bringServiceToFront: .GDEPreferPeerInForeground,
            requestID: nil
        )
    }
    
    func callService(
        _ service: String,
        version: String,
        method: String,
        desiredTarget: String? = nil,
        parameters: Any?,
        attachments: [String]
    ) throws {
        guard !service.isEmpty, !method.isEmpty else {
            preconditionFailure()
        }
        var providers = self.listAppsFor(service: service, version: version)
        if let desiredTarget = desiredTarget {
            providers = providers.filter { $0.identifier == desiredTarget }
        }
        guard let provider = providers.first, let address = provider.address else {
            if let desiredTarget = desiredTarget {
                throw BlackBerryDynamicsError.desiredAppNotFound(app: desiredTarget)
            } else {
                throw BlackBerryDynamicsError.serviceAppNotFound(service: service)
            }
        }
        let existingAttachements = attachments.filter {
            self.fileManager.fileExists(atPath: $0)
        }
        
        try self.performService(service,
                                version: version,
                                method: method,
                                address: address,
                                parameters: parameters,
                                attachments: existingAttachements)
    }
    
    func listAppsFor(service: String, version: String? = nil) -> [ServiceInformation] {
        let providers = self.good.getServiceProviders(for: service, andVersion: version, andServiceType: .application)
        return providers.map({ ServiceInformation(identifier: $0.identifier,
                                                  address: $0.address,
                                                  name: $0.name,
                                                  version: $0.version,
                                                  icon: $0.icon) })
    }
}

extension BBDServiceClient: GDServiceClientDelegate {
    
    func gdServiceClientDidReceive(from application: String, withParams params: Any, withAttachments attachments: [String], correspondingToRequestID requestID: String) {
        debugPrint("Received from application: \(application). Params: \(params)")
    }
}

extension BBDServiceClient {
    
    static let emailAppIdentifier = "com.good.gcs.g3" // BlackBerry Work
    
    func composeEmail(
        to emailAddresses: [String],
        subject: String?,
        body: String?,
        attachments: [String]
    ) throws {
        var parameters = [String: Any]()
        
        if !emailAddresses.isEmpty {
            parameters["to"] = emailAddresses
        }
        if let subject = subject {
            parameters["subject"] = subject
        }
        if let body = body {
            parameters["body"] = body
        }
        
        try self.callService(
            "com.good.gfeservice.send-email",
            version: "1.0.0.0",
            method: "sendEmail",
            desiredTarget: Self.emailAppIdentifier,
            parameters: parameters,
            attachments: attachments
        )
    }
}
