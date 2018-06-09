void alarm_on()
{
  // stop song when entering this state
  playingSong = false;
  stopSong();
}
 
void alarm_off()
{
  // stop song when entering this state
  playingSong = false;
  stopSong(); 
}

void alarm_started()
{
  playingSong = true;
  playSong();
}

void alarm_snoozed()
{
  playingSong = false;
  stopSong();
}

void set_alarmhours()
{ 
}

void set_alarmminutes()
{
}

void set_alarmsong()
{
}

void incrementHours()
{
  if(alarm[0] < 23)
  {
    alarm[0]++;
  } else
  {
    alarm[0] = 0;
  }
}

void decrementHours()
{
  if(alarm[0] > 0)
  {
    --alarm[0];
  } else
  {
    alarm[0] = 23;
  }
}

void incrementMinutes()
{
  if(alarm[1] < 59)
  {
    alarm[1]++;
  } else
  {
    alarm[1] = 0;
  }
}

void decrementMinutes()
{
  if(alarm[1] > 0)
  {
    --alarm[1];
  } else
  {
    alarm[1] = 59;
  }
}

void incrementSongNr()
{
  if(alarmSongNr < 3)
  {
    alarmSongNr++;
  } else
  {
    alarmSongNr = 1;
  }
}

void decrementSongNr()
{
  if(alarmSongNr > 1)
  {
    alarmSongNr--;
  } else
  {
    alarmSongNr = 3;
  }
}

