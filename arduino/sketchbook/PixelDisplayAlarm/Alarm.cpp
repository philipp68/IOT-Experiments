#include "Alarm.h"
#include "PixelDisplay.h"
#include <EEPROM.h>


// initialize static members
uint8_t Alarm::_alarmHours = 12;
uint8_t Alarm::_alarmMinutes = 0;
uint8_t Alarm::_alarmSnoozeTime = 0;
uint8_t Alarm::_hours = 0;
uint8_t Alarm::_minutes = 0;
uint8_t Alarm::_seconds = 0;
uint8_t Alarm::_state = STATE_NORMAL;
uint8_t Alarm::_defaultDaytimeBrightness = 50;
uint8_t Alarm::_defaultNighttimeBrightness = 5;
uint8_t Alarm::_alarmBrightness = 50;
RotaryEncoder* Alarm::_rotaryEncoderLeft = NULL;
RotaryEncoder* Alarm::_rotaryEncoderRight = NULL;
Melody* Alarm::_melody = NULL;
BackgroundAnimation* Alarm::_animation = NULL;

// handle button events
static void Alarm::eventHandler(uint8_t event) {
  switch(event) {
   case  EV_PRESSLEFTBUTTON  :
      if(_state == STATE_NORMAL) {
        _state = STATE_ARMED;
        _alarmSnoozeTime = 0;
        _animation->startOver();
        _animation->setAnimationState(BackgroundAnimation::STATE_EYES_CLOSED);
        // initialize rotary encoder with values for brightness adjustments
        updateRotaryEncoderForBrightness(); 
        storeInEEProm();
        updateForeground();
        return;
      }
      if((_state == STATE_ALARM_IMMINENT) || (_state == STATE_ARMED) || (_state == STATE_ALARM_SNOOZED) || (_state == STATE_ALARM_ON)) {
        _state = STATE_NORMAL;
        _animation->startOver();
        _animation->setAnimationState(BackgroundAnimation::STATE_BLINKING);
        updateRotaryEncoderForBrightness();
        updateForeground();
        return;
      }
      break;
   case EV_PRESSRIGHTBUTTON :
      if(_state == STATE_NORMAL) {
        _state = STATE_SET_ALARM;
        _animation->startOver();
        _animation->setAnimationState(BackgroundAnimation::STATE_LOOKING_UP);
        // use rotary encoders to adjust time
        _rotaryEncoderLeft->setInitial(_alarmHours);
        _rotaryEncoderLeft->setMax(23);
        _rotaryEncoderLeft->setMin(0);
        _rotaryEncoderLeft->startOver(true);
        _rotaryEncoderLeft->setStepSize(1);
        _rotaryEncoderRight->setInitial(_alarmMinutes);
        _rotaryEncoderRight->setMax(59);
        _rotaryEncoderRight->setMin(0); 
        _rotaryEncoderRight->startOver(true);
        _rotaryEncoderRight->setStepSize(1);
        updateForeground();
        return;
      }
      if((_state == STATE_SET_ALARM) || (_state == STATE_ALARM_IMMINENT) || (_state == STATE_ARMED) || (_state == STATE_ALARM_SNOOZED) || (_state == STATE_ALARM_ON)) {
        _state = STATE_NORMAL;
        _animation->startOver();
        _animation->setAnimationState(BackgroundAnimation::STATE_BLINKING);
        updateRotaryEncoderForBrightness();
        updateForeground();
        return;
      }
      break;
  }
}

static void Alarm::setRotaryEncoderLeft(RotaryEncoder* reLeft) {
  _rotaryEncoderLeft = reLeft;
}

static void Alarm::setRotaryEncoderRight(RotaryEncoder* reRight) {
  _rotaryEncoderRight = reRight;
}

static void Alarm::setMelody(Melody* melody) {
  _melody = melody;
}

static void Alarm::setAnimation(BackgroundAnimation* animation) {
  _animation = animation;
}

static void Alarm::rotatedLeft(int value) {
  //Serial.println("Alarm::RotatedLeft: " + String(value));
  if(_state == STATE_ALARM_ON) {
    _state = STATE_ALARM_SNOOZED;
    _alarmSnoozeTime = _alarmSnoozeTime + 8;
    updateView();
    return;
  } else if (_state == STATE_SET_ALARM) {
    _alarmHours = value;
    updateForeground();
    return;
  } else if (_state == STATE_ARMED) {
    _defaultNighttimeBrightness = value;
    updateDefaultNighttimeBrightness(value);
    return;
  } else if (_state == STATE_NORMAL) {
    _defaultDaytimeBrightness = value;
    updateDefaultDaytimeBrightness(value);
    return;
  } else if (_state == STATE_ALARM_SNOOZED) {
    // do nothing
    return;
  } else if (_state == STATE_ALARM_IMMINENT) {
    _state = STATE_ALARM_SNOOZED;
    _alarmSnoozeTime = _alarmSnoozeTime + 8;
    updateView();
    return;
  }
}

static void Alarm::pressedLeft() {
  //Serial.println("Alarm::PressedLeft!");
  eventHandler(EV_PRESSLEFTBUTTON);
}

static void Alarm::rotatedRight(int value) {
  //Serial.println("Alarm::RotatedRight: " + String(value));
  if(_state == STATE_ALARM_ON) {
    _state = STATE_ALARM_SNOOZED;
    _alarmSnoozeTime = _alarmSnoozeTime + 8;
    updateView();
    return; 
  } else if (_state == STATE_SET_ALARM) {
    _alarmMinutes = value;
    updateForeground();
    return;
  } else if (_state == STATE_ARMED) {
    _defaultNighttimeBrightness = value;
    updateDefaultNighttimeBrightness(value);
    return;
  } else if (_state == STATE_NORMAL) {
    // do nothing
    return;
  } else if (_state == STATE_ALARM_SNOOZED) {
    // do nothing
    return;
  } else if (_state == STATE_ALARM_IMMINENT) {
    _state = STATE_ALARM_SNOOZED;
    _alarmSnoozeTime = _alarmSnoozeTime + 8;
    updateView();
    return;
  }
}

static void Alarm::pressedRight() {
  //Serial.println("Alarm::PressedRight!");
  eventHandler(EV_PRESSRIGHTBUTTON);
}

static void Alarm::updateHours(uint8_t hours) {
  //Serial.println("Alarm::Hours: " + String(hours));
  _hours = hours;
  updateForeground();
}

static void Alarm::updateMinutes(uint8_t minutes) {
  //Serial.println("Alarm::Minutes: " + String(minutes));
  _minutes = minutes;
  updateForeground();
}

static void Alarm::updateSeconds(uint8_t seconds) {
  //Serial.println("Alarm::Seconds: " + String(seconds));
  _seconds = seconds;
}

static void Alarm::updateDefaultDaytimeBrightness(uint8_t brightness) {
  //Serial.println("updateDefaultDaytimeBrightness: " + String(brightness));
  PixelDisplay::setBrightness(brightness);
  _defaultDaytimeBrightness = brightness;
  PixelDisplay::show();
}

static void Alarm::updateAlarmBrightness(uint8_t brightness) {
  //Serial.println("updateAlarmBrightness: " + String(brightness));
  PixelDisplay::setBrightness(brightness);
  _alarmBrightness = brightness;
  PixelDisplay::show();
} 

static void Alarm::updateDefaultNighttimeBrightness(uint8_t brightness) {
  //Serial.println("updateDefaultNighttimeBrightness: " + String(brightness));
  PixelDisplay::setBrightness(brightness);
  _defaultNighttimeBrightness = brightness;
  PixelDisplay::show();
}

static void Alarm::updateRotaryEncoderForBrightness() {
  if(_rotaryEncoderLeft != NULL) {
    if(_state == STATE_NORMAL) {
      _rotaryEncoderLeft->setInitial(_defaultDaytimeBrightness);
    } else if(_state == STATE_ARMED) {
      _rotaryEncoderLeft->setInitial(_defaultNighttimeBrightness);
    } else if(_state == STATE_SET_ALARM) {
      _rotaryEncoderLeft->setInitial(_defaultDaytimeBrightness);
    }
    _rotaryEncoderLeft->setMax(200);
    _rotaryEncoderLeft->setMin(0);
    _rotaryEncoderLeft->setStepSize(1);
    _rotaryEncoderLeft->startOver(false);
  }
}

static void Alarm::updateView() {
  updateBackground();
  updateForeground(); 
}

static void Alarm::updateBackground() {
  // repaint foreground on top of background
  updateForeground();
}

static void Alarm::updateForeground() {
  //Serial.println("****** Alarm ******");
  //Serial.println("State               : " + String(_state));
  //Serial.println("Snoozing for        : " + String(_alarmSnoozeTime));
  //Serial.println("Daytime Brightness  : " + String(_defaultDaytimeBrightness));
  //Serial.println("Nighttime Brightness: " + String(_defaultNighttimeBrightness));
  if(_state == STATE_NORMAL) {
    displayTime(_hours, _minutes, 0x55513a, 0xfee761);
  } else if(_state == STATE_ARMED) {
    displayTime(_hours, _minutes, 0x887d3e, 0x55513a);
  } else if(_state == STATE_SET_ALARM) {
    displayTime(_alarmHours, _alarmMinutes, CRGB::Red, 0xfee761);
  }
  updateViewBrightness();
  PixelDisplay::show();
}

static void Alarm::updateViewBrightness() {
  if((_state == STATE_NORMAL )||(_state == STATE_SET_ALARM)||(_state == STATE_ALARM_ON)) {
    PixelDisplay::setBrightness(_defaultDaytimeBrightness);
  } else if((_state == STATE_ARMED)||(_state == STATE_ALARM_SNOOZED)) {
    PixelDisplay::setBrightness(_defaultNighttimeBrightness);
  } else if(_state == STATE_ALARM_IMMINENT) {
      if(_seconds != 0) {
        int brightness;
        brightness = map(_seconds, 1, 59, 5, 200);
        PixelDisplay::setBrightness(brightness);
      } 
  }
}

static void Alarm::displayTime(int hours, int minutes, CRGB foregroundColor, CRGB backgroundColor) {
  //Serial.println("Hours: " + String(hours) + " Minutes: " + String(minutes));
  int firstDigitHours = hours/10;
  int secondDigitHours = hours - firstDigitHours*10;
  PixelDisplay::printSingleDigit(1,11,firstDigitHours,foregroundColor, backgroundColor, true);
  PixelDisplay::printSingleDigit(5,11,secondDigitHours,foregroundColor, backgroundColor, true);
  PixelDisplay::printColon(7,11,foregroundColor,backgroundColor);
  
  int firstDigitMinutes = minutes/10;
  int secondDigitMinutes = minutes - firstDigitMinutes*10;         
  PixelDisplay::printSingleDigit(9,11,firstDigitMinutes,foregroundColor, backgroundColor, true);
  PixelDisplay::printSingleDigit(13,11,secondDigitMinutes,foregroundColor, backgroundColor, true);
  
}

static void Alarm::storeInEEProm() {
  // check if values fit into a byte
  if(_alarmHours <= 23 && _alarmMinutes <=59 && _defaultDaytimeBrightness <= 220) {
    EEPROM.update(0, _alarmHours);
    EEPROM.update(1, _alarmMinutes);
    EEPROM.update(2, _defaultDaytimeBrightness);
    EEPROM.update(3, _defaultNighttimeBrightness);
  }
}

static void Alarm::retrieveFromEEProm() {
  _alarmHours = EEPROM.read(0);
  _alarmMinutes = EEPROM.read(1);
  _defaultDaytimeBrightness = EEPROM.read(2);
  _defaultNighttimeBrightness = EEPROM.read(3);
}

static void Alarm::check() {
  int timeInMinutes = _hours * 60 + _minutes;
  int alarmInMinutes = _alarmHours *60 + _alarmMinutes + _alarmSnoozeTime;

  // go back to sleep...
  if(_state == STATE_ALARM_SNOOZED) {
    _animation->startOver();
    _animation->setAnimationState(BackgroundAnimation::STATE_EYES_CLOSED);
    _state = STATE_ARMED;
  }

  // get ready to wake up...
  uint8_t slowWakeUpInMinutes = 1;
  if(((timeInMinutes >= (alarmInMinutes - slowWakeUpInMinutes)) && (timeInMinutes <= alarmInMinutes)) && (_state == STATE_ARMED)) {
    _state = STATE_ALARM_IMMINENT;
    _animation->setAnimationState(BackgroundAnimation::JUMPING_JHONNY);
  }

  // time to wake up..
  if((timeInMinutes == alarmInMinutes) && (_state == STATE_ALARM_IMMINENT)) {
    _state = STATE_ALARM_ON;
  }
  
  // sound the alarm
  if(Alarm::_state == STATE_ALARM_ON) {
    _melody->sound();
    _animation->setAnimationState(BackgroundAnimation::JUMPING_JHONNY);
  }
}

