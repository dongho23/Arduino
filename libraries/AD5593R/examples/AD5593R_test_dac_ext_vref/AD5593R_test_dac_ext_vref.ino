//
//    FILE: AD5593R_test_dac_ext_vref.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: demo
//     URL: https://github.com/RobTillaart/AD5593R
//
//  outputs should have different output voltage
//  from zero to full scale in 8 steps.
//  connect a constant voltage (e.g. 3V) to EXT_REF pin

#include "AD5593R.h"
#include "Wire.h"

AD5593R AD(0x10);


void setup()
{
  while(!Serial);
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("AD5593R_LIB_VERSION: ");
  Serial.println(AD5593R_LIB_VERSION);
  Serial.println();

  Wire.begin();

  //  set all eight pins to DAC mode.
  AD.setDACmode(0xFF);
  //  use external reference
  AD.setExternalReference(true, 3.3);
  //  do not double the output.
  AD.setDACRange2x(false);
  //  COPY input register direct to DAC
  //  must be set after setExternalReference()
  AD.setLDACmode(AD5593R_LDAC_DIRECT);
}


void loop()
{
  for (int pin = 0; pin < 8; pin++)
  {
    Serial.print(AD.writeDAC(pin, (pin * 4095)/7 ));
    Serial.print("\t");
  }
  Serial.println();
  delay(1000);
}


//  -- END OF FILE --
