#include "pins.h"

#define BUTTON_DOWN LOW
#define BUTTON_UP HIGH

void Button::setup()
{
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  lastState = state();
  pushed = false;
  minInterval = 0;
}

/*
 * loop - called on each main loop.
 *
 */
 
void Button::loop()
{
  /*
   * Look for button transitions, up to down.  The time interval is only checked after
   * an up-down transition to prevent holding the button down from triggering an
   * event every minInterval milliseconds
   */
  if ( lastState == BUTTON_UP && isDown() ) {
      
    /*
     * On a transition from up to down, denote it as a button push only if
     * enough time has gone by.
     */
      
    if ( millis() >= lastTimePushed + minInterval ) {
      pushed = true;
      lastTimePushed = millis();
    }
  }
  lastState = state();
}

/**
 * setMinInterval - set the minimum interval (in milliseconds) between pushes
 */
 
void Button::setMinInterval(unsigned int _minInterval)
{
  minInterval = _minInterval;
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

unsigned int state()
{
  return digitalRead(BUTTON_PIN);
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
