/*
 * (c) 2020 BlackBerry Limited. All rights reserved.
 */

#import <Foundation/Foundation.h>
#import "GDThreat.h"
#import "GDPortability.h"

NS_ASSUME_NONNULL_BEGIN

/**
 * The enumeration for the type of network in which the mitm attack was detected
 */
typedef NS_ENUM(NSInteger, BBDNetworkType)
{
    None,
    Mobile,
    Wifi,
    Bluetooth,
    Ethernet,
    VPN
};

/**
 * Determine whether networking is subject to man in the middle attack.
 */
@interface BBDThreatNetworkSecurity : BBDThreat

/**
 * Creates an instance of BBDThreatNetworkSecurity.
 */
- (instancetype)init NS_DESIGNATED_INITIALIZER;

/**
 * Indicate the type of mitm threat.
 *
 * Indicate the specific type of mitm threat.
 *
 * @return BBDNetworkType.
 */
- (BBDNetworkType)getNetworkType;

@end

NS_ASSUME_NONNULL_END
