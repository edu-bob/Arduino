/*
 * TestMode class
 *
 * This is an alternate setup() and loop() when running this code in "test mode"
 *
 * It calls each components' test mode setup() and loop()
 */
 
#include "pins.h"


void TestMode::setup(void)
{
  button.testSetup();
}

void TestMode::loop(void)
{
  button.testLoop();
}

