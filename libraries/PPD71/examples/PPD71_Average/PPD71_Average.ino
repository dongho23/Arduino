//
//    FILE: PPD71_Average.ino
//  AUTHOR: Rob Tillaart
// PURPOSE: test basic behaviour and performance
//     URL: https://github.com/RobTillaart/PPD71


#include "PPD71.h"

PPD71 ppd(&Serial);


void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("PPD71_LIB_VERSION: ");
  Serial.println(PPD71_LIB_VERSION);
  Serial.println();

  //  wait for first data.
  delay(2000);
}


void loop()
{
  if (ppd.getData())
  {
    Serial.print(ppd.getAverage10());
    Serial.print("\t");
    Serial.print(ppd.getAverage30());
    Serial.print("\t");
    Serial.print(ppd.getAverage60());
    Serial.print("\t");
    Serial.print(ppd.getAverage180());
    Serial.print("\n");
  }
  delay(2000);
}


//  -- END OF FILE --
