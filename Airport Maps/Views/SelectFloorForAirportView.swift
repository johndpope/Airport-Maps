//
//  SelectFloorForAirportView.swift
//  Airport Maps
//
//  Created by Bart Bruijnesteijn on 19/07/2020.
//

import SwiftUI

struct SelectFloorForAirportView: View {
    @Binding var actionsheetIsPresented: Bool

    @ObservedObject var settings: Settings

    var airport : Airport

    var body: some View {
        VStack {
            Text("Select floor")
                .font(.headline)
                .foregroundColor(.accentColor)
                .padding()
            
            ForEach(airport.airportOrdinalNames.indices) { index in
                Button(action: {
                    settings.ordinal(ordinal: String(index))
                    
                    actionsheetIsPresented = false
                }) {
                    Text(airport.airportOrdinalNames[index])
                        .font(.subheadline)
                        .frame(maxWidth: .infinity)
                        .foregroundColor(Color.primary)
                        .padding()
                }                
            }
        }
    }
}
