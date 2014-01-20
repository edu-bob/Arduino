#ifndef PUSHBUTTON_H
#define PUSHBUTTON_H

#include <WProgram.h>

#define PB_DEBOUNCE (unsigned long)20

class PushButton {
  public:
    void setup(int);
    void loop(void);
    unsigned int getStableValue(void);
    bool isChanged(void);
  private:
    bool changed;
    unsigned int value();
    unsigned int lastValue;
    unsigned int stableValue;
    unsigned long lastChangeTime;
    int pin;
};

#endif

