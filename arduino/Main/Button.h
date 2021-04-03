#ifndef MY_BUTTON_H
#define MY_BUTTON_H

#include <Arduino.h>

class Button {

  const unsigned int DELAY_FOR_STATE_VERIFICATION_IN_MILLIS = 250;
  
  private:
  
    byte pin;
    byte currentState;
    unsigned long lastStateVerificationTime;
    
    void init();
    bool isNowWithinDelayOfLastStateChange();
    void updateLastStateVerificationTimeToNow();
    byte readPinAndUpdateCurrentState();
    byte inferCurrentState();
    
  public:

    Button(byte pin);
    bool isPressed();

};

#endif
