#include <stdio.h>
#include "pins.h"
#include <LiquidCrystal.h>

#include "Heartbeat.h"
#include "Button.h"
#include "Piston.h"

// The LCD display object is a global static.

LiquidCrystal lcd(
  PIN_LCD_RS,
  PIN_LCD_E,
  PIN_LCD_DB4,
  PIN_LCD_DB5,
  PIN_LCD_DB6,
  PIN_LCD_DB7
  );

// These are global statics that manage the inputs and outputs

Heartbeat heart;
Button legButton;
Button armButton;
Piston legPiston;
Piston armPiston;

// displayMode: what to show on the LCD
// 0=show button press counts; 
// 1=show time delay value
// The display reverts to mode zero after a period of time
int displayMode;
unsigned long nextDisplaySwitch;

// This holds the last-read value of the time delay potentiometer (in milliseconds)
int buttonDelay;

/*
 ** setup - called once
 *
 * The way I set up helper classes (like Button and Piston) is that each 
 * has a setup() and loop() function that take zero parameters.  These aren't
 * always used but I've just adopted it as a style.  If a class needs some
 * initialization information (like pin numbers) then I also define a begin()
 * method that finishes the setup chore.
 */
 
void setup()
{  
  lcd.begin(16,2);

  // heartbeat LED, to let me know that the program is running
  heart.setup();
  
  legButton.setup();
  armButton.setup();
  armPiston.setup();
  legPiston.setup();
  
  // define the I/O pins used
  legButton.begin(PIN_LEGS_BUTTON, PIN_DELAY);
  armButton.begin(PIN_ARMS_BUTTON, PIN_DELAY);
  legPiston.begin(PIN_LEGS_PISTON);
  armPiston.begin(PIN_ARMS_PISTON);

  // There is a single time delay pot for both legs and arms, so we can get
  // the value from either object
  buttonDelay = legButton.getDelay();

  // Introduce the program to the world through the LCD
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Posables Swing");
  delay(2000);
  
  // Initially show the time delay value for two seconds
  displayMode = 1;
  nextDisplaySwitch = millis()+2000ul;
  showDisplay();
}

void loop() 
{
  heart.loop();
  armButton.loop();
  legButton.loop();

  swingLogic();
}

/*
 * swingLogic - the control logic for the swing
 */
 
void swingLogic()
{
  // Was an arm button press passed through?
  if ( armButton.wasPressed() ) {
    armPiston.extend();
  } else {
    if ( armPiston.isExtended() && !armButton.isDown() ) {
      armPiston.retract();
    }
  }
  if ( legButton.wasPressed() ) {
    legPiston.extend();
  } else {
    if ( legPiston.isExtended() && !legButton.isDown() ) {
      legPiston.retract();
    }
  }
  
  // update the display only if any of the counters changed, to avoid flicker
  if ( displayMode == 0 && (armButton.isChanged() || legButton.isChanged()) )  showDisplay();
  
  // Display the time delay if it changed by at least ten.  Otherwise the display flutters
  // because the A/D converter doesn't return a stable value.
  unsigned long newDelay = legButton.getDelay();
  int delta = (newDelay > buttonDelay) ? (newDelay-buttonDelay) : (buttonDelay-newDelay);
  
  if ( delta >= 10 ) {
    buttonDelay = newDelay;
    // Switch the display to "show delay" mode for two seconds and refresh the display
    displayMode = 1;
    nextDisplaySwitch = millis()+2000ul;
    showDisplay();
  }
  
  // Check if it's time to switch back to normal display mode, if not already in normal mode
  if ( displayMode != 0 && millis() > nextDisplaySwitch ) {
    displayMode = 0;
    showDisplay();
  }
}
  
/*
 ** showDisplay - update the LCD Display
 *
 * What gets shown depends on the value of displayMode.
 */
 
void showDisplay()
{
  char buf[17]; // characters in a line +1 for the ASCII NUL
  switch( displayMode ) {
    case 0:
      sprintf(buf, "A:%6lu/%6lu", armButton.getFilteredPresses(), armButton.getRawPresses());
      lcd.setCursor(0,0);
      lcd.print(buf);
      sprintf(buf, "L:%6lu/%6lu", legButton.getFilteredPresses(), legButton.getRawPresses());
      lcd.setCursor(0,1);
      lcd.print(buf);
      break;
    case 1:
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Delay:");
      lcd.print(buttonDelay);
      lcd.print("ms");
      break;
  }
}

