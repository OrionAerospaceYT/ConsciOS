#pragma once

#include <Wire.h>
#include "utility.h"

struct Timer {
    uint32_t cycles = 0;
    uint32_t start_t = 0;
    uint32_t finish_t = 0;
    float delta_t = 0;

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
