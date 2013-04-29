#ifndef MOTIONDETECTOR_H
#define MOTIONDETECTOR_H

#include <WProgram.h>

class MotionDetector {
  public:
    void setup(void);
    void loop(void);
    bool isDetected(void);
    void startDelay(void);
    void setCycleTime(unsigned long);
    void setMusicObject(Music &);
    //
    // test functions
    //
    void testSetup(void);
    void testLoop(void);
  private:
    Music *music;
    unsigned long lastRead;
    unsigned long sleepUntil;
    bool newMotion;
    unsigned long cycleTime;
    bool ignoring;
    
    unsigned int testLastValue;
    unsigned long testStartTime;
};


#endif


