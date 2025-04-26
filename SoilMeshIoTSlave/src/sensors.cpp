#include "sensors.h"

#include <Adafruit_BMP280.h>
#include <Adafruit_Sensor.h>
#include <Arduino.h>
#include <Wire.h>

Adafruit_BMP280 bmp;  // I2C
Adafruit_Sensor *bmp_temp = bmp.getTemperatureSensor();
Adafruit_Sensor *bmp_pressure = bmp.getPressureSensor();

void setup_sensors() {
    Wire.begin(I2C_SDA, I2C_SCL);  // Set custom SDA and SCL pins

    if (!bmp.begin(0x76)) {
        Serial.println("BMP280 not found...aborting device!");
        while (1);
    }

    bmp.setSampling(Adafruit_BMP280::MODE_NORMAL,  /* Operating Mode. */
                    Adafruit_BMP280::SAMPLING_X2,  /* Temp. oversampling */
                    Adafruit_BMP280::SAMPLING_X16, /* Pressure oversampling */
                    Adafruit_BMP280::FILTER_X16,   /* Filtering. */
                    Adafruit_BMP280::STANDBY_MS_1000); /* Standby time. */

    Serial.println("BMP280 initialized!");

    bmp_temp->printSensorDetails();
}

float read_temperature() {
    sensors_event_t temp_event;
    bmp_temp->getEvent(&temp_event);

    // Celsius
    if (std::isnan(temp_event.temperature)) {
        return 0;
    }
    return temp_event.temperature;
}

float read_pressure() {
    sensors_event_t pressure_event;
    bmp_pressure->getEvent(&pressure_event);

    // hPa
    if (std::isnan(pressure_event.pressure)) {
        return 0;
    }
    return pressure_event.pressure;
}

float read_moisture() {
    return 1 - (analogRead(LM393_ADC_PIN) / ADC_MAX_VALUE);
}

void print_sensors() {
    Serial.print("Temperature: ");
    Serial.println(read_temperature());
    Serial.print("Pressure: ");
    Serial.println(read_pressure());
    Serial.print("Moisture: ");
    Serial.println(read_moisture());
}
