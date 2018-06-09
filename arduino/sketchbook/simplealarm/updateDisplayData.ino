// Displays time
void displaySetup()
{
  //The initialization of the display
  disp.init();
  disp.set(1);
}

void updateTime()
{
  DateTime now = rtc.now();
  displayData[0] = now.hour() / 10;
  displayData[1] = now.hour() % 10;
  displayData[2] = now.minute() / 10;
  displayData[3] = now.minute() % 10;
}

void updateHours(int alarm[])
{
  displayData[0] = alarm[0] / 10;
  displayData[1] = alarm[0] % 10;
  displayData[2] = 17;
  displayData[3] = 17;
}

void updateMinutes(int alarm[])
{
  displayData[0] = 17;
  displayData[1] = 17;
  displayData[2] = alarm[1] / 10;
  displayData[3] = alarm[1] % 10;
}

void updateSong()
{
  displayData[0] = 17;
  displayData[1] = 17;
  displayData[2] = 17;
  displayData[3] = alarmSongNr;
}

