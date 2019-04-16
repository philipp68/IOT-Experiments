#ifndef Buzzer_h
#define Buzzer_h

#include "Arduino.h"
#include "Pitches.h"

class Buzzer {
    public:
        Buzzer(const int pin) {
          _pin = pin;
        }

        void buzz(int frequency) {
          tone(_pin, frequency);
        }

        void buzz(int frequency, int interval) {
          tone(_pin, frequency, interval);
        }

        // duration quarter note = , eighth note = 8
        // check pitches.h for NOTE pitches
        void playNote(int pitch, int duration) { 
          int noteDuration = 1000 / duration;
          tone(_pin, pitch, noteDuration);
          // to distinguish the notes, set a minimum time between them.
          // the note's duration + 30% seems to work well:
          int pauseBetweenNotes = noteDuration * 1.30;
          delay(pauseBetweenNotes);
          // stop the tone playing:
          noTone(_pin);
        }
        
    private:
        uint8_t _pin; // pin buzzer is connected to

};

#endif
