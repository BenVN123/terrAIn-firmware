#ifndef SERIAL_H
#define SERIAL_H

#define TXD1 18 
#define RXD1 19 

#define BAUD_RATE 115200

#include <WString.h>

void setup_serials();
String read_next_message();

#endif