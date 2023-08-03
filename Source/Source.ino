//#include "internal.h"
#include <Wire.h>
#include "utility.h"

TwoWire wire1(6u,7u);

void setup(){
  Wire.begin();
  wire1.begin();
  Serial.begin(115200);
  while (!Serial);             // Leonardo: wait for serial monitor
  PRINTLN("\nI2C Scanner");
}
 
 
void loop()
{
  byte error, address;
  int nDevices;
 
  PRINTLN("Scanning...");
 
  nDevices = 0;
  for(address = 1; address < 127; address++ )
  {
    // The i2c_scanner uses the return value of
    // the Write.endTransmisstion to see if
    // a device did acknowledge to the address.
    wire1.beginTransmission(address);
    Wire.beginTransmission(address);
    Wire.endTransmission();
    error = wire1.endTransmission();
 
    if (error == 0)
    {
      PRINT("I2C device found at address 0x");
      if (address<16)
        PRINT("0");
      PRINTHEX(address);
      PRINTLN("  !");
 
      nDevices++;
    }
    else if (error==4)
    {
      PRINT("Unknown error at address 0x");
      if (address<16)
        PRINT("0");
        Serial.println(address,HEX);
    }    
  }
  if (nDevices == 0){
    PRINTLN("No I2C devices found\n");
  }
  else{
    PRINTLN("done\n");
  }
  END_LOG
  delay(5000);           // wait 5 seconds for next scan
}
