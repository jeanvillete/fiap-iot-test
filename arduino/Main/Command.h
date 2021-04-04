#ifndef MY_COMMAND_H
#define MY_COMMAND_H

#include <Arduino.h>
#include "PairingCode.h"

class Command {

  const unsigned int COMMAND_FIRST_POSITION = 0;
  const unsigned int COMMAND_THIRD_POSITION = 3;
  const unsigned int COMMAND_PORTION_LENGTH = 4;
  const char COMMAND_COLON = ':';

  private:

    PairingCode *pairingCode;
  
    int parseCommand(String *commandMessage);
    String parseParameters(String *commandMessage);
    void handlePairingCode(String parameters);

  public:

    Command(PairingCode *pairingCode);
    void send(String command);
    void readAndHandleCommands();
    void reset();
  
};

#endif
