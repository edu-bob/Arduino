#ifndef HEARTBEAT_H
#define HEARTBEAT_H

class Heartbeat {
  public:
    void setup(void);
    void loop(void);
  private:
    int state;
    unsigned long nextTime;
};

#endif

