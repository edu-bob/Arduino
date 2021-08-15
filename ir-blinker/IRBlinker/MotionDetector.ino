/*
 * MotionDetector - manage the motion detector
 *
 * The motion detector is assumed to be hooked up to analog pin PIR_PIN.  The spec sheet recommends
 * using a digital pin but I have found that the digital pins are at a premium and the analog pin
 * works fine. 
 *
 * Usage:
 *  MotionDetector::setup() in your main setup() function.
 *  MotionDetector::loop() in your main loop() function.
 *
 * To see if motion was detected on the last cycle, call isDetected()
 */
 
#include "pins.h"

#define PIR_THRESHOLD 200

// PIR_SETTLE_TIME is the initial time delay after startup.

#define PIR_SETTLE_TIME 10000ul

#define MOTION_TEST_INTERVAL 14000ul

void MotionDetector::setup(int _pin, bool _debug=false)
{
  lastRead = millis();
  ignoreUntil = millis() + PIR_SETTLE_TIME;
  ignoring  = true;
  newMotion = false;
  pin = _pin;
  debug = _debug;
}

/**
 * When the agreed-upon cycle time has been reached, start reading the PIR sensor again
 *
 * Saves the "motion detected" status in newMotion
 */
 
void MotionDetector::loop()
{
  if ( millis() < ignoreUntil ) {
    ignoring  = true;
  } else {
    if ( ignoring  ) {
//      if ( debug ) {
//        Serial.println(F("Motion detection on"));
//      }
      ignoring  = false;
    }
    newMotion = analogRead(pin) <= PIR_THRESHOLD;
  }
}


/*
 * isDetected - returns whether motion was detected on this cycle
 *
 * Basically does what loop() does but is meant to be called from other classes whereas loop() is
 * called from the main loop() and returns no value.
 */
 
bool MotionDetector::isDetected()
{
  bool motion = newMotion;

  // if in test mode, trigger motion detected every MOTION_TEST_INTERVAL seconds
  if ( testMode ) {
    if ( millis() >= testModeNextChange ) {
      testModeNextChange = millis() + MOTION_TEST_INTERVAL;
      return true;
    }
    return false;
  }
  
  newMotion = false;
  return motion;
}

/*
 * startDelay - initiates the beginning of a "do not detect" period"
 *
 * This should be called in the machine logic when an action is taken based on motion being
 * detected and results in no motion detion for period of time.
 */
 
void MotionDetector::startIgnore(unsigned long ignoreTime)
{
  newMotion = false;
  ignoreUntil = millis()+ignoreTime;
  ignoring = true;
}

void MotionDetector::setDebug(bool sw)
{
  debug = sw;
}

void MotionDetector::setTestMode(bool _testMode)
{
  testMode = _testMode;
  testModeNextChange = millis() + MOTION_TEST_INTERVAL;
  if ( testMode ) {
    Serial.print(F("MoionDetector testmode delay = "));
    Serial.println(MOTION_TEST_INTERVAL);
  }
}
