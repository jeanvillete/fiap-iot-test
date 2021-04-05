#include "Led.h"
#include "Button.h"
#include "Command.h"
#include "PairingCode.h"
#include "PairingStatus.h"

#define BTN_COD_PAIR_PIN 13
#define LED_PAIR_COD_DIG_1_PIN 12
#define LED_PAIR_COD_DIG_2_PIN 11
#define LED_PAIR_COD_DIG_3_PIN 10
#define LED_PAIR_COD_DIG_4_PIN 9
#define LED_PAIR_STATUS_PIN 8

const unsigned int SERIAL_BAUDS = 9600;

const Led led1(LED_PAIR_COD_DIG_1_PIN);
const Led led2(LED_PAIR_COD_DIG_2_PIN);
const Led led3(LED_PAIR_COD_DIG_3_PIN);
const Led led4(LED_PAIR_COD_DIG_4_PIN);
const PairingCode pairingCode(&led1, &led2, &led3, &led4);
const Led ledStatus(LED_PAIR_STATUS_PIN);
const PairingStatus pairingStatus(&ledStatus);
const Command command(&pairingCode, &pairingStatus);
const Button pushBtn(BTN_COD_PAIR_PIN, &command);

void setup() {
  Serial.begin(SERIAL_BAUDS);
}

void loop() {
  pushBtn.inferState();
  pairingCode.inferState();
  
  command.readAndHandleCommands();
    
  Serial.flush();
}
