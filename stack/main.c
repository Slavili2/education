/* Custom stack implementation:
    push - add an element to the top of the stack
    pop - remove an element from the top of the stack
https://en.cppreference.com/w/cpp/container/stack.html
*/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "murmurhash.h"
#include "userlib.h"
#include "stacklib.h"
#include "userstack.h"

//#define START_VALUE 0xFFFFFFFFFFFFFF
#define START_VALUE 2

int main()
{
    struct userStack uStack;
    const uint8_t key = 98; // for murmurhash3
    uint32_t seed = 0;

    uStack.data = NULL;
    uStack.pop = pop;
    uStack.push = push;
    uStack.stackCapacity = START_VALUE;
    uStack.stackSize = 0;
    menu(&uStack, &key, seed);

    return 0;
}
