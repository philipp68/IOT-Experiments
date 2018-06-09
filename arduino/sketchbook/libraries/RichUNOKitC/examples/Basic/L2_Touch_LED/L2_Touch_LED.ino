/************************************************* *************************************************
* OPEN-SMART Rich UNO Kit C Lesson 2: Touch and LED
* You can learn about the touch sensor (T) control method, how to turn on and turn off the LED. 
*
* The following functions are available:
*
* led.on();//turn on the led
* led.off();//turn off the led
* touch.get(); // return HIGH or LOW

*********************************************************************************************************/
/***********************************CHINESE********************************************************
* OPEN-SMART Rich UNO Kit C 第2课： 触摸和灯
* 您可以了解锁存型触摸传感器控制方法，如何打开和关闭LED。
* 本节用到的锁存型触摸传感器Touch Sensor(T) 可以通过板载AHLB开关修改上电时的默认电平，拨到L处就是默认低电平，
      每次触摸电平都会改变，就像一个开关
* 
* 以下函数是本节用到的：
*
* led.on();//打开灯
* led.off();//关灯
* touch.get(); //返回高电平或低电平

*********************************************************************************************************/
#include <Wire.h>
#include <SoftwareSerial.h>

#include "RichUNOKitCLED.h"
#include "RichUNOKitCSwitch.h" 


#define LED_PIN 9          //LED connect to D9 of Arduino, 9 is pwm pin
LED led(LED_PIN);         

#define TOUCH_PIN A2      //SIG pin of Touch Sensor (T) module connect to A2 of IO Shield, that is pin A2 of Arduino 
Switch touch(TOUCH_PIN);  //please push the AHLB switch to L side on the Touch Sensor(T) module

void setup()
{

}

void loop()
{
  if(touch.get()) led.on();//if it get high level, turn on the LED
  else led.off();           //otherwise, turn off the LED
}

/*********************************************************************************************************
The end of file
*********************************************************************************************************/
