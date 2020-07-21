//
//  PC_IndoorMapOrdinal.h
//  PC_IndoorMapOverlay
//
//  Copyright © 2017 Point Consulting. All rights reserved.
//

#import "PC_IndoorMapFeature.h"

/**
  The map's ordinal representation.
  Use fast enumeration (as it is defined by `NSFastEnumeration`) to enumerate all features for given ordinal.
  For Swift use `enumerateFeaturesUsingBlock`
*/
@interface PC_IndoorMapOrdinal : NSObject<NSFastEnumeration>

/**
  Enumerate all zones object for given ordinal. Effectively, the zone object is just a feature loaded from **Zones.geojson** file
*/
- (void)enumerateZonesUsingBlock:(void (NS_NOESCAPE ^ _Nonnull)(PC_IndoorMapFeature * _Nonnull zoneFeature, NSUInteger index, BOOL * _Nonnull stop))block;

/**
  Enumerate ordinal's features
*/
- (void)enumerateFeaturesUsingBlock:(void (NS_NOESCAPE ^ _Nonnull)(PC_IndoorMapFeature * _Nonnull feature, NSUInteger index, BOOL * _Nonnull stop))block;

/// The ordinal's integer value
@property(nonatomic, readonly) NSInteger integerValue;

/// All levels for given ordinal
@property(nonatomic, readonly, nonnull) NSArray<PC_IndoorMapLevel *> * levels;

/// Looks through `levels` and returns first non-empty level name (`PC_IndoorMapLevel.name` property value)
@property(nonatomic, readonly, nullable) NSString * name;

/// Looks through `levels` and returns first non-empty level short name (`PC_IndoorMapLevel.shortName` property value)
@property(nonatomic, readonly, nullable) NSString * shortName;

/// `name` or `shortName` (if `name` is empty) or `nil` (if both `name` and `shortName` are empty
@property(nonatomic, readonly, nullable) NSString * nameOrShortName;

/// `shortName` or `name` (if `name` is empty) or `nil` (if both `name` and `shortName` are empty
@property(nonatomic, readonly, nullable) NSString * shortNameOrName;

@end


