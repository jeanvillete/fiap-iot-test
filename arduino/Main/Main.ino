#include "Led.h"
#include "Button.h"
#include "Command.h"

#define LED_1_PIN 9
#define LED_2_PIN 10
#define LED_3_PIN 11
#define LED_4_PIN 12
#define BUTTON_PIN 5

const unsigned int SERIAL_BAUDS = 9600;

const Command command;
const Led led1(LED_1_PIN);
const Led led2(LED_2_PIN);
const Led led3(LED_3_PIN);
const Led led4(LED_4_PIN);
const Button pushBtn(BUTTON_PIN, &command, &led1, &led2, &led3, &led4);

void setup() {
  Serial.begin(SERIAL_BAUDS);
}

void loop() {
  pushBtn.inferState();
  command.readAndHandleCommands();
  
  Serial.flush();
}
