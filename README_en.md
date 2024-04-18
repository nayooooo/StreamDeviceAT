# AT instruction parser

English/[中文](README.md)

This library implements an AT instruction parser that can parse AT instructions sent by serial input devices and send some information out through serial output devices, which can be easily applied to debugging, instruction control, and other related tasks.

# usage

## initialization

    At at(&input_dev, &output_dev, param_max_num, terminator);
    At at(input_dev, output_dev, param_max_num, terminator);

`input_dev`: Serial input device.

`output_dev`: Serial output device.

`param_max_num`: The maximum number of parameters, default to 3.

`terminator`: The termination character of the AT instruction defaults to the line break character `\n`.

## Processing AT instructions

### Processing strings

    At_Err_t result = at.handle(atLable);

`atLable`: The pending AT instruction.

### Automatic processing of AT instructions

    At_Err_t result = at.handleAuto();

Automatically read AT instructions from input devices and process them.

## Sending messages

    At_Err_t result = at.sendInfor(infor);

Send information to the output device.

# Example

The following is a simple example code that demonstrates how to use the library:


    #include <Arduino.h>
    #include <StreamDeviceAT.h>

    // Defining AT Instruction Processing Functions
    At_Err_t handleCmd1(At_Param_t param)
    {
        // Processing AT instruction logic
        // ...
        return AT_EOK;
    }

    At_Err_t handleCmd2(At_Param_t param)
    {
        // Processing AT instruction logic
        // ...
        return AT_EOK;
    }

    // Instantiate an AT instruction parser
    At at(Serial, Serial);

    At_Err_t at_user_init(void)
    {
        at.addInstruction({"AT+CMD1", AT_TYPE_CMD, handleCmd1});
        at.addInstruction({"AT+CMD2", AT_TYPE_CMD, handleCmd2});

        return AT_EOK;
    }

    void setup()
    {
        Serial.begin(115200UL);
        at_user_init();
    }

    void loop()
    {
        At_Err_t err = at.handleAuto();
        if (err == AT_ERROR_NOT_FIND) at.sendInfor(at.error2String(err));
        // Other logical processing
    }

# note

1. Please modify and expand the AT instruction status table and processing functions according to actual needs.
2. Please ensure that the serial input/output device is set up correctly.
3. Serial input/output devices can be subclasses of the Stream class.
4. Please ensure that each instruction input must end with `\n` and there are no other characters after it.

## AddDMInsSet

1. At least support for C++11 standards is required
