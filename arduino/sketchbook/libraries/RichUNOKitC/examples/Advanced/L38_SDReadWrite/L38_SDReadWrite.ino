/************************************************* ************************************************** ******
* OPEN-SMART Rich UNO R3 Lesson 38: Micro SD card read / write and display
* Learn to create txt file, and write data into the document, and then read out and display on I2C 1602 LCD.
*
* The following functions are available for this lesson:

* lcd.init();     // I2C 1602 LCD screen initialization
* lcd.backlight();//turn on the backlight
* lcd.noBacklight();//turn off the backlight
* lcd.setCursor(uint8_t col, uint8_t row);// set the cursor position,col is column
* lcd.print(Sring str);//display string

card.init(uint8_t speed, uint8_t chipselectPin);//card initialization, speed Set SPI Frequency to F_CPU/2 if speed = 0 or F_CPU/4 if speed = 1.
                        //chipselectPin is CS pin of the MicroSD Card Adapter module.
file.open(const char* fileName, uint8_t oflag);//Open the file by file name, oflag is to setting flag for opening file, the available flag is:
                             //O_READ open for reading
							 //O_WRITE open for writing
							 //O_RDWR open for reading and writing
							 //O_APPEND The file offset shall be set to the end of the file prior to each write. 
							 //O_CREAT create the file if nonexistent
							 //O_TRUNC truncate the file to zero length
							 //If you need to enable some functions at the same time, use the or symbol "|"			 
file.close();//You can only open one file at the same time, and close it after operating. 
************************************************** **************************************************/
/****************************CHINESE********************* ************************************************** ******
* OPEN-SMART Rich UNO R3 第38课: micro SD读写与显示
* 学习创建txt文件，并写数据进文档，然后读出来并用I2C 1602液晶屏显示
*
* 以下函数是本节用到的：

* lcd.init();     // 液晶屏初始化
* lcd.backlight();//打开背光
* lcd.noBacklight();//关闭背光
* lcd.setCursor(uint8_t col, uint8_t row);//设置光标位置，col代表列标，row代表行标
* lcd.print(Sring str);//显示字符串

card.init(uint8_t speed, uint8_t chipselectPin);//卡初始化，speed就是SPI速率，speed = 0,则SPI速率是8M;speed = 1,则是4M。
                        //chipselectPin就是模块上的CS引脚
file.open(const char* fileName, uint8_t oflag);//按文件名打开，oflag是打开相关的设置标志，可用的标志是
                             //O_READ，可读
							 //O_WRITE，可写
							 //O_RDWR，可读可写
							 //O_APPEND 每次都会在文档内容末尾写
							 //O_CREAT 如果文件不存在，则新建一个
							 //O_TRUNC 清空文件内容
							 //如果需要同时使能一些功能，就要用或符号“|”
							 
file.close();//同时只能打开一个文件，操作结束后建议关闭文件
************************************************** **************************************************/
#include <Fat16.h>
#include <Fat16util.h> // use functions to print strings from flash memory
#include <SoftwareSerial.h>
#include <Wire.h> 
#include "RichUNOKitC_LCD1602.h"
LiquidCrystal_I2C lcd; 
SdCard card;
Fat16 file;

#define SD_CS 4//CS pin of MicroSD adapter module connect to D4 of IO Shield
//MicroSD adapter ----- Arduino / OPEN-SMART UNO
//     CS         ----- D4  
//     SCK        ----- SCK / D13
//     MOSI       ----- MOSI / D11
//     MISO       ----- MISO / D12
//     VCC        ----- 5V
//     GND        ----- GND
//-----------------------------------------

void setup(void) {
  lcd.init();                      // initialize the lcd 
  // Print a message to the LCD.
  lcd.backlight();
  pinMode(SS, OUTPUT);//The SS pin of the SPI interface must be set as the output interface. It is pin 10 for Arduino UNO
  lcd.setCursor(0, 0);
  // initialize the SD card
  lcd.print(F("cart init..."));
  if (card.init(1,SD_CS))
  {
    lcd.print(F(" ok"));
  }
  else 
  {
    lcd.print(F(" faild"));
	return;
  }
  
  lcd.setCursor(0, 1);
  lcd.print(F("FAT16 init..."));
  // initialize a FAT16 volume
  if (Fat16::init(&card))
  {
    lcd.print(F(" ok"));
  }
  else 
  {
    lcd.print(F(" faild"));
	return;
  }
  delay(1000);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(F("Write to smart.txt"));
  if (file.open("smart.TXT", O_WRITE|O_CREAT|O_TRUNC)) {
  	file.print("open-smart test");
  	lcd.setCursor(0, 1);
    lcd.print(F(" ok"));
  } else{
    lcd.setCursor(0, 1);
    lcd.print(F(" faild"));
    return;
  }
  file.close();	
  delay(2000);
  lcd.clear();
  
  // open a file
  lcd.setCursor(0, 0);
  lcd.print(F("Open smart.txt.."));
  if (file.open("smart.TXT", O_READ)) {
  	lcd.setCursor(0, 1);
    lcd.print(F(" ok"));
  } else{
    lcd.setCursor(0, 1);
    lcd.print(F(" faild"));
	return;
  }
  
  delay(1000);
  lcd.clear();
  lcd.setCursor(0, 0);
  int16_t n;
  uint8_t buf[10];//
  while ((n = file.read(buf, sizeof(buf))) > 0) {
    for (uint8_t i = 0; i < n; i++) lcd.write(buf[i]);
  }
  file.close();
}

void loop(void) {}
