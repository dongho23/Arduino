#pragma once
//
//    FILE: I2C_LCD_custom_chars.h
//  AUTHOR: Rob.Tillaart
// VERSION: see library.properties
// PURPOSE: Arduino library for I2C_LCD
//     URL: https://github.com/RobTillaart/I2C_LCD
//          https://maxpromer.github.io/LCD-Character-Creator/
//
//  See examples for some more


////////////////////////////////////
//
//  Special
//

//  one-liners easier to search?
//  uint8_t paragraph[] = { 0x06, 0x09, 0x04, 0x10, 0x04, 0x12, 0x0E, 0x00 };

uint8_t paragraph[] = {
  B00110,
  B01001,
  B00100,
  B01010,
  B00100,
  B10010,
  B01110,
  B00000
};

uint8_t copyRight[] = {
  B00000,
  B11111,
  B10001,
  B10111,
  B10111,
  B10001,
  B11111,
  B00000
};


////////////////////////////////////
//
//  Math
//
uint8_t lessThan[] = {
  B00000,
  B00010,
  B00100,
  B01000,
  B00100,
  B00010,
  B00000,
  B11111
};

uint8_t moreThan[] = {
  B00000,
  B01000,
  B00100,
  B00010,
  B00100,
  B01000,
  B00000,
  B11111
};

uint8_t notEqual[] = {
  B00000,
  B00010,
  B00010,
  B11111,
  B00100,
  B11111,
  B01000,
  B01000
};

////////////////////////////////////
//
//  ARROWS
//
uint8_t doubleUP[] = {
  B00100,
  B01110,
  B11111,
  B00000,
  B00100,
  B01110,
  B11111,
  B00000
};

uint8_t doubleDOWN[] = {
  B11111,
  B01110,
  B00100,
  B00000,
  B11111,
  B01110,
  B00100,
  B00000
};

uint8_t openUP[] = {
  B00000,
  B00100,
  B01010,
  B01010,
  B10001,
  B10001,
  B11111,
  B00000
};

uint8_t openDown[] = {
  B00000,
  B11111,
  B10001,
  B10001,
  B01010,
  B01010,
  B00100,
  B00000
};

////////////////////////////////////
//
//  BRACKETS   --[]--
//
uint8_t bracketRight[] = {
  B11100,
  B00100,
  B00100,
  B00111,
  B00100,
  B00100,
  B11100,
  B00000
};

uint8_t bracketLeft[] = {
  B00111,
  B00100,
  B00100,
  B11100,
  B00100,
  B00100,
  B00111,
  B00000
};

uint8_t singleLine[] = {
  B00000,
  B00000,
  B00000,
  B11111,
  B00000,
  B00000,
  B00000,
  B00000
};

uint8_t doubleLine[] = {
  B11111,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B11111,
  B00000
};


////////////////////////////////////
//
//  MIRROR DIGITS  (0 and 8 are the same)
//
uint8_t mirror_1[] =
{
  B00100,
  B00110,
  B00100,
  B00100,
  B00100,
  B00100,
  B01110,
  B00000
};

uint8_t mirror_2[] =
{
  B01110,
  B10001,
  B10000,
  B01000,
  B00100,
  B00010,
  B11111,
  B00000
};

uint8_t mirror_3[] =
{
  B11111,
  B01000,
  B00100,
  B01000,
  B10000,
  B10001,
  B01110,
  B00000
};

uint8_t mirror_4[] =
{
  B01000,
  B01100,
  B01010,
  B01001,
  B11111,
  B01000,
  B01000,
  B00000
};

uint8_t mirror_5[] =
{
  B11111,
  B00001,
  B01111,
  B10000,
  B10000,
  B10001,
  B01110,
  B00000
};

uint8_t mirror_6[] =
{
  B01100,
  B00010,
  B00001,
  B01111,
  B10001,
  B10001,
  B01110,
  B00000
};

uint8_t mirror_7[] =
{
  B11111,
  B10000,
  B01000,
  B00100,
  B00010,
  B00010,
  B00010,
  B00000
};

uint8_t mirror_9[] =
{
  B01110,
  B10001,
  B10001,
  B11100,
  B10000,
  B01000,
  B00110,
  B00000
};


////////////////////////////////////
//
//  UPSIDE DIGITS  (0 and 8 are the same)
//
uint8_t upside_1[] =
{
  B01110,
  B00100,
  B00100,
  B00100,
  B00100,
  B01100,
  B00100,
  B00000
};

uint8_t upside_2[] =
{
  B11111,
  B01000,
  B00100,
  B00010,
  B00001,
  B10001,
  B01110,
  B00000
};

uint8_t upside_3[] =
{
  B01110,
  B10001,
  B00001,
  B00010,
  B00100,
  B00010,
  B11111,
  B00000
};

uint8_t upside_4[] =
{
  B00010,
  B00010,
  B11111,
  B10010,
  B01010,
  B00110,
  B00010,
  B00000
};

uint8_t upside_5[] =
{
  B01110,
  B10001,
  B00001,
  B00001,
  B11110,
  B10000,
  B11111,
  B00000
};

uint8_t upside_6[] =
{
  B01110,
  B10001,
  B10001,
  B11110,
  B10000,
  B01000,
  B00110,
  B00000
};

uint8_t upside_7[] =
{
  B01000,
  B01000,
  B01000,
  B00100,
  B00010,
  B00001,
  B11111,
  B00000
};

uint8_t upside_9[] =
{
  B01100,
  B00010,
  B00001,
  B01111,
  B10001,
  B10001,
  B01110,
  B00000
};


////////////////////////////////////
//
//  Other
//
uint8_t OnOff[] = {
  B00100,
  B00100,
  B01110,
  B10101,
  B10101,
  B10001,
  B01110,
  B00000
};

uint8_t smiley[] = {
  B00000,
  B00000,
  B01010,
  B00000,
  B10001,
  B01110,
  B00000,
  B00000
};

uint8_t heart[] = {
  B00000,
  B01010,
  B10101,
  B10001,
  B01010,
  B00100,
  B00000,
  B00000
};

uint8_t euro[] = {
  B00000,
  B00111,
  B01000,
  B11111,
  B01000,
  B11111,
  B01000,
  B00111
};

uint8_t plusminus[] = {
  B00000,
  B00100,
  B00100,
  B11111,
  B00100,
  B00100,
  B11111,
  B00000
};


//  -- END OF FILE --

