/*
 ** Jumper class - handles all of the mechanics of the Jumper itself
 */
 
void Jumper::setup()
{
  off();
  extended = false;
  active = true;
}

void Jumper::loop()
{
}

void Jumper::begin(int _pin)
{
  pin = _pin;
  pinMode(pin, OUTPUT);
  retract();
}

void Jumper::extend()
{
  if ( active ) {
    digitalWrite(pin,1);
    extended = true;
  }
}
void Jumper::retract()
{
  if ( active ) {
    digitalWrite(pin,0);
    extended = false;
  }
}

void Jumper::off()
{
  active = false;
  retract();
}

void Jumper::on()
{
  active = true;
}
