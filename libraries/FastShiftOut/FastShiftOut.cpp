//
//    FILE: FastShiftOut.cpp
//  AUTHOR: Rob Tillaart
// VERSION: 0.4.1
// PURPOSE: ShiftOut that implements the Print interface
//    DATE: 2013-08-22
//     URL: https://github.com/RobTillaart/FastShiftOut


#include "FastShiftOut.h"


FastShiftOut::FastShiftOut(uint8_t dataOut, uint8_t clockPin, uint8_t bitOrder)
{
  _bitOrder = bitOrder;
  pinMode(dataOut, OUTPUT);
  pinMode(clockPin, OUTPUT);
  //  https://www.arduino.cc/reference/en/language/functions/advanced-io/shiftout/
  digitalWrite(clockPin, LOW);  //  assume rising pulses from clock

#if defined(ARDUINO_ARCH_AVR) || defined(ARDUINO_ARCH_MEGAAVR)

  uint8_t _port    = digitalPinToPort(dataOut);
  _dataOutRegister = portOutputRegister(_port);
  _dataOutBit      = digitalPinToBitMask(dataOut);

  _port            = digitalPinToPort(clockPin);
  _clockRegister   = portOutputRegister(_port);
  _clockBit        = digitalPinToBitMask(clockPin);

#else   //  reference implementation

  _dataPinOut = dataOut;
  _clockPin   = clockPin;

#endif
}


size_t FastShiftOut::write(uint8_t data)
{
  if (_bitOrder == LSBFIRST)
  {
    return writeLSBFIRST(data);
  }
  return writeMSBFIRST(data);
}


size_t FastShiftOut::write16(uint16_t data)
{
  if (_bitOrder == LSBFIRST)
  {
    writeLSBFIRST(data & 0xFF);
    writeLSBFIRST(data >> 8);
  }
  else
  {
    writeMSBFIRST(data >> 8);
    writeMSBFIRST(data & 0xFF);
  }
  return 2;
}


size_t FastShiftOut::write24(uint32_t data)
{
  if (_bitOrder == LSBFIRST)
  {
    writeLSBFIRST(data & 0xFF);
    data >>= 8;
    writeLSBFIRST(data & 0xFF);
    data >>= 8;
    writeLSBFIRST(data & 0xFF);
  }
  else
  {
    writeMSBFIRST((data >> 16) & 0xFF);
    writeMSBFIRST((data >> 8)  & 0xFF);
    writeMSBFIRST(data & 0xFF);
  }
  return 3;
}


size_t FastShiftOut::write32(uint32_t data)
{
  if (_bitOrder == LSBFIRST)
  {
    writeLSBFIRST(data & 0xFF);
    data >>= 8;
    writeLSBFIRST(data & 0xFF);
    data >>= 8;
    writeLSBFIRST(data & 0xFF);
    data >>= 8;
    writeLSBFIRST(data & 0xFF);
  }
  else
  {
    writeMSBFIRST((data >> 24) & 0xFF);
    writeMSBFIRST((data >> 16) & 0xFF);
    writeMSBFIRST((data >> 8)  & 0xFF);
    writeMSBFIRST(data & 0xFF);
  }
  return 4;
}


size_t FastShiftOut::write(uint8_t * array, size_t size)
{
  if (_bitOrder == LSBFIRST)
  {
    for (size_t i = size; i > 0; )      //  from end to begin ????
    {
      i--;
      writeLSBFIRST(array[i]);
    }
  }
  else
  {
    for (size_t i = 0; i < size; i++)   //  from begin to end..
    {
      writeMSBFIRST(array[i]);
    }
  }
  return size;
}


uint8_t FastShiftOut::lastWritten(void)
{
  return _lastValue;
}


bool FastShiftOut::setBitOrder(const uint8_t bitOrder)
{
  if ((bitOrder == LSBFIRST) || (bitOrder == MSBFIRST))
  {
    _bitOrder = bitOrder;
    return true;
  };
  return false;
}


uint8_t FastShiftOut::getBitOrder(void)
{
  return _bitOrder;
}


size_t FastShiftOut::writeLSBFIRST(uint8_t data)
{
  uint8_t value = data;
  _lastValue = value;

#if defined(ARDUINO_ARCH_AVR) || defined(ARDUINO_ARCH_MEGAAVR)

#if defined(FASTSHIFTOUT_AVR_LOOP_UNROLLED)  //  AVR SPEED OPTIMIZED

  uint8_t cbmask1  = _clockBit;
  uint8_t outmask1 = _dataOutBit;
  uint8_t outmask2 = ~_dataOutBit;

  volatile uint8_t* localDataOutRegister = _dataOutRegister;
  volatile uint8_t* localClockRegister   = _clockRegister;

  //  disable interrupts (for all bits)
  uint8_t oldSREG = SREG;
  noInterrupts();

  //  See discussion #17
  uint8_t d0 = *localDataOutRegister & outmask2;  //  cache 0
  uint8_t d1 = d0 | outmask1;                     //  cache 1

  if ((value & 0x01) == 0) *localDataOutRegister = d0;
  else                     *localDataOutRegister = d1;
  // *_clockRegister |= cbmask1;
  // *_clockRegister &= cbmask2;
  //  following code is allowed as interrupts are disabled.
  //  so register can not change
  uint8_t r = *localClockRegister;
  *localClockRegister = r | cbmask1;  //  set one bit
  *localClockRegister = r;            //  reset bit

  if ((value & 0x02) == 0) *localDataOutRegister = d0;
  else                     *localDataOutRegister = d1;
  r = *localClockRegister;
  *localClockRegister = r | cbmask1;  //  set one bit
  *localClockRegister = r;            //  reset it

  if ((value & 0x04) == 0) *localDataOutRegister = d0;
  else                     *localDataOutRegister = d1;
  r = *localClockRegister;
  *localClockRegister = r | cbmask1;  //  set one bit
  *localClockRegister = r;            //  reset it

  if ((value & 0x08) == 0) *localDataOutRegister = d0;
  else                     *localDataOutRegister = d1;
  r = *localClockRegister;
  *localClockRegister = r | cbmask1;  //  set one bit
  *localClockRegister = r;            //  reset it

  if ((value & 0x10) == 0) *localDataOutRegister = d0;
  else                     *localDataOutRegister = d1;
  r = *localClockRegister;
  *localClockRegister = r | cbmask1;  //  set one bit
  *localClockRegister = r;            //  reset it

  if ((value & 0x20) == 0) *localDataOutRegister = d0;
  else                     *localDataOutRegister = d1;
  r = *localClockRegister;
  *localClockRegister = r | cbmask1;  //  set one bit
  *localClockRegister = r;            //  reset it

  if ((value & 0x40) == 0) *localDataOutRegister = d0;
  else                     *localDataOutRegister = d1;
  r = *localClockRegister;
  *localClockRegister = r | cbmask1;  //  set one bit
  *localClockRegister = r;            //  reset it

  if ((value & 0x80) == 0) *localDataOutRegister = d0;
  else                     *localDataOutRegister = d1;
  r = *localClockRegister;
  *localClockRegister = r | cbmask1;  //  set one bit
  *localClockRegister = r;            //  reset it

  //  restore interrupt state
  SREG = oldSREG;

#else  //  AVR SIZE OPTIMIZED

  uint8_t cbmask1  = _clockBit;
  uint8_t outmask1 = _dataOutBit;
  uint8_t outmask2 = ~_dataOutBit;

  volatile uint8_t* localDataOutRegister = _dataOutRegister;
  volatile uint8_t* localClockRegister = _clockRegister;

  //  disable interrupts (for all bits)
  uint8_t oldSREG = SREG;
  noInterrupts();

  //  See discussion #17
  uint8_t d0 = *localDataOutRegister & outmask2;  //  cache 0
  uint8_t d1 = d0 | outmask1;                     //  cache 1
  for (uint8_t m = 1; m > 0; m <<= 1)
  {
    //  process one bit
    if ((value & m) == 0) *localDataOutRegister = d0;
    else *localDataOutRegister = d1;
    uint8_t r = *localClockRegister;
    *localClockRegister = r | cbmask1;  //  set one bit
    *localClockRegister = r;            //  reset it
  }

  //  restore interrupt state
  SREG = oldSREG;

#endif  //  if (AVR)

#else   //  other platforms reference shiftOut()

  shiftOut(_dataPinOut, _clockPin, LSBFIRST, value);

#endif

  return 1;
}


size_t FastShiftOut::writeMSBFIRST(uint8_t data)
{
  uint8_t value = data;
  _lastValue = value;

#if defined(ARDUINO_ARCH_AVR) || defined(ARDUINO_ARCH_MEGAAVR)

#if defined(FASTSHIFTOUT_AVR_LOOP_UNROLLED)  //  AVR SPEED OPTIMIZED

  uint8_t cbmask1  = _clockBit;
  //  uint8_t cbmask2  = ~_clockBit;
  uint8_t outmask1 = _dataOutBit;
  uint8_t outmask2 = ~_dataOutBit;

  volatile uint8_t* localDataOutRegister = _dataOutRegister;
  volatile uint8_t* localClockRegister = _clockRegister;

  //  disable interrupts (for all bits)
  uint8_t oldSREG = SREG;
  noInterrupts();

  //  See discussion #17
  uint8_t d0 = *localDataOutRegister & outmask2;  //  cache 0
  uint8_t d1 = d0 | outmask1;                     //  cache 1

  if ((value & 0x80) == 0) *localDataOutRegister = d0;
  else                     *localDataOutRegister = d1;
  // *localClockRegister |= cbmask1;
  // *localClockRegister &= cbmask2;
  //  following code is allowed as interrupts are disabled.
  //  so register can not change
  uint8_t r = *localClockRegister;
  *localClockRegister = r | cbmask1;  //  set one bit
  *localClockRegister = r;            //  reset it

  if ((value & 0x40) == 0) *localDataOutRegister = d0;
  else                     *localDataOutRegister = d1;
  r = *localClockRegister;
  *localClockRegister = r | cbmask1;  //  set one bit
  *localClockRegister = r;            //  reset it

  if ((value & 0x20) == 0) *localDataOutRegister = d0;
  else                     *localDataOutRegister = d1;
  r = *localClockRegister;
  *localClockRegister = r | cbmask1;  //  set one bit
  *localClockRegister = r;            //  reset it

  if ((value & 0x10) == 0) *localDataOutRegister = d0;
  else                     *localDataOutRegister = d1;
  r = *localClockRegister;
  *localClockRegister = r | cbmask1;  //  set one bit
  *localClockRegister = r;            //  reset it

  if ((value & 0x08) == 0) *localDataOutRegister = d0;
  else                     *localDataOutRegister = d1;
  r = *localClockRegister;
  *localClockRegister = r | cbmask1;  //  set one bit
  *localClockRegister = r;            //  reset it

  if ((value & 0x04) == 0) *localDataOutRegister = d0;
  else                     *localDataOutRegister = d1;
  r = *localClockRegister;
  *localClockRegister = r | cbmask1;  //  set one bit
  *localClockRegister = r;            //  reset it

  if ((value & 0x02) == 0) *localDataOutRegister = d0;
  else                     *localDataOutRegister = d1;
  r = *localClockRegister;
  *localClockRegister = r | cbmask1;  //  set one bit
  *localClockRegister = r;            //  reset it

  if ((value & 0x01) == 0) *localDataOutRegister = d0;
  else                     *localDataOutRegister = d1;
  r = *localClockRegister;
  *localClockRegister = r | cbmask1;  //  set one bit
  *localClockRegister = r;            //  reset it

  //  restore interrupt state
  SREG = oldSREG;

#else  //  AVR SIZE OPTIMIZED

  uint8_t cbmask1  = _clockBit;
  uint8_t outmask1 = _dataOutBit;
  uint8_t outmask2 = ~_dataOutBit;

  volatile uint8_t* localDataOutRegister = _dataOutRegister;
  volatile uint8_t* localClockRegister = _clockRegister;

  //  disable interrupts (for all bits)
  uint8_t oldSREG = SREG;
  noInterrupts();

  //  See discussion #17
  uint8_t d0 = *localDataOutRegister & outmask2;  //  cache 0
  uint8_t d1 = d0 | outmask1;                     //  cache 1
  for (uint8_t m = 0x80; m > 0; m >>= 1)
  {
    //  process one bit
    if ((value & m) == 0) *localDataOutRegister = d0;
    else *localDataOutRegister = d1;
    uint8_t r = *localClockRegister;
    *localClockRegister = r | cbmask1;  //  set one bit
    *localClockRegister = r;            //  reset it
  }


  //  restore interrupt state
  SREG = oldSREG;

#endif  //  if (AVR)

#else   //  other platforms reference shiftOut()

  shiftOut(_dataPinOut, _clockPin, MSBFIRST, value);

#endif

  return 1;
}


//  -- END OF FILE --

