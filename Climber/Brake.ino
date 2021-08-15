/*
 *  Control the brakes
 */


/*
** setup - initialization, called once
**
** Pass in the Arduino pins for the lower and upper brakes
** Leaves with the bottom brake gripped and the upper brake not gripped
*/
void Brake::setup(int _pinFoot, int _pinHand, bool _newType)
{
  newType = _newType;
  pinFoot = _pinFoot;
  pinHand = _pinHand;
  pinMode(pinFoot, OUTPUT);
  pinMode(pinHand, OUTPUT);

  setFoot(true);
  setHand(false);
}

void Brake::loop()
{
//  if ( oldNewSwitch.isOff() ) {
//    Serial.println("O");
//  } else {
//    Serial.println("N");
//  }
}

void Brake::setNewType(bool _newType)
{
  newType = _newType;
}
/*
** setBrake - turn a brake on (true) or off(false)
*/
void Brake::setFoot(bool grip)
{
    footOn = grip;
//      if(!grip && !upperOn) setBrake(BRAKE_UPPER, true);
    doBrake(pinFoot,grip);
}

/**
 * doBrake - set a brake depending on the OLD/New switch
 * 
 * The OLD setting is for normally retracted cylinders, NEW for normally extended
 */
void Brake::doBrake(unsigned int pin, bool grip)
{
  if ( !newType ) {
    digitalWrite(pin,grip? BRAKE_ON : BRAKE_OFF);
  } else {
    digitalWrite(pin,grip? BRAKE_OFF : BRAKE_ON);
  }
}

bool Brake::getFoot(void)
{
  return footOn;
}

void Brake::setHand(bool grip)
{
  handOn = grip;
//  if ( !grip && !lowerOn ) setBrake(BRAKE_FOOT, true);
  doBrake(pinHand,grip);
}

bool Brake::getHand(void)
{
  return handOn;
}

bool Brake::isSafe()
{
  return footOn || handOn;
}


