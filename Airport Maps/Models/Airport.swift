//
//  Airport.swift
//  Verkeersles
//
//  Created by Bart Bruijnesteijn on 28/03/2020.
//  Copyright © 2020 Bart Bruijnesteijn. All rights reserved.
//

import SwiftUI

public struct Airport: Codable, Hashable, Identifiable {
    private enum CodingKeys: String, CodingKey {
        case airportName, airportCode, airportCity, airportCountry,  airportLatitude, airportLongitude, airportRadius, airportOrdinal, airportMaximumOrdinal, airportOrdinalNames
    }
    
    public let id = UUID()
    
    var airportName: String
    var airportCode: String
    var airportCity: String
    var airportCountry: String
    var airportLatitude: String
    var airportLongitude: String
    var airportRadius: String
    var airportOrdinal: String
    var airportMaximumOrdinal: String
    var airportOrdinalNames: [String]
    
    public init() {
        airportName = ""
        airportCode = ""
        airportCity = ""
        airportCountry = ""
        airportLatitude = ""
        airportLongitude = ""
        airportRadius = ""
        airportOrdinal = ""
        airportMaximumOrdinal = ""
        airportOrdinalNames = []
    }
    
    public func name() -> String {
        return self.airportName
    }
    
    public func country() -> String {
        return self.airportCountry
    }
    
    public func city() -> String {
        return self.airportCity
    }
    
    public func code() -> String {
        return self.airportCode
    }
    
    public func latitude() -> String {
        return self.airportLatitude
    }
    
    public func longitude() -> String {
        return self.airportLongitude
    }
    
    public func radius() -> String {
        return self.airportRadius
    }
    
    public func ordinal() -> String {
        return self.airportOrdinal
    }
    
    public func maximumOrdinal() -> String {
        return self.airportMaximumOrdinal
    }
    
    public func ordinalNames() -> [String] {
        return self.airportOrdinalNames
    }
}

