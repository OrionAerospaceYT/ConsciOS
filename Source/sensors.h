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
    Vec test = cum.getAccel();
    GRAPH("x",test.x,TOP)
    GRAPH("y",test.y,TOP)
    GRAPH("z",test.z,TOP)
    END_LOG
}

}  // namespace sensors
