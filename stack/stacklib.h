#pragma once

#include <stdint.h>
#include "userstack.h"

void push(userStack * uStack, int userValue, const uint8_t* key, uint32_t seed);
void pop(userStack * uStack, const uint8_t* key, uint32_t seed);
int allocateMemory(userStack * uStack); // Initial memory allocation
int reAllocateMemory(userStack * uStack); //
