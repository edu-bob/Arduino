#include "pins.h"

#include <LiquidCrystal.h>
#include <HardwareSerial.h>

#include "Button.h"
#include "Jumper.h"
#include "Display.h"
#include "Options.h"
#include "ScoreBoard.h"

#include "TestMode.h"

Button button;
Jumper jumper;
Display display;
Options options;
ScoreBoard scoreBoard;

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
  delay(5000);

  if ( testMode ) {
    tester.setup();
  } else {
    button.setup();
    jumper.setup();
    options.setup();
    scoreBoard.setup();

    button.begin(BUTTON_PIN, DELAY_POT_PIN);
    jumper.begin(JUMPER_LEGS_PIN);
    options.begin(DIP_PIN_0);
    scoreBoard.begin(Serial1);

    jumper.on();
  }
  
   buttonDelay = button.getDelay();

}


void loop()
{
  if ( testMode ) {
    tester.loop();
  } else {
    button.loop();
    jumper.loop();
    options.loop();
    scoreBoard.loop();

    jumperLogic();
  }
}


/*
 * jumperLogic - the control logic for the jumper
 */
 
 void jumperLogic()
 {
   if ( button.wasPressed() ) {
     jumper.jump();
   }
 
   // update the display only if any of the counters changed, to avoid flicker
   if ( button.isChanged() ) showDisplay();

   // Display the time delay if it changed by at least ten.  Otherwise the display flutters
   // because the A/D converter doesn't return a stable value.
   unsigned long newDelay = button.getDelay();
   int delta = (newDelay > buttonDelay) ? (newDelay-buttonDelay) : (buttonDelay-newDelay);
  
   if ( delta >= 10 ) {
     buttonDelay = newDelay;
     showDisplay();
   }
   if (options.isChanged()) showDisplay();
}

void showDisplay()
{
  sprintf(DisplayBuf, "J:%8lu/%8lu", button.getFilteredPresses(), button.getRawPresses());
  display.clear();
  display.setCursor(0,0);
  display.print(DisplayBuf);
  display.printf(0,1,"Delay: %d ms", buttonDelay);
  display.print(0,2,"Options: ");
  for (int i=0 ; i<8 ; i++ ) {
    if(options.getValue(i)) {
      display.print("Y");
    } else {
      display.print(".");
    }
  }
}

