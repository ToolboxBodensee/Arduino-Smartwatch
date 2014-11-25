void editAlarm()
{
	switch(edit)
           {
               case 1:
                 hour_alarm++;
                 if(hour_alarm>=24)
                   hour_alarm=0;
               break;
               case 2:
                 minute_alarm++;
                 if(minute_alarm>=60)
                   minute_alarm=0;
               break;
               case 3:
                 second_alarm++;
                 if(second_alarm>=60)
                   second_alarm=0;
               break;
               case 4:
                 tft.setCursor(tft.width()-(8*7)-RECT_DIST, RECT_DIST+12);         
                 tft.setTextColor(BACKGROUND_COLOR);
                 tft.setTextSize(1);
                 if(enabled_alarm)
                  tft.println("Enabled");
                 else
                  tft.println("Disabled");
                 enabled_alarm=!enabled_alarm;
                 tft.setCursor(tft.width()-(8*7)-RECT_DIST, RECT_DIST+12);         
                 tft.setTextColor(TITLE_COLOR);
                 tft.setTextSize(1);
                 if(enabled_alarm)
                  tft.println("Enabled");
                else
                  tft.println("Disabled");
                break;
           } 
           drawAlarm();        
}

void updateEdit()
{
  tft.setCursor(tft.width()-(8*7)-RECT_DIST, RECT_DIST+12);          
  tft.setTextColor(BACKGROUND_COLOR);
  tft.setTextSize(1);
  switch(edit)
  {              
      case 1:
        tft.println("Hour");
        break;
      case 2:
        tft.println("Minute");
        break;
      case 3:
        tft.println("Second");
        break;
      case 4:
        if(enabled_alarm)
          tft.println("Enabled");
        else
          tft.println("Disabled");
        break;
  }
  edit++;
  if(edit>4)
    edit=0;
  tft.setCursor(tft.width()-(8*7)-RECT_DIST, RECT_DIST+12);;          
  tft.setTextColor(TITLE_COLOR);
  switch(edit)
  {              
      case 1:
        tft.println("Hour");
        break;
      case 2:
        tft.println("Minute");
        break;
      case 3:
        tft.println("Second");
        break;
      case 4:
        if(enabled_alarm)
          tft.println("Enabled");
        else
          tft.println("Disabled");
        break;
  }
}