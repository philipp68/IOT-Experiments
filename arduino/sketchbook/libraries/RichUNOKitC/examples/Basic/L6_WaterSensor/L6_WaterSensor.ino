/************************************************* *************************************************
* OPEN-SMART Rich UNO Kit C Lesson 6:  Water Sensor
* You can learn how to detect whether there is water. 
*
*
************************************************** ************************************************** *****/
/*******************************CHINESE****************** *************************************************
* OPEN-SMART Rich UNO Kit C 第6课: 水分传感器
* 可以了解怎么检测是否有水 
*
*
************************************************** ************************************************** *****/
#include <Wire.h>
#include <SoftwareSerial.h>

#define WATER_SENSOR A0//SIG pin of Water Sensor module connect to A0 of IO Shield, that is pin A0 of Arduino

void setup()
{
  Serial.begin(9600);//Set baud rate of serial port to be 9600bps, burn the program and open the serial monitor 
                     //on the upper right corner of Arduino IDE to check the sensor data.
}
void loop()
{
  int sensor = analogRead(WATER_SENSOR);// the value is about 160~1023
  //The deeper the depth of the board into the water, the smaller the return value
  //When there is no water on it, it return 1023
  Serial.print("sensor: ");
  Serial.println(sensor);
  delay(1000);  
}

/*********************************************************************************************************
The end of file
*********************************************************************************************************/