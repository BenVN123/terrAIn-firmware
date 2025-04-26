#include "mqtt.h"

#include <PubSubClient.h>
#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <LittleFS.h>

// Certificates and Keys for MQTT
const char* root_ca =
    "";

const char* client_cert =
    "";

const char* client_key =
    "";

WiFiClientSecure wifiClient;
PubSubClient mqttClient(wifiClient);

void setup_wifi() {
    delay(10);
    Serial.println();
    Serial.print("Connecting to WiFi...");

    WiFi.begin(WIFI_SSID, WIFI_PASS);

    while (WiFi.status() != WL_CONNECTED) {
        delay(1000);
        Serial.print(".");
    }

    Serial.println();
    Serial.print("Connected to WiFi with IP: ");
    Serial.println(WiFi.localIP());
}

void setup_mqtt() {
    // LittleFS.begin();
    // File root_ca_file = LittleFS.open(ROOT_CA_PATH, "r");
    // File client_cert_file = LittleFS.open(CLIENT_CERT_PATH, "r");
    // File client_key_file = LittleFS.open(CLIENT_KEY_PATH, "r");

    // wifiClient.setCACert(root_ca_file.readString().c_str());
    // wifiClient.setCertificate(client_cert_file.readString().c_str());
    // wifiClient.setPrivateKey(client_key_file.readString().c_str());
    // mqttClient.setServer(MQTT_BROKER, MQTT_PORT);
    wifiClient.setCACert(root_ca);
    wifiClient.setCertificate(client_cert);
    wifiClient.setPrivateKey(client_key);
    mqttClient.setServer(MQTT_BROKER, MQTT_PORT);
    
    // root_ca_file.close();
    // client_cert_file.close();
    // client_key_file.close();
    // LittleFS.end();
}

void reconnect_mqtt() {
    while (!mqttClient.connected()) {
        Serial.print("Attempting MQTT connection...");
        String clientId = "ESP32Client-";
        clientId += String(random(0xffff), HEX);

        if (mqttClient.connect(clientId.c_str(), MQTT_USER, MQTT_PASS)) {
            Serial.println("connected");
        } else {
            Serial.print("failed, rc=");
            Serial.print(mqttClient.state());
            Serial.println(" try again in 5 seconds");
            delay(5000);
        }
    }
}

void handle_join_message(String message) {
    String mqtt_msg;
    mqtt_msg = "{\"nodeId\": " + message + ", \"status\": \"join\"}";
    Serial.println(mqtt_msg);
    Serial.println(mqttClient.publish(MQTT_ALERT_TOPIC, mqtt_msg.c_str()));
}

void handle_lost_message(String message) {
    String mqtt_msg;
    mqtt_msg = "{\"nodeId\": " + message + ", \"status\": \"lost\"}";
    Serial.println(mqtt_msg);
    Serial.println(mqttClient.publish(MQTT_ALERT_TOPIC, mqtt_msg.c_str()));
}

void handle_sensor_message(String message) {
    String mqtt_msg;
    int start = 0; 
    int end = message.indexOf(';');
    String node_id = message.substring(start, end);
    start = end + 1;
    end = message.indexOf(';', start);
    String temperature = message.substring(start, end);
    start = end + 1;
    end = message.indexOf(';', start);
    String pressure = message.substring(start, end);
    start = end + 1;
    String moisture = message.substring(start);
    mqtt_msg = "{\"nodeId\": " + node_id + ", \"temperature\": " + temperature + ", \"pressure\": " + pressure + ", \"moisture\": " + moisture + "}"; 
    Serial.println(mqtt_msg);
    Serial.println(mqttClient.publish(MQTT_SENSOR_TOPIC, mqtt_msg.c_str()));
}

void handle_gps_message(String message) {
    String mqtt_msg;
    int start = 0; 
    int end = message.indexOf(';');
    String node_id = message.substring(start, end);
    start = end + 1;
    end = message.indexOf(';', start);
    String latitude = message.substring(start, end);
    start = end + 1;
    String longitude = message.substring(start);
    mqtt_msg = "{\"nodeId\": " + node_id + ", \"latitude\": " + latitude + ", \"longitude\": " + longitude + "}"; 
    Serial.println(mqtt_msg);
    Serial.println(mqttClient.publish(MQTT_GPS_TOPIC, mqtt_msg.c_str()));
}

void send_mqtt_message(String message) {
    String trimmed_msg = message.substring(5); 
    if (message.startsWith("sens:")) {
        handle_sensor_message(trimmed_msg);
    } else if (message.startsWith("join:")) {
        handle_join_message(trimmed_msg);
    } else if (message.startsWith("lost:")) {
        handle_lost_message(trimmed_msg);
    } else if (message.startsWith("gnss:")) {
        handle_gps_message(trimmed_msg);
    }
}