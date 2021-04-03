#include "Button.h"

Button::Button(byte pin, Command *command, Led *led1, Led *led2, Led *led3, Led *led4) {
  this->pin = pin;
  this->command = command;
  this->led1 = led1;
  this->led2 = led2;
  this->led3 = led3;
  this->led4 = led4;

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
  
  led1->on();
  led2->off();
  led3->on();
  led4->off();
}

void Button::handleButtonReleased() {
  led1->off();
  led2->on();
  led3->off();
  led4->on();
}
