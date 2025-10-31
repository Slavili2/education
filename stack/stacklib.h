#ifndef STACKLIB_H_INCLUDED
#define STACKLIB_H_INCLUDED
#include <stdint.h>
#endif // STACKLIB_H_INCLUDED
#include "userstack.h"

void push(struct userStack * uStack, int userValue, const uint8_t* key, uint32_t seed);
void pop(struct userStack * uStack, const uint8_t* key, uint32_t seed);
void allocateMemory(struct userStack * uStack); // Initial memory allocation
void reAllocateMemory(struct userStack * uStack); //
