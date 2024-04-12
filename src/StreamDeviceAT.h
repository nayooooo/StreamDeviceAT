/**
 * @details The parameter list obtained by this AT module is for processing parameters outside of the AT instruction code
 *          For example, the parameter list obtained from AT+WIFI SSID PSK is: 
 *              [0] SSID    [1] PSK
 */

#ifndef __STREAMDEVICEAT_H__
#define __STREAMDEVICEAT_H__

#include <StreamDeviceAT_Type.h>
#include <stdlib.h>

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
	bool isInputDevExists(void) { return (this->_input_dev != nullptr) ? true: false; }
	bool isOutputDevExists(void) { return (this->_output_dev != nullptr) ? true: false; }

	At_Err_t cutString(struct At_Param& param, const String& atLable);
	At_State_t checkString(struct At_Param& param, const String& atLable);

public:
	virtual size_t getParamMaxNum(void) { return this->_param_max_num; }
	virtual At_State_t getStateTable(void) { return this->_atTable; }

	virtual At_Err_t setInputDevice(Stream* input_dev) { this->_input_dev = input_dev; return AT_EOK; }
	virtual At_Err_t setInputDevice(Stream& input_dev) { return setInputDevice(&input_dev); }
	virtual At_Err_t setOutputDevice(Stream* output_dev) { this->_output_dev = output_dev; return AT_EOK; }
	virtual At_Err_t setOutputDevice(Stream& output_dev) { return setOutputDevice(&output_dev); }

	virtual String errorToString(At_Err_t error);

	virtual At_Err_t handle(const String& atLable);
	virtual At_Err_t handle(const char* atLable) { return handle(String(atLable)); }
	At_Err_t handleAuto(void);

	virtual size_t printf(const char* format, ...)  __attribute__ ((format (printf, 2, 3)));

	virtual size_t print(const String& message)
	{ return (isOutputDevExists()) ? (this->_output_dev->print(message)) : (0); }
	virtual size_t print(const char* message) { return print(String(message)); }

	virtual size_t println(const String& message)
	{ return this->print(message + "\r\n"); }
	virtual size_t println(const char* message = "") { return println(String(message)); }

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

#endif /* __STREAMDEVICEAT_H__ */