#ifndef SWITCHES_H
#define SWITCHES_H

#include <WProgram.h>

class Switches {
  public:
    void setup(void);
    void loop(void);
    bool isAutomaticOn(void);
    bool isMusicOn(void);
    unsigned long getAutoSwitchChanges(void);
    unsigned long getMusicSwitchChanges(void);
    //
    // This is used to announce switch changes, if set
    //
    void setMusicObject(Music &);

    //
    // test mode functions
    //
    void testSetup(void);
    void testLoop(void);
  private:
    Music *music;
    int lastAutoState;
    unsigned long lastAutoStateChange;
    
    int lastMusicState;
    unsigned long lastMusicStateChange;
    
    bool getAutoSwitch(void);
    bool getMusicSwitch(void);
    unsigned long autoSwitchChanges;
    unsigned long musicSwitchChanges;
    
    bool testLastStateAuto;
    bool testLastStateMusic;
    unsigned long testStartTime;
};

#endif

