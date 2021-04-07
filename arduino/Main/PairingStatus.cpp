#include "PairingStatus.h"

PairingStatus::PairingStatus(Led *ledStatus) {
  this->ledStatus = ledStatus;

  reset();
}

void PairingStatus::activate(String code) {
  this->code = code;
  
  active = true;  

  ledStatus->on();
}

void PairingStatus::reset() {
  active = false;
  
  ledStatus->off();
}

bool PairingStatus::isActive() {
  return active;
}
