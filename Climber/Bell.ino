/*
 *  Control the bell
 */

/*
** setup - initialization, called once
**
** Pass in the Arduino pins for the bell
*/
void Bell::setup(int _pin, int _potPin)
{
  pin = _pin;
  potPin = _potPin;
  pinMode(pin, OUTPUT);
  off();
}

void Bell::loop()
{
  if ( isOn() && millis() >= ringTill ) {
    off();
  }
}

void Bell::ring(void)
{
  unsigned long ringtime = analogRead(potPin)*BELL_MAX_DELAY/1023;
  Serial.print("ring time="); Serial.println(ringtime);
  ringTill = millis() + ringtime;
  on();
}

void Bell::on(void)
{
  digitalWrite(pin, BELL_ON);
  bellIsOn = true;
}
void Bell::off(void)
{
  digitalWrite(pin, BELL_OFF);
  bellIsOn = false;
}

bool Bell::isOn(void)
{
  return bellIsOn;
}


