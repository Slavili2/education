#pragma once
#include "userstack.h"
void select(struct userStack * uStack, const uint8_t* key, uint32_t seed);
uint32_t seedValue(struct userStack * uStack, uint32_t seed);
void quite(struct userStack * uStack);
void corruptData(struct userStack * uStack); // Emulating data corruption in memory
void menu(struct userStack * uStack, const uint8_t* key, uint32_t seed);
