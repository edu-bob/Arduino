//
// Control the LCD  
//

#include "Display.h"
#include "pins.h"
#include <LiquidCrystal.h>
#include <stdarg.h>


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
void Display::print(int val)
{
  lcd->print(val);
}
void Display::setCursor(uint8_t col, uint8_t row)
{
  lcd->setCursor(col, row);
}

/**
 * print - print two lines on the display
 */
 
void Display::print(char *line1, char *line2)
{
  lcd->clear();
  lcd->print(line1);
  lcd->setCursor(0,1);
  lcd->print(line2);
}
/**
 * print - print three lines on the display
 */
void Display::print(char *line1, char *line2, char *line3)
{
  print(line1,line2);
  lcd->setCursor(0,2);
  lcd->print(line3);
}
/**
 * print - print four lines on the display
 */
void Display::print(char *line1, char *line2, char *line3, char *line4)
{
  print(line1,line2,line3);
  lcd->setCursor(0,3);
  lcd->print(line4);
}

void Display::printf(int c, int r, char *fmt, ... )
{
  char tmp[128]; // resulting string limited to 128 chars
  va_list args;
  va_start (args, fmt );
  vsnprintf(tmp, 128, fmt, args);
  va_end (args);
  lcd->setCursor(c,r);
}
