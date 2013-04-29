#ifndef DIGITS_H
#define DIGITS_H

#include <stdint.h>

class Digits {
  public:
    void setup(void);
    void loop(void);
    void setPins(int, int, int, int g = -1, int srclr = -1);
    void setValue(unsigned long, int bits = 0);
    void setNumber(int);
    void setNumber(char *, int len=0);
    void setString(char *, int len=0);
    void scrollString(unsigned long, char *, bool doclear=false);
    void setGbar(int);
    void setSRCLRbar(int);
    void setOneDigit(int, bool period=false);
    void clear(void);
    void setNumDigits(int);
    int getNumDigits(void);
    uint8_t getBitsForDigit(uint8_t);
    uint8_t getBitsForCharacter(uint8_t);
  private:
    void shiftValue(uint8_t);
    void latchValue(void);
    int digits;

    // state data for shifting in a message
    bool shifting;
    char shiftBuffer[32];
    int shiftIndex;
    unsigned long shiftNextTime;
    int shiftLength;
    unsigned long shiftPace;

    // Arduino pins
    int8_t pin_srck;
    int8_t pin_rck;
    int8_t pin_g;
    int8_t pin_srclr;
    int8_t pin_serin;
};

#endif

