#include "Digits.h"

#include "pins.h"

// The "no such character pattern

#define DIGITS_ERROR 0x49

uint8_t Patterns[] = {
//  '0', 0x3f,
//  '1', 0x06,
//  '2', 0x5b,
//  '3', 0x4f,
//  '4', 0x66,
//  '5', 0x6d,
//  '6', 0x7d,
//  '7', 0x07,
//  '8', 0x77,
//  '9', 0x67,
  '.', 0x80,
  ' ', 0x00,
  '_', 0x08,
  '"', 0x22,
  '-', 0x40,
  '?', 0x47,
  '=', 0x48,
  'A', 0x77,
  'b', 0x7c,
  'C', 0x39,
  'c', 0x58,
  'd', 0x5e,
  'E', 0x79,
  'F', 0x71,
  'g', 0x6f,
  'h', 0x74,
  'H', 0x76,
  'i', 0x04,
  'I', 0x06,
  'J', 0x1e,
  'L', 0x38,
  'O', 0x3f,
  'o', 0x5c,
  'P', 0x73,
  'r', 0x50,
  'S', 0x6d,
  'T', 0x07,
  'u', 0x1c,
  'U', 0x3e,
  'y', 0x6e
};

uint8_t DigitsPattern[10] = {
  0x3F, // 0011 1111 0
  0x06, // 0000 0110 1
  0x5B, // 0101 1011 2
  0x4F, // 0100 1111 3
  0x66, // 0110 0110 4
  0x6D, // 0110 1101 5
  0x7D, // 0111 1101 6
  0x07, // 0000 0111 7
  0x7F, // 0111 1111 8
  0x67  // 0110 0111 9
};

void Digits::setup()
{
  setPins(2,3,4, -1, -1);
  setNumDigits(1);
  shifting = false;
}

void Digits::loop()
{
  // Process any message being shifted through the display
  
  if ( shifting && millis() >= shiftNextTime ) {
    int bits = getBitsForCharacter(shiftBuffer[shiftIndex]);
    if ( shiftBuffer[shiftIndex] != '.' && shiftIndex+1 < shiftLength && shiftBuffer[shiftIndex+1] == '.' ) {
      bits |= 0x80;
      shiftIndex++;
    }
    shiftValue(bits);
    latchValue();
    if ( shiftIndex+1 < shiftLength ) {
      shiftIndex++;
      shiftNextTime = millis() + shiftPace;
//      Serial.print(F("Digits::loop shiftNextTime="));Serial.println(shiftNextTime);
    } else {
      shifting = false;
    }
  }
}

/**
 * setPins - set the Arduino pin numbers for the connection to the shift register
 *
 * serin - serial in (DATA)
 * srck - shift register clock (CLOCK) 
 * rck - register clock
 * g (optional) - gate, set to -1 if not used
 * srclk (optional) - shift register clear, set to -1 if not used
 */
 
void Digits::setPins(int serin, 
  int srck,
  int rck,
  int g,
  int srclr)
{
  pinMode(pin_serin = serin, OUTPUT);
  pinMode(pin_srck = srck, OUTPUT);
  pinMode(pin_rck = rck, OUTPUT);
  
  // Only set the OUTPUT mode on these two pins if they are defined
  if ( (pin_g = g) >= 0 ) {
      pinMode(pin_g, OUTPUT);
  }
  if ( (pin_srclr = srclr) >= 0 ) {
      pinMode(pin_srclr, OUTPUT);
  }
}

void Digits::clear()
{
  if ( pin_srclr > 0 ) {
    setSRCLRbar(LOW);
    setSRCLRbar(HIGH); 
  } else {
    setValue(0, digits*8);
  }
}

void Digits::setNumDigits(int _digits)
{
  digits = _digits;
}
int Digits::getNumDigits()
{
//  Serial.print(F("Digits::getNumDigits="));Serial.println(digits);
  return digits;
}


void Digits::setGbar(int val)
{
  if ( pin_g >= 0 ) {
    digitalWrite(pin_g, val);
  }
}

void Digits::setSRCLRbar(int val)
{
  if ( pin_srclr >= 0 ) {
    digitalWrite(pin_srclr, val);
  }
}
void Digits::shiftValue(uint8_t val)
{
  uint8_t mask = 0x80;
  while ( mask ) {
    digitalWrite(pin_serin, (val & mask) ? HIGH : LOW );
    digitalWrite(pin_srck, LOW);
    digitalWrite(pin_srck, HIGH);
    mask >>= 1;
  }
}
void Digits::latchValue()
{
  digitalWrite(pin_rck, LOW);
  digitalWrite(pin_rck, HIGH);
}

void Digits::setValue(unsigned long val, int bits)
{
  if ( bits == 0 ) {
    bits = digits*8;
  }
//  Serial.print(F("Digits::setValue "));Serial.print(val,HEX);Serial.print(F(" bits="));Serial.println(bits);
  unsigned long mask = 1ul<<(bits-1);
  for ( uint8_t i=0 ; i<bits ; i++ ) {
    digitalWrite(pin_serin, (val & mask) ? HIGH : LOW );
    digitalWrite(pin_srck, LOW);
    digitalWrite(pin_srck, HIGH);
    mask >>= 1;
  }
  latchValue();
}

void Digits::setOneDigit(int digit, bool period)
{
// Serial.print(F("Digits::setOneDigit "));Serial.println(digit);
  if ( digit >= 0 && digit < 10 ) {
    setValue(DigitsPattern[digit] | (period ? 0x80 : 0), 8);
  } else {
    setValue(0x9f, 8);
  }
}

//
// Return the bit pattern for a digit - old style, using DigitsPattern
//

uint8_t Digits::getBitsForDigit(uint8_t digit)
{
  if ( digit >= 0 && digit < 10 ) {
    return DigitsPattern[digit];
  } else {
    return 0x9f;
  }
}

/**
 * getBitsForCharacter - return the bitt pattern for an ASCII character
 *
 * If there is no matching pattern for the upper/lower case version, this looks for
 * a matching pattern in the other case
 */
 
uint8_t Digits::getBitsForCharacter(uint8_t ch)
{
  // Short circuit the digits
  
  if ( ch >= '0' && ch <= '9' ) {
    return DigitsPattern[ch-'0'];
  }
  for ( int i=0 ; i<sizeof Patterns/sizeof *Patterns; i+=2 ) {
//    Serial.print(ch, HEX);Serial.print(F(" cmp "));Serial.println(Patterns[i],HEX);
    if ( Patterns[i] == ch ) {
      return Patterns[i+1];
    }
  }
  uint8_t lch;
  if ( ch >= 'A' && ch <= 'Z' ) {
    lch = ch + ('a' - 'A');
    Serial.print(ch,HEX);Serial.print(F(" becomes "));Serial.println(lch,HEX);
    for ( int i=0 ; i<sizeof Patterns/sizeof *Patterns; i+=2 ) {
      if ( Patterns[i] >= 'a' && Patterns[i] <= 'z' ) {
        if ( Patterns[i] == lch ) {
          return Patterns[i+1];
        }
      }
    }
  }
  uint8_t uch;
  if ( ch >= 'a' && ch <= 'z' ) {
    uch = ch - ('a' - 'A');
    Serial.print(ch,HEX);Serial.print(F(" becomes "));Serial.println(uch,HEX);
    for ( int i=0 ; i<sizeof Patterns/sizeof *Patterns; i+=2 ) {
      if ( Patterns[i] >= 'A' && Patterns[i] <= 'Z' ) {
        if ( Patterns[i] == uch ) {
          return Patterns[i+1];
        }
      }
    }
  }
  return DIGITS_ERROR;
}

void Digits::setNumber(int val)
{
  clear();
  int div = 1;
  unsigned long bits = 0;
  for ( int i=1 ; i<getNumDigits() ; i++ ) div *= 10;
  for ( int i=0 ; i<getNumDigits() ; i++ ) {
    int digit = (val/div) % 10;
    bits = (bits<<8) | getBitsForDigit(digit);
    div /= 10;
  }
  setValue(bits);
}

void Digits::setNumber(char *buf, int len)
{
  clear();
  if ( len==0 ) len = strlen(buf);
  for ( int i=0 ; i<len; i++ ) {
    int bits = getBitsForDigit(buf[i]);
    if ( i+1 < len && buf[i+1] == '.' ) {
      bits |= 0x80;
      i++;
    }
    shiftValue(bits);
  }
  latchValue();
}

void Digits::setString(char *buf, int len)
{
  clear();
  if ( len==0 ) len = strlen(buf);
//  Serial.print(F("Digits::setString len="));Serial.println(len);
  for ( int i=0 ; i<len; i++ ) {
    if ( buf[i] < ' ' ) continue;
    int bits = getBitsForCharacter(buf[i]);
    if ( i+1 < len && buf[i+1] == '.' ) {
      bits |= 0x80;
      i++;
    }
    shiftValue(bits);
    
    // latch in the value for each character over the number of digits
    if ( i >= digits ) {
      latchValue();
    }
  }
  latchValue();
}

void Digits::scrollString(unsigned long pace, char *buf, bool doclear)
{
  int len = strlen(buf);
//  Serial.print(F("Digits::scrollString len="));Serial.println(len);
  if ( len > 0 ) {
    shifting = true;
    strncpy(shiftBuffer, buf, (len >= sizeof shiftBuffer ? sizeof shiftBuffer : len+1));
    shiftIndex = 0;
    shiftLength = len;
    shiftNextTime = millis();
    shiftPace = pace;
    if ( doclear ) clear();
  }
}


