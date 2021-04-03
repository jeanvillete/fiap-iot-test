#include "Led.h"
#include "Button.h"
#include "Command.h"

#define LED_1_PIN 9
#define LED_2_PIN 10
#define LED_3_PIN 11
#define LED_4_PIN 12

#define BUTTON_PIN 5

Command command;

Led led1(LED_1_PIN);
Led led2(LED_2_PIN);
Led led3(LED_3_PIN);
Led led4(LED_4_PIN);

Button button1(BUTTON_PIN, &command, &led1, &led2, &led3, &led4);

void setup() {
  Serial.begin(9600);
}

void loop() {
  button1.inferState();
  
  Serial.flush();
}
