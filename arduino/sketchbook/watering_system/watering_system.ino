#include <Wire.h>
#include <SoftwareSerial.h>
#include <SPI.h>

#include "RTClib.h"
#include "Adafruit_GFX.h"
#include "Adafruit_PCD8544.h"

// setting up drivers for hardware components
RTC_DS1307 rtc;
Adafruit_PCD8544 display = Adafruit_PCD8544(3, 5, 6, 9, 10);

// variables for timing
unsigned long startMillis;
unsigned long currentMillis;
const unsigned long period = 1000;

void setup() {
  Serial.begin(9600);
  // short delay to give hardware some time to be ready
  delay(500);
  startMillis = millis();

  rtcSetup();
  displaySetup();

  // In case you want to adjust time, you can run this line of code and then
  // comment it back out
  //rtc.adjust(DateTime(2018,6,9,14,45));

}

void loop() {
  currentMillis = millis();
  
  if(currentMillis - startMillis >= period)
  {
    DateTime now = rtc.now();
    displayTime(now);
    startMillis = currentMillis;
  }
}

void rtcSetup()
{
  if (! rtc.begin()) {
    Serial.println("Couldn't find RTC");
    while (1);
  }

  if (! rtc.isrunning()) {
    Serial.println("RTC is NOT running!");
  }
  Serial.println("RTC is running");
}

void displaySetup()
{
  display.begin();
  display.setContrast(100);
  display.clearDisplay();
}

void displayTime(DateTime time){
    Serial.print(LCDWIDTH, DEC);
    Serial.print("/");
    Serial.print(LCDHEIGHT, DEC);
    Serial.print("\n");
    
    display.setCursor(19,20);
    display.setTextColor(BLACK, WHITE);
    display.setTextSize(1);
    String s = String(time.hour(), DEC) + ":" + String(time.minute(), DEC) + ":" + String(time.second(), DEC);
    display.print(s);
    display.display();
}

