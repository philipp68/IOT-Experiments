/************************************************* ************************************************** ******
* OPEN-SMART Rich UNO R3 Lesson 19: I2C 1602 LCD Display Clock
* You can learn to use I2C 1602 LCD to display time.
*
* The following functions are available:

* Timer1.initialize(unsigned long microseconds); // set the timed length, the unit is microseconds
* Timer1.attachInterrupt(TimingISR); // set interrupt routine function name, is the timing interrupt entry

* lcd.init();     // I2C 1602 LCD screen initialization
* lcd.backlight();//turn on the backlight
* lcd.noBacklight();//turn off the backlight
* lcd.setCursor(uint8_t col, uint8_t row);// set the cursor position,col is column
* lcd.print(Sring str);//display string

* clock.begin(); // The clock is on and the function must be called first
* clock.startClock(void); // clock start, if you stop the clock need to call this function
* clock.stopClock(void); // clock stop timing
* clock.getTime(void); / / read the clock and time, will be saved in the clock class variable
* clock.fillByHMS(uint8_t _hour, uint8_t _minute, uint8_t _second); // write minutes
* clock.fillByYMD(uint16_t _year, uint8_t _month, uint8_t _day); // write clock
* clock.fillDayOfWeek(uint8_t _dow); // write week
* clock.setTime(void); // write the clock and time that have been written to the clock chip
************************************************** **************************************************/
/****************************CHINESE********************* ************************************************** ******
* OPEN-SMART Rich UNO R3 第19课: I2C 1602液晶屏显示时钟
* 学习使用I2C 1602液晶屏显示一个计时的时钟
*
* 以下函数是本节用到的：

* Timer1.initialize(unsigned long microseconds); // 设置定时中断时间，单位是微秒
* Timer1.attachInterrupt(TimingISR); //设置定时中断例程入口，中断时会直接调用传递的函数名字

* lcd.init();     // 液晶屏初始化
* lcd.backlight();//打开背光
* lcd.noBacklight();//关闭背光
* lcd.setCursor(uint8_t col, uint8_t row);//设置光标位置，col代表列标，row代表行标
* lcd.print(Sring str);//显示字符串

* clock.begin(); // 需要先调用begin函数
* clock.startClock(void); //时钟启动计时
* clock.stopClock(void); //时钟停止计时 
* clock.getTime(void); //获取时间函数，调用后，会保存在clock类的变量成员中
* clock.fillByHMS(uint8_t _hour, uint8_t _minute, uint8_t _second); //写时分秒
* clock.fillByYMD(uint16_t _year, uint8_t _month, uint8_t _day); //写年月日
* clock.fillDayOfWeek(uint8_t _dow); //写星期几
* clock.setTime(void); //将已经写好的年月日 星期几 时分秒写到DS1307时钟芯片中
************************************************** **************************************************/
#include <TimerOne.h>
#include <Wire.h>
#include <SoftwareSerial.h>

#include "RichUNOKitCDS1307.h"
#include "RichUNOKitC_LCD1602.h"

LiquidCrystal_I2C lcd;  // set the LCD address to 0x3f for a 16 chars and 2 line display (default setting)

DS1307 clock;//define a object of DS1307 object

#define ON 1
#define OFF 0

uint8_t Update = ON;
uint8_t halfsecond = 0;

void setup() {
  clock.begin();
 // clock.fillByYMD(2017,8,9);//2017.08.09
 //  clock.fillByHMS(17,01,10);//17:01:10
 // clock.fillDayOfWeek(WED);//Wednesday,The first three letters
//  clock.setTime();//write time to the RTC chip
  lcd.init();	 // initialize the lcd 
  lcd.backlight();//turn on the backlight
  
  Timer1.initialize(500000);//timing for 500ms
  Timer1.attachInterrupt(TimingISR);//declare the interrupt serve routine:TimingISR 
  
}

void loop() {

  if(Update == ON)
  {
    DataUpdate();
  }
  
}

void TimingISR()
{
  halfsecond++;
  if(halfsecond == 2)
  {
    Update = ON;
	halfsecond = 0;
  }
}


void DataUpdate()
{
  clock.getTime();
  lcd.setCursor(0, 0);//the first place of the first line
  lcd.print("Time: ");
  if(clock.hour < 10)lcd.print(" ");
  lcd.print(clock.hour, DEC);
  lcd.print(":");
  if(clock.minute < 10)lcd.print("0");
  lcd.print(clock.minute, DEC);
  lcd.print(":");
  if(clock.second < 10)lcd.print("0");
  lcd.print(clock.second, DEC);
  
  lcd.setCursor(0, 1);//the first place of the second line
  lcd.print("Date: ");
  lcd.print(clock.year+2000, DEC);
  lcd.print(".");
  if(clock.month < 10)lcd.print("0");
  lcd.print(clock.month, DEC);
  lcd.print(".");
  if(clock.dayOfMonth < 10)lcd.print("0");
  lcd.print(clock.dayOfMonth, DEC);
  Update = OFF;
}
/*********************************************************************************************************
The end of file
*********************************************************************************************************/
