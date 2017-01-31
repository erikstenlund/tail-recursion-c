#include "tail_recursion.h"

#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>

long recursive_sum(long n)
{
	static long sum = 0;
	sum += n;

	if (n == 1) {
		return sum;
	} else {
		n--;
		tail_call_args(1, n);
		tail_call(recursive_sum);
	}
}

int main(int argc, const char *argv[])
{
	long n = atol(argv[1]);
	long res = recursive_sum(n);
	printf("sum(%ld) = %ld\n", n, res);
	return 0;
}
