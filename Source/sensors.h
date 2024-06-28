#pragma once

// -----Internals------
#include "utility.h"
#include "sensor_struct.h"
#include "bmi088.h"
// -----Internals------

// Include your sensor libraries here

namespace sensors {

Imu bmi;

void init() {
    bmi.begin();
}

Vec getGyro() {
    return bmi.getGyro();
}

}  // namespace sensors
