void playSong() 
{
  int8_t volume = 0x0F;//0~0x1e (30 adjustable level)
  int8_t folderName = 0x01;//folder name must be 01 02 03 04 ...
  int8_t fileName = alarmSongNr; // prefix of file name must be 001xxx 002xxx 003xxx 004xxx ...
  mp3.setVolume(volume);
  delay(50);//you should wait for >=50ms between two commands
  mp3.playWithFileName(folderName,fileName);
}

void stopSong()
{
  mp3.stopPlay();
}

