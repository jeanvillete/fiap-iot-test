#include "UltrasonicSensor.h"

UltrasonicSensor::UltrasonicSensor(Ultrasonic *ultrasonic, PairingStatus *pairingStatus) {
  this->ultrasonic = ultrasonic;
  this->pairingStatus = pairingStatus;
}

void UltrasonicSensor::inferState() {
  if (isPairingStatusInactive()) {
    return;
  }

  if (isNowWithinDelayOfLastStateChange()) {
    return;
  } else {
    updateLastTimeDistanceHasBeenChangedToNow();
  }

  readAndPrintCurrentDistance();
}

void UltrasonicSensor::reset() {
  updateLastTimeDistanceHasBeenChangedToNow();
}

bool UltrasonicSensor::isNowWithinDelayOfLastStateChange() {
  unsigned long now = millis();
  unsigned long differenceBetweenNowAndLastTimeDistanceHasBeenChanged = now - lastTimeDistanceHasBeenChanged;

  return differenceBetweenNowAndLastTimeDistanceHasBeenChanged <= DELAY_INFER_DISTANCE_ON_IN_MILLI_SECS;
}

void UltrasonicSensor::updateLastTimeDistanceHasBeenChangedToNow() {
  lastTimeDistanceHasBeenChanged = millis();
}

bool UltrasonicSensor::isPairingStatusInactive() {
  return !pairingStatus->isActive();
}

void UltrasonicSensor::readAndPrintCurrentDistance() {
  float currentDistanceInCentimeter = readCurrentDistanceInCentimeter();

  printMessageWithCurrentDistance(currentDistanceInCentimeter);
}

float UltrasonicSensor::readCurrentDistanceInCentimeter() {
  return ultrasonic->convert(ultrasonic->timing(), Ultrasonic::CM);
}

void UltrasonicSensor::printMessageWithCurrentDistance(float currentDistanceInCentimeter) {
  String message = "{ \"device\": { \"name\": \"sensor ultrasonico\", \"model\": \"hc-sr04\", \"distance\": { \"unit\": \"cm\", \"value\":";
  message += currentDistanceInCentimeter;
  message += "} } }";
  
  Serial.println(message);
}
