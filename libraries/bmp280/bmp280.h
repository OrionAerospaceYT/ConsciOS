#pragma once

#include "utility.h"
#include "bmp_definitions.h"

#include "stem.h"


// Thanks to adafruit for their opensource bmp library which this uses elements of
//

struct Baro{

    Baro(){}
    bmp280_calib_data bmp280_calib;
    config configReg;
    ctrl_meas measReg;
    int32_t t_fine = 0;
    float sea_level_pres = 1013.25; // default value
    float ground_level_alt = 0;

    void begin(){
        delay(1000);
        readCalib();
        setSampling();

    }

    void readCalib(){

        bmp280_calib.dig_T1 = read16_LE(BMP280_REGISTER_DIG_T1);
        bmp280_calib.dig_T2 = readS16_LE(BMP280_REGISTER_DIG_T2);
        bmp280_calib.dig_T3 = readS16_LE(BMP280_REGISTER_DIG_T3);

        bmp280_calib.dig_P1 = read16_LE(BMP280_REGISTER_DIG_P1);
        bmp280_calib.dig_P2 = readS16_LE(BMP280_REGISTER_DIG_P2);
        bmp280_calib.dig_P3 = readS16_LE(BMP280_REGISTER_DIG_P3);
        bmp280_calib.dig_P4 = readS16_LE(BMP280_REGISTER_DIG_P4);
        bmp280_calib.dig_P5 = readS16_LE(BMP280_REGISTER_DIG_P5);
        bmp280_calib.dig_P6 = readS16_LE(BMP280_REGISTER_DIG_P6);
        bmp280_calib.dig_P7 = readS16_LE(BMP280_REGISTER_DIG_P7);
        bmp280_calib.dig_P8 = readS16_LE(BMP280_REGISTER_DIG_P8);
        bmp280_calib.dig_P9 = readS16_LE(BMP280_REGISTER_DIG_P9);

    }

    void setSampling(sensor_mode mode = MODE_NORMAL,sensor_sampling tempSampling = SAMPLING_X16,sensor_sampling pressSampling = SAMPLING_X16,
                    sensor_filter filter = FILTER_OFF,standby_duration duration = STANDBY_MS_1) {

        measReg.mode = mode;
        measReg.osrs_t = tempSampling;
        measReg.osrs_p = pressSampling;

        configReg.filter = filter;
        configReg.t_sb = duration;

        auto check = internal::writeByte(&sk_internal_bus, BMP280_ADDRESS, BMP280_REGISTER_CONFIG, configReg.get());
        sk_assert(check != 0 ,"INIT OF ONBOARD PRESSURE SENSOR FAILED");
        internal::writeByte(&sk_internal_bus, BMP280_ADDRESS, BMP280_REGISTER_CONTROL, measReg.get());

    }

    float setSeaLevel(float altitude, float atmospheric){
        sea_level_pres = atmospheric / pow(1.0 - (altitude / 44330.0), 5.255);
        return sea_level_pres;
    }

    float getAlt(){
        float pressure = getPres(); 
        pressure /= 100;

        float altitude = 44330 * (1.0 - pow(pressure / sea_level_pres, 0.1903));

        return altitude;
    }


    float setGroundLevel(){
        ground_level_alt = getAlt();
        return ground_level_alt;
    }

    float getAGL(){
        float pressure = getPres(); 
        pressure /= 100;

        float altitude = 44330 * (1.0 - pow(pressure / sea_level_pres, 0.1903));

        return altitude - ground_level_alt;
    }

   // returns temp in celsius
   float getTemp() {
        int32_t var1 = 0;
        int32_t var2 = 0;
        int32_t adc_T = read24(BMP280_REGISTER_TEMPDATA);
        adc_T >>= 4;
        var1 = ((((adc_T >> 3) - ((int32_t)bmp280_calib.dig_T1 << 1))) *
                ((int32_t)bmp280_calib.dig_T2)) >>
                11;     
        var2 = (((((adc_T >> 4) - ((int32_t)bmp280_calib.dig_T1)) *
                    ((adc_T >> 4) - ((int32_t)bmp280_calib.dig_T1))) >>
                12) *
                ((int32_t)bmp280_calib.dig_T3)) >>
                14;
        t_fine = var1 + var2;
        float T = (t_fine * 5 + 128) >> 8;
        return T / 100.0f;
    } 

    float getPres() {
        int64_t var1, var2, p;
        getTfine(); 
        int32_t adc_P = read24(BMP280_REGISTER_PRESSUREDATA);
        adc_P >>= 4;

        var1 = ((int64_t)t_fine) - 128000;
        var2 = var1 * var1 * (int64_t)bmp280_calib.dig_P6;
        var2 = var2 + ((var1 * (int64_t)bmp280_calib.dig_P5) << 17);
        var2 = var2 + (((int64_t)bmp280_calib.dig_P4) << 35);
        var1 = ((var1 * var1 * (int64_t)bmp280_calib.dig_P3) >> 8) +
                ((var1 * (int64_t)bmp280_calib.dig_P2) << 12);
        var1 =
            (((((int64_t)1) << 47) + var1)) * ((int64_t)bmp280_calib.dig_P1) >> 33;

        if (var1 == 0) {
            return 0; 
        }
        p = 1048576 - adc_P;
        p = (((p << 31) - var2) * 3125) / var1;
        var1 = (((int64_t)bmp280_calib.dig_P9) * (p >> 13) * (p >> 13)) >> 25;
        var2 = (((int64_t)bmp280_calib.dig_P8) * p) >> 19;

        p = ((p + var1 + var2) >> 8) + (((int64_t)bmp280_calib.dig_P7) << 4);
        return (float)p / 256;
    }



    // just removes the last line of compute super marginal but saves that little extra
    void getTfine(){
        int32_t var1 = 0;
        int32_t var2 = 0;
        int32_t adc_T = read24(BMP280_REGISTER_TEMPDATA);
        adc_T >>= 4;
        var1 = ((((adc_T >> 3) - ((int32_t)bmp280_calib.dig_T1 << 1))) *
                ((int32_t)bmp280_calib.dig_T2)) >>
                11;     
        var2 = (((((adc_T >> 4) - ((int32_t)bmp280_calib.dig_T1)) *
                    ((adc_T >> 4) - ((int32_t)bmp280_calib.dig_T1))) >>
                12) *
                ((int32_t)bmp280_calib.dig_T3)) >>
                14;
        t_fine = var1 + var2;
    }

    void reset(){
        internal::writeByte(&sk_internal_bus,BMP280_ADDRESS,BMP280_REGISTER_SOFTRESET, MODE_SOFT_RESET_CODE);
    }

    int16_t read16_LE(uint8_t reg)
    {
        uint16_t value;

        value = read16(reg);

        return (value >> 8) | (value << 8);
    }

    int16_t readS16_LE(uint8_t reg){
        return (int16_t)read16_LE(reg);
    }

    uint16_t read16(uint8_t reg){
        sk_internal_bus.beginTransmission(BMP280_ADDRESS);
        sk_internal_bus.write(reg);
        if (sk_internal_bus.endTransmission() != 0) {
            return 0;
        }
        sk_internal_bus.requestFrom(BMP280_ADDRESS, (byte)2);
        return (sk_internal_bus.read() << 8) | sk_internal_bus.read();
    }

    uint32_t read24(uint8_t reg){
        uint32_t value;

        sk_internal_bus.beginTransmission(BMP280_ADDRESS);
        sk_internal_bus.write(reg);
        sk_internal_bus.endTransmission();
        sk_internal_bus.requestFrom(BMP280_ADDRESS, (byte)3);

        value = sk_internal_bus.read();
        value <<= 8;
        value |= sk_internal_bus.read();
        value <<= 8;
        value |= sk_internal_bus.read();

        return value;
    }

};