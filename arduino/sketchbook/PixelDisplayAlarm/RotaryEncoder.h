#ifndef RotaryEncoder_h
#define RotaryEncoder_h

#include "Arduino.h"

class RotaryEncoder {
    public:
        RotaryEncoder(const int CLK, const int DT, const int BUTTON) {
          _CLK = CLK;
          _DT = DT;
          _BUTTON = BUTTON;
          
          pinMode (_CLK, INPUT);
          pinMode (_DT, INPUT);
          pinMode (_BUTTON, INPUT);
          
          _CLKLast = digitalRead(_CLK);  // last position
        }

        void setRotationCallback(void (*rotation_callback)(int value)) {
          OnRotation = rotation_callback;
        }

        void setPressedCallback(void (*pressed_callback)()) {
          OnPressed = pressed_callback;
        }

        void setInitial(int value) {
          _encoderPosCount = value;
        }

        void setMax(int max) {
          _max = max;
        }

        void setMin(int min) {
         _min = min;
        }

        void setStepSize(uint8_t stepSize) {
          _stepSize = stepSize;
        }

        void startOver(boolean value) {
          _startOver = value;
        }

        void read() {
          // read button state
          _buttonPressed = digitalRead(_BUTTON);
          if(_buttonPressed == 0) {
            if(OnPressed != NULL) {
              OnPressed();
              delay(500);
            }
          }

          // read rotary position
          _aVal = digitalRead(_CLK);
          if (_aVal != _CLKLast) { // Means the knob is rotating
                                   // if the knob is rotating, we need to determine direction
                                   // We do that by reading pin B.
            if(!_aVal) {  // aVal is false or 0 then proceed. This prevents double incrementation.
              if (digitalRead(_DT) != _aVal) { // Means pin A Changed first – We’re Rotating Clockwise
                if((_startOver == true) && (_encoderPosCount == _max)) {
                  _encoderPosCount = _min;  
                } else if(_encoderPosCount < _max) {
                  if((_encoderPosCount + _stepSize) > _max) {
                    _encoderPosCount = _max;
                  } else {
                    _encoderPosCount = _encoderPosCount + _stepSize;
                  }
                }
                
                _bCW = true;
              } else { // Otherwise B changed first and we’re moving CCW
                 if((_startOver == true) && (_encoderPosCount == _min)) {
                  _encoderPosCount = _max;
                 } else if(_encoderPosCount > _min) {
                   if((_encoderPosCount - _stepSize) < _min) {
                    _encoderPosCount = _min;
                   } else {
                    _encoderPosCount = _encoderPosCount - _stepSize;
                   }
                 }
                _bCW = false;
             }
            }
            if(OnRotation != NULL) {
              OnRotation(_encoderPosCount);
            }
          }
          _CLKLast = _aVal;
        }

        void (*OnRotation)(int value);
        void (*OnPressed)();
        
    private:
        int _CLK; // pin for CLK
        int _DT;  // pin for DT
        int _BUTTON; // pin for button press
        int _encoderPosCount = 0; // number encoder will start with
        boolean _buttonPressed = false;  // true if button is pressed
        
        int _min = 0;
        int _max = 100;
        boolean _startOver = false;
        uint8_t _stepSize = 1;
        
        int _CLKLast;
        int _aVal;
        boolean _bCW;

};

#endif
