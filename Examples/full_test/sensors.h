#pragma once

// -----Internals------
#include "macros.h"
#include "sensor_struct.h"
// -----Internals------

// Include your sensor libraries here

#include "bmi088.h"
#include "bmp280.h"
#include "mmc5603.h"
#include "single_sensor.h"
namespace sensors {


void init() {}

void update() {}
}  // namespace sensors
