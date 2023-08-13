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

#include <Wire.h>

int pins[] = {12,49,30};

Servo s1;
Servo s2;
Servo s3;
skActuatorGroup<3>test = skActuatorGroup<3>(stem::S0,stem::S1,stem::S2);
//ActuatorGroup<Servo,3>test = ActuatorGroup<Servo,3>(s1,s2,s3);
Lerp<3>lerp(90.0f,0.0f,180.0f,0.0f,0.0f,90.0f);

namespace actuators{

  // Globals can be defined here

  void init(){
  }

  void write(){
  }

}  // namespace actuators
