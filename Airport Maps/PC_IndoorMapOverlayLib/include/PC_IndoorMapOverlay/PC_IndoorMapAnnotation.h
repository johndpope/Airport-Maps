//
//  PC_IndoorMapAnnotation.h
//  PC_IndoorMapOverlay
//
//  Copyright © 2017 Point Consulting. All rights reserved.
//

#import "PC_IndoorMapFeature.h"

typedef NS_ENUM(NSInteger, PC_IndoorMapCollisionMode) {
    PC_IndoorMapCollisionModeRectangle,
    PC_IndoorMapCollisionModeCircle
};

#pragma mark -

@interface PC_IndoorMapAnnotationRep: NSObject

// lower bound only. max level is defined by next representation OR the maxZoomLevel property of annotation itself
@property(nonatomic, readonly) CGFloat minZoomLevel;

// PC_IndoorMapCollisionModeRectangle is default
@property(nonatomic) PC_IndoorMapCollisionMode collisionMode;

// allow to build a chain of different sizes. Beware of retain cycling!
@property(nonatomic, strong, nullable) PC_IndoorMapAnnotationRep * collisionFallback;

// CGPointZero is default
@property(nonatomic) CGPoint centerOffset;

- (nonnull instancetype)init NS_DESIGNATED_INITIALIZER;
+ (nonnull instancetype)dotOfRadius:(CGFloat)radius color:(nonnull UIColor *)color minZoomLevel:(CGFloat)minZoomLevel;
+ (nonnull instancetype)image:(nonnull UIImage *)image scale:(CGFloat)scale minZoomLevel:(CGFloat)minZoomLevel;

@end

@interface PC_IndoorMapMarkerAnnotationRep: PC_IndoorMapAnnotationRep

/// The color to apply to the glyph image
@property(nonatomic, strong, nullable) UIColor * glyphTintColor;

/// The background color of the marker balloon.
@property(nonatomic, strong, nullable) UIColor * markerTintColor;

/// The image displayed in the marker balloon.
@property(nonatomic, strong, nullable) UIImage * glyphImage;

@end

#pragma mark -


/**
  Base class for map annotation objects. Concrete descendants are:
 
  - `PC_IndoorMapIconAnnotation` - Map icon object
  - `PC_IndoorMapTextAnnotation` - Map text label object
  - `PC_IndoorMapCustomAnnotation` - Custom map objects
  - `PC_IndoorMapUserAnnotation` - Base class for user-defined annotations (pins, etc)
 
 PC_IndoorMapAnnotation
 ├── PC_IndoorMapUserAnnotation
 │   ├── PC_IndoorMapMarkerAnnotation
 │   └── PC_IndoorMapPinAnnotation
 ├── PC_IndoorMapCustomAnnotation
 ├── PC_IndoorMapUserLocationAnnotation
 ├── PC_IndoorMapClusterAnnotation
 ├── PC_IndoorMapIconAnnotation
 └── PC_IndoorMapTextAnnotation
 
*/

@interface PC_IndoorMapAnnotation: NSObject

- (nonnull instancetype)initWithFeature:(nonnull PC_IndoorMapFeature *)feature;
- (nonnull instancetype)initWithLocation:(nonnull PC_IndoorMapLocation *)location;

@property(nonatomic, nonnull, strong, readonly) PC_IndoorMapLocation * location;

@property(nonatomic, copy, nullable) NSString * title;
@property(nonatomic, copy, nullable) NSString * subtitle;
@property(nonatomic, strong, nullable) id userInfo;

// Default representation properties, left here for the sake of compatibility. Mapped to default representation properties
@property(nonatomic) CGFloat minZoomLevel;
@property(nonatomic) CGPoint centerOffset;
@property(nonatomic) PC_IndoorMapCollisionMode collisionMode;
@property(nonatomic, strong, nullable) PC_IndoorMapAnnotationRep * collisionFallback; // beware of retain cycling!

@property(nonatomic) CGFloat maxZoomLevel;
@property(nonatomic) CGPoint calloutOffset;
@property(nonatomic) NSInteger priority;

@property(nonatomic, strong, nullable) PC_IndoorMapAnnotationRep * selectedRepresentation;
@property(nonatomic, strong, nullable) PC_IndoorMapAnnotationRep * markedRepresentation;
- (void)addRepresentation:(nonnull PC_IndoorMapAnnotationRep *)representation;

@end

#pragma mark -

@interface PC_IndoorMapClusterAnnotation : PC_IndoorMapAnnotation

@property(nonatomic, readonly, nonnull) NSArray<PC_IndoorMapAnnotation *> * annotations;

@end

#pragma mark -

/**
  Map annotation object that is represented by a custom view
 */
@interface PC_IndoorMapCustomAnnotation: PC_IndoorMapAnnotation

@property(nonatomic, strong, nullable) UIView * customView;

@end

/**
  Map annotation object that is represented by a single image
*/
@interface PC_IndoorMapIconAnnotation: PC_IndoorMapAnnotation

@property(nonatomic, strong, nullable) UIImage * icon;

@end

#pragma mark -

/**
  Map annotation object that is represented by an attributed text
*/
@interface PC_IndoorMapTextAnnotation: PC_IndoorMapAnnotation

@property(nonatomic) UIEdgeInsets contentInsets;
@property(nonatomic, strong, nullable) NSAttributedString * attributedText;
@property(nonatomic, strong, nullable) UIColor * backgroundColor;

/// The text max bounding rect size. Unlimited (MAXFLOAT, MAXFLOAT) by default
@property(nonatomic) CGSize textMaxBoundingRectSize;

/// Calculated text bounding rect size. Depends on `attributedText` and `textMaxBoundingRectSize` properties
@property(nonatomic, readonly) CGSize textSize;

@end

#pragma mark -

/** 
  The base class for user-defined annotations (pins, etc)
*/
@interface PC_IndoorMapUserAnnotation: PC_IndoorMapAnnotation

@property(nonatomic, nonnull, strong, readonly) NSString * identifier;
@property(nonatomic) BOOL isRemovedOnDeselection;

@end

#pragma mark -

/// User-defined map annotation object that is represented by a classic pin image
@interface PC_IndoorMapPinAnnotation: PC_IndoorMapUserAnnotation

/// The pin color for using in **overlay** mode. Please note that assigned `pinImage` property is overrides this value
@property(nonatomic, strong, nonnull) UIColor * pinColor;

/// A Boolean value indicating whether the annotation view is animated onto the screen.
/// Currently implemented only for standard MapKit pins (when `pinColor` is assigned in **overlay** mode)
@property(nonatomic) BOOL animatesDrop;

/// Custom pin image. Used both in **overlay** and **non-overlay** modes. Has priority over `pinImage`.
@property(nonatomic, strong, nullable) UIImage * pinImage;

@end

#pragma mark -

/// User-defined map annotation object that is represented by a balloon-shaped marker at designited location
@interface PC_IndoorMapMarkerAnnotation: PC_IndoorMapUserAnnotation

/// The color to apply to the glyph image.
@property(nonatomic, strong, nullable) UIColor * glyphTintColor;

/// The background color of the marker balloon
@property(nonatomic, strong, nullable) UIColor * markerTintColor;

@end

#pragma mark -

/**
  The base class for map annotation touch actions
 */
@interface PC_IndoorMapAnnotationAction: NSObject

@end

/**
  The map annotation action that represents a callout appearance
*/
@interface PC_IndoorMapShowCalloutAction: PC_IndoorMapAnnotationAction

/** Custom content view
 
  Due some MapKit implementation issues, the width and height layout constraints are required to be set
  for this view in **overlay** mode. The library will add them if needed. Add and set constraints yourself
  if you need more control 

  Also, in MapKit, the custom view suppress subtitles
*/
@property(nonatomic, strong, nullable) UIView * customContentView;
@property(nonatomic, copy, nullable) void (^disclosureButtonAction)(void);
@property(nonatomic) BOOL isDisclosureButtonEnabled;

@end

/**
   Custom action.
 
   Use this kind of action when you need some non-standard response on annotation tapping.
   For example, you may show annotation or location info in a separated screen.
*/
@interface PC_IndoorMapCustomAction: PC_IndoorMapAnnotationAction

+ (nonnull instancetype)actionWithBlock:(void (^ _Nullable)(void))block;
@property(nonatomic, copy, nullable) void (^actionBlock)(void);

@end

@interface PC_IndoorMapUserLocationAnnotation: PC_IndoorMapAnnotation

@property (nonatomic, readonly) CLLocationAccuracy horizontalAccuracy;

@end

