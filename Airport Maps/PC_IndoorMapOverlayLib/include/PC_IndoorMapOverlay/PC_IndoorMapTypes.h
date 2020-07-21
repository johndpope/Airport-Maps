//
//  PC_IndoorMapTypes.h
//  PC_IndoorMapOverlay
//
//  Copyright © 2017 Point Consulting. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <MapKit/MapKit.h>

@class PC_IndoorMapView, PC_IndoorMapFeature;


typedef NS_ENUM(NSInteger, PC_DataFormat) {
    PC_DataFormatUnknown,
    PC_DataFormatAVF,
    PC_DataFormatIMDF,
};

typedef NS_ENUM(NSInteger, PC_IndoorMapErrorCode) {
    /// Generic error
    PC_IndoorMapErrorCodeGeneric = 0,
    
    /// Unable to calculate the route: no user location is currently available
    PC_IndoorMapErrorCodeNoUserLocation = 1,
    
    /// Unable to calculate the route: no requested navigation data exists for given navigation index
    PC_IndoorMapErrorCodeBadNavigationIndex = 2,
};

@interface NSError(PC_IndoorMapLibrary)

@property (class, nonatomic, nonnull, readonly) NSString * pc_indoorMapErrorDomain;
+ (nonnull instancetype)pc_indoorMapErrorWithCode:(PC_IndoorMapErrorCode)errorCode description:(nullable NSString *)description;

@end

/// Dash pattern for the line drawing.
/// @see `PC_IndoorMapRenderer`
@interface PC_IndoorMapLineDash: NSObject

/// Singleton for solid line.
+ (nonnull instancetype)solid;

/// Creates and returns an `PC_IndoorMapLineDash` object with given dash pattern.
/// See `MKOverlayPathRenderer.lineDashPattern` for details of pattern creation
+ (nonnull instancetype)dashWithPattern:(nonnull NSArray<NSNumber *> *)pattern;

@end

/** This class is responsible for map objects rendering (drawing) */
@interface PC_IndoorMapRenderer: NSObject

/// Creates and returns a `PC_IndoorMapRenderer` object to draw solid line of given color and width
+ (nonnull instancetype)strokeRendererWithColor:(nullable UIColor *)color width:(CGFloat)width;

/// Line stroke color. Default is `nil`
@property(nonatomic, strong, nullable) UIColor * strokeColor;

/// Line width. Default is `1.0`
@property(nonatomic) CGFloat strokeWidth;

/// Line dash. Default is `PC_IndoorMapLineDash.solid`
@property(nonatomic, strong, nonnull) PC_IndoorMapLineDash * strokeDash;

/// Fill color. Default is `nil`
@property(nonatomic, strong, nullable) UIColor * fillColor;

@property(nonatomic, readonly) BOOL isDrawable;

@end

#pragma mark -

/// Standard map layer types
typedef NS_ENUM(NSInteger, PC_IndoorMapLayerType) {
    PC_IndoorMapLayerTypeOther,
    PC_IndoorMapLayerTypeLevels, // AVF: Levels, IMDF: Level
    PC_IndoorMapLayerTypePoints, // AVF: Points, IMDF: Amenity
    PC_IndoorMapLayerTypeUnits, // AVF: Units, IMDF: Unit
    PC_IndoorMapLayerTypeOpenings, // AVF: Openings, IMDF: Opening
    PC_IndoorMapLayerTypeOccupants, // AVF: Occupants, IMDF: Occupant
    PC_IndoorMapLayerTypeBuildings, // AVF: Buildings, IMDF: Building
    PC_IndoorMapLayerTypeFixtures, // AVF: Fixtures, IMDF: Fixture
    PC_IndoorMapLayerTypeZones, // AVF: Zones
    PC_IndoorMapLayerTypeVenue, // AVF: Venue, IMDF: Venue
    PC_IndoorMapLayerTypeAnchors, // AVF: Anchors, IMDF: Anchor
    PC_IndoorMapLayerTypeBuildingMesh, // AVF: BuildingMesh
    PC_IndoorMapLayerTypeDetails, // AVF: Details, IMDF: Detail
    PC_IndoorMapLayerTypeSections, // AVF: Sections, IMDF: Section
    PC_IndoorMapLayerTypeAddresses, // IMDF: Address
    PC_IndoorMapLayerTypeFootprints, // IMDF: Footprint
    PC_IndoorMapLayerTypeKiosks, // IMDF: Kiosk
    PC_IndoorMapLayerTypeRelashionships // IMDF: Relashionship
};

/// Map layer, as defined by the name of a file in the venue directory
@interface PC_IndoorMapLayer: NSObject

/// Layer name. Actually, the name of data file (without extension)
@property(nonatomic, readonly, nonnull) NSString * name;

/// Standard map layer type
@property(nonatomic, readonly) PC_IndoorMapLayerType layerType;

@end

#pragma mark -

typedef NS_ENUM(NSInteger, PC_IndoorMapCategoryType) {
    PC_IndoorMapCategoryTypeOther,
};

/// Feature category. An encapsulation of feature's "CATEGORY" property value.
@interface PC_IndoorMapCategory: NSObject

/// Raw name of the category, the same as was specified in the feature's "CATEGORY" property value.
@property(nonatomic, readonly, nonnull) NSString * name;
@property(nonatomic, readonly) PC_IndoorMapCategoryType categoryType;
@property(nonatomic, strong, nullable) id userInfo;

@end

#pragma mark - 

@interface PC_IndoorRotatableView: UIView

@property(nonatomic) BOOL isRotatable;
- (void)updateWithMatrix:(CGAffineTransform const * _Nullable)matrixInv;

@end

#pragma mark - 

//
// The class is only used in **non-overlay** mode and plays the same role as `MKUserTrackingBarButtonItem` does in **overlay** mode.
// A `PC_IndoorUserTrackingBarButtonItem` object is a specialized bar button item that allows the user to toggle through the
// user tracking modes. For example, when the user taps the button, the map view toggles between tracking the user with
// and without heading. The button also reflects the current user tracking mode if set elsewhere.
// This bar button item is associated to a single map view.

@interface PC_IndoorUserTrackingBarButtonItem : UIBarButtonItem

@property(nonatomic, strong, nullable) PC_IndoorMapView * mapView;
@property(nonatomic) MKUserTrackingMode userTrackingMode;

// Initializes a newly created bar button item with the specified map view and images for different `MKUserTrackingMode` modes.
//
// @param mapView  The map view used by this bar button item.
// @param imageNone Image used for `MKUserTrackingModeNone` mode.
// @param imageFollow Image used for `MKUserTrackingModeFollow` mode.
// @param imageFollowWithHeading Image used for `MKUserTrackingModeFollowWithHeading` mode.
-(nonnull instancetype)initWithMapView:(nonnull PC_IndoorMapView *)mapView
                             imageNone:(nonnull UIImage *)imageNone
                           imageFollow:(nonnull UIImage *)imageFollow
                imageFollowWithHeading:(nonnull UIImage *)imageFollowWithHeading;

@end

/**
  3-dimensional location.
*/
@interface PC_IndoorMapLocation: NSObject

- (nonnull instancetype)initWithMapPoint:(MKMapPoint)mapPoint mapItem:(nonnull MKMapItem *)mapItem;
- (nonnull instancetype)initWithMapPoint:(MKMapPoint)mapPoint ordinalValue:(NSInteger)ordinalValue;

/// 2-dimensional position.
@property (nonatomic, readonly) MKMapPoint mapPoint;
@property (nonatomic, readonly) CLLocationCoordinate2D coordinate;

/// Level ordinal value.
@property (nonatomic) NSInteger ordinalValue;

// An unique feature index. Will be removed soon. Do not use
@property (nonatomic) NSUInteger featureIndex;

/// The feature object associated with given location.
@property(nonatomic, weak, readonly, nullable) PC_IndoorMapFeature * feature;

/// A map item corresponding to the location.
@property (nonatomic, strong, nullable) MKMapItem * mapItem;

/// Hardcoded title of the location.
@property (nonatomic, strong, nullable) NSString * title;

/// Hardcoded subtitle of the location.
@property (nonatomic, strong, nullable) NSString * subtitle;

/// Distance to other location in meters
- (CLLocationDistance)distanceToLocation:(nonnull PC_IndoorMapLocation *)otherLocation;

@end

