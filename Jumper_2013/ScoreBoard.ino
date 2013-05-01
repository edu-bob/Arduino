
void ScoreBoard::setup()
{
}

void ScoreBoard::loop()
{
}

void ScoreBoard::begin(HardwareSerial &_serial)
{
  serial = &_serial;
}

void ScoreBoard::clear()
{
  serial->println("c");
}

