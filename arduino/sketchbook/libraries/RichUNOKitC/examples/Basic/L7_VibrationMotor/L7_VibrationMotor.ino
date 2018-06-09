/************************************************* *************************************************
* OPEN-SMART Rich UNO Kit C Lesson 7:  Vibration Motor
* You can learn how to control the vibration motor. 
*
* The following functions are available:
*
* vibration.on();//Turn on vibration
* vibration.off();//Turn off vibration
* touch.get(); // return HIGH or LOW
*
************************************************** ************************************************** *****/
/***************************************CHINESE********** *************************************************
* OPEN-SMART Rich UNO Kit C 第7课: 振动电机
* 可以了解如何控制振动电机
*
* 以下函数是本节用到的：
*
* vibration.on();//开启振动
* vibration.off();//停止振动
* touch.get(); //返回高电平或低电平
*
************************************************** ************************************************** *****/
#include <Wire.h>
#include <SoftwareSerial.h>

#include "RichUNOKitCSwitch.h"
#include "RichUNOKitCVibration.h"

#define VibrationMotor_PIN 9//the SIG pin of the module is connected with D9 of Arduino / OPEN-SMART UNO
Vibration vibration(VibrationMotor_PIN);

#define TOUCH_PIN A2 //SIG pin of Touch Sensor (T) module connect to A2 of IO Shield, that is pin A2 of Arduino 
Switch touch(TOUCH_PIN);  //please push the AHLB switch to L side on the Touch Sensor(T) module

void setup()
{
  
}
void loop()
{
  if(touch.get()) vibration.on();
  else vibration.off();
}
											
/*********************************************************************************************************
The end of file
*********************************************************************************************************/