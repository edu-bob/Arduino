#include "pins.h"

#include <LiquidCrystal.h>

// HardwareSerial allows me to pass "Serial1" by reference
#include <HardwareSerial.h>

#include "Heartbeat.h"
#include "Button.h"
#include "Jumper.h"
#include "Display.h"
#include "Options.h"
#include "ScoreBoard.h"
#include "DisableSwitch.h"
#include "Sensor.h"
#include "Wire.h"

#define OPT_TILT 0
#define OPT_COUNT 1

#include "TestMode.h"

Heartbeat heart;
Button button;
Jumper jumper;
Display display;
Options options;
ScoreBoard scoreBoard;
DisableSwitch disableSwitch;
Sensor sensor;

// Variabes for managing the display of tilt information

int tiltOffset;
unsigned long nextTiltUpdate;
#define TILTUPDATE 50

// Variables for managing the display of button count information
unsigned long lastPress;
int pressOffset;
#define PRESS_RESET_TIME 5000u

char DisplayBuf[21]; // characters in a line +1 for the ASCII NUL

unsigned long buttonDelay;

const bool testMode = false;
TestMode tester;

void setup()
{
  Serial.begin(9600);
  Serial.println(F("Starting..."));
  Serial.print(F("Free RAM: "));
  Serial.println(freeRam());

  // First off, set up the LCD in order to display start-up information

  display.setup();
  sprintf(DisplayBuf, "Free RAM: %d", freeRam());
  display.print("Maker Faire 2013", "Posable Jumper M3", DisplayBuf);
  display.setCursor(0,3);
  for ( int i = 5 ; i>=1 ; i-- ) {
    display.printf("%d..", i);
    delay(1000);
  }
  display.print("GO");
  delay(250);

  if ( testMode ) {
    tester.setup();
  } 
  else {
    // heartbeat LED, to let me know that the program is running
    heart.setup();

    button.setup();
    button.begin(BUTTON_PIN, DELAY_POT_PIN);

    jumper.setup();
    jumper.begin(JUMPER_LEGS_PIN);

    options.setup();
    options.begin(DIP_PIN_0);
    scoreBoard.setup();
    scoreBoard.begin(Serial1);

    disableSwitch.setup();
    disableSwitch.begin(DISABLE_SWITCH_PIN);

    if ( options.getValue(OPT_TILT) ) {
      sensor.setup();
    }


    jumper.on();
    scoreBoard.scroll(" POSABLES    ");
    scoreBoard.clear();

  }
  nextTiltUpdate = millis();
  tiltOffset = 0;
  buttonDelay = button.getDelay();
  pressOffset = 0;
  lastPress = millis();

  refreshDisplay();
}

// Iteration cycle, each device has work to do in setting up the game logic

void loop()
{
  // As of now, test mode isn't implemented

  if ( testMode ) {
    tester.loop();
  } 
  else {
    heart.loop();
    button.loop();
    jumper.loop();
    options.loop();
    scoreBoard.loop();
    disableSwitch.loop();
    if ( options.getValue(OPT_TILT) ) {
      sensor.loop();
    }

    jumperLogic();
  }
}

/*
 * jumperLogic - the control logic for the jumper
 */

void jumperLogic()
{
  // This is a special case - the disabled switch was turned back on in this cycle
  // and the button was pressed during the cycle.  Make sure we don't kick the jumper.
  // Also, turn on or off press counting.  This might not be necessary now since I added 
  // disabling the button during disable mode.

  if ( disableSwitch.isChanged() ) {
    if ( disableSwitch.isEnabled() ) {

      // switch went from disable to enabled. Start forwarding button presses
      // and clear any button changes that happened while disabled.
      button.enable();
      button.clearPressed();

      // reset the tilt zero value at this point
      int16_t gyro, acc;
      sensor.getTilt(gyro, acc);
      tiltOffset = acc;

      // reset the button presses offset
      pressOffset = button.getFilteredPresses();

    } 
    else {
      // switch went from enabled to disabled.  Stop forwarding button presses.
      button.disable();
    }
  }

  // If the disable switch is on, skip checking the pushbutton.
  // This might not be needed in light of the button.disable() feature.
  if ( disableSwitch.isEnabled() ) {

    if ( button.wasPressed() ) {
      lastPress = millis();
      jumper.extend();

      if ( options.getValue(OPT_COUNT) ) {
        scoreBoard.show(button.getFilteredPresses() - pressOffset);
      }

    } 
    else {

      // retract the piston? 

      if ( jumper.isExtended() && !button.isDown() ) {
        jumper.retract();
      }

      // Time to reset the press counter to zero?  If so, do it and reset the scoreboard
      // if the scoreboard is displaying the count.

      if ( millis() > lastPress + PRESS_RESET_TIME ) {
        pressOffset = button.getFilteredPresses();
        if ( options.getValue(OPT_COUNT) ) {
          scoreBoard.show(button.getFilteredPresses() - pressOffset);
        }
      }

      // update the scoreboard if displaying the tilt information
      if ( options.getValue(OPT_TILT) && millis() > nextTiltUpdate ) {
        int16_t gyro, acc;
        sensor.getTilt(gyro, acc);
        scoreBoard.show(acc-tiltOffset);
        nextTiltUpdate += TILTUPDATE;
      }

    }
  }

  // Display the time delay if it changed by at least ten.  Otherwise the display flutters
  // because the A/D converter doesn't return a stable value.
  bool potChanged = false;
  unsigned long newDelay = button.getDelay();
  int delta = (newDelay > buttonDelay) ? (newDelay-buttonDelay) : (buttonDelay-newDelay);

  if ( delta >= 10 ) {
    buttonDelay = newDelay;
    potChanged = true;
  }
  if (potChanged || button.isChanged() || options.isChanged() || disableSwitch.isChanged() ) refreshDisplay();

  // Signal the scoreboard that the jumper is disabled
  if ( disableSwitch.isChanged() ) {
    if ( disableSwitch.isEnabled() ) {
      scoreBoard.clear();
    } 
    else {
      scoreBoard.show("OFF");
    }
  }


}

void refreshDisplay()
{
  display.clear();
  display.printf(0,0,"Jumper: %s", disableSwitch.isEnabled() ? "RUNNING" : "DISABLED");
  display.printf(0,1,"J:%8lu/%8lu", button.getFilteredPresses(), button.getRawPresses());
  display.printf(0,2,"Delay: %d ms", buttonDelay);
  display.print(0,3,"Opt: ");
  for (int i=0 ; i<8 ; i++ ) {
    if(options.getValue(i)) {
      display.print("Y");
    } 
    else {
      display.print(".");
    }
  }
  if ( button.isDown() ) {
    display.print(16,3,"JUMP");
  } 
  else {
    display.print(16,3,"----");
  }

}


