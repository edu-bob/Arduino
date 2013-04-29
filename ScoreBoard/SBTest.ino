
void SBTest::setup()
{
//  Serial.println(F("SBTest::setup"));
  running = false;
  digits = (Digits *)0;
}

void SBTest::loop()
{
  if ( running ) {
    if ( millis() < nextTime ) return;
    doNextStep();
    nextTime += getDelay();
    step++;
  }
}

unsigned long SBTest::getDelay()
{
  return 50ul;
}

void SBTest::setDigitsObject(Digits &_digits)
{
  digits = &_digits;
}

void SBTest::start(void)
{
  running = true;
  step = 0;
  nextTime = millis();
//  Serial.println(F("Test mode started."));
  
}



void SBTest::stop(void)
{
  running = false;
}



