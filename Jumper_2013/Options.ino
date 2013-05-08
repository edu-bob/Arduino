//
// Options class - reads 8 DIP switches that are used as binary options to the proigram
//

#define OPTIONS_SAMPLE_INTERVAL 100

void Options::setup()
{
  nextSampleTime = millis();
  changed = false;
}

void Options::begin(int _pin)
{
  int i;
  for ( i=0 ; i<OPTIONS_COUNT ; i++ ) {
    pins[i] = _pin+i;
  }
  begin2();
}

void Options::begin(int p0, int p1, int p2, int p3, int p4, int p5, int p6, int p7)
{
  pins[0] = p0;
  pins[1] = p1;
  pins[2] = p2;
  pins[3] = p3;
  pins[4] = p4;
  pins[5] = p5;
  pins[6] = p6;
  pins[7] = p7;
  begin2();
}

//
// Set the pin mode on all of the options pins
//
void Options::begin2()
{
  int i;
  for ( i=0 ; i<OPTIONS_COUNT ; i++ ) {
    pinMode(pins[i], INPUT_PULLUP);
    values[i] = !digitalRead(pins[i]);
  }
}

void Options::loop()
{
  if ( millis() >= nextSampleTime ) {
    int i;
    for ( i=0 ; i<OPTIONS_COUNT ; i++ ) {
      int value = !digitalRead(pins[i]);
      if ( value != values[i] ) changed = true;
      values[i] = value;
    }
    nextSampleTime += OPTIONS_SAMPLE_INTERVAL;
  }
}

int Options::getValue(int i)
{
  if ( i>=0 && i<=OPTIONS_COUNT ) return values[i];
  return 0;
}

bool Options::isChanged()
{
  bool saveChanged = changed;
  changed = false;
  return saveChanged;
}

