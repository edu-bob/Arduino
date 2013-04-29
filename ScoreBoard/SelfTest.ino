//
// Self Test controller
//
// Cycles through a sequence of test
//

#include "SelfTest.h"

void SelfTest::setup()
{
  running = false;
}

void SelfTest::loop()
{
  if ( running ) {
    test->loop();
  }
}

void SelfTest::setDigitsObject(Digits &_digits)
{
  digits = &_digits;
}

void SelfTest::start(int num)
{
//  Serial.print(F("SelfTest::start "));Serial.println(num);
  testNumber = num;
  switch ( num ) {
    case 1:
      test = &test1;
      break;
    case 2:
      test = &test2;
      break;
    case 3:
      test = &test3;
      break;
    case 4:
      test = &test4;
      break;
    case 5:
      test = &test5;
      break;
    case 6:
      test = &test6;
      break;
    default:
      test = &test1;
  }
  test->setDigitsObject(*digits);
  digits->clear();
  test->start();
  running = true;
}

void SelfTest::stop()
{
  test->stop();
  running = false;
  digits->clear();
}

