#ifndef SBTEST_H
#define SBTEST_H

#include "Digits.h"

class SBTest {
  public:
    virtual void setup(void);
    virtual void loop(void);
    virtual void setDigitsObject(Digits &);
    virtual void start(void);
    virtual void stop(void);
    virtual void doNextStep(void) = 0;
    virtual int getNumSteps(void) = 0;
    virtual unsigned long getDelay(void);
  protected:
    Digits *digits;
    bool running;
    int step;
    unsigned long nextTime;
    unsigned long delay;
};

#endif

