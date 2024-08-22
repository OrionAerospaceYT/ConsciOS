#pragma once
#include "sk_math.h"
#include "quat_vec.h"

struct Orientation{
    Quat base;
    Vec gyroToYpr(Vec gyro, float dt){
        base += base.fromAngularRate(gyro) * -dt;
        base.normalize();
        auto ypr = base.toEulerVector();
        return ypr * RAD2DEG;
    }
};
