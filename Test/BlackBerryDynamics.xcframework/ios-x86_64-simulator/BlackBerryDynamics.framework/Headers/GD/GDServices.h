/*
 * (c) 2017 BlackBerry Limited. All rights reserved.
 * 
 * The documentation in this file is also used elsewhere.
 */

#ifndef __GD_SERVICES_H__
#define __GD_SERVICES_H__

#import <Foundation/Foundation.h>
#import "GDPortability.h"

/* \cond DOXYGEN_IGNORE */
#if __has_extension(attribute_deprecated_with_message)
#   define DEPRECATE_BRINGTOFRONTWITHOUTCOMPLETION __attribute((deprecated("Use bringToFront:completion:error:")))
#else
#   define DEPRECATE_BRINGTOFRONTWITHOUTCOMPLETION __attribute((deprecated))
#endif
/* \endcond */

NS_ASSUME_NONNULL_BEGIN

/** \defgroup iccerrors AppKinetics Errors
 * \copydetails ssGDServicesICCErrorsPreamble
 * \{
 */

/** Error domain for AppKinetics errors.
 * 
 * \copydetails ssGDServicesICCErrorsDomain
 */
extern NSString* const GDServicesErrorDomain;

/** A general AppKinetics error occurred.
 */
extern NSInteger const GDServicesErrorGeneral;

/** Application's process has been suspended by system.
 */
extern NSInteger const GDServicesErrorProcessSuspended;

/** The service consumer sent a request to an application that couldn't be found
 *  on the device or computer.
 */
extern NSInteger const GDServicesErrorApplicationNotFound; 

/** The service consumer sent a request that specified a service that isn't
 *  supported by the service provider.
 */
extern NSInteger const GDServicesErrorServiceNotFound;

/** The service consumer sent a request that specified a service version that
 *  isn't supported by the service provider.
 */
extern NSInteger const GDServicesErrorServiceVersionNotFound;

/** The service consumer sent a request that specified a method that isn't
 *  supported by the service provider.
 */
extern NSInteger const GDServicesErrorMethodNotFound;

/** The service consumer sent a request to an application that couldn't be
 *  unlocked.
 */
extern NSInteger const GDServicesErrorNotAllowed;

/** The application attempted to utilize an unsupported type as a service
 *  parameter, either in a service request or in a service response.
 */
extern NSInteger const GDServicesErrorInvalidParams;

/** The application attempted to establish a connection but couldn't find a
 *  valid X509 certificate.
 */
extern NSInteger const GDServicesErrorCertificateNotFound;

/** The service consumer sent a request that specified a method that has been
 *  disabled in the service provider.
 */
extern NSInteger const GDServicesMethodDisabled;

/** The service consumer sent a request that specified a service version that
 *  has been disabled in the service provider.
 */
extern NSInteger const GDServicesVersionDisabled;

/** The service consumer sent a request that specified a service that has been
 *  disabled in the service provider.
 */
extern NSInteger const GDServicesServiceDisabled;

/** The application attempted to establish a connection to the application that
 *  was activated for a different user.
 */
extern NSInteger const GDServicesErrorEnterpriseUserNotMatch;

/** \}
 */

/** \defgroup iccconstants AppKinetics Miscellaneous Constants
 * These miscellaneous constants are part of the AppKinetics programming
 * interface.
 *
 * For an overall description of AppKinetics see the \ss_serviceoverview_link.
 * 
 * \{
 */

/** Constants for specifying foreground execution preference.
 * 
 * This enumeration represents a preference for which application is to execute
 * in foreground. The <tt>option</tt> parameter of the
 * \ss_serviceclient_sendto_link and \ss_service_replyto_link \ss_functions
 * always takes one of these values. See \ss_function references for details.
 */

typedef NS_ENUM(NSInteger, GDTForegroundOption)
{
    /** The current application is to be in the foreground. */
    GDEPreferMeInForeground,
    
    /** The other application is to be in the foreground. */
    GDEPreferPeerInForeground,
    
    /** There is no preference for which application is in foreground. */
    GDENoForegroundPreference
    
};

/** BlackBerry Dynamics service ID for Front Request.
 * 
 * Use this constant to send or identify a front request. See under Foreground
 * Execution and Front Request Programming Interface in the
 * \ss_serviceoverview_link.
 */
extern NSString* const GDFrontRequestService;

/** Method name for the Front Request API.
 * 
 * Use this constant to identify the method in a front request. See under
 * Foreground Execution and Front Request Programming Interface in the
 * \ss_serviceoverview_link.
 */
extern NSString* const GDFrontRequestMethod;

/** \}
 */

/** Handler for AppKinetics consumer events.
 * 
 * \copydetails ssGDServicesClientListener
 */
@protocol GDServiceClientDelegate<NSObject>
@required
/** AppKinetics service response callback.
 * 
 * \copydetails ssGDServicesClientResponseCallback
 */
- (void) GDServiceClientDidReceiveFrom:(NSString*)application
                            withParams:(id)params
                       withAttachments:(NSArray<NSString *> *)attachments
              correspondingToRequestID:(NSString*)requestID;

@optional
/** Service request file attachment transmission start callback.
 * 
 * \copydetails ssGDServiceClientDidStartSendingTo
 */
- (void) GDServiceClientDidStartSendingTo:(NSString*)application withFilename:(NSString*)filename correspondingToRequestID:(NSString*)requestID;

@optional
/** Service request transmission complete callback.
 * 
 * \copydetails ssGDServiceClientDidFinishSendingTo
 */
- (void) GDServiceClientDidFinishSendingTo:(NSString*)application withAttachments:(NSArray<NSString *> *)attachments withParams:(id)params correspondingToRequestID:(NSString*)requestID;

@optional
/** Service response file attachments transmission start callback.
 * 
 * \copydetails ssGDServicesClientWillReceiveAttachmentsCallback
 */
- (void) GDServiceClientWillStartReceivingFrom:(NSString*)application
                           numberOfAttachments:(NSUInteger)attachments
                                  forRequestID:(NSString*)requestID;

@optional
/** Service response individual file attachment transmission start callback.
 * 
 * \copydetails ssGDServicesClientWillReceiveAttachmentDataCallback
 */
- (void) GDServiceClientWillStartReceivingFrom:(NSString*)application
                                attachmentPath:(NSString*)path
                                      fileSize:(NSNumber*)size
                                  forRequestID:(NSString*)requestID;

@end


/** AppKinetics service consumer.
 * 
 * \copydetails ssGDServicesServiceClient
 */
@interface GDServiceClient : NSObject

/** Send a service request.
 * 
 * \copydetails ssGDServicesSendTo
 */
+ (BOOL) sendTo:(NSString*)application
    withService:(NSString*)service
    withVersion:(NSString*)version
     withMethod:(NSString*)method
     withParams:(nullable id)params
withAttachments:(nullable NSArray<NSString *> *)attachments
bringServiceToFront:(GDTForegroundOption)option
      requestID:(NSString * GD_NSNULLABLE_POINTER * GD_NSNULLABLE_POINTER)requestID
          error:(NSError**)error;

/** Cancel a service request.
 * 
 * \copydetails ssGDServicesCancelRequest
 */
+ (BOOL) cancelRequest:(NSString*)requestID toApplication:(NSString*)application;

/** Bring another application to the foreground.
 *
 * \copydetails ssGDServicesBringToFrontConsumerPreamble
 * \copydetails ssGDServicesBringToFrontCommonWithCompletion
 */
+ (BOOL) bringToFront:(nonnull NSString*)application completion:( void(^)(BOOL) )completion error:(NSError**)error;

/** Bring another application to the foreground (deprecated).
 * 
 * \deprecated This \ss_function is deprecated and will be removed in a future
 * release. Use \ss_serviceclient_bringtofront_link with a completion block
 * instead.
 * 
 * \copydetails ssGDServicesBringToFrontConsumerPreamble
 * \copydetails ssGDServicesBringToFrontCommonWithoutCompletion
 */
+ (BOOL) bringToFront:(NSString*)application error:(NSError**)error DEPRECATE_BRINGTOFRONTWITHOUTCOMPLETION;

/** Handler for responses to service requests.
 * 
 * \copydetails ssGDServicesServiceClientSetListener
 */
@property (nullable, weak, getter = getDelegate, setter = setDelegate:) id<GDServiceClientDelegate> delegate;

@end

/** AppKinetics service provider implementation.
 * 
 * \copydetails ssGDServicesServiceListener
 */
@protocol GDServiceDelegate<NSObject>

@required
/** Service request callback.
 * 
 * \copydetails ssGDServicesServiceRequestCallback
 */
- (void) GDServiceDidReceiveFrom:(NSString*)application
                      forService:(NSString*)service
                     withVersion:(NSString*)version
                       forMethod:(NSString*)method
                      withParams:(id)params
                 withAttachments:(NSArray<NSString *> *)attachments
                    forRequestID:(NSString*)requestID;

@optional

/** Service response file attachment transmission start callback.
 * 
 * \copydetails ssGDServiceDidStartSendingTo
 */
- (void) GDServiceDidStartSendingTo:(NSString*)application withFilename:(NSString*)filename correspondingToRequestID:(NSString*)requestID;

/** Service response transmission complete callback.
 * 
 * \copydetails ssGDServiceDidFinishSendingTo
 */
- (void) GDServiceDidFinishSendingTo:(NSString*)application withAttachments:(NSArray<NSString *> *)attachments withParams:(id)params correspondingToRequestID:(NSString*)requestID;

@optional
/** Service request file attachments transmission start callback.
 * 
 * \copydetails ssGDServicesServiceWillReceiveAttachmentsCallback
 */
- (void) GDServiceWillStartReceivingFrom:(NSString*)application
                     numberOfAttachments:(NSUInteger)attachments
                            forRequestID:(NSString*)requestID;

@optional
/** Service request individual file attachment transmission start callback.
 * 
 * \copydetails ssGDServicesServiceWillReceiveAttachmentDataCallback
 */
- (void) GDServiceWillStartReceivingFrom:(NSString*)application
                          attachmentPath:(NSString*)path
                                fileSize:(NSNumber*)size
                            forRequestID:(NSString*)requestID;

@end

/** AppKinetics service provider.
 * 
 * \copydetails ssGDServicesService
 * 
 * <h3>AppKinetics</h3>
 * \copydetails ssGDServices
 */
@interface GDService : NSObject

/** Send a response or error message.
 * 
 * \copydetails ssGDServicesReplyTo
 */
+ (BOOL) replyTo:(nullable NSString*)application
      withParams:(nullable id)params
bringClientToFront:(GDTForegroundOption)option
 withAttachments:(nullable NSArray<NSString *> *)attachments
       requestID:(NSString*)requestID
           error:(NSError**)error;

/** Bring another application to the foreground.
 *
 * \copydetails ssGDServicesBringToFrontProviderPreamble
 * \copydetails ssGDServicesBringToFrontCommonWithCompletion
 */
+ (BOOL) bringToFront:(nonnull NSString *)application completion:( void(^)(BOOL) )completion error:(NSError**)error;

/** Bring another application to the foreground (deprecated).
 *
 * \deprecated This \ss_function is deprecated and will be removed in a future
 * release. Use \ss_class_link{GDService,bringToFront:completion:error:}
 * instead.
 *
 * \copydetails ssGDServicesBringToFrontProviderPreamble
 * \copydetails ssGDServicesBringToFrontCommonWithoutCompletion
 */
+ (BOOL) bringToFront:(nonnull NSString *)application error:(NSError**)error DEPRECATE_BRINGTOFRONTWITHOUTCOMPLETION;

/** Handler that implements the services provided by the application.
 * 
 * \copydetails ssGDServicesServiceSetListener
 */
@property (nullable, weak, getter = getDelegate, setter = setDelegate:) id<GDServiceDelegate> delegate;

@end

NS_ASSUME_NONNULL_END

#endif
