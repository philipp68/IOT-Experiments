/************************************************* *************************************************
* OPEN-SMART Rich UNO Kit C Lesson 1: Touch and sound
* You can learn about the touch pad control method, how to turn on and turn off the buzzer. 
*
* The following functions are available: 
*
* buzzer.on();//turn on the buzzer
* buzzer.off();//turn off the buzzer
* touch.get(); // return is the touch area corresponding Arduino pin number, if not then return -1
* touch.getLongPress(); // return long press the corresponding Arduino pin number, if not return -1
*
************************************************** ************************************************** *****/
/*************************************CHINESE************ *************************************************
* OPEN-SMART Rich UNO Kit C 第1课：触摸与发声
* 你可以学到触摸面板的控制方法和有源蜂鸣器的控制
*
* 以下函数是本节用到的：
*
* buzzer.on();//打开蜂鸣器发声
* buzzer.off();//关闭蜂鸣器
* touch.get(); // 返回触摸区域对应的Arduino引脚号，都没有触摸则返回-1
* touch.getLongPress(); //返回长时间触摸的触摸区域对应的Arduino引脚号，都没有触摸则返回-1
*
************************************************** ************************************************** *****/
#include <Wire.h>
#include <SoftwareSerial.h>

#include "RichUNOKitCTouchSensor.h"
#include "RichUNOKitCBuzzer.h"

#define BUZZER_PIN 9         //SIG pin of Buzzer module connect to D9 of Arduino
Buzzer buzzer(BUZZER_PIN);    

#define TOUCH_OUT1 3//out1-TCH1 area corresponds to turn on the buzzer
#define TOUCH_OUT2 4//out2-TCH2 area corresponds to turn off the buzzer
#define TOUCH_OUT3 5//out3-TCH3 area not use now
#define TOUCH_OUT4 6//out4-TCH4 area not use now
TouchSensor touch(TOUCH_OUT1,TOUCH_OUT2, TOUCH_OUT3,TOUCH_OUT4); //定义4路触摸板对象


void setup()
{
  
}

void loop()
{
  int button;
  button = touch.get();
  if(button == TOUCH_OUT1) //if touch the TCH1 area
  {
    buzzer.on();//turn on the buzzer
  }
  else if(button == TOUCH_OUT2) //if touch the TCH2 area
  {
    buzzer.off();//turn off the buzzer
  }
  else if(button == TOUCH_OUT3) 
  {
  
  }
  else if(button == TOUCH_OUT4) 
  {
  }
 
  delay(50);//delay 50ms and then detect whether someone touch
}

/*********************************************************************************************************
The end of file
*********************************************************************************************************/
