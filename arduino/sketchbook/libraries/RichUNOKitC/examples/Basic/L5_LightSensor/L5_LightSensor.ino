/************************************************* *************************************************
* OPEN-SMART Rich UNO Kit C Lesson 5:  Light Sensor
* You can learn how to know the ambient light is dark or bright. 
*
* The following functions are available:
*
* lightsensor.get();//it return the resistance of the light sensor, the darker the ambient light, the larger the resistance.
*
************************************************** ************************************************** *****/
/***************************************CHINESE********** *************************************************
* OPEN-SMART Rich UNO Kit C 第5课:  光敏传感器
* 可以了解环境光究竟是暗还是亮
*
* 以下函数是本节用到的：
*
* lightsensor.get();//返回光敏电阻的阻值，环境越暗，阻值越大；环境越亮，阻值越小；.
*
************************************************** ************************************************** *****/
#include <math.h>
#include <Wire.h>
#include <SoftwareSerial.h>

#include "RichUNOKitCLightSensor.h"

#define LIGHTSENSOR_PIN A0//SIG pin of Rocker Switch module connect to A0 of IO Shield, that is pin A0 of Arduino
LightSensor lightsensor(LIGHTSENSOR_PIN);

void setup() {
  Serial.begin(9600); //Set baud rate of serial port to be 9600bps, burn the program and open the serial monitor 
                     //on the upper right corner of Arduino IDE to check the sensor data.
}
void loop() {
  float Rsensor = lightsensor.getRes();//if Rsensor is larger than 40 KOhm, the ambient light is very dark.
                                       //if Rsensor is smaller than 10 KOhm, the ambient light is bright.
  Serial.println("The resistance of the Light sensor is "); 
  Serial.print(Rsensor,1);
  Serial.println(" KOhm");
  float lux;
  lux = 325*pow(Rsensor,-1.4);
  Serial.print("Illuminance is almost "); // may be it is not exactly right
  Serial.print(lux,1);
  Serial.println(" lux");
  delay(1000);  
}

/*********************************************************************************************************
The end of file
*********************************************************************************************************/