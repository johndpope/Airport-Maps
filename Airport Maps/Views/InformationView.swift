//
//  InformationView.swift
//  AirportMaps
//
//  Created by Bart Bruijnesteijn on 08/01/2020.
//  Copyright © 2020 Bart Bruijnesteijn. All rights reserved.
//

import SwiftUI

let version = Bundle.main.infoDictionary!["CFBundleShortVersionString"] as! String

struct InformationView: View {
    var body: some View {
        VStack {
            Image(decorative: "logo")
                .resizable()
                .scaledToFit()
                .frame(width: 120.0, height: 120.0)
            Text("Airport Maps")
                .foregroundColor(.accentColor)
                .font(Font.largeTitle)
                .frame(width: 600, height: 50, alignment: .center)
                .padding(.vertical)
            Text("Version \(version)")
                .foregroundColor(.primary)
                .font(Font.headline)
            Text("XCode 11.3 - iOS 13.2")
                .foregroundColor(.secondary)
                .font(Font.body)
                .padding()
            Text("Swift 5 - SwiftUI")
                .foregroundColor(.secondary)
                .font(Font.body)
        }
    }
}

struct InformationView_Preview: PreviewProvider {
    static var previews: some View {
        Group {
            InformationView()
                .environment(\.colorScheme, .light)
            InformationView()
                .environment(\.colorScheme, .dark)
        }
    }
}
