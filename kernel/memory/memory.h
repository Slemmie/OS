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
	
	// size excluding header block
	unsigned int size;
	
	// occupied?, available?
	// has '_MBH_State' value
	unsigned char state;
	
} _MBH;

// size of memory block header - add 4 null-bytes of padding
// currently 8 bytes
#define _MBH_SIZE (sizeof(_MBH) + 3)

#define _MBH_EMPTY ((_MBH) { 0, _MBH_STATE_NONE });

// memset, set a block of memory starting at ptr and ending at ptr + size to value
// size is a number of BYTES
// value parameter is an unsigned byte, cast to this when using memset
// memory is set per-byte, so values cannot exceed 255
void memset(void* ptr, unsigned char value, unsigned int size);

// memcpy, copy values in one memory block to another
// size is number of BYTES to copy
// copy from src to dest
void memcpy(void* dest, void* src, unsigned int size);


// 4 KB block size
#define _PM_BLOCK_SIZE (4u * 1024u)

// initialize physical memory starting at pm_begin
void init_paging();
