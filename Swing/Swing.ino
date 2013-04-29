#include <stdio.h>
#include "pins.h"
#include <LiquidCrystal.h>

#include "Heartbeat.h"
#include "Button.h"
#include "Piston.h"


LiquidCrystal lcd(
  PIN_LCD_RS,
  PIN_LCD_E,
  PIN_LCD_DB4,
  PIN_LCD_DB5,
  PIN_LCD_DB6,
  PIN_LCD_DB7
  );

Heartbeat heart;
Button legButton;
Button armButton;
Piston legPiston;
Piston armPiston;

int displayMode;
unsigned long nextDisplaySwitch;

int buttonDelay;

void setup()
{  
  lcd.begin(16,2);
 
  heart.setup();
  
  legButton.setup();
  armButton.setup();
  armPiston.setup();
  legPiston.setup();
  
  buttonDelay = legButton.getDelay();

  legButton.begin(PIN_LEGS_IN, PIN_DELAY);
  armButton.begin(PIN_ARMS_IN, PIN_DELAY);
  legPiston.begin(PIN_LEGS_OUT);
  armPiston.begin(PIN_ARMS_OUT);

  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Posables Swing");
  delay(2000);
  
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
  if ( armButton.wasPressed() ) {
    armPiston.extend();
  } else {
    if ( !armButton.isDown() ) {
      armPiston.retract();
    }
  }
  if ( legButton.wasPressed() ) {
    legPiston.extend();
  } else {
    if ( !legButton.isDown() ) {
      legPiston.retract();
    }
  }
  if ( armButton.isChanged() || legButton.isChanged() )  showDisplay();
  
  // Display the time delay if it changed
  
  unsigned long newDelay = legButton.getDelay();
  int delta = (newDelay > buttonDelay) ? (newDelay-buttonDelay) : (buttonDelay-newDelay);
  
  if ( delta >= 10 ) {
    buttonDelay = newDelay;
    displayMode = 1;
    nextDisplaySwitch = millis()+2000ul;
    showDisplay();
  }
  if ( displayMode != 0 && millis() > nextDisplaySwitch ) {
    displayMode = 0;
    showDisplay();
  }
}
  

void showDisplay()
{
  char buf[17];
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

