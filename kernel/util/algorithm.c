// implementing some functionality of algorithm.h

#include "algorithm.h"

// sorting utility
void _heapify(size_t ptr, void* begin, void* end, size_t bytes_per_element, const bool_t (*cmp) (void*, void*)) {
	void* last = begin + ptr;
	void* left = begin + (ptr << (size_t) 1) + (size_t) 1;
	void* right = begin + (ptr << (size_t) 1) + (size_t) 2;
	if (left < end && !cmp(left, last)) {
		last = left;
	}
	if (right < end && !cmp(right, last)) {
		last = right;
	}
	if (last != begin + ptr) {
		for (size_t swaps = 0; swaps < bytes_per_element; swaps++) {
			swap(
			*((uint_8*)(((size_t) (begin + ptr)) * bytes_per_element + swaps)),
			*((uint_8*)(((size_t) (last       )) * bytes_per_element + swaps)));
		}
		_heapify((size_t) (last - begin), begin, end, bytes_per_element, cmp);
	}
}

// sorts a range of elements
void sort(void* begin, void* end, size_t bytes_per_element, const bool_t (*cmp) (void*, void*)) {
	size_t size = (size_t) (end - begin);
	if (!size) {
		return;
	}
	for (size_t i = (size >> (size_t) 1); i; i--) {
		_heapify(i - 1, begin, end, bytes_per_element, cmp);
	}
	for (size_t i = size - 1; i; i--) {
		for (size_t swaps = 0; swaps < bytes_per_element; swaps++) {
			swap(
			*((uint_8*)(((size_t) (begin    )) * bytes_per_element + swaps)),
			*((uint_8*)(((size_t) (begin + i)) * bytes_per_element + swaps)));
		}
		_heapify(0, begin, begin + i, bytes_per_element, cmp);
	}
}
