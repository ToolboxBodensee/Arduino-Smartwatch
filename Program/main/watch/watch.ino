/***************************************************
  Arduino-Smartwatch 

  This is the main file here you can find the main logic.
  Other parts:
  const.h:        Just some constants for quick modifications
  draw.h:         Drawing the UI-Parts
  touch.h:        Managing touches and interaction
  notification.h: Getting notifications via Hardware-UART or Bluetooth
  interrupt.h:    Initialising and managing the interrupt
  alarm.h:        Manage the alarm
  debug.h:        Just calculate and manage some debug data
  bluetooth.h:    Managing bluetooth


  Hardware:
    -Arduino (Arduino UNO, Atmel ATmega328P)
     http://arduino.cc/en/Main/ArduinoBoardUno
    -Screen (2.8''-TFT-Touchscreen-Shield for Arduino)
     http://www.adafruit.com/products/1651
    -Bluetooth (Bluetooth Low Energy - nRF8001 Breakout)
     https://www.adafruit.com/product/1697

  If you like the code help me getting this even better
  by sponsoring me just contact me: paul.nykiel@gmail.com

  Please support Adafruit and open-source hardware by purchasing
  products from Adafruit! They have the best support in the world!

  Written by Paul Nykiel.

  This program is free software; you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation; either version 3 of the License, or
  (at your option) any later version.


  Todo-List:
  -Better Documentation
  -Let the ATmega sleep to save power

 ****************************************************/

//Core Librarys for Hardware
#include <SPI.h>                    //Arduino SPI Library
#include <Wire.h>                   //Arduino I²C Library
#include <EEPROM.h>                 //Arduino EEPROM Library

//Adafruit Librarys (just Middleware for their devices)
#include <Adafruit_ILI9341.h>       //Adafruit LCD-Driver Library
#include <Adafruit_BLE_UART.h>      //Adafruit Bluetooth-Low-Energy SPI Library (UART-Emulation)
#include <Adafruit_STMPE610.h>      //Adafruit Touchscreen-Driver Library
#include <Adafruit_GFX.h>           //Adafruit Core graphics library

//My own Librarys
#include "const.h"                  //All the defines (if you just want to change some colors...: change it in this file)
#include "interrupt.h"              //All the Software and Hardware Interrupts Low-Level Code
#include "draw.h"                   //All the Low-Level UI Code
#include "notification.h"           //All the Notification-Code
#include "touch.h"                  //The Code managing all touches
#include "debug.h"                  //Send Debug-Data via Hardware-Serial
#include "alarm.h"                  //Edit the alarm
#include "bluetooth.h"              //Handle the bluetooth stuff
 
//##################################################
//##################################################
//
//        ####  ####  ##### #   #  #####
//        #     #       #   #   #  #   #
//        ####  ####    #   #   #  #####
//           #  #       #   #   #  #
//        ####  ####    #   #####  #
//
//##################################################
//##################################################
void setup()                        //Initialising of the watch
{           
  #ifdef DEBUG
  Serial.begin(9600);               //Set the UART-Baud-Rate to 9600
  #endif
  #ifdef BLUETOOTH
  BTLEserial.begin();               //Initialize the Bluetooth-Module
  #endif
  tft.begin();                      //Initialize the Screen
  tft.fillScreen(WALL_COLOR);       //Draw the Wallpaper-Color 
  
  #ifdef TOUCH
  bool skip=false;                  //A boolean if to skip the time initialisation
  if (!ts.begin())                  //Start the Touchscreen Controller
    while (1);                      //Wait for the Touchscreen to be ready
  while(!Serial.available() > 0)    //Wait for data via UART
  {
    if(ts.touched())                //If the Screen got touched
    {
      skip=true;                    //Set the skip-boolean to true
      break;                        //Break out of the loop waiting for data
    }
    #ifdef EE_USE
    else if(EEPROM.read(EE_BOOL)==1)//Check if a time is saved in the EEPROM
    {
      skip=true;                    //Set the skip-boolean to true
      hour = EEPROM.read(EE_HOUR);  //read the hour from EEPROM
      minute = EEPROM.read(EE_MINUTE) + 1;//read the minute from EEPROM and add a minute
      EEPROM.write(EE_BOOL, 0);     //Write a Boolean to the EEPROM that the time had been read
      break;
    }
    #endif
  }
  if(!skip)                         //Check if the watch have to wait for a time
  {
    hour = Serial.read()-'0';       //Read the first hour digit and decode it from ascii
    while(!Serial.available() > 0); //Wait for next character
    hour = hour*10 + (Serial.read()-'0');//Read the next digit, decode it from ascii and calculate it to one hour number     
    while(!Serial.available() > 0); //Wait for next character
    minute = Serial.read()-'0';     //Read the first digit of the minute and decode it from ascii
    while(!Serial.available() > 0); //Wait for next character
    minute = minute*10 + (Serial.read()-'0');//Read the next digit, decode it from ascii and calculate it to one minute number 
  }
  #endif

  clockInterruptInit();             //Initialize the Timer Interrupt

  tft.setRotation(ROTATION);        //Set the TFT Rotation
  tft.fillRoundRect(RECT_DIST,RECT_DIST,tft.width()-(2*RECT_DIST),tft.height()-(2*RECT_DIST),ROUND,BACKGROUND_COLOR);//Draw the main rectangle at the top 
  for(int zaehler = -MAX_PAGE; zaehler<=MAX_PAGE; zaehler++)//Draw the dots at the top
    tft.drawCircle(tft.width()/2+zaehler*20, RECT_DIST+12, 4,TITLE_COLOR);//Draw the dots
  tft.fillCircle(tft.width()/2, RECT_DIST+12, 4,TITLE_COLOR) ;//Fill the middle circle
  tft.setCursor(RECT_DIST+8, RECT_DIST+8);
  tft.setTextColor(TITLE_COLOR);    //Set the text color to the title (and dots) color            
  tft.println("Watch");             //Draw the title of the first page
}

//##################################################
//##################################################
//
//        #     #####  #####  #####
//        #     #   #  #   #  #   #
//        #     #   #  #   #  #####
//        #     #   #  #   #  #
//        ####  #####  #####  #
//
//##################################################
//##################################################

void loop()                         //Main Loop
{       
  #ifdef TOUCH                      
  if(ts.touched())                  //Check if the screen is touched
  {
    if(used>=TIMEOUT)               //Check if the screen is off
    {
      analogWrite(3, 255);          //Turn Brightness to max
      while(ts.touched())           //Wait for touch
        used=0;                     //Reset used to 0
      return;                       //Restart loop
    }
    used=0;                         //Set used to 0
    
    switch(getTouch())              //Check the sort of touch
    {
      case PREV_PAGE:               //If touch is a touch on the left side
        clearTitle();               //Clear the title
        pos--;                      //Go a page to the left
        if(pos<-MAX_PAGE)           //Check if already on the most left page
          pos=-MAX_PAGE;            //Set the page to the most left
        updateTitle();              //Redraw the title
        break;
      case NEXT_PAGE:               //If touch is a touch on the right side
        clearTitle();               //Clear the title
        pos++;                      //Go a page to the right
        if(pos>MAX_PAGE)            //Check if already on the most right page
          pos=MAX_PAGE;             //Set the page to the most right
        updateTitle();              //Redraw the title
        break;
      case TITLE_PRESS:             //If the touch is a touch on the main area
        switch(pos)                 //Check on wich page we are currently
        {
          case PAGE_STOP:           //On the stopwatch page
              stopped=!stopped;     //Change between pause and running
            break;
          case PAGE_NOTIF:          //On the notification page
              txt_null();           //Delete the notification
            break;
          case PAGE_ALARM:          //On the alarm page
              editAlarm();          //Start editing the alarm
            break;
        }
      case LONG_PRESS:              //If the touch is a long press
        switch(pos)                 //Check on wich page we are
        {
          case PAGE_STOP:           //On the stopwatch page
              drawStop();           //Draw the stopwatch
              hour_stop=0;          //Set the hour to 0
              minute_stop=0;        //Set the minute to 0
              second_stop=0;        //Set the second to 0
              isr_counter_stop=0;   //Set the isr-counter to 0
            break;
          case PAGE_ALARM:          //On the alarm page
              updateEdit();         //Update the alarm page
            break;
        }
        break;          
    } 
    while(ts.touched());            //Wait until the touch is released     
  } 
#endif  
  updateMainText();                 //Update the main text
  

  if(Serial.available())            //Check if something is on the UART available
    getNotification();              //Read the notification

  #ifdef DEBUG                      
  sendDebugData();                  //Send Debug Data
  #endif
  dispatchBluetooth();              //Manage BT
}
