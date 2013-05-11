#ifndef GYROMETER_H
#define GYROMETER_H

class Gyrometer {
  public:
    void setup(void);
    void loop(void);
    void getValues(int *);
    void calibrate(void);
  private:
    int16_t real_x;
    int16_t real_y;
    int16_t real_z;
};

#endif

