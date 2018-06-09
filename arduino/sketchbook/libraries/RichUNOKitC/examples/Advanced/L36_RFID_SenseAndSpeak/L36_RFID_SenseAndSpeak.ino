/************************************************* ************************************************** ******
* OPEN-SMART Rich UNO R3 Lesson 26: Read ID number of RFID card and speak
If you have done in lesson 25, you ignore these notes below.
NOTE!!! First of all you should download the voice resources from our google drive:
https://drive.google.com/drive/folders/0B6uNNXJ2z4CxbTduWWYzRU13a1U?usp=sharing
Then unzip it and find the 01 and 02 folder and put them into your TF card (should not larger than 32GB). 
Note 2: Use the audio cable to connect the mono amplifier module with the MP3 module together, 
then use the DuPont cable to connect the 3.3V power supply of IO Shield with power supply pins of the amplifier module.

* You can learn how to get the ID number from the serial RFID module, 
  and use I2C 1602 LCD to display then ten digit of ID number, and speak every digit of it.
  
* The following functions are available for this lesson:

* rfid.readTag();//Read ID number of an EM4100 or EM4001 ID card / tag, return is an unsigned long integer, 
  which the number marked on the tag.
* rfid.waitResume();//Because it will return 3 times the ID number each time it read the tag, in order to avoid repeated triggering,
                // you should wait for finished receving data and then clear, so it can read the next tag.
* rfid.listen();//As only one software serial port can receive data at the same time, if you use more than one software serial port in the program
             //you should call this function first so that you will not miss the feedback data.
             //It needs this function because the serial MP3 module also uses a software serial port.
				
* lcd.init();     // I2C 1602 LCD screen initialization
* lcd.backlight();//turn on the backlight
* lcd.noBacklight();//turn off the backlight
* lcd.setCursor(uint8_t col, uint8_t row);// set the cursor position,col is column
* lcd.print(Sring str);//display string
* lcd.print(uint8_t);//display a decimal number

mp3.waitStop();//Waiting for the end of song, commonly used in voice broadcast, because the voice is short, will soon feedback a stop command.
mp3.setVolume(int8_t vol);//vol is 0~0x1e, 30 adjustable level
mp3.playWithFileName(int8_t directory, int8_t file);//play a song according to the folder name and prefix of its file name
                                                            //foler name must be 01 02 03...09 10...99
                                                            //prefix of file name must be 001...009 010...255
mp3.listen();//As only one software serial port can receive data at the same time, if you use more than one software serial port in the program
             //you should call this function first so that you will not miss the feedback data.
             //It needs this function because the serial RFID module also uses a software serial port.															
************************************************** **************************************************/
/********************************CHINESE***************** ************************************************** ******
* OPEN-SMART Rich UNO R3 第36课: 读取RFID卡的ID号并语音播报出来
如果已经学习了25课，可以忽略这两个注意事项。
注意：在本课开始之前你要下载好需要用的语音资源，可以从我们的百度网盘下载
http://pan.baidu.com/s/1skEjoqp
然后将01和02文件夹复制到TF卡的根目录中
注意2：用音频线将单路功放模块和MP3模块连接器，再用杜邦线将IO扩展板的3.3V电源接到功放模块的电源引脚，注意电源正负

* 了解如何通过串口RFID模块读取RFID卡的ID号，并用I2C 1602液晶屏显示出来，然后用串口MP3模块将卡号按位读出。

* 以下函数是本节课用到的：

* rfid.readTag();//读一个EM4100或EM4001的ID卡、钥匙的ID号，返回的是一个无符号长整型的整数，就是ID卡上印的卡号
* rfid.waitResume();//由于每次读卡号都会返回3次重复的数据，避免重复触发就等待接收完数据然后清除，就可以读下一个ID卡
* rfid.listen();//由于软串口同时只能一个能接收数据，如果一个程序中用了超过一个软串口，需要接收数据前要调用这个函数，避免错过了模块返回的数据
             //由于串口MP3模块也用软串口，所以就会用到这个函数

* lcd.init();     // 液晶屏初始化
* lcd.backlight();//打开背光
* lcd.noBacklight();//关闭背光
* lcd.setCursor(uint8_t col, uint8_t row);//设置光标位置，col代表列标，row代表行标
* lcd.print(Sring str);//显示字符串
* lcd.print(uint8_t);//显示一个数字，十进制的

* mp3.waitStop();//等待播放结束，常用语音播报，由于语音较短，很快就会有播放结束命令反馈
* mp3.setVolume(int8_t vol);//vol的范围是0~0x1e, 30级音量，0x1e表示30级
* mp3.playWithFileName(int8_t directory, int8_t file);//按照文件夹名字和文件名前缀播放相应曲目
                                                  //文件夹名字必须是01 02 03...09 10...99
                                                  //曲目名字的前面3个字符必须是 001...009 010...255，例如001xxx.mp3的文件名就是合法的
* mp3.listen();//由于软串口同时只能一个能接收数据，如果一个程序中用了超过一个软串口，需要接收数据前要调用这个函数，避免错过了模块返回的数据
             //由于串口RFID模块也用软串口，所以就会用到这个函数
************************************************** **************************************************/
#include <Wire.h>
#include <SoftwareSerial.h>

#include "RichUNOKitCMP3.h"
#include "RichUNOKitCRFID.h"
#include "RichUNOKitC_LCD1602.h"

#define MP3_RX 7//RX of Serial MP3 module connect to D7 of Arduino
#define MP3_TX 8//TX to D8
MP3 mp3(MP3_RX, MP3_TX);
int8_t volume = 0x1a;//0~0x1e (30 adjustable level)
int8_t folderName = 2;//folder name must be 01 02 03 04 ...
int8_t fileName = 1; // prefix of file name must be 001xxx 002xxx 003xxx 004xxx ...
#define NUM_OFFSET 2//offset between number and file name, such as file name of 0 is 002, 1 is 003

LiquidCrystal_I2C lcd; // set the LCD address to 0x3f for a 16 chars and 2 line display (default setting)

#define RFID_TX 2//TX pin of Buzzer module connect to D2 of Arduino
RFID rfid(RFID_TX);

void setup()
{
  delay(500);//Requires 500ms to wait for the MP3 module to initialize
  lcd.init();	 // initialize the lcd 
  lcd.backlight();//turn on the backlight
  mp3.setVolume(volume);//Set the volume
  delay(50);
}

void loop()
{
  uint32_t tagID;
  rfid.listen();//Listen to the data returned by the RFID module
  tagID = rfid.readTag();//Read the ID number returned by the RFID module
  if(tagID != 0)//If the ID number is valid
  {
    displayID(tagID);
	
	mp3.listen();//Listen to the data returned by the MP3 module
	mp3.playWithFileName(folderName,41); //041 Welcome back
	mp3.waitStop();
	delay(500);
	mp3.playWithFileName(folderName,42);//042 Your ID is
	mp3.waitStop();
	speakTagID(tagID);//speak 10 digit of the tagID
  }
  delay(1000);
  rfid.listen();//Continue to resume monitoring the data of the RFID module
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
void speakTagID(uint32_t tagID)
{
  uint8_t array[10];
  num2Array(tagID,array);
  for(int8_t i = 9; i >= 0; i--)
  {
    speakDigit(array[i]);
  }
}
void speakDigit(char c) {
  
  if (0 <= c && c <= 9) {
    fileName = c + NUM_OFFSET;
  } 
  mp3.playWithFileName(folderName,fileName);
  mp3.waitStop();
  delay(50);
}
/**********************************/
//Tag ID is 10 digit number
void num2Array(uint32_t num, uint8_t array[])
{
  for(uint8_t i = 0;i < 10;i ++)
  {
    array[i] = num%10;
	num /= 10;
  }
}
/*********************************************************************************************************
The end of file
*********************************************************************************************************/
