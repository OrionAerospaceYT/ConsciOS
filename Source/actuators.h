#pragma once

// -----Internals------
#include "actuator_struct.h"
#include "utility.h"
// -----Internals------


// Include your Actuator libraries here
#include "skServo.h"

#define Y_RATIO 4.76
#define Z_RATIO 4.76


namespace actuators {
  float posY = 0.0f;
  float posZ = 0.0f;
  // Globals can be defined here
  void init() {}

  void update(float phi, float theta) {
    posY = (0.7 * phi) * Y_RATIO;
    posZ = (0.7 * theta) * Y_RATIO;

    stem::S1.write(posY + 90);
    stem::S4.write(posZ + 90);
  }

}  // namespace actuators
