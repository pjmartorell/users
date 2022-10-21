/*
 * (c) 2019 BlackBerry Limited. All rights reserved.
 *
 */

#pragma once

#import <Foundation/Foundation.h>

#import "GDPortability.h"

/** \defgroup jwtcallback BlackBerry Enterprise Identity JWT request callback
 * \{
 */

/** Status codes from BlackBerry Enterprise Identity JWT request.
 * 
 * These constants can be used for handling errors returned from JWT retrieval
 *
 * @see \ref GDUtility class reference.
 */

NS_ASSUME_NONNULL_BEGIN

typedef NS_ENUM(NSInteger, BBDJWTStatusCode) {
    /** Request successful
     */
    BBDJWTStatusOK = 0,
    
    /** A general error occurred not covered by other status codes.
     */
    BBDJWTStatusUnknownError,
    
    /** MTD is not enabled (only for MTD related requests)
     */
    BBDJWTMTDNotEnabled,
    
    /** Server responded with an error.
     */
    BBDJWTServerError,
    
    /** Server not reachable or cannot establish a connection
     */
    BBDJWTServerUnreachable,
    
    /** Client is not authorised to make this request. For Zero Sign On (ZSO), a valid certificate is not enrolled.
     */
    BBDJWTAuthFailure,
    
    /** Server has not yet updated to accept a recently enrolled authorisation. Eg a ZSO is enrolled but not yet activated on the
     * server. This is temporary and can be retried.
     */
    BBDJWTPendingActivation
};
 
/** Completion Block definition for JWT retrieval
 *
 * @param JWT If successful an NSString object pointer containing the JWT. Empty otherwise.
 *
 * @param status A BBDJWTStatusCode value indicating the status of the request.
 *
 * @see BBDJWTStatusCode
 *
 * @param error An additional error parameter which may contain the HTTP status code of a server related failure, 0 on success.
 *
 */
typedef void (^BBDJWTCompletion)(NSString* JWT, BBDJWTStatusCode status, int error);
/** \}
 */

/** Delegate for handling the results of BlackBerry Dynamics authentication
 *  token requests.
 * 
 * \copydetails ssGDAuthTokenListener
 */
@protocol GDAuthTokenDelegate

/** Successful token request callback.
 * 
 * \copydetails ssGDAuthTokenListenerSuccess
 * 
 * @param gdAuthToken \ss_string containing the token.
 */
- (void)onGDAuthTokenSuccess:(NSString*)gdAuthToken;

/** Failed token request callback.
 * 
 * \copydetails ssGDAuthTokenListenerFailure
 *
 * @param authTokenError <tt>NSError</tt> describing the error condition that
 *                       led to the failure of the token request.
 *
 * @see \ref gdauthtokendomain
 */
- (void)onGDAuthTokenFailure:(NSError*) authTokenError;

@end

/** BlackBerry Dynamics utility for managing authentication tokens and identity.
 * 
 * \copydetails ssGDAuthToken
 * \copydetails ssSharedUserId
 */
@interface GDUtility : NSObject

/** BlackBerry Dynamics authentication token request.
 * 
 * \copydetails ssGDAuthTokenRequest
 */
- (void)getGDAuthToken: (NSString*) challenge serverName:(nullable NSString*) serverName;

/** Get User Dynamics Shared identifier.
 *
 * \copydetails ssGetSharedUserId
 */
- (NSString *)getDynamicsSharedUserIDWithError:(NSError **)error;

/** Get JWT from BlackBerry Enterprise Identity (EID) server
 *
 * \copydetails ssGetEIDToken
 */
- (BOOL) getEIDToken:(NSString *) clientID withScope:(NSString*) scope withResourceServer:(NSString*) resourceServer withRefresh:(BOOL) refresh withCompletion:(BBDJWTCompletion) callback withError:(NSError**) error;

/** Delegated event-handling.
 * 
 * BlackBerry Dynamics authentication token requests are asynchronous. When a
 * request succeeds or fails, a callback in the application code is invoked by
 * the BlackBerry Dynamics runtime.
 * 
 * Set this property to an instance of a class in the application that contains
 * the code for the required callbacks, i.e. a class that implements
 * the GDAuthTokenDelegate protocol.
 */
@property (nullable, weak, getter = getGDAuthDelegate, setter = setGDAuthDelegate:) id<GDAuthTokenDelegate> gdAuthDelegate;


@end

/**
 * \defgroup gdauthtokendomain BlackBerry Dynamics authentication token error domain
 * These constants can be used when handling BlackBerry Dynamics authentication
 * token request errors, in a \ss_class_link{GDAuthTokenDelegate}
 * implementation.
 *
 * \{
 */

/** Error domain for the BlackBerry Dynamics authentication token mechanism.
 */
extern NSString* const GDAuthTokenDomain;


typedef NS_ENUM(NSInteger, GDAuthTokenError)
{
    /** The BlackBerry Dynamics server software installed at the enterprise
     * doesn't support the authentication token mechanism.
     */
    GDAuthTokenErrNotSupported = -2,
    
    /** An error occurred during token generation or communication.
     * 
     * Sending the same request later mightn't encounter the same condition, and
     * could succeed.
     */
    GDAuthTokenErrRetry         = -1,
    
};

/** \}
 */

NS_ASSUME_NONNULL_END
