#include "controller/controller.h"

Controller controller;

void setup() {
  Serial.begin(115200);
  Serial.println("Meow init");  
  controller.start();
}

void loop() {
  controller.update();
}