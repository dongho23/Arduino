//
//    FILE: ADS_read_comparator_1.ino
//  AUTHOR: Rob.Tillaart
// PURPOSE: read analog inputs - straightforward.
//     URL: https://github.com/RobTillaart/ADS1X15

//  test
//  connect 1 potmeter per port.
//
//  GND ---[   x   ]------ 5V
//             |
//
//  measure at x (connect to AIN0).
//
//
//  GND ---[LED]---[ALERT_PIN]---[ R ]--- 5V
//
//  Connect a LED (+ resistor) to ALERT/RDY pin
//  and see it triggered by the comparator in the configured way.
//


#include "ADS1X15.h"

ADS1115 ADS(0x48);


void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.println(__FILE__);
  Serial.print("ADS1X15_LIB_VERSION: ");
  Serial.println(ADS1X15_LIB_VERSION);
  Serial.println();

  Wire.begin();

  ADS.begin();

  //  change if needed.
  ADS.setComparatorMode(1);              //  0 = TRADITIONAL    1 = WINDOW

  ADS.setComparatorPolarity(0);          //  0 = LOW (default)  1 = HIGH

  //  note NON-LATCH gives only a short pulse
  ADS.setComparatorLatch(1);             //  0 = NON LATCH      1 = LATCH

  ADS.setComparatorQueConvert(0);        //  0 = trigger alert after 1 conversion

  //  set the thresholds as a number...
  //  ADS.setComparatorThresholdLow(5000);    //  change if needed
  //  ADS.setComparatorThresholdHigh(20000);  //  change if needed

  //  set the threshold as a voltage by using the voltage factor.
  float factor = ADS.toVoltage(1);  //  voltage factor
  ADS.setComparatorThresholdLow(1.234 / factor);   //  convert volts to number needed
  ADS.setComparatorThresholdHigh(3.142 / factor);  //  convert volts to number needed

  Serial.println(ADS.getComparatorThresholdLow());
  Serial.println(ADS.getComparatorThresholdHigh());
}


void loop()
{
  ADS.setGain(0);

  int16_t value0 = ADS.readADC(0);

  float factor = ADS.toVoltage(1);  //  voltage factor

  Serial.print("\tAnalog0: ");
  Serial.print(value0);
  Serial.print('\t');
  Serial.print(value0 * factor, 3);
  Serial.print('\t');
  Serial.print(ADS.getComparatorThresholdLow() * factor, 3);
  Serial.print('\t');
  Serial.print(ADS.getComparatorThresholdHigh() * factor, 3);
  Serial.println();

  delay(100);
}


//  -- END OF FILE --

