#pragma once 

#include "pin_mapping.h"

#define MODE1 0x00
#define ADDR 0x40 // Address of PCA
#define RESTART 0x80
#define MODE2 0x01



struct Multiplexer{

    TwoWire *bus;
    Multiplexer() : bus(&Wire) {}
     
    void begin(){
        bus->begin();
        reset();
    }

    void reset(){
        internal::writeByte<TwoWire>(bus,ADDR,MODE1,RESTART);
    }

    uint8_t setPWM(uint8_t pin, uint16_t start, uint16_t end){
        bus->beginTransmission(MODE1);
        bus->write(start);
        bus->write(start >> 8);
        bus->write(end);
        bus->write(end >> 8);
        return bus->endTransmission();
    }

    void writeMicroseconds(uint8_t num, uint16_t microseconds){
        float pulse = microseconds;
        float pulse_length = 1000000.0f;
        pulse /= pulse_length;
        setPWM(num,0,pulse);
    }

};
