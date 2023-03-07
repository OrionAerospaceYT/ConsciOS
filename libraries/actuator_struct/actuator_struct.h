#pragma once
#include "array.h"
#include "sk_math.h"

#define SMOOTH 1
#define LINEAR 0
// this is a little too geared towards servos at the moment... will need to do
// more testing with other actuator types assert that size > 1
template <typename T, size_t Size>
struct ActuatorGroup : Array<T,Size> {
    Array<T,Size> a;
    float smooth_start = 0;
    float current_smooth = 0;
    float smooth_max = 0;
    float increment = 0;
    template <typename ...Args>
    explicit  ActuatorGroup(const Args&... args) : a{args...} {}

    void writeAll(int pos) {
            for (auto i = 0; i < Size; ++i){
                 a.data[i].write(pos);
            }
    }
    void write(int actuator_number, int pos){
        a.data[actuator_number].write(pos);
    }
    void write(int* values){
        for(auto i = 0; i < Size; ++i){
            a.data[i].write(values[i]);
        }
    }
    // This function must be called to enable lerpWrite
    // Parameters include the starting position, end position, and the number of interpolation steps to take
    void initLerp(float start, float end, float interp_points){
        this->smooth_start = start;
        this->smooth_max = end;
        this->increment = (smooth_max - smooth_start)/interp_points;
    }

    // actuator_number is the actuator to move and type is the type of interpolation to use
    bool lerpWrite(int actuator_number,int type){
        float interp_point = sk_math::MAP(current_smooth,smooth_start,smooth_max,0.0f,1.0f);
        float output = 0.0f;
        if(type == 0){
            output = sk_math::LERP(smooth_start,smooth_max,interp_point);
        }
        if(type == 1){
            output = sk_math::SMOOTHLERP(smooth_start,smooth_max,interp_point);
        }
        if(sk_math::ISCLOSE(output,smooth_max,0.001f)){
            return true;
        }
        current_smooth += increment;
        a.data[actuator_number].write(output);
        GRAPH("lerp",output,TOP);
        return false;
    }
    void attach(int* pins){
        for(auto i = 0; i < Size; ++i){
            a.data[i].attach((pins[i]));
        }
    }
    void attach(int p1){
        a.data[0].attach(p1);
    }
    void attach(int p1, int p2) {
        a.data[0].attach(p1);
        a.data[1].attach(p2);
    }
};
