#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
int main() //gcc tutorial3-5.c -o chall -m32
{
	int a, b, c;
	setbuf(stdin, 0);
	setbuf(stdout, 0);
	puts("Input 2 number\n");
	puts("A: ");
	scanf("%d", &a);
	puts("B: ");
	scanf("%d", &b);
	puts("That's ok i guess?\n");
	if (a < 0 || b < 0)
	{
		puts("A or B can't be negative\n");
		exit(1);
	}
	c = a + b; //make interger overflow! a = int_max; b = 1
	if (c < 0)
	{
		puts("You wi-, ... Wait that's illegal!\n");
		unsigned int fd = open("flag.txt", O_RDONLY);
		if(fd == -1)
		{
			exit(-1);
		}
		char flag[0x20];
		read(fd, flag, 0x20);
		printf("FLAG : %s", flag);
	}
}