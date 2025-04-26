#include "mesh.h"

#include <WiFi.h>
#include <painlessMesh.h>
#include <Arduino.h>
#include <unordered_set>
#include <WString.h>

#include "sensors.h"
#include "serial.h"
#include "gps.h"

// Create the Mesh object
painlessMesh mesh;

// Declare userScheduler
Scheduler userScheduler;


void send_sensor_data();
void send_gps_data();

// Declare task for sending sensor data
Task task_send_sensor(TASK_SECOND * SENSOR_CYCLE_TIME, TASK_FOREVER, &send_sensor_data);
Task task_send_gps(TASK_SECOND * GPS_CYCLE_TIME, TASK_FOREVER, &send_gps_data);

// Function to send sensor data
void send_sensor_data() {
    String msg = "sens:" + String(mesh.getNodeId()) + ";" + String(read_temperature()) +
                 ";" + String(read_pressure()) + ";" +
                 String(read_moisture());
    mesh.sendBroadcast(msg);
    send_serial_bridge_data(msg);
    Serial.println(msg);
}


void send_gps_data() {
  GPSLocation location = read_gps();
  String msg = "gnss:" + String(mesh.getNodeId()) + ";" + String(location.latitude, 6) + ";" + String(location.longitude, 6);
  mesh.sendBroadcast(msg);
  send_serial_bridge_data(msg);
  Serial.println(msg);
}


void received_callback(uint32_t from, String &msg) {
    Serial.printf("startHere: Received from %u msg=%s\n", from, msg.c_str());
    send_serial_bridge_data(msg);
}


void new_connection_callback(uint32_t node_id) {
    Serial.printf("--> New Connection: %u\n", node_id);
    send_serial_bridge_data("join:" + String(node_id));
}

void dropped_connection_callback(uint32_t node_id) {
    Serial.printf("--> Node Lost: %u\n", node_id);
    send_serial_bridge_data("lost:" + String(node_id));
}

// Function to initialize the mesh network
void setup_mesh() {
    mesh.setDebugMsgTypes(ERROR | STARTUP);  // Set the debug message types

    mesh.init(MESH_PREFIX, MESH_PASSWORD, &userScheduler,
              MESH_PORT);  // Pass userScheduler to mesh init
    mesh.onReceive(&received_callback);
    mesh.onNewConnection(&new_connection_callback);
    mesh.onDroppedConnection(&dropped_connection_callback);

    userScheduler.addTask(task_send_sensor);    // Add the task to the scheduler
    userScheduler.addTask(task_send_gps);    // Add the task to the scheduler
    task_send_sensor.enable();                  // Enable the task
    task_send_gps.enable();                  // Enable the task
}

void update_mesh() {
    mesh.update();            // Update mesh communication
    userScheduler.execute();  // Execute scheduled tasks
}
