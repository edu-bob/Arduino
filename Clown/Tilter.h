#ifndef TILTER_H
#define TILTER_H

#include <WProgram.h>

#define TILTED_DOWN 0
#define TILTED_UP 1

#define TILT_VALUE_OPEN HIGH
#define TILT_VALUE_CLOSED LOW

#define TILT_TEST_DELAY_DOWN 10000ul
#define TILT_TEST_DELAY_UP 3000ul

class Tilter {
  public:
    void setup(void);
    void loop(void);
    void tiltUp(void);
    void tiltDown(void);
    void testSetup(void);
    void testLoop(void);
  private:
    int state;
    
    unsigned long testStartTime;
    unsigned long testNextTime;
    int testState;
    
};

#endif


