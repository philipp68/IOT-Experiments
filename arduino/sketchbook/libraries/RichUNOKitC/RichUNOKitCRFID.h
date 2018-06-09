#ifndef _RichUNOKitC_RFID_H__
#define _RichUNOKitC_RFID_H__

#include <SoftwareSerial.h>
#include <Arduino.h>

class RFID
{
public:
	RFID(uint8_t txd):myRFID(txd,0){myRFID.begin(9600);}
	uint32_t readTag();
	void waitResume();
	void listen(){myRFID.listen();}
private:
	SoftwareSerial myRFID;
};

#endif
