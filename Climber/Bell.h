#ifndef BELL_H
#define BELL_H

/*
 * This holds the value passed to digitalWrite to turn on the bell
 * ON - Ringing
 * OFF - not ringing
 */
#define BELL_ON 1
#define BELL_OFF 0 

#define BELL_MAX_DELAY 5000L


class Bell {
  public:
    void setup(int, int);
    void loop(void);

    void ring(void);
    void off(void);
    void on(void);
    bool isOn(void);
  private:
    int pin;
    int potPin;
    unsigned long ringTill;
    bool bellIsOn;
};
#endif

