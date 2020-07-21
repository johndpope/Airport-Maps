//
//  PC_IndoorMapFeature.h
//  PC_IndoorMapOverlay
//
//  Copyright © 2017-2018 Point Consulting. All rights reserved.
//

#import <MapKit/MapKit.h>
#import "PC_IndoorMapTypes.h"

@class PC_IndoorMapLevel, PC_IndoorMapLocation;

/**
   The default order (z-index) values for `PC_IndoorMapFeature` object.
*/
typedef NS_ENUM(NSInteger, PC_IndoorMapZIndex) {
    PC_IndoorMapZIndexFootprints = -6000,
    PC_IndoorMapZIndexVenue      = -5000,
    PC_IndoorMapZIndexLevels     = -4000,
    PC_IndoorMapZIndexUnits      = -3000,
    PC_IndoorMapZIndexFixtures   = -2000,
    PC_IndoorMapZIndexKiosks     = -1900,
    PC_IndoorMapZIndexNames      = -1000,
    PC_IndoorMapZIndexDefault    = 0,
    PC_IndoorMapZIndexZones      = 1000,
    PC_IndoorMapZIndexBuildings  = 2000,
    PC_IndoorMapZIndexSections   = 3000,
    PC_IndoorMapZIndexPoints     = 4000,
    PC_IndoorMapZIndexOpenings   = 5000,
    PC_IndoorMapZIndexOccupants  = 6000,
};

/**
    Feature `PC_IndoorMapFeature` geometry type
*/
typedef NS_ENUM(NSInteger, PC_IndoorMapGeometryType) {
    
    /// Unknown or absent geometry data
    PC_IndoorMapGeometryTypeOther,
    
    /// The feature is a point
    PC_IndoorMapGeometryTypePoint,
    
    /// The feature is a polygon
    PC_IndoorMapGeometryTypePolygon,
    
    /// The feature is a set of polygons
    PC_IndoorMapGeometryTypeMultiPolygon,
    
    /// The feature is a line string
    PC_IndoorMapGeometryTypeLineString,
    
    /// The feature is a set of line strings
    PC_IndoorMapGeometryTypeMultiLineString
};

#pragma mark -

/**
   Class that represents a **geojson** feature object.
*/
@interface PC_IndoorMapFeature: NSObject

/// All features properties, as they was represented in the **geojson** file
@property(nonatomic, nullable, readonly) NSDictionary * properties;

/** 
  Returns the value for the given key stored in the feature properties
  
  @param key The key for which to return the corresponding value.
  @return The value associated with `key` or `nil` if no value is stored for this `key`.
*/
- (nullable id)propertyForKey:(nonnull NSString *)key;

/**
 Returns the string for the given key stored in the feature properties
 
 @param key The key for which to return the corresponding value.
 @return The string value associated with `key` or `nil` if no value is stored for this `key`
         or the stored value could not be casted to a string.
*/
- (nullable NSString *)stringForKey:(nonnull NSString *)key;

/**
 Returns the integer for the given key stored in the feature properties
 
 @param key The key for which to return the corresponding value.
 @return The integer value associated with `key` or `nil` if no value is stored for this `key`
 or the stored value could not be casted to an integer.
*/
- (NSInteger)integerForKey:(nonnull NSString *)key defaultValue:(NSInteger)defaultValue;

/**
 Returns the dictionary for the given key stored in the feature properties
 
 @param key The key for which to return the corresponding value.
 @return The dictionary value associated with `key` or `nil` if no value is stored for this `key`
 or the stored value could not be represented as a dictionary.
*/
- (nullable NSDictionary *)dictionaryForKey:(nonnull NSString *)key;

/**
 Returns the array for the given key stored in the feature properties
 
 @param key The key for which to return the corresponding value.
 @return The array value associated with `key` or `nil` if no value is stored for this `key`
 or the stored value could not be represented as an array.
 */
- (nullable NSArray *)arrayForKey:(nonnull NSString *)key;

/// Feature's level object as it is referenced by feature's **LEVEL_ID** property value
@property(nonatomic, weak, nullable, readonly) PC_IndoorMapLevel * level;

/// Feature's layer object, i.e. the **geojson** file representation where the feature was loaded from
@property(nonatomic, strong, nonnull, readonly) PC_IndoorMapLayer * layer;

/// Feature's idendifier as it is referenced by feature's **id** property value.
/// Defined for IMDF data format currently
@property(nonatomic, readonly, nullable) NSString * identifier;

/// Feature's category object as it is referenced by feature's **CATEGORY** property value
/// or `nil` if no **CATEGORY** string is stored in the feature properties
/// @see `PC_IndoorMapFeature.categoryName`
@property(nonatomic, strong, nullable) PC_IndoorMapCategory * category;

/// Feature's category name as it is referenced by feature's **CATEGORY** property value
/// or `nil` if no **CATEGORY** string is stored in the feature properties
@property(nonatomic, readonly, nullable) NSString * categoryName;

/// Feature's location. A single location that represents feature geometric center or `nil` the feature has no suitable geometry.
@property(nonatomic, nullable, readonly) PC_IndoorMapLocation * location;

/// Feature's localized short name as it is referenced by feature's **SHORT_NAME** property value
/// or `nil` if no **SHORT_NAME** string is stored in the feature properties
@property(nonatomic, readonly, nullable) NSString * shortName;

/// Feature's localized name as it is referenced by feature's **NAME** property value
/// or `nil` if no **NAME** string is stored in the feature properties.
@property(nonatomic, readonly, nullable) NSString * name;

/// First non-empty (not `nil` and not `""`) localized string from **NAME**, **SHORT_NAME** value list, in this order, or `nil` if nothing non-empty found
@property(nonatomic, readonly, nullable) NSString * nameOrShortName;

/// First non-empty (not `nil` and not `""`) localized string from **SHORT_NAME**, **NAME** value list, in this order, or `nil` if nothing non-empty found
@property(nonatomic, readonly, nullable) NSString * shortNameOrName;

/// Feature's title. This value entirely for application usage
@property(nonatomic, strong, nullable) NSString * title;

/// Feature's title. This value entirely for application usage
@property(nonatomic, strong, nullable) NSString * subtitle;


/// Feature's building identifier as it is referenced by feature's **BLDG_ID** property value
/// or `nil` if no **BLDG_ID** string is stored in the feature properties.
@property(nonatomic, readonly, nullable) NSString * buildingIdentifier;

/// User info. Any context that could be associated with the feature by application
@property(nonatomic, strong, nullable) id userInfo;

/// Global feature index, the value is assigned to each feature object from global counter upon creation.
/// Value is unique to each feature object during application runtime.
/// Must not be used as an unique feature identifier to reference features between application launches
@property(nonatomic, readonly) NSInteger globalIndex;

/** 
 The feature's z-index, i.e. the rendering order on the map. Set higher values to order the feature visual representation front
 The `PC_IndoorMapZIndex` raw integer values are used by default.
 
 Please note that z-index changing affect only before the feature in rendered on the map, the best place for it is the
 `-[PC_IndoorMapManager loadVenueFromDirectoryAtPath:navigationIndex:options:onFeatureLoad:completion:]` method's callbacks;
*/
@property(nonatomic) NSInteger zIndex;

/// Checks if the given point belongs to a feature.
/// @return `YES` if the `point` lies inside the feature's geometry object or `NO` otherwise
- (BOOL)containsPoint:(MKMapPoint)point;

/// `YES` is the feature has suitable geometry (i.e. could be represented on the map)
@property(nonatomic, readonly) BOOL isGeometryValid;

/// The feature geometry type
@property(nonatomic, readonly) PC_IndoorMapGeometryType geometryType;

@end

#pragma mark -

/** 
  The map level object. Effectively, this is a feature object loaded from **Levels.geojson** file
 */
@interface PC_IndoorMapLevel: PC_IndoorMapFeature

/// The level's ordinal value as it is referenced by level's **ORDINAL** property value
@property(nonatomic, readonly) NSInteger ordinalValue;

/// The level's identifier as it is referenced by level's **LEVEL_ID** property value (AVF) or **id** (IMDF)
@property(nonatomic, readonly, nonnull) NSString * levelIdentifier;

/// The building feature object. Buildings are loaded from **Buildings.geojson** file and linked to
/// level object by **BLDG_ID** property value
@property(nonatomic, strong, nullable, readonly) PC_IndoorMapFeature * building;

@end

#pragma mark -

/**
 The loaded venue top object. Effectively, this is a feature object loaded from **Venue.geojson** file
 */
@interface PC_IndoorMapVenue: PC_IndoorMapFeature

/// Venue's coordinate as it is referenced by feature's **POI_Coordinate** property value
@property(nonatomic, readonly) CLLocationCoordinate2D poiCoordinate;
@property(nonatomic, readonly) BOOL isPoiCoordinateValid;

/// Venue's point of interest collection dictionary as it is referenced by feature's **POI** property value
/// or `nil` if no **POI** dictionary is stored in the venue properties
@property(nonatomic, readonly, nullable) NSDictionary * poiAttributes;

@end

#pragma mark -

/**
  Feature's map visual representation object. 
  The application may adjust feature appearance in the `-[PC_IndoorMapManagerDelegate indoorMapManager:willDisplayFeatureOverlay:]`
*/
@interface PC_IndoorMapFeatureOverlay: NSObject

/// The rendered feature object
@property(nonatomic, readonly, nonnull) PC_IndoorMapFeature * feature;

/// The feature renderer. Assign `nil` to hide the feature from the map
@property(nonatomic, strong, nullable) PC_IndoorMapRenderer * renderer;


/// Minimal map zoom level on which the overlay remains visible.
@property(nonatomic) CGFloat minZoomLevel;

/// Maximal map zoom level on which the overlay remains visible.
@property(nonatomic) CGFloat maxZoomLevel;

@end


