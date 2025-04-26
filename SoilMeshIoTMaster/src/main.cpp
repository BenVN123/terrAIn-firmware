#include "main.h"

#include <Arduino.h>
#include <stdlib.h>
#include <string.h>

#include "mesh.h"
#include "mqtt.h"
#include "serial.h"

void setup() {
  setup_serials();
    Serial.print("Booting master node...");
    pinMode(LED_BUILTIN, OUTPUT);
    digitalWrite(LED_BUILTIN, HIGH);
    setup_wifi();
    setup_mqtt();
    Serial.println("ready!");
}

void loop() {
    if (!mqttClient.connected()) {
        reconnect_mqtt();
    }

    mqttClient.loop();
    // nodeId;temp;pressure;soilMoisture
    // int rand_node_id = rand() % 10;
    // float rand_temp = rand() % 100 / 3.0;
    // float rand_pressure = rand() % 100 / 3.0;
    // float rand_moisture = rand() / RAND_MAX;
    // String rand_message = String(rand_node_id) + ";" + String(rand_temp) + ";" +
    //                       String(rand_pressure) + ";" + String(rand_moisture);
    // mqttClient.publish(MQTT_SENSOR_TOPIC, rand_message.c_str());
    // Serial.println("Published: " + rand_message);
    // delay(10000);

    send_mqtt_message(read_next_message());
}