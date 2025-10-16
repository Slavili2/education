#ifndef MURMURHASH_H_INCLUDED
#define MURMURHASH_H_INCLUDED
#include <stdint.h>
#endif // MURMURHASH_H_INCLUDED

uint32_t murmur3_32(const uint8_t* key, size_t len, uint32_t seed);
