inline void txt_null()
{
  for(uint8_t zaehler=0; zaehler<TEXT_COUNT; zaehler++)
    txt[zaehler]=0;
}

void getNotification()
{
  txt_null();
  for(int counter=0; counter<=TEXT_COUNT && Serial.available() ;counter++)
  {
    txt [counter] = Serial.read();
    delay(10);          
  }
  if(txt[0]=='*')
  {
    tft.fillScreen(ILI9341_RED);
    #ifdef EE_USE
    EEPROM.write(EE_BOOL, 1);
    EEPROM.write(EE_HOUR, hour);
    EEPROM.write(EE_MINUTE, minute);
    #endif
    while(true);
  }
  else if(txt[0]=='\\')
    txt_null();
  
  if(pos==1)
      drawNotification();
}