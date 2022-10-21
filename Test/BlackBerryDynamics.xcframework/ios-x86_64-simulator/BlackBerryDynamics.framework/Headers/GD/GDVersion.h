/*
 * (c) 2017 BlackBerry Limited. All rights reserved.
 *
 */

#pragma once

#import <Foundation/Foundation.h>

#import "GDPortability.h"

NS_ASSUME_NONNULL_BEGIN

/** BlackBerry Dynamics entitlement version.
 * 
 * \copydetails ssGDRunTimeGDVersion
 */
@interface GDVersion : NSObject

/** Initialize from a dotted string representation.
 * 
 * @return <tt>GDVersion</tt> object with constituent version numbers read from
 *         a dotted string representation.
 */
- (nullable instancetype)initWithString:(NSString*)versionString;

/** Initialize from an array of <tt>NSNumber</tt> objects.
 * 
 * @return <tt>GDVersion</tt> object with constituent version numbers
 *         initialized from an array of <tt>NSNumber</tt> objects.
 */
- (nullable instancetype)initWithArray:(NSArray*)array;

/** Count of how many constituent numbers are in the version.
 * 
 * @return <tt>NSUInteger</tt> representation of the count of how many
 *         constituent numbers there are in the version.
 */
- (NSUInteger)numberOfVersionParts;

/** Get one constituent version number.
 * 
 * Call this \ss_function to get one of the constituent numbers in the version,
 * specified by a numeric position. Position zero is the major version number,
 * which is the most significant.
 *
 * @return The constituent version number at the specified position.
 */
- (NSUInteger)versionPartAt:(NSUInteger)position;

/** Compare this version with another version.
 * 
 * @return <tt>NSComparisonResult</tt> representing the relative value of this
 *         version compared to the other version.
 */
- (NSComparisonResult)compare:(GDVersion*)anotherVersion;

/** Check for equality with another version.
 * 
 * @return \ss_true if the two versions are the same.
 * @return \ss_false Otherwise.
 */
- (BOOL)isEqualToVersion:(nullable GDVersion*)anotherVersion;

/** Check whether this version is more than another version.
 * 
 * @return \ss_true if this version is more than the specified version.
 * @return \ss_false Otherwise.
 */
- (BOOL)isGreaterThanVersion:(nullable GDVersion*)anotherVersion;

/** Check whether this version is less than another version.
 * 
 * @return \ss_true if this version is less than the specified version.
 * @return \ss_false Otherwise.
 */
- (BOOL)isLessThanVersion:(nullable GDVersion*)anotherVersion;

/** Dotted string representation.
 * 
 * @return Dotted string representation of this version.
 */
@property(nonatomic, readonly) NSString *stringValue;
@end

NS_ASSUME_NONNULL_END
