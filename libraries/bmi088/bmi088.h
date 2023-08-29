#pragma once

#include "utility.h"
#include "bmi_definitions.h"
#include <Wire.h>
// Thanks to Seed studio for their library which this is heavily influenced by
// https://github.com/Seeed-Studio/Grove_6Axis_Accelerometer_And_Gyroscope_BMI088/blob/master/BMI088.h


struct bmi{
    float accRange = 0.0f;
    float gyroRange = 0.0f;
    bmi(){
        //setAccScaleRange(RANGE_6G);
        //setAccOutputDataRate(ODR_100);
        //setAccPoweMode(ACC_ACTIVE);

        //setGyroScaleRange(RANGE_2000);
        //setGyroOutputDataRate(ODR_2000_BW_532);
        //setGyroPoweMode(GYRO_NORMAL); 
        PRINTLN("coom");
    }

    //void resetAcc(void) {
        //internal::writeByte(&Wire,ACC, BMI088_ACC_SOFT_RESET, 0xB6);
    //}

    //void resetGyro(void) {
        //internal::writeByte(&Wire,GYRO, BMI088_GYRO_SOFT_RESET, 0xB6);
    //}

    //void setAccPoweMode(acc_power_type_t mode) {
        //if (mode == ACC_ACTIVE) {
            //internal::writeByte(&Wire,ACC, BMI088_ACC_PWR_CTRl, 0x04);
            //internal::writeByte(&Wire,ACC, BMI088_ACC_PWR_CONF, 0x00);
        //} else if (mode == ACC_SUSPEND) {
            //internal::writeByte(&Wire,ACC, BMI088_ACC_PWR_CONF, 0x03);
            //internal::writeByte(&Wire,ACC, BMI088_ACC_PWR_CTRl, 0x00);
        //}
    //}

    //void setGyroPoweMode(gyro_power_type_t mode) {
        //if (mode == GYRO_NORMAL) {
            //internal::writeByte(&Wire, GYRO, BMI088_GYRO_LPM_1, (uint8_t)GYRO_NORMAL);
        //} else if (mode == GYRO_SUSPEND) {
            //internal::writeByte(&Wire, GYRO, BMI088_GYRO_LPM_1, (uint8_t)GYRO_SUSPEND);
        //} else if (mode == GYRO_DEEP_SUSPEND) {
            //internal::writeByte(&Wire, GYRO, BMI088_GYRO_LPM_1, (uint8_t)GYRO_DEEP_SUSPEND);
        //}
    //}

    //void setAccScaleRange(acc_scale_type_t range) {
        //if (range == RANGE_3G) {
            //accRange = 3000;
        //} else if (range == RANGE_6G) {
            //accRange = 6000;
        //} else if (range == RANGE_12G) {
            //accRange = 12000;
        //} else if (range == RANGE_24G) {
            //accRange = 24000;
        //}
        //PRINTLN("COOMIEEE")
        //internal::writeByte(&Wire,ACC, BMI088_ACC_RANGE, (uint8_t)range);
    //}

    //void setAccOutputDataRate(acc_odr_type_t odr) {
        //uint8_t data = 0;

        //data = internal::readByte(&Wire,ACC, BMI088_ACC_CONF);
        //data = data & 0xf0;
        //data = data | (uint8_t)odr;

        //internal::writeByte(&Wire,ACC, BMI088_ACC_CONF, data);
    //}

    //void setGyroScaleRange(gyro_scale_type_t range) {
        //if (range == RANGE_2000) {
            //gyroRange = 2000;
        //} else if (range == RANGE_1000) {
            //gyroRange = 1000;
        //} else if (range == RANGE_500) {
            //gyroRange = 500;
        //} else if (range == RANGE_250) {
            //gyroRange = 250;
        //} else if (range == RANGE_125) {
            //gyroRange = 125;
        //}

        //auto test = internal::writeByte(&Wire,GYRO, BMI088_GYRO_RANGE, (uint8_t)range);
        //PRINTLN(test);
    //}

    //void setGyroOutputDataRate(gyro_odr_type_t odr) {
        //internal::writeByte(&Wire,GYRO, BMI088_GYRO_BAND_WIDTH, (uint8_t)odr);
    //}

};