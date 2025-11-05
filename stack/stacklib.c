#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#include "murmurhash.h"
#include "userstack.h"


void allocateMemory(struct userStack * uStack)
{
    uStack->data = (int *)calloc(uStack->stackCapacity, sizeof(int));
    if(!uStack->data)
        exit(1);
}

void reAllocateMemory(struct userStack * uStack)
{
    uStack->data = (int *)realloc( (void *)uStack->data, uStack->stackCapacity * sizeof(int) );
    if(!uStack->data)
        exit(1);
}

void push(struct userStack * uStack, int userValue, const uint8_t* key, uint32_t seed)
{
    if(murmur3_32(key, uStack->stackSize,seedValue(uStack, seed)) != uStack->hash){
        free(uStack->data);
         exit(10);
    }
    if(uStack->stackCapacity - uStack->stackSize > 0){
        *(uStack->data + uStack->stackSize) = userValue;
        uStack->stackSize++;
        uStack->hash = murmur3_32(key, uStack->stackSize,seedValue(uStack, seed));
    }
    else {
        uStack->stackCapacity = uStack->stackCapacity * 2;
        reAllocateMemory(uStack);
        *(uStack->data + uStack->stackSize) = userValue;
        uStack->stackSize++;
        uStack->hash = murmur3_32(key, uStack->stackSize,seedValue(uStack, seed));
    }
}

void pop(struct userStack * uStack, const uint8_t* key, uint32_t seed)
{
    if(murmur3_32(key, uStack->stackSize,seedValue(uStack, seed)) != uStack->hash){
        free(uStack->data);
        exit(10);
    }

    if(uStack->stackSize > 0 && uStack->stackSize <= uStack->stackCapacity){
        *(uStack->data + uStack->stackSize - 1) = 0;
        uStack->stackSize--;
        uStack->hash = murmur3_32(key, uStack->stackSize,seedValue(uStack, seed));
        if( (uStack->stackSize * 2) == uStack->stackCapacity && uStack->stackCapacity > 2){
            uStack->stackCapacity = uStack->stackCapacity/2;
            printf("\nuStack->stackCapacity = %llu\n", uStack->stackCapacity);
            reAllocateMemory(uStack);
        }

    }else
        printf("\nStack is empty.\n");
}
