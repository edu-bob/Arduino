#ifndef BUTTON_H
#define BUTTON_H

class Button {
  public:
    void setup(void);
    void loop(void);
    void begin(int, int);
    bool isDown(void);
    bool wasPressed(void);
    bool isChanged(void);
    unsigned long getDelay(void);
    unsigned long getRawPresses(void) { return pressesRaw; };
    unsigned long getFilteredPresses(void) { return pressesFiltered; };
  private:
    bool changed;
    unsigned long pressesRaw;
    unsigned long pressesFiltered;
    unsigned int state(void);
    int pin;
    int delayPin;
    unsigned int lastState;
    unsigned long lastTimePushed;
    bool pushed;
};
#endif

