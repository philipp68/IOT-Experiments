/****************************************************************************/	
//	Function: Cpp file for Red Serial MP3 Player module
//	Hardware: Serial MP3 Player A
//	Arduino IDE: Arduino-1.6.5
//	Author:	 Fred	
//	Date: 	 2017.05.20
//	by OPEN-SMART Team
//
//  This library is free software; you can redistribute it and/or
//  modify it under the terms of the GNU Lesser General Public
//  License as published by the Free Software Foundation; either
//  version 2.1 of the License, or (at your option) any later version.
//
//  This library is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
//  Lesser General Public License for more details.
//
//  You should have received a copy of the GNU Lesser General Public
//  License along with this library; if not, write to the Free Software
//  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA
//
/****************************************************************************/
#include <SoftwareSerial.h>
#include "RichUNOKitCMP3.h"

MP3::MP3(uint8_t rxd, uint8_t txd):myMP3(txd, rxd)
{
  myMP3.begin(9600);//baud rate is 9600bps
}
void MP3::begin()
{
  sendCommand(CMD_SEL_DEV, DEV_TF);//select the TF card  
  delay(100);
}
void MP3::play()
{
  sendCommand(CMD_PLAY);
}
void MP3::pause()
{
  sendCommand(CMD_PAUSE);
}

void MP3::nextSong()
{
  sendCommand(CMD_NEXT_SONG);
}

void MP3::previousSong()
{
  sendCommand(CMD_PREV_SONG);
}

void MP3::volumeUp()
{
  sendCommand(CMD_VOLUME_UP);
}

void MP3::volumeDown()
{
  sendCommand(CMD_VOLUME_DOWN);
}


void MP3::stopPlay()
{
  sendCommand(CMD_STOP);
}

void MP3::startSingleCycle()
{
  sendCommand(CMD_SINGLE_CYCLE_PLAY,SINGLE_CYCLE_ON);
}	
void MP3::stopSingleCycle()
{
  sendCommand(CMD_SINGLE_CYCLE_PLAY,SINGLE_CYCLE_OFF);
}
void MP3::folderCyclePlay(uint8_t directory)
{
  sendCommand(CMD_FOLDER_CYCLE,directory);
}
void MP3::shufflePlay()
{
  sendCommand(CMD_SHUFFLE_PLAY);
}

void MP3::playWithIndex(int8_t index)
{
  sendCommand(CMD_PLAY_W_INDEX,index);
}
void MP3::waitStop()
{
  int dat;
  while(myMP3.available()<20);
  while(myMP3.read() != 0x3D)//
  {}

  int temp;
  while(myMP3.available())temp = myMP3.read();
  
}


uint8_t MP3::getStatus()
{
  int dat;
  while(myMP3.available()){
  	dat = myMP3.read();
	delay(2);
  }
  sendCommand(CMD_CHECK_STATUS);
  while(myMP3.available()<10);
  while(myMP3.read() != CMD_CHECK_STATUS)//the status come after the command 
  {}
  dat = myMP3.read();//0x00
  dat = myMP3.read();
  dat = myMP3.read();//status byte: 0 = stop; 1=pause; 2 = playing
 // Serial.print("*");
//  Serial.println(dat);
  return dat;
  
}

void MP3::setVolume(int8_t volume)
{
  if(volume < 0) volume = 0;          //min volume
  else if(volume > 0x1e) volume = 0x1e;//max volume
  sendCommand(CMD_SET_VOLUME, volume);
}

void MP3::playWithFileName(int8_t directory, int8_t file)
{
  int16_t dat;
  dat = ((int16_t)directory) << 8;
  dat |= file;
  sendCommand(CMD_PLAY_FILE_NAME, dat);
}

void MP3::playWithVolume(int8_t index, int8_t volume)
{
  if(volume < 0) volume = 0;          //min volume
  else if(volume > 0x1e) volume = 0x1e;//max volume
  int16_t dat;
  dat = ((int16_t)volume) << 8;
  dat |= index;
  sendCommand(CMD_PLAY_W_VOL, dat);
}


/*cycle play with an index*/
/*void MP3::cyclePlay(int16_t index)
{
  mp3_6bytes(CMD_SET_PLAY_MODE,index);
}*/

/*void MP3::setCyleMode(int8_t AllSingle)
{
 //AllSingle parameter should be 0 or 1, 0 is all songs cycle play, 1 is single cycle play
  if((AllSingle == 0) || (AllSingle == 1))
    mp3_5bytes(CMD_SET_PLAY_MODE,AllSingle);
}*/



void MP3::sendCommand(int8_t command, int16_t dat)
{
  uint8_t Send_buf[8];
  Send_buf[0] = 0x7e; //
  Send_buf[1] = 0xff; //
  Send_buf[2] = 0x06; //
  Send_buf[3] = command; //
  Send_buf[4] = 0x00;//
  Send_buf[5] = (int8_t)(dat >> 8);//datah
  Send_buf[6] = (int8_t)(dat); //datal
  Send_buf[7] = 0xef; //
  for(uint8_t i=0; i<8; i++)//
  {
    myMP3.write(Send_buf[i]) ;
  }
}


