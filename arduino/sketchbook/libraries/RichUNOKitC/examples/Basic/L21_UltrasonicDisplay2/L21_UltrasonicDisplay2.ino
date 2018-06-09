/************************************************* ************************************************** ******
* OPEN-SMART Rich UNO R3 Lesson 22: Ultrasonic distance measurement and display Part 2
* You can learn to use  the ultrasonic distance measurement module to measure the distance 
* of the nearest obstacle in front, the maximum measurement is 500 cm, at least 3 cm, 
* the I2C 1602 LCD will display the value.
*
* The following functions are available:

* ultrasonic.readDistance();//Get the measured distance, and return a float type value in centimeters
* lcd.init();     // I2C 1602 LCD screen initialization
* lcd.clear();     //clear the display
* lcd.backlight();//turn on the backlight
* lcd.noBacklight();//turn off the backlight
* lcd.setCursor(uint8_t col, uint8_t row);// set the cursor position,col is column
* lcd.print(Sring str);//display string
************************************************** **************************************************/
/****************************CHINESE********************* ************************************************** ******
* OPEN-SMART Rich UNO R3 第21课: 超声波测距与显示2
* 学习使用超声波测距模块测量前方最近障碍物的距离，最大测量500厘米，最少3厘米，将结果显示到I2C 1602液晶屏上。
*
* 以下函数是本节用到的：

* ultrasonic.readDistance();//获取测量出来的距离，返回一个float类型数值，单位是厘米
* lcd.init();     // 液晶屏初始化
* lcd.clear();     // 清屏
* lcd.backlight();//打开背光
* lcd.noBacklight();//关闭背光
* lcd.setCursor(uint8_t col, uint8_t row);//设置光标位置，col代表列标，row代表行标
* lcd.print(Sring str);//显示字符串
************************************************** **************************************************/
#include <Wire.h>
#include <SoftwareSerial.h>

#include "RichUNOKitCUltrasonic.h"
#include "RichUNOKitC_LCD1602.h"

LiquidCrystal_I2C lcd;  // set the LCD address to 0x3f for a 16 chars and 2 line display (default setting)

//module--- Arduino
//VCC   --- 5V
//GND   --- GND
#define TRIGGER_PIN  A2//Trig pin of ultrasonic sensor module connect to A2 of Arduino
#define ECHO_PIN     A3 //Echo to A3
Ultrasonic ultrasonic(TRIGGER_PIN, ECHO_PIN);


void setup()
{
  lcd.init();	 
  lcd.backlight();//turn on the backlight
}

void loop()
{
  float cmMsec;  
  cmMsec = ultrasonic.readDistance();//if out of range, it return -1;
  lcd.setCursor(0, 0);
  lcd.clear();
  lcd.print(cmMsec,0);
  lcd.print(" cm");
  delay(1000);
}
