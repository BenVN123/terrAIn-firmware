#ifndef SERIAL_H
#define SERIAL_H

#define BRIDGE_TX 18 
#define BRIDGE_RX 19 

#define BRIDGE_BAUD_RATE 115200

#include <WString.h>

void setup_serial_bridge();
void send_serial_bridge_data(String msg);

#endif