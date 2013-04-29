#ifndef DISPLAY_H
#define DISPLAY_H

#include <LiquidCrystal.h>

#define DISPLAY_COLUMNS 16
#define DISPLAY_ROWS 2
#include <stdint.h>


class Display {
  public:
    void setup();
    void loop();
    void clear();
    void update();
    void print(char *);
    void print2(char *, char *);
    void setCursor(uint8_t, uint8_t);
  private:
    LiquidCrystal *lcd;
};

#endif

