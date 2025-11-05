#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

#include "murmurhash.h"
#include "stacklib.h"
#include "userstack.h"

void select(struct userStack * uStack, const uint8_t* key, uint32_t seed)
{
    if(murmur3_32(key, uStack->stackSize,seedValue(uStack, seed)) != uStack->hash){
        free(uStack->data);
         exit(10);
    }
    for(int i = uStack->stackSize - 1; i >= 0; i--)
        printf("%d -> %d \n", i, *(uStack->data + i));
}


void quit(struct userStack * uStack)
{
    free(uStack->data);
}


void corruptData(struct userStack * uStack)
{
    if(uStack->stackSize > 0)
        *(uStack->data + uStack->stackSize - 1) = -1;
}

void help(){
    printf("\na - add value into stack\
           \nd - delete top element\
           \ns - display on screen\
           \nq - quit program\
           \nc - corrupt data\n");
}

void menu(struct userStack * uStack, const uint8_t* key, uint32_t seed)
{
    switchOperations userChoice;
    int userValue = 0;
    allocateMemory(uStack);
    uStack->hash = murmur3_32(key, uStack->stackSize,seedValue(uStack, seed));

    do{
        help();
        printf("\nSelect an action: ");
        userChoice = getchar();
        while (getchar() != '\n');

        switch(userChoice){
            case ADD: printf("\nEnter value: ");
                      scanf(" %d", &userValue);
                      while (getchar() != '\n');
                      uStack->push(uStack, userValue, key, seed);
                      break;
            case DELETE: uStack->pop(uStack, key, seed);
                         break;
            case SHOW: putchar('\n');
                       select(uStack, key, seed);
                       break;
            case QUIT: quit(uStack);
                       break;
            case CORRUPT: corruptData(uStack);
                          break;
            default: printf("\nUnknown an action!!!\n");
        }
    }while('q' != userChoice);
}

