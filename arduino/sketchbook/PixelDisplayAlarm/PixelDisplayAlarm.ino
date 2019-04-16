#include "PixelDisplay.h"
#include "RotaryEncoder.h"
#include "ProgMemImages.h"
#include "RealTimeClock.h"
#include "Buzzer.h"
#include "Pitches.h"
#include "Alarm.h"
#include "Melody.h"
#include "BackgroundAnimation.h"

RotaryEncoder reLeft(4,5,6);
RotaryEncoder reRight(7,8,9);
RealTimeClock realTimeClock;
Buzzer buzzer(10);
Melody melody(&buzzer);
BackgroundAnimation backgroundAnimation;

void setup() {
  Serial.begin(9600);
  Wire.begin();
  
  realTimeClock.begin();
  realTimeClock.setCallbacks(&(Alarm::updateHours), &(Alarm::updateMinutes), &(Alarm::updateSeconds));

  reLeft.setRotationCallback(&(Alarm::rotatedLeft));
  reLeft.setPressedCallback(&(Alarm::pressedLeft));
  
  reRight.setRotationCallback(&(Alarm::rotatedRight));
  reRight.setPressedCallback(&(Alarm::pressedRight));

  backgroundAnimation.setCallback(&(Alarm::updateBackground));

  PixelDisplay::setup();

  Alarm::retrieveFromEEProm();
  Alarm::setRotaryEncoderLeft(&reLeft);
  Alarm::setRotaryEncoderRight(&reRight);
  Alarm::updateRotaryEncoderForBrightness();
  Alarm::setMelody(&melody);
  Alarm::setAnimation(&backgroundAnimation);

  
}

void loop() { 
  reLeft.read();
  reRight.read();
  realTimeClock.read();
  backgroundAnimation.play();
  Alarm::check();
}

