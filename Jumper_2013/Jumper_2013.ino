#include "Button.h"
#include "Jumper.h"
#include "Display.h"

#include "TestMode.h"

Button button;
Jumper jumper;
Display display;

const bool testMode = false;
TestMode tester;

void setup() {
  Serial.begin(9600);
  Serial.println(F("Starting..."));
  Serial.print(F("Free RAM: "));Serial.println(freeRam());
  
  button.setMinInterval(1000ul);
  
  display.setup();
  display.print2("Maker Faire 2013", "Posable Jumper M3");

  if ( testMode ) {
    tester.setup();
  } else {
    button.setup();
    jumper.setup();
    Jumper.on();
  }
}


void loop()
{
  if ( testMode ) {
    tester.loop();
  } else {
    button.loop();
    jumper.loop();

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
 }
 
