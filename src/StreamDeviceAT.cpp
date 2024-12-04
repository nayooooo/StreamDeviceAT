#include "StreamDeviceAT.h"

using namespace StreamDeviceAT;

At_Err_t At::cutString(struct At_Param& param, String&& pendIns) const
{
	if (pendIns.isEmpty()) return AT_ERROR;  // do not accept empty string
	// TODO: If necessary, modify to create a copy of the character array,
	//       as this function will modify the resulting character array
	char* str = (char*)(pendIns.c_str());

	size_t param_num = this->getParamMaxNum();

	param.cmd = "";
	param.argc = 0;
	param.argv.clear();

	// find at set
	param.cmd = strtok(str, " \r\n");
	if (param.cmd.isEmpty()) return AT_ERROR;
	// find at param
	for (int i = 0; i < param_num; i++)
	{
		String temp = strtok(NULL, " \r\n");
		if (temp.isEmpty())
			break;
		param.argv.push_back(temp);
		param.argc++;
	}

	return AT_EOK;
}

At_Ins_t At::checkString(struct At_Param& param, String&& pendIns) const
{
	At_Ins_t target = nullptr;

	At_Err_t err = this->cutString(param, std::move(pendIns));
	if (err != AT_EOK) return nullptr;

	std::list<struct At_Ins>::const_iterator it = std::find_if(this->_atInsSet.begin(), this->_atInsSet.end(),
															[param](const struct At_Ins& ins) -> bool {
																return ins.atLable == param.cmd;
															});
	if (it == this->_atInsSet.end()) target = nullptr;
	else {
		struct At_Ins& temp = (struct At_Ins&)(*it);  // prevent optimization
		target = &temp;
	}

	return target;
}

At_Err_t At::addInstruction(const struct At_Ins& ins)
{
	if (ins.atLable.isEmpty()) return AT_ERROR;
	if (ins.type == AT_TYPE_NULL) return AT_ERROR;
	if (ins.act == nullptr) return AT_ERROR_NO_ACT;

	std::list<struct At_Ins>::iterator it = std::find_if(this->_atInsSet.begin(), this->_atInsSet.end(),
															[ins](const struct At_Ins& insr) -> bool {
																return insr.atLable == ins.atLable;
															});
	if (it != this->_atInsSet.end()) return AT_ERROR_DUPLICATE_LABEL;

	this->_atInsSet.push_back(ins);

	return AT_EOK;
}

At_Err_t At::delInstruction(const String& atLable)
{
	if (atLable.isEmpty()) return AT_ERROR;

	std::list<struct At_Ins>::iterator it;
	it = std::find_if(this->_atInsSet.begin(), this->_atInsSet.end(),
						[atLable](const struct At_Ins& ins) -> bool {
							return ins.atLable == atLable;
						});
	if (it == this->_atInsSet.end()) return AT_ERROR_NOT_FIND;

	// erase one
	this->_atInsSet.erase(it);

	return AT_EOK;
}

const char* At::error2String(At_Err_t error) const
{
	switch (error)
	{
	case AT_ERROR:
		return "AT normal error";
	case AT_ERROR_NULL_OBJECT:
		return "AT object is nullptr";
	case AT_ERROR_INPUT:
		return "AT input device error";
	case AT_ERROR_OUTPUT:
		return "AT output device error";
	case AT_ERROR_NOT_FIND:
		return "AT not find this string command";
	case AT_ERROR_NO_ACT:
		return "AT this string command not have act";
	case AT_ERROR_CANNOT_CUT:
		return "AT this string can't be cut";
	}
	return "AT no error";
}

At_Err_t At::handle(String&& pendIns) const
{
	At_Err_t ret;
	struct At_Param param;
	At_Ins_t target = this->checkString(param, std::move(pendIns));

	if (target == nullptr) {
		ret = AT_ERROR_NOT_FIND;
		goto error_out;
	}
	if (target->act == nullptr) {
		ret = AT_ERROR_NO_ACT;
		goto error_out;
	}

	ret = target->act(&param);

error_out:
	param.argv.clear();
	return ret;
}

At_Err_t At::handleAuto(void)
{
	int in = 0;

	if (!isInputDevExists()) return AT_ERROR_INPUT;

	if (this->_input_dev->available()) {
		in = this->_input_dev->read();
		if ((in >= 0) && ((char)in != this->_terminator)) {
			this->_readString += (char)in;
			return AT_EOK;
		} else if ((char)in == this->_terminator) {
			At_Err_t err = this->handle(this->_readString);
			this->_readString.clear();
			return err;
		}
	}

	return AT_EOK;
}

size_t At::printf(const char* format, ...) const
{
	va_list arg;
	va_start(arg, format);
	char temp[64] = { 0 };
	char *buffer = temp;
	size_t len = vsnprintf(temp, sizeof(temp), format, arg);
	va_end(arg);
	if (len > sizeof(temp) - 1) {
		buffer = new(std::nothrow) char[len + 1];
		if (!buffer) return 0;
		memset(buffer, 0, len + 1);
		va_start(arg, format);
        vsnprintf(buffer, len + 1, format, arg);
        va_end(arg);
	}
	this->print(buffer);
    if (buffer != temp) {
        delete[] buffer;
    }

	return len;
}

At_Err_t At::printSet(const String& name) const
{
	this->println();
	this->println(String("the set(") + name + "): ");
	if (this->_atInsSet.size() == 0) {
		this->println("have nothing AT commond!");
	} else {
		for (struct At_Ins ins : this->_atInsSet) {
			this->println(String("--") + ins.atLable);
		}
	}
	return AT_EOK;
}
