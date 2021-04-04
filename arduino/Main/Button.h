#ifndef MY_BUTTON_H
#define MY_BUTTON_H

#include <Arduino.h>
#include "Command.h"

class Button {

  const unsigned int DELAY_FOR_STATE_VERIFICATION_IN_MILLI_SEC = 250;
  const String SUBMIT_REQUEST_PAIR_CODE = ":19:";
  
  private:
  
    byte pin;
    byte currentState;
    unsigned long lastStateVerificationTime;
    Command *command;
    
    void init();
    bool isNowWithinDelayOfLastStateChange();
    void updateLastStateVerificationTimeToNow();
    byte readPinAndUpdateCurrentState();
    byte inferCurrentState();
    
  public:

    Button(byte pin, Command *command);
    void inferState();
    
    void handleButtonPressed();
    void handleButtonReleased();

};

#endif
