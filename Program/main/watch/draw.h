//Time                          
char t [TEXT_COUNT];                //Character of the current time

char old_text[TEXT_COUNT];          //Old text (for redrawing)
uint8_t old_size;                   //Old text size (for redrawing)

//Notifications
char txt[TEXT_COUNT];               //Character of the current notification

int8_t pos = 0;                     //Current Page (Position)

uint8_t edit=0;                     //Edit the Alarm (0 means no edit; 1 means hour; 2 means minute; 3 means second; 4 means Enable/Disable Alarm)



//Some defines for the pages (no real use just to make the code more readable)
#define PAGE_ALARM -2
#define PAGE_STOP -1
#define PAGE_CLOCK 0
#define PAGE_NOTIF 1


//This Function is used to draw or delete the main Text (for example the Time or the Notification)
//Parameters: char text[]: an array of characters, the text to be drawn
//            uint8_t size: the font size of the text
//            bool visible: a boolean which shows if the text should be drawn or deleted
void drawMainText(char text[], uint8_t size, bool visible)
{
    tft.setTextSize(old_size);      //Set the old font size
    tft.setCursor(CLOCK_X,CLOCK_Y); //Set the cursor position                   
    tft.setTextColor(BACKGROUND_COLOR);//set the color to the background color
    tft.println(old_text);          //delete the text
    tft.setTextColor(CLOCK_COLOR);  //set the text color to the default clock color
    tft.setCursor(CLOCK_X,CLOCK_Y); //Set the cursor position
    if(visible)                     //Check if the text need to be redrawn
    {
      tft.setTextSize(size);        //set the new text size
      tft.println(text);            //redraw the text   
    }
    for(int count=0; count<18; count++)//save the text to the old-buffer
      old_text[count]=text[count];  
    old_size=size;                  //save the text size
}

void deleteMainText()
{
    tft.setTextSize(old_size);      //Set the old font size
    tft.setCursor(CLOCK_X,CLOCK_Y); //Set the cursor position                   
    tft.setTextColor(BACKGROUND_COLOR);//set the color to the background color
    tft.println(old_text);          //delete the text
    
    for(int count=0; count<18; count++)//save the text to the old-buffer
      old_text[count]=0;  
    old_size=0;                     //save the text size
}

String fromInt(uint8_t _hour, uint8_t _minute, int8_t _second)
{
    String tmp = String();
    if(_hour<10)
    tmp+=String("0");
    tmp+=String(_hour);
    tmp+=":";
    if(_minute<10)
      tmp+=String("0");
    tmp+=String(_minute);
    tmp+=":";
    if(_second<10)
      tmp+=String("0");
    tmp+=String(_second);
    return tmp;
}

String fromInt(uint8_t _hour, uint8_t _minute, int8_t _second, uint16_t _isr_counter)
{
    String tmp = String();
    if(_hour<10)
      tmp+=String("0");
    tmp+=String(_hour);
    tmp+=":";
    if(_minute<10)
      tmp+=String("0");
    tmp+=String(_minute);
    tmp+=":";
    if(_second<10)
      tmp+=String("0");
    tmp+=String(_second);
    tmp+=":";
    if(_isr_counter<10)
      tmp+=String("0");
    if(_isr_counter<100)
      tmp+=String("0"); 
    tmp+=String(_isr_counter); 
    return tmp;
}



inline void drawNotification()
{
  drawMainText(txt, NOTIFICATION_SIZE, true);
}

void drawTime()
{
  fromInt(hour,minute,second).toCharArray(t, 18);
  drawMainText(t, CLOCK_SIZE, true);
  time_changed=false;       
}

void drawStop()
{
  fromInt(hour_stop,minute_stop,second_stop,isr_counter_stop).toCharArray(t, 18);
  drawMainText(t, STOP_SIZE, true);        
}

void drawAlarm()
{  
  fromInt(hour_alarm,minute_alarm,second_alarm).toCharArray(t, 18);
  drawMainText(t, CLOCK_SIZE, true);
}

void clearTitle()
{
  tft.fillCircle(tft.width()/2+(pos*20), RECT_DIST+12, 4,BACKGROUND_COLOR);
  
  tft.setCursor(RECT_DIST+8, RECT_DIST+8);
  tft.setTextSize(1);
  tft.setTextColor(BACKGROUND_COLOR);
  switch(pos)
  {
  case 0:              
    tft.println("Watch");
    break;
  case -1:
    tft.println("Stopwatch");
    break;
  case 1:
    tft.println("Notifications");
    break;
  case -2:
    tft.println("Alarm");
    tft.setCursor(tft.width()-(8*7), 0);          
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
    break;
  }
  tft.drawCircle(tft.width()/2+(pos*20), RECT_DIST+12, 4,TITLE_COLOR);
}

void updateTitle()
{
  tft.fillCircle(tft.width()/2+(pos*20), RECT_DIST+12, 4,TITLE_COLOR);
  tft.setCursor(RECT_DIST+8, RECT_DIST+8);
  tft.setTextSize(1);
  tft.setTextColor(TITLE_COLOR);
  switch(pos)
  {
  case PAGE_CLOCK:              
    tft.println("Watch");
    drawTime();
    break;
  case PAGE_STOP:
    tft.println("Stopwatch");
    stopped=false;
    drawStop();
    stopped=true;
    hour_stop=0;
    minute_stop=0;
    second_stop=0;
    isr_counter_stop=0;
    break;
  case PAGE_NOTIF:
    tft.println("Notifications");
    drawNotification();
    break;
  case PAGE_ALARM:
    tft.println("Alarm");
    drawAlarm();
    break;
  }
}

void updateMainText()
{
  switch(pos)
  {
  case 0:
    if(time_changed)
      drawTime();
    break;
  case -1: 
   if(!stopped)
      drawStop();         
    break;
  }
}

