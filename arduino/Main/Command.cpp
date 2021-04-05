#include "Command.h"
#include "PairingCode.h"

Command::Command(PairingCode *pairingCode, PairingStatus *pairingStatus) {
  this->pairingCode = pairingCode;
  this->pairingStatus = pairingStatus;
}

void Command::send(String command) {
  Serial.println(command);
}

void Command::readAndHandleCommands() {
  if (Serial.available()) {
    String commandMessage = Serial.readString();

    int command = parseCommand(&commandMessage);
    String parameters = parseParameters(&commandMessage);

    switch (command) {
      case 11: 
        handlePairingSucceeded(parameters);
        break;
      case 12: 
        handleEndingPairing(parameters);
        break;
      case 91: 
        handlePairingCode(parameters);
        break;
      default:
        reset();
        break;
    }
  }
}

int Command::parseCommand(String *commandMessage) {
  if (commandMessage->charAt(COMMAND_FIRST_POSITION) != COMMAND_COLON) {
    return 0;
  }
  if (commandMessage->charAt(COMMAND_THIRD_POSITION) != COMMAND_COLON) {
    return 0;
  }
  
  String commandPortionAsString = commandMessage->substring(1,3);

  return commandPortionAsString.toInt();
}

String Command::parseParameters(String *commandMessage) {
  if (commandMessage->length() <= COMMAND_PORTION_LENGTH) {
    return "";
  }

  return commandMessage->substring(4);
}

void Command::handlePairingCode(String parameters) {
  pairingStatus->reset();
  
  pairingCode->printCode(parameters);
}

void Command::handlePairingSucceeded(String parameters) {
  String currentActiveCode = pairingCode->getCode();
  
  pairingStatus->activate(currentActiveCode);

  pairingCode->reset();
}

void Command::handleEndingPairing(String parameters) {
  pairingStatus->reset();
}

void Command::reset() {
  pairingCode->reset();
  pairingStatus->reset();
}
