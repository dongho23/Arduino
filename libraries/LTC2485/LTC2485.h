#pragma once
//
//    FILE: LTC2485.h
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.0
//    DATE: 2025-02-21
// PURPOSE: Arduino library for LTC2485 I2C 24 bit ADC.
//     URL: https://github.com/RobTillaart/LTC2485
//          https://www.analog.com/en/products/ltc2485.html

#include "Arduino.h"
#include "Wire.h"


#define LTC2485_LIB_VERSION               (F("0.1.0"))


//  CONFIGURATION BITS, TABLE 1
#define LTC2485_SPEED_1X                        0x00
#define LTC2485_SPEED_2X                        0x01
#define LTC2485_REJECT_50HZ                     0x02
#define LTC2485_REJECT_60HZ                     0x04
#define LTC2485_REJECT_50_60_HZ                 0x00
#define LTC2485_INTERNAL_TEMP                   0x08


class LTC2485
{
public:
  explicit LTC2485(uint8_t address, TwoWire *wire = &Wire);

  bool     begin(float VREF = 5.0);
  bool     isConnected();
  uint8_t  getAddress();

  uint8_t  configure(uint8_t config);
  int32_t  getADC();
  float    getVolts();
  float    getMilliVolts() { return getVolts() * 1e-3; };
  float    getMicroVolts() { return getVolts() * 1e-6; };
  float    getTemperature();

private:

  uint8_t  _write(uint8_t value);
  uint32_t _read();

  float     _vref = 5.0;
  uint8_t   _config = LTC2485_SPEED_1X | LTC2485_REJECT_50_60_HZ;
  uint8_t   _address = 0x00;
  TwoWire * _wire;
};


//  -- END OF FILE --

