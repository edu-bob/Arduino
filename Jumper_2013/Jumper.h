#ifndef JUMPER_H
#define JUMPER_H

class Jumper {
  public:
    void setup(void);
    void loop(void);
    void begin(int);
    void jump(void);
    void off(void);
    void on(void);
    
    void testSetup(void);
    void testLoop(void);
  private:
    int pin;
    bool active;
    unsigned int testLastState;
    unsigned long testStartTime;
};

#endif
