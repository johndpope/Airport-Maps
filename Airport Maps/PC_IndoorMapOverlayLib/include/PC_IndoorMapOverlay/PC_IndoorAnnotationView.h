//
//  PC_IndoorAnnotationView.h
//  PC_IndoorMapOverlay
//
//  Created by n.gerasimov on 22/05/16.
//  Copyright © 2016 Point Consulting. All rights reserved.
//

#import "PC_IndoorMapAnnotation.h"

/**
  The class is only used in **non-overlay** mode and plays the same role as `MKAnnotationView` does in **overlay** mode.
  You do not create instances of this class directly.
*/
@interface PC_IndoorAnnotationView: PC_IndoorRotatableView

@property(nonatomic, strong, readonly) PC_IndoorMapAnnotation * annotation;

/// Position of the callout’s anchor relative to annotation view bounds (left-top).
@property(nonatomic, readonly) CGPoint calloutPos;

@end
