/*
 * (c) 2020 BlackBerry Limited. All rights reserved.
 */

#import "GDThreat.h"
#import "GDPortability.h"

NS_ASSUME_NONNULL_BEGIN

/**  
 * Determine whether current application activity matches the behavior and identity of the authorized user.
 * 
 * Requires BlackBerry Persona to be enabled.
 *
 */
@interface BBDThreatIdentity : BBDThreat

/**
 * Determine a user’s security risk level based on behavior and usage analysis.
 * 
 * Determine a user’s security risk level based on behavior and usage analysis.
 *
 * @return BBDThreatLevel 
 */
@property (nonatomic, assign, readonly) BBDThreatLevel behaviouralLocationRisk;

/**
 * Determine a user’s security risk level based on ip address analysis.
 *
 * @return BBDThreatLevel
 */
@property (nonatomic, assign, readonly) BBDThreatLevel egressIPRisk;

/**
 * Determine a user’s security risk level based on app anomal detection.
 *
 * @return BBDThreatLevel
 */
@property (nonatomic, assign, readonly) BBDThreatLevel continuousAuthenticationRisk;

/**
 * Determine a user’s security risk level based on network anomlay detection.
 *
 * @return BBDThreatLevel
 */
@property (nonatomic, assign, readonly) BBDThreatLevel networkAnomalyRisk;

/**
 * Creates an instance of BBDThreatIdentity.
 */
- (instancetype)init NS_DESIGNATED_INITIALIZER;

@end

NS_ASSUME_NONNULL_END
