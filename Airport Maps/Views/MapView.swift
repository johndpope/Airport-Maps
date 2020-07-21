//
//  MapView.swift
//  Wrapper
//
//  Created by Bart Bruijnesteijn on 17/07/2020.
//

import SwiftUI

struct MapView: UIViewControllerRepresentable {
    @EnvironmentObject var airports : Airports
    
    @ObservedObject var settings: Settings
    
    var index: Int

    func makeUIViewController(context: Context) -> MapViewController {
        let controller = MapViewController(airport: airports.maps[index], settings: settings, floor: settings.ordinal)
        
        return controller
    }
    
    func updateUIViewController(_ controller: MapViewController, context: Context) {
        controller.settings = settings
        
        controller.showMap()
    }
}
