# Macros for tail recursion in C.

## Background
Using recursion for iteration is a pattern used in many
functional languages. For longer iterations this might lead
to stack overflow due to the amount of stack frames needed 
for the recursive function calls. A common way to solve
this is by using tail recursion. This is done by reusing the old 
stack frame when the last statement of a function is a recursive
call to the same function.

This is of course not needed in C due to its language constructs for iteration,
but the best way to learn something is by hacking it together with a couple
of filthy macros. So take this for what it is.

## Usage
The macro `tail_call_args(argc, args...)` takes six or less arguments and
updates the parameter registers according to System V AMD64 ABI specification.
A function pointer to the current pointer the needs to be passed to the
macro `tail_call(func)` for the actual jump.

No expressions may be passed as arguments to `tail_call_args` the input to the 
assembly instructions needs to be valid memory at compile time.

Using compiler optimizations while using the tail recursion macros will probably make everything blow up due to it being undefined actions.

### Example
```c
#include "tail_recursion.h"

...

void rec(long n)
{
	if (n == 0) {
		/* Done */
		return;
	} else {
		n -= 1;
		tail_call_args(1, n); /* Set arguments */
		tail_call(rec); /* Call rec using tail recursion */
	}
}
```

