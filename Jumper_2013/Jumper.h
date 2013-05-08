#ifndef JUMPER_H
#define JUMPER_H

class Jumper {
  public:
    void setup(void);
    void loop(void);
    void begin(int);
    void extend(void);
    void retract(void);
    bool isExtended(void) { return extended; };
    void off(void);
    void on(void);
    
    void testSetup(void);
    void testLoop(void);
  private:
    int pin;
    bool active;
    bool extended;
    unsigned int testLastState;
    unsigned long testStartTime;
};

#endif
