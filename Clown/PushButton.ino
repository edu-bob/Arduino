#define PUSHBUTTON_DOWN LOW
#define PUSHBUTTON_UP HIGH

#define PUSHBUTTON_DELAY 1000

void PushButton::setup()
{
  pinMode(PUSHBUTTON_PIN, INPUT_PULLUP);
}

/*
 * loop - called on each main loop.
 *
 */
 
void PushButton::loop()
{
}

bool PushButton::isPressed()
{
  return digitalRead(PUSHBUTTON_PIN) == PUSHBUTTON_DOWN;
}

//--------------------------------------------------------
// Test Functions
//
void PushButton::testSetup(void)
{
    pinMode(PUSHBUTTON_PIN, INPUT_PULLUP);
    testLastState = digitalRead(PUSHBUTTON_PIN);
    testStartTime = millis();
}
void PushButton::testLoop(void)
{
  unsigned int currentState = digitalRead(PUSHBUTTON_PIN);
  if ( currentState != testLastState ) {
    Serial.print(millis()-testStartTime);
    Serial.print(F(" Push button changed from "));
    Serial.print(testLastState);
    Serial.print(F(" to "));
    Serial.println(currentState);
    testLastState = currentState;
  }
}
