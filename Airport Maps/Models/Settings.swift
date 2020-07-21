//
//  Settings.swift
//  Airport Maps
//
//  Created by Bart Bruijnesteijn on 18/07/2020.
//

import SwiftUI
import Combine

public class Settings: ObservableObject {
//    public let objectWillChange: ObservableObjectPublisher = ObservableObjectPublisher()
    @Published var ordinal: String = "0"
    
    public func ordinal(ordinal: String) {
        self.ordinal = ordinal
    }
    
//    @Published var ordinal: String = "0" {
//        willSet {
//            objectWillChange.send()
//        }
//    }
}
