#ifndef _RichUNOKitC_MP3_H__
#define _RichUNOKitC_MP3_H__

#include <SoftwareSerial.h>
#include <Arduino.h>

/************Command byte**************************/
#define CMD_NEXT_SONG 0X01
#define CMD_PREV_SONG 0X02
#define CMD_PLAY_W_INDEX 0X03
#define CMD_VOLUME_UP 0X04
#define CMD_VOLUME_DOWN 0X05
#define CMD_SET_VOLUME 0X06
#define CMD_SINGLE_CYCLE_PLAY 0X08
#define CMD_SEL_DEV 0X09
  #define DEV_TF 0X02
#define CMD_SLEEP_MODE 0X0A
#define CMD_WAKE_UP 0X0B
#define CMD_RESET 0X0C
#define CMD_PLAY 0X0D
#define CMD_PAUSE 0X0E
#define CMD_PLAY_FILE_NAME 0X0F
#define CMD_STOP 0X16
#define CMD_FOLDER_CYCLE 0X17
#define CMD_SHUFFLE_PLAY 0X18
#define CMD_SET_SINGLE_CYCLE 0X19
  #define SINGLE_CYCLE_ON 0X00
  #define SINGLE_CYCLE_OFF 0X01
#define CMD_SET_DAC 0X1A
  #define DAC_ON  0X00
  #define DAC_OFF 0X01
#define CMD_PLAY_W_VOL 0X22

#define CMD_CHECK_STATUS 0x42
  #define STATUS_STOP 0
  #define STATUS_PAUSE 1
  #define STATUS_PLAY 1
/*********************************************************************/


class MP3
{
public:
	MP3(uint8_t rxd, uint8_t txd);
	void begin();
	void play();
	void pause();
	void nextSong();
	void previousSong();
	void volumeUp();
	void volumeDown();
	void stopPlay();
	
	
	void startSingleCycle();
	void stopSingleCycle();
	void folderCyclePlay(uint8_t directory);
	void shufflePlay();	
	
	void playWithIndex(int8_t index);
    void waitStop();
	uint8_t getStatus();

	void setVolume(int8_t volume);
	void playWithFileName(int8_t directory, int8_t file);
	void playWithVolume(int8_t index, int8_t volume);
//	void cyclePlay(int16_t index);
//	void setCyleMode(int8_t AllSingle);
	void sendCommand(int8_t command, int16_t dat = 0);
    void listen(){myMP3.listen();}

private:
	SoftwareSerial myMP3;
	
};

#endif
