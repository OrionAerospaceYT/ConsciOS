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
}

void update() {
    auto t = bmp.readTemperature();
    auto p = bmp.readPressure();
    PRINTLN(t);
    //auto vec = bmi.getAccel();
    GRAPH("x",t,TOP)
    GRAPH("x",p,BOT)
    //GRAPH("yro",vec.x,TOP)
    END_LOG
}

}  // namespace sensors
