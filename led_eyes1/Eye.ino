//
// Control logic an eye
//

#include "pins.h"

#define EYE_CYCLE_TIME 2000l

/**
 * setup - constructor, sort of, for a new eye
 *
 * "cycle" is just a number to determine left from right (from anything else) in case some logic is
 *    needed to do something different between the two eyes, like alternating blinking.
 */

void Eye::setup(int _pin, char *_label, RandCache *_rand, int _cycle)
{
  pin = _pin;
  label = _label;
  rand = _rand;
  cycle = _cycle;
  debug = 0;
  reset();
}

/*
 * reset - reset the eye to an initial state.
 *
 * This is separated from setup in order to allow for re-initializing the eye.
 */

void Eye::reset()
{
  pinMode(pin, OUTPUT);
  state = EYE_INVALID;
  actionNextTime = 0;
  actionBaseTime = 0;
  rand->reset();
}

/**
 * setDebug - turn on and off debugging
 */

void Eye::setDebug(bool _debug)
{
  debug = _debug;  
}
/**
 * Polling routine.  
 */
 
void Eye::loop()
{
  switch (state) {
    case EYE_IDLE:
      loopIdle();
      break;
    case EYE_BLINKING:
      loopBlinking();
      break;
    case EYE_ALTERNATING:
      loopAlternating();
      break;
  }
  // delay(30);
  // Serial.print("value ");Serial.println(value);
}

/**
 * Can the eye blink?  Determines by being in idel state, full on
 */

bool Eye::canBlink()
{
  return state == EYE_IDLE && idleState == EYE_IDLE_STEADY_FULL;
}
/**
 * Set state
 */

void Eye::setState(EyeState _state)
{
  if ( state != _state ) {
    switch(state) {
      case EYE_IDLE: 
        stopIdle();
        break;
      case EYE_BLINKING:
        stopBlinking();
        break;      
      case EYE_ALTERNATING:
        stopAlternating();
        break;      
    }
    state = _state;
    switch(state) {
      case EYE_IDLE:
        startIdle();
        break;
      case EYE_BLINKING:
        startBlinking();
        break;
      case EYE_ALTERNATING:
        startAlternating();
        break;      
    }
  }
}

void Eye::stopIdle()
{
}
void Eye::stopBlinking()
{
}
void Eye::stopAlternating()
{
}

void Eye::startIdle()
{
  setIdleState(EYE_IDLE_STEADY_FULL);
  setLED(EYE_ON);
}

void Eye::startBlinking()
{
  setBlinkingState(EYE_BLINKING_CLOSED);
  blinks = rand->getRandom(EYE_BLINKING_RAND_KEY, 1, 11) <= 7 ? 1 : 2;  
  setLED(EYE_OFF);
}

void Eye::startAlternating()
{
  setAlternatingState(EYE_ALTERNATING_0);
  blinks = 7;
  setLED(EYE_ON);
}

/**
 * idle mode loop
 */
void Eye::loopIdle()
{
  switch(idleState) {
    case EYE_IDLE_STEADY_FULL:
      setLED(EYE_ON);
      if ( millis() >= actionNextTime ) {
        setIdleState(EYE_IDLE_GOING_DIM);        
      }
      break;
    case EYE_IDLE_GOING_DIM:
      if ( millis() >= actionNextTime ) {
        setIdleState(EYE_IDLE_STEADY_DIM);
      } else {
        setLED(EYE_ON-abs(EYE_ON-EYE_IDLE_MIN)*(millis()-actionBaseTime)/(actionNextTime-actionBaseTime));
      }    
      break;
    case EYE_IDLE_STEADY_DIM:
      setLED(EYE_IDLE_MIN);
      if ( millis() >= actionNextTime ) {
        setIdleState(EYE_IDLE_GOING_FULL);        
      }
      break;
    case  EYE_IDLE_GOING_FULL:
      if ( millis() >= actionNextTime ) {
        setIdleState(EYE_IDLE_STEADY_FULL);        
      } else {
        setLED(EYE_IDLE_MIN+(EYE_ON-EYE_IDLE_MIN) * (millis()-actionBaseTime)/(actionNextTime-actionBaseTime));
      }
      break;
  }
}

void Eye::loopBlinking()
{
  switch ( blinkingState ) {
    case EYE_BLINKING_CLOSED:
      if ( millis() >= actionNextTime ) {
        setBlinkingState(EYE_BLINKING_REOPEN);
        setLED(EYE_ON);
        break;
      }
      case EYE_BLINKING_REOPEN:
        if ( millis() > actionNextTime ) {
          if ( --blinks > 0 ) {
            setBlinkingState(EYE_BLINKING_CLOSED);
            setLED(EYE_OFF);
          } else {
            setState(EYE_IDLE);
            setLED(EYE_ON);
          }
          break;
        }    
    }
}
void Eye::loopAlternating()
{
  switch ( alternatingState ) {
    case EYE_ALTERNATING_0:
      if ( millis() >= actionNextTime ) {
        setAlternatingState(EYE_ALTERNATING_1);
        setLED(cycle ? EYE_ON : EYE_OFF);
        break;
      }
      case EYE_ALTERNATING_1:
        if ( millis() > actionNextTime ) {
          if ( --blinks > 0 ) {
            setAlternatingState(EYE_ALTERNATING_0);
            setLED(cycle ? EYE_OFF : EYE_ON);
          } else { // all done
            setState(EYE_IDLE);
            setLED(EYE_ON);
          }
          break;
        }    
    }
}

void Eye::setIdleState(EyeIdleState _state)
{
  int randVal = rand->getRandom(_state, eyeIdleMinTimes[_state],eyeIdleMaxTimes[_state]);
  idleState = _state;
  actionBaseTime = millis();
  actionNextTime = millis()+randVal;
  if ( debug ) {
    Serial.println(F("----------"));
    Serial.print(F("Switching "));
    Serial.print(label);
    Serial.print(F(" to mode "));
    Serial.print(idleState);
    Serial.print(F(" value "));
    Serial.println(randVal);
  }
}

void Eye::setBlinkingState(EyeBlinkingState _state)
{
  blinkingState = _state;
  actionBaseTime = millis();
  actionNextTime = millis()+EYE_BLINKING_MS;
}
void Eye::setAlternatingState(EyeAlternatingState _state)
{
  alternatingState = _state;
  actionBaseTime = millis();
  actionNextTime = millis()+EYE_ALTERNATING_MS;
}
/**
 * setLED - set LED, based on 0..255 scale
*/

void Eye::setLED(unsigned int brightness)
{
//  for pin sink to ground
  value = 255-brightness;
  analogWrite(pin, value);  
}