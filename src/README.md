# 更新日志（Branch）

## AddDMInsSet

1. 将StreamDeviceAT_Type.h文件中的宏`AT_PARAM_MAX_NUM`重命名为`AT_PARAM_MAX_NUM_DEFAULT`
2. 在StreamDeviceAT_Type.h文件中新增宏`AT_TERMINATOR_DEFAULT`用于表示接收字符串的结束符
3. 将StreamDeviceAT_Type.h文件中的结构体`At_State`重命名为`At_Ins`，同时将结构体指针`At_State_t`重命名为`At_Ins_t`
4. 给`At::println(const String&)`方法设置了默认值`""`（空字符串）
5. 给`At::sendInfor(const String&)`方法增加了输出设备存在检测
6. 将`At`类中的各个重载方法进行了调整，防止在使用默认值时出现多个对应的方法的情况出现
7. 对`At::checkString(struct At_Param& param, const String& atLable)`方法进行了调整，增加了判断指令字符串切片成功的判断
8. 给`At`类中相应的方法加上了`const`
9. 添加预编译宏，确保能够使用`std::size`来获取字符串数组的数组大小
10. 优化了`At`类中各个方法的逻辑结构
11. 需要至少支持C++11标准
12. 重构部分方法以适应属性`std::list<struct At_Ins> _atInsSet`

## DMInsSet.LessRAM

1. 将`At::error2String`中的字符串替换为字符串字面量，降低动态内存分配带来的内存占用和性能消耗
2. 在预编译时期增加`C++11`标准判断，以便更清晰地提示错误
3. 将`At::cutString`、`At::checkString`、`At::handle`中的形参`atLable`改成`pendIns`，因为它是个未经处理的字符串，而不是AT指令标签
4. 在`./examples/serial_at`中添加`AT+ECHO`指令，用于回显参数
5. 增加析构函数以清空`At::_atInsSet`
6. 删除模板`At::arraySize`
7. 将`StreamDeviceAT::At_Param::argv`的类型由`String`改成`std::vector<String>`以适应不同长度的参数表
8. 向构造函数中添加了参数数目判断，如果输入值小于等于0，那么修改为1
9. 修改行为`At::handle`以适应新的vector模板参数
10. 修改行为`At::cutString`以适应新的vector模板参数
11. 在`./examples/serial_at`中修改变量`at`的最大参数数为`10`

## V1-MoreFlexibleParameters

1. 重构了`At::handle`，达到不改变传入参数的目的
2. 重构了`At::addInstruction`，达到传递匿名结构体时不再次构造对象的目的
3. 重构了`At::handleAuto`，达到在调用`At::handle`时不构造新的`String`的目的
4. 将`At::_terminator`的类型换成`String`，用于应对多字节结束标识的指令模式，增强稳定性
5. 重载了运算符`+=`和`-=`，用于增删指令条目
6. 添加`At`的深拷贝构造函数，方便复用指令条目

## V2-StdStringAndStdIOStream

TODO:

1. 使用`std::string`替换`String`
2. 添加自定义抽象类`Stream`和硬件串口类`HardwareSerial`，从而脱离固定平台
