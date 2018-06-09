/************************************************* ************************************************** ******
* OPEN-SMART Rich UNO R3 Lesson 30: Speak voice
If you have done in lesson 25, you ignore these notes below.
NOTE!!! First of all you should download the voice resources from our google drive:
https://drive.google.com/drive/folders/0B6uNNXJ2z4CxbTduWWYzRU13a1U?usp=sharing
Then unzip it and find the 01 and 02 folder and put them into your TF card (should not larger than 32GB). 
Note 2: Use the audio cable to connect the mono amplifier module with the MP3 module together, 
then use the DuPont cable to connect the 3.3V power supply of IO Shield with power supply pins of the amplifier module.

* You can learn know all the voice sources in the 02 folder so you can make your voice broadcast project.

*
* The following functions are available:
*
* disp.init(); // initialization
* disp.display(int Decimal);   // display range: -999 ~ 9999

* touch.get(); // return is the touch area corresponding Arduino pin number, if not then return -1

* mp3.playWithFileName(int8_t directory, int8_t file);//play a song according to the folder name and prefix of its file name
                                                            //foler name must be 01 02 03...09 10...99
                                                            //prefix of file name must be 001...009 010...255

************************************************** **************************************************/
/*************************CHINESE************************ ************************************************** ******
* OPEN-SMART Rich UNO R3 第30课: 播报语音
如果已经学习了25课，可以忽略这两个注意事项。
注意：在本课开始之前你要下载好需要用的语音资源，可以从我们的百度网盘下载
http://pan.baidu.com/s/1skEjoqp
然后将01和02文件夹复制到TF卡的根目录中
注意2：用音频线将单路功放模块和MP3模块连接器，再用杜邦线将IO扩展板的3.3V电源接到功放模块的电源引脚，注意电源正负

* 您可以了解02文件夹中的所有语音源，以便您进行语音播报项目，每段语音的地址都会显示在数码管上。

*
* 以下函数是本节课用到的：

* disp.init(); //初始化
* disp.display(int Decimal); //显示范围：-999~9999

* touch.get(); // 返回触摸区域对应的Arduino引脚号，都没有触摸则返回-1

* mp3.playWithFileName(int8_t directory, int8_t file);//按照文件夹名字和文件名前缀播放相应曲目
                                                  //文件夹名字必须是01 02 03...09 10...99
                                                  //曲目名字的前面3个字符必须是 001...009 010...255，例如001xxx.mp3的文件名就是合法的
************************************************** **************************************************/

#include <Wire.h>
#include <SoftwareSerial.h>
#include "RichUNOKitCMP3.h"
#include "RichUNOKitCTouchSensor.h"
#include "RichUNOKitCTM1637.h"
#define CLK 10//CLK of the TM1637 IC connect to D10 of Arduino
#define DIO 11//DIO of the TM1637 IC connect to D11 of Arduino
TM1637 disp(CLK,DIO);

#define TOUCH_OUT1 3//out1-TCH1 area corresponds to the number increase
#define TOUCH_OUT2 4//out2-TCH2 area corresponds to the number decrease
#define TOUCH_OUT3 5//out3-TCH3 area corresponds to play again
#define TOUCH_OUT4 6//out4-TCH4 area not use now
TouchSensor touch(TOUCH_OUT1,TOUCH_OUT2, TOUCH_OUT3,TOUCH_OUT4);

#define MP3_RX 7//RX of Serial MP3 module connect to D7 of Arduino
#define MP3_TX 8//TX to D8
MP3 mp3(MP3_RX, MP3_TX);

int8_t volume = 0x1a;//0~0x1e (30 adjustable level)
int8_t folderName = 2;//folder name must be 01 02 03 04 ...
int8_t fileName = 1; // prefix of file name must be 001xxx 002xxx 003xxx 004xxx ...
int8_t maxNum = 47;//we just supply 47 number of voice in derectory of 02 on our google drive
int8_t minNum = 1;//minimum number should be 1 but not 0
void setup()
{
  delay(500);//Requires 500ms to wait for the MP3 module to initialize
  mp3.setVolume(volume);//Set the volume
  disp.init();///The initialization of the display
  delay(50);//you should wait for >=50ms between two commands
}

void loop()
{
  int button;
  uint8_t flag_speak = 0;//Broadcast flag, 0 = not speak, 1 = to speak
  button = touch.get();
  if(button != -1) //if touch the area
  {
    delay(10);//delay for 10ms
    if(button == TOUCH_OUT1) //if touch the TCH1 area
    {
      if(fileName < maxNum)
      {
        flag_speak = 1;
        fileName++;
      }
    }
    else if(button == TOUCH_OUT2) //if touch the TCH2 area
    {
      if(fileName > minNum)
      {
        flag_speak = 1;
        fileName--;
      }
    }
    else if(button == TOUCH_OUT3) //if touch the TCH3 area
    {
      flag_speak = 1;
    }
    else if(button == TOUCH_OUT4) //if touch the TCH4 area
    {
    }
	while(button == touch.get());//Wait for the button to be released
  }
  if(button!=-1)disp.display(fileName);

  if(flag_speak)
  {
    mp3.playWithFileName(folderName,fileName);//play the voice
	delay(50);
	flag_speak = 0;
  }
}

/*********************************************************************************************************
The end of file
*********************************************************************************************************/
