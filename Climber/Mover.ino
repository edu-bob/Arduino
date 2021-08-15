/*
 *  Control the movement solenoid
 */

/*
** setup - initialization, called once
**
** Pass in the Arduino pins for the solenoid
*/
void Mover::setup(int _pin)
{
  pin = _pin;
  pinMode(pin, OUTPUT);
  digitalWrite(pin, MOVER_OFF);
  state = MOVER_CONTRACTED;
}

void Mover::loop()
{
}

int Mover::getState(void)
{
  return state;
}

/**
 * setState
 * 
 * newState - MOVER_CONTRACTED or MOVER_EXPANDED
 */
void Mover::setState(int newState)
{
  digitalWrite(pin,newState == MOVER_CONTRACTED ? MOVER_OFF : MOVER_ON);
  state = newState;
}
void Mover::toggleState(void)
{
  switch(state) {
    case MOVER_EXPANDED:
      digitalWrite(pin, MOVER_OFF);
      state = MOVER_CONTRACTED;
      Serial.println("CONTRACT");
      break;
    case MOVER_CONTRACTED:
      digitalWrite(pin, MOVER_ON);
      state = MOVER_EXPANDED;
      Serial.println("EXPANDED");
      break;
  }
}

