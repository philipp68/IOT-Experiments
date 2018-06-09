uint8_t read_IR()
{
  // detect clapping
  if(clapDetected())
  {
    return CLAP_DETECTED;
  }
  
  // read button input
  for(int8_t buttonNr = 0; buttonNr < NUMBER_OF_BUTTONS; buttonNr++)
  {
    buttonStates[buttonNr] = digitalRead(BUTTON_PIN[buttonNr]);
    
    if (buttonStates[buttonNr] == HIGH)
    {
      if (buttonNr == 0)
      {
        delay(200);
        return TOGGLE_ALARM;
      } 
      else if (buttonNr == 1)
      {
        delay(200);
        return PROGRAM_ALARM;
      }
      else if (buttonNr == 2)
      {
        delay(200);
        return INCREMENT;  
      }
      else if (buttonNr == 3)
      {
        delay(200);
        return DECREMENT;
      }
      else if (buttonNr == 4)
      {
        delay(200);
        return ALARM_SNOOZE;
      }
    }
  }

  // detected nothing
  return NONE;
}


