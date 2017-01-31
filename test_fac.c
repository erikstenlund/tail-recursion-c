#include <stdio.h>
#include <stdlib.h>
#include "tail_recursion.h"

long factorial(long n, long product)
{
	if (n == 1)
		return product;

	product *= n;
	n--;
	tail_call_args(2, n, product);
	tail_call(factorial);
}
int main(int argc, const char *argv[])
{
	long n = atol(argv[1]);
	printf("%d! = %ld\n", n, factorial(n, 1));
	return 0;
}
