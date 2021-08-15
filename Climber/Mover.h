#ifndef MOVER_H
#define MOVER_H

/*
 * This holds the value passed to digitalWrite to turn on the mover solenoid
 * ON - EXPANDED
 * OFF - CONTRACTED
 */
#define MOVER_ON 1
#define MOVER_OFF 0 

#define MOVER_EXPAND_TIME 1250L

//
// Describes te state of the mover piston
//
#define MOVER_CONTRACTED 0
#define MOVER_EXPANDED 1

class Mover {
  public:
    void setup(int);
    void loop(void);

    int getState(void);
    void setState(int);
    void toggleState(void);
    bool isContracted(void) const { return state==MOVER_CONTRACTED; }
    bool isExpanded(void) const { return state==MOVER_EXPANDED; }

  private:
    int pin;

    int state;  //MOVER_CONTRACTED or MOVER_EXPANDED
};
#endif

