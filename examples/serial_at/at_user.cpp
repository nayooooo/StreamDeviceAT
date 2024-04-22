#include "at_user.h"

At at(Serial, Serial, 10);
static At _at_led(Serial, Serial);

At_Err_t at_user_AT(At_Param_t param)
{
    at.sendInfor(AT_USER_OK);
    return AT_EOK;
}

At_Err_t at_user_AT_Echo(At_Param_t param)
{
    at.println();
    at.println("args: ");
    if (param->argc == 0) {
        at.println("\tno arg");
    }
    for (int i = 0; i < param->argc; i++) {
        at.printf("\t[%d] %s", i, param->argv[i]);
        at.println();
    }
    return AT_EOK;
}

At_Err_t at_user_AT_List(At_Param_t param)
{
    at.printSet("AT");
    return AT_EOK;
}

#include <EspSaveCrash.h>  // reboot
At_Err_t at_user_AT_Reboot(At_Param_t param)
{
    ESP.reset();
    return AT_EOK;
}

// Establish LED sub instruction set under AT instruction set
#define _AT_USER_LED_ON      LOW
#define _AT_USER_LED_OFF     HIGH

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

At_Err_t _at_user_add_AT_Reboot(At_Param_t param)
{
    At_Err_t err = at.addInstruction({ "AT+REBOOT", AT_TYPE_CMD, at_user_AT_Reboot });
    if (err == AT_EOK) _at_led.sendInfor(AT_USER_OK);
    else _at_led.sendInfor(AT_USER_ERROR);
    return err;
}

At_Err_t _at_user_del_AT_Reboot(At_Param_t param)
{
    At_Err_t err = at.delInstruction("AT+REBOOT");
    if (err == AT_EOK) _at_led.sendInfor(AT_USER_OK);
    else if (err == AT_ERROR_NOT_FIND) _at_led.sendInfor(AT_USER_ERROR_NOTFIND);
    else _at_led.sendInfor(AT_USER_ERROR);
    return err;
}

At_Err_t at_user_init(void)
{
    at.addInstruction({ "AT", AT_TYPE_CMD, at_user_AT });
    at.addInstruction({ "AT+ECHO", AT_TYPE_CMD, at_user_AT_Echo });
    at.addInstruction({ "AT+LS", AT_TYPE_CMD, at_user_AT_List });
    at.addInstruction({ "AT+REBOOT", AT_TYPE_CMD, at_user_AT_Reboot });
    at.addInstruction({ "AT+LED", AT_TYPE_CMD, at_user_led });
    at.addInstruction({ "AT+ADDREBOOT", AT_TYPE_CMD, _at_user_add_AT_Reboot });
    at.addInstruction({ "AT+DELREBOOT", AT_TYPE_CMD, _at_user_del_AT_Reboot });

    _at_led.addInstruction({ "on", AT_TYPE_CMD, _at_user_led_on });
    _at_led.addInstruction({ "off", AT_TYPE_CMD, _at_user_led_off });

    return AT_EOK;
}
