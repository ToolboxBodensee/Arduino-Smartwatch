<h1>Arduino-Smartwatch</h1>
  <h2>Files:</h2>
  <p>watch.ino:        The main file and the main logic</p>
  <p>const.h:        Just some constants for quick modifications</p>
  <p>draw.h:         Drawing the UI-Parts</p>
  <p>touch.h:        Managing touches and interaction</p>
  <p>notification.h: Getting notifications via Hardware-UART or Bluetooth</p>
  <p>interrupt.h:    Initialising and managing the interrupt</p>
  <p>alarm.h:        Manage the alarm</p>
  <p>debug.h:        Just calculate and manage some debug data</p>
  <p>bluetooth.h:    Managing bluetooth</p>
  
  <h2>Hardware:</h2>
    <p>-Arduino (Arduino UNO, Atmel ATmega328P)
     http://arduino.cc/en/Main/ArduinoBoardUno</p>
    <p>-Screen (2.8''-TFT-Touchscreen-Shield for Arduino)
     http://www.adafruit.com/products/1651</p>
    <p>-Bluetooth (Bluetooth Low Energy - nRF8001 Breakout)
     https://www.adafruit.com/product/1697</p>
     
  <h2>App</h2>
  At the moment there is only an Android app. It works on devices with at least android 4.3. To get the notifications working you have to enable the app to read notification (Settings->Security->Notification Access).<br>
  You can build the app using the latest (1.0) version of android studio.

  <h2>Case UNTESTED</h2>
  There is a 3d-printable case for the watch it consists of 2 Parts (main part and a part of the watch band).
  The complete case should be printed using the ninja-flex filament.

  <h2>Support the project</h2>
  If you like the code help me getting this even better
  by sponsoring me. <br>
  Please support Adafruit and open-source hardware by purchasing
  products from Adafruit! They have the best support in the world!<br>
  Written by Paul Nykiel.<br>
  <h2>License</h2>
  
  This program is free software; you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation; either version 3 of the License, or
  (at your option) any later version.<br>
  <h2>Todo-List:</h2>
  <p>-Better Documentation</p>
  <p>-Let the ATmega sleep to save power</p>

