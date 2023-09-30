#pragma once


#define BMP280_ADDRESS 0x76 
#define BMP280_CHIPID 0x58 

#define BMP280_REGISTER_DIG_T1  0x88
#define BMP280_REGISTER_DIG_T2  0x8A
#define BMP280_REGISTER_DIG_T3  0x8C
#define BMP280_REGISTER_DIG_P1  0x8E
#define BMP280_REGISTER_DIG_P2  0x90
#define BMP280_REGISTER_DIG_P3  0x92
#define BMP280_REGISTER_DIG_P4  0x94
#define BMP280_REGISTER_DIG_P5  0x96
#define BMP280_REGISTER_DIG_P6  0x98
#define BMP280_REGISTER_DIG_P7  0x9A
#define BMP280_REGISTER_DIG_P8  0x9C
#define BMP280_REGISTER_DIG_P9  0x9E
#define BMP280_REGISTER_CHIPID  0xD0
#define BMP280_REGISTER_VERSION  0xD1
#define BMP280_REGISTER_SOFTRESET  0xE0
#define BMP280_REGISTER_CAL26  0xE1
#define BMP280_REGISTER_STATUS  0xF3
#define BMP280_REGISTER_CONTROL  0xF4
#define BMP280_REGISTER_CONFIG  0xF5
#define BMP280_REGISTER_PRESSUREDATA  0xF7
#define BMP280_REGISTER_TEMPDATA  0xFA

enum sensor_sampling {
    /** No over-sampling. */
    SAMPLING_NONE = 0x00,
    /** 1x over-sampling. */
    SAMPLING_X1 = 0x01,
    /** 2x over-sampling. */
    SAMPLING_X2 = 0x02,
    /** 4x over-sampling. */
    SAMPLING_X4 = 0x03,
    /** 8x over-sampling. */
    SAMPLING_X8 = 0x04,
    /** 16x over-sampling. */
    SAMPLING_X16 = 0x05
  };

  /** Operating mode for the sensor. */
  enum sensor_mode {
    /** Sleep mode. */
    MODE_SLEEP = 0x00,
    /** Forced mode. */
    MODE_FORCED = 0x01,
    /** Normal mode. */
    MODE_NORMAL = 0x03,
    /** Software reset. */
    MODE_SOFT_RESET_CODE = 0xB6
  };

  /** Filtering level for sensor data. */
  enum sensor_filter {
    /** No filtering. */
    FILTER_OFF = 0x00,
    /** 2x filtering. */
    FILTER_X2 = 0x01,
    /** 4x filtering. */
    FILTER_X4 = 0x02,
    /** 8x filtering. */
    FILTER_X8 = 0x03,
    /** 16x filtering. */
    FILTER_X16 = 0x04
  };

  /** Standby duration in ms */
  enum standby_duration {
    /** 1 ms standby. */
    STANDBY_MS_1 = 0x00,
    /** 62.5 ms standby. */
    STANDBY_MS_63 = 0x01,
    /** 125 ms standby. */
    STANDBY_MS_125 = 0x02,
    /** 250 ms standby. */
    STANDBY_MS_250 = 0x03,
    /** 500 ms standby. */
    STANDBY_MS_500 = 0x04,
    /** 1000 ms standby. */
    STANDBY_MS_1000 = 0x05,
    /** 2000 ms standby. */
    STANDBY_MS_2000 = 0x06,
    /** 4000 ms standby. */
    STANDBY_MS_4000 = 0x07
  };

// Struct to store calibration values
struct bmp280_calib_data{
  uint16_t dig_T1;
  int16_t dig_T2;  
  int16_t dig_T3; 

  uint16_t dig_P1;
  int16_t dig_P2; 
  int16_t dig_P3; 
  int16_t dig_P4; 
  int16_t dig_P5; 
  int16_t dig_P6; 
  int16_t dig_P7; 
  int16_t dig_P8; 
  int16_t dig_P9; 

  void display_calibs(){
    PRINT(dig_T1);
    PRINT(",");
    PRINT(dig_T2);
    PRINT(",");
    PRINT(dig_T3);

    //PRINT(",");
    //PRINT(dig_P1);
    //PRINT(",");
    //PRINT(dig_P2);
    //PRINT(",");
    //PRINT(dig_P3);
    //PRINT(",");
    //PRINT(dig_P4);
    //PRINT(",");
    //PRINT(dig_P5);
    //PRINT(",");
    //PRINT(dig_P6);
    //PRINT(",");
    //PRINT(dig_P7);
    //PRINT(",");
    //PRINT(dig_P8);
    //PRINT(",");
    //PRINT(dig_P9);
    END_LOG;
  }
};

struct config {
    /** Initialize to power-on-reset state */
    config() : t_sb(STANDBY_MS_1), filter(FILTER_OFF), none(0), spi3w_en(0) {}
    /** Inactive duration (standby time) in normal mode */
    unsigned int t_sb : 3;
    /** Filter settings */
    unsigned int filter : 3;
    /** Unused - don't set */
    unsigned int none : 1;
    /** Enables 3-wire SPI */
    unsigned int spi3w_en : 1;
    /** Used to retrieve the assembled config register's byte value. */
    unsigned int get() { return (t_sb << 5) | (filter << 2) | spi3w_en; }
};

struct ctrl_meas {
    /** Initialize to power-on-reset state */
    ctrl_meas()
        : osrs_t(SAMPLING_NONE), osrs_p(SAMPLING_NONE), mode(MODE_SLEEP) {}
    /** Temperature oversampling. */
    unsigned int osrs_t : 3;
    /** Pressure oversampling. */
    unsigned int osrs_p : 3;
    /** Device mode */
    unsigned int mode : 2;
    /** Used to retrieve the assembled ctrl_meas register's byte value. */
    unsigned int get() { return (osrs_t << 5) | (osrs_p << 2) | mode; }
  };



