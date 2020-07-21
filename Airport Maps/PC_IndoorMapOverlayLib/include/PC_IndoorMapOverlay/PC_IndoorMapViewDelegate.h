#import "PC_IndoorAnnotationView.h"

@class PC_IndoorMapView, IndoorView_OverlayLayerFactory, PC_IndoorMapAnnotationAction;

/**
 The protocol defines a set of required methods which you use to receive map-related update methods.
 The `PC_IndoorMapView` also uses these methods to request annotation and overlay views and to
 manage interactions with those views.
 */
@protocol PC_IndoorMapViewDelegate

/** Asks the delegate for a renderer object to use when drawing the specified overlay.
 
 You should forward this method to the `PC_IndoorMapManager` object.
 
 @param mapView The map view that requested the renderer object.
 @param overlay The overlay object that is about to be displayed.
 @return The renderer to use when presenting the specified overlay on the map.
 */
- (IndoorView_OverlayLayerFactory *)indoorMapView:(PC_IndoorMapView *)mapView layerFactoryForOverlay:(id<MKOverlay>)overlay;

/** Returns the view associated with the specified annotation object.
 
 You should forward this method to the `PC_IndoorMapManager` object.

 @param mapView The map view that requested the annotation view.
 @param annotation The object representing the annotation that is about to be displayed.
 @return The annotation view to display for the specified annotation.
 */
-(PC_IndoorAnnotationView *)indoorMapView:(PC_IndoorMapView *)mapView viewForAnnotation:(id<MKAnnotation>)annotation;

/** Tells the delegate that the region displayed by the map view just changed.
 
 You should forward this method to the `PC_IndoorMapManager` object.

 @param mapView The map view whose visible region changed.
 @param animated If `YES`, then the change to the new region was animated.
 */
-(void)indoorMapView:(PC_IndoorMapView *)mapView regionDidChangeAnimated:(BOOL)animated;

/** Tells the delegate that one or more annotation views were added to the map.
 
 You should forward this method to the `PC_IndoorMapManager` object.

 @param mapView The map view that added the annotation views.
 @param views Currently is nil.
 */
-(void)indoorMapView:(PC_IndoorMapView *)mapView didAddAnnotationViews:(NSArray<PC_IndoorAnnotationView *> *)views;

/** Tells the delegate that one of its annotation views was deselected.
 
 You should forward this method to the `PC_IndoorMapManager` object.

 @param mapView The map view containing the annotation.
 @param annotation The annotation whose view was deselected.
 */
-(void)indoorMapView:(PC_IndoorMapView *)mapView didDeselectAnnotation:(id<MKAnnotation>)annotation;

/** Tells the delegate that one of its annotation views was selected.
 
 You should forward this method to the `PC_IndoorMapManager` object.

 @param mapView The map view containing the annotation.
 @param annotation The annotation whose view was selected.
 */
-(void)indoorMapView:(PC_IndoorMapView *)mapView didSelectAnnotation:(id<MKAnnotation>)annotation;

/** Tells the delegate that the user tracking mode changed.
 
 You should forward this method to the `PC_IndoorMapManager` object.

 @param mapView The map view whose user tracking mode changed.
 @param mode The mode used to track the user’s location.
 */
-(void)indoorMapView:(PC_IndoorMapView *)mapView didChangeUserTrackingMode:(MKUserTrackingMode)mode;

/** 
 Map view calls this method when callout view is about to show for an annotation.
 The delegate can either return nil to show standard callout bubble view, or return custom
 view which will be added as a subview to the annotation's view.
 
 @param mapView The map view which the annotation belongs to.
 @param annotation The annotation for which callout view needs to show.
 @return nil to show a standard callout bubble view, or a custom callout view.
 */
-(UIView *)indoorMapView:(PC_IndoorMapView *)mapView calloutForAnnotation:(id<MKAnnotation>)annotation;

-(PC_IndoorMapAnnotationAction *)indoorMapView:(PC_IndoorMapView *)mapView actionForSelectedAnnotation:(id<MKAnnotation>)annotation;

@end

