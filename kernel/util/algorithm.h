// simple algorithm type stuff

#pragma once

#include "types.h"

// return minimum of _v1 and _v2
#define min(_v1, _v2) (_v1 < _v2 ? _v1 : _v2)
// return maximum of _v1 and _v2
#define max(_v1, _v2) (_v1 > _v2 ? _v1 : _v2)

// return absolute value of _v
#define abs(_v) (max(_v, -_v))
