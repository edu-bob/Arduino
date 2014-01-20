#ifndef LIMITSWITCH_H
#define LIMITSWITCH_H

#define LS_DEBOUNCE (unsigned long)20

#define LS_NEAROUT 1
#define LS_OUT 2
#define LS_NEARIN 4
#define LS_IN 8

class LimitSwitch {
  public:
    void setup(void);
    void loop(void);
    unsigned int value(void);
    unsigned int getStableValue(void);
    bool isChanged(void);
    bool isIn(void);
    bool isNearIn(void);
    bool isOut(void);
    bool isNearOut(void);
  private:
    bool changed;
    unsigned int pinValue(int);
    unsigned int lastValue;
    unsigned int stableValue;
    unsigned long lastChangeTime;
    
};

#endif

