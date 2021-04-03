#include "Button.h"

Button::Button(byte pin) {
  this->pin = pin;

  init();
}

void Button::init() {
  pinMode(pin, INPUT);
  
  inferCurrentState();
}

bool Button::isNowWithinDelayOfLastStateChange() {
  unsigned long now = millis();
  unsigned long differenceBetweenNowAndLastStateVerificationTime = now - lastStateVerificationTime;

  return differenceBetweenNowAndLastStateVerificationTime <= DELAY_FOR_STATE_VERIFICATION_IN_MILLIS;
}

void Button::updateLastStateVerificationTimeToNow() {
  lastStateVerificationTime = millis();
}

byte Button::readPinAndUpdateCurrentState() {
  byte readPinValue = digitalRead(pin);
  bool stateHasBeenChanged = currentState != readPinValue;
  if (stateHasBeenChanged) {
    Serial.println("State has been changed");

    if (readPinValue == HIGH) {
      Serial.println("Button has been pushed.");
    } else {
      Serial.println("Button has been released.");
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

bool Button::isPressed() {
  return inferCurrentState() == HIGH;
}
