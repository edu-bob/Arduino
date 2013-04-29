#ifndef SELFTEST_H
#define SELFTEST_H

#include "SBTest.h"
#include "T1.h"
#include "T2.h"
#include "T3.h"
#include "T4.h"
#include "T5.h"
#include "T6.h"

class SelfTest {
  public:
    void setup(void);
    void loop(void);
    void setDigitsObject(Digits &);
    int getTestNumber(void) {return testNumber;};
    void start(int);
    void stop(void);
    bool isRunning(void) {return running;};
  private:
    SBTest *test;
    Digits *digits;
    bool running;
    int testNumber;
    T1 test1;
    T2 test2;
    T3 test3;
    T4 test4;
    T5 test5;
    T6 test6;
};

#endif

