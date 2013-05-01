
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
void ScoreBoard::show(int val)
{
  serial->print("=");
  serial->println(val);
}
void ScoreBoard::show(char *str)
{
  serial->print("=");
  serial->println(str);
}
void ScoreBoard::scroll(char *str)
{
  serial->print("S");
  serial->println(str);
}
void ScoreBoard::on(void)
{
  serial->println("N");
}

void ScoreBoard::off(void)
{
  serial->println("F");
}
void ScoreBoard::runTest(int num)
{
  serial->print("t");
  serial->println(num);
}
void ScoreBoard::pattern(unsigned long hex)
{
  serial->print("x");
  serial->println(hex, HEX);
}

