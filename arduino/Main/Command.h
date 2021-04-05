#ifndef MY_COMMAND_H
#define MY_COMMAND_H

#include <Arduino.h>
#include "PairingCode.h"
#include "PairingStatus.h"

class Command {

  const unsigned int COMMAND_FIRST_POSITION = 0;
  const unsigned int COMMAND_THIRD_POSITION = 3;
  const unsigned int COMMAND_PORTION_LENGTH = 4;
  const char COMMAND_COLON = ':';

  private:

    PairingCode *pairingCode;
    PairingStatus *pairingStatus;
  
    int parseCommand(String *commandMessage);
    String parseParameters(String *commandMessage);
    void handlePairingCode(String parameters);
    void handlePairingSucceeded(String parameters);
    void handleEndingPairing(String parameters);

  public:

    Command(PairingCode *pairingCode, PairingStatus *pairingStatus);
    void send(String command);
    void readAndHandleCommands();
    void reset();
  
};

#endif
