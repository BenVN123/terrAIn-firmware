#include "serial.h"

#include <Arduino.h>

HardwareSerial serial_bridge(1);

void setup_serial_bridge() {
    serial_bridge.begin(BRIDGE_BAUD_RATE, SERIAL_8N1, BRIDGE_RX, BRIDGE_TX);
    Serial.println("Serial bridge initialized");
}

void send_serial_bridge_data(String msg) {
    serial_bridge.println(msg);
}