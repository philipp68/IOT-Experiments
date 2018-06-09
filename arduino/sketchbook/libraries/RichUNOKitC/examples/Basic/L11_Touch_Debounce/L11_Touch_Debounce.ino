/************************************************* ************************************************** ******
* OPEN-SMART Rich UNO R3 Lesson 11: Touch and debounce
* Learn about software debounce method to achieve the number increasing step by step.
*
* The following functions are available:
*
* touch.get(); / / return is the touch area corresponding Arduino pin number, if not then return -1
* touch.getLongPress(); / / return long press the corresponding Arduino pin number, if not return -1
*
* disp.init(); // initialization
* disp.display(int Decimal);   // display range: -999 ~ 9999
************************************************** ************************************************** *****/
/***********************************CHINESE************** ************************************************** ******
* OPEN-SMART Rich UNO R3 第11课: 触摸与防抖动
* 了解软件去抖动方法，实现数量的逐步增加。
*
* 以下函数是本节用到的：
*
* touch.get(); // 返回触摸区域对应的Arduino引脚号，都没有触摸则返回-1
* touch.getLongPress(); //返回长时间触摸的触摸区域对应的Arduino引脚号，都没有触摸则返回-1
*
* disp.init(); //初始化
* disp.display(int Decimal); //显示范围：-999~9999
************************************************** ************************************************** *****/
#include <Wire.h>
#include <SoftwareSerial.h>	
#include "RichUNOKitCTouchSensor.h"
#include "RichUNOKitCTM1637.h"
		
#define CLK 10//CLK of the TM1637 IC connect to D10 of Arduino
#define DIO 11//DIO of the TM1637 IC connect to D11 of Arduino
TM1637 disp(CLK,DIO);
	
#define TOUCH_OUT1 3//out1-TCH1 area corresponds to the number increase
#define TOUCH_OUT2 4//out2-TCH2 area not use now
#define TOUCH_OUT3 5//out3-TCH3 area not use now
#define TOUCH_OUT4 6//out4-TCH4 area not use now
TouchSensor touch(TOUCH_OUT1,TOUCH_OUT2, TOUCH_OUT3,TOUCH_OUT4);

int count = 0;

void setup()
{
  disp.init();//The initialization of the display
  disp.display(count);//display counter number
}

void loop()
{
  int button;
  button = touch.get();
  if(button == TOUCH_OUT1) //if touch the TCH1 area
  {
    delay(10);//delay for 10ms
    if(touch.get() == TOUCH_OUT1)//check it again
    {
      count++;
	  disp.display(count);
    }
	while(touch.get() == TOUCH_OUT1);//Wait for the button to be released
  }
  
}

/*********************************************************************************************************
The end of file
*********************************************************************************************************/

