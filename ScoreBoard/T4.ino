//
// Test #4 - scroll digits through the display
//

int T4::getNumSteps()
{
  return 10;
}

// Override getDelay to slow it down

unsigned long T4::getDelay()
{
  return 500ul;
}

//
// nextStep - return the next value in the test sequence
//
void T4::doNextStep()
{
  int s = getNumSteps();
 
  if ( step >= s ) step = 0;
//  Serial.print(F("T4::doNextStep: "));Serial.println(step);
  digits->setOneDigit(step);
}


