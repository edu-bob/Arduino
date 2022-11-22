#ifndef EYE_H
#define EYE_H

#include "RandCache.h"

#define EYE_OFF 0
#define EYE_ON 255
#define EYE_IDLE_MIN 0
#define EYE_BLINKING_MS 120ul

enum EyeState { EYE_INVALID, EYE_IDLE, EYE_BLINKING };
enum EyeIdleState { EYE_IDLE_STEADY_FULL=0, EYE_IDLE_GOING_DIM=1, EYE_IDLE_STEADY_DIM=2, EYE_IDLE_GOING_FULL=3 };
#define EYE_BLINK_RAND_KEY 4
enum EyeBlinkingState { EYE_BLINKING_CLOSED, EYE_BLINKING_REOPEN };

int eyeIdleMinTimes[] = { 5000, 800, 50, 200 };
//int eyeIdleMinTimes[] = { 6000, 1200, 200, 600 };
int eyeIdleMaxTimes[] =  { 9000, 1200, 200, 600 };

class Eye {
  public:
    void setup(int, char *, RandCache *);
    void loop(void);
    void setState(EyeState);
    void setDebug(bool);
    bool canBlink(void);
  private:
    int pin;
    EyeState state;
    char *label;
    RandCache *rand;
    EyeIdleState idleState;
    EyeBlinkingState blinkingState;
    int blinks;
    unsigned long actionNextTime;
    unsigned long actionBaseTime;
    unsigned int value;
    unsigned int seed;
    bool debug;

    void setIdleState(EyeIdleState);
    void startIdle(void);
    void loopIdle(void);
    void stopIdle(void);
    void setLED(unsigned int);

    void loopBlinking(void);
    void startBlinking(void);
    void stopBlinking();
    void setBlinkingState(EyeBlinkingState);
};

#endif
