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
		const At_Ins_t atTable, Stream* input_dev, Stream* output_dev,
		size_t param_max_num = AT_PARAM_MAX_NUM_DEFAULT, char terminator = AT_TERMINATOR_DEFAULT
	):
	_atInsSet(atTable), _input_dev(input_dev), _output_dev(output_dev), _param_max_num(param_max_num), _terminator(terminator),
	_readString("")
	{
	}

	At(
		const At_Ins_t atTable, Stream* input_dev, Stream& output_dev,
		size_t param_max_num = AT_PARAM_MAX_NUM_DEFAULT, char terminator = AT_TERMINATOR_DEFAULT
	): At(atTable, input_dev, &output_dev, param_max_num, terminator) {}

	At(
		const At_Ins_t atTable, Stream& input_dev, Stream* output_dev,
		size_t param_max_num = AT_PARAM_MAX_NUM_DEFAULT, char terminator = AT_TERMINATOR_DEFAULT
	): At(atTable, &input_dev, output_dev, param_max_num, terminator) {}

	At(
		const At_Ins_t atTable, Stream& input_dev, Stream& output_dev,
		size_t param_max_num = AT_PARAM_MAX_NUM_DEFAULT, char terminator = AT_TERMINATOR_DEFAULT
	): At(atTable, &input_dev, &output_dev, param_max_num, terminator) {}

private:
	template <typename T, size_t N>
	constexpr size_t arraySize(T (&)[N]) const
	{
		return N;
	}

	bool isInputDevExists(void) const { return (this->_input_dev != nullptr) ? true: false; }
	bool isOutputDevExists(void) const { return (this->_output_dev != nullptr) ? true: false; }

	At_Err_t cutString(struct At_Param& param, const String& atLable) const;
	At_Ins_t checkString(struct At_Param& param, const String& atLable) const;

public:
	size_t getParamMaxNum(void) const { return this->_param_max_num; }
	At_Ins_t getInsSet(void) const { return this->_atInsSet; }

	At_Err_t setInputDevice(Stream* input_dev) { this->_input_dev = input_dev; return AT_EOK; }
	At_Err_t setInputDevice(Stream& input_dev) { return this->setInputDevice(&input_dev); }
	At_Err_t setOutputDevice(Stream* output_dev) { this->_output_dev = output_dev; return AT_EOK; }
	At_Err_t setOutputDevice(Stream& output_dev) { return this->setOutputDevice(&output_dev); }

	String error2String(At_Err_t error) const;

	At_Err_t handle(const String& atLable) const;
	At_Err_t handle(const char* atLable) const { return this->handle(String(atLable)); }
	At_Err_t handleAuto(void);

	size_t print(const String& message) const { return (this->isOutputDevExists()) ? (this->_output_dev->print(message)) : (0); }
	size_t print(const char* message) const { return this->print(String(message)); }

	size_t println(const String& message) const { return this->print(message + "\n"); }
	size_t println(const char* message = "") const { return this->println(String(message)); }

	size_t printf(const char* format, ...) const  __attribute__ ((format (printf, 2, 3)));

	At_Err_t printSet(const String& name) const;
	At_Err_t printSet(const char* name = "") const { return this->printSet(String(name)); }

	At_Err_t sendInfor(const String& infor) const {
		if (this->isOutputDevExists()) {
			this->_output_dev->print(String("AT+{") + infor + "}");
			return AT_EOK;
		} else return AT_ERROR_OUTPUT;
	}
	At_Err_t sendInfor(const char* infor = "") const { return this->sendInfor(String(infor)); }

private:
	At_Ins_t _atInsSet;
	Stream* _input_dev;
	Stream* _output_dev;
	size_t _param_max_num;
	char _terminator;
	String _readString;
};

#endif /* __STREAMDEVICEAT_H__ */
