/*
 * (c) 2018 BlackBerry Limited. All rights reserved.
 *
 */

#ifndef __GD_IOS_H__
#define __GD_IOS_H__

#import <UIKit/UIKit.h>
#import "GDAppResultCode.h"
#import "GDPortability.h"
#import "GDAppConfig.h"
#import "GDVersion.h"

/* \cond DOXYGEN_IGNORE */
// See: http://clang.llvm.org/docs/LanguageExtensions.html
#ifndef __has_extension
#define __has_extension(x) 0  // Compatibility with non-clang compilers.
#endif
/* \endcond */

@class GDServiceProvider, GDVersion, GDState;


/** Constants for BlackBerry Dynamics service type.
 *
 * This enumeration represents the type of service for which a service discovery
 * query is being issued. The <tt>serviceType</tt> parameter of the
 * \ss_servicediscovery_link \ss_function always takes one of these values.
 */
typedef NS_ENUM(NSInteger, GDServiceType)
{
    /** Application-based service. */
    GDServiceTypeApplication=0,
    /** Server-based service. */
    GDServiceTypeServer,
};


/** Deprecated constants for BlackBerry Dynamics service provider type.
 *
 * \deprecated This enumeration is deprecated and will be removed in a future
 * release. Use \ref GDServiceType instead.
 *
 * This enumeration represents the type of service for which a service discovery
 * query is being issued. The <tt>serviceProviderType</tt> parameter of the
 * \ss_servicediscovery_link \ss_function always takes one of these values.
 */
typedef NS_ENUM(NSInteger, GDServiceProviderType)
{
    /** Application-based service.
     *
     * \deprecated The enumeration is deprecated and will be removed in a future
     * release. Use \ref GDServiceTypeApplication instead.
     */
    GDServiceProviderApplication __deprecated_enum_msg("Use GDServiceTypeApplication instead.") = 0,
    
    /** Server-based service.
     *
     * \deprecated The enumeration is deprecated and will be removed in a future
     * release. Use \ref GDServiceTypeServer instead.
     */
    GDServiceProviderServer __deprecated_enum_msg("Use GDServiceTypeServer instead"),
};


NS_ASSUME_NONNULL_BEGIN

/** Event dispatched from the BlackBerry Dynamics runtime.
 * 
 * This class is used to deliver events to the \ss_runtime_link event handler
 * in the application. See \ref GDiOSDelegate.
 */
@interface GDAppEvent : NSObject
{
   
    NSString* message;

    GDAppResultCode code;

    GDAppEventType type;
}

/** Textual description of the event.
 * 
 * This property contains a textual description of the event. The text is
 * suitable for display to the end user, at least for reporting diagnostic
 * information for support purposes.
 */
@property (nonatomic, copy) NSString* message;

/** Numeric result code.
 * 
 * This property contains a numeric result code.
 * For success events, the <tt>GDErrorNone</tt> code is used. Other values in
 * the \ref GDAppEvent.code enumeration are used for errors.
 */
@property (nonatomic, assign) GDAppResultCode code;
/* error code 0, means success */

/** Numeric event type.
 * 
 * This property contains a numeric type code. To determine the type of event
 * being notified, compare this property's value to the constants in the \ref
 * GDAppEvent.type enumeration.
 */
@property (nonatomic, assign) GDAppEventType type;

@end


/** Handler for events dispatched from the BlackBerry Dynamics Runtime,
 *  including authorization events.
 * 
 * Errors and state changes that occur when using \ss_runtime_link can be
 * handled by creating a class that implements this protocol.
 *
 * @see \ref GDState for an alternative interface.
 */
@protocol GDiOSDelegate
@optional

/** Callback for all events.
 * 
 * The callback is invoked whenever a BlackBerry Dynamics runtime object event
 * occurs. Runtime object events include authorization results, see
 * \ss_authorize_link for details.
 *
 * @param anEvent GDAppEvent populated with details of the event.
 */
- (void)handleEvent:(GDAppEvent*)anEvent;

@end

/** BlackBerry Dynamics Runtime object interface, including authorization.
 * 
 * \copydetails ssGDRunTime
 * 
 * \snippets_intro
 * \snippet{Authorization}
 * The following snippet shows initiation of BlackBerry Dynamics authorization.
 * \code
 * [GDiOS sharedInstance].delegate = self;
 * [[GDiOS sharedInstance] authorize];
 * \endcode
 * After executing the above code, the application would wait for its delegate
 * callback to be invoked. The invocation would have an event type of
 * <tt>GDAppEventAuthorized</tt> if the user was authorized. After that, the
 * application could make full use of all BlackBerry Dynamics capabilities.
 *
 * The above code relies on the identification parameters being in the
 * Info.plist file, as shown in the following snippet.
 * \code
 * <key>GDApplicationID</key>
 * <string>com.example.browser</string>
 * <key>GDApplicationVersion</key>
 * <string>1.0.0.0</string>
 * \endcode
 * The above is an extract from the XML of the application's Info.plist file.
 * The extract sets "com.example.browser" as the BlackBerry Dynamics entitlement
 * identifer, and "1.0.0.0" as the BlackBerry Dynamics entitlement version.
 *
 * \snippet{User interface pre-initialization}
 * The following snippet shows some necessary steps that precede initialization
 * of the application's user interface. The recommended place in the code for
 * these steps is as shown in the snippet.
 * \code
 *
 * - (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions
 * { 
 *     GDiOS *gdiOS = [GDiOS sharedInstance];
 *     gdiOS.delegate = self;
 *     started = NO;
 *     // Following line will cause the BlackBerry Dynamics user interface to open.
 *     [gdiOS authorize];
 *     return YES;
 * }
 * \endcode
 *
 * The above snippet shows the following sequence of actions.
 * -# A reference to the GDiOS singleton object is obtained.
 * -# The current class is set as the delegated event handler.
 * -# The <tt>started</tt> flag is set, to control initialization of the
 *    application's user interface, which is covered in the following snippet.
 *    The flag's declaration (not shown) would be <tt>BOOL</tt>.
 * -# The application initiates BlackBerry Dynamics authorization.
 * .
 * Authorization processing is asynchronous. On completion, an event will be
 * dispatched to the application's handler. The application completes user
 * interface initialization within its event handler, as shown in the following
 * code snippet.
 *
 * \snippet{User interface initialization}
 * The following snippet shows the recommended place in the code to initialize
 * the application's user interface.
 * \code
 *
 * -(void)handleEvent:(GDAppEvent*)anEvent
 * {
 *     switch (anEvent.type) {
 *         case GDAppEventAuthorized: {
 *             if (!started) {
 *                 [self initializeUI];
 *                 started = YES;
 *             }
 *             break;
 *         }
 *
 *         case GDAppEventNotAuthorized: {
 *             [self onNotAuthorized:anEvent];
 *             break;
 *         }
 *
 *         case GDAppEventRemoteSettingsUpdate:
 *         case GDAppEventServicesUpdate:
 *         case GDAppEventPolicyUpdate:
 *         default: {
 *             // This application ignores other types of event.
 *             break;
 *         }
 *     }
 * }
 * \endcode
 * The above code shows a simple BlackBerry Dynamics runtime event handler.
 *
 * The handler calls the application's own <tt>initializeUI</tt> function when a
 * <tt>GDAppEventAuthorized</tt> event is received for the first time. The
 * application's <tt>started</tt> flag is used to control first-time execution.
 * Initialization of this flag is shown in the previous snippet.\n
 * The <tt>initializeUI</tt> function would complete user interface
 * initialization, utilizing a reference to the BlackBerry Dynamics runtime
 * <tt>UIWindow</tt>. This reference can be obtained using the <tt>window</tt>
 * property from the main app delegate.
 *
 * The handler calls the application's own <tt>onNotAuthorized</tt> function
 * whenever a <tt>GDAppEventNotAuthorized</tt> event is received.
 */
@interface GDiOS : NSObject

/** Get a reference to the runtime interface object.
 * 
 * \copydetails ssGDRunTimeSharedInstance
 */
+ (instancetype)sharedInstance;

/** Connect to the BlackBerry Dynamics infrastructure.
 * 
 * \copydetails ssGDRunTimeAuthorise
 *
 * @param delegate Reference to the delegated event handler, typically
 *                 <tt>self</tt>.
 *
 * Application identification parameters will be read from the following properties
 * in the application Info.plist fi<tt></tt>le:<table>
 *     <tr><th>Key</th><th>Type</th><th>Value</th>
 *     </tr><tr><td>
 *         <tt>GDApplicationID</tt></td>
 *         <td><tt>String</tt></td>
 *         <td>BlackBerry Dynamics entitlement identifier.\n
 *         (This identifier was previously referred to as the Good Dynamics
 *         application identifier, or in the abbreviated form GD App ID.)\n
 *         This identifier is used to control access to the application by end
 *         users, and to configure its application server connections. The value
 *         passed must be the same as the value present in the enterprise
 *         management console.\n
 *         (Note that the value needn't be the same as the native application
 *         identifier.)\n
 *         For syntax details see under Entitlement Identifier Format,
 *         above.</td>
 *     </tr><tr><td>
 *         <tt>GDApplicationVersion</tt></td>
 *         <td><tt>String</tt></td>
 *         <td>BlackBerry Dynamics entitlement version number\n The version
 *         number can be combined with the entitlement identifier, above, to
 *         control access to particular versions of the application.</td>
 *     </tr>
 * </table>
 * (In case there are multiple Info.plist files, check that the correct one has
 * been edited by opening the Info tab of the application target being built.
 * The settings should appear there.)
 * 
 * Authorization is asynchronous. When authorization processing completes:
 * - The delegate \link GDiOSDelegate::handleEvent: handleEvent\endlink callback
 *   is invoked.
 * - The \ref GDState singleton object is updated, and any observers of that
 *   object are sent notifications.
 * .
 *
 * @see \ref GC
 * @see \ref enterprisesimulation.
 */
- (void)authorize:(id<GDiOSDelegate> _Nonnull)delegate;

/** Connect to the BlackBerry Dynamics infrastructure, without specifying a
 *  delegate.
 * 
 * Call this \ss_function to initiate BlackBerry Dynamics authorization
 * processing without specifying a delegated event handler. This style of call
 * can be used in the following cases.
 * - The <tt>delegate</tt> property has already been set directly, to a
 *   GDiOSDelegate implementation.
 * - The application uses the \ref GDState interface to monitor authorization
 *   state, doesn't implement <tt>GDiOSD</tt><tt>elegate</tt>, and has switched
 *   off the event receiver check. (Instructions for switching off are on the
 *   \ref BuildTimeConfiguration page, under the Event Receiver Check heading.)
 * .
 * 
 * Calling this \ss_function is otherwise equivalent to calling the
 * <tt>authorize:</tt> \ss_function, above. See \ss_authorize_link for details.
 */
- (void)authorize;

/** Connect to the BlackBerry Dynamics infrastructure in background.
 *
 * Call this \ss_function to initiate BlackBerry Dynamics authorization
 * processing in background.
 *
 * This \ss_function should be called when the application is launched in
 * background. This could happen if any of the following are in use.
 * - Apple Push Notification Service (APNS).
 * - Background fetch.
 * .
 *
 * Authorization processing can complete in background, if all the following
 * conditions are met:
 * - Activation has completed. The application must have run in foreground and
 *   completed BlackBerry Dynamics authorization processing at least once for
 *   this to be the case.
 * - Authorization can complete autonomously, without user interaction, i.e. a
 *   <em>no-password</em> enterprise policy is in effect for the current end
 *   user.
 * - The application is currently in background.
 * .
 * 
 * Call this \ss_function from any callback that handles background launch, for
 * example the application <tt>didReceiveRemoteNotification:</tt> or
 * <tt>performFetchWithCompletionHandler:</tt> \ss_function. Access the
 * \ss_runtime_link{canAuthorizeAutonomously} property first, to check that a
 * no-password policy applies to the current end user and that autonomous
 * authorization is possible.
 * 
 * If authorization can complete autonomously, calling this \ss_function
 * results in the same processing and notification as if \ss_authorize_link had
 * been called. Application identification parameters will be read from the
 * Info.plist file.
 *
 * @param delegate Reference to the delegated event handler, typically
 *                 <tt>self</tt>.
 *        
 * @return \ss_true if authorization can complete autonomously. The application
 *         will be notified when authorization completes, or if it fails for
 *         some reason.
 * @return \ss_false if authorization cannot complete autonomously. No further
 *         notification will be dispatched.
 */
- (BOOL)authorizeAutonomously:(id<GDiOSDelegate> _Nonnull)delegate;

/** Connect to the BlackBerry Dynamics infrastructure in background, without
 *  specifying a delegate.
 * 
 * Call this \ss_function to initiate autonomous BlackBerry Dynamics
 * authorization processing without specifying a delegated event handler. This
 * style of call can be used in the same cases as the
 * \ss_runtime_link{authorize} \ss_function that takes no parameters, see above.
 * 
 * Calling this \ss_function is otherwise equivalent to calling the
 * <tt>authorizeAutonomously:</tt> \ss_function, above.
 * 
 * See \ss_runtime_link{authorizeAutonomously:} for details.
 */
- (BOOL)authorizeAutonomously;

/** String constants used as keys for programmatic activation parameters.
 *\copydetails ssGDRunTimeProgrammticActivationParameters
 * \link GDiOS::programmaticAuthorize: \endlink
 */
typedef NSString *ActivationParameter;
extern ActivationParameter const ActivationParameterUserIdentifier;
extern ActivationParameter const ActivationParameterAccessKey;
extern ActivationParameter const ActivationParameterNOCAddress;
extern ActivationParameter const ActivationParameterShowUserInterface;
extern ActivationParameter const ActivationParameterEnrollmentAddress;
extern ActivationParameter const ActivationParameterPassword;

/** Initiate programmatic activation.
 *
 * \copydetails ssGDRunTimeProgrammaticAuthoriseWithActivationParameters
 * @param activationParameters \ss_Apple_Android{<tt>NSDictionary</tt>,<tt>Map&lt;String\, Object&gt;</tt>}
 *         object containing configuration values. Use the
 *         <tt>ActivationParameter</tt> string constants as keys.
 */
- (void)programmaticAuthorize:(NSDictionary<ActivationParameter, id> *)activationParameters;

/* \cond DOXYGEN_IGNORE */
#if __has_extension(attribute_deprecated_with_message)
#   define DEPRECATE_PROGRAMMATICAUTHORIZE __attribute((deprecated("Use -programmaticAuthorize:activationParameters instead.")))
#else
#   define DEPRECATE_PROGRAMMATICAUTHORIZE __attribute((deprecated))
#endif
/* \endcond */

/** Initiate programmatic activation (deprecated).
 *
 * \deprecated This \ss_function is deprecated and will be removed in a future
 * release. Use
 * \link GDiOS::programmaticAuthorize: \endlink
 * instead.
 *
 * \copydetails ssGDRunTimeProgrammaticAuthorise
 */
- (void)programmaticAuthorize:(NSString *)userID  withAccessKey:(NSString *)accessKey DEPRECATE_PROGRAMMATICAUTHORIZE;

/** Initiate programmatic activation by a specific Network Operation Center (deprecated).
 *
 * \deprecated This \ss_function is deprecated and will be removed in a future
 * release. Use
 * \link GDiOS::programmaticAuthorize: \endlink
 * instead.
 *
 * \copydetails ssGDRunTimeProgrammaticAuthoriseWithNOC
 */
- (void)programmaticAuthorize:(NSString *)userID
                withAccessKey:(NSString *)accessKey
       networkOperationCenter:(NSURL *)nocAddress DEPRECATE_PROGRAMMATICAUTHORIZE;

#undef DEPRECATE_PROGRAMMATICAUTHORIZE

/** Application activation status.
 *
 * Read the value of this property, using the <tt>isActivated</tt> accessor, to
 * check whether the application has already been activated. It is necessary to
 * check whether the application has been activated before initiating
 * programmatic activation.
 *
 * This property has the value:
 * - \ss_true if the application has been activated.
 * - \ss_false otherwise.
 * .
 */
@property (nonatomic, assign, readonly, getter=isActivated) BOOL activationComplete;

/** Get application configuration and other settings from the enterprise.
 * 
 * \copydetails ssGDRunTimeApplicationConfig
 */
- (NSDictionary<NSString *, id> *)getApplicationConfig;

/** Get application-specific policy settings from the enterprise management
 *  console, as a collection.
 *  
 * \copydetails ssGDRunTimeApplicationPolicy
 */
- (NSDictionary<NSString *, id> *)getApplicationPolicy;

/** Get application-specific policy settings from the enterprise management
 *  console, as JSON.
 * 
 * \copydetails ssGDRunTimeApplicationPolicyString
 */
- (NSString*)getApplicationPolicyString;

/** Get providers of shared services.
 * 
 * \copydetails ssGDRunTimeServiceProviders
 */
- (NSArray<GDServiceProvider *> *)getServiceProviders;

/** Discover providers of a specific shared service.
 *
 *  \copydetails ssGDRunTimeServiceProvidersForType
 */
- (NSArray<GDServiceProvider *> *)getServiceProvidersFor:(NSString*)serviceId andVersion:(nullable NSString*)version andServiceType:(GDServiceType)serviceType;

/* \cond DOXYGEN_IGNORE */
#if __has_extension(attribute_deprecated_with_message)
#   define DEPRECATE_GETSERVICEPROVIDERSFOR __attribute((deprecated("Use getServiceProvidersFor:andVersion:andServiceType:")))
#else
#   define DEPRECATE_GETSERVICEPROVIDERSFOR __attribute((deprecated))
#endif
/* \endcond */

/** Discover providers of a specific shared service (deprecated).
 * 
 * \deprecated This \ss_function is deprecated and will be removed in a future
 * release. Use
 * \link GDiOS::getServiceProvidersFor:andVersion:andServiceType: \endlink
 * instead.
 *
 * \copydetails ssGDRunTimeServiceProvidersFor
 */
- (NSArray<GDServiceProvider *> *)getServiceProvidersFor:(NSString*)serviceId andVersion:(nullable NSString*)version andType:(GDServiceProviderType)serviceProviderType DEPRECATE_GETSERVICEPROVIDERSFOR;

#undef DEPRECATE_GETSERVICEPROVIDERSFOR

/** Type for getEntitlementsFor block parameter.
 * 
 * Pass a code block of this type as the <tt>block</tt> parameter to the
 * \link GDiOS::getEntitlementVersionsFor:callbackBlock:
 * getEntitlementVersionsFor: \endlink \ss_function.
 *
 * The block receives the following parameters.
 * @param entitlementVersions <tt>NSArray</tt> of \ref GDVersion objects
 *                            representing the versions of the entitlement to
 *                            which the end user is entitled if the original
 *                            call succeeded, or \ss_null otherwise.
 * 
 * @param error <tt>NSError</tt> containing a description of the error condition
 *                               if the original call failed, or \ss_null
 *                               otherwise.
 */
typedef void (^GDGetEntitlementVersionsForBlock) (NSArray<GDVersion *>* GD_NSNULLABLE_POINTER entitlementVersions, NSError* error);

/** Check whether the end user has a particular entitlement.
 * 
 * \copydetails ssGDRunTimeEntitlementVersions
 */
- (void)getEntitlementVersionsFor:(NSString*)identifier
                    callbackBlock:(GDGetEntitlementVersionsForBlock)block;

/* \cond DOXYGEN_IGNORE */
#if __has_extension(attribute_deprecated_with_message)
#   define DEPRECATE_GETWINDOW __attribute((deprecated("Use the window property from the main app delegate instance.")))
#else
#   define DEPRECATE_GETWINDOW __attribute((deprecated))
#endif
/* \endcond */

/** Get the <tt>UIWindow</tt> for the application (deprecated).
 * \deprecated This \ss_function is deprecated and will be removed in a future
 * release. Use the <tt>window</tt> property from the main app delegate instance.
 *
 * This \ss_function returns a reference to the <tt>UIWindow</tt> that contains
 * the core logic of the BlackBerry Dynamics runtime. Always use this \ss_function
 * instead of creating a new <tt>UIWindow</tt> in the application.
 *
 * The BlackBerry Dynamics runtime creates its own <tt>UIWindow</tt> in order to
 * show its user interface elements, and to track for user inactivity. The
 * runtime doesn't add any persistent subviews, so the application is free to
 * add and remove its own subviews on the BlackBerry Dynamics <tt>UIWindow</tt>.
 * For example, after authorization, the application could call
 * <tt>setRootViewController</tt> to add its own <tt>UIViewController</tt> or
 * <tt>UINavigationController</tt>.
 *
 * The runtime calls <tt>makeKeyAndVisible</tt> on its <tt>UIWindow</tt> during
 * authorization processing, so the application needn't do this. The application
 * mustn't make a different <tt>UIWindow</tt> the key window. The application
 * also mustn't release the runtime's <tt>UIWindow</tt> object.
 *
 * @return Reference to the BlackBerry Dynamics <tt>UIWindow</tt>, which must be
 *         used as the application's key window.
 *
 * @see <a
 *     HREF="https://developer.apple.com/reference/uikit/uiwindow?language=objc"
 *     target="_blank"
 * >UIWindow class reference</a> in the Apple API Reference on the apple.com
 * developer website.
 */
- (UIWindow*)getWindow DEPRECATE_GETWINDOW;

#undef DEPRECATE_GETWINDOW

/** Get the BlackBerry Dynamics runtime library version.
 * @return <tt>NSString</tt> containing the BlackBerry Dynamics runtime library
 *         version in
 *         <em>major</em><tt>.</tt><em>minor</em><tt>.</tt><em>build</em>
 *         format.
 */
- (NSString*)getVersion;

/** Open the BlackBerry Dynamics preferences user interface.
 * 
 * Call this \ss_function to show the BlackBerry Dynamics preferences user
 * interface. This is the interface in which the end user sets any options that
 * are applied by the runtime directly, without reference to the application.
 * This includes, for example, changing their unlock password.
 * 
 * This \ss_function enables a BlackBerry Dynamics user interface element to be
 * included in the application's own user interface.
 *
 * @param baseViewController Reference to the navigation controller within which
 *        the BlackBerry Dynamics user interface element is to open as a view
 *        controller.\n
 *        Pass a null pointer to open the the user interface as a modal view
 *        controller, for example when no navigation controller is available.
 *
 * @return \ss_true if the user interface element opened OK.
 * @return \ss_false if the user interface element was already open, or if 
 *                   authorization is delegated to another application.
 */
- (BOOL)showPreferenceUI:(nullable UIViewController*)baseViewController;

/** Configure the visual appearance of the BlackBerry Dynamics user interface.
 * 
 * \copydetails ssGDRunTimeConfigureUI
 */
- (void)configureUIWithLogo:(NSString*)imagePath
                     bundle:(nullable NSBundle*)bundle
                      color:(nullable UIColor*)color;

/* \cond DOXYGEN_IGNORE */
#if __has_extension(attribute_deprecated_with_message)
#   define DEPRECATE_CONFIG_UI_WITH_BLOCK_MESSAGE __attribute__((deprecated("No longer supported")))
#   define DEPRECATE_CONFIG_UI_WITH_WIPE_MESSAGE __attribute__((deprecated("No longer supported")))
#else
#   define DEPRECATE_CONFIG_UI_WITH_BLOCK_MESSAGE __attribute__((deprecated))
#   define DEPRECATE_CONFIG_UI_WITH_WIPE_MESSAGE __attribute__((deprecated))
#endif
/* \endcond */

/** Customize the BlackBerry Dynamics blocked screen (deprecated).
 * 
 * \copydetails ssGDRunTimeConfigureUIWithBlockedMessage
 */
- (void)configureUIWithBlockedMessage:(nullable NSString*)message DEPRECATE_CONFIG_UI_WITH_BLOCK_MESSAGE;

/** Customize the BlackBerry Dynamics wiped screen (deprecated).
 * 
 * \copydetails ssGDRunTimeConfigureUIWithWipedMessage
 */
- (void)configureUIWithWipedMessage:(nullable NSString*)message DEPRECATE_CONFIG_UI_WITH_WIPE_MESSAGE;

/** Delegated event-handling.
 * 
 * When authorization processing completes, or a BlackBerry Dynamics runtime
 * object event occurs, an event is generated by the runtime, and passed to a
 * callback function in the application code.
 *
 * Set this property to an instance of a class in the application that contains
 * the code for the required callback function, i.e. a class that implements
 * the GDiOSDelegate protocol.
 *
 * @see \ref GDState for an alternative mechanism.
 */
@property (nullable, nonatomic, weak) id<GDiOSDelegate> delegate;

/* \cond DOXYGEN_IGNORE */
#if __has_extension(attribute_deprecated_with_message)
#   define DEPRECATE_LAUNCHOPTIONS __attribute__((deprecated("No longer required.")))
#else
#   define DEPRECATE_LAUNCHOPTIONS __attribute__((deprecated))
#endif
/* \endcond */

/** Application launch options (deprecated).
 *
 * \deprecated This property is deprecated and will be removed in a future release.
 *
 * Access this property to obtain the options with which the application was
 * launched. The property is a reference to an object with the same semantics as
 * the <tt>launchOptions</tt> parameter to the
 * <tt>application:didFinishLaunchingWithOptions:</tt> function in the
 * <tt>UIApplicationDelegate</tt> protocol.
 *
 * There is a known issue in the BlackBerry Dynamics SDK for iOS that this
 * property isn't always populated.
 * 
 * @see <a
 *     HREF="https://developer.apple.com/reference/uikit/uiapplicationdelegate/1622921-application?language=objc"
 *     target="_blank"
 * >application:didFinishLaunchingWithOptions: documentation</a> in the Apple
 * API Reference on the apple.com developer website, for details.
 */
@property (nullable, nonatomic, strong) NSDictionary<NSObject *, id>* launchOptions DEPRECATE_LAUNCHOPTIONS;

/** Whether it is possible to authorize autonomously.
 *
 * \copydetails ssCanAuthorizeAutonomously
 */
@property (nonatomic, readonly) BOOL canAuthorizeAutonomously;

/** Lock the application permanently.
 * 
 * \copydetails ssGDRunTimeExecuteRemoteLock
 */
- (BOOL)executeRemoteLock;

/** Blocks application locally with defined blockId.
 *
 * \copydetails ssGDRunTimeExecuteBlock
 */
- (void)executeBlock:(NSString *)blockId withTitle:(NSString *)title withMessage:(NSString *)message;

/** Unblocks application locally with defined blockId.
 *
 * \copydetails ssGDRunTimeExecuteUnBlock
 */
- (void)executeUnblock:(NSString *)blockId;

/** Executes migration of the application to a different management console.
 * @return <tt>YES</tt> if destinationTenantID is provided
 * @return <tt>NO</tt> if destinationTenantID is empty
 *
 * \copydetails ssGDRunTimeExecutePendingConsoleMigration
 */
-(BOOL)executePendingConsoleMigration:(NSString *)destinationTenantID withUemServerAddress:(NSString *)uemServerAddress;

/** Observable representation of authorization state and user interface state.
 *
 * Access this property to check or observe the state of the BlackBerry Dynamics
 * runtime.
 *
 * A number of aspects of run-time state are represented in this property,
 * including authorization state and user interface state. The representation is
 * compatible with key-value observing (KVO). See the \link GDState \endlink
 * class reference for details.
 * 
 * @return GDState instance representing the current state.
 */
@property (nonatomic, strong, readonly) GDState *state;

@end

NS_ASSUME_NONNULL_END

#endif /* __GD_IOS_H__ */
