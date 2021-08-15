#ifndef BLINKER_H
#define BLINKER_H

#define BLINKER_DEFAULT_DURATION 1000ul

#define LEDS 2

#define LED_ON 0
#define LED_OFF 1

class Blinker {
  public:
    void setup(int, bool);
    void loop(void);
    void setDuration(unsigned long);
    void start(void);
    void stop(void);
    void setDebug(bool);
    void setTestMode(bool);
  private:
    void setStates(int[2]);
    void setState(int, int);
    void setLEDsByState(void);
    static const int ledStates[][LEDS];
    static const unsigned long ledDelays[];
    bool running;
    int states;
    unsigned long duration;
    unsigned long nextChange;
    int state;
    int pinbase;
    bool debug;
    bool testMode;
};


#endif
