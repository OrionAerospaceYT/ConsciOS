#pragma once
//-----Internals------
#include "utility.h"
#include "sensor_struct.h"
//-----Internals------
#include "bmi088.h"
// Include your sensor libraries here
namespace sensors {

Imu cum;
void init() {
    cum.begin();
}

void update() {
    GRAPH("cum",cum.getGyroscopeZ(),TOP);
    END_LOG
}

}  // namespace sensors
