#include <Arduino.h>
#include <TinyGPS++.h>
#include "gps.h"

HardwareSerial ss(2);

TinyGPSPlus gps;

void setup_gps() {
    ss.begin(GPS_BAUD_RATE, SERIAL_8N1, GPS_RX, GPS_TX);
}

GPSLocation read_gps() {
    if (ss.available() > 0) {
        Serial.println(ss.read());
        gps.encode(ss.read());
    }
    // GPSLocation location = {
    //     .latitude = (float) gps.location.lat(),
    //     .longitude = (float) gps.location.lng(),
    // };
    // GPSLocation location = {
    //     .latitude = 37.272409, 
    //     .longitude = -121.767586, 
    // };
    // GPSLocation location = {
    //     .latitude = 37.272537, 
    //     .longitude = -121.767334, 
    // };
    GPSLocation location = {
        .latitude = 37.272681, 
        .longitude = -121.767211, 
    };
    return location;
}