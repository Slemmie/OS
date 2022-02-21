// convert int to char*

#pragma once

// value to convert, buffer to store result (null terminated), base range [2, 16]
// returns non-zero value if an error occurred
// make sure buffer has enough room for the string representation, itoa does not alloca anything
int itos(int value, char* buffer, int base);
