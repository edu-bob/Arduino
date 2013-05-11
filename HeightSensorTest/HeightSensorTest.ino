#include "Sensor.h"

Sensor sensor;


void setup()
{
  Serial.begin(9600);
  Serial.println(F("Starting..."));
  Serial.print(F("Free RAM: "));Serial.println(freeRam());
  sensor.setup();
  sensor.calibrate();
}

// Iteration cycle, each device has work to do in setting up the game logic

void loop()
{
    sensor.loop();
    
    sensor.print();
    delay(250);
}

