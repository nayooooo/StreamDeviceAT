#include <Arduino.h>

#define USE_SERIAL_AT     (1)  // 使用串口作为AT的指令获取设备

#if USE_SERIAL_AT

#include "at_user.h"

#endif  // USE_SERIAL_AT

void setup() {
    Serial.begin(115200UL);
}

void loop() {
    #if USE_SERIAL_AT
    
    at.handleAuto();

    #endif  // USE_SERIAL_AT
}
