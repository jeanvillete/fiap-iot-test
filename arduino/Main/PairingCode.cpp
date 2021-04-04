#include "PairingCode.h"

PairingCode::PairingCode(Led *ledForDigit1, Led *ledForDigit2, Led *ledForDigit3, Led *ledForDigit4) {
  this->ledForDigit1 = ledForDigit1;
  this->ledForDigit2 = ledForDigit2;
  this->ledForDigit3 = ledForDigit3;
  this->ledForDigit4 = ledForDigit4;

  reset();
}

void PairingCode::reset() {
  this->code = EMPTY_CODE;
  
  turnLedsOff();
  resetCurrentCharAtPosition();
  updateLastTimeLedHasBeenChangedToNow();
}

void PairingCode::resetCurrentCharAtPosition() {
  currentCharAtPosition = 0;
}

void PairingCode::turnLedsOff() {
  ledForDigit1->off();
  ledForDigit2->off();
  ledForDigit3->off();
  ledForDigit4->off();
}

void PairingCode::printCode(String code) {
  reset();
  
  this->code = code;
}

void PairingCode::inferState() {
  if (!isThereAnyCodeToBePrinted()) {
    return;
  }

  if (isNowWithinDelayOfLastStateChange()) {
    return;
  } else {
    updateLastTimeLedHasBeenChangedToNow();
  }

  if (isThereAnyLedOn()) {
    turnLedsOff();
    return;
  }

  if (getCurrentCharAtPosition() > MAX_NUMBER_OF_DIGITS) {
    resetCurrentCharAtPosition();
    return;
  }

  getAndPrintCurrentDigit();

  incrementAndGetCurrentCharAtPosition();
}

boolean PairingCode::isThereAnyCodeToBePrinted() {
  return code.length() == 4;
}

bool PairingCode::isNowWithinDelayOfLastStateChange() {
  unsigned long now = millis();
  unsigned long differenceBetweenNowAndLastTimeLedHasBeenChanged = now - lastTimeLedHasBeenChanged;

  return differenceBetweenNowAndLastTimeLedHasBeenChanged <= DELAY_KEEP_LED_ON_IN_MILLI_SECS;
}

void PairingCode::updateLastTimeLedHasBeenChangedToNow() {
  lastTimeLedHasBeenChanged = millis();
}

char PairingCode::getDigitToBePrinted() {
  return code.charAt(currentCharAtPosition);
}

void PairingCode::getAndPrintCurrentDigit() {
  char digit = getDigitToBePrinted();

  switch (digit) {
    case '1':
      ledForDigit1->on();
      break;
    case '2':
      ledForDigit2->on();
      break;
    case '3':
      ledForDigit3->on();
      break;
    case '4':
      ledForDigit4->on();
      break;
    default:
      break;
  }
}

byte PairingCode::incrementAndGetCurrentCharAtPosition() {
  return currentCharAtPosition++;
}

byte PairingCode::getCurrentCharAtPosition() {
  return currentCharAtPosition;
}

bool PairingCode::isThereAnyLedOn() {
  return ledForDigit1->isOn() ||
          ledForDigit2->isOn() ||
          ledForDigit3->isOn() ||
          ledForDigit4->isOn();
}
