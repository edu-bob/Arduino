
void ScoreBoard::setup()
{
}

void ScoreBoard::loop()
{
}

void ScoreBoard::begin(HardwareSerial &_serial)
{
  serial = &_serial;
  serial->begin(9600);
}

void ScoreBoard::clear()
{
  serial->print("c");
  serial->print("\n");
}
void ScoreBoard::show(int val)
{
//  Serial.print(F("show: "));
//  Serial.println(val);
  serial->print("=");
  serial->print(val);
  serial->print("\n");
}
void ScoreBoard::show(char *str)
{
//  Serial.print(F("show: "));
//  Serial.println(str);
  serial->print("s");
  serial->print(str);
  serial->print("\n");
}
void ScoreBoard::scroll(char *str)
{
//  Serial.print(F("scroll: "));
//  Serial.println(str);
  serial->print("S");
  serial->print(str);
  serial->print("\n");
}
void ScoreBoard::on(void)
{
  serial->print("N");
  serial->print("\n");
}

void ScoreBoard::off(void)
{
  serial->print("F");
  serial->print("\n");
}
void ScoreBoard::runTest(int num)
{
  serial->print("t");
  serial->print(num);
  serial->print("\n");
}
void ScoreBoard::pattern(unsigned long hex)
{
  serial->print("x");
  serial->print(hex, HEX);
  serial->print("\n");
}

