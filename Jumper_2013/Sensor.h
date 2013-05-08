#ifndef SENSOR_H
#define SENSOR_H

class Sensor {
  public:
    void setup();
    void begin(int);
    void loop();
    void setSampleInterval(unsigned long);
    int recentMaximum(void);
  private:
    int pin;
    unsigned long sampleInterval;
};

#endif

