#pragma once

//-----Internals------
#include "sensors.h"
#include "actuators.h"
#include "sub_task.h"
#include "utility.h"
#include "control.h"
#include "time_handler.h"
//-----Internals------

#include "orientation.h"

// Tasks go here-- this keeps the main file clean and focused on the "flow" of tasks
// Our general functions will be defined here things like our main loops
// Long sections of code or repeated code loops can be moved to sub_task.h

// The functions in place here can be changed to suit your needs
// The ones listed here serve as inspiration--feel free to change them as you need -- but remember to change your Tasks in main.h
namespace task
{

    // Globals can be defined here
    PID controller = PID(15.0f,0.1f,0.05f);
    Timer sk_timer = Timer();
    // Can be used for code that only runs once
    // This can also be run multiple times by changing the code flow in main.h

    void Setup()
    {
        subtask::exampleLongFunc(); // you can delete this purely for demonstration
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
        sensors::init();
        controller.setlims(-90,90);
        PRINTLN("CALIB")
    }

    // Code that loops
    void Loop()
    {
        //actuators::write();
        PRINTLN("LOOP")
    }

    void Loop2(){
        while(Serial.available()){
        sk_timer.start();
        auto accel = sensors::getAccel(); 
        auto gyro = sensors::getGyro(); 
        gyro *= DEG2RAD;
        accel /= 10.0f;
        auto state = ori::resolve_orientation(accel,gyro,sk_timer.deltaT());
        state *= RAD2DEG;
        state *= 100.0f;
        GRAPH("x",state.x,BOT);
        GRAPH("y",state.y,BOT);
        GRAPH("z",state.z,BOT);
        auto control_input = controller.compute(-state.y,sk_timer.deltaT()) + 90.0f;
        //GRAPH("CONTROL",control_input,BOT);
        END_LOG;
        //actuators::write(control_input);
        sk_timer.stop();
        }
    }

} // namespace task
