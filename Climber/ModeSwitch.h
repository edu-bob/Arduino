#ifndef MODESWITCH_H
#define MODESWITCH_H

#define MODESWITCH_ON 0

#define MODESWITCH_DEBOUNCE 20

class ModeSwitch {
  public:
    void setup(const char *, int);
    void loop(void);
    bool isOn(void) const { return current; }
    bool isOff(void) const { return !current; };
    bool changedToOn(void) { return switchedToOn; }

  private:
    const char *whoami;
    bool readSwitch(void);
    bool current;
    bool previous;
    bool switchedToOn;
    int pin;
    unsigned long sleepUntil;
    void showStatus(void);

};
#endif
