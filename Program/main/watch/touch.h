#define NEXT_PAGE 1
#define PREV_PAGE -1
#define LONG_PRESS 3
#define TITLE_PRESS 2

int8_t getTouch()
{
  #ifdef TOUCH
  TS_Point anfang = ts.getPoint();
  anfang.x = map(anfang.x, TS_MINX, TS_MAXX, 0, tft.width());
  anfang.y = map(anfang.y, TS_MINY, TS_MAXY, 0, tft.height()); 
  TS_Point ende;
  int8_t timer=0;
  int16_t x_diff, y_diff;
  for(int zaehler=0; zaehler<=40&&timer<LONGPRESS_TIME; zaehler++)
  {
    while(ts.touched())
    {     
      ende = ts.getPoint();
      ende.x = map(ende.x, TS_MINX, TS_MAXX, 0, tft.width());
      ende.y = map(ende.y, TS_MINY, TS_MAXY, 0, tft.height()); 
      delay(TOUCH_DELAY);
      if(timer++>LONGPRESS_TIME)
        break;       
    }
    delay(1);                
  }
  /*x_diff = abs(anfang.x-ende.x);
  y_diff = abs(anfang.y-ende.y);
  Serial.println("____");
  Serial.println(anfang.y);
  Serial.println(ende.y);
  Serial.println(anfang.y-ende.y);
  if(sqrt(x_diff*x_diff+y_diff*y_diff)>SWIPE_DIST)
  {
    if((anfang.x-ende.x)<0)
      return NEXT_PAGE;
    else
      return PREV_PAGE;
  }
  else if(timer>LONGPRESS_TIME)
    return LONG_PRESS;
  else
    return TITLE_PRESS;*/
  if(ende.x>(tft.height()-RECT_DIST-12))//(tft.width()-(CLOCK_Y+CLOCK_SIZE*7+10)))
  {
    if(ende.y>tft.height()/2)
      return NEXT_PAGE;
    else
      return PREV_PAGE;
  }
  else
  {  
    if(timer>LONGPRESS_TIME)
      return LONG_PRESS;
    else
      return TITLE_PRESS;
  }
  #endif
}