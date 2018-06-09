#ifndef __RichUNOKitC_LIGHTSENSOR_H__
#define __RichUNOKitC_LIGHTSENSOR_H__

#include <Arduino.h>

class LightSensor{

private:

    uint8_t _pin;

public:

    LightSensor(uint8_t pin)
    {
      _pin = pin;
      pinMode(_pin, INPUT);
    }
    
   float getRes()
   {
     int sensorValue = analogRead(A0);
     float Rsensor;
     Rsensor=(float)(1023-sensorValue)*10/sensorValue;
	 return Rsensor;//unit is KOhm
   }
};

#endif
/*********************************************************************************************************
  END FILE
*********************************************************************************************************/