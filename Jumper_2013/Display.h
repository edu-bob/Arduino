#ifndef DISPLAY_H
#define DISPLAY_H

#include <LiquidCrystal.h>

#define DISPLAY_COLUMNS 20
#define DISPLAY_ROWS 4

#include <stdint.h>


class Display {
  public:
    void setup();
    void loop();
    void clear();
    void update();
    void print(int, int, char *);
    void print(int);
    void print(char *);
    void print(char *, char *);
    void print(char *, char *, char *);
    void print(char *, char *, char *, char *);
    void printf(int, int, char *, ... );
    void printf(char *, ...);
    void setCursor(uint8_t, uint8_t);
  private:
    LiquidCrystal *lcd;
    char buffer[DISPLAY_COLUMNS*DISPLAY_ROWS+1];

};

#endif

