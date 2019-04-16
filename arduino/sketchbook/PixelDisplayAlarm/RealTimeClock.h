#ifndef RealTimeClock_h
#define RealTimeClock_h

#include "Arduino.h"
#include <Wire.h>
#include "RTClib.h"

class RealTimeClock {
    public:
        RealTimeClock() {
          _previousMillis = 0;   
        }

        void setCallbacks(void (*hours_callback)(int hours), void (*minutes_callback)(int minutes), void (*seconds_callback)(int seconds)) {
          OnHours = hours_callback;
          OnMinutes = minutes_callback;
          OnSeconds = seconds_callback;
        }

        void begin() {
          _rtc.begin();
          
          if (! _rtc.isrunning()) {
            Serial.println("RTC is NOT running!");
            // following line sets the RTC to the date & time this sketch was compiled
            _rtc.adjust(DateTime(__DATE__, __TIME__));
          }
        }

        void read() {
          unsigned long currentMillis = millis();
          
          if((currentMillis - _previousMillis >= _interval)) {
            DateTime now = _rtc.now();

            if((OnHours!=NULL) && (_hour!=now.hour())) {
              _hour = now.hour();  
              OnHours(_hour);
            }
            if((OnMinutes!=NULL) && (_minute!=now.minute())) {
              _minute = now.minute();
              OnMinutes(_minute); 
            }
            if((OnSeconds!=NULL) && (_second!=now.second())) {
              _second = now.second();
              OnSeconds(_second); 
            }
            _previousMillis = currentMillis;  
          }
        }

        void (*OnHours)(int hours);
        void (*OnMinutes)(int minutes);
        void (*OnSeconds)(int seconds);  

    private:
      DS3231 _rtc;
      unsigned long _previousMillis;
      int _interval = 500;
      /*
       * Resolution to bug which woke us at 01:00:
       * - set _hour/_minute/_second to an impossible default value
       * - this will force the initial callback for all values
       */
      uint8_t _hour = 100;
      uint8_t _minute = 100;
      uint8_t _second = 100;
};

#endif
