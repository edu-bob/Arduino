#ifndef OPTIONS_H
#define OPTIONS_H

#define OPTIONS_COUNT 8

class Options {
  public:
    void setup(void);
    void begin(int);
    void begin(int, int, int, int, int, int, int, int);
    void loop(void);
//    uint8_t getValuesAsSet(void);
//    int *getValuesAsArray(void);
    int getValue(int);
    bool isChanged(void);
  private:
    void begin2(void);
    int pins[OPTIONS_COUNT];
    uint8_t values[OPTIONS_COUNT];
    unsigned long nextSampleTime;
    bool changed;
};

#endif

