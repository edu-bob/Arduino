#ifndef PUSHBUTTON_H
#define PUSHBUTTON_H

#include <WProgram.h>

class PushButton {
  public:
    void setup(void);
    void loop(void);
    bool isPressed(void);
    
    void testSetup(void);
    void testLoop(void);
  private:
    unsigned int testLastState;
    unsigned long testStartTime;
};

#endif

