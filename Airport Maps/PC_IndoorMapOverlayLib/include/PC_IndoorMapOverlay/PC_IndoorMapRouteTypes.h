//
//  PC_IndoorMapRouteTypes.h
//  PC_IndoorMapOverlay
//
//  Copyright © 2017 Point Consulting. All rights reserved.
//

#import <MapKit/MapKit.h>
#import "PC_IndoorMapTypes.h"

@class PC_IndoorMapRoute, PC_IndoorMapLocation;

//--------------------------------------------------------------------------------------------
// Route requests
//--------------------------------------------------------------------------------------------

/**
 The base abstract class to create a route request. The class is not intended to be instantiated.
 @see `PC_IndoorMapSimpleRouteRequest`, `PC_IndoorMapTSPRouteRequest`
*/
@interface PC_IndoorMapRouteRequest: NSObject

/// The unique route identifier. This identifier will be passed to the route created with `-[PC_IndoorMapManager makeRouteWithRequest:]` call
@property(nonatomic, strong, readonly, nonnull) NSString * identifier;

/// The route start point or `nil` if current user location must be used
@property(nonatomic, strong, nullable) PC_IndoorMapLocation * startLocation;

/// Desired transport type
@property(nonatomic) MKDirectionsTransportType transportType;

/// Navigation index. Typically, there are 2 indices: 0 - normal mode, 1 - wheelchair mode
@property(nonatomic) NSUInteger navigationIndex;

/**
 The designited initializer.
 @param identifier The route identifier
*/
- (nonnull instancetype)initWithIdentifier:(nonnull NSString *)identifier;

@end

/**
 A typical two point "from"-"to" route request. Allows to create a single segment route from `startLocation` to `endLocation`
*/
@interface PC_IndoorMapSimpleRouteRequest: PC_IndoorMapRouteRequest

/// The route destination point or `nil` if current user location must be used
@property(nonatomic, strong, nullable) PC_IndoorMapLocation * endLocation;

@end

/**
 A simplified _Travelling Salesman Problem_ route request. The route starts in `startLocation` point and
 subsequently visits all locations added through `-[PC_IndoorMapTSPRouteRequest addLocation:identifier:priority:]` basing
 on the following conditions:
 
 - The higher priority locations must be visited first
 - Having two or more equal priority locations the closest one must be visited first
*/
@interface PC_IndoorMapTSPRouteRequest: PC_IndoorMapRouteRequest

/**
  Add a destination point of given priority.
 
  @param location Destination location or `nil` if current user location must be used
  @param identifier The identifier to be assigned to the appropriate route's segment
  @param priority The visit priority. Higher values mean that this location will be visited sooner
*/
- (void)addLocation:(nullable PC_IndoorMapLocation *)location
         identifier:(nullable NSString *)identifier
           priority:(NSInteger)priority;

@end

//--------------------------------------------------------------------------------------------
// Route steps
//--------------------------------------------------------------------------------------------

/**
 This structure holds single route step (i.e. one part of an overall route) description.
 This is a part of `PC_IndoorMapRouteSegment`
 */
@interface PC_IndoorMapStep : NSObject

/// Written instructions for following the path represented by this step.
@property(nonatomic, strong, readonly, nullable) NSString * instructions;

/// Detailed step geometry.
@property(nonatomic, strong, readonly, nonnull) MKPolyline * polyline;

/// Polyline visible map rect or `MKMapRectNull` for empty polyline
@property(nonatomic, readonly) MKMapRect polylineVisibleMapRect;

/// Level (floor) ordinal.
@property(nonatomic, readonly) NSInteger ordinal;

@end

//--------------------------------------------------------------------------------------------
// Route segments
//--------------------------------------------------------------------------------------------

/**
 A part of a `PC_IndoorMapRoute` route object, the path between two endpoints: `startLocation` and `endLocation`.
 A typical route contains only one segment. Refer to `PC_IndoorMapTSPRouteRequest` for multi-segment route creation.
 */
@interface PC_IndoorMapRouteSegment: NSObject

/// Concrete steps directions and instructions.
@property(nonatomic, strong, readonly, nonnull) NSArray<PC_IndoorMapStep *> * steps;

/// The segment visual appearance used to render subpaths (lines) inside the venue.
@property(nonatomic, strong, nonnull) PC_IndoorMapRenderer * indoorLineRenderer;

/// The segment visual appearance used to render subpaths (lines) outside the venue.
@property(nonatomic, strong, nonnull) PC_IndoorMapRenderer * outdoorLineRenderer;

/// The total (indoor + outdoor) approximate travelling time. It is negative in case of error.
@property(nonatomic, readonly) NSTimeInterval totalTime;

/// The total (indoor + outdoor) travelling distance, in meters. It is negative in case of error.
@property(nonatomic, readonly) CLLocationDistance totalDistance;

/// The segment start location
@property(nonatomic, readonly, nullable) PC_IndoorMapLocation * startLocation;

/// The segment end location
@property(nonatomic, readonly, nullable) PC_IndoorMapLocation * endLocation;

/// An identifier. Currently used only by `PC_IndoorMapTSPRouteRequest` for visited locations tagging.
@property(nonatomic, strong, nullable) NSString * identifier;

/// Index of this segment in the `PC_IndoorMapRoute.segments` list.
@property(nonatomic, readonly) NSUInteger index;

@end

//--------------------------------------------------------------------------------------------
// Routes
//--------------------------------------------------------------------------------------------

/**
 The delegate of a `PC_IndoorMapRoute` object may adopt this protocol to track and manage the route created and
 registered by `-[PC_IndoorMapManager makeRouteWithRequest:]` call
*/
@protocol PC_IndoorMapRouteDelegate<NSObject>

/**
 The method is called then the route change it's state
 @param route The route
*/
- (void)routeDidChangeState:(nonnull PC_IndoorMapRoute *)route;

@optional

/**
 This optional method is called just before the route segment is added to the map view.
 This is the best place to adjust the segments visual appearance using `indoorLineRenderer` and `outdoorLineRenderer` properties
 @param route The route
 @param segment The segment that will be displayed
 */
- (void)route:(nonnull PC_IndoorMapRoute *)route willDisplaySegment:(nonnull PC_IndoorMapRouteSegment *)segment;

@end

/// Route state (see `PC_IndoorMapRoute.state`)
typedef NS_ENUM(NSInteger, PC_IndoorMapRouteState) {
    
    /// Invalid, empty, idle, expired or initial state. The route is just created or reset to initial state due any external events
    /// (user location changing, new navigation data updating, switching to other's map layer etc). As soon as it possible, the
    /// route will be placed to the processing queue by the `PC_IndoorMapManager`
    /// At the moment of `PC_IndoorMapRouteStateIdle` state all the route data is considered as invalid and must not be used for
    /// travelling and route rendering.
    PC_IndoorMapRouteStateIdle,
    
    /// The route is being recalculated by the `PC_IndoorMapManager`.
    /// At the moment of `PC_IndoorMapRouteStateCalculating` state all the route data is considered as invalid and must not be used for
    /// travelling and route rendering.
    PC_IndoorMapRouteStateCalculating,

    /// The route is fully calculated and ready to be rendered / used by the application.
    PC_IndoorMapRouteStateCompleted,

    /// The route could not be calculated. See `PC_IndoorMapRoute.error` to get more info about the error
    PC_IndoorMapRouteStateFailed,
    
    /// The route has been detached from manager by `-[PC_IndoorMapManager removeRoute:]` or `-[PC_IndoorMapManager removeRouteWithIdentifier:]` call.
    /// Typically, this is the last state before route's destroying/releasing. The application should not keep or use the route data at this state.
    PC_IndoorMapRouteStateRemoved
};

/**
   The main route class. Created by manager with `-[PC_IndoorMapManager makeRouteWithRequest:]` call. Maintains all the route information.
*/
@interface PC_IndoorMapRoute: NSObject

/// The route data structures state
@property(nonatomic, readonly) PC_IndoorMapRouteState state;

/// The concrete route calculation error when `PC_IndoorMapRoute.state` property is ``
@property(nonatomic, readonly, nullable) NSError * error;

/// The unique route identifier. This is the same as the appropriate `PC_IndoorMapRouteRequest.identifier` one
@property(nonatomic, readonly, nonnull) NSString * identifier;

/// Same as `PC_IndoorMapRouteRequest.navigationIndex`;
@property(nonatomic) NSUInteger navigationIndex;

/// Delegate to track and manage the route
@property(nullable, nonatomic, weak) id<PC_IndoorMapRouteDelegate> delegate;

/// List of route segments as soon as they are calculated. 
@property(nonatomic, readonly, strong, nonnull) NSArray<PC_IndoorMapRouteSegment *> * segments;

@end

