/**
 * @details In this example, you need to install the EspSaveCrash library or block the restart command
 * @module Generic ESP8266 Module
*/

#include <Arduino.h>

#include "at_user.h"

void setup() {
    Serial.begin(115200UL);
}

void loop() {
    at.handleAuto();
}
