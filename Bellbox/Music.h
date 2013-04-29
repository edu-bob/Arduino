#ifndef MUSIC_H
#define MUSIC_H


//  Language
//  
//  A "note" as passed to playNote has two parts:
//  1) an optional duration specifier:
//     s - sixteenth note
//     8 - eigth note
//     q - quarter note (the default if omitted)
//     h - half note
//     w - whole note
//     a) a duration character can be followed  by a dot to denote a dotted note
//     b) a duration can be followed  by a '3' to denote a note in a triplet
//  2) A tone specifier as listed in the notes[] array in the cpp file, three parts
//     a) the note name a b c d e f g
//     b) an optoinal s for sharp and b for flat
//     c) an octave 1-6
//     
//  Tones range from b0 to eb8, c4 is middle C
//  

typedef struct {
  char *name;
  int value;
} note_t;

class Music {
  public:
    Music();
    ~Music();
    void setup();
    void loop();
    void setPin(int);
    bool playNote(char *);
    bool playNotes(char **);

  private:
    int outPin;
    int defaultDuration;
    static const note_t notes[];
    static const note_t duration[];
    int isDuration(char);
    int isNote(char *);
};

#endif

