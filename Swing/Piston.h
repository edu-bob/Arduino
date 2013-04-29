#ifndef PISTON_H
#define PISTON_H

class Piston {
  public:
    void setup(void);
    void loop(void);
    void begin(int);
    void extend(void);
    void retract(void);
  private:
    int pin;
};

#endif

