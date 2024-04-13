# 更新日志（Branch）

## AddDynamicManagingATInstructionSet

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