#ifndef EYE_H
#define EYE_H

#include "RandCache.h"

#define EYE_OFF 0
#define EYE_ON 255

enum EyeMode { EYE_INVALID, EYE_IDLE, EYE_BLINKING, EYE_ALTERNATING };

// Idle modes
// EYE_IDLE_MIN is how dim the eyes go when pulsing in idle mode
#define EYE_IDLE_MIN 0
enum EyeIdleState { EYE_IDLE_STEADY_FULL=0, EYE_IDLE_GOING_DIM=1, EYE_IDLE_STEADY_DIM=2, EYE_IDLE_GOING_FULL=3 };

// open, closing, closed, opening
int eyeIdleMinTimes[] = { 5000,  800,  50, 200 };
int eyeIdleMaxTimes[] = { 9000, 1200, 200, 600 };

// Blinking modes
#define EYE_BLINKING_RAND_KEY 4  // RandCache key, if needs a random variable
#define EYE_BLINKING_MS 120ul    // How long the blink lasts
enum EyeBlinkingState { EYE_BLINKING_CLOSED, EYE_BLINKING_REOPEN };

// Alternating modes - only used at power-on
#define EYE_ALTERNATING_KEY 5  // RandCache key, if needs a random variable
#define EYE_ALTERNATING_MS 500ul  // initial on time when alternating
#define EYE_ALTERNATING_LOOPS 100 // max loops for alternating, though fewer may be used
enum EyeAlternatingState { EYE_ALTERNATING_0, EYE_ALTERNATING_1 };

// One of these for each eye
class Eye {
  public:
    void setup(int, char *, RandCache *, int);
    void reset(void);
    void loop(void);
    void setMode(EyeMode);
    void setDebug(bool);
    bool canBlink(void);
  private:
    int pin;
    int cycle;
    EyeMode mode;
    char *label;
    RandCache *rand;
    unsigned long blink_ms;
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
