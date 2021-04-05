#ifndef PAIR_STATUS_H
#define PAIR_STATUS_H

#include <Arduino.h>
#include "Led.h"

class PairingStatus {

  private:

    bool active;
    String code;
    Led *ledStatus;

  public:

    PairingStatus(Led *ledStatus);
    void activate(String code);
    void reset();
  
};

#endif
