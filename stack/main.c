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
#include "userlib.h"
#include "stacklib.h"

#define START_VALUE 2

struct userStack{ // user stack
    int * data;  // aray of data
    size_t stackCapacity; // maximum stack capacity
    size_t stackSize; // current stack fullness (stackSize <= stackCapcity)
    uint32_t hash;
    void (*pop)(const uint8_t* key, uint32_t seed);
    void (*push)(int userValue, const uint8_t* key, uint32_t seed);
};

struct userStack uStack;
const uint8_t key = 98; // for murmurhash3
uint32_t seed = 0;

int main()
{
    uStack.pop = pop;
    uStack.push = push;
    uStack.stackCapacity = START_VALUE;
    uStack.stackSize = 0;
    menu(&key, seed);

    return 0;
}
