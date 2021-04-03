#ifndef MY_BUTTON_H
#define MY_BUTTON_H

#include <Arduino.h>
#include "Led.h"

class Button {

  const unsigned int DELAY_FOR_STATE_VERIFICATION_IN_MILLI_SEC = 250;
  
  private:
  
    byte pin;
    byte currentState;
    unsigned long lastStateVerificationTime;
    Led *led1;
    Led *led2;
    Led *led3;
    Led *led4;
    
    void init();
    bool isNowWithinDelayOfLastStateChange();
    void updateLastStateVerificationTimeToNow();
    byte readPinAndUpdateCurrentState();
    byte inferCurrentState();
    
  public:

    Button(byte pin, Led *led1, Led *led2, Led *led3, Led *led4);
    void inferState();
    
    void handleButtonPressed();
    void handleButtonReleased();

};

#endif
