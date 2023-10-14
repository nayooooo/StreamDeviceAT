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
	):
	_atTable(atTable), _input_dev(input_dev), _output_dev(output_dev), _param_max_num(param_max_num), _terminator(terminator)
	{
		this->_readString = "";
	}

	At(
		const At_State_t atTable, Stream& input_dev, Stream& output_dev,
		size_t param_max_num = AT_PARAM_MAX_NUM, char terminator = '\n'
	):
	At(atTable, &input_dev, &output_dev, param_max_num, terminator)
	{
	}

private:
	At_Err_t cutString(struct At_Param& param, const String& atLable);
	At_State_t checkString(struct At_Param& param, const At_State_t atTable, const String& atLable);

public:
	virtual size_t getParamMaxNum(void) { return _param_max_num; }
	virtual At_State_t getStateTable(void) { return _atTable; }

	virtual At_Err_t setInputDevice(Stream* input_dev)
	{ this->_input_dev = input_dev; return AT_EOK; }
	virtual At_Err_t setInputDevice(Stream& input_dev) { return setInputDevice(&input_dev); }
	virtual At_Err_t setOutputDevice(Stream* output_dev)
	{ this->_output_dev = output_dev; return AT_EOK; }
	virtual At_Err_t setOutputDevice(Stream& output_dev) { return setOutputDevice(&output_dev); }

	virtual String errorToString(At_Err_t error);

	virtual At_Err_t handle(const String& atLable);
	virtual At_Err_t handle(const char* atLable) { return handle(String(atLable)); }
	At_Err_t handleAuto(void);

	virtual size_t printf(const char* format, ...)  __attribute__ ((format (printf, 2, 3)));

	virtual size_t print(const String& message)
	{ return this->_output_dev->print(message); }
	virtual size_t print(const char* message) { return print(String(message)); }

	virtual size_t println(const String& message)
	{ return this->_output_dev->println(message); }
	virtual size_t println(const char* message) { return println(String(message)); }

	virtual At_Err_t printSet(const String& name = "");
	virtual At_Err_t printSet(const char* name = "") { return printSet(String(name)); }

	virtual At_Err_t sendInfor(const String& infor)
	{ this->_output_dev->print(String("AT+{") + infor + "}"); return AT_EOK; }
	virtual At_Err_t sendInfor(const char* infor) { return sendInfor(String(infor)); }

private:
	At_State_t _atTable;
	Stream* _input_dev;
	Stream* _output_dev;
	size_t _param_max_num;
	char _terminator;
	String _readString;
};

#endif /* __AT_H__ */
