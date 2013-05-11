#ifndef ACCELEROMETER_H
#define ACCELEROMETER_H

class Accelerometer {
  public:
    void setup(void);
    void loop(void);
    void getValues(int *);
    int getValue(void);
  private:
    int16_t real_x;
    int16_t real_y;
    int16_t real_z;
};

#endif

