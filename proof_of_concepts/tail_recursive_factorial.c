#include <stdio.h>
#include <stdlib.h>

long factorial(long n, long product)
{
	if (n == 1) {
		return product;
	} else {
		/* Dont try this at home */
		long a = (long) &factorial + 4;
		__asm__
		(
		"mov %%rsi, %%rax \n"
		"mul %%rdi \n"
		"mov %%rax, %%rsi \n"
		"dec %%rdi \n"
		"mov %[a], %%rax \n"
		"jmp *%%rax \n"
		:
		: [a] "m" (a)
		);
	}

	return 1;
}

int main(int argc, const char *argv[])
{
	long n = atol(argv[1]);
	long res = factorial(n, 1);

	printf("%ld! = %ld\n", n, res);
	return 0;
}
