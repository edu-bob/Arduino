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

// PIR_CYCLE_TIME - the motion sensor will only return a result after this amount of time (mS) since the last detection
// This logic shold really be in the calling code.

#define PIR_CYCLE_TIME 10000ul
#define PIR_THRESHOLD 200

// PIR_SETTLE_TIME is the initial time delay after startup.

#define PIR_SETTLE_TIME 10000ul

void MotionDetector::setup()
{
  lastRead = millis();
  sleepUntil = millis() + PIR_SETTLE_TIME;
  ignoring  = true;
  cycleTime = PIR_CYCLE_TIME;
  newMotion = false;
  music = (Music *)0;
}

/**
 * When the agreed-upon cycle time has been reached, start reading the PIR sensor again
 *
 * Saves the "motion detected" status in newMotion
 */
 
void MotionDetector::loop()
{
  if ( millis() > sleepUntil ) {
    if ( ignoring  ) {
      Serial.println(F("Motion detection on"));
      // If we have a music object, play the file indicating that the motion detector is active again.
      if ( music ) {
          music->playFile("WATCHING.WAV");
      }
      ignoring  = false;
    }
    newMotion = analogRead(PIR_PIN) <= PIR_THRESHOLD;
  } else {
    ignoring  = true;
  }
}

/*
 * setMusicObject - give this class a copy of the Music singleton.
 *
 */
 
void MotionDetector::setMusicObject(Music &_music)
{
  music = &_music;
}

/*
 * isDetected - returns whether motion was detected on this cycle
 *
 * Basically does what loop() does but is meant to be called from other classes whereas loop() is
 * called from the main loop() and returns no value.
 */
 
bool MotionDetector::isDetected()
{
  return newMotion;
}

/*
 * startDelay - initiates the beginning of a "do not detect" period"
 *
 * This should be called in the machine logic when an action is taken based on motion being
 * detected and results in no motion detion for period of time.
 */
 
void MotionDetector::startDelay()
{
  newMotion = false;
  sleepUntil = millis()+cycleTime;
  ignoring = true;
}

void MotionDetector::setCycleTime(unsigned long _cycleTime)
{
  cycleTime = _cycleTime;
}

//--------------------------------------------------------
// Test Functions
//
void MotionDetector::testSetup(void)
{
    testLastValue = analogRead(PIR_PIN);
    testStartTime = millis();
}
void MotionDetector::testLoop(void)
{
  unsigned int currentValue = analogRead(PIR_PIN);
  if ( abs((int)currentValue-(int)testLastValue) > 20 ) {
    Serial.print(millis()-testStartTime);
    Serial.print(F(" Motion sensor changed from "));
    Serial.print(testLastValue);
    Serial.print(F(" to "));
    Serial.println(currentValue);
    testLastValue = currentValue;
  }
}
