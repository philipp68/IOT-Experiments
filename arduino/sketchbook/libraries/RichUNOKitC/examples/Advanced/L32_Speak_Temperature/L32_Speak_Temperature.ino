/************************************************* ************************************************** ******
* OPEN-SMART Rich UNO R3 Lesson 32: Speak temperature
NOTE!!! First of all you should download the voice resources from our google drive:
https://drive.google.com/drive/folders/0B6uNNXJ2z4CxaXFpakMxR0p1Unc?usp=sharing

Then unzip it and find the 01 and 02 folder and put them into your TF card (should not larger than 32GB). 

* You can learn how to speak the temperature you get from the temperature sensor
   according to the value and the filename of digit /beep tone.
   And only when you touch TCH1 area, it will speak temperature.
*
* The following functions are available:

* disp.init(); // initialization
* disp.display(int8_t DispData []); // display the numbers in the array
* // For example, the array is {1,2,3,4}, then show 1234

* temper.getTemperature(); / / get the temperature value, the return of the float is the decimal

* displayTemperature(int8_t temperature); // display temperature, at the end of the value of the word added C is the degree of Celsius

* touch.get(); / / return is the touch area corresponding Arduino pin number, if not then return -1

mp3.waitStop();//Waiting for the end of song, commonly used in voice broadcast, because the voice is short, will soon feedback a stop command.
mp3.setVolume(int8_t vol);//vol is 0~0x1e, 30 adjustable level
mp3.playWithFileName(int8_t directory, int8_t file);//play a song according to the folder name and prefix of its file name
                                                            //foler name must be 01 02 03...09 10...99
                                                            //prefix of file name must be 001...009 010...255

************************************************** **************************************************/
/****************************CHINESE********************* ************************************************** ******
* OPEN-SMART Rich UNO R3 ��32��: ���������¶�
����Ѿ�ѧϰ��25�Σ����Ժ���������ע�����
ע�⣺�ڱ��ο�ʼ֮ǰ��Ҫ���غ���Ҫ�õ�������Դ�����Դ����ǵİٶ���������
http://pan.baidu.com/s/1skEjoqp
Ȼ��01��02�ļ��и��Ƶ�TF���ĸ�Ŀ¼��
ע��2������Ƶ�߽���·����ģ���MP3ģ�������������öŰ��߽�IO��չ���3.3V��Դ�ӵ�����ģ��ĵ�Դ���ţ�ע���Դ���� 

* ������ѧϰ��θ����¶ȴ�������õ��¶�ֵ�����ֶ�Ӧ���ļ������������������¶�һֱ��ʾ��������ϣ�
??ֻ�е�������TCH1����ʱ���ŻᲥ���¶ȡ�
*
* ���º����Ǳ��ڿ��õ��ģ�

* disp.init(); //��ʼ��
* disp.display(int8_t DispData []); //��ʾ�����е�����
* //���磬������{1,2,3,4}��Ȼ����ʾ1234
* temper.getTemperature(); //��ȡ�¶ȣ����ص��Ǹ������͵���ֵ����λ�����϶�
*
* displayTemperature(int8_t temperature); //��ʾ�¶ȣ���λ�����϶ȣ�ֻ����ʾ��������

* touch.get(); // ���ش��������Ӧ��Arduino���źţ���û�д����򷵻�-1

* mp3.waitStop();//�ȴ����Ž����������������������������϶̣��ܿ�ͻ��в��Ž��������
* mp3.setVolume(int8_t vol);//vol�ķ�Χ��0~0x1e, 30��������0x1e��ʾ30��
* mp3.playWithFileName(int8_t directory, int8_t file);//�����ļ������ֺ��ļ���ǰ׺������Ӧ��Ŀ
                                                  //�ļ������ֱ�����01 02 03...09 10...99
                                                  //��Ŀ���ֵ�ǰ��3���ַ������� 001...009 010...255������001xxx.mp3���ļ������ǺϷ���
************************************************** **************************************************/

#include <Wire.h>
#include <SoftwareSerial.h>
#include "RichUNOKitCMP3.h"
#include "RichUNOKitCTemperature.h"
#include "RichUNOKitCTouchSensor.h"
#include "RichUNOKitCTM1637.h"

#define CLK 10//CLK of the TM1637 IC connect to D10 of Arduino
#define DIO 11//DIO of the TM1637 IC connect to D11 of Arduino
TM1637 disp(CLK,DIO);

#define TOUCH_OUT1 3//out1-TCH1 area corresponds to start speaker temperature
#define TOUCH_OUT2 4//out2-TCH2 area not use now
#define TOUCH_OUT3 5//out3-TCH3 area not use now
#define TOUCH_OUT4 6//out4-TCH4 area not use now
TouchSensor touch(TOUCH_OUT1,TOUCH_OUT2, TOUCH_OUT3,TOUCH_OUT4);

#define NTC_PIN A1  //SIG pin of NTC module connect to A1 of IO Shield, that is pin A1 of Arduino
Temperature temper(NTC_PIN); // initialize an Temperature object "temper" for temperature


#define MP3_RX 7//RX of Serial MP3 module connect to D7 of Arduino
#define MP3_TX 8//TX to D8
MP3 mp3(MP3_RX, MP3_TX);
int8_t volume = 0x1e;//0~0x1e (30 adjustable level)
int8_t folderName = 2;//folder name must be 01 02 03 04 ...
int8_t fileName = 1; // prefix of file name must be 001xxx 002xxx 003xxx 004xxx ...099xxx
#define NUM_OFFSET 2//offset between number and file name, such as file name of 0 is 002, 1 is 003

void setup()
{
  delay(500);//Requires 500ms to wait for the MP3 module to initialize
  disp.init();//The initialization of the display
  mp3.setVolume(volume);
  delay(50);
}

void loop()
{
  
  int button;
  uint8_t flag_speak = 0;//Broadcast flag, 0 = not speak, 1 = to speak
  button = touch.get();
  if(button == TOUCH_OUT1) //if touch the TCH1 area
  {
    delay(10);//delay for 10ms
    if(touch.get() == TOUCH_OUT1)//check it again
    {
      flag_speak = 1;
    }
	while(touch.get() == TOUCH_OUT1);//Wait for the button to be released
  }
  float celsius;
  celsius = temper.getTemperature();//get temperature
  displayTemperature((int8_t)celsius);//
  if(flag_speak)
  {
    SpeakTemp(celsius);
	flag_speak = 0;
  }
}
void SpeakTemp(float temp)
{
  if(temp >= 1000)return;
  else if(temp <= -1000)return;
  
  uint8_t addr[10] = {0};
  uint8_t next = 0;
  addr[next++] = 31;//031 before speak time
  addr[next++] = 35;//035 opensmart temperature
  if(temp < 0)
  {
    temp = abs(temp);
	addr[next++] = 40;//040 minus
  }
  int t = temp;//Get the integer part of the temperature
  uint8_t flag_hundred;
  if(t >= 100)
  	{
  	  flag_hundred = 1;
  	  addr[next++] = t / 100 + NUM_OFFSET;//digit before hundred
	  addr[next++] = 30;//030 hundred
	  t %= 100;
  	}
  else flag_hundred = 0;
  if(t != 0) 
  {
  	if(flag_hundred)addr[next++] = 38;//038 and
  	if(t < 20)
  	{
  	  addr[next++] = t + 2;
  	}
    else
  	{
  	  addr[next++] = t / 10 + 20;
	  t %= 10;
	  if(t != 0)addr[next++] = t + NUM_OFFSET;
  	}
  }
 
  addr[next++] = 1;//001 point
 
  uint8_t subbit;
  subbit = ((int)(temp*10))%10;// 
  addr[next++] = subbit + NUM_OFFSET; 
  addr[next++] = 36;//036 Degrees Celsius
  SpeakGroup(addr, next);
}

void SpeakGroup(uint8_t addr[], uint8_t size)//
{
  while(mp3.getStatus()!=STATUS_STOP)delay(50);
  for(uint8_t i=0; i < size; i ++)
  {
	mp3.playWithFileName(folderName,addr[i]);
	mp3.waitStop();//aiting for a voice to end
  }
}


/************************************************* *********************/
/* Function: Display temperature on 4-digit digital tube */
/* Parameter: -int8_t temperature, temperature range is -40 ~ 125 degrees celsius */
/* Return Value: void */

void displayTemperature(int8_t temperature)
{
  int8_t temp[4];
  if(temperature < 0)
	{
		temp[0] = INDEX_NEGATIVE_SIGN;
		temperature = abs(temperature);
	}
	else if(temperature < 100)temp[0] = INDEX_BLANK;
	else temp[0] = temperature/100;
	temperature %= 100;
	temp[1] = temperature / 10;
	temp[2] = temperature % 10;
	temp[3] = 12;	          //index of 'C' for celsius degree symbol.
	disp.display(temp);
}

/*********************************************************************************************************
The end of file
*********************************************************************************************************/

