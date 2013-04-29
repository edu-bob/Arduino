
//
// Mode Switch
//
// Implements reading values from a three-bit SCSI selector switch hooled up via pullups to
// three D pins
//

#define MODESWITCH_SETTLE 50ul

void ModeSwitch::setup()
{
  pinMode(MODESW_1,INPUT_PULLUP);
  pinMode(MODESW_2,INPUT_PULLUP);
  pinMode(MODESW_4,INPUT_PULLUP);
  goodValue = readBits();
  bouncing = false;
}

//
// On each iteration, see if we are debouncing /or/ check for a change
//
// This copies the bits into goodValue only after no change for MODESWITCH_SETTLE milliseconds
//
void ModeSwitch::loop()
{
  // This implements a delay after the last time the bits were read.
  
  if ( bouncing ) {
    
    // Has the settling time elapsed since the last change?
    if ( millis() > lastSampleTime+MODESWITCH_SETTLE ) {
      goodValue = readBits();
//      Serial.print(F("ModeSwitch value="));Serial.println(goodValue);
      bouncing = false;
    } else { 
      
      // if debouncing, check for another change and record its timestamp if changed
      int newValue = readBits();
      if ( newValue != lastValue ) {
        lastValue = newValue;
        lastSampleTime = millis();
      }
    }
  } else {
    
    // not debouncing, check for a change in the bits
    lastValue = readBits();
    if ( lastValue != goodValue ) {
      bouncing = true;
      lastSampleTime = millis();
    }
  }
}

//
// getValue - return the last debounced value
//

int ModeSwitch::getValue()
{
  return goodValue;
}

//
// readValue - private function to read the input bits
//
int ModeSwitch::readBits()
{
  return ((digitalRead(MODESW_4) ? 0 : 1)<<2) | ((digitalRead(MODESW_2) ? 0 : 1)<<1) | (digitalRead(MODESW_1) ? 0 : 1);
}
