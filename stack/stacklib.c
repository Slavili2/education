#ifndef STACKLIB_C_INCLUDED
#define STACKLIB_C_INCLUDED
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "murmurhash.h"
#include "userlib.h"
struct userStack{ // user stack
    int * data;  // aray of data
    size_t stackCapacity; // maximum stack capacity
    size_t stackSize; // current stack fullness (stackSize <= stackCapcity)
    uint32_t hash;
    void (*pop)(const uint8_t* key, uint32_t seed);
    void (*push)(int userValue, const uint8_t* key, uint32_t seed);
};
struct userStack uStack;
#endif // STACKLIB_C_INCLUDED

int * allocateMemory()
{
    int * tempData = NULL;
    tempData = (int *)calloc(uStack.stackCapacity, sizeof(int));
    if(!tempData)
        exit(1);
    return tempData;
}

void reAllocateMemory(size_t size)
{
    uStack.data = (int *)realloc( (void *)uStack.data, size * sizeof(int) );
    if(!uStack.data)
        exit(1);
}

void push(int userValue, const uint8_t* key, uint32_t seed)
{
    if(murmur3_32(key, uStack.stackSize,seedValue(seed)) != uStack.hash){
        free(uStack.data);
         exit(10);
    }
    if(uStack.stackCapacity - uStack.stackSize > 0){
        *(uStack.data + uStack.stackSize) = userValue;
        uStack.stackSize++;
        uStack.hash = murmur3_32(key, uStack.stackSize,seedValue(seed));
    }
    else {
        uStack.stackCapacity = uStack.stackCapacity * 2;
        reAllocateMemory(uStack.stackCapacity);
        *(uStack.data + uStack.stackSize) = userValue;
        uStack.stackSize++;
        uStack.hash = murmur3_32(key, uStack.stackSize,seedValue(seed));
    }
}

void pop(const uint8_t* key, uint32_t seed)
{
    if(murmur3_32(key, uStack.stackSize,seedValue(seed)) != uStack.hash){
        free(uStack.data);
        exit(10);
    }

    if(uStack.stackSize > 0 && uStack.stackSize <= uStack.stackCapacity){
        *(uStack.data + uStack.stackSize - 1) = 0;
        uStack.stackSize--;
        uStack.hash = murmur3_32(key, uStack.stackSize,seedValue(seed));
        if( (uStack.stackSize * 2) == uStack.stackCapacity && uStack.stackCapacity > 2){
            uStack.stackCapacity = uStack.stackCapacity/2;
            printf("\nuStack.stackCapacity = %Iu\n", uStack.stackCapacity);
            reAllocateMemory(uStack.stackCapacity);
        }

    }else
        printf("\nStack is empty.\n");
}
