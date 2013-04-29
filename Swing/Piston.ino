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
}

void Piston::loop()
{
}

void Piston::extend()
{
  digitalWrite(pin,1);
}

void Piston::retract()
{
  digitalWrite(pin,0);
}

