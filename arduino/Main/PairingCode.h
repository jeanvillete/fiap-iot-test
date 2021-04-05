#ifndef PAIR_CODE_H
#define PAIR_CODE_H

#include <Arduino.h>
#include "Led.h"

class PairingCode {

  const unsigned int DELAY_KEEP_LED_ON_IN_MILLI_SECS = 1000;
  const unsigned int MAX_NUMBER_OF_DIGITS = 4;
  const String EMPTY_CODE = "";

  private:
    String code;

    Led *ledForDigit1;
    Led *ledForDigit2;
    Led *ledForDigit3;
    Led *ledForDigit4;

    byte currentCharAtPosition;
    unsigned long lastTimeLedHasBeenChanged;

    void turnLedsOff();
    boolean isThereAnyCodeToBePrinted();
    bool isNowWithinDelayOfLastStateChange();
    void updateLastTimeLedHasBeenChangedToNow();
    char getDigitToBePrinted();
    void getAndPrintCurrentDigit();
    byte incrementAndGetCurrentCharAtPosition();
    void resetCurrentCharAtPosition();
    byte getCurrentCharAtPosition();
    bool isThereAnyLedOn();
    
  public:

    PairingCode(Led *ledForDigit1, Led *ledForDigit2, Led *ledForDigit3, Led *ledForDigit4);
    void reset();
    void printCode(String code);
    void inferState();
    String getCode();
    
};

#endif
