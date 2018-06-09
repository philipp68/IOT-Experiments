/************************************************* ************************************************** ******
* OPEN-SMART Rich UNO R3 Lesson 35: Read ID number of RFID card

* You can learn how to get the ID number from the serial RFID module, 
  and use I2C 1602 LCD to display then ten digit of ID number.
  
* The following functions are available for this lesson:

* rfid.readTag();//Read ID number of an EM4100 or EM4001 ID card / tag, return is an unsigned long integer, 
  which the number marked on the tag.
* rfid.waitResume();//Because it will return 3 times the ID number each time it read the tag, in order to avoid repeated triggering,
                // you should wait for finished receving data and then clear, so it can read the next tag.

* lcd.init();     // I2C 1602 LCD screen initialization
* lcd.backlight();//turn on the backlight
* lcd.noBacklight();//turn off the backlight
* lcd.setCursor(uint8_t col, uint8_t row);// set the cursor position,col is column
* lcd.print(Sring str);//display string
* lcd.print(uint8_t);//display a decimal number
************************************************** **************************************************/
/********************************CHINESE***************** ************************************************** ******
* OPEN-SMART Rich UNO R3 第35课: 读取RFID卡的ID号

* 了解如何通过串口RFID模块读取RFID卡的ID号，并用I2C 1602液晶屏显示出来。

* 以下函数是本节课用到的：

* rfid.readTag();//读一个EM4100或EM4001的ID卡、钥匙的ID号，返回的是一个无符号长整型的整数，就是ID卡上印的卡号
* rfid.waitResume();//由于每次读卡号都会返回3次重复的数据，避免重复触发就等待接收完数据然后清除，就可以读下一个ID卡

* lcd.init();     // 液晶屏初始化
* lcd.backlight();//打开背光
* lcd.noBacklight();//关闭背光
* lcd.setCursor(uint8_t col, uint8_t row);//设置光标位置，col代表列标，row代表行标
* lcd.print(Sring str);//显示字符串
* lcd.print(uint8_t);//显示一个数字，十进制的

************************************************** **************************************************/

#include <Wire.h>
#include <SoftwareSerial.h>

#include "RichUNOKitCRFID.h"
#include "RichUNOKitC_LCD1602.h"

LiquidCrystal_I2C lcd; // set the LCD address to 0x3f for a 16 chars and 2 line display (default setting)

#define RFID_TX 2  //TX pin of Buzzer module connect to D2 of Arduino
RFID rfid(RFID_TX);

void setup() 
{
  lcd.init();	 // initialize the lcd 
  lcd.backlight();//turn on the backlight
}
void loop()
{
  uint32_t tagID;
  tagID = rfid.readTag();
  if(tagID != 0)
  {
    displayID(tagID);
  }
  delay(1000);
  rfid.waitResume();
}

void displayID(uint32_t tagID)
{
  lcd.clear();
  lcd.setCursor(0, 0);//the first place of the first line
  lcd.print("ID = ");
  uint8_t array[10];
  num2Array(tagID,array);
  for(int8_t i = 9; i >= 0; i--)
  {
    lcd.print(array[i]);
  }
}
/**********************************/
//the code on the white card and keychain is 10 digit
void num2Array(uint32_t num, uint8_t array[])
{
  for(uint8_t i = 0;i < 10;i ++)
  {
    array[i] = num%10;
	num /= 10;
  }
/*********************************************************************************************************
The end of file
*********************************************************************************************************/
}
