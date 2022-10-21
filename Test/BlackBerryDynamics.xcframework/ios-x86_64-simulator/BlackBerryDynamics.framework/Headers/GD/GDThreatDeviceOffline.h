/*
* (c) 2020 BlackBerry Limited. All rights reserved.
*
*/

#import <Foundation/Foundation.h>
#import "GDThreat.h"

NS_ASSUME_NONNULL_BEGIN

/**
 * Provide details of threats related to the device. A range of checks are performed to determine the security health of the users device. 
 * For example, if the user has jailbroken their device or if the iOS device integrity checks have failed.
 */
@interface BBDThreatDeviceOffline : BBDThreat

/**
 * Creates an instance of BBDThreatDeviceOffline.
 */
- (instancetype)init NS_DESIGNATED_INITIALIZER;

@end

NS_ASSUME_NONNULL_END
