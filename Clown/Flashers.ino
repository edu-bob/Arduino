//
// Control logic for the clown flashing lights
//

#include "pins.h"

void Flashers::setup(void)
{
    pinMode(FLASHER_1_PIN, OUTPUT);
    pinMode(FLASHER_2_PIN, OUTPUT);
    stop();
}

/**
 * Polling subroutine.  If flashing is running and time to switch lights, switch.
 */
 
void Flashers::loop(void)
{
  if ( running ) {
    if ( millis() >= nextFlashTime ) {
      if ( flashMode ) {
        flashMode = 0;
        digitalWrite(FLASHER_1_PIN, 0);
        digitalWrite(FLASHER_2_PIN, 1);
      } else {
        flashMode = 1;
        digitalWrite(FLASHER_1_PIN, 1);
        digitalWrite(FLASHER_2_PIN, 0);
      }
      nextFlashTime = millis() + FLASHER_FLASH_TIME;
    }
  }
}

/**
 * Start flashing.
 */ 
 
void Flashers::start(void)
{
  running = true;
  flashMode = 0;
  nextFlashTime = millis();
}

/**
 * Stop the flashing process
 *
 * Also turns off both lights.
 */
 
void Flashers::stop(void)
{
    digitalWrite(FLASHER_1_PIN, 0);
    digitalWrite(FLASHER_2_PIN, 0);
    running = false;
}

//--------------------------------------------------------
// Test Functions
//
void Flashers::testSetup(void)
{
    pinMode(FLASHER_1_PIN, OUTPUT);
    pinMode(FLASHER_2_PIN, OUTPUT);
    testStartTime = millis();
    testNextStartTime = millis() + FLASHER_TEST_DELAY;
    testRunning = false;
    digitalWrite(FLASHER_1_PIN, 0);
    digitalWrite(FLASHER_2_PIN, 0);
}
void Flashers::testLoop(void)
{
  if ( testRunning ) {
    if ( millis() >= testNextEndTime ) {
      testRunning = false;
      digitalWrite(FLASHER_1_PIN, 0);
      digitalWrite(FLASHER_2_PIN, 0);
      testNextStartTime = millis() + FLASHER_TEST_DELAY;
      Serial.print(millis()-testStartTime);
      Serial.println(F(" End Flasher test"));
    } else {
      if ( millis() >= testNextFlashTime ) {
        if ( testFlashMode ) {
          testFlashMode = 0;
          digitalWrite(FLASHER_1_PIN, 0);
          digitalWrite(FLASHER_2_PIN, 1);
        } else {
          testFlashMode = 1;
          digitalWrite(FLASHER_1_PIN, 1);
          digitalWrite(FLASHER_2_PIN, 0);
        }
        testNextFlashTime = millis() + FLASHER_FLASH_TIME;
      }
    }
  } else {
    if ( millis() >= testNextStartTime ) { // start the next test
      testRunning = true;
      testFlashMode = 0;
      testNextFlashTime = millis();
      testNextEndTime = millis() + FLASHER_TEST_RUNNING_TIME;
      Serial.print(millis()-testStartTime);
      Serial.println(F(" Start Flasher test"));
    }
  }
      
}

