#include "pins.h"

#define BUTTON_DOWN LOW
#define BUTTON_UP HIGH

#define BUTTON_DELAY_MAX 1000ul
#define BUTTON_DELAY_MIN 200ul

void Button::setup()
{
  pressesRaw = 0;
  pressesFiltered = 0;
  changed = false;
}

/*
 * begin - initialization; save the pin numbers
 */
 
void Button::begin(int _pin, int _delayPin)
{
  pin = _pin;
  delayPin = _delayPin;
  pinMode(pin, INPUT_PULLUP);
  
  lastState = state();
  pushed = false;
  enabled = true;
}

//
// Called once per cycle.
// If the button was pressed, flag "changed"
// But only count presses that were passed along if "enabled"
//

void Button::loop()
{
  changed = false;
  
  /*
   * Look for button transitions, up to down.  The time interval is only checked after
   * an up-down transition to prevent holding the button down from triggering an
   * event every minInterval milliseconds
   */
  if ( lastState == BUTTON_UP && isDown() ) {
     pressesRaw++;
     changed = true;
    /*
     * On a transition from up to down, denote it as a button push only if
     * enough time has gone by.
     */
      
    if ( millis() >= lastTimePushed + getDelay() ) {
      if ( enabled ) pressesFiltered++;
      pushed = true;
      lastTimePushed = millis();
    }
  }
  if ( lastState == BUTTON_DOWN && !isDown() ) {
    changed = true;
  }
  
  lastState = state();
}


/*
 * wasPressed - determine if the button rtansitioned from up to down since the last time checked.
 */
 
bool Button::wasPressed()
{
  if ( pushed ) {
    pushed = false;
    return true;
  }
  return false;
}

/*
 ** isDown - determine if the button is presed right now
 */
 
bool Button::isDown()
{
  return state() == BUTTON_DOWN;
}

unsigned int Button::state()
{
  return digitalRead(pin);
}

unsigned long Button::getDelay()
{
  unsigned long pot = analogRead(delayPin);
  unsigned long delay = BUTTON_DELAY_MIN + (unsigned long)(pot * (unsigned long)(BUTTON_DELAY_MAX-BUTTON_DELAY_MIN)) / 1023ul;
  return (delay > BUTTON_DELAY_MAX ? BUTTON_DELAY_MAX : delay);
}

bool Button::isChanged()
{
  bool saveChanged = changed;
//  changed = false;
  return saveChanged;
}

//--------------------------------------------------------
// Test Functions
//
void Button::testSetup(void)
{
    pinMode(BUTTON_PIN, INPUT_PULLUP);
    testLastState = digitalRead(BUTTON_PIN);
    testStartTime = millis();
}
void Button::testLoop(void)
{
  unsigned int currentState = digitalRead(BUTTON_PIN);
  if ( currentState != testLastState ) {
    Serial.print(millis()-testStartTime);
    Serial.print(F(" Push button changed from "));
    Serial.print(testLastState);
    Serial.print(F(" to "));
    Serial.println(currentState);
    testLastState = currentState;
  }
}
