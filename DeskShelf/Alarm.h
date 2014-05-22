#ifndef ALARM_H
#define ALARM_H

#define ALARM_OKAY 0
#define ALARM_OVERCURRENT 1

class Alarm {
  public:
    void setup(void);
    void loop(void);
    void setStatus(int);
    int getStatus(void) { return status; }
    void setMusicObject(Music &);
  private:
    int status;
    unsigned long nextTime;
    Music *music;
};

#endif

