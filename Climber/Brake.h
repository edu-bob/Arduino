#ifndef BRAKE_H
#define BRAKE_H

/*
 * This holds the value passed to digitalWrite to turn on a brake
 */
#define BRAKE_ON 1
#define BRAKE_OFF 0

class Brake {
  public:
    void setup(int,int,bool);
    void loop(void);

    void setNewType(bool);
    void setFoot(bool);
    bool getFoot(void);
    void setHand(bool);
    bool getHand(void);

    bool isSafe(void);
    bool isOn(void);

  private:
    bool newType;
    int pinHand;
    int pinFoot;

    bool footOn;
    bool handOn;
    void doBrake(unsigned int, bool);
};
#endif

