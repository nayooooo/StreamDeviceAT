#ifndef __STREAMDEVICEAT_TYPE_H__
#define __STREAMDEVICEAT_TYPE_H__

#include <Arduino.h>

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
	AT_ERROR_INPUT,
	AT_ERROR_OUTPUT,
	AT_ERROR_NOT_FIND,
	AT_ERROR_NO_ACT,
	AT_ERROR_CANNOT_CUT,
};
typedef enum At_Err At_Err_t;

#define AT_LABLE_TAIL ""
#define AT_PARAM_MAX_NUM (3)
struct At_Param
{
	String cmd;
	int argc;
	String argv[AT_PARAM_MAX_NUM];
};
typedef struct At_Param* At_Param_t;

typedef At_Err_t (*At_Act_t)(At_Param_t param);
struct At_State
{
	String atLable;
	At_Type_t type;
	At_Act_t act;
};
typedef struct At_State* At_State_t;

#endif  // !__STREAMDEVICEAT_TYPE_H__
