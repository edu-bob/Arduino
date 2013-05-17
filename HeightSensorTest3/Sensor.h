#ifndef SENSOR_H
#define SENSOR_H

class Sensor {
  public:
    void setup();
    void loop();
    void print(void);
    void printHex(void);
    void setComplement(bool _c) { complement = _c; };
    void getValues(int16_t &, int16_t &, int16_t &, int16_t &, int16_t &, int16_t &, int16_t &);
  private:
    int readBytes(uint8_t, uint8_t, uint8_t *, int);
    int16_t temp;
    int16_t gyro_x;
    int16_t gyro_y;
    int16_t gyro_z;
    int16_t acc_x;
    int16_t acc_y;
    int16_t acc_z;
    int pin;
    unsigned long sampleInterval;
    bool complement;
};

#endif

