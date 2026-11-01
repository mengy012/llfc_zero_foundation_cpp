#pragma once

#ifdef MYMATH_EXPORTS
#define MYMATH_API __declspec(dllexport)
#else
#define MYMATH_API __declspec(dllimport)
#endif

extern "C"
{
    MYMATH_API int add_int(int a, int b);
    MYMATH_API float add_float(float a, float b);
}