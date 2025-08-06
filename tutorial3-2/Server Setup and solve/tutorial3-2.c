/*
	stack exec -> NopSled
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int rand_offset = 0;

void important(void) __attribute__((naked, unused));
void important()
{
	__asm__(
		"leave;"
		"mov rand_offset(%rip), %rax;"
		"add %rsp, %rax;"
		"jmp %rax;"
	);
}


int main() //gcc tutorial3-2.c -o chall -fno-stack-protector -z execstack
{
	char input[0x10];
	srand(time(NULL));
	rand_offset = rand() % 500;

	scanf("%s", input);
}