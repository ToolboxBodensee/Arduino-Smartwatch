/*
  Morse.h - Library for flashing Morse code.
  Created by David A. Mellis, November 2, 2007.
  Released into the public domain.
*/

#ifndef PROGRAM_H
#define PROGRAM_H

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif  
#include <Adafruit_GFX.h>    // Core graphics library
#include "Adafruit_ILI9341.h" // Hardware-specific library
#include <SPI.h>
#include <SD.h>

class Program
{
  public:
    void show();
    void pause();
    void play();
    void end();
    void run();
    Program(String prog);	
  private:
    int color(char value);
    /*class Object
    {
	public:
		void saveBoxCount(int boxCount, int box);
		int getBoxCount(int box);
		void saveProgCount(int counter, int box);
		int getProgCount(int box);
    };*/    	  
};

#endif

