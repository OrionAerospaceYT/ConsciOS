#pragma once

//-----Internals------
#include "sensors.h"
#include "actuators.h"
#include "sub_task.h"
#include "utility.h"
//-----Internals------

// Tasks go here-- this keeps the main file clean and focused on the "flow" of tasks
// Our general functions will be defined here things like our main loops
// Long sections of code or repeated code loops can be moved to sub_task.h

// The functions in place here can be changed to suit your needs
// The ones listed here serve as inspiration--feel free to change them as you need -- but remember to change your Tasks in main.h
namespace task
{

    // Globals can be defined here

    // Can be used for code that only runs once
    // This can also be run multiple times by changing the code flow in main.h

    void Setup()
    {
        subtask::exampleLongFunc(); // you can delete this purely for demonstration
        sensors::init();
        PRINTLN("Setup")
    }

    // Can be used to automatically test actuators
    // Very useful for quick plug and play testing
    void ActuatorTest()
    {
        PRINTLN("Act Test")
    }

    // Can be used to print sensor values and any other required calibration
    void Calibration()
    {
        PRINTLN("CALIB")
    }

    // Code that loops
    void Loop()
    {
        //actuators::write();
        PRINTLN("LOOP")
    }

    void Loop2(){
        sensors::update();
    }

} // namespace task
