#ifndef SCOREBOARD_H
#define SCOREBOARD_H

class ScoreBoard {
  public:
    void setup(void);
    void loop(void);
    void begin(HardwareSerial &);
    void clear(void);
  private:
    HardwareSerial *serial;
};


#endif

