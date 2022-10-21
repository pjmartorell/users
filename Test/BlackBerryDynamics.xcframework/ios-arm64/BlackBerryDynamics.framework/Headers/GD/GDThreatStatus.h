/*
* (c) 2019 BlackBerry Limited. All rights reserved.
*
*/

#pragma once

#import <Foundation/Foundation.h>
#import "GDThreat.h"

NS_ASSUME_NONNULL_BEGIN

/** Notification name for BlackBerry Dynamics threat status changes.
 *
 * Use this value to add an <tt>NSNotificationCenter</tt> observer to detect threat status changes.
 */
extern NSString * const BBDThreatStatusNotification;

/**
 * Class providing details of security threats related to the device, application, network, and user.
 */
@interface BBDThreatStatus : NSObject


/** Get the overall level of risk.
 *
 * Return the overall level of risk combining all threat types being evaluated. For example, if any detected
 * threat poses a HIGH risk then the overall threat level will also be deemed to be HIGH.
 *
 * @return BBDThreatLevel specifying the overall threat level.
 */
- (BBDThreatLevel)getOverallThreatLevel;

/**
 * Return the threat information for a specific type of threat.
 *
 * Return details for specific threat type including the risk level, evaluation time and status
 *
 * @param ruleType ThreatType to be retrieved. 
 *
 * @return BBDThreat object for the requested ThreatType.
 * @return <tt>nil</tt> if ThreatType is invalid.
 */
- (nullable BBDThreat *)getThreat:(BBDThreatType)ruleType;

/**
 * Return status of all threats evaluated.
 * 
 * Return the threat information of all types of threats that are evaluated by the runtime. 
 *
 * @return NSArray of BBDThreat for all available types.
 */
- (NSArray<BBDThreat *> *)getThreat;

@end

NS_ASSUME_NONNULL_END

