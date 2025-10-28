#ifndef USERLIB_C_INCLUDED
#define USERLIB_C_INCLUDED
#include "murmurhash.h"
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include "stacklib.h"
#include "userstack.h"
#endif // USERLIB_C_INCLUDED

uint32_t seedValue(struct userStack * uStack, uint32_t seed)
{
    for(int i = uStack->stackSize; i > 0; i-- ){
        seed^= *(uStack->data + uStack->stackSize - 1);
        seed = seed << 2;
    }
    return seed;
}

void select(struct userStack * uStack, const uint8_t* key, uint32_t seed)
{
    if(murmur3_32(key, uStack->stackSize,seedValue(uStack, seed)) != uStack->hash){
        free(uStack->data);
         exit(10);
    }
    for(int i = uStack->stackSize - 1; i >= 0; i--)
        printf("%d -> %d \n", i, *(uStack->data + i));
}


void quite(struct userStack * uStack)
{
    free(uStack->data);
    exit(EXIT_SUCCESS);
}


void corruptData(struct userStack * uStack)
{
    if(uStack->stackSize > 0)
        *(uStack->data + uStack->stackSize - 1) = -1;
}

void menu(struct userStack * uStack, const uint8_t* key, uint32_t seed)
{
    int userChoice, userValue = 0;
    allocateMemory(uStack);
    uStack->hash = murmur3_32(key, uStack->stackSize,seedValue(uStack, seed));

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
                      uStack->push(uStack, userValue, key, seed);
                      break;
            case 'D': uStack->pop(uStack, key, seed);
                      break;
            case 'S': putchar('\n');
                      select(uStack, key, seed);
                      break;
            case 'Q': quite(uStack);
                      break;
            case 'C': corruptData(uStack);
                      break;
            default: printf("Unknown choice\n");
        }
    }
}
