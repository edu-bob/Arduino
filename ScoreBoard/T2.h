#ifndef SBTEST2_H
#define SBTEST2_H

#include "Digits.h"
#include "SBTest.h"

class T2: public SBTest {
  public:
    virtual void doNextStep(void);
    virtual int getNumSteps(void);
    virtual unsigned long getDelay(void);
  private:
    static uint8_t *bits[4];
    static uint8_t b1[];
    static uint8_t b2[];
    static uint8_t b3[];
    static uint8_t b4[];
};

#endif

