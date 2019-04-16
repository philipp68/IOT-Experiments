#ifndef Alarm_h
#define Alarm_h

#include "Arduino.h"
#include "FastLED.h"
#include "RotaryEncoder.h"
#include "Melody.h"
#include "BackgroundAnimation.h"

class Alarm {
    public:
        static void setRotaryEncoderLeft(RotaryEncoder* reLeft);
        static void setRotaryEncoderRight(RotaryEncoder* reRight);
        static void setMelody(Melody *melody);
        static void setAnimation(BackgroundAnimation *animation);
        static void rotatedLeft(int value);
        static void pressedLeft();
        static void rotatedRight(int value);
        static void pressedRight();
        static void updateHours(uint8_t hours);
        static void updateMinutes(uint8_t minutes);
        static void updateSeconds(uint8_t seconds);
        static void updateAlarmBrightness(uint8_t brightness);
        static void updateRotaryEncoderForBrightness();
        static void eventHandler(uint8_t event);
        static void storeInEEProm();
        static void retrieveFromEEProm();

        static void check();

        static void updateView();
        static void updateViewBrightness();
        static void updateBackground();
        static void updateForeground();
        
        static void displayTime(int hours, int minutes, CRGB foregroundColor, CRGB backgroundColor);  

        static uint8_t _alarmHours;
        static uint8_t _alarmMinutes;
        static uint8_t _alarmSnoozeTime;
        static uint8_t _hours;
        static uint8_t _minutes;
        static uint8_t _seconds;
        static uint8_t _state;
        static uint8_t _alarmBrightness;

        static RotaryEncoder* _rotaryEncoderLeft;
        static RotaryEncoder* _rotaryEncoderRight;
        static Melody* _melody;
        static BackgroundAnimation* _animation;

        static const uint8_t EV_PRESSLEFTBUTTON = 1;
        static const uint8_t EV_PRESSRIGHTBUTTON = 2;

        static const uint8_t STATE_NORMAL = 0;
        static const uint8_t STATE_ARMED = 1;
        static const uint8_t STATE_SET_ALARM = 2;
        static const uint8_t STATE_ALARM_ON = 3;
        static const uint8_t STATE_ALARM_SNOOZED = 4;
        static const uint8_t STATE_ALARM_IMMINENT = 5;

};

#endif
