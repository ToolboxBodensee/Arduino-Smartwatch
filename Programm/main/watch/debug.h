#ifdef DEBUG
int freeRam () 
{
  extern int __heap_start, *__brkval; 
  int v; 
  return (int) &v - (__brkval == 0 ? (int) &__heap_start : (int) __brkval); 
}

void sendDebugData()
{
	#ifdef RAM_DEBUG
	Serial.println(freeRam());
	#endif   
	#ifdef TIMOUT_DEBUG
	Serial.println(used);
	#endif
	#ifdef STOPPED_DEBUG
	Serial.println(stopped);
	#endif
}
#endif