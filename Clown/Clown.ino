#include <FatReader.h>
#include <SdReader.h>
#include <avr/pgmspace.h>
#include <WaveUtil.h>
#include <WaveHC.h>

#include <stdlib.h>

#include "Music.h"
#include "MotionDetector.h"
#include "Tilter.h"
#include "Switches.h"
#include "PushButton.h"
#include "AmbientMusic.h"
#include "Flashers.h"
#include "TestMode.h"

// testMode - set to true to run only the test mode functions

const bool testMode = false;
TestMode tester;


//
// TILT_CYCLE_TIME - how long (in mS) the clown is tilted forward
//
#define TILT_CYCLE_TIME 5000

// Instances of each of the functional objects in the clown system

Music music;
MotionDetector motion;
Tilter tilter;
Switches switches;
PushButton button;
AmbientMusic ambient;
Flashers flashers;

// state 0 - waiting to tilt
// state 1 - tilted, waiting to return to upright

int state = 0;
unsigned long endTime;
bool musicIsOn;

bool debug = false;

// Initially, the tilt mechanism is not armed.

bool tiltArmed = false;

//
// When starting up, this many changes in the Auto switch need to be seen before the
// motion sensor will be watched.
//
#define STARTUP_SWITCH_CHANGES_MIN 3


void setup() {
  Serial.begin(9600);
  Serial.println(F("Starting..."));
  Serial.print(F("Free RAM: "));Serial.println(freeRam());
  if ( testMode ) {
    tester.setup();
  } else {
    switches.setup();
    button.setup();
    flashers.setup();
    music.setup();
    ambient.setup();
    motion.setup();
    tilter.setup();
    music.playFile("START.WAV");
    music.wait();

    // Pass the music object to the classes that can make use of it.
    
    switches.setMusicObject(music);
    motion.setMusicObject(music);
  
    // Set up the ambient music
  
    musicIsOn = switches.isMusicOn();
    ambient.setMusicObject(music);
    if ( !musicIsOn ) {
      ambient.stop();
    }
    Serial.print(F("Free RAM: "));Serial.println(freeRam());
  }
}


void loop()
{
  if ( testMode ) {
    tester.loop();
  } else {
    switches.loop();
    button.loop();
    music.loop();
    ambient.loop();
    motion.loop();
    tilter.loop();
    flashers.loop();

    clownLogic();
  }
}

/*
 * clownLogic - the main clown control logic
 */

void clownLogic()
{
  // Check for music switches changing
  
  if ( switches.isMusicOn() != musicIsOn ) {
    musicIsOn = switches.isMusicOn();
    if ( switches.isMusicOn() ) {
      ambient.start();
    } else {
      ambient.stop();
    }
  }
  
  // Check for arming the tilt mechanism.  After start-up, the AUTO switch must be
  // toggled STARTUP_SWITCH_CHANGES_MIN times before the tilt mechanism can be used.
  // This is a safety feature.
  
  if ( !tiltArmed && switches.getAutoSwitchChanges() >= STARTUP_SWITCH_CHANGES_MIN ) {
    tiltArmed = true;
    music.playFile("ARMED.WAV");
    music.wait();
  }
  
  // Give warning if trying to push the button and not yet armed
  
  if ( !tiltArmed && button.isPressed() ) {
    music.playFile("DISABLED.WAV");
  }
  //
  // State 0: platform is down, waiting for the right conditions to start the tilt cycle
  // State 1: Tilt cycle has started, looking for conditions to stop it.
  //
  switch ( state ) {
    
    case 0:
      if ( tiltArmed && ((switches.isAutomaticOn() && motion.isDetected()) || button.isPressed()) ) {
        Serial.println(F("Start cycle"));
        ambient.stop();
        tilter.tiltUp();
        flashers.start();
        music.playFile("LAUGH3.WAV");
        endTime = millis() + TILT_CYCLE_TIME;
        state = 1;
      }
      break;
      
    //
    // When tilted up, come back down after the time delay but only if 
    // the manuel button is up.
    //
    case 1:
    
      // Keep pushing out the motion detection start time as long as the manual button is pressed
      
      if ( button.isPressed() ) {
        motion.startDelay();
      } else {
        if ( millis() >= endTime ) {
          Serial.println(F("End cycle"));
          tilter.tiltDown();
          music.playFile("TILT_D.WAV");
          flashers.stop();
          if ( switches.isMusicOn() ) ambient.start();
          motion.startDelay();
          state = 0;
        }
      }
      break;
  }
}



