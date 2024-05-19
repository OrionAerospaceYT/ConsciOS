#pragma once

#include <Wire.h>
#include "utility.h"

struct Timer {
    float cycles = 0;
    float t_start = 0;
    float t_finish = 0;

    Timer() {}
    void start() { start_t = micros(); }
    void stop() { finish_t = micros(); }
    float deltaT() {
        if (finish_t == 0) {
            stop();
        }
        return (finish_t - start_t) / 1000000.0f;
    }
    void count() { cycles++; }
    uint32_t getCycles() { return cycles; }
    uint32_t getUpTime() { return micros() / 1000000.0; }
    uint32_t getTime() { return (micros() - start_t) / 1000000.0; }
};
