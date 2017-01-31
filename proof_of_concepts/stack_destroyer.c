#include <stdio.h>
#include <stdlib.h>

long tail_recursive_sum(long n)
{
	static long sum = 0;
	sum += n;
	if (n == 1) {
		return sum;
	} else {
		long a = (long) &tail_recursive_sum + 4;
		__asm__
		(
		"dec %%rdi \n"
		"mov %[a], %%rax \n"
		"jmp *%%rax \n"
		:
		: [a] "m" (a)
		);
	}
}

long recursive_sum(long n)
{
	if (n == 1) {
		return 1;
	} else {
		return n + recursive_sum(n - 1);
	}
}

int main(int argc, const char *argv[])
{
	long n = atol(argv[1]);
	long func = atoi(argv[2]);
	long res;
	if (func) {
		res = recursive_sum(n);
	} else {
		res = tail_recursive_sum(n);
	}
	printf("sum(%ld) = %ld\n", n, res);
	return 0;
}
