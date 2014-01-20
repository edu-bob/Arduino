
void Motor::setup()
{
  state = M_STOP;
  speed = 0;
}

void Motor::loop()
{
}

void Motor::stop()
{
  if ( state != M_STOP ) {
    Serial.println(F("MOTOR STOP"));
  }
  // put hardware stop here
  state = M_STOP;
}
void Motor::forward(int _speed)
{
  if ( state != M_FORWARD || _speed != speed ) {
    Serial.print(F("MOTOR FORWARD "));Serial.println(_speed);
  }
  // put hardware forward direction here
  speed = _speed;
  state = M_FORWARD;
}
void Motor::reverse(int _speed)
{
  if ( state != M_REVERSE || speed != _speed) {
    Serial.print(F("MOTOR REVERSE "));Serial.println(_speed);
  }
  // put hardware reverse direction here
  speed = _speed;
  state = M_REVERSE;
}

