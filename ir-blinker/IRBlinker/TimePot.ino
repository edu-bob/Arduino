#include "pins.h"

// Min and max times in seconds

#define TIMEPOT_MIN 10
#define TIMEPOT_MAX 14400ul

#define TIMEPOT_TESTMODE_VALUE 10000ul

void TimePot::setup(int _pin, bool _debug=false)
{
  debug = _debug;
  pin = _pin;
}

 
void TimePot::loop()
{
}

unsigned long TimePot::getValue()
{
  if ( testMode ) {
    value = TIMEPOT_TESTMODE_VALUE;
  } else {
    value = analogRead(pin)*(TIMEPOT_MAX-TIMEPOT_MIN)/1023 + TIMEPOT_MIN;
  }

  if ( debug ) {
    Serial.print(F("Timepot analogRead = ")); Serial.println(analogRead(pin));
    Serial.print(F("Timepot delay time = ")); Serial.print(value);Serial.println(F(" seconds"));
  }
  return value*1000;
}

void TimePot::setDebug(bool sw)
{
  debug = sw;
}

void TimePot::setTestMode(bool _testMode)
{
  testMode = _testMode;
  if ( testMode ) {
    Serial.print(F("TimePot test mode value = "));
    Serial.println(TIMEPOT_TESTMODE_VALUE);
  }
}
