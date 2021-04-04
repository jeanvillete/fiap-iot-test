#include "Button.h"

Button::Button(byte pin, Command *command) {
  this->pin = pin;
  this->command = command;

  init();
}

void Button::init() {
  pinMode(pin, INPUT);

  handleButtonReleased();
  inferCurrentState();
}

bool Button::isNowWithinDelayOfLastStateChange() {
  unsigned long now = millis();
  unsigned long differenceBetweenNowAndLastStateVerificationTime = now - lastStateVerificationTime;

  return differenceBetweenNowAndLastStateVerificationTime <= DELAY_FOR_STATE_VERIFICATION_IN_MILLI_SEC;
}

void Button::updateLastStateVerificationTimeToNow() {
  lastStateVerificationTime = millis();
}

byte Button::readPinAndUpdateCurrentState() {
  byte readPinValue = digitalRead(pin);
  bool stateHasBeenChanged = currentState != readPinValue;
  if (stateHasBeenChanged) {
    if (readPinValue == HIGH) {
      handleButtonPressed();
    } else {
      handleButtonReleased();
    }
  }
  
  return currentState = readPinValue;
}

byte Button::inferCurrentState() {
  if (isNowWithinDelayOfLastStateChange()) {
    return currentState;
  } else {
    updateLastStateVerificationTimeToNow();
  }
  
  return readPinAndUpdateCurrentState();
}

void Button::inferState() {
  inferCurrentState();
}

void Button::handleButtonPressed() {
  command->send(SUBMIT_REQUEST_PAIR_CODE);
}

void Button::handleButtonReleased() {
  
}
