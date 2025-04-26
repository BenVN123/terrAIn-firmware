#ifndef MESH_H
#define MESH_H

#define MESH_PREFIX "soilMesh"
#define MESH_PASSWORD "soilMeshPassword"
#define MESH_PORT 5555

#define SENSOR_CYCLE_TIME 5
#define GPS_CYCLE_TIME 30 

#include <WString.h>
#include <stdint.h>
#include "sensors.h"

void setup_mesh();
void update_mesh();

#endif
