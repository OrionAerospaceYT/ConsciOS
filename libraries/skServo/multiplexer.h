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

struct Multiplexer{

    arduino::MbedI2C bus = arduino::MbedI2C(8,9);
    Multiplexer(){
        begin();
    }
     
    void begin(){
        this->bus.begin();
        reset();
    }

    void reset(){
        internal::writeByte(this->bus,ADDR,MODE1,RESTART);
    }

    int readPrescale(){
        return internal::readByte(this->bus,ADDR,PRESCALE);
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
        int oldmode = internal::readByte(bus,ADDR, MODE1);
        int newmode = (oldmode & RESTART) | SLEEP;
        internal::writeByte(bus,ADDR,MODE1,newmode);
        internal::writeByte(bus,ADDR,PRESCALE,prescale);
        internal::writeByte(bus,ADDR,MODE1,oldmode);
        delay(5); //idk if i like this but its in the adafruit docu 
        internal::writeByte(bus,ADDR,MODE1,oldmode | RESTART | AI);
    }

    int setPWM(int pin, int start, int end){
        this->bus.beginTransmission(ADDR);
        this->bus.write(0x06 + 4 * pin);
        this->bus.write(start);
        this->bus.write(start >> 8);
        this->bus.write(end);
        this->bus.write(end >> 8);
        return this->bus.endTransmission();
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
