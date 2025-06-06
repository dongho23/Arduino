//
//    FILE: AD5680.cpp
//  AUTHOR: Rob Tillaart
// VERSION: 0.4.0
//    DATE: 2023-09-19
// PURPOSE: Arduino library for AD5680 Digital Analog Convertor (18 bit).


#include "AD5680.h"


//  HARDWARE SPI
AD5680::AD5680(uint8_t slaveSelect, __SPI_CLASS__ * mySPI)
{
  _select    = slaveSelect;
  _hwSPI     = true;
  _mySPI     = mySPI;
  _value     = 0;
  _type      = 18;
  _maxValue  = 262143;
}

//  SOFTWARE SPI
AD5680::AD5680(uint8_t slaveSelect, uint8_t spiData, uint8_t spiClock)
{
  _select    = slaveSelect;
  _hwSPI     = false;
  _mySPI     = NULL;
  _dataOut   = spiData;
  _clock     = spiClock;
  _value     = 0;
  _type      = 18;
  _maxValue  = 262143;
}


//  initializes the SPI
//  and sets internal state
void AD5680::begin()
{
  pinMode(_select, OUTPUT);
  digitalWrite(_select, HIGH);

  _spi_settings = SPISettings(_SPIspeed, MSBFIRST, SPI_MODE1);

  if (_hwSPI)
  {
    //  _mySPI->end();
    //  _mySPI->begin();
    //  delay(1);
  }
  else  //  SOFTWARE SPI
  {
    pinMode(_dataOut, OUTPUT);
    pinMode(_clock, OUTPUT);
    digitalWrite(_dataOut, LOW);
    digitalWrite(_clock, LOW);
  }
}


uint8_t AD5680::getType()
{
  return _type;
}


//
//  SET VALUE
//
//  value = 0..262143 == 0x0003FFFF (18 bit)
bool AD5680::setValue(uint32_t value)
{
  //  range check
  if (value > 0x3FFFF) return false;
  //  keep last value
  _value = value;
  //  prepare 18 bit transfer.
  updateDevice(_value);
  return true;
}


//  returns 0..262143 == 0x0003FFFF (18 bit)
uint32_t AD5680::getValue()
{
  return _value;
}


uint32_t AD5680::getMaxValue()
{
  return _maxValue;
}


bool AD5680::setPercentage(float percentage)
{
  //  range check
  if ((percentage < 0) || (percentage > 100)) return false;

  uint32_t value = round( 2621.43 * percentage);
  return setValue(value);
}


float AD5680::getPercentage()
{
  float value = getValue();
  if (value > 0)
  {
    return value * ( 1.0 / 2621.43);
  }
  return 0;
}


//
//  SPI
//
void AD5680::setSPIspeed(uint32_t speed)
{
  _SPIspeed = speed;
  _spi_settings = SPISettings(_SPIspeed, MSBFIRST, SPI_MODE1);
};


uint32_t AD5680::getSPIspeed()
{
  return _SPIspeed;
}


bool AD5680::usesHWSPI()
{
  return _hwSPI;
}


//////////////////////////////////////////////////////////////////
//
//  PROTECTED
//

void AD5680::updateDevice(uint32_t data)
{
  uint8_t a = (data >> 14) & 0x0F;  //  bit 14-17
  uint8_t b = (data >> 6)  & 0xFF;  //  bit 06-13
  uint8_t c = (data << 2)  & 0xFC;  //  bit 00-05

  digitalWrite(_select, LOW);
  if (_hwSPI)
  {
    _mySPI->beginTransaction(_spi_settings);
    _mySPI->transfer(a);
    _mySPI->transfer(b);
    _mySPI->transfer(c);
    _mySPI->endTransaction();
  }
  else  //  Software SPI
  {
    swSPI_transfer(a);
    swSPI_transfer(b);
    swSPI_transfer(c);
  }
  digitalWrite(_select, HIGH);
}


//  simple one mode version
void AD5680::swSPI_transfer(uint8_t value)
{
  int clk = _clock;
  int dao = _dataOut;
  //  Shifting 24 bits starting from MSB to LSB
  for (uint8_t mask = 0x80; mask; mask >>= 1)
  {
    digitalWrite(dao, (value & mask)? HIGH : LOW);
    digitalWrite(clk, HIGH);
    digitalWrite(clk, LOW);
  }
}


//  -- END OF FILE --

