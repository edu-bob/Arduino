/*
 *  Read a mode switch
 */

/*
** setup - initialization, called once
**
** Pass in the Arduino pin for the switch
*/
void ModeSwitch::setup(const char *_whoami, int _pin)
{
  pin = _pin;
  whoami = _whoami;
  pinMode(pin, INPUT);
  previous=false;
  switchedToOn = false;
  sleepUntil = millis();
}

void ModeSwitch::loop()
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

bool ModeSwitch::readSwitch(void)
{
  return (digitalRead(pin)==MODESWITCH_ON);
}

void ModeSwitch::showStatus(void) 
{
//  Serial.print(whoami);Serial.print(" switch p=");Serial.print(previous);Serial.print(" c=");Serial.print(current);Serial.print(" sw=");Serial.println(switchedToOn);
}

