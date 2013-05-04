//
// Disable Switch
//

void DisableSwitch::setup()
{
}

void DisableSwitch::begin(int _pin)
{
  pin = _pin;
  pinMode(pin, INPUT_PULLUP);
  value = readSwitch();
}

void DisableSwitch::loop()
{
  // determine if the switch has changed.  This is only used to update the display
  
  int newValue;
  newValue = readSwitch();
  if ( value != newValue ) {
    changed = true;
    value = newValue;
  }
}

// This could return "value, but to be safe and avoid races, just read the switch

bool DisableSwitch::isEnabled()
{
  return readSwitch();
}

int DisableSwitch::readSwitch()
{
  return digitalRead(pin);
}

bool DisableSwitch::isChanged()
{
  bool saveChanged = changed;
  changed = false;
  return saveChanged;
}

