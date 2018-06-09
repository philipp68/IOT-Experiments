/************************************************* ************************************************** ******
* OPEN-SMART Rich UNO R3 Lesson 12: Temperature measurement and display
* Through the NTC temperature measurement module to obtain the temperature, so that four digital display, 
* and because the digital tube is no decimal point, so only show the integer part of the temperature
*
* The following functions are available:
* temper.getTemperature(); // get the temperature value, the return of the float is the decimal
*
* displayTemperature(int8_t temperature); // display temperature, at the end of the value of the word added C is the degree of Celsius
*
* disp.init(); // initialization
* disp.display(int8_t DispData []); // display the numbers in the array
* // For example, the array is {1,2,3,4}, then show 1234
************************************************** ************************************************** *****/
/******************************CHINESE******************* ************************************************** ******
* OPEN-SMART Rich UNO R3 第12课: 温度测量与显示
* 通过NTC温度测量模块获得温度，用4位数码管显示，
* 并且因为数码管没有小数点，所以只能显示温度的整数部分
*
* 以下函数是本节用到的：
* temper.getTemperature(); //获取温度，返回的是浮点类型的数值，单位是摄氏度
*
* displayTemperature(int8_t temperature); //显示温度，单位是摄氏度，只能显示整数部分
*
* disp.init(); //初始化
* disp.display(int8_t DispData []); //显示数组中的数字
* //例如，数组是{1,2,3,4}，然后显示1234
************************************************** ************************************************** *****/
#include <Wire.h>
#include <SoftwareSerial.h>

#include "RichUNOKitCTM1637.h"
#include "RichUNOKitCTemperature.h"

#define NTC_PIN A1 //SIG pin of NTC module connect to A1 of IO Shield, that is pin A1 of Arduino
Temperature temper(NTC_PIN);  

#define CLK 10//CLK of the TM1637 IC connect to D10 of Arduino
#define DIO 11//DIO of the TM1637 IC connect to D11 of Arduino
TM1637 disp(CLK,DIO);

void setup()
{
  disp.init();//The initialization of the display
  delay(1000);//
}

void loop()
{
  float celsius;
  celsius = temper.getTemperature();//get temperature
  displayTemperature((int8_t)celsius);//
  delay(1000);//delay 1000ms
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
