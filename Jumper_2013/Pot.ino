#define POT_MIN_CHANGE 20

#define POT_DELAY_MAX 1000ul
#define POT_DELAY_MIN 100ul

void Pot::setup()
{
  changed = true;
  goodValue = readValue();
}

//
// On each iteration, see if we are debouncing /or/ check for a change
//
// This copies the bits into goodValue only after no change for POT_SETTLE milliseconds
//
void Pot::loop()
{
  changed = false;
  
  // The value must have changed more than POT_MIN_CHANGE to register
  
  int newValue = readValue();
  int delta = (newValue > goodValue) ? (newValue-goodValue) : (goodValue-newValue);

  if ( delta >= POT_MIN_CHANGE ) {
    goodValue = newValue;
    changed = true;
  }
}

//
// getValue - return the last debounced value
//

int Pot::getValue()
{
  return goodValue;
}

//
// readValue - private function to read the input bits
//
int Pot::readValue()
{
  unsigned long pot = analogRead(POT_PIN);
  unsigned long delay = POT_DELAY_MIN + (unsigned long)(pot * (unsigned long)(POT_DELAY_MAX-POT_DELAY_MIN)) / 1023ul;
  return (delay > POT_DELAY_MAX ? POT_DELAY_MAX : delay);
}

bool Pot::isChanged()
{
  return changed;
}

