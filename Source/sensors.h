#pragma once
//-----Internals------
#include "utility.h"
#include "sensor_struct.h"
//-----Internals------
#include "bmi088.h"
#include "bmp280.h"
// Include your sensor libraries here
namespace sensors {

Baro bmp;
void init() {
    bmp.begin();
    bmp.setGroundLevel();
}

void update() {
    auto t = bmp.getTemp();
    auto agl = bmp.getAGL();
    //auto vec = bmi.getAccel();
    GRAPH("x",t,TOP)
    GRAPH("alt",agl,BOT)
    //GRAPH("yro",vec.x,TOP)
    END_LOG
}

}  // namespace sensors
