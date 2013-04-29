#ifndef COMMAND_H
#define COMMAND_H

#include <stdint.h>

#define NUM_COMMANDS 5
#define MAX_TOKENS 32
#define MAX_TOKEN_LEN 6
#define MAX_COMMAND_LEN 80

class Command {
  public:
    Command();
    ~Command();
    void setup();
    void loop();
    char *getCommand();
    void freeCommand(char *);
    void setDebug(int);
    char **getTokens(char *);
    void freeTokens(char **);
  private:
    // character input buffer
    char *inputPtr;
    char *input;
    void addToInput(char);
  
    // complete commands
    char *commands[NUM_COMMANDS];
    int commandPut;
    int commandGet;
    int commandQueueLength;
    
    void addToCommands(char *);

    int debug;
};

#endif

