#pragma once

#include <stdint.h>
#include "userstack.h"

uint32_t seedValue(struct userStack * uStack, uint32_t seed);
uint32_t murmur3_32(const uint8_t* key, size_t len, uint32_t seed);
