/************************************************* *************************************************
* OPEN-SMART Rich UNO Kit C Lesson 4: Rocker Switch
* You can learn how to use rocker switch to control LED.
*
* The following functions are available:
*
* led.on();//turn on the led
* led.off();//turn off the led
* Rockerswitch.get(); // return HIGH or LOW
*
************************************************** ************************************************** *****/
/****************************************CHINESE********* *************************************************
* OPEN-SMART Rich UNO Kit C 第4课: 船型开关
* 可以了解如何用船型开关控制灯
*
* 以下函数是本节用到的：
*
* led.on();//打开灯
* led.off();//关灯
* Rockerswitch.get(); //返回高电平或低电平
*
************************************************** ************************************************** *****/
#include <Wire.h>
#include <SoftwareSerial.h>

#include "RichUNOKitCLED.h"
#include "RichUNOKitCSwitch.h"


#define LED_PIN 9          //LED connect to D9 of Arduino, 9 is pwm pin
LED led(LED_PIN);

#define ROCKER_PIN A2 //SIG pin of Rocker Switch module connect to A2 of IO Shield, that is pin A2 of Arduino
Switch Rockerswitch(ROCKER_PIN);

void setup()
{
  
}

void loop()
{
  if(Rockerswitch.get()) led.on();
  else led.off();
}

/*********************************************************************************************************
The end of file
*********************************************************************************************************/
