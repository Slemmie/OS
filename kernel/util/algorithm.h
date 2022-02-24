// simple algorithm type stuff

#pragma once

#include "types.h"

// return minimum of _v1 and _v2
#define min(_v1, _v2) ((_v1) < (_v2) ? (_v1) : (_v2))
// return maximum of _v1 and _v2
#define max(_v1, _v2) ((_v1) > (_v2) ? (_v1) : (_v2))

// return absolute value of _v
#define abs(_v) (max((_v), -(_v)))

// swaps _v1 and _v2
#define swap(_v1, _v2) ({     \
	typeof(_v1) __v1 = (_v1); \
	typeof(_v2) __v2 = (_v2); \
	(_v1) = __v2;             \
	(_v2) = __v1;             \
})

// swaps _v1 and _v2 if _cmp returns non-zero value
#define swap_if(_v1, _v2, _cmp) ({ \
	if (_cmp(_v1, _v2)) {          \
		swap(_v1, _v2);            \
	}                              \
})

// reverses array of given size
// end has to be >= begin
#define reverse(_begin, _end) ({                             \
	size_t __size = (_end) - (_begin);                       \
	for (size_t __i = 0; __i < __size / (size_t) 2; __i++) { \
		swap(*(_begin + __i), *(_end - __i - 1));            \
	}                                                        \
})

// sorts the given range of elements using a user defined comparing function
// user defined function should return true on two elements if arg1 should be AFTER arg2
// using heap sort (in place)
void sort(void* begin, void* end, size_t bytes_per_element, const bool_t (*cmp) (void*, void*));
