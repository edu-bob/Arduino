/**
 * LED Eyes for Halloween Characters
 * rlb408, edu-bob, Bob Brown, October 2022
 *
 * Meant to be wired into LEDs in the eyes of my Halloween characters.
 *
 * For a Arduino Pro Micro ATmega32U4 5V/16MHz Module Board
 * https://www.amazon.com/dp/B019SXN84E for the device
 * https://learn.sparkfun.com/tutorials/qwiic-pro-micro-usb-c-atmega32u4-hookup-guide/setting-up-arduino for the board defs
 * 
 * Normally, in idle state, the eyes pulse at somewhat random intervals.  Occasionally they blink once or twice.
 *
 * Structure:
 * Eye objects = independent control of each eye.  In hindsight, having independent eyes was a hassle
 * RandCache - a chaching layer for random numbers, so that each eye can get the same random timing value.
 */

#include "Eye.h"
#include "RandCache.h"
#include "pins.h"

#define MIN_TIME_TO_BLINK 20000ul
#define MAX_TIME_TO_BLINK 30000ul

Eye rightEye;
Eye leftEye;
RandCache randCache;

unsigned long nextBlink;

#define DEBUG 0

void setup()
{
  Serial.begin(9600);
  Serial.println(F("Starting up..."));

  randCache.setup();
  randCache.setDebug(DEBUG);

  // initialize each eye
  rightEye.setup(RIGHT_EYE_PIN, "right", &randCache, 0);
  rightEye.setDebug(DEBUG);
  
  leftEye.setup(LEFT_EYE_PIN, "left", &randCache, 1);
  leftEye.setDebug(DEBUG);

  // set up for the first blink...this doesn't accommodate the start-up, so the first blink might come early
  nextBlink = millis() + (unsigned long)random(MIN_TIME_TO_BLINK, MAX_TIME_TO_BLINK);

  // on startup, go into a brief alternating mode
  leftEye.setMode(EYE_ALTERNATING);
  rightEye.setMode(EYE_ALTERNATING);
}

void loop()
{
  randCache.loop();
  rightEye.loop();
  leftEye.loop();

  // Blinking can only be initiated in idle state and full on
  if ( rightEye.canBlink() && millis() > nextBlink ) {
    // Serial.println(F("Start blink"));
    rightEye.setMode(EYE_BLINKING);
    leftEye.setMode(EYE_BLINKING);
    nextBlink = millis() + (unsigned long)random(MIN_TIME_TO_BLINK, MAX_TIME_TO_BLINK);
  }
}

