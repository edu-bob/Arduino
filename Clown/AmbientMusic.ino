/*
 * Control the ambient music
 *
 * When enabled, this plays a music file every so often.
 *
 * Music files are files on the top level of the SD card named MUSICNN.WAV
 * where NN is a two-digit integer.  This class stores these internally as
 * an array of integers (uint8_t).  This is done to save RAM.
 */

#include "pins.h"

// Min and Max time delays between ambient music pieces

#define AMBIENT_DELAY_MAX 120000ul
#define AMBIENT_DELAY_MIN 8000ul

#define AMBIENT_ANNOUNCE_INTERVAL 10000

void AmbientMusic::setup()
{
  nextStartTime = millis() + getDelay();
  lastDelay = getDelay();
  enabled = true;
  music = (Music *)0;
  Serial.print(F("Music interval: "));Serial.println(getDelay());
}

void AmbientMusic::loop()
{
  
  // Handle time delay change announcements
  // There are announcement audio files named t%d.wav for values of %d in steps of AMBIENT_ANNOUNCE_INTERVAL/1000
  
  unsigned long currentDelay = getDelay();
  if ( (unsigned int)(currentDelay/AMBIENT_ANNOUNCE_INTERVAL) != (unsigned int)(lastDelay/AMBIENT_ANNOUNCE_INTERVAL) ) {
    char filename[13];
    unsigned int currentMark = (unsigned int)(currentDelay/AMBIENT_ANNOUNCE_INTERVAL);
//    Serial.print(F("currentDelay="));Serial.print(currentDelay);Serial.print(F("  currentMark="));Serial.println(currentMark);
    if ( currentMark < 1 ) {
      strcpy(filename, "t10_undr.wav");
    } else if ( currentMark > 12 ) {
      strcpy(filename, "t120_over.wav");
    } else {
      sprintf(filename,"t%d.wav", currentMark*(AMBIENT_ANNOUNCE_INTERVAL/1000));
    }
    if ( music ) {
      music->playFile(filename);
    }
  }
  lastDelay = currentDelay;
  
  // Check if the current ambient music file ended normally and if so, schedule the next one.
  
  if ( playing && !music->isPlaying() ) {
    playing = false;
//    Serial.println(F("Done."));
    nextStartTime = millis() + getDelay();
  }
  
  // Check if it's time to start another ambient music file
  
  if ( !playing && millis() >= nextStartTime ) {
    if ( enabled ) startTune();
  }
}

void AmbientMusic::stop(void)
{
  if ( music ) {
    music->stop();
  }
  enabled = false;
  playing = false;
}

void AmbientMusic::start(void)
{
  enabled = true;
  nextStartTime = millis() + getDelay();
}

/*
 * setMusicObject - give this class a copy of the Music singleton.
 *
 * Upon receiving a reference to the music object, this function gets the list of ambient
 * music files on the SD card.
 */
 
void AmbientMusic::setMusicObject(Music &_music)
{
  int i;
  music = &_music;
  numMusicFiles = music->getFiles("MUSIC", musicFiles, MUSIC_MAXFILES);
  Serial.print(F("MUSIC files count: "));Serial.println(numMusicFiles);
//  Serial.print(F("Files: "));
//  for(i=0 ; i<numMusicFiles ; i++ ) {
//    Serial.print(musicFiles[i]);Serial.print(" ");
//  }
//  Serial.println("");
  nextTune = 0;
}

/*
 * getDelay - read the delay timing pot and convert to a range AMBIENT_DELAY_MIN to AMBIENT_DELAY_MAX
 */
 
unsigned long AmbientMusic::getDelay(void)
{
  unsigned long pot = analogRead(AMBIENTMUSIC_DELAY_PIN);
  unsigned long delay = AMBIENT_DELAY_MIN + (unsigned long)(pot * (unsigned long)(AMBIENT_DELAY_MAX-AMBIENT_DELAY_MIN)) / 1023ul;
  return (delay > AMBIENT_DELAY_MAX ? AMBIENT_DELAY_MAX : delay);
}

/*
 * Start a tune
 */
 
void AmbientMusic::startTune(void)
{
  char filename[13];
  if ( music ) {
    if ( nextTune >= numMusicFiles ) nextTune = 0;
    sprintf(filename, "MUSIC%02d.WAV", musicFiles[nextTune]);
    music->playFile(filename);
    nextTune++;
    playing = true;
  }
}

//-----------------------------------------------------------------------------
// Test mode functions
//
// The only thing special to AMbientMusic is the time delay pot
//
void AmbientMusic::testSetup(void)
{
  testStartTime = millis();
  testLastValue = analogRead(AMBIENTMUSIC_DELAY_PIN);
}

void AmbientMusic::testLoop(void)
{
  unsigned int currentValue = analogRead(AMBIENTMUSIC_DELAY_PIN);
  if ( abs((int)currentValue-(int)testLastValue ) > 10 ) {
    Serial.print(millis()-testStartTime);
    Serial.print(F(" Ambient delay changed from "));
    Serial.print(testLastValue);
    Serial.print(F(" to "));
    Serial.println(currentValue);
    testLastValue = currentValue;
  }
}

