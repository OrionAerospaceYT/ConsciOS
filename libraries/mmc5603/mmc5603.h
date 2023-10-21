#pragma once 

#include "utility.h"
#include "mmc_definitions.h"
#include "stem.h"
#include "vector.h"

// Thanks to Adafruit for their opensource library that elements of this are based on 
// https://github.com/adafruit/Adafruit_MMC56x3

struct Mag{
    bool continous_mode = true;
    Mag(){}

    void begin(){
        auto check = internal::writeByte(&sk_internal_bus,MMC56X3_ADDRESS,MMC56X3_CTRL1_REG, 0x80);
        sk_assert(check != 0,"INIT OF ONBOARD MAG FAILED");
        PRINTLN(check)
        delay(20);
        reset();

    }


    void reset(){
        internal::writeByte(&sk_internal_bus, MMC56X3_ADDRESS,MMC56X3_CTRL1_REG,0x80);
        magnetReset();
        setContinousRead(false);

    }
    void magnetReset(){
        auto check = internal::writeByte(&sk_internal_bus,MMC56X3_ADDRESS,MMC56X3_CTRL0_REG, 0x80);
        sk_assert(check !=0, "2");
        PRINTLN(check)
        delay(1);
        auto check2 = internal::writeByte(&sk_internal_bus,MMC56X3_ADDRESS,MMC56X3_CTRL0_REG, 0x10);
        sk_assert(check2 !=0, "3");
        PRINTLN(check2)
        delay(1);
    }

    void setContinousRead(bool mode = true){
        uint8_t ctrl2 = 0;
        if(mode){
            continous_mode = mode;
            auto check = internal::writeByte(&sk_internal_bus,MMC56X3_ADDRESS,MMC56X3_CTRL0_REG,0x80);
            sk_assert(check != 0, "4");
            PRINTLN(check)
            ctrl2 |= 0x10;
        }else{
            continous_mode = mode;
            ctrl2 &= ~0x10;
        }
        internal::writeByte(&sk_internal_bus,MMC56X3_ADDRESS,MMC56X3_CTRL2_REG,ctrl2);
    }

    Vec getMag(){
        Vec out;
        int32_t x,y,z;
        if(!continous_mode){
            internal::writeByte(&sk_internal_bus,MMC56X3_ADDRESS,MMC56X3_CTRL0_REG,0x01);
        }
        // there is a line in the adafruit lib that im skipping here

        uint8_t buffer[9];
        
        internal::read(&sk_internal_bus,MMC56X3_ADDRESS,MMC56X3_OUT_X_L,buffer,9);
        //PRINTLN(buffer[0]);

        x = (uint32_t)buffer[0] << 12 | (uint32_t)buffer[1] << 4 |
            (uint32_t)buffer[6] >> 4;
        y = (uint32_t)buffer[2] << 12 | (uint32_t)buffer[3] << 4 |
            (uint32_t)buffer[7] >> 4;
        z = (uint32_t)buffer[4] << 12 | (uint32_t)buffer[5] << 4 |
            (uint32_t)buffer[8] >> 4;

        // fix center offsets
        x -= (uint32_t)1 << 19;
        y -= (uint32_t)1 << 19;
        z -= (uint32_t)1 << 19;

        out.x = (float)x * 0.00625;
        out.y = (float)y * 0.00625;
        out.z = (float)z * 0.00625;

        return out;
    }

};