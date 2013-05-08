#include "pins.h"

#include <LiquidCrystal.h>
#include <HardwareSerial.h>

#include "Heartbeat.h"
#include "Button.h"
#include "Jumper.h"
#include "Display.h"
#include "Options.h"
#include "ScoreBoard.h"
#include "DisableSwitch.h"

#include "TestMode.h"

Heartbeat heart;
Button button;
Jumper jumper;
Display display;
Options options;
ScoreBoard scoreBoard;
DisableSwitch disableSwitch;

char DisplayBuf[21]; // characters in a line +1 for the ASCII NUL

unsigned long buttonDelay;

const bool testMode = false;
TestMode tester;

void setup()
{
  Serial.begin(9600);
  Serial.println(F("Starting..."));
  Serial.print(F("Free RAM: "));Serial.println(freeRam());

  display.setup();
  sprintf(DisplayBuf, "Free RAM: %d", freeRam());
  display.print("Maker Faire 2013", "Posable Jumper M3", DisplayBuf);
  display.setCursor(0,3);
  for ( int i = 5 ; i>=1 ; i-- ) {
    display.printf("%d...", i);
    delay(1000);
  }
  display.print("0");
  delay(250);

  if ( testMode ) {
    tester.setup();
  } else {
    // heartbeat LED, to let me know that the program is running
    heart.setup();
    
    button.setup();
    jumper.setup();
    options.setup();
    scoreBoard.setup();
    disableSwitch.setup();

    button.begin(BUTTON_PIN, DELAY_POT_PIN);
    jumper.begin(JUMPER_LEGS_PIN);
    options.begin(DIP_PIN_0);
    scoreBoard.begin(Serial1);
    disableSwitch.begin(DISABLE_SWITCH_PIN);

    jumper.on();
  }
  
  buttonDelay = button.getDelay();
  refreshDisplay();
}


void loop()
{
  if ( testMode ) {
    tester.loop();
  } else {
    heart.loop();
    button.loop();
    jumper.loop();
    options.loop();
    scoreBoard.loop();
    disableSwitch.loop();

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
   // Also, turn on or off press counting.
   
   if ( disableSwitch.isChanged() ) {
     if ( disableSwitch.isEnabled() ) {
       button.enable();
       button.clearPressed();
     } else {
       button.disable();
     }
   }
   
   // If the disable switch is set, skip checking the pushbutton
   if ( disableSwitch.isEnabled() ) {
     if ( button.wasPressed() ) {
       jumper.extend();
     } else {
       if ( jumper.isExtended() && !button.isDown() ) {
       jumper.retract();
       }
     }
   }
 

   // Display the time delay if it changed by at least ten.  Otherwise the display flutters
   // because the A/D converter doesn't return a stable value.
   unsigned long newDelay = button.getDelay();
   int delta = (newDelay > buttonDelay) ? (newDelay-buttonDelay) : (buttonDelay-newDelay);
  
   if ( delta >= 10 ) {
     buttonDelay = newDelay;
     refreshDisplay();
   }
   if (button.isChanged() || options.isChanged() || disableSwitch.isChanged() ) refreshDisplay();
   
   // Signal the scoreboard that the jumper is disabled
   if ( disableSwitch.isChanged() ) {
     if ( disableSwitch.isEnabled() ) {
     } else {
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
    } else {
      display.print(".");
    }
  }
  if ( button.isDown() ) {
     display.print(16,3,"JUMP");
  } else {
     display.print(16,3,"----");
  }

}

