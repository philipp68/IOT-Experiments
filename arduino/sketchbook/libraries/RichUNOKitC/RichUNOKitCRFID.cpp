/****************************************************************************/	
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

#include "RichUNOKitCRFID.h"

uint32_t RFID::readTag()
{
  char temp;
  char raw[14];
  char hexcode[8];
  
  while(myRFID.available()<14);
  for(unsigned char i=0;i < 14;i++)// 
  {
	temp=myRFID.read();
	raw[i] = temp;
  } 	  
  if((raw[0] == 0x02)&& (raw[13] == 0x03))
  {
	 for(unsigned char i=0;i < 8;i++){
	 hexcode[i] = raw[i+3];
	 }
  }
  else return 0;
  unsigned long IDcode = 0;
  for(unsigned char i=0;i < 8;i++)//
  {
	IDcode <<= 4;
	if(hexcode[i]>0x40)  IDcode+=hexcode[i]-55;
	else IDcode +=hexcode[i]-0x30;
  }

  return IDcode;
}
void RFID::waitResume()
{
  char temp;
  while(myRFID.available()){
	temp=myRFID.read();
	delay(1);
  }
  delay(500);
  while(myRFID.available()){
	temp=myRFID.read();
	delay(1);
  }
}
