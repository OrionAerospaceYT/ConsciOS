#pragma once 

#include "utility.h"
#include "Wire.h"
#include "sk_math.h"
#include "multiplexer.h"
#include <mbed.h>

/* NOTE: I'm breaking naming convention with this file 
         to make it swappable with Servo
*/

/*
    A large portion of this library is code modified 
    from the Adafruit-PWM-Servo-Driver-Library 
    Thanks to them for their contributions to
    the open source community :) 


    Internal Library for the PCA96585 PWM multiplexer    
*/

// Serves as an interface between normal Servo usage and the internal STEM

// User calls skServo to create a Servo object just like normal
// skServo myServo;
// myServo.attach(S1);

//no ignore all this

//user includes "skServo.h"
//automatically creates 12 servos from s1-s12
//user can add limits for each servo S1.limits()
//S1.write(value); calls the multiplexer in the background and interprets

#define _Nbr_16timers 32

#define OSCILLATOR 25000000
#define MIN_PULSE_WIDTH       544     // the shortest pulse sent to a servo  
#define MAX_PULSE_WIDTH      2400     // the longest pulse sent to a servo 
#define DEFAULT_PULSE_WIDTH  1500     // default pulse width when servo is attached
#define REFRESH_INTERVAL    20000     // minimum time to refresh servos in microseconds 

#define SERVOS_PER_TIMER       12     // the maximum number of servos controlled by one timer 
#define MAX_SERVOS   (_Nbr_16timers  * SERVOS_PER_TIMER)

#define INVALID_SERVO         255     // flag indicating an invalid servo index



#if !defined __has_include
#  if __has_include ("Servo.h")
#    include "Servo.h"
#  else
typedef struct  {
  uint8_t nbr        :6 ;             // a pin number from 0 to 63
  uint8_t isActive   :1 ;             // true if this channel is enabled, pin not pulsed if false 
} ServoPin_t   ;  

typedef struct {
  ServoPin_t Pin;
  volatile unsigned int ticks;
} servo_t;
#  endif
#endif

#if defined __has_include
#  if __has_include ("pinDefinitions.h")
#    include "pinDefinitions.h"
#  endif
#endif

class skServoImpl {
    mbed::DigitalOut   *pin;
    mbed::Timeout      timeout;  // calls a callback once when a timeout expires
    mbed::Ticker       ticker;   // calls a callback repeatedly with a timeout

public:
    explicit skServoImpl(PinName _pin) {
      pin = new mbed::DigitalOut(_pin);
    }

    ~skServoImpl() {
        ticker.detach();
        timeout.detach();
        delete pin;
    }

    void start(uint32_t duration_us) {
      duration = duration_us;
      ticker.attach(mbed::callback(this, &skServoImpl::call), 0.02f);
    }

    void call() {
        timeout.attach(mbed::callback(this, &skServoImpl::toggle), duration / 1e6);
        toggle();
    }

    void toggle() {
      *pin = !*pin;
    }

    int32_t           duration = -1;
};

static skServoImpl* servos[12];                      // static array of servo structures
uint8_t sk_servoCount = 0;                                    // the total number of attached servos

#define TRIM_DURATION   15      
// From Arduino Servo Library
#define SERVO_MIN() (MIN_PULSE_WIDTH - this->min)   // minimum value in us for this servo
#define SERVO_MAX() (MAX_PULSE_WIDTH - this->max)   // maximum value in us for this servo

// Breaking lint convention for ease of use
struct skServo{
    int min = MIN_PULSE_WIDTH;
    int max = MAX_PULSE_WIDTH;
    int servoIndex = 0;
    int pin = -1;
    Multiplexer multi = Multiplexer();
    skServo(){
        if (sk_servoCount < MAX_SERVOS) {
            this->servoIndex = sk_servoCount++;
        } else {
            this->servoIndex = INVALID_SERVO;  // too many servos
        }
    }

    void setFreq(float frequency){
        multi.setPWMFreq(frequency);
    }
    

    int attach(int pin){
        //Check if pin has tried to be re-assigned
        //sk_servo will only every be assigned internally so we reject re assings
        if(this->pin != -1){
            PRINT("Can't re-assign sk_servo pins");
            return this->pin;
        }
        multi.begin(); // adding this in as attach is kind of servo begin call 
        this->pin = pin;
        multi.setPWMFreq(50);
        return this->pin;
    }  

    void limits(int min, int max){
        this->min = MIN_PULSE_WIDTH - min;
        this->max = MAX_PULSE_WIDTH - max;
    }

    // From Arduino Servo Library
    void write(int value)
    {
    // treat values less than 544 as angles in degrees (valid values in microseconds are handled as microseconds)
        if (value < MIN_PULSE_WIDTH)
        {
            if (value < 0){
                value = 0;
            }
            else if (value > 180){
                value = 180;
            }
        value = map(value, 0, 180, this->min, this->max);
        }
        multi.writeMicroseconds(pin,value);
    }

    void writeMicroseconds(int value)
    {
        if (!servos[this->servoIndex]) {
            return;
        }
        // calculate and store the values for the given channel
        byte channel = this->servoIndex;
        if( (channel < MAX_SERVOS) )   // ensure channel is valid
        {
            if (value < SERVO_MIN())          // ensure pulse width is valid
            value = SERVO_MIN();
            else if (value > SERVO_MAX())
            value = SERVO_MAX();

            value = value - TRIM_DURATION;
            if (servos[this->servoIndex]->duration == -1) {
            servos[this->servoIndex]->start(value);
            }
            servos[this->servoIndex]->duration = value;
        }
    }
};