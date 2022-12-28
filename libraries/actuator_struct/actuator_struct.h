#pragma once
#include "array.h"

// this is a little too geared towards servos at the moment... will need to do
// more testing with other actuator types assert that size > 1
template <typename T, size_t Size>
<<<<<<< HEAD
struct ActuatorGroup : Array<T, Size> {
    Array<T, Size> a;
    template <typename... Args>
    explicit constexpr ActuatorGroup(const Args &...args) {
        a = {args...};
    }
    void writeAll(int pos) {
        for (auto i = 0; i < Size; ++i) {
            a.data[i].write(pos);
=======
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
    bool smoothWrite(int actuator_number, int pos, float number_of_interps){
        //check if desired range has been completed 
        if(!smooth_complete){
            auto increment = :wq / number_of_interps;
            smooth_write_interp += increment;
            auto output = sk_math::SMOOTHLERP()
        }
    }

    void attach(int* pins){
	//assert pins length = array size (i.e each actuator must have pin)
	for(auto i = 0; i < Size; ++i){
		a.data[i].attach(*(pins + i));
	    }
    }
    void attach(Array<int,Size> pins){
        for(auto i = 0; i < Size; ++i){
            a.data[i].attach(pins[i]);
>>>>>>> a997c9e (changed filters.h from template to float quickly)
        }
    }
    // add assert
    void write(int actuator_number, int pos) {
        a.data[actuator_number].write(pos);
    }
    void attach(int *pins) {
        // assert pins length = array size (i.e each actuator must have pin)
        for (auto i = 0; i < Size; ++i) {
            a.data[i].attach(*(pins + i));
        }
    }
    void attach(int p1, int p2) {
        a.data[0].attach(p1);
        a.data[1].attach(p2);
    }
    // repeated code probably bad
    void attach(int p1, int p2, int p3) {
        a.data[0].attach(p1);
        a.data[1].attach(p2);
        a.data[2].attach(p3);
    }
};
