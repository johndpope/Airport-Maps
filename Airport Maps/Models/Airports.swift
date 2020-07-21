//
//  Airports.swift
//  AirportMapFramework
//
//  Created by Bart Bruijnesteijn on 21/05/2020.
//  Copyright © 2020 Bart Bruijnesteijn. All rights reserved.
//

import SwiftUI
import MapKit

public class Airports: ObservableObject {
    @Published var maps: [Airport] = []
    
    public init() {
        fetchMaps()
    }
    
    private func fetchMaps() {
        guard let url = Bundle.main.url(forResource: "Maps/AirportMapsConfiguration", withExtension: "json") else {
            fatalError("Failed to locate file in bundle.")
        }

        guard let data = try? Data(contentsOf: url) else {
            fatalError("Failed to load file from bundle.")
        }

        let decoder = JSONDecoder()
        
        guard let decoded = try? decoder.decode([Airport].self, from: data) else {
            fatalError("Failed to decode file from bundle.")
        }
        
        maps = decoded
    }
    
    public func region(index: Int) -> MKCoordinateRegion {
        return MKCoordinateRegion(center: CLLocationCoordinate2D(latitude: Double(maps[index].airportLatitude)!, longitude: Double(maps[index].airportLongitude)!), span: MKCoordinateSpan(latitudeDelta: Double(maps[index].airportRadius)!, longitudeDelta: Double(maps[index].airportRadius)!))
    }
}

struct Airports_Previews: PreviewProvider {
    static var previews: some View {
        /*@START_MENU_TOKEN@*/Text("Hello, World!")/*@END_MENU_TOKEN@*/
    }
}
