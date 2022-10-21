//
//  BBPDFService.swift
//  App_Tests
//
//  Created by Igor Ferreira on 02/07/2021.
//  Copyright © 2021 Future Workshops. All rights reserved.
//

import Foundation
import MobileWorkflowCore

enum BBPDFOpenError: LocalizedError {
    case unableToPerformTask
    case appNotInstalled
}

class BBPDFService: AsyncTaskService {
    private let kViewPDFService = "com.good.gdservice.transfer-file"
    private let kViewPDFMethod = "transferFile"
    private let kViewPDFVersion = "1.0.0.0"
    
    let dynamics: BlackBerryDynamics
    
    init(dynamics: BlackBerryDynamics = BlackBerryDynamics.shared) {
        self.dynamics = dynamics
    }
    
    func perform<T>(task: T, session: ContentProvider, respondOn: DispatchQueue, completion: @escaping (Result<T.Response, Error>) -> Void) where T : AsyncTask {
        if let list = task as? PDFListAppsTask {
            self.fetchList(task: list, queue: respondOn, completion: completion)
        } else if let viewer = task as? PDFViewerTask {
            self.viewPDF(task: viewer, queue: respondOn, completion: completion)
        } else {
            completion(.failure(BBPDFOpenError.unableToPerformTask))
        }
    }
    
    private func fetchList<T>(task: PDFListAppsTask, queue: DispatchQueue, completion: @escaping (Result<T, Error>) -> Void) {
        let providers = self.dynamics.serviceClient?.listAppsFor(service: kViewPDFService, version: kViewPDFVersion) ?? []
        var options = providers.map({ PDFAppOption.externalApp(appId: $0.identifier, appName: $0.name) })
        if !options.isEmpty {
            //For now, we are always allowing the user to open the PDF in-app as an option,
            //given that the PDF is being downloaded and stored securely.
            options.append(PDFAppOption.inApp)
        }
        if let validResponse = options as? T {
            self.notify(result: .success(validResponse), on: queue, completion: completion)
        } else {
            self.notify(result: .failure(BBPDFOpenError.unableToPerformTask), on: queue, completion: completion)
        }
    }
    
    private func viewPDF<T>(task: PDFViewerTask, queue: DispatchQueue, completion: @escaping (Result<T, Error>) -> Void) {
        let providers = self.dynamics.serviceClient?.listAppsFor(service: kViewPDFService, version: kViewPDFVersion) ?? []
        
        guard let desiredProvider = providers.first(where: { $0.identifier == task.input.appId }), let address = desiredProvider.address else {
            self.notify(result: .failure(BBPDFOpenError.appNotInstalled), on: queue, completion: completion)
            return
        }
        
        do {
            try self.dynamics.serviceClient?.performService(kViewPDFService,
                                                            version: kViewPDFVersion,
                                                            method: kViewPDFMethod,
                                                            address: address,
                                                            parameters: nil,
                                                            attachments: [task.input.filePath])
            if let validResponse = () as? T {
                self.notify(result: .success(validResponse), on: queue, completion: completion)
            } else {
                self.notify(result: .failure(BBPDFOpenError.unableToPerformTask), on: queue, completion: completion)
            }
        } catch (let error) {
            self.notify(result: .failure(error), on: queue, completion: completion)
        }
    }
    
    func canPerform<T>(task: T) -> Bool where T : AsyncTask {
        return task is PDFListAppsTask || task is PDFViewerTask
    }
}
