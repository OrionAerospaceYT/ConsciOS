#pragma once
#include "common.h"
#include "array.h"
#include "sk_math.h"

//TODO: LOOK INTO INHERT FROM ARRAY STRUCT

//this is a little too geared towards servos at the moment... will need to do more testing with other actuator types 
//assert that size > 1
template <typename T, size_t Size>
struct ActuatorGroup : Array<T,Size> {
    Array<T,Size> a;
    float smooth_write_interp;
    float init_value;
    template <typename ...Args>
    constexpr ActuatorGroup(const Args&... args) : a{args...} {}
    void writeAll(int pos) {
            for (auto i = 0; i < Size; ++i){
                 a.data[i].write(pos);
            }
    }
    void write(int actuator_number, int pos){
        a.data[actuator_number].write(pos);
    }

    //Servo Only 
    void smoothWrite(int actuator_number, int pos, int number_of_interps){
        float increment = 1.0 / float(number_of_interps); 
        if(smooth_write_interp == 0){
            init_value = a.data[actuator_number].read();
        }
        auto current_pos = sk_math::SMOOTLERP(init_value, float(pos), smooth_write_interp); 
        smooth_write_interp += increment;
        a.data[actuator_number].write(current_pos);
        if(smooth_write_interp > 1.0){
            smooth_write_interp = 0;
        }
    }

    void attach(int* pins){
	//assert pins length = array size (i.e each actuator must have pin)
	for(auto i = 0; i < Size; ++i){
		a.data[i].attach(*(pins + i));
	}
    }
    void attach(int p1, int p2){
        a.data[0].attach(p1);
        a.data[1].attach(p2);
    }
    //repeated code probably bad
    void attach(int p1, int p2, int p3){
        a.data[0].attach(p1);
        a.data[1].attach(p2);
        a.data[2].attach(p3);
    }
};
