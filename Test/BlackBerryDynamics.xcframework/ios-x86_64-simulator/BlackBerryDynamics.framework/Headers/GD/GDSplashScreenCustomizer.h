/*
 * (c) 2020 BlackBerry Limited. All rights reserved.
 *
 */

#import <Foundation/Foundation.h>


/** Delegate for handling GDSplashScreenCustomizer callback when a splash screen is about to be displayed.
 *
 * The GDSplashScreenCustomizerDelegate protocol includes a single property which
 * enables an application to display a custom view controller instead of the default
 * BlackBerry Dynamics splash screen when an application becomes inactive.
 */

@protocol GDSplashScreenCustomizerDelegate <NSObject>

@optional

/** If current property returns a custom view controller, then it will be
 * displayed instead of the default BlackBerry Dynamics splash screen.
 *
 * The getter method of this current property is called on the main thread right before
 * the splash screen is displayed. Due to this, it is essential to make sure the current method
 * does not carry out intensive computations as it might slow down the
 * responsiveness of the user interface.
 *
 * If the application accesses underlying instance variables from a background thread,
 * access to the current property must be synchronized.
 *
 * Note: <tt>customSplashScreenViewController.view</tt> should cover the whole
 * application screen and be opaque, otherwise the underlying BlackBerry Dynamics 
 * splash screen will show through.
 *
 */

@property (atomic, strong, readonly) __kindof UIViewController * _Nullable customSplashScreenViewController;

@end


/** Display a custom view controller instead of the default BlackBerry Dynamics splash screen
 * 
 *
 * When a BlackBerry Dynamics applications becomes inactive by default a BlackBerry 
 * branded splash screen is shown. This screen contains a BlackBerry logo in the center 
 * with no text. It is shown when the user sends the app to the background, 
 * transitions between apps, or when a system alert is displayed. 
 *
 * There are two ways to customize the BlackBerry branded splash screen. 
 *
 * <h3>Build-time splash screen replacement</h3>
 *
 * Add a value to your application plist using the key 'UILaunchStoryboardName'. When this 
 * value is configured, the runtime will attempt to instantiate a splash screen from the 
 * storyboard with this name. By default in Xcode the name will be 'LaunchScreen'.
 *
 * <h3>Runtime splash screen replacement</h3>
 *
 * To customize the splash screen during the life-cycle of your application, for 
 * example to handle the user experience for specific system events, use this class and
 * its associated delegate. This will enable you to replace the build-time splash screen 
 * with a custom view controller. 
 *
 */

@interface GDSplashScreenCustomizer : NSObject

/** Class method which returns a unique instance of
 * GDSplashScreenCustomizer singleton class.
 *
 * Obtain a unique instance of the GDSplashScreenCustomizer singleton class. 
 */

+ (nonnull instancetype)sharedInstance;

/** An object that acts as a delegate and enables an application to display a 
 * custom view controller.
 *
 * If an application sets its own object as <tt>splashScreenCustomizerDelegate</tt> 
 * then the GDSplashScreenCustomizerDelegate protocol callback method
 * <tt>customSplashScreenViewController</tt> will be called prior to displaying 
 * a splash screen. This enables the application to set a custom view 
 * controller instead of the default BlackBerry Dynamics splash screen.
 *
 */

@property (atomic, weak) id <GDSplashScreenCustomizerDelegate> _Nullable splashScreenCustomizerDelegate;

@end
