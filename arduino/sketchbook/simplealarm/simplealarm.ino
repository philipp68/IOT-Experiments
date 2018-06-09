#include <TimerOne.h>
#include <Wire.h>
#include <SoftwareSerial.h>

#include "RichUNOKitCTM1637.h"
#include "RTClib.h"
#include "RedMP3.h"
//#include "RichUNOKitCMP3.h"

// set up real time clock
RTC_DS1307 rtc;

// set up 4 digit display
#define CLK 10//CLK of the TM1637 IC connect to D10 of Arduino
#define DIO 11//DIO of the TM1637 IC connect to D11 of Arduino
TM1637 disp(CLK,DIO);
int8_t displayData[4];
bool showDot = true; // show a dot
bool blinkDot = false; // blink dot
bool dot = true; // last state of dot  
bool blinkDisplay = false;  // blink complete display

// set up microphone sensor module
int analogMicInput = A0;
int digitalMicInput = 12;
int noiseLevel = 0;
int noiseDetected = 0;

// set up MP3 player
#define MP3_RX 7//RX of Serial MP3 module connect to D7 of Arduino
#define MP3_TX 8//TX to D8, note that D8 can not be used as RX on Mega2560, you should modify this if you donot use Arduino UNO
RedMP3 mp3(MP3_RX, MP3_TX);
bool playingSong = false;
int nrOfSongs = 3;
int alarmSongNr = 3;  // nr of song to start playing

// hard coded alarm time
int alarm[2] = {12,13};  // alarm set at 12:00
int snoozeTime = 9; // time to snooze in minutes
DateTime time_alarm_started;  // time when alarm started

// configure buttons to program alarm
int8_t buttonStates[] = {0,0,0,0,0};
const int8_t NUMBER_OF_BUTTONS = 5;
const int8_t BUTTON_PIN[] = {2,3,4,5,6};

// simple state machine
enum State_enum {STATE_ALARM_OFF, STATE_ALARM_ON, STATE_ALARM_STARTED, STATE_ALARM_SNOOZED, STATE_SET_ALARM_HOURS, STATE_SET_ALARM_MINUTES, STATE_SET_ALARM_SONG};
enum Sensors_enum {NONE, TOGGLE_ALARM, PROGRAM_ALARM, INCREMENT, DECREMENT, ALARM_ON, ALARM_SNOOZE, CLAP_DETECTED};
 
void state_machine_run(uint8_t sensors);
void alarm_off();
void alarm_on();
void alarm_started();
void alarm_snoozed();
void set_alarmhours();
void set_alarmminutes();
void set_alarmsong();
void incrementHours();
void decrementHours();
void incrementMinutes();
void decrementMinutes();
void incrementSongNr();
void decrementSongNr();

uint8_t read_IR();
uint8_t state = STATE_ALARM_OFF;

// variables for timing
unsigned long startMillis;
unsigned long currentMillis;
const unsigned long period = 200;

void setup()
{
  Serial.begin(9600); //the baud rate of serial monitor is 9600bps
  startMillis = millis();  //initial start time

  delay(500);
  rtcSetup();
  setupMicrophone();
  displaySetup();
  stopSong();
  
  // run once to set time
  //rtc.adjust(DateTime(2018,5,12,17,13));
}

void loop()
{
  currentMillis = millis();
  
  state_machine_run(read_IR());
  
  if(currentMillis - startMillis >= period)
  {
    updateDisplay();
    startMillis = currentMillis;
  }
}

void updateDisplay()
{
  // check if a dot should be shown
  if(showDot)
  {
    disp.point(true);
  } else
  {
    disp.point(false);
  }
  
  // check if dot should blink
  if(showDot && blinkDot)
  {
    disp.point(dot);
    dot = !dot;
  }

  // display text
  if(blinkDisplay) {
      disp.display(displayData);
      delay(100);
      disp.clearDisplay();
      delay(30);
  } else
  {
    disp.display(displayData);
    delay(100);
  }
  
}

void state_machine_run(uint8_t sensors) 
{
  DateTime now = rtc.now();
  switch(state)
  {
    case STATE_ALARM_OFF:
      if(sensors == TOGGLE_ALARM){
        alarm_on();
        state = STATE_ALARM_ON;
      }
      else if (sensors == PROGRAM_ALARM){
        set_alarmhours();
        state = STATE_SET_ALARM_HOURS;
      }
      else {
        showDot = true;
        blinkDot = false;
        blinkDisplay = false;
        updateTime();
      }
      break;
       
    case STATE_ALARM_ON:
      if(sensors == TOGGLE_ALARM){
        alarm_off();
        state = STATE_ALARM_OFF;
      }
      else if (sensors == PROGRAM_ALARM){
        set_alarmhours();
        state = STATE_SET_ALARM_HOURS;
      }
      else if((alarm[0] == now.hour()) && (alarm[1] == now.minute()) && (now.second() <= 5))
      {
        time_alarm_started = now;
        alarm_started();
        state = STATE_ALARM_STARTED;
      }
      else {
        showDot = true;
        blinkDot = true;
        blinkDisplay = false;
        updateTime();
      }
      break;

    case STATE_ALARM_STARTED:
      if(sensors == TOGGLE_ALARM){
        alarm_on();
        state = STATE_ALARM_ON;
      }
      else if (sensors == ALARM_SNOOZE){
        alarm_snoozed();
        state = STATE_ALARM_SNOOZED;
      }
      else if (sensors == CLAP_DETECTED){
        alarm_snoozed();
        state = STATE_ALARM_SNOOZED;
      }
      else {
        showDot = true;
        blinkDot = true;
        updateTime();
      }
      break;

    case STATE_ALARM_SNOOZED:
      if(sensors == TOGGLE_ALARM){
        alarm_on();
        state = STATE_ALARM_ON;
      }
      else if((time_alarm_started.hour() == now.hour()) && (now.minute() == (time_alarm_started.minute()+snoozeTime)))
      {
          time_alarm_started = now;
          alarm_started();
          state = STATE_ALARM_STARTED;
      } else
      { 
        showDot = true;
        blinkDot = true;
        updateTime();
      }
      break;

      case STATE_SET_ALARM_HOURS:
      if(sensors == PROGRAM_ALARM){
        set_alarmminutes();
        state = STATE_SET_ALARM_MINUTES;
      }
      else if (sensors == INCREMENT){
        incrementHours();
      }
      else if (sensors == DECREMENT){
        decrementHours();
      }
      else {
        showDot = true;
        blinkDot = false;
        blinkDisplay = true;
      }
      updateHours(alarm);
      break;

      case STATE_SET_ALARM_MINUTES:
      if(sensors == PROGRAM_ALARM){
        set_alarmsong();
        state = STATE_SET_ALARM_SONG;
      }
      else if (sensors == INCREMENT){
        incrementMinutes();
      }
      else if (sensors == DECREMENT){
        decrementMinutes();
      }
      else {
        showDot = true;
        blinkDot = false;
        blinkDisplay = true;
      }
      updateMinutes(alarm);
      break;

      case STATE_SET_ALARM_SONG:
      if(sensors == PROGRAM_ALARM){
        alarm_on();
        state = STATE_ALARM_ON;
      }
      else if (sensors == INCREMENT){
        incrementSongNr();
      }
      else if (sensors == DECREMENT){
        decrementSongNr();
      }
      else {
        showDot = false;
        blinkDot = false;
        blinkDisplay = true;
      }
      updateSong();
      break;
  }
}


