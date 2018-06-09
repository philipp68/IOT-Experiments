/************************************************* ************************************************** ******
* OPEN-SMART Rich UNO R3 Lesson 24: Infrared remote control and display
* You can learn how to recoginze the key on the IR remote control and display the number on the display.
*
* The following functions are available:

* buzzer.on();//turn on the buzzer
* buzzer.off();//turn off the buzzer

* IR.enableIRIn(); // Start the receiver
* IR.decode();//if no result, it return 0, otherwise it return 1; .
* IR.resume(); // so that it can receive the next value
* IR.isReleased();//if the button is not released yet, it return 1; otherwise it return 0;
*
* disp.init (); // initialization
* disp.display (int Decimal);   // display range: -999 ~ 9999
************************************************** **************************************************/
/*******************************CHINESE****************** ************************************************** ******
* OPEN-SMART Rich UNO R3 第24课: 红外遥控键位码显示
* 可以学习如何识别红外遥控器上的按键，并将数字按键对应的数字显示出来。
*
* 以下函数是本节用到的：

* buzzer.on();//打开蜂鸣器发声
* buzzer.off();//关闭蜂鸣器

* IR.enableIRIn(); // 启动接收器，开启红外接收功能
* IR.decode();//如果没有解码结果，它返回0，否则返回1;
* IR.resume(); //恢复操作，调用后，可以恢复接收功能
* IR.isReleased();//如果遥控器按键尚未释放，则返回0; 否则返回1; 由于按键长按时会一直发送0xff过来，为了避免
*                 //识别错按键编码，就可以用这个函数来确认
*
* disp.init(); //初始化
* disp.display(int Decimal); //显示范围：-999~9999

************************************************** **************************************************/
#include <Wire.h>
#include <SoftwareSerial.h>

#include "RichUNOKitCTM1637.h"
#include "RichUNOKitCIRremote.h"
#include "RichUNOKitCBuzzer.h"

#define BUZZER_PIN 9    //the SIG pin of the Buzzer module is connected with D9 of Arduino / OPEN-SMART UNO
Buzzer buzzer(BUZZER_PIN);

#define RECV_PIN 2//the SIG pin of Infrared Receiver is connected with D2 of Arduino / OPEN-SMART UNO
IRrecv IR(RECV_PIN);

#define CLK 10//CLK of the TM1637 IC connect to D10 of Arduino
#define DIO 11//DIO of the TM1637 IC connect to D11 of Arduino
TM1637 disp(CLK,DIO);

unsigned char num = 0;
void setup()
{
  disp.init();//The initialization of the display
  IR.enableIRIn(); // Start the receiver
}


void loop()
{
  if (IR.decode()) {//If a valid key code is detected

    if(IR.isReleased())//If it is not the repeat code for long press
	{
	  buzzer.on();//every time you press the key, the buzzer will beep
	  switch(IR.keycode)
	  {
	    case KEY_ZERO:  num = 0;break;
		case KEY_ONE:   num = 1;break;
		case KEY_TWO:   num = 2;break;
		case KEY_THREE: num = 3;break;
		case KEY_FOUR:  num = 4;break;
		case KEY_FIVE:  num = 5;break;
		case KEY_SIX:   num = 6;break;
		case KEY_SEVEN: num = 7;break;
		case KEY_EIGHT: num = 8;break;
		case KEY_NINE:  num = 9;break;
		case KEY_PLUS:  num = num+1;break;
		case KEY_MINUS: num = num-1;break;
		default: break;
	  }
	  disp.display(num);
	  delay(100);   //buzzer beep for 100ms
	  buzzer.off(); //turn off the buzzer
    }
    IR.resume(); // Receive the next value
  }
}


/*********************************************************************************************************
The end of file
*********************************************************************************************************/
