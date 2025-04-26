#ifndef SENSORS_H
#define SENSORS_H

#define I2C_SDA 21
#define I2C_SCL 22

#define LM393_ADC_PIN 34
#define ADC_MAX_VALUE 4095.0f

void setup_sensors();
void update_sensors();
void print_sensors();
float read_temperature();
float read_pressure();
float read_moisture();

#endif
