#pragma once
//-----Internals------
#include "utility.h"
#include "sensor_struct.h"
//-----Internals------
#include "bmi088.h"
#include "bmp280.h"
#include "mmc5603.h"

// Include your sensor libraries here
namespace sensors {

Baro bmp;
Mag mmc;
void init() {
    bmp.begin();
    bmp.setGroundLevel();
    mmc.begin();
}

void update() {
    auto t = bmp.getTemp();
    auto agl = bmp.getAGL();
    auto ma = mmc.getMag();
    //auto vec = bmi.getAccel();
    GRAPH("x",ma.x,TOP)
    GRAPH("y",ma.y,TOP)
    GRAPH("z",ma.z,TOP)
    //GRAPH("yro",vec.x,TOP)
    END_LOG
}

}  // namespace sensors
