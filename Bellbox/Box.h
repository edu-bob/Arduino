#ifndef BOX_H
#define BOX_H


#define LED_RED 4
#define LED_GREEN 2
#define LED_BLUE 1
#define LED_YELLOW 6
#define LED_CYAN 3
#define LED_MAGENTA 5
#define LED_WHITE 7
#define LED_OFF 0

#define HEART_INTERVAL 5000L
#define HEART_BLINK 60L
#define HEART_BRIGHTNESS 100

class Box {
  public:
     void setup();
     void loop();
     void led(unsigned char, unsigned char);
     void dimled(unsigned char, unsigned char);
     void color(unsigned char);
     void color(unsigned char, unsigned char, unsigned char);
     void solenoid(unsigned char);
     void doLED(unsigned char);
     void doLED(unsigned char, int);
     void doBell();
     void setHeartbeat(int);
  private:
    void setHeart(int);
     int heartbeat;
     unsigned long lastHeartbeat;
     int heart;
};


#endif

