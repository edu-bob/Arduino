/*
 ** Jumper class - handles all of the mechanics of the Jumper itself
 */
 
void Jumper::setup()
{
  off();
}

void Jumper::loop()
{
  pinMode(JUMPER_LEGS_PIN, OUTPUT);
  pinMode(JUMPER_LEGS_PIN, 0);
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
