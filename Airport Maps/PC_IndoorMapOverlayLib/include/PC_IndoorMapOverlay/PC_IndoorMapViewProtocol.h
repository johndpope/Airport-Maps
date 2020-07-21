//
//  PC_IndoorMapViewProtocol.h
//  PC_IndoorMapOverlay
//
//  Copyright © 2018 Point Consulting. All rights reserved.
//

#import <MapKit/MapKit.h>
#import "PC_IndoorMapView.h"

/**
 This is a way to use same application interface for MKMapView and PC_IndoorMapView.
 Additionally, it adds some useful methods to use in both overlay and non-overlay methods
 */
@protocol PC_IndoorMapViewProtocol<NSObject>

@property(nonatomic, readonly) double zoomLevel;

/// A boolean value indicating whether the map displays point-of-interest information.
/// @warning `PC_IndoorMapView` ignores this property
@property(nonatomic) BOOL showsPointsOfInterest;

/// A Boolean indicating whether the map displays a compass control.
/// @warning `PC_IndoorMapView` ignores this property
@property(nonatomic) BOOL showsCompass;

/// A Boolean indicating whether the map displays extruded building information.
/// @warning `PC_IndoorMapView` ignores this property
@property(nonatomic) BOOL showsBuildings;

/// The area currently displayed by the map view.
@property(nonatomic) MKMapRect visibleMapRect;

/// Changes the currently visible portion of the map and optionally animates the change.
- (void)setVisibleMapRect:(MKMapRect)mapRect animated:(BOOL)animated;

/// The mode used to track the user location.
@property(nonatomic) MKUserTrackingMode userTrackingMode;

/// A Boolean value indicating whether the map should try to display the user’s location.
@property(nonatomic) BOOL showsUserLocation;

/// The area currently displayed by the map view.
@property(nonatomic) MKCoordinateRegion region;

/// Changes the currently visible region and optionally animates the change.
- (void)setRegion:(MKCoordinateRegion)region animated:(BOOL)animated;

/// The map coordinate at the center of the map view.
@property(nonatomic) CLLocationCoordinate2D centerCoordinate;

/// Converts a point in the specified view’s coordinate system to a map coordinate.
- (CLLocationCoordinate2D)convertPoint:(CGPoint)point toCoordinateFromView:(nullable UIView *)view;

- (void)setCenterCoordinate:(CLLocationCoordinate2D)centerCoordinate
      visibleRadialDistance:(CLLocationDistance)radialDistance animated:(BOOL)animated;

- (void)setCenterCoordinate:(CLLocationCoordinate2D)centerCoordinate
      visibleRadialDistance:(CLLocationDistance)radialDistance
          centerSpanXOffset:(CGFloat)centerSpanXOffset
          centerSpanYOffset:(CGFloat)centerSpanYOffset
                   animated:(BOOL)animated;

- (void)setCoordinate:(CLLocationCoordinate2D)coordinate atPoint:(CGPoint)point animated:(BOOL)animated;

@end


#pragma mark - Concrete PC_IndoorMapViewProtocol conformed classes

@interface PC_IndoorMapView(PC_IndoorMapViewProtocol_Conformance)<PC_IndoorMapViewProtocol>
@end

@interface MKMapView(PC_IndoorMapViewProtocol_Conformance)<PC_IndoorMapViewProtocol>
@end
