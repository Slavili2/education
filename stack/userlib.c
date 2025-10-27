#ifndef USERLIB_C_INCLUDED
#define USERLIB_C_INCLUDED
#include "murmurhash.h"
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include "stacklib.h"

struct userStack{ // user stack
    int * data;  // aray of data
    size_t stackCapacity; // maximum stack capacity
    size_t stackSize; // current stack fullness (stackSize <= stackCapcity)
    uint32_t hash;
    void (*pop)(const uint8_t* key, uint32_t seed);
    void (*push)(int userValue, const uint8_t* key, uint32_t seed);
};
struct userStack uStack;
#endif // USERLIB_C_INCLUDED

uint32_t seedValue(uint32_t seed)
{
    for(int i = uStack.stackSize; i > 0; i-- ){
        seed^= *(uStack.data + uStack.stackSize - 1);
        seed = seed << 2;
    }
    return seed;
}

void select(const uint8_t* key, uint32_t seed)
{
    if(murmur3_32(key, uStack.stackSize,seedValue(seed)) != uStack.hash){
        free(uStack.data);
         exit(10);
    }
    for(int i = uStack.stackSize - 1; i >= 0; i--)
        printf("%d -> %d \n", i, *(uStack.data + i));
}


void quite()
{
    free(uStack.data);
    exit(EXIT_SUCCESS);
}


void corruptData()
{
    if(uStack.stackSize > 0)
        *(uStack.data + uStack.stackSize - 1) = -1;
}

void menu(const uint8_t* key, uint32_t seed)
{
    int userChoice, userValue = 0;
    uStack.data = allocateMemory();
    uStack.hash = murmur3_32(key, uStack.stackSize,seedValue(seed));

    while(1){
        printf("\nA - add value into stack\
               \nD - delete top element\
               \nS - display on screen\
               \nQ - quit program\
               \nC - corrupt data\n");
        printf("\nYour choice: ");
        fflush(stdin);
        userChoice = getchar();
        userChoice = toupper(userChoice);

        switch(userChoice){
            case 'A': printf("\nEnter value: ");
                      fflush(stdin);
                      scanf(" %d", &userValue);
                      uStack.push(userValue, key, seed);
                      break;
            case 'D': uStack.pop(key, seed);
                      break;
            case 'S': putchar('\n');
                      select(key, seed);
                      break;
            case 'Q': quite();
                      break;
            case 'C': corruptData();
                      break;
            default: printf("Unknown choice\n");
        }
    }
}
