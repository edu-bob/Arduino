
void Motor::setup()
{
  state = M_STOP;
  stop();
  requestSpeed = 0;
  requestDirection = M_IN;
  nextSpeedChange = millis();
}

void Motor::loop()
{
  // If the motor is stopped or at target speed, do nothing
  
  if ( state == M_STOP || (requestDirection == realDirection && requestSpeed == realSpeed) ) return;
  
  // Make sure the hardware is set to go in the right direction.  Don't do a fast reverse, it might break the linkage.
  
  if ( requestDirection != realDirection && realSpeed != 0 ) {
    int speed = realSpeed;
    stop();
    delay(200*speed/100);
    HWsetDirection(requestDirection);
  }

  if ( millis() >= nextSpeedChange ) {
    int delta = abs(requestSpeed - realSpeed);
    if ( delta > M_SPEEDSTEP ) {
      delta = M_SPEEDSTEP;
    }
    if ( requestSpeed > realSpeed ) {
      HWsetSpeed(realSpeed + delta);
    } else if ( requestSpeed < realSpeed ) {
      HWsetSpeed(realSpeed - delta);
    }
    nextSpeedChange += M_TIMESTEP;
  }
  
  
}

void Motor::setDirection(int _direction)
{
  if ( requestDirection != _direction ) {
    nextSpeedChange = millis();
  }
  requestDirection = _direction;
}

void Motor::setSpeed(int _speed)
{
  if ( requestSpeed != _speed ) {
    nextSpeedChange = millis();
  }
  requestSpeed = _speed;
  state = M_RUNNING;
}

// Implement a hard stop of the motor.
// Soft stop would be setTarget(0)

void Motor::stop()
{
  if ( state != M_STOP ) {
    Serial.println(F("MOTOR STOP"));
  }
  // put hardware stop here
  HWstop();
  requestSpeed = 0;
  state = M_STOP;
}

bool Motor::isOverCurrent()
{
  return HWisOverCurrent();
}

// Hardware controls.

void Motor::HWstop()
{
  realSpeed = 0;
  if ( state != M_STOP ) Serial.println(F("STOP"));
}

void Motor::HWsetSpeed(int _speed)
{
//  Serial.print(F("SPEED "));
  if ( _speed/20 != realSpeed/20 || _speed == 0 ) Serial.println("");
  Serial.print(_speed);Serial.print(" ");
  realSpeed = _speed;
}

void Motor::HWsetDirection(int _direction)
{
  realDirection = _direction;
  Serial.print(F("DIRECTION ")); Serial.println(realDirection);
}

bool Motor::HWisOverCurrent()
{
  return false;
}

