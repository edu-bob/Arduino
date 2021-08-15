#ifndef LIMITSWITCH_H
#define LIMITSWITCH_H

/*
 * This holds the value seen by digitalRead when the limitswitch is tripped
 */
#define LIMITSWITCH_ON 0

#define LIMITSWITCH_DEBOUNCE 20


class LimitSwitch {
  public:
    void setup(const char *,int);
    void loop(void);

    bool isOn(void);
    bool changedToOn(void);
    
  private:
    bool readSwitch(void);
    
    int pin;
    const char *whoami;
    bool previous;
    bool current;

    unsigned long sleepUntil;

    bool switchedToOn;
};

#endif
