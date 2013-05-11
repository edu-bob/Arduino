//
// Height sensor
//

#include <Wire.h>
#include <Accelerometer.h>

Accelerometer accelerometer;

void Sensor::setup()
{
  accelerometer.setup();
}


void Sensor::loop()
{
  accelerometer.loop();
}

void Sensor::setSampleInterval(unsigned long interval)
{
}

int Sensor::recentMaximum()
{
}

int Sensor::getValue()
{
  return accelerometer.getValue();
}

