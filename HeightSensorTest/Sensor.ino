//
// Height sensor
//

#include <Wire.h>
#include "Accelerometer.h"
#include "Gyrometer.h"

Accelerometer accelerometer;
Gyrometer gyrometer;

void Sensor::setup()
{
   // Join the I2C bus as master
   Wire.begin();

  accelerometer.setup();
  gyrometer.setup();
}


void Sensor::loop()
{
  accelerometer.loop();
  gyrometer.loop();
}

void Sensor::setSampleInterval(unsigned long interval)
{
}

int Sensor::recentMaximum()
{
}

void Sensor::getRawValues(int *res)
{
  accelerometer.getValues(res);
  gyrometer.getValues(res+3);
}

void Sensor::calibrate()
{
  gyrometer.calibrate();
}

void Sensor::print()
{
  int values[6];
  char buf[60];
  getRawValues(values);
  sprintf(buf, "%7d %7d %7d | %7d %7d %7d",values[0],values[1],values[2],values[3],values[4],values[5]);
  Serial.println(buf);

}
