#include "pins.h"
#include "MotionDetector.h"
#include "TimePot.h"
#include "Blinker.h"

// Instances of each of the functional objects in the clown system

MotionDetector motion;
TimePot timepot;
Blinker blinker;

bool testMode = false;   // use when no pot or motion sensor attached.
bool debug = true || testMode;

int state = 0;
unsigned long turnOffAt;

void setup() {
  Serial.begin(9600);
  Serial.println(F("Starting..."));
  Serial.print(F("Free RAM: "));Serial.println(freeRam());

  motion.setup(PIR_PIN, debug);
  timepot.setup(TIMEPOT_PIN, debug);
  blinker.setup(LED_PINBASE, debug);

  motion.setTestMode(testMode);
  timepot.setTestMode(testMode);
}

void loop() {
    motion.loop();
    timepot.loop();
    blinker.loop();
    
    blinkerLogic();
}

void blinkerLogic()
{
  switch (state) {
    // Idle mode, not blinking, looking for motion.
    case 0:
      if ( motion.isDetected() ) {
        if ( debug ) {
          Serial.println(F("Motion detected, switching to blinking"));
        }
        blinker.start();
        motion.startIgnore(5000);
        turnOffAt = millis() + timepot.getValue();
        digitalWrite(ACTIVE_LED,1);
        state = 1;
      }
      break;
    case 1:
      if ( millis() > turnOffAt ) {
        if ( debug ) {
          Serial.println(F("Blinking done."));
        }
        blinker.stop();
        digitalWrite(ACTIVE_LED,0);
        if ( debug ) {
          Serial.println(F("Waiting for motion..."));
        }
        state = 0;
      }
      break;
  }
}
