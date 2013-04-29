//
// Test Sequence 2 - a moving circle around the perimeter
//
uint8_t T2::b1[] = { 0,  1,  2,  3,  4,  5                        };
uint8_t T2::b2[] = { 0,  1,  2,  3, 11, 12, 13,  8                };
uint8_t T2::b3[] = { 0,  1,  2,  3, 11, 19, 20, 21, 16, 8         };
uint8_t T2::b4[] = { 0,  1,  2,  3, 11, 19, 27, 28, 29, 24, 16, 8 };

uint8_t *T2::bits[] = { b1, b2, b3, b4 };

int T2::getNumSteps()
{
  return 8 + (digits->getNumDigits()-2) * 2;
}

// Override getDelay to slow it down

unsigned long T2::getDelay()
{
  return 50ul;
}

//
// nextStep - return the next value in the test sequence
//
void T2::doNextStep()
{
  int d = digits->getNumDigits();
  int s = getNumSteps();
 
  if ( step >= s ) step = 0;
  int shift = bits[d-1][step];

//  Serial.print(F("step="));Serial.print(step);
//  Serial.print(F(" d="));Serial.print(d);
//  Serial.print(F(" s="));Serial.print(s);
//  Serial.print(F(" shift="));Serial.print(shift);
//  Serial.println("");
  digits->clear();
  unsigned long value = (1ul << shift);
  if ( d > 0 && d <= 4 ) {
    digits->setValue( value );
  } else {
    digits->setValue((step%2) ? 0 : 0x79797979);
  }
}


