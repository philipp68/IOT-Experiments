#ifndef __RichUNOKitC_SWITCH_H__
#define __RichUNOKitC_SWITCH_H__

#include <Arduino.h>


class Switch{

private:

    uint8_t _pin;

public:

    Switch(uint8_t pin)
    {
      _pin = pin;
      pinMode(_pin, INPUT);
    }
    
    inline uint8_t get()                        
    {
      uint8_t level = digitalRead(_pin);
	  delay(10);
	  if(level == digitalRead(_pin))
      return level;
    }
};

#endif
/*********************************************************************************************************
  END FILE
*********************************************************************************************************/