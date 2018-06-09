/************************************************* ************************************************** ******
* OPEN-SMART Rich UNO R3 Lesson 28: Touch control MP3
If you have done in lesson 25, you ignore these notes below.
NOTE!!! First of all you should download the voice resources from our google drive:
https://drive.google.com/drive/folders/0B6uNNXJ2z4CxbTduWWYzRU13a1U?usp=sharing
Then unzip it and find the 01 and 02 folder and put them into your TF card (should not larger than 32GB). 
Note 2: Use the audio cable to connect the mono amplifier module with the MP3 module together, 
then use the DuPont cable to connect the 3.3V power supply of IO Shield with power supply pins of the amplifier module.

* You can learn how to use the 4-channel touch sensor to control the MP3, 
* such as play / pause / next song / previous song operations.
*
* The following functions are available:

* touch.get(); // return is the touch area corresponding Arduino pin number, if not then return -1

/--------basic operations---------------/
mp3.play();
mp3.pause();
mp3.nextSong();
mp3.previousSong();
/--------------------------------/
mp3.setVolume(int8_t vol);//vol is 0~0x1e, 30 adjustable level

mp3.playWithFileName(int8_t directory, int8_t file);//play a song according to the folder name and prefix of its file name
                                                            //foler name must be 01 02 03...09 10...99
                                                            //prefix of file name must be 001...009 010...099

************************************************** **************************************************/
/********************************CHINESE***************** ************************************************** ******
* OPEN-SMART Rich UNO R3 第28课: 触摸控制MP3
如果已经学习了25课，可以忽略这两个注意事项。
注意：在本课开始之前你要下载好需要用的语音资源，可以从我们的百度网盘下载
http://pan.baidu.com/s/1skEjoqp
然后将01和02文件夹复制到TF卡的根目录中
注意2：用音频线将单路功放模块和MP3模块连接器，再用杜邦线将IO扩展板的3.3V电源接到功放模块的电源引脚，注意电源正负

* 您可以学习如何使用4通道触摸传感器来控制MP3，如播放/暂停/下一首歌曲/上一首歌曲操作。
*
* 以下函数是本节课用到的：

* touch.get(); // 返回触摸区域对应的Arduino引脚号，都没有触摸则返回-1

/--------基本操作---------------/
mp3.play(); //播放指令，只有在歌曲暂停的时候有效
mp3.pause(); //暂停指令，只有在歌曲播放的时候有效
mp3.nextSong(); //下一曲
mp3.previousSong(); //上一曲
/--------------------------------/
mp3.setVolume(int8_t vol);//vol的范围是0~0x1e, 30级音量，0x1e表示30级
mp3.playWithFileName(int8_t directory, int8_t file);//按照文件夹名字和文件名前缀播放相应曲目
                                                  //文件夹名字必须是01 02 03...09 10...99
                                                  //曲目名字的前面3个字符必须是 001...009 010...255，例如001xxx.mp3的文件名就是合法的

************************************************** **************************************************/

#include <Wire.h>
#include <SoftwareSerial.h>

#include "RichUNOKitCTouchSensor.h"
#include "RichUNOKitCMP3.h"

#define MP3_RX 7//RX of Serial MP3 module connect to D7 of Arduino
#define MP3_TX 8//TX to D8
MP3 mp3(MP3_RX, MP3_TX);

#define TOUCH_OUT1 3//out1-TCH1 area corresponds to play song operation
#define TOUCH_OUT2 4//out2-TCH2 area corresponds to pause operation
#define TOUCH_OUT3 5//out3-TCH3 area corresponds to next song operation
#define TOUCH_OUT4 6//out4-TCH4 area corresponds to previous song operation
TouchSensor touch(TOUCH_OUT1,TOUCH_OUT2, TOUCH_OUT3,TOUCH_OUT4);


int8_t volume = 0x1a;//0~0x1e (30 adjustable level)
int8_t folderName = 0x01;//folder name must be 01 02 03 04 ...
int8_t fileName = 0x01; // prefix of file name must be 001xxx 002xxx 003xxx 004xxx ...

void setup()
{
  delay(500);//Requires 500ms to wait for the MP3 module to initialize
  mp3.setVolume(volume);
  delay(50);//you should wait for >=50ms between two commands
  mp3.playWithFileName(folderName,fileName);
  delay(50);
}

void loop()
{
  int button;
  button = touch.get();
  if(button != -1)// there is a touch
  {
    delay(10);
	if(button == touch.get())// Check again if there is a touch
	{
	  switch(button)
	  {
	    case TOUCH_OUT1: mp3.play();break;//touch TCH1 area 
		case TOUCH_OUT2: mp3.pause();break;//touch TCH2 area 
		case TOUCH_OUT3: mp3.nextSong();
						 break;//touch TCH3 area
		case TOUCH_OUT4: mp3.previousSong();
		                 break;//touch TCH4 area
		default: break;
	  }
	}
	while(button == touch.get());//Wait for the button to be released
  }
  delay(50);//
}

/*********************************************************************************************************
The end of file
*********************************************************************************************************/
