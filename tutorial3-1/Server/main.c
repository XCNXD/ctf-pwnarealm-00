#include <stdio.h>
#include <stdlib.h>
void setup()
{
	setvbuf(stderr, 0LL, 2, 0LL);
	setvbuf(stdout, 0LL, 2, 0LL);
    setvbuf(stdin, 0LL, 1, 0LL);
}

void win()
{
	system("/bin/sh");
}

int main() //gcc main.c -o challx -fstack-protector-all -no-pie
{
	setup();
	char buffer[56];
	printf("Hey!, Don't forget this ok? %lx", *(long int*)(buffer+56));//56+16-10
	puts("\nwhat do you have?");
	scanf("%s", buffer);
}