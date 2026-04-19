#include <stdio.h>
#include <assert.h>
#include "usermath.h"

int main()
{
	int x, y, result = 0, nItem=0;

	printf("Enter x and y: ");
	nItem = scanf("%d%d", &x, &y);
	assert(2 == nItem);
	assert(0 != y);
	result = gcd(x, y);
	
	printf("HOK(%d;%d)=%d\n", x, y, result);

	return 0;
}
