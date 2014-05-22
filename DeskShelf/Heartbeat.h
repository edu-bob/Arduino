#ifndef HEARTBEAT_H
#define HEARTBEAT_H

class Heartbeat {
  public:
    void setup(int);
    void loop(void);
  private:
    int pin;
    int state;
    unsigned long nextTime;
};

#endif

