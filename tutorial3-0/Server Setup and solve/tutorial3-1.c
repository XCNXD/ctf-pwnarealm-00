/*
Basic ret2win and calculate address
*/

#include <stdio.h>
#define format "Your format string : %p"
void win()
{
	system("/bin/sh");
}

int main() //gcc tutorial3-1 -o chall -pie -fno-stack-protector
{
	char input[0x10];
	setbuf(stdin, 0);
	setbuf(stdout, 0);
	printf(format, format);
	scanf("%s", input);
}