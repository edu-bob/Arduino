/*
 * Piston class - control a single piston
 */
 
void Piston::setup()
{
}

void Piston::begin(int _pin)
{
  pin = _pin;
  pinMode(pin, OUTPUT);
  digitalWrite(pin, 0);
  extended = false;
}

void Piston::loop()
{
}

void Piston::extend()
{
  digitalWrite(pin,1);
  extended = true;
}

void Piston::retract()
{
  digitalWrite(pin,0);
  extended = false;
}

