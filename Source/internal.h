#pragma once

//-----Internals------
#include "utility.h"
#include "task_flow.h"
#include "time_handler.h"
#include "sidekick_state.h"

//-----Internals------

Timer sk_timer = Timer();
SideKickState<> state_info = SideKickState<>();

namespace sm {
//------INTERNAL-----
// DO NOT TOUCH
void SM_UPDATE_LOOP() {
    taskSchedule();
}


void SM_INIT() {
    //stem::S0.attach(PS0);
    //stem::S1.attach(PS1);
    //stem::S2.attach(PS2);
    //stem::S3.attach(PS3);
    //stem::S4.attach(PS4);
    //stem::S5.attach(PS5);
    //stem::S6.attach(PS6);
    //stem::S7.attach(PS7);
    //stem::S8.attach(PS8);
    //stem::S9.attach(PS9);
    //stem::S10.attach(PS10);
    //stem::S11.attach(PS11);
    Serial.begin(115200);
    taskInit();
}
//------INTERNAL-----
}  // namespace sm
