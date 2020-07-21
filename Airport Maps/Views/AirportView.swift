//
//  AirportView.swift
//  Wrapper
//
//  Created by Bart Bruijnesteijn on 15/07/2020.
//

import SwiftUI

struct AirportView: View {
    @EnvironmentObject var airports : Airports
    
    @ObservedObject var settings = Settings()
    
    @State private var actionsheetIsPresented = false
    
    var index: Int
    
    var body: some View {
        VStack {
            MapView(settings: settings, index: index)
                .navigationTitle(airports.maps[index].airportCode)
            
            HStack {
                Spacer()
                
                Button(airports.maps[index].airportOrdinalNames[Int(settings.ordinal)!]) {
                    self.actionsheetIsPresented = true
                }
                .frame(minWidth: 0, idealWidth: .infinity, maxWidth: .infinity, minHeight:
                        0, idealHeight: 40, maxHeight: 80, alignment: .center)
                .background(Color.white)
                .cornerRadius(40)
                .padding()
                
                Spacer()
            }
            
            
            .sheet(isPresented: self.$actionsheetIsPresented, content: {
                SelectFloorForAirportView(actionsheetIsPresented: $actionsheetIsPresented, settings: settings, airport: airports.maps[index])
            })
        }
        .edgesIgnoringSafeArea(.bottom)
    }
}

struct AirportView_Previews: PreviewProvider {
    static var previews: some View {
        AirportView(index: 0)
    }
}
