/*
 * (c) 2017 BlackBerry Limited. All rights reserved.
 *
 */

#pragma once

#import <Foundation/Foundation.h>
#import "GDURLLoadingSystem.h"
#import "GDPortability.h"

NS_ASSUME_NONNULL_BEGIN

/** NSURLCache category with additional features.
 * 
 * This class is a category of the native <tt>NSURLCache</tt> class that adds
 * the \ss_functions documented below to the interface. The additional
 * \ss_functions can be used when the BlackBerry Dynamics proxy infrastructure
 * is in use in the
 * \if iOS
 * URL Loading System, see \ref GDURLLoadingSystem, or in the URL session
 * system, see \ref nsurlsession_support.
 * \else
 * URL Loading System, see \ref GDURLLoadingSystem.
 * \endif
 *
 * This class provides additional features to the default cache.
 *
 * This documentation includes only additional operations that are not part
 * of the default <tt>NSURLCache</tt> interface.
 *
 * Note that the additional features cannot be used when the BlackBerry Dynamics
 * proxy infrastructure isn't in use, even if temporarily. If the functions are
 * called in this state, they have no effect.
 *
 * @see <a
 *   href="https://developer.apple.com/reference/foundation/nsurlcache?language=objc"
 *   target="_blank"
 * >NSURLCache Class Reference</a> on the apple.com developer website.
 */
@interface NSURLCache (GDURLCache)

/** Set the default maximum age of cached files.
 * 
 * Call this function to set a default maximum age for cached files.
 * The default maximum age will be used where it is less than the maximum age
 * specified in the server cache directive, if any.
 *
 * The default maximum only applies when the BlackBerry Dynamics proxy
 * infrastructure is in use as described in the description, above.
 *
 * @param age <tt>NSTimeInterval</tt> representing the maximum age in
 *            seconds.
 */
- (void) setMaxCacheFileAge:(NSTimeInterval) age;

/** Set the maximum permitted size of a cached file.
 * 
 * Call this function to set the maximum permitted size of a cached file. If not
 * set, a default maximum of 1 megabyte will be used.
 *
 * This function sets the limit for a single file, not for the size of the whole
 * cache. The capacity of the cache as a whole can be set using the native
 * <tt>NSURLCache</tt> programming interfacer. See the <a
 *   href="https://developer.apple.com/reference/foundation/nsurlcache?language=objc"
 *   target="_blank"
 * >NSURLCache Class Reference</a> on the apple.com developer website for
 * details.
 *
 * The permitted maximum only applies when the BlackBerry Dynamics proxy
 * infrastructure is in use as described in the description, above.
 *
 * @param fileSize <tt>NSUInteger</tt> representing the maximum file size in
 *                 bytes.
 */
- (void) setMaxCacheFileSize:(NSUInteger) fileSize;

/** Get the maximum permitted size of a cached file.
 * 
 * Call this function to get the maximum permitted size of a cached file.
 *
 * This function returns the limit for a single file, not for the size of the
 * whole cache. The native <tt>NSURLCache</tt> API can be used to access
 * information about the cache as a whole. See the <a
 *   href="https://developer.apple.com/reference/foundation/nsurlcache?language=objc"
 *   target="_blank"
 * >NSURLCache Class Reference</a> on the apple.com developer website for
 * details.
 *
 * The permitted maximum only applies when the BlackBerry Dynamics proxy
 * infrastructure is in use as described in the description, above.
 *
 * @return <tt>NSUInteger</tt> representing the maximum file size in bytes.
 */
- (NSUInteger) maxCacheFileSize;

@end


/** Control the secure authentication cache.
 * 
 * Use this class to control the secure authentication cache of the
 * \ref GDURLLoadingSystem 
 * \if iOS
 * and the deprecated \ref GDHttpRequest class. (Currently, there are only two
 * controls.)
 * \endif
 * The secure authentication cache is used as follows.
 * <dl>
 * <dt>URL Loading System</dt><dd>
 * Stores credentials for all authentication methods.\n
 * Stores tickets for Kerberos authentication.</dd>
 * \if iOS
 * <dt>G<tt></tt>DHttpRequest (deprecated)</dt>
 * <dd>Stores tickets for Kerberos authentication.</dd>
 * \endif
 * </dl>
 *
 * @see \ref GDURLLoadingSystem
 * \if iOS
 * @see \ref GDHttpRequest
 * \endif
 */
@interface GDCacheController : NSObject {
}

/** Clear cached authentication credentials.
 * 
 * \if Apple
 * \copydetails ssGDCommunicationsClearCredentials
 * \endif
 */
+ (void) clearCredentialsForMethod:(nullable NSString*) method;

/** Allow or disallow Kerberos delegation.
 * 
 * \copydetails ssGDCommunicationsKerberosAllowDelegation
 *
 * When this function is called, the Kerberos ticket and credentials caches
 * will be cleared. I.e. there is an effective call to the
 * \reflink GDCacheController::clearCredentialsForMethod:
 * clearCredentialsForMethod:\endlink
 * \ss_function with an <tt>NSURLAuthenticationMethodNegotiate</tt> parameter.
 *
 * @param allow \ss_true to allow delegation, \ss_false to disallow.
 */
+ (void) kerberosAllowDelegation:(BOOL)allow;
@end


NS_ASSUME_NONNULL_END
