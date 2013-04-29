//
// Test #5 - scroll digits through the display
//

int T5::getNumSteps()
{
  int val=1;
  for ( int i=0 ; i < digits->getNumDigits() ; i++ ) val *= 10;
  return val;
}

// Override getDelay to slow it down

unsigned long T5::getDelay()
{
  if ( step == 1953 || step == 2013 ) return 3000ul;
  return 100ul;
}

//
// nextStep - return the next value in the test sequence
//
void T5::doNextStep()
{
  if ( step== 0 ) step = 1900;
  int s = getNumSteps();
 
  if ( step >= s ) step = 0;
  digits->clear();
  digits->setNumber(step);
}
