extern int8_t HAL_IO_RADIO_IRQ;

void dispatchBluetooth()
{
	#ifdef BLUETOOTH
   // Tell the nRF8001 to do whatever it should be working on.
  BTLEserial.pollACI();

  // Ask what is our current status
  aci_evt_opcode_t status = BTLEserial.getState();
  // If the status changed....
  if (status != laststatus) 
  {
    // print it out!
    if (status == ACI_EVT_DEVICE_STARTED) 
        Serial.println(F("* Advertising started"));
    if (status == ACI_EVT_CONNECTED) 
        Serial.println(F("* Connected!"));
    if (status == ACI_EVT_DISCONNECTED) 
        Serial.println(F("* Disconnected or advertising timed out"));
    // OK set the last status change to this one
    laststatus = status;
  }

  if (status == ACI_EVT_CONNECTED) 
  {
    // Lets see if there's any data for us!
    if (BTLEserial.available()) 
      Serial.print("* "); Serial.print(BTLEserial.available()); Serial.println(F(" bytes available from BTLE"));

    // OK while we still have something to read, get a character and print it out
    while (BTLEserial.available()) 
    {
      char c = BTLEserial.read();
      Serial.print(c);
    }
  }
  #endif
}