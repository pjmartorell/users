/*
 * (c) 2017 BlackBerry Limited. All rights reserved.
 *
 */

#pragma once

#import <Foundation/Foundation.h>

/** BlackBerry Dynamics infrastructure connection management.
 * 
 * \copydetails ssGDConnectionManagement
 */
@interface GDConnectivityManager : NSObject

/** Reset the BlackBerry Dynamics infrastructure connection.
 * 
 * \copydetails ssGDConnectionManagementForceResetAllConnections
 */
+ (BOOL)forceResetAllConnections;

@end
