//Low-Level Stuff
volatile uint16_t isr_counter;      //The current number of Timer-Interrupt-Overflows since the last second
volatile bool time_changed=true;    //Gets true if the secon changes

//The actual time paŕt
volatile uint8_t hour=0;            //Number of hours 
volatile uint8_t minute=0;          //Number of minutes
volatile int8_t second=0;           //Number of seconds
            

//Stopwatch
volatile uint8_t hour_stop=0;       //Number of hours 
volatile uint8_t minute_stop=0;     //Number of minutes
volatile int8_t second_stop=0;      //Number of seconds
volatile uint16_t isr_counter_stop; //The current number of Timer-Interrupt-Overflows since the last second
volatile bool stopped=true;         //Those are true if the Stopwatch got stopped

//Alarm
volatile uint8_t hour_alarm=0;      //The hour of the alarm
volatile uint8_t minute_alarm=0;    //The minute of the alarm
volatile uint8_t second_alarm=0;    //The second of the alarm
volatile bool enabled_alarm = false;//A boolean if the Alarm is enabled

uint8_t used = 0;                   //Check if the watch had been used the last minute

//##################################################
//##################################################
//
//        #   ####  #####
//        #   #     #   #
//        #   ####  #####
//        #      #  #  #
//        #   ####  #   #
//
//##################################################
//##################################################

ISR(TIMER2_OVF_vect)              //Timer-Interrupt            
{

  //###################
  //      Clock
  //###################
  if(isr_counter++>SECOND_OVERFLOW)//Overflow of the Timer-Interrupt-Clock-Timer (means new second)
  {
    second++;                     //add a second
    isr_counter-=SECOND_OVERFLOW; //reset timer-timer
    time_changed=true;            //set a boolean to high, that forces the ui to redraw
    if(enabled_alarm)             //check if a alarm is enabled
    {
        if(hour==hour_alarm&&minute==minute_alarm&&second==second_alarm)//check if the alarm is now
        {
                                  //alert the user
        }
    }
    #ifndef TOUCH
    if(used>TIMEOUT)              //Check if the time since the last interaction is longer than the timeout (standby)
      analogWrite(3, LOW_BRIGHTNESS);//Lower the brightness
    else                          //If the time since the last interaction is smaller than the timeout (means still active)
      used++;                     //Increment the used timer
    #endif
  }

  if(second>=60)                  //check if this is the 60th second
  {
    second-=60;                   //reset second counter
    minute++;                     //add a  minute     
  }
  if(minute>=60)                  //check if it is the 60th minute 
  {
    minute-=60;                   //reset minute counter
    hour++;                       //add a hour
    second--;                     //just some correction to make the watch more accurate
  }
  if(hour>=24)                    //check if this is the 24th hour
    hour-=24;                     //reset hours (no need to count days)

  //###################
  //    Stopwatch
  //###################
  if(!stopped)                    //Check if Stopwatch is running                
  {
    if(isr_counter_stop++>973)    //Overflow of the Timer-Interrupt-Stopwatch-Timer
    {
      second_stop++;              //Add a second
      isr_counter_stop-=SECOND_OVERFLOW;//reset counter       
    }
    if(second_stop>=60)           //Check if it is the 60th second          
    {
      second_stop-=60;            //reset second counter
      minute_stop++;              //add a  minute
    }
    if(minute_stop>=60)           //check if it is the 60th minute 
    {
      minute_stop-=60;            //reset minute counter
      hour_stop++;                //add a hour
      second_stop--;              //just some correction to make the stopwatch more accurate
    }
    if(hour_stop>=24)             //check if this is the 24th hour
      hour_stop-=24;              //reset hours (no need to count days)
  }
};

void clockInterruptInit()         //Initialise the Timer Interrupt
{
  //Timer2 Settings: Timer Prescaler /64,
  TCCR2B |= (1<<CS22); 
  TCCR2B &= ~((1<<CS21) | (1<<CS20));     
  TCCR2A &= ~((1<<WGM21) | (1<<WGM20));   
  TCCR2B &= ~(1<<WGM22);                 
  ASSR |= (0<<AS2);
  TIMSK2 |= (1<<TOIE2) | (0<<OCIE2A);  
  TCNT2 = 6;    
}