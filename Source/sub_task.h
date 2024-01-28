#pragma once

#include "utility.h"
#include "vector.h"
// This is where we place long functions or repeated code
/*Say hypothetically you have a filtering process you apply to your data 10
times for a loop (its a hypothetical) you might do that in here to keep the
task.h file cleaner
*/
namespace subtask {
void exampleLongFunc() {}

Vec accelToAngle(Vec accel){
    Vec out;
    out.x = atan2(accel.y, accel.z) * 180/PI;
    out.y = atan2(-accel.x, sqrt(accel.y*accel.y + accel.z*accel.z)) * 180/PI;
   return out; 
}

}  // namespace subtask
