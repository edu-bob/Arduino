#include "Music.h"

const note_t Music::notes[] = {
  { "b0", 31 },
  { "c1", 33 },
  { "cs1", 35 },
  { "dd1", 35 },
  { "d1", 37 },
  { "ds1", 39 },
  { "eba", 39 },
  { "e1", 41 },
  { "f1", 44 },
  { "fs1", 46 },
  { "gg1", 46 },
  { "g1", 49 },
  { "gs1", 52 },
  { "ab1", 52 },
  { "a1", 55 },
  { "as1", 58 },
  { "bb1", 58 },
  { "b1", 62 },
  { "c2", 65 },
  { "cs2", 69 },
  { "dd2", 69 },
  { "d2", 73 },
  { "ds2", 78 },
  { "eb2", 78 },
  { "e2", 82 },
  { "f2", 87 },
  { "fs2", 93 },
  { "gb2", 93 },
  { "g2", 98 },
  { "gs2", 104 },
  { "ab2", 104 },
  { "a2", 110 },
  { "as2", 117 },
  { "bb2", 117 },
  { "b2", 123 },
  { "c3", 131 },
  { "cs3", 139 },
  { "dd3", 139 },
  { "d3", 147 },
  { "ds3", 156 },
  { "eb3", 156 },
  { "e3", 165 },
  { "f3", 175 },
  { "fs3", 185 },
  { "gb3", 185 },
  { "g3", 196 },
  { "gs3", 208 },
  { "ab3", 208 },
  { "a3", 220 },
  { "as3", 233 },
  { "bb3", 233 },
  { "b3", 247 },
  { "c4", 262 },
  { "cs4", 277 },
  { "dd4", 277 },
  { "d4", 294 },
  { "ds4", 311 },
  { "eb4", 311 },
  { "e4", 330 },
  { "f4", 349 },
  { "fs4", 370 },
  { "gb4", 370 },
  { "g4", 392 },
  { "gs4", 415 },
  { "ab4", 415 },
  { "a4", 440 },
  { "as4", 466 },
  { "bb4", 466 },
  { "b4", 494 },
  { "c5", 523 },
  { "cs5", 554 },
  { "dd5", 554 },
  { "d5", 587 },
  { "ds5", 622 },
  { "eb5", 622 },
  { "e5", 659 },
  { "f5", 698 },
  { "fs5", 740 },
  { "gb5", 740 },
  { "g5", 784 },
  { "gs5", 831 },
  { "ab5", 831 },
  { "a5", 880 },
  { "as5", 932 },
  { "bb5", 932 },
  { "b5", 988 },
  { "c6", 1047 },
  { "cs6", 1109 },
  { "dd6", 1109 },
  { "d6", 1175 },
  { "ds6", 1245 },
  { "eb6", 1245 },
  { "e6", 1319 },
  { "f6", 1397 },
  { "fs6", 1480 },
  { "gb6", 1480 },
  { "g6", 1568 },
  { "gs6", 1661 },
  { "ab6", 1661 },
  { "a6", 1760 },
  { "as6", 1865 },
  { "bb6", 1865 },
  { "b6", 1976 },
  { "c7", 2093 },
  { "cs7", 2217 },
  { "dd7", 2217 },
  { "d7", 2349 },
  { "ds7", 2489 },
  { "eb7", 2489 },
  { "e7", 2637 },
  { "f7", 2794 },
  { "fs7", 2960 },
  { "gb7", 2960 },
  { "g7", 3136 },
  { "gs7", 3322 },
  { "ab7", 3322 },
  { "a7", 3520 },
  { "as7", 3729 },
  { "bb7", 3729 },
  { "b7", 3951 },
  { "c8", 4186 },
  { "cs8", 4435 },
  { "dd8", 4435 },
  { "d8", 4699 },
  { "ds8", 4978 },
  { "eb8", 4978 }
};

const note_t Music::duration[] = {
  { "s", 16 },
  { "8", 8 },
  { "q", 4 },
  { "h", 2 },
  { "w", 1 }
};

Music::Music()
{
  setup();
}

Music::~Music()
{
}

void Music::setup()
{
  defaultDuration = 1000/isDuration('q');
}

void Music::setPin(int pin)
{
  outPin = pin;
}

bool Music::playNote(char *notestr)
{
  int index = 0;
  bool dotted = false;
  bool triplet = false;
  
  int duration, note;
  if ( (duration = isDuration(notestr[index]) )) {
    index++;
    if ( notestr[index] == '.' ) {
      dotted = true;
      index++;
    } else if ( notestr[index] == '3' ) {
      triplet = true;
      index++;
    }
  }
  
  if ( strcmp(notestr+index, "r") == 0 ) {
    note = 0;
  } else if ( (note = isNote(notestr+index)) == 0 ) {
    Serial.print(F("400 Bad tone specifier: "));Serial.println(notestr+index);
    return false;
  }

  int noteDuration;
  if ( duration ) {
    noteDuration = 1000/duration;
    if ( dotted ) {
      noteDuration += noteDuration/2;
    }
    if ( triplet ) {
      noteDuration = noteDuration/2 * 3;
    }
    defaultDuration = noteDuration;
  } else {
    noteDuration = defaultDuration;
  }
  
//  Serial.print(note);Serial.print(" ");Serial.println(noteDuration);
  tone(outPin, note, noteDuration);

  // The following few lines come from http://www.arduino.cc/en/Tutorial/Tone
  // to distinguish the notes, set a minimum time between them.
  int pauseBetweenNotes = noteDuration * 1.30;
  delay(pauseBetweenNotes);
  // stop the tone playing:
  noTone(outPin);
  
  return true;
}

bool Music::playNotes(char **tune)
{
  int i;
  for ( i=0 ; tune[i] != NULL ; i++ ) {
    if ( !playNote(tune[i]) ) {
      return false;
    }
  }
  return true;
}

int Music::isDuration(char timechar)
{
  int i;
  for ( i=0 ; i<sizeof duration/sizeof(note_t) ; i++ ) {
    if ( timechar == duration[i].name[0] ) {
      return duration[i].value;
    }
  }
  return 0;
}

int Music::isNote(char *notestr)
{
  int i;
  for ( i=0 ; i<sizeof notes/sizeof(note_t) ; i++ ) {
    if ( strcmp(notestr, notes[i].name ) == 0 ) {
      return notes[i].value;
    }
  }
  return 0;
}

