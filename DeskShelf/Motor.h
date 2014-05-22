#ifndef MOTOR_H
#define MOTOR_H

#define M_STOP 0
#define M_RUNNING 1

#define M_OUT 1
#define M_IN 2

#define M_SLOW 25
#define M_FAST 100

// milliseconds per step increment

#define M_TIMESTEP 10ul

// Speed step increment

#define M_SPEEDSTEP 2

class Motor {
  public:
    void setup(void);
    void loop(void);
    void stop(void);
    void setSpeed(int);
    void setDirection(int);
    bool isOverCurrent(void);
  private:
    int state;
    int requestSpeed;
    int realSpeed;
    int requestDirection;
    int realDirection;
    unsigned long nextSpeedChange;
    void HWstop(void);
    void HWsetSpeed(int);
    void HWsetDirection(int);
    bool HWisOverCurrent(void);
};

#endif

