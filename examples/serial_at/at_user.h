#ifndef __AT_USER_H__
#define __AT_USER_H__

#include <Arduino.h>
#include <at.h>

#define AT_USER_OK "OK"
#define AT_USER_ERROR_ARGC "error by argc"
#define AT_USER_ERROR_TIMEOUT "error by timeout"
#define AT_USER_ERROR_NOTFIND "error by not found"
#define AT_USER_ERROR_FUNCTION "error by function"

extern At at;

#endif  // !__AT_USER_H__
