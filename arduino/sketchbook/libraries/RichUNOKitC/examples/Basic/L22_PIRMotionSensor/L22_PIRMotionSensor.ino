/************************************************* *************************************************
* OPEN-SMART Rich UNO R3 Lesson 22: PIR motion sensor
* You can learn about the application of PIR motion sensor principle, turn on or turn off the LED
* according to the results of detection. 
* Note that the default settings for this PIR motion sensor module:
* Hold time (delay time): 2 seconds, you can adjust the potentiometer to modify
* Block time: 2.5 seconds, can not be modified

* The following functions are available:
*
* led.on();//turn on the led
* led.off();//turn off the led
* pir.get(); // return HIGH or LOW
*
************************************************** ************************************************** *****/
/***********************************CHINESE************** *************************************************
* OPEN-SMART Rich UNO R3 第22课: 人体红外感应
* 了解应用人体红外感应传感器的原理，根据感应的结果来操作开关灯。
* 注意这人体红外模块的默认设置:
* 保持时间（延时）：2秒，可以调节电位器来修改
* 封锁时间：2.5秒，不可修改
*
* 以下函数是本节用到的：
*
* led.on();//打开灯
* led.off();//关灯
* pir.get(); //返回高电平或低电平
*

************************************************** ************************************************** *****/
#include <Wire.h>
#include <SoftwareSerial.h>

#include "RichUNOKitCLED.h"
#include "RichUNOKitCSwitch.h"


#define LED_PIN 9     //LED connect to D9 of Arduino, 9 is pwm pin
LED led(LED_PIN);

#define PIR_PIN A2 
Switch pir(PIR_PIN);//Take away the white lid so you can see the pin name, the middle pin is OUT pin, connect to A2 IO Shield
                    //Of course you should supply power for it, GND to GND, VCC to 5V of IO Shield

void setup()
{
  
}

void loop()
{
  if(pir.get()) led.on();
  else led.off();
}

/*********************************************************************************************************
The end of file
*********************************************************************************************************/
