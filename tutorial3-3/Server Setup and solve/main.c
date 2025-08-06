/*
	I hope today you learn that \"Implicit declaration\" or the other name \"uninitialize variable\"\n" \
	"will locate in .bss section as same as global variable ^^\n
*/

#include <stdio.h>
#define flag "pwn{1mplic1t_d3cl4r4ti0n!}"
			 
			 
void setup(void* ptr)
{
	setvbuf(stderr, 0LL, 2, 0LL);
	setvbuf(stdout, 0LL, 2, 0LL);
    setvbuf(stdin, 0LL, 1, 0LL);
}

char input[10];

extern char **__libc_argv;

int main() //gcc -no-pie -static -fstack-protector-all -o chall main.c
{
	setup(flag);
	printf("Here is my argv : %lx, Your input : %lx\n", __libc_argv, input);
	scanf("%s", input);
	puts("Your argv");
	for (int i = 0; *__libc_argv!= 0;__libc_argv+=8)
	{
		printf("%s\n", *__libc_argv);
	}
}
