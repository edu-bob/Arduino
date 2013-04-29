//
// Bellbox control program
//

#include "bellbox_consts.h"
#include "Box.h"
#include "Command.h"
#include "Music.h"

Command cmd;
Music music;
Box box;
int debug;

char *startupMusic[] = {"sc4","e4","g4","c5",NULL};

// Setup - configure inputs and outputs and initialize the solenoids to "open"

void setup()
{
  int i;
  
  Serial.begin(9600);

  debug = 3;
  cmd.setup();
  cmd.setDebug(debug);
  box.setup();
  music.setup();
  music.setPin(SPEAKER);
  for ( i=0 ; i< 8 ; i++ ) {
    box.doLED((i+1)%8, 15);
  }
  box.doLED(2, 150);
  music.playNotes(startupMusic);
  delay(50);
  box.doBell();
  Serial.print(F("100 Ready, free RAM: "));
  Serial.println(freeRam());
}

void loop()
{
  char *input;
  cmd.loop();
  if ((input = cmd.getCommand()) != NULL ) {
    if ( debug ) {
      Serial.print(F("Command: "));
      Serial.println(input);
    }
    if ( process(input) ) {
      Serial.println(F("400 Bad"));
    } else {
      Serial.println(F("200 OK"));
    }
    cmd.freeCommand(input);
  }
//  if ( debug ) { // flicker the LED if in debug mode
//    box.color(7);
//    delay(10);
//    box.color(0);
//    delay (50);
//  }
  box.loop();
}

int process(char *input)
{
  int led, ms;
  
  char **argv = cmd.getTokens(input);
  int argc,  i;
  
  if ( argv == NULL ) {
    return 0;
  }
  for(argc=0 ; argv[argc]!=NULL ; argc++ ) {
    if ( debug >= 4 ) {
      Serial.print(argc);Serial.print(": ");Serial.println(argv[argc]);
    }
  }
  switch ( input[0] ) {
    case 'h':
      if ( argc > 1 ) {
        box.setHeartbeat(atoi(argv[1]) ? 1 : 0);
      }
      break;
    case 'e': // echo
      for(i=1 ; i<argc ; i++ ) {
        if ( i > 1 ) {
          Serial.print(" ");
        }
        Serial.print(argv[i]);
      }
      Serial.println();
      break;
    case 'L':
      led = argc > 1 ? atoi(argv[1]) : 1;
      ms = argc > 2 ? atoi(argv[2]) : 256;
//      Serial.print("LED: ");Serial.println(led);
      box.doLED(led, ms);
      break;
    case 'B':
      box.doBell();
      break;
    case 'd':
      if ( argc > 1 ) {
        debug = atoi(argv[1]);
      } else {
        debug = !debug;
      }
      Serial.println(debug ? "debug on" : "debug off");
      cmd.setDebug(debug);
      break;
    case 'M':
      music.playNotes(argv+1);
      break;
    default:
      box.doLED(LED_RED,100);
//M a4 c5 e5      Serial.println("400 Bad command character");
      cmd.freeTokens(argv);
      return 1;
  }
  cmd.freeTokens(argv);
  return 0;
}


