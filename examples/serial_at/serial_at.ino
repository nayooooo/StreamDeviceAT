/**
 * @details In this example, you need to install the EspSaveCrash library or block the restart command
 * @module Generic ESP8266 Module
 *         Actually is ESP-01S
*/

#include <Arduino.h>

#include "at_user.h"

void setup() {
    at_user_init(115200UL);
}

void loop() {
    At_Err_t err = at.handleAuto();
    if (err == AT_ERROR_NOT_FIND) at.sendInfor(at.error2String(err));
    delay(1);
}
