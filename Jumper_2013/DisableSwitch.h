#ifndef DISABLESWITCH_H
#define DISABLESWITCH_H

class DisableSwitch {
  public:
    void setup(void);
    void loop(void);
    void begin(int);
    bool isEnabled(void);
    bool isChanged(void);
  private:
    int readSwitch(void);
    int pin;
    int value;
    bool changed;
};

#endif

