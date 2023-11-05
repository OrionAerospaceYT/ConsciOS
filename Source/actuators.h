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
  }

  void write(){
    stem::S1.write(90);
    delay(100);
    stem::S1.write(180);
    delay(100);
  }

}  // namespace actuators
