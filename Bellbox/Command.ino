//
// Process commands from the host
//

#include <ctype.h>

Command::Command()
{
  setup();
}

Command::~Command()
{
}

void Command::setup()
{
  Serial.begin(9600);
  input = NULL;
  commandPut = 0;
  commandGet = 0;
  commandQueueLength = 0;
  debug = 0;
}

void Command::loop()
{
  while ( Serial.available() ) {
    char c = Serial.read();
    if ( debug >= 5 ) {
      Serial.print(F("100 char: "));
      if ( c == '\012' ) {
        Serial.println(F("NL"));
      } else {
        Serial.println((int)c, OCT);
      }
    }
    
    // Is the end of a command line?
    
    if ( c == '\012' || c == ';' ) {
      if ( strlen(input) > 0 ) {
        if ( debug >= 4 ) {
          Serial.print(F("100 Command line complete: "));Serial.println(input);
        }
         addToCommands(input);
         input = NULL;
      }
    } else {
      addToInput(c);
    }
  }
}

/**
 * Add a complete command string to the list of available commands.  This wraps the "commands"
 * array around and checks for overlap with the consumer end.  Probably should keep reallocating
 * the commands list but I have found the AVR malloc management to be flakey.
 */
 
void Command::addToCommands(char *cmd)
{
  if ( commandQueueLength == NUM_COMMANDS ) { 
    Serial.println(F("500 Ran out of room to put a received command"));
    return;
  }
  commands[commandPut] = cmd;
  commandPut = (commandPut+1) % NUM_COMMANDS;
  commandQueueLength++;
}

void Command::addToInput(char c)
{
  if ( input == NULL ) {
    if ((input = (char *)malloc(MAX_COMMAND_LEN)) == NULL ) {
      Serial.println(F("500 malloc failed on allocating input buffer"));
      return;
    }
    inputPtr = input;
  }
  if ( inputPtr >= input + MAX_COMMAND_LEN - 2 ) {
    Serial.println(F("500 Ran out of command buffer space: command line too long"));
    return;
  }
  *inputPtr++ = c;
  *inputPtr = '\0';
}

void Command::setDebug(int val)
{
  debug = val;
}

char *Command::getCommand()
{
  if ( commandQueueLength == 0 ) {
    return NULL;
  }
  commandQueueLength--;
  char *cmd = commands[commandGet];
  commandGet = (commandGet+1) % NUM_COMMANDS;
  return cmd;
}

void Command::freeCommand(char *cmd)
{
    free(cmd);
}

/**
 * Break a String in to individual tokens
 *
 * This returns a dynamically allocated array of pointers to dynamically allocated character arrays
 * which must be freed via freeTokens
 */
 
char **Command::getTokens(char *input)
{
    char **tokens;
    int state = 0;
    int tokenindex = 0;
    int token = 0;
    int i;
    
    // Allocate the array of pointers to resulting tokens.  Always allow for a NULL at the end
    int bytes = sizeof (char *) * (MAX_TOKENS+1);
    if ( debug >= 3 ) {
      Serial.print(F("Token array bytes: "));Serial.println(bytes);
    }
    tokens = (char **)malloc(bytes);
    if ( tokens == NULL ) {
      Serial.println(F("500 Token array malloc failed"));
      return NULL;
    }
    
    for ( i=0 ; i<strlen(input) ;  ) {
//      Serial.print("State: ");Serial.print(state);Serial.print(" char: ");Serial.println(i);
      // If we're out of space for more tokens, bail on scanning the string
      if ( token >= MAX_TOKENS-1  ) {
          Serial.println(F("400 Ran out of token space"));
          tokens[token] = NULL;
          return tokens;
      }
      
      switch(state) {
        case 0: // skipping spaces, looking for a new token
          if ( isspace(input[i]) ) {
            i++;
            break;
          }
          bytes = sizeof (char) * MAX_TOKEN_LEN;
          if ( debug >= 3 ) {
            Serial.print(F("Token array buffer bytes: "));Serial.println(bytes);
          }
          tokens[token] = (char *)malloc(bytes);
          if ( tokens[token] == NULL ) {
            Serial.print(F("500: Token storage malloc failed, token "));
            Serial.print(token);
            Serial.print(F(", bytes: "));
            Serial.println(bytes);
            return tokens;
          }
          tokenindex = 0;
          state = 1;
          break;
        case 1: // looking for the end of a token
          if ( isspace(input[i]) ) { // end of a token
            tokens[token][tokenindex] = 0;
            if ( debug >= 3 ) {
              Serial.print(F("End of a token, tokenindex= "));Serial.print(tokenindex);
              Serial.print(F(" token: "));Serial.println(tokens[token]);
            }
            token++;
            state = 0;
          } else { // extend this token, if there's room for another character
            if ( tokenindex < MAX_TOKEN_LEN-1 ) {
              tokens[token][tokenindex++] = input[i];
            }
            i++;
          }
          break;
      }  
    }
    // at the end, we might need to wrap up the final token
    if ( state == 1 ) {
      tokens[token++][tokenindex] = '\0';
    }
    
    // This should always be true since we allocated one extra slot at the end but did not
    // allow it to be used.
    
    if ( token <= MAX_TOKENS ) {
      tokens[token] = NULL;
    }
    if ( debug ) {
      Serial.print(F("At end token="));Serial.println(token);
    }
    return tokens;
}

void Command::freeTokens(char **tokens)
{
  int i;
  for ( i=0 ; i<MAX_TOKENS && tokens[i] != NULL ; i++ ) {
    free(tokens[i]);
  }
  free(tokens);
}


