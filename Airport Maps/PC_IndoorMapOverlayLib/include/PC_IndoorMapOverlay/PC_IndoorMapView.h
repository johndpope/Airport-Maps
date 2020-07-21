#import "PC_IndoorMapViewDelegate.h"
#import "PC_IndoorMapTypes.h"

/**
 This class is only used in **non-overlay** mode and plays the same role as `MKMapView` does in **overlay** mode.
 
 You create an instance of this class with `-[PC_IndoorMapView initWithFrame:]`.
 After that you pass the instance created to `-[PC_IndoorMapManager initWithIndoorMapView:]`.
 After that you set `PC_IndoorMapManager` instance as a delegate of `PC_IndoorMapView` or you need to forward `PC_IndoorMapViewDelegate` events to
 `PC_IndoorMapManager` yourself.
*/
@interface PC_IndoorMapView: UIView

-(void)deselectAnnotation:(nonnull id<MKAnnotation>)annotation animated:(BOOL)animated;
-(void)selectAnnotation:(nonnull id<MKAnnotation>)annotation animated:(BOOL)animated;

-(void)addOverlays:(nonnull NSArray<id<MKOverlay> > *)overlays;
-(void)removeOverlays:(nonnull NSArray<id<MKOverlay> > *)overlays;
-(void)removeAnnotation:(nonnull id<MKAnnotation>)annotation;
-(void)addAnnotation:(nonnull id<MKAnnotation>)annotation;

/**
 Returns the annotation view associated with the specified annotation object, if any.
 @param annotation The annotation object whose view you want.
 @return The annotation view or `nil` if the view has not yet been created. This method may also return `nil` if the annotation is not
   in the visible map region and therefore does not have an associated annotation view.
*/
-(nullable PC_IndoorAnnotationView *)viewForAnnotation:(nonnull id<MKAnnotation>)annotation;

-(void)addAnnotations:(nonnull NSArray<id<MKAnnotation> > *)annotations;
-(void)removeAnnotations:(nonnull NSArray<id<MKAnnotation> > *)annotations;

@property(nonatomic, readonly, nonnull) id<MKAnnotation> userLocation;

/// Delegate
@property(nonatomic, weak,nullable) NSObject<PC_IndoorMapViewDelegate> *delegate;

/// Map rectangle which limits scrolling in the view and zooming out.
@property(nonatomic) MKMapRect limitRect;

/// Minimal visible map region diameter (in meters). Use this parameters to limit zooming in.
@property(nonatomic) double minimalDiameter;

@property(nonatomic, weak, nullable) PC_IndoorUserTrackingBarButtonItem *userTrackingBarButtonItem;

@end
