#ifndef MODESWITCH_H
#define MODESWITCH_H

class ModeSwitch {
  public:
    void setup(void);
    void loop(void);
    int getValue();
  private:
    int readBits();
    int lastValue;
    int goodValue;
    unsigned long lastSampleTime;
    bool bouncing;
};

#endif

