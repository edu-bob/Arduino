#ifndef SBTEST1_H
#define SBTEST1_H

#include "Digits.h"
#include "SBTest.h"

class T1: public SBTest {
  public:
    virtual void doNextStep(void);
    virtual int getNumSteps(void);
    virtual unsigned long getDelay(void);
  private:
    static unsigned long bits[];};

#endif

