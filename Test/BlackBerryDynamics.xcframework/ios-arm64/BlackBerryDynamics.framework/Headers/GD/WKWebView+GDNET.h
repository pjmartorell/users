/*
 * (c) 2020 BlackBerry Limited. All rights reserved.
 */

#import <WebKit/WebKit.h>

NS_ASSUME_NONNULL_BEGIN

/** WKWebView category with additional features.
 *
 * This class is a category of the <tt>WKWebView</tt> class that adds the
 * properties documented below to the programming interface.
*/
@interface WKWebView (GDNET)

/** Specify HTTP/HTTPS proxy protection space
 *
 * If this property is specified, all traffic of this WKWebView instance going through specified proxy. In order to remove proxy set this property to nil.
 *
 * @param proxyProtectionSpace <tt>NSURLProtectionSpace</tt> containing the following:\n
 *              Hostname or address,\n
 *              Port number,\n
 *              Authentication method,\n
 *              Proxy indicator.
 *              In order to create this object should be used method initWithProxyHost:port:type:realm:authenticationMethod: of class NSURLProtectionSpace
 */
@property (strong, nullable) NSURLProtectionSpace* proxyProtectionSpace;

/** Specify HTTP/HTTPS proxy credentials
 *
 * @param proxyCredentials <tt>NSURLCredential</tt> containing the username and
 *                    password.
*/
@property (strong, nullable) NSURLCredential* proxyCredentials;

@end

NS_ASSUME_NONNULL_END
