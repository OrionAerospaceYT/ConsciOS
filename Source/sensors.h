#pragma once

// -----Internals------
#include "utility.h"
#include "sensor_struct.h"
#include "bmi088.h"
// -----Internals------

// Include your sensor libraries here

namespace sensors {

Imu bmi;

void init() {}

void update() {}
}  // namespace sensors
