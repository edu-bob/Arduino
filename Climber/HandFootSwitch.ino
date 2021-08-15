/*
 *  Read the hand/foot switches
 */

/*
** setup - initialization, called once
**
** Pass in the Arduino pins for the switches
*/
void HandFootSwitch::setup(int _pinFoot, int _pinHand)
{
  pinFoot = _pinFoot;
  pinHand = _pinHand;
  pinMode(pinFoot, INPUT);
  pinMode(pinHand, INPUT);
  previous = getSetting();
  ignoreUntil = millis();
}

void HandFootSwitch::loop()
{
  // ignore the switch until a certain amount of time has gone by.
  // this prevents the user from just quickly flipping the switch back and forth and shaking the carriage to bits.
  if ( millis() < ignoreUntil ) return;

  previous = current;
  current = getSetting();
  ignoreUntil = millis() + HANDFOOT_IGNORE_TIME;
}

// if not set to FOOT, then must be HAND

int HandFootSwitch::getSetting(void)
{
  return digitalRead(pinFoot) == HANDFOOT_ON ? FOOT_SW : digitalRead(pinHand) == HANDFOOT_ON ? HAND_SW : NO_SW;
}

bool HandFootSwitch::isFoot(void) {
  return current == FOOT_SW;
}
bool HandFootSwitch::isHand(void) {
  return current == HAND_SW;
}

