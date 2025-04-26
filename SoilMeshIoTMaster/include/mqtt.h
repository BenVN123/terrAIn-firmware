#ifndef MQTT_H
#define MQTT_H

// REPLACE WITH WIFI SETTINGS
#define WIFI_SSID "iphone"
#define WIFI_PASS "hotspotpw"

// REPLACE WITH AWS IoT SETTINGS
#define MQTT_BROKER "a2nkc7jmrkgiu6-ats.iot.us-east-2.amazonaws.com"
#define MQTT_PORT 8883
#define MQTT_USER ""
#define MQTT_PASS ""

#define MQTT_SENSOR_TOPIC "soilMesh/test/sensor"
#define MQTT_GPS_TOPIC "soilMesh/test/gps"
#define MQTT_ALERT_TOPIC "soilMesh/test/alert"

#define ROOT_CA_PATH "/data/creds/AmazonRootCA1.pem"
#define CLIENT_CERT_PATH "/data/creds/e3af66cda61e45bb49b5f28cdb14a11e854fe59d5d0bab45fafe36a93fd89594-certificate.pem.crt"
#define CLIENT_KEY_PATH "/data/creds/e3af66cda61e45bb49b5f28cdb14a11e854fe59d5d0bab45fafe36a93fd89594-private.pem.key"

#include <PubSubClient.h>
#include <WiFiClientSecure.h>

extern WiFiClientSecure wifiClient;
extern PubSubClient mqttClient;

void setup_wifi();
void setup_mqtt();
void reconnect_mqtt();
void send_mqtt_message(String msg);

#endif
