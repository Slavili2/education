#pragma once

#include <stdint.h>
#include "userstack.h"

void push(struct userStack * uStack, int userValue, const uint8_t* key, uint32_t seed);
void pop(struct userStack * uStack, const uint8_t* key, uint32_t seed);
int allocateMemory(struct userStack * uStack); // Initial memory allocation
int reAllocateMemory(struct userStack * uStack); //
