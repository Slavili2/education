#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include "murmurhash.h"
#include "stacklib.h"
#include "userstack.h"

void select(userStack * uStack, const uint8_t* key, uint32_t seed)
{
    if(murmur3_32(key, uStack->stackSize,seedValue(uStack, seed)) != uStack->hash){
        free(uStack->data);
        printf("\nThe data is corrupted\n");
        exit(EXIT_FAILURE);
    }
    for(int i = uStack->stackSize - 1; i >= 0; i--)
        printf("%d -> %d \n", i, *(uStack->data + i));
}


void quit(userStack * uStack)
{
    free(uStack->data);
}

int enterValue(int * userValue)
{
    int result = 0;
    printf("\nEnter value(integer): ");
    result = scanf(" %d", userValue);
    while (getchar() != '\n');
    return result;
}

void corruptData(userStack * uStack)
{
    if(uStack->stackSize > 0)
        *(uStack->data + uStack->stackSize - 1) = -1;
}

void help(){
    printf("\na - add value (integer) into stack\
           \nd - delete top element\
           \ns - display on screen\
           \nq - quit program\
           \nc - corrupt data\n");
}

void menu(userStack * uStack, const uint8_t* key, uint32_t seed)
{
    switchOperations userChoice;
    int userValue = 0;
    if(allocateMemory(uStack)){
        printf("\nOut of memory!\n");
        exit(EXIT_FAILURE);
    }

    uStack->hash = murmur3_32(key, uStack->stackSize,seedValue(uStack, seed));

    do{
        help();
        printf("\nSelect an action: ");
        userChoice = getchar();
        while(getchar() != '\n');

        switch(userChoice){
            case ADD:
                 if(enterValue(&userValue) == 0){
                    printf("\nYou enter bad value!\n");
                    continue;
                 }
                 uStack->push(uStack, userValue, key, seed);
                 break;
            case DELETE:
                 uStack->pop(uStack, key, seed);
                 break;
            case SHOW:
                 putchar('\n');
                 select(uStack, key, seed);
                 break;
            case QUIT:
                 quit(uStack);
                 break;
            case CORRUPT:
                 corruptData(uStack);
                 break;
            default:
                 printf("\nUnknown an action!!!\n");
        }
    }while('q' != userChoice);
}

