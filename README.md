# AT指令解析器

中文/[English](README_en.md)

该库实现了一个AT指令解析器，可以解析串行输入设备发送的AT指令，并通过串行输出设备将一些信息发送出去。

# 用法

## 初始化

    At at(atTable, &input_dev, &output_dev, param_max_num, terminator);
    At at(atTable, input_dev, output_dev, param_max_num, terminator);

`atTable`：AT指令状态表，定义了支持的AT指令及其处理函数。

`input_dev`：串行输入设备。

`output_dev`：串行输出设备。

`param_max_num`：参数的最大数量，默认为3。

`terminator`：AT指令的终止字符，默认为换行符`\n`。

## 处理AT指令

### 处理字符串

    At_Err_t result = at.handle(atLable);

`atLable`：待处理的AT指令。

### 自动处理AT指令

    At_Err_t result = at.handleAuto();

自动从输入设备读取AT指令并进行处理。

## 发送信息

    At_Err_t result = at.sendInfor(infor);

向输出设备发送信息。

# 示例

以下是一个简单的示例代码，演示了如何使用该库：


    #include <Arduino.h>
    #include <at.h>

    // 定义AT指令处理函数
    At_Err_t handleCmd1(At_Param_t param)
    {
        // 处理AT指令逻辑
        // ...
        return AT_EOK;
    }

    At_Err_t handleCmd2(At_Param_t param)
    {
        // 处理AT指令逻辑
        // ...
        return AT_EOK;
    }

    // 定义AT指令状态表
    At_State stateTable[] = {
        {"AT+CMD1", AT_TYPE_CMD, handleCmd1},
        {"AT+CMD2", AT_TYPE_CMD, handleCmd2},
        {AT_LABLE_TAIL, AT_TYPE_NULL, nullptr}
    };

    // 实例化一个AT指令解析器
    At at(stateTable, Serial, Serial);

    void setup()
    {
        Serial.begin(115200UL);
    }

    void loop()
    {
        at.handleAuto();
        // 其他逻辑处理
    }

# 注意事项

1. 请根据实际需求修改和扩展AT指令状态表和处理函数。
2. 请确保正确设置串行输入输出设备。
3. 串行输入输出设备可以是Stream类的子类。
4. 请确保每次指令输入必须以`'\n'`为结尾，并且其后没有其它字符。
