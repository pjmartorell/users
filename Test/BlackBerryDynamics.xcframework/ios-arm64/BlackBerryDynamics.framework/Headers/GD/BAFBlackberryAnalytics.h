/*
 * (c) 2020 BlackBerry Limited. All rights reserved.
 *
 */

#import <Foundation/Foundation.h>

/**
 * Invoked when the track event operation completes (optional).
 *
 * @param error The BAFAnalyticsResponse error returned if the operation fails.
 */
typedef void (^BAFAnalyticsResponseCompletion)(NSError *__nullable error) API_AVAILABLE(ios(9.0));

/** Analytics Event Type.
 * Use constants in this enumeration to indicate the type of analytics event being recorded. 
* The methods BlackBerryAnalytics.trackFeatureEvent and BlackBerryAnalytics.trackApplicationEvent always require one of these eventTypes. 
 */
typedef NS_ENUM(NSUInteger, BAFAnalyticsEvent) {
    /**
     * Record the start of an event which has a specific end point. 
     */
    BAFFeatureActive = 1000,
    
    /**
     * Record the end of an event which has a specific start point.
     */
    BAFFeatureInactive = 1001,
    
    /**
     * Record events or actions which occur in your application.
     */
    BAFAdoptionEvent = 1002,
};

/**
 * Security Event Type.
 */
typedef NS_ENUM(NSUInteger, BAFSecurityEventType) {
    /**
     * App Active Event.
     */
    BAFSecurityAppActive = 4001,
    
    /**
     * App Inactive Event.
     */
    BAFSecurityAppInactive = 4002,
    
    /**
     * Feature Active Event.
     */
    BAFSecurityFeatureActive = 4003,
    
    /**
     * Feature Inactive Event.
     */
    BAFSecurityFeatureInactive = 4004,
    
    /**
     * Adoption Event.
     */
    BAFSecurityAdoptionEvent = 4005,
};

/**
 *  App Usage Event Type.
 */
typedef NS_ENUM(NSUInteger, BISAppUsageEventType) {
    /**
     * Continuous Auth type event.
     */
    BISContinuousAuth = 0,
    
    /**
     * App Intelligence type event.
     */
    BISAppIntelligence,
};

/**
 * NSNotification name for changes to threat level during risk assessment.
 *
 * The name of the notification for which to register an observer.
 *
 * <tt>UserInfo</tt> dictionary from <tt>BISThreatLevelChangeNotification</tt> contains the following keys:\n
 * - BISThreatLevelChangeKey - contains the current threat level value as <tt>NSString</tt>
 */
extern NSString * _Nonnull const BISThreatLevelChangeNotification;

// Keys for Notification user info dictionary
/**
 * <tt>UserInfo</tt> dictionary from <tt>BISThreatLevelChangeNotification</tt> contains threat level change key. It has
 * value of type <tt>NSString</tt> for updated threat level.
 */
extern NSString * _Nonnull const BISThreatLevelChangeKey;



/** Class for BlackBerry Analytics and BlackBerry Persona
 *
 * <h3>BlackBerry Analytics </h3>
* 
* BlackBerry Analytics provides developers and UEM administrators metrics about the BlackBerry Dynamics 
* apps and devices in an organization's environment. BlackBerry Dynamics apps with this feature enabled 
* by their administrator will periodically send events (including startup, crash information) and data 
* (including OS, minutes used, app name, version) to the BlackBerry Analytics platform. The BlackBerry 
* Analytics platform processes and compiles the events and data into dashboard reports. 
* An app developer can optionally use this programmatic interface to record usage of custom features or 
* events within their app to enable these metrics to be included within the Analytics dashboard. 
* 
* For more information, see the <a href="https://docs.blackberry.com/en/endpoint-management/blackberry-analytics" target="_blank">BlackBerry Analytics documentation</a>.
*
*
* <h3>BlackBerry Persona</h3>
* 
* BlackBerry Persona processes events and location data from BlackBerry Dynamics apps to 
* assess a user’s security risk level based on their real-world context, and adjusts the user’s device 
* and app behavior based on their current risk level. For example, if a user’s app data reports a 
* geographic location that is not typical for the user, BlackBerry Persona can dynamically 
* limit the user’s access to work apps or disable certain device features such as the camera. In addition,
* it can be configured by the enterprise administrator to enforce stricter authentication requirements 
* by applying an override policy.
*
* This service requires enabling and configuration by the enterprise administrator. In addition, application 
* developers are required to perform steps to enable BlackBerry Persona.
* 
* <h4>Enabling BlackBerry Persona</h4>
*
* Implement these step to enable Persona within a BlackBerry Dynamics application.
*
*
*
*
* 1. Add the following custom properties to the <tt>Info</tt> section of your project target in Xcode. The resulting <tt>Info.plist</tt> file should contain:
*
* \code 
* <dict>
*   <key>BlackBerryDynamics</key>
*   <dict>
*     <key>EnableBlackBerryPersona</key>
*     <true/>
*   </dict>
* </dict>
* \endcode
*
* 2. Add a setting in the application user interface for end users to enable or disable BlackBerry Persona. 
*
* This setting should ideally be implemented within the 'Settings' or 'Preferences' section of your application's user interface.  
* When the user selects a menu item called 'BlackBerry Persona Settings' the application should call the method 
* BAFBlackberryAnalytics.displaySISsettings.
* This triggers the runtime to display a settings screen which provides the user the 
* option to opt in or out of using location based information when assessing their current risk level. This is a legal 
* requirement to ensure end users are able to opt out of location data collection at any time. It is best practice to 
* only show this option to users who have BlackBerry Persona enabled by their administrator, see  
* BAFBlackberryAnalytics.isSISenabled.
* 
* For more information, see the <a href="https://docs.blackberry.com/en/cylance-and-security/blackberry-persona-uem" target="_blank">BlackBerry Persona documentation</a>.
*
 * 
 */
@interface BAFBlackberryAnalytics : NSObject


/**
 * Record feature events to analyse the period a specific app feature is used. 
 *
 * Call to record an event that has a start point (a "feature active event") followed by a stop point 
* (a "feature inactive event"). The start and stop points provide a period of time where the feature was active. 
* This type of event is typically used to measure user engagement of app features. The name that is used to 
* track a feature must be unique within the app.
 *
 * @param event         BAFAnalyticsEvent specifies the type of event. For example, <tt>FEATURE_ACTIVE</tt> or <tt>FEATURE_INACTIVE</tt>.
 * @param featureName   <tt>NSString</tt> containing the name of the feature for a given event.
 * @param completion    The completion block to be invoked when the operation completes.
 * BAFAnalyticsResponse will return <tt>RECORD_SUCCESS</tt> if event is valid or a specific error otherwise.
 */
+ (void)trackFeatureEvent:(BAFAnalyticsEvent)event
          withFeatureName:(NSString *_Nonnull)featureName
               completion:(_Nullable BAFAnalyticsResponseCompletion)completion;

/**
 * Record adoption events to analyse the frequency of specific user actions or events. 
 *
 * Call to record an event which occurs in your application. An adoption event has two attributes, key and value. 
* The key must be unique within the app, and the value is a count of the number of times a specific event occurs (for example,
* an event key called "Emails deleted" that tracks the number of emails deleted by a user). The adoption event value should be the 
* string representation of the integer count. An app can combine events and record a single event.
 *
 * @param event         AnalyticsEvent specifies the type of event. In this case use <tt>ADOPTION_EVENT</tt>.
 * @param eventValue    <tt>NSString</tt> containing the event value to record for the given event key.
 * @param eventKey      <tt>NSString</tt> to define the name of the event.
 * @param completion    The completion block to be invoked when the operation completes.
 * BAFAnalyticsResponse will return <tt>RECORD_SUCCESS</tt> if event is valid or a specific error otherwise.
 */
+ (void)trackApplicationEvent:(BAFAnalyticsEvent)event
                    withValue:(NSString *_Nonnull)eventValue
                       forKey:(NSString *_Nonnull)eventKey
                   completion:(_Nullable BAFAnalyticsResponseCompletion)completion;


/**
 * Register a security event which will trigger BlackBerry Persona risk analysis.
 *
 * BlackBerry Persona risk analysis is performed by default when an application is brought to the foreground. 
* To trigger risk analysis at other points in your application life-cycle, use this method to register the appropriate events. 
* For example, your application could trigger risk analysis if a file is shared, money is transferred, or data is deleted. 
* 
* Call this method setting the <tt>eventVal</tt> to correspond with the specific application event which should trigger risk analysis, 
* e.g. 'SHARE_FILE'. Set SecurityEventType to <tt>SECURITY_ADOPTION_EVENT</tt> or other appropriate SecurityEventType. After you've 
* successfully registered the security event, all subsequent calls, in this example, to trackApplicationEvent with the 
* eventKey of 'SHARE_FILE' will trigger BlackBerry Persona risk analysis.
 *
 * @param eventType Specifies BAFSecurityEventType which event type should be security event.
 * @param eventVal Specifies name/label to associate with security event.
 */
+ (void)trackSecurityEvent:(BAFSecurityEventType)eventType
            withEventValue:(NSString *_Nullable)eventVal;

/**
 * Track App Usage events to detect anomalies in user behaviour.
 * 
 * BlackBerry Persona can perform enhanced risk analysis and continuous authentication by tracking anomalies in user behavior.
* The risk engine can detect a user's anomalous app usage behavior and enforce user identity either by requiring a user to re-authenticate 
* to confirm their identity, or by applying predefined policy.
 *
 * @param eventType specifies BISAppUsageEventType.
 * @param version specifies track api version.
 * @param appData specifies app usage data of app feature.
 * @param completion The completion block to be invoked when the operation completes.
 *
 *  
*
* To instrument user actions in your application, construct the following information to send within appData:
* 
* <h4>JSON Schema</h4>
*
* The following schema applies to the payload sent within <tt>appData</tt>
*
* \code
* appData:
    type: object
    description: Record data for model generation and scoring based on app usage
    required:
      - module
      - moduleVersion
      - eventTs
      - eventType
    properties:
      module:
        type: string
        description: App feature/module which the event corresponds to.
        example: 'email'
      moduleVersion:
        type: string
        description: Schema version of the payload. This version along with the application identifier is used by BlackBerry Persona service to process the payload.
        example: '1.0'
      eventTs:
        type: integer
        format: int64
        description: Time-stamp of the event expressed as an epoch.
        example: 994953488910
      eventType:
        type: string
        description: The type of custom action performed by the user within a module.
        example: 'SHARE'
      event:
        description: Optional object to include additional details related to an event. For example a search string or attributes of a file being shared. 
        type: object
        additionalProperties:
          description: Event specific fields (object type is a map)
          type: object
*\endcode
* 
* <h4>Module</h4>
*
* If your application contains disparate capabilities, subdivide these into modules, e.g. payments, email, editor. 
*
* <h4>EventType</h4>
*
* Identify a set of custom eventTypes which correspond to specific user actions within each module. The following are 
* examples of events that you may wish to track.
*
* - COPY
* - DELETE
* - FORWARD
* - DOWNLOAD
* - OPEN_IN
* - REPLY
* - SCREEN_SHOT
* - SCROLL_DOWN
* - SCROLL_UP
* - SEARCH
* - SEND
* - SHARE
* - SWIPE_LEFT
* - SWIPE_RIGHT
*
* <h4>Example Payload</h4>
*
* The following is an example of JSON payload for appData.
*
* \code
{
	"eventType": "SWIPE_RIGHT",
	"module": "email",
	"moduleVersion": "1.0",
	"eventTs": 1580938248291
},
{
	"eventType": "DELETE",
	"module": "filemanager",
	"moduleVersion": "1.0",
	"eventTs": 1580938248705
}
*\endcode
 *
 */
+ (void)trackAppUsagePattern:(BISAppUsageEventType)eventType
                     version:(NSUInteger)version
                        data:(NSDictionary<NSString *, NSObject *> *_Nonnull)appData
                  completion:(_Nullable BAFAnalyticsResponseCompletion)completion;

/**
 * Determine if BlackBerry Persona is enabled for the current user by their administrator.
 *
 * Call this method to determine if BlackBerry Persona is enabled for the current user. For help see 'Steps to configure and use BlackBerry Persona' within the 
* <a href="https://docs.blackberry.com/en/endpoint-management/blackberry-intelligent-security/latest" target="_blank">BlackBerry Persona documentation</a>.
 */
+ (BOOL)isSISenabled;

/**
 * Show a settings screen to enable the user to manage BlackBerrry Persona.
 *
 * Show a settings screen to enable the user to manage BlackBerrry Persona.
* The settings screen provides the user the option to opt in or out of using location based information 
* when assessing their current risk level. The settings can only be changed if BlackBerry Persona 
* is enabled for the user by the administrator. 
 */
+ (void)displaySISsettings;

// Deprecated public methods

/** 
 * Deprecated method
 *
 * @deprecated This method is deprecated and will be removed in a
 * future release.
 */
+ (void)sendGDAppEvent:(id _Null_unspecified )anEvent __attribute__((deprecated("Remove sendGDAppEvent: no longer required from this version")));

 /**
  * Deprecated method. 
  *
  * Returns SDK version.
  *
  * @return version <tt>NSString</tt> representation
  *
  * @deprecated now returns the BlackBerry Dynamics SDK version. Will be removed in a future release. See GDiOS.getVersion class.
  */
+ (NSString * _Nonnull)getAnalyticsVersion;

/**
 * Deprecated method. Implementation now does nothing. 
 * 
 * Method remains for compatibility support only
 *
 * @deprecated Will be removed in a future release. There is no replacement for this method call.
 */
+ (void)hostInitializationCompleted:(BOOL)proceedAnalyticsUX __attribute__((deprecated("Will be removed in a future release. There is no replacement for this method call.")));

/**
 * Deprecated method. Implementation now does nothing. 
 *
 * Method remains for compatibility support only.
 * @deprecated Will be removed in a future release. There is no replacement for this method call.
 */
+ (void)setStage;

#pragma mark - Threat Level APIs
/**
 * Deprecated method. 
 *
 * Returns the currently identified threat level determined by BlackBerry Persona.
 *
 * Threat level will contain following values:
 * LOW              app state is identified as low risk.
 * MEDIUM           app state is identified as medium risk.
 * HIGH             app state is identified as high risk.
 * CRITICAL         app state is identified as critical risk.
 * nil              when threat level is not available.
 *
 * @return returns value of type <tt>NSString</tt> which specifies current threat level.
 *
 * @deprecated Will be removed in a future release. Use BBDThreatStatus API instead
 * @see BBDThreatStatus.getOverallThreatLevel
 * @see BBDThreatGeoZone.getRiskLevel
 * @see BBDThreatIdentity.getRiskLevel
 */
+ (NSString *_Nullable)getThreatLevel;

/**
 * Deprecated method.
 *
 * Provides detailed threat information for each Persona risk engine. Applications may choose 
 * to take action on various threat factors based on the details provided.
 *
 *
 * @return JSONObject which contains the threat details or null.
 *
 * @deprecated Will be removed in the future release. Use BBDThreat API instead
 * @see BBDThreatStatus
 * @see BBDThreatGeoZone
 * @see BBDThreatIdentity
 */
+ (NSDictionary *_Nullable)getThreatDetails;

@end
