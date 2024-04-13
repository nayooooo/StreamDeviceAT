#include "at_user.h"

At_Err_t at_user_AT_NULL(At_Param_t param);
At_Err_t at_user_AT(At_Param_t param);
At_Err_t at_user_AT_List(At_Param_t param);
At_Err_t at_user_AT_Reboot(At_Param_t param);
At_Err_t at_user_led(At_Param_t param);

struct At_Ins atSet[] = {
    { "AT", AT_TYPE_CMD, at_user_AT },
    { "AT+LS", AT_TYPE_CMD, at_user_AT_List },
    { "AT+REBOOT", AT_TYPE_CMD, at_user_AT_Reboot },
    { "AT+LED", AT_TYPE_CMD, at_user_led },
    { AT_LABLE_TAIL, AT_TYPE_NULL, at_user_AT_NULL },
};

At at(atSet, Serial, Serial);

At_Err_t at_user_AT_NULL(At_Param_t param)
{
    return AT_EOK;
}

At_Err_t at_user_AT(At_Param_t param)
{
    at.sendInfor(AT_USER_OK);
    return AT_EOK;
}

At_Err_t at_user_AT_List(At_Param_t param)
{
    at.printSet("AT");
    at.sendInfor(AT_USER_OK);
    return AT_EOK;
}

#include <EspSaveCrash.h>  // reboot
At_Err_t at_user_AT_Reboot(At_Param_t param)
{
    at.sendInfor(AT_USER_OK);
    ESP.reset();
    return AT_EOK;
}

// Establish LED sub instruction set under AT instruction set
#define _AT_USER_LED_ON      LOW
#define _AT_USER_LED_OFF     HIGH
At_Err_t _at_user_led_on(At_Param_t param);
At_Err_t _at_user_led_off(At_Param_t param);
struct At_Ins atLEDSet[] = {
    { "on", AT_TYPE_CMD, _at_user_led_on },
    { "off", AT_TYPE_CMD, _at_user_led_off },
    { AT_LABLE_TAIL, AT_TYPE_NULL, at_user_AT_NULL },
};
static At _at_led(atLEDSet, Serial, Serial);

At_Err_t at_user_led(At_Param_t param)
{
    At_Err_t err;
    String str = "";

    // if ((param->argc < 1) || (param->argc > 2)) {
    if (param->argc != 1) {
        goto err_out;
    }
    
    for (size_t i = 0; i < param->argc; i++) {
        str += String(param->argv[i]) + " ";
    }
    err = _at_led.handle(str);
    if (err != AT_EOK) goto err_out;
    at.sendInfor(AT_USER_OK);
    return err;

    if (0) {
    err_out:
        _at_led.printSet(param->cmd);
        at.sendInfor(String("commond(") + param->cmd + ")'s param is error");
        return AT_ERROR;
    }
}

At_Err_t _at_user_led_on(At_Param_t param)
{
    pinMode(2, OUTPUT);
    digitalWrite(2, _AT_USER_LED_ON);
    _at_led.sendInfor(AT_USER_OK);
    return AT_EOK;
}

At_Err_t _at_user_led_off(At_Param_t param)
{
    pinMode(2, OUTPUT);
    digitalWrite(2, _AT_USER_LED_OFF);
    _at_led.sendInfor(AT_USER_OK);
    return AT_EOK;
}
