//
//  MapViewController.swift
//  Wrapper
//
//  Created by Bart Bruijnesteijn on 17/07/2020.
//

import SwiftUI
import UIKit
import MapKit
import CoreLocation

class MapViewController: UIViewController, CLLocationManagerDelegate, PC_IndoorMapManagerDelegate {
    private let pcMapManager = PC_IndoorMapManager()
    private var pcMapView: (PC_IndoorMapViewProtocol & UIView)!

    var airport: Airport
    var settings: Settings
    
    var locationManager = CLLocationManager()
    
    init() {
        self.airport = Airport()
        self.settings = Settings()
        
        super.init(nibName: nil, bundle: nil)
    }
    
    init(airport: Airport, settings: Settings, floor: String) {
        self.airport = airport
        self.settings = settings
        
        super.init(nibName: nil, bundle: nil)
    }

    required init?(coder: NSCoder) {
        fatalError("init(coder:) has not been implemented")
    }
    
    override func viewDidLoad() {
        super.viewDidLoad()
        
        locationManager.delegate = self
        locationManager.desiredAccuracy = kCLLocationAccuracyBest

        let mapView = MKMapView()
        mapView.frame = CGRect(x: 0, y: 0, width: view.frame.size.width, height: view.frame.size.height)

        mapView.mapType = .standard
        mapView.showsUserLocation = true
        mapView.isRotateEnabled = true
        mapView.isZoomEnabled = true
        mapView.showsCompass =  true
        mapView.setUserTrackingMode(.followWithHeading, animated: true)
        mapView.showsScale = true
        
        mapView.mapType = .mutedStandard
        mapView.showsBuildings = false
        mapView.showsTraffic = false
        mapView.pointOfInterestFilter = .excludingAll

        self.view.addSubview(mapView)
        
        pcMapView = mapView
        pcMapManager.delegate = self
        pcMapManager.setMapView(mapView)

        showMap()
    }
    
    public func showMap() {
        guard let venueFolderPath = Bundle.main.resourceURL?.appendingPathComponent("Maps/AVF/\(self.airport.airportCode)").path else {
            fatalError("Unable to find map data")
        }

        pcMapManager.loadVenueFromDirectory(atPath: venueFolderPath, options: [],  onFeatureLoad: { (_, _, _) in

        }) { [weak self] finished in
            guard let strongSelf = self, finished else { return }
            strongSelf.centerMap()
        }
    }
    
    private func centerMap() {
        let center = CLLocationCoordinate2D(latitude: Double(self.airport.airportLatitude)!, longitude: Double(self.airport.airportLongitude)!)
        let visibleRadialDistance = CLLocationDistance(Double(self.airport.airportRadius)!)
        
        pcMapView.setCenter(center, visibleRadialDistance: visibleRadialDistance, animated: true)
        pcMapManager.ordinalValue = Int(settings.ordinal)!
    }

    // PC_IndoorMapManagerDelegate methods
    func indoorMapManager(_ manager: PC_IndoorMapManager, willDisplay featureOverlay: PC_IndoorMapFeatureOverlay) {
        // No drawing by default
        featureOverlay.renderer = nil

        // Conditional drawing for certain objects
        switch featureOverlay.feature.layer.layerType {

        case .units:
            guard let categoryName = featureOverlay.feature.categoryName else { break }

            let renderer = PC_IndoorMapRenderer()
            featureOverlay.renderer = renderer
            renderer.strokeWidth = 0.5

            if categoryName == "Room" || categoryName == "room" {
                renderer.strokeColor = UIColor.black
                renderer.fillColor = UIColor.white
                break
            }

            if categoryName.contains("Stairs") || categoryName.contains("Escalator") ||
                categoryName.contains("Elevator") {
                renderer.strokeColor = UIColor.black
                renderer.fillColor = UIColor.white
                break
            }

            renderer.strokeColor = UIColor.black

        case .levels:
            let renderer = PC_IndoorMapRenderer()
            renderer.strokeColor = UIColor.black
            renderer.fillColor = UIColor.white
            featureOverlay.renderer = renderer

        default:
            break
        }
    }

    // CLLocationManagerDelegate methods
    func locationManager(_ manager: CLLocationManager, didChangeAuthorization status: CLAuthorizationStatus) {
        switch status {
        case .notDetermined:
            locationManager.requestAlwaysAuthorization()
            break
            
        case .authorizedWhenInUse:
            break
            
        case .authorizedAlways:
            locationManager.allowsBackgroundLocationUpdates = true
            locationManager.pausesLocationUpdatesAutomatically = false
            break
            
        case .restricted:
            // restricted by e.g. parental controls. User can't enable Location Services
            break
            
        case .denied:
            // user denied your app access to Location Services, but can grant access from Settings.app
            break
            
        default:
            break
        }

        if CLLocationManager.locationServicesEnabled(){
            locationManager.startUpdatingLocation()
        }
    }
}
