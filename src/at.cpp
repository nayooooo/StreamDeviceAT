#include "at.h"

At::At(
		const At_State_t atTable, Stream& input_dev, Stream& output_dev,
		size_t param_max_num, char terminator
	):
	_atTable(atTable), _input_dev(input_dev), _output_dev(output_dev), _param_max_num(param_max_num), _terminator(terminator)
{
	this->_readString = "";
}

At_Err_t At::cutString(struct At_Param& param, const String& atLable)
{
	char* str = (char*)(atLable.c_str());

	param.cmd = AT_LABLE_TAIL;
	param.argc = 0;
	for (int i = 0; i < getParamMaxNum(); i++)
		param.argv[i] = (char *)"";

	// find at lable
	param.cmd = strtok(str, " \r\n");
	// find at param
	for (int i = 0; i < getParamMaxNum(); i++)
	{
		param.argv[i] = strtok(NULL, " \r\n");
		if (param.argv[i] == NULL)
			break;
		param.argc++;
	}

	return AT_EOK;
}

At_State_t At::checkString(struct At_Param& param, const At_State_t atTable, const String& atLable)
{
	uint32_t i = 0;
	At_State_t target = nullptr;

	cutString(param, atLable);

	while (atTable[i].atLable != AT_LABLE_TAIL)
	{
		if (atTable[i].atLable == param.cmd)
		{
			target = &atTable[i];
			break;
		}
		i++;
	}

	return target;
}

size_t At::getParamMaxNum(void)
{
	return _param_max_num;
}

At_State_t At::getStateTable(void)
{
	return _atTable;
}

String At::errorToString(At_Err_t error)
{
	switch (error)
	{
	case AT_ERROR:
		return String("AT normal error");
	case AT_ERROR_INPUT:
		return String("AT input device error");
	case AT_ERROR_OUTPUT:
		return String("AT output device error");
	case AT_ERROR_NOT_FIND:
		return String("AT not find this string command");
	case AT_ERROR_NO_ACT:
		return String("AT this string command not have act");
	case AT_ERROR_CANNOT_CUT:
		return String("AT this string can't be cut");
	}
	return String("AT no error");
}

At_Err_t At::handle(const String& atLable)
{
	struct At_Param param;
	At_State_t target = checkString(param, _atTable, atLable);

	if (target == NULL)
		return AT_ERROR_NOT_FIND;
	if (target->act == NULL)
		return AT_ERROR_NO_ACT;

	At_Err_t ret = target->act(&param);
	if (ret != AT_EOK)
		return AT_ERROR;

	return AT_EOK;
}

At_Err_t At::handle(const char* atLable)
{
	return handle(String(atLable));
}

At_Err_t At::handleAuto(void)
{
	int in = 0;

	if (this->_input_dev.available()) {
		in = this->_input_dev.read();
		if ((in >= 0) && ((char)in != this->_terminator)) {
			this->_readString += (char)in;
			return AT_EOK;
		} else if ((char)in == this->_terminator) {
			At_Err_t err = handle(this->_readString);
			this->_readString = "";
			return err;
		}
	}

	return AT_ERROR_INPUT;
}

size_t At::print(const String& message)
{
	return this->_output_dev.print(message);
}

size_t At::println(const String& message)
{
	return this->_output_dev.println(message);
}

At_Err_t At::printSet(const String& name)
{
	this->_output_dev.println();
	if (name != "") {
		this->_output_dev.println(String("the set(") + name + "): ");
	} else {
		this->_output_dev.println("the set: ");;
	}
	if (this->_atTable[0].atLable == AT_LABLE_TAIL) {
		this->_output_dev.println("have nothing AT commond!");
	} else {
		for (size_t i = 0; this->_atTable[i].atLable != AT_LABLE_TAIL; i++) {
			String lable = this->_atTable[i].atLable;
			this->_output_dev.println(String("--") + lable);
		}
	}
	return AT_EOK;
}

At_Err_t At::printSet(const char* name)
{
	return printSet(String(name));
}

At_Err_t At::sendInfor(const String& infor)
{
	return sendInfor(infor.c_str());
}

At_Err_t At::sendInfor(const char* infor)
{
	this->_output_dev.print(String("AT+{") + infor + "}");
	return AT_EOK;
}
