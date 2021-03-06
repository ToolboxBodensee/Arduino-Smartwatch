/*
  Morse.h - Library for flashing Morse code.
  Created by David A. Mellis, November 2, 2007.
  Released into the public domain.
*/

#ifndef BITMAP_H
#define BITMAP_H

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif  
#include <Adafruit_GFX.h>    // Core graphics library
#include "Adafruit_ILI9341.h" // Hardware-specific library
#include <SPI.h>
#include <SD.h>

class Bitmap
{
  public:
    void draw(char *filename, uint8_t x, uint16_t y);
    Bitmap();
  private:
    uint16_t read16(File &f);
    uint32_t read32(File &f);
};

#endif

