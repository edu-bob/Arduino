#ifndef MOVEBUTTON_H
#define MOVEBUTTON_H

#define MOVEBUTTON_PRESSED 0

#define MOVEBUTTON_DEBOUNCE 20

class MoveButton {
  public:
    void setup(int);
    void loop(void);
    bool getButton(void);
    bool isPressed(void);

  private:
    bool readButton(void);
    int pin;
    bool previouslyPressed;
    bool pressed;
    unsigned long sleepUntil;
};
#endif
