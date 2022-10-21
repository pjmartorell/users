/*
* (c) 2019 BlackBerry Limited. All rights reserved.
*
*/

#import <Foundation/Foundation.h>
#import "GDPortability.h"
#import "GDThreatStatus.h"
#import "GDThreat.h"

NS_ASSUME_NONNULL_BEGIN

/** 
* 
* Detect when an end user has permitted applications from an untrusted developer to be installed on an iOS devices. 
* To launch a sideloaded application a user must first indicate they trust the certificate associated with the 
* application developer. If a developer has been trusted this threat will be detected, as apps not from an official 
* app store pose a security risk. 
*
* Requires BlackBerry "Mobile Threat Defense" to be enabled.
*/
@interface BBDThreatUntrustedDeveloper : BBDThreat

/**
 * Creates an instance of BBDThreatUntrustedDeveloper
 */
- (instancetype)init NS_DESIGNATED_INITIALIZER;

/** Gets the number of untrusted developer certificates detected on the device.
*/
- (unsigned int)getUntrustedDevelopersDetected;

/** Gets the list of untrusted developers based on the names of the certificates detected on the device.
*/
- (NSArray *)getUntrustedDevelopers;

@end

NS_ASSUME_NONNULL_END
