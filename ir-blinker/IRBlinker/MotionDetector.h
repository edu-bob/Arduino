#ifndef MOTIONDETECTOR_H
#define MOTIONDETECTOR_H

// #include <WProgram.h>

class MotionDetector {
  public:
    void setup(int, bool);
    void loop(void);
    bool isDetected(void);
    void startIgnore(unsigned long);
    void setDebug(bool);
    void setTestMode(bool);
  private:
    unsigned long lastRead;
    unsigned long ignoreUntil;
    bool newMotion;
    bool ignoring;
    int pin;
    bool debug;
    bool testMode;
    unsigned long testModeNextChange;
};


#endif
