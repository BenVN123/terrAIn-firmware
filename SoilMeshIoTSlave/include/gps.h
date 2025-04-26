#ifndef GPS_H
#define GPS_H

#define GPS_BAUD_RATE 9600
#define GPS_RX 16  // RX2
#define GPS_TX 17  // TX2

typedef struct GPSLocation {
    float latitude;
    float longitude;
} GPSLocation;

void setup_gps();
GPSLocation read_gps();

#endif