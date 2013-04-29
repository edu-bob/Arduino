#ifndef FLASHERS_H
#define FLASHERS_H


#define FLASHER_TEST_DELAY 10000ul
#define FLASHER_TEST_RUNNING_TIME 3000ul
#define FLASHER_FLASH_TIME 300ul

class Flashers {
  public:
    void setup(void);
    void loop(void);
    void start(void);
    void stop(void);
    //
    // Test functions
    //
    void testSetup(void);
    void testLoop(void);
  private:
    bool running;
    unsigned long nextFlashTime;
    unsigned int flashMode;
    
    // Test mode variables
    unsigned long testStartTime;
    unsigned long testNextStartTime;
    unsigned long testNextEndTime;
    unsigned long testNextFlashTime;
    int testFlashMode;
    bool testRunning;
};

#endif

