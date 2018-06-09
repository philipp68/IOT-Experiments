/************************************************* ************************************************** ******
* OPEN-SMART Rich UNO R3 Lesson 29: IR control MP3
If you have done in lesson 25, you ignore these notes below.
NOTE!!! First of all you should download the voice resources from our google drive:
https://drive.google.com/drive/folders/0B6uNNXJ2z4CxbTduWWYzRU13a1U?usp=sharing
Then unzip it and find the 01 and 02 folder and put them into your TF card (should not larger than 32GB). 
Note 2: Use the audio cable to connect the mono amplifier module with the MP3 module together, 
then use the DuPont cable to connect the 3.3V power supply of IO Shield with power supply pins of the amplifier module.

* You can learn how to use the Infrared remote control to control the MP3, and when you press the button, the buzzer beep.
*
* The following functions are available:

* buzzer.on();//turn on the buzzer
* buzzer.off();//turn off the buzzer

* IR.enableIRIn(); // Start the receiver
* IR.decode();//if no result, it return 0, otherwise it return 1; .
* IR.resume(); // so that it can receive the next value
* IR.isReleased();//if the button is not released yet, it return 0; otherwise it return 1;

/--------basic operations---------------/
mp3.play();
mp3.pause();
mp3.nextSong();
mp3.previousSong();
mp3.volumeUp();
mp3.volumeDown();
/--------------------------------/
mp3.playWithIndex(int8_t index);//play the song according to the physical index of song in the TF card
mp3.setVolume(int8_t vol);//vol is 0~0x1e, 30 adjustable level
mp3.playWithFileName(int8_t directory, int8_t file);//play a song according to the folder name and prefix of its file name
                                                            //foler name must be 01 02 03...09 10...99
                                                            //prefix of file name must be 001...009 010...255

************************************************** *************************************************/
/***************************CHINESE************************************************************************ ******
* OPEN-SMART Rich UNO R3 第29课: 红外控制MP3
如果已经学习了25课，可以忽略这两个注意事项。
注意：在本课开始之前你要下载好需要用的语音资源，可以从我们的百度网盘下载
http://pan.baidu.com/s/1skEjoqp
然后将01和02文件夹复制到TF卡的根目录中
注意2：用音频线将单路功放模块和MP3模块连接器，再用杜邦线将IO扩展板的3.3V电源接到功放模块的电源引脚，注意电源正负

* 您可以学习如何使用红外遥控器来控制MP3，当您按下按钮时，蜂鸣器会发出蜂鸣声。
*
* 以下函数是本节课用到的：

* buzzer.on();//打开蜂鸣器发声
* buzzer.off();//关闭蜂鸣器

* IR.enableIRIn(); // 启动接收器，开启红外接收功能
* IR.decode();//如果没有解码结果，它返回0，否则返回1;
* IR.resume(); //恢复操作，调用后，可以恢复接收功能
* IR.isReleased();//如果遥控器按键尚未释放，则返回0; 否则返回1; 由于按键长按时会一直发送0xff过来，为了避免
*                 //识别错按键编码，就可以用这个函数来确认

/--------基本操作---------------/
mp3.play(); //播放指令，只有在歌曲暂停的时候有效
mp3.pause(); //暂停指令，只有在歌曲播放的时候有效
mp3.nextSong(); //下一曲
mp3.previousSong(); //上一曲
mp3.volumeUp();//音量增
mp3.volumeDown();//音量减
/--------------------------------/

mp3.playWithIndex(int8_t index);//按照TF卡中歌曲的物理顺序序号播放歌曲
mp3.setVolume(int8_t vol);//vol的范围是0~0x1e, 30级音量，0x1e表示30级
mp3.playWithFileName(int8_t directory, int8_t file);//按照文件夹名字和文件名前缀播放相应曲目
                                                  //文件夹名字必须是01 02 03...09 10...99
                                                  //曲目名字的前面3个字符必须是 001...009 010...255，例如001xxx.mp3的文件名就是合法的
************************************************** **************************************************/

#include <Wire.h>
#include <SoftwareSerial.h>

#include "RichUNOKitCMP3.h"
#include "RichUNOKitCIRremote.h"
#include "RichUNOKitCBuzzer.h"

#define BUZZER_PIN 9     //the SIG pin of the Buzzer module is connected with D9 of Arduino / OPEN-SMART UNO
Buzzer buzzer(BUZZER_PIN);

#define MP3_RX 7//RX of Serial MP3 module connect to D7 of Arduino
#define MP3_TX 8//TX to D8
MP3 mp3(MP3_RX, MP3_TX);

#define RECV_PIN 2//the SIG pin of Infrared Receiver is connected with D2 of Arduino / OPEN-SMART UNO
IRrecv IR(RECV_PIN);

int8_t flag_play = 1; //Play flag, 1 = Play, 0 = Pause
void setup()
{
  delay(500);//Requires 500ms to wait for the MP3 module to initialize
  IR.enableIRIn();
  Serial.begin(9600);
}

void loop()
{
  if (IR.decode()) {//If decode is valid

    if(IR.isReleased())//If it is not the repeat code for long press
	{
	  buzzer.on();//every time you press the key, the buzzer will beep
	  switch(IR.keycode)
	  {
	    case KEY_PLUS:  mp3.volumeUp();break;
		case KEY_MINUS: mp3.volumeDown();break;
		case KEY_PLAY:  flag_play = !flag_play;
			            if(flag_play)mp3.play();
						else mp3.pause();
						break;
		case KEY_PREV: mp3.previousSong();break;
		case KEY_NEXT:  mp3.nextSong();break;
		case KEY_ONE:  mp3.playWithIndex(0x01);break;
		case KEY_TWO:   mp3.playWithIndex(0x02);break;
		default: break;
	  }	 
	  delay(100);   //buzzer beep for 100ms
	  buzzer.off(); //turn off the buzzer
    }
    IR.resume(); // Receive the next value
  }
  
}

/*********************************************************************************************************
The end of file
*********************************************************************************************************/
