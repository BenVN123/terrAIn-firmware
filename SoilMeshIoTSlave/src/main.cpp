#include "main.h"

#include <Arduino.h>

#include "mesh.h"
#include "sensors.h"
#include "serial.h"
#include "gps.h"

bool led_state = false;

void setup() {
    Serial.begin(115200);
    setup_serial_bridge();
    pinMode(LED_BUILTIN, OUTPUT);
    digitalWrite(LED_BUILTIN, HIGH);
    setup_mesh();
    //setup_sensors();
}

void loop() {
    led_state = !led_state;
    digitalWrite(LED_BUILTIN, led_state ? HIGH : LOW);
    print_sensors();
    update_mesh();
    delay(1000);
}
