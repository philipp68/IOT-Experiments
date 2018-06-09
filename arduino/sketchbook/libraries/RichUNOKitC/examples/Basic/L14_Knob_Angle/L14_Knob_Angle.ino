/************************************************* ************************************************** ******
* OPEN-SMART Rich UNO R3 Lesson 14: Knob angle display
* You can learn get the angle of the knob(rotary angle sensor) and display.
*
* The following functions are available:
*
* knob.getAngle();//read the angle of the knob, the range of angle is 0~280 degrees
* 
* disp.init(); // initialization
* disp.display(int Decimal);   // display range: -999 ~ 9999
************************************************** **************************************************/
/***************************CHINESE********************** ************************************************** ******
* OPEN-SMART Rich UNO R3 第14课: 旋转角度显示
* 学习获取旋转的角度并显示到数码管上
*
* 以下函数是本节用到的：
*
* knob.getAngle();//读取旋钮的角度，角度范围为0 - 280度
* 
* disp.init(); //初始化
* disp.display(int Decimal); //显示范围：-999~9999
************************************************** **************************************************/
#include <Wire.h>
#include <SoftwareSerial.h>
#include "RichUNOKitCTM1637.h"
#include "RichUNOKitCKnob.h"
#define KNOB_PIN A0//SIG pin of Rotary Angle Sensor module connect to A0 of IO Shield, that is pin A0 of Arduino
Knob knob(KNOB_PIN);

#define CLK 10//CLK of the TM1637 IC connect to D10 of Arduino
#define DIO 11//DIO of the TM1637 IC connect to D11 of Arduino
TM1637 disp(CLK,DIO);

void setup()
{
  disp.init();//The initialization of the display
}

void loop()
{
  int angle;
  angle = knob.getAngle();
  disp.display(angle);
  delay(500);
}

/*********************************************************************************************************
The end of file
*********************************************************************************************************/
