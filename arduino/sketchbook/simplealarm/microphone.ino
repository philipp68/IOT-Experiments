void setupMicrophone()
{
  pinMode(digitalMicInput, INPUT);
}

bool clapDetected()
{
  // analog input
  noiseLevel = analogRead(analogMicInput);

  if(noiseLevel >= 522)
  {
    Serial.println (noiseLevel, DEC);
    return true;
  }
  else
  {
    Serial.println (noiseLevel, DEC);
    return false;
  }
  
}

