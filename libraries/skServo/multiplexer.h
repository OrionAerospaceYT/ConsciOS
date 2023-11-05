#pragma once 

#include "pin_mapping.h"
#include <Wire.h>

#define MODE1 0x00
#define ADDR 0x40 // Address of PCA
#define RESTART 0x80
#define MODE2 0x01
#define OSCILLATOR 25000000
#define MULTI_MIN 3
#define MULTI_MAX 255
#define PRESCALE 0xFE
#define SLEEP 0x10
#define AI 0x20

//Stem include wrapper 
// NOTE: Not robust for regualr pico compiles
#ifdef ARDUINO_ARCH_RP2040
#include "stem.h"
#endif

struct Multiplexer{
    Multiplexer(){}
     
    void begin(){
        reset();
    }

    void reset(){
        auto check = internal::writeByte(&sk_internal_bus,ADDR,MODE1,RESTART);
    }

    int readPrescale(){
        return internal::readByte(&sk_internal_bus,ADDR,PRESCALE);
    }

    void setPWMFreq(float freq){
        if(freq < 1)
            freq = 1;
        if(freq > 3500)
            freq = 3500;
        float prescale_eval = ((OSCILLATOR / (freq * 4096.0)) + 0.5) - 1;
        if(prescale_eval < MULTI_MIN)
            prescale_eval = MULTI_MIN;
        if(prescale_eval > MULTI_MAX)
            prescale_eval = MULTI_MAX;
        int prescale = int(prescale_eval);
        int oldmode = internal::readByte(&sk_internal_bus,ADDR, MODE1);
        int newmode = (oldmode & RESTART) | SLEEP;
        internal::writeByte(&sk_internal_bus,ADDR,MODE1,newmode);
        internal::writeByte(&sk_internal_bus,ADDR,PRESCALE,prescale);
        internal::writeByte(&sk_internal_bus,ADDR,MODE1,oldmode);
        delay(5); //idk if i like this but its in the adafruit docu 
        internal::writeByte(&sk_internal_bus,ADDR,MODE1,oldmode | RESTART | AI);
    }

    int setPWM(int pin, int start, int end){
        sk_internal_bus.beginTransmission(ADDR);
        sk_internal_bus.write(0x06 + 4 * pin);
        sk_internal_bus.write(start);
        sk_internal_bus.write(start >> 8);
        sk_internal_bus.write(end);
        sk_internal_bus.write(end >> 8);
        sk_internal_bus.endTransmission();
    }

    void writeMicroseconds(int num, float microseconds){
        float pulse_length = 1000000.0f;
        int prescale = readPrescale();
        prescale += 1;
        pulse_length *= prescale;
        pulse_length /= float(OSCILLATOR);
        float out  = microseconds / pulse_length;
        //need to include prescale i think
        setPWM(num,0,out);
    }

};
