#ifndef AMBIENTMUSIC_H
#define AMBIENTMUSIC_H

#define MUSIC_MAXFILES 20

class AmbientMusic {
  public:
    void setup(void);
    void loop(void);
    void setMusicObject(Music &);
    unsigned long getDelay(void);
    void start(void);
    void stop(void);
    
    //
    // test mode functions
    //
    void testSetup(void);
    void testLoop(void);
  private:
    void startTune(void);
    Music *music;
    bool enabled;
    bool playing;
    unsigned long nextStartTime;
    int nextTune;
    uint8_t musicFiles[MUSIC_MAXFILES];
    int numMusicFiles;
    unsigned long lastDelay;
    
    unsigned long testStartTime;
    unsigned int testLastValue;
};

#endif

