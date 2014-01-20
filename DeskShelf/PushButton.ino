#define PUSHBUTTON_DOWN LOW
#define PUSHBUTTON_UP HIGH

#define PUSHBUTTON_DELAY 1000

void PushButton::setup(int _pin)
{
  pin = _pin;
  pinMode(pin, INPUT_PULLUP);
}

/*
 * loop - called on each main loop.
 *
 */
 
void PushButton::loop()
{
  unsigned int val = value();
  if ( val == lastValue ) {
    if ( millis() > lastChangeTime + PB_DEBOUNCE ) {
      if ( stableValue != val ) {
        changed = true;
      }
      stableValue = val;
    }
  } else {
    lastValue = val;
    lastChangeTime = millis();
  }
}

bool PushButton::isChanged()
{
  bool _changed = changed;
  changed = false;
  return _changed;
}

unsigned int PushButton::getStableValue()
{
  return stableValue;
}

unsigned int PushButton::value()
{
  return digitalRead(pin)==LOW;
}

