#include <stdint.h>
#include <Wire.h>
#include "Sensor.h"

Sensor sensor;
int outMode = 1;
int timeDelay = 50;

#define ALPHA 0.0
int accelerator, gyro;
unsigned long nextFlash;
bool flashOn;
#define FLASH 250

void setup()
{
  Serial.begin(9600);
  Serial.println(F("Starting..."));
  Serial.print(F("Free RAM: "));Serial.println(freeRam());
  Serial.println(F("1=dec, 2=hex, other=ms delay"));
  delay(2000);
  pinMode(13,OUTPUT);
  nextFlash = millis();
  flashOn = true;
  sensor.setup();
  int16_t temp, gyro_x, gyro_y, gyro_z, acc_x, acc_y, acc_z;
  sensor.getValues(temp, gyro_x, gyro_y, gyro_z, acc_x, acc_y, acc_z);
  accelerator = acc_x;
  gyro = gyro_y;
}

// Iteration cycle, each device has work to do in setting up the game logic

void loop()
{
  sensor.loop();
  
  if ( millis() > nextFlash ) {
    flashOn = !flashOn;
    digitalWrite(13, flashOn ? 1 : 0 );
    nextFlash += FLASH;
  }
  if ( Serial.available() ) {
    int val = Serial.parseInt();
//    Serial.print(F("VALUE="));Serial.println(val);
    if ( val==1 || val==2 ) {
      outMode = val;
    } else {
      if ( val != 0 ) timeDelay = val;
    }
  }
  
  switch ( outMode ) {
    case 1:
//      sensor.print();
        int16_t temp, gyro_x, gyro_y, gyro_z, acc_x, acc_y, acc_z;
        sensor.getValues(temp, gyro_x, gyro_y, gyro_z, acc_x, acc_y, acc_z);
//        Serial.print(millis());
//        Serial.print(",");
//        Serial.print(temp);
//        Serial.print(",");
//        Serial.print(gyro_y);
//        Serial.print(",");
//        Serial.println(acc_x);
      accelerator = ALPHA*accelerator + (1.0-ALPHA)*acc_x;
      gyro = ALPHA*gyro + (1.0-ALPHA)*gyro_y;
        Serial.print(millis());
        Serial.print(",");
         Serial.print(gyro);
        Serial.print(",");
        Serial.println(accelerator);
      break;
    case 2:
      sensor.printHex();
      break;
  }
  delay(timeDelay);
}

