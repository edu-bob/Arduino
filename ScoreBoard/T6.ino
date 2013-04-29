//
// Test #6 - Serial line test
//

int T6::getNumSteps()
{
  return 1000;
}

//
// nextStep - return the next value in the test sequence
//
void T6::doNextStep()
{
  if ( step == 0 ) {
    digits->setString("TEST");
  }
  if ( step >= getNumSteps() ) step = 1; // Don't go back to step 0
  Serial.print(F("U*"));
}


