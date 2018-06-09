/************************************************* *************************************************
* OPEN-SMART Rich UNO Kit C Lesson 3: Breathing Light
* You can learn how to make breathing light. 
*
* The following functions are available:
*
* led.on();//turn on the led
* led.off();//turn off the led
* led.breathe(); // breathe(uint8_t speed = 1) default parameter is 1, and you can pass the number more than one to 
*                     // speed up the breath.
*
************************************************** ************************************************** *****/
/***********************************CHINESE************** *************************************************
* OPEN-SMART Rich UNO Kit C 第3课: 呼吸灯
* 可以了解如何制作呼吸灯 
*
* 以下函数是本节用到的：
*
* led.on();//打开灯
* led.off();//关灯
* led.breathe(); // breathe(uint8_t speed = 1)默认参数为1，您可以将传递比1更大的参数来加快呼吸速度
*
************************************************** ************************************************** *****/
#include <Wire.h>
#include <SoftwareSerial.h>

#include "RichUNOKitCLED.h"

#define LED_PIN 9          //LED connect to D9 of Arduino, 9 is pwm pin
LED led(LED_PIN);          

void setup()
{
  led.on(); 
  delay(500);
  led.off();
  delay(1000);
}

void loop()
{
  led.breathe(); //The default speed is 3 seconds to breathe once
}

/*********************************************************************************************************
The end of file
*********************************************************************************************************/