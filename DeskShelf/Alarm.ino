
/*
 * Alarm - manage alarms on the shelf
 */
 
void Alarm::setup()
{
  status = ALARM_OKAY;
  nextTime = millis();
}

void Alarm::loop()
{
}

void Alarm::setStatus(int _status)
{
  status = _status;
  switch(status) {
    case ALARM_OKAY:
      break;
    case ALARM_OVERCURRENT:
      break;
  }
  
}

/*
 * setMusicObject - give this class a copy of the Music singleton.
 *
 */
 
void Alarm::setMusicObject(Music &_music)
{
  music = &_music;
}

