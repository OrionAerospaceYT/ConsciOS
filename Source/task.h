#pragma once

// -----Internals------
#include "sensors.h"
#include "actuators.h"
#include "sub_task.h"
#include "utility.h"
#include "control.h"
#include "time_handler.h"
// -----Internals------

#include "orientation.h"

namespace task {

    // I have commented my changes, sorry if you didnt want it pushed but it works so
    // enjoy testing it yourself - I think the problems were:
    // 1) You didn'd convert the bmi inputs to to radians
    // 2) The way you calculated delta time
    // 3) The sensor input was being maxed out consistently

    Timer timer;
    Orientation ori;

    void Setup() {
        sensors::init();

    }

    void ActuatorTest() {

    }

    void Calibration() {
        // Make sure the first iteration doesnt mess anything up with a large delta t
        timer.start();
        timer.stop();
    }

    void Loop() {
        // Moved around timer because the way you did it didnt make sense
        float dt = timer.deltaT();
        timer.start();

        // Changed sensor range to 2000 as it was capping out at 125 (bmi088.h)
        // Changed dt to positive because why the hell was it negative lmfao (oritentation.h)
        auto gyro = sensors::getGyro() * DEG2RAD;
        auto ypr = ori.gyroToYpr(gyro, dt);

        // IDK what this does but im guessing ur using it
        actuators::update(ypr.y, ypr.z);

        // Added some more graphs because #WeLoveData
        GRAPH("x", ypr.x, TOP);
        GRAPH("y", ypr.y, TOP);
        GRAPH("z", ypr.z, TOP);
        GRAPH("x", gyro.x, BOT);
        GRAPH("y", gyro.y, BOT);
        GRAPH("z", gyro.z, BOT);
        END_LOG;

        // End the timer at an appropriate time
        timer.stop();
    }

    void Loop2() {

    }

}
