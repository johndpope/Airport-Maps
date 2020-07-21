//
//  PC_IndoorMapManager+Routing.h
//  PC_IndoorMapOverlay
//
//  Copyright © 2017 Point Consulting. All rights reserved.
//

#import "PC_IndoorMapManager.h"
#import "PC_IndoorMapRouteTypes.h"

#pragma mark - Routing

/// PC_IndoorMapManager extensions to handle routes
@interface PC_IndoorMapManager(Routing)

/**
 Create and register a route conforming an appropriate route request.
 @param request The configured route request object to create the route.
 @return The created `PC_IndoorMapRoute` object reference.
*/
- (nonnull PC_IndoorMapRoute *)makeRouteWithRequest:(nonnull PC_IndoorMapRouteRequest *)request;

/**
 Get a route for given identifier. The route must be previously created with `-[PC_IndoorMapManager makeRouteWithRequest:]` call
 @param identifier The unique route identifier (see `PC_IndoorMapRoute.identifier`)
 @return The route or `nil` if no route for given identifier was found
*/
- (nullable PC_IndoorMapRoute *)routeForIdentifier:(nonnull NSString *)identifier;

/**
 Unregister and release a route previously created with `-[PC_IndoorMapManager makeRouteWithRequest:]` call
 @param route The route
*/
- (void)removeRoute:(nonnull PC_IndoorMapRoute *)route;

/**
 Unregister and release the route by it's identifier.
 @param identifier The route's identifier
 */
- (void)removeRouteWithIdentifier:(nonnull NSString *)identifier;

/**
 Unregister and release all routes
 */
- (void)removeAllRoutes;

@end

#pragma mark - Deprecated Routing

/// PC_IndoorMapManager extensions to handle deprecated route management
@interface PC_IndoorMapManager(Deprecated_Routing)

/**
 Creates the default navigation route.
 Sends request to navigation system to calculate and render a path between two locations. If both source and destination locations are
 inside the venue, or if the mode is **non-overlay*, then only indoor navigation service is used. Otherwise, outdoor navigation
 service is used together with indoor navigation service to calculate the full path.
 
 A location is considered inside the venue if it's coordinate is inside the venue polygon (the polygon is defined in **Venue.geojson**).
 `PC_IndoorMapManagerDelegate` can override it in `-[PC_IndoorMapManagerDelegate indoorMapManager:isPointInsideVenue:isDestination:hint:]` method.
 
 @see `-[PC_IndoorMapManager isLocationInsideVenue:]`
 @warning The _default route_ concept will be deprecated soon.
 @param idFrom User-defined identifier for the mark of start location, or `nil` if start is current user location.
 @param idTo User-defined identifier for the mark of destination location, or `nil` if destination is current user location.
 @param transportType Transport type (only used if outdoor navigation service is involved).
*/
- (void)makeRouteFrom:(nullable NSString *)idFrom to:(nullable NSString *)idTo
       transportType:(MKDirectionsTransportType)transportType
       __deprecated_msg("Use `makeRouteFrom:to:transportType:navigationIndex:`");

- (void)makeRouteFrom:(nullable NSString *)idFrom to:(nullable NSString *)idTo
       transportType:(MKDirectionsTransportType)transportType
      navigationIndex:(NSUInteger)navigationIndex;

/**
 Removes the default navigation route from the map.
 @warning The _default route_ concept will be deprecated soon.
*/
-(void)removeRoute;

/**
 Check if the default navigation route exists in the map. YES, if navigation route exists in the map, NO otherwise.
 @warning The _default route_ concept will be deprecated soon.
*/
@property(nonatomic, readonly) BOOL routeExists;

@end
