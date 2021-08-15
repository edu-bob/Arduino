/*
 * limitSwitch - control the limit switch
 */

 void LimitSwitch::setup(const char *_whoami, int _pin)
{
  pin = _pin;
  whoami = _whoami;
  pinMode(pin, INPUT);
  previous=false;
  switchedToOn = false;
}

void LimitSwitch::loop()
{
  // debounce
  if ( millis() < sleepUntil ) return;

  previous = current;
  current = readSwitch();
  
  if ( current != previous ) {
    switchedToOn = current;
//    Serial.print("limit switch p=");Serial.print(previous);Serial.print(" c=");Serial.print(current);Serial.print(" sw=");Serial.println(switchedToOn);
    sleepUntil = millis() + LIMITSWITCH_DEBOUNCE;
  } else {
    switchedToOn = false;
  }

}

bool LimitSwitch::readSwitch(void)
{
  return digitalRead(pin) == LIMITSWITCH_ON;
}

bool LimitSwitch::isOn(void)
{
  return current;
}

bool LimitSwitch::changedToOn(void)
{
  return switchedToOn;
}

