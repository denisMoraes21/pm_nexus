
#include <Arduino.h>
#include "deep_sleep.h"

void setup() {
  Serial.begin(115200);
  delay(1000);

  deep_sleep(5);
}

void loop() {
  // Nunca será executado
}