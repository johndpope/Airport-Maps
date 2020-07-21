//
//  PC_IndoorMapLocationProvider.h
//  PC_IndoorMapOverlay
//
//  Copyright © 2017 Point Consulting. All rights reserved.
//

#import <CoreLocation/CoreLocation.h>
#import "PC_IndoorMapTypes.h"

/**
   Location data provider for `PC_IndoorMapManager`.
   @see `PC_IndoorMapCoreLocationProvider`
*/
@interface PC_IndoorMapLocationProvider: NSObject

/// Heading filter for location updates.
@property(assign, nonatomic) CLLocationDegrees headingFilter;

/// Starts updating location and heading
- (void)start;

/// Stops updating location and heading
- (void)stop;

/// Notifies the `PC_IndoorMapManager` manager about heading update. Overridden methods should call `super`
- (void)updateHeadingWith:(nullable CLHeading *)heading;

/// Notifies the `PC_IndoorMapManager` manager about location update. Overridden methods should call `super`
- (void)updateLocationWith:(nullable CLLocation *)location;

@end

/**
  The location data provider class based on standard Core Location facility usage.
  This is the default location provider for `PC_IndoorMapManager` class
 
  @see `PC_IndoorMapManager.locationProvider`
*/
@interface PC_IndoorMapCoreLocationProvider: PC_IndoorMapLocationProvider

@end
