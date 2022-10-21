//
//  MWBlackBerryDynamicsEmailStep.swift
//  MobileWorkflowCore
//
//  Created by Jonathan Flintham on 13/10/2020.
//

import Foundation
import MobileWorkflowCore
import UIKit

class MWBlackBerryDynamicsEmailStep: MWStep, EmailStep {
    var emailProperties: [EmailProperty]
    var imageURL: String? { nil }
    var image: UIImage? { nil }

    let body: String?
    let subject: String
    let sendTo: String?
    let session: Session
    let services: StepServices
    
    init(identifier: String, body: String?, subject: String, sendTo: String?, emailProperties: [EmailProperty], session: Session, services: StepServices, theme: Theme) {
        self.body = body
        self.subject = subject
        self.sendTo = sendTo
        self.emailProperties = emailProperties
        self.services = services
        self.session = session
        
        
        super.init(identifier: identifier, theme: theme)
    }
    
    required init(coder aDecoder: NSCoder) {
        fatalError("init(coder:) has not been implemented")
    }
    
	override func instantiateViewController() -> StepViewController {
	    MWBlackBerryDynamicsEmailViewController(emailStep: self)
	}
}

extension MWBlackBerryDynamicsEmailStep: BuildableStep {
 
    public static func build(stepInfo: StepInfo, services: StepServices) throws -> Step {
        
        let emailPropertyData = stepInfo.data.content["requestPropertyIdentifiers"] as? [[String: Any]] ?? []
        let emailProperites = try emailPropertyData.asEmailProperties()
        
        return MWBlackBerryDynamicsEmailStep(
            identifier: stepInfo.data.identifier,
            body: services.localizationService.translate(stepInfo.data.content["text"] as? String),
            subject: stepInfo.context.appName ?? "",
            sendTo: stepInfo.data.content["sendTo"] as? String,
            emailProperties: emailProperites,
            session: stepInfo.session,
            services: services,
            theme: stepInfo.context.theme
        )
    }
}
