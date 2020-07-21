//
//  PC_IndoorMapBackground.h
//  PC_IndoorMapOverlay
//
//  Copyright © 2018 Point Consulting. All rights reserved.
//

#import <Foundation/Foundation.h>

/**
   Background map view object. Allows to add custom objects (images) to map view using `PC_IndoorMapManager.backgrounds` property.
   Non-overlay map mode only.
*/
@interface PC_IndoorMapBackground : NSObject


/**
 Initialize a new background object
 
 @param coordinate The center coordinate of background object on the map.
 @param scale Background content scaling. `1.0` means the bounding box of approximately 100x100 meters (actual values may vary depending on object's coordinate latitude)
 @param rotationAngle Background content rotation, in radians.
*/
- (nonnull instancetype)initWithCoordinate:(CLLocationCoordinate2D)coordinate scale:(CGFloat)scale
                             rotationAngle:(CGFloat)rotationAngle;


/// Background content image. Must be assigned before adding the background object to the map manager
@property(nonatomic, strong, nullable) UIImage * contentImage;

@end

