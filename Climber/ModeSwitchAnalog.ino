/*
 *  Read a mode switch, from an analog port
 */

/*
** setup - initialization, called once
**
** Pass in the Arduino pin for the switch
*/
void ModeSwitchAnalog::setup(const char *_whoami, int _pin)
{
  pin = _pin;
  whoami = _whoami;
  previous=false;
  switchedToOn = false;
  sleepUntil = millis();
}

void ModeSwitchAnalog::loop()
{
  // debounce
  if ( millis() < sleepUntil ) return;

  previous = current;
  current = readSwitch();
  
  if ( current != previous ) {
    switchedToOn = current;
    sleepUntil = millis() + MODESWITCH_DEBOUNCE;
    showStatus();
  } else {
    switchedToOn = false;
  }
}

bool ModeSwitchAnalog::readSwitch(void)
{
  return (analogRead(pin) > MODESWITCHANALOG_ON);
}

void ModeSwitchAnalog::showStatus(void) 
{
//  Serial.print(whoami);Serial.print(" switch p=");Serial.print(previous);Serial.print(" c=");Serial.print(current);Serial.print(" sw=");Serial.println(switchedToOn);
}

