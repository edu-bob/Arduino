/*
 * Control program for the motorized desk shelf
 *
 */

#include "pins.h"
#include "PushButton.h"
#include "LimitSwitch.h"
#include "Motor.h"
#include "Heartbeat.h"


PushButton inButton;
PushButton outButton;
LimitSwitch limit;
Motor motor;
Heartbeat heart;

void setup()
{
  Serial.begin(9600);
  
  // heartbeat LED, to let we know that the program is running
  heart.setup();

  motor.setup();
  inButton.setup(PUSHBUTTON_OUT_PIN);
  outButton.setup(PUSHBUTTON_IN_PIN);
  limit.setup();
}

void loop()
{
  heart.loop();

  inButton.loop();
  outButton.loop();
  limit.loop();
  motor.loop();
  
  shelfLogic();
}

void shelfLogic()
{
  unsigned int val = (((inButton.getStableValue() << 1) | outButton.getStableValue()) << 4) | limit.getStableValue();
  if ( limit.isChanged() || inButton.isChanged() || outButton.isChanged() ) {
    //Serial.print("CHANGED: ");
//    Serial.println(val, BIN);
  }
  
  // If both buttons are down or both are up, stop the motor
  
  if ( inButton.getStableValue() == outButton.getStableValue() ) {
    motor.stop();
  } else if ( inButton.getStableValue() ) {
    if ( limit.isIn() ) {
      motor.stop();
    } else {
      if ( limit.isNearIn() ) {
        motor.reverse(M_SLOW);
      } else {
        motor.reverse(M_FAST);
      }
    }
  } else if ( outButton.getStableValue() ) {
    if ( limit.isOut() ) {
      motor.stop();
    } else {
      if ( limit.isNearOut() ) {
        motor.forward(M_SLOW);
      } else {
        motor.forward(M_FAST);
      }
    }
  }
}


