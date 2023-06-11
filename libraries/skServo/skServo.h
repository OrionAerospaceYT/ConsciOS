#pragma once 

#include "sk_servo.h"
#include "utility.h"
#include "pin_mapping.h"
#include "multiplexer.h"
#include <Wire.h>



// im not sure if this is dumb but it feels dumb 
    Multiplexer* multi = new Multiplexer();
    sk_servo S0 = sk_servo(multi);
    sk_servo S1 = sk_servo(multi);
    sk_servo S2 = sk_servo(multi);
    sk_servo S3 = sk_servo(multi);
    sk_servo S4 = sk_servo(multi);
    sk_servo S5 = sk_servo(multi);
    sk_servo S6 = sk_servo(multi);
    sk_servo S7 = sk_servo(multi);
    sk_servo S8 = sk_servo(multi);
    sk_servo S9 = sk_servo(multi);
    sk_servo S10 = sk_servo(multi);
    sk_servo S11 = sk_servo(multi);

        //S0.attach(PS0);
        //S1.attach(PS1);
        //S2.attach(PS2);
        //S3.attach(PS3);
        //S4.attach(PS4);
        //S5.attach(PS5);
        //S6.attach(PS6);
        //S7.attach(PS7);
        //S8.attach(PS8);
        //S9.attach(PS9);
        //S10.attach(PS10);
        //S11.attach(PS11);