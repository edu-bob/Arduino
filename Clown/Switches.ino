/*
 * Manage the mode settings switches
 *
 * Switch 1 - auto/manual (for enabling/disabling motion detection)
 * Switch 2 - music on/off for enabling/disabling ambient music
 */
 
#include "pins.h"


void Switches::setup()
{
  lastAutoState = getAutoSwitch();
  lastAutoStateChange = 0;
  lastMusicState = getMusicSwitch();
  
  lastMusicStateChange = 0;
  autoSwitchChanges = 0;
  musicSwitchChanges = 0;
  music = (Music *)0;

  Serial.print(F("Auto switch: "));Serial.println(isAutomaticOn() ? "ON" : "OFF");
  Serial.print(F("Music switch: "));Serial.println(isMusicOn() ? "ON" : "OFF");
}

/*
 * loop - called on each main loop.
 */
 
void Switches::loop()
{
  int autoState = getAutoSwitch();
  if ( autoState != lastAutoState ) {
    Serial.print(F("Mode switch changed to "));
    Serial.println(autoState ? "auto" : "manual");
    if ( music ) {
      music->playFile(autoState ? "SW1_ON.WAV" : "SW1_OFF.WAV");
//      music->wait();
    }
    lastAutoState = autoState;
    lastAutoStateChange = millis();
    autoSwitchChanges++;
  }
  int musicState = getMusicSwitch();
  if ( musicState != lastMusicState ) {
    Serial.print(F("Music switch changed to "));
    Serial.println(musicState ? "music" : "off");
    if ( music ) {
      music->playFile(musicState ? "SW2_ON.WAV" : "SW2_OFF.WAV");
      music->wait();
    }
    lastMusicState = musicState;
    lastMusicStateChange = millis();
    musicSwitchChanges++;
  }
}

//
// If this is called to set the music controller, it is used to announce switch changes
//

void Switches::setMusicObject(Music &_music)
{
  int i;
  music = &_music;
}

bool Switches::isAutomaticOn()
{
  return getAutoSwitch();
}
bool Switches::isMusicOn()
{
  return getMusicSwitch();
}

bool Switches::getAutoSwitch(void)
{
    unsigned int value = analogRead(SWITCHES_AUTO_PIN);
//    Serial.print(F("Auto Switch: "));Serial.println(analogRead(SWITCHES_AUTO_PIN));
    return value > 512;
}
bool Switches::getMusicSwitch(void)
{
   unsigned int value = analogRead(SWITCHES_MUSIC_PIN);
//    Serial.print(F("Musc Switch: "));Serial.println(analogRead(SWITCHES_MUSIC_PIN));
   return value > 512;
}
unsigned long Switches::getAutoSwitchChanges(void)
{
  return autoSwitchChanges;
}
unsigned long Switches::getMusicSwitchChanges(void)
{
  return musicSwitchChanges;
}

//-------------------------------------------------------
// Test mode functions

void Switches::testSetup(void)
{
  testLastStateAuto = analogRead(SWITCHES_AUTO_PIN) > 512;
  testLastStateMusic = analogRead(SWITCHES_MUSIC_PIN) > 512;
  testStartTime = millis();
}

void Switches::testLoop(void)
{
  bool currentStateAuto = analogRead(SWITCHES_AUTO_PIN) > 512;
  bool currentStateMusic = analogRead(SWITCHES_MUSIC_PIN) > 512;
  if ( currentStateAuto != testLastStateAuto ) {
    Serial.print(millis()-testStartTime);
    Serial.print(F(" Auto switch changed from "));
    Serial.print(testLastStateAuto);
    Serial.print(F(" to "));
    Serial.println(currentStateAuto);
    testLastStateAuto = currentStateAuto;
  }
  if ( currentStateMusic != testLastStateMusic ) {
    Serial.print(millis()-testStartTime);
    Serial.print(F(" Music switch changed from "));
    Serial.print(testLastStateMusic);
    Serial.print(F(" to "));
    Serial.println(currentStateMusic);
    testLastStateMusic = currentStateMusic;
  }
}
