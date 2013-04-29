#ifndef SBTEST4_H
#define SBTEST4_H

#include "Digits.h"
#include "SBTest.h"

class T4: public SBTest {
  public:
    virtual void doNextStep(void);
    virtual int getNumSteps(void);
    virtual unsigned long getDelay(void);
};

#endif

