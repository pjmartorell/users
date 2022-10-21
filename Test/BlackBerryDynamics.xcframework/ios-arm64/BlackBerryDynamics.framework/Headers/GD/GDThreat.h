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
    * Detects malicious applications or malware on an Android device using models built with machine learning 
* to analyze the app package. 
*
* Requires BlackBerry Mobile Threat Defense (MTD) to be enabled.
    */
    AppMalware = 0,

    /**
    * Detect applications installed from an untrusted source on Android devices.
    *
    * Detect applications that the user has installed from untrusted source on Android devices. 
* Sideloaded apps are installed manually rather than from an official app store. Applications not from an 
* official app store pose a security risk. 
*
* Requires BlackBerry Mobile Threat Defense (MTD) to be enabled.
    */
    AppSideload = 1,

    /**
    * Detect when device level security is compromised.
    *
    * Device security encapsulates a range of checks to determine the security health of the users device. For example
* if the user has rooted or jailbroken the device, whether the disk is unencrypted, if the user has set a screen
* lock or if the device is running in developer mode.
    */
    DeviceSecurity = 2,

    /**
    * Detect when the device operating system or security patches do not meet recommended standards.
    *
    * Detect when the device operating system version or security patches met the recommended security requirements. Devices
* running old versions of software pose a security risk. Detect whether the device model and/or manufacturer being used is listed
* as a prohibited device. For example, there might be a known security vulnerability in the Android software which was customized 
* by a specific manufacturer. 
    */
    DeviceSoftware = 3,

    /**
    * Detect when network or browsing requests are made to malicious links.
    *
    * Detect when network or browsing requests are made to malicious links. Checks are performed use machine-learning capabilities and 
* accumulated knowledge from threat intelligence feeds to provide an assessment of the safety of the URL. Use GD.SafeUrl::checkUrl to 
* check specific URLs or IPs.
*
* Requires Mobile Threat Defense (MTD) to be enabled. 
    */
    SafeBrowsing = 4,

    /**
    * Detect when messages contain malicious content or links.
    *
    * ContentChecker.checkMessage interface detects when messages contain unsafe links. For example links to malicious websites, 
* phishing attempts, malware, adware, and other web sources that pose a threat. 
* 
* Requires BlackBerry Mobile Threat Defense (MTD) to be enabled.
    */
    SafeMessaging = 5,

    /**
    * Determine a user’s security risk level based on their real-world context.
    *
    * Determine a user’s security risk level based on their real-world context. Utilizes events and location data and scores these 
* against geozones set by an administrator. 
*
* Requires BlackBerry Persona to be enabled.
    */
    GeoZone = 6,

    /**
    * Determine whether current application activity matches the behavior and identity of the authorized user.
    *
    * Determine a user’s security risk level based on behavior and usage analysis. Requires BlackBerry 
Persona to be enabled.
    */
    Identity = 7,
    
    /**
    * Detect when the application's integrity is at risk or the app requires updating.
    *
    * Detect when the application binary fails integrity or attestation checks. Indicate if the application is out of date and needs
* upgrading.
    */
    ApplicationSecurity = 8,

    
    /**
    * Detect when applications from an untrusted developer are permitted to be installed on an iOS device.
    *
    * Detect when an end user has permitted applications from an untrusted developer to be installed on an iOS devices. 
* To launch a sideloaded application a user must first indicate they trust the certificate associated with the 
* application developer. If a developer has been trusted this threat will be detected, as apps not from an official 
* app store pose a security risk. 
*
* Requires BlackBerry "Mobile Threat Defense" to be enabled.
    */
    UntrustedDeveloper = 9,

    /**
    * Detect when networking is subject to man in the middle attack.
    *
    * Detect when the attached network is subject to a man in the middle attack and a rogue actor is attempting to compromise the connection.
    */
    NetworkSecurity = 10,
    
    /**
    * Detect if attached WiFi network is insecure.
    *
    * Detect if the attached Wi-Fi network is using a protocol whose encryption and authentication are not considered secure.
    */
    WiFiSecurity = 11,

    /**
    * Detect when the device has been offline for an extended period of time.
    *
    * Detect when the device has been offline for an extended period of time. This poses a risk due to the runtime 
* library being unable to obtain new threat rules and models from BlackBerry. 
*
* Requires BlackBerry Spark AppSecure SDK.
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
