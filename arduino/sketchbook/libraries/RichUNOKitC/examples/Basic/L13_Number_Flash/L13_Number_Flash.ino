/************************************************* ************************************************** ******
* OPEN-SMART Rich UNO R3 Lesson 13: Number flashing
*
* Learn how to use the timer method to make the displayed number flash
*
* The following functions are available:

* Timer1.initialize(unsigned long microseconds); // set the timed length, the unit is microseconds
* Timer1.attachInterrupt(TimingISR); // set interrupt routine function name, is the timing interrupt entry
* Timer1.stop(); // Timer 1 stops timing
* Timer1.start(); // Start Timer 1

* touch.get(); // return is the touch area corresponding Arduino pin number, if not then return -1
* touch.getLongPress(); // return long press the corresponding Arduino pin number, if not return -1
*
* disp.init(); // initialization
* disp.display(int Decimal);   // display range: -999 ~ 9999
* disp.clearDisplay(); // clear the display

************************************************** ************************************************** *****/
/*********************************CHINESE**************** ************************************************** ******
* OPEN-SMART Rich UNO R3 第13课: 数字闪烁
*
* 学习使用定时器方法去显示闪烁的数字
*
* 以下函数是本节用到的：

* Timer1.initialize(unsigned long microseconds); // 设置定时中断时间，单位是微秒
* Timer1.attachInterrupt(TimingISR); //设置定时中断例程入口，中断时会直接调用传递的函数名字
* Timer1.stop(); // 停止1号定时器
* Timer1.start(); //启动1号定时器

* touch.get(); // 返回触摸区域对应的Arduino引脚号，都没有触摸则返回-1
* touch.getLongPress(); //返回长时间触摸的触摸区域对应的Arduino引脚号，都没有触摸则返回-1
*
* disp.init(); //初始化
* disp.display(int Decimal); //显示范围：-999~9999
* disp.clearDisplay(); //清除显示

************************************************** ************************************************** *****/

#include <Wire.h>
#include <SoftwareSerial.h>

#include <TimerOne.h>
#include "RichUNOKitCTM1637.h"
#include "RichUNOKitCTouchSensor.h"

#define CLK 10//CLK of the TM1637 IC connect to D10 of Arduino
#define DIO 11//DIO of the TM1637 IC connect to D11 of Arduino
TM1637 disp(CLK,DIO);

#define TOUCH_OUT1 3//out1-TCH1 area corresponds to the number increase
#define TOUCH_OUT2 4//out2-TCH2 area corresponds to the number decrease
#define TOUCH_OUT3 5//out3-TCH3 area corresponds to confirm the number you set (OK Button)
#define TOUCH_OUT4 6//out4-TCH4 area corresponds to make it enter settimg number mode and the number will flash("next step button")
TouchSensor touch(TOUCH_OUT1,TOUCH_OUT2, TOUCH_OUT3,TOUCH_OUT4);


uint8_t flag_disp = 0;// display flag, 0 = no number, 1 = display
uint8_t flag_ok = 0;  //Uint8_t flag_ok = 0; // confirm flag, 1 = just press the OK button
uint8_t flag_next = 0;//Uint8_t flag_next = 0; // next step flag, 1 = just press the next step button
uint8_t flag_change = 0;// digital modification flag, 1 = number can be modified, 0 = number can not be modified

int num = 2017;// the initial value of the number


void setup()
{
  disp.init();//The initialization of the display
  Timer1.initialize(500000);// 500 milliseconds timed, allowing the number to flash once per second
  Timer1.attachInterrupt(TimingISR);
  Timer1.stop();// timer stops timing
  flag_disp = 1;
}

void loop()
{
/*---------------------------------------------------*/
  int button;
  button = touch.get();
  if(button != -1)// there is a touch
  {
    delay(10);
	if(button == touch.get())// Check again if there is a touch
	{
	  switch(button)
	  {
	    case TOUCH_OUT1: if(flag_change)num++; break;//touch TCH1 area corresponds to the number increase
		case TOUCH_OUT2: if(flag_change)num--; break;//touch TCH2 area corresponds to the number decrease
		case TOUCH_OUT3: flag_ok = 1;
		                 flag_change = 0; //Has been confirmed, can not be adjusted
						 break;
		case TOUCH_OUT4: flag_next = 1;
		                 flag_change = 1;//You can adjust the number
						 break;
		default: break;
	  }
	}
	while(button == touch.get());//Wait for the button to be released
  }
  if(flag_ok)
  {
  	Timer1.stop();// timer stops timing
	flag_disp = 1;
	flag_ok = 0;
  }
  if(flag_next)
  {
  	Timer1.start();// timer starts timing
	flag_next = 0;
  }
/*---------------------------------------------------*/
  if(flag_disp) disp.display(num);
  else disp.clearDisplay();
/*---------------------------------------------------*/
  
}

/**********1号定时器 中断服务例程*********/
void TimingISR()
{
  flag_disp = !flag_disp;
}

/*********************************************************************************************************
The end of file
*********************************************************************************************************/

