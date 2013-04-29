#ifndef MUSIC_H
#define MUSIC_H

#include <WProgram.h>

class Music {
  public:
    void setup();
    void loop();
    bool playFile(const char *);
    bool play1(FatReader &);
    void playR(FatReader &, int);
    void lsR(FatReader &, int);
    void wait(void);
    void stop(void);
    bool isPlaying(void);
    int getFiles(char *, uint8_t *, int);
  private:
    void sdErrorCheck(void);
    WaveHC wave;      // This is the only wave (audio) object, since we will only play one at a time
    SdReader card;    // This object holds the information for the card
    FatVolume vol;    // This holds the information for the partition on the card
    FatReader root;   // This holds the information for the filesystem on the card
    FatReader file;
};


#endif


