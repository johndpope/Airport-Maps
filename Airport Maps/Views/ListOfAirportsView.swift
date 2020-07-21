//
//  ListOfAirportsView.swift
//  AirportMaps
//
//  Created by Bart Bruijnesteijn on 07/01/2020.
//  Copyright © 2020 Bart Bruijnesteijn. All rights reserved.
//

import SwiftUI

struct ListOfAirportsView: View {
    @EnvironmentObject var airports : Airports
    
    @State private var informationIsPresented = false
    
    var body: some View {
        NavigationView {
            List(airports.maps.indices, id: \.self) { index in
                RowWithAirportView(index: index)
                    
                    
                    .navigationBarItems(trailing:
                                            Button(action: {
                                                self.informationIsPresented.toggle()
                                            }) {
                                                Image(systemName: "info.circle")
                                                    .font(.title)
                                                    .font(Font.largeTitle.weight(.light))
                                                    .foregroundColor(.primary)
                                            })
            }
            .edgesIgnoringSafeArea(.bottom)
            .navigationBarTitle("ListOfAirportsViewTitle")
            
            .sheet(isPresented: self.$informationIsPresented, content: {
                InformationView()
            })
        }
    }
}

struct ListOfAirportsView_Previews: PreviewProvider {
    static var previews: some View {
        Group {
            ListOfAirportsView()
                .environmentObject(Airports())
                .environment(\.colorScheme, .light)
            ListOfAirportsView()
                .environmentObject(Airports())
                .environment(\.sizeCategory, .extraExtraExtraLarge)
            ForEach(["en", "nl", "fr", "zh", "es", "it", "de", "ja", "pt", "ru"], id: \.self) { localIdentifier in ListOfAirportsView()
                .environmentObject(Airports())
                .environment(\.locale, .init(identifier: localIdentifier))
            }
            ListOfAirportsView()
                .environmentObject(Airports())
                .environment(\.layoutDirection, .rightToLeft)
                .environment(\.locale, .init(identifier: "ar"))
            ListOfAirportsView()
                .environmentObject(Airports())
                .environment(\.sizeCategory, .extraExtraExtraLarge)
            ListOfAirportsView()
                .environment(\.colorScheme, .dark)
                .environmentObject(Airports())
        }
    }
}

