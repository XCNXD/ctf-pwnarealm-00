#include <stdio.h>

int main() //gcc -no-pie -fno-stack-protector main.c -o challx
{
	char name[29];

	setbuf(stdout, 0LL);
    setbuf(stdin, 0LL);
	puts("What is your name");
	scanf("%23s", name);
	printf(name);
	printf(" uhm, You've got a nice name. \" %s \" Nice to meet you.\n", name);
	puts("Good bye...");

}