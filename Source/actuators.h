#pragma once

//-----Internals------

#include "actuator_struct.h"
#include "utility.h"
#include "lerp.h"
//#include "internal_defs.h"

//-----Internals------
#include <Servo.h>
// Include your Actuator libraries here
#include "skServo.h"

namespace actuators{

  // Globals can be defined here
  void init(){
    pinMode(11,INPUT);
    pinMode(18,INPUT);
  }

  void write(float input){
    PRINTLN(input);
    stem::S1.write(input);
    stem::S4.write(input);


  }

}  // namespace actuators
