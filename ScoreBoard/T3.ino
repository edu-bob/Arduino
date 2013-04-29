//
// Test Sequence 3 - some pattern
//
unsigned long T3::bits[] = { 
0x01010101,0x40404040,0x88888888,0x40404040,0x01010101,0x40404040,0x88888888,0x40404040,0x01010101,
0x00000006,0x00000030,0x00000600,0x00003000,0x00060000,0x00300000,0x06000000,0x30000000,0x06000000,0x00300000,0x00060000,0x00003000,0x00000600,0x00000030,0x00000006,
0x00000086,0x000000cf,0x000000ff,0x000086ff,0x0000cfff,0x0000ffff,0x0086ffff,0x00cfffff,0x00ffffff,0x86ffffff,0xcfffffff,0xffffffff,
0xffffff79,0xffffff30,0xffffff00,0xffff7900,0xffff3000,0xffff0000,0xff790000,0xff300000,0xff000000,0x79000000,0x30000000,0x00000000
//  0x01010101,0x22222222,0x40404040,0x14141414,0x88888888,
//  0x00000006,0x00000049,0x00000030,0x00000600,0x00004900,0x00003000,0x00060000,0x00490000,0x00300000,0x06000000,0x49000000,0x30000000
};

int T3::getNumSteps()
{
  return sizeof bits / sizeof *bits;
}

// Override getDelay to slow it down

unsigned long T3::getDelay()
{
  return 200ul;
}

//
// nextStep - return the next value in the test sequence
//
void T3::doNextStep()
{
  int d = digits->getNumDigits();
  int s = getNumSteps();
 
//  Serial.print(F("step="));Serial.print(step);
//  Serial.print(F(" d="));Serial.print(d);
//  Serial.print(F(" s="));Serial.print(s);
//  Serial.print(F(" pattern="));Serial.print(bits[step]);
//  Serial.println("");

  if ( step >= s ) step = 0;
  if ( d > 0 && d <= 4 ) {
    digits->setValue( bits[step] );
  } else {
    digits->setValue((step%2) ? 0 : 0x79797979);
  }
}


