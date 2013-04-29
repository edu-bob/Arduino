#ifndef SBTEST3_H
#define SBTEST3_H

#include "Digits.h"
#include "SBTest.h"

class T3: public SBTest {
  public:
    virtual void doNextStep(void);
    virtual int getNumSteps(void);
    virtual unsigned long getDelay(void);
  private:
    static unsigned long bits[];
};

#endif

