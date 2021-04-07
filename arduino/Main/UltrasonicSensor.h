#ifndef ULTR_SON_SENSOR_H
#define ULTR_SON_SENSOR_H

#include <Arduino.h>
#include <Ultrasonic.h>
#include "PairingStatus.h"

class UltrasonicSensor {

  const unsigned int DELAY_INFER_DISTANCE_ON_IN_MILLI_SECS = 500;

  private:
    Ultrasonic *ultrasonic;
    PairingStatus *pairingStatus;

    unsigned long lastTimeDistanceHasBeenChanged;

    void reset();
    bool isNowWithinDelayOfLastStateChange();
    void updateLastTimeDistanceHasBeenChangedToNow();
    bool isPairingStatusInactive();
    void readAndPrintCurrentDistance();
    float readCurrentDistanceInCentimeter();
    void printMessageWithCurrentDistance(float currentDistanceInCentimeter);

  public:
    UltrasonicSensor(Ultrasonic *ultrasonic, PairingStatus *pairingStatus);
    void inferState();
  
};

#endif
