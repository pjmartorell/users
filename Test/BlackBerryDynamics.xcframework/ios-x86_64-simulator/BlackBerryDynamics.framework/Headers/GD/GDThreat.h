    /*
* (c) 2020 BlackBerry Limited. All rights reserved.
*
*/

#pragma once

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

/** Enumeration to indicate the level of risk posed by a threat.
* 
* The overall threat level is returned as part BBDThreatStatus.getOverallThreatLevel. 
* To understand the risk for specific threat type use BBDThreat.getRiskLevel.
*
* To determine if a specific threat type is being evaluated you can also use BBDThreat.getDetectionEnabled.
*/
typedef NS_ENUM(NSInteger, BBDThreatLevel)
{
    /**
    * A critical threat has been detected which requires immediate action.
    */
    Critical = 0,
    /**
    * A high threat requires the user or administrator to take action.
    */
    High = 1,
    /**
    * A medium threat indicates moderate risk and can be interpreted as an advisory.
    */
    Medium = 2,
    /**
    * There is no threat detected or the risk level is low.
    */
    Low = 3,
    /**
    * The threat level is unknown or not evaluated. 
    */
    Null = 4,
};

/** Constants for GDComplianceType.
*
* The enumeration for types of threats detected by the runtime.
*/
typedef NS_ENUM(NSInteger, BBDThreatType)
{
    /** Detect malicious applications or malware on an Android device.
    *
    * \copydetails ssThreatStatusAppMalware
    */
    AppMalware = 0,

    /**
    * Detect applications installed from an untrusted source on Android devices.
    *
    * \copydetails ssThreatStatusAppSideload
    */
    AppSideload = 1,

    /**
    * Detect when device level security is compromised.
    *
    * \copydetails ssThreatStatusDeviceSecurity
    */
    DeviceSecurity = 2,

    /**
    * Detect when the device operating system or security patches do not meet recommended standards.
    *
    * \copydetails ssThreatStatusDeviceOS
    */
    DeviceSoftware = 3,

    /**
    * Detect when network or browsing requests are made to malicious links.
    *
    * \copydetails ssThreatStatusSafeBrowsing
    */
    SafeBrowsing = 4,

    /**
    * Detect when messages contain malicious content or links.
    *
    * \copydetails ssThreatStatusSafeMessaging
    */
    SafeMessaging = 5,

    /**
    * Determine a user’s security risk level based on their real-world context.
    *
    * \copydetails ssThreatStatusGeoZone
    */
    GeoZone = 6,

    /**
    * Determine whether current application activity matches the behavior and identity of the authorized user.
    *
    * \copydetails ssThreatStatusIdentity
    */
    Identity = 7,
    
    /**
    * Detect when the application's integrity is at risk or the app requires updating.
    *
    * \copydetails ssThreatStatusApplicationSecurity
    */
    ApplicationSecurity = 8,

    
    /**
    * Detect when applications from an untrusted developer are permitted to be installed on an iOS device.
    *
    * \copydetails ssThreatStatusUntrustedDeveloper
    */
    UntrustedDeveloper = 9,

    /**
    * Detect when networking is subject to man in the middle attack.
    *
    * \copydetails ssThreatStatusNetworkSecurity
    */
    NetworkSecurity = 10,
    
    /**
    * Detect if attached WiFi network is insecure.
    *
    * \copydetails ssThreatStatusWiFiSecurity
    */
    WiFiSecurity = 11,

    /**
    * Detect when the device has been offline for an extended period of time.
    *
    * \copydetails ssThreatStatusDeviceOffline
    */
    DeviceOffline = 12
};

/**
* Interface for retrieving threat details for a specific BBDThreatType.
*/
@interface BBDThreat: NSObject

/**
 * Indicate the type of threat being checked.
 *
 * Indicate the specific type of threat being checked.
 *
 * @return BBDThreatType.
 */
- (BBDThreatType)getType;

/**
 * Determine when the check last completed. 
 *
 * Return the timestamp of when the threat was last evaluated. For example, when a malware scan was last completed.
 *
 * @return <tt>long</tt> Unix timestamp in milliseconds of when the check last ran. The result is 0 if checks have not yet been performed, 
 * for example after the app hosting the runtime has just been installed.
 */
- (long)getEvaluatedTime;

/**
 * Return the level of risk posed by the threat. 
 * 
 * Return the level of risk posed by the threat. 
 *
 * @return BBDThreatLevel
 */
- (BBDThreatLevel)getRiskLevel;

/**
 * Check whether the threat is being evaluated.
 *
 * Check whether the threat is being evaluated by the runtime. If detection is not enabled it may be 
 * because the feature hasn't been enabled by the enterprise administrator. Alternatively for some 
 * threats, like GeoZone, the end user is required to allow a specific a system permission, e.g. location,
 * in order for the runtime to be able to perform checks. If a required permission is not allowed by the user
 * the threat detection will be disabled.
 *
 * @return <tt>YES</tt> if the detection is enabled.
 * @return <tt>NO</tt> if detection is disabled. 
 */
- (BOOL)getDetectionEnabled;

/**
 * Get information on possible remediation actions to the threat.
 *
 * Return a string providing any possible remediation actions or further details about the threat.
 *
 * @return <tt>NSString</tt> providing remediation information.
 */
- (NSString* )getInfo;

 /**
 * Only the subclasses of BBDThreat maybe instantiated.
 */
- (instancetype)init NS_UNAVAILABLE;
+ (instancetype)new NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END
