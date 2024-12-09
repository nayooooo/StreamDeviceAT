/**
 * @details The parameter list obtained by this AT module is for processing parameters outside of the AT instruction code
 *          For example, the parameter list obtained from AT+WIFI SSID PSK is: 
 *              [0] SSID    [1] PSK
 */

#ifndef __STREAMDEVICEAT_H__
#define __STREAMDEVICEAT_H__

#include <cstring>
#include <string>
#include <vector>
#include <list>
#include <algorithm>

#if defined(USE_STREAM_SELF)
#include "Stream/Stream.h"
#else
#include <Arduino.h>
#endif

// 需要至少支持C++11
#if __cplusplus < 201103L
	#error "This library needs at least a C++11 compliant compiler"
#endif

namespace StreamDeviceAT{

	enum At_Type
	{
		AT_TYPE_NULL = 0,
		AT_TYPE_CMD,
		AT_TYPE_DATA,
	};
	typedef enum At_Type At_Type_t;

	enum At_Err
	{
		AT_EOK = 0,
		AT_ERROR,
		AT_ERROR_NULL_OBJECT,
		AT_ERROR_INPUT,
		AT_ERROR_OUTPUT,
		AT_ERROR_NOT_FIND,
		AT_ERROR_NO_ACT,
		AT_ERROR_CANNOT_CUT,
		AT_ERROR_DUPLICATE_LABEL,
	};
	typedef enum At_Err At_Err_t;

	#define AT_PARAM_MAX_NUM_DEFAULT (3)
	#define AT_TERMINATOR_DEFAULT "\n"
	struct At_Param
	{
		std::string cmd;
		int argc;
		std::vector<std::string> argv;
	};
	typedef struct At_Param* At_Param_t;

	// AT instruction
	#define AT_ATLABLE_TAIL ""
	typedef At_Err_t (*At_Act_t)(At_Param_t param);
	struct At_Ins
	{
		std::string atLable;
		At_Type_t type;
		At_Act_t act;
	};
	typedef struct At_Ins* At_Ins_t;


#if defined(USE_STREAM_SELF)
	class Stream;
#endif

	class At
	{
	public:
		At(
			Stream* input_dev, Stream* output_dev,
			size_t param_max_num = AT_PARAM_MAX_NUM_DEFAULT, std::string terminator = AT_TERMINATOR_DEFAULT
		):
		_input_dev(input_dev), _output_dev(output_dev), _param_max_num(param_max_num), _terminator(terminator), _readString("")
		{
			if (_param_max_num <= 0) {
				_param_max_num = 1;
			}
		}

		At(
			Stream* input_dev, Stream& output_dev,
			size_t param_max_num = AT_PARAM_MAX_NUM_DEFAULT, std::string terminator = AT_TERMINATOR_DEFAULT
		): At(input_dev, &output_dev, param_max_num, terminator) {}

		At(
			Stream& input_dev, Stream* output_dev,
			size_t param_max_num = AT_PARAM_MAX_NUM_DEFAULT, std::string terminator = AT_TERMINATOR_DEFAULT
		): At(&input_dev, output_dev, param_max_num, terminator) {}

		At(
			Stream& input_dev, Stream& output_dev,
			size_t param_max_num = AT_PARAM_MAX_NUM_DEFAULT, std::string terminator = AT_TERMINATOR_DEFAULT
		): At(&input_dev, &output_dev, param_max_num, terminator) {}

		// deep copy
		At(const At& at)
		  : _input_dev(at._input_dev), _output_dev(at._output_dev),
			_param_max_num(at._param_max_num), _terminator(at._terminator),
			_readString(at._readString), _atInsSet(at._atInsSet)
		{}

		~At()
		{
			_atInsSet.clear();
		}

	private:
		bool isInputDevExists(void) const { return (_input_dev != nullptr) ? true: false; }
		bool isOutputDevExists(void) const { return (_output_dev != nullptr) ? true: false; }

		At_Err_t cutString(struct At_Param& param, std::string&& pendIns) const;
		At_Ins_t checkString(struct At_Param& param, std::string&& pendIns) const;

	public:
		size_t getParamMaxNum(void) const { return _param_max_num; }

		At_Err_t setInputDevice(Stream* input_dev) { _input_dev = input_dev; return AT_EOK; }
		At_Err_t setInputDevice(Stream& input_dev) { return setInputDevice(&input_dev); }
		At_Err_t setOutputDevice(Stream* output_dev) { _output_dev = output_dev; return AT_EOK; }
		At_Err_t setOutputDevice(Stream& output_dev) { return setOutputDevice(&output_dev); }

		At_Err_t addInstruction(const struct At_Ins& ins) { return addInstruction(At_Ins(ins)); }
		At_Err_t addInstruction(struct At_Ins&& ins);
		At_Err_t delInstruction(const std::string& atLable);
		At_Err_t delInstruction(const struct At_Ins& ins) { return delInstruction(ins.atLable); };

		const char* error2String(At_Err_t error) const;

		At_Err_t handle(const std::string& pendIns) const { return handle(std::string(pendIns)); }
		At_Err_t handle(std::string&& pendIns) const;
		At_Err_t handleAuto(void);

		size_t print(const std::string& message) const { return isOutputDevExists() ? (_output_dev->print(message.c_str())) : (0); }
		size_t print(const char* message) const { return isOutputDevExists() ? print(std::string(message)) : (0); }

		size_t println(const std::string& message) const { return print(message + "\n"); }
		size_t println(const char* message = "") const { return println(std::string(message)); }

		size_t printf(const char* format, ...) const  __attribute__ ((format (printf, 2, 3)));

		At_Err_t printSet(const std::string& name) const;
		At_Err_t printSet(const char* name = "") const { return printSet(std::string(name)); }

		At_Err_t sendInfor(const std::string& infor) const {
			if (isOutputDevExists()) {
				_output_dev->print((std::string("AT+{") + infor + "}").c_str());
				return AT_EOK;
			} else return AT_ERROR_OUTPUT;
		}
		At_Err_t sendInfor(const char* infor = "") const { return sendInfor(std::string(infor)); }

	public:
		At& operator+=(const struct At_Ins& ins) {
			addInstruction(ins);
			return *this;
		}
		At& operator+=(struct At_Ins&& ins) {
			addInstruction(std::move(ins));
			return *this;
		}
		At& operator+=(const At& at) {
			for (const struct At_Ins& item : at._atInsSet)
			{
				addInstruction(item);
			}
			return *this;
		}

		At& operator-=(const std::string& atLable) {
			delInstruction(atLable);
			return *this;
		}
		At& operator-=(const struct At_Ins& ins) {
			delInstruction(ins);
			return *this;
		}
		At& operator-=(const At& at) {
			for (const struct At_Ins& item : at._atInsSet)
			{
				delInstruction(item);
			}
			return *this;
		}

	private:
		std::list<struct At_Ins> _atInsSet;
		Stream* _input_dev = nullptr;
		Stream* _output_dev = nullptr;
		size_t _param_max_num;
		std::string _terminator;  // only use in At::handleAuto
		std::string _readString;
	};

}

#endif /* __STREAMDEVICEAT_H__ */
