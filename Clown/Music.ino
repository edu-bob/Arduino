
#include "pins.h"
#include <stdlib.h>

dir_t dirBuf;     // buffer for directory reads

/**
 * Music manager.  A lot of this code comes from the WaveHC sample programs.
 */

void Music::setup()
{
  pinMode(DAC1_PIN, OUTPUT);
  pinMode(DAC2_PIN, OUTPUT);
  pinMode(DAC3_PIN, OUTPUT);
  pinMode(DAC4_PIN, OUTPUT);

  //  if (!card.init(true)) { //play with 4 MHz spi if 8MHz isn't working for you
  if (!card.init()) {         //play with 8 MHz spi (default faster!)  
    Serial.println(F("Card init. failed!"));  // Something went wrong, lets print out why
    sdErrorCheck();
    while(1);                            // then 'halt' - do nothing!
  }

  // enable optimize read - some cards may timeout. Disable if you're having problems
//  card.partialBlockRead(true);

  // Look for a FAT partition!
  uint8_t part;
  for (part = 0; part < 5; part++) {     // we have up to 5 slots to look in
    if (vol.init(card, part)) 
      break;                             // we found one, lets bail
  }
  if (part == 5) {                       // if we ended up not finding one  :(
    Serial.println(F("No valid FAT partition!"));
    sdErrorCheck();      // Something went wrong, lets print out why
    while(1);                            // then 'halt' - do nothing!
  }

  // Try to open the root directory
  if (!root.openRoot(vol)) {
    Serial.print(F("Can't open root dir!")); Serial.println("");
    while(1);                             // then 'halt' - do nothing!
  }

  if ( 0 ) {
    Serial.println(F("Files found:"));
    lsR(root, 0);
  }
}

/*
 * loop - called from the main loop.
 *
 * Nothing to do here.
 */
 
void Music::loop()
{
}

/*
 * playFile - play a file by its name
 *
 * Note: in the sample code, "FatReader file" was a local variable which falls out of scope when this
 *  function returns, causing the vave object to lose it, and the music to not play.  Now it's a member
 *  variable in the "Music" object and does not fall out of scope as long as the caller keeps the original
 *  Music object in scope.
 */

bool Music::playFile(const char *name)
{
  Serial.print(F("Playing: "));
  Serial.println(name);
  
  if ( wave.isplaying ) {
    wave.stop();
  }
  
  if (!file.open(root, (char *)name)) {
    Serial.print(name);
    Serial.println(F(": file.open failed")); 
    return false;
  }

  if (!wave.create(file)) {            // Figure out, is it a WAV proper?
    Serial.print(name);
    Serial.println(F(": not a valid WAV file"));
    return false;
  } 
  wave.play();
  return true;
}

void Music::wait(void)
{
  while (wave.isplaying) {           // playing occurs in interrupts, so we print dots in realtime
    delay(100);
  }
}

void Music::stop(void)
{
    if ( wave.isplaying ) {
      wave.stop();
    }
}
bool Music::isPlaying(void)
{
    return wave.isplaying;
}

/*
 * getFilesMatching - get files from the top-level directory maching a prefix
 *
 * Files are assumed to be named {prefix}NN.WAV and this function returns
 * an array of uint8_t's contaiing the NN values found
 */
 
int Music::getFiles(char *prefix, uint8_t *result, int maxResults)
{
  int nextFile = 0;
  int len = strlen(prefix);
  dir_t dir;

//  Serial.print("maxResults=");Serial.println(maxResults);
  root.rewind();

  while (root.readDir(dir) > 0) { 
    if ( !DIR_IS_FILE(dir) ) continue;
    if ( memcmp(&dir.name, prefix, len) == 0 ) {
//    printName(dir);Serial.println("");
      *result++ = atoi((const char *)&dir.name[len]);   
      if ( ++nextFile >= maxResults ) break;
    }
  }
  
  return nextFile;
}


/*
 * list recursively - possible stack overflow if subdirectories too nested
 */
void Music::lsR(FatReader &d, int dirLevel)
{
  int8_t r;                     // indicates the level of recursion

  while ((r = d.readDir(dirBuf)) > 0) { 
    if (dirBuf.name[0] == '.') 
      continue;

    for (uint8_t i = 0; i < dirLevel*2; i++) Serial.print(' '); 
    printName(dirBuf);          // print the name of the file we just found
    Serial.println();           // and a new line

    if (DIR_IS_SUBDIR(dirBuf)) {   // we will recurse on any direcory
      FatReader s;                 // make a new directory object to hold information
      if (s.open(vol, dirBuf)) 
        lsR(s, dirLevel+1);                    // list all the files in this directory now!
    }
  }
  sdErrorCheck();                  // are we doing OK?
}

/////////////////////////////////// HELPERS
/*
 * print error message and halt if SD I/O error, great for debugging!
 */
void Music::sdErrorCheck(void)
{
  if (!card.errorCode()) return;
  Serial.print(F("\n\rSD I/O error: "));
  Serial.print(card.errorCode(), HEX);
  Serial.print(", ");
  Serial.println(card.errorData(), HEX);
  while(1);
}

