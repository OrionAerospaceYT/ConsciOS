#pragma once 


#include <Wire.h>
// Single Include for Stem related libraries

#ifdef ARDUINO_ARCH_RP2040
extern arduino::MbedI2C sk_internal_bus(6u, 7u);
#endif




