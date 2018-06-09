/************************************************* ************************************************** ******
* OPEN-SMART Rich UNO R3 Lesson 20: Ultrasonic distance measurement and display
* You can learn to use  the ultrasonic distance measurement module to measure the distance 
* of the nearest obstacle in front, the maximum measurement is 500 cm, at least 3 cm, 
* the 4-digit display will display the integer part of value.
*
* The following functions are available:

* ultrasonic.readDistance();//Get the measured distance, and return a float type value in centimeters
* disp.init(); // initialization
* disp.display(int Decimal);   // display range: -999 ~ 9999
************************************************** **************************************************/
/****************************CHINESE********************* ************************************************** ******
* OPEN-SMART Rich UNO R3 第20课: 超声波测距与显示
* 学习使用超声波测距模块测量前方最近障碍物的距离，最大测量500厘米，最少3厘米，将整数部分显示到数码管上
*
* 以下函数是本节用到的：

* ultrasonic.readDistance();//获取测量出来的距离，返回一个float类型数值，单位是厘米
* disp.init(); //初始化
* disp.display(int Decimal); //显示范围：-999~9999
************************************************** **************************************************/
#include <Wire.h>
#include <SoftwareSerial.h>

#include "RichUNOKitCUltrasonic.h"
#include "RichUNOKitCTM1637.h"

#define CLK 10//CLK of the TM1637 IC connect to D10 of Arduino
#define DIO 11//DIO of the TM1637 IC connect to D11 of Arduino
TM1637 disp(CLK,DIO);


//module--- Arduino
//VCC   --- 5V
//GND   --- GND
#define TRIGGER_PIN  A2//Trig pin of ultrasonic sensor module connect to A2 of Arduino
#define ECHO_PIN     A3 //Echo to A3
Ultrasonic ultrasonic(TRIGGER_PIN, ECHO_PIN);


void setup()
{
  disp.init();//The initialization of the display
}

void loop()
{
  float cmMsec;  
  cmMsec = ultrasonic.readDistance();//if out of range, it return -1;
  disp.display((int)cmMsec);//in centimeters
  delay(500);
}
/*********************************************************************************************************
The end of file
*********************************************************************************************************/