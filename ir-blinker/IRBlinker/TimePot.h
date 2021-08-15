#ifndef TIMEPOT_H
#define TIMEPOT_H

class TimePot {
  public:
    void setup(int, bool);
    void loop(void);
    unsigned long getValue(void);
    void setDebug(bool);
    void setTestMode(bool);
  private:
    unsigned long value;
    int pin;
    bool debug;
    bool testMode;
};


#endif
