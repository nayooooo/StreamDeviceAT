#include <Arduino.h>

#include "at_user.h"

void setup() {
    Serial.begin(115200UL);
}

void loop() {
    at.handleAuto();
}
