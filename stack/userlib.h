#pragma once

#include "userstack.h"

void select(userStack * uStack, const uint8_t* key, uint32_t seed);
uint32_t seedValue(userStack * uStack, uint32_t seed);
void quite(userStack * uStack);
void corruptData(userStack * uStack); // Emulating data corruption in memory
void menu(userStack * uStack, const uint8_t* key, uint32_t seed);
