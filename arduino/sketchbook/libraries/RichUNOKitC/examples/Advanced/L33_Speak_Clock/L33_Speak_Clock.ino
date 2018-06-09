/************************************************* ************************************************** ******
* OPEN-SMART Rich UNO R3 Lesson 33: Speak Time
If you have done in lesson 25, you ignore these notes below.
NOTE!!! First of all you should download the voice resources from our google drive:
https://drive.google.com/drive/folders/0B6uNNXJ2z4CxbTduWWYzRU13a1U?usp=sharing
Then unzip it and find the 01 and 02 folder and put them into your TF card (should not larger than 32GB). 
Note 2: Use the audio cable to connect the mono amplifier module with the MP3 module together, 
then use the DuPont cable to connect the 3.3V power supply of IO Shield with power supply pins of the amplifier module.

* You can learn how to speak the time you get from the RTC module
   according to the value and the filename of digit /beep tone.

* The following functions are available for this lesson:

* timer1.initialize(unsigned long microseconds); // set the timed length, the unit is subtle
* timer1.attachInterrupt (TimingISR); // set interrupt routine function name, is the timing interrupt entry

* disp.init(); // initialization
* disp.display(int8_t DispData []); // display the numbers in the array
* // For example, the array is {1,2,3,4}, then show 1234
* disp.point(0); // Turn off the display colon and the next display takes effect
* disp.point(1); // Turn on the display colon and the next display takes effect

* touch.get(); / / return is the touch area corresponding Arduino pin number, if not then return -1

mp3.waitStop();//Waiting for the end of song, commonly used in voice broadcast, because the voice is short, will soon feedback a stop command.
mp3.setVolume(int8_t vol);//vol is 0~0x1e, 30 adjustable level
mp3.playWithFileName(int8_t directory, int8_t file);//play a song according to the folder name and prefix of its file name
                                                            //foler name must be 01 02 03...09 10...99
                                                            //prefix of file name must be 001...009 010...255
* clock.begin(); // The clock is on and the function must be called first
* clock.getTime(void); / / read the clock and time, will be saved in the clock class variable
	That is, the seven variables save the date and time:
	uint8_t second;
	uint8_t minute;
	uint8_t hour; 
	uint8_t dayOfWeek;
	uint8_t dayOfMonth;
	uint8_t month;
	uint16_t year;
************************************************** **************************************************/
/********************************CHINESE***************** ************************************************** ******
* OPEN-SMART Rich UNO R3 第33课: 语音播报时钟
如果已经学习了25课，可以忽略这两个注意事项。
注意：在本课开始之前你要下载好需要用的语音资源，可以从我们的百度网盘下载
http://pan.baidu.com/s/1skEjoqp
然后将01和02文件夹复制到TF卡的根目录中
注意2：用音频线将单路功放模块和MP3模块连接器，再用杜邦线将IO扩展板的3.3V电源接到功放模块的电源引脚，注意电源正负

* 可以学习如何根据从DS1307时钟模块获取的时间进行语音播报，对于语音播报项目非常重要。数码管显示变化的时钟。
  只有当您触摸TCH2区域时，才会播报时间。

* 以下函数是本节课用到的：

* Timer1.initialize(unsigned long microseconds); // 设置定时中断时间，单位是微秒
* Timer1.attachInterrupt(TimingISR); //设置定时中断例程入口，中断时会直接调用传递的函数名字

* disp.init(); //初始化
* disp.display(int8_t DispData []); //显示数组中的数字
* //例如，数组是{1,2,3,4}，然后显示1234
* disp.point(0); //关闭显示冒号，下一次显示将生效
* disputpoint(1); //打开显示冒号，下一次显示将生效


* touch.get(); // 返回触摸区域对应的Arduino引脚号，都没有触摸则返回-1

* mp3.waitStop();//等待播放结束，常用语音播报，由于语音较短，很快就会有播放结束命令反馈
* mp3.setVolume(int8_t vol);//vol的范围是0~0x1e, 30级音量，0x1e表示30级
* mp3.playWithFileName(int8_t directory, int8_t file);//按照文件夹名字和文件名前缀播放相应曲目
                                                  //文件夹名字必须是01 02 03...09 10...99
                                                  //曲目名字的前面3个字符必须是 001...009 010...255，例如001xxx.mp3的文件名就是合法的
												  
* clock.begin(); // 需要先调用begin函数
* clock.getTime(void); //获取时间函数，调用后，会保存在clock类的变量成员中
即这7个变量保存的就是日期、时间。
    uint8_t second;
	uint8_t minute;
	uint8_t hour; 
	uint8_t dayOfWeek;
	uint8_t dayOfMonth;
	uint8_t month;
	uint16_t year;
************************************************** **************************************************/

#include <Wire.h>
#include <SoftwareSerial.h>
#include <TimerOne.h>

#include "RichUNOKitCMP3.h"
#include "RichUNOKitCTouchSensor.h"
#include "RichUNOKitCTM1637.h"
#include "RichUNOKitCDS1307.h"

DS1307 clock;//define a object of DS1307 class

#define CLK 10//CLK of the TM1637 IC connect to D10 of Arduino
#define DIO 11//DIO of the TM1637 IC connect to D11 of Arduino
TM1637 disp(CLK,DIO);

int8_t Time[] = {0,0,0,0};

unsigned char ClockPoint = 1;//Clock point flag, 1 = display clock point, 0 = not display

#define ON 1
#define OFF 0
unsigned char Update;//Update flag, 1 = read time and display, 0 = no action

#define TOUCH_OUT1 3//out1-TCH1 area not use now
#define TOUCH_OUT2 4//out2-TCH2 area  corresponds to start speak time
#define TOUCH_OUT3 5//out3-TCH3 area not use now
#define TOUCH_OUT4 6//out4-TCH4 area not use now
TouchSensor touch(TOUCH_OUT1,TOUCH_OUT2, TOUCH_OUT3,TOUCH_OUT4);

#define MP3_RX 7//RX of Serial MP3 module connect to D7 of Arduino
#define MP3_TX 8//TX to D8
MP3 mp3(MP3_RX, MP3_TX);
int8_t volume = 0x1e;//0~0x1e (30 adjustable level)
int8_t folderName = 2;//folder name must be 01 02 03 04 ...
int8_t fileName = 1; // prefix of file name must be 001xxx 002xxx 003xxx 004xxx ...099xxx
#define NUM_OFFSET 2//offset between number and file name, such as file name of 0 is 002, 1 is 003
#define TEN_OFFSET 20//only for whole ten, offset between whole ten digit and file name, such as file name of 20 is 22, 30 is 23, 40 is 24

void setup()
{
  delay(500);//Requires 500ms to wait for the MP3 module to initialize
  disp.init();//The initialization of the display
  clock.begin();
  Timer1.initialize(500000);//timing for 500ms
  Timer1.attachInterrupt(TimingISR);//declare the interrupt serve routine:TimingISR 
  mp3.setVolume(volume);
}

void loop()
{
  
  int button;
  uint8_t flag_speak = 0;//0 = not speak, 1 = to speak
  button = touch.get();
  if(button == TOUCH_OUT2) //if touch the TCH1 area
  {
    delay(10);//delay for 10ms
    if(touch.get() == TOUCH_OUT2)//check it again
    {
      flag_speak = 1;
    }
	while(touch.get() == TOUCH_OUT2);//Wait for the button to be released
  }
  if(Update == ON)//Update the display time, is to flash the clock porint
  {
    TimeUpdate();
    disp.display(Time);
  }
  if(flag_speak)
  {
    SpeakTime(Time);
	flag_speak = 0;
  }
}


void SpeakTime(int8_t time[])
{
  uint8_t addr[10] = {0};
  uint8_t next = 0;
  addr[next++] = 31;//031 before speak time
  addr[next++] = 32;//032 opensmart time
  if(Time[0] < 2)
  {
    addr[next++] = Time[0]*10 + Time[1]+NUM_OFFSET;
  }
  else
  {
    addr[next++] = 22;//022 twenty
    if(Time[1] != 0) addr[next++] = Time[1] + NUM_OFFSET;
  }
  if((Time[2] == 0) && (Time[3] == 0)) addr[next++] = 33;//033 e clock
  else{
    if(Time[2] < 2){
  	  addr[next++] = Time[2]*10 + Time[3]+NUM_OFFSET;
  	}
	else
	{
	  addr[next++] = Time[2] + TEN_OFFSET;
	  if(Time[3] != 0)addr[next++] = Time[3] + NUM_OFFSET;
	}
  }
  SpeakGroup(addr, next);
}



void SpeakGroup(uint8_t addr[], uint8_t size)//
{
  while(mp3.getStatus()!=STATUS_STOP)delay(50);
  for(uint8_t i=0; i < size; i ++)
  {
	mp3.playWithFileName(folderName,addr[i]);
	mp3.waitStop();
  }
}

/**********Timer 1 interrupt routine*********/
void TimingISR()
{
  Update = ON;
  ClockPoint = !ClockPoint;
}

void TimeUpdate(void)
{
  if(ClockPoint)disp.point(POINT_ON);
  else disp.point(POINT_OFF);
  clock.getTime();
  Time[0] = clock.hour / 10;
  Time[1] = clock.hour % 10;
  Time[2] = clock.minute / 10;
  Time[3] = clock.minute % 10;
  Update = OFF;
}

/*********************************************************************************************************
The end of file
*********************************************************************************************************/

