#include "pins.h"

#include <WProgram.h>

#include "Tilter.h"

void Tilter::setup(void)
{
  pinMode(TILTER_PIN, OUTPUT);
  state = TILTED_DOWN;
}

void Tilter::loop(void)
{
}

void Tilter::tiltUp()
{
  digitalWrite(TILTER_PIN, TILT_VALUE_OPEN);
  state = TILTED_UP;
}


void Tilter::tiltDown()
{
  digitalWrite(TILTER_PIN, TILT_VALUE_CLOSED);
  state = TILTED_DOWN;
}
//--------------------------------------------------------
// Test Functions
//
void Tilter::testSetup(void)
{
    pinMode(TILTER_PIN, OUTPUT);
    digitalWrite(TILTER_PIN, TILT_VALUE_CLOSED);
    testStartTime = millis();
    testNextTime = millis() + TILT_TEST_DELAY_DOWN;
    testState = TILTED_DOWN;
}
void Tilter::testLoop(void)
{
  if ( millis() > testNextTime ) {
    if ( testState == TILTED_DOWN ) {
      digitalWrite(TILTER_PIN, TILT_VALUE_OPEN);
      testState = TILTED_UP;
      testNextTime = millis() + TILT_TEST_DELAY_UP;
      Serial.print(millis()-testStartTime);
      Serial.println(F(" Tilter changed from DOWN to UP"));
    } else {
      digitalWrite(TILTER_PIN, TILT_VALUE_CLOSED);
      testState = TILTED_DOWN;
      testNextTime = millis() + TILT_TEST_DELAY_DOWN;
      Serial.print(millis()-testStartTime);
      Serial.println(F(" Tilter changed from UP to DOWN"));
    }
  }

}

