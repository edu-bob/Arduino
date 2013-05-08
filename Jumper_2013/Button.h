#ifndef BUTTON_H
#define BUTTON_H

#include <WProgram.h>

class Button {
  public:
    void setup(void);
    void loop(void);
    void begin(int, int);
    bool isDown(void);
    bool wasPressed(void);
    bool isChanged(void);
    void enable(void) { enabled = true; };
    void disable(void) { enabled = false; };
    void clearPressed(void) { pushed = false; };
    unsigned long getDelay(void);
    unsigned long getRawPresses(void) { return pressesRaw; };
    unsigned long getFilteredPresses(void) { return pressesFiltered; };

    void testSetup(void);
    void testLoop(void);
  private:
    bool enabled;
    bool changed;
    unsigned long pressesRaw;
    unsigned long pressesFiltered;
    unsigned int state(void);
    int pin;
    int delayPin;
    unsigned int lastState;
    unsigned long lastTimePushed;
    bool pushed;
    unsigned int testLastState;
    unsigned long testStartTime;
};

#endif

