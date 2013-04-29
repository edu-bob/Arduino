#ifndef BUTTON_H
#define BUTTON_H

#include <WProgram.h>

class Button {
  public:
    void setup(void);
    void loop(void);
    void setMinInterval(unsigned int);
    bool isDown(void);
    bool wasPressed(void);
    
    void testSetup(void);
    void testLoop(void);
  private:
    unsigned int lastState;
    unsigned long lastTimePushed;
    unsigned int minInterval;
    bool pushed;
    unsigned int testLastState;
    unsigned long testStartTime;
};

#endif

