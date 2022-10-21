//
//  MWBlackBerryDynamicsEmailViewController.swift
//  MobileWorkflowCore
//
//  Created by Jonathan Flintham on 13/10/2020.
//

import Foundation
import MobileWorkflowCore
import UIKit

class MWBlackBerryDynamicsEmailViewController: MWEmailStepViewController {
    
    override func viewWillAppear(_ animated: Bool) {
        super.viewWillAppear(animated)
    }
    
    override func extractAttachements(completion: @escaping (Result<[Attachment], Error>) -> Void) {
        let session = self.emailStep.session
        let properties = self.emailStep.emailProperties.filter { $0.checked }
        let attachments: [Attachment] = properties.compactMap {
            guard let file = session.fetchFiles(withKey: $0.sessionKeyPath) else { return nil }
            return Attachment.filePath(file.fileURL.absoluteString)
        }
        completion(.success(attachments))
    }
    
    override func openEmailComposer(
        sendTo: String,
        subject: String,
        body: String?,
        attachments: [Attachment]
    ) {
        guard let serviceClient = BlackBerryDynamics.shared.serviceClient else { preconditionFailure() }
        do {
            try serviceClient.composeEmail(
                to: [sendTo],
                subject: subject,
                body: body,
                attachments: attachments.compactMap({
                    guard case let Attachment.filePath(filePath) = $0 else { return nil }
                    return filePath
                })
            )
        } catch let error {
            guard let bbError = error as? BlackBerryDynamicsError, case .desiredAppNotFound(let appId) = bbError, appId == BBDServiceClient.emailAppIdentifier else {
                self.show(error)
                return
            }
            
            let alertController = UIAlertController(title: L10n.appNotFoundTitle, message: L10n.appNotFoundMessage, preferredStyle: .alert)
            alertController.addAction(UIAlertAction(title: L10n.cancel, style: .cancel))
            alertController.addAction(UIAlertAction(title: L10n.install, style: .default, handler: { _ in
                let url = URL(string: "https://apps.apple.com/us/app/blackberry-work/id890656632")!
                UIApplication.shared.open(url, options: [:])
            }))
            self.present(alertController, animated: true)
            
        }
    }
}
