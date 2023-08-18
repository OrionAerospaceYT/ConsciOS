#pragma once
#include "array.h"
#include "sk_math.h"
#include "lerp.h"
//#include "sk_servo.h"
// this is a little too geared towards servos at the moment... will need to do
// more testing with other actuator types assert that size > 1



//make a custom case for stem servos
template <typename T, size_t Size>
struct ActuatorGroup : Array<T,Size> {

    Array<T,Size> a;
    template <typename ...Args>
    explicit  ActuatorGroup(const Args&... args){
    }

    int* readAll() {
      static int read[Size];
      for (int i=0; i<Size; i++) {
        read[i] = a[i].read();
      }
      return read;
    }

    int read(int actuator_number){
      return a[actuator_number].read();
    }

    void writeAll(int pos) {
      for (auto i = 0; i < Size; ++i){
           a.data[i].write(pos);
      }
    }

    void write(int actuator_number, int pos){
      a.data[actuator_number].write(pos);
    }

    void write(int* values){
      for(int i = 0; i < Size; ++i){
          a.data[i].write(values[i]);
      }
    }

    void attach(int* pins){
      for(int i = 0; i < Size; ++i){
          PRINT(i);
          a.data[i].attach(pins[i]);
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

//template <size_t Size>
//struct skActuatorGroup{

    //skArray<Size> a;
    //template <typename ...Args>
    //explicit  skActuatorGroup(Args&... args) : a{&args...}{}

    //int* readAll() {
      //static int read[Size];
      //for (int i=0; i<Size; i++) {
        //read[i] = a[i]->read();
      //}
      //return read;
    //}

    //int read(int actuator_number){
      //return a[actuator_number]->read();
    //}

    //void writeAll(int pos) {
      //for (auto i = 0; i < Size; ++i){
          //PRINT(a.data[i]->pin)
          //PRINT("SK:" + String(stem::S0.pin))
          //END_LOG
          //a.data[i]->write(pos);
      //}
    //}

    //void write(int actuator_number, int pos){
      //a.data[actuator_number]->write(pos);
    //}

    //void write(int* values){
      //for(int i = 0; i < Size; ++i){
          //a.data[i]->write(values[i]);
      //}
    //}

    //void attach(int* pins){
      //for(int i = 0; i < Size; ++i){
          //a.data[i]->attach(pins[i]);
      //}
    //}

    //void attach(int p1){
      //a.data[0]->attach(p1);
    //}

    //void attach(int p1, int p2) {
      //a.data[0]->attach(p1);
      //a.data[1]->attach(p2);
    //}
//};