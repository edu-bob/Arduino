/*
 *  Read the movement button
 */

/*
** setup - initialization, called once
**
** Pass in the Arduino pins for the button
*/
void MoveButton::setup(int _pin)
{
  pin = _pin;
  pinMode(pin, INPUT);
  sleepUntil = millis();
  previouslyPressed = false;
}

void MoveButton::loop()
{
  if ( millis() < sleepUntil ) return;
  previouslyPressed = pressed;
  pressed = readButton();
  if ( pressed != previouslyPressed ) {
    sleepUntil = millis() + MOVEBUTTON_DEBOUNCE;
  }
}

bool MoveButton::readButton(void)
{
  int val = digitalRead(pin);
  return (val==MOVEBUTTON_PRESSED);
}

bool MoveButton::getButton(void)
{
  return pressed;
}
bool MoveButton::isPressed()
{
  return pressed;
}

