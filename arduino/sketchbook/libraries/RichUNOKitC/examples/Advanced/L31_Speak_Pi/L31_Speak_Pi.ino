/************************************************* ************************************************** ******
* OPEN-SMART Rich UNO R3 Lesson 31: Speak pi
If you have done in lesson 25, you ignore these notes below.
NOTE!!! First of all you should download the voice resources from our google drive:
https://drive.google.com/drive/folders/0B6uNNXJ2z4CxbTduWWYzRU13a1U?usp=sharing
Then unzip it and find the 01 and 02 folder and put them into your TF card (should not larger than 32GB). 
Note 2: Use the audio cable to connect the mono amplifier module with the MP3 module together, 
then use the DuPont cable to connect the 3.3V power supply of IO Shield with power supply pins of the amplifier module.

* You can learn how to play a number according to the value and the filename of digit.
*
* The following functions are available:
*
mp3.waitStop();//Waiting for the end of song, commonly used in voice broadcast, because the voice is short, will soon feedback a stop command.
mp3.playWithFileName(int8_t directory, int8_t file);//play a song according to the folder name and prefix of its file name
                                                            //foler name must be 01 02 03...09 10...99
                                                            //prefix of file name must be 001...009 010...255
************************************************** **************************************************/
/*****************************CHINESE******************** ************************************************** ******
* OPEN-SMART Rich UNO R3 第31课: 将圆周率的前几位有效数字读出来
如果已经学习了25课，可以忽略这两个注意事项。
注意：在本课开始之前你要下载好需要用的语音资源，可以从我们的百度网盘下载
http://pan.baidu.com/s/1skEjoqp
然后将01和02文件夹复制到TF卡的根目录中
注意2：用音频线将单路功放模块和MP3模块连接器，再用杜邦线将IO扩展板的3.3V电源接到功放模块的电源引脚，注意电源正负 

* 您可以根据数字的值和文件名来学习如何播报数字语音，学习如何组合播放，这对于语音播报项目非常重要。
*
* The following functions are available:
*
* mp3.waitStop();//等待播放结束，常用语音播报，由于语音较短，很快就会有播放结束命令反馈
* mp3.playWithFileName(int8_t directory, int8_t file);//按照文件夹名字和文件名前缀播放相应曲目
                                                  //文件夹名字必须是01 02 03...09 10...99
                                                  //曲目名字的前面3个字符必须是 001...009 010...255，例如001xxx.mp3的文件名就是合法的

************************************************** **************************************************/
#include <Wire.h>
#include <SoftwareSerial.h>
#include "RichUNOKitCMP3.h"

#define MP3_RX 7//RX of Serial MP3 module connect to D7 of Arduino
#define MP3_TX 8//TX to D8
MP3 mp3(MP3_RX, MP3_TX);
int8_t volume = 0x1e;//0~0x1e (30 adjustable level)
int8_t folderName = 2;//folder name must be 01 02 03 04 ...
int8_t fileName = 1; // prefix of file name must be 001xxx 002xxx 003xxx 004xxx ...
#define NUM_OFFSET 2//offset between number and file name, such as file name of 0 is 002, 1 is 003

const char pi[] = "3.14159265";//The 9-digit effective number of pi
void setup()
{
  delay(500);//Requires 500ms to wait for the MP3 module to initialize
  
}

void loop()
{
  uint8_t num = sizeof(pi);
  mp3.playWithFileName(folderName,39);//039 pi is
  delay(200);
  mp3.waitStop();
  for(uint8_t i = 0; i < num; i++)
  {
    speaknum(pi[i]);//
  }
  while(1);
  
}

void speaknum(char c) {
  
  if ('0' <= c && c <= '9') {
    fileName = c - 0x30 + NUM_OFFSET;
  } 
  else if(c == '.')
  {
    fileName = 1;//001 point
  }
  else if (c != '.') {
    // error if not period
    return;
  }
  mp3.playWithFileName(folderName,fileName);
  mp3.waitStop();//Waiting for a voice to end
 delay(200);
}

/*********************************************************************************************************
The end of file
*********************************************************************************************************/
