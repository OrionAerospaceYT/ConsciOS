#pragma once
#include <Wire.h>
#include "utility.h"

struct Timer {
    float cycles = 0;
    float t_start = 0;
    float t_finish = 0;

    Timer() {}
    void start() { t_start = micros(); }
    void stop() { t_finish = micros(); }
    float deltaT() {
        if (t_finish == 0) {
            stop();
        }
        return (t_start - t_finish) / 1000000.0f;
    }
    void count() { cycles++; }
    float getDeltaT() {
        start();
        float delta_t = deltaT();
        stop();
        return delta_t;
     }
    float getCycles() { return cycles; }
    float getUpTime() { return micros() / 1000000.0; }
    float getTime() { return (micros() - t_start) / 1000000.0; }
};
