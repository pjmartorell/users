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
 * \copydetails ssAnalyticsEventType
 */
typedef NS_ENUM(NSUInteger, BAFAnalyticsEvent) {
    /**
     * \copydetails ssAnalyticsFeatureActive 
     */
    BAFFeatureActive = 1000,
    
    /**
     * \copydetails ssAnalyticsFeatureInActive
     */
    BAFFeatureInactive = 1001,
    
    /**
     * \copydetails ssAnalyticsFeatureAdoption
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
 * \copydetails ssAnalytics 
 * 
 */
@interface BAFBlackberryAnalytics : NSObject


/**
 * Record feature events to analyse the period a specific app feature is used. 
 *
 * \copydetails ssAnalyticsFeatureEvent
 *
 * @param event         BAFAnalyticsEvent specifies the type of event. For example, <tt>FEATURE_ACTIVE</tt> or <tt>FEATURE_INACTIVE</tt>.
 * @param featureName   \ss_string containing the name of the feature for a given event.
 * @param completion    The completion block to be invoked when the operation completes.
 * BAFAnalyticsResponse will return <tt>RECORD_SUCCESS</tt> if event is valid or a specific error otherwise.
 */
+ (void)trackFeatureEvent:(BAFAnalyticsEvent)event
          withFeatureName:(NSString *_Nonnull)featureName
               completion:(_Nullable BAFAnalyticsResponseCompletion)completion;

/**
 * Record adoption events to analyse the frequency of specific user actions or events. 
 *
 * \copydetails ssAnalyticsAdoptionEvent
 *
 * @param event         AnalyticsEvent specifies the type of event. In this case use <tt>ADOPTION_EVENT</tt>.
 * @param eventValue    \ss_string containing the event value to record for the given event key.
 * @param eventKey      \ss_string to define the name of the event.
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
 * \copydetails ssAnalyticsSecurityEvent
 *
 * @param eventType Specifies BAFSecurityEventType which event type should be security event.
 * @param eventVal Specifies name/label to associate with security event.
 */
+ (void)trackSecurityEvent:(BAFSecurityEventType)eventType
            withEventValue:(NSString *_Nullable)eventVal;

/**
 * Track App Usage events to detect anomalies in user behaviour.
 * 
 * \copydetails ssAnalyticsAppUsageEvent
 *
 * @param eventType specifies BISAppUsageEventType.
 * @param version specifies track api version.
 * @param appData specifies app usage data of app feature.
 * @param completion The completion block to be invoked when the operation completes.
 *
 * \copydetails ssAnalyticsAppUsageEventJSON
 *
 */
+ (void)trackAppUsagePattern:(BISAppUsageEventType)eventType
                     version:(NSUInteger)version
                        data:(NSDictionary<NSString *, NSObject *> *_Nonnull)appData
                  completion:(_Nullable BAFAnalyticsResponseCompletion)completion;

/**
 * Determine if BlackBerry Persona is enabled for the current user by their administrator.
 *
 * \copydetails ssAnalyticsIsSISenabled
 */
+ (BOOL)isSISenabled;

/**
 * Show a settings screen to enable the user to manage BlackBerrry Persona.
 *
 * \copydetails ssAnalyticsDisplaySISsettings
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
  * @return version \ss_string representation
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
