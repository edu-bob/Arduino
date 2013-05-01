/*
 ** Jumper class - handles all of the mechanics of the Jumper itself
 */
 
void Jumper::setup()
{
  off();
}

void Jumper::loop()
{
}

void Jumper::begin(int _pin)
{
  pin = _pin;
  pinMode(pin, OUTPUT);
  pinMode(pin, 0);
}

void Jumper::jump()
{
}

void Jumper::off()
{
  active = false;
}

void Jumper::on()
{
  active = true;
}
