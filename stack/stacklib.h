#ifndef STACKLIB_H_INCLUDED
#define STACKLIB_H_INCLUDED
#include <stdint.h>
#endif // STACKLIB_H_INCLUDED
void push(int userValue, const uint8_t* key, uint32_t seed);
void pop(const uint8_t* key, uint32_t seed);
int * allocateMemory(); // Initial memory allocation
void reAllocateMemory(size_t size); //
