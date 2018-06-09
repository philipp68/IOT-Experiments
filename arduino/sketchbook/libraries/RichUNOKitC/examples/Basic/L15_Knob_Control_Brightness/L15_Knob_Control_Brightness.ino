/************************************************* ************************************************** ******
* OPEN-SMART Rich UNO R3 Lesson 15: Knob control brightness
* You can learn use the knob(rotary angle sensor) to control the brightness of the display.
*
* The following functions are available:

* knob.getAngle();//read the angle of the knob, the range of angle is 0~280 degrees

* disp.init(); // initialization
* disp.display(int8_t DispData []); // display the numbers in the array
* // For example, the array is {1,2,3,4}, then show 1234
* disp.set(uint8_t brightness); // set the brightness, 0 ~ 7, the greater the value, the higher the brightness, 
                                       //the next display takes effect
* disp.point(0); // Turn off the display colon and the next display takes effect
* disp.point(1); // Turn on the display colon and the next display takes effect
************************************************** **************************************************/
/****************************CHINESE********************* ************************************************** ******
* OPEN-SMART Rich UNO R3 第15课: 旋钮控制亮度
* 学习用旋钮去控制4位数码管的显示亮度
*
* 以下函数是本节用到的：

* knob.getAngle();//读取旋钮的角度，角度范围为0 - 280度

* disp.init(); //初始化
* disp.display(int8_t DispData []); //显示数组中的数字
* //例如，数组是{1,2,3,4}，然后显示1234
* disp.set(uint8_t brightness); //设置亮度，0~7，值越大，亮度越高，
                                        //下一次显示效果
* disp.point(0); //关闭显示冒号，下一次显示将生效
* disputpoint(1); //打开显示冒号，下一次显示将生效
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
  disp.point(1);//turn on the clock point;
}

void loop()
{
  int angle;
  angle = knob.getAngle();

  int brightness;
	/*The degrees is 0~280, should be converted to be 0~7 to control the*/
	/*brightness of display */
  brightness = map(angle, 0, FULL_ANGLE, 0, BRIGHTEST); 
  disp.set(brightness);
  int8_t ListDisp[4] = {8,8,8,8};
  disp.display(ListDisp);//display array
}
/*********************************************************************************************************
The end of file
*********************************************************************************************************/
