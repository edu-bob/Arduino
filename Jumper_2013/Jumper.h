#ifndef JUMPER_H
#define JUMPER_H

class Jumper {
  public:
    void setup(void);
    void loop(void);
    void jump(void);
    void off(void);
    void on(void);
    
    void testSetup(void);
    void testLoop(void);
  private:
    bool active;
    unsigned int testLastState;
    unsigned long testStartTime;
};

#endif
