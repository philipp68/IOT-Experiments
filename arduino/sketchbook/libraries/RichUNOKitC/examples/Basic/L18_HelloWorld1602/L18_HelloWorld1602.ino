/************************************************* ************************************************** ******
* OPEN-SMART Rich UNO R3 Lesson 18: I2C 1602 LCD Display
* You can learn to use I2C 1602 LCD to display number, character.
*
* The following functions are available:

* lcd.init();     // I2C 1602 LCD screen initialization
* lcd.backlight();//turn on the backlight
* lcd.noBacklight();//turn off the backlight
* lcd.setCursor(uint8_t col, uint8_t row);// set the cursor position,col is column
* lcd.print(Sring str);//display string
************************************************** **************************************************/
/****************************CHINESE********************* ************************************************** ******
* OPEN-SMART Rich UNO R3 第18课: I2C 1602液晶屏显示
* 学习使用I2C 1602液晶屏显示数字、字符
*
* 以下函数是本节用到的：

* lcd.init();     // 液晶屏初始化
* lcd.backlight();//打开背光
* lcd.noBacklight();//关闭背光
* lcd.setCursor(uint8_t col, uint8_t row);//设置光标位置，col代表列标，row代表行标
* lcd.print(Sring str);//显示字符串
************************************************** **************************************************/


#include <Wire.h> 
#include <SoftwareSerial.h>

#include "RichUNOKitC_LCD1602.h"

LiquidCrystal_I2C lcd;  // set the LCD address to 0x3f for a 16 chars and 2 line display (default setting)

void setup()
{
  lcd.init();                      // initialize the lcd 

  // Print a message to the LCD.
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Hello, world!");
  lcd.setCursor(0, 1);
  lcd.print("OPEN-SMART");
}

void loop()
{
}
/*********************************************************************************************************
The end of file
*********************************************************************************************************/
