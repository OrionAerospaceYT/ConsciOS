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

  void write(){
      GRAPH("11", digitalRead(11), TOP);
      GRAPH("18", digitalRead(18),BOT);
      stem::S1.write(180);
      END_LOG;
  }

}  // namespace actuators
