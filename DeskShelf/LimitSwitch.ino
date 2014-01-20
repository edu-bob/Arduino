/*
 * Limit Switch implementation
 */
 
void LimitSwitch::setup()
{
    pinMode(LIMIT_IN_PIN, INPUT_PULLUP);
    pinMode(LIMIT_NEAR_IN_PIN, INPUT_PULLUP);
    pinMode(LIMIT_OUT_PIN, INPUT_PULLUP);
    pinMode(LIMIT_NEAR_OUT_PIN, INPUT_PULLUP);
    lastValue = value();
    stableValue = lastValue;
    lastChangeTime = millis();
    changed = true;
}

void LimitSwitch::loop()
{
  unsigned int val = value();
  if ( val == lastValue ) {
    if ( millis() > lastChangeTime + LS_DEBOUNCE ) {
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

bool LimitSwitch::isChanged()
{
  bool _changed = changed;
  changed = false;
  return _changed;
}

unsigned int LimitSwitch::getStableValue()
{
  return stableValue;
}

unsigned int LimitSwitch::value()
{
  return (((((pinValue(LIMIT_IN_PIN) << 1) | pinValue(LIMIT_NEAR_IN_PIN)) << 1) | pinValue(LIMIT_OUT_PIN)) << 1) | pinValue(LIMIT_NEAR_OUT_PIN);
}
unsigned int LimitSwitch::pinValue(int pin)
{
  return digitalRead(pin)==LOW;
}


// pin-by-pin functions

bool LimitSwitch::isIn(void)
{
  return (getStableValue() & LS_IN) != 0;
}
bool LimitSwitch::isNearIn(void)
{
  return (getStableValue() & LS_NEARIN) != 0;
}
bool LimitSwitch::isOut(void)
{
  return (getStableValue() & LS_OUT) != 0;
}
bool LimitSwitch::isNearOut(void)
{
  return (getStableValue() & LS_NEAROUT) != 0;
}

