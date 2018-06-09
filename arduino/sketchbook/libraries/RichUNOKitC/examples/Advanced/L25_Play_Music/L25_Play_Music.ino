/************************************************* ************************************************** ******
* OPEN-SMART Rich UNO R3 Lesson 25: Play a song
NOTE!!! First of all you should download the voice resources from our google drive:
https://drive.google.com/drive/folders/0B6uNNXJ2z4CxbTduWWYzRU13a1U?usp=sharing
Then unzip it and find the 01 and 02 folder and put them into your TF card (should not larger than 32GB). 
Note 2: Use the audio cable to connect the mono amplifier module with the MP3 module together, 
then use the DuPont cable to connect the 3.3V power supply of IO Shield with power supply pins of the amplifier module.


* You can learn how to play a song with its index in the TF card.
*
* The following functions are available for MP3 module:
*
/--------basic operations---------------/
mp3.play();
mp3.pause();
mp3.nextSong();
mp3.previousSong();
mp3.volumeUp();
mp3.volumeDown();
mp3.stopPlay();  
mp3.startSingleCycle();//start single cycle play the current song
mp3.stopSingleCycle(); //stop single cycle play
mp3.folderCyclePlay(uint8_t directory);//cycle play all the songs in the "directory", the directory must be named "01" --- "99". Can not exceed 99.
mp3.shufflePlay();// random play all the voice files in the TF card, and it will play the physical first index song 
                  //first every time you call this function.
/--------------------------------/

mp3.playWithIndex(int8_t index);//play the song according to the physical index of song in the TF card
mp3.waitStop();//Waiting for the end of song, commonly used in voice broadcast, because the voice is short, will soon feedback a stop command.
mp3.getStatus();//Get status, 0 = song stopped, 1 = song is paused, 2 = song is playing, commonly used for voice broadcast
mp3.setVolume(int8_t vol);//vol is 0~0x1e, 30 adjustable level
mp3.playWithFileName(int8_t directory, int8_t file);//play a song according to the folder name and prefix of its file name
                                                            //foler name must be 01 02 03...09 10...99
                                                            //prefix of file name must be 001...009 010...255
mp3.playWithVolume(int8_t index, int8_t volume);//play the song according to the physical index of song in the TF card and the volume set
mp3.listen();//As only one software serial port can receive data at the same time, if you use more than one software serial port in the program
             //you should call this function first so that you will not miss the feedback data.
             //In lesson 36, it needs this function because the serial RFID module also uses a software serial port.
************************************************** **************************************************/
/*****************************CHINESE******************** ************************************************** ******
* OPEN-SMART Rich UNO R3 第25课: 播放音乐
注意：在本课开始之前你要下载好需要用的语音资源，可以从我们的百度网盘下载
http://pan.baidu.com/s/1skEjoqp
然后将01和02文件夹复制到TF卡的根目录中
注意2：用音频线将单路功放模块和MP3模块连接器，再用杜邦线将IO扩展板的3.3V电源接到功放模块的电源引脚，注意电源正负

* 您可以学习如何按序号播放TF卡中的歌曲，例如：从顺序上，第一首歌的序号就1，第二首歌的序号就是2
* 以下函数是MP3模块用到的：
*
/--------基本操作---------------/
mp3.play(); //播放指令，只有在歌曲暂停的时候有效
mp3.pause(); //暂停指令，只有在歌曲播放的时候有效
mp3.nextSong(); //下一曲
mp3.previousSong(); //上一曲
mp3.volumeUp(); //音量增
mp3.volumeDown(); //音量减
mp3.stopPlay();  //停止播放
mp3.startSingleCycle();//对当前播放歌曲单曲循环
mp3.stopSingleCycle(); //停止单曲循环
mp3.folderCyclePlay(uint8_t directory);//指定文件夹循环播放，文件夹的命名方式必须是”01” --- “99”。不可以超过 99
mp3.shufflePlay();// 此指令是随机播放设备里面存储的所有语音文件，是按照物理顺序随机播放，不分设备里面是
否带有文件夹。并且播放的第一个语音文件肯定是设备里面的第一个语音文件
/--------------------------------/

mp3.playWithIndex(int8_t index);//按照TF卡中歌曲的物理顺序序号播放歌曲
mp3.waitStop();//等待播放结束，常用语音播报，由于语音较短，很快就会有播放结束命令反馈
mp3.getStatus();//获取状态，0 = 歌曲已停止，1 = 歌曲正在暂停，2=歌曲正在播放，常用于语音播报
mp3.setVolume(int8_t vol);//vol的范围是0~0x1e, 30级音量，0x1e表示30级
mp3.playWithFileName(int8_t directory, int8_t file);//按照文件夹名字和文件名前缀播放相应曲目
                                                  //文件夹名字必须是01 02 03...09 10...99
                                                  //曲目名字的前面3个字符必须是 001...009 010...255，例如001xxx.mp3的文件名就是合法的
mp3.playWithVolume(int8_t index, int8_t volume);//按TF卡中歌曲的物理顺序序号及音量播放曲目
mp3.listen();//由于软串口同时只能一个能接收数据，如果一个程序中用了超过一个软串口，需要接收数据前要调用这个函数，避免错过了模块返回的数据
             //第36课由于串口RFID模块也用软串口，所以就会用到这个函数
************************************************** **************************************************/
#include <Wire.h>
#include <SoftwareSerial.h>
#include "RichUNOKitCMP3.h"

#define MP3_RX 7//RX of Serial MP3 module connect to D7 of Arduino
#define MP3_TX 8//TX to D8
MP3 mp3(MP3_RX, MP3_TX);


int8_t index  = 0x01;//the first song in the TF card
int8_t volume = 0x1a;//0~0x1e (30 adjustable volume level)
void setup()
{
  delay(500);//Requires 500ms to wait for the MP3 module to initialize
  mp3.playWithVolume(index,volume);//Play a song according to the physical and volume
  delay(50);//you should wait for >=50ms between two commands
}

void loop()
{
  
}

/*********************************************************************************************************
The end of file
*********************************************************************************************************/
