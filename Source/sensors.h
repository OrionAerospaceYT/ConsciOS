#pragma once
//-----Internals------
#include "utility.h"
#include "sensor_struct.h"
//-----Internals------
#include "bmi088.h"
#include "bmp280.h"
#include "mmc5603.h"
#include "filters.h"

// Include your sensor libraries here
namespace sensors {

Imu bmi;
Baro bmp;
Mag mmc;
LowPassFilter roll_fil(0.9);
LowPassFilter pitch_fil(0.95);

void init() {
    bmp.begin();
    bmp.setGroundLevel();
    mmc.begin();
    bmi.begin();
}

Vec accelToAngle(Vec accel){
    Vec out;
    out.x = atan2(accel.y, accel.z) * RAD2DEG;
    out.y = atan2(-accel.x, sqrt(accel.y*accel.y + accel.z*accel.z)) * RAD2DEG;
    out.y = pitch_fil.filter(out.y);
   return out; 
}

Vec getAccel(){
    Vec temp = bmi.getAccel();
    return Vec(temp.x,temp.y,-temp.z);
}

Vec getGyro(){
    return bmi.getGyro();
}

Vec update() {
    auto vec = bmi.getAccel();
    // z and x swap z senses negative 9.8 x now senses positive 9.8
    Vec resolved = Vec(vec.z,vec.y,-vec.x);
    auto ori = accelToAngle(resolved);
    GRAPH("Pitch",ori.y,TOP);
    return ori;
}

}  // namespace sensors
