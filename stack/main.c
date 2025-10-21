/* Custom stack implementation:
    push - add an element to the top of the stack
    pop - remove an element from the top of the stack
https://en.cppreference.com/w/cpp/container/stack.html
*/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <conio.h>
#include "murmurhash.h"

#define START_VALUE 2

struct userStack{ // user stack
    int * data;  // aray of data
    size_t stackCapacity; // maximum stack capacity
    size_t stackSize; // current stack fullness (stackSize <= stackCapcity)
    uint32_t hash;
    void (*pop)();
    void (*push)();
};

void pop();
void push(int userValue);
void select();
void menu();
void quite();
uint32_t seedValue(uint32_t seed);
void corruptData(); // Emulating data corruption in memory
int * allocateMemory(); // Initial memory allocation
void reAllocateMemory(size_t size); //

struct userStack uStack;
const uint8_t key = 98; // for murmurhash3
uint32_t seed = 0;

int main()
{
    uStack.pop = pop;
    uStack.push = push;
    uStack.stackCapacity = START_VALUE;
    uStack.stackSize = 0;
    menu();

    return 0;
}

void menu()
{
    int userChoice, userValue = 0;
    uStack.data = allocateMemory();
    uStack.hash = murmur3_32(&key, uStack.stackSize,seedValue(seed));

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
                      uStack.push(userValue);
                      break;
            case 'D': uStack.pop();
                      break;
            case 'S': putchar('\n');
                      select();
                      break;
            case 'Q': quite();
                      break;
            case 'C': corruptData();
                      break;
            default: printf("Unknown choice\n");
        }
    }
}

void select()
{
    if(murmur3_32(&key, uStack.stackSize,seedValue(seed)) != uStack.hash){
        free(uStack.data);
         exit(10);
    }
    for(int i = uStack.stackSize - 1; i >= 0; i--)
        printf("%d -> %d \n", i, *(uStack.data + i));
}

void pop()
{
    if(murmur3_32(&key, uStack.stackSize,seedValue(seed)) != uStack.hash){
        free(uStack.data);
        exit(10);
    }

    if(uStack.stackSize > 0 && uStack.stackSize <= uStack.stackCapacity){
        *(uStack.data + uStack.stackSize - 1) = 0;
        uStack.stackSize--;
        uStack.hash = murmur3_32(&key, uStack.stackSize,seedValue(seed));
        if( (uStack.stackSize * 2) == uStack.stackCapacity && uStack.stackCapacity > 2){
            uStack.stackCapacity = uStack.stackCapacity/2;
            printf("\nuStack.stackCapacity = %Iu\n", uStack.stackCapacity);
            reAllocateMemory(uStack.stackCapacity);
        }

    }else
        printf("\nStack is empty.\n");
}

void push(int userValue)
{
    if(murmur3_32(&key, uStack.stackSize,seedValue(seed)) != uStack.hash){
        free(uStack.data);
         exit(10);
    }
    if(uStack.stackCapacity - uStack.stackSize > 0){
        *(uStack.data + uStack.stackSize) = userValue;
        uStack.stackSize++;
        uStack.hash = murmur3_32(&key, uStack.stackSize,seedValue(seed));
    }
    else {
        uStack.stackCapacity = uStack.stackCapacity * 2;
        reAllocateMemory(uStack.stackCapacity);
        *(uStack.data + uStack.stackSize) = userValue;
        uStack.stackSize++;
        uStack.hash = murmur3_32(&key, uStack.stackSize,seedValue(seed));
    }
}

void quite()
{
    free(uStack.data);
    exit(EXIT_SUCCESS);
}
uint32_t seedValue(uint32_t seed)
{
    for(int i = uStack.stackSize; i > 0; i-- ){
        seed^= *(uStack.data + uStack.stackSize - 1);
        seed = seed << 2;
    }
    return seed;
}

void corruptData()
{
    if(uStack.stackSize > 0)
        *(uStack.data + uStack.stackSize - 1) = -1;
}

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
