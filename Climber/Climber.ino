#include "pins.h"

#include "Brake.h"
#include "LimitSwitch.h"
#include "Mover.h"
#include "HandFootSwitch.h"
#include "MoveButton.h"
#include "Bell.h"
#include "ModeSwitch.h"
#include "ModeSwitchAnalog.h"

// SIMPLE_BUTTON means "press to expand, release to contract"
// otherwise, "press and release" to expand, "press and release" to contract
#define SIMPLE_BUTTON 0

// delay this long after switching brakes before moving the climbing cylinder
#define BRAKE_DELAY 10

// The bell won't sound more often than this
#define BELL_SILENCE_AFTER_RING 30000L

Brake brake;
LimitSwitch upperLimit;
LimitSwitch lowerLimit;
Mover mover;
HandFootSwitch handFootSwitch;
MoveButton moveButton;
ModeSwitch disableSwitch;
ModeSwitchAnalog runHomeSwitch;
ModeSwitchAnalog oldNewSwitch;
Bell bell;

void displayMove(void);

// wasPressed is used to track the push-release toggling of the drive cylinder
bool wasPressed;
bool bellArmed;
unsigned long pauseUntil;
unsigned long bellSilenceUntil;

// overrideControllerState:
//  0... normal operation
//  1... hit limit, reversed brakes, waiting for button-not-pressed
//  2... after button up, waiting for button down

int overrideControllerState;

int output = 0;
unsigned long loops;

void setup()
{
  Serial.begin(9600);
  Serial.println("Starting up...");

  // Initially, the MOVE button was not previously pressed.  This is used
  // for the non-SIMPLE_BUTTon mode of the MOVE button
  wasPressed = false;

  bellArmed = true;
  overrideControllerState = 0;
  pauseUntil = millis();

  // Initialize each of the I/Os, hand the objects their pin numbers
  
  oldNewSwitch.setup("oldNew",OLD_NEW_PIN);
  brake.setup(BRAKE_FOOT_PIN,BRAKE_HAND_PIN,oldNewSwitch.isOn());
  lowerLimit.setup("lower", LIMITSWITCH_LOWER_PIN);
  upperLimit.setup("upper", LIMITSWITCH_UPPER_PIN);
  mover.setup(MOVER_PIN);
  handFootSwitch.setup(FOOT_SW_PIN,HAND_SW_PIN);
  moveButton.setup(MOVE_SW_PIN);
  disableSwitch.setup("disable", DISABLE_SW_PIN);
  bell.setup(BELL_PIN, BELL_POT_PIN);
  runHomeSwitch.setup("internal",INTERNAL_SW_PIN);
  loops = 0;
}

void loop()
{
  brake.loop();
  lowerLimit.loop();
  upperLimit.loop();
  mover.loop();
  handFootSwitch.loop();
  runHomeSwitch.loop();
  oldNewSwitch.loop();
  moveButton.loop();
  disableSwitch.loop();
  bell.loop();

  // Assembly mode.  Release both brakes if
  // disableSwitch is ON
  // oldNewSwitch is in NEW
  // RUN/HOME is in HOME (runHomeSwitch)
  // both limit switches are ON
  // NOTE as long as the OLD/NEW switch exists for this purpose (maybe only in 2019) then you can
  //      achieve the same thing by setting Disable and setting oldNew to OLD since in OLD mode the brack pistons are 
  //      activated (turning on the brakes) but if they're NEW pistons, this will release them.

  if ( disableSwitch.isOn() && oldNewSwitch.isOn() && runHomeSwitch.isOn()
  && lowerLimit.isOn() && upperLimit.isOn() ) {
    brake.setHand(false);
    brake.setFoot(false);
    return;
  }
  //
//Serial.println(runHomeSwitch.isOn());delay(500);
  loops++;

  // Controller test
  if ( 0 ) {
    if ( handFootSwitch.isHand() )  Serial.print("H");
    if ( handFootSwitch.isFoot() ) Serial.print("F");
    if ( handFootSwitch.getSetting() == NO_SW ) Serial.print("N");
    if ( moveButton.isPressed() ) Serial.print(">");
    if ( loops%20 == 0 ) Serial.println("");
    delay(200);
    return;
  }

  // Wiring test - hand/foot switch controls the brakes
  if ( 0 ) {
    if ( handFootSwitch.isHand() ) {
      brake.setHand(true);
      brake.setFoot(false);
    }
    if ( handFootSwitch.isFoot() ) {
      brake.setFoot(true);
      brake.setHand(false);
    }
    return;
  }

  // vehicle logic  
  climber();
}

void climber()
{
  // Tell the Brake what type of pistons we have
  brake.setNewType(oldNewSwitch.isOn());
  if ( oldNewSwitch.changedToOn() ) {
//    Serial.println("Switched to NEW");
  }

  // if the mode switch is in the disabled position, , contract the piston, set both brakes on, and make sure the bell is off.
  
  if ( disableSwitch.isOn() ) {
//    Serial.println("Disabled"); delay(1000);
    mover.setState(MOVER_CONTRACTED);
    brake.setHand(true);
    brake.setFoot(true);
    bell.off();
    return;
  }

  // The internal switch is used to automatically walk the climber back to the bottom
  if ( runHomeSwitch.isOn() ) {

    // if we just hit bottom, quickly flip the brakes, don't wait for the cylinder expansion time
    if ( lowerLimit.changedToOn() ) {
      brake.setFoot(true);
      brake.setHand(false);
    }
    if ( millis() < pauseUntil ) return;
    if ( runHomeSwitch.changedToOn() ) Serial.println("Return to base");

    // If not at the bottom, cycle between contracted and expanded, toggleing brakes.  Set a delay
    // to allow the main cylinder to complete its movement
    
    if ( !lowerLimit.isOn() ) {
      if ( mover.isContracted() ) {
        brake.setHand(true);
        delay(BRAKE_DELAY);
        brake.setFoot(false);
        mover.setState(MOVER_EXPANDED);
      } else {
        brake.setFoot(true);
        delay(BRAKE_DELAY);
        brake.setHand(false);
        mover.setState(MOVER_CONTRACTED);
      }
      pauseUntil = millis() + MOVER_EXPAND_TIME;
    }
    return;
  }
  

  if ( millis() < pauseUntil ) return;
  
  // overrideControllerStats will be non-zero if the vehicle state is inconsistent with the controller, due to
  // hitting one of the limit switche
  switch(overrideControllerState) {
    // not overriding, just continue
    case 0:
      break;
    case 1:
      Serial.println("After hitting bottom and expanding, setting hand brake");
      brake.setHand(true);
      overrideControllerState = 0;
      break;
    case 2:
      brake.setFoot(true);
      overrideControllerState = 0;
      break;
   }


  // check the limit switches

  // if the lower switch is on, the the foot brake must stay locked regardless of the 
  // hand/foot switch setting, until the driver piston is expanded
  if ( lowerLimit.changedToOn() ) {
    Serial.println("Hit bottom");
    brake.setFoot(true);
    brake.setHand(false);
    delay(BRAKE_DELAY);
    mover.setState(MOVER_EXPANDED);
    pauseUntil = millis() + MOVER_EXPAND_TIME;
    overrideControllerState = 1;

  // likewise, if the upper limit switch is on, the upper brake must stay set
  } else if ( upperLimit.changedToOn() ) {
    brake.setHand(true);
    brake.setFoot(false);
    delay(BRAKE_DELAY);
    mover.setState(MOVER_EXPANDED);
    pauseUntil = millis() + MOVER_EXPAND_TIME;
    overrideControllerState = 2;
  } else {

    // Set the brakes according to the switch setting
    
    int handfoot = handFootSwitch.getSetting();
    switch(handfoot) {
      // what should move?
      case FOOT_SW:
        brake.setHand(true);
        brake.setFoot(false);
        break;
      case HAND_SW:
        brake.setFoot(true);
        brake.setHand(false);
        break;
    }
  }

  // SIMPLE_BUTTON means "press to expand, release to contract"
  // otherwise, "press and release" to expand, "press and release" to contract
  
  if ( SIMPLE_BUTTON ) {
    if ( moveButton.isPressed() ) {
      mover.setState(MOVER_EXPANDED);
    } else {
      mover.setState(MOVER_CONTRACTED);
    }
  } else {

    // Click-release, click-release mode:

    if ( !wasPressed ) {
      if ( moveButton.isPressed() ) { // change state
        wasPressed = true;

        // Check for being pegged at top of bottom and contracted
        if ( mover.isContracted() ) {
          if ( lowerLimit.isOn() && handFootSwitch.isFoot() ) {
            Serial.println("At bottom, foot switch set, expanding.  Ignore.");
            return;
          }
          if ( upperLimit.isOn() && handFootSwitch.isHand() ) {
             Serial.println("At top, hand switch set, expanding.  Ignore.");
           return;
          }
        }
        mover.toggleState();
        
        // display what movement happened
        displayMove();
      }

    } else {

      // Check for button released, basically do nothing
    
      if ( !moveButton.isPressed() ) {
//        Serial.println("pressed->unpressed");
        wasPressed = false;
      }

    }
  }

  // if the upper switch just switched to on, and this is the first time since the lower switch, ring the bell

  if ( upperLimit.changedToOn() && bellArmed ) {
    Serial.println("Ring bell");
    bell.ring();
    bellArmed = false;
    bellSilenceUntil = millis() + BELL_SILENCE_AFTER_RING;
  }
  if ( millis() > bellSilenceUntil || lowerLimit.isOn() ) {
//    Serial.println("bell armed");
    bellArmed = true;
  }
}

/**
 * displayMove - show what happened
 * 
 * Call after the state of the drive piston has changed
 */

void displayMove(void)
{
  if ( brake.getFoot() ) {
    Serial.print("Hands move ");
    if ( mover.getState() == MOVER_EXPANDED ) {
      Serial.println("up");
    } else {
      Serial.println("down");
    }
  } else {
    Serial.print("Feet move ");
    if ( mover.getState() == MOVER_EXPANDED ) {
      Serial.println("down");
    } else {
      Serial.println("up");
    }
  }
}

