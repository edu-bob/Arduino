#include "pins.h"

static const int Blinker::ledStates[][LEDS] = {{1,0},{0,1},{1,0},{0,1},{0,0}};
static const unsigned long Blinker::ledDelays[] = { 500ul, 500ul, 500ul, 500ul, 5000ul};

void Blinker::setup(int _pinbase, bool _debug=false)
{
  running = false;
  state = 0;
  debug = _debug;
  pinbase = _pinbase;
  for ( int i=0 ; i<LEDS ; i++ ) {
    pinMode(pinbase+i,OUTPUT);
  }
  setDuration(BLINKER_DEFAULT_DURATION);
  setState(0,LED_OFF);
  setState(1,LED_OFF);
  states = sizeof ledStates / sizeof ledStates[0];
}

void Blinker::loop()
{
  if ( running ) {
    if ( millis() >= nextChange ) {
      setLEDsByState();
      nextChange = millis() + ledDelays[state];
      if ( debug ) {
        Serial.print(F("Blinker: state = "));
        Serial.print(state);
        for ( int i=0; i<LEDS ; i++ ) {
          Serial.print(ledStates[state][i]?F(" ON"):F(" OFF"));
        }
        Serial.println();
      }
      state = ++state % states;
    }
  }
}

void Blinker::start()
{
  running = true;
  nextChange = millis() + duration;
  state = 0;
}
void Blinker::stop()
{
  running = false;
  setState(0,LED_OFF);
  setState(1,LED_OFF);
}

void Blinker::setLEDsByState()
{
  for ( int i=0 ; i<LEDS ; i++ ) {
    setState(i, ledStates[state][1] ? LED_ON : LED_OFF);
  }
}
void Blinker::setDuration(unsigned long _duration)
{
  duration = _duration;
}

void Blinker::setState(int led, int onoff)
{
  digitalWrite(pinbase+led, onoff);
}

void Blinker::setDebug(bool sw)
{
  debug = sw;
}

void Blinker::setTestMode(bool _testMode)
{
  testMode = _testMode;
}
