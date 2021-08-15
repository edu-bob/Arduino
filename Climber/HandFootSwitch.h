#ifndef HANDFOOTSWITCH_H
#define HANDFOOTSWITCH_H

#define FOOT_SW 0
#define HAND_SW 1
#define NO_SW 2

#define HANDFOOT_IGNORE_TIME 150

#define HANDFOOT_ON 1

class HandFootSwitch {
  public:
    void setup(int,int);
    void loop(void);

    int getSetting(void);
    bool isFoot(void);
    bool isHand(void);

  private:
    int pinFoot;
    int pinHand;
    int previous;
    int current;
    unsigned long ignoreUntil;
};
#endif
