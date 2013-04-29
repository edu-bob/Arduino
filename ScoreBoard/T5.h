#ifndef SBTEST5_H
#define SBTEST5_H

#include "Digits.h"
#include "SBTest.h"

class T5: public SBTest {
  public:
    virtual void doNextStep(void);
    virtual int getNumSteps(void);
    virtual unsigned long getDelay(void);
};

#endif

