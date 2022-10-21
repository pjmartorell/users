/*
 * (c) 2017 BlackBerry Limited. All rights reserved.
 */

#import <Foundation/Foundation.h>
#import <SystemConfiguration/SystemConfiguration.h>

#if TARGET_OS_IPHONE || TARGET_IPHONE_SIMULATOR

/* \cond DOXYGEN_IGNORE */
#ifndef __has_extension
#define __has_extension(x) 0  // Compatibility with non-clang compilers.
#endif
/* \endcond */

/* \cond DOXYGEN_IGNORE */
#if __has_extension(attribute_deprecated_with_message)
#   define DEPRECATED_IN_GDREACHABILITY __attribute__((deprecated("Deprecated in GDReachability. Use isNetworkAvailable property instead.")))
#else
#   define DEPRECATED_IN_GDREACHABILITY __attribute__((deprecated))
#endif
/* \endcond */

/**
 * \if iOS
 * Constants for GDReachability network status.
 * 
 * This enumeration represents the different possible statuses of the connection
 * to the BlackBerry Dynamics infrastructure. The <tt>status</tt> property of a
 * \ref GDReachability object always takes one of these values.
 */
typedef NS_ENUM(NSInteger, GDReachabilityStatus) {
    /** The infrastructure isn't reachable.
     */
    GDReachabilityNotReachable = 0,
    
    /** The infrastructure is reachable via a Wi-Fi connection.
     */
    GDReachabilityViaWiFi,

    /** The infrastructure is reachable via a mobile data (cellular) connection.
     * \endif
     */
    GDReachabilityViaCellular
};

#endif

/** Notification name for changes to BlackBerry Dynamics infrastructure
 *  reachability.
 * 
 * Use this value to add an observer of changes to BlackBerry Dynamics
 * infrastructure reachability. See the \ref GDReachability class reference for
 * details.
 */
extern NSString *GDReachabilityChangedNotification;

/** BlackBerry Dynamics infrastructure connection status.
 * 
 * \copydetails ssGDConnectionManagementNetworkInfo
 */
@interface GDReachability : NSObject

/** Get a reference to the BlackBerry Dynamics infrastructure connection status
 *  object.
 * 
 * This function returns a reference to the BlackBerry Dynamics infrastructure
 * connection status object, which is a "singleton class".
 *
 * @return Reference that can be used, for example, to access the
 *         <tt>status</tt> property.
 */
+ (instancetype) sharedInstance;

#if TARGET_OS_IPHONE || TARGET_IPHONE_SIMULATOR
/**
 * \if iOS
 * Connection status and medium.
 * 
 * The value of this property represents the type of connection through which
 * the BlackBerry Dynamics infrastructure is reachable. It always takes a value
 * from the \ref GDReachabilityStatus enumeration:
 * - <tt>GDReachabilityViaCellular</tt> if the infrastructure is reachable via a
 *   mobile data (cellular) connection.
 * - <tt>GDReachabilityViaWiFi</tt> if the infrastructure is reachable via a
 *   Wi-Fi connection.
 * - <tt>GDReachabilityNotReachable</tt> if the infrastructure isn't reachable.
 * .
 * \endif
 */
@property (nonatomic, readonly) GDReachabilityStatus status;

#endif

/** Connection availability.
 *
 * The value of this property represents the availability of the connection
 * to the BlackBerry Dynamics infrastructure.
 * 
 * A change to the availability of the connection will trigger an infrastructure
 * status change notification to the application. See the class description, 
 * above, for details of how to register for these notifications. In addition, 
 * key-value observing (KVO) can be applied to this property.
 */
@property (nonatomic, readonly) BOOL isNetworkAvailable;

/** Push Channel availability.
 *
 * The value of this property represents the availability of the BlackBerry
 * Dynamics Push Channel service. For an overall description of how to use the
 * service, see under \ss_pushchannel_link.
 *
 * A change to the availability of the Push Channel service will trigger an
 * infrastructure status change notification to the application. See the class
 * description, above, for details of how to register for these notifications.
 * In addition, key-value observing (KVO) can be applied to this property.
 */
@property (nonatomic, readonly) BOOL isPushChannelAvailable;

#if TARGET_OS_IPHONE || TARGET_IPHONE_SIMULATOR
/** 
 * \if iOS
 * Connection availability (deprecated).
 * \deprecated This \ss_function is deprecated and will be removed in a future
 * release. Use the <tt>isNetworkAvailable</tt> property instead.
 * 
 * @return \ss_true if there is a current connection to the infrastructure.
 * @return \ss_false otherwise.
 * \endif
 */
+ (BOOL) isNetworkAvailable DEPRECATED_IN_GDREACHABILITY;
#endif

@end
