/*
 * (c) 2017 BlackBerry Limited. All rights reserved.
 */

#pragma once

#import <Foundation/Foundation.h>

extern NSString* const GDURLAuthenticationParameters;

/** NSMutableURLRequest category with additional features.
 * 
 * This class is a category of the \foundation <tt>NSMutableURLRequest</tt>
 * class that can be used when the BlackBerry Dynamics proxy infrastructure is
 * in use via the URL Loading System (see \ref GDURLLoadingSystem). This class
 * provides additional features to the default request class.
 *
 * This documentation includes only additional operations that are not part
 * of the default <tt>NSMutableURLRequest</tt> API.
 *
 * @see <a
 *          HREF="https://developer.apple.com/reference/foundation/nsmutableurlrequest?language=objc"
 *          target="_blank"
 *      >NSMutableURLRequest class reference</a
 *      > on the apple.com developer website.
 *
 * <h3>Authentication error-handling</h3>
 * Authentication errors may be encountered when this class is in use. For
 * example, the combination of user name and password may be rejected by the
 * server that receives the HTTP request.
 *
 */
@interface NSMutableURLRequest (GDNET)

/** Specify authorization credentials.
 * 
 * Call this function to set the authorization credentials that will be sent if
 * the response to the URL request contains an authentication challenge.
 *
 * Authorization credentials would usually be sent in response to receiving
 * <tt>NSURLConnectionDelegate didReceiveAuthenticationChallenge</tt>.
 *
 * Server and proxy credentials can both be set, in separate calls to the
 * function.
 *
 * This function can only be used when the BlackBerry Dynamics proxy
 * infrastructure is in use via the URL Loading System.
 *
 * @param credentials <tt>NSURLCredential</tt> containing the username and
 *                    password.
 * @param space <tt>NSURLProtectionSpace</tt> containing the following:\n
 *              Hostname or address,\n
 *              Port number,\n
 *              Authentication method,\n
 *              Proxy indicator.
 */
- (BOOL) setAuthorizationCredentials:(NSURLCredential*)credentials withProtectionSpace:(NSURLProtectionSpace*)space;

/** Cancel persistence of a stored server trust credential.
 * 
 * Call this \ss_function to cancel the persistence of a server trust
 * credential. Persistence must have been set via the
 * <tt>NSURLCredential(GDNET)</tt> <tt>gdPersistence</tt> property, so that the
 * credential is being managed by the BlackBerry Dynamics runtime.
 *
 * Credentials managed by the BlackBerry Dynamics runtime are stored
 * persistently in the BlackBerry Dynamics secure store on the mobile device.
 * The URL of the <tt>NSMutableURLRequest</tt> object on which this method is
 * called will be used by the runtime to identify the server certificate.
 *
 * @return \ss_true if a persistent server trust credential was found and
 *         cancelled.
 * @return \ss_false otherwise.
 *
 * @see The class reference of the \ref NSURLCredential(GDNET) category for the
 *      programming interface and implications of setting persistence.
 */
- (BOOL)undoPriorTrustDecision;

@end
