#define tail_call(func) \
{ \
	long addr = (long) &func + 4; \
	__tail_call(addr); \
}

#define __tail_call(addr) \
{ \
	__asm__ \
	( \
	"mov %[x], %%rax \n" \
	"jmp *%%rax" \
	: : [x] "m" (addr) \
	); \
}

#define tail_call_args(argc, args...) \
{ \
        __tail_call_##argc(args); \
}

#define __tail_call_1(a) \
{ \
        __tail_call_args(1, a, a, a, a, a, a); \
}

#define __tail_call_2(a, b) \
{ \
        __tail_call_args(2, a, b, a, a, a, a); \
}

#define __tail_call_3(a, b, c) \
{ \
        __tail_call_args(3, a, b, c, a, a, a); \
}

#define __tail_call_4(a, b, c, d) \
{ \
        __tail_call_args(4, a, b, c, d, a, a); \
}

#define __tail_call_5(a, b, c, d, e) \
{ \
        __tail_call_args(5, a, b, c, d, e, a); \
}

#define __tail_call_6(a, b, c, d, e, f) \
{ \
        __tail_call_args(6, a, b, c, d, e, f); \
}

/* Horrible but there is no way to specify the register
 * during run time. */
#define __tail_call_args(argc, arg_1, arg_2, arg_3, arg_4, arg_5, arg_6) \
{ \
	switch (argc) { \
		case 6: \
			__asm__("mov %[arg], %%r9": : [arg] "m" (arg_6)); \
		case 5: \
			__asm__("mov %[arg], %%r8": : [arg] "m" (arg_5)); \
		case 4: \
			__asm__("mov %[arg], %%rcx": : [arg] "m" (arg_4)); \
		case 3: \
			__asm__("mov %[arg], %%rdx": : [arg] "m" (arg_3)); \
		case 2: \
			__asm__("mov %[arg], %%rsi": : [arg] "m" (arg_2)); \
		case 1: \
			__asm__("mov %[arg], %%rdi": : [arg] "m" (arg_1)); \
		default: \
			break; /* Unreachable */ \
	} \
}
/* This is assuming argc < 7, System V AMD64 ABI
 * and only integer/pointer arguments.
 * ToDo: Check rcx vs r10 on linux.
 */

