#ifndef MODESWITCHANALOG_H
#define MODESWITCHANALOG_H

#define MODESWITCHANALOG_ON 512

#define MODESWITCHANALOG_DEBOUNCE 20

class ModeSwitchAnalog {
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
