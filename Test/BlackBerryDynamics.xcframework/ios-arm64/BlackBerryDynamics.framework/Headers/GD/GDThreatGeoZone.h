/*
 * (c) 2020 BlackBerry Limited. All rights reserved.
 */

#import "GDThreat.h"
#import "GDPortability.h"

NS_ASSUME_NONNULL_BEGIN

/**
 * Determine a user’s security risk level based on their real-world context.
 *
 * Utilizes events and location data and scores these against geozones set by an administrator. Requires BlackBerry Persona 
 * to be enabled and configured.
 */
@interface BBDThreatGeoZone : BBDThreat

/**
 * Return the name of the users current GeoZone.  
 *
 * Return the name defined by the administrator of the BlackBerry Persona GeoZone within which the user is currently located.
 *
 * @return <tt>NSString</tt> Name of the BlackBerry Persona GeoZone or null.
 */
@property (nonatomic, readonly, nullable, strong) NSString *geoZoneName;

/**
 * Determine defined geozone risk level value.
 *
 * @return BBDThreatLevel
 */
@property (nonatomic, assign, readonly) BBDThreatLevel definedGeozoneRisk;

/**
 * Determine learned geozone risk level value.
 *
 * @return BBDThreatLevel
 */
@property (nonatomic, assign, readonly) BBDThreatLevel learnedGeozoneRisk;

/**
 * Creates an instance of BBDThreatGeoZone.
 */
- (instancetype)init NS_DESIGNATED_INITIALIZER;

@end

NS_ASSUME_NONNULL_END
