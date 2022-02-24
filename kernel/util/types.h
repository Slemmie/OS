// typedeffing

#pragma once

typedef          char        int_8;
typedef unsigned char       uint_8;

typedef          short      int_16;
typedef unsigned short     uint_16;

typedef          int        int_32;
typedef unsigned int       uint_32;

typedef          long long  int_64;
typedef unsigned long long uint_64;

typedef _Bool bool_t;
#ifndef __cplusplus
#define true  1
#define false 0
#endif

typedef uint_64 size_t;

typedef       float   float_4;
typedef      double   float_8;
typedef long double  float_12;

typedef       float  double_4;
typedef      double  double_8;
typedef long double double_12;
