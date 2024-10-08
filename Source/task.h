#pragma once

// -----Internals------
#include "sensors.h"
#include "actuators.h"
#include "sub_task.h"
#include "goose.h"
#include "control.h"
#include "time_handler.h"
// -----Internals------

#include "orientation.h"

// Tasks go here-- this keeps the main file clean and focused on the "flow" of tasks
// Our general functions will be defined here things like our main loops
// Long sections of code or repeated code loops can be moved to sub_task.h

// The functions in place here can be changed to suit your needs
// The ones listed here serve as inspiration--feel free to change them as
// you need -- but remember to change your Tasks in main.h

namespace task {

    // Globals can be defined here
    // Can be used for code that only runs once
    // This can also be run multiple times by changing the code flow in main.h
    void Setup() {}

    // Can be used to automatically test actuators
    // Very useful for quick plug and play testing
    void ActuatorTest() {}

    // Can be used to print sensor values and any other required calibration
    void Calibration() {}

    // Code that loops
    void Loop() {}

    void Loop2() {}

}  // namespace task
