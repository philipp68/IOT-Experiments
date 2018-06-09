/************************************************* ************************************************** ******
* OPEN-SMART Rich UNO R3 Lesson 26: Play song with its file name
If you have done in lesson 25, you ignore these notes below.
NOTE!!! First of all you should download the voice resources from our google drive:
https://drive.google.com/drive/folders/0B6uNNXJ2z4CxbTduWWYzRU13a1U?usp=sharing
Then unzip it and find the 01 and 02 folder and put them into your TF card (should not larger than 32GB). 
Note 2: Use the audio cable to connect the mono amplifier module with the MP3 module together, 
then use the DuPont cable to connect the 3.3V power supply of IO Shield with power supply pins of the amplifier module.

* You can learn how to play a song with folder name and file name.

* The following functions are available for this lesson:

mp3.setVolume(int8_t vol);//vol is 0~0x1e, 30 adjustable level
mp3.playWithFileName(int8_t directory, int8_t file);//play a song according to the folder name and prefix of its file name
                                                            //foler name must be 01 02 03...09 10...99
                                                            //prefix of file name must be 001...009 010...255

************************************************** **************************************************/
/********************************CHINESE***************** ************************************************** ******
* OPEN-SMART Rich UNO R3 第26课: 按文件名播放歌曲
如果已经学习了25课，可以忽略这两个注意事项。
注意：在本课开始之前你要下载好需要用的语音资源，可以从我们的百度网盘下载
http://pan.baidu.com/s/1skEjoqp
然后将01和02文件夹复制到TF卡的根目录中
注意2：用音频线将单路功放模块和MP3模块连接器，再用杜邦线将IO扩展板的3.3V电源接到功放模块的电源引脚，注意电源正负

* 可以学习如何根据文件夹名字和曲目文件名播放曲目，对于语音播报项目非常重要。

* 以下函数是本节课用到的：

mp3.setVolume(int8_t vol);//vol的范围是0~0x1e, 30级音量，0x1e表示30级
mp3.playWithFileName(int8_t directory, int8_t file);//按照文件夹名字和文件名前缀播放相应曲目
                                                  //文件夹名字必须是01 02 03...09 10...99
                                                  //曲目名字的前面3个字符必须是 001...009 010...255，例如001xxx.mp3的文件名就是合法的
************************************************** **************************************************/

#include <Wire.h>
#include <SoftwareSerial.h>
#include "RichUNOKitCMP3.h"

#define MP3_RX 7//RX of Serial MP3 module connect to D7 of Arduino
#define MP3_TX 8//TX to D8
MP3 mp3(MP3_RX, MP3_TX);

int8_t volume = 0x1a;//0~0x1e (30 adjustable level)
int8_t folderName = 0x01;//folder name must be 01 02 03 04 ...
int8_t fileName = 0x01; // prefix of file name must be 001xxx 002xxx 003xxx 004xxx ...
void setup()
{
  delay(500);//Requires 500ms to wait for the MP3 module to initialize
  mp3.setVolume(volume);//Set volume
  delay(50);//you should wait for >=50ms between two commands
  mp3.playWithFileName(folderName,fileName);
  delay(50);
}

void loop()
{
  
}

/*********************************************************************************************************
The end of file
*********************************************************************************************************/
