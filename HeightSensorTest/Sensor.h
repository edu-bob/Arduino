#ifndef SENSOR_H
#define SENSOR_H

class Sensor {
  public:
    void setup();
    void loop();
    void getRawValues(int *);
    void print(void);
    void setSampleInterval(unsigned long);
    int recentMaximum(void);
    void calibrate();
  private:
    int pin;
    unsigned long sampleInterval;
};

#endif

