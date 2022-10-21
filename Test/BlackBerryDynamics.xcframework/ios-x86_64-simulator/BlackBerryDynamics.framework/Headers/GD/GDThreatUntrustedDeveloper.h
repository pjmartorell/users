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
* \copydetails ssThreatStatusUntrustedDeveloper
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
