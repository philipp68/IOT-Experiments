#ifndef BackgroundAnimation_h
#define BackgroundAnimation_h

#include "Arduino.h"
#include "PixelDisplay.h"

class BackgroundAnimation {
    public:
        BackgroundAnimation() {
          _previousMillis = 0;
          _state = STATE_BLINKING;
        }

        void setCallback(void (*update_callback)()) {
          OnUpdateView = update_callback;
        }

        void setAnimationState(uint8_t state) {
          _state = state;
          //_currentFrame = 0;
        }

        void startOver() {
          _currentFrame = 0;
          _showNextFrameFor = 0;
        }

        void play() {
          unsigned long currentMillis = millis();
          unsigned long interval = _showNextFrameFor;
         
   
          if((currentMillis - _previousMillis >= interval)) {
              if(_state == STATE_BLINKING) {         
                switch(_currentFrame) {
                  case 0 : 
                    PixelDisplay::setImgFromProgmem(EyesFront);
                    _showNextFrameFor = 2000;
                    _currentFrame++; 
                  break;
                  case 1 : 
                    PixelDisplay::setImgFromProgmem(EyesBlink);
                    _showNextFrameFor = 300;
                    _currentFrame++;  
                  break;
                  case 2 :
                    PixelDisplay::setImgFromProgmem(EyesFront);
                    _showNextFrameFor = 5000;
                    _currentFrame++;  
                  break;
                  case 3 :
                    PixelDisplay::setImgFromProgmem(EyesBlink);
                    _showNextFrameFor = 200;
                    _currentFrame++; 
                  break;
                  case 4 :
                    PixelDisplay::setImgFromProgmem(EyesFront);
                    _showNextFrameFor = 200;
                    _currentFrame++;
                  break;
                  case 5 :
                    PixelDisplay::setImgFromProgmem(EyesBlink);
                    _showNextFrameFor = 100;
                    _currentFrame++; 
                  break;
                  case 6 :
                    PixelDisplay::setImgFromProgmem(EyesFront);
                    _showNextFrameFor = 4000;
                    _currentFrame = 0;
                  break;
                 }
              }

              if(_state == STATE_LOOKING_UP) {         
                switch(_currentFrame) {
                  case 0 : 
                    PixelDisplay::setImgFromProgmem(EyesUpRight);
                    _showNextFrameFor = 800;
                    _currentFrame++; 
                  break;
                  case 1 : 
                    PixelDisplay::setImgFromProgmem(EyesUpLeft);
                    _showNextFrameFor = 800;
                    _currentFrame = 0;  
                  break;
                  break;
                  default:
                    _currentFrame = 0;
                  break;
  
                 }
              }

              if(_state == STATE_EYES_CLOSED) {         
                switch(_currentFrame) {
                  case 0 : 
                    PixelDisplay::setImgFromProgmem(EyesSleepy01);
                    _showNextFrameFor = 300;
                    _currentFrame++;  
                  break;
                  case 1 :
                    PixelDisplay::setImgFromProgmem(EyesSleepy02);
                    _showNextFrameFor = 300;
                    _currentFrame++;  
                  break;
                  case 2 :
                    PixelDisplay::setImgFromProgmem(EyesAsleep);
                    _showNextFrameFor = 1000;
                    _currentFrame = 2; 
                  break;
                  default:
                    _currentFrame = 0;
                  break;
  
                 }
              }

              if(_state == JUMPING_JHONNY) {        
                switch(_currentFrame) {
                  case 0 : 
                    PixelDisplay::setImgFromProgmem(Jump01);
                    _showNextFrameFor = 150;
                    _currentFrame++;   
                  break;
                  case 1 :
                    PixelDisplay::setImgFromProgmem(Jump02);
                    _showNextFrameFor = 150;
                    _currentFrame++;
                  break;
                  case 2 :
                    PixelDisplay::setImgFromProgmem(Jump03);
                    _showNextFrameFor = 150;
                    _currentFrame++;  
                  break;
                  case 3 :
                    PixelDisplay::setImgFromProgmem(Jump04);
                    _showNextFrameFor = 150;
                    _currentFrame++;  
                  break;
                  case 4 :
                    PixelDisplay::setImgFromProgmem(Jump03);
                    _showNextFrameFor = 150;
                    _currentFrame++;  
                  break;
                  case 5 :
                    PixelDisplay::setImgFromProgmem(Jump05);
                    _showNextFrameFor = 150;
                    _currentFrame++;  
                  break;
                  case 6 :
                    PixelDisplay::setImgFromProgmem(Jump06);
                    _showNextFrameFor = 150;
                    _currentFrame++;  
                  break;
                  case 7 :
                    PixelDisplay::setImgFromProgmem(Jump07);
                    _showNextFrameFor = 150;
                    _currentFrame++;  
                  break;
                  case 8 :
                    PixelDisplay::setImgFromProgmem(Jump08);
                    _showNextFrameFor = 200;
                    _currentFrame++;  
                  break;
                  case 9 :
                    PixelDisplay::setImgFromProgmem(Jump08); // 09
                    _showNextFrameFor = 150;
                    _currentFrame++;  
                  break;
                  case 10 :
                    PixelDisplay::setImgFromProgmem(Jump08);
                    _showNextFrameFor = 150;
                    _currentFrame++;  
                  break;
                  case 11 :
                    PixelDisplay::setImgFromProgmem(Jump07);
                    _showNextFrameFor = 150;
                    _currentFrame++;  
                  break;
                  case 12 :
                    PixelDisplay::setImgFromProgmem(Jump06);
                    _showNextFrameFor = 150;
                    _currentFrame++;  
                  break;
                  case 13 :
                    PixelDisplay::setImgFromProgmem(Jump01);
                    _showNextFrameFor = 150;
                    _currentFrame = 0;  
                  break;
                  default:
                    _currentFrame = 0;
                  break;
  
                 }
              }
             
             _previousMillis = currentMillis;

             if(OnUpdateView != NULL) {
                 OnUpdateView();
             }
          }                
        }

        void (*OnUpdateView)();

        static const uint8_t STATE_BLINKING = 0;
        static const uint8_t STATE_LOOKING_UP = 1;
        static const uint8_t STATE_EYES_CLOSED = 2;
        static const uint8_t JUMPING_JHONNY = 3;
        
    private:        
        unsigned long _previousMillis;

        unsigned long _showNextFrameFor = 2000;

        uint8_t _state;
        uint8_t _currentFrame = 0;
        
   
};

#endif
