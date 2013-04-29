#ifndef PIN_H
#define PIN_H


//
// Reserved pins
//   The Waveshield uses digital pins 2,3,4,5 for the DAC and 10,11,12,13 for the SD card
//
//
// Music pins
//
#define DAC1_PIN 2
#define DAC2_PIN 3
#define DAC3_PIN 4
#define DAC4_PIN 5

//
// Flashers pins
//
#define FLASHER_1_PIN 6
#define FLASHER_2_PIN 7

//
// Push Button pin
// 
#define PUSHBUTTON_PIN 8

//
// Tilter pins
//
#define TILTER_PIN 9

//
// Motion Detector pins
//

#define PIR_PIN A0

//
// Ambient Music ti
//
#define AMBIENTMUSIC_DELAY_PIN A1

//
// Mode settings - using analog pins since the digital are mostly all taken
//
#define SWITCHES_AUTO_PIN A2
#define SWITCHES_MUSIC_PIN A3



#endif

