//
// Test Sequence 1 - all LEDs
//
unsigned long T1 ::bits[] = { 0xffffffff };

int T1::getNumSteps()
{
  return sizeof bits / sizeof *bits;
}

// Override getDelay to slow it down

unsigned long T1::getDelay()
{
  return (step%2) ? 200ul : 1000ul;
}

//
// nextStep - return the next value in the test sequence
//
void T1::doNextStep()
{
  int d = digits->getNumDigits();
  int s = getNumSteps();
 
  if ( step >= s ) step = 0;
  if ( d > 0 && d <= 4 ) {
    digits->setValue( bits[step] );
  } else {
    digits->setValue((step%2) ? 0 : 0x79797979);
  }
}


