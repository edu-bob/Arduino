#include "Box.h"
#include "bellbox_consts.h"

void Box::setup()
{
  pinMode(RED_LED, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);
  pinMode(BLUE_LED, OUTPUT);
  pinMode(SOLENOID, OUTPUT);
  pinMode(REED_SWITCH, INPUT);
  
  digitalWrite(SOLENOID, 0);
  digitalWrite(RED_LED, 0);
  digitalWrite(GREEN_LED, 0);
  digitalWrite(BLUE_LED, 0);
  heartbeat = 1;
}

void Box::setHeartbeat(int value)
{
  heartbeat = value;
  if ( value ) {
    heart = 0;
    lastHeartbeat = millis();
  } else {
    setHeart(0);
  }
}

void Box::loop()
{
  if ( heartbeat ) {
    unsigned long m = millis();
    if ( m % HEART_INTERVAL < HEART_BLINK && heart == 0 ) {
      heart = 1;
//      int bright = (((m % HEART_INTERVAL) * HEART_BRIGHTNESS) / HEART_BLINK)
      setHeart(1);
//      Serial.println(((m % HEART_INTERVAL) * HEART_BRIGHTNESS) / HEART_BLINK);
    }
    if ( m % HEART_INTERVAL >= HEART_BLINK && heart == 1 ) {
      heart = 0;
      setHeart(0);
    }
  }
}

void Box::setHeart(int value)
{
  if ( value ) {
    color(0, value, 0);
  } else {
    color(0, 0, 0);
  }
}

void Box::led(unsigned char which, unsigned char state)
{
  digitalWrite(which, state);
}
void Box::color(unsigned char c)
{
  led(RED_LED, (c >> 2) & 1);
  led(GREEN_LED, (c >> 1) & 1);
  led(BLUE_LED, c & 1);
}
void Box::color(unsigned char r, unsigned char g, unsigned char b)
{
  dimled(RED_LED, r);
  dimled(GREEN_LED, g);
  dimled(BLUE_LED, b);
}
void Box::dimled(unsigned char which, unsigned char value)
{
  analogWrite(which, value);
}

void Box::solenoid(unsigned char value)
{
  digitalWrite(SOLENOID, value);
}

/**
 * turn on and off the LED slowly
 */

void Box::doLED(unsigned char color)
{
  doLED(color, 256);
}

void Box::doLED(unsigned char color, int ms)
{
  int red = (color>>2) & 1;
  int green = (color>>1) & 1;
  int blue = color & 1;
  
  int i;
  
  for ( i=0 ; i<ms ; i++ ) {
    Box::color(i*red, i*green, i*blue);
    delay(i<ms/2 ? (i<ms/4?7:5): 3);
  }
  for ( i=ms ; i>=0 ; i-- ) {
    Box::color(i*red, i*green, i*blue);
//    delay(1);
    delay(i<ms/2 ? (i<ms/4?9:5): 3);
  }
}

void Box::doBell()
{
  solenoid(1);
  delay(75);
  solenoid(0);
}

