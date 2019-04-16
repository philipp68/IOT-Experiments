#ifndef Melody_h
#define Melody_h

#include "Arduino.h"
#include "Buzzer.h"
#include "Pitches.h"

class Melody {
    public:
        Melody(Buzzer *buzzer) {
          _buzzer = buzzer;
          _previousMillis = 0;
        } 

        void sound() {
          int noteDuration = 1000 / _noteDurations[_note];
        
          unsigned long currentMillis = millis();
   
          if((currentMillis - _previousMillis >= _interval)) {
            
            _buzzer->playNote(_melody[_note], noteDuration);
            _interval = noteDuration * 1.30;
            
            _note = _note + 1;
            if(_note == 8) {
              _note = 0;
              _interval = 1500;
            }
            
            _previousMillis = currentMillis;
          }             
        }
        
    private:
        Buzzer* _buzzer;
        unsigned long _previousMillis;
        int _interval = 1500;
        int _note = 0;
           
        int _melody[8] = { NOTE_C4, NOTE_G3, NOTE_G3, NOTE_A3, NOTE_G3, 0, NOTE_B3, NOTE_C4 };
        int _noteDurations[8] = { 4, 8, 8, 4, 4, 4, 4, 4 };
   
};

#endif
