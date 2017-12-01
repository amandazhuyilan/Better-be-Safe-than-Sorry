// A simple c code to get the current stack pointer 
// Compile it with: gcc -m32 -o stack

#include <stdio.h>

unsigned long get_sp()
{
	__asm__("mov %esp, %eax");
}

main()
{
	printf("SP is: %lx\n\n", get_sp());
}
