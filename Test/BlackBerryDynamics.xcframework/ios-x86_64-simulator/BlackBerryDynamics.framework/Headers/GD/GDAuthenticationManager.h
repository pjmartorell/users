/*
 * (c) 2019 BlackBerry Limited. All rights reserved.
 *
 */

#import <Foundation/Foundation.h>


/** NSNotification name for <tt>GDAuthenticationManager</tt> notifications.
 *
 *  The name of the notification for which to register an observer.
 *
 *  <tt>UserInfo</tt> dictionary from <tt>GDReAuthenticationResultNotification</tt> contains the following:\n
 *  - token    - specific request token, enables the caller to associate an event with a specific call to the interface (as interface will synchronously return with a token for that call)
 *  - result   - denotes whether user was successfully authenticated and provides details of any error. See \ref GDReAuthResult.
 *  - authType - indicates how user was authenticated. See \ref GDReAuthType.
 *
 *  To get the reauthenticate results from the notification, use these convenient methods from GDAuthenticationManager:
 *     - getReauthenticationToken
 *     - getReauthenticationResult
 *     - getReauthenticationType
 */
extern NSString * _Nonnull const GDReAuthenticationResultNotification;

/// BlackBerry reauthentication result type
/// \copydetails ssReauthResult
typedef NS_ENUM(NSInteger, GDReAuthResult)
{
    /// \copydetails ssReauthResultSuccess
    GDReAuthResultSuccess,

    /// \copydetails ssReauthResultErrorFailed
    GDReAuthResultErrorFailedAuth,

    /// \copydetails ssReauthResultErrorUserCancelled
    GDReAuthResultErrorUserCancelled,

    /// \copydetails ssReauthResultErrorExpired
    GDReAuthResultErrorExpired,

    /// \copydetails ssReauthResultErrorInProgress
    GDReAuthResultErrorInProgress,

    /// \copydetails ssReauthResultErrorNotSupported
    GDReAuthResultErrorNotSupported,

    /// \copydetails ssReauthResultInvalidRequest
    GDReAuthResultErrorInvalidRequest,

    /// \copydetails ssReauthResultErrorUnknown
    GDReAuthResultErrorUnknown
};

/// BlackBerry reauthentication result type
/// \copydetails ssReauthType
typedef NS_ENUM(NSInteger, GDReAuthType)
{
    /// \copydetails ssReauthTypeNone
    GDReAuthTypeNone,

    /// \copydetails ssReauthTypeNoPassword
    GDReAuthTypeNoPassword,

    /// \copydetails ssReauthTypePassword
    GDReAuthTypePassword,

    /// \copydetails ssReauthTypeBiometric
    GDReAuthTypeBiometric,

    /// \copydetails ssReauthTypeGracePeriod
    GDReAuthTypeGracePeriod,
    
    /// \copydetails ssReauthTypeTrusted
    GDReAuthTypeTrustedAuthenticator
    
    
};

NS_ASSUME_NONNULL_BEGIN



/**
 * \copydetails ssAuthenticationManager
 */

@interface GDAuthenticationManager : NSObject

/// Requests user reauthentication
///
///\copydetails ssReauthenticate
+ (NSString *)reauthenticate:(NSString *)title
                     message:(NSString *)message
            timeoutInSeconds:(NSUInteger)timeout
        gracePeriodInSeconds:(NSUInteger)gracePeriod
                     enforce:(BOOL)enforce
             requirePassword:(BOOL)requirePassword;

/// Requests user reauthentication
///\overload
+ (NSString *)reauthenticate:(NSString *)title
                     message:(NSString *)message
            timeoutInSeconds:(NSUInteger)timeout;

/// Requests user reauthentication
///\overload
+ (NSString *)reauthenticate:(NSString *)title
                     message:(NSString *)message
            timeoutInSeconds:(NSUInteger)timeout
        gracePeriodInSeconds:(NSUInteger)gracePeriod;

/**
 * Gets token from reauthentication notification.
 *
 * This \ss_function is a helper that returns the reuthentication token from \ss_notification.
 *
 * @param notification              \ss_notification instance which has been received after subscribing on
 *                                  notification with name GDReAuthenticationResultNotification.
 *
 * @return <tt>NSString</tt> token value for the type of event being notified.
 */
+ (NSString *)getReauthenticationToken:(NSNotification *)notification;


/**
 * Gets authentication result from reauthentication notification.
 *
 * This \ss_function is a helper that returns the reauthentication result from \ss_notification.
 *
 * @param notification              \ss_notification instance which has been received after subscribing to
 *                                  notification with name GDReAuthenticationResultNotification.
 *
 * @return <tt>GDReAuthResult</tt> value for the type of event being notified.
 */
+ (GDReAuthResult)getReauthenticationResult:(NSNotification *)notification;


/**
 * Gets authentication type from reauthentication notification.
 *
 * This \ss_function is a helper that returns the reauthentication type from \ss_notification.
 *
 * @param notification              \ss_notification instance which has been received after subscribing to
 *                                  notification with name GDReAuthenticationResultNotification.
 *
 * @return <tt>GDReAuthType</tt> value for the type of event being notified.
 */
+ (GDReAuthType)getReauthenticationType:(NSNotification *)notification;

@end

NS_ASSUME_NONNULL_END
