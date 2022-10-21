/*
* (c) 2020 BlackBerry Limited. All rights reserved.
*
*/

#import <Foundation/Foundation.h>
#import "GDPortability.h"
#import "GDThreat.h"

NS_ASSUME_NONNULL_BEGIN

/**
 * Provide threat details related to the application's integrity.
 * 
 * Detect if the application binary fails integrity or attestation checks. Indicate if the application is out of date and needs
 * upgrading.
 */
@interface BBDThreatApplicationSecurity : BBDThreat

/**
 * Creates an instance of BBDThreatApplicationSecurity.
 */
- (instancetype)init NS_DESIGNATED_INITIALIZER;

/**
* Determine when the application binary has failed integrity or attestation checks.
*
* Determine when the application binary has failed integrity or attestation checks. 
*/
- (BOOL)isAppAttestationFailed;

/**
* Return the risk posed by a failed integrity or attestation check.
*
* Return the risk posed by a failed integrity or attestation check.
*/
- (BBDThreatLevel) getAppAttestationRisk;

/**
* Determine whether the application is out of date.
*
* Determine whether the application is out of date and it is necessary for the user to update to the 
* latest version. 
*
* A developer may configure the minimum recommended version and update URL within their application policy.
*
*/
- (BOOL)isAppVersionOutOfDate;

/**
* Return the url for the end user to download the latest version of the application.
*
* Return the url where the latest version of the application may be downloaded. This URL is defined by
* the application developer within the application policy. 
* 
*/
- (NSString *)getAppUpdateURL;

@end

NS_ASSUME_NONNULL_END
