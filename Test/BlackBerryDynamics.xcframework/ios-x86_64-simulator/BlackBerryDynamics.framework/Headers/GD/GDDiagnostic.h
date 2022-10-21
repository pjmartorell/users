/*
 * (c) 2017 BlackBerry Limited. All rights reserved.
 *
 */

#ifndef GDDiagnostic_h
#define GDDiagnostic_h

/** BlackBerry Dynamics diagnostic checks and information.
 *
 * \copydetails ssGDDiagnostic
 */
@interface GDDiagnostic : NSObject

/** \defgroup gdreachabilityerrors BlackBerry Dynamics Reachability Errors
 * \{
 */

/** Error codes for reachability checks.
 * 
 * These constants can be used for handling errors returned by BlackBerry
 * Dynamics reachability diagnostic checks.
 *
 * @see \ref GDDiagnostic class reference.
 */
typedef NS_ENUM(NSInteger, GDDiagnosticReachabilityErrorType)
{
    /** No error.
     */
    GDDiagnosticNoError=0,

    /** No network connection.
     */
    GDDiagnosticNoNetwork,

    /** Network changed during reachability check.
     */
    GDDiagnosticNetworkChange,

    /** Time out expired before reachability results could be generated.
     */
    GDDiagnosticTimedOut
};

/** \}
 */

#pragma mark Singleton

/** Get a reference to the BlackBerry Dynamics diagnostic object.
 * 
 * This \ss_function returns a reference to the BlackBerry Dynamics diagnostic
 * object, which is a "singleton class".
 *
 * @return Reference that can be used to call, for example, the
 *         \ref currentSettings \ss_function.
 */
+ (GDDiagnostic *)sharedInstance;


#pragma mark Reachability

/** \defgroup gddiagnosticreachabilityresultsblock Type for check reachability results callback
 * \{
 */

/** Type for check reachability results callback.
 * 
 * Pass a code block of this type as the <tt>block</tt> parameter to any of the
 * reachability checking \ss_functions in the \ref GDDiagnostic class.
 *
 * The block receives the following parameters.
 * @param results \ss_string containing results of the reachability check, which
 *                can be logged by the application for diagnostic purposes.
 * @param requestID <tt>NSInteger</tt> value that was returned by the original
 *                  check reachability \ss_function call.
 */
typedef void (^GDDiagnosticReachabilityResultsBlock)(NSString* results,
                                                     NSInteger requestID);
/** \}
 */

/** Check that an application server can be reached.
 * 
 * \copydetails ssGDDiagnosticCheckApplicationServerReachability
 */
- (NSInteger)checkApplicationServerReachability:(NSString*)host
                                       withPort:(NSInteger)port
                                         useSSL:(BOOL)ssl
                            validateCertificate:(BOOL)validateCertificate
                                    withTimeOut:(NSTimeInterval)timeOut
                                  callbackBlock:(GDDiagnosticReachabilityResultsBlock)block;

/** Check that the BlackBerry Dynamics management console can be reached.
 * 
 * \copydetails ssGDDiagnosticCheckManagementConsoleReachability
 */
- (NSArray*)checkManagementConsoleReachability:(NSTimeInterval)timeOut
                                 callbackBlock:(GDDiagnosticReachabilityResultsBlock)block;

#pragma mark Configs

/** Current application configuration settings.
 * 
 * \copydetails ssGDDiagnosticCurrentSettings
 */
@property (nonatomic, readonly) NSString* currentSettings;

@end

#endif /* GDDiagnostic_h */
