/**
 * @details 该AT模块得到的参数列表是处理AT指令码外的参数，
 *          如：AT+WIFI SSID PSK得到的参数列表是
 *              [0] SSID    [1] PSK
 */

#ifndef __AT_H__
#define __AT_H__

#include <Arduino.h>
#include <stdlib.h>
#include <at_type.h>

class At
{
public:
	At(
		const At_State_t atTable, Stream* input_dev, Stream* output_dev,
		size_t param_max_num = AT_PARAM_MAX_NUM, char terminator = '\n'
	);
	At(
		const At_State_t atTable, Stream& input_dev, Stream& output_dev,
		size_t param_max_num = AT_PARAM_MAX_NUM, char terminator = '\n'
	);

private:
	At_Err_t cutString(struct At_Param& param, const String& atLable);
	At_State_t checkString(struct At_Param& param, const At_State_t atTable, const String& atLable);

public:
	virtual size_t getParamMaxNum(void);
	virtual At_State_t getStateTable(void);
	virtual At_Err_t setInputDevice(Stream* input_dev);
	virtual At_Err_t setInputDevice(Stream& input_dev);
	virtual At_Err_t setOutputDevice(Stream* output_dev);
	virtual At_Err_t setOutputDevice(Stream& output_dev);
	virtual String errorToString(At_Err_t error);

	virtual At_Err_t handle(const String& atLable);
	virtual At_Err_t handle(const char* atLable);
	At_Err_t handleAuto(void);

	virtual size_t print(const String& message);
	virtual size_t print(const char* message);
	virtual size_t println(const String& message);
	virtual size_t println(const char* message);
	virtual At_Err_t printSet(const String& name = "");
	virtual At_Err_t printSet(const char* name = "");

	virtual At_Err_t sendInfor(const String& infor);
	virtual At_Err_t sendInfor(const char* infor);

private:
	At_State_t _atTable;
	Stream* _input_dev;
	Stream* _output_dev;
	size_t _param_max_num;
	char _terminator;
	String _readString;
};

#endif /* __AT_H__ */
