#ifndef EYE_H
#define EYE_H

#include "RandCache.h"

#define EYE_OFF 0
#define EYE_ON 255

enum EyeState { EYE_INVALID, EYE_IDLE, EYE_BLINKING, EYE_ALTERNATING };

// Idle modes
#define EYE_IDLE_MIN 0
enum EyeIdleState { EYE_IDLE_STEADY_FULL=0, EYE_IDLE_GOING_DIM=1, EYE_IDLE_STEADY_DIM=2, EYE_IDLE_GOING_FULL=3 };

// Blinking modes
#define EYE_BLINKING_RAND_KEY 4
#define EYE_BLINKING_MS 120ul
enum EyeBlinkingState { EYE_BLINKING_CLOSED, EYE_BLINKING_REOPEN };

// Alternating modes
#define EYE_ALTERNATING_KEY 5
#define EYE_ALTERNATING_MS 200ul
enum EyeAlternatingState { EYE_ALTERNATING_0, EYE_ALTERNATING_1 };

int eyeIdleMinTimes[] = { 5000, 800, 50, 200 };
//int eyeIdleMinTimes[] = { 6000, 1200, 200, 600 };
int eyeIdleMaxTimes[] =  { 9000, 1200, 200, 600 };

class Eye {
  public:
    void setup(int, char *, RandCache *, int);
    void reset(void);
    void loop(void);
    void setState(EyeState);
    void setDebug(bool);
    bool canBlink(void);
  private:
    int pin;
    int cycle;
    EyeState state;
    char *label;
    RandCache *rand;
    EyeIdleState idleState;
    EyeBlinkingState blinkingState;
    EyeAlternatingState alternatingState;
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

    // Blinking methods
    void loopBlinking(void);
    void startBlinking(void);
    void stopBlinking();
    void setBlinkingState(EyeBlinkingState);

    // Alternating methods
    void loopAlternating(void);
    void startAlternating(void);
    void stopAlternating();
    void setAlternatingState(EyeAlternatingState);
};

#endif
