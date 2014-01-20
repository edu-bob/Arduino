#ifndef POT_H
#define POT_H

class Pot {
  public:
    void setup(void);
    void loop(void);
    int getValue(void);
    bool isChanged(void);
  private:
    bool changed;
    int readValue(void);
    int goodValue;
    unsigned long lastSampleTime;
};

#endif

