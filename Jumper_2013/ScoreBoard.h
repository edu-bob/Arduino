#ifndef SCOREBOARD_H
#define SCOREBOARD_H

class ScoreBoard {
  public:
    void setup(void);
    void loop(void);
    void begin(HardwareSerial &);
    void clear(void);
    void show(int);
    void show(char *);
    void scroll(char *);
    void on(void);
    void off(void);
    void runTest(int);
    void pattern(unsigned long);
  private:
    HardwareSerial *serial;
};


#endif

