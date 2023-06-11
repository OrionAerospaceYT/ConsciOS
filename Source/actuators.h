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

int pins[] = {0,1,2};

ActuatorGroup<sk_servo,3>test = ActuatorGroup<sk_servo,3>(S1,S2,S3);
Lerp<3>lerp(90.0f,0.0f,180.0f,0.0f,0.0f,90.0f);

namespace actuators{

  // Globals can be defined here

  void init(){
    test.attach(pins);
    test.writeAll(0);
    delay(1000);
  }

  void write(){
   lerp.writeAll(&test); 
   delay(100);
  }

}  // namespace actuators
