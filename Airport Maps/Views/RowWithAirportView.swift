//
//  RowWithAirportView.swift
//  AirportMaps
//
//  Created by Bart Bruijnesteijn on 08/01/2020.
//  Copyright © 2020 Bart Bruijnesteijn. All rights reserved.
//

import SwiftUI

struct RowWithAirportView: View {
    @EnvironmentObject var airports : Airports

    var index: Int

    var body: some View {
        HStack {
            NavigationLink(destination: AirportView(index: index)) {
                HStack {
                    VStack(alignment: .leading) {
                        Text(airports.maps[index].airportCode)
                            .font(.headline)
                            .foregroundColor(.accentColor)
                            .padding(.vertical)
                        
                        Text(airports.maps[index].airportName)
                            .font(.subheadline)
                            .padding(.bottom)
                        
                        Text(airports.maps[index].airportCity)
                            .font(.subheadline)
                            .fontWeight(.light)
                    }
                    .padding(.bottom)
                    
                    Spacer()
                    
//                    if(airport.downloaded) {
//                        Button(action: {
//                            print("Available")
//                        }) {
//                            Image("available")
//                                .renderingMode(.original)
//                                .font(.title)
//                                .font(Font.largeTitle.weight(.light))
//                                .foregroundColor(Color("klm_green"))
//                        }
//                        .buttonStyle(BorderlessButtonStyle())
//                    }
//                    else {
//                        Button(action: {
//                            print("Download")
//                        }) {
//                            Image("download")
//                                .renderingMode(.original)
//                                .font(.title)
//                                .font(Font.largeTitle.weight(.light))
//                                .foregroundColor(Color("klm_light_blue"))
//                        }
//                        .buttonStyle(BorderlessButtonStyle())
//                    }
                }
            }
        }
    }
}

struct RowWithAirportView_Previews: PreviewProvider {
    static var previews: some View {
        Group {
            RowWithAirportView(index: 0)
                .environment(\.colorScheme, .light)
            RowWithAirportView(index: 0)
                .environment(\.sizeCategory, .extraExtraExtraLarge)
            RowWithAirportView(index: 0)
                .environment(\.colorScheme, .dark)
        }
    }
}

