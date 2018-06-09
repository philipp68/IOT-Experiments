/************************************************* ************************************************** ******
* OPEN-SMART Rich UNO R3 Lesson 23: Test infrared remote keys 
*
* Learn how to get keys code of the buttons on the IR remote and display on the serial monitor of Arduino IDE.
*
* The following functions are available:
* IR.enableIRIn(); // Start the receiver
* IR.decode();//if no result, it return 0, otherwise it return 1; .
* IR.resume(); // so that it can receive the next value
* IR.isReleased();//if the button is not released yet, it return 0; otherwise it return 1;
*********************************************************************************************************/
/************************CHINESE************************* ************************************************** ******
* OPEN-SMART Rich UNO R3 第23课: 测试红外遥控器按键
*
* 了解如何获取IR遥控器上按钮的按键代码，并显示在Arduino IDE的串行监视器上。
*
* 以下函数是本节用到的：
* IR.enableIRIn(); // 启动接收器，开启红外接收功能
* IR.decode();//如果没有解码结果，它返回0，否则返回1;
* IR.resume(); //恢复操作，调用后，可以恢复接收功能
* IR.isReleased();//如果遥控器按键尚未释放，则返回0; 否则返回1; 由于按键长按时会一直发送0xff过来，为了避免
*                 //识别错按键编码，就可以用这个函数来确认
*********************************************************************************************************/

#include <Wire.h>
#include <SoftwareSerial.h>

#include "RichUNOKitCIRremote.h"

#define RECV_PIN 2//the SIG pin of Infrared Receiver is connected with D2 of Arduino / OPEN-SMART UNO
IRrecv IR(RECV_PIN);

void setup()
{
  Serial.begin(9600);
  IR.enableIRIn(); // Start the receiver
}

void loop()
{
  if (IR.decode()) {//If a valid key code is detected

    if(IR.isReleased())//If it is not the repeat code for long press, then read out to display
	{
      Serial.print("user code is ");
      Serial.println(IR.usercode,HEX);
      Serial.print("key code is ");
      Serial.println(IR.keycode,HEX);
    }
    IR.resume(); //resume to receive again
  }
}


/*********************************************************************************************************
The end of file
*********************************************************************************************************/
