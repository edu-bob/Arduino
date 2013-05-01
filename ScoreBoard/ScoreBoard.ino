
#include "Digits.h"
#include "ModeSwitch.h"
#include "SelfTest.h"
#include "pins.h"

#define DIGITS 4

/**
 * TPIC6A596 based scoreboard
 */

// "Digits" is the low-level controller for the scoreboard

Digits digits;
ModeSwitch modeSwitch;
bool testMode = false;
bool selfTestMode = false;
bool blank;
bool softwareSwitch;
SelfTest selfTest;

void setup()
{
  Serial.begin(9600);
//  Serial.println(F("Starting..."));
  Serial.print(F("Free RAM: "));Serial.println(freeRam());
  
  // Set up the scoreboard controller - pins numbers and initial logic state
  
  digits.setup();
  digits.setPins(DIGITS_SERIN,
    DIGITS_SRCK,
    DIGITS_RCK,
    DIGITS_G,
    DIGITS_SRCLR);
  digits.setGbar(LOW); // enable outputs
  digits.setSRCLRbar(HIGH); // don't clear storage register
  digits.setNumDigits(DIGITS);

  softwareSwitch = false;
  modeSwitch.setup();
//  Serial.print(F("Mode switch: "));
//  Serial.println(modeSwitch.getValue());
  
  
  selfTest.setup();
  selfTest.setDigitsObject(digits);
  hello();
}

void loop()
{
  digits.loop();
  modeSwitch.loop();
  selfTest.loop();
  
  // handle the mode switch setting: 0=>normal, other=>test number

  int testNumber = modeSwitch.getValue();
  if ( selfTest.isRunning() ) {
    
    // switch was set back to zero
    if ( testNumber==0 ) { 
      selfTest.stop();

    // test number switch changed
    } else if ( testNumber != selfTest.getTestNumber() ) {
//      Serial.print(F("test change: "));Serial.print(selfTest.getTestNumber());Serial.print(" -> ");Serial.println(testNumber);
      selfTest.start(testNumber);
      
    // no change
    } else {
      selfTest.loop();
    }
  } else {
    if ( testNumber ) { // enter self test mode
      selfTest.start(testNumber);
    } else {
      ScoreBoard();
    }
  }
}

//
// Command processor
//
// =NUM - display the number (decimal) integer)
// dSTR - display the string
// N - turn on
// F - turn off
// C - clear
// eSTR - echo STR back on the serial line
// xNUM - use HEX number as the 64 bit value to load
// t# - run test #

void ScoreBoard(void)
{
  char buf[32];
  if ( Serial.available() ) {
    int bytes = Serial.readBytesUntil('\n', buf, sizeof buf);
    if ( bytes <= 0 ) return;
    buf[bytes] = 0;
//    Serial.print(bytes); Serial.println(" bytes read");
    if ( bytes >= 2 && buf[0] == '=' ) {
      if ( selfTest.isRunning() ) selfTest.stop();
      unsigned long value = readASCII(buf+1, bytes-1, 10);
      digits.setNumber(value);
      Serial.println(F("OK"));
    } else if ( buf[0] == 'N' ) {
      if ( selfTest.isRunning() ) selfTest.stop();
      digits.setGbar(LOW);
      Serial.println(F("OK"));
    } else if ( buf[0] == 'F' ) {
      if ( selfTest.isRunning() ) selfTest.stop();
      digits.setGbar(HIGH);
      Serial.println(F("OK"));
    } else if ( bytes >= 2 && buf[0] == 't' ) {
      Serial.print(F("Test mode: "));Serial.println(buf[1]);
      softwareSwitch = true;
      selfTest.start(buf[1] - '0');
      Serial.println(F("OK"));
    } else if ( buf[0] == 'c' ) {
      if ( selfTest.isRunning() ) selfTest.stop();
      digits.clear();
      Serial.println(F("OK"));
    } else if ( buf[0] == 'e' ) { //echo
      if ( selfTest.isRunning() ) selfTest.stop();
      Serial.println(buf+1);
    } else if ( buf[0] == 's' ){
      if ( selfTest.isRunning() ) selfTest.stop();
      digits.setString(buf+1);
      Serial.println(F("OK"));
    } else if ( buf[0] == 'S' ){
      if ( selfTest.isRunning() ) selfTest.stop();
      digits.scrollString(300ul,buf+1);
      Serial.println(F("OK"));
    } else if ( buf[0] == 'x' ) {
      if ( selfTest.isRunning() ) selfTest.stop();

      unsigned long value = readASCII(buf+1, bytes-1, 16);
      digits.setValue(value, digits.getNumDigits()*8);
      Serial.println(F("OK"));
    } else {
      Serial.println(F("NAK"));
    }
  }
  
}

unsigned long readASCII(char *buf, int len, int base)
{
  int byte;
  unsigned long value;
  value = 0; 
  for ( int i=0 ; i<len ; i++ ) {
    byte = buf[i];
    if (byte == '\n') break;
    value *= base;
    if ( byte >= 65 && byte <=70 ) {
      value += byte - 65 + 10;
    } else if ( byte >= 97 && byte <= 102 ) {
      value += byte-97 + 10;
    } else if ( byte >= 48 && byte <= 57 ) {
      value += byte - 48;
    } else {
      Serial.print(byte);
      Serial.println(F(": Bogus value."));
    }
  }
//  Serial.print(F("hex value: "));Serial.println(value,HEX);
//  Serial.print(F("readASCII: "));Serial.println(value);
  return value;

}

//
// Display the start up message
//

void hello()
{
  uint8_t bits[32];
  unsigned long pattern = 0x7679383f; //0x7679363f;
  
  // make a list of the bit numbers that are on
  unsigned long pat = pattern;
  int index = 0;
  for ( int i=0 ; i<32 ; i++ ) {
    if ( pat & 1 ) {
      bits[index++] = i;
    }
    pat >>= 1;
  }
  
  // shuffle the bit numbers
  for ( int i=0 ; i<index ; i++ ) {
    int swap = random(i, index);
    uint8_t save = bits[i];
    bits[i] = bits[swap];
    bits[swap] = save;
  }
  // display the message
//  digits.setValue(pattern);
//  delay(3000ul);
  digits.scrollString(150ul,"HELO");
  unsigned long until = millis() + 3000ul;
  while ( millis() < until ) digits.loop();
  
  // dissolve
  pat = pattern;
  for ( int i=0 ; i<index ; i++ ) {
    unsigned long bit = 1ul << bits[i];
    pat = pat & ~bit;
//    Serial.print(bits[i]);Serial.print(" 0x");Serial.print(pat,HEX);Serial.print(" 0x");Serial.print(bit,HEX);Serial.println();
    digits.setValue(pat);
    delay(60ul);
  }
  delay(500ul);
  digits.setValue(pattern);
  delay(500ul);
//  digits.scrollString(150ul,"    ");
//  until = millis() + 3000ul;
//  while ( millis() < until ) digits.loop();

  digits.clear();
}


