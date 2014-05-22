/*
 * Control program for the motorized desk shelf
 *
 * this controls a shelf that attaches under my desk and has the following components:
 *  a shelf that slids about 18" on full-extension slides mounted to wood attached under my desk.
 *  a DC motor that spins a threaded rod that can drive the shelf in and out.
 *  a (fragile) flexible coupling between the motor and the threaded rod.
 *  micro switches at the full-in and full-out positions
 *  micro switches that trip about 2 inches from the full-in and full-out positions.
 *  two push buttons - one to drive the shelf out and one to drive it in
 *  an Arduino control program (this software right here)
 *
 * code requirements:
 *   drive the shelf out when the out-button is pressed (and held)
 *   drive the shelf in when the in-button is pressed and held
 *   don't go from stop to full speed suddenly (the coupling is fragile) and vice versa
 *   don't crash into the limit switches, slow down at the 2" switch
 *   detect over-current on the motor and shut down
 *
 */

#include <WProgram.h>

#include "pins.h"
#include "Music.h"
#include "Alarm.h"
#include "PushButton.h"
#include "LimitSwitch.h"
#include "Motor.h"
#include "Heartbeat.h"


Alarm alarm;
PushButton inButton;
PushButton outButton;
LimitSwitch limit;
Motor motor;
Heartbeat heart;
Music music;

void setup()
{
  Serial.begin(9600);
  Serial.println(F("Starting..."));
  Serial.print(F("Free RAM: "));Serial.println(freeRam());

  alarm.setup();
  music.setup(MUSIC_SPEAKER);
  alarm.setMusicObject(music);

  // heartbeat LED, to let we know that the program is running
  heart.setup(HEARTBEAT_PIN);

  motor.setup();
  inButton.setup(PUSHBUTTON_OUT_PIN);
  outButton.setup(PUSHBUTTON_IN_PIN);
  limit.setup();
}

void loop()
{
  // Check if the motor is over current and shutdown if so
  
  while ( motor.isOverCurrent() ) {
    motor.stop();
    alarm.setStatus(ALARM_OVERCURRENT);
    delay(5000);
  }
  
  heart.loop();

  // read the buttons
  inButton.loop();
  outButton.loop();
  
  // read the limit microswitches
  limit.loop();
  
  // control the motor based on what is requested in shelfLogic()
  motor.loop();
  
  shelfLogic();
}

// Handle the push buttons and how they change the motor control

void shelfLogic()
{
  unsigned int val = (((inButton.getStableValue() << 1) | outButton.getStableValue()) << 4) | limit.getStableValue();
  
  // If both buttons are down or both are up, stop the motor
  
  if ( inButton.getStableValue() == outButton.getStableValue() ) {
    motor.setSpeed(0);
  } else 
  
  // if the shelf-in button is pressed ...
  if ( inButton.getStableValue() ) {
    
    // stop the motor if the final limit switch it hit
    if ( limit.isIn() ) {
      motor.stop();
    } else {
      
      // make sure the direction is correct and move at full speed in the green zone and slower in the yellow zone
      motor.setDirection(M_IN);
      if ( limit.isNearIn() ) {
        motor.setSpeed(M_SLOW);
      } else {
        motor.setSpeed(M_FAST);
      }
    }
  } else 
  
  // If the shelf-out button is pressed...
  if ( outButton.getStableValue() ) {
    if ( limit.isOut() ) {
      motor.stop();
    } else {
      motor.setDirection(M_OUT);
      if ( limit.isNearOut() ) {
        motor.setSpeed(M_SLOW);
      } else {
        motor.setSpeed(M_FAST);
      }
    }
  }
}


