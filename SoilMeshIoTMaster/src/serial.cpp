#include "serial.h"
#include <Arduino.h>

HardwareSerial serial_bridge(1);

void setup_serials() {
    Serial.begin(BAUD_RATE);
    serial_bridge.begin(BAUD_RATE, SERIAL_8N1, RXD1, TXD1);
    // ser÷al_bridge.setRxBufferSize(2048);
    Serial.println("Serial bridge initialized");
}

String read_next_message() {
    String message = "";
    if (serial_bridge.available()) {
        message = serial_bridge.readStringUntil('\n');
        Serial.println("Received: " + message);
    }
    return message;
}