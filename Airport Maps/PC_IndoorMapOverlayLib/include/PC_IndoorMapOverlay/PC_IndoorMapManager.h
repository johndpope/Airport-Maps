#import <Foundation/Foundation.h>
#import <MapKit/MapKit.h>
#import "PC_IndoorMapTypes.h"
#import "PC_IndoorMapFeature.h"
#import "PC_IndoorMapBackground.h"
#import "PC_IndoorMapAnnotation.h"
#import "PC_IndoorMapOrdinal.h"
#import "PC_IndoorMapRouteTypes.h"
#import "PC_IndoorMapLocationProvider.h"
#import "PC_IndoorMapViewProtocol.h"

@class PC_IndoorMapManager;

/**
  Invalid level marker.
 
      NSInteger const kPC_IndoorMapInvalidOrdinalValue = -100000;
 
  This constant can be used in `-[PC_IndoorMapManager setOrdinalValue:]` method to unload current indoor level.
*/
extern NSInteger const kPC_IndoorMapInvalidOrdinalValue;

/**
  Minimal render priority to ignore intersection tests

      NSInteger const kPC_IndoorMapIgnoreIntersectionsZIndex = 100000;

  Minimal render priority for annotation pins which do not participate in intersection tests
  against indoor map icons, labels and other marker pins. This constant can be used in `PC_IndoorMapAnnotation.priority`.
*/
extern NSInteger const kPC_IndoorMapIgnoreIntersectionsZIndex;

//typedef NS_OPTIONS(NSUInteger, PC_IndoorMapInvalidateOption) {
//    PC_IndoorMapInvalidateOptionOverlays = 1 << 0
//};

/// The venue loading options. No concrete loaded options are defined currently
typedef NS_OPTIONS(NSUInteger, PC_IndoorMapLoadingOption) {
    PC_IndoorMapLoadingOptionNone = 0
};

//--------------------------------------------------------------------------------------------
// PC_IndoorMapManagerDelegate
//--------------------------------------------------------------------------------------------

/**
 The delegate of a `PC_IndoorMapManager` object must adopt this protocol to provide the indoor map
 manager with visual appearance parameters and to be notified about events in the map.
 All methods are optional.
 
*/
@protocol PC_IndoorMapManagerDelegate<NSObject>

@optional

/**
   Asks the delegate if the manager should allow selection of the specified feature.
 
   @param manager The indoor map manager
   @param feature The feature
   @return `YES` to permit selection of the feature, `NO` to deny selection.
*/
- (BOOL)indoorMapManager:(nonnull PC_IndoorMapManager *)manager shouldSelectFeature:(nonnull PC_IndoorMapFeature *)feature;

/**
 To display's feature annotation the delegate creates one of more concrete descendants of `PC_IndoorMapAnnotation` class
 for given feature.
 
 The following annotation classes are currently defined in the library:
 
 - `PC_IndoorMapIconAnnotation` - Map icon object
 - `PC_IndoorMapTextAnnotation` - Map text label object
 
 @param manager The indoor map manager
 @param feature The feature
 @return An array of `PC_IndoorMapAnnotation` objects or `nil` if no annotation objects is needed for given feature.
*/
- (nullable NSArray<PC_IndoorMapAnnotation *> *)indoorMapManager:(nonnull PC_IndoorMapManager *)manager
                                       makeAnnotationsForFeature:(nonnull PC_IndoorMapFeature *)feature;

/**
 Manager calls this delegate method to adjust rendering options for a feature just before it is rendered on the map view
 
 @param manager The indoor map manager
 @param featureOverlay The feature overlay object. Adjust rendering with `featureOverlay.rendering` property
*/
- (void)indoorMapManager:(nonnull PC_IndoorMapManager *)manager willDisplayFeatureOverlay:(nonnull PC_IndoorMapFeatureOverlay *)featureOverlay;


/**
 Manager calls this method to notify delegate that a user performed long tap on map view.
 @param manager The indoor map manager.
 @param location Tap location.
 @param mapViewPoint Tap point in map view's coordinates.
 */
- (void)indoorMapManager:(nonnull PC_IndoorMapManager *)manager didPerformLongPressOnLocation:(nonnull PC_IndoorMapLocation *)location
          atMapViewPoint:(CGPoint)mapViewPoint;

/**
 Manager calls this method to notify delegate that a new ordinal has been loaded.
 @param manager The indoor map manager.
*/
- (void)indoorMapManagerDidChangeOrdinal:(nonnull PC_IndoorMapManager *)manager;

/**
 Manager calls this method to determine if a given point inside or outside the venue.
 If it is outside, then `MKDirection` request will be used for navigation. Otherwise, indoor
 navigation service will be used.

 @param manager The indoor map manager.
 @param point Coordinate of the point.
 @param isDestination Is this point a source or a destination.
 @param hint `YES`, if the point is inside venue polygon, `NO` otherwise.
 @return `YES`, if the point must be treated as "inside", `NO` otherwise.
*/
- (BOOL)indoorMapManager:(nonnull PC_IndoorMapManager *)manager isPointInsideVenue:(MKMapPoint)point
           isDestination:(BOOL)isDestination hint:(BOOL)hint;

/**
 Manager calls this method to determine an action required to newly selected annotation.
 The delegate should return a descendant of `PC_IndoorMapAnnotationAction` or `nil` if no action is required.
 Currently the only allowed actions are `PC_IndoorMapShowCalloutAction` and `PC_IndoorMapCustomAction`
 
 Еру method is called multiple times for the same annotation. Consider caching or reusing for any
 heavy/complex objects, views and even actions returned in this method.
 
 @param manager The indoor map manager.
 @param annotation The feature annotation.
 @return `PC_IndoorMapAnnotationAction` object or `nil` if no action is required.
*/
- (nullable PC_IndoorMapAnnotationAction *)indoorMapManager:(nonnull PC_IndoorMapManager *)manager
                                actionForSelectedAnnotation:(nonnull PC_IndoorMapAnnotation *)annotation;

/**
 Manager calls this method to get a turn-by-turn instruction.
 
 @param manager The indoor map manager.
 @param features Array of feature. May be empty.
 @param ordinalValue Destination level(floor) ordinal value.
 @return A turn-by-turn instruction.
*/

- (nonnull NSString *)indoorMapManager:(nonnull PC_IndoorMapManager *)manager
              routeStepInstructionForFeatures:(nonnull NSArray<PC_IndoorMapFeature *> *)features
                                 ordinalValue:(NSInteger)ordinalValue;

- (nonnull NSString *)indoorMapManager:(nonnull PC_IndoorMapManager *)manager
                  routeStepInstructionForDestinationLocation:(nullable PC_IndoorMapLocation *)destinationLocation;

- (void)indoorMapManager:(nonnull PC_IndoorMapManager *)manager willDisplaySegment:(nonnull PC_IndoorMapRouteSegment *)segment
         forDefaultRoute:(nonnull PC_IndoorMapRoute *)defaultRoute;

- (void)indoorMapManager:(nonnull PC_IndoorMapManager *)manager defaultRouteDidCalculateDistance:(CLLocationDistance)distance
                    time:(NSTimeInterval)time
                   steps:(nullable NSArray<PC_IndoorMapStep *> *)steps
     destinationLocation:(nullable PC_IndoorMapLocation *)destinationLocation
    fromLocationServices:(BOOL)fromLocationServices
                   error:(nullable NSError *)error;

@end

//--------------------------------------------------------------------------------------------
// PC_IndoorMapManager
//--------------------------------------------------------------------------------------------

/**
 Indoor map control object. In **overlay** mode, this object communicates with `MKMapView` object,
 and in **non-overlay** mode, this object communicates with `PC_IndoorMapView` object.
*/
@interface PC_IndoorMapManager : NSObject<MKMapViewDelegate, PC_IndoorMapViewDelegate>

@property (class, nonatomic, nonnull, readonly) NSString * versionString;


- (void)setOverlayMapView:(nonnull MKMapView *)mapView;
- (void)setNonOverlayMapView:(nonnull PC_IndoorMapView *)mapView;
- (void)setMapView:(nullable UIView<PC_IndoorMapViewProtocol> *)mapView;

/// A boolean value indicating whether the manager is in **overlay** or in **non-overlay** mode.
@property(nonatomic, readonly) BOOL isOverlayMode;

/// Delegate
@property(weak, nonatomic, nullable) NSObject<PC_IndoorMapManagerDelegate> *delegate;

/// Bounding rectangle for the indoor venue.
@property(nonatomic, readonly) MKMapRect limitRect;

/// Boolean value indicating whether the manager should try to display the user’s location on the map view.
@property(nonatomic) BOOL showsUserLocation;

// Discontinued. Use locationProvider.headingFilter instead
// Heading filter for Core Location updates.
// @property(nonatomic) CLLocationDegrees headingFilter;

/// User (blue dot) location. May be `nil`.
@property(nonatomic, readonly, nullable) PC_IndoorMapLocation * userLocation;


@property(nonatomic) BOOL isClusterizationEnabled;

/// The mode used to track the user location
/// This is a convenient way to achieve the userTrackingMode for attached map view.
/// The property is Key-Value Observing (KVO) compliant
@property(nonatomic) MKUserTrackingMode userTrackingMode;

/**
   Location data provider. By default a `PC_IndoorMapCoreLocationProvider` instance is used.
   Assign `nil` to disable any location data updates (including user location updates)
*/
@property(nonatomic, strong, nullable) PC_IndoorMapLocationProvider * locationProvider;

/**
 Checks if the location is inside the venue.

 A location is considered inside the venue if it's coordinate is inside the venue polygon (the polygon is defined in **Venue.geojson**).
 `PC_IndoorMapManagerDelegate` can override it in `-[PC_IndoorMapManagerDelegate indoorMapManager:isPointInsideVenue:isDestination:hint:]` method.

 @param location Location to check.
 @return `YES` if the location belongs to venue, `NO` otherwise
 */
- (BOOL)isLocationInsideVenue:(nonnull PC_IndoorMapLocation *)location;

- (void)loadVenueFromDirectoryAtPath:(nonnull NSString *)path
                     navigationIndex:(NSUInteger)navigationIndex
                             options:(PC_IndoorMapLoadingOption)options
                       onFeatureLoad:(void (^ _Nullable)(PC_IndoorMapFeature * _Nonnull feature, BOOL * _Nonnull discard, BOOL * _Nonnull stop))block
                          completion:(nullable void (^)(BOOL finished))completion __deprecated_msg("Use `loadVenueFromDirectoryAtPath:options:onFeatureLoad:completion:`");


- (void)loadVenueFromDirectoryAtPath:(nonnull NSString *)path
                             options:(PC_IndoorMapLoadingOption)options
                       onFeatureLoad:(void (^ _Nullable)(PC_IndoorMapFeature * _Nonnull feature, BOOL * _Nonnull discard, BOOL * _Nonnull stop))block
                          completion:(nullable void (^)(BOOL finished))completion;

- (void)invalidateMapObjectsWithFeatures:(nonnull NSArray<PC_IndoorMapFeature *> *)features;

- (void)addUserAnnotation:(nonnull PC_IndoorMapUserAnnotation *)userAnnotation withIdentifier:(nonnull NSString *)identifier needSelect:(BOOL)needSelect;

- (void)beginUserAnnotationUpdates;
- (void)endUserAnnotationUpdates;

- (void)removeUserAnnotationWithIdentifier:(nonnull NSString *)identifier;
- (void)removeAllUserAnnotations;

/// retuerns first available annotation with the given identifier
- (nullable PC_IndoorMapUserAnnotation *)userAnnotationWithIdentifier:(nonnull NSString *)identifier;
- (nonnull NSArray<PC_IndoorMapAnnotation *> *)annotationsForFeature:(nonnull PC_IndoorMapFeature *)feature;
- (void)selectAnnotation:(nullable PC_IndoorMapAnnotation *)annotation;
- (void)markAnnotation:(nonnull PC_IndoorMapAnnotation *)annotation;
- (void)unmarkAnnotation:(nonnull PC_IndoorMapAnnotation *)annotation;
- (BOOL)isAnnotationVisible:(nonnull PC_IndoorMapAnnotation *)annotation inMapViewBounds:(CGRect)mapViewBounds;


/// Current level(floor) ordinal value.
@property(nonatomic) NSInteger ordinalValue;

/// Current level(floor) ordinal.
@property(nonatomic, readonly, nullable) PC_IndoorMapOrdinal * ordinal;

/// Sorted list of venue level (floor) ordinals.
@property(nonatomic, readonly, nullable) NSArray<PC_IndoorMapOrdinal *> * ordinals;

- (nullable PC_IndoorMapOrdinal *)ordinalForValue:(NSInteger)value;

/**
  This method enumerates features around the given location. For each feature, a callback `block` is called.
  @param location Location to enumerate features around.
  @param block callback block which is called for each feature.
*/
- (void)enumerateFeaturesAroundLocation:(nullable PC_IndoorMapLocation *)location
                             usingBlock:(void (NS_NOESCAPE ^ _Nullable)(PC_IndoorMapFeature * _Nonnull feature, BOOL * _Nonnull stop))block;


/**
  This method enumerates features which contain the given location. For each found feature, a callback `block` is called.
 
  The `location.ordinalValue` value is taken in account, so only given ordinal features is enumerated. For global (whole map) search use
  `kPC_IndoorMapInvalidOrdinalValue` for the `location.ordinalValue`, for example:
 
 
      MKMapPoint point = ...
      PC_IndoorMapLocation * location = [[PC_IndoorMapLocation alloc] initWithMapPoint: point ordinalValue:kPC_IndoorMapInvalidOrdinalValue];
      [mapManager enumerateFeaturesAtLocation: location usingBlock:^(PC_IndoorMapFeature * feature, BOOL * stop) {
          ...
      }];
 
  @param location Location to enumerate features.
  @param block callback block which is called for each feature.
*/
- (void)enumerateFeaturesAtLocation:(nullable PC_IndoorMapLocation *)location
                         usingBlock:(void (NS_NOESCAPE ^ _Nullable)(PC_IndoorMapFeature * _Nonnull feature, BOOL * _Nonnull stop))block;


/**
 This method searches features by a search string. Search is performed in two ways:
 
   1. By title of the feature.
   2. By keywords defined for a designated properties field. The keywords may be defined in a file named **CategoryKeywords.txt**.
      The file in JSON format must contain array of JSON objects. Each JSON object defines value of the designated field
      by `"cat"` key and keywords by `"keywords"` key.
 
   Example of **CategoryKeywords.txt**:
       [
         {
           "cat": "Restaurants",
           "keywords": ["Food", "Eat", "Cafe"]
         },
         {
           "cat": "Shopping",
           "keywords": ["Buy", "Purchase"]
         }
       ]
 
 Here restaurants keywords are Food, Eat and Cafe. Shopping keywords are Buy and Purchase. When user types "Eat",
 the features whose designated field (for instance, “CATEGORY”) equals to “Restaurants” will be shown in search results.
 Minimal search length for prefix comparison is 3, so if user types “Pu” then nothing will be found.
 And if user types “Pur” it will match “Purchase” – and “Shopping” features will be found.
 
 Consider using asynchronous version of this method (`-[PC_IndoorMapManager searchAsync:searchField:location:completionBlock:]`)
 which does not block main thread.
 
 @param string Search string.
 @param field Designated properties field of **geojson** feature, which is used in conjunction with **CategoryKeywords.txt**.
    For instance, possible value is `@"CATEGORY"`.
 @param location Location to sort found features by distance from. If `nil` then found features will be sorted in alphabetical order.
 @return Array of found features sorted by distance from location or alphabetically by titles.
*/
- (nonnull NSArray<PC_IndoorMapFeature *> *)searchString:(nonnull NSString *)string
                                                 inField:(nonnull NSString *)field
                                                location:(nullable PC_IndoorMapLocation *)location;

/**
 This method asynchronously (without blocking the main thread) searches features by search string.
 This is an asynchronous version of `-[PC_IndoorMapManager search:searchField:location:]`. See there for details.

 @param string Search string.
 @param field Designated properties field of **geojson** feature, which is used in conjunction with **CategoryKeywords.txt**.
 @param completion Callback block which is called when search finishes.
*/
- (void)searchAsyncString:(nonnull NSString *)string
                  inField:(nonnull NSString *)field
                 location:(nullable PC_IndoorMapLocation *)location
               completion:(void (^ _Nullable)(NSArray<PC_IndoorMapFeature *> * _Nonnull features))completion;

// Discontinued.
// The navigation index can be used, for instance, to switch between normal and wheelchair navigation modes.
@property(nonatomic) NSUInteger navigationIndex __deprecated_msg("Use `PC_IndoorMapRouteRequest.navigationIndex`");


/// Set of background objects (static images for instance) for map view. Non-overlay mode only
@property(nonatomic, strong, nullable) NSArray<PC_IndoorMapBackground *> * backgrounds;

@end
