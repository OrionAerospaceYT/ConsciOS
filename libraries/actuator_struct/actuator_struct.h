#pragma once
#include "array.h"

// this is a little too geared towards servos at the moment... will need to do
// more testing with other actuator types assert that size > 1
template <typename T, size_t Size>
struct ActuatorGroup : Array<T,Size> {
    Array<T,Size> a;
    float smooth_write_interp;
    float init_value;
    template <typename ...Args>
    explicit constexpr ActuatorGroup(const Args&... args) : a{args...} {}

    void writeAll(int pos) {
            for (auto i = 0; i < Size; ++i){
                 a.data[i].write(pos);
            }
    }
    void write(int actuator_number, int pos){
        a.data[actuator_number].write(pos);
    }

    void attach(Array<int,Size> pins){
        for(auto i = 0; i < Size; ++i){
            a.data[i].attach(pins[i]);
        }
    }

    void attach(int p1, int p2) {
        a.data[0].attach(p1);
        a.data[1].attach(p2);
    }
};
