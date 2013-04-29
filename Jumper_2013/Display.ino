//
// Control The LCD  
//

#include "Display.h"
#include "pins.h"
#include <LiquidCrystal.h>



void Display::setup()
{
  lcd = new LiquidCrystal(LCD_RS, LCD_E, LCD_D4, LCD_D5, LCD_D6, LCD_D7);
  lcd->begin(DISPLAY_COLUMNS, DISPLAY_ROWS);
  lcd->clear();
}

void Display::loop()
{
}

void Display::clear()
{
  lcd->clear();
}
void Display::update()
{
}
void Display::print(char *str)
{
  lcd->print(str);
}
void Display::setCursor(uint8_t col, uint8_t row)
{
  lcd->setCursor(col, row);
}

/**
 * print2 - print two lines on the display
 */
 
void Display::print2(char *line1, char *line2)
{
  lcd->clear();
  lcd->print(line1);
  lcd->setCursor(0,1);
  lcd->print(line2);
}

