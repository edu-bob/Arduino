#ifndef MOTOR_H
#define MOTOR_H

#define M_STOP 0
#define M_FORWARD 1
#define M_REVERSE 2
#define M_SLOW 1
#define M_FAST 2

class Motor {
  public:
    void setup(void);
    void loop(void);
    void stop(void);
    void forward(int);
    void reverse(int);
  private:
    int state;
    int speed;
};

#endif

