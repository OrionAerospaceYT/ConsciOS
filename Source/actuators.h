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
    Wire.begin();
    //test.attach(pins);
  }

  void write(){
    Wire.beginTransmission(0x68);
    PRINT("BUS1");
    PRINT(Wire.endTransmission());
    test.writeAll(0);
    PRINT("zero")
    END_LOG
    delay(500);
    test.writeAll(45);
    PRINT("45")
    END_LOG
    delay(500);
    test.writeAll(90);
    PRINT("ninety")
    END_LOG
    delay(500);
    test.writeAll(135);
    PRINT("136");
    END_LOG
    delay(500);
    test.writeAll(180);
    PRINT("180")
    delay(500);
    END_LOG
   test.writeAll(90);
   delay(500);
   //S0.write(0);
   //delay(1000);
  }

}  // namespace actuators
