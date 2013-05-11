#ifndef SENSOR_H
#define SENSOR_H

class Sensor {
  public:
    void setup();
    void loop();
    int getValue(void);
    void setSampleInterval(unsigned long);
    int recentMaximum(void);
  private:
    int pin;
    unsigned long sampleInterval;
};

#endif

