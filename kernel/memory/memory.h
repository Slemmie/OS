// main memory header
// has (or will have later) memory utility such as memory allocations/frees/sets/etc.

#pragma once

// memory block header
// stores whether it is being used
// stores the size

typedef enum {
	
	_MBH_STATE_NONE      = 0,
	_MBH_STATE_OCCUPIED  = 1,
	_MBH_STATE_AVAILABLE = 2
	
} _MBH_State;

typedef struct {
	
	unsigned int size;
	
	unsigned char state;
	
} _MBH;

#define _MBH_SIZE sizeof(_MBH)

#define _MBH_EMPTY ((_MBH) { 0, _MBH_STATE_NONE });
